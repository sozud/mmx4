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

void func_800D4984(struct QuadObj* arg0)
{
    s32* p = arg0->ext.quad_2.vertices;

    arg0->unk14.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->unk18.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->unk1C.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->unk20.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->unk24.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->unk28.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->unk2C.val = p[0] * arg0->ext.quad_2.x_scale.value;
    arg0->unk30.val = p[1] * arg0->ext.quad_2.y_scale.value;
}

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

void func_800D4DE0(struct QuadObj* arg0)
{
    u8 integer = arg0->ext.quad_2.x_scale.bytes.integer;

    if (integer == 0) {
        arg0->unk5++;
        if (arg0->unk2 == 0x15) {
            D_8013B960[0] = 1;
        }
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = integer - 1;
        if (arg0->unk2 == 0x15) {
            arg0->unk14.val += D_8010F878[0] << 16;
            arg0->unk1C.val += D_8010F77C[arg0->unk2].speed[0] << 16;
            arg0->unk24.val += D_8010F77C[arg0->unk2].speed[2] << 16;
            arg0->unk2C.val += D_8010F77C[arg0->unk2].speed[2] << 16;
        } else {
            arg0->unk24.u.hi += D_8010F77C[arg0->unk2].speed[0] * 2;
            arg0->unk2C.u.hi += D_8010F77C[arg0->unk2].speed[2] * 2;
            arg0->unk28.u.hi += D_8010F77C[arg0->unk2].speed[1] * 2;
            arg0->unk30.u.hi += D_8010F77C[arg0->unk2].speed[3] * 2;
        }
    }
}

void func_800D4F84(struct QuadObj* arg0)
{
    if (arg0->unk2 == 0x15) {
        arg0->ext.quad_2.x_scale.bytes.integer = 0xF;
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = 2;
    }
}

void func_800D4FA0(struct QuadObj* arg0)
{
    u8 integer = arg0->ext.quad_2.x_scale.bytes.integer;

    if (integer == 0) {
        arg0->state++;
        if (arg0->unk2 == 0x15) {
            D_8013B960[0] = 0;
        }
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = integer - 1;
        if (arg0->unk2 == 0x15) {
            arg0->unk14.val += D_8010F878[2] << 16;
            arg0->unk1C.val += D_8010F77C[arg0->unk2].speed[2] << 16;
            arg0->unk24.val += D_8010F77C[arg0->unk2].speed[0] << 16;
            arg0->unk2C.val += D_8010F77C[arg0->unk2].speed[0] << 16;
        } else {
            arg0->unk1C.u.hi += D_8010F77C[arg0->unk2].speed[0] * 2;
            arg0->unk14.u.hi += D_8010F77C[arg0->unk2].speed[2] * 2;
            arg0->unk20.u.hi += D_8010F77C[arg0->unk2].speed[1] * 2;
            arg0->unk18.u.hi += D_8010F77C[arg0->unk2].speed[3] * 2;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D5144);

void (*D_8010F748[])(struct QuadObj*) = {
    func_800D4A64,
    func_800D4B30,
    func_800D4C14,
};
