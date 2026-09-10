// MainObj, main_object_update_funcs[17]
// 8004FF90..80050708
#include "common.h"

void func_8004FF90(struct MainObj* arg0)
{
    D_800FBEB4[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_8004FFE0);

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_800500D4);

void func_80050238(struct MainObj* arg0)
{
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[4] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005026C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_17.saved_unk5;
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050278);

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050418);

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050480);

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050540);

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050644);

void func_80050690(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 5;
        arg0->unk2C = 0x4200;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk67 = 1;
    }
}

void func_800506D8(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
