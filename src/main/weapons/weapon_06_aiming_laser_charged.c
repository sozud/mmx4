// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..80096E10
#include "common.h"
#include "scratchpad.h"

// aiming_laser_update
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_800961B0);

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
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0x12;
    arg0->ext.weapon_6.direction = 8;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    set_animation(arg0, 1);
    arg0->state++;
    aiming_laser_reticle_place(arg0, arg1);
}

// aiming_laser_reticle_main
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_800963E8);

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", aiming_laser_reticle_place);
#else
void aiming_laser_reticle_place(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    u8* temp_a0;

    arg0->unk15 = arg1->unk15;
    temp_a0 = arg0->ext.raw;
    if (arg0->unk15 != 0) {
        arg0->ext.raw[1] = arg0->ext.raw[0];
    } else {
        arg0->ext.raw[1] = 0x20 - arg0->ext.raw[0];
    }
    set_velocity_from_angle(MOVING_OBJECT(arg0), (temp_a0[1] - 8) & 0x1F);
    arg0->x_pos.val = arg1->x_pos.val + arg0->x_vel.val * 0x60;
    arg0->y_pos.val = arg1->y_pos.val + arg0->y_vel.val * 0x60;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", aiming_laser_try_lock_on);
#else
s32 aiming_laser_try_lock_on(struct WeaponObj* arg0, struct PlayerObj* player, struct MainObj* target)
{
    s32 slot;
    s8 active;

    if (target == player->weapon_06_slots[0]) {
        return 0;
    }
    if (target == player->weapon_06_slots[1]) {
        return 0;
    }
    if (target == player->weapon_06_slots[2]) {
        return 0;
    }
    active = target->active;
    if (active == 0) {
        return 0;
    }
    if (active & 4) {
        return 0;
    }
    if (target->unk7A != 0) {
        return 0;
    }
    if (target->hurt_box == NULL) {
        return 0;
    }
    if (target->hp == 0) {
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
    if (slot != -1 && func_8002BB80(MAIN_OBJECT(arg0), target) != 0) {
        if (player_spawn_weapon(1, 6, slot, PLAYER_OBJECT(target)) != NULL) {
            player->weapon_06_slots[slot] = target;
            player->special_shot_count++;
            func_8001540C(0, 0x1C, arg0);
        }
        arg0->unk50 = NULL;
        update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
        return 1;
    }
    return 0;
}
#endif

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
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0x12;
    arg0->unk15 = 0;
    set_animation(arg0, 2);
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x18);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", aiming_laser_marker_wait_fire);
#else
void aiming_laser_marker_wait_fire(struct WeaponObj* self, struct PlayerObj* player,
    struct PlayerObj* owner)
{
    struct QuadObj* quad;

    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x18, 0x18);
    if ((player->shot_fired != 0) && (player->shot_type == 6)) {
        self->unk50 = &aiming_laser_marker_box;
        self->unk64 = 1;
        self->ext.weapon_6.lifetime = 0x3C;
        self->ext.weapon_6.timer = 6;
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
#endif

void aiming_laser_marker_fire(struct WeaponObj* arg0)
{
    u8* ext = arg0->ext.raw;
    u8 timer;

    animate_object(ANIMATED_OBJECT(arg0));
    if (ext[2] == 0) {
        arg0->unk50 = 0;
        arg0->on_screen = 0;
        arg0->state = 3;
        return;
    }
    timer = ext[3];
    if (timer == 0) {
        ext[3] = 6;
        arg0->unk64++;
    } else {
        ext[3] = timer - 1;
    }
    ext[2] -= 1;
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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", aiming_laser_charged_init);
#else
void aiming_laser_charged_init(struct WeaponObj* arg0)
{
    s8 i;
    struct QuadObj* quad;

    i = 0;
    arg0->ext.weapon_15.unk8D = 8;
    arg0->ext.weapon_15.unk8C = 8;
    arg0->ext.weapon_15.unk8E = 0xF0;
    arg0->ext.weapon_15.unk8F = 6;

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
    func_8001540C(0, 0x1D, arg0);
    arg0->unk5 = 0;
    arg0->state = (u8)arg0->state + 1;
}
#endif

// aiming_laser_charged_main
INCLUDE_ASM("main/nonmatchings/weapons/weapon_06_aiming_laser_charged", func_80096B54);

void aiming_laser_charged_aim(struct WeaponObj* self, struct PlayerObj* player)
{
    u8* angle = &self->ext.weapon_15.unk8C;

    self->unk15 = player->unk15;
    if (0 != player->unk15) {
        self->x_pos.i.hi = player->x_pos.u.hi - D_8011B230.components[player->animation_step.fields.frame_index * 2];
        angle[1] = angle[0];
    } else {
        self->x_pos.i.hi = player->x_pos.u.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2];
        angle[1] = 0x20 - angle[0];
    }
    self->y_pos.i.hi = player->y_pos.u.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2 + 1];
    set_velocity_from_angle(MOVING_OBJECT(self), (angle[1] - 8) & 0x1F);
    self->x_pos.val += self->x_vel.val * 104;
    self->y_pos.val += self->y_vel.val * 104;
}

void aiming_laser_charged_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    stop_sound(0, 0x1D);
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
