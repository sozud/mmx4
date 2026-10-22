// MiscObj, misc_object_update_funcs[32]
// 800CE114..800CE340
#include "common.h"
#include "main/misc/misc_32_option_sprite.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/misc/misc_31_option_toggle.h"
#endif

// option_sprite_state_funcs
extern void (*option_sprite_state_funcs[])(struct MiscObj*);

// option_sprite_init
#ifdef MMX4_PC
void func_800CE114(struct MiscObj* arg0);
#endif

#ifdef MMX4_PC
void func_800CE114(struct MiscObj* arg0)
{
    const u8* rows = (const u8*)arg0->ext.misc_32.owner;

    arg0->unk40 = 0x1E00;
    arg0->animation_table = (u32**)option_toggle_animations;
    arg0->bg_offset = -1;
    arg0->unk42 = 0x7806;
    arg0->unk15 = 0;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
    arg0->x_pos.i.hi += 8;
    arg0->y_pos.i.hi = rows[main_bss_state.transition.selection * 2 + 2] + 8;
    arg0->unk16 = 0x10;
    arg0->state++;
    arg0->ext.misc_32.animation = main_bss_state.transition.selection;
    set_animation(arg0, 0);
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_32_option_sprite", func_800CE114);
#endif

// option_sprite_animate
void func_800CE1D4(struct MiscObj* self)
{
    if (self->ext.misc_32.timer == 0) {
        if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
            || ((controller_input.pressed & PADstart) && (game_info.unk0 == 0xA))) {
            self->unk2 = -1;
        }
        if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
            || ((controller_input.pressed & PADstart) && (game_info.unk0 == 8))) {
            self->unk2 = -1;
        }
    }

    if (self->unk2 != -1 && (u8)self->ext.misc_32.animation != main_bss_state.transition.selection) {
        self->y_pos.i.hi = ((u8*)self->ext.misc_32.owner)[main_bss_state.transition.selection * 2 + 2] + 8;
        self->ext.misc_32.animation = main_bss_state.transition.selection;
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
