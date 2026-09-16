#!/usr/bin/env python3

import argparse
import csv
import datetime
import html
import os
import shutil
import struct
import subprocess
import zlib
from pathlib import Path

import ssim
from ssim import read_ppm
from run_replay_regression import REPLAY_SHA256, validate_replay


WORKSPACE = Path(__file__).resolve().parents[2]


def run(command, log_path, environment):
    with log_path.open("w") as log:
        subprocess.run(command, cwd=WORKSPACE, env=environment, stdout=log,
                       stderr=subprocess.STDOUT, check=True)


def png_chunk(kind, data):
    return (struct.pack(">I", len(data)) + kind + data
            + struct.pack(">I", zlib.crc32(kind + data) & 0xFFFFFFFF))


def write_png(path, width, height, pixels):
    rows = b"".join(
        b"\0" + pixels[y * width * 3:(y + 1) * width * 3]
        for y in range(height)
    )
    path.write_bytes(
        b"\x89PNG\r\n\x1a\n"
        + png_chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
        + png_chunk(b"IDAT", zlib.compress(rows, 6))
        + png_chunk(b"IEND", b"")
    )


def write_ranked_images(output, ranked, psx_dir, pc_dir, top):
    ranked_dir = output / "ranked"
    ranked_dir.mkdir()
    cards = []
    for rank, (filename, score) in enumerate(ranked[:top], 1):
        frame = int(Path(filename).stem.split("_")[1])
        width, height, psx = read_ppm(psx_dir / filename)
        pc_width, pc_height, pc = read_ppm(pc_dir / filename)
        if (width, height) != (pc_width, pc_height):
            raise ValueError(f"dimension mismatch for {filename}")
        difference = bytes(
            min(255, abs(left - right) * 4) for left, right in zip(psx, pc)
        )
        prefix = f"{rank:04d}_f{frame:06d}_ssim_{score:.6f}"
        names = {
            "psx": f"{prefix}_psx.png",
            "pc": f"{prefix}_pc.png",
            "diff": f"{prefix}_diff4x.png",
        }
        write_png(ranked_dir / names["psx"], width, height, psx)
        write_png(ranked_dir / names["pc"], width, height, pc)
        write_png(ranked_dir / names["diff"], width, height, difference)
        cards.append((rank, frame, score, names))

    with (output / "index.html").open("w") as page:
        page.write("<!doctype html><meta charset=utf-8><title>MMX4 replay SSIM</title>")
        page.write("<style>body{font:14px sans-serif;background:#181818;color:#eee}"
                   ".card{margin:24px 0}.images{display:flex;gap:8px;flex-wrap:wrap}"
                   "figure{margin:0}img{width:640px;image-rendering:pixelated;max-width:31vw}"
                   "figcaption{text-align:center}</style>")
        page.write("<h1>MMX4 replay frames, worst SSIM first</h1>")
        for rank, frame, score, names in cards:
            page.write(f"<section class=card><h2>#{rank} — frame {frame} — SSIM {score:.9f}</h2><div class=images>")
            for label in ("psx", "pc", "diff"):
                name = html.escape(names[label])
                page.write(f"<figure><img src='ranked/{name}'><figcaption>{label}</figcaption></figure>")
            page.write("</div></section>")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--replay", type=Path,
                        default=WORKSPACE / "tools/oracle/recordings/intro-20260912-153816-normalized.mmx4r")
    parser.add_argument("--output", type=Path, default=WORKSPACE / "replay-ssim")
    parser.add_argument("--build", type=Path, default=WORKSPACE / "build-linux")
    parser.add_argument("--mednafen", type=Path,
                        default=WORKSPACE / "tools/mednafen-build/src/mednafen")
    parser.add_argument("--cue", type=Path, default=WORKSPACE / "disks/mmx4.us.cue")
    parser.add_argument("--bios", type=Path, default=WORKSPACE / "tools/SCPH1001.BIN")
    parser.add_argument("--first", type=int, default=0)
    parser.add_argument("--last", type=int)
    parser.add_argument("--interval", type=int, default=10,
                        help="capture every Nth replay frame (default: 10)")
    parser.add_argument("--top", type=int, default=100,
                        help="write browsable PNG triplets for the N worst frames")
    parser.add_argument("--psx-frames", type=int, default=20000)
    parser.add_argument("--reuse-psx", type=Path,
                        help="reuse a previous raw/psx capture directory")
    parser.add_argument("--reuse-pc", type=Path,
                        help="reuse a previous raw/pc capture directory")
    parser.add_argument("--skip-build", action="store_true")
    parser.add_argument("--expect-sha256", default=REPLAY_SHA256)
    args = parser.parse_args()

    metadata = validate_replay(args.replay)
    if args.expect_sha256 and metadata["sha256"] != args.expect_sha256:
        parser.error("replay SHA-256 does not match the expected intro replay")
    last = metadata["frames"] - 1 if args.last is None else args.last
    if args.first < 0 or last < args.first or last >= metadata["frames"]:
        parser.error(f"capture range must be within 0..{metadata['frames'] - 1}")
    if args.interval < 1 or args.top < 1:
        parser.error("--interval and --top must be positive")

    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    output = args.output / stamp
    raw = output / "raw"
    psx_dir = raw / "psx"
    pc_dir = raw / "pc"
    raw.mkdir(parents=True)
    if args.reuse_psx is not None:
        psx_dir = args.reuse_psx.resolve()
        if not psx_dir.is_dir():
            parser.error(f"PSX capture directory does not exist: {psx_dir}")
    else:
        psx_dir.mkdir()
    if args.reuse_pc is not None:
        pc_dir = args.reuse_pc.resolve()
        if not pc_dir.is_dir():
            parser.error(f"PC capture directory does not exist: {pc_dir}")
    else:
        pc_dir.mkdir()

    if not args.skip_build:
        subprocess.run(("cmake", "--build", str(args.build), "-j",
                        str(os.cpu_count() or 1)), cwd=WORKSPACE, check=True,
                       stdout=subprocess.DEVNULL)
        subprocess.run(("make", "-C", "tools/mednafen-build", "-j",
                        str(os.cpu_count() or 1)), cwd=WORKSPACE, check=True,
                       stdout=subprocess.DEVNULL)

    capture_env = {
        "MMX4_ORACLE_FRAME_FIRST": str(args.first),
        "MMX4_ORACLE_FRAME_LAST": str(last),
        "MMX4_ORACLE_FRAME_INTERVAL": str(args.interval),
        "MMX4_ORACLE_FRAME_STOP_AFTER": str(last),
    }
    if args.reuse_psx is None:
        print(f"== capturing PSX replay frames {args.first}..{last}/{args.interval}")
        environment = os.environ.copy()
        environment.update(capture_env)
        environment.update(MMX4_INPUT_PLAY=str(args.replay),
                           MMX4_ORACLE_FRAME_DIR=str(psx_dir))
        run((str(args.mednafen), str(args.cue), str(args.bios),
             str(args.psx_frames)), output / "psx.log", environment)
    else:
        print(f"== reusing PSX captures from {psx_dir}")

    if args.reuse_pc is None:
        print(f"== capturing PC replay frames {args.first}..{last}/{args.interval}")
        environment = os.environ.copy()
        environment.update(capture_env)
        environment.update(ASAN_OPTIONS="detect_leaks=0",
                           MMX4_CANONICAL_LOAD="1",
                           MMX4_MAX_FRAMES="20000",
                           MMX4_ORACLE_FRAME_DIR=str(pc_dir),
                           MMX4_REPLAY_EXIT="1")
        command = [str(args.build / "mmx4_pc"), "--replay", str(args.replay)]
        if shutil.which("xvfb-run") is not None:
            command = ["xvfb-run", "-a", *command]
        run(command, output / "pc.log", environment)
    else:
        print(f"== reusing PC captures from {pc_dir}")

    psx_files = {path.name: path for path in psx_dir.glob("frame_*.ppm")}
    pc_files = {path.name: path for path in pc_dir.glob("frame_*.ppm")}
    shared = sorted(set(psx_files) & set(pc_files))
    if not shared:
        raise SystemExit("no shared PC/PSX frame captures")
    print(f"== scoring {len(shared)} shared frames")
    ranked = sorted(ssim.score_directories(psx_dir, pc_dir),
                    key=lambda row: row[1])

    with (output / "scores.tsv").open("w") as report:
        writer = csv.writer(report, delimiter="\t", lineterminator="\n")
        writer.writerow(("rank", "frame", "ssim", "psx", "pc"))
        for rank, (filename, score) in enumerate(ranked, 1):
            frame = int(Path(filename).stem.split("_")[1])
            writer.writerow((rank, frame, f"{score:.9f}",
                             str(psx_files[filename]), str(pc_files[filename])))
    write_ranked_images(output, ranked, psx_dir, pc_dir,
                        min(args.top, len(ranked)))
    (output / "metadata.txt").write_text(
        f"replay={args.replay.resolve()}\nsha256={metadata['sha256']}\n"
        f"range={args.first}..{last}\ninterval={args.interval}\n"
        f"shared={len(shared)}\nworst={ranked[0][1]:.9f}\n"
        f"best={ranked[-1][1]:.9f}\npsx={psx_dir}\n"
    )
    print(f"worst={ranked[0][1]:.6f}, best={ranked[-1][1]:.6f}")
    print(f"report: {output / 'scores.tsv'}")
    print(f"images: {output / 'index.html'}")


if __name__ == "__main__":
    main()
