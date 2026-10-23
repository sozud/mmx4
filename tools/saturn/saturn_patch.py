#!/usr/bin/env python3

import argparse
import hashlib
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import os

ROOT = Path(__file__).resolve().parents[2]
RETAIL_SHA256 = 'f2430b86e9e1021d4644bd981afb82c24f6f98d10846a0bf1c8b180584ef313d'
RETAIL_FILES = {'0.BIN': (416232, RETAIL_SHA256),
    'X4LOW.X4': (565247, '2cf9aff3b2683a271d556065b3d526822b1c527b872d64f1c4979bee508df029')}


def read_user(track, lba, size):
    data = bytearray()
    while len(data) < size:
        track.seek(lba * 2352)
        sector = track.read(2352)
        if len(sector) != 2352 or sector[:12] != b'\0' + b'\xff' * 10 + b'\0' or sector[15] != 1:
            raise ValueError(f'Expected a complete MODE1/2352 sector at LBA {lba}')
        data.extend(sector[16:16 + min(2048, size - len(data))])
        lba += 1
    return bytes(data)


def find_root_file(track, filename):
    pvd = read_user(track, 16, 2048)
    if pvd[:7] != b'\x01CD001\x01':
        raise ValueError('Missing ISO9660 primary volume descriptor')
    root = pvd[156:]
    directory = read_user(track, int.from_bytes(root[2:6], 'little'),
                          int.from_bytes(root[10:14], 'little'))
    offset = 0
    while offset < len(directory):
        length = directory[offset]
        if not length:
            offset = (offset // 2048 + 1) * 2048
            continue
        record = directory[offset:offset + length]
        if len(record) < 34 or len(record) != length:
            raise ValueError('Malformed ISO9660 directory record')
        name = record[33:33 + record[32]]
        if name == (filename+';1').encode('ascii'):
            if record[25] & (2 | 128) or record[26] or record[27]:
                raise ValueError(filename+' must be a contiguous, single-extent file')
            return int.from_bytes(record[2:6], 'little'), int.from_bytes(record[10:14], 'little')
        offset += length
    raise ValueError(filename+';1 was not found in the disc root')


def find_executable(track):
    return find_root_file(track, '0.BIN')


def encoder():
    source = ROOT / 'tools/mednafen/src/cdrom'
    helper = Path(__file__).with_name('encode_mode1.cpp')
    output = ROOT / 'build/saturn-tools/encode-mode1'
    inputs = [helper, source / 'lec.cpp', source / 'lec.h']
    if not all(p.is_file() for p in inputs):
        raise ValueError('Initialize tools/mednafen first (git submodule update --init tools/mednafen)')
    if not output.exists() or any(p.stat().st_mtime > output.stat().st_mtime for p in inputs):
        output.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(shlex.split(os.environ.get('CXX', 'g++')) +
                       ['-O2', '-I', str(source), str(helper), str(source / 'lec.cpp'),
                        '-o', str(output)], check=True)
    return output


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('replacement', type=Path, help='Replacement 0.BIN (must keep the retail size)')
    parser.add_argument('--low', type=Path, help='Also replace X4LOW.X4, retaining its original size')
    parser.add_argument('--cue', type=Path, default=ROOT / 'disks/saturn/original/Mega Man X4 (USA).cue')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/saturn-disc',
                        help='New directory for the patched disc; must not already exist')
    args = parser.parse_args()
    cue = args.cue.resolve()
    text = cue.read_text()
    files = re.findall(r'^FILE "([^"]+)" BINARY\s*$', text, re.MULTILINE)
    if len(files) != 3 or len(set(files)) != 3 or not re.search(r'TRACK 01 MODE1/2352', text):
        parser.error('Expected the US three-file Saturn CUE with a MODE1/2352 first track')
    if any(Path(name).name != name or '\\' in name for name in files):
        parser.error('CUE track filenames must be plain filenames in the CUE directory')
    tracks = [cue.parent / name for name in files]
    if not all(p.is_file() for p in tracks):
        parser.error('A CUE track file is missing')
    replacements = [('0.BIN',args.replacement)] + ([('X4LOW.X4',args.low)] if args.low else [])
    patches = []
    with tracks[0].open('rb') as track:
        if read_user(track, 0, 16) != b'SEGA SEGASATURN ':
            parser.error('The disc is not a Sega Saturn image')
        for filename,path in replacements:
            replacement = path.read_bytes(); lba,size = find_root_file(track,filename)
            if size != RETAIL_FILES[filename][0] or len(replacement) != size:
                parser.error(f'{filename} replacement must be exactly {RETAIL_FILES[filename][0]} bytes')
            original = read_user(track,lba,size)
            if hashlib.sha256(original).hexdigest() != RETAIL_FILES[filename][1]:
                parser.error('Source disc '+filename+' is not the supported unmodified US executable')
            track.seek(lba*2352)
            sectors = bytearray(track.read(((size+2047)//2048)*2352))
            for offset in range(0,size,2048):
                chunk=replacement[offset:offset+2048]; start=(offset//2048)*2352+16
                sectors[start:start+len(chunk)] = chunk
            encoded = subprocess.run([str(encoder()),str(lba)],input=sectors,stdout=subprocess.PIPE,check=True).stdout
            if len(encoded)!=len(sectors):raise ValueError('Sector encoder returned an unexpected byte count')
            patches.append((filename,lba,size,replacement,encoded))
    spans=sorted((lba,lba+(size+2047)//2048) for _,lba,size,_,_ in patches)
    if any(b[0]<a[1] for a,b in zip(spans,spans[1:])):raise ValueError('Executable extents overlap')
    args.output.mkdir(parents=True, exist_ok=False)
    for source, name in zip(tracks, files):
        shutil.copyfile(source, args.output / name)
    patched = args.output / files[0]
    with patched.open('r+b') as track:
        for filename,lba,size,replacement,encoded in patches:
            track.seek(lba*2352);track.write(encoded)
            if read_user(track,lba,size)!=replacement:raise OSError('Patched '+filename+' verification failed')
    output_cue = args.output / cue.name
    output_cue.write_text(text)
    for filename,lba,size,_,_ in patches:print(f'Replaced {filename}: LBA {lba}, {size} bytes; MODE1 EDC/ECC regenerated.')
    print(f'Patched disc: {output_cue.resolve()}')


if __name__ == '__main__':
    main()
