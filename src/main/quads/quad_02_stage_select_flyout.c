// QuadObj, quad_object_update_funcs[2]
// 800D4948..800D4C50
#include "common.h"
#include "main/quads/quad_02_stage_select_flyout.h"
#include "main/object_motion.h"

// stage_select_flyout_state_funcs
extern void (*stage_select_flyout_state_funcs[])(struct QuadObj*);

extern s32 stage_select_flyout_vertices[4][2];

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

    arg0->vertices[0].x.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->vertices[0].y.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->vertices[1].x.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->vertices[1].y.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->vertices[2].x.val = *p++ * arg0->ext.quad_2.x_scale.value;
    arg0->vertices[2].y.val = *p++ * arg0->ext.quad_2.y_scale.value;
    arg0->vertices[3].x.val = p[0] * arg0->ext.quad_2.x_scale.value;
    arg0->vertices[3].y.val = p[1] * arg0->ext.quad_2.y_scale.value;
}

void stage_select_flyout_init(struct QuadObj* self)
{
    self->active |= 0x90;
    self->unk36 = 0x10;
    self->unk34 = 0x771;
    self->bg_offset = -1;
    self->x_pos.val = FIXED(160);
    self->y_pos.val = FIXED(128);
    self->ext.quad_2.vertices = &stage_select_flyout_vertices[0][0];
    self->ext.quad_2.x_scale.value = 0x100;
    self->ext.quad_2.y_scale.value = 0x100;
    stage_select_flyout_scale(self);
    self->ext.quad_2.direction[0] = angle_from_delta(
        self->x_pos.val - (stage_select_flyout_targets[self->unk2][0] << 16),
        self->y_pos.val - (stage_select_flyout_targets[self->unk2][1] << 16));
    quad_is_on_screen(self);
    self->state++;
}

// stage_select_flyout_main

#if defined(MMX4_PC) || defined(MMX4_SATURN)
u8 func_800D41EC(s32* x, s32* y, s32 target_x, s32 target_y, s32 x_speed, s32 y_speed);
void func_800D4B30(struct QuadObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D4B30(struct QuadObj* arg0)
{
    u8 old_direction;
    u8 direction;
    s16 target_x = stage_select_flyout_targets[(u8)arg0->unk2][0];
    s16 target_y = stage_select_flyout_targets[(u8)arg0->unk2][1];

    arg0->ext.quad_2.x_scale.value += 0xC;
    old_direction = arg0->ext.quad_2.direction[0];
    arg0->ext.quad_2.direction[1] = old_direction;
    arg0->ext.quad_2.y_scale.value += 0xC;
    direction = func_800D41EC(&arg0->x_pos.val, &arg0->y_pos.val,
        (s32)target_x << 16, (s32)target_y << 16, 0x28, 0x28);
    arg0->ext.quad_2.direction[1] = direction;
    if (((direction ^ old_direction) & 0x10) != 0) {
        arg0->x_pos.i.hi = target_x;
        arg0->y_pos.i.hi = target_y;
        arg0->state = 2;
        arg0->unk7 = 0x3C;
    }
    stage_select_flyout_scale(arg0);
    quad_is_on_screen(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_02_stage_select_flyout", func_800D4B30);
#endif

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

// boss_warning_quad_main

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
