// PlayerObj
// 800311EC..8003B3DC
#include "common.h"

struct PlayerHurtVelocity {
    s32 x_vel;
    s32 x_accel;
    s32 y_vel;
    s32 gravity;
};

void player_update(void)
{
    engine_obj.unk38 = &g_Player;
    if (g_Player.update_delay_request != 0) {
        g_Player.update_delay = 5;
        g_Player.update_delay_request = 0;
        return;
    }
    if (g_Player.update_delay == 0 || --g_Player.update_delay == 0) {
        g_Player.unk18.val = g_Player.x_pos.val;
        g_Player.unk1C.val = g_Player.y_pos.val;
        player_state_funcs[g_Player.state](&g_Player);
        soul_body_clone_update();
    }
}

void player_update_normal(struct PlayerObj* self)
{
    self->input_locked = self->script_state | engine_obj.unkF;
    self->input_locked |= self->capsule_state;
    self->unk88.bytes.collision_flags = self->unk70 | self->unk71;
    self->shot_fired = 0;
    self->attack_ended = 0;
    self->actions_reset = 0;

    if (engine_obj.unk10 == 0) {
        player_check_damage(self);
        if (self->hp == 0) {
            return;
        }

        if (self->shot_cooldown) {
            self->shot_cooldown--;
        }

        if (self->attack_pose_timer != 0) {
            self->attack_pose_timer--;
            if (!self->attack_pose_timer) {
                self->attack_ended = 1;
                self->attacking = 0;
            }
        }

        if (self->voice_timer > 0) {
            self->voice_timer--;
            if (!self->voice_timer) {
                self->voice_timer = -1;
            }
        }

        player_check_capsule(self);
        player_check_ride(self);
        player_update_double_tap(self);
        player_check_fall(self);
        player_update_weapon(self);

        player_normal_state_funcs[self->unk5](self);
        self->unk71 = 0;
        self->wall_climbable = 0;
    }
    player_update_charge(self);
    player_update_flash(self);
    player_update_frame_hitbox(self);
}

void player_beam_in(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->beam_in_delay != 0) {
            if (--self->beam_in_delay == 0) {
                player_set_collision_bounds(self);
            }
            move_object(MOVING_OBJECT(self));
            return;
        }
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
            player_set_animation(self, 2);
            self->air_state = 0;
            background_objects[0].unk44 = 1;
            background_objects[1].unk44 = 1;
            background_objects[2].unk44 = 1;
            self->unk6++;
            return;
        }
        move_object(MOVING_OBJECT(self));
        player_check_splash(self);
        return;
    }
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        self->armor_parts = engine_obj.unk47;
        self->arm_type = engine_obj.unk48;
    }
    if (self->animation_step.fields.relative_step == 0) {
        engine_obj.unk1C = 0;
        player_enter_idle(self);
    }
}

void player_beam_out(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            player_set_animation(self, 4);
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else {
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x40) == 0) {
            move_object(MOVING_OBJECT(self));
            player_check_splash(self);
            return;
        }
        self->on_screen = 0;
        self->state = PLAYER_STATE_INACTIVE;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void player_idle(struct PlayerObj* self)
{
    if (player_check_script(self) == 0 && player_check_ladder(self) == 0 && player_check_shoot(self) == 0 && player_zero_check_ground_technique(self) == 0 && player_check_dash_jump(self) == 0 && player_zero_check_saber(self) == 0) {
        if (player_check_walk_start(self) != 0) {
            player_enter_walk_start(self);
        } else {
            player_idle_animate(self);
        }
    }
}

void player_walk_start(struct PlayerObj* self)
{
    if ((player_check_script(self) == 0) && (player_check_ladder(self) == 0) && (player_check_shoot(self) == 0) && (player_zero_check_ground_technique(self) == 0) && (player_check_dash_jump(self) == 0) && (player_zero_check_saber(self) == 0)) {
        if (player_check_walk_start(self) != 0) {
            animate_object(ANIMATED_OBJECT(self));
            if (self->animation_step.fields.relative_step < 0) {
                player_enter_walk(self);
                return;
            }
            move_object(MOVING_OBJECT(self));
            func_80038568(self, 7);
            return;
        }
        player_enter_stand(self);
    }
}

void player_walk(struct PlayerObj* self)
{
    if (player_check_script(self) == 0 && player_check_ladder(self) == 0 && player_check_shoot(self) == 0 && player_zero_check_ground_technique(self) == 0 && player_check_dash_jump(self) == 0 && player_zero_check_saber(self) == 0) {
        if (player_check_walk(self) != 0) {
            animate_object(ANIMATED_OBJECT(self));
            move_object(MOVING_OBJECT(self));
            func_80038568(self, 8);
        } else {
            player_enter_stand(self);
        }
    }
}

void player_settle(struct PlayerObj* self)
{
    if ((player_check_script(self) == 0) && (player_check_ladder(self) == 0) && (player_zero_check_ground_technique(self) == 0) && (player_check_dash_jump(self) == 0) && (player_zero_check_saber(self) == 0)) {
        if (player_check_walk_start(self) != 0) {
            player_enter_walk_start(self);
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step < 0) {
            player_enter_idle(self);
        }
    }
}

void player_jump(struct PlayerObj* self)
{
    if (self->input_locked) {
        self->y_vel.val = 0;
    }
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) {
        self->y_vel.val = 0;
    }
    if (!(self->input.buttons.held & PLAYER_INPUT_JUMP)) {
        self->y_vel.val = 0;
    }
    if (player_check_shoot_air(self) == 0 && player_zero_check_jump_slash(self) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event & 0x80) {
            self->animation_step.fields.event &= 0x3F;
            func_8001540C(1, 1, self);
        }
        if (player_check_ladder_air(self) == 0) {
            if (self->unk8A.bytes.high == 0) {
                if (player_check_wall(self) != 0) {
                    return;
                }
            } else {
                self->unk8A.bytes.high--;
            }
            if (player_check_air_move(self) == 0) {
                player_air_steer(self);
                player_check_splash(self);
                if (self->y_vel.val <= 0) {
                    player_set_animation_shooting(self, 0xB);
                    self->air_state = -1;
                    self->unk5 = PLAYER_FALL;
                    self->unk6 = 0;
                } else {
                    func_80038568(self, 0xA);
                }
            }
        }
    }
}

void player_fall(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }

    if ((player_check_shoot_air(self) == 0) && (player_zero_check_fall_slash(self) == 0) && (player_check_ladder_air(self) == 0) && (player_check_wall(self) == 0) && (player_check_air_move(self) == 0)) {
        animate_object(ANIMATED_OBJECT(self));
        player_air_steer(self);
        player_check_splash(self);
        func_80038568(self, 0xB);
    }
}

void player_land(struct PlayerObj* self)
{
    if ((player_check_script(self) == 0) && (player_check_ladder(self) == 0) && (player_check_shoot(self) == 0) && (player_zero_check_ground_technique(self) == 0) && (player_check_dash_jump_walk(self) == 0) && (player_zero_check_saber(self) == 0)) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step < 0) {
            player_enter_stand(self);
        } else {
            func_80038568(self, 0xC);
        }
    }
}

void player_wall_cling(struct PlayerObj* self)
{
    s8 timer;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }
    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }
    if (player_check_shoot_air(self) != 0) {
        return;
    }
    if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT)) == 0) {
        player_enter_fall(self);
        return;
    }
    if (player_check_wall_jump(self) != 0) {
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event & 0x80) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
            self->unk15 = 0;
        } else {
            self->unk15 = 0x40;
        }
        self->animation_step.fields.event &= 0x3F;
    }

    timer = self->unk8A.bytes.low - 1;
    self->unk8A.bytes.low = timer;
    if (timer == 0) {
        player_enter_wall_slide(self);
        return;
    }
    func_80038568(self, 0xD);
}

void player_wall_jump(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        player_wall_jump_push(self);
    } else {
        player_wall_jump_rise(self);
    }
}

void player_wall_jump_push(struct PlayerObj* self)
{
    s32 should_end_state;
    s32 direction_mask;
    s32 vertical_mask;
    u8 collision_flags;
    s8 timer;

    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }

    if (player_check_shoot_air(self) != 0) {
        return;
    }

    collision_flags = self->unk88.bytes.collision_flags;
    vertical_mask = collision_flags & PLAYER_COLLIDE_CEILING;
    should_end_state = vertical_mask != 0;
    if (self->unk15 != 0) {
        direction_mask = collision_flags & PLAYER_COLLIDE_LEFT;
    } else {
        direction_mask = collision_flags & PLAYER_COLLIDE_RIGHT;
    }
    if (direction_mask != 0) {
        should_end_state = 1;
    }

    if (should_end_state != 0) {
        player_enter_fall(self);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    player_check_splash(self);

    timer = self->unk8A.bytes.low - 1;
    self->unk8A.bytes.low = timer;
    if (timer == 0) {
        self->x_vel.val = 0;
        self->unk6++;
        return;
    }

    func_80038568(self, 0xE);
}

