// MiscObj, misc_object_update_funcs[22]
// 800CBA80..800CBD40
#include "common.h"

// misc obj update #22
void dialogue_ui_update(struct MiscObj* self)
{
    u8* ptr;

    switch (self->unk2) {
    case 0:
        is_on_screen(self);
        return;
    case 1:
        if ((u8)controller_state == 0) {
            if (--self->ext.unk.unk56.sht == 0) {
                self->ext.unk.unk56.sht = 0x20;
                self->ext.unk.unk54 ^= 1;
            }
            if (self->ext.unk.unk54) {
                self->on_screen = 0;
                return;
            }
            is_on_screen(self);
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
