// WeaponObj, weapon_object_update_funcs[24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]
// 80097EEC..800981CC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_24", func_80097EEC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_24", func_80097FC4);

void func_80098138(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    u8 id;
    u8 value;

    arg0->x_pos.val = arg1->x_pos.val;
    arg0->y_pos.val = arg1->y_pos.val;
    arg0->unk15 = arg1->unk15;
    if (arg0->animation_step.fields.event == 0) {
        arg0->unk50 = 0;
    } else {
        arg0->unk50 = (u8*)&D_80108A50[arg0->animation_step.fields.event];
    }
    id = arg0->id;
    if (id - 0x18 < 2U) {
        value = arg0->unk2 + 1;
    } else {
        value = arg0->animation_step.fields.event;
    }
    arg0->unk64 = value;
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}
