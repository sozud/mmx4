// ItemObj, item_object_update_funcs[19]
// 800C470C..800C4CE4
#include "common.h"

struct Item19SpawnPosition {
    u16 x;
    u16 y;
};

struct Item19SpawnPosition D_8010D1D8[4] = {
    { 0x07B0, 0x022C },
    { 0x07B0, 0x03A0 },
    { 0x07B0, 0x0458 },
    { 0x07B0, 0x05D8 },
};

u8 D_8010D1E8[4] = { 0, 0xFE, 0x29, 8 };
u8 D_8010D1EC[4] = { 0, 4, 0x29, 0x0B };
u8 D_8010D1F0[4] = { 0, 4, 0x29, 0x0B };

void (*D_8010D1F4[])(struct ItemObj*) = {
    func_800C4778,
    func_800C49BC,
    func_800C4BE4,
};

void (*D_8010D200[])(struct ItemObj*) = {
    func_800C4BEC,
    func_800C4C64,
    func_800C4BE4,
};

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C470C);

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C4778);

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C49BC);

void func_800C4BE4(struct ItemObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C4BEC);

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C4C64);
