// UnkObj, unk_object_update_funcs[1]
// 800D3964..800D3AC0
#include "common.h"

void menu_label_init(struct UnkObj* self)
{
    s16 var_v0;
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    self->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    self->bg_offset = -1;
    self->unk3C = temp_v1 + (s32)addr_801F3000;
    self->unk15 = 0;
    if (self->y_pos.i.hi == 0x10) {
        self->unk42 = 0x7802;
    } else {
        self->unk42 = 0x7800;
    }
    self->x_pos.i.hi = 0xA0;
    self->unk16 = 0;
    self->animation_step.fields.frame_index = self->unk2;
    self->state++;
    is_on_screen(self);
}

void menu_label_highlight(struct UnkObj* self)
{
    s8 temp_v1; // probably fake

    if (self->y_pos.i.hi != 0x10) {
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = 0x7803;
        } else {
            self->unk42 = 0x7800;
        }
    }
    if ((main_bss_state.character_mode == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        temp_v1 = self->unk7;
        if ((self->unk7 < 7) && (temp_v1 >= 5)) {
            self->unk42 = 0x7804;
        }
    }
    is_on_screen(self);
}

void menu_label_update(struct UnkObj* self)
{
    self->on_screen = 0;
    menu_label_state_funcs[self->state](self);
}

void (*menu_label_state_funcs[2])(struct UnkObj*) = {
    menu_label_init,
    menu_label_highlight,
};
