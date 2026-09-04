// QuadObj, quad_object_update_funcs[6]
// 800D5934..800D5C54
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_06", func_800D5934);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_06", func_800D5AB0);

void func_800D5BF8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D5C18(struct QuadObj* arg0)
{
    D_8010FAE0[arg0->state](arg0);
}
