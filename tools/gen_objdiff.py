import json
import os

BUILD_DIR = "build/us"
EXPECTED_DIR = "expected/build/us"
EMPTY_OBJ = "build/us/empty.o"
OUTPUT = "objdiff.json"

CATEGORIES = [
    ("game", "Game code"),
    ("sdk", "PSX SDK"),
]


def is_excluded(src):
    return src.endswith(".bss.s") or src == "asm/us/main/header.s"


def category_for(src):
    return "sdk" if "/psxsdk/" in src else "game"


def is_asm(src):
    return src.startswith("asm/")


def collect_units():
    units = []
    for root, _, files in os.walk(BUILD_DIR):
        for f in files:
            if not f.endswith(".o"):
                continue
            obj = os.path.join(root, f)
            rel = os.path.relpath(obj, BUILD_DIR)
            if not rel.startswith(("src/", "asm/")):
                continue
            src = rel[: -len(".o")]
            if is_excluded(src):
                continue
            target = os.path.join(EXPECTED_DIR, rel)
            if not os.path.exists(target):
                continue
            units.append({
                "name": os.path.splitext(src)[0],
                "base_path": EMPTY_OBJ if is_asm(src) else obj,
                "target_path": target,
                "metadata": {
                    "source_path": src,
                    "progress_categories": [category_for(src)],
                },
            })
    units.sort(key=lambda unit: unit["name"])
    return units


def main():
    units = collect_units()
    if not units:
        raise SystemExit(f"no objects found under {BUILD_DIR} and {EXPECTED_DIR}")

    config = {
        "build_base": False,
        "build_target": False,
        "units": units,
        "progress_categories": [{"id": i, "name": n} for i, n in CATEGORIES],
    }

    with open(OUTPUT, "w") as f:
        json.dump(config, f, indent=2)
        f.write("\n")

    asm_units = sum(1 for unit in units if is_asm(unit["metadata"]["source_path"]))
    print(f"{OUTPUT}: {len(units)} units ({asm_units} not yet decompiled)")


main()
