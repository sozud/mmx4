// QuadObj, quad_object_update_funcs[5]
// 800D553C..800D5934
#include "common.h"

void func_800D553C(struct QuadObj* arg0)
{
    D_8010FAD4[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_05", func_800D5578);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_05", func_800D55E4);

void func_800D56A8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_05", func_800D56C8);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_05", func_800D57A8);
