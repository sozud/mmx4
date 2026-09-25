// ShotObj, shot_object_update_funcs[43]
// 800A6960..800A6FCC
#include "common.h"

void func_800A6960(struct ShotObj* arg0)
{
    D_801099C0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A699C);

void func_800A6C00(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else {
        func_8002D9BC(arg0);
        if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
            is_on_screen(BASE_OBJECT(arg0));
            return;
        }
    }
    arg0->state = 3;
}

void func_800A6C7C(struct ShotObj* arg0)
{
    struct MiscObj* misc;
    s16 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 3;
        return;
    }
    if (func_8002D9BC(arg0) != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    if (arg0->unk8C.word != 0) {
        func_800A6DF4(arg0);
        arg0->unk8C.word--;
    }
    if (arg0->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            y = arg0->y_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = 7;
            misc->y_pos.i.hi = y;
        }
        arg0->unk7 = 2;
    } else {
        arg0->unk7--;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
    } else {
        arg0->state++;
    }
}

void func_800A6DCC(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A6DEC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A6DF4);

u8 D_801099B0[4] = { 0xF7, 0xFB, 0x0C, 0x08 };

u8 D_801099B4[4] = { 0xFA, 0xFA, 0x0C, 0x0D };

s32 D_801099B8[2] = { -0x40000, 0x40000 };

void (*D_801099C0[])(struct ShotObj*) = {
    func_800A699C,
    func_800A6C00,
    func_800A6C7C,
    func_800A6DCC,
    func_800A6DEC,
};
