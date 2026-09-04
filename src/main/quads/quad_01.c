// QuadObj, quad_object_update_funcs[1]
// 800D41B0..800D4948
#include "common.h"

void func_800D41B0(struct QuadObj* arg0)
{
    D_8010F71C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_01", func_800D41EC);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_01", func_800D4334);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_01", func_800D43F4);

void func_800D46D4(struct QuadObj* arg0)
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

void (*D_8010F71C[])(struct QuadObj*) = {
    func_800D4334,
    func_800D43F4,
    func_800D46D4,
};
