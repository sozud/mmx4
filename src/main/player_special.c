// 80038678..8003B3DC
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

void player_reset_weapon(struct PlayerObj* self);

void player_update_weapon(struct PlayerObj* self);

// player_select_weapon

void player_update_shot_types(struct PlayerObj* self);

void player_update_charged_shot_type(struct PlayerObj* self, s32 button);

void player_equip_weapon(struct PlayerObj* self);

s32 player_check_shoot(struct PlayerObj* self);

s32 player_check_shoot_air(struct PlayerObj* self);

s32 player_check_shoot_ladder(struct PlayerObj* self);

// player_enter_weapon_pose

s32 player_check_hover(struct PlayerObj* self);

s32 player_check_nova_strike(struct PlayerObj* self);

void player_update_shooting(struct PlayerObj* self);

void player_check_shoot_button(struct PlayerObj* self);

void player_check_special_button(struct PlayerObj* self);

s32 player_has_weapon_energy(struct PlayerObj* self);

void player_use_weapon_energy(struct PlayerObj* self, s8 shot_type);

void player_fire_none(struct PlayerObj* self);

void player_fire_weapon(struct PlayerObj* self);

void player_fire_charged_buster(struct PlayerObj* self);

// player_fire_twin_slasher

void player_fire_lightning_web_charged(struct PlayerObj* self);

void player_enter_frost_tower_pose(struct PlayerObj* self);

void player_enter_soul_body(struct PlayerObj* self);

void player_enter_rising_fire(struct PlayerObj* self, s32 airborne);

void player_enter_rising_fire_charged(struct PlayerObj* self, s32 airborne);

void player_enter_double_cyclone_pose(struct PlayerObj* self);

void player_update_charge(struct PlayerObj* self);

s32 player_set_charge_flash(struct PlayerObj* self, s8 button);

s32 player_charge_released(struct PlayerObj* self);

void player_charge_shoot_button(struct PlayerObj* self);

void player_charge_special_button(struct PlayerObj* self);

void player_reset_charge_and_weapon(struct PlayerObj* self);

void player_reset_charge(struct PlayerObj* self);

void player_set_animation_shooting(struct PlayerObj* self, s32 animation);

// player_continue_animation

void player_cancel_released_charge(void);

u8 player_shoot_animations[] = {
    0x58,
    0x58,
    0x00,
    0x58,
    0x00,
    0x58,
    0x59,
    0x00,
    0x58,
    0x5A,
    0x58,
    0x00,
    0x00,
    0x00,
    0x58,
    0x59,
    0x00,
    0x5B,
    0x5B,
    0x5A,
    0x5B,
    0x00,
    0x00,
    0x00,
};

u8 player_ladder_shoot_animations[] = {
    0x5C,
    0x5C,
    0x00,
    0x5C,
    0x00,
    0x5C,
    0x5D,
    0x00,
    0x5C,
    0x5C,
    0x5C,
    0x00,
    0x00,
    0x00,
    0x5C,
    0x5D,
    0x00,
    0x5C,
    0x5C,
    0x5C,
    0x5C,
    0x00,
    0x00,
    0x00,
};

void (*player_hover_funcs[])(struct PlayerObj*) = {
    player_hover_start,
    player_hover_rise,
    player_hover_hold,
    player_hover_forward,
    player_hover_forward_stop,
    player_hover_back,
    player_hover_back_stop,
};

s8 player_hover_bob[16] = {
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    0,
    0,
    -1,
    0,
    -1,
    -1,
    0,
    -1,
    0,
};

void (*player_nova_strike_funcs[])(struct PlayerObj*) = {
    player_nova_strike_windup,
    player_nova_strike_dash,
    player_nova_strike_end,
};

void (*player_rising_fire_charged_funcs[])(struct PlayerObj*) = {
    player_rising_fire_charged_start,
    player_rising_fire_charged_rise,
    player_rising_fire_charged_peak,
    player_rising_fire_charged_fall,
};

u8 player_zero_combo_sounds[4][2] = {
    { 7, 3 },
    { 8, 4 },
    { 7, 5 },
    { 0, 0 },
};

void (*player_zero_hyouretsuzan_funcs[])(struct PlayerObj*) = {
    player_zero_hyouretsuzan_start,
    player_zero_hyouretsuzan_drop,
    player_zero_hyouretsuzan_land,
};

void (*player_zero_ryuenjin_funcs[])(struct PlayerObj*) = {
    player_zero_ryuenjin_start,
    player_zero_ryuenjin_rise,
    player_zero_ryuenjin_peak,
    player_zero_ryuenjin_fall,
};

void player_idle_animate(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        if (self->shot_fired != 0) {
            player_set_shoot_animation(self);
            return;
        }
        if (self->attack_ended != 0) {
            player_set_idle_animation(self);
            return;
        }
    }
    if (self->unk17 == 6) {
        if (self->hp >= engine_obj.unk46 / 3) {
            player_set_animation(self, 5);
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

extern u8 player_shoot_animations[];

void player_set_shoot_animation(struct PlayerObj* self)
{
    s32 animation;

    animation = player_shoot_animations[self->shot_type];
    player_set_animation(self, animation);
    if (animation == 0x59) {
        self->animation_step.fields.duration = self->attack_pose_timer - 8;
    }
}

void player_enter_ladder_shoot(struct PlayerObj* self)
{
    player_set_ladder_shoot_animation(self);
    self->x_pos.i.hi = (self->x_pos.i.hi & 0xFFF0) + 8;
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->unk5 = PLAYER_LADDER_SHOOT;
    self->unk6 = 0;
}

void player_set_ladder_shoot_animation(struct PlayerObj* self)
{
    s32 animation;

    animation = player_ladder_shoot_animations[self->last_shot_type];
    player_set_animation(self, animation);
    if (animation == 0x5D) {
        self->animation_step.fields.duration = self->attack_pose_timer - 8;
    }
}

void player_ladder_shoot(struct PlayerObj* self)
{
    if ((player_check_off_ladder(self) == 0) && (player_check_shoot_ladder(self) == 0)) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->pressed_input & PLAYER_INPUT_LEFT) {
            self->unk15 = 0;
        }
        if (self->pressed_input & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
        }
        if (self->attack_ended != 0) {
            player_set_animation_frame(self, 0x20, 3);
            player_enter_ladder_down(self);
        }
    }
}

