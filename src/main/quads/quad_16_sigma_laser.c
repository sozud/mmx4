// QuadObj, quad_object_update_funcs[16]
// 800D802C..800D8648
#include "common.h"
#include "main/quads/quad_16_sigma_laser.h"
#include "main/objects.h"
#include "main/visuals/visual_03_small_effect.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/visuals/visual_03_small_effect.h"
#endif

extern u8 sigma_laser_flash_colors[];

extern s16 sigma_laser_end_offsets[8][2];

// sigma_laser_step_funcs
extern void (*sigma_laser_step_funcs[])(struct QuadObj*);
void sigma_laser_wait(struct QuadObj*);
void func_800D8180(struct QuadObj*);
void sigma_laser_flash(struct QuadObj*);
void func_800D82E8(struct QuadObj*);

// sigma_laser_cancel_funcs
extern void (*sigma_laser_cancel_funcs[])(struct QuadObj*);
void sigma_laser_cancel_wait(struct QuadObj*);

// sigma_laser_state_funcs
extern void (*sigma_laser_state_funcs[])(struct QuadObj*);
void sigma_laser_cancel(struct QuadObj*);

void sigma_laser_main(struct QuadObj*);
void sigma_laser_despawn(struct QuadObj*);
void sigma_laser_cancel(struct QuadObj*);

// sigma_laser_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D802C(struct QuadObj* self);
void func_800D845C(struct QuadObj* self);
// src/main/quads/quad_16_sigma_laser.c

extern s16 sigma_laser_origin_offsets[2][2];
extern s16 sigma_laser_start_offsets[8][2];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D802C(struct QuadObj* self)
{
    s32 i;
    s16(*offsets)[2];

    self->unk36 = self->bg_offset = 0;
    self->x_pos.val = self->y_pos.val = 0;
    self->active |= 0x92;
    if ((self->unk2 & 0x10) == 0) {
        self->ext.unk38 = 20;
        self->state = 1;
        self->unk34 = 0x12;

        for (i = 0; i < 4; i++) {
            s32 pair = self->unk2 * 4 + i;
            offsets = pair < 2 ? &sigma_laser_origin_offsets[pair]
                               : &sigma_laser_sweep_offsets[pair - 2];
            self->vertices[i].x.val = (s32)(*offsets)[0] * 65536;
            self->vertices[i].y.val = (s32)(*offsets)[1] * 65536;
        }
    } else {
        self->unk2 &= 1;
        self->ext.unk38 = 15;
        self->state = 3;
        self->unk34 = 0x13;
        for (i = 0; i < 4; i++) {
            offsets = &sigma_laser_start_offsets[self->unk2 * 4 + i];
            self->vertices[i].x.val = (s32)(*offsets)[0] * 65536;
            self->vertices[i].y.val = (s32)(*offsets)[1] * 65536;
        }
    }
    quad_is_on_screen(self);
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_16_sigma_laser", func_800D802C);
#endif

void sigma_laser_wait(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 8;
        arg0->unk5++;
    }
}

// sigma_laser_charge
void func_800D8180(struct QuadObj* quad)
{
    struct MainObj* owner = MAIN_OBJECT(quad->unk5C);
    s32* out;
    s16* to;
    s16* from;
    s16 base;
    s32 delta;
    u32 i;

    if (--quad->ext.unk38 != 0) {
        out = &quad->vertices[2].x.val;
        to = &sigma_laser_end_offsets[quad->unk2 * 2][0];
        from = &sigma_laser_sweep_offsets[quad->unk2 * 4][0];
        for (i = 0; i < 4; i++) {
            base = *from;
            delta = ((s32)(*to - base) * 65536) >> 3;
            delta *= 8 - quad->ext.unk38;
            *out = delta + FIXED(base);
            to++;
            out++;
            from++;
        }
        return;
    }
    to = &sigma_laser_end_offsets[quad->unk2 * 2][0];
    quad->vertices[2].x.val = FIXED(*to++);
    quad->vertices[2].y.val = FIXED(*to++);
    quad->vertices[3].x.val = FIXED(*to++);
    quad->vertices[3].y.val = FIXED(*to);
    quad->ext.unk38 = 0x2F;
    owner->ext.main_74.pad95 = 1;
    quad->unk5++;
}

void sigma_laser_flash(struct QuadObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk5C);
    arg0->ext.unk38--;
    if (arg0->ext.unk38 == 0) {
        arg0->unk34 = 0x12;
        arg0->ext.unk38 = 0x10;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        owner->ext.main_74.pad95 = 0;
    } else {
        arg0->unk34 = sigma_laser_flash_colors[arg0->ext.unk38 & 3];
    }
}

