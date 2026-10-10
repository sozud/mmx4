// MiscObj, misc_object_update_funcs[1]
// 800C7BF4..800C7DA4
#include "common.h"

struct Misc01AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Misc01AnimationStep common_effect_anim_0[3] = {
    { 4, 0, 1, 0 },
    { 4, 0, 1, 1 },
    { 4, 0, 254, 2 },
};

struct Misc01AnimationStep common_effect_anim_1[7] = {
    { 4, 0, 1, 3 },
    { 4, 0, 1, 4 },
    { 4, 0, 1, 5 },
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 1, 0, 9 },
};

struct Misc01AnimationStep common_effect_anim_2[4] = {
    { 8, 0, 1, 10 },
    { 8, 0, 1, 11 },
    { 8, 0, 1, 12 },
    { 8, 0, 253, 11 },
};

struct Misc01AnimationStep common_effect_anim_3[4] = {
    { 6, 0, 1, 13 },
    { 6, 0, 1, 14 },
    { 6, 0, 1, 15 },
    { 6, 0, 253, 16 },
};

struct Misc01AnimationStep common_effect_anim_4[8] = {
    { 3, 0, 1, 17 },
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 3, 1, 249, 24 },
};

struct Misc01AnimationStep common_effect_anim_5[9] = {
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 248, 33 },
};

struct Misc01AnimationStep common_effect_anim_6[6] = {
    { 3, 0, 1, 34 },
    { 3, 0, 1, 35 },
    { 3, 0, 1, 36 },
    { 3, 0, 1, 37 },
    { 3, 0, 252, 38 },
    { 1, 0, 0, 40 },
};

struct Misc01AnimationStep* common_effect_animations[8] = {
    common_effect_anim_0,
    common_effect_anim_1,
    common_effect_anim_2,
    common_effect_anim_3,
    common_effect_anim_4,
    common_effect_anim_5,
    common_effect_anim_6,
    common_effect_anim_6,
};

void common_effect_update(struct MiscObj* self)
{
    common_effect_state_funcs[self->state](self);
}

void common_effect_init(struct MiscObj* self)
{
    self->state = 1;
    self->unk6 = 0;
    self->bg_offset = 0;
    self->animation_table = (u32**)common_effect_animations;
    self->unk40 = D_801406A8[func_8002938C(0x84)] >> 7;
    self->unk42 = CLUT_FROM_ID(0x84);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x84)];
    if (self->unk2 == 5) {
        self->unk16 = 5;
    } else {
        self->unk16 = 0x11;
    }
    set_animation(ANIMATED_OBJECT(self), self->unk2);
}

void common_effect_animate(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->state = 2;
    }
    is_on_screen(BASE_OBJECT(self));
}

void common_effect_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*common_effect_state_funcs[])(struct MiscObj*) = { common_effect_init, common_effect_animate, common_effect_despawn };