void player_hover(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        player_enter_fall(self);
    } else if (player_check_shoot_air(self) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        player_hover_funcs[self->unk6](self);
    }
}

void player_hover_start(struct PlayerObj* self)
{
    func_80038568(self, 0x15);
    if (self->animation_step.fields.event & 0x80) {
        self->animation_step.fields.event &= 0x7F;
        player_spawn_visual(0x21, 0x21, 0, 0);
        self->unk6++;
    }
}

void player_hover_rise(struct PlayerObj* self)
{
    s32 direction;

    if (player_hover_check_end(self) != 0) {
        return;
    }
    if (player_check_wall(self) != 0) {
        return;
    }
    if ((player_check_dash_input(self) != 0) && (self->shot_cooldown == 0)) {
        player_enter_air_dash(self);
        return;
    }
    direction = player_hover_steer(self);
    if (direction != 0) {
        self->hover_timer = 0x28;
        player_hover_set_direction(self, direction);
        return;
    }
    func_80038568(self, 0x15);
}

void player_hover_hold(struct PlayerObj* self)
{
    s32 direction;

    if ((player_hover_check_end(self) == 0) && (player_check_wall(self) == 0)) {
        direction = player_hover_steer(self);
        if (direction != 0) {
            player_hover_set_direction(self, direction);
            return;
        }
        func_80038568(self, 0x16);
    }
}

void player_hover_forward(struct PlayerObj* self)
{
    s32 direction;

    if (player_hover_check_end(self) != 0 || player_check_wall(self) != 0) {
        return;
    }

    direction = player_hover_steer(self);
    if (direction != 0) {
        if (direction > 0) {
            move_object(MOVING_OBJECT(self));
            func_80038568(self, 0x17);
            return;
        }
        player_set_animation_shooting(self, 0x19);
        self->unk6 = 5;
    } else {
        player_set_animation_shooting(self, 0x18);
        self->unk6 = 4;
    }
}

void player_hover_forward_stop(struct PlayerObj* self)
{
    s32 action;

    if (player_hover_check_end(self) == 0 && player_check_wall(self) == 0) {
        action = player_hover_steer(self);
        if (action != PLAYER_BEAM_IN) {
            player_hover_set_direction(self, action);
            return;
        }
        if (self->animation_step.fields.relative_step == 0) {
            player_set_animation_shooting(self, 0x16);
            self->unk6 = 2;
            return;
        }
        func_80038568(self, 0x18);
    }
}

void player_hover_back(struct PlayerObj* self)
{
    s32 direction;

    if ((player_hover_check_end(self) == 0) && (player_check_wall(self) == 0)) {
        direction = player_hover_steer(self);
        if (direction != 0) {
            if (direction > 0) {
                player_set_animation_shooting(self, 0x17);
                self->unk6 = 3;
            } else {
                move_object(MOVING_OBJECT(self));
                func_80038568(self, 0x19);
                return;
            }
        } else {
            player_set_animation_shooting(self, 0x1A);
            self->unk6 = 6;
        }
    }
}

void player_hover_back_stop(struct PlayerObj* self)
{
    s32 action;

    if (player_hover_check_end(self) == 0 && player_check_wall(self) == 0) {
        action = player_hover_steer(self);
        if (action != PLAYER_BEAM_IN) {
            player_hover_set_direction(self, action);
            return;
        }
        if (self->animation_step.fields.relative_step == 0) {
            player_set_animation_shooting(self, 0x16);
            self->unk6 = 2;
            return;
        }
        func_80038568(self, 0x1A);
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/player_special", player_hover_check_end);
#else
s32 player_hover_check_end(struct PlayerObj* self)
{
    s32 result;
    s32 trigger;
    u8 timer;

    trigger = self->pressed_input & PLAYER_INPUT_JUMP;
    timer = self->hover_timer - 1;
    self->hover_timer = timer;
    trigger = trigger != 0;
    if (!(timer & 0xFF)) {
        trigger = 1;
    }
    result = 0;
    if (trigger != 0) {
        player_enter_fall(self);
        result = 1;
    }
    return result;
}
#endif

s32 player_hover_steer(struct PlayerObj* self)
{
    u16 buttons;

    self->y_pos.i.hi += player_hover_bob[self->hover_bob];
    self->hover_bob = (self->hover_bob + 1) & 0xF;
    buttons = self->input.buttons.held;
    self->x_vel.val = 0;

    if (!(buttons & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT))) {
        return 0;
    }

    if (buttons & PLAYER_INPUT_RIGHT) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            return 0;
        }
        self->x_vel.val = FIXED(2);
        if (self->unk15 != 0) {
            return 1;
        }
        return -1;
    } else {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
            return 0;
        }
        self->x_vel.val = FIXED(-2);
        if (self->unk15 != 0) {
            return -1;
        }
        return 1;
    }
}

