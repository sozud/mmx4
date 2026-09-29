// QuadObj, quad_object_update_funcs[1]
// 800D41B0..800D4948
#include "common.h"

void stage_select_panel_update(struct QuadObj* arg0)
{
    stage_select_panel_state_funcs[arg0->state](arg0);
}

// quad_move_toward
INCLUDE_ASM("main/nonmatchings/quads/quad_01", func_800D41EC);

// stage_select_panel_init
INCLUDE_ASM("main/nonmatchings/quads/quad_01", func_800D4334);

// stage_select_panel_main
INCLUDE_ASM("main/nonmatchings/quads/quad_01", func_800D43F4);

void stage_select_panel_idle(struct QuadObj* arg0)
{
    quad_is_on_screen(arg0);
}

void quad_is_on_screen(struct QuadObj* arg0)
{
    u16 w, h;

    arg0->on_screen = 0;

    if (arg0->bg_offset < 0) {
        w = arg0->unk14.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk18.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk14.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->unk18.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->unk1C.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk20.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk1C.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->unk20.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->unk24.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk28.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk24.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->unk28.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->unk2C.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk30.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk2C.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->unk30.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }
}

s16 stage_select_panel_shapes[8][8] = {
    { 8, 16, 80, 16, 93, 78, 33, 78 },
    { 85, 16, 157, 16, 158, 78, 98, 78 },
    { 162, 16, 234, 16, 222, 78, 162, 78 },
    { 239, 16, 311, 16, 286, 78, 226, 78 },
    { 33, 161, 93, 161, 80, 223, 8, 223 },
    { 97, 161, 157, 161, 157, 223, 84, 223 },
    { 162, 161, 222, 161, 235, 223, 162, 223 },
    { 226, 161, 286, 161, 311, 223, 239, 223 },
};

void (*stage_select_panel_state_funcs[])(struct QuadObj*) = {
    func_800D4334,
    func_800D43F4,
    stage_select_panel_idle,
};
