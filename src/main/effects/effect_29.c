// EffectObj, effect_object_update_funcs[29]
// 800BC144..800BC2E0
#include "common.h"

void func_800BC144(struct EffectObj* arg0)
{
    D_8010BF30[arg0->state](arg0);
}

void func_800BC180(struct EffectObj* arg0)
{
    struct Effect28AnimationStep* temp_v0;
    u8 temp_v1;

    arg0->ext.effect_29.unk14 = 2;
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        temp_v0 = D_8010BF24[arg0->unk2];
        arg0->ext.effect_29.palette_source.animation = temp_v0;
        arg0->ext.effect_29.palette.fields.timer = temp_v0->timer;
        arg0->ext.effect_29.palette.fields.unk1 = arg0->ext.effect_29.palette_source.animation->unused;
        arg0->ext.effect_29.palette.fields.step = arg0->ext.effect_29.palette_source.animation->frame_step;
        temp_v1 = arg0->ext.effect_29.palette_source.animation->frame;
        arg0->state = (u8)arg0->state + 1;
        arg0->ext.effect_29.palette.fields.id = temp_v1;
    }
}

void func_800BC210(struct EffectObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_800BC258(arg0);
        return;
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_29", func_800BC258);

void (*D_8010BF30[])(struct EffectObj*) = {
    func_800BC180,
    func_800BC210,
};

u8 D_8010BF38[4][2] = {
    { 0x28, 0x18 },
    { 0x40, 0x20 },
    { 0x10, 0x40 },
    { 0, 0 },
};

struct Effect29AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 position;
};

struct Effect29AnimationStep D_8010BF40[9] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 0, 8 },
};

struct Effect29AnimationStep D_8010BF64[9] = {
    { 2, 0, 1, 8 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 5 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 1 },
    { 2, 0, 0, 0 },
};

u8* D_8010BF88[2] = {
    (u8*)D_8010BF40,
    (u8*)D_8010BF64,
};
