// ItemObj, item_object_update_funcs[21]
// 800C52CC..800C5544
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_21", func_800C52CC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_21", func_800C53A0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_21", func_800C5444);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_21", func_800C54DC);

void func_800C54FC(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D250[arg0->base.state](arg0);
}

void (*D_8010D250[])(struct ItemObj*) = {
    func_800C52CC,
    func_800C5444,
    func_800C54DC,
};
