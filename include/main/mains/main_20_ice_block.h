#ifndef MAIN_MAINS_MAIN_20_ICE_BLOCK_H
#define MAIN_MAINS_MAIN_20_ICE_BLOCK_H

void ice_block_update(struct MainObj* arg0);

// ice_block_state_funcs
void func_800545EC(struct MainObj*);

// ice_block_step_funcs
extern void (*ice_block_step_funcs[])(struct MainObj*);

void func_800548B8(struct MainObj*);

#endif
