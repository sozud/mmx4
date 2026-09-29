// EffectObj, effect_object_update_funcs[28]
// 800BBC14..800BC144
#include "common.h"

void fortress_collapse_update(struct EffectObj* self)
{
    fortress_collapse_state_funcs[self->state](self);
}

// fortress_collapse_init
INCLUDE_ASM("main/nonmatchings/effects/effect_28_fortress_collapse", func_800BBC50);

void fortress_collapse_shake(struct EffectObj* self)
{
    if (self->unk7 == 0) {
        start_screen_shake_y(10, 4, 2);
        self->unk7 = 10;
        self->state++;
    }
    self->unk7--;
}

// fortress_collapse_explode
INCLUDE_ASM("main/nonmatchings/effects/effect_28_fortress_collapse", func_800BBD88);

void fortress_collapse_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void fortress_collapse_flash_red(struct EffectObj* self)
{
    u8 temp_v0;

    temp_v0 = self->ext.effect_28.filter_timer - 1;
    self->ext.effect_28.filter_timer = temp_v0;
    if (temp_v0 == 0) {
        need_palette_load |= 1;
        self->ext.effect_28.timer = 0x5A;
        self->ext.effect_28.filter_timer = 4;
        self->ext.effect_28.palette_index ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.effect_28.finished = 0;
        return;
    }
    g_FilterAmountR = 0x1F;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
}

void fortress_collapse_flash_white(struct EffectObj* self)
{
    if (--self->ext.effect_28.filter_timer == 0) {
        need_palette_load |= 1;
        self->ext.effect_28.timer = 0x28;
        self->ext.effect_28.filter_timer = 4;
        self->ext.effect_28.palette_index ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.effect_28.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

extern s32 fortress_collapse_explosion_sounds[4];

void fortress_collapse_spawn_random_explosion(struct EffectObj* self)
{
    s16 x = background_objects[0].x_pos.i.hi;
    s16 y = background_objects[0].y_pos.i.hi;
    self->ext.effect_28.unk1B = get_random_nonzero() % 4;
    switch (self->ext.effect_28.unk1B) {
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
    x += get_random_nonzero() % 0xA0;
    y += get_random_nonzero() % 0x78;
    spawn_explosion_at(0, x, y, 0xFF);
    if ((D_80141BD8.unk0 & 3) == 0) {
        func_8001540C(0, fortress_collapse_explosion_sounds[get_random() & 3], NULL);
    }
}

void (*fortress_collapse_state_funcs[])(struct EffectObj*) = {
    func_800BBC50,
    fortress_collapse_shake,
    func_800BBD88,
    fortress_collapse_despawn,
};

void (*fortress_collapse_flash_funcs[])(struct EffectObj*) = {
    fortress_collapse_flash_red,
    fortress_collapse_flash_white,
};

s32 fortress_collapse_explosion_sounds[4] = { 0, 1, 2, 3 };

struct Effect28AnimationStep tile_anim_script_0[3] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, -2, 2 },
};

struct Effect28AnimationStep tile_anim_script_1[3] = {
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -2, 5 },
};

struct Effect28AnimationStep tile_anim_script_2[4] = {
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 0, -3, 9 },
};

struct Effect28AnimationStep* tile_anim_scripts[3] = {
    tile_anim_script_0,
    tile_anim_script_1,
    tile_anim_script_2,
};
