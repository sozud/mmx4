#!/bin/sh
set -eu

VERSION=${VERSION:-us}
export VERSION
python3 ./build.py
ninja
sha1sum --check "check.$VERSION.txt"
