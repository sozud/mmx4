// MiscObj, misc_object_update_funcs[8]
// 800C9510..800C9D64
#include "common.h"
#include "main/misc/misc_08_crumbling_tile.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/misc/misc_02_rubble.h"
#include "main/objects.h"

extern struct Misc08EffectTripletTable crumbling_tile_second_effects;
extern u8 crumbling_tile_debris_0[];
extern u8 crumbling_tile_debris_1[];
extern u8 crumbling_tile_debris_2[];
extern u8 crumbling_tile_debris_3[];
extern u8 crumbling_tile_debris_4[];
extern u8 crumbling_tile_debris_5[];
extern u8 crumbling_tile_debris_6[];
extern u8 crumbling_tile_debris_7[];
extern u8 crumbling_tile_debris_8[];
extern u8 crumbling_tile_debris_9[];
extern u8 crumbling_tile_debris_10[];
extern struct Misc08EffectDescriptor crumbling_tile_first_effects[];

// crumbling_tile_second_funcs
extern void (*crumbling_tile_second_funcs[])(struct MiscObj*);
void crumbling_tile_second_wait_anim(struct MiscObj*);
void crumbling_tile_second_delay(struct MiscObj*);
void crumbling_tile_break_second(struct MiscObj*);

// crumbling_tile_main_funcs
extern void (*crumbling_tile_main_funcs[])(struct MiscObj*);
void crumbling_tile_break_first(struct MiscObj*);
void crumbling_tile_second(struct MiscObj* arg0);

// crumbling_tile_state_funcs
extern void (*crumbling_tile_state_funcs[])(struct MiscObj*);
void func_800C9510(struct MiscObj*);
void crumbling_tile_main(struct MiscObj* arg0);
void crumbling_tile_despawn(struct MiscObj*);
#include "weapon_resources.h"

extern u8 crumbling_tile_debris_0[];
extern u8 crumbling_tile_debris_1[];
extern u8 crumbling_tile_debris_5[];
extern u8 crumbling_tile_debris_6[];
extern u8 crumbling_tile_debris_9[];
extern u8 crumbling_tile_debris_10[];

// crumbling_tile_init
void func_800C9510(struct MiscObj* self)
{
    self->animation_table = (u32**)D_8010DF48;
    self->ext.misc_8.alternate = (u8)self->unk2 >> 7;
    self->unk2 &= 0x7F;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x99)];
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x99));
    self->unk42 = OBJECT_STAGE_CLUT(0x99);
    self->unk16 = VISUAL_SATURN_LAYER(7);
    self->unk15 = 0;
    if ((u8)(self->unk2 - 0xD) < 6) {
        self->unk15 = PLAYER_FACING_RIGHT;
        self->x_pos.u.hi += 0x10;
    }
    self->ext.misc_8.timer = 0;
    if (self->ext.misc_8.alternate != 0) {
        set_animation(self, crumbling_tile_second_effects.entries[self->unk2].first);
    } else {
        set_animation(self, crumbling_tile_first_effects[self->unk2].effect_id);
    }
}

void crumbling_tile_break_first(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (self->on_screen != 0) {
            switch (self->unk2) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(8), FIXED(0));
                break;
            case 5:
            case 20:
                spawn_debris_offset(3, crumbling_tile_debris_0, self, FIXED(16), FIXED(16));
                spawn_debris_offset(3, crumbling_tile_debris_1, self, FIXED(48), FIXED(16));
                spawn_debris_offset(4, crumbling_tile_debris_5, self, FIXED(40), FIXED(48));
                spawn_debris_offset(4, crumbling_tile_debris_6, self, FIXED(40), FIXED(64));
                break;
            case 6:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(8), FIXED(32));
                break;
            case 7:
            case 8:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(-8), FIXED(32) + FIXED((self->unk2 - 7) * 8));
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(-8), FIXED(32) + FIXED((self->unk2 - 9) * 4));
                break;
            case 13:
            case 14:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(8), FIXED(32) + FIXED((self->unk2 - 13) * 8));
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                spawn_debris_offset(2, crumbling_tile_debris_0, self, FIXED(8), FIXED(32) + FIXED((self->unk2 - 15) * 4));
                break;
            case 19:
                spawn_debris_offset(4, crumbling_tile_debris_9, self, FIXED(16), FIXED(24));
                spawn_debris_offset(3, crumbling_tile_debris_10, self, FIXED(16), FIXED(56));
                break;
            }
        }
        if (self->unk15 != 0) {
            self->x_pos.i.hi -= 0x10;
        }
        apply_tile_effect(crumbling_tile_first_effects[self->unk2].variant, (s16)self->x_pos.u.hi, self->y_pos.i.hi);
        self->state++;
    }
}

