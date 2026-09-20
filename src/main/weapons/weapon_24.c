// WeaponObj, weapon_object_update_funcs[24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]
// 80097EEC..800981CC
#include "common.h"

void func_80097EEC(struct WeaponObj* arg0)
{
    s32 var_a0;
    struct PlayerObj* ptr = &g_Player;

    var_a0 = 0;
    if (g_Player.unk5C == 0) {
        var_a0 = 1;
    }
    if (g_Player.unkC3 != 0) {
        var_a0 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a0 = 1;
    }
    if (arg0->unk84.word != g_Player.unk17) {
        var_a0 = 1;
    }
    if (var_a0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    if (arg0->state != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
        } else {
            func_80098138(arg0, ptr);
        }
    } else {
        func_80097FC4(arg0, ptr);
        func_80098138(arg0, ptr);
    }
}

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
