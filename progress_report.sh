#!/bin/sh
set -e

OBJDIFF_VERSION=v3.3.1
OBJDIFF_CLI=bin/objdiff-cli-linux-x86_64
REPORT=build/us/report.json

if [ ! -x "$OBJDIFF_CLI" ]; then
    mkdir -p bin
    wget -O "$OBJDIFF_CLI" \
        "https://github.com/encounter/objdiff/releases/download/$OBJDIFF_VERSION/objdiff-cli-linux-x86_64"
    chmod +x "$OBJDIFF_CLI"
fi

python3 ./build.py
ninja
sha1sum --check check.us.txt

rm -rf expected/build/us
mkdir -p expected/build
cp -a build/us expected/build/us

MMX4_PROGRESS_REPORT=1 python3 ./build.py
MMX4_PROGRESS_REPORT=1 ninja objects

: > build/us/empty.s
mipsel-linux-gnu-as build/us/empty.s -o build/us/empty.o

python3 ./tools/gen_objdiff.py
"$OBJDIFF_CLI" report generate -o "$REPORT"

python3 ./build.py

echo "wrote $REPORT"
