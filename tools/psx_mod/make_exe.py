#!/usr/bin/env python3

import argparse
import struct
import subprocess
import sys
import tempfile

HEADER = 0x800
SECTOR = 0x800
LOAD_ADDRESS = 0x80010000
STACK = 0x801FFFF0
LICENSE_OFFSET = 0x4C
LICENSE = {
    "us": b"Sony Computer Entertainment Inc. for North America area",
    "jp": b"Sony Computer Entertainment Inc. for Japan area",
    "eu": b"Sony Computer Entertainment Inc. for Europe area",
}


def entry_point(elf):
    output = subprocess.run(("mipsel-linux-gnu-readelf", "-h", elf), check=True,
                            capture_output=True, text=True).stdout
    for line in output.splitlines():
        if "Entry point address" in line:
            return int(line.split()[-1], 16)
    raise SystemExit(f"{elf}: no entry point")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("elf")
    parser.add_argument("output")
    parser.add_argument("--version", required=True, choices=sorted(LICENSE))
    args = parser.parse_args()

    with tempfile.NamedTemporaryFile() as raw:
        subprocess.run(("mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".main", args.elf, raw.name),
                       check=True)
        body = open(raw.name, "rb").read()
    body += bytes(-len(body) % SECTOR)

    header = bytearray(HEADER)
    header[:8] = b"PS-X EXE"
    struct.pack_into("<IIIIIIIIII", header, 0x10,
                     entry_point(args.elf), 0, LOAD_ADDRESS, len(body), 0, 0, 0, 0, STACK, 0)
    license = LICENSE[args.version]
    header[LICENSE_OFFSET:LICENSE_OFFSET + len(license)] = license

    with open(args.output, "wb") as handle:
        handle.write(header + body)
    return 0


if __name__ == "__main__":
    sys.exit(main())
