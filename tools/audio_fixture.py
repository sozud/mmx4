#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import math
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
import wave


ROOT = Path(__file__).resolve().parents[1]
SAMPLE_RATE = 44100
CHANNELS = 2
SAMPLE_WIDTH = 2
FFT_SIZE = 4096
FFT_HOP = FFT_SIZE // 2

FRONTEND_SUITE = {
    "0:12": ("title-menu-move",),
    "0:34": ("title-screen-start", "title-menu-confirm"),
    "5:0": ("character-select-move",),
    "5:1": ("character-select-confirm",),
    "0:14": ("mission-briefing-text",),
    "0:10": ("stage-ready",),
    "1:13": ("stage-warp-in",),
}


def parse_sfx(text: str) -> tuple[int, int]:
    try:
        if ":" in text:
            group_text, index_text = text.split(":", 1)
            group = int(group_text, 0)
            index = int(index_text, 0)
        else:
            group = 0
            index = int(text, 0)
    except ValueError as exc:
        raise argparse.ArgumentTypeError(
            "SFX must be INDEX or GROUP:INDEX"
        ) from exc
    if not 0 <= group < 8 or not 0 <= index <= 0xFF:
        raise argparse.ArgumentTypeError("SFX group/index is out of range")
    return group, index


def run_logged(command: list[str], log: Path, env: dict[str, str] | None = None) -> None:
    with log.open("w", encoding="utf-8") as output:
        result = subprocess.run(
            command,
            cwd=ROOT,
            env=env,
            stdout=output,
            stderr=subprocess.STDOUT,
        )
    if result.returncode:
        raise RuntimeError(
            f"command failed ({result.returncode}); see {log}: "
            + " ".join(command)
        )


def trigger_result(log: Path) -> int:
    matches = re.findall(r"SFX fixture.*result=(-?\d+)",
                         log.read_text(encoding="utf-8", errors="replace"))
    if not matches:
        raise RuntimeError(f"fixture never reached its trigger; see {log}")
    return int(matches[-1])


def run_suite(args: argparse.Namespace) -> int:
    output = (args.output or ROOT / "build/audio-fixtures/frontend").resolve()
    output.mkdir(parents=True, exist_ok=True)
    targets = ("pc", "psx") if args.target == "both" else (args.target,)
    if not args.no_build:
        if "pc" in targets:
            build_pc()
        if "psx" in targets:
            build_mednafen()

    cases = []
    for selector, names in FRONTEND_SUITE.items():
        group, index = parse_sfx(selector)
        case_output = output / f"sfx-{group}-{index}"
        command = [
            sys.executable, str(Path(__file__).resolve()),
            "--sfx", selector,
            "--target", args.target,
            "--frames", str(args.frames),
            "--output", str(case_output),
            "--pc", str(args.pc),
            "--mednafen", str(args.mednafen),
            "--disc", str(args.disc),
            "--bios", str(args.bios),
            "--no-build",
        ]
        if args.reuse_audio:
            command.append("--reuse-audio")
        subprocess.run(command, cwd=ROOT, check=True)
        report_path = case_output / "comparison.json"
        cases.append({
            "selector": selector,
            "names": names,
            "artifacts": str(case_output.relative_to(output)),
            "report": json.loads(report_path.read_text(encoding="utf-8")),
        })

    manifest = {
        "suite": "frontend",
        "capture_frames": args.frames,
        "cases": cases,
    }
    manifest_path = output / "suite.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(manifest, indent=2))
    print(f"suite artifacts: {output}")
    return 0


def build_pc() -> None:
    subprocess.run(
        ["cmake", "--build", str(ROOT / "build/pc"), "-j4"],
        cwd=ROOT,
        check=True,
    )


def build_mednafen() -> None:
    build = ROOT / "tools/mednafen-build/src"
    subprocess.run(["make", "-C", str(build / "drivers_libxxx"), "-j4"], check=True)
    subprocess.run(["make", "-C", str(build), "-j4", "mednafen"], check=True)


def raw_to_wav(raw_path: Path, wav_path: Path) -> None:
    data = raw_path.read_bytes()
    frame_size = CHANNELS * SAMPLE_WIDTH
    if len(data) % frame_size:
        raise RuntimeError(f"unaligned PC PCM output: {raw_path}")
    with wave.open(str(wav_path), "wb") as output:
        output.setnchannels(CHANNELS)
        output.setsampwidth(SAMPLE_WIDTH)
        output.setframerate(SAMPLE_RATE)
        output.writeframes(data)


