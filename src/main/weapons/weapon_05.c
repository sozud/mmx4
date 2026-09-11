// WeaponObj, weapon_object_update_funcs[5]
// 800957B0..80095DC0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_800957B0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095854);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_8009596C);

void func_80095A28(struct WeaponObj* arg0)
{
    if (func_80095C38(arg0) == 0) {
        if (g_Player.input.buttons.held & 8) {
            func_80095D18(arg0);
        }
        if (arg0->unk70 & 8) {
            func_80095CC0(arg0);
        }
        func_8002B718(MOVING_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
    }
}

void func_80095AAC(struct WeaponObj* arg0)
{
    if (func_80095C38(arg0) == 0) {
        if ((arg0->unk70 & 8) == 0) {
            func_80095D18(arg0);
        }
        func_8002B718(MOVING_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
    }
}

void func_80095B10(struct WeaponObj* arg0)
{
    s32 mask;
    u32 flags;

    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    flags = arg0->unk70;
    if (flags & 8) {
        if (mask & flags) {
            func_80095D60(arg0);
        } else {
            func_80095CC0(arg0);
        }
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
}

void func_80095B94(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        func_80095DA8(arg0);
        return;
    }
    func_8002B318((struct BaseObj*)arg0, 0x2C, 0x20);
}

void func_80095BE8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095C38);

void func_80095CC0(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 1);
    arg0->unk67 = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(6);
    } else {
        arg0->x_vel.val = FIXED(-6);
    }
    arg0->y_vel.val = 0;
    arg0->unk5 = 1;
}

void func_80095D18(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 2);
    arg0->unk67 = 1;
    arg0->y_vel.val = -FIXED(6);
    arg0->x_vel.val = 0;
    arg0->unk5 = 2;
}

void func_80095D60(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 6);
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

void func_80095DA8(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}
