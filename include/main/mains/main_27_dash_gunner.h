#ifndef MAIN_MAINS_MAIN_27_DASH_GUNNER_H
#define MAIN_MAINS_MAIN_27_DASH_GUNNER_H

void dash_gunner_update(struct MainObj* arg0);

void func_80058740(struct MainObj*);
void func_80058AC8(struct MainObj*);

void func_80059640(struct MainObj* arg0);

// dash_gunner_run_funcs
void dash_gunner_run_move(struct MainObj*);

void dash_gunner_turn_flip(struct MainObj*);

void dash_gunner_shoot_fire(struct MainObj*);

// dash_gunner_dash_funcs
void dash_gunner_dash_start(struct MainObj* arg0);
void dash_gunner_dash_move(struct MainObj*);

void dash_gunner_dash_end(struct MainObj*);

#endif