void player_wall_jump_rise(struct PlayerObj* self)
{
    if (self->input_locked != 0) {
        self->y_vel.val = 0;
    }
    if ((self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) != 0) {
        self->y_vel.val = 0;
    }
    if ((self->input.buttons.held & PLAYER_INPUT_JUMP) == 0) {
        self->y_vel.val = 0;
    }
    if ((player_check_shoot_air(self) == 0) && (player_zero_check_jump_slash(self) == 0) && (player_check_ladder_air(self) == 0) && (player_check_wall(self) == 0) && (player_check_air_move(self) == 0)) {
        animate_object(ANIMATED_OBJECT(self));
        player_air_steer(self);
        player_check_splash(self);
        if (self->y_vel.val <= 0) {
            player_set_animation_shooting(self, 0xB);
            self->air_state = -1;
            self->unk5 = PLAYER_FALL;
            self->unk6 = 0;
            return;
        }
        func_80038568(self, 0xE);
    }
}

void player_wall_slide_down(struct PlayerObj* self);

void player_wall_slide_release(struct PlayerObj* self);

void player_wall_slide(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        player_wall_slide_down(self);
    } else {
        player_wall_slide_release(self);
    }
}

void player_wall_slide_down(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }

    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }
    if (player_check_shoot_air(self) != 0) {
        return;
    }
    if (player_zero_check_wall_slash(self) != 0) {
        return;
    }
    if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT)) == 0) {
        player_enter_fall(self);
        return;
    }

    if (player_check_wall_jump(self) != 0) {
        return;
    }
    if (player_is_pushing_wall(self) != 0) {
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        player_check_splash(self);
        func_80038568(self, 0xF);
        return;
    }
    func_80034B64(self);
}

void player_wall_slide_release(struct PlayerObj* self)
{
    s8 timer;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }
    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }
    if ((player_check_shoot_air(self) == 0) && (player_zero_check_fall_slash(self) == 0)) {
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        player_check_splash(self);
        timer = self->unk8A.bytes.low - 1;
        self->unk8A.bytes.low = timer;
        if (timer == 0) {
            self->x_vel.val = 0;
            self->unk5 = PLAYER_FALL;
            self->unk6 = 0;
            return;
        }
        func_80038568(self, 0xB);
    }
}

void player_dash(struct PlayerObj* self)
{
    if (player_check_script(self) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        player_dash_funcs[self->unk6](self);
    }
}

void player_dash_start(struct PlayerObj* self)
{
    s8 event;
    u8 unsigned_event;

    if ((player_check_shoot(self) == 0) && (player_zero_check_ground_technique(self) == 0)) {
        if (self->pressed_input & PLAYER_INPUT_JUMP) {
            player_enter_jump(self);
            return;
        }
        if (player_zero_check_saber(self) == 0) {
            unsigned_event = self->animation_step.fields.event;
            if (unsigned_event & 0x20) {
                self->animation_step.fields.event = unsigned_event & 0xF;
                player_spawn_dash_spark(self);
            }
            event = self->animation_step.fields.event;
            if (event & 0x80) {
                self->animation_step.fields.event = event & 0xF;
                func_8001540C(1, 5, self);
                self->afterimage = 1;
                self->unk6++;
                return;
            }
            func_80038568(self, 0x10);
        }
    }
}

void player_dash_move(struct PlayerObj* self)
{
    u8 event;

    if ((player_check_shoot(self) == 0) && (player_zero_check_shippuuga(self) == 0)) {
        if (self->pressed_input & PLAYER_INPUT_JUMP) {
            player_enter_jump(self);
            return;
        }
        if (player_zero_check_saber(self) == 0) {
            if (player_dash_should_end(self) != 0) {
                player_enter_dash_end(self);
                return;
            }
            event = self->animation_step.fields.event;
            if (event & 0x40) {
                self->animation_step.fields.event = event & 0xF;
                player_spawn_dash_dust(self);
            }
            if (!(self->dash_timer & 3)) {
                player_spawn_dash_splash(self);
            }
            func_80038568(self, 0x10);
        }
    }
}

void player_dash_end(struct PlayerObj* self)
{
    s32 wall_flag;
    s8 event;

    if (player_check_ladder(self) == 0 && player_check_shoot(self) == 0 && player_zero_check_ground_technique(self) == 0 && player_check_dash_jump_walk(self) == 0 && player_zero_check_saber(self) == 0) {
        event = self->animation_step.fields.event;
        if (event & 0x80) {
            self->animation_step.fields.event = event & 0x7F;
            func_8001540C(1, 6, self);
        }
        if ((self->animation_step.fields.event & 0x40) && self->dash_timer == 0) {
            wall_flag = PLAYER_COLLIDE_LEFT;
            if (self->unk15 != 0) {
                wall_flag = PLAYER_COLLIDE_RIGHT;
            }
            if (wall_flag & self->unk88.bytes.collision_flags) {
                self->x_vel.val = 0;
            }
            if (self->x_vel.val != 0) {
                move_with_gravity(ANIMATED_OBJECT(self));
                if (self->unk15 != 0) {
                    if (self->x_vel.val < 0) {
                        self->x_vel.val = 0;
                    }
                } else if (self->x_vel.val > 0) {
                    self->x_vel.val = 0;
                }
            }
        }
        if (self->animation_step.fields.relative_step < 0) {
            player_enter_idle(self);
            return;
        }
        func_80038568(self, 0x11);
    }
}

void player_air_dash(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
    } else if (self->input_locked != 0) {
        player_enter_fall(self);

    } else if (self->unk2 == 0) {
        if (player_check_shoot_air(self) == 0) {
            if (self->attacking != 0) {
                player_enter_fall_shooting(self);
            } else {
                animate_object(ANIMATED_OBJECT(self));
                player_air_dash_funcs[self->unk6](self);
            }
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        player_air_dash_funcs[self->unk6](self);
    }
}

void player_air_dash_start(struct PlayerObj* self)
{
    s8 event;
    u8 raw_event;

    if (player_zero_check_fall_slash(self) != 0) {
        self->unk2C = FIXED(0.2578125);
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->air_state = -1;
        self->dash_momentum = 0;
        return;
    }

    raw_event = (u8)self->animation_step.fields.event;
    if (raw_event & 0x40) {
        self->animation_step.fields.event = raw_event & 0x3F;
        player_spawn_dash_dust(self);
    }

    event = self->animation_step.fields.event;
    if (event & 0x80) {
        self->animation_step.fields.event = event & 0x3F;
        func_8001540C(1, 5, self);
        self->afterimage = 1;
        self->unk6 = (u8)self->unk6 + 1;
    }
}

void player_air_dash_move(struct PlayerObj* self)
{
    u8 event;

    if (player_zero_check_fall_slash(self) != 0) {
        self->unk2C = FIXED(0.2578125);
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->air_state = -1;
        self->dash_momentum = 0;
    } else if (player_dash_should_end(self) != 0) {
        player_enter_air_dash_end(self);
    } else {
        event = self->animation_step.fields.event;
        if (event & 0x40) {
            self->animation_step.fields.event = event & 0x3F;
            player_spawn_dash_dust(self);
        }
    }
}

void player_air_dash_end(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }
    if (player_zero_check_fall_slash(self) != 0) {
        self->unk2C = FIXED(0.2578125);
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->air_state = -1;
        self->dash_momentum = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    player_check_splash(self);
    if ((self->animation_step.fields.relative_step < 0) || (self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT))) {
        player_set_animation(self, 0x14);
        self->unk5 = PLAYER_FALL;
        self->unk6 = 0;
    }
}

void player_ladder_transition(struct PlayerObj* self)
{
    player_ladder_transition_funcs[self->unk6](self);
}

void player_ladder_grab(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        player_set_animation(self, 0x1F);
        player_enter_ladder_up(self);
    }
}

void player_ladder_climb_off_top(struct PlayerObj* self)
{
    u16 y;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event & 0x80) {
        y = self->y_pos.u.hi;
        self->animation_step.fields.event = 0;
        self->y_pos.i.hi = y - 0x10;
        self->unk1C.i.hi = y - 0x20;
        player_set_collision_bounds(self);
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->air_state = 0;
        player_enter_stand(self);
    }
}

void player_ladder_climb_on_top(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event & 0x80) {
        self->animation_step.fields.event = 0;
        self->y_pos.i.hi = (self->y_pos.u.hi & 0xFFF0) + 0x20;
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->y_pos.i.hi = self->y_pos.u.hi + 0x10;
        player_set_collision_bounds(self);
        player_set_animation_frame(self, 0x20, 3);
        player_enter_ladder_down(self);
    }
}

void player_ladder_step_off_bottom(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        self->air_state = 0;
        player_enter_stand(self);
    }
}

void player_ladder_let_go(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        player_enter_fall(self);
    }
}

void player_ladder_up(struct PlayerObj* self)
{
    u16 buttons;
    u8 duration;

    if ((func_80033FF0(self) == 0) && (player_check_shoot_ladder(self) == 0) && (player_zero_check_ladder_slash(self) == 0)) {
        if (self->pressed_input & PLAYER_INPUT_LEFT) {
            self->unk15 = 0;
        }
        if (self->pressed_input & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
        }
        buttons = self->input.buttons.held;
        if (buttons & PLAYER_INPUT_UP) {
            animate_object(ANIMATED_OBJECT(self));
            move_object(MOVING_OBJECT(self));
            return;
        }
        if (buttons & PLAYER_INPUT_DOWN) {
            duration = self->animation_step.fields.duration;
            player_set_animation_frame(self, 0x20, self->animation_step.fields.event);
            self->animation_step.fields.duration = duration;
            player_enter_ladder_down(self);
        }
    }
}

