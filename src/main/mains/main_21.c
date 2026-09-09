// MainObj, main_object_update_funcs[21]
// 80054C50..80054FE8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054C50);

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054CA8);

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054D8C);

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054EF8);

void func_80054F14(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054F34);

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054F98);

void func_80054FBC(struct MainObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054FDC);
