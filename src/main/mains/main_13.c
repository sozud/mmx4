// MainObj, main_object_update_funcs[13]
// 8004C734..8004CF24
#include "common.h"

void func_8004C734(struct MainObj* arg0)
{
    D_800FB858[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C784);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C860);

void func_8004C97C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->state = 3;
    } else if (--arg0->unk7E == 0) {
        arg0->unk7E = 6;
        func_800AF878(arg0, 1, 24, 32);
    }
}

void func_8004C9E8(struct MainObj* arg0)
{
    arg0->ext.main_13.unk80 = 0;
    arg0->ext.main_13.unk84 = 0;
    arg0->ext.main_13.unk88 = 0;
    arg0->ext.main_13.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004CA14(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_13.saved_unk5;
}

void func_8004CA20(struct MainObj* arg0)
{
    D_800FB880[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CA5C);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CA94);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CBD4);

void func_8004CC64(struct MainObj* arg0)
{
    D_800FB888[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CCA0);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CDC8);

void func_8004CE48(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 3;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

void func_8004CE94(struct MainObj* arg0)
{
    if (arg0->unk5 != 5 && arg0->ext.main_13.unk80 == 0x8001) {
        func_80015D60(arg0, 3);
        arg0->ext.main_13.unk80 = 0x8000;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8004CEF4(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
