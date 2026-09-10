// ItemObj, item_object_update_funcs[15]
// 800C3CF8..800C3FEC
#include "common.h"

void func_800C3CF8(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D070[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_15", func_800C3D40);

INCLUDE_ASM("main/nonmatchings/items/item_15", func_800C3E4C);

INCLUDE_ASM("main/nonmatchings/items/item_15", func_800C3F98);

void (*D_8010D070[])(struct ItemObj*) = {
    func_800C3D40,
    func_800C3E4C,
    func_800C3F98,
};

u8 D_8010D07C[4][16] = {
    { 0x00, 0xD8, 0x30, 0x28 },
    { 0x00, 0x28, 0x30, 0x28 },
    { 0x00, 0xD8, 0x30, 0x30 },
    { 0x00, 0x30, 0x30, 0x28 },
};

u8 D_8010D0BC[4][16] = {
    { 0x00, 0xB8, 0x30, 0x10 },
    { 0x00, 0x48, 0x30, 0x10 },
    { 0x00, 0xC0, 0x30, 0x10 },
    { 0x00, 0x40, 0x30, 0x10 },
};
