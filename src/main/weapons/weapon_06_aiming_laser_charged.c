// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..80096E10
#include "common.h"
#include "main/player_weapon.h"
#include "main/player_check.h"

extern struct Unk_unk68 aiming_laser_reticle_box[];
extern struct Unk_unk68 aiming_laser_charged_box[];
void func_800963E8(struct WeaponObj* arg0, struct PlayerObj* player);

#include "weapon_resources.h"
#include "scratchpad.h"
#include "main/objects.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/sprite_animations.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/player_check.h"
#include "main/player_weapon.h"
#endif

void aiming_laser_marker_init(struct WeaponObj*);

void aiming_laser_marker_fire(struct WeaponObj*);
void aiming_laser_marker_despawn(struct WeaponObj*, struct PlayerObj*);

// aiming_laser_charged_state_funcs
extern void (*aiming_laser_charged_state_funcs[])(struct WeaponObj*);

void aiming_laser_charged_despawn(struct WeaponObj*);
void aiming_laser_charged_despawn(struct WeaponObj*);

// aiming_laser_update

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800963E8(struct WeaponObj* arg0, struct PlayerObj* player);
void func_800961B0(struct WeaponObj* arg0);
void func_80096B54(struct WeaponObj* self);
extern struct Unk_unk68 aiming_laser_reticle_box[];
void aiming_laser_reticle_init(struct WeaponObj* arg0, struct PlayerObj* arg1);
void aiming_laser_reticle_place(struct WeaponObj* arg0, struct PlayerObj* arg1);
// src/main/weapons/weapon_06_aiming_laser_charged.c

