// QuadObj, quad_object_update_funcs[1]
// 800D41B0..800D4948
#include "common.h"
#include "main/quads/quad_01_stage_select_panel.h"
#include "main/objects.h"

// stage_select_panel_state_funcs
extern void (*stage_select_panel_state_funcs[])(struct QuadObj*);

void stage_select_panel_idle(struct QuadObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/objects.h"
#endif

void stage_select_panel_update(struct QuadObj* arg0)
{
    stage_select_panel_state_funcs[arg0->state](arg0);
}

// quad_move_toward

extern s32 D_800F459C[];
extern s32 D_800F45C0[];
extern s16 stage_select_panel_shapes[8][8];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
u8 func_800D41EC(s32* x, s32* y, s32 target_x, s32 target_y, s32 x_speed, s32 y_speed);
void func_800D4334(struct QuadObj* self);
void func_800D43F4(struct QuadObj* self);
u8 angle_from_delta(s32 arg0, s32 arg1);
extern s32 D_800F459C[];
extern s32 D_800F45C0[];
#endif

u8 func_800D41EC(s32* x, s32* y, s32 target_x, s32 target_y,
    s32 x_speed, s32 y_speed)
{
    u8 direction = angle_from_delta(*x - target_x, *y - target_y);
    s16 table_index;
    s16 x_sign;
    s16 y_sign;

    if (direction < 0x10) {
        if (direction < 8) {
            y_sign = -1;
            table_index = 8 - direction;
            x_sign = 1;
        } else {
            y_sign = -1;
            table_index = direction - 8;
            x_sign = -1;
        }
    } else {
        if (direction < 0x18) {
            y_sign = 1;
            table_index = 0x18 - direction;
            x_sign = -1;
        } else {
            y_sign = 1;
            table_index = direction - 0x18;
            x_sign = 1;
        }
    }
    *x += (D_800F459C[table_index] * x_sign * x_speed) >> 4;
    *y += (D_800F45C0[table_index] * y_sign * y_speed) >> 4;
    return direction;
}

// stage_select_panel_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_01_stage_select_panel", func_800D4334);
#else
void func_800D4334(struct QuadObj* self)
{
    self->unk36 = 0x13;
    self->bg_offset = -1;
    self->vertices[2].y.val = 0x900000;
    self->vertices[3].y.val = 0x900000;
    self->vertices[0].y.val = 0x900000;
    self->vertices[1].y.val = 0x900000;
    self->vertices[2].x.val = 0xA00000;
    self->ext.quad_1.steps = 0x1E;
    self->vertices[3].x.val = 0xA00000;
    self->vertices[0].x.val = 0xA00000;
    self->vertices[1].x.val = 0xA00000;
    self->unk34 = 0;
    self->x_pos.val = 0;
    self->y_pos.val = 0;
    self->ext.quad_1.settled[0] = 0;
    self->ext.quad_1.settled[1] = 0;
    self->ext.quad_1.settled[2] = 0;
    self->ext.quad_1.settled[3] = 0;
    self->ext.quad_1.unk42 = 1;
    self->active |= 0x92;
    if (!(self->unk2 & 0x10)) {
        self->ext.quad_1.delay = self->unk2 << 3;
    } else {
        self->unk2 &= 0xF;
        self->ext.quad_1.delay = 1;
    }
    self->state++;
    quad_is_on_screen(self);
}
#endif

// stage_select_panel_main
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_01_stage_select_panel", func_800D43F4);
#else
void func_800D43F4(struct QuadObj* self)
{
    struct QuadVertex* vertex;
    struct MiscObj* misc;
    struct EffectObj* effect;
    s16* target;
    s32 dx;
    s32 dy;
    s32 i;
    s32 region;

    if (self->ext.quad_1.delay != 0) {
        self->ext.quad_1.delay--;
        quad_is_on_screen(self);
        return;
    }
    vertex = self->vertices;
    for (i = 0; i < 4; i++) {
        target = &stage_select_panel_shapes[self->unk2][i * 2];
        dx = vertex->x.val - (target[0] << 16);
        dy = vertex->y.val - (target[1] << 16);
        region = angle_from_delta(dx, dy);
        if ((((self->ext.quad_1.region[i] ^ region) & 0x10) || self->ext.quad_1.settled[i] != 0) && self->ext.quad_1.unk42 == 0) {
            self->x_pos.i.lo = 0;
            self->y_pos.i.lo = 0;
            self->ext.quad_1.settled[i] = 1;
        } else {
            vertex->x.val -= dx / (s32)self->ext.quad_1.steps;
            vertex->y.val -= dy / (s32)self->ext.quad_1.steps;
            self->ext.quad_1.settled[i] = 0;
            if (i == 3)
                self->ext.quad_1.unk42 = 0;
        }
        vertex++;
        self->ext.quad_1.region[i] = region;
    }
    if (--self->ext.quad_1.steps == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xC;
            misc->unk2 = self->unk2;
        }
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 3;
            effect->unk2 = 0;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xC;
            misc->unk2 = self->unk2 | 0x80;
        }
        target = stage_select_panel_shapes[self->unk2];
        self->vertices[0].x.i.hi = *target++;
        self->vertices[0].y.i.hi = *target++;
        self->vertices[1].x.i.hi = *target++;
        self->vertices[1].y.i.hi = *target++;
        self->vertices[2].x.i.hi = *target++;
        self->vertices[2].y.i.hi = *target++;
        self->vertices[3].x.i.hi = *target;
        self->vertices[3].y.i.hi = target[1];
        self->state = 2;
    }
    quad_is_on_screen(self);
}
#endif

void stage_select_panel_idle(struct QuadObj* arg0)
{
    quad_is_on_screen(arg0);
}

void quad_is_on_screen(struct QuadObj* arg0)
{
    u16 w, h;

    arg0->on_screen = 0;

    if (arg0->bg_offset < 0) {
        w = arg0->vertices[0].x.i.hi + arg0->x_pos.i.hi;
        h = arg0->vertices[0].y.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->vertices[0].x.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->vertices[0].y.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        QUAD_SET_ON_SCREEN(arg0);
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->vertices[1].x.i.hi + arg0->x_pos.i.hi;
        h = arg0->vertices[1].y.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->vertices[1].x.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->vertices[1].y.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        QUAD_SET_ON_SCREEN(arg0);
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->vertices[2].x.i.hi + arg0->x_pos.i.hi;
        h = arg0->vertices[2].y.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->vertices[2].x.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->vertices[2].y.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        QUAD_SET_ON_SCREEN(arg0);
        return;
    }

    if (arg0->bg_offset < 0) {
        w = arg0->vertices[3].x.i.hi + arg0->x_pos.i.hi;
        h = arg0->vertices[3].y.i.hi + arg0->y_pos.i.hi;
    } else {
        w = (arg0->vertices[3].x.i.hi + arg0->x_pos.i.hi) - background_objects[arg0->bg_offset].x_pos.i.hi;
        h = (arg0->vertices[3].y.i.hi + arg0->y_pos.i.hi) - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (w < 320 && h < 240) {
        QUAD_SET_ON_SCREEN(arg0);
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
