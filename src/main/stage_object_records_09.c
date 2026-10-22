#include "common.h"
#include "main/effects/effect_03_palette_animator.h"

s8 D_800F815C[] = { 0, 24, 2, 22, 4, 20, 6, 18, 8, 15, 10, 12, 12, 10, 14, 8, 16, 6, 18, 4, 20, 2, 0, -1 };

s8* palette_animator_scripts_s09_0[1] = {
    D_800F815C,
};

struct PaletteAnimatorTarget palette_animator_timings_s09_0[1] = {
    { 0x50, 0x02 },
};

u8 D_800F817C[6] = {
    0x45,
    0x97,
    0x93,
    0x91,
    0x92,
    0xFF,
};

struct StageObjectRecord stage_object_records_9_0[4] = {
    { 0x00, 0x45, 0x01, 0x00, 928, 176 },
    { 0x00, 0x00, 0x00, 0xFF, 0, 0 },
    { 0x00, 0x02, 0x0F, 0x03, 104, 0 },
    { 0x00, 0x00, 0x00, 0xFF, 0, 0 },
};
