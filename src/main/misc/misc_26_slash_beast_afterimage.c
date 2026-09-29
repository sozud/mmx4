// MiscObj, misc_object_update_funcs[26]
// 800CC7BC..800CC908
#include "common.h"

void slash_beast_afterimage_update(struct MiscObj* self)
{
    slash_beast_afterimage_state_funcs[self->state](self);
}

// slash_beast_afterimage_fade
INCLUDE_ASM("main/nonmatchings/misc/misc_26_slash_beast_afterimage", func_800CC7F8);

void slash_beast_afterimage_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*slash_beast_afterimage_state_funcs[])(struct MiscObj*) = {
    func_800CC7F8,
    slash_beast_afterimage_despawn,
};
