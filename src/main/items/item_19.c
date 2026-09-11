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

void func_800C470C(struct ItemObj* arg0)
{
    if (arg0->unk2 >= 0) {
        D_8010D1F4[arg0->state](arg0);
    } else {
        D_8010D200[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C4778);

INCLUDE_ASM("main/nonmatchings/items/item_19", func_800C49BC);

void func_800C4BE4(struct ItemObj* arg0)
{
}

void func_800C4BEC(struct ItemObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk54 = 0;
    arg0->unk50 = 0;
    arg0->unk68 = NULL;
    arg0->unk67 = 0;
    arg0->unk76 = 0;
    arg0->unk75 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 4;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_80015D60(arg0, 1);
}

void func_800C4C64(struct ItemObj* arg0)
{
    struct MainObj* owner;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    owner = arg0->ext.owner;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    if (owner->unk5 == 5) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}
