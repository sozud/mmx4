// MainObj, main_object_update_funcs[31]
// 8005B894..8005C824
#include "common.h"
#include "func_tables.h"

void thorn_trap_update(struct MainObj* self)
{
    thorn_trap_state_funcs[self->state](self);
}

// thorn_trap_init
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005B8D0);

void thorn_trap_idle(struct MainObj* self)
{
}

// thorn_trap_wait
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005BA2C);

void thorn_trap_open(struct MainObj* self)
{
    s8 object_variant;

    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 2);
        object_variant = self->unk2;
        if (object_variant < 6) {
            self->unk5 = 4;
            return;
        }
        if (object_variant < 0xC) {
            if (self->ext.main_0.flags[0] != 0) {
                self->unk5 = 7;
                set_animation(self, 7);
                return;
            }
            self->unk5 = 6;
        } else {
            if (self->ext.main_0.flags[0] != 0) {
                self->unk5 = 9;
                set_animation(self, 4);
                return;
            }
            self->unk5 = 8;
        }
        set_animation(self, 3);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_windup(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 9);
        self->unk5 = 5;
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_strike(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        self->attack_box = &thorn_trap_strike_boxes;
        func_8002D9BC(self);
        self->attack_box = &D_800FD9F8;
        func_8002D9BC(self);
        self->attack_box = &D_800FD9FC;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA00;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA04;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA08;
        func_8002D9BC(self);
        self->contact_damage = 6;
        self->attack_box = &thorn_trap_attack_box;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_extend(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->hurt_box = (const u8*)&thorn_trap_open_hurt_box;
        self->ext.main_0.flags[0] = 1;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 7);
        self->unk5 = 7;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// thorn_trap_extended
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005BDE4);

void thorn_trap_extend_high(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->hurt_box = (const u8*)&thorn_trap_open_hurt_box;
        self->ext.main_0.flags[0] = 1;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 4);
        self->unk5 = 9;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// thorn_trap_extended_high
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005BFC0);

// thorn_trap_main
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005C0E4);

// thorn_trap_break
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005C474);

void thorn_trap_despawn(struct MainObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

struct Unk_unk68 thorn_trap_open_hurt_box[] = {
    { 58, -27, 0x18, 0x33 },
};

struct Unk_unk68 thorn_trap_attack_box[] = {
    { -105, -16, 0xC0, 0x1F },
};

struct Unk_unk68 thorn_trap_strike_boxes[] = {
    { -95, 15, 7, 0x15 },
};

struct Unk_unk68 D_800FD9F8[] = {
    { -59, -44, 7, 0x18 },
};

struct Unk_unk68 D_800FD9FC[] = {
    { -16, -28, 7, 0xF },
};

struct Unk_unk68 D_800FDA00[] = {
    { -20, -15, 7, 0x11 },
};

struct Unk_unk68 D_800FDA04[] = {
    { 23, 12, 7, 0x13 },
};

struct Unk_unk68 D_800FDA08[] = {
    { 48, -36, 7, 0x13 },
};

struct Unk_unk68 D_800FDA0C[] = {
    { -105, -15, 0xB3, 0x1C },
};

union AnimationStep thorn_trap_anim_0[] = {
    { 0x0D010001 },
    { 0x0DFF0001 },
    { 0x0101000D },
    { 0x0201000D },
    { 0x03010010 },
    { 0x04010010 },
    { 0x05010010 },
    { 0x06010010 },
    { 0x0701000F },
    { 0x07F90001 },
};

union AnimationStep thorn_trap_anim_1[] = {
    { 0x02010004 },
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07010003 },
    { 0x07FA0001 },
};

union AnimationStep thorn_trap_anim_2[] = {
    { 0x02010004 },
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07010004 },
    { 0x02010004 },
    { 0x00010003 },
    { 0x00F80001 },
};

union AnimationStep thorn_trap_anim_3[] = {
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010108 },
    { 0x0B010008 },
    { 0x0C010008 },
    { 0x0D01000F },
    { 0x0E010006 },
    { 0x0F010007 },
    { 0x0E010006 },
    { 0x0D010004 },
    { 0x0DFF0001 },
};

union AnimationStep thorn_trap_anim_4[] = {
    { 0x0D010005 },
    { 0x10010005 },
    { 0x11010005 },
    { 0x12010009 },
    { 0x2C010005 },
    { 0x2D01010A },
    { 0x2D01030A },
    { 0x2D010506 },
    { 0x2C010005 },
    { 0x12010009 },
    { 0x11010005 },
    { 0x10010005 },
    { 0x0D010004 },
    { 0x0DF50001 },
};

