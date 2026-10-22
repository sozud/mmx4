// QuadObj, quad_object_update_funcs[13]
// 800D7A4C..800D7A54
#include "common.h"
#include "main/quads/quad_13_null.h"
#include "weapon_resources.h"

void quad_null_update(struct QuadObj* arg0)
{
#ifdef MMX4_SATURN
    if (arg0->state == 0) {
        arg0->active |= 0x81;
        arg0->unk36 = 0x10;
        arg0->unk34 = 0xFFFF;
        arg0->state = 1;
        arg0->bg_offset = -1;
        arg0->x_pos.val = 0;
        arg0->y_pos.val = 0;
        arg0->vertices[0].x.val = 0;
        arg0->vertices[0].y.val = 0;
        arg0->vertices[1].x.val = 0x1400000;
        arg0->vertices[1].y.val = 0;
        arg0->vertices[2].x.val = 0x1400000;
        arg0->vertices[2].y.val = 0xF00000;
        arg0->vertices[3].x.val = 0;
        arg0->vertices[3].y.val = 0xF00000;
        engine_obj.unk1F = 0;
    }
    arg0->on_screen = 1;
    saturn_queue_frozen_quad(arg0);
#endif
}
