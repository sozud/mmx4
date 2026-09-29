// MiscObj, misc_object_update_funcs[25]
// 800CC460..800CC7BC
#include "common.h"

void sentry_flash_update(struct MiscObj* self)
{
    struct ObjectHeader* owner;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    owner = OBJECT_HEADER(self->ext.unk.unk50);
    if (owner->active != 0x41) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else if (owner->id != 0x30) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        sentry_flash_state_funcs[self->state](self);
    }
}

// sentry_flash_init
INCLUDE_ASM("main/nonmatchings/misc/misc_25_sentry_flash", func_800CC4E0);

void sentry_flash_animate(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x10);
        if (self->animation_step.fields.relative_step != 0) {
            return;
        }
    }
    self->state++;
}

void sentry_flash_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

struct Misc25Velocity {
    s8 x;
    s8 y;
};

struct Misc25Velocity sentry_flash_offsets[8] = {
    { -13, 0 },
    { 13, 0 },
    { -10, -12 },
    { 10, -12 },
    { 0, -16 },
    { 0, 16 },
    { -10, 12 },
    { 10, 12 },
};

void (*sentry_flash_state_funcs[3])(struct MiscObj*) = {
    func_800CC4E0,
    sentry_flash_animate,
    sentry_flash_despawn,
};