void player_hover_set_direction(struct PlayerObj* self, s32 direction)
{
    if (direction > 0) {
        player_set_animation_shooting(self, 0x17);
        self->unk6 = 3;
    } else {
        player_set_animation_shooting(self, 0x19);
        self->unk6 = 5;
    }
}

void player_nova_strike(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        self->spike_immune = 0;
        self->nova_strike_active = 0;
        player_reset_palette(self);
        player_enter_land_or_fall(self);
    } else {
        animate_object(ANIMATED_OBJECT(self));
        player_nova_strike_funcs[self->unk6](self);
    }
}

void player_nova_strike_windup(struct PlayerObj* self)
{
    player_nova_strike_hit_wall(self);
    if (self->animation_step.fields.event & 0x80) {
        self->animation_step.fields.event = 0;
        self->unk6++;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void player_nova_strike_dash(struct PlayerObj* self)
{
    if (player_nova_strike_hit_wall(self) != 0 && ((u8)self->animation_step.fields.event & 0x40)) {
        self->spike_immune = 0;
        self->nova_strike_active = 0;
        engine_obj.unk1C = 0;
        player_enter_land_or_fall(self);
        return;
    }
    if ((u8)self->animation_step.fields.event & 0x20) {
        self->animation_step.fields.event = 0;
        player_spawn_weapon(1, 0x16, 0, NULL);
        player_set_palette(self, 0x49);
        func_8001540C(1, 5, self);
        func_8001540C(0, 0x20, self);
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(8);
        } else {
            self->x_vel.val = FIXED(-8);
        }
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->unk2C = 0;
        self->unk6++;
    }
}

void player_nova_strike_end(struct PlayerObj* self)
{
    s32 should_reset;
    u8 timer;

    should_reset = player_nova_strike_hit_wall(self) != 0;
    timer = self->nova_strike_timer;
    if (timer == 0) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        self->spike_immune = 0;
        self->nova_strike_active = 0;
        engine_obj.unk1C = 0;
        player_reset_palette(self);
        player_enter_land_or_fall(self);
    } else {
        self->nova_strike_timer = timer - 1;
        move_object(MOVING_OBJECT(self));
    }
}

s32 player_nova_strike_hit_wall(struct PlayerObj* self)
{
    u8 wall_flag;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) {
        self->y_vel.val = 0;
        self->unk2C = 0;
    }
    if (self->unk15 != 0) {
        wall_flag = PLAYER_COLLIDE_RIGHT;
    } else {
        wall_flag = PLAYER_COLLIDE_LEFT;
    }
    if (self->unk88.bytes.collision_flags & wall_flag) {
        self->x_vel.val = 0;
        self->unk28 = 0;
        return 1;
    }
    return 0;
}

void player_soul_body(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        player_soul_body_cast(self);
    } else {
        player_soul_body_wait(self);
    }
}

void player_soul_body_cast(struct PlayerObj* self)
{
    s8 event;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event & 0x80) {
        self->animation_step.fields.event = event & 0x7F;
        func_8001540C(1, 9, self);
        player_play_voice(self, 5U);
        player_init_clone();
        g_Entity.active = 1;
        g_Entity.x_pos.val = self->x_pos.val;
        g_Entity.y_pos.val = self->y_pos.val;
        g_Entity.unk15 = self->unk15;
        g_Entity.air_state = 1;
        g_Entity.clone_timer = 0xF0;
        g_Entity.clone_offset.value = 0;
        player_set_collision_bounds(&g_Entity);
        self->unk6 = (u8)self->unk6 + 1;
    }
}

void player_soul_body_wait(struct PlayerObj* self)
{
    if (self->controlling_clone == 0) {
        player_enter_land_or_fall(self);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void player_soul_body_clone_advance(struct PlayerObj* self)
{
    u8 facing;
    s16 offset;
    s32 done;

    done = 0;
    facing = g_Player.unk15;
    self->unk15 = facing;
    if (facing != 0) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            done = 1;
        } else {
            self->x_pos.i.hi = g_Player.x_pos.u.hi + self->clone_offset.unsigned_value;
        }
    } else if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
        done = 1;
    } else {
        self->x_pos.i.hi = g_Player.x_pos.u.hi - self->clone_offset.unsigned_value;
    }

    offset = self->clone_offset.value;
    if (offset == 0x40) {
        done = 1;
    }
    if (done != 0) {
        player_enter_land_or_fall(self);
    } else {
        self->clone_offset.value = offset + 8;
    }
}

void player_soul_body_clone_vanish(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->active = 0;
        self->on_screen = 0;
        g_Player.controlling_clone = 0;
        g_Player.spike_immune = 0;
    }
}

void player_weapon_pose(struct PlayerObj* self)
{
    struct WeaponObj* weapon;
    s8 event;
    s8 row;
    s8 column;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event & 0x80) {
        self->animation_step.fields.event = event & 0x7F;
        if (self->shot_type == 2) {
            weapon = player_spawn_weapon(1, 2, 0, NULL);
            if (weapon != NULL) {
                player_spawn_visual(1, 0x1A, 1, weapon);
            }
            self->shot_count++;
            self->special_shot_count++;
        }
        if (self->shot_type == 0xB) {
            player_spawn_weapon(1, 0xB, 0, NULL);
            self->shot_count++;
            self->special_shot_count++;
        }
        if (self->shot_type == 7) {
            player_spawn_weapon(1, 7, 0, NULL);
            player_spawn_weapon(1, 7, 1, NULL);
            self->shot_count += 2;
            self->special_shot_count += 2;
        }
        if (self->shot_type == 0x10) {
            player_spawn_visual(1, 0x13, 0, NULL);
            player_spawn_visual(1, 0x13, 1, NULL);
            for (row = 0; row < 2; row++) {
                for (column = 0; column < 5; column++) {
                    player_spawn_weapon(1, 0x10, column | (row << 7), NULL);
                }
            }
            self->shot_count++;
            self->special_shot_count++;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        player_enter_land_or_fall(self);
    }
}

