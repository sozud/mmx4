// QuadObj, quad_object_update_funcs[2]
// 800D4948..800D514C
#include "common.h"

s16 stage_select_flyout_targets[8][2] = {
    { 0x28, 0x10 },
    { 0x78, 0x10 },
    { 0xC8, 0x10 },
    { 0x118, 0x10 },
    { 0x28, 0xE0 },
    { 0x78, 0xE0 },
    { 0xC8, 0xE0 },
    { 0x118, 0xE0 },
};

void stage_select_flyout_update(struct QuadObj* arg0)
{
    stage_select_flyout_state_funcs[arg0->state](arg0);
}

void stage_select_flyout_scale(struct QuadObj* arg0)
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

void stage_select_flyout_init(struct QuadObj* self)
{
    self->unk36 = 0x10;
    self->unk34 = 0x771;
    self->bg_offset = -1;
    self->x_pos.val = FIXED(160);
    self->y_pos.val = FIXED(128);
    self->ext.quad_2.vertices = &stage_select_flyout_vertices[0][0];
    self->ext.quad_2.x_scale.value = 0x100;
    self->ext.quad_2.y_scale.value = 0x100;
    self->active |= 0x90;
    stage_select_flyout_scale(self);
    self->ext.quad_2.direction[0] = angle_from_delta(
        self->x_pos.val - (stage_select_flyout_targets[self->unk2][0] << 16),
        self->y_pos.val - (stage_select_flyout_targets[self->unk2][1] << 16));
    quad_is_on_screen(self);
    self->state++;
}

// stage_select_flyout_main
INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4B30);

void stage_select_flyout_wait(struct QuadObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->state = 0;
        return;
    }
    arg0->unk7--;
    quad_is_on_screen(arg0);
}

// boss_warning_quad_init
INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D4C50);

void boss_warning_quad_open(struct QuadObj* arg0)
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
            arg0->unk14.val += boss_warning_quad_motions[arg0->unk2].speed[0] << 16;
            arg0->unk1C.val += boss_warning_quad_motions[arg0->unk2].speed[0] << 16;
            arg0->unk24.val += boss_warning_quad_motions[arg0->unk2].speed[2] << 16;
            arg0->unk2C.val += boss_warning_quad_motions[arg0->unk2].speed[2] << 16;
        } else {
            arg0->unk24.u.hi += boss_warning_quad_motions[arg0->unk2].speed[0] * 2;
            arg0->unk2C.u.hi += boss_warning_quad_motions[arg0->unk2].speed[2] * 2;
            arg0->unk28.u.hi += boss_warning_quad_motions[arg0->unk2].speed[1] * 2;
            arg0->unk30.u.hi += boss_warning_quad_motions[arg0->unk2].speed[3] * 2;
        }
    }
}

void boss_warning_quad_hold(struct QuadObj* arg0)
{
    if (arg0->unk2 == 0x15) {
        arg0->ext.quad_2.x_scale.bytes.integer = 0xF;
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = 2;
    }
}

void boss_warning_quad_close(struct QuadObj* arg0)
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
            arg0->unk14.val += boss_warning_quad_motions[arg0->unk2].speed[2] << 16;
            arg0->unk1C.val += boss_warning_quad_motions[arg0->unk2].speed[2] << 16;
            arg0->unk24.val += boss_warning_quad_motions[arg0->unk2].speed[0] << 16;
            arg0->unk2C.val += boss_warning_quad_motions[arg0->unk2].speed[0] << 16;
        } else {
            arg0->unk1C.u.hi += boss_warning_quad_motions[arg0->unk2].speed[0] * 2;
            arg0->unk14.u.hi += boss_warning_quad_motions[arg0->unk2].speed[2] * 2;
            arg0->unk20.u.hi += boss_warning_quad_motions[arg0->unk2].speed[1] * 2;
            arg0->unk18.u.hi += boss_warning_quad_motions[arg0->unk2].speed[3] * 2;
        }
    }
}

// boss_warning_quad_main
INCLUDE_ASM("main/nonmatchings/quads/quad_02", func_800D5144);

void (*stage_select_flyout_state_funcs[])(struct QuadObj*) = {
    stage_select_flyout_init,
    func_800D4B30,
    stage_select_flyout_wait,
};

s32 stage_select_flyout_vertices[4][2] = {
    { -0xF00, -0x700 },
    { 0xF00, -0x700 },
    { 0xF00, 0x700 },
    { -0xF00, 0x700 },
};

struct QuadMotionData boss_warning_quad_motions[22] = {
    { { 0x20, 0x30, 0x2C, 0x30 }, { 2, 12, 2, 12 } },
    { { 0x30, 0x60, 0x34, 0x60 }, { 2, -12, 2, -12 } },
    { { 0x38, 0x30, 0x44, 0x30 }, { 2, 12, 2, 12 } },
    { { 0x48, 0x60, 0x4C, 0x60 }, { 2, -12, 2, -12 } },
    { { 0x54, 0x60, 0x50, 0x60 }, { 5, -12, 5, -12 } },
    { { 0x64, 0x30, 0x70, 0x30 }, { 0, 12, 0, 12 } },
    { { 0x80, 0x60, 0x74, 0x60 }, { 0, -12, 0, -12 } },
    { { 0x76, 0x30, 0x76, 0x34 }, { 7, 0, 7, 0 } },
    { { 0x82, 0x30, 0x92, 0x30 }, { 2, 5, 4, 9 } },
    { { 0x84, 0x50, 0x90, 0x48 }, { 3, 6, 2, 4 } },
    { { 0xA4, 0x60, 0xA0, 0x60 }, { 0, -12, 0, -12 } },
    { { 0xA4, 0x30, 0xA0, 0x40 }, { 8, 8, 8, 8 } },
    { { 0xC4, 0x60, 0xC0, 0x60 }, { 0, -12, 0, -12 } },
    { { 0xC8, 0x30, 0xD4, 0x30 }, { 0, 12, 0, 12 } },
    { { 0xDC, 0x60, 0xD8, 0x60 }, { 0, -12, 0, -12 } },
    { { 0xDC, 0x30, 0xD8, 0x40 }, { 8, 8, 8, 8 } },
    { { 0xFC, 0x60, 0xF8, 0x60 }, { 0, -12, 0, -12 } },
    { { 0x128, 0x30, 0x128, 0x34 }, { -8, 0, -8, 0 } },
    { { 0x108, 0x30, 0x118, 0x30 }, { -2, 6, -2, 6 } },
    { { 0x100, 0x48, 0x110, 0x48 }, { 2, 6, 2, 6 } },
    { { 0x128, 0x60, 0x118, 0x60 }, { 1, -7, 0, -7 } },
    { { 0xA4, 0x64, 0xA4, 0x68 }, { -9, 0, 9, 0 } },
};
