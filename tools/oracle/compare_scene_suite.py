#!/usr/bin/env python3
import argparse
import csv
from difflib import SequenceMatcher
import math
from pathlib import Path
import statistics
import sys

import ssim
from ssim import read_ppm


STATE_FIELDS = (
    "trigger", "object", "slot", "old_active", "active", "old_id", "id",
    "old_state", "old_step", "old_substep", "state", "step", "substep",
    "old_phase", "phase",
)
SCENES = ("title", "character-select", "mission-briefing", "initial-stage")


def load_events(directory: Path):
    with (directory / "manifest.tsv").open() as stream:
        rows = list(csv.DictReader(stream, delimiter="\t"))
    events = []
    for row in rows:
        identity = (row["event"], row["filename"])
        if not events or events[-1][0] != identity:
            events.append([identity, []])
        events[-1][1].append(tuple(row[field] for field in STATE_FIELDS))
    return [(identity, tuple(changes)) for identity, changes in events]


def compare_scene(original: Path, port: Path, output, minimum_threshold,
                  mean_threshold):
    left_events, right_events = load_events(original), load_events(port)
    matcher = SequenceMatcher(
        a=[changes for _, changes in left_events],
        b=[changes for _, changes in right_events],
        autojunk=False,
    )
    matched = []
    for left_index, right_index, count in matcher.get_matching_blocks():
        for offset in range(count):
            left = left_events[left_index + offset][0]
            right = right_events[right_index + offset][0]
            left_image = original / left[1]
            right_image = port / right[1]
            if (read_ppm(left_image)[:2] != (320, 240)
                    or read_ppm(right_image)[:2] != (320, 240)):
                raise ValueError("suite images must both be 320x240")
            matched.append((left, right, left_image, right_image))
    scores = ssim.score_pairs((left, right) for _, _, left, right in matched)
    writer = csv.writer(output, delimiter="\t", lineterminator="\n")
    writer.writerow(("mednafen_event", "pc_event", "mednafen_image", "pc_image", "ssim"))
    for (left, right, _, _), score in zip(matched, scores):
        writer.writerow((left[0], right[0], left[1], right[1], f"{score:.9f}"))
    unmatched_left = len(left_events) - len(scores)
    unmatched_right = len(right_events) - len(scores)
    passed = bool(
        not unmatched_left
        and not unmatched_right
        and scores
        and min(scores) >= minimum_threshold
        and statistics.mean(scores) >= mean_threshold
    )
    return {
        "pairs": len(scores),
        "mednafen_events": len(left_events),
        "pc_events": len(right_events),
        "unmatched_mednafen": unmatched_left,
        "unmatched_pc": unmatched_right,
        "minimum": min(scores) if scores else math.nan,
        "mean": statistics.mean(scores) if scores else math.nan,
        "passed": passed,
    }


def main():
    workspace = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser()
    parser.add_argument("--mednafen", type=Path, default=workspace / "mednafen-object-changes")
    parser.add_argument("--pc", type=Path, default=workspace / "pc-object-changes")
    parser.add_argument("--output", type=Path, default=workspace / "scene-comparison")
    parser.add_argument("--minimum-threshold", type=float, default=0.85)
    parser.add_argument("--mean-threshold", type=float, default=0.97)
    parser.add_argument("--scene", choices=SCENES)
    parser.add_argument(
        "--allow-failure",
        action="store_true",
        help="report differences without returning a failing exit status",
    )
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    failed = False
    scenes = SCENES if args.scene is None else (args.scene,)
    for scene in scenes:
        with (args.output / f"{scene}.tsv").open("w") as report:
            result = compare_scene(
                args.mednafen / scene, args.pc / scene, report,
                args.minimum_threshold, args.mean_threshold
            )
        print(
            f"{scene}: {result['pairs']} pairs, "
            f"unmatched={result['unmatched_mednafen']}/{result['unmatched_pc']}, "
            f"min={result['minimum']:.6f}, mean={result['mean']:.6f}"
        )
        failed |= not result["passed"]
    return 0 if args.allow_failure else int(failed)


if __name__ == "__main__":
    sys.exit(main())
