// MainObj, main_object_update_funcs[5]
// 80044F4C..80046B30
#include "common.h"
#include "func_tables.h"

void func_80044F4C(struct MainObj* arg0)
{
    D_800FA388[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_80044F88);

void func_800450A8(struct MainObj* arg0)
{
    s32 collision;
    s8 subtype;

    func_80046AA4(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        collision = func_8002DD04(arg0);
        subtype = arg0->unk5;
        if (subtype != 0) {
            arg0->ext.main_5.saved_unk5 = subtype;
        }
        if (collision < 0) {
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(5, D_800FA340, arg0);
            func_800BF60C(BASE_OBJECT(arg0), 0);
            arg0->state = 2;
            return;
        }
        D_800FA394[arg0->unk5](arg0);
        func_8002D9BC(arg0);
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    } else {
        arg0->state = 2;
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
}

void func_80045198(struct MainObj* arg0)
{
    struct MainObj* target;
    u8 subtype;
    func_80015930(2, 0x13);
    func_80015930(2, 0x14);
    arg0->on_screen = 0;
    subtype = arg0->unk2;
    if ((subtype >= 3) && (subtype <= 4)) {
        target = arg0->ext.main_5.owner;
        if ((target->active != 0) && (target->id == 0x16)) {
            target->ext.main_22.parts_mask ^= 1 << arg0->ext.main_5.part_index;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80045240(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_5.saved_unk5;
}

void func_8004524C(struct MainObj* arg0)
{
    if (func_80015A10(0x13, arg0) != 0) {
        func_8001540C(2, 0x13, arg0);
    }
    D_800FA3BC[arg0->unk6](arg0);
}

void func_800452B4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x13, arg0);
    arg0->unk6++;
}

void func_800452FC(struct MainObj* arg0)
{
    s32 object_x;
    s32 player_x;
    s32 delta;
    s32* velocity;
    s32 x_vel;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    object_x = arg0->x_pos.val;
    player_x = g_Player.x_pos.val;
    delta = object_x - player_x;
    if (delta >= 0 ? delta <= FIXED(144) : (player_x - object_x) <= FIXED(144)) {
        velocity = D_800FA108;
        if (!(arg0->unk15 & 0x40)) {
            velocity++;
        }
        x_vel = *velocity;
        arg0->unk24 = 0;
        arg0->unk5 = 3;
        arg0->unk20 = x_vel;
    }
}

void func_8004539C(struct MainObj* arg0)
{
    if (func_80015A10(0x13, arg0) != 0) {
        func_8001540C(2, 0x13, arg0);
    }
    D_800FA3C4[arg0->unk6](arg0);
}

void func_80045404(struct MainObj* arg0)
{
    s32* velocity;
    s32 x_vel;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    velocity = D_800FA108;
    if (!(arg0->unk15 & 0x40)) {
        velocity++;
    }
    x_vel = *velocity;
    arg0->unk24 = FIXED(1);
    arg0->unk20 = x_vel;
    arg0->unk6++;
}

void func_80045464(struct MainObj* arg0)
{
    arg0->unk2C = FIXED(0.04296875);
    arg0->unk28 = FIXED(0.0234375);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_800454A4(struct MainObj* arg0)
{
    if (func_80015A10(0x14, arg0) != 0) {
        func_8001540C(2, 0x14, arg0);
    }
    D_800FA3CC[arg0->unk6](arg0);
}

void func_8004550C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015930(2, 0x13);
    func_8001540C(2, 0x14, arg0);
    arg0->unk6++;
}

void func_80045560(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk7C-- == 4) {
        arg0->unk6++;
    }
}

void func_800455BC(struct MainObj* arg0)
{
    s32* velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    velocity = D_800FA110;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    arg0->unk20 = *velocity;
    if (arg0->unk7C-- == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 9);
        arg0->unk28 = FIXED(0.1875);
        arg0->unk2C = FIXED(-0.03125);
    }
}

void func_80045648(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 > 0x14FFFF) {
        arg0->unk28 = 0;
    }
}

void func_80045694(struct MainObj* arg0)
{
    if (arg0->unk6 >= 4) {
        if (func_80015A10(0x14, arg0) != 0) {
            func_8001540C(2, 0x14, arg0);
        } else if (func_80015A10(0x13, arg0) != 0) {
            func_8001540C(2, 0x13, arg0);
        }
    }
    D_800FA3DC[arg0->unk6](arg0);
}

void func_80045728(struct MainObj* arg0)
{
    s32* velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    func_80015930(2, 0x13);
    func_8001540C(2, 0x13, arg0);
    velocity = D_800FA118;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    arg0->unk20 = *velocity;
    arg0->unk6++;
}

