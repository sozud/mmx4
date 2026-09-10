// ItemObj, item_object_update_funcs[23]
// 800C5C4C..800C6054
#include "common.h"

void func_800C5C4C(struct ItemObj* arg0)
{
    D_8010D344[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_23", func_800C5C88);

INCLUDE_ASM("main/nonmatchings/items/item_23", func_800C5D44);

void func_800C5F04(struct ItemObj* arg0)
{
    arg0->unk5++;
    func_80015DC8(arg0);
}

void func_800C5F30(struct ItemObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800C5F50(struct ItemObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800C5F70(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_23", func_800C5F90);

u8 D_8010D340[4] = { 0, 0, 4, 4 };

void (*D_8010D344[])(struct ItemObj*) = {
    func_800C5C88,
    func_800C5F90,
    func_800C5F70,
};

void (*D_8010D350[])(struct ItemObj*) = {
    func_800C5D44,
    func_800C5F04,
    func_800C5F50,
    func_800C5F30,
};