void crumbling_tile_second_wait_anim(struct MiscObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->ext.misc_8.timer = 0xF;
        self->unk5++;
    }
}

void crumbling_tile_second_delay(struct MiscObj* self)
{
    s32 step;
    u8 specialStep;

    if (self->ext.misc_8.timer == 0) {
        self->unk5++;
        step = self->unk2;

        if (step < 0x16) {
            if (step < 0x13) {
                specialStep = 5;
            } else {
                return;
            }
        } else {
            specialStep = 0x19;
        }

        if (step == specialStep) {
            return;
        }
        set_animation(self, crumbling_tile_second_effects.entries[self->unk2].second);
    } else {
        self->ext.misc_8.timer--;
    }
}

void crumbling_tile_break_second(struct MiscObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        if (self->on_screen != 0) {
            switch (self->unk2) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 22:
            case 23:
            case 24:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(8), FIXED(32));
                break;
            case 5:
            case 20:
            case 21:
            case 25:
                spawn_debris_offset(4, crumbling_tile_debris_2, self, FIXED(16), FIXED(16));
                spawn_debris_offset(4, crumbling_tile_debris_3, self, FIXED(32), FIXED(16));
                spawn_debris_offset(3, crumbling_tile_debris_4, self, FIXED(48), FIXED(16));
                spawn_debris_offset(3, crumbling_tile_debris_7, self, FIXED(40), FIXED(48));
                spawn_debris_offset(2, crumbling_tile_debris_8, self, FIXED(40), FIXED(64));
                break;
            case 6:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(8), FIXED(32));
                break;
            case 7:
            case 8:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(-8), FIXED((self->unk2 - 7) * 8) + FIXED(32));
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(-8), FIXED((self->unk2 - 9) * 4) + FIXED(32));
                break;
            case 13:
            case 14:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(8), FIXED((self->unk2 - 7) * 8) + FIXED(32));
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                spawn_debris_offset(2, crumbling_tile_debris_3, self, FIXED(8), FIXED((self->unk2 - 9) * 4) + FIXED(32));
                break;
            case 19:
                spawn_debris_offset(4, crumbling_tile_debris_2, self, FIXED(16), FIXED(24));
                spawn_debris_offset(4, crumbling_tile_debris_3, self, FIXED(16), FIXED(56));
                break;
            }
        }
        if (self->unk15 != 0) {
            self->x_pos.i.hi -= 0x10;
        }
        apply_tile_effect(crumbling_tile_second_effects.entries[self->unk2].third, (s16)self->x_pos.u.hi, self->y_pos.i.hi);
        self->state++;
    }
}

void crumbling_tile_second(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    crumbling_tile_second_funcs[self->unk5](self);
}

void crumbling_tile_main(struct MiscObj* self)
{
    crumbling_tile_main_funcs[self->ext.misc_8.alternate](self);
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
}

void crumbling_tile_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void crumbling_tile_update(struct MiscObj* self)
{
    crumbling_tile_state_funcs[self->state](self);
}

union AnimationStep D_8010DC7C[] = { { 3, 0, 1, 0x00 }, { 3, 0, 1, 0x01 }, { 3, 0, 1, 0x02 }, { 3, 0, 1, 0x03 }, { 2, 0, 1, 0x04 }, { 1, 0, 0, 0x04 } };

