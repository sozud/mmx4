// ShotObj, shot_object_update_funcs[13]
// 8009BD28..8009BF14
#include "common.h"

u8 D_80108EB8[4] = { 0xFD, 0xFE, 0x05, 0x04 };

void func_8009BD28(struct ShotObj* arg0)
{
    D_80108EBC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_13", func_8009BD64);

INCLUDE_ASM("main/nonmatchings/shots/shot_13", func_8009BE14);

void func_8009BEF4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108EBC[])(struct ShotObj*) = {
    func_8009BD64,
    func_8009BE14,
    func_8009BEF4,
};
