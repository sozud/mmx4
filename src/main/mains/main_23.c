// MainObj, main_object_update_funcs[23]
// 80055E04..80056788
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055E04);

void func_80055E9C(struct MainObj* arg0)
{
    s8 step;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    step = arg0->unk6;
    if (step == 0) {
        arg0->unk6 = step + 1;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk24 = 0;
        arg0->unk67 = -1;
    }
    if (arg0->unk70 & 8) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055F1C);

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055FD0);

void func_80056018(struct MainObj* arg0)
{
    D_800FCE88[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80056054);

void func_80056230(struct MainObj* arg0)
{
    s32 velocity;

    arg0->unk6++;
    func_80055C54();
    velocity = FIXED(-4.5);
    if (arg0->unk15 != 0) {
        velocity = FIXED(4.5);
    }
    arg0->unk20 = velocity;
    func_80015D60(arg0, (arg0->ext.main_23.unk80 & 0x7F) + 4);
    func_8001540C(2, 0x3A, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_800562AC);

void func_80056470(void)
{
}

void func_80056478(struct MainObj* arg0)
{
    D_800FCEA0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_800564B4);

void func_800565EC(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0xC1) {
        arg0->unk5 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80056618);

void func_80056718(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80056738(struct MainObj* arg0)
{
    D_800FCEC8[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}
