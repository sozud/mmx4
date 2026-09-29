// WeaponObj, weapon_object_update_funcs[58]
// 80098990..80098ABC
#include "common.h"

void ice_block_hitbox_update(struct WeaponObj* arg0)
{
    ice_block_hitbox_state_funcs[arg0->state](arg0);
}

// ice_block_hitbox_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_58_ice_block_hitbox", func_800989CC);

void ice_block_hitbox_main(struct WeaponObj* arg0)
{
    if ((u8)arg0->unk5-- == 0) {
        arg0->state = 2;
    }
}

void ice_block_hitbox_despawn(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 ice_block_hitbox_box_0[4] = { 0xF4, 0xB1, 0x16, 0x88 };

u8 ice_block_hitbox_box_1[4] = { 0xF4, 0xB1, 0x16, 0x4C };

u8 ice_block_hitbox_box_2[4] = { 0xF4, 0, 0x16, 0x39 };

void (*ice_block_hitbox_state_funcs[])(struct WeaponObj*) = {
    func_800989CC,
    ice_block_hitbox_main,
    ice_block_hitbox_despawn,
};
