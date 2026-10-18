#ifndef MAIN_QUADS_QUAD_03_BOSS_WARNING_QUAD_H
#define MAIN_QUADS_QUAD_03_BOSS_WARNING_QUAD_H

struct QuadMotionData {
    u16 vertex[4];
    s8 speed[4];
};

void boss_warning_quad_update(struct QuadObj* arg0);

void func_800D4C50(struct QuadObj*);

extern struct QuadMotionData boss_warning_quad_motions[22];

#endif
