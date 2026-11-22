// UnkObj, unk_object_update_funcs[0]
// 800D354C..800D3964
#include "common.h"
#include "main/unks/unk_00_menu_text.h"
#include "main/55C4.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/objects.h"
#include "main/2824.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#define MENU_TEXT_LABEL_TEXTURE SATURN_OPTION_WINDOW_TEXTURE
#define MENU_TEXT_CURSOR_TEXTURE SATURN_OPTION_CURSOR_TEXTURE
#define MENU_TEXT_TITLE_PALETTE SATURN_OPTION_TITLE_PALETTE
#define MENU_TEXT_SELECTED_PALETTE SATURN_OPTION_SELECTED_PALETTE
#define MENU_TEXT_LOCKED_PALETTE SATURN_OPTION_LOCKED_PALETTE
#define MENU_TEXT_PALETTE SATURN_OPTION_PALETTE
#define MENU_TEXT_CURSOR_PALETTE SATURN_OPTION_CURSOR_PALETTE
#define MENU_TEXT_HINT_PALETTE SATURN_OPTION_HINT_PALETTE
#else
#define MENU_TEXT_LABEL_TEXTURE 0x1F00
#define MENU_TEXT_CURSOR_TEXTURE 0x1E00
#define MENU_TEXT_TITLE_PALETTE 0x7802
#define MENU_TEXT_SELECTED_PALETTE 0x7803
#define MENU_TEXT_LOCKED_PALETTE 0x7804
#define MENU_TEXT_PALETTE 0x7800
#define MENU_TEXT_CURSOR_PALETTE 0x7806
#define MENU_TEXT_HINT_PALETTE 0x784B
#endif

extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];

#ifndef VERSION_DEMO
void menu_text_init_label(struct UnkObj* self)
{
#ifndef MMX4_SATURN
    s32* addr_801F3000 = (s32*)WINDOW_ARCHIVE_DATA;
    s32 temp_v1;
#endif

    self->unk40 = MENU_TEXT_LABEL_TEXTURE;
#ifndef MMX4_SATURN
    temp_v1 = *addr_801F3000;
#endif
    self->bg_offset = -1;
    self->unk15 = 0;
#if defined(MMX4_SATURN)
    self->unk3C = SATURN_OPTION_WINDOW_FRAMES;
#elif defined(MMX4_PC)
    self->unk3C = (u8*)addr_801F3000 + temp_v1;
#else
    self->unk3C = (void*)(temp_v1 + (s32)addr_801F3000);
#endif
    if (self->y_pos.i.hi == 0x10) {
        self->unk42 = MENU_TEXT_TITLE_PALETTE;
    } else {
        self->unk42 = MENU_TEXT_PALETTE;
    }
    self->x_pos.i.hi = 0xA0;
    self->unk16 = 0;
    self->animation_step.fields.frame_index = self->unk2;
    self->state++;
    if (self->unk2 < 9) {
        self->state++;
    }
}
#endif

#ifndef VERSION_DEMO
void menu_text_init_cursor(struct UnkObj* self)
{
#ifndef MMX4_SATURN
    s32* addr_801F3000 = (s32*)WINDOW_ARCHIVE_DATA;
#endif
    s32* addr_801F3008;

    self->unk40 = MENU_TEXT_CURSOR_TEXTURE;
    self->animation_table = option_toggle_animations;
#if defined(MMX4_SATURN)
    self->unk3C = (s8*)SATURN_OPTION_CURSOR_FRAMES + *(s32*)SATURN_OPTION_CURSOR_FRAMES;
#elif defined(MMX4_PC)
    self->unk3C = (u8*)addr_801F3000 + addr_801F3000[2];
#else
    self->unk3C = (void*)((*((s32*)0x801F3008)) + (s32)addr_801F3000);
#endif
    self->unk15 = 0;
    self->bg_offset = -1;
    if (self->unk2 == -1) {
        self->unk42 = MENU_TEXT_CURSOR_PALETTE;
        self->y_pos.i.hi = self->link.data[main_bss_state.transition.selection * 2] + 8;
        self->ext.unk_0.selection_index = main_bss_state.transition.selection;
        set_animation(self, 0);
    } else {
        self->unk42 = MENU_TEXT_HINT_PALETTE;
        self->x_pos.i.hi = 0x60;
        self->y_pos.i.hi = 0xD0;
        self->animation_step.fields.frame_index = 0x29;
    }
    self->unk16 = 0;
    self->state = 3;
}
#endif

