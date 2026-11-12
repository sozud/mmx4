import os
import re
import subprocess
import ninja_syntax

VERSION = os.environ.get("VERSION", "us").lower()
if VERSION not in ("us", "jp", "eu"):
    raise RuntimeError(f"unsupported VERSION={VERSION!r}; expected 'us', 'jp' or 'eu'")

OUTPUT_DIR = f"build/{VERSION}"
BUILD_FILE = f"{OUTPUT_DIR}/build.ninja"
COMPILATION_DATABASE = "compile_commands.json"
ASM_ROOT = f"asm/{VERSION}/main"
LINKER_SCRIPT = "main.ld" if VERSION == "us" else f"main.{VERSION}.ld"
UNDEFINED_SYMBOL_FILES = (
    f"config/undefined_funcs_auto.{VERSION}.main.txt "
    f"config/undefined_syms_auto.{VERSION}.main.txt "
    f"config/undefined_syms.{VERSION}.main.txt"
)
if VERSION == "jp":
    UNDEFINED_SYMBOL_FILES += " config/undefined_syms.jp.manual.txt"
EXE_SIZE = 0x11B800 if VERSION == "eu" else 0x120000
CC1 = "./bin/compilers/gcc-2.8.1/cc1" if VERSION == "eu" else "./bin/cc1"
ASPSX_VERSION = "2.56"
EXTRA_CPP_DEFS = f" -DVERSION_{VERSION.upper()}=1"
if os.environ.get("MMX4_PROGRESS_REPORT") == "1":
    EXTRA_CPP_DEFS += " -DSKIP_ASM=1"

PSYQ_DIR = "tools/psy-q-decomp"
PSYQ_CC1 = "./bin/cc1"


def load_psyq_objects():
    objects = {}
    path = f"config/psyq.{VERSION}.txt"
    if os.path.exists(path):
        with open(path) as f:
            for line in f:
                fields = line.split("#")[0].split()
                if fields:
                    objects[fields[0]] = fields[1:]
    return objects


def anchor_noload_bss(linker_script_path):
    with open(linker_script_path) as linker_script:
        linker_script_text = linker_script.read()

    generated = ".main_bss (NOLOAD) : SUBALIGN(1)"
    anchored = ".main_bss main_DATA_END (NOLOAD) : SUBALIGN(1)"
    if anchored not in linker_script_text:
        if generated not in linker_script_text:
            raise RuntimeError("unexpected Splat NOLOAD BSS linker section")
        linker_script_text = linker_script_text.replace(generated, anchored, 1)
        with open(linker_script_path, "w") as linker_script:
            linker_script.write(linker_script_text)

    return linker_script_text


def add_lib(srcs, output_dir, lib_name, flags, folder):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        obj_name = f"{output_dir}/{filename_without_extension}.obj"
        ninja.build(
            obj_name,
            'compile',
            inputs=[src],
            variables={'FLAGS': flags, 'FOLDER': folder})

        # this doesn't generate a file output but ninja apparently needs an output name
        ninja.build(
            f"{obj_name}.check",
            'check',
            inputs=[obj_name],
            variables={'LIBRARY': lib_name}
        )

def add_lib_263(srcs, output_dir, linker_inputs):
    flags = ""
    folder = ""
    for src in srcs:
        filename_without_extension = os.path.splitext(src)[0]
        obj_name = f"{output_dir}/{filename_without_extension}.obj"

        cpp_flags = f"-undef -D__GNUC__=2{EXTRA_CPP_DEFS} {flags} -v -D__OPTIMIZE__ -I./src/snd -I./include -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C"

        # run c preprocessor
        ninja.build(
            f"{output_dir}/{filename_without_extension}.cpp",
            'cpp_263',
            inputs=[src],
            variables={'FLAGS': flags, 'FOLDER': folder, 'CPP_FLAGS': cpp_flags})

        # run cc1
        ninja.build(
            f"{output_dir}/{filename_without_extension}.s",
            'cc1_263',
            inputs=[f"{output_dir}/{filename_without_extension}.cpp"],
            variables={'FLAGS': flags, 'FOLDER': folder})

        # run aspsx
        ninja.build(
            f"{output_dir}/{filename_without_extension}.s_",
            'aspsx_263',
            inputs=[f"{output_dir}/{filename_without_extension}.s"],
            variables={'FLAGS': flags, 'FOLDER': folder})

        # run as
        ninja.build(
            f"{output_dir}/{filename_without_extension}.c.o",
            'as',
            inputs=[f"{output_dir}/{filename_without_extension}.s_"],
            variables={'FLAGS': flags, 'FOLDER': folder})

        linker_inputs.append(f"{output_dir}/{filename_without_extension}.c.o")

        # # # check it
        # # # this doesn't generate a file output but ninja apparently needs an output name
        # ninja.build(
        #     f"{obj_name}.check",
        #     'check',
        #     inputs=[obj_name]) # ,variables={'LIBRARY': lib_name}

