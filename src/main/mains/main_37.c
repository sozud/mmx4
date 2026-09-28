// MainObj, main_object_update_funcs[37]
// 8005FDBC..80060A88
#include "common.h"

extern u8 D_800FE6CC[12];
#include "func_tables.h"

void func_8005FDBC(struct MainObj* arg0)
{
    D_800FE6E4[arg0->state](arg0);
    if (arg0->unk5 != 4) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_8005FE1C);

extern void (*D_800FE6F0[])(struct MainObj*);

void func_80060144(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_800FE6F0[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_37.saved_unk5 = self->unk5;
    if (func_8002DD04(self) < 0) {
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(0xA, D_800FE6CC, self);
        func_800BF60C(BASE_OBJECT(self), 0x13);
        self->state = 2;
    } else if (self->unk2 == 3 || func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
}

void func_80060228(struct MainObj* arg0)
{
    arg0->unk62 = 0;
    arg0->ext.main_37.unk80.word = 0;
    arg0->ext.main_37.unk84.val = 0;
    arg0->ext.main_37.unk88.val = 0;
    arg0->ext.main_37.unk8C.val = 0;
    arg0->ext.main_37.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8006025C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_37.saved_unk5;
}

void func_80060268(struct MainObj* arg0)
{
    D_800FE704[arg0->unk6](arg0);
}

void func_800602A4(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->ext.main_37.unk80.saved_direction = arg0->unk15;
        func_80060A58(ANIMATED_OBJECT(arg0));
        arg0->unk24 = 0;
        if (arg0->unk15 == 0) {
            arg0->unk20 = FIXED(-1.5);
        } else {
            arg0->unk20 = FIXED(1.5);
        }
        if (arg0->unk15 != arg0->ext.main_37.unk80.saved_direction) {
            func_80015D60(arg0, 2);
            arg0->unk5 = 3;
            arg0->unk6 = 2;
        } else {
            func_80015D60(arg0, 3);
            arg0->unk6 = 1;
        }
    }
}

void func_80060354(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800603A0(struct MainObj* arg0)
{
    D_800FE70C[arg0->unk6](arg0);
}

void func_800603DC(struct MainObj* arg0)
{
    s32 direction_mask;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        direction_mask = arg0->unk70 & 2;
    } else {
        direction_mask = arg0->unk70 & 1;
    }
    if (direction_mask != 0) {
        arg0->unk6 = 2;
        arg0->unk15 ^= 0x40;
        arg0->unk20 = -arg0->unk20;
        func_80015D60(arg0, 2);
        return;
    }
    if ((arg0->unk70 & 8) == 0) {
        arg0->unk20 = 0;
        arg0->unk24 = FIXED(-1.5);
        func_80015D60(arg0, 3);
        arg0->unk6 = 1;
    }
}

void func_800604A0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_800604EC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80060538(struct MainObj* arg0)
{
    D_800FE718[arg0->unk6](arg0);
}

void func_80060574(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_37.unk8C.bytes[1] == 0) {
        func_8001540C(2, 0x59, arg0);
        arg0->ext.main_37.unk8C.bytes[1] = 0x1E;
    }
    if (g_Player.y_pos.i.hi <= arg0->ext.main_37.unk88.i.lo) {
        arg0->unk7C = 0x26;
        arg0->unk6 = 1;
    }
    if (!(arg0->unk7E & 3)) {
        if (arg0->unk15 == 0) {
            func_800C8214(1, &D_800FE6D8[arg0->ext.main_37.unk8C.bytes[0]], arg0, 0x7988, FIXED(-32), 0);
        } else {
            func_800C8214(1, &D_800FE6D8[arg0->ext.main_37.unk8C.bytes[0]], arg0, 0x7988, FIXED(32), 0);
        }
        if (++arg0->ext.main_37.unk8C.bytes[0] == 0xA) {
            arg0->ext.main_37.unk8C.bytes[0] = 0;
        }
    }
    if (!(++arg0->unk7E & 7)) {
        u16 left = arg0->ext.main_37.unk84.i.lo;
        u16 top = arg0->ext.main_37.unk84.u.hi;
        func_800B10E4(0x11, (s16)(left + 0x10), (s16)(top + 0x10), (s16)(left + 0x20), (s16)(top + 0x30), 1);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800606D8);

void func_80060870(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk28 = FIXED(0.125);
        arg0->unk20 = 0;
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800608CC);

void func_8006097C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk6 = 5;
    }
}

