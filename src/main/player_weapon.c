// 80036E98..80038678
#include "common.h"
#include "main/objects.h"
#include "main/player.h"
#include "main/player_common.h"
#include "main/player_weapon.h"
#include "main/1CF60.h"
#include "main/object_motion.h"
#include "main/player_check.h"
#include "main/player_enter.h"
#include "main/55C4.h"
#include "main/player_special.h"

extern s8 player_shot_has_pose[];
extern s8 player_shot_is_special_weapon[];
extern s8 player_shot_is_charged_special[];

extern struct PlayerShotTiming player_shot_timings[];
extern s8 player_shot_limits[];
extern s8 player_shot_waits_for_specials[];
extern s8 player_shot_counts_as_shot[];
extern s8 player_shot_counts_as_special[];

// player_fire_funcs
extern void (*player_fire_funcs[])(struct PlayerObj*);

void func_80036F50(struct PlayerObj* self);
void func_80037484(struct PlayerObj* self, s32 airborne);
void func_80037C28(struct PlayerObj* self);
void player_enter_frost_tower_pose(struct PlayerObj* self);
void player_enter_soul_body(struct PlayerObj* self);
void player_enter_rising_fire(struct PlayerObj* self, s32 airborne);
void player_enter_rising_fire_charged(struct PlayerObj* self, s32 airborne);
void player_enter_double_cyclone_pose(struct PlayerObj* self);

#ifdef MMX4_SATURN
#define PLAYER_WEAPON_SELECT_SOUND 0xD
#else
#define PLAYER_WEAPON_SELECT_SOUND 0xC
#endif

s32 player_charge_released(struct PlayerObj* self);
void player_charge_shoot_button(struct PlayerObj* self);
void player_charge_special_button(struct PlayerObj* self);
s32 player_check_nova_strike(struct PlayerObj* self);
void player_check_shoot_button(struct PlayerObj* self);
void player_check_special_button(struct PlayerObj* self);
s32 player_has_weapon_energy(struct PlayerObj* self);
void player_reset_charge(struct PlayerObj* self);
s32 player_set_charge_flash(struct PlayerObj* self, s8 button);
void player_update_charged_shot_type(struct PlayerObj* self, s32 button);
void player_update_shooting(struct PlayerObj* self);
void player_use_weapon_energy(struct PlayerObj* self, s8 shot_type);

void player_update(void);

void player_update_normal(struct PlayerObj* self);

void player_beam_in(struct PlayerObj* self);

void player_beam_out(struct PlayerObj* self);

void player_idle(struct PlayerObj* self);

void player_walk_start(struct PlayerObj* self);

void player_walk(struct PlayerObj* self);

void player_settle(struct PlayerObj* self);

void player_jump(struct PlayerObj* self);

void player_fall(struct PlayerObj* self);

void player_land(struct PlayerObj* self);

void player_wall_cling(struct PlayerObj* self);

void player_wall_jump(struct PlayerObj* self);

void player_wall_jump_push(struct PlayerObj* self);

void player_wall_jump_rise(struct PlayerObj* self);

void player_wall_slide_down(struct PlayerObj* self);

void player_wall_slide_release(struct PlayerObj* self);

void player_wall_slide(struct PlayerObj* self);

void player_wall_slide_down(struct PlayerObj* self);

void player_wall_slide_release(struct PlayerObj* self);

void player_dash(struct PlayerObj* self);

void player_dash_start(struct PlayerObj* self);

void player_dash_move(struct PlayerObj* self);

void player_dash_end(struct PlayerObj* self);

void player_air_dash(struct PlayerObj* self);

void player_air_dash_start(struct PlayerObj* self);

void player_air_dash_move(struct PlayerObj* self);

void player_air_dash_end(struct PlayerObj* self);

void player_ladder_transition(struct PlayerObj* self);

void player_ladder_grab(struct PlayerObj* self);

void player_ladder_climb_off_top(struct PlayerObj* self);

void player_ladder_climb_on_top(struct PlayerObj* self);

void player_ladder_step_off_bottom(struct PlayerObj* self);

void player_ladder_let_go(struct PlayerObj* self);

void player_ladder_up(struct PlayerObj* self);

void player_ladder_down(struct PlayerObj* self);

void player_hurt(struct PlayerObj* self);

void player_hurt_slide(struct PlayerObj* self);

void player_hurt_knockback(struct PlayerObj* self);

void player_hurt_launch(struct PlayerObj* self);

void player_hurt_stun(struct PlayerObj* self);

void player_hurt_slide(struct PlayerObj* self);

void player_ride(struct PlayerObj* self);

void player_capsule(struct PlayerObj* self);

// player_capsule_enter

void player_capsule_fall(struct PlayerObj* self);

void player_script_wait(struct PlayerObj* self);

// player_script_walk

void player_script_vanish(struct PlayerObj* self);

void player_script_jump(struct PlayerObj* self);

void player_script_victory(struct PlayerObj* self);

void player_stage_clear(struct PlayerObj* self);

s32 player_check_dash_jump_walk(struct PlayerObj* self);

s32 player_check_dash_jump(struct PlayerObj* self);

s32 player_check_walk_start(struct PlayerObj* self);

s32 player_check_walk(struct PlayerObj* self);

void player_check_fall(struct PlayerObj* self);

s32 player_check_dash_input(struct PlayerObj* self);

void player_update_double_tap(struct PlayerObj* self);

s32 player_dash_should_end(struct PlayerObj* self);

void player_check_capsule(struct PlayerObj* self);

void player_check_ride(struct PlayerObj* self);

s32 player_check_air_move(struct PlayerObj* self);

s32 player_check_wall(struct PlayerObj* self);

s32 player_check_wall_jump(struct PlayerObj* self);

s32 player_is_pushing_wall(struct PlayerObj* self);

void player_check_damage(struct PlayerObj* self);

void player_reset_actions(struct PlayerObj* self);

// player_take_hit

u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

s32 player_check_ladder(struct PlayerObj* self);

s32 player_check_ladder_air(struct PlayerObj* self);

// player_check_ladder_end

s32 player_check_off_ladder(struct PlayerObj* self);

s32 player_check_script(struct PlayerObj* self);

void player_script_walk_to_mark(struct PlayerObj* self);

s32 player_leap_check_peak(struct PlayerObj* self);

