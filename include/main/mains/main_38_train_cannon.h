#ifndef MAIN_MAINS_MAIN_38_TRAIN_CANNON_H
#define MAIN_MAINS_MAIN_38_TRAIN_CANNON_H

void train_cannon_update(struct MainObj* arg0);

// train_cannon_state_funcs
void train_cannon_init(struct MainObj*);
void train_cannon_main(struct MainObj*);

void train_cannon_idle_pick(struct MainObj*);

extern union AnimationStep* train_cannon_animations[21];

extern struct Unk_unk68 train_cannon_hurt_box;
extern struct Unk_unk68 train_cannon_attack_box;
extern struct Unk_unk68 train_cannon_terrain_box;

void train_cannon_fire_blast(struct PlayerObj*);
void train_cannon_fire_volley(struct MainObj*);
void train_cannon_spawn_charge_glow(struct VisualObj*);

#endif
