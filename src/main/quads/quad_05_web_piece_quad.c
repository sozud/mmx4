// QuadObj, quad_object_update_funcs[5]
// 800D553C..800D5934
#include "common.h"

void web_piece_quad_update(struct QuadObj* arg0)
{
    web_piece_quad_state_funcs[arg0->state](arg0);
}

void web_piece_quad_init(struct QuadObj* arg0)
{
    arg0->unk36 = 4;
    arg0->unk34 = 0x7EC0;
    arg0->state = 1;
    arg0->bg_offset = 0;
    arg0->ext.quad_5.scale = 0x100;
    arg0->ext.quad_5.index = 0;
    arg0->ext.quad_5.update_timer = 0;
    arg0->active |= 0x80;
    arg0->ext.quad_5.data = web_piece_quad_frame_table[arg0->ext.quad_5.index];
    web_piece_quad_scale(arg0);
}

void web_piece_quad_main(struct QuadObj* arg0)
{
    u16 temp_v0;
    u16 temp_v1;

    temp_v1 = arg0->ext.quad_5.update_timer;
    if (temp_v1 < 2U) {
        arg0->ext.quad_5.update_timer = temp_v1 + 1;
    } else {
        temp_v1 = arg0->ext.quad_5.index;
        temp_v0 = arg0->ext.quad_5.scale;
        arg0->ext.quad_5.update_timer = 0;
        temp_v1 = (temp_v1 + 1) & 7;
        arg0->ext.quad_5.index = temp_v1;
        temp_v0 += 0x40;
        arg0->ext.quad_5.scale = temp_v0;
        if ((u32)temp_v0 >= 0x501U) {
            arg0->ext.quad_5.scale = 0x100;
        }
    }

    arg0->ext.quad_5.data = web_piece_quad_frame_table[arg0->ext.quad_5.index];
    web_piece_quad_scale(arg0);
    if ((web_piece_quad_is_visible(arg0) << 16) != 0) {
        arg0->on_screen = 1;
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

void web_piece_quad_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void web_piece_quad_scale(struct QuadObj* arg0)
{
    s32* p = arg0->ext.quad_5.data;

    arg0->vertices[0].x.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[0].y.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[1].x.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[1].y.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[2].x.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[2].y.val = *p++ * arg0->ext.quad_5.scale;
    arg0->vertices[3].x.val = p[0] * arg0->ext.quad_5.scale;
    arg0->vertices[3].y.val = p[1] * arg0->ext.quad_5.scale;
}

s32 web_piece_quad_is_visible(struct QuadObj* arg0)
{
    u16 x, y, x2, y2;
    u16 width, height;
    s32 x_p, y_p;
    s32 result;

    result = 0;
    x = arg0->x_pos.u.hi - background_objects[arg0->bg_offset].x_pos.u.hi;
    y = arg0->y_pos.u.hi - background_objects[arg0->bg_offset].y_pos.u.hi;
    width = ABS(arg0->vertices[1].x.i.hi, arg0->vertices[0].x.i.hi);
    height = ABS(arg0->vertices[3].y.i.hi, arg0->vertices[0].y.i.hi);
    if (ON_SCREEN_X(x, width)) {
        if (ON_SCREEN_Y(y, height)) {
            result = 1;
        }
    }
    x_p = arg0->x_pos.u.hi + arg0->vertices[0].x.u.hi;
    y_p = arg0->y_pos.u.hi + arg0->vertices[0].y.u.hi;
    x2 = x_p + (u16)(width >> 1) - background_objects[arg0->bg_offset].x_pos.u.hi;
    y2 = y_p + (u16)(height >> 1) - background_objects[arg0->bg_offset].y_pos.u.hi;
    if (ON_SCREEN_X(x2, width)) {
        if (ON_SCREEN_Y(y2, height)) {
            result = 1;
        }
    }
    return result;
}

s32 web_piece_quad_frames[8][8] = {
    { 0, -0x800, 0x800, 0, 0, 0x800, -0x800, 0 },
    { 0, -0x800, 0x700, 0, 0, 0x800, -0x700, 0 },
    { 0, -0x800, 0x600, 0, 0, 0x800, -0x600, 0 },
    { 0, -0x800, 0x500, 0, 0, 0x800, -0x500, 0 },
    { 0, -0x800, 0x400, 0, 0, 0x800, -0x400, 0 },
    { 0, -0x800, 0x300, 0, 0, 0x800, -0x300, 0 },
    { 0, -0x800, 0x200, 0, 0, 0x800, -0x200, 0 },
    { 0, -0x800, 0x100, 0, 0, 0x800, 0x100, 0 },
};

s32* web_piece_quad_frame_table[8] = {
    web_piece_quad_frames[0],
    web_piece_quad_frames[1],
    web_piece_quad_frames[2],
    web_piece_quad_frames[3],
    web_piece_quad_frames[4],
    web_piece_quad_frames[5],
    web_piece_quad_frames[6],
    web_piece_quad_frames[7],
};

void (*web_piece_quad_state_funcs[])(struct QuadObj*) = {
    web_piece_quad_init,
    web_piece_quad_main,
    web_piece_quad_despawn,
};
