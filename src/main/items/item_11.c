// ItemObj, item_object_update_funcs[11]
// 800C2BE0..800C3224
#include "common.h"

struct Item11AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item11AnimationStep D_8010CE70[1] = {
    { 1, 0, 0, 0 },
};

struct Item11AnimationStep D_8010CE74[4] = {
    { 1, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 1, 0, 253, 2 },
};

struct Item11AnimationStep D_8010CE84[19] = {
    { 1, 0, 1, 13 },
    { 1, 0, 1, 14 },
    { 1, 0, 1, 15 },
    { 1, 0, 1, 16 },
    { 1, 0, 1, 17 },
    { 1, 0, 1, 18 },
    { 1, 0, 1, 22 },
    { 1, 0, 1, 23 },
    { 1, 0, 1, 24 },
    { 1, 0, 1, 25 },
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, 1, 28 },
    { 1, 0, 1, 29 },
    { 1, 0, 1, 30 },
    { 1, 0, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, 238, 34 },
};

struct Item11AnimationStep D_8010CED0[18] = {
    { 1, 0, 1, 19 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 20 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 20 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 21 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 21 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 12 },
    { 1, 0, 1, 3 },
    { 1, 1, 0, 4 },
};

struct Item11AnimationStep D_8010CF18[32] = {
    { 1, 0, 1, 3 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 8 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 9 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 9 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 10 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 10 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 11 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 11 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 12 },
    { 1, 0, 1, 4 },
    { 1, 0, 225, 12 },
};

struct Item11AnimationStep* D_8010CF98[5] = {
    D_8010CE70,
    D_8010CE74,
    D_8010CE84,
    D_8010CED0,
    D_8010CF18,
};

void func_800C2BE0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CFAC[arg0->state](arg0);
    func_8002E184(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2C3C);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2D6C);

void func_800C2DE0(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800C2E00(struct ItemObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C2E20(struct ItemObj* arg0)
{
    if ((u8)arg0->unk72 & 8) {
        g_Player.x_pos.u.hi = arg0->x_pos.u.hi;
        g_Player.y_pos.i.hi = ((u16)arg0->y_pos.i.hi - arg0->unk68->unk3) - g_Player.unk68->unk3;
        func_80036AE4(0x14, g_Player.unk15);
        reset_main_and_shots();
        arg0->unk5 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2EAC);

void func_800C2F18(struct ItemObj* arg0)
{
    D_8010CFD0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2F54);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C3030);

void func_800C3114(struct ItemObj* arg0)
{
    struct MainObj* owner;

    owner = arg0->ext.owner;
    if (owner->animation_step.fields.event == 1) {
        func_80015D60(owner, 4);
        arg0->unk7C.misc->ext.misc_11.active = 1;
        arg0->unk84.timer = 0;
        func_80036AE4(0x16, g_Player.unk15);
        func_8001540C(5, 1, NULL);
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_800C3198(struct ItemObj* arg0)
{
    if (++arg0->unk84.timer == 0x32) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C31C4);

void (*D_8010CFAC[])(struct ItemObj*) = {
    func_800C2C3C,
    func_800C2D6C,
    func_800C2DE0,
    func_800C2E00,
};

void (*D_8010CFBC[])(struct ItemObj*) = {
    func_800C2E20,
    func_800C2EAC,
    func_800C2F18,
    func_800C31C4,
};

u8 D_8010CFCC[4] = { 0, 0, 0x1C, 8 };

void (*D_8010CFD0[])(struct ItemObj*) = {
    func_800C2F54,
    func_800C3030,
    func_800C3114,
    func_800C3198,
};
