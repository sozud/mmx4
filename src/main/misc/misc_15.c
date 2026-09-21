// MiscObj, misc_object_update_funcs[15]
// 800CA86C..800CAC18
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CA86C);

void func_800CA954(struct MiscObj* self)
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
    func_80015DC8(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void func_800CA9B0(struct MiscObj* arg0)
{
    D_8010E678[arg0->state](arg0);
}

void func_800CA9EC(struct MiscObj* arg0, u8 count)
{
    struct MiscObj* slot;
    u32 i;
    u16 t;

    for (i = 0; i < count; i++) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            continue;
        }
        slot->active = 0x41;
        slot->id = 0x10;
        slot->x_pos.val = arg0->x_pos.val;
        slot->y_pos.val = arg0->y_pos.val;
        slot->x_pos.i.hi += get_random() & 0x1F;
        slot->ext.misc_15.unk54 = (get_random() & 7) + (i << 3);
        slot->unk2 = get_random() & 1;
        if (i < 3) {
            slot->unk2 = 0;
        } else {
            slot->unk2 = 1;
        }
        slot->animation_table = arg0->animation_table;
        slot->unk40 = arg0->unk40;
        slot->unk3C = arg0->unk3C;
        t = arg0->unk42;
        slot->unk16 = 3;
        slot->unk42 = t & 0x7FFF;
        slot->unk15 = arg0->unk15;
    }
}

void func_800CAB10(struct MiscObj* arg0, u8 count)
{
    struct MiscObj* slot;
    u32 i;
    u16 t;

    for (i = 0; i < count; i++) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            continue;
        }
        slot->active = 0x41;
        slot->id = 0x10;
        slot->x_pos.val = arg0->x_pos.val;
        slot->y_pos.val = arg0->y_pos.val;
        slot->x_pos.i.hi += get_random() & 0x1F;
        slot->ext.misc_15.unk54 = (get_random() & 7) + (i << 3);
        slot->unk2 = 1;
        slot->animation_table = arg0->animation_table;
        slot->unk40 = arg0->unk40;
        slot->unk3C = arg0->unk3C;
        t = arg0->unk42;
        slot->unk16 = 3;
        slot->unk42 = t & 0x7FFF;
        slot->unk15 = arg0->unk15;
    }
}

union AnimationStep D_8010E654[4] = {
    { .packed = 0x00010006 },
    { .packed = 0x01010006 },
    { .packed = 0x02010005 },
    { .packed = 0x02FD0001 },
};

union AnimationStep D_8010E664[3] = {
    { .packed = 0x03000001 },
    { .packed = 0x05000001 },
    { .packed = 0x04000001 },
};

union AnimationStep* D_8010E670[2] = { D_8010E654, D_8010E664 };

void (*D_8010E678[2])(struct MiscObj*) = {
    func_800CA86C,
    func_800CA954,
};
