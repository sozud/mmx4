// MiscObj, misc_object_update_funcs[30]
// 800CDCC0..800CDE44
#include "common.h"

void func_800CDCC0(struct MiscObj* arg0)
{
    D_8010EC30[arg0->state](arg0);
}

void func_800CDCFC(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_30.owner;

    if (owner->state >= 2) {
        arg0->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->unk2 == 0) {
        if (--arg0->ext.misc_30.unk56 == 0) {
            arg0->state = 1;
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
        if (arg0->ext.misc_30.unk54 == 0) {
            arg0->x_pos.i.hi += 0x20;
        } else {
            arg0->x_pos.i.hi -= 0x20;
        }
        arg0->y_pos.i.hi++;
        arg0->ext.misc_30.unk54 ^= 0x20;
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        if (--arg0->ext.misc_30.unk54 == 0) {
            arg0->state = 1;
        }
        arg0->x_pos.val = arg0->ext.misc_30.owner->x_pos.val;
        arg0->y_pos.val = arg0->ext.misc_30.owner->y_pos.val;
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_800CDE24(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010EC30[2])(struct MiscObj*) = {
    func_800CDCFC,
    func_800CDE24,
};
