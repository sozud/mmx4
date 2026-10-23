#!/usr/bin/env python3
import argparse
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / 'tools/saturn'))
import ninja_syntax
from saturn_sega_libs import shc_to_gas

GCC = ['sh-elf-gcc', '-m2', '-mb']
SDK_CFLAGS = [*GCC, '-Os', '-ffreestanding', '-fno-builtin', '-fno-merge-constants', '-ffunction-sections',
              '-fdata-sections']
LIBC_CFLAGS = [*GCC, '-mrenesas', '-O2', '-ffreestanding', '-fno-builtin', '-fno-tree-loop-distribute-patterns']
STDLIB = '#ifndef NULL\n#define NULL ((void *)0)\n#endif\n#ifndef _SIZE_T\n#define _SIZE_T\ntypedef unsigned long size_t;\n#endif\n'
STRING = STDLIB + ''.join(f'{p};\n' for p in (
    'void *memcpy(void *, const void *, size_t)', 'void *memset(void *, int, size_t)',
    'int memcmp(const void *, const void *, size_t)', 'int strncmp(const char *, const char *, size_t)',
    'int strcmp(const char *, const char *)', 'char *strncpy(char *, const char *, size_t)',
    'char *strcpy(char *, const char *)', 'size_t strlen(const char *)'))
RETAIL_SIZES = {'0.BIN': 416232, 'X4LOW.X4': 565247}
MAIN_BASE, LOW_BASE = 0x06009000, 0x00220000
SCRIPT = Path(__file__).resolve()


def run(command, **kwargs):
    result = subprocess.run(command, capture_output=True, text=True, **kwargs)
    if result.returncode:
        raise SystemExit(' '.join(map(str, command)) + '\n' + result.stdout + result.stderr)
    return result.stdout


def write_if_changed(path, data):
    if not path.exists() or path.read_bytes() != data:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)


def sdk_workdir(output, spec):
    return output / 'sdk' / spec['segalib'].split('/')[0]


def sdk_prepared(sdk, spec, work):
    files = {}
    for library in (spec['library'], 'INCLUDE'):
        for source in sorted((sdk / spec['segalib'] / library).iterdir()):
            if source.suffix.upper() in ('.C', '.H'):
                files[work / source.name.lower()] = source
    return files


def step_prepare_sdk(args):
    manifest = json.loads(args.manifest.read_text())
    for spec in manifest['sdk']['source']:
        work = sdk_workdir(args.output, spec)
        for target, source in sdk_prepared(args.sdk, spec, work).items():
            write_if_changed(target, source.read_bytes().replace(b'\x1a', b''))
        write_if_changed(work / 'stdlib.h', STDLIB.encode())
        write_if_changed(work / 'string.h', STRING.encode())
    args.stamp.write_text('')


def step_shc(args):
    run(['sh-elf-as', '--isa=sh2', '-big', '-o', str(args.output), '-'], input=shc_to_gas(args.source.read_text(errors='ignore')))


def step_extract(args):
    args.output.write_bytes(subprocess.run(['sh-elf-ar', 'p', str(args.archive), args.member], check=True, capture_output=True).stdout)


def free_spans(start, end, taken):
    spans, cursor = [], start
    for a, b in sorted(taken):
        if b <= cursor or a >= end:
            continue
        if a > cursor:
            spans.append((cursor, a))
        cursor = max(cursor, b)
    if cursor < end:
        spans.append((cursor, end))
    return [((a + 3) & ~3, b & ~3) for a, b in spans if (b & ~3) - ((a + 3) & ~3) >= 64]


def section_sizes(obj):
    sizes = {}
    for row in run(['sh-elf-objdump', '-h', str(obj)]).splitlines():
        parts = row.split()
        if len(parts) >= 3 and parts[0].isdigit():
            sizes[parts[1]] = int(parts[2], 16)
    return sizes


def inputs(paths, coff):
    out = []
    for path in paths:
        out += ['-b', 'coff-sh', path, '-b', 'elf32-sh'] if path in coff else [path]
    return out


