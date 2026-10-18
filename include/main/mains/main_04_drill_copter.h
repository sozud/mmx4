#ifndef MAIN_MAINS_MAIN_04_DRILL_COPTER_H
#define MAIN_MAINS_MAIN_04_DRILL_COPTER_H

void drill_copter_update(struct MainObj* arg0);

void func_80044458(struct MainObj*);
void func_80044508(struct MainObj*);

void drill_copter_noop(struct MainObj*);

void drill_copter_approach_idle(struct MainObj*);

void drill_copter_sway_idle(struct MainObj*);

void drill_copter_drop_fall(struct MainObj*);

void drill_copter_drop_idle(struct MainObj*);

void drill_copter_fire_shots(struct MainObj*);

#endif
