// VisualObj, visual_object_update_funcs[24]
// 800B35B8..800B3D3C
#include "common.h"

s32 frost_walrus_fx_blizzard_x_vels[4] = { 0x1C000, 0x2C000, 0x3C000, 0x34000 };
s32 frost_walrus_fx_blizzard_y_vels[4] = { 0x18000, 0x28000, 0x8000, 0x30000 };
s32 frost_walrus_fx_breath_x_vels[4] = { 0x1C000, 0x2C000, 0x3C000, 0x34000 };
s32 frost_walrus_fx_breath_y_vels[4] = { -0x18000, -0x28000, -0x8000, -0x30000 };
s16 frost_walrus_fx_sparkle_offsets[8] = { -9, 0x13, -0x26, -0x16, 0x2B, -0xA, 0x1C, 0x26 };

void frost_walrus_fx_update(struct VisualObj* arg0)
{
    frost_walrus_fx_state_funcs[arg0->state](arg0);
}

void frost_walrus_fx_init(struct VisualObj* self)
{
    u8 background;
    s32 state;

    self->unk3C = self->unk50->unk3C;
    self->animation_table = self->unk50->animation_table;
    self->unk40 = self->unk50->unk40;
    if (self->unk2 == 0x20) {
        self->unk42 = self->unk50->unk42;
    } else {
        self->unk42 = self->unk50->unk42 & 0x7FFF;
    }
    self->unk16 = 3;
    background = (u8)g_Player.bg_offset;
    self->state = (u8)self->state + 1;
    state = (s32)((u8)self->unk2 << 24) >> 28;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->bg_offset = (s8)background;
    self->unk5 = (s8)state;
    if (state == 2) {
        set_animation(self, 0x18);
    } else {
        set_animation(self, 0x1D);
    }
    self->unk2 = (u8)self->unk2 & 0xF;
}

void frost_walrus_fx_main(struct VisualObj* arg0)
{
    frost_walrus_fx_mode_funcs[arg0->unk5](arg0);
}

void frost_walrus_fx_burst(struct VisualObj* arg0)
{
    frost_walrus_fx_burst_funcs[arg0->unk6](arg0);
}

void frost_walrus_fx_burst_start(struct VisualObj* arg0)
{
    arg0->unk15 = 0;
    switch (arg0->unk2) {
    case 0:
        arg0->x_vel.val = 0;
        arg0->y_vel.val = FIXED(1.25);
        break;
    case 1:
        arg0->x_vel.val = 0;
        arg0->y_vel.val = FIXED(-1.25);
        break;
    case 2:
        arg0->x_vel.val = FIXED(1.25);
        arg0->y_vel.val = 0;
        break;
    case 3:
        arg0->x_vel.val = FIXED(-1.25);
        arg0->y_vel.val = 0;
        break;
    }
    arg0->unk6++;
}

void frost_walrus_fx_burst_move(struct VisualObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void frost_walrus_fx_breath(struct VisualObj* arg0)
{
    frost_walrus_fx_breath_funcs[arg0->unk6](arg0);
}

void frost_walrus_fx_breath_start(struct VisualObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = frost_walrus_fx_breath_x_vels[get_random() & 3];
    } else {
        arg0->x_vel.val = -frost_walrus_fx_breath_x_vels[get_random() & 3];
    }
    arg0->y_vel.val = frost_walrus_fx_breath_y_vels[get_random() & 3];
    arg0->unk6++;
}

void frost_walrus_fx_breath_move(struct VisualObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void frost_walrus_fx_blizzard(struct VisualObj* arg0)
{
    frost_walrus_fx_blizzard_funcs[arg0->unk6](arg0);
}

void frost_walrus_fx_blizzard_start(struct VisualObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = frost_walrus_fx_blizzard_x_vels[get_random() & 3];
    } else {
        arg0->x_vel.val = -frost_walrus_fx_blizzard_x_vels[get_random() & 3];
    }
    arg0->y_vel.val = frost_walrus_fx_blizzard_y_vels[get_random() & 3];
    arg0->unk6++;
}

void frost_walrus_fx_blizzard_move(struct VisualObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void frost_walrus_fx_regrow(struct VisualObj* arg0)
{
    arg0->unk42 = arg0->unk50->unk42;
    is_on_screen(BASE_OBJECT(arg0));
    if (g_Player.update_delay == 0) {
        animate_object(arg0);
        if (arg0->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
        }
    }
}

void frost_walrus_fx_sparkle(struct VisualObj* arg0)
{
    frost_walrus_fx_sparkle_funcs[arg0->unk6](arg0);
}

void frost_walrus_fx_sparkle_start(struct VisualObj* arg0)
{
    set_animation(arg0, 0x13);
    arg0->unk6++;
}

// frost_walrus_fx_sparkle_move
INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3B94);

void frost_walrus_fx_stagger(struct VisualObj* arg0)
{
    frost_walrus_fx_stagger_funcs[arg0->unk6](arg0);
    arg0->unk42 = arg0->unk50->unk42;
}

void frost_walrus_fx_stagger_start(struct VisualObj* arg0)
{
    set_animation(arg0, 0x15);
    arg0->unk6++;
}

void frost_walrus_fx_stagger_follow(struct VisualObj* arg0)
{
    struct PlayerObj* source;

    animate_object(ANIMATED_OBJECT(arg0));
    source = arg0->unk50;
    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    arg0->unk15 = source->unk15;
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void (*frost_walrus_fx_state_funcs[])(struct VisualObj*) = {
    frost_walrus_fx_init,
    frost_walrus_fx_main,
};

void (*frost_walrus_fx_mode_funcs[])(struct VisualObj*) = {
    frost_walrus_fx_burst,
    frost_walrus_fx_breath,
    frost_walrus_fx_regrow,
    frost_walrus_fx_blizzard,
    frost_walrus_fx_sparkle,
    frost_walrus_fx_stagger,
};

void (*frost_walrus_fx_burst_funcs[])(struct VisualObj*) = { frost_walrus_fx_burst_start, frost_walrus_fx_burst_move };
void (*frost_walrus_fx_breath_funcs[])(struct VisualObj*) = { frost_walrus_fx_breath_start, frost_walrus_fx_breath_move };
void (*frost_walrus_fx_blizzard_funcs[])(struct VisualObj*) = { frost_walrus_fx_blizzard_start, frost_walrus_fx_blizzard_move };
void (*frost_walrus_fx_sparkle_funcs[])(struct VisualObj*) = { frost_walrus_fx_sparkle_start, func_800B3B94 };
void (*frost_walrus_fx_stagger_funcs[])(struct VisualObj*) = { frost_walrus_fx_stagger_start, frost_walrus_fx_stagger_follow };
