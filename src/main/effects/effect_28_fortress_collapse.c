// EffectObj, effect_object_update_funcs[28]
// 800BBC14..800BC144
#include "common.h"

void fortress_collapse_update(struct EffectObj* self)
{
    fortress_collapse_state_funcs[self->state](self);
}

// fortress_collapse_init
void func_800BBC50(struct EffectObj* self)
{
    u8 i;

    for (i = 0; i < 4; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->ext.effect_28.timer = 0x28;
    self->ext.effect_28.filter_timer = 4;
    self->ext.effect_28.palette_index = 0;
    self->ext.effect_28.unk1A = 3;
    func_8002B560(2, 1);
    self->state++;
    start_screen_shake_y(0x28, 4, 2);
    self->unk7 = 0x27;
}

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
    if (0 == temp_v0) {
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
    if ((main_bss_state.frame_counter & 3) == 0) {
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

extern struct Effect28AnimationStep tile_anim_script_0[3];

extern struct Effect28AnimationStep tile_anim_script_1[3];

extern struct Effect28AnimationStep tile_anim_script_2[4];

extern struct Effect28AnimationStep* tile_anim_scripts[3];
