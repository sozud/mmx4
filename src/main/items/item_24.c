// ItemObj, item_object_update_funcs[24]
// 800C6054..800C62DC
#include "common.h"

void func_800C6054(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D3AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_24", func_800C609C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_24", func_800C6198);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_24", func_800C6228);

void (*D_8010D3AC[])(struct ItemObj*) = {
    func_800C609C,
    func_800C6198,
    func_800C6228,
};