void player_ladder_down(struct PlayerObj* self)
{
    u16 buttons;
    s8 duration;

    if ((func_80033FF0(self) == 0) && (player_check_shoot_ladder(self) == 0) && (player_zero_check_ladder_slash(self) == 0)) {
        if (self->pressed_input & PLAYER_INPUT_LEFT) {
            self->unk15 = 0;
        }
        if (self->pressed_input & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
        }

        buttons = self->input.buttons.held;
        if (buttons & PLAYER_INPUT_UP) {
            duration = self->animation_step.fields.duration;
            player_set_animation_frame(self, 0x1F, self->animation_step.fields.event);
            self->animation_step.fields.duration = duration;
            player_enter_ladder_up(self);
            return;
        }
        if (buttons & PLAYER_INPUT_DOWN) {
            animate_object(ANIMATED_OBJECT(self));
            move_object(MOVING_OBJECT(self));
        }
    }
}

void player_hurt(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    player_hurt_funcs[self->hurt_type](self);
}

void player_hurt_slide(struct PlayerObj* self);

void player_hurt_knockback(struct PlayerObj* self)
{
    player_hurt_slide(self);
    if (self->unk2 == 0) {
        if (self->animation_step.fields.frame_index == 0xEC) {
            player_set_palette(self, 0x49);
        } else {
            player_reset_palette(self);
        }
    }
    if (self->invincibility_timer == 0x3C) {
        player_enter_land_or_fall(self);
        if (self->input_locked != 0) {
            self->hurt_phase = 0;
            self->invincibility_timer = 0;
            return;
        }
        player_check_low_hp_alarm(self);
        self->hurt_phase = -1;
    }
}

void player_hurt_launch(struct PlayerObj* self)
{
    s8 substate;

    player_hurt_slide(self);
    player_check_splash(self);
    substate = self->unk6;
    if (substate == 0) {
        self->unk6 = substate + 1;
        return;
    }
    if ((self->air_state != 0) && (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND)) {
        self->air_state = 0;
        if (self->unk15 != 0) {
            self->x_vel.val = FIXED(-0.5);
        } else {
            self->x_vel.val = FIXED(0.5);
        }
        self->y_vel.val = 0;
        self->unk2C = 0;
    }
    if (self->invincibility_timer == 0x3C) {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
            self->air_state = 0;
            player_enter_idle(self);
        } else if (self->unk2C != 0) {
            player_set_animation(self, 0xB);
            self->air_state = -1;
            self->unk5 = PLAYER_FALL;
            self->unk6 = 0;
        } else {
            player_enter_fall(self);
        }
        if (self->input_locked != 0) {
            self->hurt_phase = 0;
            self->invincibility_timer = 0;
            return;
        }
        player_check_low_hp_alarm(self);
        self->hurt_phase = -1;
    }
}

void player_hurt_stun(struct PlayerObj* self)
{
    s8 stun;
    s8 next_stun;

    if (self->input.buttons.held & PLAYER_INPUT_LEFT) {
        self->unk15 = 0;
    }
    if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
        self->unk15 = 0x40;
    }

    stun = self->stun_timer;
    if (stun > 0) {
        return;
    }
    if (stun == 0) {
        self->hurt_phase = 0;
        player_enter_land_or_fall(self);
        return;
    }

    if (stun == -1) {
        player_set_animation(self, 0x25);
        next_stun = -2;
    } else if (self->animation_step.fields.relative_step < 0) {
        player_set_animation(self, 0x24);
        next_stun = 1;
    } else {
        return;
    }
    self->stun_timer = next_stun;
}

void player_hurt_slide(struct PlayerObj* self)
{
    s32 velocity;
    s32 direction;

    if (self->capsule_state != 0) {
        return;
    }

    velocity = self->x_vel.val;
    if (velocity != 0) {
        direction = PLAYER_COLLIDE_LEFT;
        if (velocity > 0) {
            direction = PLAYER_COLLIDE_RIGHT;
        }
        if ((direction & self->unk88.bytes.collision_flags) != 0) {
            self->x_vel.val = 0;
            self->unk28 = 0;
        }
    }

    move_with_gravity(ANIMATED_OBJECT(self));

    if (self->unk15 != 0) {
        if (self->x_vel.val <= 0) {
            return;
        }
    } else if (self->x_vel.val >= 0) {
        return;
    }

    self->x_vel.val = 0;
    self->unk28 = 0;
}

void player_ride(struct PlayerObj* self)
{
    if (engine_obj.unkF != 0) {
        player_start_stage_clear(self);
        return;
    }
    if ((self->script_state > 0) && (self->script_action == 0x17)) {
        func_80034E2C(self);
        return;
    }
    if (self->ride_state == 0) {
        player_set_collision_bounds(self);
        player_enter_jump(self);
        self->air_action = 1;
        return;
    }
    if (self->unk6 == 0) {
        player_set_animation(self, (u8)self->ride_animation);
        self->unk6++;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void player_capsule(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        func_80032FA4(self);
    } else {
        player_capsule_fall(self);
    }
}

// player_capsule_enter
INCLUDE_ASM("main/nonmatchings/player", func_80032FA4);

void player_capsule_fall(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        player_enter_land(self);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    player_check_splash(self);
}

void player_script_wait(struct PlayerObj* self)
{
    if (player_check_script(self) == 0) {
        if (self->script_state == 0) {
            self->unk5 = PLAYER_IDLE;
            self->unk6 = 0;
        } else {
            animate_object(ANIMATED_OBJECT(self));
        }
    }
}

// player_script_walk
INCLUDE_ASM("main/nonmatchings/player", func_80033108);

void player_script_vanish(struct PlayerObj* self)
{
    if (player_check_script(self) == 0 && self->unk6 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            self->on_screen = 0;
            self->unk6++;
        }
    }
}

void player_script_jump(struct PlayerObj* self)
{
    if (self->unk6 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_vel.val <= 0) {
            player_set_animation(self, 0xB);
            self->air_state = -1;
            self->y_vel.val = 0;
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else {
        if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
            self->script_state = 0;
            player_enter_land(self);
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
    }
}

void player_script_victory(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

    if (self->unk6 == 0) {
        if (self->item_step == 4) {
            player_set_animation(self, 0x27);
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else {
        if (self->animation_step.fields.event & 0x80) {
            self->animation_step.fields.event = 0;
            func_8001540C(0, 0x21, 0);
        }

        if (self->animation_step.fields.relative_step == 0) {
            player_end_script_action();
            player_enter_idle(self);
        }
    }
}

void player_stage_clear(struct PlayerObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (D_80173C84 == 0) {
            player_set_animation(self, 0x27);
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else {
        if (self->animation_step.fields.event & 0x80) {
            self->animation_step.fields.event = 0;
            func_8001540C(0, 0x21, 0);
        }
        if (self->animation_step.fields.relative_step == 0) {
            player_set_animation(self, 0x28);
            player_enter_beam_out(self);
        }
    }
}

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
    if (player_check_walk(self) == 0) {
        return 0;
    }
    player_enter_walk(self);
    return 1;
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
        if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT)) {
            self->x_vel.val = FIXED(0.5);
            return 1;
        } else {
            return 0;
        }
    }

    self->unk15 = 0;
    if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT)) {
        self->x_vel.val = FIXED(-0.5);
        return 1;
    } else {
        return 0;
    }
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
        if ((self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT)) {
            return 0;
        } else {
            self->x_vel.val = FIXED(6.5);
            return 1;
        }
    } else if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT)) {
        self->x_vel.val = FIXED(-6.5);
        return 1;
    } else {
        return 0;
    }
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

    collision_side = PLAYER_COLLIDE_LEFT;
    if (self->unk15 != 0) {
        collision_side = PLAYER_COLLIDE_RIGHT;
    }
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

s32 player_is_pushing_wall(struct PlayerObj* self)
{
    if ((self->input_locked != 0) || (self->wall_climbable == 0)) {
        return 0;
    }
    return (self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT) & self->unk88.bytes.collision_flags) != 0;
}

void player_check_damage(struct PlayerObj* self)
{
    s8 action;
    if (self->is_clone == 0 && (action = self->unk5, action != 0) && (action != PLAYER_BEAM_OUT)) {
        if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_CEILING | PLAYER_COLLIDE_GROUND)) == 0xC) {
            self->hp = -0x80;
        }
        if ((self->unk88.bytes.collision_flags & (PLAYER_COLLIDE_RIGHT | PLAYER_COLLIDE_LEFT)) == 3) {
            self->hp = -0x80;
        }
        if (self->touching_spikes != 0 && self->invincibility_timer == 0 && self->spike_immune == 0) {
            self->hp = -0x80;
        }
        if (self->hp == -0x80) {
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
INCLUDE_ASM("main/nonmatchings/player", func_80033D54);

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
    if (self->input_locked != 0 || !(self->input.buttons.held & PLAYER_INPUT_UP)) {
        return 0;
    }

    if (func_8002D994(self) == 0x20) {
        if (self->attacking) {
            player_enter_ladder_shoot(self);
            return 1;
        }
        player_set_animation(self, 0x1F);
        player_enter_ladder_up(self);
        return 1;
    }
    return 0;
}

