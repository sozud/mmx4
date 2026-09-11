// ItemObj, item_object_update_funcs[8]
// 800C1994..800C20AC
#include "common.h"

struct Item08AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item08AnimationStep D_8010CB68[30] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 3, 0, 1, 3 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 4 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 4, 1, 1, 10 },
    { 4, 0, 1, 11 },
    { 4, 2, 0, 12 },
};

struct Item08AnimationStep D_8010CBE0[30] = {
    { 4, 0, 1, 12 },
    { 4, 0, 1, 11 },
    { 4, 1, 1, 10 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 2, 2, 0, 0 },
};

u8 D_8010CC58[4] = { 0, 0, 0x10, 0x20 };

struct Item08AnimationStep* D_8010CC5C[2] = {
    D_8010CB68,
    D_8010CBE0,
};

void func_800C1994(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CC64[arg0->state](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C19F0);

void func_800C1B54(struct ItemObj* arg0)
{
    D_8010CC70[arg0->unk5](arg0, &engine_obj, &g_Player);
}

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1B98);

void func_800C1C24(struct ItemObj* arg0, struct EngineObj* arg1, struct PlayerObj* arg2)
{
    if (arg2->unkC4 < 0) {
        arg1->unk10 = 1;
        arg1->unk12 = 1;
        func_8001540C(0, 0x10, arg0);
        arg2->unk68 = NULL;
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1C88);

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1D90);

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1E10);

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1E7C);

INCLUDE_ASM("main/nonmatchings/items/item_08", func_800C1FE4);

void func_800C204C(struct ItemObj* arg0)
{
    volatile struct PlayerObj* player = &g_Player;

    if (arg0->unk72 & 4) {
        player->unk71 = (u8)(player->unk71 & 0xB);
    }
    if (arg0->unk72 & 8) {
        player->unk71 = (u8)(player->unk71 & 7);
    }
}

void (*D_8010CC64[])(struct ItemObj*) = {
    func_800C19F0,
    func_800C1B54,
    func_800C1FE4,
};

Item08StateFunc D_8010CC70[5] = {
    func_800C1B98,
    func_800C1C24,
    func_800C1C88,
    func_800C1D90,
    func_800C1E10,
};
