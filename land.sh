#!/bin/sh
set -eu

SOURCE_REPO=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
LAND_REPO=${LAND_REPO:-"$SOURCE_REPO-land"}
HARNESS=${HARNESS:-"$SOURCE_REPO/tools/harness/target/release/saturn-harness"}
BEST_ROOT=${BEST_ROOT:-"$SOURCE_REPO/tools/harness/psx_psp/best"}
LAND_LIMIT=${LAND_LIMIT:-1000}

DEFAULT_IGNORE_FILE=$(dirname "$SOURCE_REPO")/mmx4-jp/funcs.txt
IGNORE_FILE=${IGNORE_FILE:-$DEFAULT_IGNORE_FILE}

if [ -f "$IGNORE_FILE" ]; then
    set -- --ignore-file "$IGNORE_FILE" "$@"
fi

exec "$HARNESS" \
    --family psx-psp \
    --repo "$LAND_REPO" \
    --best-root "$BEST_ROOT" \
    land \
    --base-ref origin/main \
    --limit "$LAND_LIMIT" \
    --max-lines 500 \
    --skip-nanny \
    --no-commit \
    "$@"
