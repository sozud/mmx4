// MainObj, main_object_update_funcs[24]
// 80056788..80057100
#include "common.h"

void func_80056788(struct MainObj* arg0)
{
    D_800FCFA8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_800567C4);

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_80056AC4);

void func_80056BA8(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.main_24.unk80 = 0;
    arg0->ext.main_24.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80056BD0(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_24.saved_unk5;
}

void func_80056BDC(struct MainObj* arg0)
{
    D_800FCFC4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_80056C18);

void func_80056D20(struct MainObj* arg0)
{
    s32 direction;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        direction = arg0->unk2 & 3;
        arg0->unk2C = (direction < 2) ? FIXED(0.1875) : FIXED(-0.1875);
    }
    if (arg0->unk20 == 0) {
        arg0->unk7C = 0xA;
        arg0->unk28 >>= 2;
        func_80015D60(arg0, 2);
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_80056DB4);

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_80056EF4);

void func_800570A4(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0xA1) {
        func_8001540C(2, 0x50, arg0);
        arg0->unk7A = 0;
        arg0->unk5 = 2;
    }
}
