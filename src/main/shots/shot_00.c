// ShotObj, shot_object_update_funcs[0]
// 800994A0..80099B30
#include "common.h"

void func_800994A0(struct ShotObj* arg0)
{
    D_80108C74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_800994DC);

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_80099784);

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_8009982C);

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_800998D4);

void func_800999D0(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002D9BC(arg0);
    func_8002B318((struct BaseObj*)arg0, 0x19, 0x19);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state = 4;
        arg0->unk5 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_80099A28);

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_80099A8C);

void func_80099B0C(struct ShotObj* arg0)
{
    arg0->unk7C->unk54 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108C74[])(struct ShotObj*) = {
    func_800994DC,
    func_80099784,
    func_8009982C,
    func_80099A28,
    func_80099B0C,
    func_80099A8C,
};
