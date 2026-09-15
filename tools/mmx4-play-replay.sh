#!/bin/sh
set -eu

usage() {
    echo "usage: $0 [--binary PATH] FILE.mmx4r [extra mmx4_pc arguments...]" >&2
    exit 2
}

workspace=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
binary=""
while [ $# -gt 0 ]; do
    case "$1" in
        --binary) [ $# -ge 2 ] || usage; binary="$2"; shift 2 ;;
        --) shift; break ;;
        -*) usage ;;
        *) break ;;
    esac
done
[ $# -ge 1 ] || usage
replay="$1"
shift

if [ -z "$binary" ]; then
    for candidate in build-asan build-linux build-macos build; do
        if [ -x "$workspace/$candidate/mmx4_pc" ]; then
            binary="$workspace/$candidate/mmx4_pc"
            break
        fi
    done
fi
[ -n "$binary" ] || { echo "$0: no mmx4_pc binary found; pass --binary" >&2; exit 1; }
[ -f "$replay" ] || { echo "$0: no such replay: $replay" >&2; exit 1; }

cd "$workspace"
if [ -n "${MMX4_HEADLESS:-}" ] && command -v xvfb-run >/dev/null 2>&1; then
    exec xvfb-run -a "$binary" --replay "$replay" "$@"
fi
exec "$binary" --replay "$replay" "$@"
