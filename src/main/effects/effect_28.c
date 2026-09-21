// EffectObj, effect_object_update_funcs[28]
// 800BBC14..800BC144
#include "common.h"

void func_800BBC14(struct EffectObj* arg0)
{
    D_8010BED4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBC50);

void func_800BBD24(struct EffectObj* arg0)
{
    if (arg0->unk7 == 0) {
        func_80028BAC(10, 4, 2);
        arg0->unk7 = 10;
        arg0->state++;
    }
    arg0->unk7--;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBD88);

void func_800BBE84(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BBEA4(struct EffectObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->ext.effect_28.filter_timer - 1;
    arg0->ext.effect_28.filter_timer = temp_v0;
    if (temp_v0 == 0) {
        need_palette_load |= 1;
        arg0->ext.effect_28.timer = 0x5A;
        arg0->ext.effect_28.filter_timer = 4;
        arg0->ext.effect_28.palette_index ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.effect_28.finished = 0;
        return;
    }
    g_FilterAmountR = 0x1F;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
}

void func_800BBF34(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_28.filter_timer == 0) {
        need_palette_load |= 1;
        arg0->ext.effect_28.timer = 0x28;
        arg0->ext.effect_28.filter_timer = 4;
        arg0->ext.effect_28.palette_index ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.effect_28.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

extern s32 D_8010BEEC[4];

void func_800BBFCC(struct EffectObj* arg0)
{
    s16 x = background_objects[0].x_pos.i.hi;
    s16 y = background_objects[0].y_pos.i.hi;
    arg0->ext.effect_28.unk1B = func_8002B780() % 4;
    switch (arg0->ext.effect_28.unk1B) {
    case 0:
        break;
    case 1:
        x += 0xA0;
        break;
    case 3:
        x += 0xA0;
        // Fall through.
    case 2:
        y += 0x78;
        break;
    }
    x += func_8002B780() % 0xA0;
    y += func_8002B780() % 0x78;
    func_800AFAB4(0, x, y, 0xFF);
    if ((D_80141BD8.unk0 & 3) == 0) {
        func_8001540C(0, D_8010BEEC[get_random() & 3], NULL);
    }
}

void (*D_8010BED4[])(struct EffectObj*) = {
    func_800BBC50,
    func_800BBD24,
    func_800BBD88,
    func_800BBE84,
};

void (*D_8010BEE4[])(struct EffectObj*) = {
    func_800BBEA4,
    func_800BBF34,
};

s32 D_8010BEEC[4] = { 0, 1, 2, 3 };

struct Effect28AnimationStep D_8010BEFC[3] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, -2, 2 },
};

struct Effect28AnimationStep D_8010BF08[3] = {
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -2, 5 },
};

struct Effect28AnimationStep D_8010BF14[4] = {
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 0, -3, 9 },
};

struct Effect28AnimationStep* D_8010BF24[3] = {
    D_8010BEFC,
    D_8010BF08,
    D_8010BF14,
};
