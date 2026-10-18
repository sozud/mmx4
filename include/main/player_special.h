#ifndef MAIN_PLAYER_SPECIAL_H
#define MAIN_PLAYER_SPECIAL_H

enum PlayerAction {
    PLAYER_BEAM_IN,
    PLAYER_BEAM_OUT,
    PLAYER_IDLE,
    PLAYER_WALK_START,
    PLAYER_WALK,
    PLAYER_SETTLE,
    PLAYER_JUMP,
    PLAYER_FALL,
    PLAYER_LAND,
    PLAYER_WALL_CLING,
    PLAYER_WALL_JUMP,
    PLAYER_WALL_SLIDE,
    PLAYER_DASH,
    PLAYER_AIR_DASH,
    PLAYER_LADDER_TRANSITION,
    PLAYER_LADDER_UP,
    PLAYER_LADDER_DOWN,
    PLAYER_HURT,
    PLAYER_RIDE,
    PLAYER_CAPSULE,
    PLAYER_SCRIPT_WAIT,
    PLAYER_SCRIPT_WALK,
    PLAYER_SCRIPT_VANISH,
    PLAYER_SCRIPT_JUMP,
    PLAYER_SCRIPT_VICTORY,
    PLAYER_STAGE_CLEAR,
    PLAYER_LADDER_SHOOT = 0x20,
    PLAYER_HOVER,
    PLAYER_NOVA_STRIKE,
    PLAYER_SOUL_BODY,
    PLAYER_SOUL_BODY_CLONE,
    PLAYER_SOUL_BODY_VANISH,
    PLAYER_WEAPON_POSE,
    PLAYER_RISING_FIRE,
    PLAYER_RISING_FIRE_CHARGED,
    PLAYER_ZERO_SABER = 0x30,
    PLAYER_ZERO_JUMP_SLASH,
    PLAYER_ZERO_FALL_SLASH,
    PLAYER_ZERO_LADDER_SLASH,
    PLAYER_ZERO_WALL_SLASH,
    PLAYER_ZERO_RAIJINGEKI,
    PLAYER_ZERO_HYOURETSUZAN,
    PLAYER_ZERO_SPIN_JUMP_SLASH,
    PLAYER_ZERO_SPIN_FALL_SLASH,
    PLAYER_ZERO_RYUENJIN,
    PLAYER_ZERO_RAKUHOUHA,
    PLAYER_ZERO_SHIPPUUGA,
};

void player_ladder_shoot(struct PlayerObj*);
void player_hover(struct PlayerObj*);
void player_nova_strike(struct PlayerObj*);
void player_soul_body(struct PlayerObj*);

void player_soul_body_clone_advance(struct PlayerObj*);
void player_soul_body_clone_vanish(struct PlayerObj*);
void player_weapon_pose(struct PlayerObj*);
void player_rising_fire(struct PlayerObj*);
void player_rising_fire_charged(struct PlayerObj*);

void player_zero_saber(struct PlayerObj*);
void player_zero_jump_slash(struct PlayerObj*);
void player_zero_fall_slash(struct PlayerObj*);
void player_zero_ladder_slash(struct PlayerObj*);
void player_zero_wall_slash(struct PlayerObj*);
void player_zero_raijingeki(struct PlayerObj*);
void player_zero_hyouretsuzan(struct PlayerObj*);
void player_zero_jump_slash(struct PlayerObj*);
void player_zero_fall_slash(struct PlayerObj*);
void player_zero_ryuenjin(struct PlayerObj*);
void player_zero_rakuhouha(struct PlayerObj*);
void player_zero_shippuuga(struct PlayerObj*);

void player_rising_fire_charged_start(struct PlayerObj*);

void player_zero_hyouretsuzan_start(struct PlayerObj*);

#ifdef MMX4_PC
extern s32 player_nova_strike_hit_wall (struct PlayerObj *arg0);

extern s32 player_zero_check_fall_slash (struct PlayerObj *arg0);

extern void player_zero_spawn_saber (struct PlayerObj *arg0, s8 arg1);

extern void player_idle_animate (struct PlayerObj *arg0);

extern s32 func_8003A1DC (struct PlayerObj *arg0);
#endif

extern u8 player_ladder_shoot_animations[];

s32 player_zero_check_ladder_slash(struct PlayerObj*);
s32 player_zero_check_shippuuga(struct PlayerObj*);

s32 player_zero_check_ryuenjin(struct PlayerObj*);

s32 player_hover_steer(struct PlayerObj*);

s32 player_zero_shippuuga_cancel(struct PlayerObj*);

s32 player_zero_check_ground_technique(struct PlayerObj* self);
s32 player_zero_check_saber(struct PlayerObj* self);

void player_enter_ladder_shoot(struct PlayerObj* self);

#endif
