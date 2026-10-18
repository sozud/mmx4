#ifndef MAIN_PLAYER_ENTER_H
#define MAIN_PLAYER_ENTER_H

#ifdef MMX4_PC
extern void player_enter_idle (struct PlayerObj *arg0);

extern void player_enter_air_dash_end (struct PlayerObj *arg0);
extern void func_800349F4 (struct PlayerObj *arg0);
extern void player_enter_ladder_down (struct PlayerObj *arg0);
#endif

s32 func_80034E2C();
void player_start_stage_clear(struct PlayerObj*);

void player_enter_beam_out(struct PlayerObj*);
void player_enter_stand(struct PlayerObj*);

void player_enter_ladder_grab(struct PlayerObj*);
void player_enter_ladder_climb_on_top(struct PlayerObj*);

void player_enter_jump(struct PlayerObj*);
void player_enter_land(struct PlayerObj*);
void player_enter_dash(struct PlayerObj*);
void player_enter_dash_end(struct PlayerObj*);
void player_enter_air_dash(struct PlayerObj*);
void player_enter_fall_shooting(struct PlayerObj*);
void player_enter_wall_cling(struct PlayerObj*);
void player_enter_ladder_up(struct PlayerObj*);

void func_80034B64(struct PlayerObj* player);

void player_enter_fall(struct PlayerObj* self);

void player_enter_walk(struct PlayerObj* self);

#endif