void func_800457A8(struct MainObj* arg0)
{
    s32 player_x;
    s32 object_x;
    s32 delta;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    player_x = g_Player.x_pos.val;
    object_x = arg0->x_pos.val;
    delta = player_x - object_x;
    if (delta >= 0 ? delta <= FIXED(96) - 1 : object_x - player_x <= FIXED(96) - 1) {
        func_80015D60(arg0, 2);
        arg0->unk7C = 0xF;
        arg0->unk6++;
    }
}

void func_8004583C(struct MainObj* arg0)
{
    s32* velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->unk7C-- < 5) {
        velocity = D_800FA120;
        if (arg0->unk15 & 0x40) {
            velocity++;
        }
        arg0->unk20 = *velocity;
        arg0->unk6++;
    }
}

void func_800458B4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    if (arg0->unk7C-- <= 0) {
        arg0->unk7C = 8;
        arg0->ext.main_5.unk80 = 0;
        func_80015930(2, 0x13);
        func_8001540C(2, 0x14, arg0);
        func_80015D60(arg0, 0xB);
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_80045940);

void func_80045D80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    if (arg0->unk7C-- == 0) {
        arg0->unk7C = 8;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_80045DD8);

void func_80046104(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80046134(struct MainObj* arg0)
{
    if (func_80015A10(0x13, arg0) != 0) {
        func_8001540C(2, 0x13, arg0);
    }
    D_800FA3FC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_8004619C);

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_80046220);

void func_8004636C(struct MainObj* arg0)
{
    if (arg0->unk6 >= 2) {
        if (func_80015A10(0x14, arg0) != 0) {
            func_8001540C(2, 0x14, arg0);
        } else if (func_80015A10(0x13, arg0) != 0) {
            func_8001540C(2, 0x13, arg0);
        }
    }
    D_800FA404[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_05", func_80046400);

void func_80046610(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80046640(struct MainObj* arg0)
{
    if (func_80015A10(0x13, arg0) != 0) {
        func_8001540C(2, 0x13, arg0);
    }
    D_800FA40C[arg0->unk6](arg0);
}

void func_800466A8(struct MainObj* arg0)
{
    struct MainObj* self = arg0;

    func_80015D60(self, 1);
    func_8001540C(2, 0x13, self);
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B93C(
        MOVING_OBJECT(self),
        func_8002B7B0(
            OBJECT_HEADER(self),
            self->ext.main_5.target_y << 0x10,
            self->ext.main_5.target_x << 0x10)
            & 0xFF);

    self->unk7C = 0x14;
    if (self->unk15 == 0) {
        if (self->ext.main_5.part_index & 1) {
            self->unk7C = 0x16;
        }
    }
    if (self->unk15 != 0) {
        if (!(self->ext.main_5.part_index & 1)) {
            self->unk7C += 2;
        }
    }
    self->unk6++;
}

void func_8004677C(struct MainObj* arg0)
{
    s16 timer;
    s16 next_delay;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;

        next_delay = get_random() & 0x7F;
        arg0->unk7C = next_delay;
        if (next_delay < 0x78) {
            arg0->unk7C = next_delay + 0x78;
        } else if (next_delay >= 0xF1) {
            arg0->unk7C = 0xF0;
        }
        arg0->unk6++;
    }
}

void func_80046818(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80046864(struct MainObj* arg0)
{
    if (func_80015A10(0x13, arg0) != 0) {
        func_8001540C(2, 0x13, arg0);
    }
    D_800FA418[arg0->unk6](arg0);
}

void func_800468CC(struct MainObj* arg0)
{
    func_80015D60(arg0, 1);
    func_8001540C(2, 0x13, arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0),
            arg0->ext.main_5.target_y << 0x10,
            arg0->ext.main_5.target_x << 0x10)
            & 0xFF);

    arg0->unk7C = 0x14;
    if (arg0->unk15 == 0) {
        if (arg0->ext.main_5.part_index & 1) {
            arg0->unk7C = 0x16;
        }
    }
    if (arg0->unk15 != 0) {
        if (!(arg0->ext.main_5.part_index & 1)) {
            arg0->unk7C += 2;
        }
    }
    arg0->unk6++;
}

void func_800469A0(struct MainObj* arg0)
{
    s16 timer;
    s16 next_delay;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;

        next_delay = get_random() & 0x7F;
        arg0->unk7C = next_delay;
        if (next_delay < 0x78) {
            arg0->unk7C = next_delay + 0x78;
        } else if (next_delay >= 0xF1) {
            arg0->unk7C = 0xF0;
        }
        arg0->unk6++;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80046A4C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

void func_80046AA4(struct MainObj* arg0)
{
    s32 player_x;

    if ((arg0->unk5 == 3) && (arg0->y_pos.val + FIXED(16) >= g_Player.y_pos.val)) {
        player_x = g_Player.x_pos.val;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk7C = 0xF;
        arg0->unk15 = (arg0->x_pos.val < player_x) << 6;
        func_80015D60(arg0, 2);
    }
}

struct Unk_unk68 D_800FA100 = { -10, -12, 19, 24 };

struct Unk_unk68 D_800FA104 = { -3, -4, 8, 9 };

s32 D_800FA108[] = {
    (s32)0xFFFF0000,
    (s32)0x00010000,
};

s32 D_800FA110[] = {
    (s32)0xFFFD0000,
    (s32)0x00030000,
};

s32 D_800FA118[] = {
    (s32)0xFFFE0000,
    (s32)0x00020000,
};

s32 D_800FA120[] = {
    (s32)0xFFFD0000,
    (s32)0x00030000,
};

s32 D_800FA128[] = {
    (s32)0xFFF9E000,
    (s32)0x00062000,
};

s32 D_800FA130[] = {
    (s32)0xFFFF8000,
    (s32)0x00008000,
};

union AnimationStep D_800FA138[] = {
    { 0x00000001 },
};

union AnimationStep D_800FA13C[] = {
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
    { 0x0FF10001 },
};

union AnimationStep D_800FA17C[] = {
    { 0x10010002 },
    { 0x11010009 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15000001 },
};

union AnimationStep D_800FA194[] = {
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25F10002 },
};

union AnimationStep D_800FA1D4[] = {
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010003 },
    { 0x29FD0003 },
};

