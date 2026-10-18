#ifndef MAIN_MAINS_MAIN_23_SLOPE_SKIER_H
#define MAIN_MAINS_MAIN_23_SLOPE_SKIER_H

struct VisualSpawnOffset {
    s8 x, y;
};

void slope_skier_update(struct MainObj* arg0);

// slope_skier_jump_funcs
void func_80055F1C(struct MainObj*);

void func_800562AC(struct MainObj*);

void func_80056054(struct MainObj* arg0);

void func_800564B4(struct MainObj*);

void slope_skier_read_slope(struct MainObj*);

#endif