void player_leap_check_wall(struct PlayerObj* self);

void player_noop(void);

void player_enter_idle(struct PlayerObj* self);

void player_enter_stand(struct PlayerObj* self);

void player_enter_walk_start(struct PlayerObj* self);

void player_enter_walk(struct PlayerObj* self);

void player_enter_jump(struct PlayerObj* self);

void player_enter_fall(struct PlayerObj* self);

void player_enter_land(struct PlayerObj* self);

void player_enter_land_or_fall(struct PlayerObj* self);

void player_enter_dash(struct PlayerObj* self);

void player_enter_dash_end(struct PlayerObj* self);

void player_enter_air_dash(struct PlayerObj* self);

void player_enter_air_dash_end(struct PlayerObj* self);

void player_enter_fall_shooting(struct PlayerObj* self);

void player_enter_wall_cling(struct PlayerObj* self);

// player_enter_wall_jump

void player_enter_wall_slide(struct PlayerObj* self);

// player_enter_wall_slide_release

void player_enter_ladder_grab(struct PlayerObj* self);

void player_enter_ladder_climb_off_top(struct PlayerObj* self);

void player_enter_ladder_climb_on_top(struct PlayerObj* self);

void player_enter_ladder_step_off_bottom(struct PlayerObj* self);

void player_enter_ladder_up(struct PlayerObj* self);

void player_enter_ladder_down(struct PlayerObj* self);

// player_start_script

void player_start_stage_clear(struct PlayerObj* self);

void player_enter_beam_out(struct PlayerObj* self);

s32 player_set_animation(struct PlayerObj* self, s32 animation);

void player_set_animation_frame(struct PlayerObj* self, s32 animation, s32 frame);

extern s16 player_afterimage_cluts[];

void player_spawn(void);

void player_init_clone(void);

void player_update_init(struct PlayerObj* self);

void player_entry_beam_in(struct PlayerObj* self);

void player_entry_placed(struct PlayerObj* self);

void player_entry_ride(struct PlayerObj* self);

void player_update_death(struct PlayerObj* self);

void player_death_start(struct PlayerObj* self);

void player_death_wait(struct PlayerObj* self);

// player_death_explode

void player_death_end(struct PlayerObj* self);

void player_spawn_death_orb(s8 direction);

void player_spawn_death_orbs(s8 pattern);

void player_update_inactive(struct PlayerObj* self);

void player_update_frame_hitbox(struct PlayerObj* self);

void player_set_collision_bounds(struct PlayerObj* self);

void player_read_input(void);

u16 player_map_buttons(s32 pad);

void player_clear_dash(struct PlayerObj* self);

void player_clear_attack(struct PlayerObj* self);

void player_clear_dash_and_attack(struct PlayerObj* self);

void player_clear_flash(struct PlayerObj* self);

void player_update_flash(struct PlayerObj* self);

void player_copy_palette(struct PlayerObj* self, s32 source, s32 dest);

void player_reset_palette(struct PlayerObj* self);

void player_set_palette(struct PlayerObj* self, s32 palette);

void player_play_voice(struct PlayerObj* self, u8 voice);

void player_check_low_hp_alarm(struct PlayerObj* self);

void player_damage(s8 damage);

void player_set_idle_animation(struct PlayerObj* self);

void player_air_steer(struct PlayerObj* self);

void player_spawn_dash_dust(struct PlayerObj* self);

void player_spawn_dash_spark(struct PlayerObj* self);

void player_spawn_dash_splash(struct PlayerObj* self);

extern f32 player_wall_kick_spark_offsets[];

void player_spawn_wall_kick_spark(struct PlayerObj* self);

void player_spawn_wall_slide_dust(struct PlayerObj* self);

void player_start_script_action(s8 action, s8 facing);

void player_end_script_action(void);

void player_check_splash_tile(struct PlayerObj* self);

void player_check_splash(struct PlayerObj* self);

// player_spawn_splash

struct WeaponObj* player_spawn_weapon(s8 active, s8 id, s8 type, struct PlayerObj* owner);

struct VisualObj* player_spawn_visual(s8 active, s8 id, s8 variant, void* owner);

#ifdef VERSION_DEMO
void func_8004390C_demo(struct PlayerObj* self); // player_fire_none
void func_80043914_demo(struct PlayerObj* self); // player_fire_weapon
void func_80043990_demo(struct PlayerObj* self); // player_fire_charged_buster
void func_80043A34_demo(struct PlayerObj* self);

union PlayerChargeData player_weapon_energy = {
    {
        { 0, 4, 3, 6, 3, 1 },
        { 1, 1, 1 },
        { 0, 12, 12, 12, 12, 6, 12, 12, 6, 0, 0, 0, 0, 0, 0 },
    },
};

// player_shot_has_pose
s8 D_800CC728_demo[24] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 };

// player_weapon_bits
u8 D_800CC740_demo[12] = { 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };

// player_shot_timings
struct PlayerShotTiming D_800CC74C_demo[22] = {
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x01, 0x01 },
    { 0x14, 0x0F },
    { 0x0C, 0x0C },
    { 0x14, 0x0A },
    { 0x46, 0x46 },
    { 0x01, 0x01 },
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x19, 0x14 },
    { 0x01, 0x01 },
    { 0x01, 0x01 },
    { 0, 0 },
    { 0x19, 0x14 },
    { 0xFA, 0xFA },
    { 0x01, 0x01 },
    { 0x19, 0x14 },
    { 0x23, 0x0F },
    { 0x19, 0x06 },
    { 0x23, 0x0F },
    { 0, 0 },
};

// player_fire_funcs
void (*D_800CC778_demo[])(struct PlayerObj*) = {
    func_80043914_demo,
    func_80043914_demo,
    func_8004390C_demo,
    func_80043914_demo,
    func_8004390C_demo,
    func_80043914_demo,
    func_8004390C_demo,
    func_8004390C_demo,
    func_80043A34_demo,
    func_80043990_demo,
    player_fire_lightning_web_charged,
    func_8004390C_demo,
    func_8004390C_demo,
    player_fire_none,
    func_80043914_demo,
    func_80043914_demo,
    func_8004390C_demo,
    func_80043A34_demo,
    func_80043990_demo,
    func_80043990_demo,
    func_80043990_demo,
};

// player_shot_counts_as_shot
s8 D_800CC7CC_demo[24] = { 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 };

