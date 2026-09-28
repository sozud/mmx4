// QuadObj, quad_object_update_funcs[3]
// 800D514C..800D526C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/quads/quad_03", func_800D514C);

void func_800D5210(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D5230(struct QuadObj* arg0)
{
    D_8010F898[arg0->state](arg0);
}

u8 D_8010F87C[16] = { 4, 6, 7, 8, 9, 10, 11, 12, 11, 10, 9, 8, 7, 6, 0, 0 };

void (*D_8010F88C[])(struct QuadObj*) = {
    func_800D4DE0,
    func_800D4F84,
    func_800D4FA0,
};

void (*D_8010F898[])(struct QuadObj*) = {
    func_800D4C50,
    func_800D5144,
    func_800D5210,
};
