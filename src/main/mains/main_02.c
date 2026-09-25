// MainObj, main_object_update_funcs[2]
// 80042914..80043340
#include "common.h"
#include "func_tables.h"

extern struct Unk_unk68 D_800F9B24[];
extern struct Unk_unk68 D_800F9B34;
extern u8 D_800F9C44[];
extern u8 D_800F9C48[];

void func_80042914(struct MainObj* arg0)
{
    D_800F9C54[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_02", func_80042950);

INCLUDE_ASM("main/nonmatchings/mains/main_02", func_80042A48);

INCLUDE_ASM("main/nonmatchings/mains/main_02", func_80042AFC);

void func_80042CB0(struct MainObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state++;
}

void func_80042CC4(struct MainObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_80042CE4(struct MainObj* arg0)
{
    D_800F9C8C[arg0->unk6](arg0);
}

void func_80042D20(struct MainObj* arg0)
{
    s32 var_a1;

    var_a1 = -0x20000;
    arg0->unk6++;
    if (arg0->unk15 != 0) {
        var_a1 = 0x20000;
    }
    arg0->unk20 = var_a1;
    func_80015D60(arg0, 0);
}

void func_80042D60(struct MainObj* arg0)
{
    s32 distance;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (distance < 0) {
        distance = g_Player.x_pos.val - arg0->x_pos.val;
    }
    if (distance <= FIXED(64)) {
        arg0->unk20 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 1);
    }
}

void func_80042DD8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }
}

void func_80042E18(struct MainObj* arg0)
{
    D_800F9C98[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80042E70(struct MainObj* arg0)
{
    arg0->unk7C = 0x12C;
    arg0->unk7E = 0xA;
    arg0->unk20 = 0;
    arg0->unk24 = 0x2000;
    arg0->unk6++;
    func_80015D60(arg0, 3);
}

void func_80042EB8(struct MainObj* arg0)
{
    s16 timer;
    s16 countdown;

    timer = arg0->unk7E;
    if (timer == 0) {
        arg0->unk7E = 0x14;
        arg0->unk24 = -arg0->unk24;
    } else {
        arg0->unk7E = timer - 1;
    }
    countdown = arg0->unk7C - 1;
    arg0->unk7C = countdown;
    if ((countdown << 0x10) == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80042F18(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
    }
}

void func_80042F80(struct MainObj* arg0)
{
    D_800F9CA4[arg0->unk6](arg0);
}

void func_80042FBC(struct MainObj* arg0)
{
    arg0->unk24 = 0x40000;
    arg0->unk2C = 0x4200;
    arg0->unk68 = D_800F9B24;
    arg0->unk54 = &D_800F9B34;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk50 = NULL;
    arg0->unk67 = -1;
    arg0->unk6++;
    func_80015D60(arg0, 4);
    CollisionRelated(PLAYER_OBJECT(arg0));
    if ((arg0->unk70 & 0xF) == 0xF) {
        arg0->unk6 = 3;
        arg0->unk67 = 0;
        arg0->x_pos.val = arg0->unk18.val;
        arg0->y_pos.val = arg0->unk1C.val;
    }
}

void func_80043064(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6++;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
}

void func_800430C0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk2C = 0;
        arg0->unk67 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 4);
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
}

void func_80043128(struct MainObj* arg0)
{
}

void func_80043130(struct MainObj* arg0)
{
    D_800F9CB4[arg0->unk6](arg0);
}

void func_8004316C(struct MainObj* arg0)
{
    s32 state;
    state = arg0->y_pos.val > g_Player.y_pos.val;
    if (state) {
        state = 1;
    } else {
        state = 2;
    }
    arg0->unk6 = state;
    arg0->unk7 = 0;
}

void func_80043198(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->unk20 = 0;
        arg0->unk24 = FIXED(1);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
        if (arg0->on_screen == 0) {
            arg0->state++;
        }
    }
}

void func_80043214(struct MainObj* arg0)
{
    D_800F9CC0[arg0->unk7](arg0);
}

void func_80043250(struct MainObj* arg0)
{
    arg0->unk24 = 0;
    arg0->unk7++;
    func_80015D60(arg0, 2);
}

