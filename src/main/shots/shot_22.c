// ShotObj, shot_object_update_funcs[22]
// 8009D74C..8009DD40
#include "common.h"

u8 D_80109004[4] = { 0xF7, 0xF8, 0x11, 0x10 };

void func_8009D74C(struct ShotObj* arg0)
{
    D_80109008[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009D788);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009D85C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009D8F0);

void func_8009DA08(struct ShotObj* arg0)
{
    g_Player.x_pos.val = arg0->x_pos.val;
    g_Player.y_pos.val = arg0->y_pos.val;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DA28);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DA7C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DB1C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DB9C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DCF4);

void (*D_80109008[])(struct ShotObj*) = {
    func_8009D788,
    func_8009DB9C,
    func_8009DCF4,
};
