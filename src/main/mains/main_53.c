// MainObj, main_object_update_funcs[53]
// 8006AF70..8006BB00
#include "common.h"
#include "func_tables.h"

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006AF70);

void func_8006B114(struct MainObj* arg0)
{
    if (arg0->x_pos.val < background_objects[arg0->bg_offset].x_pos.val - 0x20) {
        if (arg0->unk2 == 2) {
            arg0->unk5 = 5;
        } else {
            arg0->unk5 = 2;
        }
        arg0->state++;
    }
}

void func_8006B180(struct MainObj* arg0)
{
    D_801001C8[arg0->unk5](arg0);
}

void func_8006B1BC(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B1C4);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B2A4);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B398);

void func_8006B514(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_8006B2A4(arg0);
    } else {
        func_8006B398(arg0);
    }
    func_8002B694(arg0);
}

s32 func_8006B568(struct MainObj* arg0)
{
    s32 background_x;
    s32 x;
    s32 distance;

    arg0->ext.main_53.unk84 = 1;
    func_8006B514(arg0);
    if (arg0->unk67 != 0) {
        return 0;
    }
    background_x = background_objects[arg0->bg_offset].x_pos.val;
    x = arg0->x_pos.val - FIXED(64);
    distance = x - background_x;
    if (distance < 0) {
        distance = background_x - x;
    }
    return distance <= 0x1FFFF;
}

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B5F8);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B6B0);

