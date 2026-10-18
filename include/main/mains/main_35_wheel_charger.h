#ifndef MAIN_MAINS_MAIN_35_WHEEL_CHARGER_H
#define MAIN_MAINS_MAIN_35_WHEEL_CHARGER_H

void wheel_charger_update(struct MainObj* arg0);

void func_8005ECA8(struct MainObj*);
void wheel_charger_main(struct MainObj*);

void wheel_charger_resume_step(struct MainObj* arg0);

void func_8005EFB0(struct MainObj* arg0);

void wheel_charger_crash(struct MainObj* arg0);
void wheel_charger_check_fall(struct MainObj* arg0);

void wheel_charger_charge_spin(struct MainObj*);
void wheel_charger_charge_roll(struct MainObj*);

#endif
