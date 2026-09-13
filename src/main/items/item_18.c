// ItemObj, item_object_update_funcs[18]
// 800C4544..800C470C
#include "common.h"

void func_800C4544(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D1CC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_18", func_800C458C);

void func_800C460C(struct ItemObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if ((0x188 - (arg0->unk2 << 6)) < arg0->y_pos.i.hi) {
        func_8001540C(2, 0x88, arg0);
        arg0->state = 2;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x60);
}

void func_800C4678(struct ItemObj* arg0)
{
    if (arg0->unk2 != 2) {
        func_800DABE4(
            0xC,
            (s16)(arg0->x_pos.u.hi - 0x10),
            (s16)(arg0->y_pos.u.hi - 0x30));
    } else {
        func_800DABE4(
            0xD,
            (s16)(arg0->x_pos.u.hi - 0x10),
            (s16)(arg0->y_pos.u.hi - 0x70));
    }

    func_80028BAC(0x10, 4, 2);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010D1CC[])(struct ItemObj*) = {
    func_800C458C,
    func_800C460C,
    func_800C4678,
};
