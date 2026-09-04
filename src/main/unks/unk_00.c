// UnkObj, unk_object_update_funcs[0]
// 800D3928..800D3964
#include "common.h"

void func_800D3928(struct UnkObj* arg0)
{
    arg0->base.on_screen = 0;
    D_8010F5E8[arg0->base.state](arg0);
}
