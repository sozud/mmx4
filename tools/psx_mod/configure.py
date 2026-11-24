#!/usr/bin/env python3

import argparse
import glob
import os
import re
import sys

sys.path.insert(0, os.getcwd())
import ninja_syntax

GAME_DIRS = ("", "data", "effects", "items", "layers", "mains", "misc", "quads",
             "shots", "unks", "visuals", "weapons")
VERSIONS = ("us",)
SPLAT_CONFIG = {"us": "config/SLUS_005.61.splat.yaml"}
PSYQ_DIR = "tools/psy-q-decomp"
SKIP_SOURCES = {"src/main/data/sdk_runtime_data.c", "src/main/data/bss.c"}
MOD_ASM = [
    ("", "src/psx_mod/bss.s"),
    ("psxsdk/2mbyte", "src/psx_mod/crt0.s"),
    ("psxsdk/libsn/sndef", "src/psx_mod/sndef.s"),
]
EXTRA_SDK = [
    ("psxsdk/libsnd/sepinit", "src/psx_mod/sepinit.s", {}),
    ("psxsdk/libcard/patch", "src/psx_mod/card_patch.s", {}),
    ("psxsdk/libcard/end", "src/psx_mod/card_end.s", {}),
    ("psxsdk/libapi/patch", "src/psx_mod/api_patch.s", {}),
    ("psxsdk/libgte/patchgte", "src/psx_mod/patchgte.s", {}),
    ("psxsdk/libpress/vlc", "src/psx_mod/vlc.s", {}),
]
SEGMENT = re.compile(r"^\s*- \[0x([0-9A-Fa-f]+), *([.\w]+)(?:, *([\w/]+))?\]")

CPP_COMMON = ("-undef -D__GNUC__=2 -D__OPTIMIZE__ -lang-c -Dmips -D__mips__ -D__mips -Dpsx"
              " -D__psx__ -D__psx -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__"
              " -D_LANGUAGE_C -DLANGUAGE_C")


def psyq_objects(version):
    objects = []
    with open(f"config/psyq.{version}.txt") as config:
        for line in config:
            fields = line.split("#")[0].split()
            if fields:
                options = dict(field.split("=", 1) for field in fields[2:])
                objects.append((fields[0], f"{PSYQ_DIR}/{fields[1]}", options))
    return objects


def retail_sections(version):
    order = {"rodata": [], "text": [], "data": []}
    kinds = {".rodata": "rodata", "rodata": "rodata", "c": "text", "asm": "text", ".data": "data", "data": "data"}
    with open(SPLAT_CONFIG[version]) as config:
        for line in config:
            match = SEGMENT.match(line)
            if match and match.group(2) in kinds:
                offset, kind, name = match.groups()
                name = name or offset.upper()
                if name not in order[kinds[kind]]:
                    order[kinds[kind]].append(name)
    return order


