// EffectObj, effect_object_update_funcs[9]
// 800B75C8..800B7EE8
#include "common.h"

struct Effect09MovementStep {
    u8 timer;
    s8 direction;
    u8 tile_offset;
    u8 pad;
};

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

extern struct Effect09MovementStep D_8010B534[3];
extern struct Effect09MovementStep D_8010B528[3];
extern struct Effect09MovementStep D_8010B518[4];

void func_800B7934(struct EffectObj* arg0)
{
    s32 shifted_target;
    if (--arg0->ext.effect_9.movement_timer << 16 == 0) {
        if (arg0->ext.effect_9.direction != 0) {
            arg0->ext.effect_9.movement_timer = 0x168;
            arg0->ext.effect_9.movement_table = (u8*)D_8010B534;
            arg0->unk5--;
        } else {
            arg0->ext.effect_9.movement_timer = 0x78;
            arg0->ext.effect_9.movement_table = (u8*)D_8010B528;
            arg0->unk5++;
        }
        arg0->ext.effect_9.timer = arg0->ext.effect_9.movement_table[0];
        arg0->ext.effect_9.frame = arg0->ext.effect_9.movement_table[1];
        arg0->ext.effect_9.target_x = arg0->ext.effect_9.movement_table[2];
        return;
    }
    if (--arg0->ext.effect_9.timer == 0) {
        s16* bg_hi;
        s32 final_target;

        arg0->ext.effect_9.movement_table = (u8*)&arg0->ext.effect_9.movement_table[(arg0->ext.effect_9.frame * 4)];
        arg0->ext.effect_9.target_x = arg0->ext.effect_9.movement_table[2];
        arg0->ext.effect_9.timer = arg0->ext.effect_9.movement_table[0];
        arg0->ext.effect_9.frame = arg0->ext.effect_9.movement_table[1];

        bg_hi = &background_objects[2].x_pos.i.hi;
        final_target = (arg0->ext.effect_9.target_x << 9) + *(u8*)bg_hi;
        *bg_hi = (s32)final_target;

        background_objects[2].unk4C = 1;
    }
    if (arg0->ext.effect_9.direction != 0) {
        if (arg0->ext.effect_9.velocity > FIXED(2.5)) {
            arg0->ext.effect_9.velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (arg0->ext.effect_9.velocity <= FIXED(2.5) - 1) {
            arg0->ext.effect_9.velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val += arg0->ext.effect_9.velocity;
    shifted_target = arg0->ext.effect_9.target_x << 9;
    if (background_objects[2].x_pos.i.hi >= (shifted_target + 0xC0)) {
        background_objects[2].x_pos.i.hi = shifted_target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
        background_objects[2].unk4C = 1;
    }
}

void func_800B7B18(struct EffectObj* arg0)
{
    s32 shifted_target;
    if (--arg0->ext.effect_9.movement_timer << 16 == 0) {
        if (arg0->ext.effect_9.direction != 0) {
            arg0->ext.effect_9.movement_timer = 0xB4;
            arg0->ext.effect_9.movement_table = (u8*)D_8010B528;
            arg0->unk5--;
        } else {
            arg0->ext.effect_9.movement_timer = 0x96;
            arg0->ext.effect_9.movement_table = (u8*)D_8010B518;
            arg0->unk5++;
        }
        arg0->ext.effect_9.timer = arg0->ext.effect_9.movement_table[0];
        arg0->ext.effect_9.frame = arg0->ext.effect_9.movement_table[1];
        arg0->ext.effect_9.target_x = arg0->ext.effect_9.movement_table[2];
        return;
    }
    if (--arg0->ext.effect_9.timer == 0) {
        s16* bg_hi;
        s32 final_target;

        arg0->ext.effect_9.movement_table = (u8*)&arg0->ext.effect_9.movement_table[(arg0->ext.effect_9.frame * 4)];
        arg0->ext.effect_9.target_x = arg0->ext.effect_9.movement_table[2];
        arg0->ext.effect_9.timer = arg0->ext.effect_9.movement_table[0];
        arg0->ext.effect_9.frame = arg0->ext.effect_9.movement_table[1];

        bg_hi = &background_objects[2].x_pos.i.hi;
        final_target = (arg0->ext.effect_9.target_x << 9) + *(u8*)bg_hi;
        *bg_hi = (s32)final_target;

        background_objects[2].unk4C = 1;
    }
    if (arg0->ext.effect_9.direction != 0) {
        if (arg0->ext.effect_9.velocity > FIXED(3.5)) {
            arg0->ext.effect_9.velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (arg0->ext.effect_9.velocity <= FIXED(3.5) - 1) {
            arg0->ext.effect_9.velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val += arg0->ext.effect_9.velocity;
    shifted_target = arg0->ext.effect_9.target_x << 9;
    if (background_objects[2].x_pos.i.hi >= (shifted_target + 0xC0)) {
        background_objects[2].x_pos.i.hi = shifted_target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
        background_objects[2].unk4C = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7CFC);

u8 func_800B7E88(s16* bounds)
{
    s16 x;
    s16 y;

    x = g_Player.x_pos.i.hi;
    y = g_Player.y_pos.i.hi;
    if ((x > bounds[0]) && (x < bounds[1]) && (bounds[2] < y)) {
        if (y < bounds[3]) {
            return 1;
        }
    }
    return 0;
}

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