union AnimationStep D_8010DC94[] = { { 1, 0, 0, 0x05 } };

union AnimationStep D_8010DC98[] = { { 1, 0, 0, 0x06 } };

union AnimationStep D_8010DC9C[] = { { 1, 0, 0, 0x07 } };

union AnimationStep D_8010DCA0[] = { { 1, 0, 0, 0x08 } };

union AnimationStep D_8010DCA4[] = { { 1, 0, 0, 0x09 } };

union AnimationStep D_8010DCA8[] = { { 1, 0, 0, 0x0A } };

union AnimationStep D_8010DCAC[] = { { 1, 0, 0, 0x0B } };

union AnimationStep D_8010DCB0[] = { { 3, 0, 1, 0x0D }, { 3, 0, 1, 0x0E }, { 3, 0, 0, 0x0F } };

union AnimationStep D_8010DCBC[] = { { 1, 0, 0, 0x11 } };

union AnimationStep D_8010DCC0[] = { { 1, 0, 0, 0x12 } };

union AnimationStep D_8010DCC4[] = { { 1, 0, 0, 0x13 } };

union AnimationStep D_8010DCC8[] = { { 1, 0, 0, 0x14 } };

union AnimationStep D_8010DCCC[] = { { 1, 0, 0, 0x15 } };

union AnimationStep D_8010DCD0[] = { { 1, 0, 0, 0x16 } };

union AnimationStep D_8010DCD4[] = { { 1, 0, 0, 0x17 } };

union AnimationStep D_8010DCD8[] = { { 1, 0, 0, 0x18 } };

union AnimationStep D_8010DCDC[] = { { 1, 0, 0, 0x19 } };

union AnimationStep D_8010DCE0[] = { { 1, 0, 0, 0x1A } };

union AnimationStep D_8010DCE4[] = { { 1, 0, 0, 0x1B } };

union AnimationStep D_8010DCE8[] = { { 3, 0, 1, 0x4E }, { 3, 0, 1, 0x4F }, { 3, 0, 1, 0x50 }, { 3, 0, 1, 0x51 }, { 3, 0, 1, 0x52 }, { 3, 0, 1, 0x53 }, { 3, 0, 1, 0x54 }, { 3, 0, 1, 0x55 }, { 2, 0, 1, 0x56 }, { 1, 0, 0, 0x56 } };

union AnimationStep D_8010DD10[] = { { 3, 0, 1, 0x5E }, { 3, 0, 1, 0x5F }, { 3, 0, 1, 0x60 }, { 3, 0, 1, 0x62 }, { 3, 0, 1, 0x64 }, { 3, 0, 1, 0x65 }, { 2, 0, 1, 0x66 }, { 1, 0, 0, 0x66 } };

union AnimationStep D_8010DD30[] = { { 3, 0, 1, 0x3F }, { 3, 0, 1, 0x40 }, { 3, 0, 1, 0x41 }, { 3, 0, 1, 0x42 }, { 3, 0, 1, 0x43 }, { 2, 0, 1, 0x44 }, { 1, 0, 0, 0x44 } };

union AnimationStep D_8010DD4C[] = { { 3, 0, 1, 0x3F }, { 3, 0, 1, 0x40 }, { 3, 0, 1, 0x41 }, { 3, 0, 1, 0x42 }, { 3, 0, 1, 0x45 }, { 2, 0, 1, 0x46 }, { 1, 0, 0, 0x46 } };

union AnimationStep D_8010DD68[] = { { 3, 0, 1, 0x99 }, { 3, 0, 1, 0x9A }, { 3, 0, 1, 0x9B }, { 3, 0, 1, 0x9C }, { 3, 0, 1, 0x9D }, { 2, 0, 1, 0x9E }, { 1, 0, 0, 0x9E } };

union AnimationStep D_8010DD84[] = { { 3, 0, 1, 0x9F }, { 3, 0, 1, 0xA0 }, { 3, 0, 1, 0xA1 }, { 3, 0, 1, 0xA2 }, { 3, 0, 1, 0xA3 }, { 2, 0, 1, 0xA4 }, { 1, 0, 0, 0xA4 } };