void player_rising_fire(struct PlayerObj* self)
{
    s8 event;
    struct WeaponObj* weapon;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event & 0x80) {
        self->animation_step.fields.event = event & 0x7F;
        if (self->unk17 == 0x63) {
            weapon = player_spawn_weapon(1, 4, 0, NULL);
        } else {
            weapon = player_spawn_weapon(1, 4, 1, NULL);
        }
        if (weapon != NULL) {
            player_spawn_visual(1, 0x1A, 0, weapon);
        }
        self->shot_count++;
        self->special_shot_count++;
    }

    if ((self->unk17 == 0x63) && (self->attacking == 0)) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
            self->air_state = 0;
            if (player_check_script(self) != 0) {
                return;
            }
            if (player_check_ladder(self) != 0) {
                return;
            }
            if (player_check_shoot(self) != 0) {
                return;
            }
            if (player_check_dash_jump(self) != 0) {
                return;
            }
            if (player_check_walk_start(self) != 0) {
                player_enter_walk_start(self);
                return;
            }
            if (self->shot_fired != 0) {
                player_set_shoot_animation(self);
                self->unk5 = PLAYER_IDLE;
                self->unk6 = 0;
                return;
            }
            self->air_state = 1;
        } else {
            player_enter_fall(self);
            return;
        }
    }

    if (self->animation_step.fields.relative_step == 0) {
        player_enter_land_or_fall(self);
    }
}

void player_rising_fire_charged(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    player_rising_fire_charged_funcs[self->unk6](self);
}

void player_rising_fire_charged_start(struct PlayerObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event &= 0x7F;
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(4);
        } else {
            self->x_vel.val = FIXED(-4);
        }
        self->unk28 = FIXED(-0.25);
        self->y_vel.val = FIXED(6.75);
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
    }
}

void player_rising_fire_charged_rise(struct PlayerObj* self)
{
    if (player_leap_check_peak(self) == 0) {
        player_leap_check_wall(self);
    }
}

void player_rising_fire_charged_peak(struct PlayerObj* self)
{
    player_leap_check_peak(self);
}

void player_rising_fire_charged_fall(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        self->spike_immune = 0;
        player_enter_land(self);
        return;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        player_set_animation_shooting(self, 0xB);
        self->spike_immune = 0;
        self->unk5 = PLAYER_FALL;
        self->unk6 = 0;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/player_special", player_zero_check_ground_technique);
#else
s32 player_zero_check_ground_technique(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        return 0;
    } else if (self->input_locked != 0) {
        return 0;
    } else if (func_80039F28(self) != 0) {
        return 1;
    } else if (player_zero_check_ryuenjin(self) == 0) {
        return player_zero_check_raijingeki(self) != 0;
    }
    return 1;
}
#endif

s32 player_zero_check_saber(struct PlayerObj* self)
{
    if (player_zero_check_slash_input(self) == 0) {
        return 0;
    }
    player_set_animation(self, 0x58);
    func_8001540C(1, 7, self);
    player_play_voice(self, 3);
    self->dash_momentum = 0;
    self->air_action = 0;
    self->unk5 = PLAYER_ZERO_SABER;
    self->unk6 = 0;
    player_zero_saber(self);
    return 1;
}

s32 player_zero_check_jump_slash(struct PlayerObj* self)
{
    if (player_zero_check_slash_input(self) != 0) {
        if (self->boss_flags & 4) {
            player_set_animation(self, 0x64);
            func_8001540C(1, 7, self);
            self->unk5 = PLAYER_ZERO_SPIN_JUMP_SLASH;
        } else {
            player_set_animation(self, 0x5B);
            func_8001540C(1, 8, self);
            self->unk5 = PLAYER_ZERO_JUMP_SLASH;
        }
        self->unk6 = 0;
        player_zero_jump_slash(self);
        return 1;
    }
    return 0;
}

s32 player_zero_check_fall_slash(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        return 0;
    }
    if (self->input_locked != 0) {
        return 0;
    }
    if (player_zero_check_hyouretsuzan(self) != 0) {
        return 1;
    }
    if (player_zero_check_slash_input(self) == 0) {
        return 0;
    }

    if (self->boss_flags & 4) {
        player_set_animation(self, 0x64);
        func_8001540C(1, 7, self);
        self->unk5 = PLAYER_ZERO_SPIN_FALL_SLASH;
    } else {
        player_set_animation(self, 0x5B);
        func_8001540C(1, 8, self);
        self->unk5 = PLAYER_ZERO_FALL_SLASH;
    }

    self->unk6 = 0;
    player_zero_fall_slash(self);
    return 1;
}

s32 player_zero_check_ladder_slash(struct PlayerObj* self)
{
    if (player_zero_check_slash_input(self) == 0) {
        return 0;
    }
    player_set_animation(self, 0x5D);
    func_8001540C(1, 7, self);
    player_play_voice(self, 8);
    self->dash_momentum = 0;
    self->air_action = 0;
    self->unk5 = PLAYER_ZERO_LADDER_SLASH;
    self->unk6 = 0;
    player_zero_ladder_slash(self);
    return 1;
}

