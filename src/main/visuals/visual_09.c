// VisualObj, visual_object_update_funcs[9]
// 800B1354..800B14E8
#include "common.h"

void func_800B1354(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        func_800B1394(arg0);
    } else {
        func_800B1450(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_09", func_800B1394);

void func_800B1450(struct VisualObj* arg0)
{
    u8 temp_v1;

    func_8002B718((struct MovingObj*)arg0);
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk5C = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    temp_v1 = (u8)arg0->unk5C;
    arg0->on_screen = 0;
    if (((temp_v1 & 3) && !(temp_v1 & 1)) || ((D_80141BD8.unk0 & 1) == arg0->unk7)) {
        is_on_screen((struct BaseObj*)arg0);
    }
}
