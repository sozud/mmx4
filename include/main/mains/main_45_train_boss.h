#ifndef MAIN_MAINS_MAIN_45_TRAIN_BOSS_H
#define MAIN_MAINS_MAIN_45_TRAIN_BOSS_H

void train_boss_update(struct MainObj* arg0);

void train_boss_main(struct MainObj*);
void train_boss_defeated(struct MainObj*);
void func_80065EA4(struct MainObj*);
void func_800661AC(struct MainObj*);
void func_8006630C(struct MainObj*);
void func_80066478(struct MainObj*);

// train_boss_arrive_funcs
void func_800665BC(struct MainObj*);

void func_80066970(struct MainObj*);

extern u8 train_boss_attack_timers[20];
extern union AnimationStep* train_boss_animations[];

#endif