s32 player_zero_check_wall_slash(struct PlayerObj* self)
{
    if (player_zero_check_slash_input(self) == 0) {
        return 0;
    }

    player_set_animation(self, 0x5E);
    func_8001540C(1, 7, self);
    player_play_voice(self, 8);
    self->unk5 = PLAYER_ZERO_WALL_SLASH;
    self->unk6 = 0;
    player_zero_wall_slash(self);
    return 1;
}

s32 player_zero_check_slash_input(struct PlayerObj* self)
{
    if (self->unk2 != 0 && self->input_locked == 0 && (self->pressed_input & PLAYER_INPUT_SHOOT) && self->attacking == 0) {
        player_zero_begin_attack(self);
        return 1;
    }
    return 0;
}

void player_zero_begin_attack(struct PlayerObj* self)
{
    self->attacking = 1;
    self->combo = 0;
    self->afterimage = 0;
}

s32 player_zero_check_raijingeki(struct PlayerObj* self)
{
    if (!(self->boss_flags & 1))
        return 0;
    if (self->pressed_input & PLAYER_INPUT_SPECIAL) {
        if (self->attacking == 0) {
            player_zero_begin_attack(self);
            player_set_animation(self, 0x5F);
            self->unk5 = PLAYER_ZERO_RAIJINGEKI;
            self->unk6 = 0;
            player_zero_raijingeki(self);
            return 1;
        }
    }
    return 0;
}

s32 player_zero_check_hyouretsuzan(struct PlayerObj* self)
{
    if (!(self->boss_flags & 2)) {
        return 0;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_DOWN)) {
        return 0;
    }
    if (!(self->pressed_input & PLAYER_INPUT_SPECIAL)) {
        return 0;
    }
    if (self->attacking != 0) {
        return 0;
    }

    player_zero_begin_attack(self);
    player_set_animation(self, 0x61);
    player_play_voice(self, 5);
    if (self->input.buttons.held & PLAYER_INPUT_LEFT) {
        self->unk15 = 0;
    }
    if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
    }
    self->unk5 = PLAYER_ZERO_HYOURETSUZAN;
    self->unk6 = 0;
    player_zero_hyouretsuzan(self);
    return 1;
}

s32 player_zero_check_double_jump(struct PlayerObj* self)
{
    if (!(self->boss_flags & 4)) {
        return 0;
    } else if (!(self->pressed_input & PLAYER_INPUT_JUMP)) {
        return 0;
    } else {
        player_set_animation(self, 0x63);
        func_8001540C(1, 1, self);
        player_play_voice(self, 7);
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = FIXED(5.8125);
        self->unk2C = FIXED(0.2578125);
        self->dash_momentum = 0;
        self->air_action = 6;
        self->afterimage = 0;
        player_air_steer(self);
        self->unk5 = PLAYER_JUMP;
        self->unk6 = 0;
        return 1;
    }
}

s32 player_zero_check_ryuenjin(struct PlayerObj* self)
{
    if (!(self->boss_flags & 8)) {
        return 0;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_UP)) {
        return 0;
    }
    if (!(self->pressed_input & PLAYER_INPUT_SPECIAL)) {
        return 0;
    }
    if (self->attacking != 0) {
        return 0;
    }

    player_zero_begin_attack(self);
    player_set_animation(self, 0x65);
    func_8001540C(0, 0x1B, self);
    player_play_voice(self, 9);
    self->air_state = 1;
    self->spike_immune = 1;
    self->unk5 = PLAYER_ZERO_RYUENJIN;
    self->unk6 = 0;
    player_zero_ryuenjin(self);
    return 1;
}

// player_zero_check_rakuhouha
s32 func_80039F28(struct PlayerObj* arg)
{
    struct PlayerObj* player = arg;

    if ((player->boss_flags & 0x20) && (player->weapon_energy[0] >= 0xC) && (player->pressed_input & 0x40)) {
        if (player->attacking != 0) {
            return 0;
        }
        player_zero_begin_attack(arg);
        player_set_animation(arg, 0x67);
        player_play_voice(arg, 0xAU);
        player->invincibility_timer = 0;
        player->hurt_phase = 0;
        player_reset_palette(arg);
        player->air_state = 1;
        player->spike_immune = 1;
        player->weapon_energy[0] -= 0xC;
        player->unk5 = 0x3A;
        player->unk6 = 0;
        player_zero_rakuhouha(arg);
        return 1;
    }
    return 0;
}
s32 player_zero_check_shippuuga(struct PlayerObj* self)
{
    if (self->unk2 == 0) {
        return 0;
    }
    if (self->input_locked != 0) {
        return 0;
    }
    if (((u8)self->boss_flags & 0x80) == 0) {
        return 0;
    }
    if ((self->pressed_input & PLAYER_INPUT_SPECIAL) == 0) {
        return 0;
    }
    if (self->attacking != 0) {
        return 0;
    }
    self->attacking = 1;
    self->combo = 0;
    player_clear_dash(self);
    player_set_animation(self, 0x68);
    func_8001540C(1, 8, self);
    player_play_voice(self, 9);
    if (self->unk15 != 0) {
        self->x_vel.val = FIXED(4.125);
    } else {
        self->x_vel.val = FIXED(-4.125);
    }
    self->unk28 = FIXED(-0.21875);
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk5 = PLAYER_ZERO_SHIPPUUGA;
    self->unk6 = 0;
    player_zero_shippuuga(self);
    return 1;
}

