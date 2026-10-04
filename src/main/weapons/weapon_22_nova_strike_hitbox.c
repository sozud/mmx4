// WeaponObj, weapon_object_update_funcs[22]
// 80092D64..80092F08
#include "common.h"

void nova_strike_hitbox_update(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    u8 temp_v0;

    if (g_Player.unk17 != 0x6A) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state == 0) {
        arg0->unk50 = &nova_strike_hit_box;
        arg0->unk64 = 1U;
        arg0->ext.raw[0] = 4U;
        arg0->state++;
    } else {
        temp_v0 = arg0->ext.raw[0];
        if (temp_v0 == 0) {
            arg0->ext.raw[0] = 4U;
            arg0->unk64++;
        } else {
            arg0->ext.raw[0] = temp_v0 - 1;
        }
    }
    arg0->x_pos.val = player->x_pos.val;
    arg0->y_pos.val = player->y_pos.val;
    arg0->unk15 = player->unk15;
}

u16 buster_muzzle_offsets[48] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFEF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFF2, 0, 0, 0, 0xFFF2 };

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_22_nova_strike_hitbox", buster_shot_place_at_muzzle);
#else
void buster_shot_place_at_muzzle(struct VisualObj* arg0, struct PlayerObj* arg1, arg_u8 arg2)
{
    s16 y;
    s32 frame_component;
    s8 weapon_offset;

    frame_component = arg1->animation_step.fields.frame_index * 2;
    weapon_offset = arg2;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = arg1->x_pos.u.hi - D_8011B230.components[frame_component];
        arg0->x_pos.i.hi -= buster_muzzle_offsets[weapon_offset * 2];
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.u.hi + D_8011B230.components[frame_component];
        arg0->x_pos.i.hi += buster_muzzle_offsets[weapon_offset * 2];
    }
    y = arg1->y_pos.u.hi + D_8011B230.components[frame_component + 1];
    arg0->y_pos.i.hi = y;
    arg0->y_pos.i.hi = y + buster_muzzle_offsets[weapon_offset * 2 + 1];
}
#endif
