// VisualObj, visual_object_update_funcs[3]
// 800AF6A0..800AF808
#include "common.h"
#include "main/objects.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/object_motion.h"
#include "main/55C4.h"

struct Visual03Bounds {
    s32 x;
    s32 y;
};

extern u8 small_effect_animations[];

extern struct Visual03Bounds small_effect_bounds[];
#include "weapon_resources.h"

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
#ifndef VERSION_DEMO
    0x09,
    0x00,
    0x00,
#endif
};

struct Visual03Bounds small_effect_bounds[DEMO_ALT(14, 13)] = {
#ifndef VERSION_DEMO
    { 0x20, 0x20 },
#endif
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
