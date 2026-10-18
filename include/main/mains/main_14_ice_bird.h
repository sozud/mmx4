#ifndef MAIN_MAINS_MAIN_14_ICE_BIRD_H
#define MAIN_MAINS_MAIN_14_ICE_BIRD_H

void ice_bird_update(struct MainObj* arg0);

void ice_bird_main(struct MainObj* arg0);
void ice_bird_despawn(struct MainObj*);

// ice_bird_fly_in_funcs
void ice_bird_fly_in_start(struct MainObj*);

void ice_bird_blast_release(struct MainObj*);

// ice_bird_leave_funcs
void ice_bird_leave_start(struct MainObj*);

extern s32 ice_bird_fly_speeds[2];

extern struct Unk_unk68 ice_bird_body_box;
extern union AnimationStep* ice_bird_animations[];

void func_8004D6FC(struct MainObj* arg0);

void ice_bird_spawn_ice_shards(struct AnimatedObj*);
void ice_bird_face_player(struct AnimatedObj*);

#endif
