// ShotObj, shot_object_update_funcs[52]
// 800AAAD4..800AAC98
#include "common.h"

void func_800AAAD4(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk54 = D_80109BA8[0];
    arg0->unk50.data = D_80109BA8[0];
    arg0->unk58.collision_bounds = D_801060F0;
    arg0->unk5C = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->timer = 0;
    arg0->unk8A = 0;
    arg0->bg_offset = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 4;
    arg0->unk61 = 0;
    func_80015D60(arg0, 0x17);
    arg0->x_vel.val = 0;
    arg0->y_vel.val = FIXED(-4);
    arg0->unk28 = 0;
    arg0->unk2C = 0;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_52", func_800AAB74);

void func_800AAC5C(struct ShotObj* arg0)
{
    D_80109C2C[arg0->state](arg0);
}

void (*D_80109C2C[])(struct ShotObj*) = {
    func_800AAAD4,
    func_800AAB74,
    func_800A9D98,
};
