#ifndef MAIN_MAINS_MAIN_51_FORTRESS_CANNON_H
#define MAIN_MAINS_MAIN_51_FORTRESS_CANNON_H

void fortress_cannon_update(struct MainObj* arg0);

void func_80069AD0(struct MainObj*);
void func_80069BE4(struct MainObj*);

void fortress_cannon_fall(struct MainObj* arg0);

void fortress_cannon_fire_start(struct MainObj*);
void func_80069F28(struct MainObj*);

void fortress_cannon_fire_shot(struct MainObj*);
void fortress_cannon_fire_double_shot(struct MainObj*);

extern void (*fortress_cannon_step_funcs[])(struct MainObj*);

void fortress_cannon_check_fall(struct MainObj*);
extern u8 fortress_cannon_debris[8];

#endif
