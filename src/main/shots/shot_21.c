// ShotObj, shot_object_update_funcs[21]
// 8009D200..8009D74C
#include "common.h"

u8 D_80108FDC[4] = { 0xF7, 0xF8, 0x11, 0x11 };
u8 D_80108FE0[4] = { 0xF3, 0xFC, 0x18, 0x0B };
u8 D_80108FE4[4] = { 0xFC, 0xF4, 0x08, 0x18 };
u8 D_80108FE8[4] = { 0, 0, 5, 5 };
u8 D_80108FEC[4] = { 0, 2, 0x0A, 4 };
u8 D_80108FF0[4] = { 0, 0, 4, 0x0A };

void func_8009D200(struct ShotObj* arg0)
{
    D_80108FF4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D23C);

void func_8009D3F4(struct ShotObj* arg0)
{
    struct MiscObj* misc;
    s16 y;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    func_8002D9BC(arg0);
    if (arg0->unk84.value != 0) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
    func_8009D588(arg0);
    if (arg0->y_pos.i.hi >= background_objects[0].y_pos.i.hi + 0xE0) {
        arg0->unk70 = 1;
    }
    if (arg0->unk70 != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state++;
        return;
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
        arg0->unk7 = 1;
    } else {
        arg0->unk7--;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x120, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    } else {
        arg0->state++;
    }
}

void func_8009D560(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009D580(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D588);

void (*D_80108FF4[])(struct ShotObj*) = {
    func_8009D23C,
    func_8009D3F4,
    func_8009D560,
    func_8009D580,
};
