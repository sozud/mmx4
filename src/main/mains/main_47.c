// MainObj, main_object_update_funcs[47]
// 80066DAC..80067350
#include "common.h"

void func_80066DAC(struct MainObj* arg0)
{
    D_800FFA0C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_80066DE8);

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_80066F1C);

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_800671D8);

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_800672BC);

void func_800672D8(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 1;
}

void func_800672EC(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        if (arg0->x_pos.i.hi >= 0x1AA1) {
            arg0->unk6 = 1;
            return;
        }
        func_8002B718(MOVING_OBJECT(arg0));
        return;
    }
    arg0->unk42 &= 0x7FFF;
}
