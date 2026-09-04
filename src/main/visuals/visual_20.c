// VisualObj, visual_object_update_funcs[20]
// 800B2D48..800B2E98
#include "common.h"

void func_800B2D48(struct VisualObj* arg0)
{
    D_8010A5B0[arg0->base.state](arg0);
}

void func_800B2D84(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->base.unk16 = 4;
    if (arg0->base.unk2 == 0) {
        func_80015D60(arg0, 0x11);
    } else {
        arg0->unk54 = 0;
        func_80015D60(arg0, 0x15);
    }
}

void func_800B2DD0(struct VisualObj* arg0)
{
    struct PlayerObj* temp_v1;
    struct BaseObj* temp_a0;

    func_80015DC8(arg0);
    if (arg0->base.unk2 == 0) {
        temp_v1 = arg0->unk50;
        temp_a0 = temp_v1->unk7C;
        arg0->base.x_pos.val = temp_a0->x_pos.val;
        arg0->base.y_pos.val = temp_a0->y_pos.val;
        if (temp_v1->base.unk2 != 0) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(arg0);
        }
    } else {
        temp_a0 = arg0->unk50;
        if (arg0->unk46 >= 0 && temp_a0->state == 1 && (temp_a0->unk5 == 3 || temp_a0->unk5 == 5)) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(arg0);
        }
    }
}

void (*D_8010A5B0[])(struct VisualObj*) = {
    func_800B2D84,
    func_800B2DD0,
};
