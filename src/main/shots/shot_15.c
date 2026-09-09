// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

void func_8009C0F0(struct ShotObj* arg0)
{
    D_80108EDC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_15", func_8009C12C);

void func_8009C238(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_8009C258(struct ShotObj* arg)
{
}

void func_8009C260(struct ShotObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    func_80015DC8(arg0);
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_15", func_8009C298);

void func_8009C344(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108EDC[])(struct ShotObj*) = {
    func_8009C12C,
    func_8009C298,
    func_8009C344,
};
