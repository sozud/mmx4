// ShotObj, shot_object_update_funcs[17]
// 8009C5F0..8009CAC0
#include "common.h"

u8 D_80108F60[4] = { 0xFB, 0xFB, 0x08, 0x09 };
u8 D_80108F64[8] = { 0xFF, 0xFF, 0x04, 0x05, 0xF8, 0xF6, 0x0E, 0x0E };

void func_8009C5F0(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80108F6C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C638);

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C784);

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C860);

void func_8009C96C(struct ShotObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 0;
        arg0->state++;
        func_800AF808(BASE_OBJECT(arg0));
    }
}

void func_8009C9C8(struct ShotObj* arg0)
{
}

void func_8009C9D0(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C9F0);

void func_8009CAA0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108F6C[])(struct ShotObj*) = {
    func_8009C638,
    func_8009C9F0,
    func_8009CAA0,
};

void (*D_80108F78[])(struct ShotObj*) = {
    func_8009C9D0,
    func_8009C9C8,
    func_8009C784,
    func_8009C860,
    func_8009C96C,
};

u8 D_80108F8C[4] = { 0xFC, 0xFD, 0x06, 0x05 };
