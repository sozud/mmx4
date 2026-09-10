// ItemObj, item_object_update_funcs[24]
// 800C6054..800C62DC
#include "common.h"

struct Item24AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item24AnimationStep D_8010D360[7] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
};

struct Item24AnimationStep* D_8010D37C[7] = {
    &D_8010D360[0],
    &D_8010D360[1],
    &D_8010D360[2],
    &D_8010D360[3],
    &D_8010D360[4],
    &D_8010D360[5],
    &D_8010D360[6],
};

u8 D_8010D398[12] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 0, 0 };
u8 D_8010D3A4[4] = { 0, 0, 0x17, 0x26 };
u32 D_8010D3A8 = 0x4927DBEC;

void func_800C6054(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D3AC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_24", func_800C609C);

INCLUDE_ASM("main/nonmatchings/items/item_24", func_800C6198);

INCLUDE_ASM("main/nonmatchings/items/item_24", func_800C6228);

void (*D_8010D3AC[])(struct ItemObj*) = {
    func_800C609C,
    func_800C6198,
    func_800C6228,
};

u32 D_8010D3B8[4] = { 0, 1, 2, 3 };
