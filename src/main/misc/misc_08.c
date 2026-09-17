// MiscObj, misc_object_update_funcs[8]
// 800C9510..800C9D64
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9510);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C969C);

void func_800C9914(struct MiscObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->ext.misc_8.timer = 0xF;
        arg0->unk5++;
    }
}

void func_800C993C(struct MiscObj* arg0)
{
    s32 step;
    s32 specialStep;

    if (arg0->ext.misc_8.timer == 0) {
        arg0->unk5++;
        step = arg0->unk2;

        if (step < 0x16) {
            if (step < 0x13) {
                specialStep = 5;
            } else {
                return;
            }
        } else {
            specialStep = 0x19;
        }

        if (step == specialStep) {
            return;
        }
        func_80015D60(arg0, D_8010E090.entries[arg0->unk2].second);
    } else {
        arg0->ext.misc_8.timer--;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C99CC);

void func_800C9C64(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    D_8010E0E0[arg0->unk5](arg0);
}

void func_800C9CB0(struct ItemObj* arg0)
{
    D_8010E0EC[(u8)arg0->unk54](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

void func_800C9D08(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C9D28(struct MiscObj* arg0)
{
    D_8010E0F4[arg0->state](arg0);
}
