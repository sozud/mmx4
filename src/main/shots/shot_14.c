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

void func_8009BFE0(struct ShotObj* arg0)
{
    s32 in_range;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (engine_obj.stage == 3) {
        if ((u8)arg0->unk2 < 4) {
            in_range = g_Player.x_pos.i.hi < 0x7B7;
        } else {
            in_range = g_Player.x_pos.i.hi < 0x9B7;
        }
        if (in_range != 0) {
            func_8002D9BC(arg0);
        }
    } else {
        func_8002D9BC(arg0);
    }
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
    } else {
        arg0->unk42 &= 0x7FFF;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
    } else {
        arg0->state = 2;
    }
}

void func_8009C0D0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108ECC[])(struct ShotObj*) = {
    func_8009BF50,
    func_8009BFE0,
    func_8009C0D0,
};
