// WeaponObj, weapon_object_update_funcs[9, 18]
// 80092648..800927EC
#include "common.h"

void charge_shot_update(struct WeaponObj* arg0)
{
    charge_shot_state_funcs[arg0->state](arg0);
}

// charge_shot_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_09_charge_shot", func_80092684);

void charge_shot_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x14) == 0 && arg0->unk98 == 0) {
        animate_object(arg0);
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
        return;
    }
    buster_shot_hide(arg0);
}

void player_shot_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*charge_shot_state_funcs[])(struct WeaponObj*) = {
    func_80092684,
    charge_shot_main,
    player_shot_despawn,
    player_shot_despawn,
};
