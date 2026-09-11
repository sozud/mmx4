// MiscObj, misc_object_update_funcs[6]
// 800C91B0..800C938C
#include "common.h"

void func_800C91B0(struct MiscObj* arg0)
{
    D_8010DC60[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_06", func_800C91EC);

INCLUDE_ASM("main/nonmatchings/misc/misc_06", func_800C92B8);

void func_800C92E0(struct MiscObj* arg0)
{
    s16 x_center;
    s16 x_pos;
    s16 y_center;
    s16 y_pos;

    func_8002B718(MOVING_OBJECT(arg0));

    x_center = arg0->ext.misc_6.saved_position.position.x;
    x_pos = arg0->x_pos.i.hi;
    if (x_pos >= x_center - 0x10) {
        if (x_pos <= x_center + 0x10) {
            y_center = arg0->ext.misc_6.saved_position.position.y;
            y_pos = arg0->y_pos.i.hi;
            if (y_pos >= y_center - 0x10) {
                if (y_pos <= y_center + 0x10) {
                    arg0->state = 3;
                }
            }
        }
    }

    func_8002B318(BASE_OBJECT(arg0), 0x140, 0x140);
}

void func_800C9368(struct MiscObj* arg0)
{
    arg0->ext.misc_6.saved_position.packed = 0;
    arg0->ext.misc_6.timer = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
