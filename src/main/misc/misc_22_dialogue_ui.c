// MiscObj, misc_object_update_funcs[22]
// 800CBA80..800CBD40
#include "common.h"
#include "main/misc/misc_22_dialogue_ui.h"
#include "main/55C4.h"
#include "main/objects.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#endif

// misc obj update #22
void dialogue_ui_update(struct MiscObj* self)
{
    u8* ptr;

    switch (self->unk2) {
    case 0:
        is_on_screen(self);
        return;
    case 1:
#ifdef MMX4_SATURN
        if ((saturn_pad_pressed & SATURN_PAD_DIALOGUE_SKIP) == 0) {
#else
        if ((u8)controller_input.pressed == 0) {
#endif
            if (--self->ext.unk.unk56.sht == 0) {
                self->ext.unk.unk56.sht = 0x20;
                self->ext.unk.unk54 ^= 1;
            }
            if (!self->ext.unk.unk54) {
                is_on_screen(self);
                return;
            }
            self->on_screen = 0;
            return;
        }
        ZeroObjectState(self);
        return;
    case 2:
        if (abc_object.unkC != 0) {
            if (abc_object.unkD == 0 || abc_object.unkD == 4) {
                animate_object(self);
            }
            is_on_screen(self);
            return;
        }
        ZeroObjectState(self);
        return;
    case 3:
        ptr = abc_object.unkE + &self->ext.unk.unk50->unk0;
        if (*ptr != 0 && (abc_object.unkC == 1)) {
            if (self->ext.unk.unk55 == 0) {
                set_animation(self, 1);
                self->ext.unk.unk55 = 1;
            } else {
                animate_object(self);
                if (self->animation_step.fields.event != 0) {
                    self->ext.unk.unk55 = 0;
                }
            }
        } else if (self->ext.unk.unk55 != 0) {
            animate_object(self);
            if (self->animation_step.fields.event != 0) {
                self->ext.unk.unk55 = 0;
                set_animation(self, 0);
            }
        } else {
            set_animation(self, 0);
        }
        is_on_screen(self);
        return;
    case 4:
        animate_object(self);
        is_on_screen(self);
        return;
    case 5:
        ptr = abc_object.unkE + &self->ext.unk.unk50->unk0;
        if ((*ptr == 0) && (abc_object.unkC == 1)) {
            if (self->ext.unk.unk55 == 0) {
                set_animation(self, self->ext.unk.unk54 + 1);
                self->ext.unk.unk55 = 1;
            } else {
                animate_object(self);
                if (self->animation_step.fields.event != 0) {
                    self->ext.unk.unk55 = 0;
                }
            }
        } else if (self->ext.unk.unk55) {
            animate_object(self);
            if (self->animation_step.fields.event != 0) {
                self->ext.unk.unk55 = 0;
                set_animation(self, self->ext.unk.unk54);
            }
        } else {
            set_animation(self, self->ext.unk.unk54);
        }
        is_on_screen(self);
        return;
#ifdef MMX4_SATURN
    case 6:
        if (self->unk6 == 0) {
            self->unk6 = 1;
            self->unk40 = SATURN_OPTION_WINDOW_TEXTURE;
            self->unk3C = SATURN_OPTION_WINDOW_FRAMES;
            self->bg_offset = -1;
            self->unk15 = 0;
            if (self->y_pos.i.hi == SATURN_OPTION_TITLE_Y) {
                self->unk42 = SATURN_OPTION_TITLE_PALETTE;
            } else if (self->unk7 == 0) {
                self->unk42 = SATURN_OPTION_SELECTED_PALETTE;
            } else if ((u8)self->unk7 == SATURN_OPTION_BACK_ROW) {
                self->unk42 = SATURN_OPTION_LOCKED_PALETTE;
            } else {
                self->unk42 = SATURN_OPTION_PALETTE;
            }
            self->x_pos.i.hi = 0xA0;
            self->unk16 = 0x10;
        }
        if (main_bss_state.transition.selection == (u8)self->unk7) {
            self->unk42 = SATURN_OPTION_SELECTED_PALETTE;
        } else if (self->y_pos.i.hi != SATURN_OPTION_TITLE_Y) {
            if ((u8)self->unk7 == SATURN_OPTION_BACK_ROW) {
                self->unk42 = SATURN_OPTION_LOCKED_PALETTE;
            } else {
                self->unk42 = SATURN_OPTION_PALETTE;
            }
        }
        if ((u8)self->unk7 == SATURN_OPTION_EMPTY_ROW) {
            if (saturn_save_slots[(s8)(main_bss_state.transition.selection * SATURN_SAVE_SLOT_BYTES)] == SATURN_SAVE_SLOT_HIDDEN) {
                is_on_screen(self);
            }
            return;
        }
        is_on_screen(self);
        return;
    case 7:
        if (self->unk6 == 0) {
            self->unk6 = 1;
            self->unk40 = SATURN_OPTION_CURSOR_TEXTURE;
            self->unk42 = 7;
            self->unk3C = (s8*)SATURN_OPTION_CURSOR_FRAMES + *(s32*)SATURN_OPTION_CURSOR_FRAMES;
            self->unk16 = 0x13;
            self->bg_offset = -1;
            self->unk15 = 0;
            self->animation_step.fields.frame_index = 42;
        }
        if (self->unk6 == 1) {
            if (main_bss_state.transition.selection != SATURN_OPTION_CURSOR_BACK) {
                is_on_screen(self);
            }
            return;
        }
        if (main_bss_state.transition.selection == SATURN_OPTION_CURSOR_BACK) {
            return;
        }
        if (saturn_save_slots[(s8)(main_bss_state.transition.selection * SATURN_SAVE_SLOT_BYTES)] == SATURN_SAVE_SLOT_HIDDEN) {
            return;
        }
        is_on_screen(self);
        return;
#endif
    case 8:
        if (self->unk5 == 0) {
            animate_object(self);
            if (--self->ext.unk.unk56.byte == 0) {
                self->unk5 = 1;
            }
            if (self->unk6) {
                self->x_pos.val = self->ext.unk.unk50->x_pos.val;
                self->y_pos.val = self->ext.unk.unk50->y_pos.val;
            }
            is_on_screen(self);
            return;
        }
        self->on_screen = 0;
        ZeroObjectState(self);
        return;
    }
}
