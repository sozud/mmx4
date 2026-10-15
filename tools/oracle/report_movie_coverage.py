#!/usr/bin/env python3

import argparse
import datetime
import json
import os
from pathlib import Path
import re
import subprocess

from run_replay_regression import load_sync, sha256, validate_replay

ROOT = Path(__file__).resolve().parents[2]
METRICS = ("lines", "functions", "regions", "branches")


def command(*args, cwd=ROOT):
    return subprocess.check_output([str(arg) for arg in args], cwd=cwd, text=True)


def checked_movies(root, manifest, raw, results, binary_hash, revision):
    movies, profiles, stems = [], [], set()
    for line in manifest.read_text().splitlines():
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        parts = line.split()
        if len(parts) not in (2, 3) or (len(parts) == 3 and parts[2] != "object-state"):
            raise ValueError(f"invalid manifest entry: {line}")
        replay, digest = parts[:2]
        path = root / replay
        if path.stem in stems:
            raise ValueError(f"duplicate movie stem: {path.stem}")
        stems.add(path.stem)
        expected = validate_replay(path)
        if expected["sha256"] != digest:
            raise ValueError(f"{replay}: manifest digest mismatch")
        sync_path = Path(str(path) + ".sync.json")
        sync = load_sync(sync_path, expected)
        sync_hash = sha256(sync_path) if sync else None
        evidence = sorted((results / path.stem).glob("*/metadata.json"))
        if len(evidence) != 1:
            raise ValueError(f"{replay}: expected exactly one regression result")
        result = json.loads(evidence[0].read_text())
        checks = {
            "sha256": digest, "sync_sha256": sync_hash, "commit": revision,
            "binary_sha256": binary_hash, "status": 0, "pc_exit": 0,
            "frames": expected["frames"], "pc_frames": expected["frames"],
            "psx_frames": expected["frames"],
        }
        for name, value in checks.items():
            if name not in result or result[name] != value:
                raise ValueError(f"{replay}: regression {name} does not match {value!r}")
        if result.get("psx_exit", 0) != 0:
            raise ValueError(f"{replay}: PSX oracle failed")
        runs = sorted((raw / path.stem).glob("*.profraw"))
        if len(runs) != 1 or not runs[0].stat().st_size:
            raise ValueError(f"{replay}: expected one nonempty raw profile")
        if not (
            result.get("pc_started_ns", 0) > 0
            and result["pc_started_ns"] <= runs[0].stat().st_mtime_ns
            <= result.get("pc_finished_ns", 0)
        ):
            raise ValueError(f"{replay}: profile was not written during this check")
        profiles.extend(runs)
        movies.append({"movie": replay, "sha256": digest, "sync_sha256": sync_hash,
                       "samples": expected["frames"], "status": "passed"})
    if not movies:
        raise ValueError("manifest has no movies")
    if set(raw.rglob("*.profraw")) != set(profiles):
        raise ValueError("unexpected raw profiles; use a fresh coverage directory")
    return movies, profiles


def game_files(export, root):
    files = []
    for entry in export["data"][0]["files"]:
        path = Path(entry["filename"])
        if not path.is_absolute():
            path = root / path
        try:
            relative = path.resolve().relative_to(root).as_posix()
        except ValueError:
            continue
        if not (relative.startswith("src/main/") or relative == "src/pc/placeholder.c"):
            continue
        files.append({"file": relative, **{
            metric: {"covered": entry["summary"][metric]["covered"],
                     "count": entry["summary"][metric]["count"]}
            for metric in METRICS
        }})
    if not files:
        raise ValueError("binary has no coverage for game C")
    return sorted(files, key=lambda entry: entry["file"])


def totals(files):
    return {metric: {
        "covered": sum(entry[metric]["covered"] for entry in files),
        "count": sum(entry[metric]["count"] for entry in files),
    } for metric in METRICS}


def fraction(value):
    covered, count = value["covered"], value["count"]
    return f"{covered}/{count} ({100 * covered / count:.2f}%)" if count else "0/0 (n/a)"


