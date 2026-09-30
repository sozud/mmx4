// EffectObj, effect_object_update_funcs[10]
// 800B7EE8..800B8064
#include "common.h"

// sound_zone_update
INCLUDE_ASM("main/nonmatchings/effects/effect_10", func_800B7EE8);

struct Effect10Trigger {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    u8 sound_id;
    u8 pad;
};

struct Effect10Trigger sound_zone_list_0[4] = {
    { 0x0000, 0x0700, 0x0000, 0x0200, 0, 0 },
    { 0x0670, 0x1500, 0x0000, 0x0600, 2, 0 },
    { 0x14A0, 0x1900, 0x0280, 0x0600, 1, 0 },
    { 0x1500, 0x1900, 0x0000, 0x03C0, 2, 0 },
};

struct Effect10Trigger sound_zone_list_1[4] = {
    { 0x0520, 0x05F0, 0x0130, 0x0220, 1, 0 },
    { 0x0200, 0x05F0, 0x01E0, 0x0320, 1, 0 },
    { 0x0200, 0x03B0, 0x02E0, 0x03F0, 1, 0 },
    { 0x0700, 0x0930, 0x0280, 0x0600, 1, 0 },
};

struct Effect10Trigger* sound_zone_lists[2] = {
    sound_zone_list_0,
    sound_zone_list_1,
};

extern u16 sound_zone_data[65];

extern u16 sound_zone_padding;
