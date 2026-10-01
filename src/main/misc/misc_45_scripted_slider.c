// MiscObj, misc_object_update_funcs[45]
// 800D0E48..800D1284
#include "common.h"

u8 stage_cutscene_data[24] = {
    0,
    2,
    4,
    5,
    6,
    7,
    9,
    10,
    12,
    1,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    3,
    8,
    11,
#ifdef VERSION_JP
    0,
#else
    21,
#endif
    0,
    0,
};

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D0E7C_jp);
#endif

// scripted_slider_init
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D0E48);

void scripted_slider_slide(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->ext.misc_45.direction == 0) {
        if (self->x_pos.i.hi > self->ext.misc_45.target_x) {
            self->unk28 = FIXED(1);
            self->unk5++;
        }
    } else if (self->x_pos.i.hi < self->ext.misc_45.target_x) {
        self->unk28 = -FIXED(1);
        self->unk5++;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", scripted_slider_brake);
#else
void scripted_slider_brake(struct MiscObj* self)
{
    volatile u8 stack_pad[0x10];
    s32 var_v0;
    s32 var_v1;
    s32 var_a0;

    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->ext.misc_45.direction == 0) {
        var_v1 = self->ext.misc_45.target_x;
        var_v0 = self->x_pos.i.hi;
        var_a0 = var_v1;
    } else {
        var_v0 = self->ext.misc_45.target_x;
        var_v1 = self->x_pos.i.hi;
        var_a0 = var_v0;
    }
    if (var_v0 < var_v1) {
        self->x_pos.i.hi = var_a0;
        self->unk28 = 0;
        self->x_vel.val = 0;
        self->unk5++;
    }
}
#endif

void scripted_slider_idle(void)
{
}

struct Misc45PositionData {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

extern struct Misc45PositionData scripted_slider_offsets[];

void scripted_slider_follow_owner(struct MiscObj* self)
{
    s32 index;
    struct MainObj* source;

    index = self->unk2;
    source = self->ext.misc_45.owner;
    self->x_pos.u.hi = source->x_pos.u.hi + scripted_slider_offsets[index].x;
    self->y_pos.u.hi = source->y_pos.u.hi + scripted_slider_offsets[self->unk2].y;
}

// scripted_slider_step_4
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D11B0);

void scripted_slider_main(struct MiscObj* self)
{
    if (engine_flags != 0) {
        scripted_slider_step_funcs[self->unk5](self);
        self->on_screen = 1;
    }
}

void scripted_slider_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void scripted_slider_update(struct MiscObj* self)
{
    scripted_slider_state_funcs[self->state](self);
}

struct Misc45PositionData scripted_slider_offsets[] = {
    { -120, 176, 184, 160 },
    { 424, 208, 99, 123 },
    { 448, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 448, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 464, 208, 136, 160 },
    { -120, 176, 184, 160 },
    { 440, 208, 136, 160 },
#ifdef VERSION_JP
    { 440, 208, 136, 160 },
#else
    { 440, 208, 136, 152 },
#endif
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 136, 0, 0, 0 },
    { 144, 0, 0, 0 },
    { 144, 0, 0, 0 },
#ifndef VERSION_JP
    { 136, 0, 0, 0 },
#endif
};

void (*scripted_slider_step_funcs[5])(struct MiscObj*) = {
    scripted_slider_slide,
    scripted_slider_brake,
    scripted_slider_idle,
    scripted_slider_follow_owner,
    func_800D11B0,
};

void (*scripted_slider_state_funcs[3])(struct MiscObj*) = {
    func_800D0E48,
    scripted_slider_main,
    scripted_slider_despawn,
};
