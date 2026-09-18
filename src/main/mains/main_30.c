// MainObj, main_object_update_funcs[30]
// 8005B3FC..8005B894
#include "common.h"

void func_8005B3FC(struct MainObj* arg0)
{
    D_800FD9C4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_30", func_8005B438);

void func_8005B504(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    func_80015D60(arg0, 10);
}

void func_8005B52C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5++;
        func_80015D60(arg0, 1);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8005B578(struct MainObj* arg0)
{
    struct ShotObj* shot;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5--;

        if (arg0->unk15 == 0
                ? arg0->x_pos.i.hi < g_Player.x_pos.i.hi
                : arg0->x_pos.i.hi > g_Player.x_pos.i.hi) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0xF;
                shot->unk7C = WEAPON_OBJECT(arg0);
                shot->state = 0;
                shot->unk5 = 0;
                shot->unk6 = 0;
            }
        }

        func_80015D60(arg0, 0xA);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8005B64C(struct MainObj* arg0)
{
    if (func_8002DD04(arg0) < 0) {
        arg0->unk5 = 0;
        arg0->active |= 4;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        return;
    }

    D_800FD9D0[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
        return;
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005B708(struct MainObj* arg0)
{
    arg0->unk5++;
    func_800AF808(BASE_OBJECT(arg0));
    func_800C813C(5, D_800FD9BC, arg0);
    func_80015D60(arg0, 2);
}

void func_8005B760(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5++;
        func_80015D60(arg0, 3);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8005B7AC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
        arg0->unk5C = 6;
        func_80015D60(arg0, 0);
        arg0->active &= ~4;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_8005B818(struct MainObj* arg0)
{
    D_800FD9E0[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}
