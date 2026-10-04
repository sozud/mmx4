// LayerObj, layer_object_update_funcs[4]
// 800DA05C..800DA298
#include "common.h"

void volcano_camera_section_0_done(struct LayerObj* arg0);
void volcano_camera_section_0_wait(struct LayerObj* arg0);
void volcano_camera_section_1_done(struct LayerObj* arg0);
void volcano_camera_section_1_wait(struct LayerObj* arg0);

s16 volcano_camera_section_positions[2] = { 0x8D0, 0 };

void volcano_camera_update(struct LayerObj* arg0)
{
    volcano_camera_state_funcs[arg0->state](arg0);
}

void volcano_camera_init(struct LayerObj* arg0)
{
    arg0->unk5 = 1;
    arg0->bg_offset = 2;
    arg0->state++;
    background_objects[0].unk2E = 0xA0;
    background_objects[0].unk2C = 0x50;
    volcano_camera_main(arg0);
}

void volcano_camera_main(struct LayerObj* arg0)
{
    arg0->unk15 = arg0->bg_offset;
    volcano_camera_update_section(arg0);
    volcano_camera_section_funcs[arg0->unk5](arg0);
}

void volcano_camera_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(arg0);
}

void volcano_camera_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        volcano_camera_section_0_wait(arg0);
    } else {
        volcano_camera_section_0_done(arg0);
    }
}

void volcano_camera_section_0_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void volcano_camera_section_0_done(struct LayerObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void volcano_camera_section_1(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        volcano_camera_section_1_wait(arg0);
    } else {
        volcano_camera_section_1_done(arg0);
    }
}

void volcano_camera_section_1_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void volcano_camera_section_1_done(struct LayerObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void volcano_camera_idle(struct LayerObj* arg0)
{
}

void volcano_camera_update_section(struct LayerObj* arg0)
{
    s8 index;

    for (index = 0; index < 1; index++) {
        if (g_Player.x_pos.i.hi - volcano_camera_section_positions[index] < 0) {
            break;
        }
    }

    arg0->bg_offset = index;
    if (index != arg0->unk15) {
        arg0->unk5 = index;
        arg0->unk6 = 0;
    }
}

void (*volcano_camera_state_funcs[])(struct LayerObj*) = {
    volcano_camera_init,
    volcano_camera_main,
    volcano_camera_despawn,
};

void (*volcano_camera_section_funcs[])(struct LayerObj*) = {
    volcano_camera_section_0,
    volcano_camera_section_1,
    volcano_camera_idle,
};
