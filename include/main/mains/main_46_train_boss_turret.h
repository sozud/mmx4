#ifndef MAIN_MAINS_MAIN_46_TRAIN_BOSS_TURRET_H
#define MAIN_MAINS_MAIN_46_TRAIN_BOSS_TURRET_H

void train_boss_turret_update(struct MainObj* arg0);

// train_boss_turret_state_funcs
void train_boss_turret_init(struct MainObj*);
void train_boss_turret_main(struct MainObj*);
void train_boss_turret_destroyed(struct MainObj* arg0);

void train_boss_turret_start_idle(struct MainObj* arg0);
void train_boss_turret_arrive(struct MainObj* arg0);
void train_boss_turret_fire(struct MainObj* arg0);

#endif
