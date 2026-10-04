// 80033414..800343A4
#include "common.h"

s32 player_check_hover(struct PlayerObj* self);
void player_clear_flash(struct PlayerObj* self);
void player_reset_actions(struct PlayerObj* self);
s32 player_zero_check_double_jump(struct PlayerObj* self);

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

u8 player_hurt_animations[8] = { 0, 0x21, 0x22, 0x24, 0x23, 0, 0, 0 };

struct PlayerHurtVelocity player_hurt_velocities[5] = {
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
    { 0xC000, 0, 0x2C000, 0x4200 },
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
};

u8 player_hurt_invincibility[8] = { 0, 0x4B, 0x64, 0, 0x4B, 0, 0, 0 };

u8 player_leap_fall_animations[2] = { 0x67, 0x66 };

static u16 s_PlayerEffectIdPad = 0;

s32 player_check_dash_jump_walk(struct PlayerObj* self)
{
    if (player_check_dash_input(self) != 0) {
        player_enter_dash(self);
        return 1;
    }
    if ((self->pressed_input & PLAYER_INPUT_JUMP) != 0) {
        player_enter_jump(self);
        return 1;
    }
    if (player_check_walk(self) != 0) {
        player_enter_walk(self);
        return 1;
    }
    return 0;
}

s32 player_check_dash_jump(struct PlayerObj* self)
{
    if (player_check_dash_input(self) != 0) {
        player_enter_dash(self);
        return 1;
    }
    if (self->pressed_input & PLAYER_INPUT_JUMP) {
        player_enter_jump(self);
        return 1;
    }
    return 0;
}

s32 player_check_walk_start(struct PlayerObj* self)
{
    if (self->input_locked) {
        return 0;
    }

    if (!(self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT))) {
        return 0;
    }

    if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            return 0;
        }
        self->x_vel.val = FIXED(0.5);
    } else {
        self->unk15 = 0;
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
            return 0;
        }
        self->x_vel.val = FIXED(-0.5);
    }

    return 1;
}

s32 player_check_walk(struct PlayerObj* self)
{
    u16 buttons;

    if (self->input_locked != 0) {
        return 0;
    }

    buttons = self->input.buttons.held;
    if ((buttons & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT)) == 0) {
        return 0;
    }

    if (buttons & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            return 0;
        }
        self->x_vel.val = FIXED(2);
    } else {
        self->unk15 = 0;
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
            return 0;
        }
        self->x_vel.val = FIXED(-2);
    }

    return 1;
}

void player_check_fall(struct PlayerObj* self)
{
    s8 action;

    action = self->unk5; // fake
    if ((self->unk5 != PLAYER_BEAM_IN) && (action != PLAYER_BEAM_OUT) && (self->air_state == 0) && (self->hurt_phase <= 0) && (self->ride_state >= 0) && (self->capsule_state == 0) && !(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND)) {
        if (self->unk2 != 0) {
            player_clear_attack(self);
        }
        player_enter_fall(self);
    }
}

s32 player_check_dash_input(struct PlayerObj* self)
{
    if (self->input_locked || (!self->double_tap_dash && !(self->pressed_input & PLAYER_INPUT_DASH))) {
        return 0;
    }

    if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
    }
    if (self->input.buttons.held & PLAYER_INPUT_LEFT) {
        self->unk15 = 0;
    }

    if (self->unk15 != 0) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            return 0;
        }
        self->x_vel.val = FIXED(6.5);
    } else {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
            return 0;
        }
        self->x_vel.val = FIXED(-6.5);
    }

    return 1;
}

void player_update_double_tap(struct PlayerObj* self)
{
    s8 action;

    self->double_tap_dash = 0;
    if ((self->input_locked == 0) && (action = self->unk5, (action != PLAYER_BEAM_IN)) && (action != PLAYER_BEAM_OUT)) {
        if (self->unk88.bytes.timer == 0) {
            self->double_tap_direction = self->pressed_input & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT);
            if (self->double_tap_direction != 0) {
                self->unk88.bytes.timer = 0xC;
            }
        } else {
            self->unk88.bytes.timer--;
            if (self->pressed_input & self->double_tap_direction) {
                self->double_tap_dash = 1;
                self->unk88.bytes.timer = 0;
            }
        }
    }
}

