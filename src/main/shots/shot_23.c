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
        arg0->unk7C->unk80 = 0;
    }
    func_80015DC8();
}

INCLUDE_ASM("main/nonmatchings/shots/shot_23", func_8009DFA0);

void func_8009E098(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801090AC[])(struct ShotObj*) = {
    func_8009DD7C,
    func_8009DE04,
    func_8009E098,
};
