// ShotObj, shot_object_update_funcs[45]
// 800A7AF0..800A8628
#include "common.h"

s16 D_80109A38[2][2] = {
    { 0x45, -0x12 },
    { 0x45, 0x10 },
};

s8 D_80109A40[14][4] = {
    { -1, -18, 15, 35 },
    { -4, -25, 19, 49 },
    { -1, 11, 10, 20 },
    { -1, 4, 10, 27 },
    { -4, -20, 15, 51 },
    { -1, -18, 15, 35 },
    { -11, -45, 28, 76 },
    { -11, -54, 28, 85 },
    { -15, -64, 33, 95 },
    { -18, -6, 41, 9 },
    { -6, -13, 12, 43 },
    { -11, -13, 23, 24 },
    { -64, -24, 35, 54 },
    { -62, -32, 30, 61 },
};

void func_800A7AF0(struct ShotObj* arg0)
{
    D_80109A78[arg0->state](arg0);
}

void func_800A7B2C(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;
    u8 temp_unk15;
    s32 temp_y;

    weapon = arg0->unk7C;
    arg0->unk3C = weapon->unk3C;
    arg0->unk40 = weapon->unk40;
    arg0->unk42 = weapon->unk42 & 0x7FFF;
    arg0->bg_offset = weapon->bg_offset;
    arg0->animation_table = weapon->animation_table;
    temp_unk15 = weapon->unk15;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk15 = temp_unk15;
    arg0->x_pos.val = weapon->x_pos.val;
    temp_y = weapon->y_pos.val;
    arg0->state++;
    arg0->unk5 = (s8)(u8)arg0->unk2 >> 4;
    arg0->y_pos.val = temp_y;
    arg0->unk2 &= 0xF;
}

void func_800A7BC8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A7BE8(struct ShotObj* arg0)
{
    D_80109A84[arg0->unk5](arg0);
    if (arg0->unk8C.object->state == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7C50);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7CE8);

void func_800A7E10(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800A7E40(struct ShotObj* arg0)
{
    D_80109AA4[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7E98);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7F44);

void func_800A7FF8(struct ShotObj* arg0)
{
    D_80109AAC[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
    } else {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800A8074(struct ShotObj* arg0)
{
    func_80015D60(arg0, 0x11);
    arg0->unk5C = 5;
    arg0->unk60 = 6;
    arg0->timer = 0;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    arg0->unk50.data = (const u8*)D_80109A40[11];
    arg0->unk6++;
}

void func_800A80D4(struct ShotObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    shot = SHOT_OBJECT(arg0->unk7C);
    if (shot->state != 2) {
        return;
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x2D;
        shot->unk2 = arg0->timer + 0x30;
        shot->timer = arg0->timer + 1;
        shot->unk7C = WEAPON_OBJECT(arg0);
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

void func_800A8164(struct ShotObj* arg0)
{
    D_80109AB4[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
    } else {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800A81E0(struct ShotObj* arg0)
{
    func_80015D60(arg0, 0xF);
    arg0->unk5C = 5;
    arg0->unk60 = 9;
    arg0->y_vel.val = FIXED(8);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    arg0->unk50.data = (const u8*)D_80109A40[10];
    if (arg0->unk2 == 0) {
        func_8001540C(2, 0xD7, arg0);
    }
    arg0->unk6++;
}

void func_800A826C(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800A829C(struct ShotObj* arg0)
{
    D_80109ABC[arg0->unk6](arg0);
    func_8002D9BC(arg0);
}

void func_800A82EC(struct ShotObj* arg0)
{
    arg0->unk5C = 0;
    arg0->unk60 = 9;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    if (arg0->unk2 == 0) {
        arg0->unk50.data = (const u8*)D_80109A40[12];
    } else {
        arg0->unk50.data = (const u8*)D_80109A40[13];
    }
    arg0->timer = 5;
    arg0->unk6++;
}

void func_800A833C(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800A836C(struct ShotObj* arg0)
{
    D_80109AC4[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A83C4);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A84D4);

INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A858C);

void (*D_80109A78[])(struct ShotObj*) = {
    func_800A7B2C,
    func_800A7BE8,
    func_800A7BC8,
};

void (*D_80109A84[])(struct ShotObj*) = {
    func_800A7C50,
    func_800A7E40,
    func_800A7FF8,
    func_800A8164,
    func_800A829C,
    func_800A836C,
};

void (*D_80109A9C[])(struct ShotObj*) = {
    func_800A7CE8,
    func_800A7E10,
};

void (*D_80109AA4[])(struct ShotObj*) = {
    func_800A7E98,
    func_800A7F44,
};

void (*D_80109AAC[])(struct ShotObj*) = {
    func_800A8074,
    func_800A80D4,
};

void (*D_80109AB4[])(struct ShotObj*) = {
    func_800A81E0,
    func_800A826C,
};

void (*D_80109ABC[])(struct ShotObj*) = {
    func_800A82EC,
    func_800A833C,
};

void (*D_80109AC4[])(struct ShotObj*) = {
    func_800A83C4,
    func_800A84D4,
};
