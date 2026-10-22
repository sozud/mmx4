// MiscObj, misc_object_update_funcs[12]
// 800CA228..800CA52C
#include "common.h"
#include "main/misc/misc_12_stage_icon.h"
#include "main/objects.h"
#include "main/55C4.h"

// stage_icon_state_funcs
extern void (*stage_icon_state_funcs[])(struct MiscObj*);

void stage_icon_highlight(struct MiscObj*);

void stage_icon_follow(struct MiscObj*);
void stage_icon_show_selected(struct MiscObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#endif

// stage_icon_init
struct Misc12Position {
    s16 x;
    s16 y;
};

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CA228(struct MiscObj* self);
void func_800CA40C(struct MiscObj* self);
extern union AnimationStep* stage_icon_animations[2];
extern struct Misc12Position stage_icon_positions[8];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CA228(struct MiscObj* self)
{
    s32 index;

    self->unk40 = OBJECT_STAGE_TEXTURE(0);
    self->animation_table = (u32**)stage_icon_animations;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
    index = self->unk2 & 0x7F;
    self->x_pos.val = index < 8 ? stage_icon_positions[index].x << 16 : 0;
    self->y_pos.val = index < 8 ? stage_icon_positions[index].y << 16 : 0;
    self->bg_offset = 0;
    self->unk15 = 0;
    if (self->unk2 < 0) {
        index = self->unk2 & 0x7F;
        self->unk42 = OBJECT_CLUT((index & 0xF) | (((index >> 4) | 0x1E0) << 6));
        self->unk16 = 0x12;
        set_animation_frame(ANIMATED_OBJECT(self), 1, index);
        self->state = 2;
    } else {
        self->unk42 = OBJECT_CLUT(0x780A);
        self->unk16 = 0x10;
        if ((u8)(self->unk2 - 8) < 2) {
            if (self->unk2 == 8) {
                self->x_pos.i.hi = 0x60;
                self->y_pos.i.hi = 0x180;
                self->state = 3;
            } else {
                self->x_pos.i.hi = 0x3C;
                self->y_pos.i.hi = 0x160;
                self->state = 4;
            }
            self->unk2 = 8;
        } else {
            self->state++;
        }
        set_animation_frame(ANIMATED_OBJECT(self), 0, self->unk2);
    }
    self->unk7 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_12_stage_icon", func_800CA228);
#endif

void stage_icon_highlight(struct MiscObj* self)
{
    self->on_screen = 0;
    if (engine_obj.unk3 == self->unk2) {
        self->unk42 = OBJECT_CLUT(0x780A);
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->unk42 = OBJECT_CLUT(0x7809);
    }
}

// stage_icon_follow_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CA40C(struct MiscObj* self)
{
    s32 index = self->unk2 & 0x7F;

    self->unk42 = OBJECT_CLUT((index & 0xF) | (((index >> 4) | 0x1E0) << 6));
    is_on_screen(BASE_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_12_stage_icon", func_800CA40C);
#endif

void stage_icon_follow(struct MiscObj* self)
{
    if (self->ext.misc_24.main->active == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    is_on_screen(BASE_OBJECT(self));
}

void stage_icon_show_selected(struct MiscObj* self)
{
    self->on_screen = 0;
    if (engine_obj.unk3 == self->unk2) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void stage_icon_update(struct MiscObj* self)
{
    stage_icon_state_funcs[self->state](self);
}

union AnimationStep stage_icon_anim_0[9] = {
    { 30, 0, 1, 0x00 },
    { 30, 0, 1, 0x01 },
    { 30, 0, 1, 0x02 },
    { 30, 0, 1, 0x03 },
    { 30, 0, 1, 0x04 },
    { 30, 0, 1, 0x05 },
    { 30, 0, 1, 0x06 },
    { 30, 0, 1, 0x07 },
    { 30, 0, 0, 0x10 },
};

union AnimationStep stage_icon_anim_1[8] = {
    { 30, 0, 1, 0x08 },
    { 30, 0, 1, 0x09 },
    { 30, 0, 1, 0x0A },
    { 30, 0, 1, 0x0B },
    { 30, 0, 1, 0x0C },
    { 30, 0, 1, 0x0D },
    { 30, 0, 1, 0x0E },
    { 30, 0, -7, 0x0F },
};

union AnimationStep* stage_icon_animations[2] = { stage_icon_anim_0, stage_icon_anim_1 };

struct Misc12Position stage_icon_positions[8] = {
    { 8, 0x120 },
    { 0x55, 0x120 },
    { 0xA2, 0x120 },
    { 0xEF, 0x120 },
    { 0x21, 0x1B0 },
    { 0x61, 0x1B0 },
    { 0xA2, 0x1B0 },
    { 0xE2, 0x1B0 },
};

void (*stage_icon_state_funcs[5])(struct MiscObj*) = {
    func_800CA228,
    stage_icon_highlight,
    func_800CA40C,
    stage_icon_follow,
    stage_icon_show_selected,
};