// player_shot_counts_as_special
s8 D_800CC7E4_demo[24] = { 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 };

s8 D_800CC7FC_demo[24] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
#else
union PlayerChargeData player_weapon_energy = {
#ifdef MMX4_SHC
    0,
    4,
    3,
    6,
    3,
    1,
    1,
    1,
    1,
    0,
    12,
    12,
    12,
    12,
    6,
    12,
    12,
    6,
    0,
    0,
    0,
    0,
    0,
    0,
#else
    {
        { 0, 4, 3, 6, 3, 1 },
        { 1, 1, 1 },
        { 0, 12, 12, 12, 12, 6, 12, 12, 6, 0, 0, 0, 0, 0, 0 },
    },
#endif
};

s8 player_shot_has_pose[24] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1 };

s8 player_shot_is_special_weapon[24] = { 0, 1, 1, 1, 1, 1, 1, 1, 1 };

s8 player_shot_is_charged_special[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };

u8 player_weapon_bits[12] = { 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };

struct PlayerShotTiming player_shot_timings[22] = {
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x01, 0x01 },
    { 0x14, 0x0F },
    { 0x0A, 0x0A },
    { 0x14, 0x0A },
    { 0x46, 0x46 },
    { 0x01, 0x01 },
    { 0x14, 0x06 },
    { 0x19, 0x0F },
    { 0x19, 0x14 },
    { 0x01, 0x01 },
    { 0x01, 0x01 },
    { 0x01, 0x01 },
    { 0x19, 0x14 },
    { 0xFA, 0xFA },
    { 0x01, 0x01 },
    { 0x23, 0x14 },
    { 0x23, 0x0F },
    { 0x19, 0x06 },
    { 0x23, 0x0F },
    { 0, 0 },
};

void (*player_fire_funcs[])(struct PlayerObj*) = {
    player_fire_weapon,
    player_fire_weapon,
    player_fire_none,
    player_fire_weapon,
    player_fire_none,
    player_fire_weapon,
    player_fire_none,
    player_fire_none,
    func_80037C28,
    player_fire_charged_buster,
    player_fire_lightning_web_charged,
    player_fire_none,
    player_fire_none,
    player_fire_none,
    player_fire_weapon,
    player_fire_weapon,
    player_fire_none,
    func_80037C28,
    player_fire_charged_buster,
    player_fire_weapon,
    player_fire_charged_buster,
};

s8 player_shot_limits[24] = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 4, 4, 4, 4, 4, 1, 4, 4, 3, 4, 4 };

s8 player_shot_waits_for_specials[24] = { 0, 1, 1, 1, 1, 0, 0, 1 };

s8 player_shot_counts_as_shot[24] = { 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 };

s8 player_shot_counts_as_special[24] = { 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 };
#endif

#ifndef VERSION_DEMO
void player_reset_weapon(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        self->weapon = 0;
        self->stock_charge = 0;
        player_reset_charge(self);
        player_update_shot_types(self);
        player_equip_weapon(self);
    }
}
#endif

#ifndef VERSION_DEMO
void player_update_weapon(struct PlayerObj* self)
{
    s8 previous_weapon;

    if (self->unk2 == 0) {
        previous_weapon = self->weapon;
        func_80036F50(self);
        player_update_shot_types(self);
        if (previous_weapon != self->weapon) {
            player_equip_weapon(self);
        }
    }
}
#endif

// player_select_weapon

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80036F50(struct PlayerObj* player);
void func_80037484(struct PlayerObj* arg0, s32 arg1);
void func_80037C28(struct PlayerObj* arg0);
void player_enter_frost_tower_pose(struct PlayerObj* arg0);
void player_enter_soul_body(struct PlayerObj* arg0);
void player_enter_rising_fire(struct PlayerObj* arg0, s32 arg1);
void player_enter_rising_fire_charged(struct PlayerObj* arg0, s32 arg1);
void player_enter_double_cyclone_pose(struct PlayerObj* arg0);
#endif

#ifndef VERSION_DEMO
void func_80036F50(struct PlayerObj* player)
{
    u16 input;
    u16 pressed;
    s8 weapon;

    if (player->input_locked != 0 || player->is_clone != 0 || player->special_shot_count != 0 || player->ride_state != 0 || player->nova_strike_active != 0 || engine_obj.gameplay_locked != 0)
        return;
    input = player->pressed_input;
    pressed = input & 0x600;
    if (((player->input.buttons.held & 0x600) == 0x600) || (pressed == 0x600)) {
        if (player->weapon != 0) {
            player->weapon = 0;
            player_reset_charge(player);
            func_8001540C(0, PLAYER_WEAPON_SELECT_SOUND, 0);
        }
    } else if (pressed != 0) {
        weapon = player->weapon;
        if (input & 0x200) {
            while (1) {
                if (++weapon == 9) {
                    weapon = 0;
                    break;
                }
                if ((s8)player_weapon_bits[weapon] & (u8)player->boss_flags)
                    break;
            }
        } else {
            while (1) {
                weapon--;
                if (weapon < 0)
                    weapon = 8;
                if (weapon == 0)
                    break;
                if ((s8)player_weapon_bits[weapon] & (u8)player->boss_flags)
                    break;
            }
        }
        if (player->weapon != weapon) {
            player->weapon = weapon;
            player_reset_charge(player);
            func_8001540C(0, PLAYER_WEAPON_SELECT_SOUND, 0);
            player->stock_charge = 0;
        }
    }
}
#endif
#ifdef VERSION_DEMO
void player_clear_weapon(struct PlayerObj* self)
{
    self->weapon = 0;
    player_reset_palette(self);
}
#endif

#ifdef VERSION_DEMO
void func_8004314C_demo(struct PlayerObj* self);

void player_update_shot_types(struct PlayerObj* self)
{
    if (self->unk2 != 0) {
        return;
    }
    func_8004314C_demo(self);
    if (self->is_clone == 0) {
        self->shot_types[0] = self->weapon;
    } else {
        self->shot_types[0] = 0;
    }
    self->shot_types[1] = 0;
    if (self->weapon != 0) {
        if (self->charge_state[0] == PLAYER_CHARGE_FULL) {
            self->shot_types[0] += 9;
        }
    } else {
        player_update_charged_shot_type(self, 0);
    }
    player_update_charged_shot_type(self, 1);
}
#else
void player_update_shot_types(struct PlayerObj* self)
{
    if (self->is_clone != 0) {
        self->shot_types[0] = 0;
        self->shot_types[1] = 0;
        return;
    }
    self->shot_types[0] = self->weapon;
    if (self->weapon != 0) {
        if (self->charge_state[0] == PLAYER_CHARGE_FULL) {
            self->shot_types[0] += 9;
        }
    } else {
        player_update_charged_shot_type(self, 0);
    }
    self->shot_types[1] = 0;
    player_update_charged_shot_type(self, 1);
}
#endif

