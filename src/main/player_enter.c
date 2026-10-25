// 800343A4..800350A4
#include "common.h"
#include "main/player.h"
#include "main/1CF60.h"
#include "main/object_motion.h"
#include "main/player_check.h"
#include "main/player_enter.h"
#include "main/55C4.h"
#include "main/player_common.h"
#include "main/player_special.h"
#include "main/player_weapon.h"
#include "main/xa_sequence_data.h"

extern u8 player_jump_voices[][4];

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

u8 player_jump_voices[][4] = { { 2, 3, 6, 6 }, { 2, 4, 7, 7 } };

void player_enter_idle(struct PlayerObj* self)
{
    s32 frame; // ???

    if (player_check_script(self) == 0) {
        self->unk5 = PLAYER_IDLE;
        self->unk6 = 0;
        if ((self->unk2 == 0) && (self->attacking != 0)) {
            frame = self->attack_pose_timer < 9;
            if (self->attack_pose_timer <= 4) {
                frame = 2;
            }
            player_set_animation_frame(self, 0x5E, frame);
            if (self->attack_pose_timer > 8) {
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
    self->air_state = 1;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(5.8125);
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
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0x4200;
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
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_timer = 0x1E;
    self->unk5 = PLAYER_DASH;
    self->unk6 = 0;
}

void player_enter_dash_end(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0x11);
#ifndef MMX4_SATURN
    stop_sound(1, 5);
#endif
    if (self->unk15 != 0) {
        self->x_vel.val = FIXED(4.125);
    } else {
        self->x_vel.val = FIXED(-4.125);
    }
    self->unk28 = FIXED(-0.1875);
    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = -1;
    self->unk6 = 2;
}

void player_enter_air_dash(struct PlayerObj* self)
{
    player_set_animation(self, 0x12);
    self->unk28 = FIXED(-0.1875);
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_momentum = -1;
    self->dash_timer = 0x12;
    self->air_action = 3;
    player_clear_attack(self);
    self->unk5 = PLAYER_AIR_DASH;
    self->unk6 = 0;
}

void player_enter_air_dash_end(struct PlayerObj* self)
{
    player_set_animation(self, 0x13);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = FIXED(0.2578125);
    self->air_state = -1;
    self->dash_momentum = 0;
    self->afterimage = -1;
    self->unk6 = 2;
}

void player_enter_fall_shooting(struct PlayerObj* self)
{
    player_set_animation(self, 0x84);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = FIXED(0.2578125);
    self->air_state = -1;
    self->dash_momentum = 0;
    self->afterimage = 0;
    self->unk5 = PLAYER_FALL;
    self->unk6 = 0;
}

void player_enter_wall_cling(struct PlayerObj* self)
{
    player_set_animation_shooting(self, 0xD);
    func_8001540C(1, 4, self);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->dash_momentum = 0;
    self->air_action = 0;
    self->afterimage = -1;
    self->unk8A.bytes.low = 8;
    if (self->unk88.bytes.collision_flags & PLAYER_COLLIDE_RIGHT) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
    self->unk5 = PLAYER_WALL_CLING;
    self->unk6 = 0;
}

// player_enter_wall_jump

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800349F4(struct PlayerObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/player_enter", func_800349F4);
#else
void func_800349F4(struct PlayerObj* arg0)
{
    player_set_animation_shooting(arg0, 0xE);
    func_8001540C(1, 3, BASE_OBJECT(arg0));
    player_play_voice(arg0, 2);
    arg0->air_state = 1;
    if (arg0->input.buttons.held & 0x100) {
        arg0->dash_momentum = 1;
        arg0->air_action = 1;
        arg0->afterimage = 1;
    } else {
        player_clear_dash(arg0);
    }
    if (arg0->unk88.bytes.collision_flags & 1) {
        arg0->unk15 = PLAYER_FACING_RIGHT;
        if (arg0->dash_momentum != 0)
            arg0->x_vel.val = FIXED(-4.125);
        else
            arg0->x_vel.val = FIXED(-2);
    } else {
        arg0->unk15 = 0;
        if (arg0->dash_momentum != 0)
            arg0->x_vel.val = FIXED(4.125);
        else
            arg0->x_vel.val = FIXED(2);
    }
    arg0->unk28 = 0;
    arg0->y_vel.val = FIXED(5.625);
    arg0->unk2C = 0x4200;
    arg0->unk8A.bytes.low = 10;
    player_spawn_wall_kick_spark(arg0);
    arg0->unk5 = 10;
    arg0->unk6 = 0;
}
#endif
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
void func_80034B64(struct PlayerObj* player)
{
    player_set_animation_shooting(player, 0xB);

    if (player->unk88.bytes.collision_flags & 1) {
        player->x_vel.val = FIXED(-2);
    } else {
        player->x_vel.val = FIXED(2);
    }

    player->unk2C = 0x4200;
    player->unk8A.bytes.low = 4;
    player->air_state = -1;
    player->unk5 = 0xB;
    player->unk28 = 0;
    player->y_vel.val = 0;
    player->unk6 = 1;
}
void player_enter_ladder_grab(struct PlayerObj* self)
{
    player_set_animation(self, 0x1B);
    self->x_pos.i.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    self->x_pos.u.lo = 0;
    self->y_pos.u.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(1);
    self->unk2C = 0;
    self->air_state = 1;
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
    self->y_pos.i.hi &= 0xFFF0;
    player_clear_attack(self);
    self->unk5 = PLAYER_LADDER_TRANSITION;
    self->unk6 = 1;
}

void player_enter_ladder_climb_on_top(struct PlayerObj* self)
{
    player_set_animation(self, 0x1D);
    self->x_pos.i.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    self->x_pos.u.lo = 0;
    self->y_pos.u.lo = 0;
    self->unk68 = 0;
    self->air_state = 1;
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
    self->x_pos.i.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(1.5);
    self->unk2C = 0;
    player_clear_dash(self);
    self->unk5 = PLAYER_LADDER_UP;
    self->unk6 = 0;
}

void player_enter_ladder_down(struct PlayerObj* self)
{
    self->x_pos.i.hi = (self->x_pos.u.hi & 0xFFF0) + 8;
    self->x_pos.i.lo = 0;
    self->y_pos.i.lo = 0;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(-1.5);
    self->unk2C = 0;
    player_clear_dash(self);
    self->unk5 = PLAYER_LADDER_DOWN;
    self->unk6 = 0;
}

// player_start_script
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/player_enter", func_80034E2C);
#else
#ifdef MMX4_PC
void func_80034E2C(void)
{
    struct PlayerObj* player = &g_Player;
#else
void func_80034E2C(struct PlayerObj* player)
{
#endif

    player->unk6 = 0;
    player->unk5 = player->script_action;
    player_clear_dash_and_attack(player);
    switch ((s8)(player->unk5 - 0x14)) {
    case 0:
        if ((u8)(player->unk17 - 5) >= 2)
            player_set_idle_animation(player);
        player->script_state = -1;
        player->unk15 = player->script_facing;
        break;
    case 1:
        player_set_animation(player, 0x26);
        player->y_vel.val = 0;
        player->unk28 = 0;
        player->unk2C = 0;
        if ((u8)player->script_facing == 0) {
            player_script_walk_to_mark(player);
            break;
        }
        player->unk15 = PLAYER_FACING_RIGHT;
        break;
    case 2:
        player_set_animation(player, 3);
        player->script_state = -1;
        player->unk15 = player->script_facing;
        break;
    case 3:
        player_set_animation(player, 0xA);
        player_set_collision_bounds(player);
        player->y_vel.val = 0x5D000;
        player->unk2C = 0x4200;
        player->x_vel.val = 0;
        player->unk28 = 0;
        player->air_state = 1;
        player->unk15 = player->script_facing;
        break;
    case 4:
        player_set_animation(player, 0x6B);
        player_reset_weapon(player);
        player->unk15 = player->script_facing;
        break;
    }
}
#endif
void player_start_stage_clear(struct PlayerObj* self)
{
    u8 flags;

    player_clear_dash_and_attack(self);
    player_reset_charge_and_weapon(self);

    flags = engine_obj.unkF;
    engine_obj.gameplay_locked = 1;

    if (flags & 0x10) {
        player_set_idle_animation(self);
        player_reset_weapon(self);

        if (self->unk2 == 0) {
#ifdef MMX4_SATURN
            func_8001663C(0x14, 0);
#else
            func_8001663C(MUSIC_STAGE_CLEAR_X, 0x75);
#endif
        } else {
#ifdef MMX4_SATURN
            func_8001663C(0x15, 0);
#else
            func_8001663C(MUSIC_STAGE_CLEAR_ZERO, 0x72);
#endif
        }

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
#ifdef MMX4_SATURN
    func_8001540C(1, 0xD, self);
#else
    func_8001540C(1, 0xB, self);
#endif
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(8);
    self->unk2C = 0;
    self->unk68 = 0;
    self->air_state = 1;
    self->unk5 = PLAYER_BEAM_OUT;
    self->unk6 = 0;
}
