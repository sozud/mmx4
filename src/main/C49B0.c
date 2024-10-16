#include "common.h"

void func_800D41B0(struct QuadObj* arg0)
{
    D_8010F71C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D41EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4334);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D43F4);

void func_800D46D4(struct QuadObj* arg0)
{
    quad_is_on_screen(arg0);
}

void quad_is_on_screen(struct QuadObj* arg0)
{
    u16 w, h;

    arg0->on_screen = 0;

    if (arg0->unk37 < 0) {
        w = arg0->unk14.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk18.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk14.i.hi + arg0->x_pos.i.hi) - screen_offsets[arg0->unk37 * 2].x_offset;
        h = (arg0->unk18.i.hi + arg0->y_pos.i.hi) - screen_offsets[arg0->unk37 * 2].y_offset;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->unk37 < 0) {
        w = arg0->unk1C.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk20.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk1C.i.hi + arg0->x_pos.i.hi) - screen_offsets[arg0->unk37 * 2].x_offset;
        h = (arg0->unk20.i.hi + arg0->y_pos.i.hi) - screen_offsets[arg0->unk37 * 2].y_offset;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->unk37 < 0) {
        w = arg0->unk24.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk28.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk24.i.hi + arg0->x_pos.i.hi) - screen_offsets[arg0->unk37 * 2].x_offset;
        h = (arg0->unk28.i.hi + arg0->y_pos.i.hi) - screen_offsets[arg0->unk37 * 2].y_offset;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }

    if (arg0->unk37 < 0) {
        w = arg0->unk2C.i.hi + arg0->x_pos.i.hi;
        h = arg0->unk30.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->unk2C.i.hi + arg0->x_pos.i.hi) - screen_offsets[arg0->unk37 * 2].x_offset;
        h = (arg0->unk30.i.hi + arg0->y_pos.i.hi) - screen_offsets[arg0->unk37 * 2].y_offset;
    }
    if (w < 320 && h < 240) {
        arg0->on_screen = 1;
        return;
    }
}

void func_800D4948(struct QuadObj* arg0)
{
    D_8010F748[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4984);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4A64);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4B30);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4C14);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4C50);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4F84);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D4FA0);

INCLUDE_ASM("asm/us/main/nonmatchings/C49B0", func_800D5144);
