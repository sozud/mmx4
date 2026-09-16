#!/usr/bin/env python3

import argparse
import os
import subprocess
import tempfile
from pathlib import Path

WORKSPACE = Path(__file__).resolve().parents[2]
GOOD = b"MMX4RPL2" + bytes([0, 0, 0, 0]) + bytes(4) + b"\x00\x00"

CASES = (
    ("empty", b""),
    ("header only", GOOD[:16]),
    ("odd length", GOOD + b"\x00"),
    ("truncated header", GOOD[:12]),
    ("bad magic", b"MMX4RPL3" + GOOD[8:]),
    ("nonzero reserved", GOOD[:12] + b"\x01\x00\x00\x00" + GOOD[16:]),
)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--binary", type=Path, default=WORKSPACE / "build-asan/mmx4_pc")
    args = parser.parse_args()
    if not args.binary.is_file():
        raise SystemExit(f"{args.binary}: PC binary is missing")

    failures = 0
    with tempfile.TemporaryDirectory() as directory:
        for name, data in CASES:
            path = Path(directory) / "fixture.mmx4r"
            path.write_bytes(data)
            environment = os.environ.copy()
            environment["ASAN_OPTIONS"] = "detect_leaks=0"
            completed = subprocess.run(
                (str(args.binary), "--replay", str(path)), cwd=WORKSPACE,
                env=environment, capture_output=True, text=True, timeout=120)
            if completed.returncode == 0:
                print(f"FAIL {name}: accepted an invalid replay")
                failures += 1
            else:
                print(f"ok   {name}: rejected ({completed.returncode})")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
