#ifndef MAIN_MAINS_MAIN_71_RIDE_ARMOR_PILOT_H
#define MAIN_MAINS_MAIN_71_RIDE_ARMOR_PILOT_H

void ride_armor_pilot_update(struct MainObj* arg0);

// ride_armor_pilot_step_funcs
void ride_armor_pilot_reset(struct MainObj* arg0);
void func_8008A064(struct MainObj* arg0);
void func_8008A180(struct MainObj* arg0);
void func_8008AAF4(struct MainObj* arg0);
void func_8008A4D8(struct MainObj* arg0);
void func_8008A778(struct MainObj* arg0);
void func_8008A8E4(struct MainObj* arg0);
void func_8008A3B0(struct MainObj* arg0);
void ride_armor_pilot_punch(struct MainObj* arg0);
void func_8008A60C(struct MainObj* arg0);
void func_8008A9F4(struct MainObj* arg0);
void ride_armor_pilot_return_to_idle(struct MainObj *arg0);
void ride_armor_pilot_set_scripted_speed(struct MainObj* arg0);
u8 ride_armor_pilot_update_facing(struct MainObj* arg0);
void ride_armor_pilot_set_jump_speed(struct MainObj* arg0);

void func_8008AC40(struct MainObj*);

#ifdef MMX4_PC
extern void ride_armor_pilot_stub (struct MainObj *arg0, s32 arg1, s32 arg2);
#endif

extern u8 ride_armor_pilot_hurt_box[];

extern u8 ride_armor_pilot_attack_box[];
extern struct Unk_unk68 ride_armor_pilot_punch_box;

void ride_armor_pilot_spawn_dust(struct VisualObj*, u8);

#endif