def unit_results(log):
    text = log.read_text()
    passed = len(re.findall(r"^PASS\t", text, re.M))
    failed = len(re.findall(r"^FAIL\t", text, re.M))
    if failed or not passed:
        raise ValueError(f"unit tests: {passed} passed, {failed} failed")
    return {"passed": passed}


def markdown(report):
    sources = report.get("sources")
    lines = ["# Code coverage", "",
             f"Revision: `{report['revision']}`. "
             f"Movies passed: **{len(report['movies'])}/{len(report['movies'])}**."
             + (f" Unit test cases passed: **{report['unit_tests']['passed']}**." if sources else ""), ""]
    if report["ci_run"]:
        lines += [f"[CI run and detailed coverage artifacts]({report['ci_run']})", ""]
    if sources:
        lines += ["| Metric | Movies | Unit tests | Total |", "| --- | --- | --- | --- |"]
        lines += [f"| {metric.capitalize()} | " + " | ".join(
            fraction(sources[name][metric]) for name in ("movies", "unit_tests", "combined")) + " |"
            for metric in METRICS]
        lines += ["", "## Files", "",
                  "| File | Lines (movies) | Lines (unit tests) | Lines | Functions | Regions | Branches |",
                  "| --- | --- | --- | --- | --- | --- | --- |"]
        by_source = {name: {entry["file"]: entry for entry in report["source_files"][name]}
                     for name in ("movies", "unit_tests")}
        for entry in report["files"]:
            split = [fraction(by_source[name][entry["file"]]["lines"]) if entry["file"] in by_source[name]
                     else "0/0 (n/a)" for name in ("movies", "unit_tests")]
            lines.append("| `" + entry["file"] + "` | " + " | ".join(
                split + [fraction(entry[metric]) for metric in METRICS]) + " |")
    else:
        lines += ["| Metric | Covered / total |", "| --- | --- |"]
        lines += [f"| {metric.capitalize()} | {fraction(report['totals'][metric])} |"
                  for metric in METRICS]
        lines += ["", "## Files", "", "| File | Lines | Functions | Regions | Branches |",
                  "| --- | --- | --- | --- | --- |"]
        for entry in report["files"]:
            lines.append("| `" + entry["file"] + "` | " + " | ".join(
                fraction(entry[metric]) for metric in METRICS) + " |")
    lines += ["", "## Movies", "", "| Movie | Input samples | Result |",
              "| --- | --- | --- |"]
    lines += [f"| `{Path(movie['movie']).name}` | {movie['samples']} | Passed |"
              for movie in report["movies"]]
    lines += ["", "## Provenance", "",
              f"- Generated: {report['created']}",
              f"- Binary SHA-256: `{report['binary_sha256']}`",
              f"- Manifest SHA-256: `{report['manifest_sha256']}`",
              f"- LLVM: `{report['tool_versions']['llvm-cov'].splitlines()[0]}`",
              "- Movie and sync-sidecar hashes: [coverage.json](coverage.json)", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--source-root", type=Path, default=ROOT)
    parser.add_argument("--manifest", type=Path, default=ROOT / "tools/oracle/replay_ci_manifest.txt")
    parser.add_argument("--coverage", type=Path, default=ROOT / "coverage")
    parser.add_argument("--llvm-profdata", default="llvm-profdata")
    parser.add_argument("--llvm-cov", default="llvm-cov")
    parser.add_argument("--unit-binary", type=Path, help="unit test binary built from the same game objects")
    parser.add_argument("--unit-log", type=Path, help="output of the unit test binary")
    parser.add_argument("--ci-run", default=(
        f"{os.environ.get('GITHUB_SERVER_URL', 'https://github.com')}/"
        f"{os.environ['GITHUB_REPOSITORY']}/actions/runs/{os.environ['GITHUB_RUN_ID']}"
        if "GITHUB_RUN_ID" in os.environ and "GITHUB_REPOSITORY" in os.environ else ""))
    args = parser.parse_args()
    if (args.unit_binary is None) != (args.unit_log is None):
        parser.error("--unit-binary and --unit-log go together")
    root, output, binary = args.source_root.resolve(), args.coverage.resolve(), args.binary.resolve()
    try:
        revision = command("git", "rev-parse", "HEAD", cwd=root).strip()
        versions = {name: command(tool, "--version").strip() for name, tool in (
            ("llvm-profdata", args.llvm_profdata), ("llvm-cov", args.llvm_cov))}
        majors = [re.search(r"LLVM version (\d+)", version) for version in versions.values()]
        if any(major is None for major in majors) or majors[0][1] != majors[1][1]:
            raise ValueError("llvm-profdata and llvm-cov must have matching LLVM versions")
        binary_hash = sha256(binary)
        movies, profiles = checked_movies(root, args.manifest, output / "raw",
                                         output / "replays", binary_hash, revision)
        def merge(name, paths):
            listing = output / f"{name}.txt"
            listing.write_text("".join(f"{path}\n" for path in paths))
            merged = output / f"{name}.profdata"
            subprocess.run([args.llvm_profdata, "merge", "-sparse", "-f", str(listing),
                            "-o", str(merged)], check=True)
            return merged

        def export(merged, binaries):
            objects = [str(binaries[0])] + [f"-object={path}" for path in binaries[1:]]
            return game_files(json.loads(command(args.llvm_cov, "export", *objects,
                                                 f"-instr-profile={merged}", "-summary-only")), root)

        merged = merge("profiles", profiles)
        binaries = [binary]
        extra = {}
        if args.unit_binary:
            unit_binary = args.unit_binary.resolve()
            unit_profiles = sorted((output / "unit").glob("*.profraw"))
            if not unit_profiles or not all(path.stat().st_size for path in unit_profiles):
                raise ValueError("unit tests: expected nonempty raw profiles in coverage/unit")
            movie_files = export(merged, [binary])
            unit_merged = merge("unit-profiles", unit_profiles)
            unit_files = export(unit_merged, [unit_binary])
            combined = output / "combined.profdata"
            subprocess.run([args.llvm_profdata, "merge", "-sparse", str(merged), str(unit_merged),
                            "-o", str(combined)], check=True)
            merged, binaries = combined, [binary, unit_binary]
            extra = {"unit_tests": {**unit_results(args.unit_log), "binary_sha256": sha256(unit_binary)},
                     "source_files": {"movies": movie_files, "unit_tests": unit_files}}
        # Select game files explicitly for all exports, including annotated HTML.
        files = export(merged, binaries)
        if extra:
            extra["sources"] = {"movies": totals(extra["source_files"]["movies"]),
                                "unit_tests": totals(extra["source_files"]["unit_tests"]),
                                "combined": totals(files)}
        sources = [str(root / entry["file"]) for entry in files]
        command(args.llvm_cov, "show", str(binaries[0]), *[f"-object={path}" for path in binaries[1:]],
                f"-instr-profile={merged}",
                "-format=html", f"-output-dir={output / 'html'}", "-show-branches=count",
                "-show-expansions", *sources)
        report = {"schema_version": 1,
                  "created": datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  "revision": revision, "binary_sha256": binary_hash,
                  "manifest_sha256": sha256(args.manifest), "tool_versions": versions,
                  "ci_run": args.ci_run, "scope": ["src/main/**", "src/pc/placeholder.c"],
                  "totals": totals(files), "files": files, "movies": movies, **extra}
        (output / "coverage.json").write_text(json.dumps(report, indent=2) + "\n")
        (output / "coverage.md").write_text(markdown(report))
        print(f"{len(movies)} movies passed; game line coverage: {fraction(report['totals']['lines'])}")
        if extra:
            print("movies " + fraction(extra["sources"]["movies"]["lines"]) + ", unit tests "
                  + fraction(extra["sources"]["unit_tests"]["lines"]) + " (lines)")
        print(f"Report: {output / 'coverage.md'}")
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"coverage: {error}\n")


if __name__ == "__main__":
    main()
