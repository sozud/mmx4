#ifndef MAIN_MAINS_MAIN_75_GENERAL_H
#define MAIN_MAINS_MAIN_75_GENERAL_H

void general_update(struct MainObj* arg0);

void func_8008FBCC(struct MainObj*);

void func_800905D4(struct MainObj*);

void general_punch_launch(struct MainObj*);

void general_punch_rings(struct MainObj*);

void general_slam_windup(struct MainObj*);
void general_slam_fall(struct MainObj*);

void general_slam_rise(struct MainObj*);
void general_slam_ascend(struct MainObj*);
void general_slam_leave(struct MainObj*);

void func_8009027C(struct MainObj* arg0);

void general_death_blink(struct MainObj* arg0);
void func_800915C4(struct MainObj*);

void func_800917AC(struct MainObj*);

void func_80091218(struct MainObj*);

extern void* general_scripts[2];
extern u8 general_script_weights[4];

extern struct Unk_unk68 D_801059D8;
extern struct Unk_unk68 D_801059DC;

#endif
