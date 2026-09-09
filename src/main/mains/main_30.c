// MainObj, main_object_update_funcs[30]
// 8005B3FC..8005B894
#include "common.h"

void func_8005B3FC(struct MainObj* arg0)
{
    D_800FD9C4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B438);

void func_8005B504(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    func_80015D60(arg0, 10);
}

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B52C);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B578);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B64C);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B708);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B760);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B7AC);

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B818);
