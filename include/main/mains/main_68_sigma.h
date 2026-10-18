#ifndef MAIN_MAINS_MAIN_68_SIGMA_H
#define MAIN_MAINS_MAIN_68_SIGMA_H

void sigma_update(struct MainObj* arg0);

// sigma_intro_funcs
void sigma_intro_wait_player(struct MainObj*);
void func_8008329C(struct MainObj*);

void func_80083710(struct MainObj*);
void func_800837FC(struct MainObj*);

void func_80083C2C(struct MainObj*);

void sigma_scythe_plant_throw(struct MainObj*);

void sigma_darts_spawn(struct MainObj*);

void func_80084B14(struct MainObj*);
void sigma_eye_laser_fire(struct MainObj*);

void sigma_pose(struct MainObj* arg0);

void func_80084EE4(struct MainObj*);
void func_8008502C(struct MainObj*);

void sigma_death_blink(struct MainObj* arg0);

void func_80085460(struct MainObj*);

void sigma_cloak_stagger_trail(struct MainObj*);

void sigma_reveal_fall(struct MainObj*);
void func_80085A44(struct MainObj*);

extern struct Unk_unk68 D_80103F08;
extern struct Unk_unk68 D_80103F0C;

extern struct Unk_unk68 D_80103EE4;

extern struct Unk_unk68 D_80103EE8;
extern struct Unk_unk68 D_80103F00;
extern struct Unk_unk68 D_80103F04;

extern void (*sigma_step_funcs[9])();

#endif
