#ifndef MAIN_MAINS_MAIN_05_ROBOT_BEE_H
#define MAIN_MAINS_MAIN_05_ROBOT_BEE_H

void robot_bee_update(struct MainObj* arg0);

// robot_bee_state_funcs
void func_80044F88(struct MainObj* arg0);

extern void (*robot_bee_step_funcs[])();

void func_80045940(struct MainObj*);

void func_80045DD8(struct MainObj*);

void func_80046220(struct MainObj*);

void func_80046400(struct MainObj*);

void robot_bee_check_dive(struct MainObj* arg0);

extern u8 robot_bee_debris[];

#endif
