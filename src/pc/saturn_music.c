
#include "common.h"
#include <psyz/audio.h>
#include <psyz/cd.h>
#include <psyz/disc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR_DATA 2048
#define BLOCK_BYTES 4096
#define MAX_FILES 256

enum SaturnSampleFormat {
    SATURN_PCM8,
    SATURN_PCM16,
};

struct SaturnSong {
    u8 psx_track;
    u8 format;
    const char* intro;
    const char* body;
};

static const struct SaturnSong saturn_songs[] = {
    { 0x00, SATURN_PCM16, "ST51_0.BIN", NULL },
    { 0x01, SATURN_PCM8, "ST1A_0.BIN", "ST1A_1.BIN" },
    { 0x02, SATURN_PCM8, "ST19_0.BIN", "ST19_1.BIN" },
    { 0x03, SATURN_PCM8, "ST01_0.BIN", "ST01_1.BIN" },
    { 0x04, SATURN_PCM8, "ST0B_0.BIN", "ST0B_1.BIN" },
    { 0x05, SATURN_PCM8, "ST08_0.BIN", "ST08_1.BIN" },
    { 0x06, SATURN_PCM8, "ST03_0.BIN", "ST03_1.BIN" },
    { 0x07, SATURN_PCM8, "ST13_0.BIN", "ST13_1.BIN" },
    { 0x08, SATURN_PCM8, "ST0D_0.BIN", "ST0D_1.BIN" },
    { 0x09, SATURN_PCM8, "ST02_0_1.BIN", "ST02_1_1.BIN" },
    { 0x0A, SATURN_PCM8, "ST06_0.BIN", "ST06_1.BIN" },
    { 0x0B, SATURN_PCM8, "ST18_0.BIN", "ST18_1.BIN" },
    { 0x0C, SATURN_PCM8, "ST07_0.BIN", "ST07_1.BIN" },
    { 0x0D, SATURN_PCM8, "ST16_0.BIN", "ST16_1.BIN" },
    { 0x0E, SATURN_PCM8, "ST02_0_0.BIN", "ST02_1_0.BIN" },
    { 0x0F, SATURN_PCM8, "ST17_0.BIN", "ST17_1.BIN" },
    { 0x10, SATURN_PCM8, "ST00_0_X.BIN", "ST00_1_X.BIN" },
    { 0x11, SATURN_PCM8, "ST04_0.BIN", "ST04_1.BIN" },
    { 0x12, SATURN_PCM8, "ST05_0.BIN", "ST05_1.BIN" },
    { 0x13, SATURN_PCM8, "ST00_0_Z.BIN", "ST00_1_Z.BIN" },
    { 0x14, SATURN_PCM8, "ST0A_0.BIN", "ST0A_1.BIN" },
    { 0x15, SATURN_PCM8, "ST12_0.BIN", "ST12_1.BIN" },
    { 0x16, SATURN_PCM8, "ST1C_0.BIN", "ST1C_1.BIN" },
    { 0x17, SATURN_PCM8, "ST1B_0.BIN", "ST1B_1.BIN" },
    { 0x18, SATURN_PCM8, "ST1E_0.BIN", "ST1E_1.BIN" },
    { 0x19, SATURN_PCM8, "ST20_0.BIN", "ST20_1.BIN" },
    { 0x1A, SATURN_PCM8, "ST1F_0.BIN", "ST1F_1.BIN" },
    { 0x1B, SATURN_PCM8, "ST1D_0.BIN", "ST1D_1.BIN" },
    { 0x1C, SATURN_PCM8, "ST0E_0_1.BIN", "ST0E_1_1.BIN" },
    { 0x21, SATURN_PCM8, "ST15_0.BIN", NULL },
    { 0x22, SATURN_PCM8, "ST14_0.BIN", NULL },
};

struct SaturnFile {
    char name[16];
    u32 lba;
    u32 size;
};

struct SaturnSegment {
    u32 lba;
    u32 blocks;
};

static struct {
    PsyzDisc* disc;
    struct SaturnFile files[MAX_FILES];
    int file_count;

