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

void func_800D56C8(struct QuadObj* arg0)
{
    s32* p = arg0->ext.quad_5.data;

    arg0->unk14.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk18.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk1C.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk20.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk24.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk28.val = *p++ * arg0->ext.quad_5.unk3C;
    arg0->unk2C.val = p[0] * arg0->ext.quad_5.unk3C;
    arg0->unk30.val = p[1] * arg0->ext.quad_5.unk3C;
}

INCLUDE_ASM("main/nonmatchings/quads/quad_05", func_800D57A8);
