#!/usr/bin/env python3

import argparse
from pathlib import Path


def load(path):
    lines = path.read_text(errors="replace").splitlines()
    if not lines:
        raise SystemExit(f"{path}: empty log")
    header = lines[0].split("\t")
    width = len(header)
    rows = {}
    truncated = 0
    for line in lines[1:]:
        fields = line.split("\t")
        if len(fields) != width:
            truncated += 1
            continue
        rows.setdefault(int(fields[0]), []).append(fields)
    if truncated and rows:
        del rows[max(rows)]
    return header, rows, truncated


def describe(header, row):
    return " ".join(f"{name}={value}" for name, value in zip(header, row))


def compare_frames(psx, pc, limit):
    header_a, rows_a, trunc_a = psx
    header_b, rows_b, trunc_b = pc
    if header_a != header_b:
        print("schema mismatch between PSX and PC logs")
        print("  psx:", "\t".join(header_a))
        print("  pc: ", "\t".join(header_b))
        return 1
    failures = 0
    shared = sorted(set(rows_a) & set(rows_b))
    for frame in shared:
        a = rows_a[frame]
        b = rows_b[frame]
        if a == b:
            continue
        failures += 1
        print(f"frame {frame}: {len(a)} psx rows vs {len(b)} pc rows")
        keyed_a = {(row[3], row[4]): row for row in a} if len(header_a) > 4 else {}
        keyed_b = {(row[3], row[4]): row for row in b} if len(header_b) > 4 else {}
        if keyed_a and keyed_b:
            for key in sorted(set(keyed_a) | set(keyed_b)):
                ra = keyed_a.get(key)
                rb = keyed_b.get(key)
                if ra == rb:
                    continue
                if ra is None:
                    print(f"  {key}: missing on psx; pc  {describe(header_b, rb)}")
                elif rb is None:
                    print(f"  {key}: missing on pc;  psx {describe(header_a, ra)}")
                else:
                    fields = [
                        f"{name}: psx={x} pc={y}"
                        for name, x, y in zip(header_a, ra, rb)
                        if x != y
                    ]
                    print(f"  {key}: " + ", ".join(fields))
        else:
            for ra, rb in zip(a, b):
                if ra != rb:
                    print("  psx:", describe(header_a, ra))
                    print("  pc: ", describe(header_b, rb))
        if failures >= limit:
            break
    return failures


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("psx", type=Path, help="PSX oracle log directory")
    parser.add_argument("pc", type=Path, help="PC log directory")
    parser.add_argument("--limit", type=int, default=3,
                        help="stop after this many differing frames per file")
    args = parser.parse_args()

    status = 0
    for name in ("frames.tsv", "objects.tsv"):
        psx = load(args.psx / name)
        pc = load(args.pc / name)
        frames_a, frames_b = set(psx[1]), set(pc[1])
        shared = frames_a & frames_b
        print(f"== {name}")
        print(f"   psx frames {len(frames_a)} "
              f"[{min(frames_a, default=-1)}..{max(frames_a, default=-1)}] "
              f"truncated rows {psx[2]}")
        print(f"   pc  frames {len(frames_b)} "
              f"[{min(frames_b, default=-1)}..{max(frames_b, default=-1)}] "
              f"truncated rows {pc[2]}")
        only_a = sorted(frames_a - frames_b)
        only_b = sorted(frames_b - frames_a)
        if only_a:
            print(f"   frames only on psx ({len(only_a)}): {only_a[:12]}")
        if only_b:
            print(f"   frames only on pc  ({len(only_b)}): {only_b[:12]}")
        print(f"   compared {len(shared)} shared frames")
        failures = compare_frames(psx, pc, args.limit)
        if failures:
            status = 1
            print(f"   {name}: first differing frame reported above")
        else:
            print(f"   {name}: all shared frames agree")
    return status


if __name__ == "__main__":
    raise SystemExit(main())
