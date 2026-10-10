// MiscObj, misc_object_update_funcs[43]
// 800D0374..800D07EC
#include "common.h"

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_43_intro_messenger", func_800D03A8_jp);
#endif

void intro_messenger_update(struct MiscObj* self)
{
    intro_messenger_state_funcs[self->state](self);
}

void intro_messenger_init(struct MiscObj* self)
{
    self->bg_offset = g_Player.bg_offset;
    self->x_vel.val = 0;
    self->y_vel.val = FIXED(10);
    self->unk28 = 0;
    self->unk2C = FIXED(0.125);
    self->unk40 = D_801406A8[func_8002938C(0x45)] >> 7;
    self->unk42 = CLUT_FROM_ID(0x45);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x45)];
    self->animation_table = (u32**)intro_messenger_animations;
    self->unk16 = 6;
    self->unk15 = 0;
    self->state = 1;
    self->unk5 = 0;
    set_animation(ANIMATED_OBJECT(self), 0);
}

void intro_messenger_main(struct MiscObj* self)
{
    intro_messenger_step_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
}

void intro_messenger_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void intro_messenger_wait_scroll(struct MiscObj* self)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == 0x12F0) {
        player_start_script_action(0x15, 0);
        self->unk5 = 1;
    }
}

void intro_messenger_wait_script(struct MiscObj* self)
{
    if (g_Player.script_state == -1) {
        set_animation(self, 1);
        self->unk5 = 2;
    }
}

void intro_messenger_land(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (engine_obj.cur_character == 0) {
            func_8002217C(0x2E, 0xFF, 0);
        } else {
            func_8002217C(0x27, 0xFF, 0);
        }
        self->unk5 = 3;
    }
}

void intro_messenger_wait_dialogue(struct MiscObj* self)
{
    if (abc_object.unkC == 0) {
        set_animation(self, 2);
        self->unk5 = 4;
    }
}

void intro_messenger_take_off(struct MiscObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.event != 0) {
        move_object(MOVING_OBJECT(self));
        self->unk5 = 5;
    }
}

void intro_messenger_fly_up(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi < background_objects[g_Player.bg_offset].y_pos.i.hi - 0x30) {
        self->ext.unk.unk54 = 0x3C;
        self->unk5 = 6;
    }
}

void intro_messenger_delay(struct MiscObj* self)
{
    if (--self->ext.unk.unk54 != 0) {
        return;
    }
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x2F, 0, 0);
    } else {
        func_8002217C(0x28, 0, 0);
    }
    self->unk5 = 7;
}

void intro_messenger_finish(struct MiscObj* self)
{
    if (abc_object.unkC == 0) {
        self->state = 2;
        engine_obj.unkF = 1;
    }
}

union AnimationStep intro_messenger_anim_0[1] = { { 0x00000101 } };

union AnimationStep intro_messenger_anim_1[4] = {
    { 0x00010002 },
    { 0x02010002 },
    { 0x01010001 },
    { 0x01000101 },
};

union AnimationStep intro_messenger_anim_2[7] = {
    { 0x02010002 },
    { 0x0001000A },
    { 0x02010002 },
    { 0x03010006 },
    { 0x00010002 },
    { 0x04010001 },
    { 0x04000101 },
};

union AnimationStep* intro_messenger_animations[3] = {
    intro_messenger_anim_0,
    intro_messenger_anim_1,
    intro_messenger_anim_2,
};

void (*intro_messenger_state_funcs[3])(struct MiscObj*) = {
    intro_messenger_init,
    intro_messenger_main,
    intro_messenger_despawn,
};

void (*intro_messenger_step_funcs[8])(struct MiscObj*) = {
    intro_messenger_wait_scroll,
    intro_messenger_wait_script,
    intro_messenger_land,
    intro_messenger_wait_dialogue,
    intro_messenger_take_off,
    intro_messenger_fly_up,
    intro_messenger_delay,
    intro_messenger_finish,
};
