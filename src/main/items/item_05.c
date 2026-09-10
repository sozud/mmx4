// ItemObj, item_object_update_funcs[5]
// 800C0E74..800C1390
#include "common.h"

struct Item05AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item05MotionConfig {
    u32 collision_mode;
    s32 velocity;
    s16 acceleration;
    s16 unused;
};

struct Item05StageConfig {
    u16 tile;
    u16 index;
    u16 x;
    u16 y;
};

struct Item05AnimationStep D_8010C928[11] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 2 },
    { 3, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 0xF6, 10 },
};

struct Item05AnimationStep D_8010C954[8] = {
    { 3, 0, 1, 11 },
    { 3, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 0xF9, 18 },
};

struct Item05AnimationStep D_8010C974[8] = {
    { 4, 0, 1, 19 },
    { 4, 0, 1, 20 },
    { 4, 0, 1, 21 },
    { 4, 0, 1, 22 },
    { 4, 0, 1, 23 },
    { 4, 0, 1, 22 },
    { 4, 0, 1, 21 },
    { 4, 0, 0xF9, 20 },
};

struct Item05AnimationStep D_8010C994[8] = {
    { 3, 0, 1, 24 },
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 0xF9, 31 },
};

struct Item05AnimationStep* D_8010C9B4[4] = {
    D_8010C928,
    D_8010C954,
    D_8010C974,
    D_8010C994,
};

struct Item05MotionConfig D_8010C9C4[9] = {
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
};

struct Item05StageConfig D_8010CA30[9] = {
    { 0x0541, 0, 0x10A0, 0x04E0 },
    { 0x0541, 1, 0x1110, 0x04C0 },
    { 0x0541, 2, 0x1178, 0x04A0 },
    { 0x0541, 3, 0x11D8, 0x0480 },
    { 0x0541, 4, 0x1218, 0x0430 },
    { 0x0541, 5, 0x1318, 0x0420 },
    { 0x0541, 6, 0x1378, 0x03E0 },
    { 0x0541, 7, 0x13E8, 0x03B0 },
    { 0x0541, 8, 0x1478, 0x0350 },
};

u8 D_8010CA78[9][4] = {
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 0, 0x10, 0x20 },
    { 0, 0, 0x10, 0x20 },
    { 0, 0, 0x10, 0x20 },
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 0, 0x10, 0x20 },
};

void func_800C0E74(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CA9C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_05", func_800C0EBC);

INCLUDE_ASM("main/nonmatchings/items/item_05", func_800C1050);

void func_800C1224(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_05", func_800C1244);

INCLUDE_ASM("main/nonmatchings/items/item_05", func_800C1318);

void (*D_8010CA9C[])(struct ItemObj*) = {
    func_800C0EBC,
    func_800C1050,
    func_800C1224,
};
