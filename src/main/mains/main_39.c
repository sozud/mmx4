// MainObj, main_object_update_funcs[39]
// 80061590..80061DC0
#include "common.h"

void func_80061590(struct MainObj* arg0)
{
    D_800FE9A4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_800615CC);

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_8006185C);

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_800618F4);

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_80061918);

void func_80061AA8(struct MainObj* arg0)
{
    D_800FE9BC[arg0->unk6](arg0);
}

void func_80061AE4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi >= 0x119) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7C = 0x3C;
        func_80015D60(arg0, 2);
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_80061B58);

void func_80061D18(struct MainObj* arg0)
{
    u8 object_id;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    object_id = arg0->unk2;
    if (!(object_id & 1)) {
        func_800DABE4((s8)object_id / 2, arg0->ext.main_39.unk82, 0x120);
    }
    arg0->ext.main_39.unk88 = 1;
    arg0->unk2C = FIXED(0.125);
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_80061D90);
