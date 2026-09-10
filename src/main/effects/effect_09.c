// EffectObj, effect_object_update_funcs[9]
// 800B75C8..800B7EE8
#include "common.h"

void func_800B75C8(struct EffectObj* arg0)
{
    D_8010B4F8[arg0->state](arg0);
}

void func_800B7604(struct EffectObj* arg0)
{
    arg0->state++;
    background_objects[2].x_pos.val = 0;
    background_objects[2].y_pos.val = 0;
    arg0->ext.effect_9.transition_timer = 1;
}

void func_800B7630(struct EffectObj* arg0)
{
    s16 temp_v0;

    temp_v0 = arg0->ext.effect_9.transition_timer - 1;
    arg0->ext.effect_9.transition_timer = temp_v0;
    if (temp_v0 == 0) {
        arg0->ext.effect_9.direction = 0;
        arg0->unk5 = 0;
        arg0->state++;
    }
}

void func_800B7668(struct EffectObj* arg0)
{
    D_8010B504[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B76A4);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7764);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7934);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7B18);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7CFC);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7E88);

void (*D_8010B4F8[])(struct EffectObj*) = {
    func_800B7604,
    func_800B7630,
    func_800B7668,
};

void (*D_8010B504[])(struct EffectObj*) = {
    func_800B76A4,
    func_800B7764,
    func_800B7934,
    func_800B7B18,
    func_800B7CFC,
};

struct Effect09MovementStep {
    u8 timer;
    s8 direction;
    u8 tile_offset;
    u8 pad;
};

struct Effect09MovementStep D_8010B518[4] = {
    { 5, 1, 0, 0 },
    { 5, 1, 1, 0 },
    { 5, 1, 2, 0 },
    { 5, -3, 3, 0 },
};

struct Effect09MovementStep D_8010B528[3] = {
    { 5, 1, 4, 0 },
    { 5, 1, 5, 0 },
    { 5, -2, 6, 0 },
};

struct Effect09MovementStep D_8010B534[3] = {
    { 5, 1, 7, 0 },
    { 5, 1, 8, 0 },
    { 5, -2, 9, 0 },
};