union AnimationStep D_8010DDA0[] = { { 3, 0, 1, 0xA5 }, { 3, 0, 1, 0xA6 }, { 3, 0, 1, 0xA7 }, { 3, 0, 1, 0xA8 }, { 3, 0, 1, 0xA9 }, { 2, 0, 1, 0xAA }, { 1, 0, 0, 0xAA } };

union AnimationStep D_8010DDBC[] = { { 3, 0, 1, 0x3F }, { 3, 0, 1, 0x40 }, { 3, 0, 1, 0x41 }, { 3, 0, 1, 0x42 }, { 3, 0, 1, 0x47 }, { 2, 0, 1, 0x48 }, { 1, 0, 0, 0x48 } };

union AnimationStep D_8010DDD8[] = { { 3, 0, 1, 0x9F }, { 3, 0, 1, 0xA0 }, { 3, 0, 1, 0xA1 }, { 3, 0, 1, 0xA2 }, { 3, 0, 1, 0xAB }, { 2, 0, 1, 0xAC }, { 1, 0, 0, 0xAC } };

union AnimationStep D_8010DDF4[] = { { 1, 0, 0, 0x49 } };

union AnimationStep D_8010DDF8[] = { { 1, 0, 0, 0x4A } };

union AnimationStep D_8010DDFC[] = { { 1, 0, 0, 0x4B } };

union AnimationStep D_8010DE00[] = { { 1, 0, 0, 0x4C } };

union AnimationStep D_8010DE04[] = { { 1, 0, 0, 0x4D } };

union AnimationStep D_8010DE08[] = { { 3, 0, 1, 0x21 }, { 3, 0, 1, 0x22 }, { 3, 0, 1, 0x23 }, { 3, 0, 1, 0x25 }, { 3, 0, 1, 0x27 }, { 3, 0, 1, 0x28 }, { 2, 0, 1, 0x29 }, { 1, 0, 0, 0x29 } };

union AnimationStep D_8010DE28[] = { { 3, 0, 1, 0x2A }, { 3, 0, 1, 0x2B }, { 3, 0, 1, 0x2C }, { 3, 0, 1, 0x2E }, { 3, 0, 1, 0x30 }, { 3, 0, 1, 0x31 }, { 2, 0, 1, 0x32 }, { 1, 0, 0, 0x32 } };

union AnimationStep D_8010DE48[] = { { 3, 0, 1, 0x6C }, { 3, 0, 1, 0x6D }, { 3, 0, 1, 0x6E }, { 3, 0, 1, 0x70 }, { 3, 0, 1, 0x72 }, { 3, 0, 1, 0x73 }, { 2, 0, 1, 0x74 }, { 1, 0, 0, 0x74 } };

union AnimationStep D_8010DE68[] = { { 3, 0, 1, 0x75 }, { 3, 0, 1, 0x76 }, { 3, 0, 1, 0x77 }, { 3, 0, 1, 0x79 }, { 3, 0, 1, 0x7B }, { 3, 0, 1, 0x7C }, { 2, 0, 1, 0x7D }, { 1, 0, 0, 0x7D } };

union AnimationStep D_8010DE88[] = { { 3, 0, 1, 0x7E }, { 3, 0, 1, 0x7F }, { 3, 0, 1, 0x80 }, { 3, 0, 1, 0x82 }, { 3, 0, 1, 0x84 }, { 3, 0, 1, 0x85 }, { 2, 0, 1, 0x86 }, { 1, 0, 0, 0x86 } };

union AnimationStep D_8010DEA8[] = { { 3, 0, 1, 0x33 }, { 3, 0, 1, 0x34 }, { 3, 0, 1, 0x36 }, { 3, 0, 1, 0x38 }, { 3, 0, 1, 0x39 }, { 3, 0, 1, 0x3A }, { 2, 0, 1, 0x3B }, { 1, 0, 0, 0x3B } };