#ifdef VERSION_DEMO
extern u8 D_800CC740_demo[];

void func_8004314C_demo(struct PlayerObj* player)
{
    u16 input;
    u16 pressed;
    s8 weapon;
    struct VisualObj* visual;
    struct WeaponObj* companion;

    if (player->input_locked != 0 || player->is_clone != 0)
        return;
    if (player->unk5 == PLAYER_BEAM_IN)
        return;
    if (player->unk5 == PLAYER_BEAM_OUT)
        return;
    if (player->special_shot_count != 0 || player->ride_state < 0)
        return;
    input = player->pressed_input;
    pressed = input & 0x300;
    if (((player->input.buttons.held & 0x300) == 0x300) || (pressed == 0x300)) {
        if (player->weapon != 0) {
            func_8001540C(0, PLAYER_WEAPON_SELECT_SOUND, 0);
            player->weapon = 0;
            player_reset_palette(player);
        }
    } else if (pressed != 0) {
        weapon = player->weapon;
        if (input & 0x100) {
            while (1) {
                if (++weapon == 9) {
                    weapon = 0;
                    break;
                }
                if ((s8)D_800CC740_demo[weapon] & (u8)player->boss_flags)
                    break;
            }
        } else {
            while (1) {
                weapon--;
                if (weapon < 0)
                    weapon = 8;
                if (weapon == 0)
                    break;
                if ((s8)D_800CC740_demo[weapon] & (u8)player->boss_flags)
                    break;
            }
        }
        if (player->weapon != weapon) {
            func_8001540C(0, PLAYER_WEAPON_SELECT_SOUND, 0);
            player->weapon = weapon;
            player_reset_palette(player);
            if (player->weapon != 0 && !(player->armor_parts & 4)) {
                player_reset_weapon(player);
            }
            switch (player->weapon) {
            case 5:
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 1;
                    visual->id = 0x1B;
                    visual->unk2 = 0;
                }
                break;
            case 6:
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 1;
                    visual->id = 0x12;
                    visual->unk2 = 0;
                }
                companion = find_free_weapon_obj();
                if (companion != NULL) {
                    companion->active = 1;
                    companion->id = 6;
                    companion->unk2 = 3;
                }
                player->weapon_06_slots[0] = NULL;
                player->weapon_06_slots[1] = NULL;
                player->weapon_06_slots[2] = NULL;
                break;
            case 8:
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 1;
                    visual->id = 0x1B;
                    visual->unk2 = 1;
                }
                break;
            }
        }
    }
}
#endif

void player_update_charged_shot_type(struct PlayerObj* self, s32 button)
{
    if (self->stock_charge != 0) {
        self->shot_types[button] = 0x13;
        return;
    }

    if (self->charge_state[button] != PLAYER_CHARGE_NONE) {
        if (self->charge_state[button] == PLAYER_CHARGE_PARTIAL) {
            self->shot_types[button] = 9;
        } else if (self->arm_type == 0) {
            self->shot_types[button] = 0x12;
        } else {
            self->shot_types[button] = 0x14;
        }
    }
}

#ifdef VERSION_DEMO
extern struct PlayerShotTiming D_800CC74C_demo[];
extern void (*D_800CC778_demo[])(struct PlayerObj*);
extern s8 D_800CC7CC_demo[];
extern s8 D_800CC7E4_demo[];
extern s8 D_800CC7FC_demo[];

void func_8004345C_demo(struct PlayerObj* self)
{
    s8 shot_type;
    s32 limit;

    if (self->unk2 != 0) {
        return;
    }
    if (self->input_locked != 0) {
        return;
    }
    self->shot_type = -1;
    player_check_shoot_button(self);
    player_check_special_button(self);
    if (self->shot_type == -1) {
        return;
    }
    if (self->shot_cooldown != 0) {
        return;
    }
    switch (self->shot_type) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
        if (self->special_shot_count != 0) {
            return;
        }
        limit = 3;
        break;
    case 6:
        if (self->special_shot_count == 0) {
            return;
        }
        limit = 3;
        break;
    case 10:
        if (self->special_shot_count != 0) {
            if (self->last_shot_type == 10) {
                return;
            }
        }
        limit = 4;
        break;
    case 11:
        if (self->special_shot_count != 0) {
            if (self->last_shot_type == 11) {
                return;
            }
        }
        limit = 4;
        break;
    case 15:
        limit = 1;
        break;
    case 8:
    case 12:
    case 14:
    case 16:
    case 17:
        limit = 4;
        break;
    default:
        limit = 3;
        break;
    }
    if (self->shot_count >= limit) {
        return;
    }
    self->attacking = 1;
    self->shot_fired = 1;
    self->attack_ended = 0;
    shot_type = self->last_shot_type = self->shot_type;
    self->attack_pose_timer = D_800CC74C_demo[shot_type].pose_time;
    self->shot_cooldown = D_800CC74C_demo[shot_type].cooldown;
    D_800CC778_demo[shot_type](self);
    if (D_800CC7CC_demo[shot_type] != 0) {
        self->shot_count++;
    }
    if (D_800CC7E4_demo[shot_type] != 0) {
        self->special_shot_count++;
    }
    self->shot_cycle++;
    if (self->shot_cycle == 3) {
        self->shot_cycle = 0;
    }
    if (self->shot_type == 0x13) {
        self->stock_charge--;
    }
    if (D_800CC7FC_demo[shot_type] != 0) {
        self->weapon_energy[self->weapon] -= player_weapon_energy.shot_costs[shot_type];
    }
    if (self->is_clone == 0 && self->weapon == 0 && self->hurt_phase == 0) {
        self->shot_palette_timer = shot_type < 10 ? 6 : 7;
        if (shot_type == 9) {
            self->shot_palette_timer = 5;
        }
    }
}
#endif

