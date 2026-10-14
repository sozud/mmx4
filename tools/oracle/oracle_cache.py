import gzip
import hashlib
import io
import json
import os
import tarfile
from pathlib import Path
from functools import lru_cache

ROOT = Path(__file__).resolve().parents[2]
SCHEMA_VERSION = 1
REPLAY_LOGS = ('frames.tsv', 'objects.tsv', 'extensions.tsv', 'state.tsv')
ARCHIVE_FILES = (*REPLAY_LOGS, 'run.log', 'complete.json')


def digest(path):
    value = hashlib.sha256()
    with Path(path).open('rb') as handle:
        for chunk in iter(lambda: handle.read(1 << 20), b''): value.update(chunk)
    return value.hexdigest()


@lru_cache(maxsize=None)
def oracle_recipe(binary):
    source = ROOT/'tools/mednafen/src'
    files = [source/'mednafen.cpp', source/'drivers_libxxx/main.cpp']
    for directory in ('psx', 'cdrom'):
        files += [p for p in (source/directory).rglob('*') if p.suffix in ('.h', '.cpp', '.inc')]
    if not files or any(not p.is_file() for p in files):
        return {'binary_sha256': digest(binary)}
    value = hashlib.sha256()
    for path in sorted(files):
        value.update(str(path.relative_to(source)).encode()); value.update(b'\0')
        value.update(path.read_bytes()); value.update(b'\0')
    return {'psx_source_sha256': value.hexdigest()}


@lru_cache(maxsize=None)
def disc_digest(cue):
    override = os.environ.get('MMX4_ORACLE_DISC_SHA256')
    if override: return [override]
    import shlex
    cue = Path(cue)
    files = []
    for line in cue.read_text().splitlines():
        fields = shlex.split(line)
        if fields and fields[0].upper() == 'FILE': files.append(cue.parent/fields[1])
    return [digest(p) for p in files]


def inputs(replay_sha, binary, cue, bios, frames=0):
    stamp = {'schema_version': SCHEMA_VERSION, 'replay_sha256': replay_sha,
             'oracle': oracle_recipe(str(Path(binary).resolve())),
             'disc': disc_digest(str(Path(cue).resolve())), 'cue_sha256': digest(cue),
             'bios_sha256': digest(bios), 'psx_frames': frames}
    return stamp


def seal(directory, stamp, logs=REPLAY_LOGS, frames=None):
    directory = Path(directory)
    outputs = {}
    for name in logs:
        path = directory/name
        if not path.is_file(): return False
        with path.open('rb') as handle:
            header = handle.readline().decode('ascii').strip()
            if not header.startswith('frame\t'): return False
            handle.seek(-1, 2)
            if handle.read(1) != b'\n': return False
        outputs[name] = {'header': header, 'size': path.stat().st_size, 'sha256': digest(path)}
    if frames is not None:
        with (directory/'frames.tsv').open() as handle:
            header = next(handle).strip().split('\t')
            observed = 0
            for line in handle:
                row = line.rstrip('\n').split('\t')
                if len(row) != len(header) or int(row[0]) != observed: return False
                observed += 1
            if observed != frames: return False
    document = {'inputs': stamp, 'outputs': outputs, 'frames': frames}
    temporary = directory/'complete.json.tmp'
    temporary.write_text(json.dumps(document, indent=2)+'\n')
    temporary.replace(directory/'complete.json')
    return True


def valid(directory, stamp, logs=REPLAY_LOGS):
    directory = Path(directory)
    try:
        doc = json.loads((directory/'complete.json').read_text())
        if not isinstance(doc, dict): return False
        if doc.get('inputs') != stamp: return False
        for name in logs:
            record = doc['outputs'][name]; path = directory/name
            if path.stat().st_size != record['size'] or digest(path) != record['sha256']: return False
            with path.open() as handle:
                if handle.readline().strip() != record['header']: return False
        return True
    except (OSError, ValueError, KeyError, TypeError):
        return False


def upgrade_legacy(directory, stamp, mednafen_sha256, frames):
    legacy = {'replay_sha256': stamp['replay_sha256'], 'psx_frames': stamp['psx_frames'],
              'mednafen_sha256': mednafen_sha256}
    try:
        if json.loads((Path(directory)/'complete.json').read_text()) != legacy: return False
    except (OSError, ValueError):
        return False
    return seal(directory, stamp, frames=frames)


def stamp_id(stamp):
    return hashlib.sha256(json.dumps(stamp, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def pack(directory, archive):
    directory = Path(directory)
    buffer = io.BytesIO()
    with tarfile.open(fileobj=buffer, mode='w', format=tarfile.PAX_FORMAT) as tar:
        for name in ARCHIVE_FILES:
            data = (directory/name).read_bytes()
            info = tarfile.TarInfo(name)
            info.size, info.mode = len(data), 0o644
            tar.addfile(info, io.BytesIO(data))
    with open(archive, 'wb') as raw, gzip.GzipFile(filename='', mode='wb', fileobj=raw, mtime=0) as out:
        out.write(buffer.getvalue())


def unpack(archive, directory):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    with tarfile.open(archive, mode='r:gz') as tar:
        members = tar.getmembers()
        if sorted(m.name for m in members) != sorted(ARCHIVE_FILES) or not all(m.isfile() for m in members):
            raise ValueError(f'{archive}: unexpected archive contents')
        for member in members:
            (directory/member.name).write_bytes(tar.extractfile(member).read())
