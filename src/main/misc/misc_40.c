// MiscObj, misc_object_update_funcs[40]
// 800CFB70..800CFE98
#include "common.h"

// ambient_bubble_init
INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFB70);

// ambient_bubble_wait
INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFC6C);

void ambient_bubble_float(struct MiscObj* self)
{
    s8 subtype;

    subtype = self->unk2;
    if (self->y_vel.val < ambient_bubble_max_speeds[subtype]) {
        self->unk2C = -ambient_bubble_accels[subtype];
        set_animation(self, 2);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->unk5 = 0;
    self->ext.misc_24.timer = ambient_bubble_respawn_delays[self->unk2] + (get_random() & 0x3F);
}

void ambient_bubble_main(struct MiscObj* self)
{
    ambient_bubble_step_funcs[self->unk5](self);
}

void ambient_bubble_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void ambient_bubble_update(struct MiscObj* self)
{
    ambient_bubble_state_funcs[self->state](self);
}

union AnimationStep ambient_bubble_anim_0[4] = {
    { .packed = 0x0001000E },
    { .packed = 0x0101000E },
    { .packed = 0x0201000E },
    { .packed = 0x01FD000E },
};

union AnimationStep ambient_bubble_anim_1[3] = {
    { .packed = 0x0001000E },
    { .packed = 0x0101000E },
    { .packed = 0x0200000E },
};

union AnimationStep ambient_bubble_anim_2[3] = {
    { .packed = 0x0201000E },
    { .packed = 0x0101000E },
    { .packed = 0x0000000E },
};

union AnimationStep* ambient_bubble_animations[3] = {
    ambient_bubble_anim_0,
    ambient_bubble_anim_1,
    ambient_bubble_anim_2,
};

u16 ambient_bubble_positions[8] = {
    0x90,
    0x70,
    0xB0,
    0xD0,
    0x80,
    0xA0,
    0xC0,
    0xE0,
};

s32 ambient_bubble_speeds[4] = {
    -0x18000,
    -0x28000,
    -0x38000,
    -0x48000,
};

s32 ambient_bubble_accels[4] = {
    0x1000,
    0x1000,
    0x1000,
    0x1000,
};

s32 ambient_bubble_max_speeds[4] = {
    -0x18000,
    -0x10000,
    -0x8000,
    -0x4000,
};

u16 ambient_bubble_respawn_delays[4] = { 0xB4, 0x12C, 0x168, 0 };

void (*ambient_bubble_step_funcs[2])(struct MiscObj*) = {
    func_800CFC6C,
    ambient_bubble_float,
};

void (*ambient_bubble_state_funcs[3])(struct MiscObj*) = {
    func_800CFB70,
    ambient_bubble_main,
    ambient_bubble_despawn,
};
