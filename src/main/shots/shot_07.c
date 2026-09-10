// ShotObj, shot_object_update_funcs[7]
// 8009AD30..8009AEE4
#include "common.h"

u8 D_80108D6C[4] = { 0xFE, 0x16, 0x07, 0x0E };
u8 D_80108D70[4] = { 0xF8, 0x0A, 0x0D, 0x1A };

void func_8009AD30(struct ShotObj* arg0)
{
    D_80108D74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_07", func_8009AD6C);

INCLUDE_ASM("main/nonmatchings/shots/shot_07", func_8009ADF8);

void func_8009AEBC(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009AEDC(struct ShotObj* arg0)
{
}

void (*D_80108D74[])(struct ShotObj*) = {
    func_8009AD6C,
    func_8009ADF8,
    func_8009AEBC,
    func_8009AEDC,
};
