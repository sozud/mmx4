#!/bin/bash
set -e
cd "$(dirname "$0")/../.."
REPLAY=${1:-tools/oracle/recordings/memcard-load-unformatted.mmx4r}
OUTPUT=${2:-replay-runs/memcard}
BUILD=${3:-build-replay-fast}
MEDNAFEN=${MEDNAFEN:-tools/mednafen-build/src/mednafen}
SAV=tools/oracle/mednafen-state/sav/mmx4.us.7f9bb0cc4a835b8c03513b4a7fb0d284
mkdir -p "$OUTPUT/cards" "$OUTPUT/backup"
cp $SAV.0.mcr "$OUTPUT/backup/card0.mcr"
cp $SAV.1.mcr "$OUTPUT/backup/card1.mcr"
trap 'cp "$OUTPUT/backup/card0.mcr" $SAV.0.mcr; cp "$OUTPUT/backup/card1.mcr" $SAV.1.mcr' EXIT
head -c 131072 /dev/zero > $SAV.0.mcr
cp $SAV.0.mcr "$OUTPUT/cards/card0.mcr"
cp $SAV.1.mcr "$OUTPUT/cards/card1.mcr"
MMX4_MEMCARD_DIR="$OUTPUT/cards" python3 tools/oracle/run_replay_regression.py --skip-build \
    --replay "$REPLAY" --output "$OUTPUT" --build "$BUILD" --mednafen "$MEDNAFEN" \
    --expect-sha256 "$(sha256sum "$REPLAY" | cut -d' ' -f1)"
