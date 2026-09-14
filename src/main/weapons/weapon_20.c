#include "common.h"

void func_800929A0(struct WeaponObj* arg0)
{
    D_80108758[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_800929DC);

void func_80092AE4(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2A, 0x22) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->id == 0x14) {
            func_80092B5C(arg0);
            return;
        }
        func_80092C2C(arg0);
        return;
    }
    func_80092600(arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_80092B5C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_80092C2C);

void func_80092CEC(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk84.word == 0) {
        owner = arg0->owner;
        if (owner->unk8E == 0) {
            arg0->unk84.word = 1;
        }
        if (owner->unk15 != arg0->unk15) {
            arg0->unk84.word = 1;
        }
        if (arg0->unk84.word == 0) {
            func_80092E2C(VISUAL_OBJECT(arg0), owner, arg0->id);
        }
    }
}

void (*D_80108758[])(struct WeaponObj*) = {
    func_800929DC,
    func_80092AE4,
    func_800927B4,
    func_800927B4,
};
