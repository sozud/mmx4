// ShotObj, shot_object_update_funcs[48]
// 800A9964..800A9DF4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9964);

void func_800A9AEC(struct ShotObj* arg0)
{
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1;

    temp_s2 = arg0->x_pos.val - ((s16)arg0->unk8C.half << 16);
    temp_s1 = arg0->y_pos.val - (arg0->unk8C.halves[1] << 16);
    temp_a2 = func_8002B810(temp_s2, temp_s1);
    if ((s16)arg0->unk8A == 0) {
        temp_a0 = (u8)arg0->unk5;
        arg0->timer = 0x5A;
        temp_v0 = (s16)arg0->unk8C.half;
        temp_v1 = arg0->unk8C.halves[1];
        temp_a0 += 1;
        arg0->x_pos.val = temp_v0 << 16;
        arg0->y_pos.val = temp_v1 << 16;
        arg0->unk5 = temp_a0;
    } else {
        arg0->x_pos.val -= temp_s2 / (s16)arg0->unk8A;
        arg0->y_pos.val -= temp_s1 / (s16)arg0->unk8A;
        arg0->unk8A = (u16)arg0->unk8A - 1;
    }
    arg0->unk84.value = temp_a2 & 0xFF;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800A9C24(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        arg0->unk5++;
        func_80015D60(arg0, 0xD);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800A9C7C(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->on_screen = 0;
        return;
    }
    func_80015DC8(arg0);
}

void func_800A9CBC(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109BB8[arg0->unk5](arg0);
    if (arg0->unk7C->state == 2) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 0;
}

void func_800A9D98(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->state](arg0);
}

u8 D_80109B88[2][4] = {
    { 0xF0, 0xF2, 0x1F, 0x1B },
    { 0xFE, 0xFE, 0x10, 0x10 },
};

u8 D_80109B90[2][4] = {
    { 0xF3, 0xBD, 0x26, 0x87 },
    { 0, 8, 0x2E, 0x78 },
};

u8 D_80109B98[4] = { 0xF9, 0xFA, 0x0D, 0x0B };

u8 D_80109B9C[4] = { 0, 0, 0x0E, 0x0E };

u8 D_80109BA0[2][4] = {
    { 0xF8, 0xF8, 0x10, 0x10 },
    { 0, 0, 0x0E, 0x0E },
};

u8 D_80109BA8[2][4] = {
    { 0xFC, 0xF9, 7, 0x0A },
    { 0, 6, 3, 7 },
};

u8 D_80109BB0[4] = { 0x1A, 0x1B, 0x1A, 0x1B };

u8 D_80109BB4[4] = { 0x1C, 0x1D, 0x1C, 0x1D };

void (*D_80109BB8[3])(struct ShotObj*) = {
    func_800A9AEC,
    func_800A9C24,
    func_800A9C7C,
};

void (*D_80109BC4[])(struct ShotObj*) = {
    func_800A9964,
    func_800A9CBC,
    func_800A9D98,
};
