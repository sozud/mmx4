#!/bin/sh
set -eu
here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
out=${1:-$here/../../playerdumps/$(date +%Y%m%d-%H%M%S)}
mkdir -p "$out"
while read -r group script stage substage character loadout; do
    case "$group" in ''|'#'*) continue ;; esac
    "$here/run.sh" "$here/$script" "$out/$group" "$character" "$stage" "$substage" 0 "$loadout"
done < "$here/runs.txt"
python3 "$here/../player_poke_index.py" "$out"
