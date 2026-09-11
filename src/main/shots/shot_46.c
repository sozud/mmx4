// ShotObj, shot_object_update_funcs[46]
// 800A8628..800A9964
#include "common.h"

s8 D_80109ACC[10][4] = {
    { 0, -1, 10, 10 },
    { -7, -8, 13, 14 },
    { -6, -7, 11, 12 },
    { -10, -10, 19, 19 },
    { -25, 82, 71, 24 },
    { -23, -25, 46, 48 },
    { 0, -11, 18, 14 },
    { -31, -5, 62, 7 },
    { -4, -33, 7, 63 },
    { -128, -18, -116, 25 },
};

u8 D_80109AF4[20] = {
    0x27,
    0x28,
    0x27,
    0x28,
    0x27,
    0x28,
    0,
    0,
    0x0F,
    6,
    0x16,
    0xF0,
    0xF8,
    0x16,
    2,
    0xFF,
    0x0D,
    0x0C,
    0x0D,
    0x0B,
};

u8 D_80109B08[4] = { 0xDD, 0xF1, 0x0F, 0x23 };

s8 D_80109B0C[4][2] = {
    { 0x20, -0x20 },
    { 0x10, -0x10 },
    { 0x20, 0 },
    { -0x20, 0x28 },
};

void (*D_80109B14[])(struct ShotObj*) = {
    func_800A8B88,
    func_800A8C88,
    func_800A8D1C,
    func_800A8D68,
    func_800A8D1C,
    func_800A8DB8,
};

void (*D_80109B2C[])(struct ShotObj*) = {
    func_800A8E50,
    func_800A8FBC,
    func_800A9054,
    func_800A90C8,
};

void (*D_80109B3C[])(struct ShotObj*) = {
    func_800A9210,
    func_800A92C8,
    func_800A9334,
    func_800A93FC,
    func_800A94A4,
};

void (*D_80109B50[])(struct ShotObj*) = {
    func_800A8AE4,
    func_800A8DC0,
    func_800A8DC0,
    func_800A916C,
    func_800A91D8,
    func_800A91D8,
    func_800A94D4,
    func_800A9544,
    func_800A9654,
    func_800A96F8,
    func_800A97C0,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8628);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8A58);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8AE4);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8B88);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8C88);

void func_800A8D1C(struct ShotObj* arg0)
{
    if (arg0->unk70 & 3) {
        arg0->x_vel.val = 0;
        if (arg0->unk5 == 2) {
            arg0->y_vel.val = FIXED(-5);
        } else {
            arg0->y_vel.val = FIXED(5);
        }
        arg0->unk5++;
    }
}

void func_800A8D68(struct ShotObj* arg0)
{
    s32 var_a1;

    var_a1 = FIXED(-5);
    if (arg0->unk70 & 8) {
        arg0->unk5++;
        if (arg0->unk99 != 0) {
            var_a1 = FIXED(5);
        }
        arg0->x_vel.val = var_a1;
        if (arg0->unk2 == 2) {
            arg0->x_vel.val = -var_a1;
        }
        arg0->y_vel.val = 0;
    }
}

void func_800A8DB8(struct ShotObj* arg0)
{
}

void func_800A8DC0(struct ShotObj* arg0)
{
    D_80109B14[arg0->unk5](arg0);
    if (func_8002DD04(arg0) != 0) {
        arg0->state = 2;
    }
    func_80015DC8(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7C->state == 4) {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8E50);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8FBC);

void func_800A9054(struct ShotObj* arg0)
{
    s32 x;
    s32 target_x;
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    arg0->unk5++;
    x = weapon->x_pos.i.hi;
    if (weapon->unk15 == 0) {
        target_x = x - 0x21;
    } else {
        target_x = x + 0x21;
    }
    arg0->unk90.i.lo = target_x;
    arg0->unk90.u.hi = weapon->y_pos.u.hi - 0x15;
    func_80015D60(arg0, 0x1E);
    func_8001540C(2, 5, arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A90C8);

void func_800A916C(struct ShotObj* arg0)
{
    D_80109B2C[arg0->unk5](arg0);
    is_on_screen((struct BaseObj*)arg0);
    if (arg0->unk7C->state == 2) {
        arg0->state = 2;
    }
}

void func_800A91D8(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9210);

void func_800A92C8(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->unk5++;
        arg0->unk90.u.lo = g_Player.x_pos.u.hi;
        arg0->unk90.u.hi = g_Player.y_pos.u.hi;
        func_8001540C(2, 0xB, arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9334);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A93FC);

void func_800A94A4(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800A94D4(struct ShotObj* arg0)
{
    arg0->unk98 = func_8002DD04(MAIN_OBJECT(arg0));
    D_80109B3C[arg0->unk5](arg0);
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->unk7C->state == 2) {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9544);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9654);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A96F8);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A97C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9818);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A98AC);

void func_800A9928(struct ShotObj* arg0)
{
    D_80109B7C[arg0->state](arg0);
}

void (*D_80109B7C[])(struct ShotObj*) = {
    func_800A8628,
    func_800A9818,
    func_800A98AC,
};