    const struct SaturnSong* song;
    struct SaturnSegment segments[2];
    int segment;
    u32 block;
    int playing;
    int finished;
    short pcm[BLOCK_BYTES * 2];
    u32 pcm_frames;
    u32 pcm_pos;
} saturn;

static int read_sectors(u32 lba, u32 count, u8* out)
{
    u8 raw[PSYZ_DISC_SECTOR_SIZE];
    u32 i;
    for (i = 0; i < count; i++) {
        if (Psyz_DiscReadSector(saturn.disc, (int)(lba + i), raw) != 0)
            return -1;
        memcpy(out + i * SECTOR_DATA, raw + (raw[15] == 2 ? 24 : 16), SECTOR_DATA);
    }
    return 0;
}

static u32 le32(const u8* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((u32)p[3] << 24); }

static int is_iso9660(void)
{
    u8 pvd[SECTOR_DATA];
    return read_sectors(16, 1, pvd) == 0 && pvd[0] == 1 && memcmp(pvd + 1, "CD001", 5) == 0;
}

static int read_root_directory(void)
{
    u8 pvd[SECTOR_DATA];
    u8* directory;
    u32 lba, size, offset;
    if (read_sectors(16, 1, pvd) != 0)
        return -1;
    lba = le32(pvd + 156 + 2);
    size = le32(pvd + 156 + 10);
    directory = malloc(size);
    if (directory == NULL || read_sectors(lba, (size + SECTOR_DATA - 1) / SECTOR_DATA, directory) != 0) {
        free(directory);
        return -1;
    }
    offset = 0;
    while (offset < size && saturn.file_count < MAX_FILES) {
        u8 length = directory[offset];
        u8 name_length;
        struct SaturnFile* file;
        size_t i;
        if (length == 0) {
            offset = (offset / SECTOR_DATA + 1) * SECTOR_DATA;
            continue;
        }
        name_length = directory[offset + 32];
        file = &saturn.files[saturn.file_count];
        if (!(directory[offset + 25] & 2) && name_length < sizeof(file->name)) {
            for (i = 0; i < name_length && directory[offset + 33 + i] != ';'; i++)
                file->name[i] = directory[offset + 33 + i];
            file->name[i] = '\0';
            file->lba = le32(directory + offset + 2);
            file->size = le32(directory + offset + 10);
            saturn.file_count++;
        }
        offset += length;
    }
    free(directory);
    return 0;
}

static const struct SaturnFile* find_file(const char* name)
{
    int i;
    for (i = 0; i < saturn.file_count; i++) {
        if (strcmp(saturn.files[i].name, name) == 0)
            return &saturn.files[i];
    }
    return NULL;
}

int mmx4_pc_saturn_music_open(const char* path)
{
    size_t i;
    int missing = 0;
    saturn.disc = Psyz_DiscOpen(path);
    if (saturn.disc == NULL) {
        fprintf(stderr, "MMX4 PC: unable to open Saturn disc: %s\n", Psyz_DiscLastError());
        return -1;
    }
    saturn.file_count = 0;
    if (!is_iso9660() || read_root_directory() != 0) {
        fprintf(stderr, "MMX4 PC: %s is not a readable Saturn data track\n", path);
        Psyz_DiscClose(saturn.disc);
        saturn.disc = NULL;
        return -1;
    }
    for (i = 0; i < sizeof(saturn_songs) / sizeof(saturn_songs[0]); i++) {
        if (find_file(saturn_songs[i].intro) == NULL
            || (saturn_songs[i].body != NULL && find_file(saturn_songs[i].body) == NULL))
            missing++;
    }
    if (missing == (int)(sizeof(saturn_songs) / sizeof(saturn_songs[0]))) {
        fprintf(stderr, "MMX4 PC: %s has no Saturn music streams\n", path);
        Psyz_DiscClose(saturn.disc);
        saturn.disc = NULL;
        return -1;
    }
    fprintf(stderr, "MMX4 PC: Saturn music from %s (%d songs missing)\n", path, missing);
    return 0;
}

