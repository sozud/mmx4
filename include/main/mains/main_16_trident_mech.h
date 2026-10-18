#ifndef MAIN_MAINS_MAIN_16_TRIDENT_MECH_H
#define MAIN_MAINS_MAIN_16_TRIDENT_MECH_H

void trident_mech_update(struct MainObj* arg0);

void func_8004E8E0(struct MainObj*);
void trident_mech_main(struct MainObj*);

void func_8004FAE4(struct MainObj* arg0);

void trident_mech_throw_pod(struct MainObj* arg0);

void func_8004FD38(struct MainObj*, s32);

void func_8004ED60(struct MainObj*);

// trident_mech_jump_funcs
void trident_mech_jump_launch_pod(struct MainObj*);

// trident_mech_fan_shot_funcs
void trident_mech_fan_shot_start(struct MainObj*);
void trident_mech_fan_shot_fire(struct MainObj*);

// trident_mech_double_shot_funcs
void trident_mech_double_shot_first(struct MainObj*);
void trident_mech_double_shot_second(struct MainObj*);

extern struct Unk_unk68 trident_mech_hurt_box;
extern struct Unk_unk68 trident_mech_attack_box;

extern struct Unk_unk68 trident_mech_stunned_hurt_box;

#endif