s32 player_dash_should_end(struct PlayerObj* self)
{
    s32 collision_side;
    u16 held;
    u8 timer;

    collision_side = self->unk15 != 0 ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT;
    if (collision_side & self->unk88.bytes.collision_flags) {
        return 1;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->x_vel.val <= FIXED(4.125) - 1) {
            self->x_vel.val = FIXED(4.125);
        }
    } else if (self->x_vel.val > FIXED(-4.125)) {
        self->x_vel.val = FIXED(-4.125);
    }

    timer = self->dash_timer - 1;
    self->dash_timer = timer;
    if ((timer << 24) == 0) {
        return 1;
    }

    held = self->input.buttons.held;
    if (!(held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT | PLAYER_INPUT_DASH))) {
        return 1;
    }
    if (self->unk15 != 0) {
        if (held & PLAYER_INPUT_LEFT) {
            return 1;
        }
    } else if (held & PLAYER_INPUT_RIGHT) {
        return 1;
    }
    return 0;
}

void player_check_capsule(struct PlayerObj* self)
{
    s32 play_turn;

    if (self->capsule_state > 0 && self->hurt_phase <= 0) {
        player_clear_attack(self);

        // maybe these can be combined? couldn't get a match
        play_turn = 0;
        if (self->unk17 == 5) {
            play_turn = 1;
        }
        if (self->unk17 == 6) {
            play_turn = 1;
        }
        if (self->unk17 == 0xC) {
            play_turn = 1;
        }
        if (play_turn) {
            player_set_animation(self, 0x26);
        }

        self->unk15 = 0x40;
        self->capsule_state = -1;
        self->afterimage = 0;
        self->unk5 = PLAYER_CAPSULE;
        self->unk6 = 0;
    }
}

void player_check_ride(struct PlayerObj* self)
{
    if (self->ride_state > 0) {
        player_clear_dash_and_attack(self);
        player_reset_charge_and_weapon(self);
        player_reset_weapon(self);
        self->unk68 = 0;
        self->air_state = 1;
        self->ride_state = -1;
        self->unk5 = PLAYER_RIDE;
        self->unk6 = 1;
    }
}

s32 player_check_air_move(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        return 0;
    }
    if (self->air_action != 0) {
        return 0;
    }
    if (self->unk2 == 0) {
        if (player_check_hover(self) != 0) {
            return 1;
        }
    } else if (player_zero_check_double_jump(self) != 0) {
        return 1;
    }

    if (self->unk2 == 0) {
        if (self->shot_cooldown != 0) {
            return 0;
        }
        if ((self->armor_parts & 8) == 0) {
            return 0;
        }
    } else if ((self->boss_flags & 0x10) == 0) {
        return 0;
    }

    if (player_check_dash_input(self) != 0) {
        player_enter_air_dash(self);
        return 1;
    }
    return 0;
}

s32 player_check_wall(struct PlayerObj* self)
{
    if (self->input_locked) {
        return 0;
    }

    if (!(self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT))) {
        return 0;
    }

    if (player_check_wall_jump(self)) {
        return 1;
    }

    if (player_is_pushing_wall(self)) {
        player_enter_wall_cling(self);
        return 1;
    }

    return 0;
}

s32 player_check_wall_jump(struct PlayerObj* self)
{
    if (self->input_locked == 0) {
        if (self->pressed_input & PLAYER_INPUT_JUMP) {
            if (self->wall_climbable > 0) {
                func_800349F4(self);
                return 1;
            }
        }
    }
    return 0;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/player_check", player_is_pushing_wall);
#else
s32 player_is_pushing_wall(struct PlayerObj* self)
{
    if ((self->input_locked != 0) || (self->wall_climbable == 0)) {
        return 0;
    }
    return (self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT) & self->unk88.bytes.collision_flags) != 0;
}
#endif

void player_check_damage(struct PlayerObj* self)
{
    s8 action;
    if (self->is_clone == 0 && (action = self->unk5, action != 0) && (action != PLAYER_BEAM_OUT)) {
        if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_CEILING | PLAYER_COLLIDE_GROUND)) == 0xC) {
            EASY_HP_SET(0);
            self->hp = -0x80;
        }
        if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT)) == 3) {
            EASY_HP_SET(0);
            self->hp = -0x80;
        }
        if (self->touching_spikes != 0 && self->invincibility_timer == 0 && self->spike_immune == 0) {
            EASY_HP_SET(0);
            self->hp = -0x80;
        }
        if (self->hp == -0x80) {
            EASY_HP_SET(0);
            self->hp = 0;
            engine_obj.unk1C = 1;
            player_reset_actions(self);
            player_reset_charge_and_weapon(self);
            self->unk68 = 0;
            self->unk54 = 0;
            self->state = PLAYER_STATE_DEATH;
            self->unk5 = 0;
            self->unk6 = 0;
            return;
        }
        if (self->invincibility_timer != 0) {
            self->invincibility_timer--;
            if (self->invincibility_timer == 0) {
                self->hurt_phase = 0;
                player_reset_palette(self);
                return;
            }
        }
        if (self->hp <= 0) {
            func_80033D54(self);
        }
    }
}

