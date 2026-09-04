// ItemObj, item_object_update_funcs[8]
// 800C1994..800C20AC
#include "common.h"

void func_800C1994(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010CC64[arg0->base.state](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C19F0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1B54);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1B98);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1C24);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1C88);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1D90);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1E10);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1E7C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C1FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_08", func_800C204C);

void (*D_8010CC64[])(struct ItemObj*) = {
    func_800C19F0,
    func_800C1B54,
    func_800C1FE4,
};
