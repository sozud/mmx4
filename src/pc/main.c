#include "common.h"
#include "oracle_capture.h"
#include <psyz/cd.h>
#include <psyz/spu.h>
#include <psyz/video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Alignas(16) u8 mmx4_scratchpad[0x400];
void* mmx4_sp_primitive_cursor;
void* mmx4_sp_draw_mode_cursor;
void* mmx4_sp_background_cursor;
void* mmx4_sp_background_primitive_cursor;
void* mmx4_sp_ordering_cursor;
void* mmx4_sp_auxiliary_cursor;

s32 mmx4_pc_sfx_group = -1;
u32 mmx4_pc_sfx_index;
const char* mmx4_pc_sfx_raw;
u32 mmx4_pc_sfx_frames = 360;
s32 mmx4_pc_canonical_load;

static int parse_sfx(const char* text)
{
    char* end;
    unsigned long first = strtoul(text, &end, 0);
    unsigned long group = 0;
    unsigned long index = first;

    if (end == text)
        return -1;
    if (*end == ':') {
        char* index_end;
        group = first;
        index = strtoul(end + 1, &index_end, 0);
        if (index_end == end + 1 || *index_end != '\0')
            return -1;
    } else if (*end != '\0') {
        return -1;
    }
    if (group >= 8 || index > 0xff)
        return -1;
    mmx4_pc_sfx_group = (s32)group;
    mmx4_pc_sfx_index = (u32)index;
    return 0;
}

static int parse_args(int argc, char** argv, const char** disc)
{
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--sfx") == 0 && i + 1 < argc) {
            if (parse_sfx(argv[++i]) != 0) {
                fprintf(stderr, "MMX4 PC: invalid --sfx value (use INDEX or GROUP:INDEX)\n");
                return -1;
            }
        } else if (strcmp(argv[i], "--cue") == 0 && i + 1 < argc) {
            *disc = argv[++i];
        } else if (strcmp(argv[i], "--audio-raw") == 0 && i + 1 < argc) {
            mmx4_pc_sfx_raw = argv[++i];
        } else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc) {
            char* end;
            unsigned long frames = strtoul(argv[++i], &end, 0);
            if (*end != '\0' || frames == 0 || frames > 36000) {
                fprintf(stderr, "MMX4 PC: invalid --frames value\n");
                return -1;
            }
            mmx4_pc_sfx_frames = (u32)frames;
        } else if (strcmp(argv[i], "--canonical-load") == 0) {
            mmx4_pc_canonical_load = 1;
        } else if (strcmp(argv[i], "--fast-load") == 0) {
            mmx4_pc_canonical_load = 0;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("usage: %s [--cue GAME.cue] [--sfx INDEX|GROUP:INDEX] "
                   "[--audio-raw FILE --frames N] "
                   "[--canonical-load|--fast-load]\n",
                argv[0]);
            return 1;
        } else {
            fprintf(stderr, "MMX4 PC: unknown or incomplete option: %s\n", argv[i]);
            return -1;
        }
    }
    if (mmx4_pc_sfx_raw != NULL && mmx4_pc_sfx_group < 0) {
        fprintf(stderr, "MMX4 PC: --audio-raw requires --sfx\n");
        return -1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    int oracle_result = mmx4_oracle_capture_placeholder();
    const char* disc = getenv("MMX4_CUE");
    const char* canonical_load = getenv("MMX4_CANONICAL_LOAD");
    int parse_result;
    if (oracle_result != MMX4_ORACLE_NOT_REQUESTED)
        return oracle_result;

    mmx4_pc_canonical_load = canonical_load != NULL && canonical_load[0] != '\0' && canonical_load[0] != '0';
    if (disc == NULL)
        disc = "disks/mmx4.us.cue";
    parse_result = parse_args(argc, argv, &disc);
    if (parse_result != 0)
        return parse_result < 0 ? 2 : 0;
    if (Psyz_CdSetDiskPath(disc) != 0) {
        fprintf(stderr, "MMX4 PC: unable to load disc image %s\n", disc);
        return 1;
    }

    Psyz_SpuInit();
    if (getenv("MMX4_MAX_FRAMES") != NULL)
        Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS);
    func_80012024();
    return 0;
}
