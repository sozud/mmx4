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

void func_8009DA28(struct ShotObj* arg0)
{
    arg0->timer = 0x78;
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->x_vel.val = 0;
    arg0->unk5++;
    func_8009DA08(arg0);
    arg0->unk90.val = 0x30;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DA7C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DB1C);

INCLUDE_ASM("main/nonmatchings/shots/shot_22", func_8009DB9C);

void func_8009DCF4(struct ShotObj* arg0)
{
    if (arg0->unk8C.word == 3 && g_Player.unkBA != 0) {
        g_Player.unkBA = 0;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80109008[])(struct ShotObj*) = {
    func_8009D788,
    func_8009DB9C,
    func_8009DCF4,
};
