// ShotObj, shot_object_update_funcs[38]
// 800A428C..800A47C4
#include "common.h"

u8 D_801097DC[4] = { 0xFC, 0xFC, 0x08, 0x08 };
u8 D_801097E0[4] = { 0xF0, 0x92, 0x1F, 0xD4 };

void func_800A428C(struct ShotObj* arg0)
{
    D_801097E4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_38", func_800A42C8);

void func_800A4518(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (arg0->unk2 < 5) {
        func_800A46FC(arg0);
        if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
            func_800AF808(BASE_OBJECT(arg0));
            arg0->state++;
            return;
        }
    } else {
        if (owner->state == 2) {
            arg0->state++;
            return;
        }
        if (--arg0->timer == 0) {
            switch (arg0->unk84.value) {
            case 0:
                arg0->unk84.value = 1;
                arg0->timer = 0x2D;
                arg0->y_vel.val = 0;
                break;
            case 1:
                arg0->timer = 0xC;
                arg0->unk84.value = 2;
                arg0->y_vel.val = FIXED(21);
                break;
            case 2:
                arg0->unk84.value = 3;
                arg0->timer = 0x3E;
                arg0->y_vel.val = 0;
                break;
            case 3:
                arg0->unk84.value = 4;
                arg0->y_vel.val = FIXED(21);
                arg0->timer = 0xC;
                break;
            }
        }
    }
    if (owner->active == 0) {
        arg0->state++;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, arg0->unk2 < 5 ? 0x20 : 0x80) == 0) {
        if (arg0->unk2 < 5) {
            func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        }
    } else {
        arg0->state++;
    }
}

void func_800A46D4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A46F4(struct ShotObj* arg0)
{
}

void func_800A46FC(struct ShotObj* arg0)
{
    struct ShotObj* shot;
    struct MiscObj* misc;
    s32 timer;

    shot = arg0;
    timer = shot->unk84.value;
    if (timer == 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 0x23;
            misc->unk2 = shot->unk2;
            misc->ext.pointer.unk50 = shot;
            misc->bg_offset = shot->bg_offset;
            misc->unk42 = shot->unk42;
            misc->animation_table = shot->animation_table;
            misc->unk3C = shot->unk3C;
            misc->unk40 = shot->unk40;
            misc->unk15 = shot->unk15;
            misc->x_pos.u.hi = shot->x_pos.u.hi;
            misc->y_pos.u.hi = shot->y_pos.u.hi;
        }
        timer = 5;
    } else {
        timer--;
    }
    shot->unk84.value = timer;
}

void (*D_801097E4[])(struct ShotObj*) = {
    func_800A42C8,
    func_800A4518,
    func_800A46D4,
    func_800A46F4,
};
