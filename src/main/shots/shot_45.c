// ShotObj, shot_object_update_funcs[45]
// 800A7AF0..800A8628
#include "common.h"

void func_800A7AF0(struct ShotObj* arg0)
{
    D_80109A78[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7B2C);

void func_800A7BC8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7BE8);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7C50);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7CE8);

void func_800A7E10(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800A7E40(struct ShotObj* arg0)
{
    D_80109AA4[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7E98);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7F44);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7FF8);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A8074);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A80D4);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A8164);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A81E0);

void func_800A826C(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800A829C(struct ShotObj* arg0)
{
    D_80109ABC[arg0->unk6](arg0);
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A82EC);

void func_800A833C(struct ShotObj* arg0)
{
    if (--arg0->unk88 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800A836C(struct ShotObj* arg0)
{
    D_80109AC4[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A83C4);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A84D4);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A858C);

void (*D_80109A78[])(struct ShotObj*) = {
    func_800A7B2C,
    func_800A7BE8,
    func_800A7BC8,
};
