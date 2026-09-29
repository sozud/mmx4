// MainObj, main_object_update_funcs[40]
// 80061DC0..800623C4
#include "common.h"
#include "func_tables.h"

void breakable_terrain_update(struct MainObj* self)
{
    breakable_terrain_state_funcs[self->state](self);
}

// breakable_terrain_init
INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061DFC);

// breakable_terrain_main
INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061F2C);

void breakable_terrain_crumble(struct MainObj* self)
{
    s32 index;

    self->ext.main_40.timer--;
    if (self->ext.main_40.timer != 0) {
        if (!(D_80141BD8.unk0 & 7)) {
            if (self->ext.main_40.unk80 < 2U) {
                func_800AF878(BASE_OBJECT(self), 1, 0x10, 0x30);
            }
        }
        if (self->ext.main_40.unk80 >= 2U && self->ext.main_40.timer == self->ext.main_40.trigger_time) {
            index = (self->ext.main_40.unk80 - 2) * 2;
            ((void (*)(s32, s32, s32))apply_tile_effect)(self->ext.main_40.unk81 + 6,
                self->x_pos.i.hi + breakable_terrain_effect_offsets[index],
                self->y_pos.i.hi + breakable_terrain_effect_offsets[index + 1]);
        }
    } else {
        self->state++;
    }
}

void breakable_terrain_remove(struct MainObj* self)
{
    u8 state = self->ext.main_40.unk80;
    s32 offset;

    if (state >= 2U) {
        offset = (state - 2) * 2;
        ((void (*)(s32, s32, s32))apply_tile_effect)(self->ext.main_40.unk81 + 0xB,
            self->x_pos.i.hi + breakable_terrain_effect_offsets[offset],
            self->y_pos.i.hi + breakable_terrain_effect_offsets[offset + 1]);
        breakable_terrain_spawn_rubble(self);
    }
    despawn_object_permanently(OBJECT_HEADER(self));
}

extern u8 breakable_terrain_rubble_sizes[];
extern u8 breakable_terrain_rubble_variants[];

void breakable_terrain_spawn_rubble(struct MainObj* self)
{
    s32 temp_v0;
    u16 temp_s0;
    u16 temp_s1;
    u8 temp_s2;
    u8 temp_s3;
    u8 temp_s5;

    temp_s1 = (u16)self->x_pos.i.hi;
    temp_s0 = (u16)self->y_pos.i.hi;
    temp_v0 = self->ext.main_0.index * 3;
    temp_s5 = breakable_terrain_rubble_sizes[2 + temp_v0];
    temp_s2 = breakable_terrain_rubble_sizes[temp_v0];
    temp_s3 = breakable_terrain_rubble_sizes[1 + temp_v0];
    spawn_rubble(temp_s5 * 2, breakable_terrain_rubble_variants, self, 0);
    func_800B10E4(0x21,
        (s16)temp_s1 - (temp_s2 >> 1),
        (s16)temp_s0 - (temp_s3 >> 1) + 0x10,
        (s16)temp_s1 + (temp_s2 >> 1),
        (s16)temp_s0 + (temp_s3 >> 1) + 0x10,
        temp_s5);
    func_8001540C(0, (get_random() & 1) ^ 1, self);
}

// breakable_terrain_check_hit
INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80062338);

s8 D_800FE9C8[4] = { -32, -32, 64, 80 };

s8 D_800FE9CC[4] = { -16, -48, 32, 96 };

s8 D_800FE9D0[4] = { -16, -32, 32, 64 };

s8 D_800FE9D4[4] = { -40, -48, 80, 96 };

s8 D_800FE9D8[4] = { -104, -24, -48, 48 };

s8 D_800FE9DC[4] = { -40, -48, 80, 96 };

s8 D_800FE9E0[4] = { -32, -24, 64, 48 };

union AnimationStep breakable_terrain_anim_0[] = { { 0x00000001 } };

union AnimationStep breakable_terrain_anim_1[] = { { 0x01000001 } };

union AnimationStep breakable_terrain_anim_2[] = { { 0x02000001 } };

union AnimationStep breakable_terrain_anim_3[] = { { 0x03000001 } };

union AnimationStep breakable_terrain_anim_4[] = { { 0x04000001 } };

union AnimationStep breakable_terrain_anim_5[] = { { 0x05000001 } };

union AnimationStep* breakable_terrain_animations[6] = {
    breakable_terrain_anim_0,
    breakable_terrain_anim_1,
    breakable_terrain_anim_2,
    breakable_terrain_anim_3,
    breakable_terrain_anim_4,
    breakable_terrain_anim_5,
};

u8 D_800FEA14[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };

u8 D_800FEA1C[8] = { 1, 2, 3, 4, 5, 2, 4, 0 };

s8* D_800FEA24[7] = {
    D_800FE9C8,
    D_800FE9CC,
    D_800FE9D0,
    D_800FE9D4,
    D_800FE9D8,
    D_800FE9DC,
    D_800FE9E0,
};

union AnimationStep** D_800FEA40[7] = {
    NULL,
    breakable_terrain_animations,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s8 breakable_terrain_effect_offsets[12] = { -16, -32, -40, -48, -104, -24, -40, -48, -32, -24, 0, 0 };

u8 breakable_terrain_rubble_sizes[16] = { 32, 48, 3, 80, 80, 6, 208, 32, 8, 64, 32, 5, 64, 32, 5, 0 };

void (*breakable_terrain_state_funcs[])(struct MainObj*) = {
    func_80061DFC,
    func_80061F2C,
    breakable_terrain_crumble,
    breakable_terrain_remove,
};

u8 breakable_terrain_rubble_variants[24] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    0,
    0,
};

struct Unk_unk68 D_800FEAA0 = { 0, 0, 16, 48 };