extern struct Unk_unk68 aiming_laser_charged_box[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800961B0(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    struct MainObj* owner;
    s32 reset;

    if (arg0->unk2 == 3) {
        reset = engine_obj.unkF != 0;
        if (player->weapon != 6)
            reset = 1;
        if (player->hp == 0)
            reset = 1;
        if (reset)
            ZeroObjectState(OBJECT_HEADER(arg0));
        else if (arg0->state == 0)
            aiming_laser_reticle_init(arg0, player);
        else
            func_800963E8(arg0, player);
        return;
    }
    owner = (struct MainObj*)arg0->owner;
    reset = player->input_locked != 0;
    if (player->capsule_state != 0 || player->weapon != 6 || player->actions_reset != 0 || player->hp == 0 || owner->active == 0 || owner->hp == 0)
        reset = 1;
    if (reset)
        arg0->state = 3;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    switch (arg0->state) {
    case 0:
        aiming_laser_marker_init(arg0);
        break;
    case 1:
        aiming_laser_marker_wait_fire(arg0, player, (struct PlayerObj*)owner);
        break;
    case 2:
        aiming_laser_marker_fire(arg0);
        break;
    default:
        aiming_laser_marker_despawn(arg0, player);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_800961B0);
#endif

void aiming_laser_reticle_init(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;

    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    gfx_offset = player_gfx[0x1C / 4];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[0x3C / 4];
    arg0->animation_table = D_8011C0E4;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0x12;
    arg0->ext.weapon_6.direction = 8;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    set_animation(arg0, 1);
    arg0->state++;
    aiming_laser_reticle_place(arg0, arg1);
}

// aiming_laser_reticle_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800963E8(struct WeaponObj* arg0, struct PlayerObj* player)
{
    s32 hidden = player->weapon_energy[6] == 0;
    u32 i;

    if (!(player->armor_parts & 1) && player->weapon_energy[6] < player_weapon_energy.charge.initial_thresholds[0])
        hidden = 1;
    if (player->special_shot_count >= 3)
        hidden = 1;
    if (player->hurt_phase > 0)
        hidden = 1;
    if (player->attacking != 0 && (player->last_shot_type == 6 || player->last_shot_type == 0xF))
        hidden = 1;
    if (hidden) {
        arg0->on_screen = 0;
        return;
    }
    arg0->on_screen = 1;
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->ext.weapon_6.direction != 0 && (player->input.buttons.held & 4))
        arg0->ext.weapon_6.direction--;
    if (arg0->ext.weapon_6.direction != 0x10 && (player->input.buttons.held & 8))
        arg0->ext.weapon_6.direction++;
    aiming_laser_reticle_place(arg0, player);
    arg0->unk50 = aiming_laser_reticle_box;
    for (i = 0; i < COUNT(main_objects); i++) {
        if (aiming_laser_try_lock_on(arg0, player, &main_objects[i]))
            return;
    }
    arg0->unk50 = NULL;
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_800963E8);
#endif

void aiming_laser_reticle_place(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    struct Weapon6Ext* ext;

    arg0->unk15 = arg1->unk15;
    ext = &arg0->ext.weapon_6;
    if (arg0->unk15 != 0) {
        ext->adjusted_direction = arg0->ext.weapon_6.direction;
    } else {
        ext->adjusted_direction = 0x20 - arg0->ext.weapon_6.direction;
    }
    set_velocity_from_angle(MOVING_OBJECT(arg0), (ext->adjusted_direction - 8) & 0x1F);
    arg0->x_pos.val = arg1->x_pos.val + arg0->x_vel.val * 0x60;
    arg0->y_pos.val = arg1->y_pos.val + arg0->y_vel.val * 0x60;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
}

s32 aiming_laser_try_lock_on(struct WeaponObj* arg0, struct PlayerObj* player, struct MainObj* target)
{
    struct MainObj* lock_target;
    s32 slot;
    s8 active;

    lock_target = target;
    if (lock_target == player->weapon_06_slots[0]) {
        return 0;
    }
    if (lock_target == player->weapon_06_slots[1]) {
        return 0;
    }
    if (lock_target == player->weapon_06_slots[2]) {
        return 0;
    }
    active = lock_target->active;
    if (active == 0) {
        return 0;
    }
    if (active & 4) {
        return 0;
    }
    if (lock_target->unk7A != 0) {
        return 0;
    }
    if (lock_target->hurt_box == NULL) {
        return 0;
    }
    if (lock_target->hp == 0) {
        return 0;
    }
    slot = -1;
    if (player->weapon_06_slots[2] == NULL) {
        slot = 2;
    }
    if (player->weapon_06_slots[1] == NULL) {
        slot = 1;
    }
    if (player->weapon_06_slots[0] == NULL) {
        slot = 0;
    }
    if (slot != -1 && func_8002BB80(MAIN_OBJECT(arg0), lock_target) != 0) {
        if (player_spawn_weapon(1, 6, slot, PLAYER_OBJECT(lock_target)) != NULL) {
            player->weapon_06_slots[slot] = lock_target;
            player->special_shot_count++;
            func_8001540C(0, WEAPON_SOUND_LASER_LOCK, arg0);
        }
        arg0->unk50 = NULL;
        update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
        return 1;
    }
    return 0;
}

void aiming_laser_marker_init(struct WeaponObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;

    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk38 = (u8*)player_gfx + (player_gfx[0x1C / 4]);
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk3C = (u8*)sprite_frames + (sprite_frames[0x3C / 4]);
    arg0->animation_table = D_8011C0E4;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0x12;
    arg0->unk15 = 0;
    set_animation(arg0, 2);
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
}

void aiming_laser_marker_wait_fire(struct WeaponObj* self, struct PlayerObj* player,
    struct PlayerObj* owner)
{
    struct Weapon6Ext* weapon_6 = &self->ext.weapon_6;
    struct QuadObj* quad;

    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x18, 0x18);
    if ((player->shot_fired != 0) && (player->shot_type == 6)) {
        self->unk50 = &aiming_laser_marker_box;
        self->unk64 = 1;
        weapon_6->lifetime = 0x3C;
        weapon_6->timer = 6;
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 9;
            quad->unk2 = (u8)self->unk2;
            quad->unk5C = owner;
        }
        self->state = (u8)self->state + 1;
    }
}

void aiming_laser_marker_fire(struct WeaponObj* arg0)
{
    struct Weapon6Ext* ext = &arg0->ext.weapon_6;
    u8 timer;

    animate_object(ANIMATED_OBJECT(arg0));
    if (ext->lifetime == 0) {
        arg0->unk50 = 0;
        arg0->on_screen = 0;
        arg0->state = 3;
        return;
    }
    timer = ext->timer;
    if (timer == 0) {
        ext->timer = 6;
        arg0->unk64++;
    } else {
        ext->timer = timer - 1;
    }
    ext->lifetime -= 1;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
}