#ifndef VERSION_DEMO
void player_equip_weapon(struct PlayerObj* self)
{
    player_reset_palette(self);
    if (self->weapon == 5) {
        player_spawn_visual(1, 0x1B, 0, 0);
    }
    if (self->weapon == 6) {
        player_spawn_visual(1, 0x12, 0, 0);
        player_spawn_weapon(1, 6, 3, 0);
        self->weapon_06_slots[0] = 0;
        self->weapon_06_slots[1] = 0;
        self->weapon_06_slots[2] = 0;
    }
    if (self->weapon == 8) {
        player_spawn_visual(1, 0x1B, 1, 0);
    }
}
#endif

#ifndef VERSION_DEMO
s32 player_check_shoot(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        return 0;
    }

    if (self->unk2 != 0) {
        return 0;
    }

    if (player_check_nova_strike(self) != 0) {
        return 1;
    }

    player_update_shooting(self);

    if (self->shot_fired == 0) {
        return 0;
    }

    if (player_shot_has_pose[self->shot_type] == 0) {
        return 0;
    }

    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = 0;
    func_80037484(self, 0);

    return 1;
}
#endif

#ifndef VERSION_DEMO
s32 player_check_shoot_air(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        return 0;
    }
    if (self->unk2 != 0) {
        return 0;
    }
    if (player_check_nova_strike(self) != 0) {
        return 1;
    }
    player_update_shooting(self);
    if (self->shot_fired == 0) {
        return 0;
    }
    if (player_shot_has_pose[self->shot_type] == 0) {
        return 0;
    }
    self->dash_momentum = 0;
    self->afterimage = 0;
    func_80037484(self, 1);
    return 1;
}
#endif

#ifndef VERSION_DEMO
s32 player_check_shoot_ladder(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        return 0;
    }
    if (self->unk2 != 0) {
        return 0;
    }
    if (player_check_nova_strike(self) != 0) {
        return 1;
    }
    player_update_shooting(self);
    if (self->shot_fired == 0) {
        return 0;
    }
    if (player_shot_has_pose[self->shot_type] == 0) {
        player_enter_ladder_shoot(self);
    } else {
        self->afterimage = 0;
        func_80037484(self, 1);
    }
    return 1;
}
#endif

// player_enter_weapon_pose
#ifndef VERSION_DEMO
void func_80037484(struct PlayerObj* arg0, s32 arg1)
{
    switch (arg0->shot_type) {
    case 2:
    case 11:
        player_enter_frost_tower_pose(arg0);
        break;
    case 12:
        player_enter_soul_body(arg0);
        break;
    case 4:
        player_enter_rising_fire(arg0, arg1);
        break;
    case 13:
        player_enter_rising_fire_charged(arg0, arg1);
        break;
    case 7:
    case 16:
        player_enter_double_cyclone_pose(arg0);
        break;
    }
}
#endif
#ifndef VERSION_DEMO
s32 player_check_hover(struct PlayerObj* self)
{
    if (!(self->armor_parts & 8)) {
        return 0;
    }
    if (!(self->pressed_input & PLAYER_INPUT_JUMP)) {
        return 0;
    }
    player_set_animation_shooting(self, 0x15);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_momentum = 0;
    self->air_action = 4;
    self->afterimage = 0;
    self->hover_timer = 0xB4;
    self->hover_bob = 0;
    self->unk5 = PLAYER_HOVER;
    self->unk6 = 0;
    return 1;
}
#endif

#ifndef VERSION_DEMO
s32 player_check_nova_strike(struct PlayerObj* self)
{
    u8 wall_side;

    if (self->shot_cooldown) {
        return 0;
    }
    if (!(self->armor_parts & 2)) {
        return 0;
    }
    if (self->weapon_energy[0] != 0x30) {
        return 0;
    }
    if (self->air_action) {
        return 0;
    }
    wall_side = self->unk15 ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT;
    if (self->unk88.bytes.collision_flags & wall_side) {
        return 0;
    }
    if (!(self->pressed_input & PLAYER_INPUT_GIGA)) {
        return 0;
    }

    player_set_animation(self, 0x6A);
    player_clear_attack(self);
    player_reset_weapon(self);
    self->dash_momentum = 0;
    self->air_action = 5;
    self->afterimage = 0;
    self->invincibility_timer = 0;
    self->hurt_phase = 0;
    self->air_state = 1;
    if (engine_obj.unk37 == 0) {
        self->weapon_energy[0] = 0;
    }
    self->spike_immune = 1;
    self->nova_strike_active = 1;
    self->nova_strike_timer = 0x18;
    engine_obj.gameplay_locked = 1;

    if (self->unk15) {
        self->x_vel.val = FIXED(2.5);
    } else {
        self->x_vel.val = FIXED(-2.5);
    }
    self->unk28 = 0;
    self->y_vel.val = FIXED(3.5);
    self->unk2C = 0x4200;
    self->unk5 = PLAYER_NOVA_STRIKE;
    self->unk6 = 0;

    return 1;
}
#endif

#ifndef VERSION_DEMO
void player_update_shooting(struct PlayerObj* self)
{
    s8 shot_type;

    if (self->shot_cooldown == 0) {
        self->shot_type = -1;
        player_check_shoot_button(self);
        player_check_special_button(self);
        shot_type = self->shot_type;
        if (self->shot_type != -1 && self->shot_count < player_shot_limits[self->shot_type] && (player_shot_waits_for_specials[self->shot_type] == 0 || self->special_shot_count == 0)) {
            if ((player_shot_is_charged_special[self->shot_type] == 0 || self->special_shot_count == 0 || self->last_shot_type != self->shot_type)) {
                if ((shot_type != 6 || self->special_shot_count != 0)) {
                    player_fire_funcs[shot_type](self);
                    self->last_shot_type = shot_type;
                    self->attacking = 1;
                    self->shot_fired = 1;
                    self->attack_ended = 0;
                    self->attack_pose_timer = player_shot_timings[shot_type].pose_time;
                    self->shot_cooldown = player_shot_timings[shot_type].cooldown;
                    if (player_shot_counts_as_shot[shot_type] != 0) {
                        self->shot_count++;
                    }
                    if (player_shot_counts_as_special[shot_type] != 0) {
                        self->special_shot_count++;
                    }
                    self->shot_cycle++;
                    if (self->shot_cycle == 3) {
                        self->shot_cycle = 0;
                    }
                    if (shot_type == 0x13) {
                        self->stock_charge--;
                    }
                    player_use_weapon_energy(self, shot_type);
                    if (self->is_clone == 0 && self->weapon == 0 && self->hurt_phase == 0) {
                        if (shot_type == 0) {
                            self->shot_palette_timer = 6;
                        }
                        if (shot_type == 9) {
                            self->shot_palette_timer = 5;
                        }
                        if (shot_type == 0x12) {
                            self->shot_palette_timer = 7;
                        }
                    }
                }
            }
        }
    }
}
#endif

