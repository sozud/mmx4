#ifndef MAIN_MAINS_MAIN_66_IRIS_H
#define MAIN_MAINS_MAIN_66_IRIS_H

void iris_update(struct MainObj* arg0);

// iris_state_funcs
void func_80080700(struct MainObj*);
void func_80080834(struct MainObj*);

// iris_step_funcs
extern void (*iris_step_funcs[])(struct MainObj*);

void func_80081E44(struct MainObj* arg0);

void func_80080DF4(struct MainObj*);

void iris_intro_toss_crystal(struct MainObj*);

void func_80081718(struct MainObj*);

void iris_robot_dash_laser(struct MainObj*);

void func_80081BA0(struct MainObj*);

void iris_crystal_drop_fire(struct MainObj*);

#endif