void func_8006B79C(struct MainObj* arg0)
{
    if (arg0->x_pos.val - background_objects[arg0->bg_offset].x_pos.val > FIXED(160)) {
        arg0->unk20 = FIXED(5);
        arg0->unk5 = 2;
        func_80015D60(arg0, 0);
    }
    arg0->ext.main_53.unk81 = func_8006B1C4(arg0, 0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B848(struct MainObj* arg0)
{
    func_80015D60(arg0, 2);
    if (arg0->unk2 == 4) {
        arg0->unk20 = FIXED(-1);
    } else {
        arg0->unk20 = FIXED(11);
    }
    arg0->unk24 = FIXED(8);
    arg0->unk2C = FIXED(0.3125);
    arg0->unk67 = 1;
    arg0->unk5 = 6;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B8BC(struct MainObj* arg0)
{
    func_8006B514(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B8F4(struct MainObj* arg0)
{
    s32 destroyed;

    arg0->unk54 = &D_800FFFE8;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk65 = arg0->ext.main_53.unk82;
    destroyed = func_8002DD04(arg0) < 0;
    if (!destroyed) {
        arg0->unk54 = D_800FFFEC;
        arg0->ext.main_53.unk82 = arg0->unk65;
        arg0->unk65 = arg0->ext.main_53.unk83;
        destroyed = func_8002DD04(arg0) < 0;
    }
    if (destroyed) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        func_800C813C(8, D_801001B8, arg0);
        func_800C813C(7, D_801001C0, arg0);
        func_800AF808(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.main_53.unk83 = arg0->unk65;
    D_801001D0[arg0->unk5](arg0);
    if ((u8)func_8006B1C4(arg0, 1) == 0x24) {
        if (arg0->ext.main_53.unk85 == 0) {
            arg0->x_pos.i.hi -= 8;
            arg0->y_pos.i.hi += 0x10;
            func_800C7B80(arg0, 4);
            arg0->ext.main_53.unk85 = 2;
            arg0->x_pos.i.hi += 8;
            arg0->y_pos.i.hi -= 0x10;
        } else {
            arg0->ext.main_53.unk85--;
        }
    } else {
        arg0->ext.main_53.unk85 = 0;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        arg0->unk5 = 0;
        arg0->state++;
    }
}

void func_8006BAA4(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8006BAC4(struct MainObj* arg0)
{
    D_801001EC[arg0->state](arg0);
}

struct Unk_unk68 D_800FFFE4 = { -7, 15, 33, 11 };

struct Unk_unk68 D_800FFFE8 = { -40, -5, 50, 29 };

struct Unk_unk68 D_800FFFEC[2] = {
    { -14, -16, 39, 39 },
    { -40, -16, 65, 41 },
};

struct Unk_unk68 D_800FFFF4 = { -30, -10, 49, 30 };

union AnimationStep D_800FFFF8[] = {
    { 0x00010002 },
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010001 },
    { 0x00010001 },
    { 0x06010003 },
    { 0x00000101 },
};

union AnimationStep D_80100014[] = {
    { 0x01010002 },
    { 0x07010002 },
    { 0x08010006 },
    { 0x07010001 },
    { 0x01010001 },
    { 0x09010003 },
    { 0x01000001 },
};

union AnimationStep D_80100030[] = {
    { 0x02010002 },
    { 0x0A010002 },
    { 0x0B010006 },
    { 0x0A010001 },
    { 0x02010001 },
    { 0x0C010003 },
    { 0x02000101 },
};

union AnimationStep D_8010004C[] = {
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100058[] = {
    { 0x01010002 },
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100068[] = {
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100070[] = {
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0FFE0001 },
};

union AnimationStep D_8010007C[] = {
    { 0x10010002 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010002 },
    { 0x15010001 },
    { 0x15FA0001 },
};

union AnimationStep D_80100098[] = {
    { 0x16010002 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010002 },
    { 0x1B010001 },
    { 0x1BFA0001 },
};

union AnimationStep D_801000B4[] = {
    { 0x1C010002 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010002 },
    { 0x21010001 },
    { 0x21FA0001 },
};

union AnimationStep D_801000D0[] = {
    { 0x22010002 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010002 },
    { 0x27010001 },
    { 0x27FA0001 },
};

union AnimationStep D_801000EC[] = {
    { 0x28010003 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x2FF80001 },
};

union AnimationStep D_80100110[] = {
    { 0x30000001 },
};

union AnimationStep D_80100114[] = {
    { 0x31000001 },
};

union AnimationStep D_80100118[] = {
    { 0x32000001 },
};

union AnimationStep D_8010011C[] = {
    { 0x33000001 },
};

union AnimationStep D_80100120[] = {
    { 0x34000001 },
};

union AnimationStep D_80100124[] = {
    { 0x35000001 },
};

union AnimationStep D_80100128[] = {
    { 0x36000001 },
};

union AnimationStep D_8010012C[] = {
    { 0x37000001 },
};

union AnimationStep D_80100130[] = {
    { 0x38000001 },
};

union AnimationStep D_80100134[] = {
    { 0x39000001 },
};

union AnimationStep D_80100138[] = {
    { 0x3A000001 },
};

union AnimationStep D_8010013C[] = {
    { 0x3B000001 },
};

union AnimationStep D_80100140[] = {
    { 0x3C000001 },
};

union AnimationStep D_80100144[] = {
    { 0x3D000001 },
};

union AnimationStep D_80100148[] = {
    { 0x3E000001 },
};

union AnimationStep* D_8010014C[27] = {
    D_800FFFF8,
    D_80100014,
    D_80100030,
    D_8010004C,
    D_80100058,
    D_80100068,
    D_8010007C,
    D_80100098,
    D_801000B4,
    D_801000D0,
    D_801000EC,
    D_80100070,
    D_80100110,
    D_80100114,
    D_80100118,
    D_8010011C,
    D_80100120,
    D_80100124,
    D_80100128,
    D_8010012C,
    D_80100130,
    D_80100134,
    D_80100138,
    D_8010013C,
    D_80100140,
    D_80100144,
    D_80100148,
};

u8 D_801001B8[8] = { 12, 13, 14, 15, 16, 17, 18, 19 };

u8 D_801001C0[8] = { 20, 21, 22, 23, 24, 25, 26, 0 };

void (*D_801001C8[2])(struct MainObj*) = {
    func_8006AF70,
    func_8006B114,
};

void (*D_801001D0[7])(struct MainObj*) = {
    func_8009216C,
    func_8006B1BC,
    func_8006B5F8,
    func_8006B6B0,
    func_8006B79C,
    func_8006B848,
    func_8006B8BC,
};

void (*D_801001EC[3])() = {
    func_8006B180,
    func_8006B8F4,
    func_8006BAA4,
};
