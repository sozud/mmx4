// MainObj, main_object_update_funcs[4]
// 8004441C..80044F4C
#include "common.h"
#include "func_tables.h"

void func_8004441C(struct MainObj* arg0)
{
    D_800FA080[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_04", func_80044458);

INCLUDE_ASM("main/nonmatchings/mains/main_04", func_80044508);

void func_80044630(struct MainObj* arg0)
{
    if (arg0->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
    func_80015930(2, 7);
    func_80015930(2, 8);
    func_80015930(2, 9);
}

void func_80044694(struct MainObj* arg0)
{
}

void func_8004469C(struct MainObj* arg0)
{
    D_800FA0B8[arg0->unk6](arg0);
}

void func_800446D8(struct MainObj* arg0)
{
    s32 x_vel;

    x_vel = FIXED(-2);
    arg0->unk6++;
    if (arg0->unk15 != 0) {
        x_vel = FIXED(2);
    }
    arg0->unk20 = x_vel;
    func_80015D60(arg0, 2);
    func_8001540C(2, 7, arg0);
}

void func_80044738(struct MainObj* arg0)
{
    s32 distance;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (distance < 0) {
        distance = g_Player.x_pos.val - arg0->x_pos.val;
    }
    if (distance <= 0x4FFFF) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_800447A4(struct MainObj* arg0)
{
}

void func_800447AC(struct MainObj* arg0)
{
    D_800FA0C4[arg0->unk6](arg0);
}

void func_800447E8(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 3);
}

void func_80044814(struct MainObj* arg0)
{
    s32 object_x;
    s32 object_x_2;
    s32 distance;
    s32 distance_2;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    object_x = arg0->x_pos.val;
    distance = object_x - g_Player.x_pos.val;
    if (distance < 0) {
        distance = g_Player.x_pos.val - object_x;
    }
    if (distance > FIXED(64)) {
        arg0->unk15 = ((arg0->unk15 & 0x40) == 0) << 6;
        arg0->unk20 = -arg0->unk20;
        object_x_2 = arg0->x_pos.val;
        distance_2 = object_x_2 - g_Player.x_pos.val;
        if (distance_2 < 0) {
            distance_2 = g_Player.x_pos.val - object_x_2;
        }
        if (distance_2 > FIXED(64)) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
        }
    }
}

void func_800448C4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800448E4(struct MainObj* arg0)
{
    D_800FA0D0[arg0->unk6](arg0);
}

void func_80044920(struct MainObj* arg0)
{
    arg0->unk7C = 0x1E;
    arg0->unk67 = -1;
    arg0->unk6++;
    func_80015D60(arg0, 4);
    func_8001540C(2, 8, arg0);
}

void func_80044978(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.1875);
        arg0->unk6++;
    }
}

void func_800449D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk67 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 5);
        func_8001540C(2, 9, arg0);
    }
}

void func_80044A4C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015930(2, 9);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk60 = 2;
    }
}

void func_80044AA0(struct MainObj* arg0)
{
}

void func_80044AA8(struct MainObj* arg0)
{
    D_800FA0E4[arg0->unk6](arg0);
}

void func_80044AE4(struct MainObj* arg0)
{
    arg0->unk7C = 0x3C;
    arg0->unk6++;
    func_80015D60(arg0, 8);
}

void func_80044B18(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = FIXED(3);
        arg0->unk2C = 0;
        arg0->unk6++;
    }
}

void func_80044B78(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80044BA8(struct MainObj* arg0)
{
    D_800FA0F0[arg0->unk6](arg0);
}

void func_80044BE4(struct MainObj* arg0)
{
    arg0->unk7C = 0x28;
    arg0->unk6++;
}

void func_80044BFC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 7);
        arg0->unk7E = 3;
        arg0->unk6++;
    }
}

void func_80044C58(struct MainObj* arg0)
{
    const u8* sprite_frames;
    u8 i;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_8001540C(2, 0xA, arg0);
        arg0->animation_step.fields.event = 0;
        i = 0;
        do {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 1;
                shot->unk40 = arg0->unk40;
                shot->unk42 = arg0->unk42;
                sprite_frames = arg0->sprite_frames;
                shot->unk2 = i;
                shot->unk3C = (void*)sprite_frames;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
            }
            i++;
        } while (i < 2);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        if (--arg0->unk7E != 0) {
            func_80015D60(arg0, 7);
            return;
        }
        arg0->unk7C = 0x5A;
        arg0->unk6++;
    }
}

