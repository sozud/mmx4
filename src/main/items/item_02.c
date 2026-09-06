// ItemObj, item_object_update_funcs[2]
// 800BF730..800C0404
#include "common.h"

void func_800BF730(struct ItemObj* arg0)
{
    D_8010C730[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BF76C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFA00);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFB90);

void func_800BFBB0(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFBD0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFF0C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800C00BC);

void func_800C03BC(s8 arg0)
{
    engine_obj.unk10 = arg0;
    engine_obj.unk11 = arg0;
    engine_obj.unk12 = arg0;
    engine_obj.unk13 = arg0;
    engine_obj.unk14 = arg0;
    engine_obj.unk15 = arg0;
    engine_obj.unk16 = arg0;
    engine_obj.unk17 = arg0;
}

void (*D_8010C730[])(struct ItemObj*) = {
    func_800BF76C,
    func_800BFA00,
    func_800BFB90,
    func_800BFBB0,
};