// player_check_ladder_end
INCLUDE_ASM("main/nonmatchings/player", func_80033FF0);

s32 player_check_off_ladder(struct PlayerObj* self)
{
    if (func_8002D994(self) == 0x20) {
        return 0;
    }

    player_enter_fall(self);
    return 1;
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
    u16 camera_x;
    s32 arrived;

    distance = (self->x_pos.u.hi - 0x40) - background_objects[self->bg_offset].x_pos.u.hi;
    arrived = 0;
    if (distance != 0) {
        if (distance > 0) {
            self->unk15 = 0;
            arrived = distance < 3;
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
        camera_x = background_objects[self->bg_offset].x_pos.u.hi;
        self->script_state = -1;
        self->unk15 = 0x40;
        self->unk5 = PLAYER_SCRIPT_WAIT;
        self->x_pos.i.hi = camera_x + 0x40;
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

        self->air_state = -1;
        self->x_vel.val = 0;
        self->unk28 = 0;
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
    s32 blocked;

    blocked = 0;
    if (self->unk15 != 0) {
        blocked = self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT;
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

void player_enter_idle(struct PlayerObj* self)
{
    s32 frame; // ???

    if (player_check_script(self) == 0) {
        self->unk5 = PLAYER_IDLE;
        self->unk6 = 0;
        if ((self->unk2 == 0) && (self->attacking != 0)) {
            frame = self->attack_pose_timer < 9;
            if (self->attack_pose_timer < 5) {
                frame = 2;
            }
            player_set_animation_frame(self, 0x5E, frame);
            if (self->attack_pose_timer >= 9) {
                self->animation_step.fields.duration = self->attack_pose_timer - 8;
            }
        } else {
            player_set_idle_animation(self);
        }
    }
}

void player_enter_stand(struct PlayerObj* self)
{
    if (player_check_script(self) == 0) {
        if (self->unk2 == 0) {
            player_enter_idle(self);
        } else {
            player_set_animation(self, 9);
            self->unk5 = PLAYER_SETTLE;
            self->unk6 = 0;
        }
    }
}

void player_enter_walk_start(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 7);
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    move_object((struct MovingObj*)self);
    self->unk5 = PLAYER_WALK_START;
    self->unk6 = 0;
}

void player_enter_walk(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 8);
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    move_object((struct MovingObj*)self);
    self->unk5 = PLAYER_WALK;
    self->unk6 = 0;
}

void player_enter_jump(struct PlayerObj* self)
{
    self->y_vel.val = FIXED(5.8125);
    self->air_state = 1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0x4200;
    if ((self->dash_momentum != 0) || ((self->input.buttons.held & PLAYER_INPUT_DASH) != 0)) {
        self->dash_momentum = 1;
        self->air_action = 2;
        self->afterimage = 1;
    }
    self->unk8A.bytes.high = 0xA;
    player_set_animation_shooting(self, 0xA);
    player_play_voice(self, player_jump_voices[self->unk2][get_random() & 3]);
    player_air_steer(self);
    self->unk5 = PLAYER_JUMP;
    self->unk6 = 0;
}

void player_enter_fall(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0xB);
    self->unk2C = 0x4200;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->air_state = -1;
    if (self->dash_momentum != 0) {
        self->dash_momentum = 0;
        self->afterimage = -1;
    }
    self->unk5 = PLAYER_FALL;
    self->unk6 = 0;
}

void player_enter_land(struct PlayerObj* self)
{
    func_8001540C(1, 2, self);
    self->air_state = 0;
    player_clear_dash(self);
    if ((player_check_script(self) == 0) && (player_check_shoot(self) == 0) && (player_zero_check_ground_technique(self) == 0) && (player_check_dash_jump_walk(self) == 0) && (player_zero_check_saber(self) == 0)) {
        player_set_animation_shooting(self, 0xC);
        self->unk5 = PLAYER_LAND;
        self->unk6 = 0;
    }
}

void player_enter_land_or_fall(struct PlayerObj* self)
{
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_GROUND) {
        self->air_state = 0;
        self->air_action = 0;
        player_enter_idle(self);
    } else {
        player_enter_fall(self);
    }
}

void player_enter_dash(struct PlayerObj* self)
{
    self->dash_momentum = 1;
    self->air_action = 1;
    if (self->pressed_input & PLAYER_INPUT_JUMP) {
        player_enter_jump(self);
        return;
    }
    player_set_animation_shooting(self, 0x10);
    self->unk28 = FIXED(-0.1875);
    self->dash_timer = 0x1E;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk5 = PLAYER_DASH;
    self->unk6 = 0;
}

void player_enter_dash_end(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0x11);
    stop_sound(1, 5);
    if (self->unk15 != 0) {
        self->x_vel.val = FIXED(4.125);
    } else {
        self->x_vel.val = FIXED(-4.125);
    }
    self->unk28 = FIXED(-0.1875);
    self->afterimage = -1;
    self->dash_momentum = 0;
    self->air_action = 0;
    self->unk6 = 2;
}

void player_enter_air_dash(struct PlayerObj* self)
{
    player_set_animation(self, 0x12);
    self->unk28 = FIXED(-0.1875);
    self->dash_momentum = -1;
    self->dash_timer = 0x12;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->air_action = 3;
    player_clear_attack(self);
    self->unk5 = PLAYER_AIR_DASH;
    self->unk6 = 0;
}

void player_enter_air_dash_end(struct PlayerObj* self)
{
    player_set_animation(self, 0x13);
    self->unk2C = FIXED(0.2578125);
    self->air_state = -1;
    self->afterimage = -1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->dash_momentum = 0;
    self->unk6 = 2;
}

void player_enter_fall_shooting(struct PlayerObj* self)
{
    player_set_animation(self, 0x84);
    self->unk2C = FIXED(0.2578125);
    self->air_state = -1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->dash_momentum = 0;
    self->afterimage = 0;
    self->unk5 = PLAYER_FALL;
    self->unk6 = 0;
}

void player_enter_wall_cling(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0xD);
    func_8001540C(1, 4, self);
    self->afterimage = -1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_momentum = 0;
    self->air_action = 0;
    self->unk8A.bytes.low = 8;
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
    self->unk5 = PLAYER_WALL_CLING;
    self->unk6 = 0;
}

// player_enter_wall_jump
INCLUDE_ASM("main/nonmatchings/player", func_800349F4);

void player_enter_wall_slide(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0xF);
    player_spawn_wall_slide_dust(self);
    self->air_state = -1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(-1.4375);
    self->unk2C = 0;
    player_clear_dash(self);
    self->unk5 = PLAYER_WALL_SLIDE;
    self->unk6 = 0;
}

// player_enter_wall_slide_release
INCLUDE_ASM("main/nonmatchings/player", func_80034B64);

void player_enter_ladder_grab(struct PlayerObj* self)
{
    player_set_animation(self, 0x1B);
    self->y_vel.val = FIXED(1);
    self->x_pos.u.lo = 0;
    self->y_pos.u.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->air_state = 1;
    self->x_pos.u.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    player_clear_dash(self);
    player_clear_attack(self);
    self->unk5 = PLAYER_LADDER_TRANSITION;
    self->unk6 = 0;
}

void player_enter_ladder_climb_off_top(struct PlayerObj* self)
{
    player_set_animation(self, 0x1C);
    self->unk68 = 0;
    self->y_pos.u.lo = 0;
    self->y_pos.u.hi &= 0xFFF0;
    player_clear_attack(self);
    self->unk5 = PLAYER_LADDER_TRANSITION;
    self->unk6 = 1;
}

void player_enter_ladder_climb_on_top(struct PlayerObj* self)
{
    player_set_animation(self, 0x1D);
    self->x_pos.u.lo = 0;
    self->y_pos.u.lo = 0;
    self->unk68 = 0;
    self->air_state = 1;
    self->x_pos.u.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    player_clear_dash(self);
    player_clear_attack(self);
    self->unk5 = PLAYER_LADDER_TRANSITION;
    self->unk6 = 2;
}

void player_enter_ladder_step_off_bottom(struct PlayerObj* self)
{
    player_set_animation(self, 0x1E);
    player_clear_attack(self);
    self->unk5 = PLAYER_LADDER_TRANSITION;
    self->unk6 = 3;
}

void player_enter_ladder_up(struct PlayerObj* self)
{
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(1.5);
    self->unk2C = 0;
    self->x_pos.u.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    player_clear_dash(self);
    self->unk5 = PLAYER_LADDER_UP;
    self->unk6 = 0;
}

void player_enter_ladder_down(struct PlayerObj* self)
{
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(-1.5);
    self->unk2C = 0;
    self->x_pos.u.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    player_clear_dash(self);
    self->unk5 = PLAYER_LADDER_DOWN;
    self->unk6 = 0;
}

// player_start_script
INCLUDE_ASM("main/nonmatchings/player", func_80034E2C);