void player_zero_saber(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        player_zero_saber_on_event(self, 0x18);
        if (func_8003A1DC(self) != 0) {
            return;
        }
    }

    if (self->input_locked == 0) {
        self->attacking = 0;
        if (player_check_dash_jump(self) != 0) {
            return;
        }
        if (self->animation_step.fields.event & 0x40) {
            if (player_zero_check_ground_technique(self) != 0 || player_zero_check_saber(self) != 0 || player_zero_check_ladder_or_walk(self) != 0) {
                return;
            }
        }
        self->attacking = 1;
    }
    player_zero_attack_finish(self);
}

// player_zero_check_combo
INCLUDE_ASM("main/nonmatchings/player_special", func_8003A1DC);
s32 player_zero_check_ladder_or_walk(struct PlayerObj* self)
{
    if (player_check_ladder(self) != 0) {
        return 1;
    }
    if (player_check_walk_start(self) == 0) {
        return 0;
    }
    player_enter_walk_start(self);
    return 1;
}

void player_zero_attack_finish(struct PlayerObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->attacking = 0;
        if (engine_obj.unkF != 0) {
            player_start_stage_clear(self);
            return;
        }
        if (self->script_state != 0) {
            func_80034E2C();
            return;
        }
        player_enter_idle(self);
    }
}

void player_zero_jump_slash(struct PlayerObj* self)
{
    s8 saved_unk8E;

    if (self->unk6 == 0) {
        if (self->unk5 == PLAYER_ZERO_JUMP_SLASH) {
            player_zero_saber_on_event(self, 0x1B);
        }
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->unk5 == PLAYER_ZERO_SPIN_JUMP_SLASH) {
            player_zero_saber_on_event(self, 0x22);
        }
    }
    if (self->input_locked != 0) {
        self->y_vel.val = 0;
    }
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) {
        self->y_vel.val = 0;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_JUMP)) {
        self->y_vel.val = 0;
    }
    if (self->attacking != 0 && self->animation_step.fields.relative_step == 0) {
        self->attacking = 0;
    }
    if (player_zero_check_jump_slash(self) != 0) {
        return;
    }
    saved_unk8E = self->attacking;
    self->attacking = 0;
    if ((self->animation_step.fields.event & 0x40) && player_zero_check_jump_slash(self) != 0) {
        return;
    }
    if (self->unk8A.bytes.high == 0) {
        if (player_check_ladder_air(self) != 0) {
            return;
        }
        if (player_check_wall(self) != 0) {
            return;
        }
        if (player_check_air_move(self) != 0) {
            return;
        }
    } else {
        self->unk8A.bytes.high--;
    }

    self->attacking = saved_unk8E;
    player_air_steer(self);
    player_check_splash(self);
    if (self->y_vel.val <= 0) {
        if (self->attacking != 0) {
            if (self->unk5 == PLAYER_ZERO_JUMP_SLASH) {
                self->unk5 = PLAYER_ZERO_FALL_SLASH;
            } else {
                self->unk5 = PLAYER_ZERO_SPIN_FALL_SLASH;
            }
            self->unk6 = 1;
        } else {
            player_set_animation_frame(self, 0xB, 5);
            self->unk8A.bytes.low = 0;
            self->unk5 = PLAYER_FALL;
            self->unk6 = 0;
        }
        self->air_state = -1;
    }
}

void player_zero_fall_slash(struct PlayerObj* self)
{
    u8 duration;
    u8 saved_unk8E;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        self->air_state = 0;
        self->dash_momentum = 0;
        self->air_action = 0;
        self->afterimage = 0;
        if (self->attacking != 0) {
            if (self->unk5 == PLAYER_ZERO_FALL_SLASH) {
                duration = self->animation_step.fields.duration;
                player_set_animation_frame(self, 0x5C, self->animation_step.fields.event & 0x1F);
                self->animation_step.fields.duration = duration;
                player_zero_spawn_saber(self, 0x1C);
                self->unk5 = PLAYER_ZERO_SABER;
                self->unk6 = 1;
                return;
            }
            self->attacking = 0;
        }
        player_enter_land(self);
        return;
    }

    if (self->unk6 == 0) {
        if (self->unk5 == PLAYER_ZERO_FALL_SLASH) {
            player_zero_saber_on_event(self, 0x1B);
        }
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->unk5 == PLAYER_ZERO_SPIN_FALL_SLASH) {
            player_zero_saber_on_event(self, 0x22);
        }
    }

    if (self->attacking != 0 && self->animation_step.fields.relative_step == 0) {
        self->attacking = 0;
    }
    if (player_zero_check_fall_slash(self) != 0) {
        return;
    }
    saved_unk8E = self->attacking;
    self->attacking = 0;
    if ((self->animation_step.fields.event & 0x40) && player_zero_check_fall_slash(self) != 0) {
        return;
    }
    if (player_check_ladder_air(self) != 0 || player_check_wall(self) != 0 || player_check_air_move(self) != 0) {
        return;
    }

    self->attacking = saved_unk8E;
    player_air_steer(self);
    player_check_splash(self);
    if (self->attacking == 0) {
        player_set_animation_frame(self, 0xB, 5);
        self->unk5 = PLAYER_FALL;
        self->unk6 = 0;
    }
}

