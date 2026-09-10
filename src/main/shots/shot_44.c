// ShotObj, shot_object_update_funcs[44]
// 800A6FCC..800A7AF0
#include "common.h"

void func_800A6FCC(struct ShotObj* arg0)
{
    D_801099E8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7008);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7104);

void func_800A7208(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    weapon->unk84--;
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7240);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7318);

void func_800A73A4(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A73C4);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7458);

void func_800A74E4(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7504);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7570);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7600);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A766C);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A77D8);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7820);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7878);

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7928);

void func_800A79A4(struct ShotObj* arg0)
{
    func_80015DC8();
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A79E0);

void func_800A7A54(struct ShotObj* arg0)
{
    func_80015DC8();
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 8;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7A90);

void (*D_801099E8[])(struct ShotObj*) = {
    func_800A7008,
    func_800A7104,
    func_800A7208,
    func_800A7240,
    func_800A7318,
    func_800A73A4,
    func_800A73C4,
    func_800A7458,
    func_800A74E4,
};
