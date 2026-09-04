// MiscObj, misc_object_update_funcs[22]
// 800CBA80..800CBD40
#include "common.h"

// misc obj update #22
void func_800CBA80(struct MiscObj* arg0)
{
    u8* ptr;

    switch (arg0->base.unk2) {
    case 0:
        is_on_screen(arg0);
        return;
    case 1:
        if ((u8)controller_state == 0) {
            if (--arg0->ext.unk.unk56.sht == 0) {
                arg0->ext.unk.unk56.sht = 0x20;
                arg0->ext.unk.unk54 ^= 1;
            }
            if (arg0->ext.unk.unk54) {
                arg0->base.on_screen = 0;
                return;
            }
            is_on_screen(arg0);
            return;
        }
        ZeroObjectState(arg0);
        return;
    case 2:
        if (abc_object.unkC != 0) {
            if (abc_object.unkD == 0 || abc_object.unkD == 4) {
                func_80015DC8(arg0);
            }
            is_on_screen(arg0);
            return;
        }
        ZeroObjectState(arg0);
        return;
    case 3:
        ptr = abc_object.unkE + &arg0->ext.unk.unk50->unk0;
        if (*ptr != 0 && (abc_object.unkC == 1)) {
            if (arg0->ext.unk.unk55 == 0) {
                func_80015D60(arg0, 1);
                arg0->ext.unk.unk55 = 1;
            } else {
                func_80015DC8(arg0);
                if (arg0->unk45 != 0) {
                    arg0->ext.unk.unk55 = 0;
                }
            }
        } else if (arg0->ext.unk.unk55 != 0) {
            func_80015DC8(arg0);
            if (arg0->unk45 != 0) {
                arg0->ext.unk.unk55 = 0;
                func_80015D60(arg0, 0);
            }
        } else {
            func_80015D60(arg0, 0);
        }
        is_on_screen(arg0);
        return;
    case 4:
        func_80015DC8(arg0);
        is_on_screen(arg0);
        return;
    case 5:
        ptr = abc_object.unkE + &arg0->ext.unk.unk50->unk0;
        if ((*ptr == 0) && (abc_object.unkC == 1)) {
            if (arg0->ext.unk.unk55 == 0) {
                func_80015D60(arg0, arg0->ext.unk.unk54 + 1);
                arg0->ext.unk.unk55 = 1;
            } else {
                func_80015DC8(arg0);
                if (arg0->unk45 != 0) {
                    arg0->ext.unk.unk55 = 0;
                }
            }
        } else if (arg0->ext.unk.unk55) {
            func_80015DC8(arg0);
            if (arg0->unk45 != 0) {
                arg0->ext.unk.unk55 = 0;
                func_80015D60(arg0, arg0->ext.unk.unk54);
            }
        } else {
            func_80015D60(arg0, arg0->ext.unk.unk54);
        }
        is_on_screen(arg0);
        return;
    case 8:
        if (arg0->base.unk5 == 0) {
            func_80015DC8(arg0);
            if (--arg0->ext.unk.unk56.byte == 0) {
                arg0->base.unk5 = 1;
            }
            if (arg0->base.unk6) {
                arg0->base.x_pos.val = arg0->ext.unk.unk50->x_pos.val;
                arg0->base.y_pos.val = arg0->ext.unk.unk50->y_pos.val;
            }
            is_on_screen(arg0);
            return;
        }
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
        return;
    }
}
