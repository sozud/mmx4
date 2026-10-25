// MiscObj, misc_object_update_funcs[16]
// 800CAC18..800CADF8
#include "common.h"
#include "main/misc/misc_16_vent_puff.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/object_motion.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

// vent_puff_state_funcs
extern void (*vent_puff_state_funcs[])(struct MiscObj*);
void vent_puff_init(struct MiscObj*);

void vent_puff_despawn(struct MiscObj*);

void vent_puff_update(struct MiscObj* self)
{
    vent_puff_state_funcs[self->state](self);
}

void vent_puff_init(struct MiscObj* self)
{
    u16 timer = self->ext.misc_16.timer;

    if (timer != 0) {
        self->ext.misc_16.timer = timer - 1;
        return;
    }

    self->unk15 = 0;
    self->state = 1;
    self->unk6 = 0;
    self->bg_offset = 0;

    if (self->unk2 == 0) {
        self->y_vel.val = FIXED(-0.625);
        self->x_vel.val = FIXED(-0.25);
        set_animation(self, 0x19);
    } else {
        self->y_vel.val = FIXED(-1.25);
        self->x_vel.val = FIXED(-0.5);
        set_animation(self, 0x1A);
    }

    self->unk2C = 0;
    self->unk28 = 0;
}

// vent_puff_rise

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CACF0(struct MiscObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_16_vent_puff", func_800CACF0);
#else
void func_800CACF0(struct MiscObj* arg0)
{
    s16 limit;

    if (arg0->unk5 == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        move_with_gravity(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        limit = engine_obj.stage != 0xC ? 0x5D0 : 0x6D0;
        if (arg0->y_pos.i.hi >= limit) {
            arg0->unk5 = 1;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            arg0->ext.misc_16.timer = 0x14;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (--arg0->ext.misc_16.timer == 0) {
        arg0->state = 2;
        return;
    }
    arg0->on_screen = 0;
    if (arg0->ext.misc_16.timer & 1)
        is_on_screen(BASE_OBJECT(arg0));
}
#endif

void vent_puff_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*vent_puff_state_funcs[3])(struct MiscObj*) = {
    vent_puff_init,
    func_800CACF0,
    vent_puff_despawn,
};
