// ItemObj, item_object_update_funcs[6]
// 800C1390..800C16F0
#include "common.h"

void func_800C1390(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CAA8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_06", func_800C13D8);

INCLUDE_ASM("main/nonmatchings/items/item_06", func_800C14F0);

INCLUDE_ASM("main/nonmatchings/items/item_06", func_800C1590);

void func_800C165C(struct ItemObj* arg0)
{
    func_80036AE4(0x15, 0x40);
    arg0->state++;
}

INCLUDE_ASM("main/nonmatchings/items/item_06", func_800C169C);

void (*D_8010CAA8[])(struct ItemObj*) = {
    func_800C13D8,
    func_800C14F0,
    func_800C1590,
    func_800C165C,
    func_800C169C,
};

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u8 D_8010CABC[2][8] = {
    { 0x08, 0x00, 0x08, 0x38, 0x00, 0xC8, 0x08, 0x70 },
    { 0xF8, 0x00, 0x08, 0x38, 0x00, 0xC8, 0x08, 0x70 },
};

u8* D_8010CACC[2] = { D_8010CABC[0], D_8010CABC[1] };
u8* D_8010CAD4[2] = { &D_8010CABC[0][4], &D_8010CABC[1][4] };

struct Item06AnimationStep D_8010CADC[6] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
};

struct Item06AnimationStep* D_8010CAF4[5] = {
    &D_8010CADC[1],
    &D_8010CADC[2],
    &D_8010CADC[3],
    &D_8010CADC[4],
    &D_8010CADC[5],
};

u8 D_8010CB08[3][4] = {
    { 0, 1, 4, 3 },
    { 4, 2, 3, 2 },
    { 2, 3, 4, 0 },
};

u32 D_8010CB14[4] = { 0, 1, 2, 3 };
s16 D_8010CB24[2] = { 0x18C0, 0x18E8 };
u16 D_8010CB28[2] = { 0x1028, 0x1028 };

struct Item06AnimationStep D_8010CB2C[5] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
};

struct Item06AnimationStep* D_8010CB40[5] = {
    &D_8010CB2C[0],
    &D_8010CB2C[1],
    &D_8010CB2C[2],
    &D_8010CB2C[3],
    &D_8010CB2C[4],
};

u8 D_8010CB54[2][4] = {
    { 1, 4, 3, 2 },
    { 3, 1, 2, 4 },
};