void player_zero_ladder_slash(struct PlayerObj* self)
{
    s8 state;

    if (player_check_off_ladder(self) != 0) {
        self->attacking = 0;
        return;
    }

    state = self->unk6;
    if (state == 0) {
        self->unk6 = state + 1;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }

    player_zero_saber_on_event(self, 0x1E);
    if ((u8)self->animation_step.fields.event & 0x40) {
        self->attacking = 0;
        if (player_zero_check_ladder_slash(self) != 0) {
            return;
        }
        self->attacking = 1;
    }

    if (self->pressed_input & PLAYER_INPUT_LEFT) {
        self->unk15 = 0;
    }
    if (self->pressed_input & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->attacking = 0;
        player_set_animation_frame(self, 0x1F, 2);
        player_enter_ladder_up(self);
    }
}

void player_zero_wall_slash(struct PlayerObj* self)
{
    u8 collision_flags;
    s8 substate;
    s32 airborne;

    collision_flags = self->unk88.bytes.collision_flags;
    if (collision_flags & PLAYER_COLLIDE_GROUND) {
        self->attacking = 0;
        player_enter_land(self);
        return;
    }
    airborne = 0;
    if (self->input_locked != 0) {
        airborne = 1;
    }
    if (!(collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT))) {
        airborne = 1;
    }
    if (airborne) {
        self->attacking = 0;
        player_enter_fall(self);
        return;
    }
    if (player_check_wall_jump(self) != 0) {
        self->attacking = 0;
        return;
    }
    if (player_is_pushing_wall(self) != 0) {
        substate = self->unk6;
        if (substate == 0) {
            self->unk6 = substate + 1;
        } else {
            animate_object(ANIMATED_OBJECT(self));
        }
        player_zero_saber_on_event(self, 0x1F);
        if (self->animation_step.fields.event & 0x40) {
            self->attacking = 0;
            if (player_zero_check_wall_slash(self) != 0) {
                return;
            }
            self->attacking = 1;
        }
        move_object(MOVING_OBJECT(self));
        player_check_splash(self);
        if (self->animation_step.fields.relative_step == 0) {
            self->attacking = 0;
            player_set_animation(self, 0xF);
            self->unk5 = PLAYER_WALL_SLIDE;
            self->unk6 = 0;
        }
    } else {
        self->attacking = 0;
        func_80034B64(self);
    }
}

void player_zero_raijingeki(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    player_zero_saber_on_event(self, 0x20);
    if (self->animation_step.fields.event & 0x10) {
        self->animation_step.fields.event = 0;
        func_8001540C(1, 8, self);
        player_play_voice(self, 6);
    }
    if (self->input_locked == 0) {
        self->attacking = 0;
        if (player_check_dash_jump(self) != 0) {
            return;
        }
        if (self->animation_step.fields.event & 0x40) {
            if (player_zero_check_ground_technique(self) != 0) {
                return;
            }
            if (player_zero_check_saber(self) != 0) {
                return;
            }
            if (player_zero_check_ladder_or_walk(self) != 0) {
                return;
            }
        }
        self->attacking = 1;
    }
    player_zero_attack_finish(self);
}

void player_zero_hyouretsuzan(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    player_zero_hyouretsuzan_funcs[self->unk6](self);
}

void player_zero_hyouretsuzan_start(struct PlayerObj* self)
{
    player_zero_saber_on_event(self, 0x21);

    if (self->input_locked == 0) {
        if (self->input.buttons.held & PLAYER_INPUT_LEFT) {
            self->unk15 = 0;
        }
        if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
        }
    }

    if (self->animation_step.fields.event & 0x10) {
        self->animation_step.fields.event = 0;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = FIXED(-3);
        self->unk2C = FIXED(0.2578125);
        self->air_state = -1;
        self->unk6++;
    }
}

void player_zero_hyouretsuzan_drop(struct PlayerObj* self)
{
    struct MiscObj* debris;
    u32 i;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_set_animation(self, 0x62);
        i = 0;
        self->air_state = 0;
        self->dash_momentum = 0;
        self->air_action = 0;
        self->afterimage = 0;
        do {
            debris = find_free_misc_obj();
            if (debris != NULL) {
                debris->active = 0x21;
                debris->id = 0x2F;
                debris->unk2 = 0;
                debris->bg_offset = self->bg_offset;
                if (self->unk15 == 0) {
                    debris->x_pos.i.hi = self->x_pos.u.hi - 0x10;
                } else {
                    debris->x_pos.i.hi = self->x_pos.u.hi + 0x10;
                }
                debris->y_pos.i.hi = self->y_pos.i.hi;
            }
            i++;
        } while (i < 8);
        func_8001540C(0, 0x1A, self);
        self->unk6++;
        return;
    }

    self->attacking = 0;
    if (player_check_ladder_air(self) == 0 && player_check_wall(self) == 0 && player_check_air_move(self) == 0) {
        self->attacking = 1;
        self->x_vel.val = 0;
        if (self->input_locked == 0) {
            if (self->input.buttons.held & PLAYER_INPUT_LEFT) {
                self->x_vel.val = FIXED(-1.5);
            }
            if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
                self->x_vel.val = FIXED(1.5);
            }
        }
        move_with_gravity(ANIMATED_OBJECT(self));
        player_check_splash(self);
    }
}

void player_zero_hyouretsuzan_land(struct PlayerObj* self)
{
    if (self->input_locked == 0) {
        self->attacking = 0;
        if (player_check_dash_jump(self) != 0) {
            return;
        }
        if (self->animation_step.fields.event & 0x40) {
            if (player_zero_check_ground_technique(self) != 0 || player_zero_check_saber(self) != 0 || player_zero_check_ladder_or_walk(self) != 0) {
                return;
            }
        }
        self->attacking = 1;
    }
    player_zero_attack_finish(self);
}

