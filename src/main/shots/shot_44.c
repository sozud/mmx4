// ShotObj, shot_object_update_funcs[44]
// 800A6FCC..800A7AF0
#include "common.h"

void func_800A6FCC(struct ShotObj* arg0)
{
    D_801099E8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7008);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7104);

void func_800A7208(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    weapon->unk84.byte--;
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7240);

void func_800A7318(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80109A24[arg0->unk5](arg0);
    if (arg0->unk7C->state >= 2) {
        arg0->state = 5;
    }
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x200, 0x200);
}

void func_800A73A4(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A73C4);

void func_800A7458(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80109A30[arg0->unk5](arg0);
    if (arg0->unk7C->state >= 2) {
        arg0->state = 8;
    }
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x100, 0x100);
}

void func_800A74E4(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A7504(struct ShotObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->timer == 0) {
        arg0->unk5 = 1;
        arg0->unk28 = -(arg0->x_vel.val >> 4);
        arg0->unk2C = arg0->y_vel.val >> 4;
    }
}

void func_800A7570(struct ShotObj* arg0)
{
    func_800A7A90(arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (abs(arg0->x_vel.val) <= 0xFFFF) {
        if (abs(arg0->y_vel.val) <= 0xFFFF) {
            arg0->unk5 = 2;
            arg0->unk61 = 0;
            arg0->x_vel.val = 0;
            arg0->y_vel.val = 0;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->timer = 0x3C;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7600);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A766C);

void func_800A77D8(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0xF);
        arg0->unk5 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7820);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7878);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7928);

void func_800A79A4(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A79E0);

void func_800A7A54(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 8;
    }
}

void func_800A7A90(struct ShotObj* arg0)
{
    arg0->x_pos.val += arg0->x_vel.val;
    arg0->y_pos.val -= arg0->y_vel.val;
    arg0->x_vel.val += arg0->unk28;
    arg0->y_vel.val -= arg0->unk2C;
    if (arg0->y_vel.val < FIXED(-6.5)) {
        arg0->y_vel.val = FIXED(-6.5);
    }
}

u8 D_801099D4[4] = { 0xFA, 0xFC, 0x0A, 0x07 };

u8 D_801099D8[4] = { 0xF6, 0xF9, 0x12, 0x0E };

u8 D_801099DC[4] = { 0xEE, 0xEB, 0x28, 0x2B };

u8 D_801099E0[4] = { 0x88, 0xEE, 0xE5, 0x22 };

u8 D_801099E4[4] = { 0xEE, 0x85, 0x22, 0xF5 };

void (*D_801099E8[])(struct ShotObj*) = {
    func_800A7008,
    func_800A7104,
    func_800A7208,
    func_800A7240,
    func_800A7318,
    func_800A73A4,
    func_800A73C4,
    func_800A7458,
    func_800A74E4,
};

void (*D_80109A0C[])(struct ShotObj*) = {
    func_800A7504,
    func_800A7570,
    func_800A7600,
    func_800A766C,
    func_800A77D8,
    func_800A7820,
};

void (*D_80109A24[])(struct ShotObj*) = {
    func_800A7878,
    func_800A7928,
    func_800A79A4,
};

void (*D_80109A30[])(struct ShotObj*) = {
    func_800A79E0,
    func_800A7A54,
};