void func_80043280(struct MainObj* arg0)
{
    s32 velocity;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    velocity = FIXED(-2);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7++;
        if (arg0->unk15 != 0) {
            velocity = FIXED(2);
        }
        arg0->unk20 = velocity;
        arg0->unk24 = FIXED(0.14453125);
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x258;
    }
}

void func_800432F0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->on_screen == 0) {
        arg0->state++;
    }
}

struct Unk_unk68 D_800F9B20 = { -1, -15, 17, 23 };

struct Unk_unk68 D_800F9B24[4] = {
    { 0, -1, 10, 13 },
    { -18, -9, 34, 17 },
    { -12, -38, 25, 31 },
    { -13, -38, 25, 44 },
};

struct Unk_unk68 D_800F9B34 = { -10, -19, 20, 32 };

union AnimationStep D_800F9B38[] = {
    { 0x00010005 },
    { 0x01010005 },
    { 0x02010005 },
    { 0x01010005 },
    { 0x00010005 },
    { 0x03FB0005 },
};

union AnimationStep D_800F9B50[] = {
    { 0x04010005 },
    { 0x05010005 },
    { 0x06010005 },
    { 0x07010005 },
    { 0x08010005 },
    { 0x09010004 },
    { 0x09000001 },
};

union AnimationStep D_800F9B6C[] = {
    { 0x09010005 },
    { 0x08010005 },
    { 0x07010005 },
    { 0x06010005 },
    { 0x05010005 },
    { 0x04010004 },
    { 0x04000001 },
};

union AnimationStep D_800F9B88[] = {
    { 0x0A010005 },
    { 0x0B010005 },
    { 0x0C010005 },
    { 0x0B010005 },
    { 0x0A010005 },
    { 0x0DFB0005 },
};

union AnimationStep D_800F9BA0[] = {
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15F90002 },
};

union AnimationStep D_800F9BC0[] = {
    { 0x16010003 },
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1BFB0003 },
};

union AnimationStep D_800F9BD8[] = { { 0x1C000001 } };

union AnimationStep D_800F9BDC[] = { { 0x1D000001 } };

union AnimationStep D_800F9BE0[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29F50002 },
};

union AnimationStep D_800F9C10[] = { { 0x2A000001 } };

union AnimationStep D_800F9C14[] = { { 0x2B000001 } };

union AnimationStep* D_800F9C18[11] = {
    D_800F9B38,
    D_800F9B50,
    D_800F9B6C,
    D_800F9B88,
    D_800F9BA0,
    D_800F9BC0,
    D_800F9BD8,
    D_800F9BDC,
    D_800F9BE0,
    D_800F9C10,
    D_800F9C14,
};

u8 D_800F9C44[4] = { 5, 6, 7, 0 };

u8 D_800F9C48[12] = { 8, 9, 10, 0, 5, 6, 7, 8, 9, 10, 0, 0 };

void (*D_800F9C54[])(struct MainObj*) = {
    func_80042950,
    func_80042A48,
    func_80042AFC,
    func_80042CB0,
    func_80042CC4,
};

struct Unk_unk68* D_800F9C68[] = {
    D_800F9B24 + 1,
    D_800F9B24 + 2,
};

u8* D_800F9C70[] = {
    D_800F9C44,
    D_800F9C48 + 4,
};

u8 D_800F9C78[] = { 3, 6, 0, 0 };

void (*D_800F9C7C[])() = {
    func_80042CE4,
    func_80042E18,
    func_80042F80,
    func_80043130,
};

void (*D_800F9C8C[])() = {
    func_80042D20,
    func_80042D60,
    func_80042DD8,
};

void (*D_800F9C98[])() = {
    func_80042E70,
    func_80042EB8,
    func_80042F18,
};

void (*D_800F9CA4[])() = {
    func_80042FBC,
    func_80043064,
    func_800430C0,
    func_80043128,
};

void (*D_800F9CB4[])() = {
    func_8004316C,
    func_80043198,
    func_80043214,
};

void (*D_800F9CC0[])() = {
    func_80043250,
    func_80043280,
    func_800432F0,
};
