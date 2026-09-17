// ItemObj, item_object_update_funcs[12]
// 800C3224..800C351C
#include "common.h"

void func_800C3224(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CFE0[arg0->state](arg0);
    arg0->x_pos.val -= arg0->ext.packed;
    func_8002E184(arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x30, 0);
    } else {
        arg0->state = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C32BC);

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C3364);

void func_800C3438(struct ItemObj* arg0)
{
    if (func_800C34F0(arg0) && (g_Player.unk70 & 8)) {
        g_Player.unk5C = -0x80;
    }
}

void func_800C3484(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C34A4(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->ext.item_12.x_offset += 0x100;
    } else {
        arg0->ext.item_12.x_offset += 0x200;
    }
}

void func_800C34D4(struct ItemObj* arg0)
{
    arg0->unk5++;
}

void func_800C34E8(struct ItemObj* arg0)
{
}

u8 func_800C34F0(struct MainObj* arg0)
{
    s32 player_x;
    s32 object_x;
    object_x = arg0->x_pos.i.hi;
    player_x = g_Player.x_pos.i.hi;
    if (object_x - 0x30 < player_x && player_x < object_x + 0x30) {
        return 1;
    }
    return 0;
}

void (*D_8010CFE0[])(struct ItemObj*) = {
    func_800C32BC,
    func_800C3364,
    func_800C3438,
    func_800C3484,
};

void (*D_8010CFF0[])(struct ItemObj*) = {
    func_800C34A4,
    func_800C34D4,
    func_800C34E8,
};

u8 D_8010CFFC[4] = { 0, 0, 0x30, 0x38 };
u16 D_8010D000[4] = { 0x0900, 0x0D60, 0x13F0, 0x1A80 };
