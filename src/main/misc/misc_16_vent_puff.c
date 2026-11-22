// MiscObj, misc_object_update_funcs[16]
// 800CA9EC..800CADF8
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

void vent_spawn_mixed_puffs(struct MiscObj* self, u8 count)
{
    struct MiscObj* slot;
    u32 i;

    for (i = 0; i < count; i++) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            continue;
        }
        slot->active = 0x41;
        slot->id = 0x10;
        slot->x_pos.val = self->x_pos.val;
        slot->y_pos.val = self->y_pos.val;
        slot->x_pos.i.hi += get_random() & 0x1F;
        // The bits do not overlap, so both forms give the same value.
        // Keep the original OR (EU) / ADDU (US/JP) instructions for matching.
#ifdef VERSION_EU
        slot->ext.misc_15.unk54 = (get_random() & 7) | (i << 3);
#else
        slot->ext.misc_15.unk54 = (get_random() & 7) + (i << 3);
#endif
        slot->unk2 = get_random() & 1;
        if (i < 3) {
            slot->unk2 = 0;
        } else {
            slot->unk2 = 1;
        }
        slot->animation_table = self->animation_table;
        slot->unk40 = self->unk40;
        slot->unk3C = self->unk3C;
        slot->unk42 = self->unk42 & 0x7FFF;
        slot->unk16 = 3;
        slot->unk15 = self->unk15;
    }
}

void vent_spawn_puffs(struct MiscObj* self, u8 count)
{
    struct MiscObj* slot;
    u32 i;
    u8 puff_variant;

    for (i = 0; i < count; i++) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            continue;
        }
        slot->active = 0x41;
        slot->id = 0x10;
        slot->x_pos.val = self->x_pos.val;
        slot->y_pos.val = self->y_pos.val;
        slot->x_pos.i.hi += get_random() & 0x1F;
        puff_variant = get_random() & 7;
        slot->ext.misc_15.unk54 = puff_variant + (i << 3);
        slot->unk2 = 1;
        slot->animation_table = self->animation_table;
        slot->unk40 = self->unk40;
        slot->unk3C = self->unk3C;
        slot->unk42 = self->unk42 & 0x7FFF;
        slot->unk16 = 3;
        slot->unk15 = self->unk15;
    }
}

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
        limit = DEMO_ALT(engine_obj.stage != 0xC ? 0x5D0 : 0x6D0, 0x5D0);
        if (arg0->y_pos.i.hi >= limit) {
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            arg0->unk5 = 1;
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
    if (BLINK_CLOCK(arg0->ext.misc_16.timer) & 1)
        is_on_screen(BASE_OBJECT(arg0));
}

void vent_puff_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*vent_puff_state_funcs[3])(struct MiscObj*) = {
    vent_puff_init,
    func_800CACF0,
    vent_puff_despawn,
};
