// MiscObj, misc_object_update_funcs[23]
// 800CBD40..800CBECC
#include "common.h"
#include "main/misc/misc_23_explosion_puff.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "weapon_resources.h"

void explosion_puff_animate(struct MiscObj* self);
void explosion_puff_init(struct MiscObj* self);

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
    self->unk40 = WEAPON_TEXTURE_BASE;
    if (self->ext.unk.unk54 != 2) {
        self->unk42 = OBJECT_CLUT(0x7805);
    } else {
        self->unk42 = OBJECT_CLUT(0x7806);
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
        if (((self->ext.unk.unk54 & 3) && !(self->ext.unk.unk54 & 1)) || (BLINK_CLOCK(WEAPON_FRAME_COUNTER) & 1) == self->unk7) {
            is_on_screen(self);
        }
    }
}

union AnimationStep explosion_anim_0[7] = {
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 4, 0, 1, 0x16 },
    { 5, 0, 1, 0x17 },
    { 6, 1, 0, 0x18 },
};

union AnimationStep explosion_anim_1[8] = {
    { 4, 0, 1, 0x19 },
    { 4, 0, 1, 0x1A },
    { 4, 0, 1, 0x1B },
    { 5, 0, 1, 0x1C },
    { 6, 0, 1, 0x1D },
    { 7, 0, 1, 0x1E },
    { 7, 0, 1, 0x1F },
    { 7, 1, 0, 0x20 },
};

union AnimationStep explosion_anim_2[17] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 4, 0, 1, 0x0F },
    { 5, 0, 1, 0x10 },
    { 6, 0, 1, 0x11 },
    { 96, 1, 0, 0x11 },
};

u32* explosion_animations[3] = {
    explosion_anim_0,
    explosion_anim_1,
    explosion_anim_2,
};
