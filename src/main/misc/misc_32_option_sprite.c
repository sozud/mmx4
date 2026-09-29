// MiscObj, misc_object_update_funcs[32]
// 800CE114..800CE340
#include "common.h"

// option_sprite_init
INCLUDE_ASM("main/nonmatchings/misc/misc_32_option_sprite", func_800CE114);

// option_sprite_animate
INCLUDE_ASM("main/nonmatchings/misc/misc_32_option_sprite", func_800CE1D4);

void option_sprite_update(struct MiscObj* self)
{
    self->on_screen = 0;
    option_sprite_state_funcs[self->state](self);
}

void (*option_sprite_state_funcs[2])(struct MiscObj*) = {
    func_800CE114,
    func_800CE1D4,
};
