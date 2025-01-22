#include "common.h"

void func_800312B4(struct PlayerObj* arg0)
{
    arg0->unkC3 = arg0->unkC0 | engine_obj.unkF;
    arg0->unkC3 |= arg0->unkC4;
    arg0->unk89 = arg0->unk70 | arg0->unk71;
    arg0->unk8F = 0;
    arg0->unk90 = 0;
    arg0->unkBF = 0;

    if (engine_obj.unk10 == 0) {
        func_80033BC8(arg0);
        if (arg0->unk5C == 0) {
            return;
        }

        if (arg0->unk92) {
            arg0->unk92--;
        }

        if (arg0->unk91 != 0) {
            arg0->unk91--;
            if (!arg0->unk91) {
                arg0->unk90 = 1;
                arg0->unk8E = 0;
            }
        }

        if (arg0->unkD7 > 0) {
            arg0->unkD7--;
            if (!arg0->unkD7) {
                arg0->unkD7 = -1;
            }
        }

        func_800338CC(arg0);
        func_80033974(arg0);
        func_80033750(arg0);
        func_800335E4(arg0);
        func_80036EE8(arg0);

        D_800F8990[arg0->base.unk5](arg0);
        arg0->unk71 = 0;
        arg0->unk4A = 0;
    }
    func_80037FF0(arg0);
    func_800360B8(arg0);
    func_80035DE4(arg0);
}

void func_80031410(struct PlayerObj* arg0)
{
    func_80015DC8();
    if (arg0->base.unk6 == 0) {
        if (arg0->unkBE != 0) {
            if (--arg0->unkBE == 0) {
                func_80035EA4(arg0);
            }
            func_8002B718(arg0);
            return;
        }
        if (arg0->unk89 & 8) {
            func_800350A4(arg0, 2);
            arg0->unk67 = 0;
            background_objects[0].unk44 = 1;
            background_objects[1].unk44 = 1;
            background_objects[2].unk44 = 1;
            arg0->base.unk6++;
            return;
        }
        func_8002B718(arg0);
        func_80036B88(arg0);
        return;
    }
    if (arg0->unk45 != 0) {
        arg0->unk45 = 0;
        arg0->unkA7 = engine_obj.unk47;
        arg0->unkB8 = engine_obj.unk48;
    }
    if (arg0->unk46 == 0) {
        engine_obj.unk1C = 0;
        func_800343A4(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031540);

void func_800315E0(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0 && func_80033EA4(arg0) == 0 && func_80037290(arg0) == 0 && func_80039880(arg0) == 0 && func_80033494(arg0) == 0 && func_800398F0(arg0) == 0) {
        if (func_800334F4(arg0) != 0) {
            func_800344A0(arg0);
        } else {
            func_80038678(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031688);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031764);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031820);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800318D0);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031A24);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031AE0);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031B90);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031DD4);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80031F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_8003200C);

void func_800320E4(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0) {
        func_80015DC8(arg0);
        D_800F8A90[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032140);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032224);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032300);

void func_80032468(struct PlayerObj* arg0)
{
    if (arg0->unk89 & 8) {
        func_80034668();
    } else if (arg0->unkC3 != 0) {
        func_80034604(arg0);

    } else if (arg0->base.unk2 == 0) {
        if (func_80037338(arg0) == 0) {
            if (arg0->unk8E != 0) {
                func_8003490C(arg0);
            } else {
                func_80015DC8(arg0);
                D_800F8A9C[arg0->base.unk6](arg0);
            }
        }
    } else {
        func_80015DC8(arg0);
        D_800F8A9C[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_8003253C);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800325EC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_8003267C);

void func_80032740(struct PlayerObj* arg0)
{
    D_800F8AA8[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_8003277C);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800327CC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032840);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800328CC);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032910);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032950);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032A28);

void func_80032B04(struct PlayerObj* arg0)
{
    func_80015DC8(arg0);
    D_800F8ABC[arg0->unk63](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032B50);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032D28);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032E94);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032F64);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80032FA4);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80033054);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800330B4);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80033108);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800331A8);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80033210);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_800332C0);

INCLUDE_ASM("asm/us/main/nonmatchings/21AB4", func_80033368);
