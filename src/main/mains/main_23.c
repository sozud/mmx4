// MainObj, main_object_update_funcs[23]
// 80055E04..80056788
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055E04);

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055E9C);

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055F1C);

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055FD0);

void func_80056018(struct MainObj* arg0)
{
    D_800FCE88[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80056054);

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80056230);

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
