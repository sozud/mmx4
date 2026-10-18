#ifndef MAIN_MAINS_MAIN_33_SPIKE_SLED_H
#define MAIN_MAINS_MAIN_33_SPIKE_SLED_H

void spike_sled_update(struct MainObj* arg0);

// spike_sled_state_funcs
void spike_sled_init(struct MainObj*);

void func_8005D4E0(struct MainObj*);

void spike_sled_resume_step(struct MainObj* arg0);

// spike_sled_patrol_funcs
void spike_sled_patrol_start(struct MainObj* arg0);
void spike_sled_patrol_drive(struct MainObj*);
void spike_sled_patrol_turn(struct MainObj*);

void func_8005DC58(struct MainObj*);
void func_8005DED4(struct MainObj*);

// spike_sled_bomb_funcs
void func_8005E108(struct MainObj*);
void spike_sled_bomb_rise(struct MainObj*);
void func_8005E298(struct MainObj*);

extern u16 D_800FDDA0[14];

extern union AnimationStep* spike_sled_animations[23];
extern struct Unk_unk68 D_800FDD88;
extern struct Unk_unk68 D_800FDD8C;

#endif