void player_start_stage_clear(struct PlayerObj* self)
{
    u8 flags;
    u8 sound_id;
    u8 sound_arg;

    player_clear_dash_and_attack(self);
    player_reset_charge_and_weapon(self);

    flags = engine_obj.unkF;
    engine_obj.unk1C = 1;

    if (flags & 0x10) {
        player_set_idle_animation(self);
        player_reset_weapon(self);

        sound_id = MUSIC_STAGE_CLEAR_ZERO;
        if (self->unk2 == 0) {
            sound_id = MUSIC_STAGE_CLEAR_X;
            sound_arg = 0x75;
        } else {
            sound_arg = 0x72;
        }
        func_8001663C(sound_id, sound_arg);

        self->unk5 = PLAYER_STAGE_CLEAR;
        self->unk6 = 0;
        return;
    }

    if (flags & 0x40) {
        self->state = PLAYER_STATE_INACTIVE;
        self->unk5 = 0;
        self->unk6 = 0;
        return;
    }

    player_set_animation(self, 3);
    player_reset_weapon(self);
    player_enter_beam_out(self);
}

void player_enter_beam_out(struct PlayerObj* self)
{
    func_8001540C(1, 0xB, self);
    self->y_vel.val = FIXED(8);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk68 = 0;
    self->air_state = 1;
    self->unk5 = PLAYER_BEAM_OUT;
    self->unk6 = 0;
}

s32 player_set_animation(struct PlayerObj* self, s32 animation)
{
    if (self->unk2 == 0) {
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 0);
    } else if (D_8011AF60[animation] == 0) {
        self->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 0);
    } else {
        self->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, 1);
        self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 5);
    }

    return set_animation(self, animation);
}

void player_set_animation_frame(struct PlayerObj* self, s32 animation, s32 frame)
{
    s32* x_gfx;
    s32* zero_gfx;
    s32* zero_saber_gfx;
    s32* x_frames;
    s32* zero_frames;
    s32* zero_saber_frames;
    if (self->unk2 == 0) {
        x_gfx = SP_PLAYER_GFX;
        x_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(x_gfx, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(x_frames, 0);
    } else if (D_8011AF60[animation] == 0) {
        zero_gfx = SP_PLAYER_GFX;
        zero_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(zero_gfx, 0);
        self->unk3C = SP_ARCHIVE_ENTRY(zero_frames, 0);
    } else {
        zero_saber_gfx = SP_PLAYER_GFX;
        zero_saber_frames = SP_SPRITE_FRAMES;
        self->unk38 = SP_ARCHIVE_ENTRY(zero_saber_gfx, 1);
        self->unk3C = SP_ARCHIVE_ENTRY(zero_saber_frames, 5);
    }

    set_animation_frame(ANIMATED_OBJECT(self), animation, frame);
}

extern s16 player_afterimage_cluts[];

void player_spawn(void)
{
    struct PlayerObj* player = &g_Player;
    struct EngineObj* engine = &engine_obj;
    struct UnkObj* object;
    struct UnkObj* active_object;
    struct UnkObj* previous;
    struct BazObj* baz;
    struct VisualObj* visual;
    struct MiscObj* misc;
    s32* sprite_frames;
    s8* initial_data;
    s8* player_data;
    s32 frame_offset;
    u32 i;

    player->active = 1;
    player->unk2 = engine->cur_character;
    player->on_screen = 0;
    player->bg_offset = 0;
    player->is_clone = 0;
    player->boss_flags = engine->palette_flags;

    switch (engine->unk1E) {
    case 0:
        i = 0;
    case -2:
        i = 0;
        player->hp = engine->unk46;
        player->hud_hp = engine->unk46;
        player->unk5E = engine->unk46;
        do {
            player->weapon_energy[i++] = 0x30;
        } while (i < 0x10);
        break;

    case -1:
        player_data = player->weapon_energy;
        initial_data = engine->player_initial_data;
        i = 0;
        player->hp = engine->unk45;
        player->hud_hp = engine->unk45;
        player->unk5E = engine->unk45;
        do {
            *player_data++ = *initial_data++;
            i++;
        } while (i < 0x10);
        player->weapon = engine->unk60;
        player_equip_weapon(player);
        player_update_shot_types(player);
        break;
    }

    if (player->unk2 == 0) {
        player->animation_table = D_80119DF0;
    } else {
        player->animation_table = D_8011AFF0;
    }

    player->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    player->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0];
    player->unk40 = 0x500;
    player->unk16 = 2;
    player->unk42 = 0x7800;
    player->unk49 = 3;
    player_reset_palette(player);
    player_init_clone();

    i = 0;
    active_object = foo_objects;
    object = foo_objects;
    do {
        active_object->active = 0x11;
        object->unk2 = i;
        object->bg_offset = player->bg_offset;
        object->unk38 = player->unk38;
        object->unk3C = player->unk3C;
        object->unk40 = player->unk40;
        object->unk42 = player_afterimage_cluts[object->unk2];
        object->unk16 = 4;
        if (i != 0) {
            object->link.previous = previous;
        } else {
            object->link.player = &g_Player;
        }
        previous = object;
        object++;
        i++;
        active_object++;
    } while (i < 3);

    baz = baz_objects;
    i = 0;
    do {
        baz->active = 0x21;
        baz->unk2 = i;
        baz->bg_offset = player->bg_offset;
        baz->unk38 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        frame_offset = sprite_frames[1];
        baz->unk3C = (u8*)sprite_frames + frame_offset;
        baz->animation_table = D_8011BF40;
        baz->unk40 = 0;
        baz->unk42 = 0x7800;
        baz->unk16 = 2;
        baz->unk15 = 0;
        baz++;
    } while (++i < 2);

    if (engine->stage == 1) {
        i = 0;
        do {
            visual = find_free_visual_obj();
            if (visual != 0) {
                visual->active = 0x41;
                visual->id = 7;
                visual->unk2 = i;
            }
            i++;
        } while (i < 4);
    }

    if (player->unk2 == 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x21;
            misc->id = 0x36;
        }
    }

    background_objects[0].unk44 = 0;
    background_objects[1].unk44 = 0;
    background_objects[2].unk44 = 0;
}

void player_init_clone(void)
{
    struct PlayerObj* entity = &g_Entity;

    reset_entity(entity);
    entity->is_clone = 1;
    entity->animation_table = D_80119DF0;
    entity->unk50 = 0;
    entity->unk54 = 0;
    entity->unk68 = NULL;
    entity->hp = engine_obj.unk46;
    entity->hud_hp = engine_obj.unk46;
    entity->unk5E = engine_obj.unk46;
    entity->unk38 = (s32*)((u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0]);
    entity->unk3C = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0];
    entity->unk40 = 0x540;
    entity->unk16 = 2;
    entity->unk42 = 0x7800;
    entity->unk49 = 1;
}

void player_update_init(struct PlayerObj* self)
{
    struct EngineObj* engine = &engine_obj;
    s32 entry;

    if (self->is_clone != 0) {
        self->on_screen = 1;
        player_set_animation(self, 0x61);
        self->unk5 = PLAYER_SOUL_BODY_CLONE;
        self->state++;
        return;
    }
    if (engine->unk1E != 0) {
        self->on_screen = 1;
        engine->unk1F = 1;
        entry = 0;
        switch (engine->stage) {
        case 3:
            if (engine->unk1E == -1 && engine->checkpoint != 0) {
                entry = 1;
            }
            break;
        case 5:
            entry = 2;
            if (engine->substage != 0) {
                if (engine->checkpoint == 0) {
                    entry = 2;
                } else {
                    entry = 0;
                }
            }
            break;
        case 6:
            if (engine->unk1E == -1) {
                entry = 1;
            }
            break;
        case 12:
            if (engine->substage == 0) {
                if (engine->checkpoint >= 2) {
                    entry = 1;
                }
            } else if (engine->checkpoint == 0) {
                entry = 1;
            }
            break;
        }
        self->state++;
        player_entry_funcs[entry](self);
    }
}

void player_entry_beam_in(struct PlayerObj* self)
{
    player_set_animation(self, 1);
    func_8001540C(1, 0xD, self);
    self->y_vel.val = FIXED(-8);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->air_state = -1;
    self->unk5 = PLAYER_BEAM_IN;
}

void player_entry_placed(struct PlayerObj* self)
{
    struct EngineObj* engine = &engine_obj;

    switch (engine_obj.stage) {
    case 3:
        self->y_pos.i.hi = player_stage_3_entry_y[engine_obj.substage][engine_obj.checkpoint];
        break;
    case 6:
        if (engine_obj.substage == 0) {
            self->y_pos.i.hi = player_stage_6_entry_y[engine_obj.checkpoint];
        } else {
            self->y_pos.i.hi = 0x9CB;
        }
        break;
    case 12:
        if (engine_obj.substage == 0) {
            self->y_pos.i.hi = player_stage_12_entry_y[engine_obj.checkpoint];
        } else {
            self->y_pos.i.hi = 0x1CB;
        }
        break;
    }

    if (self->unk2 == 0) {
        self->armor_parts = engine->unk47;
        self->arm_type = engine->unk48;
    } else {
        self->y_pos.i.hi--;
    }
    self->y_pos.i.lo = 0;
    engine->unk1C = 0;
    player_set_collision_bounds(self);
    player_enter_idle(self);
    background_objects[0].unk44 = 1;
    background_objects[1].unk44 = 1;
    background_objects[2].unk44 = 1;
}