void player_zero_ryuenjin(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    player_zero_ryuenjin_funcs[self->unk6](self);
}

void player_zero_ryuenjin_start(struct PlayerObj* self)
{
    u8 event;
    s32 scratch;

    player_zero_saber_on_event(self, 0x23);
    event = self->animation_step.fields.event;
    if (event & 0x20) {
        self->animation_step.fields.event = event & 0x1F;
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(4);
        } else {
            self->x_vel.val = -FIXED(4);
        }
        scratch = FIXED(6.75);
        self->y_vel.val = scratch;
        scratch = (u8)self->unk6;
        self->unk28 = -FIXED(0.25);
        self->unk2C = FIXED(0.2578125);
        self->spike_immune = 0;
        scratch += 1;
        self->unk6 = scratch;
    }
}

void player_zero_ryuenjin_rise(struct PlayerObj* self)
{
    if (player_leap_check_peak(self) == 0) {
        player_leap_check_wall(self);
        player_zero_ryuenjin_spawn_flame(self);
    }
}

void player_zero_ryuenjin_peak(struct PlayerObj* self)
{
    if (player_leap_check_peak(self) == 0) {
        player_zero_ryuenjin_spawn_flame(self);
    }
}

void player_zero_ryuenjin_fall(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        self->attacking = 0;
        player_enter_land(self);
        return;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        player_set_animation_frame(self, 0xB, 4);
        self->attacking = 0;
        self->unk5 = PLAYER_FALL;
        self->unk6 = 0;
    }
}

void player_zero_ryuenjin_spawn_flame(struct PlayerObj* self)
{
    struct MiscObj* obj;

    if (!(main_bss_state.frame_counter & 1)) {
        self->animation_step.fields.event &= 0xFE;
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x21;
            obj->id = 0x30;
            obj->unk2 = 0;
            obj->bg_offset = self->bg_offset;
        }
    }
}

void player_zero_rakuhouha(struct PlayerObj* self)
{
    u32 i;
    s32* sprite_frames;
    struct VisualObj* visual_obj;
    struct WeaponObj* weapon;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event & 0x80) {
        self->animation_step.fields.event = 0;
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x21;
            visual_obj->id = 3;
            visual_obj->unk2 = 0xD;
            visual_obj->bg_offset = self->bg_offset;
            sprite_frames = SP_SPRITE_FRAMES;
            visual_obj->unk3C = (u8*)sprite_frames + sprite_frames[6];
            visual_obj->animation_table = D_8011C018;
            visual_obj->unk40 = 0;
            visual_obj->unk42 = 0x7803;
            visual_obj->unk16 = 0;
            visual_obj->x_pos.val = self->x_pos.val;
            visual_obj->y_pos.val = self->y_pos.val;
            visual_obj->unk15 = self->unk15;
        }
    }
    if (self->animation_step.fields.event & 0x40) {
        self->animation_step.fields.event = 0;
        i = 0;
        do {
            weapon = find_free_weapon_obj();
            if (weapon != NULL) {
                weapon->active = 0x21;
                weapon->id = 0x24;
                weapon->unk2 = i;
                weapon->bg_offset = self->bg_offset;
            }
            i++;
        } while (i < 9);
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->attacking = 0;
        self->spike_immune = 0;
        player_enter_land_or_fall(self);
    }
}

void player_zero_saber_on_event(struct PlayerObj* self, s8 saber_id)
{
    s8 event;

    event = self->animation_step.fields.event;
    if (event & 0x80) {
        self->animation_step.fields.event = event & 0x7F;
        player_zero_spawn_saber(self, saber_id);
    }
}

void player_zero_spawn_saber(struct PlayerObj* self, s8 saber_id)
{
    struct WeaponObj* weapon;

    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = saber_id;
        weapon->unk2 = self->combo;
        weapon->bg_offset = self->bg_offset;
        weapon->unk84.word = self->unk17;
    }
}

void player_zero_shippuuga(struct PlayerObj* self)
{
    u8 side_mask;

    if (self->unk6 == 0) {
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    player_zero_saber_on_event(self, 0x1D);
    if (player_zero_shippuuga_cancel(self) == 0) {
        if (self->animation_step.fields.event & 0x20) {
            self->animation_step.fields.event = 0;
            self->x_vel.val = 0;
        }
        if (self->unk15 != 0) {
            side_mask = PLAYER_COLLIDE_RIGHT;
            if (self->x_vel.val < 0) {
                self->x_vel.val = 0;
            }
        } else {
            side_mask = PLAYER_COLLIDE_LEFT;
            if (self->x_vel.val > 0) {
                self->x_vel.val = 0;
            }
        }
        if (self->unk88.bytes.collision_flags & side_mask) {
            self->x_vel.val = 0;
        }
        if (self->x_vel.val != 0) {
            move_with_gravity(ANIMATED_OBJECT(self));
        }
        player_zero_attack_finish(self);
    }
}

s32 player_zero_shippuuga_cancel(struct PlayerObj* self)
{
    if (self->input_locked != 0 || !(self->animation_step.fields.event & 0x40)) {
        return 0;
    }

    self->attacking = 0;
    if (player_check_ladder(self) != 0 || player_zero_check_ground_technique(self) != 0 || player_check_dash_jump_walk(self) != 0) {
        return 1;
    }
    if (player_zero_check_saber(self) != 0) {
        return 1;
    }
    self->attacking = 1;
    return 0;
}
