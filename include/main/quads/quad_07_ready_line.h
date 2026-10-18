#ifndef MAIN_QUADS_QUAD_07_READY_LINE_H
#define MAIN_QUADS_QUAD_07_READY_LINE_H

void ready_line_update(struct QuadObj* arg0);

void ready_line_init(struct QuadObj* arg0);
void ready_line_main(struct QuadObj* arg0);
void ready_line_despawn(struct QuadObj* arg0);

void ready_line_sweep(struct QuadObj*);
void ready_line_shutter(struct QuadObj*);
void ready_line_streak(struct QuadObj*);

#ifdef MMX4_PC
extern void ready_line_converge_vertex (struct QuadObj *arg0, arg_u8 arg1, s32 arg2, const s16 *target);

extern void ready_line_nop (void);
#endif

#endif
