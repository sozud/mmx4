// WeaponObj, weapon_object_update_funcs[59]
// 80098ABC..80098F4C
#include "common.h"

void func_80098ABC(struct WeaponObj* arg0)
{
    D_80108BD8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098AF8);

void func_80098C08(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) && (arg0->unk98 == 0)) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
    arg0->on_screen = 0;
    arg0->unk50 = 0;
}

void func_80098C84(struct WeaponObj* arg0)
{
    struct PlayerObj* owner = arg0->owner;
    u8 timer = owner->unk86;
    if (timer != 0) {
        owner->unk86 = timer - 1;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098CC0);

void func_80098D64(struct ShotObj* arg0)
{
    D_80108BE4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098DA0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098EA8);

u8 D_80108BCC[4] = { 0xFC, 0xFD, 6, 5 };

s16 D_80108BD0[2][2] = {
    { -0x2B, 0 },
    { -0x2C, 0x19 },
};

void (*D_80108BD8[])(struct WeaponObj*) = {
    func_80098AF8,
    func_80098C08,
    func_80098C84,
};

void (*D_80108BE4[])(struct WeaponObj*) = {
    func_80098AF8,
    func_80098CC0,
    func_80098C84,
};