int mmx4_pc_saturn_music_enabled(void) { return saturn.disc != NULL; }

static void set_segment(int index, const char* name, u32 block_bytes)
{
    const struct SaturnFile* file = name == NULL ? NULL : find_file(name);
    saturn.segments[index].lba = file == NULL ? 0 : file->lba;
    saturn.segments[index].blocks = file == NULL ? 0 : file->size / block_bytes;
}

static long saturn_override(short* out, size_t frames);

void mmx4_pc_saturn_music_select(int psx_track)
{
    const struct SaturnSong* song = NULL;
    size_t i;
    if (saturn.disc == NULL)
        return;
    for (i = 0; i < sizeof(saturn_songs) / sizeof(saturn_songs[0]); i++) {
        if (saturn_songs[i].psx_track == psx_track)
            song = &saturn_songs[i];
    }
    Psyz_AudioLock();
    saturn.song = song;
    saturn.segment = 0;
    saturn.block = 0;
    saturn.pcm_frames = 0;
    saturn.pcm_pos = 0;
    saturn.finished = 0;
    saturn.playing = 0;
    if (song != NULL) {
        set_segment(0, song->intro, BLOCK_BYTES * 2);
        set_segment(1, song->body, BLOCK_BYTES * 2);
        if (saturn.segments[0].blocks == 0 && saturn.segments[1].blocks == 0)
            saturn.song = NULL;
    }
    Psyz_AudioUnlock();
    Psyz_CdSetAudioOverride(saturn.song != NULL ? saturn_override : NULL);
}

void mmx4_pc_saturn_music_set_playing(int playing)
{
    if (saturn.song == NULL || saturn.playing == playing)
        return;
    Psyz_AudioLock();
    saturn.playing = playing;
    Psyz_AudioUnlock();
}

static int next_block(void)
{
    static u8 raw[BLOCK_BYTES * 2];
    struct SaturnSegment* segment;
    u32 i;
    for (;;) {
        segment = &saturn.segments[saturn.segment];
        if (saturn.block < segment->blocks)
            break;
        if (saturn.song->body == NULL || saturn.segments[1].blocks == 0)
            return 0;
        saturn.segment = 1;
        saturn.block = 0;
    }
    if (read_sectors(segment->lba + saturn.block * 4, 4, raw) != 0)
        return 0;
    saturn.block++;
    if (saturn.song->format == SATURN_PCM16) {
        for (i = 0; i < BLOCK_BYTES / 2; i++) {
            saturn.pcm[i * 2] = (short)((raw[i * 2] << 8) | raw[i * 2 + 1]);
            saturn.pcm[i * 2 + 1] = (short)((raw[BLOCK_BYTES + i * 2] << 8) | raw[BLOCK_BYTES + i * 2 + 1]);
        }
        saturn.pcm_frames = BLOCK_BYTES / 2;
    } else {
        for (i = 0; i < BLOCK_BYTES; i++) {
            saturn.pcm[i * 2] = (short)((s8)raw[i] << 8);
            saturn.pcm[i * 2 + 1] = (short)((s8)raw[BLOCK_BYTES + i] << 8);
        }
        saturn.pcm_frames = BLOCK_BYTES;
    }
    saturn.pcm_pos = 0;
    return 1;
}

static long saturn_override(short* out, size_t frames)
{
    size_t written = 0;
    if (saturn.song == NULL)
        return -1;
    while (written < frames) {
        if (!saturn.playing || saturn.finished) {
            out[written * 2] = 0;
            out[written * 2 + 1] = 0;
            written++;
            continue;
        }
        if (saturn.pcm_pos >= saturn.pcm_frames && !next_block()) {
            saturn.finished = 1;
            continue;
        }
        out[written * 2] = saturn.pcm[saturn.pcm_pos * 2];
        out[written * 2 + 1] = saturn.pcm[saturn.pcm_pos * 2 + 1];
        saturn.pcm_pos++;
        written++;
    }
    return (long)written;
}
