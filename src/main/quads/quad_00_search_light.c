// QuadObj, quad_object_update_funcs[0]
// 800D3AC0..800D41B0
#include "common.h"
#include "main/quads/quad_00_search_light.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern void (*g_SearchLightUpdateFuncs[3])(struct QuadObj*);

extern s32 search_light_speeds[3];
extern struct SearchLightColorLookup search_light_colors;
extern struct SearchLightIntensityLookup search_light_blend_modes;

#ifdef MMX4_PC
extern void search_light_move(struct Unk22* arg0);
#endif

// D_8010F690
void search_light_init(struct QuadObj*);

void search_light_despawn(struct QuadObj*);
#include "weapon_resources.h"

// search lights in background of intro stage
void SearchLightUpdate(struct QuadObj* arg0)
{
    g_SearchLightUpdateFuncs[arg0->state](arg0);
}

// SearchLight state 0
void search_light_init(struct QuadObj* arg0)
{
    u16 temp_a0;
    struct SearchLightInit* temp_v0;
    s8 temp = arg0->unk2;

    arg0->active |= 0x90;
    arg0->unk36 = search_light_blend_modes.values[arg0->unk2 >> 1];
    temp_a0 = search_light_colors.values[temp >> 1];
    temp_v0 = &search_light_shapes[arg0->unk2];
    arg0->state = 1;
    arg0->unk34 = temp_a0;
    arg0->vertices[0].x.i.hi = temp_v0->vertices[0];
    arg0->vertices[0].y.i.hi = temp_v0->vertices[1];
    arg0->vertices[1].x.i.hi = temp_v0->vertices[2];
    arg0->vertices[1].y.i.hi = temp_v0->vertices[3];
    arg0->vertices[2].x.i.hi = temp_v0->vertices[4];
    arg0->vertices[2].y.i.hi = temp_v0->vertices[5];
    arg0->vertices[3].x.i.hi = temp_v0->vertices[6];
    arg0->vertices[3].y.i.hi = temp_v0->vertices[7];
    arg0->runtime.search_light.extent = temp_v0->extent;
    arg0->runtime.search_light.x_accumulator = 0;
    arg0->runtime.search_light.y_accumulator = 0;
    arg0->ext.search_light.velocity = search_light_speeds[arg0->unk2 >> 1];
    if (!(get_random() & 3)) {
        arg0->ext.search_light.velocity += 0x4000;
    }
    arg0->ext.search_light.vertical_velocity = 0;
    arg0->ext.search_light.acceleration = 0;
    arg0->ext.search_light.vertical_acceleration = 0;
    arg0->runtime.search_light.pause_timer = 0;
    arg0->link.direction = 0;
    arg0->runtime.search_light.base_speed = arg0->ext.search_light.velocity;
}

