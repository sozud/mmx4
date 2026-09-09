// ShotObj, shot_object_update_funcs[53]
// 800AAC98..800ABE08
#include "common.h"

s8 D_80109C38[3][4] = {
    { -34, -40, 67, 79 },
    { -54, -19, 20, 25 },
    { 0, 4, 26, 35 },
};

s16 D_80109C44[8][3][2] = {
    { { 0x3E0, 0x278 }, { 0x610, 0x258 }, { 0x610, 0x2A8 } },
    { { 0x3E0, 0x2B8 }, { 0x4D8, 0x1D0 }, { 0x610, 0x2B8 } },
    { { 0x3E0, 0x2B8 }, { 0x3E0, 0x258 }, { 0x610, 0x288 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2B8 } },
    { { 0x568, 0x1D0 }, { 0x528, 0x1D0 }, { 0x448, 0x1D0 } },
    { { 0x598, 0x308 }, { 0x448, 0x1D0 }, { 0x4E8, 0x308 } },
};

s16 D_80109CA4[8][3][2] = {
    { { 0x448, 0x278 }, { 0x598, 0x258 }, { 0x598, 0x2A8 } },
    { { 0x448, 0x2B8 }, { 0x4D8, 0x248 }, { 0x598, 0x2B8 } },
    { { 0x448, 0x2B8 }, { 0x448, 0x258 }, { 0x598, 0x288 } },
    { { 0x578, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x598, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x578, 0x2B8 }, { 0x408, 0x258 }, { 0x448, 0x2B8 } },
    { { 0x568, 0x248 }, { 0x528, 0x258 }, { 0x448, 0x248 } },
    { { 0x598, 0x2B8 }, { 0x448, 0x248 }, { 0x4E8, 0x2B8 } },
};

u8 D_80109D04[8][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 2 },
    { 1, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 1 },
};

void (*D_80109D1C[])(struct ShotObj*) = {
    func_800AAD6C,
    func_800AAE94,
};

void (*D_80109D24[])(struct ShotObj*) = {
    func_800AB128,
    func_800AB170,
    func_800AB224,
};

void (*D_80109D30[])(struct ShotObj*) = {
    func_800AB384,
    func_800AB3A4,
};

void (*D_80109D38[])(struct ShotObj*) = {
    func_800AB518,
    func_800AB564,
    func_800AB5A4,
};

void (*D_80109D44[])(struct ShotObj*) = {
    func_800AB6C4,
    func_800AB710,
};

void (*D_80109D4C[])(struct ShotObj*) = {
    func_800AB7C0,
    func_800AB814,
};

void (*D_80109D54[])(struct ShotObj*) = {
    func_800AB8C0,
    func_800AB8EC,
};

void (*D_80109D5C[])(struct ShotObj*) = {
    func_800AAD44,
    func_800AAD64,
    func_800AAFF8,
    func_800AB050,
    func_800AB32C,
    func_800AB4C0,
    func_800AB66C,
    func_800AB98C,
    func_800AB868,
    func_800AB768,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAC98);

void func_800AAD44(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800AAD64(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAD6C);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAE94);

void func_800AAFF8(struct ShotObj* arg0)
{
    D_80109D1C[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x80, 0x80);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB050);

void func_800AB128(struct ShotObj* arg0)
{
    func_80015D60(arg0, 8);
    arg0->timer = 0x3C;
    arg0->unk8A = 4;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB170);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB224);

void func_800AB32C(struct ShotObj* arg0)
{
    D_80109D24[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB384(struct ShotObj* arg0)
{
    arg0->timer = 1;
    arg0->unk8A = 6;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB3A4);

void func_800AB4C0(struct ShotObj* arg0)
{
    D_80109D30[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB518(struct ShotObj* arg0)
{
    func_80015D60(arg0, 9);
    arg0->timer = 1;
    arg0->x_vel.val = FIXED(-1);
    arg0->y_vel.val = 0;
    arg0->unk6++;
}

void func_800AB564(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB5A4);

void func_800AB66C(struct ShotObj* arg0)
{
    D_80109D38[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB6C4(struct ShotObj* arg0)
{
    func_80015D60(arg0, 0xB);
    func_8001540C(2, 4, arg0);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB710);

void func_800AB768(struct ShotObj* arg0)
{
    D_80109D44[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB7C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB814);

void func_800AB868(struct ShotObj* arg0)
{
    D_80109D4C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB8C0(struct ShotObj* arg0)
{
    arg0->timer = 0x32;
    arg0->unk8A = 2;
    arg0->unk50.data = NULL;
    arg0->unk8C = 1;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB8EC);

void func_800AB98C(struct ShotObj* arg0)
{
    D_80109D54[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB9C8);

void func_800ABB50(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C = 0;
        arg0->state = 1;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7 = 1;
        arg0->unk50.data = NULL;
        temp_s1->unk8C = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
        arg0->x_pos.i.hi = 0;
        arg0->y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->on_screen = 0;
    D_80109D84[arg0->state](arg0);
}

void (*D_80109D84[])(struct ShotObj*) = {
    func_800AAC98,
    func_800AB9C8,
    func_800ABB50,
};
