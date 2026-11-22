// MiscObj, misc_object_update_funcs[19]
// 800CB634..800CB884
#include "common.h"
#include "main/misc/misc_19_title.h"
#include "main/objects.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#endif

extern void (*g_TitleUpdateFuncs[])(struct MiscObj*);

// D_8010E824
void title_init(struct MiscObj* arg0);

void title_despawn(struct MiscObj* arg0);
#include "weapon_resources.h"

extern struct TitleObjectInit title_object_inits[];
extern u32* title_animations[];

// g_TitleUpdateFuncs state 0
#ifndef VERSION_DEMO
void title_init(struct MiscObj* self)
{
    u8 temp_a1 = self->unk2;
    u8 temp_v1;

    self->state++;
    self->animation_table = title_animations;
    self->bg_offset = -1;
    self->unk15 = 0;
    self->unk16 = 3;

#ifdef MMX4_SATURN
    self->unk40 = SATURN_TITLE_TEXTURE;
    self->unk3C = SATURN_TITLE_FRAMES;
    temp_v1 = title_object_inits[temp_a1].flags;
    self->unk42 = OBJECT_PALETTE_FROM_COLOR(temp_v1);
#else
    self->unk40 = 0x600;
    self->unk3C = SP_TITLE_FRAMES;
    temp_v1 = title_object_inits[temp_a1].flags;
    self->unk42 = ((temp_v1 % 16) | (((temp_v1 >> 4) + 0x1E0) << 6));
#endif
    // for unk2 == 0, setting position of "MEGAMAN" text
    // for unk2 == 1, didn't notice a difference
    // for unk2 == 2, setting position of greyed out "GAME START" text
    self->x_pos.val = FIXED(title_object_inits[temp_a1].x);
    self->y_pos.val = FIXED(title_object_inits[temp_a1].y);
    self->animation_step.fields.frame_index = title_object_inits[temp_a1].sprite;
    is_on_screen(self);
}
#endif

// g_TitleUpdateFuncs state 1
#ifndef VERSION_DEMO
void title_draw(struct MiscObj* self)
{
    if (self->unk2 == 0xF) {
        self->unk16 = 2;
        self->y_pos.i.hi = (game_info.unk2 % 3) * 16 + 0x80;
        switch (game_info.unk2) {
        case 0:
            self->animation_step.fields.frame_index = title_object_inits[2].sprite;
            break;
        case 1:
            self->animation_step.fields.frame_index = title_object_inits[13].sprite;
            break;
        case 2:
        default:
            self->animation_step.fields.frame_index = title_object_inits[14].sprite;
            break;
        }
    }

    if (self->unk2 == 4 || self->unk2 == 5 || self->unk2 == 6) {
        self->on_screen = 0;
        if (BLINK_CLOCK(WEAPON_FRAME_COUNTER) & 0x10) {
            is_on_screen(self);
        }
    } else {
        self->on_screen = 1;
        is_on_screen(self);
    }
}
#endif

// g_TitleUpdateFuncs state 2
void title_despawn(struct MiscObj* self)
{
    ZeroObjectState(self);
}

// title object. Includes the logo and the menu graphics
void TitleUpdate(struct MiscObj* self)
{
    g_TitleUpdateFuncs[self->state](self);
}

#ifdef VERSION_DEMO
s16 D_800DCE1C_demo[5][2] = {
    { 100, 64 },
    { 56, 120 },
    { 124, 152 },
    { 168, 152 },
    { 0, 0 },
};

s16 D_800DCE30_demo[12][2] = {
    { 120, 72 },
    { 216, 72 },
    { 160, 144 },
    { 96, 144 },
    { 160, 160 },
    { 152, 184 },
    { 152, 184 },
    { 160, 216 },
    { 248, 120 },
    { 272, 104 },
    { 120, 72 },
    { 216, 72 },
};

u8 D_800DCE60_demo[12] = { 0, 4, 6, 6, 10, 10, 10, 10, 10, 10, 0, 4 };

union AnimationStep D_800DCE6C_demo[] = {
    { 1, 0, 0, 0x16 },
    { 1, 0, 0, 0x17 },
    { 1, 0, 0, 0x18 },
    { 1, 0, 0, 0x19 },
    { 1, 0, 0, 0x03 },
};

