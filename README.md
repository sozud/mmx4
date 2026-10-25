# Mega Man X4

A matching decompilation of *Mega Man X4* (PlayStation, 1997).

[![US](https://decomp.dev/sozud/mmx4/us.svg?mode=shield&category=game&label=US)](https://decomp.dev/sozud/mmx4)
[![JP](https://decomp.dev/sozud/mmx4/jp.svg?mode=shield&category=game&label=JP)](https://decomp.dev/sozud/mmx4)
[![EU](https://decomp.dev/sozud/mmx4/eu.svg?mode=shield&category=game&label=EU)](https://decomp.dev/sozud/mmx4)
[![Build](https://github.com/sozud/mmx4/actions/workflows/build.yaml/badge.svg)](https://github.com/sozud/mmx4/actions/workflows/build.yaml)

The same C source builds:

- byte-matching PlayStation executables for the US, JP and EU releases
- a native PC port for Linux (US and JP)
- a non-matching Sega Saturn build

This repository does not contain any game assets. You need your own copy of the game.

## Versions

| Version   | Executable            | Compiler                  | Checksums      |
|-----------|-----------------------|---------------------------|----------------|
| US        | `SLUS_005.61`         | GCC 2.7.2                 | `check.us.txt` |
| JP        | `SLPS_009.02`         | GCC 2.7.2                 | `check.jp.txt` |
| EU        | `SLES_011.76`         | GCC 2.8.1                 | `check.eu.txt` |
| Saturn US | `0.BIN`, `X4LOW.X4`   | `sh-elf-gcc` (retail: SHC) | non-matching   |

## Building the PlayStation executables

Install the dependencies:

```
sudo apt-get update
sudo apt-get install binutils-mipsel-linux-gnu gcc-mipsel-linux-gnu ninja-build

pip install -r requirements.txt

git submodule update --init --recursive
sh compiler.sh
```

Copy the executable from your disc into `disks/<version>/`, for example `disks/us/SLUS_005.61`. Then split and build:

```
splat split config/SLUS_005.61.splat.yaml
sh build.sh
```

For the other versions, split with `config/SLPS_009.02.splat.yaml` or `config/SLES_011.76.splat.yaml` and run `VERSION=jp sh build.sh` or `VERSION=eu sh build.sh`. `build.sh` checks the result against `check.<version>.txt`.

## Building the PC port

```
sudo apt-get install build-essential cmake ninja-build \
    libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
    libxfixes-dev libxi-dev libxss-dev libxtst-dev

cmake -S . -B build-linux -G Ninja -DCMAKE_BUILD_TYPE=Release -DMMX4_PC_VERSION=us
cmake --build build-linux --parallel
```

Use `-DMMX4_PC_VERSION=jp` for the Japanese version. The port reads the game data from a disc image, `disks/mmx4.us.cue` (or `disks/mmx4.jp.cue`) by default. Pass `--cue` or set `MMX4_CUE` to use another path:

```
build-linux/mmx4_pc --cue path/to/game.cue
```

## Building for Saturn

The Saturn build uses GCC (`sh-elf-gcc`) instead of Hitachi's SHC compiler. We don't have the exact SHC version the original was built with, so it doesn't match byte for byte.

```
sudo apt-get install gcc-sh-elf binutils-sh-elf ninja-build
git submodule update --init tools/saturn/sdk
python3 tools/saturn/saturn_native_build.py --output build/saturn-native --jobs $(nproc) --no-disc
```

## Contributing

See the [Getting Started](https://github.com/sozud/mmx4/wiki/Getting-Started) page on the wiki.

## Project layout

| Path          | Contents                                  |
|---------------|-------------------------------------------|
| `src/main`    | decompiled game code                      |
| `src/pc`      | PC port platform layer                    |
| `src/saturn`  | Saturn platform layer                     |
| `include`     | shared headers                            |
| `config`      | splat configs, symbol lists               |
| `tests`       | unit tests                                |
| `tools`       | build, matching and testing tools         |
