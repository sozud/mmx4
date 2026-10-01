// MiscObj, misc_object_update_funcs[29]
// 800CD78C..800CDCC0
#include "common.h"

#ifdef VERSION_JP
#define TITLE_FADE_X 120
#define TITLE_SPARKLE_X 216
#define TITLE_PALETTE_WORDS 24
#else
#define TITLE_FADE_X 144
#define TITLE_SPARKLE_X 208
#define TITLE_PALETTE_WORDS 16
#endif

extern s32 title_logo_star_delays[];
extern u32* title_animations[];

// TitleLogoUpdate state 0
void title_logo_init(struct MiscObj* self)
{
    self->unk40 = 0x600;
    self->unk3C = SP_TITLE_FRAMES;
    self->animation_table = title_animations;
    self->bg_offset = -1;
    self->unk15 = 0;

    if (self->unk2 < 0x20) {
        self->unk42 = 0x7804;
        self->animation_step.fields.frame_index = 0x1C;
        if (!(self->unk2 & 0x10)) {
            self->x_pos.val = 0;
            self->y_pos.val = FIXED(240);
            self->x_vel.val = FIXED(8);
            self->y_vel.val = FIXED(6);
            self->ext.title_logo.palette_shift_speed = title_logo_star_delays[self->unk2];
            self->unk16 = 0;
            self->state++;
        } else {
            self->unk16 = 1;
            self->state = 4;
            self->ext.title_logo.palette_shift_speed = 6;
        }
        return;
    }
    self->unk42 = 0x7840;
    if (self->unk2 == 0x20) {
        set_animation(self, 0);
        self->x_pos.i.hi = TITLE_FADE_X; // set x pos of "MEGAMAN" while it's fading from white
        self->y_pos.i.hi = 72;
        self->state = 5;
    } else if (self->unk2 == 0x21) {
        set_animation(self, 1);
        self->x_pos.i.hi = TITLE_SPARKLE_X; // set x pos of "sparkle" effect
        self->y_pos.i.hi = 72;
        self->state = 7;
    } else {
        self->unk42 = 0x7804;
        self->unk16 = 0;
        self->x_pos.i.hi = 216;
        self->y_pos.i.hi = 72;
        self->state = 3;
        self->animation_step.fields.frame_index = 0x1C;
        self->unk2 = 0;
    }
    is_on_screen(self);
}

// TitleLogoUpdate state 1
void title_logo_star_delay(struct MiscObj* self)
{
    if (self->ext.title_logo.palette_shift_speed != 0) {
        self->ext.title_logo.palette_shift_speed--;
    } else {
        self->ext.title_logo.palette_shift_value = angle_to_point(OBJECT_HEADER(self), FIXED(216), FIXED(72));
        self->ext.title_logo.palette_shift_speed = 3;
        self->ext.title_logo.unk50 = NULL;
        self->state++;
    }
}

// TitleLogoUpdate state 2
void title_logo_star_fly(struct MiscObj* self)
{
    struct MiscObj* obj;
    u8 temp_v0 = angle_to_point(OBJECT_HEADER(self), FIXED(216), FIXED(72));
    if ((self->ext.title_logo.palette_shift_value ^ temp_v0) & 0x10) {
        self->x_pos.i.hi = 0xD8;
        self->y_pos.i.hi = 0x48;
        is_on_screen(self);
        self->unk16 = 2;
        self->state++;
    } else {
        if (self->ext.title_logo.palette_shift_speed == 0) {
            obj = func_8002AE90(self->ext.title_logo.unk50, 0);
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0x1D;
                obj->unk2 = 0x10;
                obj->x_pos.val = self->x_pos.val;
                obj->y_pos.val = self->y_pos.val;
                self->ext.title_logo.unk50 = obj;
            }
            self->ext.title_logo.palette_shift_speed = 3;
        } else {
            self->ext.title_logo.palette_shift_speed--;
        }
        set_velocity_from_angle(MOVING_OBJECT(self), temp_v0);
        self->x_vel.val *= 10;
        self->y_vel.val *= 8;
        move_object(MOVING_OBJECT(self));
        is_on_screen(self);
    }
}

// TitleLogoUpdate state 3
void title_logo_star_hold(struct MiscObj* self)
{
    if (self->unk2 == 0) {
        is_on_screen(self);
    } else {
        ZeroObjectState(self);
    }
}

// TitleLogoUpdate state 4
void title_logo_trail_fade(struct MiscObj* self)
{
    if (self->ext.title_logo.palette_shift_speed != 0) {
        self->ext.title_logo.palette_shift_speed--;
        is_on_screen(self);
    } else {
        ZeroObjectState(self);
    }
}

// TitleLogoUpdate state 5
void title_logo_fade_start(struct MiscObj* self)
{
    animate_object(self);
    // transition "MEGAMAN" to white before full logo appears
    if (self->animation_step.fields.relative_step == 0) {
        self->ext.title_logo.palette2 = (s32*)(SP_PALETTE + 0x100);
        self->ext.title_logo.palette1 = SP_ARC_30;
        // interval to shift on
        self->ext.title_logo.palette_shift_speed = 2;
        // how much to shift each step
        self->ext.title_logo.palette_shift_value = 0xF;
        self->state++;
    }
    is_on_screen(self);
}

// TitleLogoUpdate state 6
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_29_title_logo", title_logo_fade_palette);
#else
void title_logo_fade_palette(struct MiscObj* self)
{
    s32* src;
    s32* dst;
    u32 i;

    if (--self->ext.title_logo.palette_shift_speed == 0) {
        self->ext.title_logo.palette_shift_speed = 2;
        if (--self->ext.title_logo.palette_shift_value) {
            src = self->ext.title_logo.palette1;
            dst = self->ext.title_logo.palette2;
            for (i = 0; i < TITLE_PALETTE_WORDS; i++) {
                *dst++ = *src++;
            }
            need_palette_load |= 1;
            self->ext.title_logo.palette1 += TITLE_PALETTE_WORDS;
        } else {
            self->id = 0x13;
            self->unk2 = 0;
            self->state = 0;
        }
    }
    is_on_screen(self);
}
#endif

// TitleLogoUpdate state 7
void title_logo_sparkle(struct MiscObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        ZeroObjectState(self);
    } else {
        is_on_screen(self);
    }
}

// part of the title logo animation
void TitleLogoUpdate(struct MiscObj* self)
{
    self->on_screen = 0;
    g_TitleLogoUpdateFuncs[self->state](self);
}

s32 title_logo_star_delays[4] = { 0x1E, 0x3C, 0x5A, 0x78 };
void (*g_TitleLogoUpdateFuncs[8])(struct MiscObj*) = {
    title_logo_init,
    title_logo_star_delay,
    title_logo_star_fly,
    title_logo_star_hold,
    title_logo_trail_fade,
    title_logo_fade_start,
    title_logo_fade_palette,
    title_logo_sparkle,
};
