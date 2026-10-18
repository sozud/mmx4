#ifndef MAIN_SHOTS_SHOT_29_CANNON_MISSILE_H
#define MAIN_SHOTS_SHOT_29_CANNON_MISSILE_H

void cannon_missile_update(struct ShotObj*);

void func_8009F674(struct ShotObj*);
void func_8009F7C0(struct ShotObj*);

// cannon_missile_step_funcs
extern void (*cannon_missile_step_funcs[])(struct ShotObj*);
void func_8009F89C(struct ShotObj*);
void cannon_missile_slow(struct ShotObj*);
void cannon_missile_track(struct ShotObj*);

#endif
