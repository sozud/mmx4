// MiscObj, misc_object_update_funcs[18]
// 800CB00C..800CB634
#include "common.h"

extern const u32* ready_text_animations[];

// megaman never appears in stage if nopped out
void MegamanRelatedUpdate(struct MiscObj* self)
{
    g_MegamanRelatedUpdateFuncs[self->state](self);
}

extern u8 ready_text_palettes[];
extern s16 ready_text_x_positions[];
extern s16 ready_text_y_positions[];
extern u8 ready_text_priorities[];
extern u16 D_8013B940;

// g_MegamanRelatedUpdateFuncs state 0
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_18_ready_text", ready_text_init);
#else
void ready_text_init(struct MiscObj* self)
{
    u16* pal_dst;
    u16* color;
    u32 pal_pos;

    if (engine_obj.cur_character == CHARACTER_X) {
        self->unk3C = &SP_SPRITE_FRAMES_HDR->unk0[SP_SPRITE_FRAMES_HDR->unk24];
    } else {
        self->unk3C = &SP_SPRITE_FRAMES_HDR->unk0[SP_SPRITE_FRAMES_HDR->unk10];
    }

    self->unk40 = 0x1E00;
    self->animation_table = (u32**)ready_text_animations;
    self->state = 1;
    self->bg_offset = -1;
    self->unk42 = (ready_text_palettes[self->unk2] % 16) | (((ready_text_palettes[self->unk2] >> 4) + 0x1E0) << 6); // see water_wake_init & func_8003D4C8 for a similar pattern
    self->x_pos.i.hi = ready_text_x_positions[self->unk2];
    self->y_pos.i.hi = ready_text_y_positions[self->unk2];
    self->unk16 = ready_text_priorities[self->unk2];
    self->unk15 = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->ext.ready_text.unk54 = 0;
    self->ext.ready_text.stay_up_timer = 0;
    self->ext.ready_text.palette_pos = 0;
    self->ext.ready_text.unk58 = 0;
    self->ext.ready_text.palette_cycle_done = 0;

    if (self->unk2 < 2) {
        pal_pos = 0;
        if (self->unk2 != 0) {
            pal_dst = &D_8013B940;
            color = SP_PALETTE + 0x100;
            do {
                *pal_dst++ = *color;
                if (pal_pos != 0) {
                    *color = 0x8000;
                } else {
                    *color = 0;
                }
                pal_pos += 1;
                color += 1;
            } while (pal_pos < 16);
            need_palette_load |= 1;
        }
        set_animation(self, 0);
    } else {
        set_animation(self, self->unk2 - 1);
    }
}
#endif

// g_MegamanRelatedUpdateFuncs state 1
void ready_text_main(struct MiscObj* self)
{
    ready_text_part_funcs[self->unk2](self); // the animation before ready appears but "READY" doesn't if nopped out
}

// ready_text_word state 0, 1
// animation leading up to "READY" shows up but "READY" never apprears
// if nopped out
// asm(".rept 18 ; nop ; .endr");
void ready_text_word(struct MiscObj* self)
{
    ReadyTextUpdateFuncs[self->unk5](self);
    is_on_screen(self);
}

extern u8 ready_text_palette_cycle[];

// ReadyText State 0
void ready_text_appear(struct MiscObj* self)
{
    if (self->ext.ready_text.owner->ext.unk_effect.unk16 != 0) {
        ready_text_load_palette(self, NULL);
        self->unk5 = 1;
        self->ext.ready_text.unk54 = 8;
        if (self->unk2 != 0) {
            self->unk42 = 0x7840;
            self->x_vel.val = FIXED(.25);
            self->y_vel.val = FIXED(-.5); // set y velocity of shadow behind "READY"
            return;
        }
        self->x_vel.val = FIXED(-.25);
        self->y_vel.val = FIXED(.5); // set y velocity of blue "READY"
        func_8001540C(0, 0xA, 0);
        return;
    }
    if ((self->unk2 == 0) && (self->ext.ready_text.palette_cycle_done == 0)) {
        if (self->ext.ready_text.unk54 != 0) {
            self->ext.ready_text.unk54--;
            return;
        }
        // cycle palette when "READY" first appears
        ready_text_load_palette(self, ready_text_palette_cycle[self->ext.ready_text.palette_pos]);
        self->ext.ready_text.palette_pos++;
        if (self->ext.ready_text.palette_pos > 13) {
            self->ext.ready_text.palette_pos = 0;
            self->ext.ready_text.palette_cycle_done = 1;
        }
    }
}

extern u16 D_8013B940;

