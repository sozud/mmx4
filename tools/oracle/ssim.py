#!/usr/bin/env python3

import subprocess
from pathlib import Path

WORKSPACE = Path(__file__).resolve().parents[2]
SOURCE = Path(__file__).resolve().with_suffix(".rs")
BINARY = WORKSPACE / "build/oracle/ssim"


def read_ppm(path: Path):
    with Path(path).open("rb") as stream:
        if stream.readline() != b"P6\n":
            raise ValueError(f"{path}: expected binary PPM")
        width, height = map(int, stream.readline().split())
        if stream.readline() != b"255\n":
            raise ValueError(f"{path}: expected 8-bit PPM")
        pixels = stream.read()
    if len(pixels) != width * height * 3:
        raise ValueError(f"{path}: truncated image")
    return width, height, pixels


def scorer():
    if not BINARY.is_file() or BINARY.stat().st_mtime < SOURCE.stat().st_mtime:
        BINARY.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(("rustc", "-O", str(SOURCE), "-o", str(BINARY)),
                       cwd=WORKSPACE, check=True)
    return BINARY


def score_pairs(pairs):
    pairs = list(pairs)
    if not pairs:
        return []
    request = "".join(f"{left}\t{right}\n" for left, right in pairs)
    completed = subprocess.run((str(scorer()), "--pairs"), cwd=WORKSPACE,
                               input=request, capture_output=True, text=True,
                               check=True)
    scores = [float(line) for line in completed.stdout.splitlines()]
    if len(scores) != len(pairs):
        raise RuntimeError(
            f"scorer returned {len(scores)} scores for {len(pairs)} pairs")
    return scores


def score_directories(left: Path, right: Path):
    completed = subprocess.run((str(scorer()), str(left), str(right)),
                               cwd=WORKSPACE, capture_output=True, text=True,
                               check=True)
    return [(name, float(value)) for name, value in
            (line.split("\t", 1) for line in completed.stdout.splitlines())]
