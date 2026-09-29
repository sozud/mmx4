// MiscObj, misc_object_update_funcs[23]
// 800CBD40..800CBECC
#include "common.h"

void explosion_puff_update(struct MiscObj* self)
{
    if (self->state == 0) {
        explosion_puff_init(self);
    } else {
        explosion_puff_animate(self);
    }
}

void explosion_puff_init(struct MiscObj* self)
{
    self->on_screen = 1;
    self->unk38 = 0;
    self->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[2];
    self->animation_table = explosion_animations;
    self->unk40 = 0;
    if (self->ext.unk.unk54 != 2) {
        self->unk42 = 0x7805;
    } else {
        self->unk42 = 0x7806;
    }
    if (self->unk7 == 0) {
        self->unk16 = 1;
    }
    set_animation(self, self->ext.unk.unk54);
    self->state++;
    self->unk7 = get_random() & 1;
    is_on_screen(self);
}

void explosion_puff_animate(struct MiscObj* self)
{
    move_object((struct MovingObj*)self);
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->x_vel.val = 0;
        self->y_vel.val = 0;
        self->ext.unk.unk54 = 0;
        ZeroObjectState(self);
    } else {
        self->on_screen = 0;
        if (((self->ext.unk.unk54 & 3) && !(self->ext.unk.unk54 & 1)) || (D_80141BD8.unk0 & 1) == self->unk7) {
            is_on_screen(self);
        }
    }
}

u32 explosion_anim_0[7] = {
    0x12010002,
    0x13010002,
    0x14010002,
    0x15010003,
    0x16010004,
    0x17010005,
    0x18000106,
};

u32 explosion_anim_1[8] = {
    0x19010004,
    0x1A010004,
    0x1B010004,
    0x1C010005,
    0x1D010006,
    0x1E010007,
    0x1F010007,
    0x20000107,
};

u32 explosion_anim_2[17] = {
    0x02010002,
    0x03010002,
    0x04010002,
    0x05010002,
    0x06010002,
    0x07010002,
    0x08010002,
    0x09010002,
    0x0A010002,
    0x0B010002,
    0x0C010002,
    0x0D010003,
    0x0E010003,
    0x0F010004,
    0x10010005,
    0x11010006,
    0x11000160,
};

u32* explosion_animations[3] = {
    explosion_anim_0,
    explosion_anim_1,
    explosion_anim_2,
};