union AnimationStep thorn_trap_anim_5[] = {
    { 0x14010004 },
    { 0x15010004 },
    { 0x16010004 },
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010104 },
    { 0x1A010004 },
    { 0x1B010003 },
    { 0x1BF80001 },
};

union AnimationStep thorn_trap_anim_6[] = {
    { 0x1C010003 },
    { 0x1D010001 },
    { 0x1E010002 },
    { 0x1F010003 },
    { 0x20010004 },
    { 0x1F010003 },
    { 0x1E010065 },
    { 0x1F010003 },
    { 0x20010003 },
    { 0x1F010003 },
    { 0x20010003 },
    { 0x1F010003 },
    { 0x20010003 },
    { 0x20000001 },
};

union AnimationStep thorn_trap_anim_7[] = {
    { 0x0D010005 },
    { 0x2E010006 },
    { 0x2F010007 },
    { 0x2E010106 },
    { 0x2F010007 },
    { 0x2E010106 },
    { 0x2F010007 },
    { 0x2E010106 },
    { 0x2F010007 },
    { 0x2E010106 },
    { 0x0D010004 },
    { 0x0DF50001 },
};

union AnimationStep thorn_trap_anim_8[] = {
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010001 },
    { 0x26FA0001 },
};

union AnimationStep thorn_trap_anim_9[] = {
    { 0x00010001 },
    { 0x30010005 },
    { 0x31010004 },
    { 0x32010002 },
    { 0x32000101 },
};

union AnimationStep thorn_trap_anim_10[] = {
    { 0x32010001 },
    { 0x31010004 },
    { 0x30010005 },
    { 0x31010003 },
    { 0x31000001 },
};

union AnimationStep thorn_trap_anim_11[] = {
    { 0x13000001 },
};

union AnimationStep thorn_trap_anim_12[] = {
    { 0x27000001 },
};

union AnimationStep thorn_trap_anim_13[] = {
    { 0x28000001 },
};

union AnimationStep thorn_trap_anim_14[] = {
    { 0x29000001 },
};

union AnimationStep thorn_trap_anim_15[] = {
    { 0x2A000001 },
};

union AnimationStep thorn_trap_anim_16[] = {
    { 0x2B000001 },
};

union AnimationStep thorn_trap_anim_17[] = {
    { 0x33000001 },
};

union AnimationStep thorn_trap_anim_18[] = {
    { 0x34000001 },
};

union AnimationStep thorn_trap_anim_19[] = {
    { 0x35000001 },
};

union AnimationStep thorn_trap_anim_20[] = {
    { 0x36000001 },
};

union AnimationStep* thorn_trap_animations[] = {
    thorn_trap_anim_0,
    thorn_trap_anim_1,
    thorn_trap_anim_2,
    thorn_trap_anim_3,
    thorn_trap_anim_4,
    thorn_trap_anim_5,
    thorn_trap_anim_6,
    thorn_trap_anim_7,
    thorn_trap_anim_8,
    thorn_trap_anim_9,
    thorn_trap_anim_10,
    thorn_trap_anim_11,
    thorn_trap_anim_12,
    thorn_trap_anim_13,
    thorn_trap_anim_14,
    thorn_trap_anim_15,
    thorn_trap_anim_16,
    thorn_trap_anim_17,
    thorn_trap_anim_18,
    thorn_trap_anim_19,
    thorn_trap_anim_20,
};

u8 D_800FDC28[] = {
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x10,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC30[] = {
    0x11,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC34[] = {
    0x12,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC38[] = {
    0x13,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC3C[] = {
    0x14,
    0x00,
    0x00,
    0x00,
};

s8 D_800FDC40[8] = {
    54,
    -2,
    19,
    -9,
    -14,
    7,
    0,
    0,
};

void (*thorn_trap_state_funcs[])(struct MainObj*) = {
    func_8005B8D0,
    func_8005C0E4,
    func_8005C474,
    thorn_trap_despawn,
};

void (*thorn_trap_step_funcs[10])() = {
    enemy_hit_reaction,
    thorn_trap_idle,
    func_8005BA2C,
    thorn_trap_open,
    thorn_trap_windup,
    thorn_trap_strike,
    thorn_trap_extend,
    func_8005BDE4,
    thorn_trap_extend_high,
    func_8005BFC0,
};