void func_800609C4(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk7C = 0x28;
        arg0->unk6 = 6;
    }
}

void func_80060A10(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk6 = 3;
    }
}

void func_80060A58(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

struct Unk_unk68 D_800FE4D4 = { -19, -18, 37, 28 };

struct Unk_unk68 D_800FE4D8 = { -14, -12, 26, 17 };

struct Unk_unk68 D_800FE4DC = { -23, -14, 37, 31 };

struct Unk_unk68 D_800FE4E0 = { -18, -13, 22, 27 };

struct Unk_unk68 D_800FE4E4 = { 0, 0, 23, 20 };

union AnimationStep D_800FE4E8[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08FE0002 },
};

union AnimationStep D_800FE4F4[] = {
    { 0x20010002 },
    { 0x21010002 },
    { 0x22FE0002 },
};

union AnimationStep D_800FE500[] = {
    { 0x09010009 },
    { 0x0A010009 },
    { 0x0A000101 },
};

union AnimationStep D_800FE50C[] = {
    { 0x20010004 },
    { 0x20000101 },
};

union AnimationStep D_800FE514[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep D_800FE520[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};

union AnimationStep D_800FE538[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1E010002 },
    { 0x1E010101 },
};

union AnimationStep D_800FE5EC[] = {
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1EF90003 },
};

union AnimationStep D_800FE60C[] = {
    { 0x23000101 },
};

union AnimationStep D_800FE610[] = {
    { 0x24000101 },
};

union AnimationStep D_800FE614[] = {
    { 0x25000101 },
};

union AnimationStep D_800FE618[] = {
    { 0x26000101 },
};

union AnimationStep D_800FE61C[] = {
    { 0x27000101 },
};

union AnimationStep D_800FE620[] = {
    { 0x28000101 },
};

union AnimationStep D_800FE624[] = {
    { 0x29000101 },
};

union AnimationStep D_800FE628[] = {
    { 0x2A000101 },
};

union AnimationStep D_800FE62C[] = {
    { 0x2B000101 },
};

union AnimationStep D_800FE630[] = {
    { 0x2C000101 },
};

union AnimationStep D_800FE634[] = {
    { 0x2D000101 },
};

union AnimationStep D_800FE638[] = {
    { 0x2E000101 },
};

union AnimationStep D_800FE63C[] = {
    { 0x2F000101 },
};

union AnimationStep D_800FE640[] = {
    { 0x30000101 },
};

union AnimationStep D_800FE644[] = {
    { 0x31000101 },
};

union AnimationStep D_800FE648[] = {
    { 0x32000101 },
};

union AnimationStep D_800FE64C[] = {
    { 0x33000101 },
};

union AnimationStep D_800FE650[] = {
    { 0x34000101 },
};

union AnimationStep D_800FE654[] = {
    { 0x35000101 },
};

union AnimationStep D_800FE658[] = {
    { 0x36000101 },
};

union AnimationStep* D_800FE65C[28] = {
    D_800FE4E8,
    D_800FE4F4,
    D_800FE500,
    D_800FE50C,
    D_800FE514,
    D_800FE520,
    D_800FE538,
    D_800FE5EC,
    D_800FE60C,
    D_800FE610,
    D_800FE614,
    D_800FE618,
    D_800FE61C,
    D_800FE620,
    D_800FE624,
    D_800FE628,
    D_800FE62C,
    D_800FE630,
    D_800FE634,
    D_800FE638,
    D_800FE63C,
    D_800FE640,
    D_800FE644,
    D_800FE648,
    D_800FE64C,
    D_800FE650,
    D_800FE654,
    D_800FE658,
};

u8 D_800FE6CC[12] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0 };

u8 D_800FE6D8[12] = { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 0, 0 };

void (*D_800FE6E4[3])() = {
    func_8005FE1C,
    func_80060144,
    func_80060228,
};

void (*D_800FE6F0[5])() = {
    func_8009216C,
    func_8006025C,
    func_80060268,
    func_800603A0,
    func_80060538,
};

void (*D_800FE704[2])(struct MainObj*) = {
    func_800602A4,
    func_80060354,
};

void (*D_800FE70C[3])() = {
    func_800603DC,
    func_800604A0,
    func_800604EC,
};

void (*D_800FE718[7])() = {
    func_80060574,
    func_800606D8,
    func_80060870,
    func_800608CC,
    func_8006097C,
    func_800609C4,
    func_80060A10,
};
