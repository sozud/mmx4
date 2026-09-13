// ItemObj, item_object_update_funcs[13]
// 800C351C..800C3880
#include "common.h"

struct Item13AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item13AnimationStep D_8010D008[1] = {
    { 8, 0, 0, 0 },
};

struct Item13AnimationStep D_8010D00C[7] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 0x21, 1, 0, 7 },
};

struct Item13AnimationStep* D_8010D028[2] = {
    D_8010D008,
    D_8010D00C,
};

void func_800C351C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D030[arg0->state](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_13", func_800C3578);

void func_800C369C(struct ItemObj* arg0)
{
    struct EngineObj* engine = &engine_obj;
    struct PlayerObj* player = &g_Player;

    if (arg0->unk5 == 0) {
        func_800C36E8(arg0, engine, player);
        return;
    }
    func_800C37C4(arg0, engine, player);
}

INCLUDE_ASM("main/nonmatchings/items/item_13", func_800C36E8);

INCLUDE_ASM("main/nonmatchings/items/item_13", func_800C37C4);

INCLUDE_ASM("main/nonmatchings/items/item_13", func_800C3828);

void (*D_8010D030[])(struct ItemObj*) = {
    func_800C3578,
    func_800C369C,
    func_800C3828,
};

u8 D_8010D03C[4] = { 0, 8, 0x20, 0x10 };