def step_link(args):
    manifest = json.loads(args.manifest.read_text())
    objects = json.loads(args.objects.read_text())
    game = objects['game']
    sdk_objects = objects['sdk']
    libgcc = objects['libgcc']
    output = args.output
    storage = dict(game)[manifest['storage_object']]
    sizes = section_sizes(storage)
    placements = [(name, int(address, 16), sizes.get(f'.bss.{name}', 0)) for name, address in manifest['storage'].items()]
    taken = [(int(a, 16), int(b, 16)) for a, b in manifest['reserved']] + [(a, a + s) for _, a, s in placements]
    entry = int(manifest['entry_address'], 16)
    high = free_spans(entry + 0x20, int(manifest['program']['main'][1], 16), taken)
    low = free_spans(LOW_BASE, LOW_BASE + RETAIL_SIZES['X4LOW.X4'], taken)
    everything = [obj for _, obj in game] + sdk_objects + [libgcc]
    if any(not source.startswith(('src/main/', 'src/saturn/')) for source, _ in game):
        raise SystemExit('units must be under src/main or src/saturn')
    loaded = '.text* .rodata* .data* .sdata*'
    shared = f'"{output}/obj/src_main_*"({loaded})'
    platform = f'"{output}/obj/src_saturn_*"({loaded}) "{output}/sdk/*"({loaded}) "*{Path(libgcc).name}:"({loaded})'
    lines = ['MEMORY {'] + [f'  H{i} : ORIGIN = 0x{a:08X}, LENGTH = 0x{b - a:X}' for i, (a, b) in enumerate(high)] \
        + [f'  L{i} : ORIGIN = 0x{a:08X}, LENGTH = 0x{b - a:X}' for i, (a, b) in enumerate(low)] + ['}', 'SECTIONS {']
    lines.append(f'  .entry 0x{entry:08X} : {{ KEEP(*(.text.{manifest["entry"]})) }}')
    for name, address, _ in placements:
        lines.append(f'  .st_{name} 0x{address:08X} (NOLOAD) : {{ "{storage}"(.bss.{name}) }}')
    lines.append(f'  .bss (NOLOAD) : SUBALIGN(4) {{ __engine_bss_start = .; *(.bss* COMMON) . = ALIGN(4); __engine_end = .; }} > H{len(high) - 1}')
    lines += [f'  .low{i} : SUBALIGN(4) {{ {shared} }} > L{i}' for i in range(len(low))]
    lines += [f'  .main{i} : SUBALIGN(4) {{ {platform} }} > H{i}' for i in range(len(high))]
    lines += [f'  .spill{i} : SUBALIGN(4) {{ {shared} }} > H{i}' for i in range(len(high))]
    reserved = manifest['reserved'][0]
    lines.append(f'  __retail_bss_start = {reserved[0]}; __retail_bss_end = {reserved[1]};')
    for name, value in manifest['symbols'].items():
        lines.append(f'  _{name} = {value if re.match(r"0x[0-9a-fA-F]+$", value) else "_" + value};')
    lines += ['  /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }', '}']
    script = output / 'image.ld'
    script.write_text('\n'.join(lines) + '\n')
    run(['sh-elf-ld', '-EB', '-m', 'shelf', '--gc-sections', '--no-check-sections', '--enable-non-contiguous-regions',
         '-T', str(script), '-e', '_' + manifest['entry'], '-Map', str(output / 'image.map'), '-o', str(output / 'image.elf'),
         *inputs(everything, set(objects['coff']))])


def step_images(args):
    output = args.output
    main_image, low_image = bytearray(RETAIL_SIZES['0.BIN']), bytearray(RETAIL_SIZES['X4LOW.X4'])
    for row in run(['sh-elf-readelf', '-SW', str(args.elf)]).splitlines():
        m = re.match(r'\s*\[\s*\d+\]\s+(\S+)\s+PROGBITS\s+([0-9a-f]+)\s+[0-9a-f]+\s+([0-9a-f]+)\s+\S+\s+(\S*A\S*)', row)
        if not m or not int(m.group(3), 16):
            continue
        name, address, size = m.group(1), int(m.group(2), 16), int(m.group(3), 16)
        piece = output / 'section.bin'
        run(['sh-elf-objcopy', '-O', 'binary', '-j', name, str(args.elf), str(piece)])
        data = piece.read_bytes()
        if MAIN_BASE <= address and address + size <= MAIN_BASE + len(main_image):
            main_image[address - MAIN_BASE:address - MAIN_BASE + size] = data
        elif LOW_BASE <= address and address + size <= LOW_BASE + len(low_image):
            low_image[address - LOW_BASE:address - LOW_BASE + size] = data
        else:
            raise SystemExit(f'{name} at 0x{address:08X}+0x{size:X} is outside the program images')
        piece.unlink()
    (output / '0.BIN').write_bytes(main_image)
    (output / 'X4LOW.X4').write_bytes(low_image)


