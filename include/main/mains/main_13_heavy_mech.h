#ifndef MAIN_MAINS_MAIN_13_HEAVY_MECH_H
#define MAIN_MAINS_MAIN_13_HEAVY_MECH_H

void heavy_mech_update(struct MainObj* arg0);

void func_8004C860(struct MainObj*);

void heavy_mech_fall(struct MainObj* arg0);

void heavy_mech_stomp(struct MainObj* arg0);

void func_8004CA94(struct MainObj*);

// heavy_mech_throw_funcs
void heavy_mech_throw_anim(struct MainObj*);

extern struct Unk_unk68 heavy_mech_hurt_box;
extern struct Unk_unk68 heavy_mech_attack_box;
extern struct Unk_unk68 heavy_mech_terrain_box;
extern union AnimationStep* heavy_mech_animations[18];

#endif
