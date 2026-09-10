// ItemObj, item_object_update_funcs[16]
// 800C3FEC..800C413C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/items/item_16", func_800C3FEC);

void func_800C40A4(struct ItemObj* arg0)
{
    arg0->unk16 = 6;
    arg0->unk68 = &D_8010D0FC;
    arg0->x_vel.val = FIXED(1);
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk54 = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
}

INCLUDE_ASM("main/nonmatchings/items/item_16", func_800C40F0);
