// UnkObj, unk_object_update_funcs[1]
// 800D3964..800D3AC0
#include "common.h"

void func_800D3964(struct UnkObj* arg0)
{
    s16 var_v0;
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->base.bg_offset = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->base.unk15 = 0;
    if (arg0->base.y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->base.x_pos.i.hi = 0xA0;
    arg0->base.unk16 = 0;
    arg0->unk47 = arg0->base.unk2;
    arg0->base.state++;
    is_on_screen(arg0);
}

void func_800D39EC(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->base.y_pos.i.hi != 0x10) {
        if (arg0->base.unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        temp_v1 = arg0->base.unk7;
        if ((arg0->base.unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    is_on_screen(arg0);
}

void func_800D3A84(struct UnkObj* arg0)
{
    arg0->base.on_screen = 0;
    D_8010F5F8[arg0->base.state](arg0);
}