// SearchLight state 1
// search_light_sweep

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D3C58(struct QuadObj* arg0);
extern s32 search_light_accels[3];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D3C58(struct QuadObj* arg0)
{
    const struct SearchLightInit* init = &search_light_shapes[(u8)arg0->unk2];
    s16 origin = init->vertices[0];
    s16 span = (s16)(init->vertices[2] - origin);
    s32 x_accum = arg0->runtime.search_light.x_accumulator;
    s32 y_accum = arg0->runtime.search_light.y_accumulator;
    u16 direction = arg0->link.direction;

    if (arg0->runtime.search_light.pause_timer != 0) {
        arg0->runtime.search_light.pause_timer--;
    } else {
        x_accum += arg0->ext.search_light.velocity;
        y_accum += arg0->ext.search_light.vertical_velocity;
        arg0->ext.search_light.velocity += arg0->ext.search_light.acceleration;
        arg0->ext.search_light.vertical_velocity += arg0->ext.search_light.vertical_acceleration;
        arg0->vertices[0].x.val += arg0->ext.search_light.velocity;
        arg0->vertices[1].x.val += arg0->ext.search_light.velocity;
        switch (arg0->unk5) {
        case 0:
            if ((!direction && arg0->vertices[0].x.i.hi >= (s16)(arg0->runtime.search_light.extent + origin - 0x20)) || (direction && arg0->vertices[0].x.i.hi <= (s16)(origin + 0x20 - arg0->runtime.search_light.extent))) {
                arg0->unk5 = 1;
                arg0->ext.search_light.acceleration = direction
                    ? search_light_accels[(u8)arg0->unk2 >> 1]
                    : -search_light_accels[(u8)arg0->unk2 >> 1];
            }
            break;
        case 1:
            if (!direction) {
                if (arg0->ext.search_light.velocity <= 0x7FFF) {
                    arg0->ext.search_light.velocity = 0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->vertices[0].x.i.hi >= (s16)(origin + arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->vertices[0].x.val = 0;
                    arg0->vertices[1].x.val = 0;
                    arg0->vertices[0].x.i.hi = origin + arg0->runtime.search_light.extent;
                    arg0->vertices[1].x.i.hi = span + origin + arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            } else {
                if (arg0->ext.search_light.velocity >= -0x7FFF) {
                    arg0->ext.search_light.velocity = -0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->vertices[0].x.i.hi <= (s16)(origin - arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->vertices[0].x.val = 0;
                    arg0->vertices[1].x.val = 0;
                    arg0->vertices[0].x.i.hi = origin - arg0->runtime.search_light.extent;
                    arg0->vertices[1].x.i.hi = span + origin - arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            }
            break;
        case 2:
            arg0->ext.search_light.acceleration = direction
                ? -search_light_accels[(u8)arg0->unk2 >> 1]
                : search_light_accels[(u8)arg0->unk2 >> 1];
            arg0->unk5 = 3;
            arg0->runtime.search_light.base_speed = -arg0->runtime.search_light.base_speed;
            break;
        case 3:
            if ((!direction && arg0->vertices[0].x.i.hi >= (s16)(origin + 0x20 - arg0->runtime.search_light.extent)) || (direction && arg0->vertices[0].x.i.hi <= (s16)(arg0->runtime.search_light.extent + origin - 0x20))) {
                arg0->ext.search_light.acceleration = 0;
                arg0->unk5 = 0;
                arg0->ext.search_light.velocity = arg0->runtime.search_light.base_speed;
            }
            break;
        }
        arg0->runtime.search_light.x_accumulator = x_accum;
        arg0->runtime.search_light.y_accumulator = y_accum;
        arg0->link.direction = direction;
    }
    if (search_light_is_visible(arg0)) {
        QUAD_SET_ON_SCREEN(arg0);
    } else {
        arg0->on_screen = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_00_search_light", func_800D3C58);
#endif

// SearchLight state 2
void search_light_despawn(struct QuadObj* arg0)
{
    OBJECT_HEADER(arg0->backref)->active = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

// search light helper
void search_light_move(struct Unk22* arg0)
{
    arg0->unk48 += arg0->unk38;
    arg0->unk4C += arg0->unk40;
    arg0->unk38 += arg0->unk3C;
    arg0->unk40 += arg0->unk44;
}

// search light helper
s32 search_light_is_visible(struct QuadObj* arg0)
{
    u16 x, y, x2, y2;
    u16 width, height;
    s32 x_p, y_p;
    s32 visible;

    visible = 0;
    x = arg0->x_pos.u.hi - background_objects[arg0->bg_offset].x_pos.u.hi;
    y = arg0->y_pos.u.hi - background_objects[arg0->bg_offset].y_pos.u.hi;
    width = ABS(arg0->vertices[1].x.i.hi, arg0->vertices[0].x.i.hi);
    height = ABS(arg0->vertices[3].y.i.hi, arg0->vertices[0].y.i.hi);
    if (ON_SCREEN_X(x, width)) {
        if (ON_SCREEN_Y(y, height)) {
            visible = 1;
        }
    }
    x_p = arg0->x_pos.u.hi + arg0->vertices[0].x.u.hi;
    y_p = arg0->y_pos.u.hi + arg0->vertices[0].y.u.hi;
    x2 = x_p + (u16)(width >> 1) - background_objects[arg0->bg_offset].x_pos.u.hi;
    y2 = y_p + (u16)(height >> 1) - background_objects[arg0->bg_offset].y_pos.u.hi;
    if (ON_SCREEN_X(x2, width)) {
        if (ON_SCREEN_Y(y2, height)) {
            visible = 1;
        }
    }
    return visible;
}

struct SearchLightInit search_light_shapes[6] = {
    { { 0x0000, -0x0100, 0x0080, -0x0100, 0x0028, 0, 0, 0 }, 0x0060 },
    { { -0x0080, -0x0100, 0x0000, -0x0100, 0x0028, 0, 0, 0 }, 0x0060 },
    { { 0x0000, -0x0100, 0x0050, -0x0100, 0x0010, 0, 0, 0 }, 0x0080 },
    { { -0x0050, -0x0100, 0x0000, -0x0100, 0x0010, 0, 0, 0 }, 0x0080 },
    { { 0x0000, -0x0050, 0x0010, -0x0050, 0x0002, 0, 0, 0 }, 0x0030 },
    { { -0x0010, -0x0050, 0x0000, -0x0050, 0x0002, 0, 0, 0 }, 0x0030 },
};

s32 search_light_speeds[3] = { 0x28000, 0x20000, 0x10000 };
s32 search_light_accels[3] = { 0x2000, 0x1000, 0x0400 };

struct SearchLightColorLookup search_light_colors = {
#ifdef MMX4_SATURN
    { 0x0771, 0x0772, 0x0773 },
#else
    { 0x33ff, 0x179e, 0x0e9c },
#endif
    0,
};
struct SearchLightIntensityLookup search_light_blend_modes = {
    { 0x10, 0x20, 0x30 },
    0,
};

void (*g_SearchLightUpdateFuncs[3])(struct QuadObj*) = {
    search_light_init,
    func_800D3C58,
    search_light_despawn,
};
