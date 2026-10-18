#ifndef MAIN_MAINS_MAIN_08_EREGION_H
#define MAIN_MAINS_MAIN_08_EREGION_H

void eregion_update(struct MainObj* arg0);

void func_80047D04(struct MainObj* arg0);
void func_80047E58(struct MainObj* arg0);

void eregion_recoil(struct MainObj* arg0);

// eregion_step_funcs
void eregion_pick_start(struct MainObj*);
void func_800480D0(struct MainObj*);

// eregion_wing_slash_funcs
void eregion_wing_slash_start(struct MainObj*);
void func_80048B04(struct MainObj*);

void eregion_pounce_rise(struct MainObj*);

// eregion_fireball_funcs
void eregion_fireball_open(struct MainObj*);
void eregion_fireball_fire(struct MainObj*);

// eregion_spread_funcs
void eregion_spread_open(struct MainObj*);
void eregion_spread_fire(struct MainObj*);

void eregion_death_blink(struct MainObj* arg0);

void eregion_recoil_start(struct MainObj*);
void func_8004932C(struct MainObj*);

// eregion_intro_funcs
void eregion_intro_warning(struct MainObj*);
void eregion_intro_leap(struct MainObj*);
void eregion_intro_rise(struct MainObj*);

extern u32 D_800FA72C;
extern u32 D_800FA730;

extern u32 D_800FA734;

#endif
