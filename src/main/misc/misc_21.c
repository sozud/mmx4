// MiscObj, misc_object_update_funcs[21]
// 800CB884..800CB8F8
#include "common.h"

void func_800CB884(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->bg_offset = -1;
        arg0->unk47 = 0;
        arg0->unk3C = SP_SPRITE_FRAMES;
        arg0->unk40 = 0x600;
        arg0->unk42 = 0x7804;
        arg0->x_pos.i.hi = 0xA0;
        arg0->unk38 = 0;
        arg0->animation_table = 0;
        arg0->unk15 = 0;
        arg0->unk16 = 0;
        arg0->y_pos.i.hi = 0x78;
        arg0->state++;
    }
}
