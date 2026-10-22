// UnkObj, unk_object_update_funcs[1]
// 800D3964..800D3AC0
#include "common.h"
#include "main/unks/unk_01_menu_label.h"
#include "main/objects.h"
#include "main/55C4.h"

// menu_label_state_funcs
extern void (*menu_label_state_funcs[])(struct UnkObj*);
void menu_label_init(struct UnkObj*);

#ifdef MMX4_SATURN
#define MENU_LABEL_TEXTURE 0xC600
#define MENU_LABEL_FRAMES ((u8*)0x002C6400)
#define MENU_LABEL_PALETTE_NORMAL 0
#define MENU_LABEL_PALETTE_SELECTED 2
#define MENU_LABEL_PALETTE_HEADER 3
#define MENU_LABEL_PALETTE_LOCKED 4

void menu_label_init(struct UnkObj* self)
{
    self->unk40 = MENU_LABEL_TEXTURE;
    self->unk3C = MENU_LABEL_FRAMES;
    self->bg_offset = -1;
    self->unk15 = 0;
    if (self->y_pos.i.hi == 0x10) {
        self->unk42 = MENU_LABEL_PALETTE_HEADER;
    } else {
        self->unk42 = MENU_LABEL_PALETTE_NORMAL;
    }
    self->x_pos.i.hi = 0xA0;
    self->unk16 = 0;
    self->animation_step.fields.frame_index = self->unk2;
    self->state++;
    is_on_screen(self);
}

void menu_label_highlight(struct UnkObj* self)
{
    if (self->y_pos.i.hi != 0x10) {
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = MENU_LABEL_PALETTE_SELECTED;
        } else {
            self->unk42 = MENU_LABEL_PALETTE_NORMAL;
        }
    }
    if ((main_bss_state.character_mode == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        if (self->unk7 == 5 || self->unk7 == 6) {
            self->unk42 = MENU_LABEL_PALETTE_LOCKED;
        }
    }
    is_on_screen(self);
}
#else
void menu_label_init(struct UnkObj* self)
{
    s16 var_v0;
    s32* addr_801F3000 = (s32*)WINDOW_ARCHIVE_DATA;
    s32 temp_v1;

    self->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    self->bg_offset = -1;
#ifdef MMX4_PC
    self->unk3C = (u8*)addr_801F3000 + temp_v1;
#else
    self->unk3C = temp_v1 + (s32)addr_801F3000;
#endif
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

#endif

void menu_label_update(struct UnkObj* self)
{
    self->on_screen = 0;
    menu_label_state_funcs[self->state](self);
}

void (*menu_label_state_funcs[2])(struct UnkObj*) = {
    menu_label_init,
    menu_label_highlight,
};
