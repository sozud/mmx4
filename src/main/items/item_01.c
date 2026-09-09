// ItemObj, item_object_update_funcs[1]
// 800BEBB4..800BF730
#include "common.h"

void func_800BEBB4(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010C2F0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BEBFC);

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BED6C);

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BEED4);

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BEFCC);

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BF1FC);

void func_800BF508(struct ItemObj* self)
{
    if ((self->unk2 == 5) || (self->unk2 == 0xD)) {
        self->state = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BF530);

void func_800BF5EC(struct ItemObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3);

void func_800BF60C(struct BaseObj* arg0, s8 arg1)
{
    func_800BF638(arg0, arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}

INCLUDE_ASM("main/nonmatchings/items/item_01", func_800BF638);

void (*D_8010C2F0[])(struct ItemObj*) = {
    func_800BEBFC,
    func_800BED6C,
    func_800BF530,
    func_800BF5EC,
};
