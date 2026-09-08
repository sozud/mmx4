#!/bin/sh
set -eu

VERSION=${VERSION:-us}

ls disks
ls disks/dependencies
bchunk "disks/mmx4.$VERSION.bin" "disks/mmx4.$VERSION.cue" "disks/mmx4.$VERSION.iso"
7z x "disks/mmx4.$VERSION.iso01.iso" -o"disks/$VERSION/" || true
