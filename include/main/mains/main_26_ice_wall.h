#ifndef MAIN_MAINS_MAIN_26_ICE_WALL_H
#define MAIN_MAINS_MAIN_26_ICE_WALL_H

void ice_wall_update(struct MainObj* arg0);

// ice_wall_state_funcs
void func_80058194(struct MainObj*);

void ice_wall_break(struct MainObj*);

extern u8 ice_wall_debris[];

void func_800583B0(struct MainObj*, s16, s16, s32);

#endif
