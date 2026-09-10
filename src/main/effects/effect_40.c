// EffectObj, effect_object_update_funcs[40]
// 800BE038..800BE184
#include "common.h"

void func_800BE038(struct EffectObj* arg0)
{
    D_8010C0D4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_40", func_800BE074);

void func_800BE0FC(struct EffectObj* arg0);

void func_800BE0DC(struct EffectObj* arg0)
{
    func_800BE0FC(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_40", func_800BE0FC);

u8 D_8010C094[6][4] = {
    { 9, 0, 1, 0 },
    { 9, 0, 1, 1 },
    { 9, 0, 1, 2 },
    { 0x40, 0, 1, 3 },
    { 9, 0, 1, 4 },
    { 9, 0, 0xFB, 5 },
};

u8 D_8010C0AC[6][4] = {
    { 0x40, 0, 1, 6 },
    { 9, 0, 1, 7 },
    { 9, 0, 1, 8 },
    { 9, 0, 1, 9 },
    { 9, 0, 1, 0x0A },
    { 9, 0, 0xFB, 0x0B },
};

u16 D_8010C0C4[4] = { 0x30, 0x20, 0x40, 0x30 };

u8* D_8010C0CC[2] = { D_8010C094[0], D_8010C0AC[0] };

void (*D_8010C0D4[])(struct EffectObj*) = {
    func_800BE074,
    func_800BE0DC,
};
