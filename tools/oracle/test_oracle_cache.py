#!/usr/bin/env python3
import argparse
import io
import json
import tarfile
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path
import oracle_cache as cache
import replay_cache


class CacheTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.stamp = {'schema_version': cache.SCHEMA_VERSION, 'replay_sha256': 'movie-a'}
        for name in ('a', 'b'):
            directory = self.root/name
            directory.mkdir()
            for log in cache.REPLAY_LOGS:
                (directory/log).write_text('frame\tvalue\n0\tvalue\n')
            (directory/'run.log').write_text('ok\n')
            self.assertTrue(cache.seal(directory, self.stamp, frames=1))

    def tearDown(self): self.temp.cleanup()

    def test_partial_suite_keeps_completed_movie(self):
        (self.root/'b/objects.tsv').unlink()
        self.assertTrue(cache.valid(self.root/'a', self.stamp))
        self.assertFalse(cache.valid(self.root/'b', self.stamp))

    def test_invalid_completion_document_only_invalidates_that_movie(self):
        (self.root/'a/complete.json').write_text('[]')
        self.assertFalse(cache.valid(self.root/'a', self.stamp))
        self.assertTrue(cache.valid(self.root/'b', self.stamp))

    def test_modified_movie_and_schema_invalidate(self):
        self.assertFalse(cache.valid(self.root/'a', {**self.stamp, 'replay_sha256': 'movie-b'}))
        self.assertFalse(cache.valid(self.root/'a', {**self.stamp, 'schema_version': cache.SCHEMA_VERSION+1}))

    def test_corruption_and_changed_columns_are_rejected(self):
        (self.root/'a/objects.tsv').write_text('frame\tother\n0\tvalue\n')
        self.assertFalse(cache.valid(self.root/'a', self.stamp))
        self.assertTrue(cache.valid(self.root/'b', self.stamp))

    def test_incomplete_capture_never_gets_marker(self):
        directory = self.root/'incomplete'; directory.mkdir()
        for log in cache.REPLAY_LOGS:
            (directory/log).write_text('frame\tvalue\n0\tvalue\n')
        self.assertFalse(cache.seal(directory, self.stamp, frames=2))
        self.assertFalse((directory/'complete.json').exists())

    def test_binary_rebuild_does_not_discard_same_oracle_recipe(self):
        root = self.root/'source'; source = root/'tools/mednafen/src'
        (source/'drivers_libxxx').mkdir(parents=True)
        (source/'mednafen.cpp').write_text('stable emulation')
        (source/'drivers_libxxx/main.cpp').write_text('stable logging')
        binary = root/'mednafen'; binary.write_bytes(b'build with debug path A')
        with patch.object(cache, 'ROOT', root):
            cache.oracle_recipe.cache_clear()
            first = cache.oracle_recipe(str(binary))
            binary.write_bytes(b'build with debug path B')
            cache.oracle_recipe.cache_clear()
            self.assertEqual(first, cache.oracle_recipe(str(binary)))
            (source/'drivers_libxxx/main.cpp').write_text('changed object schema')
            cache.oracle_recipe.cache_clear()
            self.assertNotEqual(first, cache.oracle_recipe(str(binary)))
        cache.oracle_recipe.cache_clear()

    def test_pack_is_deterministic_and_round_trips(self):
        cache.pack(self.root/'a', self.root/'one.tar.gz')
        (self.root/'a/frames.tsv').touch()
        cache.pack(self.root/'a', self.root/'two.tar.gz')
        self.assertEqual((self.root/'one.tar.gz').read_bytes(), (self.root/'two.tar.gz').read_bytes())
        cache.unpack(self.root/'one.tar.gz', self.root/'restored')
        self.assertTrue(cache.valid(self.root/'restored', self.stamp))

    def test_unpack_rejects_unexpected_members(self):
        with tarfile.open(self.root/'bad.tar.gz', 'w:gz') as tar:
            for name in (*cache.ARCHIVE_FILES, '../escape'):
                info = tarfile.TarInfo(name); info.size = 1
                tar.addfile(info, io.BytesIO(b'x'))
        with self.assertRaises(ValueError):
            cache.unpack(self.root/'bad.tar.gz', self.root/'restored')
        self.assertFalse((self.root/'escape').exists())

    def test_legacy_marker_upgrades_only_for_same_binary(self):
        stamp = {**self.stamp, 'psx_frames': 0}
        legacy = {'replay_sha256': 'movie-a', 'psx_frames': 0, 'mednafen_sha256': 'binary-a'}
        (self.root/'a/complete.json').write_text(json.dumps(legacy))
        self.assertFalse(cache.upgrade_legacy(self.root/'a', stamp, 'binary-b', 1))
        self.assertTrue(cache.upgrade_legacy(self.root/'a', stamp, 'binary-a', 1))
        self.assertTrue(cache.valid(self.root/'a', stamp))


class ReleaseFlowTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        for name, data in (('mednafen', b'binary'), ('disc.bin', b'disc'), ('bios', b'bios')):
            (self.root/name).write_bytes(data)
        (self.root/'disc.cue').write_text('FILE "disc.bin" BINARY\n')
        manifest = []
        for name in ('a', 'b'):
            replay = self.root/f'{name}.mmx4r'
            replay.write_bytes(b'MMX4RPL2' + bytes(8) + name.encode() * 2)
            manifest.append(f'{replay} digest state')
        (self.root/'manifest.txt').write_text('\n'.join(manifest) + '\n')
        self.patch = patch.object(cache, 'ROOT', self.root)
        self.patch.start()
        cache.oracle_recipe.cache_clear(); cache.disc_digest.cache_clear()

    def tearDown(self):
        self.patch.stop()
        cache.oracle_recipe.cache_clear(); cache.disc_digest.cache_clear()
        self.temp.cleanup()

    def args(self, cache_dir, prune=False):
        return argparse.Namespace(manifest=self.root/'manifest.txt', cache=self.root/cache_dir,
                                  mednafen=self.root/'mednafen', cue=self.root/'disc.cue',
                                  bios=self.root/'bios', psx_frames=0, prune=prune)

    def capture(self, cache_dir):
        for replay, directory, stamp, frames in replay_cache.entries(self.args(cache_dir)):
            directory.mkdir(parents=True)
            for log in cache.REPLAY_LOGS:
                (directory/log).write_text('frame\tvalue\n0\tvalue\n')
            (directory/'run.log').write_text('ok\n')
            self.assertTrue(cache.seal(directory, stamp, frames=frames))

    def test_publish_fetch_and_prune(self):
        store = replay_cache.DirectoryStore(self.root/'release')
        self.capture('ci-1')
        (self.root/'release').mkdir()
        (self.root/'release/stale.tar.gz').write_bytes(b'old')
        replay_cache.publish(self.args('ci-1', prune=True), store)
        self.assertEqual(len(store.names()), 2)
        replay_cache.fetch(self.args('ci-2'), store)
        for replay, directory, stamp, frames in replay_cache.entries(self.args('ci-2')):
            self.assertTrue(cache.valid(directory, stamp))

    def test_corrupt_asset_is_a_miss(self):
        store = replay_cache.DirectoryStore(self.root/'release')
        self.capture('ci-1')
        replay_cache.publish(self.args('ci-1'), store)
        for name in store.names():
            (self.root/'release'/name).write_bytes(b'garbage')
        replay_cache.fetch(self.args('ci-2'), store)
        self.assertFalse(any((self.root/'ci-2').glob('*/complete.json')))


if __name__ == '__main__': unittest.main()
