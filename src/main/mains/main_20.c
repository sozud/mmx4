// MainObj, main_object_update_funcs[20]
// 8005458C..80054C50
#include "common.h"
#include "func_tables.h"

void func_8005458C(struct MainObj* arg0)
{
    D_800FC990[arg0->state](arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800545EC);

void func_80054710(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    func_80015D60(arg0, 0);
}

void func_80054738(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

void func_80054758(struct MainObj* arg0)
{
    s32 collision = func_8002DD04(arg0);
    s8 countdown;

    if (arg0->unk2 == 0 && arg0->ext.main_20.unk80 != arg0->unk5C) {
        countdown = arg0->ext.main_20.unk81--;
        if (countdown != 1) {
            if (countdown == 2) {
                func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10, 0);
            }
        } else {
            func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10, 5);
            arg0->unk5C = 1;
        }
        arg0->ext.main_20.unk80 = arg0->unk5C;
    }
    if (collision < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    D_800FC99C[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800548B8);

void func_80054B38(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk50 = (const u8*)&D_800FC860;
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80054B98(struct MainObj* arg0)
{
    arg0->unk7C = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_80054BBC(struct MainObj* self)
{
    D_800FC9A8[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        if (self->unk7C == 0) {
            func_8002B318(BASE_OBJECT(self), 0x50, 0x80);
        }
    } else {
        func_8002B108(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 D_800FC844 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC848 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC84C = { -24, -36, 48, 48 };

struct Unk_unk68 D_800FC850 = { -15, -16, 29, 64 };

struct Unk_unk68 D_800FC854 = { -15, -48, 29, 64 };

struct Unk_unk68 D_800FC858 = { -15, -16, 29, 32 };

struct Unk_unk68 D_800FC85C = { -15, -48, 29, 96 };

struct Unk_unk68 D_800FC860 = { 0, 0, 0, 0 };

union AnimationStep D_800FC864[] = {
    { 0x0001000C },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x01F40001 },
};

union AnimationStep D_800FC898[] = {
    { 0x04010003 },
    { 0x05010002 },
    { 0x06010003 },
    { 0x07010008 },
    { 0x00010002 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x09010001 },
    { 0x08F60002 },
};

union AnimationStep D_800FC8C8[] = {
    { 0x10010003 },
    { 0x11010004 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010003 },
    { 0x17010103 },
    { 0x18010003 },
    { 0x19010004 },
    { 0x1A010004 },
    { 0x1AF50001 },
};

union AnimationStep D_800FC8F8[] = {
    { 0x1B010003 },
    { 0x1C010004 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010003 },
    { 0x22010103 },
    { 0x23010003 },
    { 0x24010004 },
    { 0x25010004 },
    { 0x25F50001 },
};

union AnimationStep D_800FC928[] = {
    { 0x26010003 },
    { 0x27010004 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010003 },
    { 0x2D010103 },
    { 0x2E010003 },
    { 0x2F010004 },
    { 0x30010004 },
    { 0x30F50001 },
};

union AnimationStep D_800FC958[] = {
    { 0x0C000001 },
};

union AnimationStep D_800FC95C[] = {
    { 0x0D000001 },
};

union AnimationStep D_800FC960[] = {
    { 0x0E000001 },
};

union AnimationStep D_800FC964[] = {
    { 0x0F000001 },
};

union AnimationStep* D_800FC968[9] = {
    D_800FC864,
    D_800FC898,
    D_800FC958,
    D_800FC95C,
    D_800FC960,
    D_800FC964,
    D_800FC8C8,
    D_800FC8F8,
    D_800FC928,
};

u8 D_800FC98C[4] = { 2, 3, 4, 5 };

void (*D_800FC990[3])() = {
    func_800545EC,
    func_80054758,
    func_80054BBC,
};

void (*D_800FC99C[3])() = {
    func_8009216C,
    func_80054710,
    func_80054738,
};

void (*D_800FC9A8[3])() = {
    func_800548B8,
    func_80054B38,
    func_80054B98,
};
