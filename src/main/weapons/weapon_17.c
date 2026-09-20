// WeaponObj, weapon_object_update_funcs[17]
// 80097B28..80097EEC
#include "common.h"

void func_80097B28(struct WeaponObj* arg0)
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
    D_80108A34[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_17", func_80097BA4);

void func_80097CF4(struct WeaponObj* arg0)
{
    struct MiscObj* misc_obj;
    u8 timer;

    if (func_8002B1E8((struct BaseObj*)arg0, 0x20, 0x20) == 0) {
        timer = arg0->ext.weapon_17.timer;
        if (timer == 0) {
            arg0->ext.weapon_17.timer = 3;
            misc_obj = find_free_misc_obj();
            if (misc_obj != 0) {
                misc_obj->active = 1;
                misc_obj->id = 0x29;
                misc_obj->unk2 = ((s8)arg0->unk2) >> 1;
                misc_obj->bg_offset = arg0->bg_offset;
                misc_obj->x_pos.val = arg0->x_pos.val;
                misc_obj->y_pos.val = arg0->y_pos.val;
                misc_obj->unk15 = arg0->unk15;
            }
        } else {
            arg0->ext.weapon_17.timer = timer - 1;
        }
        func_80015DC8((struct AnimatedObj*)arg0);
        func_8002B718((struct MovingObj*)arg0);
        func_8002B318((struct BaseObj*)arg0, 0x20, 0x20);
        return;
    }
    func_80097B14(arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_17", func_80097DD8);
