// MiscObj, misc_object_update_funcs[8]
// 800C9510..800C9D64
#include "common.h"

extern u8 crumbling_tile_debris_0[];
extern u8 crumbling_tile_debris_1[];
extern u8 crumbling_tile_debris_5[];
extern u8 crumbling_tile_debris_6[];
extern u8 crumbling_tile_debris_9[];
extern u8 crumbling_tile_debris_10[];

// crumbling_tile_init
INCLUDE_ASM("main/nonmatchings/misc/misc_08_crumbling_tile", func_800C9510);

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
    struct Misc8Ext* ext = &self->ext.misc_8;

    if (ext->timer == 0) {
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
        ext->timer--;
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

void crumbling_tile_second(struct MainObj* self)
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

#define ANIM_STEP(value)  \
    {                     \
        .packed = (value) \
    }

union AnimationStep D_8010DC7C[] = { ANIM_STEP(0x00010003), ANIM_STEP(0x01010003), ANIM_STEP(0x02010003), ANIM_STEP(0x03010003), ANIM_STEP(0x04010002), ANIM_STEP(0x04000001) };

union AnimationStep D_8010DC94[] = { ANIM_STEP(0x05000001) };

union AnimationStep D_8010DC98[] = { ANIM_STEP(0x06000001) };

union AnimationStep D_8010DC9C[] = { ANIM_STEP(0x07000001) };

union AnimationStep D_8010DCA0[] = { ANIM_STEP(0x08000001) };

union AnimationStep D_8010DCA4[] = { ANIM_STEP(0x09000001) };

union AnimationStep D_8010DCA8[] = { ANIM_STEP(0x0A000001) };

union AnimationStep D_8010DCAC[] = { ANIM_STEP(0x0B000001) };

union AnimationStep D_8010DCB0[] = { ANIM_STEP(0x0D010003), ANIM_STEP(0x0E010003), ANIM_STEP(0x0F000003) };

union AnimationStep D_8010DCBC[] = { ANIM_STEP(0x11000001) };

union AnimationStep D_8010DCC0[] = { ANIM_STEP(0x12000001) };

union AnimationStep D_8010DCC4[] = { ANIM_STEP(0x13000001) };

union AnimationStep D_8010DCC8[] = { ANIM_STEP(0x14000001) };

union AnimationStep D_8010DCCC[] = { ANIM_STEP(0x15000001) };

union AnimationStep D_8010DCD0[] = { ANIM_STEP(0x16000001) };

union AnimationStep D_8010DCD4[] = { ANIM_STEP(0x17000001) };

union AnimationStep D_8010DCD8[] = { ANIM_STEP(0x18000001) };

union AnimationStep D_8010DCDC[] = { ANIM_STEP(0x19000001) };

union AnimationStep D_8010DCE0[] = { ANIM_STEP(0x1A000001) };

union AnimationStep D_8010DCE4[] = { ANIM_STEP(0x1B000001) };

union AnimationStep D_8010DCE8[] = { ANIM_STEP(0x4E010003), ANIM_STEP(0x4F010003), ANIM_STEP(0x50010003), ANIM_STEP(0x51010003), ANIM_STEP(0x52010003), ANIM_STEP(0x53010003), ANIM_STEP(0x54010003), ANIM_STEP(0x55010003), ANIM_STEP(0x56010002), ANIM_STEP(0x56000001) };

union AnimationStep D_8010DD10[] = { ANIM_STEP(0x5E010003), ANIM_STEP(0x5F010003), ANIM_STEP(0x60010003), ANIM_STEP(0x62010003), ANIM_STEP(0x64010003), ANIM_STEP(0x65010003), ANIM_STEP(0x66010002), ANIM_STEP(0x66000001) };

union AnimationStep D_8010DD30[] = { ANIM_STEP(0x3F010003), ANIM_STEP(0x40010003), ANIM_STEP(0x41010003), ANIM_STEP(0x42010003), ANIM_STEP(0x43010003), ANIM_STEP(0x44010002), ANIM_STEP(0x44000001) };

union AnimationStep D_8010DD4C[] = { ANIM_STEP(0x3F010003), ANIM_STEP(0x40010003), ANIM_STEP(0x41010003), ANIM_STEP(0x42010003), ANIM_STEP(0x45010003), ANIM_STEP(0x46010002), ANIM_STEP(0x46000001) };

union AnimationStep D_8010DD68[] = { ANIM_STEP(0x99010003), ANIM_STEP(0x9A010003), ANIM_STEP(0x9B010003), ANIM_STEP(0x9C010003), ANIM_STEP(0x9D010003), ANIM_STEP(0x9E010002), ANIM_STEP(0x9E000001) };

union AnimationStep D_8010DD84[] = { ANIM_STEP(0x9F010003), ANIM_STEP(0xA0010003), ANIM_STEP(0xA1010003), ANIM_STEP(0xA2010003), ANIM_STEP(0xA3010003), ANIM_STEP(0xA4010002), ANIM_STEP(0xA4000001) };

union AnimationStep D_8010DDA0[] = { ANIM_STEP(0xA5010003), ANIM_STEP(0xA6010003), ANIM_STEP(0xA7010003), ANIM_STEP(0xA8010003), ANIM_STEP(0xA9010003), ANIM_STEP(0xAA010002), ANIM_STEP(0xAA000001) };

union AnimationStep D_8010DDBC[] = { ANIM_STEP(0x3F010003), ANIM_STEP(0x40010003), ANIM_STEP(0x41010003), ANIM_STEP(0x42010003), ANIM_STEP(0x47010003), ANIM_STEP(0x48010002), ANIM_STEP(0x48000001) };

union AnimationStep D_8010DDD8[] = { ANIM_STEP(0x9F010003), ANIM_STEP(0xA0010003), ANIM_STEP(0xA1010003), ANIM_STEP(0xA2010003), ANIM_STEP(0xAB010003), ANIM_STEP(0xAC010002), ANIM_STEP(0xAC000001) };

union AnimationStep D_8010DDF4[] = { ANIM_STEP(0x49000001) };

union AnimationStep D_8010DDF8[] = { ANIM_STEP(0x4A000001) };

union AnimationStep D_8010DDFC[] = { ANIM_STEP(0x4B000001) };

union AnimationStep D_8010DE00[] = { ANIM_STEP(0x4C000001) };

union AnimationStep D_8010DE04[] = { ANIM_STEP(0x4D000001) };

union AnimationStep D_8010DE08[] = { ANIM_STEP(0x21010003), ANIM_STEP(0x22010003), ANIM_STEP(0x23010003), ANIM_STEP(0x25010003), ANIM_STEP(0x27010003), ANIM_STEP(0x28010003), ANIM_STEP(0x29010002), ANIM_STEP(0x29000001) };

union AnimationStep D_8010DE28[] = { ANIM_STEP(0x2A010003), ANIM_STEP(0x2B010003), ANIM_STEP(0x2C010003), ANIM_STEP(0x2E010003), ANIM_STEP(0x30010003), ANIM_STEP(0x31010003), ANIM_STEP(0x32010002), ANIM_STEP(0x32000001) };

union AnimationStep D_8010DE48[] = { ANIM_STEP(0x6C010003), ANIM_STEP(0x6D010003), ANIM_STEP(0x6E010003), ANIM_STEP(0x70010003), ANIM_STEP(0x72010003), ANIM_STEP(0x73010003), ANIM_STEP(0x74010002), ANIM_STEP(0x74000001) };

union AnimationStep D_8010DE68[] = { ANIM_STEP(0x75010003), ANIM_STEP(0x76010003), ANIM_STEP(0x77010003), ANIM_STEP(0x79010003), ANIM_STEP(0x7B010003), ANIM_STEP(0x7C010003), ANIM_STEP(0x7D010002), ANIM_STEP(0x7D000001) };

union AnimationStep D_8010DE88[] = { ANIM_STEP(0x7E010003), ANIM_STEP(0x7F010003), ANIM_STEP(0x80010003), ANIM_STEP(0x82010003), ANIM_STEP(0x84010003), ANIM_STEP(0x85010003), ANIM_STEP(0x86010002), ANIM_STEP(0x86000001) };

union AnimationStep D_8010DEA8[] = { ANIM_STEP(0x33010003), ANIM_STEP(0x34010003), ANIM_STEP(0x36010003), ANIM_STEP(0x38010003), ANIM_STEP(0x39010003), ANIM_STEP(0x3A010003), ANIM_STEP(0x3B010002), ANIM_STEP(0x3B000001) };

union AnimationStep D_8010DEC8[] = { ANIM_STEP(0x87010003), ANIM_STEP(0x88010003), ANIM_STEP(0x8A010003), ANIM_STEP(0x8C010003), ANIM_STEP(0x8D010003), ANIM_STEP(0x8E010003), ANIM_STEP(0x8F010002), ANIM_STEP(0x8F000001) };

union AnimationStep D_8010DEE8[] = { ANIM_STEP(0x57000001) };

union AnimationStep D_8010DEEC[] = { ANIM_STEP(0x58000001) };

union AnimationStep D_8010DEF0[] = { ANIM_STEP(0x59000001) };

union AnimationStep D_8010DEF4[] = { ANIM_STEP(0x5A000001) };

union AnimationStep D_8010DEF8[] = { ANIM_STEP(0x5B000001) };

union AnimationStep D_8010DEFC[] = { ANIM_STEP(0x5C000001) };

union AnimationStep D_8010DF00[] = { ANIM_STEP(0x5D000001) };

union AnimationStep D_8010DF04[] = { ANIM_STEP(0x3C010003), ANIM_STEP(0x3D010003), ANIM_STEP(0x3E000003) };

union AnimationStep D_8010DF10[] = { ANIM_STEP(0x67000003) };

union AnimationStep D_8010DF14[] = { ANIM_STEP(0x68000003) };

union AnimationStep D_8010DF18[] = { ANIM_STEP(0x69000003) };

union AnimationStep D_8010DF1C[] = { ANIM_STEP(0x6A000003) };

union AnimationStep D_8010DF20[] = { ANIM_STEP(0x6B000003) };

union AnimationStep D_8010DF24[] = { ANIM_STEP(0x90010003), ANIM_STEP(0x91010003), ANIM_STEP(0x92000003) };

union AnimationStep D_8010DF30[] = { ANIM_STEP(0x93010003), ANIM_STEP(0x94010003), ANIM_STEP(0x95000003) };

union AnimationStep D_8010DF3C[] = { ANIM_STEP(0x96010003), ANIM_STEP(0x97010003), ANIM_STEP(0x98000003) };

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
