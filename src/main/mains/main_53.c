// MainObj, main_object_update_funcs[53]
// 8006AF70..8006BB00
#include "common.h"

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
