// MainObj, main_object_update_funcs[25]
// 80057100..80058158
#include "common.h"
#include "func_tables.h"

void func_80057100(struct MainObj* arg0)
{
    D_800FD140[arg0->state](arg0);
    if (arg0->ext.main_25.unk88 == 0) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057160);

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057308);

void func_80057488(struct MainObj* arg0)
{
    arg0->ext.main_25.unk80 = 0;
    arg0->ext.main_25.unk84 = 0;
    arg0->ext.main_25.unk88 = 0;
    arg0->ext.main_25.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800574B4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_25.saved_unk5;
}

void func_800574C0(struct MainObj* arg0)
{
    D_800FD168[arg0->unk6](arg0);
}

void func_800574FC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8005807C(arg0);
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-1);
    } else {
        arg0->unk20 = FIXED(1);
    }
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_8005754C);

void func_800576F4(struct MainObj* self)
{
    s32 distance;
    s32 player_y;
    s32 object_y;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_25.unk84 = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_25.unk84 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk20 != 0) {
        return;
    }
    self->unk28 = 0;
    player_y = g_Player.y_pos.i.hi;
    object_y = self->y_pos.i.hi;
    distance = player_y - object_y;
    if (distance >= 0 ? distance < 0x1A : object_y - player_y < 0x1A) {
        func_80015D60(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_25.unk84 = 0;
        return;
    }
    if (self->unk15 == 0) {
        self->unk15 = 0x40;
        self->unk20 = FIXED(1);
    } else {
        self->unk15 = 0;
        self->unk20 = FIXED(-1);
    }
    self->unk6 = 1;
}

void func_800577E8(struct MainObj* arg0)
{
    D_800FD174[arg0->unk6](arg0);
}

void func_80057824(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8005807C(arg0);
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-2);
    } else {
        arg0->unk20 = FIXED(2);
    }
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057874);

void func_80057978(struct MainObj* arg0)
{
    s32 distance;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_25.unk84 = 1;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->ext.main_25.unk84 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        distance = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (distance >= 0) {
            if (distance < 0x1A) {
                arg0->unk6 = 0;
            } else {
                func_80015D60(arg0, 0);
                arg0->unk5 = 2;
                arg0->unk6 = 0;
                arg0->ext.main_25.unk80 = 0x40;
                arg0->ext.main_25.unk84 = 0;
            }
        } else {
            distance = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
            if (distance < 0x1A) {
                arg0->unk6 = 0;
            } else {
                func_80015D60(arg0, 0);
                arg0->unk5 = 2;
                arg0->unk6 = 0;
                arg0->ext.main_25.unk80 = 0x40;
                arg0->ext.main_25.unk84 = 0;
            }
        }
    }
}

void func_80057A44(struct MainObj* arg0)
{
    D_800FD180[arg0->unk6](arg0);
}

void func_80057A80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk2C = FIXED(0.2578125);
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->ext.main_25.unk84 = 2;
        func_80015D60(arg0, 4);
        arg0->unk6 = 1;
    }
}

void func_80057AE8(struct MainObj* self)
{
    s16 tx;
    s16 ty;
    u8 hits;

    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));

    tx = self->x_pos.u.hi + self->unk68->unk0;
    ty = self->unk68->unk3 + (self->y_pos.u.hi + self->unk68->unk1) + 0x1B;

    hits = func_8002D724(PLAYER_OBJECT(self), tx, ty);
    tx -= self->unk68->unk2;
    hits |= func_8002D724(PLAYER_OBJECT(self), tx, ty);
    hits |= func_8002D724(PLAYER_OBJECT(self), tx + self->unk68->unk2 * 2, ty);

    if (hits != 0 && hits != 0x24) {
        func_80015D60(self, 5);
        self->unk2C = 0;
        self->unk24 = 0;
        self->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_25", func_80057C00);

void func_80057D58(struct MainObj* arg0)
{
    D_800FD18C[arg0->unk6](arg0);
}

void func_80057D94(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 3);
        arg0->unk6 = 1;
    }
}

void func_80057DDC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 4);
        arg0->ext.main_25.unk84 = 2;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 2;
    }
}

void func_80057E34(struct MainObj* arg0)
{
    s16 tx;
    s16 ty;
    u8 r;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    tx = arg0->x_pos.u.hi + arg0->unk68->unk0;
    ty = (arg0->y_pos.u.hi + arg0->unk68->unk1) - arg0->unk68->unk3;
    r = func_8002D724(PLAYER_OBJECT(arg0), tx, ty);
    tx -= arg0->unk68->unk2;
    r = r | func_8002D724(PLAYER_OBJECT(arg0), tx, ty);
    r = r | func_8002D724(PLAYER_OBJECT(arg0), tx + arg0->unk68->unk2 * 2, ty);
    if (r != 0 && r != 0x24) {
        arg0->unk6 = 3;
    }
}

void func_80057F34(struct MainObj* arg0)
{
    s16 tx;
    s16 ty;
    u8 r;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    tx = arg0->x_pos.u.hi + arg0->unk68->unk0;
    ty = (arg0->y_pos.u.hi + arg0->unk68->unk1) - arg0->unk68->unk3;
    r = func_8002D724(PLAYER_OBJECT(arg0), tx, ty);
    tx -= arg0->unk68->unk2;
    r = r | func_8002D724(PLAYER_OBJECT(arg0), tx, ty);
    r = r | func_8002D724(PLAYER_OBJECT(arg0), tx + arg0->unk68->unk2 * 2, ty);
    if (r == 0 || r == 0x24) {
        arg0->unk5 = 4;
        arg0->ext.main_25.unk88 = 0;
        arg0->unk6 = 1;
    }
}

void func_80058044(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0x11) {
        arg0->unk5 = 4;
        arg0->y_pos.u.hi -= 0x18;
    }
}

