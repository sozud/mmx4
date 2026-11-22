// MiscObj, misc_object_update_funcs[9]
// 800C9D64..800C9EAC
#include "common.h"
#include "main/misc/misc_09_owner_fx.h"
#include "main/55C4.h"
#include "main/objects.h"

void owner_fx_init(struct MiscObj*);
void owner_fx_animate(struct MiscObj*);
#include "weapon_resources.h"

void owner_fx_update(struct MiscObj* self)
{
    if (self->state == 0) {
        owner_fx_init(self);
    } else {
        owner_fx_animate(self);
    }
}

void owner_fx_init(struct MiscObj* self)
{
    self->on_screen = 1;
    self->unk3C = (void*)self->ext.misc_9.owner->sprite_frames;
    self->animation_table = (u32**)self->ext.misc_9.owner->animation_table;
    self->unk40 = self->ext.misc_9.owner->unk40;
    self->unk42 = self->ext.misc_9.owner->unk42 & 0x7FFF;
    self->unk16 = VISUAL_SATURN_LAYER(5);
#ifndef VERSION_DEMO
    self->bg_offset = (s8)(u8)self->ext.misc_9.owner->bg_offset;
#endif
    set_animation(self, self->unk2);
    self->state++;
    is_on_screen(BASE_OBJECT(self));
}

#ifdef VERSION_DEMO
#define OWNER_FX_DESPAWN despawn_object_permanently
#else
#define OWNER_FX_DESPAWN ZeroObjectState
#endif

void owner_fx_animate(struct MiscObj* self)
{
    u8 on_screen;

    if (self->ext.misc_9.owner->ext.packed == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
        if (self->animation_step.fields.event == 1) {
            OWNER_FX_DESPAWN(OBJECT_HEADER(self));
        }
    } else {
        OWNER_FX_DESPAWN(OBJECT_HEADER(self));
    }
}
