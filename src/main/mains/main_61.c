// MainObj, main_object_update_funcs[61]
// 8007872C..8007B90C
#include "common.h"

void func_8007872C(struct MainObj* arg0)
{
    D_80101FF8[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007877C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800788E4);

void func_80078DF0(struct BarObj* arg0)
{
    D_80102024[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80078E2C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80078EB0);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80078FA4);

void func_800790AC(struct MainObj* arg0)
{
    D_80102030[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800790E8);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800791D4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007927C);

void func_80079364(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 17);
        arg0->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800793AC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079518);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079568);

void func_80079608(struct MainObj* arg0)
{
    D_8010204C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079644);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800796DC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079794);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800797E8);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079824);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079914);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007996C);

void func_80079A50(struct MainObj* arg0)
{
    D_80102068[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079A8C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079B50);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079DD8);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079FE4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A048);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A09C);

void func_8007A12C(struct MainObj* arg0)
{
    D_80102080[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A168);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A1EC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A2B4);

void func_8007A3B0(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if ((arg0->unk7 == 0) && (arg0->unk24 < 0)) {
        func_80015D60(arg0, 3);
        arg0->unk7 = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0xA);
        func_8001540C(2, 0xA6, arg0);
        arg0->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A444);

void func_8007A4B0(struct MainObj* arg0)
{
    D_80102094[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A4EC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A63C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A7F0);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A854);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A8AC);

void func_8007A930(struct MainObj* arg0)
{
    D_801020A8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A96C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AB1C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007ADB4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AE2C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AFB4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B054);

void func_8007B0F8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 2);
        arg0->unk6 = 7;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B140);

void func_8007B180(struct MainObj* arg0)
{
    D_801020C8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B1BC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B2FC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B3A8);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B418);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B588);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B5F0);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B640);

void func_8007B68C(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B6BC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B7B4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B834);
