// ShotObj, shot_object_update_funcs[23]
// 8009DD40..8009E0B8
#include "common.h"

void func_8009DD40(struct ShotObj* arg0)
{
    D_801090AC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_23", func_8009DD7C);

INCLUDE_ASM("main/nonmatchings/shots/shot_23", func_8009DE04);

void func_8009DF40(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
}

void func_8009DF60(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk7C->unk80.word = 0;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_23", func_8009DFA0);

void func_8009E098(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80109014[5])(struct ShotObj*) = {
    func_8009D85C,
    func_8009D8F0,
    func_8009DA28,
    func_8009DA7C,
    func_8009DB1C,
};

u8 D_80109028[4] = { 0xFC, 0x82, 0x07, 0x9B };

u8 D_8010902C[32][4] = {
    { 2, 1, 2, 0 },
    { 2, 0, 2, 2 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 0, 0, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 0, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 0x7F, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
};

void (*D_801090AC[])(struct ShotObj*) = {
    func_8009DD7C,
    func_8009DE04,
    func_8009E098,
};

void (*D_801090B8[3])(struct ShotObj*) = {
    func_8009DF40,
    func_8009DF60,
    func_8009DFA0,
};
