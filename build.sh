#!/bin/sh
set -eu

VERSION=${VERSION:-us}
export VERSION
BUILD_FILE="build/$VERSION/build.ninja"
python3 ./build.py
ninja -f "$BUILD_FILE"
sha1sum --check "check.$VERSION.txt"
