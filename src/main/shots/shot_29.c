// ShotObj, shot_object_update_funcs[29]
// 8009F638..8009FB60
#include "common.h"

u8 D_801091D0[8] = { 0xF5, 0xFD, 0x1B, 0x0A, 2, 2, 0x0D, 4 };
s32 D_801091D8[2] = { 0x5000, -0x5000 };
s32 D_801091E0[4] = { 0x10000, -0x10000, -0x10000, 0x10000 };

void func_8009F638(struct ShotObj* arg0)
{
    D_801091F0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F674);

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F7C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F89C);

void func_8009F94C(struct ShotObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->unk8C.shot_29.timer - 1;
    arg0->unk8C.shot_29.timer = temp_v0;
    if ((temp_v0 == 0) && (arg0->unk90.bytes[1] == 0)) {
        arg0->unk28 = FIXED(0.1875);
        arg0->unk90.bytes[1] = 1;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk8C.shot_29.unk8D = 0x28;
        arg0->unk5++;
    }
    if ((arg0->unk2 != 0) && (arg0->unk8C.shot_29.timer < 0x15U) && (arg0->y_vel.val != 0)) {
        arg0->y_vel.val = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F9E0);

void func_8009FB38(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009FB58(struct ShotObj* arg0)
{
}

void (*D_801091F0[])(struct ShotObj*) = {
    func_8009F674,
    func_8009F7C0,
    func_8009FB38,
    func_8009FB58,
};
