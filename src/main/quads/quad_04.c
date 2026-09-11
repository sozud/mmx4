// QuadObj, quad_object_update_funcs[4]
// 800D526C..800D553C
#include "common.h"

void func_800D526C(struct QuadObj* arg0)
{
    s32 value;

    arg0->unk34 = 2;
    arg0->unk36 = 0;
    arg0->bg_offset = 0;
    arg0->active |= 0x82;
    arg0->ext.quad_4.unk38 = arg0->unk2;
    value = func_8002B780();
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->state++;
    arg0->ext.quad_4.unk39 = value % 3;
}

INCLUDE_ASM("main/nonmatchings/quads/quad_04", func_800D52F4);

void func_800D54A0(struct QuadObj* arg0)
{
    if (arg0->ext.quad_4.timer-- == 0) {
        arg0->state++;
        quad_is_on_screen(arg0);
    }
}

void func_800D54E0(struct QuadObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D5500(struct QuadObj* arg0)
{
    D_8010F9A4[arg0->state](arg0);
}
