#!/usr/bin/env python3

###
# Generates build files for the GameCube project (Mega Man X Collection, GXGE08: MMX4 is files/x4.rel).
# Based on dtk-template (https://github.com/encounter/dtk-template).
#
# Usage (from this directory):
#   python3 configure.py
#   ninja
#
# Put the disc image or its extracted files in orig/GXGE08 (sys/main.dol and files/x4.rel are used).
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

DEFAULT_VERSION = 0
VERSIONS = [
    "GXGE08",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.9.0"
config.objdiff_tag = "v3.8.3"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# The game source is shared with the PSX build: src is a symlink to ../src.

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.map:
    config.ldflags.append("-mapunused")

config.reconfig_deps = [Path("objects.txt")]
config.scratch_preset_id = None

# Flags for the game code (MMX4's C, built for GameCube with CodeWarrior GC/2.6).
cflags_game = [
    "-nodefaults",
    "-nosyspath",
    "-proc gekko",
    "-fp hard",
    "-O4,p",
    "-use_lmw_stmw on",
    "-inline auto,deferred",
    "-enum int",
    "-relax_pointers",
    "-sdata 0",
    "-sdata2 0",
    "-str readonly",
    "-pooldata off",
    "-Cpp_exceptions off",
    '-pragma "cats off"',
    "-prefix prefix.h",
    "-i ../include",
    "-i ../include/psy-q-4.0",
    "-i sysinc",
    "-DSKIP_ASM",
    "-DMMX4_BIG_ENDIAN",
    "-DMMX4_GAMECUBE",
]

config.linker_version = "GC/2.6"
config.shift_jis = False  # the source is ASCII; no sjiswrap step

Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


def objects(list_path: Path) -> List[Object]:
    """Every TU of x4.rel, from objects.txt (paths relative to ../src); `*` marks a matching one."""
    result = []
    for line in list_path.read_text().split("\n"):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("*"):
            result.append(Object(Matching, line[1:].strip()))
        else:
            result.append(Object(NonMatching, line))
    return result


config.warn_missing_config = False
config.warn_missing_source = False
config.libs = [
    {
        "lib": "x4",
        "mw_version": "GC/2.6",
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": objects(Path("objects.txt")),
    },
]

config.progress_categories = [
    ProgressCategory("game", "Game Code"),
]
config.progress_each_module = args.verbose
config.progress_report_args = []

if args.mode == "configure":
    generate_build(config)
elif args.mode == "progress":
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