def write_linker_script(version, objects, path):
    by_name = {}
    for name, obj in objects:
        by_name.setdefault(name, obj)
    order = retail_sections(version)
    sections = {"RODATA": ("rodata", ".rodata .rodata.* .rdata"), "TEXT": ("text", ".text .text.*"),
                "DATA": ("data", ".data .data.* .sdata")}
    text = open("tools/psx_mod/psx.ld").read()
    for marker, (key, patterns) in sections.items():
        lines = [f"        {by_name[name]}({patterns})" for name in order[key] if name in by_name]
        text = text.replace(f"        /* @{marker}@ */", "\n".join(lines))
    text = text.replace("        /* @BSS@ */", f"        {by_name['']}(.bss)")
    with open(path, "w") as handle:
        handle.write(text)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version", default=os.environ.get("VERSION", "us"), choices=VERSIONS)
    args = parser.parse_args()
    version = args.version
    out = f"build/{version}-mod"
    os.makedirs(out, exist_ok=True)

    ninja = ninja_syntax.Writer(open(f"{out}/build.ninja", "w"))
    ninja.variable("cc1", "./bin/cc1")
    ninja.rule("cpp", f"cpp $flags -MMD -MF $out.d -MT $out $in $out", depfile="$out.d", deps="gcc",
               description="cpp $in")
    ninja.rule("cc1", "$cc1 -w -quiet -msoft-float $opt -g0 -G0 -funsigned-char $in -o $out",
               description="cc1 $in")
    ninja.rule("maspsx", "python3 tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div $maspsx < $in > $out",
               description="maspsx $in")
    ninja.rule("as", "mipsel-linux-gnu-as -no-pad-sections -G0 $asflags $in -o $out", description="as $in")
    ninja.rule("as_psyq_s", f"(cpp -x assembler-with-cpp -P -undef -DVERSION=$version -I{PSYQ_DIR}/include $in;"
               " printf '\\t.text\\n\\t.align 4\\n\\t.data\\n\\t.align 4\\n')"
               f" | mipsel-linux-gnu-as -I{PSYQ_DIR}/include -march=r3000 -mtune=r3000"
               " -no-pad-sections -O1 -G0 -o $out", description="as $in")
    ninja.rule("link", f"mipsel-linux-gnu-ld -T {out}/psx.ld -Map $out.map -o $out $in",
               description="link $out")
    ninja.rule("exe", f"python3 tools/psx_mod/make_exe.py --version={version} $in $out", description="exe $out")

    objects = []

    game_flags = f"{CPP_COMMON} -DVERSION_{version.upper()}=1 -DSKIP_ASM=1 -DMMX4_PSX_MOD=1 -I./include"
    sources = []
    for directory in GAME_DIRS:
        sources += sorted(glob.glob(os.path.join("src/main", directory, "*.c")))
    sources = [(s, os.path.splitext(os.path.relpath(s, "src/main"))[0]) for s in sources if s not in SKIP_SOURCES]
    for source, name in sources:
        base = f"{out}/game/{os.path.splitext(source)[0]}"
        ninja.build(f"{base}.i", "cpp", source, variables={"flags": game_flags})
        ninja.build(f"{base}.s", "cc1", f"{base}.i", variables={"opt": "-O2"})
        ninja.build(f"{base}.s_", "maspsx", f"{base}.s")
        ninja.build(f"{base}.o", "as", f"{base}.s_", variables={"asflags": "-I./src/main"})
        objects.append((name, f"{base}.o"))

    for segment, source, options in psyq_objects(version) + EXTRA_SDK:
        base = f"{out}/psyq/{segment}"
        if source.startswith("src/") and source.endswith(".s"):
            ninja.build(f"{base}.o", "as", source)
        elif source.endswith(".s"):
            ninja.build(f"{base}.o", "as_psyq_s", source, variables={"version": options["VERSION"]})
        else:
            defines = "".join(f" -D{d}" for d in options.get("D", "").split(",") if d)
            flags = (f"{CPP_COMMON} -DVERSION={options['VERSION']}{defines}"
                     f" -I{PSYQ_DIR}/src/snd -I{PSYQ_DIR}/include")
            ninja.build(f"{base}.i", "cpp", source, variables={"flags": flags})
            ninja.build(f"{base}.s", "cc1", f"{base}.i", variables={"opt": f"-O{options.get('O', '2')}"})
            ninja.build(f"{base}.s_", "maspsx", f"{base}.s",
                        variables={"maspsx": "--use-comm-section --use-comm-for-lcomm"})
            ninja.build(f"{base}.o", "as", f"{base}.s_")
        objects.append((segment, f"{base}.o"))

    for name, source in MOD_ASM:
        base = f"{out}/{os.path.splitext(source)[0]}"
        ninja.build(f"{base}.o", "as", source)
        objects.append((name, f"{base}.o"))

    write_linker_script(version, objects, f"{out}/psx.ld")
    inputs = [path for _, path in objects]
    ninja.build(f"{out}/main.elf", "link", inputs, implicit=[f"{out}/psx.ld"])
    ninja.build(f"{out}/main.exe", "exe", f"{out}/main.elf", implicit=["tools/psx_mod/make_exe.py"])
    ninja.default(f"{out}/main.exe")
    ninja.close()
    print(f"wrote {out}/build.ninja")
    return 0


if __name__ == "__main__":
    sys.exit(main())
