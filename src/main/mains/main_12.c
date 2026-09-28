// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"
#include "func_tables.h"

void func_8004B8C0(struct MainObj* arg0)
{
    D_800FB6A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004B8FC);

void func_8004BAF8(struct MainObj* arg0)
{
    s32 result;
    s8 mode = arg0->unk5;

    if (mode != 5 || arg0->unk6 != 4) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8004C6C4(arg0);
    D_800FB6B4[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    result = func_8002DD04(arg0);
    if (result < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FB67C, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0xE);
    } else {
        if (result > 0) {
            SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5 = arg0->unk5;
        }
        if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
            is_on_screen(BASE_OBJECT(arg0));
            return;
        }
    }
    arg0->state++;
}

void func_8004BC14(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

void func_8004BC2C(struct MainObj* arg0)
{
    struct MainObj* current;

    func_8002B694(ANIMATED_OBJECT(arg0));
    current = SP_CUR_MAIN_OBJ;
    if (current->ext.main_12.unk88 == 0) {
        if (arg0->unk24 >= 0) {
            arg0->unk24 = FIXED(0.5);
            arg0->unk2C = -arg0->unk2C;
            current->ext.main_12.unk88 = 1;
        }
    } else if (arg0->unk24 < 0) {
        arg0->unk24 = FIXED(-0.5);
        arg0->unk2C = -arg0->unk2C;
        current->ext.main_12.unk88 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004BCC8(struct MainObj* arg0)
{
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk7E = 8;
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BCFC);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C210);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C394);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C56C);

void func_8004C654(struct MainObj* arg0)
{
    if (arg0->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004C694(struct MainObj* arg0)
{
    if (arg0->x_pos.val < g_Player.x_pos.val) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

void func_8004C6C4(struct MainObj* arg0)
{
    s16 object_x;
    s16 distance;

    if ((arg0->unk7C != 0) && (arg0->unk5 == 2)) {
        object_x = arg0->x_pos.i.hi;
        if ((g_Player.x_pos.i.hi - object_x) >= 0) {
            distance = g_Player.x_pos.i.hi - object_x;
        } else {
            distance = object_x - g_Player.x_pos.i.hi;
        }
        if (distance < 0x90) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
        }
    }
}

union AnimationStep D_800FB570[] = {
    { 0x0001000A },
    { 0x0101001C },
    { 0x02FE000F },
};

union AnimationStep D_800FB57C[] = {
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06FD0004 },
};

union AnimationStep D_800FB58C[] = {
    { 0x07010001 },
    { 0x07FF0003 },
};

union AnimationStep D_800FB594[] = {
    { 0x08010006 },
    { 0x09010006 },
    { 0x0AFE0006 },
};

union AnimationStep D_800FB5A0[] = {
    { 0x0B010005 },
    { 0x0C010006 },
    { 0x0DFE0106 },
};

union AnimationStep D_800FB5AC[] = {
    { 0x0E010006 },
    { 0x0F010006 },
    { 0x10010105 },
    { 0x11010104 },
    { 0x12010106 },
    { 0x0B018106 },
    { 0x0C018106 },
    { 0x13010106 },
    { 0x14010006 },
    { 0x15010005 },
    { 0x16F60004 },
};

union AnimationStep D_800FB5D8[] = {
    { 0x17010008 },
    { 0x18FF010C },
};

union AnimationStep D_800FB5E0[] = {
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010008 },
    { 0x1BFF0101 },
};

union AnimationStep D_800FB5F0[] = {
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x1B010002 },
    { 0x20FE0002 },
};

union AnimationStep D_800FB60C[] = {
    { 0x0B010002 },
    { 0x0CFF0002 },
};

union AnimationStep D_800FB614[] = {
    { 0x0D010006 },
    { 0x0DFF0101 },
};

union AnimationStep D_800FB61C[] = {
    { 0x21000001 },
};

union AnimationStep D_800FB620[] = {
    { 0x22000001 },
};

union AnimationStep D_800FB624[] = {
    { 0x23000001 },
};

union AnimationStep D_800FB628[] = {
    { 0x24000001 },
};

union AnimationStep D_800FB62C[] = {
    { 0x25010001 },
    { 0x26010001 },
    { 0x25010001 },
    { 0x27FD0001 },
};

union AnimationStep* D_800FB63C[] = {
    D_800FB570,
    D_800FB57C,
    D_800FB58C,
    D_800FB594,
    D_800FB5A0,
    D_800FB5AC,
    D_800FB5D8,
    D_800FB5E0,
    D_800FB5F0,
    D_800FB60C,
    D_800FB614,
    D_800FB61C,
    D_800FB620,
    D_800FB624,
    D_800FB628,
    D_800FB62C,
};

u8 D_800FB67C[] = {
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
    0x00,
    0x00,
};

struct Unk_unk68 D_800FB684 = { -2, 3, 18, 4 };

struct Unk_unk68 D_800FB688 = { -12, -2, 21, 11 };

struct Unk_unk68 D_800FB68C = { -16, -9, 34, 20 };

struct Unk_unk68 D_800FB690 = { 0, -5, 7, 17 };

struct Unk_unk68 D_800FB694 = { -7, -18, 13, 28 };

struct Unk_unk68 D_800FB698 = { -8, -24, 15, 38 };

struct Unk_unk68 D_800FB69C = { -5, 0, 17, 9 };

struct Unk_unk68 D_800FB6A0 = { -10, -15, 11, 31 };

struct Unk_unk68 D_800FB6A4 = { -15, -27, 25, 54 };

void (*D_800FB6A8[])(struct MainObj*) = {
    func_8004B8FC,
    func_8004BAF8,
    func_8004C654,
};

void (*D_800FB6B4[9])() = {
    func_8009216C,
    func_8004BC14,
    func_8004BC2C,
    func_8004BCC8,
    func_8004BCFC,
    func_8004BF5C,
    func_8004C210,
    func_8004C394,
    func_8004C56C,
};

u16 D_800FB6D8[18] = {
    0x0010,
    0x0010,
    0x0010,
    0x0010,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0080,
    0x0080,
    0x0080,
    0x0080,
    0x00A0,
    0x00A0,
    0x00C0,
    0x0000,
};
