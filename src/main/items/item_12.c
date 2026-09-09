// ItemObj, item_object_update_funcs[12]
// 800C3224..800C351C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C3224);

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C32BC);

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C3364);

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C3438);

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

INCLUDE_ASM("main/nonmatchings/items/item_12", func_800C34F0);
