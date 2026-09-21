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

void func_8009BE14(struct ShotObj* self)
{
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (ENGINE_STAGE_ID != 3 || engine_obj.checkpoint != 0 || g_Player.x_pos.i.hi < 0x7B7) {
        func_8002D9BC(self);
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        func_800AF808(self);
        self->state = 2;
    } else {
        self->unk42 &= 0x7FFF;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 2;
}

void func_8009BEF4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108EBC[])(struct ShotObj*) = {
    func_8009BD64,
    func_8009BE14,
    func_8009BEF4,
};
