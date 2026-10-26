// QuadObj, quad_object_update_funcs[6]
// 800D5934..800D5C54
#include "common.h"
#include "main/quads/quad_06_light_ray.h"
#include "main/objects.h"
#include "main/object_motion.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

// light_ray_state_funcs
extern void (*light_ray_state_funcs[])(struct QuadObj*);

void light_ray_main(struct QuadObj*);
void light_ray_despawn(struct QuadObj*);

// light_ray_init

#define QUAD6_ANGLE(obj) ((obj)->ext.ready_line.x_vel.bytes[0])
#define QUAD6_DELAY(obj) ((obj)->ext.ready_line.x_vel.bytes[1])
#define QUAD6_AGE(obj) ((obj)->ext.ready_line.x_vel.bytes[2])
#define QUAD6_X_SPEED(obj) ((obj)->ext.ready_line.y_vel.val)
#define QUAD6_Y_SPEED(obj) ((obj)->ext.ready_line.x_accel.val)
#define QUAD6_X_SPEED2(obj) ((obj)->ext.ready_line.y_accel.val)
#define QUAD6_Y_SPEED2(obj) ((obj)->runtime.search_light.x_accumulator)
#define QUAD6_X_ACCEL(obj) ((obj)->runtime.search_light.y_accumulator)
#define QUAD6_Y_ACCEL(obj) (*(s32*)&(obj)->runtime.search_light.pause_timer)
#define QUAD6_X_ACCEL2(obj) ((obj)->runtime.search_light.base_speed)
#define QUAD6_Y_ACCEL2(obj) ((obj)->link.y_accel)
extern s32 D_800F459C[];
extern s32 D_800F45C0[];

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_06_light_ray", func_800D5934);
#else
void func_800D5934(struct QuadObj* arg0)
{
    u8 angle;
    s16 index;
    s16 x_sign;
    s16 y_sign;

    arg0->active |= 0x82;
    arg0->unk36 = 0;
    arg0->unk34 = 1;
    arg0->bg_offset = 0;
    QUAD6_ANGLE(arg0) = get_random() & 0x1F;
    angle = QUAD6_ANGLE(arg0);
    if (angle < 0x10) {
        x_sign = -1;
        if (angle < 8) {
            index = 8 - angle;
            y_sign = 1;
        } else {
            index = angle - 8;
            y_sign = -1;
        }
    } else {
        x_sign = 1;
        if (angle < 0x18) {
            index = 0x18 - angle;
            y_sign = -1;
        } else {
            index = angle - 0x18;
            y_sign = 1;
        }
    }
#ifdef MMX4_PC
    QUAD6_X_SPEED(arg0) = (s32)((u32)(D_800F459C[index] * y_sign) << 4) >> 4;
    QUAD6_Y_SPEED(arg0) = (s32)((u32)(D_800F45C0[index] * x_sign) << 4) >> 4;
#else
    QUAD6_X_SPEED(arg0) = (D_800F459C[index] * y_sign * 16) >> 4;
    QUAD6_Y_SPEED(arg0) = (D_800F45C0[index] * x_sign * 16) >> 4;
#endif
    QUAD6_X_SPEED2(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_X_ACCEL(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_Y_SPEED2(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_Y_ACCEL(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_X_ACCEL2(arg0) = QUAD6_X_SPEED2(arg0) / 2;
    QUAD6_Y_ACCEL2(arg0) = QUAD6_Y_SPEED2(arg0) / 2;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    arg0->vertices[1].x.val = 0;
    arg0->vertices[1].y.val = 0;
    arg0->vertices[2].x.val = 0;
    arg0->vertices[2].y.val = 0;
    arg0->vertices[3].x.val = 0;
    arg0->vertices[3].y.val = 0;
    QUAD6_DELAY(arg0) = 4;
    QUAD6_AGE(arg0) = 0;
    arg0->state++;
}
#endif

void light_ray_main(struct QuadObj* arg0)
{
    if (++arg0->ext.ready_line.x_vel.bytes[2] == 0) {
        arg0->ext.ready_line.x_vel.bytes[2] = 0xFE;
    }

    arg0->vertices[0].x.val += arg0->ext.ready_line.y_vel.val;
    arg0->vertices[0].y.val += arg0->ext.ready_line.x_accel.val;
    arg0->vertices[2].x.val += arg0->ext.ready_line.y_accel.val;
    arg0->vertices[2].y.val += arg0->runtime.quad_06.x_accumulator;
    arg0->ext.ready_line.y_vel.val += arg0->runtime.quad_06.y_accumulator;
    arg0->ext.ready_line.x_accel.val += arg0->runtime.quad_06.acceleration;
    arg0->ext.ready_line.y_accel.val += arg0->runtime.quad_06.base_speed;
    arg0->runtime.quad_06.x_accumulator += arg0->link.y_accel;
    arg0->vertices[1].x.val = arg0->vertices[0].x.val + FIXED(1);
    arg0->vertices[1].y.val = arg0->vertices[0].y.val + FIXED(1);
    arg0->vertices[3].x.val = arg0->vertices[2].x.val - FIXED(1);
    arg0->vertices[3].y.val = arg0->vertices[2].y.val - FIXED(1);

    if (arg0->ext.ready_line.x_vel.bytes[1] != 0) {
        arg0->ext.ready_line.x_vel.bytes[1]--;
    } else {
        quad_is_on_screen(arg0);
        if (arg0->on_screen == 0 && arg0->ext.ready_line.x_vel.bytes[2] > 60) {
            arg0->state++;
        }
    }
}

void light_ray_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void light_ray_update(struct QuadObj* arg0)
{
    light_ray_state_funcs[arg0->state](arg0);
}

void (*light_ray_state_funcs[])(struct QuadObj*) = {
    func_800D5934,
    light_ray_main,
    light_ray_despawn,
};
