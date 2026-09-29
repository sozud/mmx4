// VisualObj, visual_object_update_funcs[3]
// 800AF6A0..800AFB50
#include "common.h"

u8 small_effect_animations[] = {
    0x00,
    0x01,
    0x05,
    0x0A,
    0x0B,
    0x17,
    0x0C,
    0x0D,
    0x11,
    0x12,
    0x0E,
    0x0F,
    0x10,
    0x09,
    0x00,
    0x00,
};

struct Visual03Bounds small_effect_bounds[14] = {
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
};

void small_effect_update(struct VisualObj* arg0)
{
    switch (arg0->state) {
    case 0:
        arg0->on_screen = 1;
        set_animation(arg0, small_effect_animations[arg0->unk2]);
        arg0->state++;
        update_on_screen(BASE_OBJECT(arg0), small_effect_bounds[arg0->unk2].x,
            small_effect_bounds[arg0->unk2].y);
        break;
    case 1:
        if (func_8002B1E8(BASE_OBJECT(arg0),
                small_effect_bounds[arg0->unk2].x,
                small_effect_bounds[arg0->unk2].y)
            == 0) {
            animate_object(arg0);
            if ((arg0->unk2 == 9) && (arg0->animation_step.fields.event != 0)) {
                arg0->animation_step.fields.event = 0;
                g_Player.unkDF = 0;
            }
            if (arg0->animation_step.fields.relative_step < 0) {
                arg0->state = 2;
            }
        } else {
            arg0->state = 2;
        }
        update_on_screen(BASE_OBJECT(arg0), small_effect_bounds[arg0->unk2].x,
            small_effect_bounds[arg0->unk2].y);
        break;
    case 2:
        ZeroObjectState(OBJECT_HEADER(arg0));
        break;
    }
}

void spawn_explosion(struct BaseObj* arg0)
{
    spawn_explosion_variant(arg0, 0);
}

void spawn_explosion_variant(struct BaseObj* arg0, s8 arg1)
{
    spawn_explosion_at(arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi, (get_random() & 1) ^ 1);
}

// spawn_random_explosion
INCLUDE_ASM("main/nonmatchings/visuals/visual_03_small_effect", func_800AF878);

// spawn_explosion_in_box
INCLUDE_ASM("main/nonmatchings/visuals/visual_03_small_effect", func_800AF95C);

struct VisualObj* spawn_explosion_at(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct VisualObj* temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x21;
        temp_v0->id = 4;
        temp_v0->unk2 = arg0;
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unk5C.value = arg3;
        temp_v0->x_pos.i.hi = x;
        temp_v0->x_pos.i.lo = 0;
        temp_v0->y_pos.i.hi = y;
        temp_v0->y_pos.i.lo = 0;
        temp_v0->unk15 = 0;
        temp_v0->bg_offset = 0;
        temp_v0->unk16 = 1;
    }
    return temp_v0;
}
