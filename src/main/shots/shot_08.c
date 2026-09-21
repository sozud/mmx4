// ShotObj, shot_object_update_funcs[8]
// 8009AEE4..8009B07C
#include "common.h"

u8 D_80108D84[4] = { 0xFB, 0xFC, 0x09, 0x07 };

void func_8009AEE4(struct ShotObj* arg0)
{
    s32 temp_v1;
    s32 var_v0;
    s32 var_a1;

    var_a1 = FIXED(-2.5);
    arg0->on_screen = 1;
    arg0->state = (u8)arg0->state + 1;
    if (arg0->unk15 != 0) {
        var_a1 = FIXED(2.5);
    }
    temp_v1 = *(s16*)&arg0->x_pos.i.hi;
    arg0->x_vel.val = var_a1;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    if (arg0->unk15 != 0) {
        var_v0 = temp_v1 + 0x10;
    } else {
        var_v0 = temp_v1 - 0x10;
    }
    arg0->x_pos.i.hi = var_v0;
    arg0->unk16 = 6;
    arg0->unk54 = D_80108D84;
    arg0->unk50.data = D_80108D84;
    arg0->unk58.data = (u8*)D_80106070;
    arg0->unk68 = 0;
    arg0->unk60 = 2;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 3;
    func_80015D60(arg0, 8);
}

void func_8009AF98(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);

    if (func_8002DD04(MAIN_OBJECT(arg0)) != 0) {
        arg0->state = 2;
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }

    arg0->state++;
}

void func_8009B020(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009B040(struct ShotObj* arg0)
{
    D_80108D88[arg0->state](arg0);
}

void (*D_80108D88[])(struct ShotObj*) = {
    func_8009AEE4,
    func_8009AF98,
    func_8009B020,
};
