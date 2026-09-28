// MainObj, main_object_update_funcs[19]
// 8005284C..8005458C
#include "common.h"
#include "func_tables.h"

void func_8005284C(struct MainObj* arg0)
{
    if (arg0->unk2 < 3) {
        D_800FC784[arg0->state](arg0);
    } else {
        D_800FC790[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800528BC);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052A68);

void func_80052B94(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        func_80015D60(
            arg0, D_800FC7B4[SP_CUR_MAIN_OBJ->ext.main_19.animation_index]);
        return;
    }

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = get_random() & 1;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80052C2C(struct MainObj* arg0)
{
    arg0->unk7C++;
    D_800FC7B8[arg0->unk6](arg0);
}

void func_80052C70(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    if (arg0->unk70 != 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052CB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052E94);

void func_800531B4(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 3;
        if (SP_CUR_MAIN_OBJ->ext.main_19.animation_index < 2) {
            func_80015D60(arg0, 0xB);
        } else {
            func_80015D60(arg0, 0xA);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80053224(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 ^= 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80053274(struct MainObj* arg0)
{
    s32 animation;
    struct MainObj* current;

    if (arg0->animation_step.fields.relative_step < 0) {
        current = SP_CUR_MAIN_OBJ;
        if (current->ext.main_19.animation_index < 2) {
            animation = 9;
            if (current->ext.main_19.unk80 == 0) {
                animation = 8;
            }
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
        } else {
            animation = 7;
            arg0->unk24 = 0;
            arg0->unk2C = 0;
        }
        arg0->unk68 = D_800FC73C[arg0->unk2 >> 1];
        func_80015D60(arg0, animation);
        arg0->unk6 = 5;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053338);

void func_800535CC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_80053604(struct MainObj* arg0)
{
    D_800FC7DC[arg0->unk6](arg0);
}

void func_80053640(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    arg0->unk7C = 0;
    func_80015D60(arg0,
        D_800FC7E4[SP_CUR_MAIN_OBJ->ext.main_19.animation_index >> 1]);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005368C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800537E0);

u8 func_8005398C(struct MainObj* self)
{
    u16 player_x;
    u16 player_y;
    s16 dy;
    s16 dx;
    s32 flags;

    player_x = g_Player.x_pos.u.hi;
    player_y = g_Player.y_pos.u.hi;
    dy = player_y - self->y_pos.u.hi;
    dx = player_x - self->x_pos.u.hi;
    flags = 0;

    if ((dx < 0 ? -dx : dx) < 0x40 || (dy < 0 ? -dy : dy) >= 0x60) {
        flags = 1;
    }
    if ((dx < 0 ? -dx : dx) >= 0x80) {
        flags |= 2;
    }

    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7DC(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    return flags;
}

u8 func_80053A88(struct PlayerObj* arg0, s16 arg1, s16 arg2)
{
    s32 saved_x_pos;
    s32 saved_y_pos;
    s32 saved_unk18;
    s32 saved_unk1C;
    u8 result;

    saved_x_pos = arg0->x_pos.val;
    saved_y_pos = arg0->y_pos.val;
    saved_unk18 = arg0->unk18.val;
    saved_unk1C = arg0->unk1C.val;
    arg0->unk18.val = saved_x_pos;
    arg0->unk1C.val = saved_y_pos;
    arg0->x_pos.u.hi = arg0->x_pos.u.hi + arg1;
    arg0->y_pos.u.hi = arg0->y_pos.u.hi + arg2;
    CollisionRelated(arg0);
    result = arg0->unk70;
    arg0->x_pos.val = saved_x_pos;
    arg0->y_pos.val = saved_y_pos;
    arg0->unk18.val = saved_unk18;
    arg0->unk1C.val = saved_unk1C;
    arg0->unk70 = 0;
    return result;
}

u8 func_80053B18(struct PlayerObj* arg0, s16 arg1, s16 arg2)
{
    arg1 = arg0->x_pos.i.hi + arg1;
    arg2 = arg0->y_pos.i.hi + arg2;
    return func_8002D724(arg0, arg1, arg2);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053B54);

void func_80053D04(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053D24);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053EB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005402C);

void func_8005440C(struct MainObj* self)
{
    s32 index;

    index = (SP_CUR_MAIN_OBJ->ext.main_19.animation_index << 2) + SP_CUR_MAIN_OBJ->ext.main_19.unk80;
    self->unk20 = D_800FC814[index] << 16;
    self->unk24 = D_800FC824[index] << 16;
    self->unk15 = D_800FC834[index];
    func_80015D60(self, D_800FC83C[index]);
    self->unk54 = D_800FC754[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->unk50 = D_800FC764[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->unk68 = D_800FC774[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
}

void func_80054518(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->unk6 == 0) {
        func_8005440C(arg0);
        arg0->unk6 = 1;
        arg0->unk7C = 0x1E;
        return;
    }
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

union AnimationStep D_800FC40C[] = {
    { 0x00000001 },
};

union AnimationStep D_800FC410[] = {
    { 0x01000001 },
};

union AnimationStep D_800FC414[] = {
    { 0x0001000A },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010009 },
    { 0x05010101 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F30002 },
};

union AnimationStep D_800FC450[] = {
    { 0x0101000A },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0C010008 },
    { 0x0D010009 },
    { 0x0D010101 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F30002 },
};

union AnimationStep D_800FC48C[] = {
    { 0x0101000A },
    { 0x40010008 },
    { 0x41010008 },
    { 0x42010008 },
    { 0x43010009 },
    { 0x43010101 },
    { 0x44010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F30002 },
};

union AnimationStep D_800FC4C8[] = {
    { 0x00010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18F70002 },
};

union AnimationStep D_800FC4F0[] = {
    { 0x01010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1FF70002 },
};

union AnimationStep D_800FC518[] = {
    { 0x18010003 },
    { 0x21010003 },
    { 0x20FE0003 },
};

union AnimationStep D_800FC524[] = {
    { 0x1F010003 },
    { 0x22010003 },
    { 0x23FE0003 },
};

union AnimationStep D_800FC530[] = {
    { 0x1F010003 },
    { 0x23010003 },
    { 0x22FE0003 },
};

union AnimationStep D_800FC53C[] = {
    { 0x1801000A },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x00010002 },
    { 0x13010002 },
    { 0x00FA000A },
};

union AnimationStep D_800FC558[] = {
    { 0x1F01000A },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x1A010002 },
    { 0x01010002 },
    { 0x1A010002 },
    { 0x01FA000A },
};

union AnimationStep D_800FC574[] = {
    { 0x24010006 },
    { 0x25010006 },
    { 0x26010006 },
    { 0x27010003 },
    { 0x28010012 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010002 },
    { 0x29010003 },
    { 0x2A010103 },
    { 0x2B010002 },
    { 0x2801000F },
    { 0x27010003 },
    { 0x26010006 },
    { 0x25010006 },
    { 0x24F10006 },
};

union AnimationStep D_800FC5B4[] = {
    { 0x2C010006 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010003 },
    { 0x30010012 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x31010003 },
    { 0x32010103 },
    { 0x33010002 },
    { 0x3001000F },
    { 0x2F010003 },
    { 0x2E010006 },
    { 0x2D010006 },
    { 0x2CF10006 },
};

union AnimationStep D_800FC5F4[] = {
    { 0x06010102 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F80002 },
};

union AnimationStep D_800FC618[] = {
    { 0x0E010102 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F80002 },
};

union AnimationStep D_800FC63C[] = {
    { 0x44010102 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F80002 },
};

union AnimationStep D_800FC660[] = {
    { 0x34010002 },
    { 0x35010001 },
    { 0x36010002 },
    { 0x37FD0001 },
};

union AnimationStep D_800FC670[] = {
    { 0x38000001 },
};

union AnimationStep D_800FC674[] = {
    { 0x39000001 },
};

union AnimationStep D_800FC678[] = {
    { 0x3A000001 },
};

union AnimationStep D_800FC67C[] = {
    { 0x3B000001 },
};

union AnimationStep D_800FC680[] = {
    { 0x3C000001 },
};

union AnimationStep D_800FC684[] = {
    { 0x3D000001 },
};

union AnimationStep D_800FC688[] = {
    { 0x3E000001 },
};

union AnimationStep D_800FC68C[] = {
    { 0x3F000001 },
};

union AnimationStep D_800FC690[] = {
    { 0x45010003 },
    { 0x46010003 },
    { 0x47FE0003 },
};

union AnimationStep* D_800FC69C[27] = {
    D_800FC40C,
    D_800FC410,
    D_800FC414,
    D_800FC450,
    D_800FC48C,
    D_800FC4C8,
    D_800FC4F0,
    D_800FC518,
    D_800FC524,
    D_800FC530,
    D_800FC53C,
    D_800FC558,
    D_800FC574,
    D_800FC5B4,
    D_800FC5F4,
    D_800FC618,
    D_800FC63C,
    D_800FC660,
    D_800FC670,
    D_800FC674,
    D_800FC678,
    D_800FC67C,
    D_800FC680,
    D_800FC684,
    D_800FC688,
    D_800FC68C,
    D_800FC690,
};

u8 D_800FC708[8] = { 18, 19, 20, 21, 22, 23, 24, 25 };

struct Unk_unk68 D_800FC710 = { 0, -9, 27, 18 };

struct Unk_unk68 D_800FC714 = { -10, 0, 20, 25 };

struct Unk_unk68 D_800FC718 = { 0, -16, 39, 30 };

struct Unk_unk68 D_800FC71C = { -18, 0, 35, 36 };

struct Unk_unk68 D_800FC720 = { 22, 0, 22, 18 };

struct Unk_unk68 D_800FC724 = { 0, 21, 18, 21 };

struct Unk_unk68 D_800FC728 = { 16, 0, 16, 16 };

struct Unk_unk68 D_800FC72C = { 0, 16, 16, 16 };

struct Unk_unk68 D_800FC730 = { 0, -16, 16, 16 };

struct Unk_unk68 D_800FC734 = { -10, -25, 20, 25 };

struct Unk_unk68 D_800FC738 = { -18, -35, 35, 35 };

struct Unk_unk68* D_800FC73C[2] = {
    &D_800FC720,
    &D_800FC724,
};

struct Unk_unk68* D_800FC744[2] = {
    &D_800FC718,
    &D_800FC71C,
};

struct Unk_unk68* D_800FC74C[2] = {
    &D_800FC710,
    &D_800FC714,
};

struct Unk_unk68* D_800FC754[4] = {
    &D_800FC738,
    &D_800FC718,
    &D_800FC71C,
    &D_800FC718,
};

struct Unk_unk68* D_800FC764[4] = {
    &D_800FC734,
    &D_800FC710,
    &D_800FC714,
    &D_800FC710,
};

struct Unk_unk68* D_800FC774[4] = {
    &D_800FC730,
    &D_800FC728,
    &D_800FC72C,
    &D_800FC728,
};

void (*D_800FC784[3])() = {
    func_800528BC,
    func_80052A68,
    func_80053D04,
};

void (*D_800FC790[3])() = {
    func_80053D24,
    func_80053EB8,
    func_80053D04,
};

void (*D_800FC79C[6])() = {
    func_8009216C,
    func_80052B94,
    func_80052C2C,
    func_80052C2C,
    func_80053604,
    func_80052C70,
};

u8 D_800FC7B4[4] = { 0x0E, 0x0F, 0x10, 0x00 };

void (*D_800FC7B8[7])() = {
    func_80052CB8,
    func_80052E94,
    func_800531B4,
    func_80053224,
    func_80053274,
    func_80053338,
    func_800535CC,
};

u8 D_800FC7D4[4] = { 0x03, 0x04, 0x00, 0x00 };

u8 D_800FC7D8[4] = { 0x00, 0x40, 0x00, 0x00 };

void (*D_800FC7DC[2])() = {
    func_80053640,
    func_8005368C,
};

u8 D_800FC7E4[4] = { 0x0D, 0x0C, 0x00, 0x00 };

s16 D_800FC7E8[6] = {
    (s16)0xFFE2,
    (s16)0x0000,
    (s16)0x001E,
    (s16)0x0000,
    (s16)0x0000,
    (s16)0x001C,
};

void (*D_800FC7F4[6])() = {
    func_8009216C,
    func_80054518,
    func_8005402C,
    func_8005402C,
    func_8005402C,
    func_80052C70,
};

u8 D_800FC80C[8] = { 0x02, 0x08, 0x01, 0x04, 0x01, 0x04, 0x02, 0x08 };

s16 D_800FC814[8] = {
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
};

s16 D_800FC824[8] = {
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
};

u8 D_800FC834[8] = { 0x00, 0x40, 0x40, 0x00, 0x40, 0x40, 0x00, 0x00 };

u8 D_800FC83C[8] = { 0x1A, 0x09, 0x07, 0x08, 0x1A, 0x08, 0x07, 0x09 };
