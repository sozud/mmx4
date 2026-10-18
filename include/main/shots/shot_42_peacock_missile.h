#ifndef MAIN_SHOTS_SHOT_42_PEACOCK_MISSILE_H
#define MAIN_SHOTS_SHOT_42_PEACOCK_MISSILE_H

void peacock_missile_update(struct ShotObj*);

void func_800A63B0(struct ShotObj*);

void func_800A6510(struct ShotObj*);

#ifdef MMX4_PC
extern void func_800A666C (struct ShotObj *arg0, s32 arg1, s32 arg2);
#endif

#endif