void player_entry_ride(struct PlayerObj* self)
{
    qux_object.active = 1;
    self->armor_parts = engine_obj.unk47;
    self->arm_type = engine_obj.unk48;
    self->ride_state = -1;
    self->ride_animation = 0x29;
    self->air_state = 1;
    self->unk5 = PLAYER_RIDE;
    self->unk6 = 1;
}

void player_update_death(struct PlayerObj* self)
{
    player_death_funcs[self->unk5](self);
}

void player_death_start(struct PlayerObj* self)
{
    stop_sound(1, 5);
    stop_sound(1, 7);
    if (self->ride_state != 0) {
        self->on_screen = 0;
        self->death_timer = 1;
    } else {
        engine_obj.unk12 = 1;
        engine_obj.unk13 = 1;
        engine_obj.unk14 = 1;
        engine_obj.unk15 = 1;
        engine_obj.unk16 = 1;
        engine_obj.unk17 = 1;
        engine_obj.unk18 = 1;
        engine_obj.unk19 = 1;
        engine_obj.unk1A = 1;
        self->death_timer = 8;
        player_set_animation(self, 0x21);
    }
    self->unk5 = (u8)self->unk5 + 1;
}

void player_death_wait(struct PlayerObj* self)
{
    if (--self->death_timer == 0) {
        engine_obj.unk12 = 0;
        engine_obj.unk13 = 0;
        engine_obj.unk14 = 0;
        engine_obj.unk15 = 0;
        engine_obj.unk16 = 0;
        engine_obj.unk17 = 0;
        engine_obj.unk18 = 0;
        engine_obj.unk19 = 0;
        engine_obj.unk1A = 0;
        self->on_screen = 0;
        func_8001540C(3, 0xC, self);
        self->death_timer = 0;
        self->unkC6 = 0;
        self->unk5 = (u8)self->unk5 + 1;
        func_80035C20(self);
    }
}

// player_death_explode
INCLUDE_ASM("main/nonmatchings/player", func_80035C20);

void player_death_end(struct PlayerObj* self)
{
    if (self->death_timer != 0) {
        self->death_timer--;
        return;
    }
    self->state = PLAYER_STATE_INACTIVE;
    self->unk5 = 0;
}

void player_spawn_death_orb(s8 direction)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x21;
        obj->id = 0x11;
        obj->unk2 = direction;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
    }
}

void player_spawn_death_orbs(s8 pattern)
{
    const s8* entry;
    const s8* end;
    s32 index;
    const s8* table;

    index = pattern;
    table = (const s8*)player_death_orb_directions;
    index *= 8;
    entry = table + index;
    end = entry + 8;

    do {
        player_spawn_death_orb(*entry++);
    } while (entry < end);
}

void player_update_inactive(struct PlayerObj* self)
{
}

void player_update_frame_hitbox(struct PlayerObj* self)
{
    u8 zero_hitbox;
    u8 x_hitbox;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            x_hitbox = D_801193F0[self->animation_step.fields.frame_index];
            if (D_801193F0[self->animation_step.fields.frame_index] != 0) {
                self->unk54 = &D_801194F0[x_hitbox];
                return;
            }
        }
        self->unk54 = NULL;
        return;
    }
    if (D_8011AF60[self->unk17] == 0) {
        zero_hitbox = D_8011A030[self->animation_step.fields.frame_index];
    } else {
        zero_hitbox = D_8011A130[self->animation_step.fields.frame_index];
    }
    if (zero_hitbox == 0) {
        self->unk54 = NULL;
        return;
    }
    self->unk54 = &D_8011A230[zero_hitbox];
}

void player_set_collision_bounds(struct PlayerObj* self)
{
    if (self->ride_state < 0) {
        self->unk68 = NULL;
        return;
    }
    if (self->unk2 == 0) {
        self->unk68 = &player_x_collision_bounds;
        return;
    }
    self->unk68 = &player_zero_collision_bounds;
}

void player_read_input(void)
{
    if (g_Player.controlling_clone == 0) {
        g_Player.input.buttons.held = player_map_buttons(D_80166C08);
        g_Player.input.buttons.previous = player_map_buttons(D_80166C0A);
        g_Player.pressed_input = player_map_buttons(controller_state);
        return;
    }
    g_Player.input.buttons.held = 0;
    g_Player.input.buttons.previous = 0;
    g_Player.pressed_input = 0;
    g_Entity.input.buttons.held = player_map_buttons(D_80166C08);
    g_Entity.input.buttons.previous = player_map_buttons(D_80166C0A);
    g_Entity.pressed_input = player_map_buttons(controller_state);
}

s32 player_map_buttons(s32 pad)
{
    u16 result = 0;
    u32 bit = 1;
    u32 i = 0;

    for (i = 0; i < 16; i++) {
        if (D_800EE430[i] & pad) {
            result |= bit;
        }
        bit *= 2;
    }

    if ((result & 3) == 3) {
        result &= ~0x3;
    }

    if ((result & 0xC) == 0xC) {
        result &= ~0xC;
    }

    return result;
}

void player_clear_dash(struct PlayerObj* self)
{
    self->dash_momentum = 0;
    self->air_action = 0;
    if (self->afterimage > 0) {
        self->afterimage = -1;
    }
}

void player_clear_attack(struct PlayerObj* self)
{
    self->attacking = 0;
    self->shot_fired = 0;
    self->attack_ended = 0;
    self->attack_pose_timer = 0;
    self->shot_cooldown = 0;
    self->shot_palette_timer = 0;
    player_reset_palette(self);
}

void player_clear_dash_and_attack(struct PlayerObj* self)
{
    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = 0;
    player_clear_attack(self);
}

void player_clear_flash(struct PlayerObj* self)
{
    self->flash_palette = 0;
}

void player_update_flash(struct PlayerObj* self)
{
    s8 action = self->unk5; // likely fake
    if ((self->unk5 != PLAYER_BEAM_IN) && (action != PLAYER_BEAM_OUT) && (self->hurt_phase <= 0)) {
        if (self->shot_palette_timer != 0) {
            if (--self->shot_palette_timer == 0) {
                player_reset_palette(self);
            }
        }
        if (self->hurt_phase < 0) {
            self->flash_palette = 0x23;
        }
        if (self->flash_palette != 0) {
            if (self->flash_delay != 0) {
                self->flash_delay--;
            } else {
                if (self->flash_phase == 0) {
                    player_set_palette(self, self->flash_palette);
                } else {
                    player_reset_palette(self);
                }
                self->flash_delay = 1;
                self->flash_phase ^= 1;
            }
            self->flash_palette = 0;
        }
    }
}

void player_copy_palette(struct PlayerObj* self, s32 source, s32 dest)
{
    u16* src;
    u16* dst;
    u32 i;

    src = SP_PALETTE_BANK[source];
    dst = SP_PALETTES[dest];

    for (i = 0; i < 16; i++) {
        *dst++ = *src++;
    }
}

void player_reset_palette(struct PlayerObj* self)
{
    u16* dst;
    u16* src;
    u32 a2;
    s32 temp;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            if (self->weapon == 0) {
                player_set_palette(self, 0);
            } else {
                temp = ((self->weapon - 1) << 6);
                dst = SP_PALETTE;
                src = SP_PALETTE_BANK[3] + temp;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *dst++ = *src++;
                }
                dst = SP_PALETTE + 0x130;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *dst++ = *src++;
                }
            }
            need_palette_load |= 1;
        }
    } else {
        if (engine_obj.unk37) {
            player_copy_palette(self, 0xD, 0);
        } else {
            player_copy_palette(self, 0, 0);
        }
        need_palette_load |= 1;
    }
}

void player_set_palette(struct PlayerObj* self, s32 palette)
{
    u16* dst;
    u16* src;
    u32 i;

    if (self->unk2 == 0) {
        if (self->is_clone == 0) {
            dst = SP_PALETTE;
            src = SP_PALETTE_BANK[palette];
            for (i = 0; i < 0x10; i++) {
                *dst++ = *src++;
            }
            dst = SP_PALETTE + 0x130;
            for (i = 0; i < 0x20; i++) {
                *dst++ = *src++;
            }
            need_palette_load |= 1;
        }
    } else {
        player_copy_palette(self, palette, 0);
        need_palette_load |= 1;
    }
}

void player_play_voice(struct PlayerObj* self, u8 voice)
{
    if (self->voice_timer <= 0) {
        func_8001540C(3, voice, self);
    }
}

void player_check_low_hp_alarm(struct PlayerObj* self)
{
    if (self->voice_timer == 0 && self->hp < (engine_obj.unk46 / 3)) {
        func_8001540C(3, 0xB, 0);
        self->voice_timer = 0x78;
    }
}

void player_damage(s8 damage)
{
    struct PlayerObj* player;
    u8 amount;
    s8 value;

    player = &g_Player;
    g_Player.stun_timer = -1;
    if (damage != 0) {
        if (g_Player.armor_parts & 2) {
            if (damage < 3) {
                amount = 1;
            } else {
                amount = (damage / 3) * 2;
            }
            player->hp = (u8)(player->hp - amount);
        } else {
            g_Player.hp = (u8)(g_Player.hp - damage);
        }
    }
    if (player->hp > 0) {
        value = player->hp | 0x80;
    } else {
        value = -0x80;
        player->stun_timer = 0;
    }
    player->hp = value;
}

