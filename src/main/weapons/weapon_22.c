// WeaponObj, weapon_object_update_funcs[22]
// 80092D64..80092F08
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_22", func_80092D64);

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
