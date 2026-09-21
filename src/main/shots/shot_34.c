// ShotObj, shot_object_update_funcs[34]
// 800A16FC..800A22D4
#include "common.h"

s8 D_80109510[10][4] = {
    { -6, -10, 10, 18 },
    { -17, -10, 33, 18 },
    { 0, -1, 11, 3 },
    { -6, -5, 10, 11 },
    { -7, -15, 13, 30 },
    { 0, 0, 7, 8 },
    { 10, 10, 10, 11 },
    { 40, 40, 40, 42 },
    { 41, 41, 41, 42 },
    { 18, 9, -18, 9 },
};

s32 D_80109538[4] = { 7, 6, 11, 15 };

s32 D_80109548[4] = { 4, 5, 3, 2 };

void (*D_80109558[])(struct ShotObj*) = {
    func_800A19A8,
    func_800A1B1C,
    func_800A1BEC,
};

u8 D_80109564[4][4] = {
    { 8, 8, 13, 17 },
    { 7, 7, 12, 16 },
    { 9, 9, 14, 18 },
    { 6, 6, 11, 15 },
};

void (*D_80109574[])(struct ShotObj*) = {
    NULL,
    func_800A18F4,
    func_800A1F7C,
    func_800A1CCC,
    func_800A1E3C,
    func_800A1C90,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A16FC);

void func_800A18A8(struct ShotObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk67 = -1;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }
}

void func_800A18F4(struct ShotObj* arg0)
{
    struct ShotObj* self;
    s8 var_v0;
    u8 temp_v1;

    self = arg0;
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    temp_v1 = self->unk70;

    if (temp_v1 & 8) {
        self->y_vel.val = 0;
        self->unk2C = 0;
        func_80015D60(self, 9);
        var_v0 = 4;
    } else if (temp_v1 & 3) {
        if (self->unk8C.bytes[3] == 0) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->x_vel.val = 0;
            self->y_vel.val = FIXED(-3);
            return;
        }
        self->y_vel.val = 0;
        self->unk2C = 0;
        func_80015D60(self, 8);
        var_v0 = 3;
    } else {
        return;
    }

    self->unk5 = var_v0;
    self->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A19A8);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1B1C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1BEC);

void func_800A1C90(struct ShotObj* arg0)
{
    D_80109558[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1CCC);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1E3C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1F7C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A2098);

void func_800A220C(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    if (arg0->unk2 < 2) {
        weapon = arg0->unk7C;
        weapon->unk84.bytes[1]--;
        weapon->unk88.bytes[0] &= ~(1 << arg0->unk8A);
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A2278(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010958C[arg0->state](arg0);
    CollisionRelated(arg0);
}

void (*D_8010958C[])(struct ShotObj*) = {
    func_800A16FC,
    func_800A2098,
    func_800A220C,
};
