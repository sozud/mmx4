// MiscObj, misc_object_update_funcs[31]
// 800CDE44..800CE114
#include "common.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/misc/option_toggle_funcs.h"
#include "main/menu.h"
#include "main/objects.h"

// option_toggle_init
#ifdef MMX4_PC
static u16 misc_31_palette(struct MiscObj* arg0);
void func_800CDE44(struct MiscObj* arg0);
static u16 misc_31_palette(struct MiscObj* arg0)
{
    return arg0->unk2 == 3 && D_800F1D90.save.character == 0xFF ? 0x7804 : 0x7800;
}
#endif

#ifdef MMX4_PC
void func_800CDE44(struct MiscObj* arg0)
{
    arg0->unk40 = 0x1F00;
    arg0->bg_offset = -1;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[0];
    arg0->unk15 = 0;
    arg0->unk42 = arg0->y_pos.i.hi == 0x10 ? 0x7802 : misc_31_palette(arg0);
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0x10;
    if ((u8)(arg0->unk2 - 0x56) < 2) {
        arg0->state += 2;
        arg0->ext.misc_31.animation = D_80171EA9;
        arg0->animation_step.fields.frame_index = D_80171EA9 != 0 ? 0x56 : 0x57;
    } else {
        arg0->state++;
        arg0->animation_step.fields.frame_index = arg0->unk2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_31_option_toggle", func_800CDE44);
#endif

// option_toggle_appear
void func_800CDF4C(struct MiscObj* self)
{
    if (self->y_pos.i.hi != 0x10) {
        if (self->ext.misc_31.timer == 0) {
            if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
                || ((controller_input.pressed & PADstart) && (game_info.unk0 == 0xA))) {
                self->unk2 = -1;
            }
            if ((self->unk2 == -1) || (controller_input.pressed & PAD_SELECTION_ALT)
                || ((controller_input.pressed & PADstart) && (game_info.unk0 == 8))) {
                self->unk2 = -1;
            }
            if (self->unk2 == -1) {
                is_on_screen(BASE_OBJECT(self));
                return;
            }
        }
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = 0x7803;
        } else if ((self->unk2 == 3) && (D_800F1D90.save.character == 0xFF)) {
            self->unk42 = 0x7804;
        } else {
            self->unk42 = 0x7800;
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
    if (D_80171EA9 != self->ext.misc_31.animation) {
        if (D_80171EA9 != 0) {
            self->animation_step.fields.frame_index = 0x56;
        } else {
            self->animation_step.fields.frame_index = 0x57;
        }
        self->ext.misc_31.animation = D_80171EA9;
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
    { 0x3101000F },
    { 0x3201000D },
    { 0x3301000A },
    { 0x31010008 },
    { 0x32010007 },
    { 0x33010006 },
    { 0x31010006 },
    { 0x32010005 },
    { 0x33010005 },
    { 0x31010004 },
    { 0x32010005 },
    { 0x33010005 },
    { 0x31010006 },
    { 0x32010006 },
    { 0x33010007 },
    { 0x31010008 },
    { 0x3201000A },
    { 0x3301000D },
    { 0x3101000F },
    { 0x3301000D },
    { 0x3201000A },
    { 0x31010008 },
    { 0x33010007 },
    { 0x32010006 },
    { 0x31010006 },
    { 0x33010005 },
    { 0x32010005 },
    { 0x31010004 },
    { 0x33010005 },
    { 0x32010005 },
    { 0x31010006 },
    { 0x33010006 },
    { 0x32010007 },
    { 0x31010008 },
    { 0x3301000A },
    { 0x32DD000D },
};

u32* option_toggle_animations[1] = { (u32*)option_toggle_anim_0 };
