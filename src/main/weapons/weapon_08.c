// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097B28
#include "common.h"

void func_80097860(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108A24[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_800978DC);

void func_80097A24(struct WeaponObj* arg0)
{
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) && (arg0->unk98 == 0)) {
        if (arg0->ext.raw[0] != 0) {
            arg0->ext.raw[0]--;
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B718(MOVING_OBJECT(arg0));
            arg0->unk50 = (const u8*)&D_801089FC[arg0->animation_step.fields.event];
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }

    func_80097B14(arg0);
}

void func_80097AC8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_80097B14(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}
