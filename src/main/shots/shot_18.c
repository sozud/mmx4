// ShotObj, shot_object_update_funcs[18]
// 8009CAC0..8009CC64
#include "common.h"

void func_8009CAC0(struct ShotObj* arg0)
{
    D_80108F90[arg0->state](arg0);
}

void func_8009CAFC(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    self->state = 1;
    self->on_screen = 1;
    self->unk54 = D_80108F8C;
    self->unk50.data = D_80108F8C;
    self->unk16 = 0;
    self->unk68 = 0;
    self->unk58.data = (u8*)D_80106070;

    func_8002B93C(
        MOVING_OBJECT(self),
        func_8002B7DC(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);

    self->unk60 = 3;
    self->unk5C = 1;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    func_80015D60(self, 0xC);
}

void func_8009CBA0(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else if (func_8002BB80(arg0, &g_Player) == 0 && func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
}

void func_8009CC44(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108F90[])(struct ShotObj*) = {
    func_8009CAFC,
    func_8009CBA0,
    func_8009CC44,
};
