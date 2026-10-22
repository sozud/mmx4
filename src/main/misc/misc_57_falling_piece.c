// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D3928
#include "common.h"
#include "main/misc/misc_57_falling_piece.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/objects.h"
#include "main/2824.h"

#ifdef MMX4_PC
#include "main/2824.h"
extern void menu_text_init_label(struct UnkObj* arg0);
extern void menu_text_init_cursor(struct UnkObj* arg0);
#endif

// falling_piece_state_funcs
extern void (*falling_piece_state_funcs[])(struct MiscObj*);
void func_800D3388(struct MiscObj*);
void falling_piece_fall(struct MiscObj*);
void falling_piece_despawn(struct MiscObj*);
#include "weapon_resources.h"
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

extern union AnimationStep* menu_text_animations[1];

// falling_piece_init
void func_800D3388(struct MiscObj* self)
{
    self->x_pos.u.hi = background_objects[0].x_pos.u.hi + ((get_random() & 0xFF) + 0x30);
    self->y_pos.u.hi = background_objects[0].y_pos.u.hi - 0x10;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA4));
    self->animation_table = (u32**)menu_text_animations;
    self->unk42 = OBJECT_STAGE_CLUT(0xA4);
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 0x10;
    set_animation_frame(ANIMATED_OBJECT(self), 0, self->unk2);
    self->y_vel.val = 0xFFFE0000;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0x4200;
    self->state++;
}

void falling_piece_fall(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (func_8002B160(self) != 0) {
        self->state = 2;
    }
}

void falling_piece_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void falling_piece_update(struct MiscObj* self)
{
    falling_piece_state_funcs[self->state](self);
}

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
    self->unk3C = temp_v1 + (s32)addr_801F3000;
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
    self->unk3C = (*((s32*)0x801F3008)) + (s32)addr_801F3000;
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

void menu_text_init(struct UnkObj* self)
{
    if (self->unk2 < 0) {
        menu_text_init_cursor(self);
    } else {
        menu_text_init_label(self);
    }
    is_on_screen(self);
}

void menu_text_highlight(struct UnkObj* self)
{
    s8 temp_v1; // probably fake

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
        temp_v1 = self->unk7;
        if ((self->unk7 < 7) && (temp_v1 >= 5)) {
            self->unk42 = MENU_TEXT_LOCKED_PALETTE;
        }
    }
    is_on_screen(self);
}

// menu_text_blink

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D3798(struct UnkObj* self);
// src/main/misc/misc_57_falling_piece.c

extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D3798(struct UnkObj* self)
{
    u16 mask;
    u8 bit, button;
    mask = menu_button_bits_a[self->unk2];

    for (bit = 0; bit < 16; bit++) {
        if (mask == (1U << bit))
            break;
    }
    for (button = 0; button < 8; button++) {
        if (D_800EE430[bit] == menu_button_bits_b[button]) {
            self->animation_step.fields.frame_index = button + 0x68;
            break;
        }
    }
    self->unk42 = MENU_TEXT_PALETTE;
    if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && self->unk2 < 7 && self->unk2 >= 5)
        self->unk42 = MENU_TEXT_LOCKED_PALETTE;
    is_on_screen(self);
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_57_falling_piece", func_800D3798);
#endif

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

union AnimationStep menu_text_anim_0[6] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 0, 0x05 },
};
union AnimationStep* menu_text_animations[1] = { menu_text_anim_0 };

void (*falling_piece_state_funcs[3])(struct MiscObj*) = {
    func_800D3388,
    falling_piece_fall,
    falling_piece_despawn,
};
