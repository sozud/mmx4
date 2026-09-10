// UnkObj, unk_object_update_funcs[0]
// 800D3928..800D3964
#include "common.h"

void func_800D3928(struct UnkObj* arg0)
{
    arg0->on_screen = 0;
    D_8010F5E8[arg0->state](arg0);
}

void (*D_8010F5E8[4])(struct UnkObj*) = {
    func_800D36AC,
    func_800D3700,
    func_800D3798,
    func_800D38A0,
};
