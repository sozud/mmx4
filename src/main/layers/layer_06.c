// LayerObj, layer_object_update_funcs[6]
// 800DA7C0..800DA878
#include "common.h"

void func_800DA7C0(struct LayerObj* arg0)
{
    D_8010FFC8[arg0->state](arg0);
}

void func_800DA7FC(struct LayerObj* arg0)
{
    arg0->bg_offset = 0;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->state++;
}

void func_800DA818(struct LayerObj* arg0)
{
    struct BackgroundObj* background;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    temp_v0 = arg0->bg_offset + 1;
    arg0->bg_offset = temp_v0;
    if (temp_v0 == 8) {
        arg0->bg_offset = 0;
        temp_v0_2 = arg0->unk15 + 1;
        arg0->unk15 = temp_v0_2;
        if (temp_v0_2 == 4) {
            arg0->unk15 = 0;
        }
        temp_v0_3 = arg0->unk15;
        background = &background_objects[1];
        background->unk4C = 1;
        background->x_pos.i.hi = temp_v0_3 << 9;
    }
}

void (*D_8010FFC8[])(struct LayerObj*) = {
    func_800DA7FC,
    func_800DA818,
};
