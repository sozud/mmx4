#!/bin/sh
set -eu
usage() {
    echo "usage: $0 SCRIPT OUTDIR [CHARACTER] [STAGE] [SUBSTAGE] [CHECKPOINT] [LOADOUT]" >&2
    exit 2
}
[ $# -ge 2 ] || usage
workspace=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
binary=${MMX4_PLAYER_POKE_BINARY:-$workspace/build-linux-playerdump/mmx4_pc}
cd "$workspace"
MMX4_ORACLE_SCENE=initial-stage \
MMX4_DIRECT_STAGE=${4:-1} MMX4_DIRECT_SUBSTAGE=${5:-0} MMX4_DIRECT_CHECKPOINT=${6:-0} \
MMX4_DIRECT_CHARACTER=${3:-0} MMX4_DIRECT_LOADOUT=${7:-0} MMX4_DIRECT_STORY=3 \
MMX4_MAX_FRAMES=1000000 MMX4_PLAYER_POKE_SCRIPT="$1" MMX4_PLAYER_POKE_DIR="$2" \
MMX4_PC_STUB_CONTINUE=1 SDL_VIDEO_DRIVER=offscreen SDL_AUDIO_DRIVER=dummy \
timeout 1800 "$binary" 2>&1 | grep "MMX4 PC"