#ifdef VERSION_DEMO
void func_800437E8_demo(struct PlayerObj* self);

void player_check_shoot_button(struct PlayerObj* self)
{
    s8 temp;

    if (self->pressed_input & PLAYER_INPUT_SHOOT) {
        if (self->weapon != 0) {
            func_800437E8_demo(self);
        } else {
            self->shot_type = self->shot_types[1];
        }
    } else if ((self->input.history & ((PLAYER_INPUT_SHOOT << 16) | PLAYER_INPUT_SHOOT)) == (PLAYER_INPUT_SHOOT << 16)) {
        temp = self->shot_types[0];
        if (temp >= 9 && temp != 0x13) {
            if (self->weapon != 0) {
                func_800437E8_demo(self);
            } else {
                self->shot_type = temp;
            }
        }
    }
}
#else
void player_check_shoot_button(struct PlayerObj* self)
{
    if (self->pressed_input & PLAYER_INPUT_SHOOT) {
        if (self->weapon != 0) {
            self->stock_charge = 0;
            if (player_has_weapon_energy(self) == 0) {
                return;
            }
        }
        self->shot_type = self->shot_types[0];
    } else if (!(self->input.buttons.held & PLAYER_INPUT_SHOOT) && (self->input.buttons.previous & PLAYER_INPUT_SHOOT)) {
        s8 temp = self->shot_types[0];
        if ((temp != 0) && (player_shot_is_special_weapon[temp] == 0) && (temp != 0x13)) {
            if (self->weapon != 0) {
                self->stock_charge = 0;
                if (player_has_weapon_energy(self) == 0) {
                    return;
                }
            }
            self->shot_type = self->shot_types[0];
        }
    }
}
#endif

#ifdef VERSION_DEMO
void func_800437E8_demo(struct PlayerObj* self)
{
    if (self->weapon_energy[self->weapon] >= player_weapon_energy.shot_costs[self->shot_types[0]]) {
        self->shot_type = self->shot_types[0];
    }
}
#endif

void player_check_special_button(struct PlayerObj* self)
{
    if (self->shot_type == -1) {
        if (self->pressed_input & PLAYER_INPUT_SPECIAL) {
#ifdef VERSION_DEMO
            if (self->stock_charge != 0) {
                self->shot_type = 0x13;
            } else if (self->charge_state[0] > self->charge_state[1]) {
                if (self->charge_state[0] == PLAYER_CHARGE_NONE) {
                    self->shot_type = 0;
                }
                if (self->charge_state[0] == PLAYER_CHARGE_PARTIAL) {
                    self->shot_type = 9;
                }
                if (self->charge_state[0] == PLAYER_CHARGE_FULL) {
                    self->shot_type = 0x12;
                }
            } else {
                self->shot_type = self->shot_types[1];
            }
#else
            self->shot_type = self->shot_types[1];
#endif
            return;
        }
#ifdef VERSION_DEMO
        if ((self->input.history & ((PLAYER_INPUT_SPECIAL << 16) | PLAYER_INPUT_SPECIAL))
            == (PLAYER_INPUT_SPECIAL << 16)) {
#else
        if (!(self->input.buttons.held & PLAYER_INPUT_SPECIAL) && (self->input.buttons.previous & PLAYER_INPUT_SPECIAL)) {
#endif
            if ((self->shot_types[1] != 0) && (self->shot_types[1] != 0x13)) {
                self->shot_type = self->shot_types[1];
            }
        }
    }
}

#ifndef VERSION_DEMO
s32 player_has_weapon_energy(struct PlayerObj* self)
{
    s8 charge_level;
    s8 charge_type;

    charge_level = self->weapon_energy[self->weapon];
    if (charge_level == 0) {
        return 0;
    }

    charge_type = self->shot_types[0];
    if (player_shot_is_special_weapon[charge_type] != 0 && (self->armor_parts & 1) != 0) {
        return 1;
    }

    return charge_level >= player_weapon_energy.shot_costs[charge_type];
}
#endif

#ifndef VERSION_DEMO
void player_use_weapon_energy(struct PlayerObj* self, s8 shot_type)
{
    s8 animation_cost;

    animation_cost = player_weapon_energy.shot_costs[shot_type];
    if ((animation_cost != 0) && ((player_shot_is_special_weapon[shot_type] == 0) || !(self->armor_parts & 1))) {
        self->weapon_energy[self->weapon] -= animation_cost;
    }
}
#endif

void player_fire_none(struct PlayerObj* self)
{
}

#ifdef VERSION_DEMO
void func_8004390C_demo(struct PlayerObj* self)
{
}
#endif

#ifdef VERSION_DEMO
void func_80043914_demo(struct PlayerObj* self)
{
    struct WeaponObj* weapon = find_free_weapon_obj();

    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = self->shot_type;
        weapon->unk2 = 0;
        weapon->bg_offset = self->bg_offset;
        if (self->shot_type == 0) {
            weapon->owner = self;
        }
    }
    if (self->shot_type == 0xF) {
        player_play_voice(self, 5);
    }
}
#endif

#ifdef VERSION_DEMO
void func_80043990_demo(struct PlayerObj* self)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual != NULL) {
        visual->active = 0x21;
        visual->id = 2;
        visual->unk2 = self->shot_type;
        visual->bg_offset = self->bg_offset;
    }
    if (self->shot_type == 9) {
        player_play_voice(self, 4);
    }
    if (self->shot_type == 0x12) {
        player_play_voice(self, (get_random() & 1) ? 8 : 9);
    }
}
#endif

