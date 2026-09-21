// ShotObj, shot_object_update_funcs[36]
// 800A3924..800A3C78
#include "common.h"

void func_800A3924(struct ShotObj* arg0)
{
    D_8010978C[arg0->state](arg0);
}

void func_800A3960(struct ShotObj* arg0)
{
    s32 owner_x;
    s32 x_pos;
    struct WeaponObj* owner;

    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk60 = 6;
    arg0->unk84.value = 0x6E;
    owner = arg0->unk7C;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk5C = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;

    if (arg0->unk2 != 0) {
        func_80015D60(arg0, 4);
        arg0->unk50.frames = D_8010977C[3];
        owner_x = owner->x_pos.i.hi;
        x_pos = arg0->unk15 != 0 ? owner_x + 0x190 : owner_x - 0x190;
    } else {
        func_80015D60(arg0, 3);
        arg0->unk50.frames = D_8010977C[2];
        owner_x = owner->x_pos.i.hi;
        x_pos = arg0->unk15 != 0 ? owner_x + 0x90 : owner_x - 0x90;
    }

    arg0->x_pos.i.hi = x_pos;
    arg0->y_pos.i.hi = owner->y_pos.i.hi - 3;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_36", func_800A3A4C);

void func_800A3C50(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A3C70(struct ShotObj* arg0)
{
}

void (*D_8010978C[])(struct ShotObj*) = {
    func_800A3960,
    func_800A3A4C,
    func_800A3C50,
    func_800A3C70,
};