union AnimationStep D_800DCE80_demo[] = {
    { 1, 0, 0, 0x00 },
    { 1, 0, 0, 0x01 },
    { 1, 0, 0, 0x02 },
    { 1, 0, 0, 0x03 },
    { 1, 0, 0, 0x04 },
    { 1, 0, 0, 0x05 },
    { 1, 0, 0, 0x06 },
    { 1, 0, 0, 0x07 },
    { 1, 0, 0, 0x08 },
    { 1, 0, 0, 0x09 },
    { 1, 0, 0, 0x1A },
    { 1, 0, 0, 0x1B },
    { 1, 0, 0, 0x1C },
};
#else
struct TitleObjectInit title_object_inits[] = {
#ifdef VERSION_JP
    { 120, 72, 0, 0 },
    { 216, 72, 1, 4 },
    { 160, 128, 2, 7 },
    { 96, 144, 3, 6 },
    { 160, 160, 4, 10 },
    { 152, 184, 5, 10 },
    { 152, 184, 6, 10 },
    { 160, 216, 7, 10 },
    { 248, 120, 8, 10 },
    { 272, 104, 9, 10 },
    { 120, 72, 26, 0 },
    { 216, 72, 27, 4 },
    { 0, 0, 28, 4 },
    { 160, 144, 29, 7 },
    { 160, 160, 30, 7 },
    { 160, 128, 2, 6 },
#else
    { 144, 72, 0, 0 },
    { 160, 72, 1, 4 },
    { 160, 128, 2, 7 },
    { 96, 144, 3, 6 },
    { 160, 160, 4, 10 },
    { 152, 184, 5, 10 },
#ifdef MMX4_WIN32
    { 160, 216, 6, 10 },
#else
    { 152, 184, 6, 10 },
#endif
#ifdef VERSION_EU
    { 148, 216, 7, 10 },
#else
    { 160, 216, 7, 10 },
#endif
    { 272, 128, 8, 10 },
    { 288, 120, 9, 10 },
    { 120, 72, 26, 0 },
    { 208, 72, 27, 4 },
    { 248, 72, 28, 4 },
    { 160, 144, 29, 7 },
    { 160, 160, 30, 7 },
    { 160, 128, 2, 6 },
    { 278, 72, 31, 4 },
#ifdef VERSION_EU
    { 164, 216, 31, 10 },
#else
    { 176, 216, 31, 10 },
#endif
    { 128, 72, 26, 0 },
    { 176, 72, 32, 0 },
    { 128, 72, 33, 8 },
    { 176, 72, 34, 8 },
#endif
};
#endif

union AnimationStep title_anim_0[] = {
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 1, 1, 0x11 },
    { 2, 2, 1, 0x11 },
    { 2, 3, 1, 0x11 },
    { 2, 4, 1, 0x11 },
    { 2, 5, 1, 0x11 },
    { 2, 6, 1, 0x11 },
    { 2, 7, 1, 0x11 },
    { 2, 8, 1, 0x11 },
    { 2, 9, 1, 0x11 },
    { 2, 10, 1, 0x11 },
    { 2, 11, 1, 0x11 },
    { 2, 12, 1, 0x11 },
    { 2, 13, 1, 0x11 },
    { 2, 14, 1, 0x11 },
    { 2, 15, 0, 0x11 },
};

union AnimationStep title_anim_1[] = {
    { 1, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 3, 0, 0, 0x19 },
};

#ifdef VERSION_DEMO
void func_800ABFDC_demo(struct MiscObj* self);
void func_800AC12C_demo(struct MiscObj* self);

u32* title_animations[] = {
    D_800DCE6C_demo,
    D_800DCE80_demo,
    title_anim_0,
    title_anim_1,
};

void (*g_TitleUpdateFuncs[3])(struct MiscObj*) = {
    func_800ABFDC_demo,
    func_800AC12C_demo,
    title_despawn,
};
#else
u32* title_animations[] = { title_anim_0, title_anim_1 };

void (*g_TitleUpdateFuncs[3])(struct MiscObj*) = {
    title_init,
    title_draw,
    title_despawn,
};
#endif
