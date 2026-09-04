// ItemObj, item_object_update_funcs[11]
// 800C2BE0..800C3224
#include "common.h"

void func_800C2BE0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010CFAC[arg0->base.state](arg0);
    func_8002E184(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2E00);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2E20);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2F18);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C2F54);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C3030);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C3114);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C3198);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_11", func_800C31C4);

void (*D_8010CFAC[])(struct ItemObj*) = {
    func_800C2C3C,
    func_800C2D6C,
    func_800C2DE0,
    func_800C2E00,
};
