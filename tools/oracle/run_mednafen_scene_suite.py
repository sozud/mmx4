#!/usr/bin/env python3
import argparse
import os
from pathlib import Path
import shutil
import subprocess

from scene_suite import MEDNAFEN_SCENES, validate_scene


def main():
    workspace = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output", type=Path, default=workspace / "mednafen-object-changes"
    )
    parser.add_argument(
        "--mednafen",
        type=Path,
        default=workspace / "tools/mednafen-build/src/mednafen",
    )
    parser.add_argument("--disc", type=Path, default=workspace / "disks/mmx4.us.cue")
    parser.add_argument("--bios", type=Path, default=workspace / "tools/SCPH1001.BIN")
    parser.add_argument(
        "--scene", choices=[scene for scene, _ in MEDNAFEN_SCENES],
        help="capture only one scene instead of the complete suite",
    )
    args = parser.parse_args()
    for required in (args.mednafen, args.disc, args.bios):
        if not required.is_file():
            parser.error(f"required file does not exist: {required}")

    args.output.mkdir(parents=True, exist_ok=True)
    scenes = MEDNAFEN_SCENES if args.scene is None else tuple(
        item for item in MEDNAFEN_SCENES if item[0] == args.scene
    )
    for scene, frames in scenes:
        destination = args.output / scene
        if destination.exists():
            shutil.rmtree(destination)
        destination.mkdir()
        environment = os.environ.copy()
        environment.update(
            MMX4_ORACLE_SCENE=scene,
            MMX4_ORACLE_AUTOPLAY="0",
            MMX4_ORACLE_LOG_INTERVAL="0",
            MMX4_ORACLE_OBJECT_CHANGE_DIR=str(destination.resolve()),
            MMX4_DIRECT_STAGE="0",
            MMX4_DIRECT_SUBSTAGE="0",
            MMX4_DIRECT_CHECKPOINT="0",
            MMX4_DIRECT_CHARACTER="0",
        )
        if scene == "mission-briefing":
            environment["MMX4_ORACLE_AUTOPLAY"] = "1"
        with (destination / "run.log").open("w") as log:
            subprocess.run(
                [str(args.mednafen), str(args.disc), str(args.bios), str(frames)],
                cwd=workspace,
                env=environment,
                stdout=log,
                stderr=subprocess.STDOUT,
                check=True,
            )
        images, triggers = validate_scene(scene, destination)
        print(f"{scene}: {images} images, {triggers} triggers -> {destination}")


if __name__ == "__main__":
    main()