// ReadyText State 1
void ready_text_bounce(struct MiscObj* self)
{
    u16* pal_src;
    u16* pal_dst;
    u32 pal_pos;

    if (self->ext.ready_text.stay_up_timer != 0) {
        self->ext.ready_text.stay_up_timer--;
        return;
    }
    self->ext.ready_text.unk54--;
    if (self->ext.ready_text.unk54 == 0) {
        if (self->unk6 == 0) {
            if (self->unk2 != 0) {
                self->x_vel.val = FIXED(-.25);
                self->y_vel.val = FIXED(.5);
            } else {
                self->x_vel.val = FIXED(.25);
                self->y_vel.val = FIXED(-.50);
            }
            self->unk6 = 1;
            self->ext.ready_text.unk54 = 8;
            self->ext.ready_text.stay_up_timer = 30; // how long the "READY" text should be in the "up" position
            return;
        }
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk42 = 0x7801;
        if (self->unk2 != 0) {
            pal_src = &D_8013B940;
            pal_pos = 0;
            self->x_vel.val = FIXED(-16);
            pal_dst = SP_PALETTE + 0x100;
            do {
                *pal_dst++ = *pal_src++;
                pal_pos += 1;
            } while (pal_pos < 16);
            need_palette_load |= 1;
        } else {
            self->x_vel.val = FIXED(16);
        }
        self->y_vel.val = 0;
        self->x_pos.i.hi = 160;
        self->y_pos.i.hi = 120;
        engine_obj.unk1E = 1;
        return;
    }
    move_with_gravity((struct AnimatedObj*)self);
}

// ReadyText State 2
// "READY" never disappears if nopped out
// asm(".rept 26 ; nop ; .endr");
void ready_text_leave(struct MiscObj* self)
{
    if (self->on_screen != 0) {
        move_with_gravity(self);
        return;
    }
    self->state = 2;
    self->unk5 = 0;
    if ((engine_obj.stage == 5) && (engine_obj.checkpoint == 0)) {
        engine_obj.unk1C = 0;
    }
}

// ready_text_part_funcs state 2
void ready_text_blink(struct MiscObj* self)
{
    self->on_screen = 0;
    if (BLINK_TIMER.unk0 & 0x10) {
        is_on_screen(self);
    }
}

// ready_text_part_funcs state 3, 4
void ready_text_show(struct MiscObj* self)
{
    self->on_screen = 1;
    is_on_screen(self);
}

// "READY" has wrong palette if nopped out
// asm(".rept 22 ; nop ; .endr");
void ready_text_load_palette(s32 arg0, s32 arg1)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a2;

    var_a2 = 0;
    arg1 += 0x39;
    var_a0 = SP_PALETTE_BANK[arg1];
    var_v1 = SP_PALETTES[1];
    do {
        *var_v1++ = *var_a0++;
        var_a2 += 1;
    } while (var_a2 < 0x10);
    need_palette_load |= 1;
}

// g_MegamanRelatedUpdateFuncs state 2
void ready_text_despawn(struct MiscObj* self)
{
    ZeroObjectState(self);
}

u32 ready_text_anim_0[] = { 0x00000001 };

u32 ready_text_anim_1[] = { 0x03000001 };

u32 ready_text_anim_2[] = { 0x01000001 };

u32 ready_text_anim_3[] = { 0x02000001 };

const u32* ready_text_animations[] = { ready_text_anim_0, ready_text_anim_1, ready_text_anim_2, ready_text_anim_3 };

u8 ready_text_palette_cycle[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    11,
    10,
    9,
    8,
    7,
    6,
    5,
    4,
    3,
    2,
    1,
};

u8 ready_text_palettes[] = { 1, 1, 0x17, 0x15, 0x15, 0, 0, 0 };

s16 ready_text_x_positions[] = {
    160,
    160,
    96,
#ifdef VERSION_JP
    200,
#else
    208,
#endif
    256,
    0,
};

s16 ready_text_y_positions[] = { 120, 120, 112, 192, 192, 0 };

u8 ready_text_priorities[] = { 0x11, 0x12, 0x10, 0x10, 0x10, 0, 0, 0 };

void (*g_MegamanRelatedUpdateFuncs[3])(struct MiscObj*) = {
    ready_text_init,
    ready_text_main,
    ready_text_despawn,
};

void (*ready_text_part_funcs[5])(struct MiscObj*) = {
    ready_text_word,
    ready_text_word,
    ready_text_blink,
    ready_text_show,
    ready_text_show,
};

void (*ReadyTextUpdateFuncs[3])(struct MiscObj*) = {
    ready_text_appear,
    ready_text_bounce,
    ready_text_leave,
};