// sigma_laser_fire
void func_800D82E8(struct QuadObj* quad)
{
    s32* out;
    s16* to;
    s16* from;
    s16 base;
    s32 delta;
    u32 i;

    if (--quad->ext.unk38 != 0) {
        out = &quad->vertices[2].x.val;
        to = &sigma_laser_end_offsets[quad->unk2 * 2][0];
        from = &sigma_laser_sweep_offsets[quad->unk2 * 4][0];
        for (i = 0; i < 4; i++) {
            base = *from;
            delta = ((s32)(*to - base) * 65536) >> 4;
            delta *= quad->ext.unk38;
            *out = delta + FIXED(base);
            to++;
            out++;
            from++;
        }
        return;
    }
    to = &sigma_laser_sweep_offsets[quad->unk2 * 4][0];
    quad->vertices[2].x.val = FIXED(*to++);
    quad->vertices[2].y.val = FIXED(*to++);
    quad->vertices[3].x.val = FIXED(*to++);
    quad->vertices[3].y.val = FIXED(*to);
    quad->state = 2;
    quad->unk5 = 0;
}

void sigma_laser_main(struct QuadObj* arg0)
{
    sigma_laser_step_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void sigma_laser_cancel_wait(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 0x10;
        arg0->unk5++;
    }
}

// sigma_laser_cancel_shrink
void func_800D845C(struct QuadObj* self)
{
    struct MainObj* owner = MAIN_OBJECT(self->unk5C);

    if (--self->ext.unk38 != 0) {
        if (self->unk2 != 0) {
            self->vertices[2].x.val += FIXED(56);
            self->vertices[3].x.val += FIXED(56);
            ((struct VisualObj * (*)(s32, s32, s32, s32)) spawn_explosion_at)(1, 0x400 + (0x10 - self->ext.unk38) * 0x1E, 0x2E0, 1);
        } else {
            self->vertices[2].y.val += FIXED(-20);
            self->vertices[3].y.val += FIXED(-20);
            ((struct VisualObj * (*)(s32, s32, s32, s32)) spawn_explosion_at)(1, 0x430, 0x2F0 - (0x10 - self->ext.unk38) * 0x12, 0);
        }
        if ((u32)(self->ext.unk38 - 5) < 7) {
            owner->ext.main_74.pad95 = 1;
        } else {
            owner->ext.main_74.pad95 = 0;
        }
    } else {
        self->state = 2;
        self->unk5++;
    }
}

void sigma_laser_cancel(struct QuadObj* arg0)
{
    sigma_laser_cancel_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void sigma_laser_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void sigma_laser_update(struct QuadObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk5C);

    if (owner->ext.main_74.death_kind != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        owner->ext.main_74.pad95 = 0;
    }
    sigma_laser_state_funcs[arg0->state](arg0);
}

s16 sigma_laser_origin_offsets[2][2] = {
    { 0x50E, 0x29C },
    { 0x50D, 0x29B },
};

s16 sigma_laser_sweep_offsets[14][2] = {
    { 0x492, 0x2F0 },
    { 0x493, 0x2F0 },
    { 0x4FF, 0x279 },
    { 0x4FE, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D1 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x410, 0x28B },
    { 0x410, 0x28C },
    { 0x4FB, 0x231 },
    { 0x4FA, 0x230 },
    { 0x410, 0x230 },
    { 0x410, 0x231 },
};

s16 sigma_laser_start_offsets[8][2] = {
    { 0x4FF, 0x279 },
    { 0x4FD, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D4 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x2C0, 0x2F0 },
    { 0x2C4, 0x2F0 },
};

s16 sigma_laser_end_offsets[8][2] = {
    { 0x453, 0x2F0 },
    { 0x4D5, 0x2F0 },
    { 0x410, 0x2AF },
    { 0x410, 0x300 },
    { 0x410, 0x273 },
    { 0x410, 0x2C3 },
    { 0x410, 0x20B },
    { 0x410, 0x263 },
};

u8 sigma_laser_flash_colors[4] = { 0x12, 0x13, 0x14, 0x13 };

void (*sigma_laser_step_funcs[])(struct QuadObj*) = {
    sigma_laser_wait,
    func_800D8180,
    sigma_laser_flash,
    func_800D82E8,
};

void (*sigma_laser_cancel_funcs[])(struct QuadObj*) = {
    sigma_laser_cancel_wait,
    func_800D845C,
};

void (*sigma_laser_state_funcs[])(struct QuadObj*) = {
    func_800D802C,
    sigma_laser_main,
    sigma_laser_despawn,
    sigma_laser_cancel,
};
