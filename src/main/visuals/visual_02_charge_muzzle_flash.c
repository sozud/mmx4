// VisualObj, visual_object_update_funcs[2]
// 800AEED8..800AF22C
#include "common.h"

void charge_muzzle_flash_update(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        charge_muzzle_flash_init(arg0);
    } else {
        charge_muzzle_flash_main(arg0);
    }
}

void charge_muzzle_flash_init(struct VisualObj* arg0)
{
    s32 temp_s0;
    s32 var_a1;

    arg0->on_screen = 1;
    if (arg0->unk2 == 9) {
        var_a1 = 0;
    }
    if (arg0->unk2 == 0x12) {
        var_a1 = 1;
    }
    if (arg0->unk2 == 0x14) {
        var_a1 = 2;
    }
    temp_s0 = var_a1;
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + ((u32*)SP_SPRITE_FRAMES)[charge_muzzle_flash_types[temp_s0].archive_slot];
    arg0->animation_table = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 0;
    arg0->unk15 = g_Player.unk15;
    arg0->unk5C.value = 0;
    charge_muzzle_flash_follow(arg0);
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    set_animation(arg0, charge_muzzle_flash_types[temp_s0].animation);
    func_8001540C(1, charge_muzzle_flash_types[temp_s0].sound, arg0);
    arg0->state++;
    update_on_screen(arg0, 0x40, 0x20);
}

void charge_muzzle_flash_main(struct VisualObj* arg0)
{
    animate_object(arg0);
    charge_muzzle_flash_follow(arg0);
    if (arg0->unk5 == 0) {
        charge_muzzle_flash_spawn_shot(arg0);
    } else {
        charge_muzzle_flash_fade(arg0);
    }
}

void charge_muzzle_flash_spawn_shot(struct VisualObj* arg0)
{
    struct WeaponObj* temp_v0;

    if (arg0->animation_step.fields.event != 0) {
        temp_v0 = find_free_weapon_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x21;
            temp_v0->id = arg0->unk2;
            temp_v0->unk2 = 0;
            temp_v0->x_pos.val = arg0->x_pos.val;
            temp_v0->y_pos.val = arg0->y_pos.val;
            temp_v0->unk15 = arg0->unk15;
            temp_v0->unk3C = arg0->unk3C;
            temp_v0->animation_table = arg0->animation_table;
            temp_v0->unk40 = arg0->unk40;
            temp_v0->unk42 = arg0->unk42;
            temp_v0->unk16 = arg0->unk16;
        }
        arg0->unk5++;
    }
    update_on_screen(arg0, 0x40, 0x20);
}

void charge_muzzle_flash_fade(struct VisualObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0 || arg0->unk5C.value != 0) {
        ZeroObjectState(arg0);
    } else {
        update_on_screen(arg0, 0x40, 0x20);
    }
}

void charge_muzzle_flash_follow(struct VisualObj* arg0)
{
    struct PlayerObj* entity;

    if (arg0->unk5C.value != 0) {
        return;
    }

    entity = &g_Player;
    if (entity->attacking == 0) {
        arg0->unk5C.value = 1;
    }
    if (entity->unk15 != arg0->unk15) {
        arg0->unk5C.value = 1;
    }
    if (arg0->unk5C.value == 0) {
        buster_shot_place_at_muzzle(arg0, entity, arg0->unk2);
    }
}

struct VisualAttachmentInit charge_muzzle_flash_types[4] = {
    { 0x03, 0x16, 0x09 },
    { 0x02, 0x17, 0x0A },
    { 0x02, 0x19, 0x0A },
    { 0x00, 0x00, 0x00 },
};
