import argparse
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
ALL_H = "include/all.h"
ALL_USERS = {"src/pc/placeholder.c"}


def module_headers():
    out = []
    for dirpath, _, files in os.walk(os.path.join(ROOT, "include", "main")):
        for f in files:
            if f.endswith(".h"):
                out.append(os.path.relpath(os.path.join(dirpath, f), os.path.join(ROOT, "include")))
    return sorted(out)


def render_all():
    lines = ["#ifndef ALL_H\n", "#define ALL_H\n", "\n", '#include "common.h"\n']
    lines += [f'#include "{h}"\n' for h in module_headers()]
    lines += ["\n", "#endif\n"]
    return "".join(lines)


def sources():
    for top in ("src", "tests"):
        for dirpath, _, files in os.walk(os.path.join(ROOT, top)):
            for f in files:
                if f.endswith((".c", ".h")):
                    yield os.path.relpath(os.path.join(dirpath, f), ROOT)


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--write", action="store_true", help=f"regenerate {ALL_H}")
    args = p.parse_args()
    errors = []

    expected = render_all()
    path = os.path.join(ROOT, ALL_H)
    current = open(path).read() if os.path.exists(path) else ""
    if args.write:
        if current != expected:
            with open(path, "w") as fh:
                fh.write(expected)
    elif current != expected:
        errors.append(f"{ALL_H} is out of date; run python3 tools/headers/check_headers.py --write")

    for h in module_headers():
        text = open(os.path.join(ROOT, "include", h)).read()
        guard = re.sub(r"\W", "_", h).upper()
        if not text.startswith(f"#ifndef {guard}\n#define {guard}\n"):
            errors.append(f"include/{h}: missing include guard {guard}")

    for f in sources():
        text = open(os.path.join(ROOT, f), errors="replace").read()
        for name in re.findall(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
            if name == "all.h" and f not in ALL_USERS:
                errors.append(f"{f}: includes all.h; include the module headers it needs instead")
            if name in ("func_tables.h", "game_prototypes.h"):
                errors.append(f"{f}: includes removed header {name}")

    for e in errors:
        print(e)
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
