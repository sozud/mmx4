#ifndef MAIN_MAINS_MAIN_52_JUMP_SHOOTER_H
#define MAIN_MAINS_MAIN_52_JUMP_SHOOTER_H

void jump_shooter_update(struct MainObj* arg0);

void jump_shooter_fire_shots(struct MainObj*);

void func_8006AAB4(struct MainObj*);

void jump_shooter_jump_launch(struct MainObj*);

void func_8006AE80(struct MainObj*);

extern union AnimationStep* jump_shooter_animations[28];
extern struct Unk_unk68 jump_shooter_hurt_box;
extern struct Unk_unk68 jump_shooter_attack_box;
extern struct Unk_unk68 jump_shooter_terrain_box;

#endif
