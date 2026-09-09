// ItemObj, item_object_update_funcs[7]
// 800C16F0..800C1994
#include "common.h"

INCLUDE_ASM("main/nonmatchings/items/item_07", func_800C16F0);

INCLUDE_ASM("main/nonmatchings/items/item_07", func_800C1820);

void func_800C1938(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C1958(struct ItemObj* arg0)
{
    D_8010CB5C[arg0->state](arg0);
}

void (*D_8010CB5C[])(struct ItemObj*) = {
    func_800C16F0,
    func_800C1820,
    func_800C1938,
};
