#!/usr/bin/env python3

import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time
import unittest

import report_movie_coverage as coverage

TOOLS = {"clang": "clang", "llvm-profdata": "llvm-profdata", "llvm-cov": "llvm-cov"}


class CoverageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for directory in ("src/main", "src/pc", "recordings", "coverage"):
            (self.root / directory).mkdir(parents=True)
        sources = {
            "src/main/game.c": "int game(int x) { if (x) return 7; return 3; }\n",
            "src/pc/placeholder.c": "int replacement(int x) { if (x) return 5; return 2; }\n",
            "src/pc/main.c": (
                "int game(int); int replacement(int);\n"
                "int main(int argc, char **argv) { return game(argc > 1) + replacement(argc > 1) == 99; }\n"),
        }
        for name, contents in sources.items():
            (self.root / name).write_text(contents)
        subprocess.run(["git", "init", "-q", str(self.root)], check=True)
        subprocess.run(["git", "-C", str(self.root), "add", "src"], check=True)
        subprocess.run(["git", "-C", str(self.root), "-c", "user.name=Coverage Test",
                        "-c", "user.email=coverage@example.invalid", "commit", "-qm", "fixture"], check=True)
        self.revision = coverage.command("git", "rev-parse", "HEAD", cwd=self.root).strip()
        self.binary = self.root / "fixture"
        subprocess.run([TOOLS["clang"], "-fprofile-instr-generate", "-fcoverage-mapping",
                        *[str(self.root / name) for name in sources], "-o", str(self.binary)], check=True)
        self.hash = coverage.sha256(self.binary)
        self.manifest = self.root / "manifest.txt"
        lines = []
        self.results = []
        self.profiles = []
        for index in (0, 1):
            stem = f"movie-{index}"
            replay = self.root / f"recordings/{stem}.mmx4r"
            replay.write_bytes(b"MMX4RPL2" + bytes(8) + bytes(2))
            digest = coverage.sha256(replay)
            lines.append(f"recordings/{stem}.mmx4r {digest}\n")
            evidence = self.root / f"coverage/replays/{stem}/run"
            (evidence / "pc").mkdir(parents=True)
            (evidence / "pc/run.log").write_text("fixture movie run\n")
            profile = self.root / f"coverage/raw/{stem}/run.profraw"
            profile.parent.mkdir(parents=True)
            started = time.time_ns()
            subprocess.run([str(self.binary), *(["true"] if index else [])], check=True,
                           env={**os.environ, "LLVM_PROFILE_FILE": str(profile)})
            finished = time.time_ns()
            metadata = evidence / "metadata.json"
            metadata.write_text(json.dumps({"sha256": digest, "commit": self.revision,
                "binary_sha256": self.hash, "sync_sha256": None, "status": 0,
                "pc_exit": 0, "frames": 1, "pc_frames": 1, "psx_frames": 1,
                "pc_started_ns": started, "pc_finished_ns": finished}))
            self.results.append(metadata)
            self.profiles.append(profile)
        self.manifest.write_text("".join(lines))

    def report(self):
        return subprocess.run([sys.executable, str(Path(coverage.__file__)),
            "--binary", str(self.binary), "--source-root", str(self.root),
            "--manifest", str(self.manifest), "--coverage", str(self.root / "coverage"),
            "--llvm-profdata", TOOLS["llvm-profdata"], "--llvm-cov", TOOLS["llvm-cov"]],
            capture_output=True, text=True)

    def mutate_result(self, **changes):
        document = json.loads(self.results[0].read_text())
        document.update(changes)
        self.results[0].write_text(json.dumps(document))

    def test_merge_includes_placeholder_and_excludes_pc_port(self):
        result = self.report()
        self.assertEqual(result.returncode, 0, result.stderr)
        report = json.loads((self.root / "coverage/coverage.json").read_text())
        self.assertEqual([entry["file"] for entry in report["files"]],
                         ["src/main/game.c", "src/pc/placeholder.c"])
        self.assertEqual(report["totals"]["functions"], {"count": 2, "covered": 2})
        self.assertEqual(report["totals"]["branches"], {"count": 4, "covered": 4})
        # Neither individual run covers both outcomes; the merge must add them.
        for index, profile in enumerate(self.profiles):
            indexed = self.root / f"single-{index}.profdata"
            subprocess.run([TOOLS["llvm-profdata"], "merge", "-sparse", str(profile),
                            "-o", str(indexed)], check=True)
            export = json.loads(coverage.command(TOOLS["llvm-cov"], "export", self.binary,
                                                f"-instr-profile={indexed}", "-summary-only"))
            self.assertEqual(coverage.totals(coverage.game_files(export, self.root))["branches"]["covered"], 2)
        html_files = list((self.root / "coverage/html").rglob("*.html"))
        self.assertTrue(any(path.name == "placeholder.c.html" for path in html_files))
        self.assertFalse(any(path.name == "main.c.html" for path in html_files))

    def test_failed_incomplete_or_wrong_binary_results_are_rejected(self):
        for change in ({"status": 1}, {"pc_exit": 1}, {"psx_exit": 1},
                       {"pc_frames": 0}, {"psx_frames": 0}, {"binary_sha256": "other"},
                       {"commit": "other"}, {"sync_sha256": "other"}):
            original = self.results[0].read_text()
            with self.subTest(change=change):
                self.mutate_result(**change)
                self.assertNotEqual(self.report().returncode, 0)
                self.assertFalse((self.root / "coverage/coverage.json").exists())
            self.results[0].write_text(original)

    def test_missing_empty_or_stale_profiles_are_rejected(self):
        original = self.profiles[0].read_bytes()
        self.profiles[0].unlink()
        self.assertNotEqual(self.report().returncode, 0)
        self.profiles[0].write_bytes(b"")
        self.assertNotEqual(self.report().returncode, 0)
        self.profiles[0].write_bytes(original)
        os.utime(self.profiles[0], (1, 1))
        self.assertNotEqual(self.report().returncode, 0)

    def test_corrupt_profile_fails_merge(self):
        self.profiles[0].write_bytes(b"not an LLVM profile")
        self.mutate_result(pc_finished_ns=time.time_ns())
        result = self.report()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("merge", result.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name, default in TOOLS.items():
        parser.add_argument(f"--{name}", default=default)
    args = parser.parse_args()
    for name in TOOLS:
        TOOLS[name] = getattr(args, name.replace("-", "_"))
        if not shutil.which(TOOLS[name]):
            parser.error(f"missing tool: {TOOLS[name]}")
    unittest.main(argv=[sys.argv[0]])


if __name__ == "__main__":
    main()
