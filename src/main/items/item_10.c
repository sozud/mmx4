// ItemObj, item_object_update_funcs[10]
// 800C24E0..800C2BE0
#include "common.h"

void func_800C24E0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CE34[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2528);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2638);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C27D8);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2850);

void func_800C28E8(struct ItemObj* arg0)
{
    func_80015DC8(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2918);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2A04);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2AF0);

void (*D_8010CE34[])(struct ItemObj*) = {
    func_800C2528,
    func_800C2638,
    func_800C27D8,
    func_800C2850,
    func_800C28E8,
    func_800C2918,
};