void player_reset_actions(struct PlayerObj* self)
{
    self->actions_reset = 1;
    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = 0;
    player_clear_attack(self);
    player_clear_flash(self);
}

// player_take_hit
INCLUDE_ASM("main/nonmatchings/player_check", func_80033D54);
u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

s32 player_check_ladder(struct PlayerObj* self)
{
    if (self->input_locked || self->shot_cooldown) {
        return 0;
    }
    if (self->input.buttons.held & PLAYER_INPUT_UP && func_8002D8B8(self) == 0x20) {
        player_enter_ladder_grab(self);
        return 1;
    }
    if (self->input.buttons.held & PLAYER_INPUT_DOWN && func_8002D94C(self) == 0x21) {
        player_enter_ladder_climb_on_top(self);
        return 1;
    }
    return 0;
}

s32 player_check_ladder_air(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        return 0;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_UP)) {
        return 0;
    }

    if (func_8002D994(self) == 0x20) {
        if (self->attacking) {
            player_enter_ladder_shoot(self);
        } else {
            player_set_animation(self, 0x1F);
            player_enter_ladder_up(self);
        }
        return 1;
    }
    return 0;
}

// player_check_ladder_end
INCLUDE_ASM("main/nonmatchings/player_check", func_80033FF0);
s32 player_check_off_ladder(struct PlayerObj* self)
{
    if (func_8002D994(self) != 0x20) {
        player_enter_fall(self);
        return 1;
    }

    return 0;
}

s32 player_check_script(struct PlayerObj* self)
{
    if (engine_obj.unkF != 0) {
        player_start_stage_clear(self);
        return 1;
    }

    if (self->script_state > 0) {
        func_80034E2C();
        return 1;
    }
    return 0;
}

void player_script_walk_to_mark(struct PlayerObj* self)
{
    s16 distance;
    s32 arrived;

    distance = (self->x_pos.u.hi - 0x40) - background_objects[self->bg_offset].x_pos.u.hi;
    arrived = 0;
    if (distance != 0) {
        if (distance > 0) {
            self->unk15 = 0;
            arrived = distance <= 2;
        } else {
            self->unk15 = 0x40;
            if (distance >= -2) {
                arrived = 1;
            }
        }
    } else {
        arrived = 1;
    }
    if (arrived != 0) {
        player_set_idle_animation(self);
        self->x_pos.i.hi = background_objects[self->bg_offset].x_pos.u.hi + 0x40;
        self->script_state = -1;
        self->unk15 = 0x40;
        self->unk5 = PLAYER_SCRIPT_WAIT;
    }
}

s32 player_leap_check_peak(struct PlayerObj* self)
{
    s32 result = 0;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) {
        result = 1;
        self->y_vel.val = 0;
    }

    if (self->y_vel.val <= 0) {
        result = 1;
    }

    if (result != 0) {
        s8 index = self->unk2;
        player_set_animation(self, player_leap_fall_animations[index]);

        if (self->unk2 != 0) {
            struct VisualObj* new_obj = find_free_visual_obj();
            if (new_obj != NULL) {
                new_obj->active = 1;
                new_obj->id = 0x27;
                new_obj->unk2 = 0;
                new_obj->bg_offset = self->bg_offset;
            }
        }

        self->x_vel.val = 0;
        self->unk28 = 0;
        self->air_state = -1;
        self->unk6 = 3;
        return 1;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        player_check_splash(self);
        return 0;
    }
}

void player_leap_check_wall(struct PlayerObj* self)
{
    u32 blocked;

    blocked = 0;
    if (self->unk15 != 0) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            blocked = 1;
        }
        if (self->x_vel.val <= 0) {
            blocked = 1;
        }
    } else {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT) {
            blocked = 1;
        }
        if (self->x_vel.val >= 0) {
            blocked = 1;
        }
    }
    if (blocked != 0) {
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->unk6++;
    }
}

void player_noop(void)
{
}
