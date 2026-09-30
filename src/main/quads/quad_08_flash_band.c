// QuadObj, quad_object_update_funcs[8]
// 800D6694..800D67DC
#include "common.h"
extern u16 ready_line_sweep_vertices[8];
extern s16 ready_line_shutter_columns[10];
extern s16 ready_line_shutter_open_vertices[10][4][2];
extern s16 ready_line_shutter_close_vertices[10][4][2];
extern s16 ready_line_streak_vertices[3][4][2];
extern u16 ready_line_shutter_repeats;

void ready_line_converge_vertex(struct QuadObj* arg0, s32 arg1, s32 arg2, const s16 target[2]);

void ready_line_update(struct QuadObj* arg0);

// ready_line_state_funcs state 0
void ready_line_init(struct QuadObj* arg0);

// ready_line_state_funcs state 1
// "READY" never appears if noppped out
//  asm(".rept 20 ; nop ; .endr");
void ready_line_main(struct QuadObj* arg0);

// ready_line_type_funcs state 0
void ready_line_sweep(struct QuadObj* arg0);

// ready_line_type_funcs state 1
void ready_line_shutter(struct QuadObj* arg0);

extern u8 ready_line_streak_shapes[];

// ready_line_type_funcs state 2
void ready_line_streak(struct QuadObj* arg0);

void ready_line_move(struct QuadObj* arg0);

void ready_line_converge_vertex(struct QuadObj* arg0, s32 arg1, s32 arg2, const s16 target[2]);

// ready_line_state_funcs state 2
void ready_line_despawn(struct QuadObj* arg0);

void ready_line_nop(void);

void flash_band_init(struct QuadObj* arg0)
{
    arg0->active |= 0x82;
    arg0->unk34 = 3;
    arg0->unk36 = 0;
    arg0->bg_offset = 0;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    arg0->vertices[1].x.val = 0;
    arg0->vertices[1].y.val = 0;
    arg0->vertices[2].x.val = 0;
    arg0->vertices[2].y.val = 0;
    arg0->vertices[3].x.val = 0;
    arg0->vertices[3].y.val = 0;
    arg0->ext.ready_line.x_vel.val = FIXED(4);
    arg0->state++;
    quad_is_on_screen(arg0);
}

void flash_band_widen(struct QuadObj* arg0)
{
    arg0->vertices[0].x.val += arg0->ext.ready_line.x_vel.val;
    arg0->vertices[3].x.val -= arg0->ext.ready_line.x_vel.val;
    arg0->ext.ready_line.x_vel.val += FIXED(4);
    quad_is_on_screen(arg0);
    if (arg0->vertices[0].x.i.hi >= 0x14B) {
        arg0->state++;
    }
}

void flash_band_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

// QuadObj #8
void flash_band_update(struct QuadObj* arg0)
{
    flash_band_state_funcs[arg0->state](arg0);
}

void (*flash_band_state_funcs[])(struct QuadObj*) = {
    flash_band_init,
    flash_band_widen,
    flash_band_despawn,
};
