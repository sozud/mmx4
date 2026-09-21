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

INCLUDE_ASM("main/nonmatchings/shots/shot_38", func_800A4518);

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
