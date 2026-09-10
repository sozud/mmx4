// ItemObj, item_object_update_funcs[22]
// 800C5544..800C5C4C
#include "common.h"

struct Item22LayoutDescriptor {
    u8 start;
    u8 length;
    u16 unused;
    u8* data;
};

struct Item22AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u8 D_8010D25C[8] = { 0x3E, 0x3F, 0x43, 0x0B, 0x0C, 0, 0, 0 };
u8 D_8010D264[8] = { 0x08, 0x09, 0x44, 0x41, 0x42, 0, 0, 0 };
u8 D_8010D26C[8] = { 0x3E, 0x3F, 0x40, 0x41, 0x42, 0, 0, 0 };
u8 D_8010D274[4] = { 0x45, 0x46, 0, 0 };
u8 D_8010D278[4] = { 0x47, 0x48, 0, 0 };
u8 D_8010D27C[4] = { 0x49, 0x4A, 0x4B, 0 };
u8 D_8010D280[4] = { 0x4C, 0x4D, 0x4E, 0 };

struct Item22LayoutDescriptor D_8010D284[7] = {
    { 4, 5, 0, D_8010D25C },
    { 4, 5, 0, D_8010D264 },
    { 4, 5, 0, D_8010D26C },
    { 0x0B, 2, 0, D_8010D274 },
    { 0x0D, 2, 0, D_8010D278 },
    { 0x0F, 3, 0, D_8010D27C },
    { 0x13, 3, 0, D_8010D280 },
};

u8 D_8010D2BC[4] = { 0, 0, 8, 8 };
u8 D_8010D2C0[4] = { 0xF8, 0xF8, 0x10, 0x10 };
u8 D_8010D2C4[4] = { 3, 6, 4, 5 };

struct Item22AnimationStep D_8010D2C8[10] = {
    { 1, 1, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
    { 1, 0, 0, 7 },
    { 1, 0, 0, 8 },
    { 1, 0, 0, 9 },
};

struct Item22AnimationStep* D_8010D2F0[10] = {
    &D_8010D2C8[0],
    &D_8010D2C8[1],
    &D_8010D2C8[2],
    &D_8010D2C8[3],
    &D_8010D2C8[4],
    &D_8010D2C8[5],
    &D_8010D2C8[6],
    &D_8010D2C8[7],
    &D_8010D2C8[8],
    &D_8010D2C8[9],
};

void func_800C5544(struct ItemObj* arg0)
{
    D_8010D318[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5580);

void func_800C56B4(struct ItemObj* arg0)
{
    D_8010D328[arg0->unk5](arg0);
}

void func_800C56F0(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5710);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5774);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C580C);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5904);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5994);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5B5C);

INCLUDE_ASM("main/nonmatchings/items/item_22", func_800C5BCC);

void (*D_8010D318[])(struct ItemObj*) = {
    func_800C5580,
    func_800C56B4,
    func_800C56F0,
    func_800C5710,
};

void (*D_8010D328[2])(struct ItemObj*) = {
    func_800C5774,
    func_800C580C,
};

s32 D_8010D330[4] = { 0, 1, 2, 3 };
