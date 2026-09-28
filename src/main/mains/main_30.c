// MainObj, main_object_update_funcs[30]
// 8005B3FC..8005B894
#include "common.h"
#include "func_tables.h"

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

struct Unk_unk68 D_800FD8AC[] = {
    { -22, -13, 0x14, 0x19 },
};

struct Unk_unk68 D_800FD8B0[] = {
    { -27, -20, 0x1A, 0x28 },
};

union AnimationStep D_800FD8B4[] = {
    { 0x00010008 },
    { 0x01010008 },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010006 },
    { 0x0601000F },
    { 0x07010006 },
    { 0x08010008 },
    { 0x07010006 },
    { 0x06010077 },
    { 0x06FF0001 },
};

union AnimationStep D_800FD8E4[] = {
    { 0x06010005 },
    { 0x09010006 },
    { 0x0A010008 },
    { 0x09010006 },
    { 0x06010004 },
    { 0x06FB0001 },
};

union AnimationStep D_800FD8FC[] = {
    { 0x0B010077 },
    { 0x0BFF0001 },
};

union AnimationStep D_800FD904[] = {
    { 0x0B010004 },
    { 0x0C010005 },
    { 0x0D010007 },
    { 0x0C010005 },
    { 0x0B010015 },
    { 0x0E010006 },
    { 0x0F010005 },
    { 0x10010004 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00EC0001 },
};

union AnimationStep D_800FD958[] = {
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010001 },
    { 0x1AFA0001 },
};

union AnimationStep D_800FD974[] = {
    { 0x06010077 },
    { 0x06FF0001 },
};

union AnimationStep D_800FD97C[] = {
    { 0x1B000001 },
};

union AnimationStep D_800FD980[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FD984[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FD988[] = {
    { 0x1E000001 },
};

union AnimationStep D_800FD98C[] = {
    { 0x1F000001 },
};

union AnimationStep* D_800FD990[] = {
    D_800FD8B4,
    D_800FD8E4,
    D_800FD8FC,
    D_800FD904,
    D_800FD958,
    D_800FD97C,
    D_800FD980,
    D_800FD984,
    D_800FD988,
    D_800FD98C,
    D_800FD974,
};

u8 D_800FD9BC[] = {
    0x05,
    0x06,
    0x07,
    0x08,
    0x09,
    0x00,
    0x00,
    0x00,
};

void (*D_800FD9C4[])(struct MainObj*) = {
    func_8005B438,
    func_8005B64C,
    func_8005B818,
};

void (*D_800FD9D0[])(struct MainObj*) = {
    func_8009216C,
    func_8005B504,
    func_8005B52C,
    func_8005B578,
};

void (*D_800FD9E0[])(struct MainObj*) = {
    func_8005B708,
    func_8005B760,
    func_8005B7AC,
};
