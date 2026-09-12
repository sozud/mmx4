// ShotObj, shot_object_update_funcs[40]
// 800A5348..800A56E4
#include "common.h"

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->state](arg0);
}

void func_800A5384(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 2;
    arg0->unk68 = &D_80109894;
    arg0->unk5C = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk8A = 0;
    arg0->unk84.value = 0;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk58.data = NULL;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x7E;
    func_80015D60(arg0, 2);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5404);

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5460);

void func_800A5500(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5540);

void func_800A56C0(struct ShotObj* arg0)
{
    arg0->unk7C->unk7 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80109890[4] = { 0xCF, 0x82, 0x60, 0xFF };

struct Unk_unk68 D_80109894 = { 0, 8, 0x2E, 0x78 };

s16 D_80109898[4] = { 0x0AE0, 0x14E0, 0x1710, 0 };

u8 D_801098A0[8] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0 };

u8 D_801098A8[16] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0, 0 };

void (*D_801098B8[])(struct ShotObj*) = {
    func_800A5384,
    func_800A5540,
    func_800A56C0,
};

void (*D_801098C4[3])(struct ShotObj*) = {
    func_800A5404,
    func_800A5460,
    func_800A5500,
};
