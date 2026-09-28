// QuadObj, quad_object_update_funcs[8]
// 800D67A0..800D67DC
#include "common.h"

// QuadObj #8
void func_800D67A0(struct QuadObj* arg0)
{
    D_8010FCAC[arg0->state](arg0);
}

void (*D_8010FCAC[])(struct QuadObj*) = {
    func_800D6694,
    func_800D6700,
    func_800D6780,
};
