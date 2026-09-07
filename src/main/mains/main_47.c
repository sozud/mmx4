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

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_800672EC);
