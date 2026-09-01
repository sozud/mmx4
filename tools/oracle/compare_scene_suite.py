#!/usr/bin/env python3
import argparse
import csv
from difflib import SequenceMatcher
import math
from pathlib import Path
import statistics
import sys


STATE_FIELDS = (
    "trigger", "object", "slot", "old_active", "active", "old_id", "id",
    "old_state", "old_step", "old_substep", "state", "step", "substep",
    "old_phase", "phase",
)
SCENES = ("title", "character-select", "mission-briefing", "initial-stage")


def read_ppm(path: Path):
    with path.open("rb") as stream:
        if stream.readline() != b"P6\n":
            raise ValueError(f"{path}: expected binary PPM")
        width, height = map(int, stream.readline().split())
        if stream.readline() != b"255\n":
            raise ValueError(f"{path}: expected 8-bit PPM")
        pixels = stream.read()
    if len(pixels) != width * height * 3:
        raise ValueError(f"{path}: truncated image")
    return width, height, pixels


def image_ssim(width, height, left, right):
    scores = []
    c1, c2 = (0.01 * 255) ** 2, (0.03 * 255) ** 2
    for top in range(0, height, 8):
        for x0 in range(0, width, 8):
            a, b = [], []
            for y in range(top, min(top + 8, height)):
                for x in range(x0, min(x0 + 8, width)):
                    offset = (y * width + x) * 3
                    a.append(
                        0.2126 * left[offset]
                        + 0.7152 * left[offset + 1]
                        + 0.0722 * left[offset + 2]
                    )
                    b.append(
                        0.2126 * right[offset]
                        + 0.7152 * right[offset + 1]
                        + 0.0722 * right[offset + 2]
                    )
            mean_a, mean_b = statistics.mean(a), statistics.mean(b)
            variance_a = sum((value - mean_a) ** 2 for value in a) / len(a)
            variance_b = sum((value - mean_b) ** 2 for value in b) / len(b)
            covariance = sum(
                (x - mean_a) * (y - mean_b) for x, y in zip(a, b)
            ) / len(a)
            scores.append(
                ((2 * mean_a * mean_b + c1) * (2 * covariance + c2))
                / (
                    (mean_a * mean_a + mean_b * mean_b + c1)
                    * (variance_a + variance_b + c2)
                )
            )
    return statistics.mean(scores) if scores else math.nan


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


def compare_scene(original: Path, port: Path, output, threshold):
    left_events, right_events = load_events(original), load_events(port)
    matcher = SequenceMatcher(
        a=[changes for _, changes in left_events],
        b=[changes for _, changes in right_events],
        autojunk=False,
    )
    scores = []
    writer = csv.writer(output, delimiter="\t", lineterminator="\n")
    writer.writerow(("mednafen_event", "pc_event", "mednafen_image", "pc_image", "ssim"))
    for left_index, right_index, count in matcher.get_matching_blocks():
        for offset in range(count):
            left = left_events[left_index + offset][0]
            right = right_events[right_index + offset][0]
            left_image = read_ppm(original / left[1])
            right_image = read_ppm(port / right[1])
            if left_image[:2] != (320, 240) or right_image[:2] != (320, 240):
                raise ValueError("suite images must both be 320x240")
            score = image_ssim(320, 240, left_image[2], right_image[2])
            scores.append(score)
            writer.writerow((left[0], right[0], left[1], right[1], f"{score:.9f}"))
    unmatched_left = len(left_events) - len(scores)
    unmatched_right = len(right_events) - len(scores)
    passed = bool(
        not unmatched_left
        and not unmatched_right
        and scores
        and min(scores) >= threshold
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
    parser.add_argument("--threshold", type=float, default=0.99)
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
                args.mednafen / scene, args.pc / scene, report, args.threshold
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
