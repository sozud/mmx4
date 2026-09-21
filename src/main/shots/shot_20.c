// ShotObj, shot_object_update_funcs[20]
// 8009CF38..8009D200
#include "common.h"

u8 D_80108FBC[4] = { 0x80, 0xF1, 0xBE, 0x26 };
u8 D_80108FC0[4] = { 0x80, 0xF1, 0xFF, 0x26 };
u8 D_80108FC4[4] = { 0x80, 0xFA, 0xBD, 0x14 };
u8 D_80108FC8[4] = { 0x80, 0xFA, 0xFF, 0x14 };

void func_8009CF38(struct ShotObj* arg0)
{
    D_80108FCC[arg0->state](arg0);
}

void func_8009CF74(struct ShotObj* raw_arg0)
{
    struct ShotObj* arg0;
    s16 var_v0;
    struct WeaponObj* temp_s1;

    arg0 = raw_arg0;
    arg0->on_screen = 1;
    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk60 = 6;
    arg0->unk84.value = 0x6E;
    temp_s1 = arg0->unk7C;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk5C = 0;
    arg0->state = (u8)arg0->state + 1;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 != 0) {
        func_80015D60(arg0, 4);
        arg0->unk50.data = D_80108FC8;
        var_v0 = (u16)temp_s1->x_pos.i.hi - 0x177;
    } else {
        func_80015D60(arg0, 3);
        arg0->unk50.data = D_80108FC4;
        var_v0 = (u16)temp_s1->x_pos.i.hi - 0x77;
    }
    arg0->x_pos.i.hi = var_v0;
    arg0->y_pos.i.hi = (s16)(u16)temp_s1->y_pos.i.hi;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_20", func_8009D048);

void func_8009D1D8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009D1F8(struct ShotObj* arg0)
{
}

void (*D_80108FCC[])(struct ShotObj*) = {
    func_8009CF74,
    func_8009D048,
    func_8009D1D8,
    func_8009D1F8,
};
