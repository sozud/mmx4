#ifndef MAIN_MAINS_MAIN_69_COLONEL_H
#define MAIN_MAINS_MAIN_69_COLONEL_H

void colonel_update(struct MainObj* arg0);

void func_80086124(struct MainObj*);

void colonel_spawn_warning(struct MainObj*);
void func_80086008(struct MainObj*);

void colonel_defeat_start(struct MainObj* arg0);
void colonel_defeat_fall(struct MainObj*);

void colonel_defeat_blink(struct MainObj*);

void func_80086C00(struct MainObj*);
void colonel_intro_port_flash(struct PlayerObj*);

void colonel_intro_hall_wait_player(struct MainObj*);

void colonel_intro_hall_effect(struct MainObj*);

void func_800877A4(struct MainObj*);
void colonel_teleport_slash_swing(struct MainObj*);

void func_80087A00(struct MainObj*);
void colonel_dash_brake(struct MainObj*);

void colonel_saber_waves_fire(struct MainObj*);
void colonel_saber_waves_fire_high(struct MainObj*);
void colonel_saber_waves_fire_last(struct MainObj*);

void colonel_jump_slam_shockwave(struct MainObj*);

void colonel_face_player(struct MainObj *arg0);
ret_u8 colonel_shot_incoming(struct MainObj*);

extern struct Unk_unk68 D_80104504;
extern struct Unk_unk68 D_80104508;

extern struct Unk_unk68 D_801044FC;
extern struct Unk_unk68 D_80104500;

#endif
