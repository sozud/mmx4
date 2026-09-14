// ShotObj, shot_object_update_funcs[28]
// 8009F46C..8009F638
#include "common.h"

u8 D_801091C0[4] = { 0xDB, 0xF2, 0x1E, 0x37 };

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->x_pos.val = unk7C->x_pos.val;
    arg0->y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_28", func_8009F4C0);

void func_8009F594(struct ShotObj* arg0)
{
    struct WeaponObj* temp_v1;

    temp_v1 = arg0->unk7C;
    if (temp_v1->state >= 2) {
        arg0->state++;
        return;
    }
    if (temp_v1->animation_step.fields.frame_index == 3) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002D9BC(arg0);
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    }
}

void func_8009F618(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801091C4[])(struct ShotObj*) = {
    func_8009F4C0,
    func_8009F594,
    func_8009F618,
};
