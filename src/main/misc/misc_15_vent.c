// MiscObj, misc_object_update_funcs[15]
// 800CA86C..800CAC18
#include "common.h"

// vent_init
INCLUDE_ASM("main/nonmatchings/misc/misc_15_vent", func_800CA86C);

void vent_animate(struct MiscObj* self)
{
    u8 value;

    self->on_screen = 0;
    if (self->unk2 == 0) {
        value = self->unk6;
        self->unk6 = value + 1;
        if (!(value & 1)) {
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void vent_update(struct MiscObj* self)
{
    vent_state_funcs[self->state](self);
}

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

union AnimationStep vent_anim_0[4] = {
    { .packed = 0x00010006 },
    { .packed = 0x01010006 },
    { .packed = 0x02010005 },
    { .packed = 0x02FD0001 },
};

union AnimationStep vent_anim_1[3] = {
    { .packed = 0x03000001 },
    { .packed = 0x05000001 },
    { .packed = 0x04000001 },
};

union AnimationStep* vent_animations[2] = { vent_anim_0, vent_anim_1 };

void (*vent_state_funcs[2])(struct MiscObj*) = {
    func_800CA86C,
    vent_animate,
};
