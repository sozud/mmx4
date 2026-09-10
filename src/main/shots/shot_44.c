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

void func_800A77D8(struct ShotObj* arg0)
{
    func_80015DC8();
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0xF);
        arg0->unk5 = 5;
    }
}

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

u8 D_801099D4[4] = { 0xFA, 0xFC, 0x0A, 0x07 };

u8 D_801099D8[4] = { 0xF6, 0xF9, 0x12, 0x0E };

u8 D_801099DC[4] = { 0xEE, 0xEB, 0x28, 0x2B };

u8 D_801099E0[4] = { 0x88, 0xEE, 0xE5, 0x22 };

u8 D_801099E4[4] = { 0xEE, 0x85, 0x22, 0xF5 };

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

void (*D_80109A0C[])(struct ShotObj*) = {
    func_800A7504,
    func_800A7570,
    func_800A7600,
    func_800A766C,
    func_800A77D8,
    func_800A7820,
};

void (*D_80109A24[])(struct ShotObj*) = {
    func_800A7878,
    func_800A7928,
    func_800A79A4,
};

void (*D_80109A30[])(struct ShotObj*) = {
    func_800A79E0,
    func_800A7A54,
};