def read_wav(path: Path) -> tuple[int, list[int], list[int]]:
    with wave.open(str(path), "rb") as source:
        if source.getsampwidth() != 2 or source.getnchannels() != 2:
            raise RuntimeError(f"expected stereo S16 WAV: {path}")
        rate = source.getframerate()
        frames = source.readframes(source.getnframes())
    samples = struct.unpack(f"<{len(frames) // 2}h", frames)
    return rate, list(samples[0::2]), list(samples[1::2])


def apply_mednafen_reduction(
    stream: tuple[int, list[int], list[int]],
) -> tuple[int, list[int], list[int]]:
    rate, left, right = stream

    def scale(samples: list[int]) -> list[int]:
        return [(sample * 3 + 2) >> 2 for sample in samples]

    return rate, scale(left), scale(right)


def stream_metrics(left: list[int], right: list[int], rate: int) -> dict[str, float | int]:
    peak = max((abs(value) for value in left + right), default=0)
    square_sum = sum(value * value for value in left) + sum(value * value for value in right)
    count = len(left) + len(right)
    nonzero = sum(value != 0 for value in left) + sum(value != 0 for value in right)
    threshold = max(8, peak // 100)
    onset = next(
        (i for i, (lval, rval) in enumerate(zip(left, right))
         if abs(lval) >= threshold or abs(rval) >= threshold),
        len(left),
    )
    active_end = next(
        (i + 1 for i, (lval, rval) in reversed(list(enumerate(zip(left, right))))
         if abs(lval) >= threshold or abs(rval) >= threshold),
        onset,
    )
    return {
        "sample_rate": rate,
        "frames": len(left),
        "seconds": len(left) / rate,
        "nonzero_samples": nonzero,
        "peak": peak,
        "rms": math.sqrt(square_sum / count) if count else 0.0,
        "onset_frame": onset,
        "onset_seconds": onset / rate,
        "active_end_frame": active_end,
        "active_seconds": max(0, active_end - onset) / rate,
    }


def fft_in_place(values: list[complex]) -> None:
    size = len(values)
    j = 0
    for i in range(1, size):
        bit = size >> 1
        while j & bit:
            j ^= bit
            bit >>= 1
        j ^= bit
        if i < j:
            values[i], values[j] = values[j], values[i]
    length = 2
    while length <= size:
        angle = -2.0 * math.pi / length
        root = complex(math.cos(angle), math.sin(angle))
        half = length // 2
        for start in range(0, size, length):
            factor = 1.0 + 0.0j
            for offset in range(half):
                even = values[start + offset]
                odd = values[start + offset + half] * factor
                values[start + offset] = even + odd
                values[start + offset + half] = even - odd
                factor *= root
        length <<= 1


def power_spectrum(stream: tuple[int, list[int], list[int]]) -> tuple[list[float], dict[str, float | int]]:
    rate, left, right = stream
    metrics = stream_metrics(left, right, rate)
    onset = int(metrics["onset_frame"])
    active_end = int(metrics["active_end_frame"])
    channels = (left[onset:active_end], right[onset:active_end])
    power = [0.0] * (FFT_SIZE // 2 + 1)
    windows = 0
    hann = [0.5 - 0.5 * math.cos(2.0 * math.pi * i / (FFT_SIZE - 1))
            for i in range(FFT_SIZE)]
    for channel in channels:
        starts = list(range(0, max(1, len(channel) - FFT_SIZE + 1), FFT_HOP))
        final_start = max(0, len(channel) - FFT_SIZE)
        if final_start not in starts:
            starts.append(final_start)
        for start in starts:
            chunk = channel[start:start + FFT_SIZE]
            mean = sum(chunk) / len(chunk) if chunk else 0.0
            values = [complex((chunk[i] - mean) * hann[i] if i < len(chunk) else 0.0)
                      for i in range(FFT_SIZE)]
            fft_in_place(values)
            for index in range(1, len(power)):
                power[index] += values[index].real ** 2 + values[index].imag ** 2
            windows += 1
    if windows:
        power = [value / windows for value in power]
    total = sum(power)
    normalized = [value / total for value in power] if total else power
    dominant = max(range(1, len(power)), key=power.__getitem__) if total else 0
    centroid = sum(index * rate / FFT_SIZE * value
                   for index, value in enumerate(normalized))
    cumulative = 0.0
    rolloff = 0
    for index, value in enumerate(normalized):
        cumulative += value
        if cumulative >= 0.95:
            rolloff = index
            break
    return normalized, {
        "fft_size": FFT_SIZE,
        "window": "hann",
        "hop_frames": FFT_HOP,
        "averaged_windows": windows,
        "bin_hz": rate / FFT_SIZE,
        "dominant_frequency_hz": dominant * rate / FFT_SIZE,
        "spectral_centroid_hz": centroid,
        "spectral_rolloff_95_hz": rolloff * rate / FFT_SIZE,
    }


def compare_spectra(pc: list[float], psx: list[float], rate: int) -> dict[str, float]:
    dot = sum(a * b for a, b in zip(pc, psx))
    pc_energy = sum(value * value for value in pc)
    psx_energy = sum(value * value for value in psx)
    cosine = dot / math.sqrt(pc_energy * psx_energy) if pc_energy and psx_energy else 0.0
    js = 0.0
    for a, b in zip(pc, psx):
        middle = (a + b) / 2.0
        if a:
            js += 0.5 * a * math.log2(a / middle)
        if b:
            js += 0.5 * b * math.log2(b / middle)
    pc_peak = max(pc, default=0.0)
    psx_peak = max(psx, default=0.0)
    pairs = []
    for index, (a, b) in enumerate(zip(pc, psx)):
        frequency = index * rate / FFT_SIZE
        if not 20.0 <= frequency <= 20000.0:
            continue
        pc_db = max(-100.0, 10.0 * math.log10(a / pc_peak)) if a and pc_peak else -100.0
        psx_db = max(-100.0, 10.0 * math.log10(b / psx_peak)) if b and psx_peak else -100.0
        if pc_db > -80.0 or psx_db > -80.0:
            pairs.append((pc_db, psx_db))
    log_rmse = math.sqrt(sum((a - b) ** 2 for a, b in pairs) / len(pairs)) if pairs else 100.0
    if pairs:
        pc_mean = sum(a for a, _ in pairs) / len(pairs)
        psx_mean = sum(b for _, b in pairs) / len(pairs)
        covariance = sum((a - pc_mean) * (b - psx_mean) for a, b in pairs)
        pc_variance = sum((a - pc_mean) ** 2 for a, _ in pairs)
        psx_variance = sum((b - psx_mean) ** 2 for _, b in pairs)
        log_correlation = covariance / math.sqrt(pc_variance * psx_variance) \
            if pc_variance and psx_variance else 0.0
    else:
        log_correlation = 0.0
    return {
        "power_cosine_similarity": cosine,
        "jensen_shannon_divergence": js,
        "log_spectrum_correlation": log_correlation,
        "log_spectrum_rmse_db": log_rmse,
    }


def compare_streams(pc: tuple[int, list[int], list[int]],
                    psx: tuple[int, list[int], list[int]]) -> dict[str, float | int]:
    pc_rate, pc_left, pc_right = pc
    psx_rate, psx_left, psx_right = psx
    if pc_rate != psx_rate:
        raise RuntimeError(f"sample-rate mismatch: PC={pc_rate}, PSX={psx_rate}")
    pc_metrics = stream_metrics(pc_left, pc_right, pc_rate)
    psx_metrics = stream_metrics(psx_left, psx_right, psx_rate)
    pc_onset = int(pc_metrics["onset_frame"])
    psx_onset = int(psx_metrics["onset_frame"])
    pc_end = int(pc_metrics["active_end_frame"])
    psx_end = int(psx_metrics["active_end_frame"])
    pc_mono = [(a + b) / 2
               for a, b in zip(pc_left[pc_onset:pc_end], pc_right[pc_onset:pc_end])]
    psx_mono = [(a + b) / 2
                for a, b in zip(psx_left[psx_onset:psx_end], psx_right[psx_onset:psx_end])]
    count = min(len(pc_mono), len(psx_mono))
    pc_mono = pc_mono[:count]
    psx_mono = psx_mono[:count]
    dot = sum(a * b for a, b in zip(pc_mono, psx_mono))
    pc_energy = sum(value * value for value in pc_mono)
    psx_energy = sum(value * value for value in psx_mono)
    correlation = dot / math.sqrt(pc_energy * psx_energy) if pc_energy and psx_energy else 0.0
    pc_peak = max((abs(value) for value in pc_mono), default=0.0)
    psx_peak = max((abs(value) for value in psx_mono), default=0.0)
    normalized_mae = (
        sum(abs(a / pc_peak - b / psx_peak) for a, b in zip(pc_mono, psx_mono)) / count
        if count and pc_peak and psx_peak else 0.0
    )
    return {
        "aligned_frames": count,
        "onset_delta_frames": pc_onset - psx_onset,
        "normalized_correlation": correlation,
        "normalized_mean_absolute_error": normalized_mae,
        "peak_ratio_pc_to_psx": (
            float(pc_metrics["peak"]) / float(psx_metrics["peak"])
            if psx_metrics["peak"] else 0.0
        ),
    }


def assess_similarity(pc_metrics: dict[str, object],
                      psx_metrics: dict[str, object],
                      comparison: dict[str, object],
                      spectral: dict[str, float]) -> dict[str, object]:
    duration_delta = abs(float(pc_metrics["active_seconds"]) -
                         float(psx_metrics["active_seconds"]))
    peak_ratio = float(comparison["peak_ratio_pc_to_psx"])
    log_correlation = spectral["log_spectrum_correlation"]
    checks = {
        "duration_delta_at_most_75ms": duration_delta <= 0.075,
        "peak_ratio_between_0.4_and_1.2": 0.4 <= peak_ratio <= 1.2,
        "log_spectrum_correlation_at_least_0.85": log_correlation >= 0.85,
    }
    return {
        "passed": all(checks.values()),
        "duration_delta_seconds": duration_delta,
        "checks": checks,
    }


def envelope(left: list[int], right: list[int], width: int) -> list[float]:
    peak = max((abs(value) for value in left + right), default=1)
    values: list[float] = []
    for column in range(width):
        start = column * len(left) // width
        end = max(start + 1, (column + 1) * len(left) // width)
        level = max(
            (max(abs(left[i]), abs(right[i])) for i in range(start, min(end, len(left)))),
            default=0,
        )
        values.append(level / peak)
    return values


def write_svg(path: Path, pc: tuple[int, list[int], list[int]],
              psx: tuple[int, list[int], list[int]], label: str) -> None:
    width, height = 1200, 420
    pc_metrics = stream_metrics(pc[1], pc[2], pc[0])
    psx_metrics = stream_metrics(psx[1], psx[2], psx[0])
    pc_start = max(0, int(pc_metrics["onset_frame"]) - pc[0] // 100)
    psx_start = max(0, int(psx_metrics["onset_frame"]) - psx[0] // 100)
    pc_end = min(len(pc[1]), int(pc_metrics["active_end_frame"]) + pc[0] // 10)
    psx_end = min(len(psx[1]), int(psx_metrics["active_end_frame"]) + psx[0] // 10)
    pc_env = envelope(pc[1][pc_start:pc_end], pc[2][pc_start:pc_end], width)
    psx_env = envelope(psx[1][psx_start:psx_end], psx[2][psx_start:psx_end], width)

    def points(values: list[float], baseline: float, amplitude: float) -> str:
        return " ".join(
            f"{x},{baseline - value * amplitude:.2f}" for x, value in enumerate(values)
        )

    svg = f"""<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">
<rect width="100%" height="100%" fill="#11151b"/>
<text x="20" y="28" fill="#e8edf2" font-family="monospace" font-size="18">MMX4 SFX {label}</text>
<text x="20" y="54" fill="#55aaff" font-family="monospace" font-size="14">PC normalized envelope</text>
<polyline fill="none" stroke="#55aaff" stroke-width="1.5" points="{points(pc_env, 190, 120)}"/>
<line x1="0" y1="190" x2="{width}" y2="190" stroke="#33404d"/>
<text x="20" y="230" fill="#ff9f43" font-family="monospace" font-size="14">PSX/Mednafen normalized envelope</text>
<polyline fill="none" stroke="#ff9f43" stroke-width="1.5" points="{points(psx_env, 390, 120)}"/>
<line x1="0" y1="390" x2="{width}" y2="390" stroke="#33404d"/>
</svg>\n"""
    path.write_text(svg, encoding="utf-8")


def write_spectrum_svg(path: Path, pc: list[float], psx: list[float],
                       rate: int, label: str) -> None:
    width, height = 1200, 440
    left, right, top, bottom = 70, 1180, 55, 390
    min_hz, max_hz = 20.0, 20000.0

    def db_values(power: list[float]) -> list[float]:
        peak = max(power, default=0.0)
        return [max(-100.0, 10.0 * math.log10(value / peak))
                if value and peak else -100.0 for value in power]

    def points(power: list[float]) -> str:
        db = db_values(power)
        result = []
        for x in range(left, right + 1):
            ratio = (x - left) / (right - left)
            frequency = min_hz * (max_hz / min_hz) ** ratio
            index = min(len(db) - 1, max(1, round(frequency * FFT_SIZE / rate)))
            y = bottom - (db[index] + 100.0) / 100.0 * (bottom - top)
            result.append(f"{x},{y:.2f}")
        return " ".join(result)

    grid = []
    for frequency in (20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000):
        ratio = math.log(frequency / min_hz) / math.log(max_hz / min_hz)
        x = left + ratio * (right - left)
        label_text = f"{frequency // 1000}k" if frequency >= 1000 else str(frequency)
        grid.append(f'<line x1="{x:.2f}" y1="{top}" x2="{x:.2f}" y2="{bottom}" stroke="#27313b"/>')
        grid.append(f'<text x="{x:.2f}" y="{bottom + 24}" text-anchor="middle" fill="#9aa7b2" font-family="monospace" font-size="12">{label_text}</text>')
    for level in (-100, -80, -60, -40, -20, 0):
        y = bottom - (level + 100.0) / 100.0 * (bottom - top)
        grid.append(f'<line x1="{left}" y1="{y:.2f}" x2="{right}" y2="{y:.2f}" stroke="#27313b"/>')
        grid.append(f'<text x="{left - 8}" y="{y + 4:.2f}" text-anchor="end" fill="#9aa7b2" font-family="monospace" font-size="12">{level}</text>')
    svg = f"""<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">
<rect width="100%" height="100%" fill="#11151b"/>
<text x="20" y="28" fill="#e8edf2" font-family="monospace" font-size="18">MMX4 SFX {label} averaged FFT spectrum</text>
{''.join(grid)}
<polyline fill="none" stroke="#55aaff" stroke-width="1.5" points="{points(pc)}"/>
<polyline fill="none" stroke="#ff9f43" stroke-width="1.5" points="{points(psx)}"/>
<text x="85" y="76" fill="#55aaff" font-family="monospace" font-size="14">PC</text>
<text x="125" y="76" fill="#ff9f43" font-family="monospace" font-size="14">PSX/Mednafen</text>
<text x="20" y="{bottom + 24}" fill="#9aa7b2" font-family="monospace" font-size="12">dB</text>
<text x="{right}" y="{bottom + 42}" text-anchor="end" fill="#9aa7b2" font-family="monospace" font-size="12">frequency (Hz, logarithmic)</text>
</svg>\n"""
    path.write_text(svg, encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    selection = parser.add_mutually_exclusive_group(required=True)
    selection.add_argument("--sfx", type=parse_sfx,
                           metavar="INDEX|GROUP:INDEX")
    selection.add_argument("--suite", choices=("frontend",),
                           help="run a named SFX regression suite")
    parser.add_argument("--target", choices=("both", "pc", "psx"), default="both")
    parser.add_argument("--frames", type=int, default=360,
                        help="post-trigger frames to render (default: 360)")
    parser.add_argument("--output", type=Path)
    parser.add_argument("--pc", type=Path, default=ROOT / "build/pc/mmx4_pc")
    parser.add_argument("--mednafen", type=Path,
                        default=ROOT / "tools/mednafen-build/src/mednafen")
    parser.add_argument("--disc", type=Path, default=ROOT / "disks/mmx4.us.cue")
    parser.add_argument("--bios", type=Path, default=ROOT / "tools/SCPH1001.BIN")
    parser.add_argument("--no-build", action="store_true")
    parser.add_argument("--reuse-audio", action="store_true",
                        help="reanalyze existing WAV/log artifacts without capturing")
    args = parser.parse_args()
    if not 1 <= args.frames <= 36000:
        parser.error("--frames must be in the range 1..36000")
    if args.suite:
        return run_suite(args)

    group, index = args.sfx
    selector = f"{group}:{index}"
    output = args.output or ROOT / "build/audio-fixtures" / f"sfx-{group}-{index}"
    output = output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    targets = ("pc", "psx") if args.target == "both" else (args.target,)

    if not args.no_build:
        if "pc" in targets:
            build_pc()
        if "psx" in targets:
            build_mednafen()

    streams: dict[str, tuple[int, list[int], list[int]]] = {}
    report: dict[str, object] = {
        "sfx": {"group": group, "index": index},
        "capture_frames": args.frames,
    }

    if "pc" in targets:
        pc_raw = output / "pc.raw"
        pc_wav = output / "pc.wav"
        if not args.reuse_audio:
            run_logged(
                [str(args.pc.resolve()), "--cue", str(args.disc.resolve()),
                 "--sfx", selector, "--audio-raw", str(pc_raw),
                 "--frames", str(args.frames)],
                output / "pc.log",
            )
            raw_to_wav(pc_raw, pc_wav)
        elif not pc_wav.is_file() or not (output / "pc.log").is_file():
            raise RuntimeError(f"missing reusable PC artifacts in {output}")
        streams["pc"] = read_wav(pc_wav)
        pc_metrics = stream_metrics(*streams["pc"][1:], streams["pc"][0])
        pc_metrics["trigger_result"] = trigger_result(output / "pc.log")
        report["pc"] = pc_metrics

    if "psx" in targets:
        psx_wav = output / "psx.wav"
        environment = os.environ.copy()
        environment.update(
            MMX4_SFX=selector,
            MMX4_SFX_FRAMES=str(args.frames),
            MMX4_AUDIO_WAV=str(psx_wav),
            MMX4_ORACLE_AUTOPLAY="0",
            MMX4_ORACLE_LOG_INTERVAL="0",
        )
        if not args.reuse_audio:
            run_logged(
                [str(args.mednafen.resolve()), str(args.disc.resolve()),
                 str(args.bios.resolve()), "10000"],
                output / "psx.log",
                environment,
            )
        elif not psx_wav.is_file() or not (output / "psx.log").is_file():
            raise RuntimeError(f"missing reusable PSX artifacts in {output}")
        streams["psx"] = read_wav(psx_wav)
        psx_metrics = stream_metrics(*streams["psx"][1:], streams["psx"][0])
        psx_metrics["trigger_result"] = trigger_result(output / "psx.log")
        report["psx"] = psx_metrics

    if "pc" in streams and "psx" in streams:
        compared_psx = apply_mednafen_reduction(streams["psx"])
        compared_psx_metrics = stream_metrics(
            compared_psx[1], compared_psx[2], compared_psx[0]
        )
        compared_psx_metrics["trigger_result"] = report["psx"]["trigger_result"]
        report["comparison_input"] = {
            "mednafen_gain_numerator": 3,
            "mednafen_gain_denominator": 4,
            "mednafen": compared_psx_metrics,
        }
        report["comparison"] = compare_streams(streams["pc"], compared_psx)
        pc_spectrum, pc_spectrum_metrics = power_spectrum(streams["pc"])
        psx_spectrum, psx_spectrum_metrics = power_spectrum(compared_psx)
        report["spectrum"] = {
            "method": "averaged Hann-window FFT power over both channels",
            "pc": pc_spectrum_metrics,
            "psx": psx_spectrum_metrics,
            "comparison": compare_spectra(pc_spectrum, psx_spectrum,
                                           streams["pc"][0]),
        }
        report["assessment"] = assess_similarity(
            report["pc"], compared_psx_metrics, report["comparison"],
            report["spectrum"]["comparison"])
        write_svg(output / "waveforms.svg", streams["pc"], compared_psx, selector)
        write_spectrum_svg(output / "spectrum.svg", pc_spectrum, psx_spectrum,
                           streams["pc"][0], selector)

    report_path = output / "comparison.json"
    report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))
    print(f"artifacts: {output}")
    return int(
        "assessment" in report and not bool(report["assessment"]["passed"])
    )


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, RuntimeError, subprocess.CalledProcessError) as exc:
        print(f"audio fixture: {exc}", file=sys.stderr)
        raise SystemExit(1)
