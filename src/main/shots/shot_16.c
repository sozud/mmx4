// ShotObj, shot_object_update_funcs[16]
// 8009C364..8009C5F0
#include "common.h"

void func_8009C364(struct ShotObj* arg0)
{
    D_80108F54[arg0->state](arg0);
}

void func_8009C3A0(struct ShotObj* rawArg0)
{
    struct ShotObj* arg0 = rawArg0;
    s32 value;

    value = 1;
    arg0->state = value;
    arg0->on_screen = value;
    arg0->unk5C = value;
    value = arg0->unk2;
    arg0->unk16 = 6;
    arg0->unk60 = 4;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk50.data = 0;

    switch (value) {
    case 0:
        arg0->unk84.value = 6;
        arg0->unk15 = 0;
        break;
    case 1:
        arg0->unk84.value = 6;
        arg0->unk15 = 0x40;
        break;
    case 2:
        arg0->unk84.value = 9;
        break;
    case 3:
        arg0->unk84.value = 0xC;
        break;
    }

    func_80015D60(arg0, arg0->unk84.value);
}

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
