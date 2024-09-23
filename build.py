import os
import subprocess
import ninja_syntax

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

        cpp_flags = f"-undef -D__GNUC__=2 {flags} -v -D__OPTIMIZE__ -I./src/snd -I./include -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C"

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


ninja = ninja_syntax.Writer(open("build.ninja", "w"))

ninja.rule('compile',
           command='sh dosemu_wrapper.sh $in $out $FLAGS $FOLDER',
           description='Building $out from $in')

ninja.rule('cpp_263',
           command=f'cpp $CPP_FLAGS $in $out',
           description='Running preprocessor on $out from $in')

ninja.rule('cc1_263',
           command='./bin/cc1 -msoft-float -O2 -g0 -G0 -funsigned-char $in -o $out',
           description='Running cc1 on $out from $in')

ninja.rule('aspsx_263',
           command='python3 tools/maspsx/maspsx.py --aspsx-version=2.56 $in > $out',
           description='Running aspsx on $out from $in')

ninja.rule('as',
           'mipsel-linux-gnu-as -no-pad-sections -I./src/main $in -o $out')

ninja.rule('link',
           'mipsel-linux-gnu-ld -Map=build/us/main.map -T main.ld config/undefined_funcs_auto.us.main.txt config/undefined_syms_auto.us.main.txt $in -o $out')

ninja.rule('objcopy',
           'mipsel-linux-gnu-objcopy $in -O binary $out')

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
    srcs.extend([os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))])

    linker_inputs = []
    output_dir = "build/us"
    add_lib_263(srcs, output_dir, linker_inputs)

    asms = []
    directory = 'asm/us/main/data'
    asms.extend([os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))])

    directory = 'asm/us/main'
    asms.extend([os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))])

    for root, dirs, files in os.walk('asm/us/main/psxsdk'):
        asms.extend([os.path.join(root, f) for f in files if os.path.isfile(os.path.join(root, f))])

    add_asm(asms, output_dir, linker_inputs)

    assets = []
    # directory = 'assets/main/'
    # assets.extend([os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))])

    for asset in assets:
        # assets
        ninja.build(
            f"build/us/{asset}.o",
            'ld_binary',
            inputs=[asset],
            variables={'FLAGS': "", 'FOLDER': ""})

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
