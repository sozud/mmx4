// QuadObj, quad_object_update_funcs[5]
// 800D553C..800D5934
#include "common.h"

void func_800D553C(struct QuadObj* arg0)
{
    D_8010FAD4[arg0->state](arg0);
}

void func_800D5578(struct QuadObj* arg0)
{
    arg0->unk36 = 4;
    arg0->unk34 = 0x7EC0;
    arg0->state = 1;
    arg0->ext.quad_5.unk3C = 0x100;
    arg0->ext.quad_5.index = 0;
    arg0->bg_offset = 0;
    arg0->ext.quad_5.unk3E = 0;
    arg0->active |= 0x80;
    arg0->ext.quad_5.data = D_8010FAB4[arg0->ext.quad_5.index];
    func_800D56C8(arg0);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_05", func_800D55E4);

void func_800D56A8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_05", func_800D56C8);

INCLUDE_ASM("main/nonmatchings/quads/quad_05", func_800D57A8);
