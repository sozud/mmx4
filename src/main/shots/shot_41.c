// ShotObj, shot_object_update_funcs[41]
// 800A56E4..800A6374
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A56E4);

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5A04);

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5AA4);

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5BA8);

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5C90);

void func_800A5D20(struct ShotObj* arg0)
{
    D_80109914[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x30, 0x30);
}

void func_800A5D78(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    func_8002D9BC(arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
    if (weapon->unk5 != 7) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

void func_800A5DEC(struct ShotObj* arg0)
{
    func_8002D9BC(arg0);
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk50.data = 0;
        arg0->unk6++;
        func_80015D60(arg0, 0x20);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5E60);

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5F4C);

void func_800A6028(struct ShotObj* arg0)
{
    func_8002D9BC(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x80);
    if (arg0->on_screen == 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

void func_800A6094(struct ShotObj* arg0)
{
    D_80109920[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A60D0);

void func_800A61CC(struct ShotObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

void func_800A6238(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800A6258(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A6260);

void func_800A62D0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A62F0(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s0 = arg0->unk7C;
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    CollisionRelated(arg0);
    if (temp_s0->state == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    D_80109950[arg0->state](arg0);
}

u8 D_801098D0[4] = { 0xEE, 0xF3, 0x18, 0x19 };

u8 D_801098D4[2][4] = {
    { 0xF7, 0xF2, 0x10, 0x18 },
    { 0xF7, 0xF7, 0x0F, 0x11 },
};

u8 D_801098DC[4] = { 0xF2, 0xF0, 0x1D, 0x1D };

u8 D_801098E0[4] = { 0xF6, 0xF6, 0x13, 0x13 };

u8 D_801098E4[4] = { 0, 0, 0x0A, 9 };

u8 D_801098E8[4] = { 0xEC, 0x85, 0x26, 0xFA };

u8 D_801098EC[4] = { 0xF6, 0xF6, 0x13, 0x13 };

u8 D_801098F0[4] = { 1, 0, 0x0A, 9 };

s16 D_801098F4[8] = { 0, 8, -4, -0x0C, 4, -8, 0, 0x0C };

u16 D_80109904[8] = { 0x90, 0xB0, 0x150, 0x1D0, 0xE0, 0x180, 0x1A0, 0x120 };

void (*D_80109914[3])(struct ShotObj*) = {
    func_800A5AA4,
    func_800A5BA8,
    func_800A5C90,
};

void (*D_80109920[5])(struct ShotObj*) = {
    func_800A5D78,
    func_800A5DEC,
    func_800A5E60,
    func_800A5F4C,
    func_800A6028,
};

void (*D_80109934[7])(struct ShotObj*) = {
    func_800A6238,
    func_800A6258,
    func_800A5A04,
    func_800A5D20,
    func_800A6094,
    func_800A60D0,
    func_800A61CC,
};

void (*D_80109950[])(struct ShotObj*) = {
    func_800A56E4,
    func_800A6260,
    func_800A62D0,
};