#ifdef VERSION_DEMO
void func_80043A34_demo(struct PlayerObj* self)
{
    struct WeaponObj* weapon;
    s8 count;
    s8 i;

    count = 8;
    if (self->shot_type == 8) {
        count = 2;
    }
    for (i = 0; i < count; i++) {
        weapon = find_free_weapon_obj();
        if (weapon != NULL) {
            weapon->active = 1;
            weapon->id = self->shot_type;
            weapon->unk2 = i;
            weapon->bg_offset = self->bg_offset;
        }
    }
    self->shot_count += count;
    self->special_shot_count += count;
}
#endif

#ifndef VERSION_DEMO
void player_fire_weapon(struct PlayerObj* self)
{
    player_spawn_weapon(1, self->shot_type, 0, self);
}
#endif

#ifndef VERSION_DEMO
void player_fire_charged_buster(struct PlayerObj* self)
{
    player_spawn_visual(0x21, 2, self->shot_type, 0);
    if ((self->shot_type == 0x12) && (get_random() & 1)) {
        player_play_voice(self, 8);
    }
}
#endif

// player_fire_twin_slasher
#ifndef VERSION_DEMO
void func_80037C28(struct PlayerObj* arg0)
{
    s8 count;
    s8 i;

    if (arg0->shot_type == 8) {
        count = 2;
        func_8001540C(1, 9, arg0);
    } else {
        count = 8;
        func_8001540C(1, 0xA, arg0);
        player_play_voice(arg0, 9);
    }
    for (i = 0; i < count; i++)
        player_spawn_weapon(1, arg0->shot_type, i, NULL);
    arg0->shot_count += count;
    arg0->special_shot_count += count;
}
#endif
void player_fire_lightning_web_charged(struct PlayerObj* self)
{
    struct WeaponObj* weapon;
    struct WeaponObj* first_weapon;
    s8 i;

    for (i = 0; i < 9; i++) {
        weapon = find_free_weapon_obj();
        if (weapon != 0) {
            weapon->active = 1;
            weapon->id = self->shot_type;
            weapon->unk2 = i;
            weapon->bg_offset = self->bg_offset;
            if (i == 0) {
                first_weapon = weapon;
            } else {
                weapon->owner = (struct PlayerObj*)first_weapon;
            }
        }
    }
}

#ifndef VERSION_DEMO
void player_enter_frost_tower_pose(struct PlayerObj* self)
{
    player_set_animation(self, 0x5F);
    player_play_voice(self, 5);
    self->air_state = 1;
    self->unk5 = PLAYER_WEAPON_POSE;
    self->unk6 = 0;
}
#endif

#ifndef VERSION_DEMO
void player_enter_soul_body(struct PlayerObj* self)
{
    player_set_animation(self, 0x60);
    self->controlling_clone = 1;
    self->spike_immune = 1;
    self->invincibility_timer = 0;
    self->hurt_phase = 0;
    self->air_state = 1;
    self->unk5 = PLAYER_SOUL_BODY;
    self->unk6 = 0;
}
#endif

#ifndef VERSION_DEMO
void player_enter_rising_fire(struct PlayerObj* self, s32 airborne)
{
    if (airborne == 0) {
        player_set_animation(self, 0x63);
    } else {
        player_set_animation(self, 0x64);
    }
    player_play_voice(self, 7);
    self->air_state = 1;
    self->unk5 = PLAYER_RISING_FIRE;
    self->unk6 = 0;
}
#endif

#ifndef VERSION_DEMO
void player_enter_rising_fire_charged(struct PlayerObj* self, s32 airborne)
{
    struct WeaponObj* weapon;

    if (airborne == 0) {
        player_set_animation(self, 0x65);
        weapon = player_spawn_weapon(1, 0xD, 0, NULL);
        if (weapon != NULL) {
            player_spawn_visual(1, 0x1A, 2, weapon);
        }
    } else {
        player_set_animation(self, 0x66);
        weapon = player_spawn_weapon(1, 0xD, 1, NULL);
        if (weapon != NULL) {
            player_spawn_visual(1, 0x1A, 3, weapon);
        }
    }

    player_play_voice(self, 7);
    self->shot_count++;
    self->special_shot_count++;
    self->air_state = 1;
    self->spike_immune = 1;
    self->unk5 = PLAYER_RISING_FIRE_CHARGED;
    self->unk6 = 0;
}
#endif

#ifndef VERSION_DEMO
void player_enter_double_cyclone_pose(struct PlayerObj* self)
{
    if (self->shot_type == 7) {
        player_set_animation(self, 0x68);
        player_play_voice(self, 4);
    } else {
        player_set_animation(self, 0x69);
        player_play_voice(self, 8);
    }
    self->air_state = 1;
    self->unk5 = PLAYER_WEAPON_POSE;
    self->unk6 = 0;
}
#endif

#ifndef VERSION_DEMO
void player_update_charge(struct PlayerObj* self)
{
    s8 action; // probably fake

    if ((self->unk2 == 0) && (self->is_clone == 0) && (self->nova_strike_active == 0) && (action = self->unk5, (self->unk5 != PLAYER_BEAM_IN)) && (self->unk5 != PLAYER_BEAM_OUT) && (self->unk5 != PLAYER_STAGE_CLEAR) && (action != PLAYER_SCRIPT_VICTORY) && (self->ride_state == 0)) {
        if (player_charge_released(self) != 0) {
            player_reset_charge(self);
            if (self->shot_palette_timer != 0) {
                player_set_palette(self, 0x32);
                return;
            }
            player_reset_palette(self);
            return;
        }
        player_charge_shoot_button(self);
        player_charge_special_button(self);
        if (player_set_charge_flash(self, 0) == 0) {
            player_set_charge_flash(self, 1);
        }
    }
}
#endif

#ifndef VERSION_DEMO
s32 player_set_charge_flash(struct PlayerObj* self, s8 button)
{
    s8 shot_type;

    if (self->charge_state[button] == PLAYER_CHARGE_NONE) {
        return 0;
    }
    if (self->charge_state[button] == PLAYER_CHARGE_PARTIAL) {
        self->flash_palette = 0x26;
        return 1;
    }

    shot_type = self->shot_types[button];
    if (shot_type == 0x13) {
        self->flash_palette = 0x2C;
        return 1;
    }
    if (shot_type == 0x14) {
        self->flash_palette = 0x2F;
        return 1;
    }
    self->flash_palette = 0x29;
    return 1;
}
#endif