void player_set_idle_animation(struct PlayerObj* self)
{
    if (self->hp >= (engine_obj.unk46 / 3)) {
        player_set_animation(self, 5);
    } else {
        player_set_animation(self, 6);
    }
}

void player_air_steer(struct PlayerObj* self)
{
    if (!self->input_locked && (self->input.buttons.held & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT))) {
        if (self->input.buttons.held & PLAYER_INPUT_RIGHT) {
            self->unk15 = 0x40;
            if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT)) {
                if (self->dash_momentum != 0) {
                    self->x_vel.val = FIXED(4.125);
                } else {
                    self->x_vel.val = FIXED(2);
                }
            } else {
                self->x_vel.val = 0;
            }
        } else {
            self->unk15 = 0;
            if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT)) {
                if (self->dash_momentum != 0) {
                    self->x_vel.val = FIXED(-4.125);
                } else {
                    self->x_vel.val = FIXED(-2);
                }
            } else {
                self->x_vel.val = 0;
            }
        }
    } else {
        self->x_vel.val = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void player_spawn_dash_dust(struct PlayerObj* self)
{
    struct VisualObj* visual_obj;
    u8 bg_offset;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 1;
        bg_offset = self->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->bg_offset = bg_offset;
    }
}

void player_spawn_dash_spark(struct PlayerObj* self)
{
    s16 x_pos;
    s32 frame_offset;
    u8 facing;
    struct VisualObj* visual_obj;
    s32* sprite_frames;

    if (func_8002D900(self) == 0x24) {
        player_spawn_dash_splash(self);
        return;
    }

    visual_obj = find_free_visual_obj();
    if (visual_obj == NULL) {
        return;
    }

    visual_obj->active = 0x21;
    visual_obj->id = 3;
    visual_obj->unk2 = 2;
    visual_obj->state = 0;
    visual_obj->unk5 = 0;
    visual_obj->unk6 = 0;
    visual_obj->bg_offset = self->bg_offset;
    sprite_frames = SP_SPRITE_FRAMES;
    visual_obj->unk38 = 0;
    frame_offset = sprite_frames[1];
    visual_obj->animation_table = D_8011BF40;
    visual_obj->unk42 = 0x7804;
    visual_obj->unk40 = 0;
    visual_obj->unk16 = 1;
    visual_obj->unk3C = (u8*)sprite_frames + frame_offset;
    facing = self->unk15;
    visual_obj->unk15 = facing;
    if (facing == 0) {
        x_pos = self->x_pos.u.hi + player_dash_effect_offsets[self->unk2 * 2];
    } else {
        x_pos = self->x_pos.u.hi - player_dash_effect_offsets[self->unk2 * 2];
    }
    visual_obj->x_pos.i.hi = x_pos;
    visual_obj->y_pos.i.hi = self->y_pos.u.hi + player_dash_effect_offsets[self->unk2 * 2 + 1];
}

void player_spawn_dash_splash(struct PlayerObj* self)
{
    s16 x_pos;
    u8 facing;
    struct VisualObj* visual_obj;
    s32* menu_frames;
    s32 column;
    s32 row;
    s32 index;
    u8 bg_offset;

    if (func_8002D900(self) == 0x24) {
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 3;
            visual_obj->unk2 = 8;
            bg_offset = self->bg_offset;
            visual_obj->unk16 = 1;
            visual_obj->animation_table = D_8011BF40;
            visual_obj->bg_offset = bg_offset;
            index = func_8002938C(0x84) & 0xFF;
            menu_frames = SP_MENU_FRAMES;
            visual_obj->unk3C = (u8*)menu_frames + menu_frames[index];
            index = func_8002938C(0x84) & 0xFF;
            visual_obj->unk40 = D_801406A8[index] >> 7;
            column = func_8002938C(0x84);
            row = func_8002938C(0x84);
            visual_obj->unk42 = (((column & 0xFF) * 4 + 0x18) % 16) | ((((row & 0xFF) + 6) / 4 + 0x1E0) << 6);
            facing = self->unk15;
            visual_obj->unk15 = facing;
            if (facing == 0) {
                x_pos = self->x_pos.u.hi + player_dash_effect_offsets[4 + self->unk2];
            } else {
                x_pos = self->x_pos.u.hi - player_dash_effect_offsets[4 + self->unk2];
            }
            visual_obj->x_pos.i.hi = x_pos;
            visual_obj->y_pos.i.hi = self->y_pos.u.hi;
        }
    }
}

extern f32 player_wall_kick_spark_offsets[];

void player_spawn_wall_kick_spark(struct PlayerObj* self)
{
    s16 x_pos;
    s32 frame_offset;
    u8 facing;
    struct VisualObj* visual_obj;
    s32* sprite_frames;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->active = 0x21;
        visual_obj->id = 3;
        visual_obj->unk2 = 1;
        visual_obj->bg_offset = self->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        sprite_frames = SP_SPRITE_FRAMES;
        visual_obj->unk38 = 0;
        frame_offset = sprite_frames[1];
        visual_obj->animation_table = D_8011BF40;
        visual_obj->unk40 = 0;
        visual_obj->unk42 = 0x7802;
        visual_obj->unk16 = 0;
        visual_obj->unk3C = (u8*)sprite_frames + frame_offset;
        facing = self->unk15;
        visual_obj->unk15 = facing;
        if (facing == 0) {
            x_pos = self->x_pos.u.hi + player_wall_kick_spark_offsets[self->unk2].u.lo;
        } else {
            x_pos = self->x_pos.u.hi - player_wall_kick_spark_offsets[self->unk2].u.lo;
        }
        visual_obj->x_pos.i.hi = x_pos;
        visual_obj->y_pos.i.hi = self->y_pos.u.hi + player_wall_kick_spark_offsets[self->unk2].u.hi;
    }
}

void player_spawn_wall_slide_dust(struct PlayerObj* self)
{
    struct VisualObj* visual_obj;
    u8 bg_offset;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x21;
        visual_obj->id = 0;
        bg_offset = self->bg_offset;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->bg_offset = bg_offset;
    }
}

void player_start_script_action(s8 action, s8 facing)
{
    g_Player.script_state = 1;
    g_Player.script_action = action;
    g_Player.script_facing = facing;
    g_Player.spike_immune = 1;
    engine_obj.unk1C = 1;
}

void player_end_script_action(void)
{
    g_Player.script_state = 0;
    g_Player.spike_immune = 0;
    engine_obj.unk1C = 0;
}

void player_check_splash_tile(struct PlayerObj* self)
{
    if (func_8002D994(self) == 0x24) {
        s16 y = self->y_pos.u.hi & 0xFFF0;
        func_80036BF4(self, y);
    }
}

void player_check_splash(struct PlayerObj* self)
{
    if (func_8002D900(self) == 0x24) {
#ifdef MMX4_PC
        s16 temp = self->y_pos.i.hi;

        if (self->unk68 != NULL)
            temp += self->unk68->unk1 + self->unk68->unk3;
#else
        s16 temp = self->y_pos.i.hi + self->unk68->unk1 + self->unk68->unk3;
#endif
        func_80036BF4(self, temp & ~0xF);
    }
}

// player_spawn_splash
INCLUDE_ASM("main/nonmatchings/player", func_80036BF4);

struct WeaponObj* player_spawn_weapon(s8 active, s8 id, s8 type, struct PlayerObj* owner)
{
    struct WeaponObj* weapon = find_free_weapon_obj();

    if (weapon == NULL) {
        return NULL;
    }

    weapon->active = active;
    weapon->id = id;
    weapon->unk2 = type;
    weapon->bg_offset = g_Player.bg_offset;
    if (owner != NULL) {
        weapon->owner = owner;
    }
    return weapon;
}

struct VisualObj* player_spawn_visual(s8 active, s8 id, s8 variant, void* owner)
{
    struct VisualObj* visual_obj = find_free_visual_obj();

    if (visual_obj == NULL) {
        return NULL;
    }

    visual_obj->active = active;
    visual_obj->id = id;
    visual_obj->unk2 = variant;
    visual_obj->bg_offset = g_Player.bg_offset;
    if (owner) {
        visual_obj->unk50 = owner;
    }
    return visual_obj;
}

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
INCLUDE_ASM("main/nonmatchings/player", func_80036F50);

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
INCLUDE_ASM("main/nonmatchings/player", func_80037484);

s32 player_check_hover(struct PlayerObj* self)
{
    if (!(self->armor_parts & 8)) {
        return 0;
    }
    if (!(self->pressed_input & PLAYER_INPUT_JUMP)) {
        return 0;
    }
    player_set_animation_shooting(self, 0x15);
    self->air_action = 4;
    self->hover_timer = 0xB4;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_momentum = 0;
    self->afterimage = 0;
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
INCLUDE_ASM("main/nonmatchings/player", func_80037C28);

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
    self->air_state = 1;
    self->invincibility_timer = 0;
    self->hurt_phase = 0;
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
    self->air_state = 1;
    self->spike_immune = 1;
    self->unk5 = PLAYER_RISING_FIRE_CHARGED;
    self->unk6 = 0;
    self->shot_count++;
    self->special_shot_count++;
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
INCLUDE_ASM("main/nonmatchings/player", func_80038568);

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
    u8 animation;

    animation = player_shoot_animations[self->shot_type];
    player_set_animation(self, animation);
    if (animation == 0x59) {
        self->animation_step.fields.duration = self->attack_pose_timer - 8;
    }
}

