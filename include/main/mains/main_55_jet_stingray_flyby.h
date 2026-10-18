#ifndef MAIN_MAINS_MAIN_55_JET_STINGRAY_FLYBY_H
#define MAIN_MAINS_MAIN_55_JET_STINGRAY_FLYBY_H

void func_8006ED44(struct MainObj*);
void func_8006EF28(struct MainObj*);

void jet_stingray_flyby_attack_rise(struct MainObj*);
void jet_stingray_flyby_attack_fire(struct MainObj*);
void jet_stingray_flyby_attack_end(struct MainObj*);
void jet_stingray_flyby_attack_align(struct MainObj*);

void jet_stingray_flyby_charge_windup(struct MainObj*);
void func_8006F5F4(struct MainObj*);

void jet_stingray_flyby_enter(struct MainObj* arg0);
void jet_stingray_flyby_wait_on_screen(struct MainObj* arg0);
void func_8006F0DC(struct MainObj* arg0);
void jet_stingray_flyby_attack(struct MainObj* arg0);
void jet_stingray_flyby_charge(struct MainObj* arg0);
void jet_stingray_flyby_drift(struct MainObj* arg0);
void func_8006F86C(struct MainObj* arg0);

// jet_stingray_flyby_state_funcs
extern void (*jet_stingray_flyby_state_funcs[])(struct MainObj*);
void func_8006EB40(struct MainObj*);
void jet_stingray_flyby_main(struct MainObj*);

#endif
