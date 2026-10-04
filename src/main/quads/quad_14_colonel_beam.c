// QuadObj, quad_object_update_funcs[14]
// 800D7A54..800D7CEC
#include "common.h"

void colonel_beam_place(struct QuadObj* arg0, u8 arg1);

void colonel_beam_update(struct QuadObj* arg0)
{
    colonel_beam_state_funcs[arg0->state](arg0);
}

void colonel_beam_init(struct QuadObj* arg0)
{
    arg0->active = -0x6D;
    arg0->bg_offset = (u8)g_Player.bg_offset;
    arg0->unk34 = 0x11;
    arg0->unk36 = 2;
    arg0->x_pos.i.hi = 0;
    arg0->y_pos.i.hi = 0;
    colonel_beam_place(arg0, (u8)arg0->unk2);
    arg0->unk5 = 0;
    arg0->state = (u8)arg0->state + 1;
}

void colonel_beam_main(struct QuadObj* arg0)
{
    colonel_beam_step_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
    arg0->on_screen = 1;
}

void colonel_beam_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void colonel_beam_drop(struct QuadObj* arg0)
{
    arg0->vertices[2].y.i.hi += 0x10;
    arg0->vertices[3].y.i.hi += 0x10;
    if (arg0->vertices[2].y.i.hi >= background_objects[0].y_pos.i.hi + 0xC8) {
        arg0->unk5++;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_14_colonel_beam", colonel_beam_widen);
#else
void colonel_beam_widen(struct QuadObj* arg0)
{
    arg0->vertices[0].x.i.hi = arg0->vertices[0].x.i.hi + 3;
    arg0->vertices[1].x.i.hi = arg0->vertices[1].x.i.hi - 3;
    arg0->vertices[2].x.i.hi = arg0->vertices[2].x.i.hi - 6;
    arg0->vertices[3].x.i.hi = arg0->vertices[3].x.i.hi + 6;
    if (arg0->vertices[2].x.i.hi - arg0->vertices[3].x.i.hi >= 0) {
        if (arg0->vertices[2].x.i.hi - arg0->vertices[3].x.i.hi < 0x40) {
            return;
        }
        arg0->unk5++;
    } else if (arg0->vertices[3].x.i.hi - arg0->vertices[2].x.i.hi >= 0x40) {
        arg0->unk5++;
    }
}
#endif

void colonel_beam_wait(struct QuadObj* arg0)
{
    if (arg0->unk5C->unk7 >= 8) {
        arg0->state++;
    }
}

void colonel_beam_place(struct QuadObj* arg0, u8 arg1)
{
    if (arg1) {
        arg0->vertices[0].x.val = arg0->unk5C->x_pos.val + FIXED(-1);
    } else {
        arg0->vertices[0].x.val = g_Player.x_pos.val + FIXED(-1);
    }
    arg0->vertices[0].y.val = 0;
    arg0->vertices[1].x.val = arg0->vertices[0].x.val + FIXED(2);
    arg0->vertices[1].y.val = arg0->vertices[0].y.val;
    arg0->vertices[2].x.val = arg0->vertices[0].x.val;
    arg0->vertices[2].y.val = arg0->vertices[0].y.val + FIXED(1);
    arg0->vertices[3].x.val = arg0->vertices[1].x.val;
    arg0->vertices[3].y.val = arg0->vertices[2].y.val;
}

void (*colonel_beam_state_funcs[])(struct QuadObj*) = {
    colonel_beam_init,
    colonel_beam_main,
    colonel_beam_despawn,
};

void (*colonel_beam_step_funcs[])(struct QuadObj*) = {
    colonel_beam_drop,
    colonel_beam_widen,
    colonel_beam_wait,
};
