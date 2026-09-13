// MainObj, main_object_update_funcs[27]
// 800586F0..80059C48
#include "common.h"

void func_800586F0(struct MainObj* arg0)
{
    D_800FD38C[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058740);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058AC8);

void func_80058D50(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->state = 3;
    } else if (--arg0->unk7E == 0) {
        arg0->unk7E = 6;
        func_800AF878(arg0, 1, 16, 16);
    }
}

void func_80058DBC(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80058DF0(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_27.saved_unk5;
}

void func_80058DFC(struct MainObj* arg0)
{
    D_800FD3BC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058E38);

void func_80058F94(struct MainObj* arg0)
{
    s8 next_state;

    if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi) >= 0xBD) {
        func_8001540C(2, 0x51, arg0);
        arg0->unk7A = 0;
        if (arg0->ext.main_27.unk80 == 0) {
            next_state = 2;
        } else {
            arg0->unk7C = 1;
            next_state = 7;
        }
        arg0->unk5 = next_state;
        arg0->unk6 = 0;
    }
}

void func_80059010(struct MainObj* arg0)
{
    D_800FD3C0[arg0->unk6](arg0);
}

void func_8005904C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk28 = 0;
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_800590BC);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059154);

void func_800591F0(struct MainObj* arg0)
{
    D_800FD3CC[arg0->unk6](arg0);
}

void func_8005922C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_27.unk8B = 1;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk7C = 4;
        arg0->unk7E = 0x1E;
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059290);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059344);

void func_800594D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 6);
        arg0->unk6 = 4;
    }
}

void func_8005952C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_27.unk8B = 0;
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 1);
        arg0->unk7C = 10;
        arg0->unk6 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059590);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059640);

void func_80059978(struct MainObj* arg0)
{
    D_800FD3E4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_800599B4);

void func_80059A94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->ext.main_27.unk8C != 1) {
        arg0->ext.main_27.unk8C--;
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 1);
        arg0->unk28 = FIXED(-0.125);
        arg0->unk6 = 2;
    }
}

void func_80059B0C(struct MainObj* arg0)
{
    if (arg0->ext.main_27.unk8C != 1) {
        arg0->ext.main_27.unk8C--;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk7C = 10;
        arg0->unk28 = 0;
        arg0->unk20 = 0;
        arg0->ext.main_27.unk88 = 0;
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059B7C);