def add_psyq(objects, output_dir, linker_script_text, linker_inputs):
    for segment, fields in objects.items():
        obj_name = f"{output_dir}/src/main/{segment}.c.o"
        if obj_name not in linker_script_text:
            continue
        src = f"{PSYQ_DIR}/{fields[0]}"
        opts = dict(opt.split("=", 1) for opt in fields[1:])
        defines = "".join(f" -D{d}" for d in opts.get("D", "").split(",") if d)
        if src.endswith(".s"):
            ninja.build(obj_name, 'as_psyq_s', inputs=[src])
        else:
            base = f"{output_dir}/psyq/{segment}"
            cpp_flags = (
                f"-undef -D__GNUC__=2 -DVERSION={opts['VERSION']}{defines} -D__OPTIMIZE__"
                f" -I{PSYQ_DIR}/src/snd -I{PSYQ_DIR}/include -lang-c -Dmips"
                " -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D__EXTENSIONS__"
                " -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C"
            )
            ninja.build(f"{base}.cpp", 'cpp_263', inputs=[src],
                        variables={'CPP_FLAGS': cpp_flags})
            ninja.build(f"{base}.s", 'cc1_psyq', inputs=[f"{base}.cpp"],
                        variables={'OPT': f"-O{opts.get('O', '2')}"})
            ninja.build(f"{base}.s_", 'aspsx_psyq', inputs=[f"{base}.s"])
            ninja.build(obj_name, 'as_psyq', inputs=[f"{base}.s_"])
        linker_inputs.append(obj_name)


def add_asm(srcs, output_dir, linker_inputs):
    flags = ""
    folder = ""
    # linker_inputs = []
    for src in srcs:
        filename_without_extension = os.path.splitext(src)[0]
        print("add_asm", filename_without_extension)
        obj_name = f"{output_dir}/{filename_without_extension}.s.o"

        print("obj_name", obj_name)

# build/us/asm/us/main/header.s.o
        ninja.build(
            obj_name,
            'as',
            inputs=[src],
            variables={'FLAGS': flags, 'FOLDER': folder})
        linker_inputs.append(obj_name)

    # ninja.build(
    #     "build/us/asm/us/main/header.s.o",
    #     'as',
    #     inputs=srcs,
    #     variables={'FLAGS': flags, 'FOLDER': folder})
    # linker_inputs.append("build/us/asm/us/main/header.s.o")

    # ninja.build(
    #     "build/us/asm/us/main/data/800.data.s.o",
    #     'as',
    #     inputs=['asm/us/main/data/800.data.s'],
    #     variables={'FLAGS': flags, 'FOLDER': folder})
    # linker_inputs.append("build/us/asm/us/main/data/800.data.s.o")


os.makedirs(OUTPUT_DIR, exist_ok=True)
ninja = ninja_syntax.Writer(open(BUILD_FILE, "w"))
ninja.variable("builddir", OUTPUT_DIR)

ninja.rule('compile',
           command='sh dosemu_wrapper.sh $in $out $FLAGS $FOLDER',
           description='Building $out from $in')

ninja.rule('cpp_263',
           command=f'cpp $CPP_FLAGS -MMD -MF $out.d -MT $out $in $out',
           description='Running preprocessor on $out from $in',
           depfile='$out.d',
           deps='gcc')

ninja.rule('cc1_263',
           command=f'{CC1} -w -quiet -msoft-float -O2 -g0 -G0 -funsigned-char $in -o $out',
           description='Running cc1 on $out from $in')

ninja.rule('aspsx_263',
           command=f'python3 tools/maspsx/maspsx.py --aspsx-version={ASPSX_VERSION} --expand-div < $in > $out',
           description='Running aspsx on $out from $in')

ninja.rule('cc1_psyq',
           command=f'{PSYQ_CC1} -w -quiet -msoft-float $OPT -g0 -G0 -funsigned-char $in -o $out',
           description='Running cc1 on $out from $in')

ninja.rule('aspsx_psyq',
           command=f'(python3 tools/maspsx/maspsx.py --aspsx-version={ASPSX_VERSION} --expand-div --use-comm-section --use-comm-for-lcomm < $in'
           " && printf '\\t.section .rodata\\n\\t.align 2\\n\\t.section .data\\n\\t.align 2\\n') > $out",
           description='Running aspsx on $out from $in')

ninja.rule('as_psyq',
           'mipsel-linux-gnu-as -no-pad-sections -G0 $in -o $out')

