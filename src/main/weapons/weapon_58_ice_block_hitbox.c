// WeaponObj, weapon_object_update_funcs[58]
// 80098990..80098ABC
#include "common.h"

void ice_block_hitbox_update(struct WeaponObj* arg0)
{
    ice_block_hitbox_state_funcs[arg0->state](arg0);
}

extern u8 ice_block_hitbox_box_0[];
extern u8 ice_block_hitbox_box_1[];
extern u8 ice_block_hitbox_box_2[];

// ice_block_hitbox_init
void func_800989CC(struct WeaponObj* arg0)
{
    struct PlayerObj* owner = arg0->owner;

    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->state++;
    switch (arg0->unk2) {
    case 1:
        arg0->unk50 = ice_block_hitbox_box_2;
        break;
    case 2:
        arg0->unk50 = ice_block_hitbox_box_1;
        break;
    case 3:
        arg0->unk50 = NULL;
        break;
    case 0:
    default:
        arg0->unk50 = ice_block_hitbox_box_0;
        break;
    }
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->unk5 = 0xC;
}

void ice_block_hitbox_main(struct WeaponObj* arg0)
{
    if (arg0->unk5-- == 0) {
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
