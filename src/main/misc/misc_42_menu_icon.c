// MiscObj, misc_object_update_funcs[42]
// 800CFE98..800D0374
#include "common.h"
#include "main/misc/misc_42_menu_icon.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/misc/misc_31_option_toggle.h"

// menu_icon_state_funcs
extern void (*menu_icon_state_funcs[])(struct MiscObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/objects.h"
#endif

#ifdef MMX4_SATURN
void menu_icon_update(struct MiscObj* self)
{
}
#else
void menu_icon_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    menu_icon_state_funcs[self->state](self);
}
#endif

// menu_icon_init

#ifdef MMX4_PC
void func_800CFEE0(struct MiscObj* self);
void func_800D0118(struct MiscObj* self);
#endif

#if defined(VERSION_EU) || defined(MMX4_SATURN)
INCLUDE_ASM("main/nonmatchings/misc/misc_42_menu_icon", func_800CFEE0);
#else
void func_800CFEE0(struct MiscObj* self)
{
    self->active = 1;
    self->on_screen = 1;
    self->unk15 = 0;
    self->bg_offset = -1;
    switch ((s8)self->unk2) {
    case 0:
        self->unk16 = 2;
        self->unk3C = (u8*)WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[0];
        self->unk40 = 0x1F00;
        if (self->y_pos.i.hi == 0x10) {
            self->unk42 = 0x7802;
        } else {
            if (self->ext.misc_42.unk56 == main_bss_state.transition.selection)
                self->unk42 = 0x7803;
            else
                self->unk42 = 0x7800;
        }
        break;
    case 1:
        self->unk16 = VISUAL_SATURN_LAYER(6);
        self->unk40 = 0x1E00;
        self->unk42 = 0x7807;
        self->unk3C = (u8*)WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
        break;
    case 2:
        self->unk15 = PLAYER_FACING_RIGHT;
        self->unk40 = 0x1E00;
        self->unk3C = (u8*)WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
        break;
    case 3:
        self->unk16 = 3;
        self->unk40 = 0x1DE0;
        self->unk3C = (u8*)WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[3];
        break;
    case 4:
        self->unk40 = 0x1E00;
        self->unk3C = (u8*)WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
        self->animation_table = (const u8* const*)option_toggle_animations;
        self->ext.misc_42.unk57 = main_bss_state.transition.selection;
        self->unk16 = 0;
        set_animation(self, 0);
        switch (self->ext.misc_42.unk58) {
        case 0:
            if (memcard_menu.card_status[1] == 0 && memcard_menu.card_status[0] != 0) {
                main_bss_state.transition.selection = 1;
                self->y_pos.i.hi = 0x98;
            } else {
                self->y_pos.i.hi = 0x78;
            }
#ifdef VERSION_JP
            self->x_pos.i.hi = 0x58;
#else
            self->x_pos.i.hi = 0x50;
#endif
            break;
        case 1:
        case 3:
            self->x_pos.i.hi = 0x28;
            self->y_pos.i.hi = 0x78;
            break;
        case 2:
#ifdef VERSION_JP
            self->x_pos.i.hi = 0x80;
            self->y_pos.i.hi = 0x98;
#else
            self->x_pos.i.hi = 0x88;
            self->y_pos.i.hi = 0xB8;
#endif
            break;
        case 4:
            self->x_pos.i.hi = 0x98;
            self->y_pos.i.hi = 0x78;
            break;
        }
        break;
    }
    self->state = 1;
    self->unk6 = 0;
}
#endif

// menu_icon_animate
#if defined(VERSION_EU) || (defined(VERSION_JP) && !defined(MMX4_PC) && !defined(MMX4_SATURN))
INCLUDE_ASM("main/nonmatchings/misc/misc_42_menu_icon", func_800D0118);
#else
void func_800D0118(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
    switch ((s8)self->unk2) {
    case 0:
        if (self->animation_step.fields.frame_index != 0x32 && self->animation_step.fields.frame_index != 8
            && self->animation_step.fields.frame_index != 0x3E && self->animation_step.fields.frame_index != 0x3C
            && self->animation_step.fields.frame_index != 0x3A) {
            if (self->ext.misc_42.unk56 == main_bss_state.transition.selection)
                self->unk42 = 0x7803;
            else
                self->unk42 = 0x7800;
        }
        break;
    case 4:
        if (self->ext.misc_42.unk57 != main_bss_state.transition.selection) {
            switch (self->ext.misc_42.unk56) {
            case 0:
            case 1:
                if (main_bss_state.transition.selection != 0)
                    self->y_pos.i.hi = 0x98;
                else
                    self->y_pos.i.hi = 0x78;
                break;
            case 2:
                switch (main_bss_state.transition.selection) {
                case 0:
                    self->y_pos.i.hi = 0x78;
                    break;
                case 1:
                    self->y_pos.i.hi = 0x98;
                    break;
                case 2:
                    self->y_pos.i.hi = 0xB8;
                    break;
                }
                break;
            case 3:
                switch (main_bss_state.transition.selection) {
                case 0:
                    self->y_pos.i.hi = 0x78;
                    break;
                case 1:
                    self->y_pos.i.hi = 0x88;
                    break;
                case 2:
                    self->y_pos.i.hi = 0x98;
                    break;
                case 3:
                    self->y_pos.i.hi = 0xB8;
                    break;
                }
                break;
            case 4:
                if (main_bss_state.transition.selection != 0)
                    self->y_pos.i.hi = 0xB8;
                else
#ifdef VERSION_JP
                    self->y_pos.i.hi = 0x98;
#else
                    self->y_pos.i.hi = 0xA8;
#endif
                break;
            }
            self->ext.misc_42.unk57 = main_bss_state.transition.selection;
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    }

    switch (self->ext.misc_42.unk55) {
    case 1:
        if (self->ext.misc_42.unk54 != (s8)engine_obj.unk1)
            ZeroObjectState(OBJECT_HEADER(self));
        break;
    case 2:
        if (self->ext.misc_42.unk54 != (s8)engine_obj.unk2)
            ZeroObjectState(OBJECT_HEADER(self));
        break;
    case 3:
        if (self->ext.misc_42.unk54 != main_bss_state.transition.selection)
            ZeroObjectState(OBJECT_HEADER(self));
        break;
    }
}
#endif

#ifndef MMX4_SATURN
void (*menu_icon_state_funcs[2])(struct MiscObj*) = {
    func_800CFEE0,
    func_800D0118,
};
#endif
