#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

enum PlayerState {
    PLAYER_STATE_INIT,
    PLAYER_STATE_NORMAL,
    PLAYER_STATE_DEATH,
    PLAYER_STATE_INACTIVE
};

enum PlayerCollision {
    PLAYER_COLLIDE_RIGHT = 0x1,
    PLAYER_COLLIDE_LEFT = 0x2,
    PLAYER_COLLIDE_CEILING = 0x4,
    PLAYER_COLLIDE_GROUND = 0x8
};

// player_state_funcs
extern void (*player_state_funcs[])(struct PlayerObj*);

void player_update_normal(struct PlayerObj*);

// player_normal_state_funcs
extern void (*player_normal_state_funcs[])(struct PlayerObj*);
void player_beam_in(struct PlayerObj*);
void player_beam_out(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_walk_start(struct PlayerObj*);
void player_walk(struct PlayerObj*);
void player_settle(struct PlayerObj*);
void player_jump(struct PlayerObj*);
void player_fall(struct PlayerObj*);
void player_land(struct PlayerObj*);
void player_wall_cling(struct PlayerObj*);
void player_wall_jump(struct PlayerObj*);
void player_wall_slide(struct PlayerObj*);
void player_wall_jump_push(struct PlayerObj* arg0);
void player_wall_jump_rise(struct PlayerObj* arg0);
void player_dash(struct PlayerObj*);
void player_air_dash(struct PlayerObj*);
void player_ladder_transition(struct PlayerObj*);
void player_ladder_up(struct PlayerObj*);
void player_ladder_down(struct PlayerObj*);
void player_hurt(struct PlayerObj*);
void player_ride(struct PlayerObj*);
void player_capsule(struct PlayerObj*);
void func_80032FA4(struct PlayerObj*);
void player_capsule_fall(struct PlayerObj*);
void player_script_wait(struct PlayerObj*);
void func_80033108(struct PlayerObj*);
void player_script_vanish(struct PlayerObj*);
void player_script_jump(struct PlayerObj*);
void player_script_victory(struct PlayerObj*);
void player_stage_clear(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);

void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);

void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);
void player_idle(struct PlayerObj*);

void player_dash_start(struct PlayerObj*);
void player_dash_move(struct PlayerObj*);
void player_dash_end(struct PlayerObj*);

void player_air_dash_start(struct PlayerObj*);
void player_air_dash_move(struct PlayerObj*);
void player_air_dash_end(struct PlayerObj*);

void player_ladder_grab(struct PlayerObj*);
void player_ladder_climb_off_top(struct PlayerObj*);
void player_ladder_climb_on_top(struct PlayerObj*);
void player_ladder_step_off_bottom(struct PlayerObj*);
void player_ladder_let_go(struct PlayerObj*);

void player_hurt_knockback(struct PlayerObj*);
void player_hurt_knockback(struct PlayerObj*);
void player_hurt_launch(struct PlayerObj*);
void player_hurt_stun(struct PlayerObj*);
void player_hurt_knockback(struct PlayerObj*);

#ifdef MMX4_PC
extern void player_update (void);
#endif

#endif
