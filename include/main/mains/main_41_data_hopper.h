#ifndef MAIN_MAINS_MAIN_41_DATA_HOPPER_H
#define MAIN_MAINS_MAIN_41_DATA_HOPPER_H

void data_hopper_update(struct MainObj* arg0);

// data_hopper_state_funcs
void data_hopper_init(struct MainObj*);
void func_80062BBC(struct MainObj*);

void func_80062650(struct MainObj* arg0);

void func_80062778(struct MainObj* arg0);
void data_hopper_blink(struct MainObj* arg0);
void data_hopper_vanish(struct MainObj* arg0);

extern union AnimationStep* data_hopper_animations[19];
extern struct Unk_unk68 data_hopper_terrain_box;

#endif
