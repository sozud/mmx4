#ifndef MAIN_MAINS_MAIN_07_AMBUSH_GUNNER_H
#define MAIN_MAINS_MAIN_07_AMBUSH_GUNNER_H

void ambush_gunner_update(struct MainObj* arg0);

// ambush_gunner_state_funcs
void func_80047404(struct MainObj* arg0);

void ambush_gunner_resume_step(struct MainObj* arg0);

void ambush_gunner_fire(struct MainObj* arg0);

// ambush_gunner_emerge_funcs
void func_80047818(struct MainObj* arg0);

void ambush_gunner_aim_wait(struct MainObj*);

#endif
