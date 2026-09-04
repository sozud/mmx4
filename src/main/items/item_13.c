// ItemObj, item_object_update_funcs[13]
// 800C351C..800C3880
#include "common.h"

void func_800C351C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D030[arg0->base.state](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_13", func_800C3578);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_13", func_800C369C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_13", func_800C36E8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_13", func_800C37C4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_13", func_800C3828);

void (*D_8010D030[])(struct ItemObj*) = {
    func_800C3578,
    func_800C369C,
    func_800C3828,
};
