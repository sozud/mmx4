// EffectObj, effect_object_update_funcs[30]
// 800BC2E0..800BC4D8
#include "common.h"

void func_800BC2E0(struct EffectObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 0;
    qux_object.active = 0x41;
    qux_object.id = 1;
    qux_object.state = 0;
    qux_object.unk5 = 0;
    qux_object.unk6 = 0;
    qux_object.unk7 = 0;
    qux_object.unk2 = arg0->unk2;
    qux_object.backref = arg0->backref;
    qux_object.x_pos.val = arg0->x_pos.val;
    qux_object.y_pos.val = arg0->y_pos.val;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800BC370(struct EffectObj* arg0)
{
    s16 temp_a0;
    s16 temp_v1;

    arg0->x_pos.val &= 0xFFF00000;
    arg0->y_pos.val &= 0xFFF00000;
    temp_a0 = arg0->x_pos.i.hi;
    temp_v1 = qux_object.x_pos.i.hi;
    if (temp_v1 >= temp_a0 + 0x18 && temp_a0 + 0x30 >= temp_v1 && qux_object.y_pos.i.hi == arg0->y_pos.i.hi - 0x1A) {
        arg0->unk5 = 3;
        arg0->state++;
    }
}

void func_800BC3E8(struct EffectObj* arg0)
{
    s8 temp_v0;
    struct ShotObj* temp_v0_2;
    struct ShotObj* temp_v0_3;

    temp_v0 = arg0->unk5 - 1;
    arg0->unk5 = temp_v0;
    if (temp_v0 == 0) {
        temp_v0_2 = find_free_shot_obj();
        if (temp_v0_2 != 0) {
            temp_v0_2->active = 0x41;
            temp_v0_2->id = 0x20;
            temp_v0_2->unk7C = WEAPON_OBJECT(arg0);
            temp_v0_2->unk2 = 0;
        }
        temp_v0_3 = find_free_shot_obj();
        if (temp_v0_3 != 0) {
            temp_v0_3->active = 0x41;
            temp_v0_3->id = 0x20;
            temp_v0_3->unk7C = WEAPON_OBJECT(arg0);
            temp_v0_3->unk2 = 1;
        }
        func_800AFAB4(0, arg0->x_pos.u.hi + 0x10, arg0->y_pos.i.hi, 0);
        func_800AFAB4(0, arg0->x_pos.u.hi + 0x28, arg0->y_pos.i.hi, 1);
        func_800DABE4(0xA, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x20);
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}
