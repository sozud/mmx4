// MiscObj, misc_object_update_funcs[53]
// 800D2A74..800D3084
#include "common.h"

extern union AnimationStep* final_cutscene_animations[1];

// final_cutscene_init
void func_800D2A74(struct MiscObj* self)
{

    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk40 = (D_801406A8[1] >> 7) + 0xB0;
    self->unk42 = CLUT_FROM_ID(0xA3);
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA3));
    self->animation_table = (u32**)final_cutscene_animations;
    self->unk16 = 6;
    self->x_pos.u.hi = 0x860;
    self->unk15 = 0;
    self->y_pos.u.hi = 0x268;
    self->x_vel.val = FIXED(-2.5);
    self->y_vel.val = 0;
    set_animation(self, 0);
}

void final_cutscene_wait_player(struct MiscObj* self)
{
    if (g_Player.x_pos.i.hi > 0x6E0) {
        self->unk5++;
        player_start_script_action(0x14, 0x40);
        background_objects[0].unk24 = 0x6B0;
        background_objects[0].unk26 = 0x6B0;
        self->ext.misc_53.timer = 0x50;
    }
}

void final_cutscene_approach(struct MiscObj* self)
{

    if (background_objects[0].x_pos.i.hi != background_objects[0].unk26) {
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->ext.misc_53.timer != 0) {
        return;
    }

    self->ext.misc_53.movement_timer = 0xA;
    self->ext.misc_53.x_step = 1;
    self->unk5++;
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x2D, 8, 0);
        return;
    }
    func_8002217C(0x26, 8, 0);
}

// final_cutscene_talk
void func_800D2CA4(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        self->y_vel.val = 0x00050000;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->unk2C = 0x4200;
        self->unk5++;
    }
    if (main_bss_state.frame_counter % 10 == 0) {
        self->y_pos.i.hi += self->ext.misc_53.x_step;
        if (--self->ext.misc_53.movement_timer == 0) {
            self->ext.misc_53.movement_timer = 0xA;
            self->ext.misc_53.x_step *= -1;
        }
    }
}

void final_cutscene_rise(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_vel.val < 0) {
        self->y_vel.val = 0;
        self->unk5++;
    }
}

void final_cutscene_leave(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->on_screen == 0) {
        self->unk5++;
    }
}

void final_cutscene_start_effect(struct MiscObj* self)
{
    struct EffectObj* effect;

    self->ext.misc_53.timer = 0x12C;
    self->unk5++;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 0x41;
        effect->id = 0x1C;
    }
}

void final_cutscene_wait_effect(struct MiscObj* self)
{
    struct EffectObj* effect;

    if (--self->ext.misc_53.timer == 0) {
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 2;
            effect->unk2 = 0xC;
            self->ext.misc_53.effect = effect;
        }
    }
}

void final_cutscene_wait_fade(struct MiscObj* self)
{
    if (self->ext.misc_53.effect->active == 0) {
        self->unk5++;
        func_8002B560(0x1C, 0);
        self->ext.misc_53.timer = 0x1E;
    }
}

void final_cutscene_finish(struct MiscObj* self)
{
    s16 timer;

    timer = self->ext.misc_53.timer - 1;
    self->ext.misc_53.timer = timer;
    if (timer == 0) {
        self->state = 2;
        D_8013E188[0] = -1;
        D_8013E188[1] = -1;
        D_8013E188[2] = -1;
        D_8013E188[3] = -1;
        g_FilterModeR = 1;
        g_FilterModeG = 2;
        g_FilterModeB = 4;
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

void final_cutscene_main(struct MiscObj* self)
{
    final_cutscene_step_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
}

void final_cutscene_despawn(struct MiscObj* self)
{
    engine_obj.unkF = 1;
    despawn_object_permanently(OBJECT_HEADER(self));
}

void final_cutscene_update(struct MiscObj* self)
{
    final_cutscene_state_funcs[self->state](self);
}

union AnimationStep final_cutscene_anim_0[3] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};
union AnimationStep* final_cutscene_animations[1] = { final_cutscene_anim_0 };

void (*final_cutscene_step_funcs[8])(struct MiscObj*) = {
    final_cutscene_wait_player,
    final_cutscene_approach,
    func_800D2CA4,
    final_cutscene_rise,
    final_cutscene_leave,
    final_cutscene_start_effect,
    final_cutscene_wait_effect,
    final_cutscene_wait_fade,
};
void (*final_cutscene_state_funcs[3])(struct MiscObj*) = {
    func_800D2A74,
    final_cutscene_main,
    final_cutscene_despawn,
};
