// QuadObj, quad_object_update_funcs[3]
// 800D514C..800D526C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_03", func_800D514C);

void func_800D5210(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D5230(struct QuadObj* arg0)
{
    D_8010F898[arg0->state](arg0);
}
