// MiscObj, misc_object_update_funcs[42]
// 800CFE98..800D0374
#include "common.h"

void menu_icon_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    menu_icon_state_funcs[self->state](self);
}

// menu_icon_init
INCLUDE_ASM("main/nonmatchings/misc/misc_42_menu_icon", func_800CFEE0);

// menu_icon_animate
INCLUDE_ASM("main/nonmatchings/misc/misc_42_menu_icon", func_800D0118);

void (*menu_icon_state_funcs[2])(struct MiscObj*) = {
    func_800CFEE0,
    func_800D0118,
};