void aiming_laser_marker_despawn(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    arg1->weapon_06_slots[arg0->unk2] = NULL;
    arg0->unk50 = 0;
    arg1->special_shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

// WeaponObj, weapon_object_update_funcs[15]

void aiming_laser_charged_update(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = 0;
    if (g_Player.input_locked != 0) {
        var_a1 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 6) {
        var_a1 = 1;
    }
    if (g_Player.hp == 0) {
        var_a1 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    aiming_laser_charged_state_funcs[arg0->state](arg0);
}

void aiming_laser_charged_init(struct WeaponObj* arg0)
{
    s8 i;
    struct QuadObj* quad;
    struct Weapon6Ext* ext;

    i = 0;
    ext = &arg0->ext.weapon_6;
    ext->adjusted_direction = 8;
    arg0->ext.weapon_6.direction = 8;
    ext->lifetime = 0xF0;
    ext->timer = 6;

    do {
        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0xA;
            quad->unk2 = i;
            quad->unk5C = PLAYER_OBJECT(arg0);
        }
        i++;
    } while (i < 4);

    aiming_laser_charged_aim(arg0, &g_Player);
    func_8001540C(0, WEAPON_SOUND_LASER_CHARGE, arg0);
    arg0->unk5 = 0;
    arg0->state = (u8)arg0->state + 1;
}

// aiming_laser_charged_main
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_80096B54);
#else
void func_80096B54(struct WeaponObj* self)
{
    struct Weapon6Ext* ext = &self->ext.weapon_6;
    struct PlayerObj* player = &g_Player;

    if (ext->lifetime == 0) {
        self->state = 3;
        return;
    }
    ext->lifetime--;
    switch (self->unk5) {
    case 0:
        if (ext->lifetime == 0xD2) {
            self->unk50 = aiming_laser_charged_box;
            self->unk64 = 1;
            self->unk5++;
        }
        break;
    case 1:
        if (ext->lifetime == 0x1E) {
            self->unk50 = NULL;
            self->unk5++;
            break;
        }
        if (ext->direction != 0 && (player->input.buttons.held & PLAYER_INPUT_UP))
            ext->direction--;
        if (ext->direction != 0x10 && (player->input.buttons.held & PLAYER_INPUT_DOWN))
            ext->direction++;
        if (ext->timer == 0) {
            ext->timer = 6;
            self->unk64++;
        } else {
            ext->timer--;
        }
        break;
    case 2:
        break;
    }
    aiming_laser_charged_aim(self, player);
}
#endif

void aiming_laser_charged_aim(struct WeaponObj* self, struct PlayerObj* player)
{
    struct Weapon6Ext* ext = &self->ext.weapon_6;

    self->unk15 = player->unk15;
    if (0 != player->unk15) {
        self->x_pos.i.hi = player->x_pos.u.hi - D_8011B230.components[player->animation_step.fields.frame_index * 2];
        ext->adjusted_direction = ext->direction;
    } else {
        self->x_pos.i.hi = player->x_pos.u.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2];
        ext->adjusted_direction = 0x20 - ext->direction;
    }
    self->y_pos.i.hi = player->y_pos.u.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2 + 1];
    set_velocity_from_angle(MOVING_OBJECT(self), (ext->adjusted_direction - 8) & 0x1F);
    self->x_pos.val += self->x_vel.val * 104;
    self->y_pos.val += self->y_vel.val * 104;
}

void aiming_laser_charged_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
#ifdef MMX4_SATURN
    func_8001540C(6, 1, NULL);
#else
    stop_sound(0, 0x1D);
#endif
    g_Player.special_shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

struct Unk_unk68 aiming_laser_reticle_box[] = {
    { -20, -20, 0x28, 0x28 },
};

struct Unk_unk68 aiming_laser_marker_box[] = {
    { -8, -8, 0x10, 0x10 },
};

struct Unk_unk68 aiming_laser_charged_box[] = {
    { -24, -24, 0x30, 0x30 },
};

void (*aiming_laser_marker_state_funcs[])(struct WeaponObj*) = {
    aiming_laser_marker_init,
    (void (*)(struct WeaponObj*))aiming_laser_marker_wait_fire,
    (void (*)(struct WeaponObj*))aiming_laser_marker_fire,
    (void (*)(struct WeaponObj*))aiming_laser_marker_despawn,
};

void (*aiming_laser_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))aiming_laser_charged_init,
    (void (*)(struct WeaponObj*))func_80096B54,
    (void (*)(struct WeaponObj*))aiming_laser_charged_despawn,
    (void (*)(struct WeaponObj*))aiming_laser_charged_despawn,
};
