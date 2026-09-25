// MainObj, main_object_update_funcs[52]
// 8006A50C..8006AF70
#include "common.h"

extern u8 D_800FFF9C[];
extern void (*D_800FFFAC[])(struct MainObj*);

void func_8006A50C(struct MainObj* arg0)
{
    D_800FFFA0[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A55C);

void func_8006A638(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FFFAC[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    arg0->ext.main_52.saved_unk5 = arg0->unk5;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(arg0);
        func_800C813C(3, &D_800FFF9C, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0);
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = 2;
}

void func_8006A70C(struct MainObj* arg0)
{
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[4] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8006A740(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_52.saved_unk5;
}

void func_8006A74C(struct MainObj* arg0)
{
    D_800FFFC0[arg0->unk6](arg0);
}

void func_8006A788(struct MainObj* arg0)
{
    func_8006AE50(ANIMATED_OBJECT(arg0));
    func_8006AE80(arg0);
    if (arg0->ext.main_52.unk80 == 0) {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 0x12);
    } else {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 0x17);
    }
    arg0->unk6 = 1;
}

void func_8006A7F0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6 = 2;
        arg0->unk7C = 2;
        arg0->unk7E = 0xC;
    }
}

void func_8006A83C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E != 0) {
        return;
    }
    if (arg0->ext.main_52.unk80 == 0) {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 2);
    } else {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 7);
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1B;
        shot->unk2 = arg0->ext.main_52.unk88 + arg0->ext.main_52.unk80 * 5;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        shot->unk15 = arg0->unk15;
        func_8002B93C(MOVING_OBJECT(shot), arg0->ext.main_52.unk84);
        shot->state = 0;
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1E;
        arg0->unk6 = 3;
        arg0->ext.main_52.unk8C = 0;
    } else {
        arg0->unk7E = 0x10;
    }
}

void func_8006A998(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->ext.main_52.unk8C = 0;
        arg0->unk7C = 0x5A;
        if (arg0->ext.main_52.unk80 == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
        } else {
            arg0->unk2C = FIXED(0.25);
            arg0->unk5 = 4;
            arg0->unk20 = 0;
            arg0->unk6 = 1;
        }
    }
}

void func_8006AA18(struct MainObj* arg0)
{
    D_800FFFD0[arg0->unk6](arg0);
}

void func_8006AA54(struct MainObj* arg0)
{
    func_8006AE50(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-1.8);
    } else {
        arg0->unk20 = FIXED(1.8);
    }
    func_80015D60(arg0, 0);
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AAB4);

void func_8006AC8C(struct MainObj* arg0)
{
    D_800FFFD8[arg0->unk6](arg0);
}

void func_8006ACC8(struct MainObj* arg0)
{
    s8 event;
    s32 variant;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    event = arg0->animation_step.fields.event;
    if (event == 2) {
        variant = arg0->ext.main_52.unk8C;
        arg0->ext.main_52.unk80 = 1;
        arg0->unk24 = FIXED(6);
        arg0->unk2C = FIXED(0.25);
        if (variant == 0) {
            if (arg0->unk15 != 0) {
                arg0->unk20 = FIXED(1.8);
            } else {
                arg0->unk20 = FIXED(-1.8);
            }
        } else if (variant == 1) {
            arg0->unk20 = 0;
        } else if (variant == event) {
            if (arg0->unk15 == 0) {
                arg0->unk20 = FIXED(1.8);
            } else {
                arg0->unk20 = FIXED(-1.8);
            }
        }
        func_8002B694(ANIMATED_OBJECT(arg0));
        arg0->unk6 = 1;
    }
}

void func_8006AD84(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0 && arg0->ext.main_52.unk8C != 0) {
        arg0->unk2C = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
    if (arg0->unk70 & 8) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0x11);
        arg0->unk6 = 2;
    }
}

void func_8006AE0C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->ext.main_52.unk80 = 0;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8006AE50(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE80);
