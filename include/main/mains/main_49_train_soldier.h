#ifndef MAIN_MAINS_MAIN_49_TRAIN_SOLDIER_H
#define MAIN_MAINS_MAIN_49_TRAIN_SOLDIER_H

void train_soldier_update(struct MainObj* arg0);

// train_soldier_state_funcs
void func_80068548(struct MainObj* arg0);

void train_soldier_wait_for_player(struct MainObj* arg0);
void func_80068D6C(struct MainObj* arg0);

// train_soldier_step_funcs
void train_soldier_idle(struct MainObj* arg0);

// train_soldier_walk_funcs
void func_80068B80(struct MainObj*);

// train_soldier_jump_funcs
void train_soldier_jump_crouch(struct MainObj* arg0);

// train_soldier_shoot_funcs
void train_soldier_shoot_aim(struct MainObj*);
void train_soldier_shoot_fire(struct MainObj*);

#endif
