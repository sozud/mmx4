// RideArmorObj, D_800F2AD4[0]
// 8003B3DC..8003D3F8
#include "common.h"
#include "func_tables.h"

void func_8003B3DC(struct RideArmorObj* arg0)
{
    arg0->unk8A = g_Player.input.buttons.held;
    arg0->unk8C.value = g_Player.pressed_input;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    D_800F90D8[arg0->state](arg0);
    arg0->unk5C &= ~0x80;
}

void func_8003B458(void* arg0, s8 arg1)
{
    g_Player.unkD4 = arg1;
    g_Player.unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003B470);

INCLUDE_ASM("main/nonmatchings/bike", func_8003B694);

INCLUDE_ASM("main/nonmatchings/bike", func_8003B7B4);

void func_8003B98C(struct PlayerObj* arg0)
{
    s8 timer;

    if (arg0->charge_state[0] == 0) {
        return;
    }
    if ((u8)arg0->unk9A == 0) {
        return;
    }

    timer = arg0->unk61;
    if (timer == 0) {
        arg0->unk9A = 0;
        arg0->unk85 = 0;
        arg0->unk42 &= 0x7FFF;
        func_8003D254(VISUAL_OBJECT(arg0));
        return;
    }

    timer -= 1;
    arg0->unk61 = timer;
    if (timer & 2) {
        arg0->unk42 |= 0x8000;
    } else {
        arg0->unk42 &= 0x7FFF;
    }
}

