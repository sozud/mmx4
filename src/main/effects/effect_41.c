// EffectObj, effect_object_update_funcs[41]
// 800BE184..800BE2C4
#include "common.h"

void func_800BE184(struct EffectObj* arg0)
{
    D_8010C0F8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_41", func_800BE1C0);

INCLUDE_ASM("main/nonmatchings/effects/effect_41", func_800BE214);

INCLUDE_ASM("main/nonmatchings/effects/effect_41", func_800BE25C);

u8 D_8010C0DC[6][4] = {
    { 0x0E, 0, 1, 0 },
    { 0x0E, 0, 1, 1 },
    { 0x0E, 0, 1, 2 },
    { 0x0E, 0, 1, 3 },
    { 0x0E, 0, 1, 4 },
    { 0x0E, 0, 0xFB, 5 },
};

u8* D_8010C0F4[1] = { D_8010C0DC[0] };

void (*D_8010C0F8[])(struct EffectObj*) = {
    func_800BE1C0,
    func_800BE214,
};
