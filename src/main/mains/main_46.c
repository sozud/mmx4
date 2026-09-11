// MainObj, main_object_update_funcs[46]
// 80066A48..80066DAC
#include "common.h"

void func_80066A48(struct MainObj* arg0)
{
    D_800FF9A4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_46", func_80066A84);

INCLUDE_ASM("main/nonmatchings/mains/main_46", func_80066B00);

void func_80066C40(struct MainObj* arg0)
{
    func_8002B318(arg0, 0x100, 0x100);
}

void func_80066C64(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_80066C74(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        if (arg0->x_pos.i.hi >= 0x1AA1) {
            arg0->unk7C = 0x78;
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            return;
        }
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_46", func_80066CCC);