#ifdef VERSION_DEMO
void menu_text_init(struct UnkObj* self)
{
    if (self->ext.unk_0.selection_index != main_bss_state.transition.selection) {
        self->y_pos.i.hi = self->link.value + main_bss_state.transition.selection * 2;
        self->ext.unk_0.selection_index = main_bss_state.transition.selection;
    }
    animate_object(self);
    is_on_screen(self);
}
#else
void menu_text_init(struct UnkObj* self)
{
    if (self->unk2 < 0) {
        menu_text_init_cursor(self);
    } else {
        menu_text_init_label(self);
    }
    is_on_screen(self);
}
#endif

#ifndef VERSION_DEMO
void menu_text_highlight(struct UnkObj* self)
{
#ifdef MMX4_WIN32
    if (self->y_pos.i.hi != 0x10 && self->y_pos.i.hi != 1) {
#else
    if (0x10 != self->y_pos.i.hi) {
#endif
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = MENU_TEXT_SELECTED_PALETTE;
        } else {
            self->unk42 = MENU_TEXT_PALETTE;
        }
    }
    if ((main_bss_state.character_mode == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        switch (self->unk7) {
        case 5:
        case 6:
            self->unk42 = MENU_TEXT_LOCKED_PALETTE;
            break;
        }
    }
    is_on_screen(self);
}
#endif

// menu_text_blink

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D3798(struct UnkObj* self);
#endif

#ifndef VERSION_DEMO
void func_800D3798(struct UnkObj* self)
{
    u16 mask;
    u16 key;
    u32 i;
    s32 bit;
    u8 button;

    mask = menu_button_bits_a[self->unk2];
    for (i = 0; (u8)i < 16; i++) {
        if ((1 << i) == mask) {
            bit = (u8)i;
            break;
        }
    }
    key = D_800EE430[bit];
    for (button = 0; button < 8; button++) {
        if (key == menu_button_bits_b[button]) {
            self->animation_step.fields.frame_index = button + 0x68;
            break;
        }
    }
    self->unk42 = MENU_TEXT_PALETTE;
    if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && self->unk2 < 7) {
        if (self->unk2 >= 5)
            self->unk42 = MENU_TEXT_LOCKED_PALETTE;
    }
    is_on_screen(self);
}
#endif

#ifndef VERSION_DEMO
void menu_text_cursor(struct UnkObj* self)
{
    if (self->unk2 == -1) {
        if (self->ext.unk_0.selection_index != main_bss_state.transition.selection) {
            self->y_pos.i.hi = self->link.data[main_bss_state.transition.selection * 2] + 8;
            self->ext.unk_0.selection_index = main_bss_state.transition.selection;
        }
        animate_object(self);
    }
    is_on_screen(self);
}
#endif

// menu_text_state_funcs
extern void (*menu_text_state_funcs[])(struct UnkObj*);

void menu_text_update(struct UnkObj* arg0)
{
    arg0->on_screen = 0;
    menu_text_state_funcs[arg0->state](arg0);
}

#ifdef MMX4_SATURN
#ifdef VERSION_DEMO
extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
#else
#ifdef VERSION_DEMO
extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
#else
u16 menu_button_bits_a[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0x400 };

u16 menu_button_bits_b[8] = { 0x400, 0x100, 0x200, 0x40, 0x20, 0x10, 0x80, 0x08 };
#endif
#endif
#else
#ifdef VERSION_DEMO
extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
#else
#ifdef VERSION_DEMO
extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
#else
u16 menu_button_bits_a[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0 };

u16 menu_button_bits_b[8] = { 0x80, 0x10, 0x40, 0x20, 4, 1, 8, 2 };
#endif
#endif
#endif

#ifdef VERSION_DEMO
void func_800AE858_demo(struct MiscObj*);

void (*menu_text_state_funcs[2])(struct UnkObj*) = {
    func_800AE858_demo,
    menu_text_init,
};
#else
void (*menu_text_state_funcs[4])(struct UnkObj*) = {
    menu_text_init,
    menu_text_highlight,
    func_800D3798,
    menu_text_cursor,
};
#endif
