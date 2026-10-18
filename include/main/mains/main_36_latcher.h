#ifndef MAIN_MAINS_MAIN_36_LATCHER_H
#define MAIN_MAINS_MAIN_36_LATCHER_H

void latcher_update(struct MainObj* arg0);

void func_8005F558(struct MainObj*);
void latcher_main(struct MainObj*);

void latcher_drift(struct MainObj* arg0);

void latcher_grab_home(struct MainObj*);
void latcher_grab_clamp(struct MainObj*);
void latcher_grab_drain(struct MainObj*);

void latcher_check_hit(struct MainObj*);

extern union AnimationStep* latcher_animations[7];

#endif