def generate(args, output):
    manifest = json.loads(args.manifest.read_text())
    sdk = args.sdk.resolve()
    step = f'{shlex.quote(sys.executable)} {shlex.quote(str(SCRIPT))}'
    includes = ' '.join('-I' + str(ROOT / d) for d in manifest['include'])
    libgcc = run(['sh-elf-gcc', '-m2', '-mb', '-print-libgcc-file-name']).strip()
    with (output / 'build.ninja').open('w') as stream:
        n = ninja_syntax.Writer(stream, width=160)
        n.rule('cc', 'sh-elf-gcc $flags -c $in -o $out -MMD -MF $out.d', depfile='$out.d', deps='gcc', description='cc $in')
        n.rule('sdk_prepare', f'{step} prepare-sdk --sdk $sdk --manifest $manifest --output $root --stamp $out', restat=True,
               description='prepare SEGA SDK sources')
        n.rule('shc', f'{step} shc $in $out', description='shc $in')
        n.rule('extract', f'{step} extract $archive $member $out', description='extract $member')
        n.rule('link', f'{step} link --manifest $manifest --objects $objects --output $root', description='link $out')
        n.rule('images', f'{step} images $in $root', description='images')
        n.rule('disc', f'rm -rf $disc && {shlex.quote(sys.executable)} {shlex.quote(str(ROOT / "tools/saturn/saturn_patch.py"))} $main --low $low '
               f'--cue $cue --output $disc', description='disc')
        implicit = [str(SCRIPT), str(args.manifest.resolve())]
        game = []
        objects_dir = output / 'obj'
        for unit in manifest['units']:
            source = ROOT / unit['source']
            target = objects_dir / (unit['source'].replace('/', '_') + '.o')
            flags = unit.get('flags') or manifest['cflags'] + unit.get('extra_flags', [])
            flags = [f for f in flags if f not in ('-m2', '-mb')] + ['-m2', '-mb'] + includes.split()
            n.build(str(target), 'cc', str(source), variables={'flags': ' '.join(map(shlex.quote, flags))})
            game.append((unit['source'], str(target)))
        stamp = output / 'sdk' / 'prepared.stamp'
        prepared = []
        for spec in manifest['sdk']['source']:
            work = sdk_workdir(output, spec)
            prepared += [str(p) for p in sdk_prepared(sdk, spec, work)] + [str(work / 'stdlib.h'), str(work / 'string.h')]
        prepared = list(dict.fromkeys(prepared))
        n.build(str(stamp), 'sdk_prepare', implicit=implicit, implicit_outputs=prepared,
                variables={'sdk': shlex.quote(str(sdk)), 'manifest': shlex.quote(str(args.manifest.resolve())), 'root': shlex.quote(str(output))})
        sdk_objects = []
        for spec in manifest['sdk']['source']:
            work = sdk_workdir(output, spec)
            for unit in spec['units']:
                target = work / f'sdk_{unit}.o'
                n.build(str(target), 'cc', str(work / f'{unit}.c'), order_only=[str(stamp)],
                        variables={'flags': ' '.join(SDK_CFLAGS[1:] + ['-I' + str(work)])})
                sdk_objects.append(str(target))
        for spec in manifest['sdk']['source']:
            work = sdk_workdir(output, spec)
            for unit in spec['asm_units']:
                source = next(p for p in (sdk / spec['segalib'] / spec['library']).iterdir() if p.name.lower() == f'{unit}.src')
                target = work / f'sdk_{unit}.o'
                n.build(str(target), 'shc', str(source), implicit=[str(SCRIPT), str(ROOT / 'tools/saturn/saturn_sega_libs.py')])
                sdk_objects.append(str(target))
        coff = []
        for spec in manifest['sdk']['prebuilt']:
            archive = sdk / spec['segalib'] / 'LIB' / spec['archive']
            for unit in spec['units']:
                target = output / 'sdk' / f'sdk_{unit}.o'
                n.build(str(target), 'extract', implicit=[str(archive)],
                        variables={'archive': shlex.quote(str(archive)), 'member': f'{unit}.o'})
                sdk_objects.append(str(target))
                coff.append(str(target))
        libc = output / 'sdk' / 'sdk_libc.o'
        n.build(str(libc), 'cc', str(ROOT / manifest['sdk_libc']), variables={'flags': ' '.join(LIBC_CFLAGS[1:])})
        sdk_objects.append(str(libc))
        objects = output / 'objects.json'
        write_if_changed(objects, (json.dumps(dict(game=game, sdk=sdk_objects, coff=coff, libgcc=libgcc), indent=1) + '\n').encode())
        elf = output / 'image.elf'
        n.build([str(elf), str(output / 'image.ld'), str(output / 'image.map')], 'link',
                [t for _, t in game] + sdk_objects, implicit=implicit + [str(objects), libgcc],
                variables={'manifest': shlex.quote(str(args.manifest.resolve())), 'objects': shlex.quote(str(objects)),
                           'root': shlex.quote(str(output))})
        images = [str(output / '0.BIN'), str(output / 'X4LOW.X4')]
        n.build(images, 'images', str(elf), implicit=[str(SCRIPT)], variables={'root': shlex.quote(str(output))})
        defaults = images
        if not args.no_disc:
            disc = output / 'disc'
            cue = disc / 'Mega Man X4 (USA).cue'
            n.build(str(cue), 'disc', images, implicit=[str(args.cue.resolve()), str(ROOT / 'tools/saturn/saturn_patch.py')],
                    variables={'main': shlex.quote(images[0]), 'low': shlex.quote(images[1]),
                               'cue': shlex.quote(str(args.cue.resolve())), 'disc': shlex.quote(str(disc))})
            defaults = [str(cue)]
        n.default([ninja_syntax.escape_path(d) for d in defaults])
    return elf


