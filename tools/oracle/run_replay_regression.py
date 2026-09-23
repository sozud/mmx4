#!/usr/bin/env python3

import argparse
import datetime
import hashlib
import json
import os
import shlex
import shutil
import subprocess
import sys
from pathlib import Path

WORKSPACE = Path(__file__).resolve().parents[2]
REPLAY_SHA256 = "e2ea3b524007787270960b7e74275fc2a043c42f53b9bfd09ffb199d5f239ef7"
ABORT_MARKERS = (
    "unimplemented traced game function",
    "unavailable game function:",
    "undecompiled function-table target reached",
    "AddressSanitizer",
    "Assertion",
)


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def validate_replay(path):
    data = path.read_bytes()
    if len(data) < 18 or (len(data) - 16) % 2:
        raise SystemExit(f"{path}: empty, odd-length, or truncated replay")
    if data[:8] not in (b"MMX4RPL1", b"MMX4RPL2"):
        raise SystemExit(f"{path}: invalid replay magic")
    if any(data[12:16]):
        raise SystemExit(f"{path}: nonzero reserved header bytes")
    return {
        "path": str(path),
        "sha256": sha256(path),
        "frames": (len(data) - 16) // 2,
        "clock": "pad-read" if data[:8] == b"MMX4RPL2" else "video-frame",
        "stage": data[8],
        "substage": data[9],
        "checkpoint": data[10],
        "character": data[11],
        "distinct_masks": len({data[16 + 2 * i : 18 + 2 * i]
                               for i in range((len(data) - 16) // 2)}),
    }


def load_sync(path, replay_metadata):
    if not path.is_file():
        return None
    document = json.loads(path.read_text())
    if document.get("format") != "MMX4SYNC1":
        raise SystemExit(f"{path}: invalid sync format")
    if document.get("clock") != "pad-read":
        raise SystemExit(f"{path}: sync clock must be pad-read")
    if document.get("replay_sha256") != replay_metadata["sha256"]:
        raise SystemExit(f"{path}: replay SHA-256 does not match")
    if document.get("samples") != replay_metadata["frames"]:
        raise SystemExit(f"{path}: replay sample count does not match")
    entries = document.get("sync_points", [])
    points = [point.get("sample") for point in entries]
    identities = [(point.get("sample"), point.get("kind")) for point in entries]
    if (not points or entries[0].get("kind") != "start" or points[0] != 0 or
            points != sorted(points) or len(identities) != len(set(identities)) or
            any(not isinstance(point, int) or point < 0 or
                point >= replay_metadata["frames"] for point in points) or
            any(point.get("kind") not in ("start", "mode-return", "load-complete",
                                           "xa-complete")
                for point in entries)):
        raise SystemExit(f"{path}: invalid sync points")
    return document


def git(*args):
    try:
        return subprocess.run(("git", *args), cwd=WORKSPACE, check=True,
                              capture_output=True, text=True).stdout.strip()
    except (subprocess.CalledProcessError, FileNotFoundError):
        return "unknown"


def run(command, log_path, env, timeout):
    with log_path.open("w") as log:
        log.write(f"$ {shlex.join(str(part) for part in command)}\n")
        log.flush()
        completed = subprocess.run(command, cwd=WORKSPACE, env=env, stdout=log,
                                   stderr=subprocess.STDOUT, timeout=timeout)
    return completed.returncode


def first_abort(log_path):
    for line in log_path.read_text(errors="replace").splitlines():
        if any(marker in line for marker in ABORT_MARKERS):
            return line.strip()
    return None


def load_log(path):
    if not path.is_file():
        return [], {}, 0
    lines = path.read_text(errors="replace").splitlines()
    if not lines:
        return [], {}, 0
    header = lines[0].split("\t")
    rows = {}
    truncated = 0
    for line in lines[1:]:
        fields = line.split("\t")
        if len(fields) != len(header):
            truncated += 1
            continue
        rows.setdefault(int(fields[0]), []).append(fields)
    if "cd_state" in header and "cd_pending" in header:
        state_index = header.index("cd_state")
        pending_index = header.index("cd_pending")
        for frame_rows in rows.values():
            for fields in frame_rows:
                if fields[state_index] == "1":
                    fields[pending_index] = "-"
    if truncated and rows:
        # A partial row can only appear at the end of an interrupted run, so the
        # frame it belongs to was never fully written.
        del rows[max(rows)]
    return header, rows, truncated


def describe(header, row):
    return " ".join(f"{name}={value}" for name, value in zip(header, row))


def describe_field(name, psx, pc):
    if ":" not in psx or ":" not in pc:
        return f"{name}: psx={psx} pc={pc}"
    base_psx, bytes_psx = psx.split(":", 1)
    base_pc, bytes_pc = pc.split(":", 1)
    if base_psx != base_pc or len(bytes_psx) != len(bytes_pc):
        return f"{name}: psx={psx} pc={pc}"
    base = int(base_psx, 16)
    changes = [f"+0x{base + i // 2:02X} psx={bytes_psx[i:i + 2]} pc={bytes_pc[i:i + 2]}"
               for i in range(0, len(bytes_psx), 2)
               if bytes_psx[i:i + 2] != bytes_pc[i:i + 2]]
    return ", ".join(changes)


def report_frames(name, header, rows):
    if not rows:
        print(f"   {name}: no frames logged")
        return None
    last = max(rows)
    print(f"   {name}: {len(rows)} frames [{min(rows)}..{last}]")
    if name.endswith("frames.tsv") and header:
        print(f"     final: {describe(header, rows[last][0])}")
    return last


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--replay", type=Path,
                        default=WORKSPACE / "tools/oracle/recordings/intro-20260912-153816-normalized.mmx4r")
    parser.add_argument("--output", type=Path,
                        default=WORKSPACE / "replay-runs")
    parser.add_argument("--build", type=Path, default=WORKSPACE / "build-asan")
    parser.add_argument("--cue", type=Path, default=WORKSPACE / "disks/mmx4.us.cue")
    parser.add_argument("--bios", type=Path, default=WORKSPACE / "tools/SCPH1001.BIN")
    parser.add_argument("--mednafen", type=Path,
                        default=Path(os.environ.get(
                            "MMX4_MEDNAFEN",
                            WORKSPACE / "tools/mednafen-build/src/mednafen")))
    parser.add_argument("--psx-frames", type=int, default=20000,
                        help="emulated video frame budget for the PSX oracle")
    parser.add_argument("--timeout", type=int, default=7200)
    parser.add_argument("--limit", type=int, default=3,
                        help="differing frames to report per log")
    parser.add_argument("--skip-build", action="store_true")
    parser.add_argument("--skip-psx", action="store_true",
                        help="reuse the PSX log named by --psx-log")
    parser.add_argument("--psx-log", type=Path,
                        help="existing PSX log directory to compare against")
    parser.add_argument("--expect-sha256", default=REPLAY_SHA256)
    parser.add_argument("--sync", type=Path,
                        help="sync sidecar (default: REPLAY.sync.json when present)")
    args = parser.parse_args()

    metadata = validate_replay(args.replay)
    if args.expect_sha256 and metadata["sha256"] != args.expect_sha256:
        raise SystemExit(
            f"{args.replay}: sha256 {metadata['sha256']} does not match "
            f"expected {args.expect_sha256}")
    sync_path = args.sync or Path(str(args.replay) + ".sync.json")
    sync = load_sync(sync_path, metadata)
    sync_points = {point["sample"] for point in sync["sync_points"]} if sync else {0}

    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    output = args.output / stamp
    if output.exists():
        raise SystemExit(f"{output}: output directory already exists")
    output.mkdir(parents=True)
    psx_dir = output / "psx"
    pc_dir = output / "pc"
    pc_dir.mkdir()

    metadata.update(
        commit=git("rev-parse", "HEAD"),
        branch=git("rev-parse", "--abbrev-ref", "HEAD"),
        dirty=bool(git("status", "--porcelain")),
        mednafen=str(args.mednafen),
        started=stamp,
    )

    if not args.skip_build:
        print("== building the PC target")
        subprocess.run(("cmake", "--build", str(args.build), "-j",
                        str(os.cpu_count() or 1)), cwd=WORKSPACE, check=True,
                       stdout=subprocess.DEVNULL)
    binary = args.build / "mmx4_pc"
    if not binary.is_file():
        raise SystemExit(f"{binary}: PC binary is missing")

    if args.skip_psx:
        if args.psx_log is None:
            raise SystemExit("--skip-psx requires --psx-log")
        psx_dir = args.psx_log
    else:
        psx_dir.mkdir()
        print("== running the PSX oracle")
        env = os.environ.copy()
        env.update(
            MMX4_INPUT_PLAY=str(args.replay),
            MMX4_OBJECT_LOG_DIR=str(psx_dir),
            MMX4_ORACLE_LOG_INTERVAL="0",
        )
        code = run((str(args.mednafen), str(args.cue), str(args.bios),
                    str(args.psx_frames)), psx_dir / "run.log", env, args.timeout)
        metadata["psx_exit"] = code

    print("== running the PC port")
    env = os.environ.copy()
    env.update(
        ASAN_OPTIONS="detect_leaks=0",
        MMX4_CANONICAL_LOAD="1",
        MMX4_MAX_FRAMES="36000",
        MMX4_OBJECT_LOG_DIR=str(pc_dir),
        MMX4_REPLAY_EXIT="1",
    )
    if sync:
        env["MMX4_REPLAY_SYNC"] = str(sync_path)
    command = [str(binary), "--replay", str(args.replay)]
    if shutil.which("xvfb-run") is not None:
        command = ["xvfb-run", "-a", *command]
    metadata["pc_exit"] = run(command, pc_dir / "run.log", env, args.timeout)

    print()
    print(f"== replay {args.replay}")
    print(f"   sha256 {metadata['sha256']}")
    print(f"   {metadata['frames']} inputs, stage {metadata['stage']}-"
          f"{metadata['substage']}, checkpoint {metadata['checkpoint']}, "
          f"character {metadata['character']}, "
          f"{metadata['distinct_masks']} distinct masks")
    print(f"   commit {metadata['commit']} on {metadata['branch']}"
          + (" (dirty worktree)" if metadata["dirty"] else ""))
    print(f"   evidence {output}")
    if sync:
        print(f"   {len(sync_points)} explicit sync points from {sync_path}")

    status = 0
    logs = {}
    for side, directory in (("psx", psx_dir), ("pc", pc_dir)):
        print(f"== {side}")
        abort = first_abort(directory / "run.log")
        metadata[f"{side}_first_abort"] = abort
        if abort:
            print(f"   first aborting or unavailable function: {abort}")
            status = 1
        for name in ("frames.tsv", "objects.tsv", "extensions.tsv", "state.tsv"):
            header, rows, truncated = load_log(directory / name)
            logs[(side, name)] = (header, rows)
            last = report_frames(f"{side}/{name}", header, rows)
            if truncated:
                print(f"     {truncated} truncated row(s) ignored")
            if name == "frames.tsv":
                consumed = (last + 1) if last is not None else 0
                metadata[f"{side}_frames"] = consumed
                if consumed != metadata["frames"]:
                    print(f"     consumed {consumed} of {metadata['frames']} inputs")
                    status = 1
                else:
                    print(f"     consumed all {metadata['frames']} inputs")

    print("== comparison")
    for name in ("frames.tsv", "objects.tsv", "extensions.tsv", "state.tsv"):
        header_a, rows_a = logs[("psx", name)]
        header_b, rows_b = logs[("pc", name)]
        if header_a and header_b and header_a != header_b:
            print(f"   {name}: schema mismatch between the two logs")
            status = 1
            continue
        shared = sorted(set(rows_a) & set(rows_b))
        missing_pc = sorted(set(rows_a) - set(rows_b))
        missing_psx = sorted(set(rows_b) - set(rows_a))
        differing = [frame for frame in shared if rows_a[frame] != rows_b[frame]]
        print(f"   {name}: compared {len(shared)} shared frames, "
              f"{len(differing)} differing")
        metadata[f"{name}_shared"] = len(shared)
        metadata[f"{name}_differing"] = len(differing)
        metadata[f"{name}_missing_pc"] = len(missing_pc)
        if missing_pc or missing_psx:
            print(f"   {name}: {len(missing_pc)} PC gaps, "
                  f"{len(missing_psx)} PSX gaps")
            status = 1
        if not differing:
            continue
        status = 1
        metadata[f"{name}_first_differing_frame"] = differing[0]
        for frame in differing[: args.limit]:
            keyed_a = {(row[3], row[4]): row for row in rows_a[frame]}
            keyed_b = {(row[3], row[4]): row for row in rows_b[frame]}
            print(f"   frame {frame}:")
            if len(header_a) > 4 and keyed_a and keyed_b:
                for key in sorted(set(keyed_a) | set(keyed_b)):
                    ra, rb = keyed_a.get(key), keyed_b.get(key)
                    if ra == rb:
                        continue
                    if ra is None:
                        print(f"     {key[0]}[{key[1]}] missing on psx")
                        print(f"       pc  {describe(header_b, rb)}")
                    elif rb is None:
                        print(f"     {key[0]}[{key[1]}] missing on pc")
                        print(f"       psx {describe(header_a, ra)}")
                    else:
                        fields = [describe_field(n, x, y)
                                  for n, x, y in zip(header_a, ra, rb) if x != y]
                        print(f"     {key[0]}[{key[1]}] " + ", ".join(fields))
            else:
                print(f"     psx {describe(header_a, rows_a[frame][0])}")
                print(f"     pc  {describe(header_b, rows_b[frame][0])}")
            for neighbour in (frame - 1, frame + 1) if name != "state.tsv" else ():
                if neighbour in rows_a and neighbour in rows_b and header_a:
                    print(f"     frame {neighbour} psx {describe(header_a, rows_a[neighbour][0])}")
                    print(f"     frame {neighbour} pc  {describe(header_b, rows_b[neighbour][0])}")

    metadata["status"] = status
    (output / "metadata.json").write_text(json.dumps(metadata, indent=2) + "\n")
    print()
    print("== reproduce")
    print(f"   git -C {WORKSPACE} checkout {metadata['commit']}")
    print(f"   {shlex.join([sys.executable, str(Path(__file__).resolve())] + sys.argv[1:])}")
    print(f"   evidence and metadata: {output}")
    return status


if __name__ == "__main__":
    raise SystemExit(main())
