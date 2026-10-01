// MiscObj, misc_object_update_funcs[32]
// 800CE114..800CE340
#include "common.h"

// option_sprite_init
INCLUDE_ASM("main/nonmatchings/misc/misc_32_option_sprite", func_800CE114);

// option_sprite_animate
void func_800CE1D4(struct MiscObj* self)
{
    if (self->ext.misc_8.timer == 0) {
        if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
            || ((controller_input.pressed & PADstart) && (game_info.unk0 == 0xA))) {
            self->unk2 = -1;
        }
        if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
            || ((controller_input.pressed & PADstart) && (game_info.unk0 == 8))) {
            self->unk2 = -1;
        }
    }

    if (self->unk2 != -1 && (u8)self->ext.misc_5.animation != main_bss_state.transition.selection) {
        self->y_pos.i.hi = ((u8*)self->ext.misc_5.owner)[main_bss_state.transition.selection * 2 + 2] + 8;
        self->ext.misc_5.animation = main_bss_state.transition.selection;
    }

    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void option_sprite_update(struct MiscObj* self)
{
    self->on_screen = 0;
    option_sprite_state_funcs[self->state](self);
}

void (*option_sprite_state_funcs[2])(struct MiscObj*) = {
    func_800CE114,
    func_800CE1D4,
};