void player_enter_ladder_shoot(struct PlayerObj* self)
{
    player_set_ladder_shoot_animation(self);
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->unk5 = PLAYER_LADDER_SHOOT;
    self->unk6 = 0;
    self->x_pos.i.hi = (self->x_pos.i.hi & 0xFFF0) + 8;
}

void player_set_ladder_shoot_animation(struct PlayerObj* self)
{
    u8 animation;

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
    s8 next_state;

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
        next_state = 5;
    } else {
        player_set_animation_shooting(self, 0x18);
        next_state = 4;
    }
    self->unk6 = next_state;
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
    s8 next_state;

    if ((player_hover_check_end(self) == 0) && (player_check_wall(self) == 0)) {
        direction = player_hover_steer(self);
        if (direction != 0) {
            if (direction > 0) {
                player_set_animation_shooting(self, 0x17);
                next_state = 3;
            } else {
                move_object(MOVING_OBJECT(self));
                func_80038568(self, 0x19);
                return;
            }
        } else {
            player_set_animation_shooting(self, 0x1A);
            next_state = 6;
        }
        self->unk6 = next_state;
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

s32 player_hover_steer(struct PlayerObj* self)
{
    u16 buttons;

    buttons = self->input.buttons.held;
    self->y_pos.i.hi += player_hover_bob[self->hover_bob];
    self->hover_bob = (self->hover_bob + 1) & 0xF;
    self->x_vel.val = 0;

    if (buttons & (PLAYER_INPUT_RIGHT | PLAYER_INPUT_LEFT)) {
        if (buttons & PLAYER_INPUT_RIGHT) {
            if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
                return 0;
            }
            self->x_vel.val = FIXED(2);
            if (self->unk15 != 0) {
                return 1;
            }
            return -1;
        }
        if (!(self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT)) {
            goto move_left;
        }
    }

return_zero:
    return 0;

move_left:
    self->x_vel.val = FIXED(-2);
    if (self->unk15 != 0) {
        return -1;
    }
    return 1;
}

void player_hover_set_direction(struct PlayerObj* self, s32 direction)
{
    s8 value;

    if (direction > 0) {
        player_set_animation_shooting(self, 0x17);
        value = 3;
    } else {
        player_set_animation_shooting(self, 0x19);
        value = 5;
    }
    self->unk6 = value;
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
    s32 wall_flag;

    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING) {
        self->y_vel.val = 0;
        self->unk2C = 0;
    }
    wall_flag = PLAYER_COLLIDE_LEFT;
    if (self->unk15 != 0) {
        wall_flag = PLAYER_COLLIDE_RIGHT;
    }
    if (wall_flag & self->unk88.bytes.collision_flags) {
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
    u8 facing;

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
        facing = self->unk15;
        g_Entity.air_state = 1;
        g_Entity.clone_timer = 0xF0;
        g_Entity.clone_offset.value = 0;
        g_Entity.unk15 = facing;
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
        self->y_vel.val = FIXED(5.8125);
        self->x_vel.val = 0;
        self->unk28 = 0;
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
INCLUDE_ASM("main/nonmatchings/player", func_80039F28);

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
INCLUDE_ASM("main/nonmatchings/player", func_8003A1DC);

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
        if (player_check_ladder_air(self) != 0 || player_check_wall(self) != 0 || player_check_air_move(self) != 0) {
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
    airborne = self->input_locked != 0;
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
        self->y_vel.val = FIXED(-3);
        self->unk2C = FIXED(0.2578125);
        self->animation_step.fields.event = 0;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->air_state = -1;
        self->unk6++;
    }
}

void player_zero_hyouretsuzan_drop(struct PlayerObj* self)
{
    s16 x_pos;
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
                    x_pos = self->x_pos.u.hi - 0x10;
                } else {
                    x_pos = self->x_pos.u.hi + 0x10;
                }
                debris->x_pos.i.hi = x_pos;
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

    if (!(D_80141BD8.unk0 & 1)) {
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
    s32 frame_offset;
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
            frame_offset = sprite_frames[6];
            visual_obj->animation_table = D_8011C018;
            visual_obj->unk40 = 0;
            visual_obj->unk42 = 0x7803;
            visual_obj->unk16 = 0;
            visual_obj->unk3C = (u8*)sprite_frames + frame_offset;
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
    s32 side_mask;

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
        if (side_mask & self->unk88.bytes.collision_flags) {
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

void (*player_state_funcs[])(struct PlayerObj*) = {
    player_update_init,
    player_update_normal,
    player_update_death,
    player_update_inactive,
};

void (*player_normal_state_funcs[])(struct PlayerObj*) = {
    player_beam_in,
    player_beam_out,
    player_idle,
    player_walk_start,
    player_walk,
    player_settle,
    player_jump,
    player_fall,
    player_land,
    player_wall_cling,
    player_wall_jump,
    player_wall_slide,
    player_dash,
    player_air_dash,
    player_ladder_transition,
    player_ladder_up,
    player_ladder_down,
    player_hurt,
    player_ride,
    player_capsule,
    player_script_wait,
    func_80033108,
    player_script_vanish,
    player_script_jump,
    player_script_victory,
    player_stage_clear,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_ladder_shoot,
    player_hover,
    player_nova_strike,
    player_soul_body,
    player_soul_body_clone_advance,
    player_soul_body_clone_vanish,
    player_weapon_pose,
    player_rising_fire,
    player_rising_fire_charged,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
    player_zero_saber,
    player_zero_jump_slash,
    player_zero_fall_slash,
    player_zero_ladder_slash,
    player_zero_wall_slash,
    player_zero_raijingeki,
    player_zero_hyouretsuzan,
    player_zero_jump_slash,
    player_zero_fall_slash,
    player_zero_ryuenjin,
    player_zero_rakuhouha,
    player_zero_shippuuga,
    player_idle,
    player_idle,
    player_idle,
    player_idle,
};

void (*player_dash_funcs[])(struct PlayerObj*) = {
    player_dash_start,
    player_dash_move,
    player_dash_end,
};

void (*player_air_dash_funcs[])(struct PlayerObj*) = {
    player_air_dash_start,
    player_air_dash_move,
    player_air_dash_end,
};

void (*player_ladder_transition_funcs[])(struct PlayerObj*) = {
    player_ladder_grab,
    player_ladder_climb_off_top,
    player_ladder_climb_on_top,
    player_ladder_step_off_bottom,
    player_ladder_let_go,
};

void (*player_hurt_funcs[])(struct PlayerObj*) = {
    player_hurt_knockback,
    player_hurt_knockback,
    player_hurt_launch,
    player_hurt_stun,
    player_hurt_knockback,
};

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

u8 player_jump_voices[][4] = { { 2, 3, 6, 6 }, { 2, 4, 7, 7 } };

s16 player_afterimage_cluts[4] = { 0x780D, 0x780E, 0x780F, 0 };

void (*player_entry_funcs[])(struct PlayerObj*) = {
    player_entry_beam_in,
    player_entry_placed,
    player_entry_ride,
};

u16 player_stage_3_entry_y[2][4] = {
    { 0x0000, 0x00AB, 0x09CB, 0x025B },
    { 0x0000, 0x01AB, 0x08AB, 0x0000 },
};

u16 player_stage_6_entry_y[6] = {
    0x00CB,
    0x03BB,
    0x02CB,
    0x03BB,
    0x09CB,
    0x03BB,
};

u16 player_stage_12_entry_y[20] = {
    0x0000,
    0x0000,
    0x069B,
    0x06CB,
    0x06CB,
    0x06B3,
    0x06BB,
    0x06BB,
    0x09BB,
    0x09BB,
    0x09CB,
    0x035B,
    0x03CB,
    0x04AB,
    0x043B,
    0x03CB,
    0x035B,
    0x04AB,
    0x043B,
    0x0000,
};

void (*player_death_funcs[])(struct PlayerObj*) = {
    player_death_start,
    player_death_wait,
    func_80035C20,
    player_death_end,
};

u8 player_death_orb_directions[4][8] = {
    { 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C },
    { 0x02, 0x06, 0x0A, 0x0E, 0x12, 0x16, 0x1A, 0x1E },
    { 0x01, 0x05, 0x09, 0x0D, 0x11, 0x15, 0x19, 0x1D },
    { 0x03, 0x07, 0x0B, 0x0F, 0x13, 0x17, 0x1B, 0x1F },
};

struct Unk_unk68 player_x_collision_bounds = { 0, 2, 0x0B, 0x13 };

struct Unk_unk68 player_zero_collision_bounds = { 0, 3, 0x0A, 0x13 };

u16 player_dash_effect_offsets[6] = { 0x10, 0x0E, 0x1A, 0x11, 0x10, 0x1A };

f32 player_wall_kick_spark_offsets[2] = {
    { 0x000CFFF5 },
    { 0x0009FFF6 },
};

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
