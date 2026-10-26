// MiscObj, misc_object_update_funcs[31]
// 800CDE44..800CE114
#include "common.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/misc/option_toggle_funcs.h"
#include "main/menu.h"
#include "main/objects.h"
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#include "saturn/game_low.h"
#define OPTION_PAD_PRESSED saturn_pad_pressed
#define OPTION_PAD_CANCEL SATURN_PAD_CANCEL
#define OPTION_PAD_START SATURN_PAD_START
#define OPTION_TOGGLE_VALUE saturn_sound_output
#define OPTION_TOGGLE_FRAME_SET 0x57
#define OPTION_TOGGLE_FRAME_CLEAR 0x56
#define OPTION_TOGGLE_TITLE_PALETTE SATURN_OPTION_TITLE_PALETTE
#define OPTION_TOGGLE_SELECTED_PALETTE SATURN_OPTION_SELECTED_PALETTE
#define OPTION_TOGGLE_LOCKED_PALETTE SATURN_OPTION_LOCKED_PALETTE
#define OPTION_TOGGLE_PALETTE SATURN_OPTION_PALETTE
#else
#define OPTION_PAD_PRESSED controller_input.pressed
#define OPTION_PAD_CANCEL PAD_SELECTION_ALT
#define OPTION_PAD_START PADstart
#define OPTION_TOGGLE_VALUE D_80171EA9
#define OPTION_TOGGLE_FRAME_SET 0x56
#define OPTION_TOGGLE_FRAME_CLEAR 0x57
#define OPTION_TOGGLE_TITLE_PALETTE 0x7802
#define OPTION_TOGGLE_SELECTED_PALETTE 0x7803
#define OPTION_TOGGLE_LOCKED_PALETTE 0x7804
#define OPTION_TOGGLE_PALETTE 0x7800
#endif

// option_toggle_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static u16 misc_31_palette(struct MiscObj* arg0);
void func_800CDE44(struct MiscObj* arg0);
static u16 misc_31_palette(struct MiscObj* arg0)
{
    return arg0->unk2 == 3 && D_800F1D90.save.character == 0xFF ? OPTION_TOGGLE_LOCKED_PALETTE : OPTION_TOGGLE_PALETTE;
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_31_option_toggle", func_800CDE44);
#else
void func_800CDE44(struct MiscObj* arg0)
{

#ifdef MMX4_SATURN
    arg0->unk40 = SATURN_OPTION_WINDOW_TEXTURE;
    arg0->unk3C = SATURN_OPTION_WINDOW_FRAMES;
    arg0->bg_offset = -1;
#else
    arg0->unk40 = 0x1F00;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[0];
    arg0->bg_offset = -1;
#endif
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10)
        arg0->unk42 = OPTION_TOGGLE_TITLE_PALETTE;
    else if (arg0->unk2 == 3 && D_800F1D90.save.character == 0xFF)
        arg0->unk42 = OPTION_TOGGLE_LOCKED_PALETTE;
    else
        arg0->unk42 = OPTION_TOGGLE_PALETTE;
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0x10;
    if ((u8)(arg0->unk2 - 0x56) < 2) {
        arg0->state += 2;
        arg0->ext.misc_31.animation = OPTION_TOGGLE_VALUE;
        if (OPTION_TOGGLE_VALUE != 0)
            arg0->animation_step.fields.frame_index = OPTION_TOGGLE_FRAME_SET;
        else
            arg0->animation_step.fields.frame_index = OPTION_TOGGLE_FRAME_CLEAR;
    } else {
        arg0->state++;
        arg0->animation_step.fields.frame_index = arg0->unk2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}
#endif

// option_toggle_appear
void func_800CDF4C(struct MiscObj* self)
{
    if (self->y_pos.i.hi != 0x10) {
        if (self->ext.misc_31.timer == 0) {
            if ((self->unk2 == -1) || (OPTION_PAD_PRESSED & OPTION_PAD_CANCEL)
                || ((OPTION_PAD_PRESSED & OPTION_PAD_START) && (game_info.unk0 == 0xA))) {
                self->unk2 = -1;
            }
            if ((self->unk2 == -1) || (OPTION_PAD_PRESSED & OPTION_PAD_CANCEL)
                || ((OPTION_PAD_PRESSED & OPTION_PAD_START) && (game_info.unk0 == 8))) {
                self->unk2 = -1;
            }
            if (self->unk2 == -1) {
                is_on_screen(BASE_OBJECT(self));
                return;
            }
        }
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = OPTION_TOGGLE_SELECTED_PALETTE;
        } else if ((self->unk2 == 3) && (D_800F1D90.save.character == 0xFF)) {
            self->unk42 = OPTION_TOGGLE_LOCKED_PALETTE;
        } else {
            self->unk42 = OPTION_TOGGLE_PALETTE;
        }
    }

    is_on_screen(BASE_OBJECT(self));
}

void option_toggle_refresh(struct MiscObj* self)
{
#ifdef MMX4_WIN32
    if (EASY_MODE != 0) {
        self->animation_step.fields.frame_index = 0x56;
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->animation_step.fields.frame_index = 0x57;
#else
    if (OPTION_TOGGLE_VALUE != self->ext.misc_31.animation) {
        if (OPTION_TOGGLE_VALUE != 0) {
            self->animation_step.fields.frame_index = OPTION_TOGGLE_FRAME_SET;
        } else {
            self->animation_step.fields.frame_index = OPTION_TOGGLE_FRAME_CLEAR;
        }
        self->ext.misc_31.animation = OPTION_TOGGLE_VALUE;
    }
#endif
    is_on_screen(BASE_OBJECT(self));
}

void option_toggle_update(struct MiscObj* self)
{
    self->on_screen = 0;
    option_toggle_state_funcs[self->state](self);
}

extern void (*option_toggle_state_funcs[3])(struct MiscObj*);

union AnimationStep option_toggle_anim_0[36] = {
    { 15, 0, 1, 0x31 },
    { 13, 0, 1, 0x32 },
    { 10, 0, 1, 0x33 },
    { 8, 0, 1, 0x31 },
    { 7, 0, 1, 0x32 },
    { 6, 0, 1, 0x33 },
    { 6, 0, 1, 0x31 },
    { 5, 0, 1, 0x32 },
    { 5, 0, 1, 0x33 },
    { 4, 0, 1, 0x31 },
    { 5, 0, 1, 0x32 },
    { 5, 0, 1, 0x33 },
    { 6, 0, 1, 0x31 },
    { 6, 0, 1, 0x32 },
    { 7, 0, 1, 0x33 },
    { 8, 0, 1, 0x31 },
    { 10, 0, 1, 0x32 },
    { 13, 0, 1, 0x33 },
    { 15, 0, 1, 0x31 },
    { 13, 0, 1, 0x33 },
    { 10, 0, 1, 0x32 },
    { 8, 0, 1, 0x31 },
    { 7, 0, 1, 0x33 },
    { 6, 0, 1, 0x32 },
    { 6, 0, 1, 0x31 },
    { 5, 0, 1, 0x33 },
    { 5, 0, 1, 0x32 },
    { 4, 0, 1, 0x31 },
    { 5, 0, 1, 0x33 },
    { 5, 0, 1, 0x32 },
    { 6, 0, 1, 0x31 },
    { 6, 0, 1, 0x33 },
    { 7, 0, 1, 0x32 },
    { 8, 0, 1, 0x31 },
    { 10, 0, 1, 0x33 },
    { 13, 0, -35, 0x32 },
};

u32* option_toggle_animations[1] = { (u32*)option_toggle_anim_0 };