void func_8005807C(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_800580AC(struct MainObj* arg0)
{
    if ((arg0->unk5 != 4) && (arg0->unk5 != 6) && !(arg0->unk70 & 8)) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        if (arg0->unk15 == 0) {
            arg0->x_pos.u.hi -= 2;
        } else {
            arg0->x_pos.u.hi += 2;
        }
        arg0->unk2C = FIXED(0.2578125);
        arg0->ext.main_25.unk84 = 2;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

struct Unk_unk68 D_800FCFD4[] = {
    { -3, -5, 0x29, 8 },
};

struct Unk_unk68 D_800FCFD8[] = {
    { -2, -24, 0xC, 0x1C },
};

struct Unk_unk68 D_800FCFDC[] = {
    { -16, -16, 0x13, 0x14 },
};

struct Unk_unk68 D_800FCFE0[] = {
    { -23, -6, 0x12, 0xA },
};

struct Unk_unk68 D_800FCFE4[] = {
    { -6, -28, 0xC, 0x37 },
};

struct Unk_unk68 D_800FCFE8[] = {
    { -10, -5, 0xF, 0x15 },
};

struct Unk_unk68 D_800FCFEC[] = {
    { 8, -20, 0xE, 0x13 },
};

struct Unk_unk68 D_800FCFF0[] = {
    { -2, -19, 0x13, 0x15 },
};

struct Unk_unk68 D_800FCFF4[] = {
    { 0, -2, 0x24, 5 },
};

struct Unk_unk68 D_800FCFF8[] = {
    { -1, -21, 9, 0x18 },
};

struct Unk_unk68 D_800FCFFC[] = {
    { -12, -13, 0xE, 0x10 },
};

struct Unk_unk68 D_800FD000[] = {
    { -20, -4, 0x11, 7 },
};

struct Unk_unk68 D_800FD004[] = {
    { -4, -26, 8, 0x33 },
};

struct Unk_unk68 D_800FD008[] = {
    { -8, -3, 0xD, 0x13 },
};

struct Unk_unk68 D_800FD00C[] = {
    { 9, -18, 0xB, 0x10 },
};

struct Unk_unk68 D_800FD010[] = {
    { 0, -16, 0xF, 0x11 },
};

struct Unk_unk68 D_800FD014[] = {
    { 0, -4, 0xD, 8 },
};

struct Unk_unk68* D_800FD018[] = {
    D_800FCFD4,
    D_800FCFD8,
    D_800FCFD4,
    D_800FCFDC,
    D_800FCFE4,
    D_800FCFE4,
    D_800FCFE8,
    D_800FCFEC,
    D_800FCFD4,
    D_800FCFF0,
    D_800FCFD4,
    D_800FCFE0,
};

struct Unk_unk68* D_800FD048[] = {
    D_800FCFF4,
};

struct Unk_unk68* D_800FD04C[] = {
    D_800FCFF8,
    D_800FCFF4,
    D_800FCFFC,
    D_800FD004,
    D_800FD004,
    D_800FD008,
    D_800FD00C,
    D_800FCFF4,
    D_800FD010,
    D_800FCFF4,
    D_800FD000,
};

union AnimationStep D_800FD078[] = {
    { 0x0001000C },
    { 0x0101020C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x04FC010C },
};

union AnimationStep D_800FD08C[] = {
    { 0x00010006 },
    { 0x01010206 },
    { 0x02010006 },
    { 0x03010006 },
    { 0x04FC0106 },
};

union AnimationStep D_800FD0A0[] = {
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010002 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010009 },
    { 0x05000101 },
};

union AnimationStep D_800FD0C0[] = {
    { 0x05010002 },
    { 0x09010201 },
    { 0x09010005 },
    { 0x0A010003 },
    { 0x0A000101 },
};

union AnimationStep D_800FD0D4[] = {
    { 0x0B010006 },
    { 0x0CFF0106 },
};

union AnimationStep D_800FD0DC[] = {
    { 0x0D010201 },
    { 0x0D010003 },
    { 0x0E010301 },
    { 0x0E010004 },
    { 0x0F010401 },
    { 0x0F010504 },
    { 0x10010601 },
    { 0x10010004 },
    { 0x11010007 },
    { 0x11000101 },
};

union AnimationStep D_800FD104[] = {
    { 0x12000101 },
};

union AnimationStep D_800FD108[] = {
    { 0x13000101 },
};

union AnimationStep D_800FD10C[] = {
    { 0x14000101 },
};

union AnimationStep D_800FD110[] = {
    { 0x15000101 },
};

union AnimationStep* D_800FD114[] = {
    D_800FD078,
    D_800FD08C,
    D_800FD0A0,
    D_800FD0C0,
    D_800FD0D4,
    D_800FD0DC,
    D_800FD104,
    D_800FD108,
    D_800FD10C,
    D_800FD110,
};

u8 D_800FD13C[] = {
    0x06,
    0x07,
    0x08,
    0x09,
};

void (*D_800FD140[])() = {
    func_80057160,
    func_80057308,
    func_80057488,
};

void (*D_800FD14C[])() = {
    func_8009216C,
    func_800574B4,
    func_800574C0,
    func_800577E8,
    func_80057A44,
    func_80057D58,
    func_80058044,
};

void (*D_800FD168[])() = {
    func_800574FC,
    func_8005754C,
    func_800576F4,
};

void (*D_800FD174[])() = {
    func_80057824,
    func_80057874,
    func_80057978,
};

void (*D_800FD180[])() = {
    func_80057A80,
    func_80057AE8,
    func_80057C00,
};

void (*D_800FD18C[])() = {
    func_80057D94,
    func_80057DDC,
    func_80057E34,
    func_80057F34,
};