#ifndef VERSION_DEMO
s32 player_charge_released(struct PlayerObj* self)
{
    if (self->pressed_input & PLAYER_INPUT_SHOOT) {
        return 1;
    }
    if (self->pressed_input & PLAYER_INPUT_SPECIAL) {
        return 1;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_SHOOT) && (self->input.buttons.previous & PLAYER_INPUT_SHOOT)) {
        return 1;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_SPECIAL) && (self->input.buttons.previous & PLAYER_INPUT_SPECIAL)) {
        return 1;
    }
    if (self->charge_timer && !(self->input.buttons.held & PLAYER_INPUT_SHOOT)) {
        return 1;
    }
    if (self->special_charge_timer && !(self->input.buttons.held & PLAYER_INPUT_SPECIAL)) {
        return 1;
    }
    return 0;
}
#endif

#ifndef VERSION_DEMO
void player_charge_shoot_button(struct PlayerObj* self)
{
    u8 full_charge_time;
    u8* ptr = (u8*)self;

    if ((self->input.buttons.held & PLAYER_INPUT_SHOOT)
        && self->charge_state[0] != PLAYER_CHARGE_FULL
        && ((self->weapon == 0) || ((self->armor_parts & 4) && (self->weapon_energy[self->weapon] >= player_weapon_energy.charge.linked_thresholds[self->weapon])))) {
        self->charge_timer = (u8)(self->charge_timer + 1);
        if (self->weapon == 0) {
            if (self->arm_type == 0) {
                full_charge_time = 0x5A;
            }
            if (self->arm_type == 1) {
                full_charge_time = 0x96;
            }
            if (self->arm_type == 2) {
                full_charge_time = 0x5A;
            }
        } else {
            full_charge_time = 0x5A;
        }
        if (self->charge_timer == 0x19) {
            func_8001540C(1, 7, self);
            self->charge_state[0] = PLAYER_CHARGE_PARTIAL;
            return;
        }
        if (self->charge_timer == full_charge_time) {
            self->charge_state[0] = PLAYER_CHARGE_FULL;
        }
        if ((self->weapon == 0) && (self->arm_type == 1)) {
#ifndef VERSION_JP
            if (self->stock_charge != 4) {
#endif
                if (self->charge_timer == 0x5A) {
                    if (self->stock_charge < 2) {
                        self->stock_charge = 2;
                    }
                }
                if (self->charge_timer == 0x78) {
                    self->stock_charge = 3;
                }
                if (self->charge_timer == 0x96) {
                    self->stock_charge = 4;
                }
#ifndef VERSION_JP
            }
#endif
        }
    }
}
#endif

#ifndef VERSION_DEMO
void player_charge_special_button(struct PlayerObj* self)
{
    u8 full_charge_time;

    if ((self->input.buttons.held & PLAYER_INPUT_SPECIAL) && (self->charge_state[1] != PLAYER_CHARGE_FULL)) {
        self->special_charge_timer++;
        if (self->arm_type == 0) {
            full_charge_time = 0x5A;
        }
        if (self->arm_type == 1) {
            full_charge_time = 0x96;
        }
        if (self->arm_type == 2) {
            full_charge_time = 0x5A;
        }
        if (self->special_charge_timer == 0x19) {
            func_8001540C(1, 7, self);
            self->charge_state[1] = PLAYER_CHARGE_PARTIAL;
            return;
        }
        if (self->special_charge_timer == full_charge_time) {
            self->charge_state[1] = PLAYER_CHARGE_FULL;
        }
        if (self->arm_type == 1) {
#ifndef VERSION_JP
            if (self->stock_charge != 4) {
#endif
                if (self->special_charge_timer == 0x5A) {
                    if (self->stock_charge < 2) {
                        self->stock_charge = 2;
                    }
                }
                if (self->special_charge_timer == 0x78) {
                    self->stock_charge = 3;
                }
                if (self->special_charge_timer == 0x96) {
                    self->stock_charge = 4;
                }
#ifndef VERSION_JP
            }
#endif
        }
    }
}
#endif

#ifndef VERSION_DEMO
void player_reset_charge_and_weapon(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        player_reset_charge(self);
        player_update_shot_types(self);
        player_equip_weapon(self);
    }
}
#endif

#ifndef VERSION_DEMO
void player_reset_charge(struct PlayerObj* self)
{
#ifdef MMX4_SATURN
    func_8001540C(6, 0, NULL);
#else
    stop_sound(1, 7);
#endif
    player_clear_flash(self);
    self->charge_state[0] = PLAYER_CHARGE_NONE;
    self->charge_state[1] = PLAYER_CHARGE_NONE;
    self->charge_timer = 0;
    self->special_charge_timer = 0;
}
#endif

void player_set_animation_shooting(struct PlayerObj* self, s32 animation)
{
    if (self->unk2 == 0 && self->attacking != 0) {
        animation += PLAYER_ATTACK_ANIM_OFFSET;
    }
    player_set_animation(self, animation);
}

// player_continue_animation
void func_80038568(struct PlayerObj* self, s32 frame)
{
    u32 attack_frame;
    u8 duration;

    if (self->unk2 != 0) {
        return;
    }
    attack_frame = frame + PLAYER_ATTACK_ANIM_OFFSET;
    if (self->attack_ended != 0) {
        duration = self->animation_step.fields.duration;
        player_set_animation_frame(self, frame, self->animation_step.fields.event & 0x3F);
        self->animation_step.fields.duration = duration;
    } else if (self->attacking != 0 && self->unk17 != attack_frame) {
        duration = self->animation_step.fields.duration;
        player_set_animation_frame(self, attack_frame, self->animation_step.fields.event & 0x3F);
        self->animation_step.fields.duration = duration;
    }
}

#ifndef VERSION_DEMO
void player_cancel_released_charge(void)
{
    struct PlayerObj* player = &g_Player;

    if (!(player->input.buttons.held & PLAYER_INPUT_SHOOT)) {
        player->charge_state[0] = 0;
        player->charge_timer = 0;
    }
    if (!(player->input.buttons.held & PLAYER_INPUT_SPECIAL)) {
        player->charge_state[1] = 0;
        player->special_charge_timer = 0;
    }
    if (player->charge_timer == 0 && player->special_charge_timer == 0) {
        player_reset_charge(player);
        player_reset_palette(player);
    }
}
#endif
