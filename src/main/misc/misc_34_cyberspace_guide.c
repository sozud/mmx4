// MiscObj, misc_object_update_funcs[34]
// 800CE894..800CF144
#include "common.h"

void cyberspace_guide_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    cyberspace_guide_state_funcs[self->state](self);
}

// cyberspace_guide_init
INCLUDE_ASM("main/nonmatchings/misc/misc_34_cyberspace_guide", func_800CE8DC);

void cyberspace_guide_main(struct MiscObj* self)
{
    cyberspace_guide_step_funcs[self->unk5](self);
    func_800CEFC0(self);
    cyberspace_guide_update_blink(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state++;
    }
}

void cyberspace_guide_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cyberspace_guide_appear(struct MiscObj* self)
{
    u8 timer;
    animate_object(ANIMATED_OBJECT(self));
    timer = self->ext.unk.unk54 - 1;
    self->ext.unk.unk54 = timer;
    if (timer == 0) {
        self->ext.unk.unk54 = 0x24;
        self->unk5 = 1;
        set_animation(self, 2);
    }
}

void cyberspace_guide_start_timer(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_34.timer == 0) {
        engine_obj.unk10 = 0;
        engine_obj.unk12 = 0;
        engine_obj.unk11 = 0;
        engine_obj.unk13 = 0;
        self->unk5 = 2;
        self->ext.misc_34.enabled = 1;
        set_animation(self, 1);
    }
}

// cyberspace_guide_follow
INCLUDE_ASM("main/nonmatchings/misc/misc_34_cyberspace_guide", func_800CEBC0);

void cyberspace_guide_leave(struct MiscObj* self)
{
    cyberspace_guide_leave_funcs[self->unk6](self);
}

void cyberspace_guide_leave_start(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 4);
    self->y_vel.val = FIXED(1);
    self->ext.misc_34.enabled = 0;
    self->x_vel.val = 0;
    self->ext.misc_34.timer = 0x1E;
    self->unk6++;
}

void cyberspace_guide_leave_drift(struct MiscObj* self)
{
    u8 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = self->ext.misc_34.timer - 1;
    self->ext.misc_34.timer = timer;
    if (timer == 0) {
        self->ext.misc_34.timer = 0x1E;
        self->x_vel.val = FIXED(3);
        self->y_vel.val = 0;
        self->unk28 = FIXED(-0.0625);
        self->unk6++;
    }
}

void cyberspace_guide_leave_finish(struct MiscObj* self)
{
    u8 timer;
    struct EffectObj* related;

    move_with_gravity(ANIMATED_OBJECT(self));
    timer = self->ext.misc_34.timer - 1;
    self->ext.misc_34.timer = timer;
    if (timer == 0) {
        related = self->ext.misc_34.related;
        related->ext.effect_38.active = 1;
        if (!(engine_obj.checkpoint % 2)) {
            related->ext.effect_38.variant = self->ext.misc_34.variant;
        } else {
            related->ext.effect_38.variant = 3;
        }
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

// cyberspace_guide_update_position
INCLUDE_ASM("main/nonmatchings/misc/misc_34_cyberspace_guide", func_800CEFC0);

void cyberspace_guide_update_blink(struct MiscObj* self)
{
    if ((self->unk17 != 1) && (self->unk17 != 4)) {
        if (--self->ext.misc_34.unk5A == 0) {
            if (self->unk17 == 2) {
                set_animation(self, 3);
                self->ext.misc_34.enabled = 0;
                self->ext.misc_34.unk5A = 0x24;
            } else {
                set_animation(self, 1);
                self->ext.misc_34.enabled = 1;
            }
        }
    }
}

#define STEP(value) \
    {               \
        (value)     \
    }

union AnimationStep cyberspace_guide_anim_0[6] = {
    STEP(0x1B010006),
    STEP(0x1C010006),
    STEP(0x1D010006),
    STEP(0x00010006),
    STEP(0x01010006),
    STEP(0x02000006),
};

union AnimationStep cyberspace_guide_anim_1[24] = {
    STEP(0x03010006),
    STEP(0x04010006),
    STEP(0x05010006),
    STEP(0x06010003),
    STEP(0x07010003),
    STEP(0x08010003),
    STEP(0x09010003),
    STEP(0x0A010003),
    STEP(0x0B010003),
    STEP(0x0C010006),
    STEP(0x0D010006),
    STEP(0x0E010006),
    STEP(0x0F010006),
    STEP(0x10010006),
    STEP(0x11010006),
    STEP(0x18010006),
    STEP(0x19010006),
    STEP(0x1A010006),
    STEP(0x12010003),
    STEP(0x13010003),
    STEP(0x14010003),
    STEP(0x15010003),
    STEP(0x16010003),
    STEP(0x17E90003),
};

union AnimationStep cyberspace_guide_anim_2[6] = {
    STEP(0x1E010003),
    STEP(0x1F010003),
    STEP(0x20010003),
    STEP(0x21010003),
    STEP(0x22010003),
    STEP(0x23FB0003),
};

union AnimationStep cyberspace_guide_anim_3[6] = {
    STEP(0x24010003),
    STEP(0x25010003),
    STEP(0x26010003),
    STEP(0x27010003),
    STEP(0x28010003),
    STEP(0x29FB0003),
};

union AnimationStep cyberspace_guide_anim_4[6] = {
    STEP(0x02010006),
    STEP(0x01010006),
    STEP(0x00010006),
    STEP(0x1D010006),
    STEP(0x1C010006),
    STEP(0x1B000006),
};

union AnimationStep* cyberspace_guide_animations[5] = {
    cyberspace_guide_anim_0,
    cyberspace_guide_anim_1,
    cyberspace_guide_anim_2,
    cyberspace_guide_anim_3,
    cyberspace_guide_anim_4,
};

#undef STEP

u8 cyberspace_guide_offsets[12] = {
    0x0F,
    0x0F,
    0,
    0,
    0x12,
    0x11,
    0,
    0,
    0x23,
    0x2C,
    0,
    0,
};

void (*cyberspace_guide_state_funcs[3])(struct MiscObj*) = {
    func_800CE8DC,
    cyberspace_guide_main,
    cyberspace_guide_despawn,
};

void (*cyberspace_guide_step_funcs[4])(struct MiscObj*) = {
    cyberspace_guide_appear,
    cyberspace_guide_start_timer,
    func_800CEBC0,
    cyberspace_guide_leave,
};

void (*cyberspace_guide_leave_funcs[3])(struct MiscObj*) = {
    cyberspace_guide_leave_start,
    cyberspace_guide_leave_drift,
    cyberspace_guide_leave_finish,
};
