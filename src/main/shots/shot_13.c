// ShotObj, shot_object_update_funcs[13]
// 8009BD28..8009BF14
#include "common.h"

u8 D_80108EB8[4] = { 0xFD, 0xFE, 0x05, 0x04 };

void func_8009BD28(struct ShotObj* arg0)
{
    D_80108EBC[arg0->state](arg0);
}

void func_8009BD64(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk42 &= 0x7FFF;
    func_8002B93C(
        MOVING_OBJECT(self),
        func_8002B7DC(
            OBJECT_HEADER(self),
            OBJECT_HEADER(&g_Player))
            & 0xFF);
    self->unk54 = D_80108EB8;
    self->unk50.data = D_80108EB8;
    self->unk60 = 3;
    self->unk16 = 0;
    self->unk68 = 0;
    self->unk5C = 1;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    func_80015D60(self, 3);
}

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
