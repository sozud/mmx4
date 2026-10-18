#ifndef MAIN_MAINS_MAIN_18_ICE_CORE_H
#define MAIN_MAINS_MAIN_18_ICE_CORE_H

void ice_core_update(struct MainObj* arg0);

// ice_core_state_funcs
void func_8005077C(struct MainObj*);
void func_80050874(struct MainObj*);

void ice_core_float(struct MainObj* arg0);

void func_80050D14(struct MainObj*);

void ice_core_bob_move(struct MainObj*);

void ice_core_charge_slide(struct MainObj*);

void ice_core_charge_run(struct MainObj*);

void ice_core_stomp_rise(struct MainObj*);
void ice_core_stomp_drop(struct MainObj*);

void ice_core_stomp_recover(struct MainObj*);

void func_800517D0(struct MainObj*);
void ice_core_build_grow(struct MainObj*);

// ice_core_spray_funcs
void ice_core_spray_fire(struct MainObj*);

// ice_core_intro_funcs
void func_80052218(struct MainObj*);

void func_800527F0(struct MainObj*);

extern struct Unk_unk68 D_800FBEF4;
extern struct Unk_unk68 D_800FBEF8;

extern struct Unk_unk68 D_800FBEFC;

extern u16 D_800FBEDC[12];

extern struct Unk_unk68 D_800FBF0C;

void ice_core_face_player(struct AnimatedObj*);

#endif
