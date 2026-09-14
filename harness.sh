#!/bin/sh
set -eu

SOURCE_REPO=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
H="$SOURCE_REPO/tools/harness/target/release/saturn-harness"

cd "$SOURCE_REPO"

if [ "$#" -gt 0 ]; then
    exec "$H" --family psx-psp "$@"
fi

exec "$H" --family psx-psp run \
--driver codex \
--model gpt-5.6-luna \
--effort max \
--isolated-object \
--no-compiler-source --no-rtl --no-nanny \
--limit 1000 --deadline-secs 3600 --jobs 6
