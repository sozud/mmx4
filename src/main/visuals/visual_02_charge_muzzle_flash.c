// VisualObj, visual_object_update_funcs[2]
// 800AEED8..800AF22C
#include "common.h"
#include "main/objects.h"
#include "main/visuals/visual_02_charge_muzzle_flash.h"
#include "main/55C4.h"
#include "main/sprite_animations.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"

struct VisualAttachmentInit {
    u8 archive_slot, animation, sound;
};

extern struct VisualAttachmentInit charge_muzzle_flash_types[4];
#include "weapon_resources.h"

void charge_muzzle_flash_fade(struct VisualObj* arg0);
void charge_muzzle_flash_follow(struct VisualObj* arg0);
void charge_muzzle_flash_init(struct VisualObj* arg0);
void charge_muzzle_flash_main(struct VisualObj* arg0);
void charge_muzzle_flash_spawn_shot(struct VisualObj* arg0);

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
#ifdef VERSION_DEMO
    if (arg0->unk2 == 0x13) {
        var_a1 = 2;
    }
#endif
    if (arg0->unk2 == 0x14) {
        var_a1 = DEMO_ALT(2, 3);
    }
    temp_s0 = var_a1;
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + ((u32*)SP_SPRITE_FRAMES)[charge_muzzle_flash_types[temp_s0].archive_slot];
    arg0->animation_table = &D_8011BF40;
    arg0->unk40 = WEAPON_TEXTURE_BASE;
    arg0->unk42 = WEAPON_PALETTE_2;
    arg0->unk16 = VISUAL_SATURN_LAYER(0);
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
    struct WeaponObj* weapon;

    if (arg0->animation_step.fields.event != 0) {
        weapon = find_free_weapon_obj();
        if (weapon != NULL) {
            weapon->active = 0x21;
            weapon->id = arg0->unk2;
#ifndef VERSION_DEMO
            weapon->unk2 = 0;
#endif
            weapon->x_pos.val = arg0->x_pos.val;
            weapon->y_pos.val = arg0->y_pos.val;
            weapon->unk15 = arg0->unk15;
            weapon->unk3C = arg0->unk3C;
            weapon->animation_table = arg0->animation_table;
            weapon->unk40 = arg0->unk40;
            weapon->unk42 = arg0->unk42;
            weapon->unk16 = arg0->unk16;
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

#ifdef VERSION_DEMO
extern s8* D_800D9684_demo[4];

static inline void charge_muzzle_flash_place(struct VisualObj* arg0, struct PlayerObj* player, s32 type)
{
    s32 shot;
    s8* offsets;

    if (type == 9)
        shot = 0;
    if (type == 0x12)
        shot = 1;
    if (type == 0x13)
        shot = 2;
    if (type == 0x14)
        shot = 3;
    offsets = D_800D9684_demo[shot];
    offsets += player->animation_step.fields.frame_index * 2;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = player->x_pos.i.hi - offsets[0];
    } else {
        arg0->x_pos.i.hi = player->x_pos.i.hi + offsets[0];
    }
    arg0->y_pos.i.hi = player->y_pos.i.hi + offsets[1];
}
#endif

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
#ifdef VERSION_DEMO
        charge_muzzle_flash_place(arg0, entity, arg0->unk2);
#else
        buster_shot_place_at_muzzle(arg0, entity, arg0->unk2);
#endif
    }
}

struct VisualAttachmentInit charge_muzzle_flash_types[4] = {
    { 0x03, 0x16, 0x09 },
    { 0x02, 0x17, 0x0A },
#ifdef VERSION_DEMO
    { 0x01, 0x18, 0x09 },
    { 0x02, 0x19, 0x0A },
#else
    { 0x02, 0x19, 0x0A },
    { 0x00, 0x00, 0x00 },
#endif
};

#ifdef VERSION_DEMO
extern s8 D_800E7748_demo[];
extern s8 D_800E7948_demo[];
extern s8 D_800E7B48_demo[];
extern s8 D_800E7D48_demo[];

s8* D_800D9684_demo[4] = {
    D_800E7748_demo,
    D_800E7948_demo,
    D_800E7B48_demo,
    D_800E7D48_demo,
};
#endif
