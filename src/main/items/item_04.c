// ItemObj, item_object_update_funcs[4]
// 800C081C..800C0E74
#include "common.h"

void func_800C081C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010C908[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_04", func_800C0864);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_04", func_800C09C4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_04", func_800C0C78);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_04", func_800C0D98);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_04", func_800C0DFC);

void (*D_8010C908[])(struct ItemObj*) = {
    func_800C0864,
    func_800C09C4,
    func_800C0C78,
    func_800C0D98,
};
