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
    parser.add_argument("--state-output", type=Path)
    parser.add_argument(
        "--binary", type=Path, default=workspace / "build-linux/mmx4_pc"
    )
    parser.add_argument(
        "--scene", choices=[scene for scene, _ in PC_SCENES],
        help="capture only one scene instead of the complete suite",
    )
    parser.add_argument("--no-xvfb", action="store_true")
    args = parser.parse_args()
    if not args.binary.is_file():
        parser.error(f"required binary does not exist: {args.binary}")

    args.output.mkdir(parents=True, exist_ok=True)
    if args.state_output is not None:
        args.state_output.mkdir(parents=True, exist_ok=True)
    scenes = PC_SCENES if args.scene is None else tuple(
        item for item in PC_SCENES if item[0] == args.scene
    )
    for scene, frames in scenes:
        destination = args.output / scene
        if destination.exists():
            shutil.rmtree(destination)
        destination.mkdir()
        state_destination = None
        if args.state_output is not None:
            state_destination = args.state_output / scene
            if state_destination.exists():
                shutil.rmtree(state_destination)
            state_destination.mkdir()
        environment = os.environ.copy()
        environment.update(
            ASAN_OPTIONS="detect_leaks=0",
            MMX4_CANONICAL_LOAD="1",
            MMX4_ORACLE_SCENE=scene,
            MMX4_ORACLE_OBJECT_CHANGE_DIR=str(destination.resolve()),
            MMX4_MAX_FRAMES=str(frames),
        )
        if state_destination is not None:
            environment["MMX4_ORACLE_SCREENSHOT_DIR"] = str(
                state_destination.resolve()
            )
        command = [str(args.binary)]
        if not args.no_xvfb and shutil.which("xvfb-run") is not None:
            command = ["xvfb-run", "-a", *command]
        with (destination / "run.log").open("w") as log:
            subprocess.run(
                command,
                cwd=workspace,
                env=environment,
                stdout=log,
                stderr=subprocess.STDOUT,
                check=True,
            )
        images, triggers = validate_scene(scene, destination)
        print(f"{scene}: {images} images, {triggers} triggers")


if __name__ == "__main__":
    main()
