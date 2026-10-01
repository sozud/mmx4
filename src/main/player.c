// PlayerObj
// 800311EC..80033414
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
    s8 timer;

    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }

    if (player_check_shoot_air(self) != 0) {
        return;
    }
    vertical_mask = self->unk88.bytes.collision_flags & PLAYER_COLLIDE_CEILING;
    should_end_state = 0;
    if (vertical_mask != 0) {
        should_end_state = 1;
    }
    if (self->unk15 != 0) {
        direction_mask = self->unk88.bytes.collision_flags & PLAYER_COLLIDE_LEFT;
    } else {
        direction_mask = self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT;
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
    u8 wall_flag;
    s8 event;

    if (player_check_ladder(self) == 0 && player_check_shoot(self) == 0 && player_zero_check_ground_technique(self) == 0 && player_check_dash_jump_walk(self) == 0 && player_zero_check_saber(self) == 0) {
        event = self->animation_step.fields.event;
        if (event & 0x80) {
            self->animation_step.fields.event = event & 0x7F;
            func_8001540C(1, 6, self);
        }
        if ((self->animation_step.fields.event & 0x40) && self->dash_timer == 0) {
            wall_flag = self->unk15 != 0 ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT;
            if (self->unk88.bytes.collision_flags & wall_flag) {
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
        return;
    }
    if (self->input_locked != 0) {
        player_enter_fall(self);
        return;
    }
    if (self->unk2 == 0) {
        if (player_check_shoot_air(self) != 0) {
            return;
        }
        if (self->attacking != 0) {
            player_enter_fall_shooting(self);
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    player_air_dash_funcs[self->unk6](self);
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
        self->stun_timer = -2;
    } else if (self->animation_step.fields.relative_step < 0) {
        player_set_animation(self, 0x24);
        self->stun_timer = 1;
    } else {
        return;
    }
}

void player_hurt_slide(struct PlayerObj* self)
{
    s32 velocity;
    u8 direction;

    if (self->capsule_state != 0) {
        return;
    }

    velocity = self->x_vel.val;
    if (velocity != 0) {
        if (velocity > 0) {
            direction = PLAYER_COLLIDE_RIGHT;
        } else {
            direction = PLAYER_COLLIDE_LEFT;
        }
        if ((self->unk88.bytes.collision_flags & direction) != 0) {
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

// player_take_hit

u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

// player_check_ladder_end

// player_enter_wall_jump

// player_enter_wall_slide_release

// player_start_script

// player_death_explode

// player_spawn_splash

// player_select_weapon

// player_enter_weapon_pose

// player_fire_twin_slasher

// player_continue_animation

// player_zero_check_rakuhouha

// player_zero_check_combo

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
