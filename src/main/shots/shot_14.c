// ShotObj, shot_object_update_funcs[14]
// 8009BF14..8009C0F0
#include "common.h"

u8 D_80108EC8[4] = { 0xFD, 0xFE, 0x05, 0x04 };

void func_8009BF14(struct ShotObj* arg0)
{
    D_80108ECC[arg0->state](arg0);
}

void func_8009BF50(struct ShotObj* arg0)
{
    s16 x_pos;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk16 = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk15 == 0) {
        x_pos = (u16)arg0->x_pos.i.hi - 6;
    } else {
        x_pos = (u16)arg0->x_pos.i.hi + 6;
    }
    arg0->x_pos.i.hi = x_pos;
    arg0->unk54 = D_80108EC8;
    arg0->unk50.data = D_80108EC8;
    arg0->unk5C = 1;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    func_80015D60(arg0, 5);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_14", func_8009BFE0);

void func_8009C0D0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108ECC[])(struct ShotObj*) = {
    func_8009BF50,
    func_8009BFE0,
    func_8009C0D0,
};
