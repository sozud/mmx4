#!/usr/bin/env python3

import argparse
import csv
import json
import os
import subprocess
import tempfile
from pathlib import Path

from run_replay_regression import WORKSPACE, sha256, validate_replay


def sync_points_from_log(path):
    points = []
    previous_mode = None
    previous_load_busy = False
    previous_reads = 0
    with path.open(newline="") as source:
        for row in csv.DictReader(source, delimiter="\t"):
            sample = int(row["frame"])
            mode = int(row["state"])
            load_busy = int(row["cd_state"]) == 1 or int(row["cd_pending"]) != 0
            reads = int(row.get("cd_reads") or 0)
            if mode == 6 and (previous_mode is None or previous_mode != 6):
                points.append({
                    "sample": sample,
                    "mode": 6,
                    "kind": "start" if previous_mode is None else "mode-return",
                })
            if "cd_reads" in row:
                completed = reads - previous_reads
            else:
                completed = int(previous_load_busy and not load_busy)
            if completed > 1:
                raise RuntimeError(f"{path}: {completed} loads completed in sample {sample}")
            if completed:
                point = {"sample": sample + 1, "kind": "load-complete"}
                if "cd_read_sample" in row:
                    completed_at = int(row["cd_read_sample"])
                    if completed_at not in (sample, sample + 1):
                        raise RuntimeError(
                            f"{path}: load completed at sample {completed_at} "
                            f"but was logged in sample {sample}")
                    point["phase"] = "input" if completed_at == sample else "frame"
                points.append(point)
            previous_mode = mode
            previous_load_busy = load_busy
            previous_reads = reads
    if not points or points[0]["sample"] != 0:
        raise RuntimeError(f"{path}: replay did not start in mode 6 at sample 0")
    return sorted(points, key=lambda point: point["sample"])


def write_sidecar(replay, frames_log):
    metadata = validate_replay(replay)
    if metadata["clock"] != "pad-read":
        raise RuntimeError(f"{replay}: sync sidecars require an RPL2 replay")
    sidecar = Path(str(replay) + ".sync.json")
    document = {
        "format": "MMX4SYNC1",
        "replay_sha256": sha256(replay),
        "clock": "pad-read",
        "samples": metadata["frames"],
        "scene": {
            key: metadata[key]
            for key in ("stage", "substage", "checkpoint", "character")
        },
        "sync_points": sync_points_from_log(frames_log),
    }
    sidecar.write_text(json.dumps(document, indent=2) + "\n")
    print(f"{replay}: wrote {len(document['sync_points'])} sync points to {sidecar}")


def run_oracle(args, replay, log_dir, normalize=None):
    environment = os.environ.copy()
    environment.update(
        MMX4_INPUT_PLAY=str(replay),
        MMX4_OBJECT_LOG_DIR=str(log_dir),
        MMX4_ORACLE_LOG_INTERVAL="0",
    )
    if normalize is not None:
        environment["MMX4_INPUT_NORMALIZE"] = str(normalize)
    with (log_dir / "run.log").open("w") as output:
        subprocess.run(
            (str(args.mednafen), str(args.cue), str(args.bios), str(args.psx_frames)),
            cwd=WORKSPACE,
            env=environment,
            stdout=output,
            stderr=subprocess.STDOUT,
            timeout=args.timeout,
            check=True,
        )


def migrate_one(args, source):
    source = source.resolve()
    metadata = validate_replay(source)
    replay = source
    with tempfile.TemporaryDirectory(prefix="mmx4-replay-sync-") as temporary:
        temporary = Path(temporary)
        if metadata["clock"] == "video-frame":
            replay = source.with_name(source.stem + "-normalized.mmx4r")
            if replay.exists() and not args.force:
                raise RuntimeError(f"{replay}: already exists (use --force to replace it)")
            if replay.exists():
                replay.unlink()
            normalization_log = temporary / "normalize"
            normalization_log.mkdir()
            run_oracle(args, source, normalization_log, replay)
            validate_replay(replay)

        oracle_log = temporary / "oracle"
        oracle_log.mkdir()
        run_oracle(args, replay, oracle_log)
        write_sidecar(replay, oracle_log / "frames.tsv")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("replays", nargs="+", type=Path)
    parser.add_argument("--mednafen", type=Path,
                        default=WORKSPACE / "tools/mednafen-build/src/mednafen")
    parser.add_argument("--cue", type=Path,
                        default=WORKSPACE / "disks/mmx4.us.cue")
    parser.add_argument("--bios", type=Path,
                        default=WORKSPACE / "tools/SCPH1001.BIN")
    parser.add_argument("--psx-frames", type=int, default=20000)
    parser.add_argument("--timeout", type=int, default=7200)
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()
    for replay in args.replays:
        migrate_one(args, replay)


if __name__ == "__main__":
    main()