union AnimationStep D_800FA1E4[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FA1E8[] = {
    { 0x2B000001 },
};

union AnimationStep D_800FA1EC[] = {
    { 0x2C000001 },
};

union AnimationStep D_800FA1F0[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FA1F4[] = {
    { 0x2E010001 },
    { 0x2F010001 },
    { 0x30010001 },
    { 0x31FD0001 },
};

union AnimationStep D_800FA204[] = {
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41F10002 },
};

union AnimationStep D_800FA244[] = {
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010017 },
    { 0x39010001 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36000002 },
};

union AnimationStep D_800FA2C8[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23010002 },
    { 0x22000002 },
};

union AnimationStep D_800FA2DC[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23000002 },
};

union AnimationStep D_800FA2EC[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24000002 },
};

union AnimationStep D_800FA2F8[] = {
    { 0x16010002 },
    { 0x25000002 },
};

union AnimationStep* D_800FA300[] = {
    D_800FA138,
    D_800FA13C,
    D_800FA17C,
    D_800FA194,
    D_800FA1D4,
    D_800FA1E4,
    D_800FA1E8,
    D_800FA1EC,
    D_800FA1F0,
    D_800FA1F4,
    D_800FA204,
    D_800FA244,
    D_800FA2C8,
    D_800FA2DC,
    D_800FA2EC,
    D_800FA2F8,
};

u8 D_800FA340[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

s32 D_800FA348[] = {
    (s32)0x00001AC2,
    (s32)0x00003539,
    (s32)0x0000681F,
    (s32)0x00009679,
    (s32)0x0000BE3E,
    (s32)0x0000DDB3,
    (s32)0x0000F378,
    (s32)0x0000FE99,
};

s32 D_800FA368[] = {
    (s32)0x0000FE99,
    (s32)0x0000FA67,
    (s32)0x0000E9DE,
    (s32)0x0000CF1B,
    (s32)0x0000AB4C,
    (s32)0x00008000,
    (s32)0x00004F1B,
    (s32)0x00001AC2,
};

void (*D_800FA388[])(struct MainObj*) = {
    func_80044F88,
    func_800450A8,
    func_80045198,
};

void (*D_800FA394[])() = {
    func_8009216C,
    func_80045240,
    func_8004524C,
    func_8004539C,
    func_800454A4,
    func_80045694,
    func_80046134,
    func_8004636C,
    func_80046640,
    func_80046864,
};

void (*D_800FA3BC[])(struct MainObj*) = {
    func_800452B4,
    func_800452FC,
};

void (*D_800FA3C4[])(struct MainObj*) = {
    func_80045404,
    func_80045464,
};

void (*D_800FA3CC[])(struct MainObj*) = {
    func_8004550C,
    func_80045560,
    func_800455BC,
    func_80045648,
};

void (*D_800FA3DC[])(struct MainObj*) = {
    func_80045728,
    func_800457A8,
    func_8004583C,
    func_800458B4,
    func_80045940,
    func_80045D80,
    func_80045DD8,
    func_80046104,
};

void (*D_800FA3FC[])(struct MainObj*) = {
    func_8004619C,
    func_80046220,
};

void (*D_800FA404[])(struct MainObj*) = {
    func_80046400,
    func_80046610,
};

void (*D_800FA40C[])(struct MainObj*) = {
    func_800466A8,
    func_8004677C,
    func_80046818,
};

void (*D_800FA418[])(struct MainObj*) = {
    func_800468CC,
    func_800469A0,
    func_80046A4C,
};
