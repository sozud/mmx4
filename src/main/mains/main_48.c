// MainObj, main_object_update_funcs[48]
// 80067350..800684F8
#include "common.h"

void func_80067350(struct MainObj* arg0)
{
    D_800FFAE8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_8006738C);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067550);

void func_80067628(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_48.saved_unk5;
}

void func_80067640(struct MainObj* arg0)
{
    D_800FFB14[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_8006767C);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800676E0);

void func_80067740(struct MainObj* arg0)
{
    D_800FFB1C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_8006777C);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800677F8);

void func_80067860(struct MainObj* arg0)
{
    D_800FFB24[arg0->unk6](arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800678B0);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800678F8);

void func_80067A80(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067AA8);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067BB0);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067C34);

void func_80067CB0(struct MainObj* arg0)
{
    D_800FFB3C[arg0->unk6](arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067D00);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067DAC);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80067EE4);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80068000);

void func_80068060(struct MainObj* arg0)
{
    arg0->unk6++;
}

void func_80068074(struct WeaponObj* arg0)
{
    arg0->unk67 = -1;
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_8006808C(struct MainObj* arg0)
{
    D_800FFB54[arg0->unk6](arg0);
}

void func_800680C8(struct MainObj* arg0)
{
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = FIXED(2);
    arg0->unk2C = 0;
    arg0->unk6++;
    func_80015D60(arg0, 1);
}

void func_80068108(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

void func_80068138(struct MainObj* arg0)
{
    s32 distance;
    s32 max_distance;
    s8 state;

    if ((arg0->unk67 == 0) && ((state = arg0->unk5) != 4) && (state != 5)) {
        max_distance = D_800FFAD8[(s8)SP_CUR_MAIN_OBJ->ext.main_0.index];
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        if (distance >= 0) {
            if (max_distance >= distance) {
                goto activate;
            }
            return;
        }
        if (max_distance < (arg0->x_pos.i.hi - g_Player.x_pos.i.hi)) {
            return;
        }
    activate:
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800681C4);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80068340);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_80068404);

INCLUDE_ASM("main/nonmatchings/mains/main_48", func_800684BC);
