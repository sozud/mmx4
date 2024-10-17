#include "common.h"

// search lights don't appear in level if nopped out
// effect_obj 0x07
void func_800B6B18(struct EffectObj* arg0)
{
    // asm(".rept 13 ; nop ; .endr");
    D_8010B4C4[arg0->state](arg0);
}

// D_8010B4C4 state 0
INCLUDE_ASM("asm/us/main/nonmatchings/search_light_maker", func_800B6B54);

// D_8010B4C4 state 1
void func_800B6C74(s32 arg0)
{
    func_800B6C9C(arg0);
}

// D_8010B4C4 state 2
void func_800B6C94(s32 arg0)
{
}

void func_800B6C9C(s32 arg0)
{
    func_800B6D1C(arg0, 0, func_800B6FF4(arg0, 0));
    func_800B6D1C(arg0, 1, func_800B6FF4(arg0, 1));
    func_800B6D1C(arg0, 2, func_800B6FF4(arg0, 2));
}

void func_800B6D1C(s32 arg0, s8 arg1, s8 arg2)
{
    s8 temp;
    u16 a1, a3;
    struct BackgroundObj* temp_s0;

    temp_s0 = &background_objects[arg1];
    if (arg2 != 0) {
        if (arg2 & 1) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            func_800B6EB4(a1 + 0x130, a1 + 0x190, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 2;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            func_800B6EB4(a1 - 0x50, a1 - 0x10, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 4;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            func_800B6EB4(a1 - 0x50, a1 + 0x190, a3 + 0x100, a3 + 0x140, arg0);
        }
        temp = arg2 & 8;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            func_800B6EB4(a1 - 0x50, a1 + 0x190, a3 - 0x50, a3 - 0x10, arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/search_light_maker", func_800B6EB4);

s8 func_800B6FF4(s32 arg0, s8 arg1)
{
    struct BackgroundObj* ptr = &background_objects[arg1];
    s8 result = 0;

    if (ptr->unk14.i.hi != ptr->x_pos.i.hi) {
        if (ptr->unk14.i.hi < ptr->x_pos.i.hi) {
            result = 1;
        } else {
            result = 2;
        }
    }

    if (ptr->unk18.i.hi != ptr->y_pos.i.hi) {
        if (ptr->unk18.i.hi < ptr->y_pos.i.hi) {
            result |= 4;
        } else {
            result |= 8;
        }
    }

    return result;
}
