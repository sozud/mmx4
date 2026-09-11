// MainObj, main_object_update_funcs[25]
// 80057100..80058158
#include "common.h"

void func_80057100(struct MainObj* arg0)
{
    D_800FD140[arg0->state](arg0);
    if (arg0->ext.main_25.unk88 == 0) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057160);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057308);

void func_80057488(struct MainObj* arg0)
{
    arg0->ext.main_25.unk80 = 0;
    arg0->ext.main_25.unk84 = 0;
    arg0->ext.main_25.unk88 = 0;
    arg0->ext.main_25.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800574B4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_25.saved_unk5;
}

void func_800574C0(struct MainObj* arg0)
{
    D_800FD168[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_800574FC);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_8005754C);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_800576F4);

void func_800577E8(struct MainObj* arg0)
{
    D_800FD174[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057824);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057874);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057978);

void func_80057A44(struct MainObj* arg0)
{
    D_800FD180[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057A80);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057AE8);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057C00);

void func_80057D58(struct MainObj* arg0)
{
    D_800FD18C[arg0->unk6](arg0);
}

void func_80057D94(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 3);
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057DDC);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057E34);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057F34);

void func_80058044(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0x11) {
        arg0->unk5 = 4;
        arg0->y_pos.u.hi -= 0x18;
    }
}

void func_8005807C(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_800580AC);
