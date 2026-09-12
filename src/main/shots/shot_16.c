// ShotObj, shot_object_update_funcs[16]
// 8009C364..8009C5F0
#include "common.h"

void func_8009C364(struct ShotObj* arg0)
{
    D_80108F54[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_16", func_8009C3A0);

INCLUDE_ASM("main/nonmatchings/shots/shot_16", func_8009C45C);

void func_8009C588(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    if ((weapon->active != 0) && (weapon->id == 0x1D) && (weapon->unk2 >= 0)) {
        weapon->ext.weapon_29.unk90 = 0;
        weapon->unk80.bytes[1] &= 0xFE;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108F54[])(struct ShotObj*) = {
    func_8009C3A0,
    func_8009C45C,
    func_8009C588,
};
