// MiscObj, misc_object_update_funcs[24]
// 800CBECC..800CC460
#include "common.h"

extern union AnimationStep* enemy_hatch_animations[4];

void enemy_hatch_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    enemy_hatch_state_funcs[self->state](self);
}

// enemy_hatch_init
void func_800CBF14(struct MiscObj* self)
{
    u8 bg_offset;
    u8 state;

    if (self->x_pos.i.hi - g_Player.x_pos.i.hi <= 0) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
    self->unk40 = D_801406A8[func_8002938C(0x8F)] >> 7;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x8F));
    self->unk42 = CLUT_FROM_ID(0x8F);
    bg_offset = g_Player.bg_offset;
    state = self->state;
    self->animation_table = (u32**)enemy_hatch_animations;
    self->unk5 = 0;
    self->unk16 = 5;
    self->unk6 = 0;
    self->bg_offset = bg_offset;
    self->ext.misc_24.child_active = 0;
    self->state = state + 1;
}

void enemy_hatch_main(struct MiscObj* self)
{
    enemy_hatch_step_funcs[self->unk5](self);
    if (func_8002B160(self) == 0) {
        is_on_screen(self);
    } else {
        self->state = 2;
    }
}

void enemy_hatch_wait(struct MiscObj* self)
{
    enemy_hatch_wait_funcs[self->unk6](self);
}

void enemy_hatch_wait_start(struct MiscObj* self)
{
    self->unk6++;
    set_animation(self, 0);
}

// enemy_hatch_wait_player
void func_800CC114(struct MiscObj* self)
{
    struct MiscObj* child;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        return;
    }
    self->unk6 = 0;
    self->unk5 = 1;
    child = find_free_misc_obj();
    if (child == NULL) {
        return;
    }
    child->active = 0x41;
    child->id = 0xB;
    child->unk2 = 3;
    child->unk16 = 3;
    child->unk15 = self->unk15;
    child->unk40 = self->unk40;
    child->unk42 = self->unk42;
    child->unk3C = self->unk3C;
    child->animation_table = ANIMATED_OBJECT(self)->animation_table;
    child->bg_offset = self->bg_offset;
    child->x_pos.val = self->x_pos.val;
    child->y_pos.val = self->y_pos.val;
    set_animation(child, 2);
    child->ext.misc_11.active = 0;
    self->ext.misc_24.child = child;
    self->ext.misc_24.child_active = 1;
}

void enemy_hatch_release(struct MiscObj* self)
{
    enemy_hatch_release_funcs[self->unk6](self);
}

void enemy_hatch_release_spawn(struct MiscObj* self)
{
    struct MainObj* main;

    set_animation(self, 1);
    animate_object(ANIMATED_OBJECT(self));
    main = find_free_main_obj();
    if (main != NULL) {
        main->active = 0x41;
        if (self->unk2 != 0) {
            main->id = 3;
        } else {
            main->id = 0x30;
        }
        main->unk2 = -0x80;
        main->unk15 = self->unk15;
        main->x_pos.val = self->x_pos.val;
        if (main->id == 3) {
            main->y_pos.val = self->y_pos.val - FIXED(4);
        } else {
            main->y_pos.val = self->y_pos.val;
        }
        self->ext.misc_5.owner = main;
        self->ext.misc_24.timer = 0x20;
        self->unk6++;
        func_8001540C(2, 0xE7, self);
    }
}

void enemy_hatch_release_wait(struct MiscObj* self)
{
    animate_object((struct AnimatedObj*)self);

    if (--self->ext.misc_24.timer == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void enemy_hatch_close(struct MiscObj* self)
{
    enemy_hatch_close_funcs[self->unk6](self);
}

void enemy_hatch_close_start(struct MiscObj* self)
{
    self->unk6++;
    set_animation(self, 3);
    self->ext.misc_24.child_active = 0;
    self->ext.misc_24.child->ext.misc_11.active = 1;
}

void enemy_hatch_close_finish(struct MiscObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void enemy_hatch_despawn(struct MiscObj* self)
{
    if (self->ext.misc_24.child_active != 0) {
        ZeroObjectState(OBJECT_HEADER(self->ext.misc_24.child));
    }
    despawn_object(OBJECT_HEADER(self));
}

union AnimationStep enemy_hatch_anim_0[16] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010001 },
    { 0x05010005 },
    { 0x04010001 },
    { 0x06010005 },
    { 0x04010001 },
    { 0x07010004 },
    { 0x04010001 },
    { 0x08010004 },
    { 0x09010006 },
    { 0x0A010004 },
    { 0x0B010004 },
    { 0x0C000003 },
};

union AnimationStep enemy_hatch_anim_1[8] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010003 },
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14F90003 },
};

union AnimationStep enemy_hatch_anim_2[8] = {
    { 0x15010003 },
    { 0x16010003 },
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1CF90003 },
};

union AnimationStep enemy_hatch_anim_3[16] = {
    { 0x0C010003 },
    { 0x0B010004 },
    { 0x0A010004 },
    { 0x09010006 },
    { 0x08010004 },
    { 0x04010001 },
    { 0x07010004 },
    { 0x04010001 },
    { 0x06010005 },
    { 0x04010001 },
    { 0x05010005 },
    { 0x04010001 },
    { 0x03010002 },
    { 0x02010002 },
    { 0x01010001 },
    { 0x00000001 },
};

union AnimationStep* enemy_hatch_animations[4] = {
    enemy_hatch_anim_0,
    enemy_hatch_anim_1,
    enemy_hatch_anim_2,
    enemy_hatch_anim_3,
};

void (*enemy_hatch_state_funcs[])(struct MiscObj*) = {
    func_800CBF14,
    enemy_hatch_main,
    enemy_hatch_despawn,
};

void (*enemy_hatch_step_funcs[])(struct MiscObj*) = {
    enemy_hatch_wait,
    enemy_hatch_release,
    enemy_hatch_close,
};

void (*enemy_hatch_wait_funcs[])(struct MiscObj*) = {
    enemy_hatch_wait_start,
    func_800CC114,
};

void (*enemy_hatch_release_funcs[])(struct MiscObj*) = {
    enemy_hatch_release_spawn,
    enemy_hatch_release_wait,
};

void (*enemy_hatch_close_funcs[])(struct MiscObj*) = {
    enemy_hatch_close_start,
    enemy_hatch_close_finish,
};
