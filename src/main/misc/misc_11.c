// MiscObj, misc_object_update_funcs[11]
// 800CA0C8..800CA228
#include "common.h"

void func_800CA0C8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010E580[arg0->state](arg0);
}

void func_800CA110(struct MiscObj* arg0)
{
    s8 variant;

    variant = arg0->unk2;
    switch (variant) {
    case 1:
    case 2:
        func_80015D60(arg0, variant + 1);
        break;
    case 3:
        is_on_screen(BASE_OBJECT(arg0));
        break;
    }
    arg0->ext.misc_11.active = 0;
    arg0->state = (u8)arg0->state + 1;
}

void func_800CA188(struct MiscObj* arg0)
{
    if (arg0->ext.misc_11.active != 0) {
        arg0->state++;
    }
    if (arg0->unk2 == 0) {
        arg0->on_screen ^= 1;
        if (arg0->on_screen == 0) {
            return;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CA208(struct MiscObj* arg0)
{
    arg0->ext.misc_11.active = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E580[])(struct MiscObj*) = {
    func_800CA110,
    func_800CA188,
    func_800CA208,
};
