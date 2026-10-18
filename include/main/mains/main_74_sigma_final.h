#ifndef MAIN_MAINS_MAIN_74_SIGMA_FINAL_H
#define MAIN_MAINS_MAIN_74_SIGMA_FINAL_H

void sigma_final_update(struct MainObj* arg0);

void func_8008D5C8(struct MainObj*);

void sigma_final_laser_aim(struct MainObj*);

void sigma_final_big_beam_charge(struct MainObj*);

void sigma_final_hide_lower_wait(struct MainObj*);

void func_8008E748(struct MainObj*);
void sigma_final_grab_release(struct MainObj*);

void sigma_final_spit_fire(struct MainObj*);

void func_8008EC48(struct MainObj*);
void sigma_final_wind_start(struct MainObj*);
void sigma_final_wind_push(struct MainObj*);

void func_8008DAE8(struct MainObj* arg0);

void func_8008F3F4(struct MainObj*);
void sigma_final_death_blink(struct MainObj*);
void func_8008F578(struct MainObj*);
void sigma_final_death_collapse(struct MainObj*);
void sigma_final_death_wait_player(struct MainObj*);

s32 sigma_spawn_sequencer(struct MainObj*, s8);
void sigma_final_set_target(struct MainObj*, s32);

void func_8008F1A8(struct MainObj*);

extern struct Unk_unk68 D_80105360;

extern struct Unk_unk68 D_8010535C;
extern struct Unk_unk68 D_80105368;
extern struct Unk_unk68 D_8010536C;
extern struct Unk_unk68 D_80105370;
extern u8 sigma_final_laser_animations[8];

#endif
