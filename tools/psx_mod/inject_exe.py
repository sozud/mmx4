#!/usr/bin/env python3

import argparse
import struct
import sys

RAW = 2352
DATA = 2048
USER = 24


def build_tables():
    forward = [0] * 256
    backward = [0] * 256
    edc = [0] * 256
    for i in range(256):
        j = ((i << 1) ^ (0x11D if i & 0x80 else 0)) & 0xFF
        forward[i] = j
        backward[i ^ j] = i
        value = i
        for _ in range(8):
            value = (value >> 1) ^ (0xD8018001 if value & 1 else 0)
        edc[i] = value
    return forward, backward, edc


FORWARD, BACKWARD, EDC = build_tables()


def compute_edc(data):
    value = 0
    for byte in data:
        value = (value >> 8) ^ EDC[(value ^ byte) & 0xFF]
    return value


def ecc_block(sector, major_count, minor_count, major_mult, minor_inc, dest):
    source = sector[0xC:]
    size = major_count * minor_count
    for major in range(major_count):
        index = (major >> 1) * major_mult + (major & 1)
        a = b = 0
        for _ in range(minor_count):
            value = source[index]
            index += minor_inc
            if index >= size:
                index -= size
            a ^= value
            b ^= value
            a = FORWARD[a]
        a = BACKWARD[FORWARD[a] ^ b]
        sector[dest + major] = a
        sector[dest + major + major_count] = a ^ b


def encode_form1(sector):
    struct.pack_into("<I", sector, 0x818, compute_edc(sector[0x10:0x818]))
    header = bytes(sector[0xC:0x10])
    sector[0xC:0x10] = bytes(4)
    ecc_block(sector, 86, 24, 2, 86, 0x81C)
    ecc_block(sector, 52, 43, 86, 88, 0x8C8)
    sector[0xC:0x10] = header


def read_sector(image, lba):
    image.seek(lba * RAW)
    return bytearray(image.read(RAW))


def find_file(image, name):
    pvd = read_sector(image, 16)[USER:USER + DATA]
    root_extent, root_size = struct.unpack_from("<I", pvd, 156 + 2)[0], struct.unpack_from("<I", pvd, 156 + 10)[0]
    wanted = name.upper().encode() + b";1"
    for index in range((root_size + DATA - 1) // DATA):
        lba = root_extent + index
        data = read_sector(image, lba)[USER:USER + DATA]
        offset = 0
        while offset < DATA and data[offset]:
            length = data[offset]
            name_length = data[offset + 32]
            if data[offset + 33:offset + 33 + name_length] == wanted:
                extent, size = struct.unpack_from("<I", data, offset + 2)[0], struct.unpack_from("<I", data, offset + 10)[0]
                return lba, offset, extent, size
            offset += length
    raise SystemExit(f"{name} is not in the root directory")


def write_sector(image, lba, sector):
    if sector[0x12] & 0x20:
        raise SystemExit(f"sector {lba} is form 2, refusing to rewrite it")
    encode_form1(sector)
    image.seek(lba * RAW)
    image.write(sector)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("image", help="raw .bin image, modified in place")
    parser.add_argument("exe", help="new executable")
    parser.add_argument("--name", default="SLUS_005.61")
    parser.add_argument("--self-test", action="store_true",
                        help="re-encode the existing file's sectors and check they come out unchanged")
    args = parser.parse_args()

    with open(args.exe, "rb") as handle:
        exe = handle.read()
    with open(args.image, "r+b") as image:
        directory_lba, record, extent, size = find_file(image, args.name)
        sectors = (size + DATA - 1) // DATA
        if args.self_test:
            for lba in range(extent, extent + sectors):
                original = read_sector(image, lba)
                sector = bytearray(original)
                encode_form1(sector)
                if sector != original:
                    raise SystemExit(f"EDC/ECC self-test failed at sector {lba}")
            print(f"self-test passed on {sectors} sectors")
            return 0
        if len(exe) > sectors * DATA:
            raise SystemExit(f"{args.exe} is {len(exe):#x} bytes; only {sectors * DATA:#x} fit in place")
        padded = exe + bytes(sectors * DATA - len(exe))
        for index in range(sectors):
            sector = read_sector(image, extent + index)
            sector[USER:USER + DATA] = padded[index * DATA:(index + 1) * DATA]
            write_sector(image, extent + index, sector)
        directory = read_sector(image, directory_lba)
        struct.pack_into("<I", directory, USER + record + 10, len(exe))
        struct.pack_into(">I", directory, USER + record + 14, len(exe))
        write_sector(image, directory_lba, directory)
    print(f"wrote {len(exe):#x} bytes at LBA {extent}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