void func_80044D8C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 7);
        arg0->unk6 = 2;
        arg0->unk7E = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_04", func_80044DE4);

struct Unk_unk68 D_800F9EBC = { 0, 8, 8, 16 };

struct Unk_unk68 D_800F9EC0 = { -9, -24, 14, 46 };

struct Unk_unk68 D_800F9EC4[2] = {
    { -9, -6, 14, 30 },
    { -9, -24, 14, 16 },
};

union AnimationStep D_800F9ECC[] = {
    { 0x00000001 },
};

union AnimationStep D_800F9ED0[] = {
    { 0x49000001 },
};

union AnimationStep D_800F9ED4[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05FB0001 },
};

union AnimationStep D_800F9EEC[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x17E90001 },
};

union AnimationStep D_800F9F4C[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1AFE0001 },
};

union AnimationStep D_800F9F58[] = {
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010003 },
    { 0x26010005 },
    { 0x27010003 },
    { 0x28010005 },
    { 0x29010003 },
    { 0x2A010007 },
    { 0x2B010007 },
    { 0x2C01000A },
    { 0x2D01010A },
    { 0x2E01000B },
    { 0x2F00000B },
};

union AnimationStep D_800F9FAC[] = {
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33000002 },
};

union AnimationStep D_800F9FC0[] = {
    { 0x34010004 },
    { 0x35010006 },
    { 0x36010009 },
    { 0x35010006 },
    { 0x37010004 },
    { 0x38010102 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x32010002 },
    { 0x33000002 },
};

union AnimationStep D_800F9FE8[] = {
    { 0x48010001 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4C010001 },
    { 0x4DFB0001 },
};

union AnimationStep D_800FA000[] = {
    { 0x3B010003 },
    { 0x3C010003 },
    { 0x3D010003 },
    { 0x3E010003 },
    { 0x3FFC0003 },
};

union AnimationStep D_800FA014[] = {
    { 0x40010002 },
    { 0x41010002 },
    { 0x42010002 },
    { 0x43FD0002 },
};

union AnimationStep D_800FA024[] = {
    { 0x44000001 },
};

union AnimationStep D_800FA028[] = {
    { 0x45000001 },
};

union AnimationStep D_800FA02C[] = {
    { 0x46000001 },
};

union AnimationStep D_800FA030[] = {
    { 0x47000001 },
};

union AnimationStep* D_800FA034[] = {
    D_800F9ECC,
    D_800F9ED0,
    D_800F9ED4,
    D_800F9EEC,
    D_800F9F4C,
    D_800F9F58,
    D_800F9FAC,
    D_800F9FC0,
    D_800F9FE8,
    D_800FA014,
    D_800FA024,
    D_800FA028,
    D_800FA02C,
    D_800FA030,
    D_800FA000,
};

u8 D_800FA070[] = {
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
    0x00,
};

u8 D_800FA078[] = {
    0x09,
    0x0B,
    0x0C,
    0x0D,
};

u8 D_800FA07C[4] = { '\n', 0, 0, 0 };

void (*D_800FA080[])() = {
    func_80044458,
    func_80044508,
    func_80044630,
    func_80044694,
};

void (*D_800FA090[])() = {
    func_8009216C,
    func_8004469C,
    func_800447AC,
    func_800448E4,
    func_80044AA8,
    func_80044BA8,
};

u8* D_800FA0A8[] = {
    D_800FA070,
    D_800FA078,
    D_800FA07C,
};

u8 D_800FA0B4[] = {
    0x05,
    0x04,
    0x01,
    0x00,
};

void (*D_800FA0B8[])() = {
    func_800446D8,
    func_80044738,
    func_800447A4,
};

void (*D_800FA0C4[])() = {
    func_800447E8,
    func_80044814,
    func_800448C4,
};

void (*D_800FA0D0[])() = {
    func_80044920,
    func_80044978,
    func_800449D8,
    func_80044A4C,
    func_80044AA0,
};

void (*D_800FA0E4[])() = {
    func_80044AE4,
    func_80044B18,
    func_80044B78,
};

void (*D_800FA0F0[])() = {
    func_80044BE4,
    func_80044BFC,
    func_80044C58,
    func_80044D8C,
};