ninja.rule('as_psyq_s',
           "(cat $in; printf '\\t.text\\n\\t.align 4\\n\\t.data\\n\\t.align 4\\n')"
           f" | mipsel-linux-gnu-as -I{PSYQ_DIR}/include -march=r3000 -mtune=r3000"
           " -no-pad-sections -O1 -G0 -o $out")

ninja.rule('as',
           'mipsel-linux-gnu-as -no-pad-sections -I./src/main $in -o $out')

ninja.rule('as_empty',
           'mipsel-linux-gnu-as -no-pad-sections /dev/null -o $out')

ninja.rule('link',
           f'mipsel-linux-gnu-ld -Map={OUTPUT_DIR}/main.map -T {LINKER_SCRIPT} {UNDEFINED_SYMBOL_FILES} $in -o $out')

ninja.rule('objcopy',
           f'mipsel-linux-gnu-objcopy --pad-to={EXE_SIZE:#x} --gap-fill=0 $in -O binary $out')

ninja.rule('copy',
           'cp $in $out')

ninja.rule('check',
           'sha1sum --check $in')

ninja.rule('ld_binary',
           'mipsel-linux-gnu-ld -r -b binary -o $out $in')

def build_35():
    srcs = [
        # 'src/main/91218.c',
        # 'src/main/CA8EC.c'
    ]

    directory = 'src/main'
    for root, _, files in os.walk(directory):
        srcs.extend(os.path.join(root, f) for f in files
                    if f.endswith('.c'))

    output_dir = OUTPUT_DIR
    linker_script_text = anchor_noload_bss(LINKER_SCRIPT)
    srcs = [
        src for src in srcs
        if f"{output_dir}/{os.path.splitext(src)[0]}.c.o" in linker_script_text
    ]

    psyq_objects = load_psyq_objects()
    srcs = [
        src for src in srcs
        if os.path.splitext(os.path.relpath(src, "src/main"))[0] not in psyq_objects
    ]

    linker_inputs = []
    add_lib_263(srcs, output_dir, linker_inputs)
    add_psyq(psyq_objects, output_dir, linker_script_text, linker_inputs)

    asms = []
    for root, dirs, files in os.walk(ASM_ROOT):
        dirs[:] = [d for d in dirs if d not in ('matchings', 'nonmatchings')]
        asms.extend(
            os.path.join(root, filename)
            for filename in files
            if filename.endswith('.s')
        )

    asms = [src for src in asms
            if f"{output_dir}/{os.path.splitext(src)[0]}.s.o" in linker_script_text]

    add_asm(asms, output_dir, linker_inputs)

    referenced_asm_objects = set(re.findall(
        rf"{re.escape(output_dir)}/{re.escape(ASM_ROOT)}/[^\s();]+\.s\.o",
        linker_script_text,
    ))
    present_asm_objects = {
        f"{output_dir}/{os.path.splitext(src)[0]}.s.o" for src in asms
    }
    for obj_name in sorted(referenced_asm_objects - present_asm_objects):
        ninja.build(obj_name, 'as_empty')
        linker_inputs.append(obj_name)

    asset_objects = set(re.findall(
        rf"{re.escape(output_dir)}/(assets/[^\s();]+\.bin)\.o",
        linker_script_text,
    ))
    for asset in sorted(asset_objects):
        obj_name = f"{output_dir}/{asset}.o"
        ninja.build(
            obj_name,
            'ld_binary',
            inputs=[asset],
            variables={'FLAGS': "", 'FOLDER': ""})
        linker_inputs.append(obj_name)

    ninja.build("objects", 'phony', inputs=linker_inputs)

    # link
    ninja.build(
        f"{output_dir}/main.o",
        'link',
        inputs=linker_inputs,
        variables={'FLAGS': "", 'FOLDER': ""})

    # strip
    ninja.build(
        f"{output_dir}/main.bin",
        'objcopy',
        inputs=[f"{output_dir}/main.o"],
        variables={'FLAGS': "", 'FOLDER': ""})

    # check
    # ninja.build(
    #     f"{output_dir}/check.txt",
    #     'objcopy',
    #     inputs=[f"{output_dir}/main.bin"],
    #     variables={'FLAGS': "", 'FOLDER': ""})

    # ninja.build(
    #     f"{output_dir}/{filename_without_extension}.s",
    #     'copy',
    #     inputs=[f"{output_dir}/{filename_without_extension}.s_"],
    #     variables={'FLAGS': flags, 'FOLDER': folder})


build_35()

ninja.close()

with open(COMPILATION_DATABASE, "w") as compilation_database:
    subprocess.run(
        ["ninja", "-f", BUILD_FILE, "-t", "compdb", "cpp_263"],
        check=True,
        stdout=compilation_database,
    )
