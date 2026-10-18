#ifndef MAIN_MAINS_MAIN_73_DOUBLE_H
#define MAIN_MAINS_MAIN_73_DOUBLE_H

void double_update(struct MainObj* arg0);

void double_intro_dialogue(struct MainObj*);
void double_intro_wait_dialogue(struct MainObj*);
void double_intro_voice(struct MainObj*);
void double_intro_fill_health(struct MainObj*);

void func_8008BA38(struct MainObj*);
void func_8008BB6C(struct MainObj*);
void double_intro_talk(struct MainObj* arg0);

void double_wait_start(struct MainObj*);
void func_8008C10C(struct MainObj*);

void double_energy_ball_windup(struct MainObj*);
void double_energy_ball_throw(struct MainObj*);
void double_energy_ball_recover(struct MainObj*);

void double_dive_leap(struct MainObj*);
void double_dive_rise(struct MainObj*);
void double_dive_climb(struct MainObj*);
void double_dive_aim(struct MainObj*);
void double_dive_fall(struct MainObj*);
void func_8008C664(struct MainObj*);
void double_dive_hit_wall(struct MainObj*);
void double_dive_stun(struct MainObj*);
void double_dive_land(struct MainObj*);

void double_aerial_shot_jump(struct MainObj*);
void double_aerial_shot_fire(struct MainObj*);
void double_aerial_shot_hang(struct MainObj*);

void double_aerial_shot_fire_again(struct MainObj*);

void double_aerial_shot_drop(struct MainObj*);
void double_aerial_shot_land(struct MainObj*);

// double_step_funcs
void double_wait(struct MainObj* arg0);
void double_energy_ball(struct MainObj* arg0);
void double_dive(struct MainObj* arg0);
void double_aerial_shot(struct MainObj* arg0);

void double_death_start(struct MainObj*);
void double_death_fall(struct MainObj*);
void double_death_wait(struct MainObj*);
void double_death_wait_dialogue(struct MainObj*);
void double_death_blink(struct MainObj*);
void double_death_wait_explosion(struct MainObj*);
void double_death_finish(struct MainObj*);

void double_intro(struct MainObj *arg0);
void func_8008CD80(struct MainObj*);
void double_death(struct MainObj*);

void double_spawn_shot(struct MainObj*, s32, s32);

extern struct Unk_unk68 double_attack_box;
extern struct Unk_unk68 double_hurt_box;

#endif
