// 80036E98..80038678
#include "common.h"

struct PlayerHurtVelocity {
    s32 x_vel;
    s32 x_accel;
    s32 y_vel;
    s32 gravity;
};

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

s32 player_map_buttons(s32 pad);

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

union PlayerChargeData player_weapon_energy = {
    {
        { 0, 4, 3, 6, 3, 1 },
        { 1, 1, 1 },
        { 0, 12, 12, 12, 12, 6, 12, 12, 6, 0, 0, 0, 0, 0, 0 },
    },
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

// player_select_weapon
INCLUDE_ASM("main/nonmatchings/player_weapon", func_80036F50);
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

s32 player_check_shoot_air(struct PlayerObj* self)
{
    if (self->input_locked != 0 || self->unk2 != 0) {
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

s32 player_check_shoot_ladder(struct PlayerObj* self)
{
    if (self->input_locked != 0 || self->unk2 != 0) {
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

// player_enter_weapon_pose
INCLUDE_ASM("main/nonmatchings/player_weapon", func_80037484);
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

s32 player_check_nova_strike(struct PlayerObj* self)
{
    s32 wall_side;

    if (self->shot_cooldown || !(self->armor_parts & 2) || self->weapon_energy[0] != 0x30 || self->air_action) {
        return 0;
    }

    wall_side = PLAYER_COLLIDE_LEFT;
    if (self->unk15) {
        wall_side = PLAYER_COLLIDE_RIGHT;
    }
    if ((wall_side & self->unk88.bytes.collision_flags) || !(self->pressed_input & PLAYER_INPUT_GIGA)) {
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
    engine_obj.unk1C = 1;

    if (self->unk15) {
        self->x_vel.val = FIXED(2.5);
    } else {
        self->x_vel.val = FIXED(-2.5);
    }
    self->y_vel.val = FIXED(3.5);
    self->unk2C = 0x4200;
    self->unk28 = 0;
    self->unk5 = PLAYER_NOVA_STRIKE;
    self->unk6 = 0;

    return 1;
}

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
                    if (++self->shot_cycle == 3) {
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
    } else if ((self->input.history & 0x100010) == 0x100000) { // flags?
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

void player_check_special_button(struct PlayerObj* self)
{
    if (self->shot_type == -1) {
        if (self->pressed_input & PLAYER_INPUT_SPECIAL) {
            self->shot_type = self->shot_types[1];
            return;
        }
        if ((self->input.history & 0x200020) == 0x200000) {
            if ((self->shot_types[1] != 0) && (self->shot_types[1] != 0x13)) {
                self->shot_type = self->shot_types[1];
            }
        }
    }
}

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

    return charge_level >= player_weapon_energy.charge.animation_indices[charge_type];
}

void player_use_weapon_energy(struct PlayerObj* self, s8 shot_type)
{
    s8 animation_cost;

    animation_cost = player_weapon_energy.charge.animation_indices[shot_type];
    if ((animation_cost != 0) && ((player_shot_is_special_weapon[shot_type] == 0) || !(self->armor_parts & 1))) {
        self->weapon_energy[self->weapon] -= animation_cost;
    }
}

void player_fire_none(struct PlayerObj* self)
{
}

void player_fire_weapon(struct PlayerObj* self)
{
    player_spawn_weapon(1, self->shot_type, 0, self);
}

void player_fire_charged_buster(struct PlayerObj* self)
{
    player_spawn_visual(0x21, 2, self->shot_type, 0);
    if ((self->shot_type == 0x12) && (get_random() & 1)) {
        player_play_voice(self, 8);
    }
}

// player_fire_twin_slasher
INCLUDE_ASM("main/nonmatchings/player_weapon", func_80037C28);
void player_fire_lightning_web_charged(struct PlayerObj* self)
{
    s8 i;
    struct PlayerObj* player;
    struct WeaponObj* weapon;
    struct WeaponObj* first_weapon;

    player = self;
    i = 0;
    do {
        weapon = find_free_weapon_obj();
        if (weapon != 0) {
            weapon->active = 1;
            weapon->id = player->shot_type;
            weapon->unk2 = i;
            weapon->bg_offset = player->bg_offset;
            if (i == 0) {
                first_weapon = weapon;
            } else {
                weapon->owner = (struct PlayerObj*)first_weapon;
            }
        }
        i++;
    } while (i < 9);
}

void player_enter_frost_tower_pose(struct PlayerObj* self)
{
    player_set_animation(self, 0x5F);
    player_play_voice(self, 5);
    self->air_state = 1;
    self->unk5 = PLAYER_WEAPON_POSE;
    self->unk6 = 0;
}

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

s32 player_set_charge_flash(struct PlayerObj* self, s8 button)
{
    s8 shot_type;
    if (self->charge_state[button] == PLAYER_CHARGE_NONE) {
        return 0;
    }
    if (self->charge_state[button] == PLAYER_CHARGE_PARTIAL) {
        self->flash_palette = 0x26;
    } else {
        shot_type = self->shot_types[button];
        if (shot_type == 0x13) {
            self->flash_palette = 0x2C;
        } else {
            self->flash_palette = (shot_type == 0x14) ? 0x2F : 0x29;
        }
    }
    return 1;
}

s32 player_charge_released(struct PlayerObj* self)
{
    if (self->pressed_input & PLAYER_INPUT_SHOOT) {
        return 1;
    }
    if (self->pressed_input & PLAYER_INPUT_SPECIAL) {
        return 1;
    }
    if ((self->input.history & 0x100010) == 0x100000) {
        return 1;
    }
    if ((self->input.history & 0x200020) == 0x200000) {
        return 1;
    }
    if (self->charge_timer && (self->input.buttons.held & PLAYER_INPUT_SHOOT) == 0) {
        return 1;
    }
    if (self->special_charge_timer && !(self->input.buttons.held & PLAYER_INPUT_SPECIAL)) {
        return 1;
    }
    return 0;
}

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

void player_reset_charge_and_weapon(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        player_reset_charge(self);
        player_update_shot_types(self);
        player_equip_weapon(self);
    }
}

void player_reset_charge(struct PlayerObj* self)
{
    stop_sound(1, 7);
    player_clear_flash(self);
    self->charge_state[0] = PLAYER_CHARGE_NONE;
    self->charge_state[1] = PLAYER_CHARGE_NONE;
    self->charge_timer = 0;
    self->special_charge_timer = 0;
}

void player_set_animation_shooting(struct PlayerObj* self, s32 animation)
{
    if (self->unk2 == 0 && self->attacking != 0) {
        animation += 0x70;
    }
    player_set_animation(self, animation);
}

// player_continue_animation
INCLUDE_ASM("main/nonmatchings/player_weapon", func_80038568);
void player_cancel_released_charge(void)
{
    struct PlayerObj* player = &g_Player;
    u16 held = player->input.buttons.held;

    if (!(held & PLAYER_INPUT_SHOOT)) {
        player->charge_state[0] = 0;
        player->charge_timer = 0;
    }
    if (!(held & PLAYER_INPUT_SPECIAL)) {
        player->charge_state[1] = 0;
        player->special_charge_timer = 0;
    }
    if (player->charge_timer == 0 && player->special_charge_timer == 0) {
        player_reset_charge(player);
        player_reset_palette(player);
    }
}
