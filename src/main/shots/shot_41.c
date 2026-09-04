// ShotObj, shot_object_update_funcs[41]
// 800A56E4..800A6374
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A56E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5A04);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5C90);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5D20);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5D78);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5E60);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A5F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A6028);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A6094);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A60D0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A61CC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A6238);

void func_800A6258(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A6260);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_41", func_800A62D0);

void func_800A62F0(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s0 = arg0->unk7C;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    if (temp_s0->base.state == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    }
    D_80109950[arg0->base.state](arg0);
}

void (*D_80109950[])(struct ShotObj*) = {
    func_800A56E4,
    func_800A6260,
    func_800A62D0,
};
