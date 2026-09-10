// QuadObj, quad_object_update_funcs[2]
// 800D4948..800D514C
#include "common.h"

s16 D_8010F728[8][2] = {
    { 0x28, 0x10 },
    { 0x78, 0x10 },
    { 0xC8, 0x10 },
    { 0x118, 0x10 },
    { 0x28, 0xE0 },
    { 0x78, 0xE0 },
    { 0xC8, 0xE0 },
    { 0x118, 0xE0 },
};

void func_800D4948(struct QuadObj* arg0)
{
    D_8010F748[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4984);

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4A64);

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4B30);

void func_800D4C14(struct QuadObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->state = 0;
        return;
    }
    arg0->unk7--;
    quad_is_on_screen(arg0);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4C50);

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4DE0);

void func_800D4F84(struct QuadObj* arg0)
{
    if (arg0->unk2 == 0x15) {
        arg0->ext.quad_2.x_scale.bytes.integer = 0xF;
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4FA0);

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D5144);

void (*D_8010F748[])(struct QuadObj*) = {
    func_800D4A64,
    func_800D4B30,
    func_800D4C14,
};
