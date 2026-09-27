// MiscObj, misc_object_update_funcs[49]
// 800D1990..800D1B44
#include "common.h"

// double_afterimage_init
INCLUDE_ASM("main/nonmatchings/misc/misc_49", func_800D1990);

// double_afterimage_fade
INCLUDE_ASM("main/nonmatchings/misc/misc_49", func_800D1A48);

void double_afterimage_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void double_afterimage_update(struct MiscObj* self)
{
    double_afterimage_state_funcs[self->state](self);
}

u8 D_8010F1DC[4] = { 4, 12, 16, 31 };

void (*double_afterimage_state_funcs[3])(struct MiscObj*) = {
    func_800D1990,
    func_800D1A48,
    double_afterimage_despawn,
};
