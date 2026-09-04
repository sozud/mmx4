// ItemObj, item_object_update_funcs[3]
// 800C0404..800C081C
#include "common.h"

void func_800C0404(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010C8A4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_03", func_800C044C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_03", func_800C0558);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_03", func_800C05FC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_03", func_800C07B8);

void (*D_8010C8A4[])(struct ItemObj*) = {
    func_800C044C,
    func_800C0558,
    func_800C05FC,
    func_800C07B8,
};
