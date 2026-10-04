// LayerObj, layer_object_update_funcs[1]
// 800D8ED4..800D9218
#include "common.h"

void jungle_parallax_section_0_setup(struct LayerObj* arg0);
void jungle_parallax_section_1_done(struct LayerObj* arg0);
void jungle_parallax_section_1_setup(struct LayerObj* arg0);
void jungle_parallax_section_2_setup(struct LayerObj* arg0);
void jungle_parallax_update_section(struct LayerObj* arg0);

void jungle_parallax_section_0_scroll(struct LayerObj* arg0);
void jungle_parallax_section_2_scroll(struct LayerObj* arg0);

s16 train_scroll_unused_positions[2] = { 0x450, 0xA00 };

void jungle_parallax_update(struct LayerObj* arg0)
{
    jungle_parallax_state_funcs[arg0->state](arg0);
}

void jungle_parallax_init(struct LayerObj* arg0)
{
    arg0->unk5 = 2;
    arg0->bg_offset = 3;
    arg0->state++;
    jungle_parallax_main(arg0);
}

void jungle_parallax_main(struct LayerObj* arg0)
{
    arg0->unk15 = arg0->bg_offset;
    jungle_parallax_update_section(arg0);
    jungle_parallax_section_funcs[arg0->unk5](arg0);
}

void jungle_parallax_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        jungle_parallax_section_0_setup(arg0);
    } else {
        jungle_parallax_section_0_scroll(arg0);
    }
}

void jungle_parallax_section_0_setup(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0x28;
    arg0->unk6++;
}

void jungle_parallax_section_0_scroll(struct LayerObj* arg0)
{
    struct BackgroundObj* background = &background_objects[1];
    volatile struct BackgroundObj* camera = background - 1;
    background->x_pos.i.hi = background->unk40 + (camera->x_pos.i.hi + (camera->x_pos.i.hi >> 1));
    background->y_pos.i.hi = camera->y_pos.i.hi;
}

void jungle_parallax_section_1(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        jungle_parallax_section_1_setup(arg0);
    } else {
        jungle_parallax_section_1_done(arg0);
    }
}

void jungle_parallax_section_1_setup(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 2;
    background_objects[1].unk40 = 0x200;
    arg0->unk6++;
}

void jungle_parallax_section_1_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void jungle_parallax_section_2(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        jungle_parallax_section_2_setup(arg0);
    } else {
        jungle_parallax_section_2_scroll(arg0);
    }
}

void jungle_parallax_section_2_setup(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0xB60;
    arg0->unk6++;
}

void jungle_parallax_section_2_scroll(struct LayerObj* arg0)
{
    struct BackgroundObj* obj = &background_objects[1];
    s16 value;
    value = background_objects[0].x_pos.i.hi - 0x960;
    value >>= 1;
    value = value + (value >> 1);
    obj->x_pos.i.hi = value + obj->unk40;
    value = background_objects[0].y_pos.i.hi - 0x500;
    obj->y_pos.i.hi = obj->unk42 + (background_objects[0].y_pos.i.hi - (value >> 2));
}

void jungle_parallax_idle(struct LayerObj* arg0)
{
}

void jungle_parallax_update_section(struct LayerObj* arg0)
{
    s8 var_v1;

    if (g_Player.y_pos.i.hi <= 0x200) {
        var_v1 = (u32) ~(g_Player.x_pos.i.hi - 0x450) >> 0x1F;
    } else {
        var_v1 = 2;
        if (g_Player.x_pos.i.hi - 0xA00 < 0) {
            var_v1 = 1;
        }
    }
    arg0->bg_offset = var_v1;
    if (var_v1 != arg0->unk15) {
        arg0->unk5 = var_v1;
        arg0->unk6 = 0;
    }
}

void (*jungle_parallax_state_funcs[])(struct LayerObj*) = {
    jungle_parallax_init,
    jungle_parallax_main,
};

void (*jungle_parallax_section_funcs[])(struct LayerObj*) = {
    jungle_parallax_section_0,
    jungle_parallax_section_1,
    jungle_parallax_section_2,
    jungle_parallax_idle,
};
