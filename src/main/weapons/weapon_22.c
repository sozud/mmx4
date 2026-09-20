// WeaponObj, weapon_object_update_funcs[22]
// 80092D64..80092F08
#include "common.h"

void func_80092D64(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    u8 temp_v0;

    if (g_Player.unk17 != 0x6A) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state == 0) {
        arg0->unk50 = &D_80108724;
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

u16 D_80108768[48] = {
    [18] = 0xFFEF,
    [36] = 0xFFF2,
    [40] = 0xFFF2,
};

void func_80092E2C(struct VisualObj* arg0, struct PlayerObj* arg1, s32 arg2)
{
    s16 y;
    s32 frame_component;
    s8 weapon_offset;

    frame_component = arg1->animation_step.fields.frame_index * 2;
    weapon_offset = arg2;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = arg1->x_pos.u.hi - D_8011B230.components[frame_component];
        arg0->x_pos.i.hi -= D_80108768[weapon_offset * 2];
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.u.hi + D_8011B230.components[frame_component];
        arg0->x_pos.i.hi += D_80108768[weapon_offset * 2];
    }
    y = arg1->y_pos.u.hi + D_8011B230.components[frame_component + 1];
    arg0->y_pos.i.hi = y;
    arg0->y_pos.i.hi = y + D_80108768[weapon_offset * 2 + 1];
}