void func_8003BA24(struct RideArmorObj* arg0)
{
    if (arg0->on_screen != 0) {
        if (arg0->unk5 == 0) {
            arg0->unk5 = 1;
            arg0->x_vel.val = FIXED(10);
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->unk2C = FIXED(0.265625);
            g_Player.unkC5 = 0;
            func_80036AE4(0x17, 0x40);
        } else {
            if (arg0->unk70 & 8) {
                arg0->y_vel.val = 0;
                arg0->unk2C = 0;
            }
            func_8002B694(ANIMATED_OBJECT(arg0));
        }
    } else {
        arg0->state = 3;
        arg0->unk5 = 0;
        func_80036B18();
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8003BAE8(struct RideArmorObj* arg0)
{
    func_80015930(5, 0);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003BB20);

void func_8003BDA0(struct RideArmorObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    func_8003C6EC(arg0, arg0->unk80.bytes.unk82);
    func_8003CCBC(arg0);
    if (arg0->unk7D == 0) {
        func_8003CB08(arg0);
    }
    func_8003C8F4(arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8003CD38(arg0);
}

void func_8003BE28(struct RideArmorObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->unk2C = FIXED(0.3125);
    }
    self->unk67 = 1;
    func_8003C6EC(self, 4);
    if ((*(u32*)&self->unk70 & 5) != 5) {
        func_8002B694(ANIMATED_OBJECT(self));
        if (self->y_vel.val < 0) {
            self->unk5 = 4;
            self->unk6 = 0;
        } else if (!((u16)self->unk8A & 0x80)) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->y_vel.val = 0;
        }
    } else {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_vel.val = 0;
        if (self->unk70 & 1) {
            self->x_vel.val = 0;
            self->unk28 = 0;
        }
    }
    func_8003CCBC(self);
    if (self->unk7D != 0) {
        self->unk8E.value = 1;
    }
    func_8003CBCC(self);
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003BF1C);

INCLUDE_ASM("main/nonmatchings/bike", func_8003C08C);

void func_8003C584(struct RideArmorObj* arg0)
{
    arg0->unk67 = 1;
    func_8003C6EC(arg0, 3);
    if (!(arg0->unk70 & 4)) {
        func_8003C624(arg0);
        if (arg0->y_vel.val < 0) {
            arg0->unk6 = 3;
            func_8001540C(5, 0, NULL);
        }
    } else {
        arg0->unk6 = 3;
        arg0->y_vel.val = 0;
        if (arg0->unk70 & 1) {
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8003C624(struct RideArmorObj* arg0)
{
    u32 value;

    if ((u32)((u8)arg0->unk6 - 1) < 4U) {
        value = arg0->unk94.value;
        value += arg0->unk90.value;
        arg0->unk94.value = value;
        background_objects[arg0->bg_offset].unk47 -= value >> 16;
        if (background_objects[arg0->bg_offset].unk47 < 6) {
            background_objects[arg0->bg_offset].unk47 = 6;
        }
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003C6EC);

void func_8003C8F4(struct RideArmorObj* arg0)
{
    if (arg0->unk8C.value & 0x80) {
        if (arg0->unk7D == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->y_vel.val = FIXED(6.5);
            arg0->unk80.bytes.unk80 |= 2;
            func_80015D60(arg0, 2);
            func_8003B458(arg0, 0x45);
        } else {
            arg0->y_vel.val = FIXED(6.5);
            arg0->unk8E.value = 1;
            arg0->unk6 = 0;
            arg0->unk67 = 1;
            arg0->unk80.bytes.unk80 |= 2;
        }
    }
}

void func_8003C9A4(struct RideArmorObj* arg0)
{
    if ((arg0->unk80.bytes.unk82 != arg0->unk80.bytes.unk83) && (arg0->unk80.bytes.unk80 & 1) && ((arg0->unk80.packed & 0xFFFF0000) == 0x20000)) {
        arg0->unk2C = FIXED(0.3125);
        arg0->unk6 = 2;
        arg0->unk80.bytes.unk80 |= 2;
        arg0->y_vel.val = (((arg0->x_vel.val < 0 ? -arg0->x_vel.val : arg0->x_vel.val) * 2) / 237) << 8;
    }
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003CA44);

void func_8003CB08(struct RideArmorObj* arg0)
{
    u16 flags;

    flags = arg0->unk8A;
    arg0->unk80.bytes.unk80 &= 0xFE;
    if (flags & 3) {
        if (flags & 1) {
            if (arg0->x_vel.val < D_800F9098[arg0->unk7D]) {
                arg0->x_vel.val = D_800F9098[arg0->unk7D];
                arg0->unk28 = 0;
            }
            arg0->unk7C = 1;
            return;
        }
        if (flags & 2) {
            if (arg0->x_vel.val >= D_800F9090[arg0->unk7D]) {
                arg0->x_vel.val = D_800F9090[arg0->unk7D];
                arg0->unk28 = 0;
            }
            arg0->unk7C = 0;
        }
    } else {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk7C = 1;
        arg0->unk80.bytes.unk80 &= 0xFE;
    }
}

void func_8003CBCC(struct RideArmorObj* arg0)
{
    u16 flags;
    s32 velocity;
    s32 limit;

    flags = arg0->unk8A;
    if ((flags & 3) || arg0->unk7D != 0) {
        if (flags & 1) {
            velocity = arg0->x_vel.val;
            if (velocity == 0) {
                arg0->unk28 = FIXED(0.125);
            } else {
                limit = D_800F9098[arg0->unk7D];
                if (velocity >= limit) {
                    arg0->x_vel.val = limit;
                    arg0->unk28 = 0;
                }
            }
            arg0->unk7C = 1;
        } else if (flags & 2) {
            velocity = arg0->x_vel.val;
            if (velocity == 0) {
                arg0->unk28 = FIXED(-0.125);
            } else {
                limit = D_800F9090[arg0->unk7D];
                if (velocity < limit) {
                    arg0->x_vel.val = limit;
                    arg0->unk28 = 0;
                }
            }
            arg0->unk7C = 0;
        }
    } else {
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk7C = 1;
    }
}

void func_8003CCBC(struct RideArmorObj* arg0)
{
    if (arg0->unk7D == 0 && (arg0->unk7E != 0 || (arg0->unk8C.value & 0x100) != 0)) {
        arg0->unk7D = 1;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk98.bytes.high = 0;
        arg0->unk80.bytes.unk80 |= 3;
        func_8001540C(5, 1, NULL);
    }
}

void func_8003CD38(struct RideArmorObj* arg0)
{
    s32 limit;

    switch (func_8003CF24(arg0)) {
    case 0:
        if (arg0->unk7C == 0) {
            limit = D_800F9070[arg0->unk7D];
            if (arg0->x_vel.val <= limit) {
                arg0->x_vel.val = limit;
                func_8003D39C(MAIN_OBJECT(arg0));
            } else {
                func_8002B694(ANIMATED_OBJECT(arg0));
            }
        } else {
            limit = D_800F9078[arg0->unk7D];
            if (arg0->x_vel.val < limit) {
                func_8003D338(ANIMATED_OBJECT(arg0));
                func_8002B718(MOVING_OBJECT(arg0));
            } else {
                func_8002B694(ANIMATED_OBJECT(arg0));
            }
        }
        break;
    case 1:
        if (arg0->unk7C != 0) {
            limit = D_800F9080[arg0->unk7D];
            if (arg0->x_vel.val < limit) {
                func_8003D338(ANIMATED_OBJECT(arg0));
                func_8002B718(MOVING_OBJECT(arg0));
            } else {
                arg0->x_vel.val = limit;
                func_8003D39C(MAIN_OBJECT(arg0));
            }
        } else {
            limit = D_800F9088[arg0->unk7D];
            if (limit < arg0->x_vel.val) {
                func_8003D338(ANIMATED_OBJECT(arg0));
                func_8002B718(MOVING_OBJECT(arg0));
            } else {
                func_8002B694(ANIMATED_OBJECT(arg0));
            }
        }
        break;
    default:
        if (arg0->unk7C == 0) {
            func_8002B694(ANIMATED_OBJECT(arg0));
            limit = D_800F9090[arg0->unk7D];
            if (limit - arg0->x_vel.val >= 0) {
                arg0->x_vel.val = limit;
            }
        } else {
            func_8003D338(ANIMATED_OBJECT(arg0));
            func_8002B718(MOVING_OBJECT(arg0));
            limit = D_800F9098[arg0->unk7D];
            if (limit - arg0->x_vel.val < 0) {
                arg0->x_vel.val = limit;
            }
        }
        break;
    }
}

INCLUDE_ASM("main/nonmatchings/bike", func_8003CF24);

INCLUDE_ASM("main/nonmatchings/bike", func_8003CF6C);

INCLUDE_ASM("main/nonmatchings/bike", func_8003D01C);

void func_8003D164(struct VisualObj* arg0, s32 arg1)
{
    s32 v;
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0xD;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->unk3C;
        v = (u8)func_8002938C(0x82);
        obj->unk42 = SOME_COORDINATE_CONVERSION(v);
        obj->unk16 = arg0->unk16;
        obj->unk50 = arg0;
        obj->unk15 = arg0->unk15;
    }
}

void func_8003D254(struct VisualObj* arg0)
{
    s32 v;
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0xF;
        obj->unk2 = 0;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->unk3C;
        v = (u8)func_8002938C(0x82);
        obj->unk42 = SOME_COORDINATE_CONVERSION(v);
        obj->unk16 = arg0->unk16;
        obj->unk50 = arg0;
        obj->unk15 = arg0->unk15;
    }
}

void func_8003D338(struct AnimatedObj* arg0)
{
    arg0->y_vel.val -= arg0->unk2C;
    arg0->x_vel.val -= arg0->unk28;
}

void func_8003D35C(struct MainObj* arg0)
{
    arg0->y_pos.val -= arg0->unk24;
    arg0->unk24 -= arg0->unk2C;
    if (arg0->unk24 < -FIXED(6.5)) {
        arg0->unk24 = -FIXED(6.5);
    }
}

void func_8003D39C(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_8003D3B4(struct PlayerObj* arg0)
{
    if (g_Player.unkC5 != 0 && arg0->charge_state[0] != PLAYER_CHARGE_NONE) {
        g_Player.x_pos = arg0->x_pos;
        g_Player.y_pos = arg0->y_pos;
    }
}

union AnimationStep D_800F8DC8[] = { { 0x00000001 } };

union AnimationStep D_800F8DCC[] = { { 0x01000001 } };

union AnimationStep D_800F8DD0[] = { { 0x02000001 } };

union AnimationStep D_800F8DD4[] = {
    { 0x00010002 },
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010001 },
    { 0x00010001 },
    { 0x06010003 },
    { 0x00000001 },
};

union AnimationStep D_800F8DF0[] = {
    { 0x01010002 },
    { 0x07010002 },
    { 0x08010006 },
    { 0x07010001 },
    { 0x01010001 },
    { 0x09010003 },
    { 0x01000001 },
};

union AnimationStep D_800F8E0C[] = {
    { 0x02010002 },
    { 0x0A010002 },
    { 0x0B010006 },
    { 0x0A010001 },
    { 0x02010001 },
    { 0x0C010003 },
    { 0x02000001 },
};

union AnimationStep D_800F8E28[] = { { 0x00010002 }, { 0x02010002 }, { 0x03010008 }, { 0x03000001 } };

union AnimationStep D_800F8E38[] = { { 0x03010008 }, { 0x02010002 }, { 0x00010002 }, { 0x00000001 } };

union AnimationStep D_800F8E48[] = { { 0x01010002 }, { 0x00010002 }, { 0x02010002 }, { 0x03010008 }, { 0x03000001 } };

union AnimationStep D_800F8E5C[] = { { 0x03010008 }, { 0x02010002 }, { 0x00010002 }, { 0x01010002 }, { 0x01000001 } };

union AnimationStep D_800F8E70[] = { { 0x02010002 }, { 0x03010008 }, { 0x03000001 } };

union AnimationStep D_800F8E7C[] = { { 0x03010002 }, { 0x02010008 }, { 0x02000001 } };

union AnimationStep D_800F8E88[] = { { 0x0D010001 }, { 0x0E010001 }, { 0x0FFE0001 } };

union AnimationStep D_800F8E94[] = { { 0x10010002 }, { 0x11010002 }, { 0x12FE0003 } };

union AnimationStep D_800F8EA0[] = { { 0x13010002 }, { 0x14010002 }, { 0x15FE0003 } };

union AnimationStep D_800F8EAC[] = { { 0x16010002 }, { 0x17010002 }, { 0x18FE0003 } };

union AnimationStep D_800F8EB8[] = { { 0x19010002 }, { 0x1A010002 }, { 0x1BFE0003 } };

union AnimationStep D_800F8EC4[] = { { 0x1C010002 }, { 0x1D010001 }, { 0x1E010002 }, { 0x1FFD0001 } };

union AnimationStep D_800F8ED4[] = { { 0x20010002 }, { 0x21010001 }, { 0x22010002 }, { 0x23FD0001 } };

union AnimationStep D_800F8EE4[] = { { 0x24010002 }, { 0x25010001 }, { 0x26010002 }, { 0x27FD0001 } };

union AnimationStep D_800F8EF4[] = { { 0x28010002 }, { 0x29010001 }, { 0x2A010002 }, { 0x2BFD0001 } };

union AnimationStep D_800F8F04[] = {
    { 0x2C010002 },
    { 0x2D010101 },
    { 0x2E010201 },
    { 0x2F010301 },
    { 0x30010402 },
    { 0x31010501 },
    { 0x31FA0501 },
};

union AnimationStep D_800F8F20[] = {
    { 0x32010002 },
    { 0x33010101 },
    { 0x34010201 },
    { 0x35010301 },
    { 0x36010402 },
    { 0x37010501 },
    { 0x37FA0501 },
};

union AnimationStep D_800F8F3C[] = {
    { 0x38010002 },
    { 0x39010101 },
    { 0x3A010201 },
    { 0x3B010001 },
    { 0x3C010402 },
    { 0x3D010501 },
    { 0x3DFA0001 },
};

union AnimationStep D_800F8F58[] = {
    { 0x3E010002 },
    { 0x3F010101 },
    { 0x40010201 },
    { 0x41010301 },
    { 0x42010402 },
    { 0x43010501 },
    { 0x43FA0501 },
};

union AnimationStep D_800F8F74[] = {
    { 0x44010003 },
    { 0x45010002 },
    { 0x46010002 },
    { 0x47010003 },
    { 0x48010003 },
    { 0x49010002 },
    { 0x4A010002 },
    { 0x4BFA0003 },
};

union AnimationStep D_800F8F94[] = { { 0x4C000001 } };

union AnimationStep D_800F8F98[] = { { 0x4D000001 } };

union AnimationStep D_800F8F9C[] = { { 0x4E000001 } };

union AnimationStep D_800F8FA0[] = { { 0x4F000001 } };

union AnimationStep D_800F8FA4[] = { { 0x50000001 } };

union AnimationStep D_800F8FA8[] = { { 0x51000001 } };

union AnimationStep D_800F8FAC[] = { { 0x52000001 } };

union AnimationStep D_800F8FB0[] = { { 0x53000001 } };

union AnimationStep D_800F8FB4[] = { { 0x54000001 } };

union AnimationStep D_800F8FB8[] = { { 0x55000001 } };

union AnimationStep D_800F8FBC[] = { { 0x56000001 } };

union AnimationStep D_800F8FC0[] = { { 0x57000001 } };

union AnimationStep* D_800F8FC4[38] = {
    D_800F8DC8,
    D_800F8DCC,
    D_800F8DD0,
    D_800F8DD4,
    D_800F8DF0,
    D_800F8E0C,
    D_800F8E28,
    D_800F8E38,
    D_800F8E48,
    D_800F8E5C,
    D_800F8E70,
    D_800F8E7C,
    D_800F8E88,
    D_800F8E94,
    D_800F8EAC,
    D_800F8EA0,
    D_800F8EB8,
    D_800F8EC4,
    D_800F8ED4,
    D_800F8EE4,
    D_800F8EF4,
    D_800F8F04,
    D_800F8F20,
    D_800F8F3C,
    D_800F8F58,
    D_800F8F74,
    D_800F8F94,
    D_800F8F98,
    D_800F8F9C,
    D_800F8FA0,
    D_800F8FA4,
    D_800F8FA8,
    D_800F8FAC,
    D_800F8FB0,
    D_800F8FB4,
    D_800F8FB8,
    D_800F8FBC,
    D_800F8FC0,
};

u8 D_800F905C[12] = { 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25 };

u8 D_800F9068[4] = { 0xFF, 0x0F, 0x1A, 0x0B };

u8 D_800F906C[4] = { 0xEB, 0xFC, 0x25, 0x16 };

s32 D_800F9070[2] = { -0x28000, -0x48000 };

s32 D_800F9078[2] = { 0x18000, 0x38000 };

s32 D_800F9080[2] = { 0x28000, 0x48000 };

s32 D_800F9088[2] = { -0x18000, -0x38000 };

s32 D_800F9090[2] = { -0x20000, -0x40000 };

s32 D_800F9098[2] = { 0x20000, 0x40000 };

u16 D_800F90A0[28] = {
    0xA2,
    0xA6,
    0xAA,
    0xAE,
    0xA3,
    0xA4,
    0xA5,
    0xA7,
    0xA8,
    0xA9,
    0xAB,
    0xAC,
    0xAD,
    0,
    0xAF,
    0xB1,
    0xB3,
    0xB5,
    0xAF,
    0xAF,
    0xAF,
    0xB1,
    0xB1,
    0xB1,
    0xB3,
    0xB3,
    0xB3,
    0,
};

void (*D_800F90D8[])(struct RideArmorObj*) = {
    func_8003B470,
    func_8003B7B4,
    func_8003BA24,
    func_8003BAE8,
};

void (*D_800F90E8[6])() = {
    func_8003BB20,
    func_8003BDA0,
    func_8003BE28,
    func_8003C584,
    func_8003BF1C,
    func_8003C08C,
};

u8 D_800F9100[4] = {
    0x0A,
    0x08,
    0x06,
    0x00,
};

u8 D_800F9104[4] = {
    0x0B,
    0x09,
    0x07,
    0x00,
};

u8 D_800F9108[4] = {
    0x02,
    0x01,
    0x00,
    0x00,
};

u8 D_800F910C[4] = {
    0x49,
    0x48,
    0x47,
    0x00,
};

u8 D_800F9110[4] = {
    0x4C,
    0x4B,
    0x4A,
    0x00,
};

u8 D_800F9114[4] = {
    0x45,
    0x43,
    0x41,
    0x00,
};