union AnimationStep D_8010DEC8[] = { { 3, 0, 1, 0x87 }, { 3, 0, 1, 0x88 }, { 3, 0, 1, 0x8A }, { 3, 0, 1, 0x8C }, { 3, 0, 1, 0x8D }, { 3, 0, 1, 0x8E }, { 2, 0, 1, 0x8F }, { 1, 0, 0, 0x8F } };

union AnimationStep D_8010DEE8[] = { { 1, 0, 0, 0x57 } };

union AnimationStep D_8010DEEC[] = { { 1, 0, 0, 0x58 } };

union AnimationStep D_8010DEF0[] = { { 1, 0, 0, 0x59 } };

union AnimationStep D_8010DEF4[] = { { 1, 0, 0, 0x5A } };

union AnimationStep D_8010DEF8[] = { { 1, 0, 0, 0x5B } };

union AnimationStep D_8010DEFC[] = { { 1, 0, 0, 0x5C } };

union AnimationStep D_8010DF00[] = { { 1, 0, 0, 0x5D } };

union AnimationStep D_8010DF04[] = { { 3, 0, 1, 0x3C }, { 3, 0, 1, 0x3D }, { 3, 0, 0, 0x3E } };

union AnimationStep D_8010DF10[] = { { 3, 0, 0, 0x67 } };

union AnimationStep D_8010DF14[] = { { 3, 0, 0, 0x68 } };

union AnimationStep D_8010DF18[] = { { 3, 0, 0, 0x69 } };

union AnimationStep D_8010DF1C[] = { { 3, 0, 0, 0x6A } };

union AnimationStep D_8010DF20[] = { { 3, 0, 0, 0x6B } };

union AnimationStep D_8010DF24[] = { { 3, 0, 1, 0x90 }, { 3, 0, 1, 0x91 }, { 3, 0, 0, 0x92 } };

union AnimationStep D_8010DF30[] = { { 3, 0, 1, 0x93 }, { 3, 0, 1, 0x94 }, { 3, 0, 0, 0x95 } };

union AnimationStep D_8010DF3C[] = { { 3, 0, 1, 0x96 }, { 3, 0, 1, 0x97 }, { 3, 0, 0, 0x98 } };

#undef ANIM_STEP

union AnimationStep* D_8010DF48[57] = {
    D_8010DC7C,
    D_8010DC94,
    D_8010DC98,
    D_8010DC9C,
    D_8010DCA0,
    D_8010DCA4,
    D_8010DCA8,
    D_8010DCAC,
    D_8010DCB0,
    D_8010DCBC,
    D_8010DCC0,
    D_8010DCC4,
    D_8010DCC8,
    D_8010DCCC,
    D_8010DCD0,
    D_8010DCD4,
    D_8010DCD8,
    D_8010DCDC,
    D_8010DCE0,
    D_8010DCE4,
    D_8010DCE8,
    D_8010DD10,
    D_8010DD30,
    D_8010DD4C,
    D_8010DD68,
    D_8010DD84,
    D_8010DDA0,
    D_8010DDBC,
    D_8010DDD8,
    D_8010DDF4,
    D_8010DDF8,
    D_8010DDFC,
    D_8010DE00,
    D_8010DE04,
    D_8010DE08,
    D_8010DE28,
    D_8010DE48,
    D_8010DE68,
    D_8010DE88,
    D_8010DEA8,
    D_8010DEC8,
    D_8010DEE8,
    D_8010DEEC,
    D_8010DEF0,
    D_8010DEF4,
    D_8010DEF8,
    D_8010DEFC,
    D_8010DF00,
    D_8010DF04,
    D_8010DF24,
    D_8010DF30,
    D_8010DF3C,
    D_8010DF10,
    D_8010DF14,
    D_8010DF18,
    D_8010DF1C,
    D_8010DF20,
};

u8 crumbling_tile_debris_0[4] = { 0x1D, 0x1E, 0x1F, 0 };

u8 crumbling_tile_debris_1[4] = { 0x20, 0x21, 5, 0 };