def main():
    steps = {'prepare-sdk': step_prepare_sdk, 'shc': step_shc, 'extract': step_extract, 'link': step_link, 'images': step_images}
    if len(sys.argv) > 1 and sys.argv[1] in steps:
        parser = argparse.ArgumentParser(prog=f'{Path(sys.argv[0]).name} {sys.argv[1]}')
        name = sys.argv.pop(1)
        if name == 'prepare-sdk':
            parser.add_argument('--sdk', type=Path, required=True)
            parser.add_argument('--manifest', type=Path, required=True)
            parser.add_argument('--output', type=Path, required=True)
            parser.add_argument('--stamp', type=Path, required=True)
        elif name == 'shc':
            parser.add_argument('source', type=Path)
            parser.add_argument('output', type=Path)
        elif name == 'extract':
            parser.add_argument('archive', type=Path)
            parser.add_argument('member')
            parser.add_argument('output', type=Path)
        elif name == 'link':
            parser.add_argument('--manifest', type=Path, required=True)
            parser.add_argument('--objects', type=Path, required=True)
            parser.add_argument('--output', type=Path, required=True)
        elif name == 'images':
            parser.add_argument('elf', type=Path)
            parser.add_argument('output', type=Path)
        steps[name](parser.parse_args())
        return
    parser = argparse.ArgumentParser()
    parser.add_argument('--sdk', type=Path, default=ROOT / 'tools/saturn/sdk', help='SEGA SDK subset (the tools/saturn/sdk submodule)')
    parser.add_argument('--cue', type=Path, help='original US disc CUE; its data files go on the built disc (not needed with --no-disc)')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--manifest', type=Path, default=ROOT / 'config/saturn/native.json')
    parser.add_argument('--jobs', type=int, default=os.cpu_count())
    parser.add_argument('--no-disc', action='store_true', help='stop after 0.BIN and X4LOW.X4')
    args = parser.parse_args()
    if not args.no_disc and not args.cue:
        parser.error('--cue is needed to build the disc (or pass --no-disc)')
    output = args.output.resolve()
    if any(c in str(output) for c in '*?[]'):
        parser.error('--output must not contain * ? [ or ] (the linker script matches objects by path pattern)')
    (output / 'obj').mkdir(parents=True, exist_ok=True)
    elf = generate(args, output)
    result = subprocess.run(['ninja', '-f', str(output / 'build.ninja'), '-j', str(args.jobs)])
    if result.returncode:
        raise SystemExit(result.returncode)
    if args.no_disc:
        print(f'{output / "0.BIN"}, {output / "X4LOW.X4"}')
        return
    cue = output / 'disc' / 'Mega Man X4 (USA).cue'
    (output / 'image.json').write_text(json.dumps(dict(mode='native-program-image', elf=str(elf), cue=str(cue)), indent=1) + '\n')
    print(f'{output / "0.BIN"}, {output / "X4LOW.X4"}, disc {cue}')


if __name__ == '__main__':
    main()
