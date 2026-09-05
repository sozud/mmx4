#!/usr/bin/env bash
set -euo pipefail

input=""
output=""

while (($#)); do
    case "$1" in
        -o)
            output="$2"
            shift 2
            ;;
        -I*)
            shift
            ;;
        *)
            input="$1"
            shift
            ;;
    esac
done

if [[ -z "$input" || -z "$output" ]]; then
    echo "usage: $0 input.c -o output.o" >&2
    exit 2
fi

task_tmp="$(mktemp -d)"
trap 'rm -rf "$task_tmp"' EXIT

./bin/cc1 -w -quiet -msoft-float -O2 -g0 -G0 -funsigned-char \
    "$input" -o "$task_tmp/input.s"
python3 tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div \
    "$task_tmp/input.s" > "$task_tmp/input.s_"
mipsel-linux-gnu-as -no-pad-sections -I./src/main \
    "$task_tmp/input.s_" -o "$output"