u8 crumbling_tile_debris_2[4] = { 9, 10, 11, 12 };

u8 crumbling_tile_debris_3[4] = { 15, 14, 13, 16 };

u8 crumbling_tile_debris_4[4] = { 0x11, 0x12, 0x13, 0 };

u8 crumbling_tile_debris_5[4] = { 0x2D, 0x2A, 0x2B, 0x2F };

u8 crumbling_tile_debris_6[4] = { 0x2E, 0x29, 0x2C, 0x2F };

u8 crumbling_tile_debris_7[4] = { '4', '5', '6', 0 };

u8 crumbling_tile_debris_8[4] = { '7', '8', 0, 0 };

u8 crumbling_tile_debris_9[4] = { 1, 2, 3, 4 };

u8 crumbling_tile_debris_10[4] = { 5, 6, 7, 0 };

struct Misc08EffectDescriptor crumbling_tile_first_effects[28] = {
    { 0x16, 0 },
    { 0x16, 1 },
    { 0x16, 2 },
    { 0x16, 3 },
    { 0x16, 4 },
    { 0x14, 5 },
    { 0x17, 6 },
    { 0x1B, 7 },
    { 0x1C, 8 },
    { 0x17, 9 },
    { 0x18, 0x0A },
    { 0x19, 0x0B },
    { 0x1A, 0x0C },
    { 0x1C, 0x0D },
    { 0x1B, 0x0E },
    { 0x17, 0x0F },
    { 0x18, 0x10 },
    { 0x19, 0x11 },
    { 0x1A, 0x12 },
    { 0, 0x13 },
    { 0x14, 0x1E },
    { 0x17, 0x20 },
    { 0x18, 0x21 },
    { 0x19, 0x22 },
    { 0x1A, 0x23 },
    { 0x1C, 0x24 },
    { 0x1D, 0x25 },
    { 0, 0 },
};

struct Misc08EffectTripletTable crumbling_tile_second_effects = { {
                                                                      { 0x22, 0x30, 0x15 },
                                                                      { 0x22, 0x30, 0x15 },
                                                                      { 0x22, 0x30, 0x15 },
                                                                      { 0x22, 0x30, 0x15 },
                                                                      { 0x22, 0x30, 0x15 },
                                                                      { 0x15, 0, 0x18 },
                                                                      { 0x23, 0x31, 0x16 },
                                                                      { 0x27, 0x30, 0x16 },
                                                                      { 0x28, 0x32, 0x16 },
                                                                      { 0x23, 0x30, 0x16 },
                                                                      { 0x24, 0x31, 0x16 },
                                                                      { 0x25, 0x32, 0x16 },
                                                                      { 0x26, 0x33, 0x16 },
                                                                      { 0x28, 0x32, 0x16 },
                                                                      { 0x27, 0x30, 0x16 },
                                                                      { 0x23, 0x30, 0x16 },
                                                                      { 0x24, 0x31, 0x16 },
                                                                      { 0x25, 0x32, 0x16 },
                                                                      { 0x26, 0x33, 0x16 },
                                                                      { 8, 0, 0x14 },
                                                                      { 0x15, 0, 0x19 },
                                                                      { 0x15, 0, 0x1A },
                                                                      { 0x22, 0x30, 0x1B },
                                                                      { 0x22, 0x30, 0x1C },
                                                                      { 0x22, 0x30, 0x1D },
                                                                      { 0x15, 0, 0x1F },
                                                                  },
    { 0, 0 } };

void (*crumbling_tile_second_funcs[3])(struct MiscObj*) = {
    crumbling_tile_second_wait_anim,
    crumbling_tile_second_delay,
    crumbling_tile_break_second,
};

void (*crumbling_tile_main_funcs[2])(struct MiscObj*) = {
    crumbling_tile_break_first,
    crumbling_tile_second,
};

void (*crumbling_tile_state_funcs[3])(struct MiscObj*) = {
    func_800C9510,
    crumbling_tile_main,
    crumbling_tile_despawn,
};
