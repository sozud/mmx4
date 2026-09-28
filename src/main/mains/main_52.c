// MainObj, main_object_update_funcs[52]
// 8006A50C..8006AF70
#include "common.h"
#include "func_tables.h"

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

struct Unk_unk68 D_800FFDD0 = { -14, -19, 25, 33 };

struct Unk_unk68 D_800FFDD4 = { -10, -18, 16, 30 };

struct Unk_unk68 D_800FFDD8 = { 0, 0, 6, 15 };

union AnimationStep D_800FFDDC[] = {
    { 0x0F010008 },
    { 0x10010008 },
    { 0x11010007 },
    { 0x12010008 },
    { 0x13010008 },
    { 0x14FB0107 },
};

union AnimationStep D_800FFDF4[] = {
    { 0x00010008 },
    { 0x01010006 },
    { 0x02010003 },
    { 0x02010201 },
    { 0x03010006 },
    { 0x04000106 },
};

union AnimationStep D_800FFE0C[] = {
    { 0x16010001 },
    { 0x15010006 },
    { 0x15000101 },
};

union AnimationStep D_800FFE18[] = {
    { 0x18010001 },
    { 0x17010006 },
    { 0x17000101 },
};

union AnimationStep D_800FFE24[] = {
    { 0x1A010001 },
    { 0x19010006 },
    { 0x19000101 },
};

union AnimationStep D_800FFE30[] = {
    { 0x1C010001 },
    { 0x1B010006 },
    { 0x1B000101 },
};

union AnimationStep D_800FFE3C[] = {
    { 0x1E010001 },
    { 0x1D010006 },
    { 0x1D000101 },
};

union AnimationStep D_800FFE48[] = {
    { 0x06010001 },
    { 0x05010006 },
    { 0x05000101 },
};

union AnimationStep D_800FFE54[] = {
    { 0x08010001 },
    { 0x07010006 },
    { 0x07000101 },
};

union AnimationStep D_800FFE60[] = {
    { 0x0A010001 },
    { 0x09010006 },
    { 0x09000101 },
};

union AnimationStep D_800FFE6C[] = {
    { 0x0C010001 },
    { 0x0B010006 },
    { 0x0B000101 },
};

union AnimationStep D_800FFE78[] = {
    { 0x0E010001 },
    { 0x0D010006 },
    { 0x0D000101 },
};

union AnimationStep D_800FFE84[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21FE0001 },
};

union AnimationStep D_800FFE90[] = {
    { 0x22000101 },
};

union AnimationStep D_800FFE94[] = {
    { 0x23000101 },
};

union AnimationStep D_800FFE98[] = {
    { 0x24000101 },
};

union AnimationStep D_800FFE9C[] = {
    { 0x25000101 },
};

union AnimationStep D_800FFEA0[] = {
    { 0x03010006 },
    { 0x01010005 },
    { 0x01000101 },
};

union AnimationStep D_800FFEAC[] = {
    { 0x17010002 },
    { 0x15010001 },
    { 0x15000101 },
};

union AnimationStep D_800FFEB8[] = {
    { 0x17000101 },
};

union AnimationStep D_800FFEBC[] = {
    { 0x17010002 },
    { 0x19010001 },
    { 0x19000101 },
};

union AnimationStep D_800FFEC8[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010001 },
    { 0x1B000101 },
};

union AnimationStep D_800FFED8[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010002 },
    { 0x1D010001 },
    { 0x1D000101 },
};

union AnimationStep D_800FFEEC[] = {
    { 0x07010002 },
    { 0x05010001 },
    { 0x05000101 },
};

union AnimationStep D_800FFEF8[] = {
    { 0x07000101 },
};

union AnimationStep D_800FFEFC[] = {
    { 0x07010002 },
    { 0x09010001 },
    { 0x09000101 },
};

union AnimationStep D_800FFF08[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010001 },
    { 0x0B000101 },
};

union AnimationStep D_800FFF18[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010002 },
    { 0x0D010001 },
    { 0x0D000101 },
};

union AnimationStep* D_800FFF2C[28] = {
    D_800FFDDC,
    D_800FFDF4,
    D_800FFE0C,
    D_800FFE18,
    D_800FFE24,
    D_800FFE30,
    D_800FFE3C,
    D_800FFE48,
    D_800FFE54,
    D_800FFE60,
    D_800FFE6C,
    D_800FFE78,
    D_800FFE84,
    D_800FFE90,
    D_800FFE94,
    D_800FFE98,
    D_800FFE9C,
    D_800FFEA0,
    D_800FFEAC,
    D_800FFEB8,
    D_800FFEBC,
    D_800FFEC8,
    D_800FFED8,
    D_800FFEEC,
    D_800FFEF8,
    D_800FFEFC,
    D_800FFF08,
    D_800FFF18,
};

u8 D_800FFF9C[4] = { 13, 14, 15, 16 };

void (*D_800FFFA0[3])() = {
    func_8006A55C,
    func_8006A638,
    func_8006A70C,
};

void (*D_800FFFAC[5])() = {
    func_8009216C,
    func_8006A740,
    func_8006A74C,
    func_8006AA18,
    func_8006AC8C,
};

void (*D_800FFFC0[4])(struct MainObj*) = {
    func_8006A788,
    func_8006A7F0,
    func_8006A83C,
    func_8006A998,
};

void (*D_800FFFD0[2])(struct MainObj*) = {
    func_8006AA54,
    func_8006AAB4,
};

void (*D_800FFFD8[3])(struct MainObj*) = {
    func_8006ACC8,
    func_8006AD84,
    func_8006AE0C,
};
