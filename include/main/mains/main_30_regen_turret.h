#ifndef MAIN_MAINS_MAIN_30_REGEN_TURRET_H
#define MAIN_MAINS_MAIN_30_REGEN_TURRET_H

void regen_turret_update(struct MainObj* arg0);

// regen_turret_state_funcs
void func_8005B438(struct MainObj*);

void regen_turret_rebuild(struct MainObj*);

void regen_turret_fire(struct MainObj* arg0);

extern u8 regen_turret_debris[];

#endif
