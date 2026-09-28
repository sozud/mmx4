// WeaponObj, weapon_object_update_funcs[5]
// 800957B0..800961B0
#include "common.h"

void func_800957B0(struct WeaponObj* arg0)
{
    s32 shouldSetState;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    shouldSetState = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        shouldSetState = 1;
    }
    if (g_Player.unk93 != 5) {
        shouldSetState = 1;
    }
    if (shouldSetState != 0) {
        arg0->state = 3;
    }

    D_80108958[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095854);

void func_8009596C(struct WeaponObj* arg0)
{
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x2C, 0x20) == 0) && (arg0->unk98 == 0)) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        D_80108968[arg0->unk5](arg0);
        if (arg0->unk50 != 0) {
            if (arg0->unk17 == 2) {
                arg0->unk50 = D_80108948;
                return;
            }
            arg0->unk50 = D_80108944;
        }
    } else {
        func_80095DA8(arg0);
    }
}

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
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80095DA8(arg0);
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
}

void func_80095BE8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

s32 func_80095C38(struct WeaponObj* arg0)
{
    s32 mask;
    u32 flags;

    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    flags = arg0->unk70;
    if (mask & flags) {
        if (flags & 8) {
            func_80095D60(arg0);
        } else {
            func_80095D18(arg0);
        }
        func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x20);
        return 1;
    }
    return 0;
}

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

// WeaponObj, weapon_object_update_funcs[14]

void func_80095DC0(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 5) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108974[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095E3C);

void func_80095F9C(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2C, 0x18) == 0) {
        func_80015DC8(arg0);
        func_8002B718(MOVING_OBJECT(arg0));
        D_80108984[arg0->unk5](arg0);
        return;
    }

    func_80095DA8(arg0);
}

void func_80096018(struct WeaponObj* arg0)
{
    if (g_Player.input.buttons.held & 0xC) {
        arg0->ext.weapon_14.unk8D = 5;
        arg0->ext.weapon_14.unk8C = 0;
        arg0->unk5 = 1;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x18);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80096060);

void func_80096170(struct WeaponObj* arg0)
{
    if (arg0->unk98 != 0) {
        func_80095DA8(arg0);
        return;
    }

    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x18);
}

struct Unk_unk68 D_80108944[] = {
    { -16, -8, 0x22, 0xE },
};

struct Unk_unk68 D_80108948[] = {
    { -10, -16, 0x12, 0x1C },
};

struct Unk_unk68 D_8010894C[] = {
    { 0, 0, 8, 6 },
};

struct Unk_unk68 D_80108950[] = {
    { -24, -12, 0x3E, 0x18 },
};

struct Unk_unk68 D_80108954[] = {
    { -10, -16, 0x12, 0x22 },
};

void (*D_80108958[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095854,
    (void (*)(struct WeaponObj*))func_8009596C,
    (void (*)(struct WeaponObj*))func_80095B94,
    (void (*)(struct WeaponObj*))func_80095BE8,
};

void (*D_80108968[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095A28,
    (void (*)(struct WeaponObj*))func_80095AAC,
    (void (*)(struct WeaponObj*))func_80095B10,
};

void (*D_80108974[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095E3C,
    (void (*)(struct WeaponObj*))func_80095F9C,
    (void (*)(struct WeaponObj*))func_80095B94,
    (void (*)(struct WeaponObj*))func_80095BE8,
};

void (*D_80108984[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80096018,
    (void (*)(struct WeaponObj*))func_80096060,
    (void (*)(struct WeaponObj*))func_80096170,
};
