// QuadObj, quad_object_update_funcs[15]
// 800D7CEC..800D802C
#include "common.h"

void sigma_beam_init(struct QuadObj* arg0)
{
    struct BaseObj* obj = arg0->unk5C;
    arg0->state++;
    arg0->active = -0x7D;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk36 = 6;
    arg0->unk34 = 0x10;
    arg0->x_pos.i.hi = obj->x_pos.i.hi;
    arg0->y_pos.i.hi = obj->y_pos.i.hi - 0x17;
    arg0->vertices[0].x.i.hi = -2;
    arg0->vertices[1].x.i.hi = 2;
    arg0->vertices[2].x.i.hi = 2;
    arg0->vertices[3].x.i.hi = -2;
    arg0->vertices[0].y.i.hi = 0;
    arg0->vertices[1].y.i.hi = 0;
    arg0->vertices[2].y.i.hi = 0;
    arg0->vertices[3].y.i.hi = 0;
}

void sigma_beam_extend(struct QuadObj* arg0)
{
    arg0->vertices[2].y.i.hi += 4;
    arg0->vertices[3].y.i.hi += 4;
    if (arg0->vertices[2].y.i.hi > 0x40) {
        arg0->ext.unk_ext4.unk3C = 0x2D;
        arg0->unk5++;
    }
}

void sigma_beam_sweep(struct QuadObj* arg0)
{
    struct ShotObj* obj;
    if (--arg0->ext.unk_ext4.unk3C == 0) {
        arg0->unk5 = (u8)arg0->unk5 + 1;
        if (engine_obj.cur_character == CHARACTER_X) {
            arg0->ext.unk_ext4.unk3C = 0xD2U;
            return;
        }
        arg0->ext.unk_ext4.unk3C = 0x46U;
        return;
    }
    if (!(main_bss_state.frame_counter % 4)) {
        obj = find_free_shot_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x2E;
            obj->unk2 = 8;
            obj->unk7C = arg0;
        }
    }
    arg0->vertices[2].x.i.hi += sigma_beam_sweep_speeds[arg0->unk2];
    arg0->vertices[3].x.i.hi += sigma_beam_sweep_speeds[arg0->unk2];
}

void sigma_beam_fade(struct QuadObj* arg0)
{
    struct ShotObj* temp_v0;

    if (!(main_bss_state.frame_counter % 4)) {
        temp_v0 = find_free_shot_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x2E;
            temp_v0->unk2 = 8;
            temp_v0->unk7C = arg0;
        }
    }
    if (arg0->ext.unk_ext4.unk3C == 0) {
        arg0->vertices[0].x.i.hi++;
        arg0->vertices[3].x.i.hi++;
        arg0->vertices[1].x.i.hi--;
        arg0->vertices[2].x.i.hi--;
        if (arg0->vertices[0].x.i.hi == arg0->vertices[1].x.i.hi) {
            arg0->state = 2;
        }
    } else {
        arg0->ext.unk_ext4.unk3C--;
    }
}

void sigma_beam_main(struct QuadObj* arg0)
{
    sigma_beam_step_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
    if (arg0->unk5C->state == 2) {
        arg0->state = 2;
    }
}

void sigma_beam_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void sigma_beam_update(struct QuadObj* arg0)
{
    sigma_beam_state_funcs[arg0->state](arg0);
}

s8 sigma_beam_sweep_speeds[4] = { -6, -3, 6, 3 };

void (*sigma_beam_step_funcs[])(struct QuadObj*) = {
    sigma_beam_extend,
    sigma_beam_sweep,
    sigma_beam_fade,
};

void (*sigma_beam_state_funcs[])(struct QuadObj*) = {
    sigma_beam_init,
    sigma_beam_main,
    sigma_beam_despawn,
};
