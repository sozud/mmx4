// QuadObj, quad_object_update_funcs[3]
// 800D4C50..800D526C
#include "common.h"
extern s16 stage_select_flyout_targets[8][2];

void stage_select_flyout_update(struct QuadObj* arg0);

void stage_select_flyout_scale(struct QuadObj* arg0);

void stage_select_flyout_init(struct QuadObj* self);

void stage_select_flyout_wait(struct QuadObj* arg0);

// boss_warning_quad_init
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

INCLUDE_ASM("main/nonmatchings/quads/quad_03_boss_warning_quad", func_800D4C50);
void boss_warning_quad_open(struct QuadObj* arg0)
{
    u8 integer = arg0->ext.quad_2.x_scale.bytes.integer;

    if (integer == 0) {
        arg0->unk5++;
        if (arg0->unk2 == 0x15) {
            D_8013B960 = 1;
        }
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = integer - 1;
        if (arg0->unk2 == 0x15) {
            arg0->vertices[0].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[0]);
            arg0->vertices[1].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[0]);
            arg0->vertices[2].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[2]);
            arg0->vertices[3].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[2]);
        } else {
            arg0->vertices[2].x.u.hi += boss_warning_quad_motions[arg0->unk2].speed[0] * 2;
            arg0->vertices[3].x.u.hi += boss_warning_quad_motions[arg0->unk2].speed[2] * 2;
            arg0->vertices[2].y.u.hi += boss_warning_quad_motions[arg0->unk2].speed[1] * 2;
            arg0->vertices[3].y.u.hi += boss_warning_quad_motions[arg0->unk2].speed[3] * 2;
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
            D_8013B960 = 0;
        }
    } else {
        arg0->ext.quad_2.x_scale.bytes.integer = integer - 1;
        if (arg0->unk2 == 0x15) {
            arg0->vertices[0].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[2]);
            arg0->vertices[1].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[2]);
            arg0->vertices[2].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[0]);
            arg0->vertices[3].x.val += FIXED(boss_warning_quad_motions[arg0->unk2].speed[0]);
        } else {
            arg0->vertices[1].x.u.hi += boss_warning_quad_motions[arg0->unk2].speed[0] * 2;
            arg0->vertices[0].x.u.hi += boss_warning_quad_motions[arg0->unk2].speed[2] * 2;
            arg0->vertices[1].y.u.hi += boss_warning_quad_motions[arg0->unk2].speed[1] * 2;
            arg0->vertices[0].y.u.hi += boss_warning_quad_motions[arg0->unk2].speed[3] * 2;
        }
    }
}

// boss_warning_quad_main
INCLUDE_ASM("main/nonmatchings/quads/quad_03_boss_warning_quad", func_800D5144);

void boss_warning_quad_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void boss_warning_quad_update(struct QuadObj* arg0)
{
    boss_warning_quad_state_funcs[arg0->state](arg0);
}

u8 boss_warning_quad_blink_levels[16] = { 4, 6, 7, 8, 9, 10, 11, 12, 11, 10, 9, 8, 7, 6, 0, 0 };

void (*boss_warning_quad_step_funcs[])(struct QuadObj*) = {
    boss_warning_quad_open,
    boss_warning_quad_hold,
    boss_warning_quad_close,
};

void (*boss_warning_quad_state_funcs[])(struct QuadObj*) = {
    func_800D4C50,
    func_800D5144,
    boss_warning_quad_despawn,
};
