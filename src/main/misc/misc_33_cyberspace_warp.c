// MiscObj, misc_object_update_funcs[33]
// 800CE340..800CE894
#include "common.h"

void cyberspace_warp_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    cyberspace_warp_state_funcs[self->state](self);
}

// cyberspace_warp_init
INCLUDE_ASM("main/nonmatchings/misc/misc_33_cyberspace_warp", func_800CE388);

void cyberspace_warp_main(struct MiscObj* self)
{
    cyberspace_warp_main_funcs[self->unk5](self);
}

void cyberspace_warp_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cyberspace_warp_fade(struct MiscObj* self)
{
    u16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->ext.misc_33.timer - 1;
    self->ext.misc_33.timer = timer;
    if (timer == 0) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state++;
}

void cyberspace_warp_wait(struct MiscObj* self)
{
    cyberspace_warp_wait_funcs[self->unk6](self);
    if (*self->ext.misc_33.completion_flag == 0) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
}

void cyberspace_warp_wait_start(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->ext.misc_33.timer = 0x14;
    self->unk6 += 1;
    func_8001540C(2, 0xE8, self);
    is_on_screen(BASE_OBJECT(self));
}

void cyberspace_warp_wait_blink(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.misc_33.timer != 0) {
        if ((self->on_screen ^= 1) != 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        }
        self->ext.misc_33.timer--;
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

#define STEP(value)       \
    {                     \
        .packed = (value) \
    }

union AnimationStep cyberspace_warp_anim_0[24] = {
    STEP(0x00010003),
    STEP(0x01010003),
    STEP(0x03010003),
    STEP(0x05010003),
    STEP(0x07010003),
    STEP(0x09010003),
    STEP(0x0B010003),
    STEP(0x0D010003),
    STEP(0x0F010003),
    STEP(0x11010003),
    STEP(0x13010003),
    STEP(0x15010003),
    STEP(0x17010003),
    STEP(0x19010003),
    STEP(0x1B010003),
    STEP(0x1D010003),
    STEP(0x1F010003),
    STEP(0x21010003),
    STEP(0x23010003),
    STEP(0x25010003),
    STEP(0x27010003),
    STEP(0x29010003),
    STEP(0x2B010003),
    STEP(0x2D000003),
};

union AnimationStep cyberspace_warp_anim_1[24] = {
    STEP(0x00010003),
    STEP(0x02010003),
    STEP(0x04010003),
    STEP(0x06010003),
    STEP(0x08010003),
    STEP(0x0A010003),
    STEP(0x0C010003),
    STEP(0x0E010003),
    STEP(0x10010003),
    STEP(0x12010003),
    STEP(0x14010003),
    STEP(0x16010003),
    STEP(0x18010003),
    STEP(0x1A010003),
    STEP(0x1C010003),
    STEP(0x1E010003),
    STEP(0x20010003),
    STEP(0x22010003),
    STEP(0x24010003),
    STEP(0x26010003),
    STEP(0x28010003),
    STEP(0x2A010003),
    STEP(0x2C010003),
    STEP(0x2E000003),
};

union AnimationStep cyberspace_warp_anim_2[1] = { STEP(0x2F000008) };
union AnimationStep cyberspace_warp_anim_3[1] = { STEP(0x30000008) };
union AnimationStep cyberspace_warp_anim_4[1] = { STEP(0x31000008) };

union AnimationStep* cyberspace_warp_animations[5] = {
    cyberspace_warp_anim_0,
    cyberspace_warp_anim_1,
    cyberspace_warp_anim_2,
    cyberspace_warp_anim_3,
    cyberspace_warp_anim_4,
};

#undef STEP

struct Misc33Position {
    s16 x;
    s16 y;
};

struct Misc33Position cyberspace_warp_positions[6] = {
    { 0x778, 0x60 },
    { 0x378, 0x360 },
    { 0x878, 0x260 },
    { 0x378, 0x360 },
    { 0xC78, 0x560 },
    { 0x378, 0x360 },
};

struct Misc33Position cyberspace_warp_exit_position = { 0xFF0, 0x290 };

void (*cyberspace_warp_state_funcs[3])(struct MiscObj*) = {
    func_800CE388,
    cyberspace_warp_main,
    cyberspace_warp_despawn,
};

void (*cyberspace_warp_main_funcs[2])(struct MiscObj*) = {
    cyberspace_warp_fade,
    cyberspace_warp_wait,
};

void (*cyberspace_warp_wait_funcs[2])(struct MiscObj*) = {
    cyberspace_warp_wait_start,
    cyberspace_warp_wait_blink,
};
