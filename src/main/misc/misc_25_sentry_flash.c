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
void func_800CC4E0(struct MiscObj* misc)
{
    struct Misc5Ext* ext = &misc->ext.misc_5;

    misc->on_screen = 1;
    misc->x_vel.val = 0;
    misc->unk28 = 0;
    misc->y_vel.val = 0;
    misc->unk2C = 0;
    misc->unk16 = 0;
    misc->unk40 = ext->owner->unk40;
    misc->unk42 = ext->owner->unk42 & 0x7FFF;
    misc->animation_table = (u32**)ext->owner->animation_table;
    misc->unk3C = ext->owner->sprite_frames;
    misc->unk15 = ext->owner->unk15;
    misc->bg_offset = ext->owner->bg_offset;
    set_animation(misc, 7);
    switch (misc->unk2 & 0xFE) {
    case 2:
    case 4:
    case 6:
        misc->x_pos.i.hi += sentry_flash_offsets[3].x;
        misc->y_pos.i.hi += sentry_flash_offsets[3].y;
        break;
    case 10:
    case 12:
    case 14:
        misc->x_pos.i.hi += sentry_flash_offsets[2].x;
        misc->y_pos.i.hi += sentry_flash_offsets[2].y;
        break;
    case 8:
        misc->x_pos.i.hi += sentry_flash_offsets[4].x;
        misc->y_pos.i.hi += sentry_flash_offsets[4].y;
        break;
    case 18:
    case 20:
    case 22:
        misc->x_pos.i.hi += sentry_flash_offsets[6].x;
        misc->y_pos.i.hi += sentry_flash_offsets[6].y;
        break;
    case 26:
    case 28:
    case 30:
        misc->x_pos.i.hi += sentry_flash_offsets[7].x;
        misc->y_pos.i.hi += sentry_flash_offsets[7].y;
        break;
    case 24:
        misc->x_pos.i.hi += sentry_flash_offsets[5].x;
        misc->y_pos.i.hi += sentry_flash_offsets[5].y;
        break;
    default:
        if (misc->unk15 & 0x40) {
            misc->x_pos.i.hi += sentry_flash_offsets[1].x;
            misc->y_pos.i.hi += sentry_flash_offsets[1].y;
        } else {
            misc->x_pos.i.hi += sentry_flash_offsets[0].x;
            misc->y_pos.i.hi += sentry_flash_offsets[0].y;
        }
        break;
    }
    misc->state++;
}

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
