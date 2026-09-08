#!/bin/sh
set -e

OBJDIFF_VERSION=v3.3.1
OBJDIFF_CLI=bin/objdiff-cli-linux-x86_64
VERSION=${VERSION:-us}
export VERSION
REPORT="build/$VERSION/report.json"

if [ -d "build/$VERSION" ]; then
    find "build/$VERSION" -depth -delete
fi

if [ ! -x "$OBJDIFF_CLI" ]; then
    mkdir -p bin
    wget -O "$OBJDIFF_CLI" \
        "https://github.com/encounter/objdiff/releases/download/$OBJDIFF_VERSION/objdiff-cli-linux-x86_64"
    chmod +x "$OBJDIFF_CLI"
fi

python3 ./build.py
if [ "$VERSION" = us ]; then
    ninja
    sha1sum --check check.us.txt
else
    ninja objects
fi

if [ -d "expected/build/$VERSION" ]; then
    find "expected/build/$VERSION" -depth -delete
fi
mkdir -p expected/build
cp -a "build/$VERSION" "expected/build/$VERSION"

MMX4_PROGRESS_REPORT=1 python3 ./build.py
MMX4_PROGRESS_REPORT=1 ninja objects

: > "build/$VERSION/empty.s"
mipsel-linux-gnu-as "build/$VERSION/empty.s" -o "build/$VERSION/empty.o"

python3 ./tools/gen_objdiff.py
"$OBJDIFF_CLI" report generate -o "$REPORT"

python3 ./build.py

echo "wrote $REPORT"
