// EffectObj, effect_object_update_funcs[30]
// 800BC2E0..800BC4D8
#include "common.h"

void func_800BC2E0(struct EffectObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 0;
    qux_object.base.active = 0x41;
    qux_object.base.id = 1;
    qux_object.base.state = 0;
    qux_object.base.unk5 = 0;
    qux_object.base.unk6 = 0;
    qux_object.base.unk7 = 0;
    qux_object.base.unk2 = arg0->unk2;
    qux_object.base.unk10 = arg0->unk10;
    qux_object.base.x_pos.val = arg0->x_pos.val;
    qux_object.base.y_pos.val = arg0->y_pos.val;
    func_8002B108(arg0);
}

void func_800BC370(struct EffectObj* arg0)
{
    s16 temp_a0;
    s16 temp_v1;

    arg0->x_pos.val &= 0xFFF00000;
    arg0->y_pos.val &= 0xFFF00000;
    temp_a0 = arg0->x_pos.i.hi;
    temp_v1 = qux_object.base.x_pos.i.hi;
    if (temp_v1 >= temp_a0 + 0x18 && temp_a0 + 0x30 >= temp_v1 && qux_object.base.y_pos.i.hi == arg0->y_pos.i.hi - 0x1A) {
        arg0->unk5 = 3;
        arg0->state++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_30", func_800BC3E8);
