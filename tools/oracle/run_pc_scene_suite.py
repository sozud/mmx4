#!/usr/bin/env python3
import argparse
import os
from pathlib import Path
import shutil
import subprocess

from scene_suite import PC_SCENES, validate_scene


def main():
    workspace = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output", type=Path, default=workspace / "pc-object-changes"
    )
    parser.add_argument(
        "--binary", type=Path, default=workspace / "build-linux/mmx4_pc"
    )
    parser.add_argument(
        "--scene", choices=[scene for scene, _ in PC_SCENES],
        help="capture only one scene instead of the complete suite",
    )
    args = parser.parse_args()
    if not args.binary.is_file():
        parser.error(f"required binary does not exist: {args.binary}")

    args.output.mkdir(parents=True, exist_ok=True)
    scenes = PC_SCENES if args.scene is None else tuple(
        item for item in PC_SCENES if item[0] == args.scene
    )
    for scene, frames in scenes:
        destination = args.output / scene
        if destination.exists():
            shutil.rmtree(destination)
        destination.mkdir()
        environment = os.environ.copy()
        environment.update(
            MMX4_ORACLE_SCENE=scene,
            MMX4_ORACLE_OBJECT_CHANGE_DIR=str(destination.resolve()),
            MMX4_MAX_FRAMES=str(frames),
        )
        with (destination / "run.log").open("w") as log:
            subprocess.run(
                [str(args.binary)],
                cwd=workspace,
                env=environment,
                stdout=log,
                stderr=subprocess.STDOUT,
                check=True,
            )
        images, triggers = validate_scene(scene, destination)
        print(f"{scene}: {images} black images, {triggers} triggers")


if __name__ == "__main__":
    main()
