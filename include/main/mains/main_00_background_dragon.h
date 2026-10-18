#ifndef MAIN_MAINS_MAIN_00_BACKGROUND_DRAGON_H
#define MAIN_MAINS_MAIN_00_BACKGROUND_DRAGON_H

void background_dragon_update(struct MainObj* arg0);

void func_80040644(struct MainObj*);
void func_80040838(struct MainObj*);

// background_dragon_step_funcs
extern void (*background_dragon_step_funcs[])(struct MainObj*);

void func_800415B0(struct MainObj*);

void func_800419B8(struct MainObj*);

void func_80040CCC(struct MainObj*);
#ifdef MMX4_PC
s32 func_80040ABC(struct MainObj*);
#endif

#endif
