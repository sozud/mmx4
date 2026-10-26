#!/usr/bin/env python3

import argparse
import shutil
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path

import oracle_cache

SUFFIX = ".tar.gz"


class ReleaseStore:
    def __init__(self, repo, tag):
        self.repo, self.tag = repo, tag

    def gh(self, *args, check=True):
        return subprocess.run(("gh", *args, "--repo", self.repo), check=check,
                              capture_output=True, text=True)

    def names(self):
        result = self.gh("release", "view", self.tag, "--json", "assets",
                         "--jq", ".assets[].name", check=False)
        if result.returncode != 0:
            print(f"replay cache: release {self.repo}@{self.tag} unavailable: "
                  f"{result.stderr.strip()}", file=sys.stderr)
            return set()
        return set(result.stdout.split())

    def download(self, name, destination):
        self.gh("release", "download", self.tag, "--pattern", name,
                "--output", str(destination), "--clobber")

    def ensure(self):
        if self.gh("release", "view", self.tag, check=False).returncode != 0:
            self.gh("release", "create", self.tag, "--title", "Mednafen replay cache",
                    "--notes", "Per-movie Mednafen oracle captures, named by input stamp.")

    def upload(self, path):
        self.gh("release", "upload", self.tag, str(path), "--clobber")

    def delete(self, name):
        self.gh("release", "delete-asset", self.tag, name, "--yes")


class DirectoryStore:
    def __init__(self, root):
        self.root = Path(root)

    def names(self):
        return {p.name for p in self.root.glob("*")} if self.root.is_dir() else set()

    def download(self, name, destination):
        shutil.copyfile(self.root / name, destination)

    def ensure(self):
        self.root.mkdir(parents=True, exist_ok=True)

    def upload(self, path):
        shutil.copyfile(path, self.root / Path(path).name)

    def delete(self, name):
        (self.root / name).unlink()


def entries(args):
    for line in args.manifest.read_text().splitlines():
        if not line.strip():
            continue
        replay = Path(line.split()[0])
        replay_sha = oracle_cache.digest(replay)
        with replay.open("rb") as handle:
            sample_size = 4 if handle.read(8) == b"MMX4RPL3" else 2
        frames = (replay.stat().st_size - 16) // sample_size
        stamp = oracle_cache.inputs(replay_sha, args.mednafen, args.cue, args.bios,
                                    args.psx_frames)
        yield replay, args.cache / replay_sha, stamp, frames


def fetch(args, store):
    available = store.names()
    restored = present = missing = 0
    with tempfile.TemporaryDirectory() as temporary:
        for replay, directory, stamp, frames in entries(args):
            name = oracle_cache.stamp_id(stamp) + SUFFIX
            if oracle_cache.valid(directory, stamp):
                present += 1
            elif name in available:
                archive = Path(temporary) / name
                if directory.exists():
                    shutil.rmtree(directory)
                try:
                    store.download(name, archive)
                    oracle_cache.unpack(archive, directory)
                except (OSError, ValueError, tarfile.TarError,
                        subprocess.CalledProcessError) as error:
                    print(f"replay cache: unable to restore {name}: {error}")
                if oracle_cache.valid(directory, stamp):
                    restored += 1
                    continue
                print(f"replay cache: discarding invalid capture {name} for {replay}")
                shutil.rmtree(directory, ignore_errors=True)
                missing += 1
            else:
                missing += 1
                print(f"replay cache: no capture for {replay}")
    print(f"replay cache: {restored} restored, {present} already present, {missing} missing")


def publish(args, store):
    store.ensure()
    available = store.names()
    wanted = set()
    uploaded = 0
    mednafen_sha = oracle_cache.digest(args.mednafen)
    with tempfile.TemporaryDirectory() as temporary:
        for replay, directory, stamp, frames in entries(args):
            name = oracle_cache.stamp_id(stamp) + SUFFIX
            wanted.add(name)
            if name in available:
                continue
            if not (oracle_cache.valid(directory, stamp) or
                    oracle_cache.upgrade_legacy(directory, stamp, mednafen_sha, frames)):
                print(f"replay cache: no complete capture for {replay}")
                continue
            archive = Path(temporary) / name
            oracle_cache.pack(directory, archive)
            store.upload(archive)
            uploaded += 1
    pruned = 0
    if args.prune:
        for name in sorted(available - wanted):
            if name.endswith(SUFFIX):
                store.delete(name)
                pruned += 1
    print(f"replay cache: {uploaded} uploaded, {len(wanted & available)} already published, "
          f"{pruned} pruned")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("action", choices=("fetch", "publish"))
    parser.add_argument("--manifest", type=Path, default=Path("tools/oracle/replay_ci_manifest.txt"))
    parser.add_argument("--cache", type=Path, default=Path("replay-psx"))
    parser.add_argument("--mednafen", type=Path, default=Path("tools/mednafen-build/src/mednafen"))
    parser.add_argument("--cue", type=Path, default=Path("disks/mmx4.us.cue"))
    parser.add_argument("--bios", type=Path, default=Path("tools/SCPH1001.BIN"))
    parser.add_argument("--psx-frames", type=int, default=0)
    parser.add_argument("--repo", default="sozud/mmx4-info")
    parser.add_argument("--tag", default="replay-cache")
    parser.add_argument("--store", type=Path)
    parser.add_argument("--prune", action="store_true")
    args = parser.parse_args()
    store = DirectoryStore(args.store) if args.store else ReleaseStore(args.repo, args.tag)
    (fetch if args.action == "fetch" else publish)(args, store)


if __name__ == "__main__":
    main()
