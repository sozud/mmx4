// MiscObj, misc_object_update_funcs[8]
// 800C9510..800C9D64
#include "common.h"

extern u8 D_8010E02C[];
extern u8 D_8010E030[];
extern u8 D_8010E040[];
extern u8 D_8010E044[];
extern u8 D_8010E050[];
extern u8 D_8010E054[];

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9510);

void func_800C969C(struct MiscObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (arg0->on_screen != 0) {
            switch (arg0->unk2) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                func_800C833C(2, D_8010E02C, arg0, FIXED(8), FIXED(0));
                break;
            case 5:
            case 20:
                func_800C833C(3, D_8010E02C, arg0, FIXED(16), FIXED(16));
                func_800C833C(3, D_8010E030, arg0, FIXED(48), FIXED(16));
                func_800C833C(4, D_8010E040, arg0, FIXED(40), FIXED(48));
                func_800C833C(4, D_8010E044, arg0, FIXED(40), FIXED(64));
                break;
            case 6:
                func_800C833C(2, D_8010E02C, arg0, FIXED(8), FIXED(32));
                break;
            case 7:
            case 8:
                func_800C833C(2, D_8010E02C, arg0, FIXED(-8), FIXED(32) + FIXED((arg0->unk2 - 7) * 8));
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                func_800C833C(2, D_8010E02C, arg0, FIXED(-8), FIXED(32) + FIXED((arg0->unk2 - 9) * 4));
                break;
            case 13:
            case 14:
                func_800C833C(2, D_8010E02C, arg0, FIXED(8), FIXED(32) + FIXED((arg0->unk2 - 13) * 8));
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                func_800C833C(2, D_8010E02C, arg0, FIXED(8), FIXED(32) + FIXED((arg0->unk2 - 15) * 4));
                break;
            case 19:
                func_800C833C(4, D_8010E050, arg0, FIXED(16), FIXED(24));
                func_800C833C(3, D_8010E054, arg0, FIXED(16), FIXED(56));
                break;
            }
        }
        if (arg0->unk15 != 0) {
            arg0->x_pos.u.hi -= 0x10;
        }
        func_800DABE4(D_8010E058[arg0->unk2].variant, (s16)arg0->x_pos.u.hi, arg0->y_pos.i.hi);
        arg0->state++;
    }
}

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

void func_800C99CC(struct MiscObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        if (arg0->on_screen != 0) {
            switch (arg0->unk2) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 22:
            case 23:
            case 24:
                func_800C833C(2, D_8010E038, arg0, FIXED(8), FIXED(32));
                break;
            case 5:
            case 20:
            case 21:
            case 25:
                func_800C833C(4, D_8010E034, arg0, FIXED(16), FIXED(16));
                func_800C833C(4, D_8010E038, arg0, FIXED(32), FIXED(16));
                func_800C833C(3, D_8010E03C, arg0, FIXED(48), FIXED(16));
                func_800C833C(3, D_8010E048, arg0, FIXED(40), FIXED(48));
                func_800C833C(2, D_8010E04C, arg0, FIXED(40), FIXED(64));
                break;
            case 6:
                func_800C833C(2, D_8010E038, arg0, FIXED(8), FIXED(32));
                break;
            case 7:
            case 8:
                func_800C833C(2, D_8010E038, arg0, FIXED(-8), FIXED((arg0->unk2 - 7) * 8) + FIXED(32));
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                func_800C833C(2, D_8010E038, arg0, FIXED(-8), FIXED((arg0->unk2 - 9) * 4) + FIXED(32));
                break;
            case 13:
            case 14:
                func_800C833C(2, D_8010E038, arg0, FIXED(8), FIXED((arg0->unk2 - 7) * 8) + FIXED(32));
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                func_800C833C(2, D_8010E038, arg0, FIXED(8), FIXED((arg0->unk2 - 9) * 4) + FIXED(32));
                break;
            case 19:
                func_800C833C(4, D_8010E034, arg0, FIXED(16), FIXED(24));
                func_800C833C(4, D_8010E038, arg0, FIXED(16), FIXED(56));
                break;
            }
        }
        if (arg0->unk15 != 0) {
            arg0->x_pos.u.hi -= 0x10;
        }
        func_800DABE4(D_8010E090.entries[arg0->unk2].third, (s16)arg0->x_pos.u.hi, arg0->y_pos.i.hi);
        arg0->state++;
    }
}

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
