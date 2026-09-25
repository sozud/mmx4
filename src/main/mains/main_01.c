// MainObj, main_object_update_funcs[1]
// 80042120..80042914
#include "common.h"
#include "func_tables.h"

void func_80042120(struct MainObj* arg0)
{
    D_800F9AEC[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

void func_80042170(struct MainObj* arg0)
{
    u8 state;
    s32 y_pos;
    s32 x_pos;
    u8 bg_offset;

    state = (u8)arg0->state;
    arg0->unk5 = 2;
    y_pos = arg0->y_pos.val;
    arg0->unk7C = 0;
    arg0->unk2 = 0;
    state += 1;
    arg0->state = state;
    x_pos = arg0->x_pos.val;
    bg_offset = (u8)g_Player.bg_offset;
    arg0->unk1C.val = y_pos;
    arg0->unk18.val = x_pos;
    arg0->bg_offset = (s8)bg_offset;
    arg0->unk15 = (g_Player.x_pos.val >= arg0->x_pos.val) << 6;
    arg0->animation_table = (u32**)D_800F9AB8;
    arg0->unk16 = 6;
    arg0->unk68 = &D_800F9A04;
    arg0->unk54 = &D_800F9A08;
    arg0->unk50 = &D_800F9A08;
    arg0->collision_data = D_80106370;
    arg0->unk5C = 0xF;
    arg0->unk61 = 0;
    arg0->unk60 = 4;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    func_80015D60(arg0, 1);
}

void func_80042248(struct MainObj* obj)
{
    if (obj->unk5 != 0) {
        func_80042884(obj);
        func_80042824(obj);
        func_800427C0(obj);
    }

    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    if (func_8002DD04(obj) < 0) {
        func_800AF808(obj);
        func_800C813C(5, D_800F9AE4, obj);
        func_800BF60C(BASE_OBJECT(obj), 9);
    } else {
        D_800F9AF8[obj->unk5](obj);
        func_8002D9BC(obj);
        if (func_8002B1E8(BASE_OBJECT(obj), 0x40, 0x40) == 0) {
            func_8002B318(BASE_OBJECT(obj), 0x20, 0x20);
            return;
        }
    }
    obj->state++;
}

void func_8004234C(struct MainObj* arg0)
{
    func_80015930(2, 0xF);
    func_8002B0C8(arg0);
}

void func_80042384(struct MainObj* arg0)
{
    if (arg0->unk67 == 0) {
        arg0->unk5 = 2;
    } else {
        arg0->unk5 = 6;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_01", func_800423A0);

void func_80042414(struct MainObj* arg0)
{
    s32 var_a0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        if (arg0->animation_step.fields.event != 0) {
            func_8001540C(2, 0x11, arg0);
            var_a0 = FIXED(2);
            arg0->unk6++;
            if (arg0->unk15 != 0) {
                var_a0 = FIXED(-2);
            }
            arg0->unk24 = FIXED(6);
            arg0->unk20 = var_a0;
            arg0->unk28 = 0;
            arg0->unk2C = FIXED(0.2578125);
        }
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk24 < 0) {
            func_80015D60(arg0, 4);
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
}

void func_800424CC(struct MainObj* arg0)
{
    s32 distance;
    u8 turn;

    if (arg0->animation_step.fields.event != 0) {
        func_8001540C(2, 0x12, arg0);
        arg0->animation_step.fields.event = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        distance = arg0->x_pos.val - g_Player.x_pos.val;
        if (arg0->unk15 != 0) {
            turn = distance > 0;
        } else {
            turn = distance < 1;
        }
        if (turn) {
            func_80015D60(arg0, 2);
            arg0->unk5 = 5;
        } else {
            func_80015D60(arg0, 1);
            arg0->unk5 = 2;
            arg0->unk67 = 0;
        }
        arg0->unk6 = 0;
        arg0->unk7C = 0;
    }
}

void func_8004258C(struct MainObj* arg0)
{
    D_800F9B14[arg0->unk6](arg0);
}

void func_800425C8(struct MainObj* arg0)
{
    if (arg0->unk7C == 0) {
        arg0->unk6++;
        func_8001540C(2, 0x10, arg0);
        func_80015D60(arg0, 2);
        arg0->unk28 = FIXED(-0.08984375);
    } else {
        arg0->unk7C--;
        func_8002B718(MOVING_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80042648(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 1);
        arg0->unk6++;
        if (arg0->unk67 == 0) {
            arg0->unk7C = 0x1E;
        }
        arg0->unk67 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_800426BC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk7C == 0x1E) {
        func_8001540C(2, 0xF, arg0);
    }
    if (arg0->unk7C == 0) {
        arg0->unk28 = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    } else {
        arg0->unk7C--;
    }
}

void func_8004272C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk28 = 0;
    }
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 5);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_800427C0(struct MainObj* arg0)
{
    if ((arg0->unk67 == 0) && !(arg0->unk70 & 8)) {
        func_80015D60(arg0, 4);
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        arg0->unk67 = -1;
    }
}

void func_80042824(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->unk5 == 2) {
        distance = arg0->x_pos.val - g_Player.x_pos.val;
        if (arg0->unk15 != 0) {
            if (distance > 0) {
                arg0->unk7C = 10;
                arg0->unk5 = 5;
                arg0->unk6 = 0;
            }
        } else if (distance < 0) {
            arg0->unk7C = 10;
            arg0->unk5 = 5;
            arg0->unk6 = 0;
        }
    }
}

void func_80042884(struct MainObj* arg0)
{
    u8 blocked;

    if (arg0->unk67 == 0 && arg0->unk5 == 2) {
        blocked = 0;
        if (arg0->unk15 != 0) {
            blocked = arg0->unk70 & 1;
        } else if (arg0->unk70 & 2) {
            blocked = 1;
        }
        if (blocked != 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            arg0->unk67 = 1;
            func_80015D60(arg0, 3);
        }
    }
}

struct Unk_unk68 D_800F9A04 = { 0, 2, 18, 20 };

struct Unk_unk68 D_800F9A08 = { -19, -16, 46, 38 };

union AnimationStep D_800F9A0C[] = { { 0x00000001 } };

union AnimationStep D_800F9A10[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep D_800F9A1C[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010001 },
    { 0x11000101 },
};

union AnimationStep D_800F9A5C[] = {
    { 0x12010001 },
    { 0x13010101 },
    { 0x14010001 },
    { 0x15FE0001 },
};

union AnimationStep D_800F9A6C[] = {
    { 0x16010001 },
    { 0x17010001 },
    { 0x18FE0001 },
};

union AnimationStep D_800F9A78[] = {
    { 0x19010104 },
    { 0x1B010001 },
    { 0x18010001 },
    { 0x13010006 },
    { 0x17010001 },
    { 0x1C010001 },
    { 0x19010003 },
    { 0x1B010001 },
    { 0x18010004 },
    { 0x1D010001 },
    { 0x1A000002 },
};

union AnimationStep D_800F9AA4[] = { { 0x1E000002 } };

union AnimationStep D_800F9AA8[] = { { 0x1F000001 } };

union AnimationStep D_800F9AAC[] = { { 0x20000001 } };

union AnimationStep D_800F9AB0[] = { { 0x21000001 } };

union AnimationStep D_800F9AB4[] = { { 0x22000001 } };

union AnimationStep* D_800F9AB8[11] = {
    D_800F9A0C,
    D_800F9A10,
    D_800F9A1C,
    D_800F9A5C,
    D_800F9A6C,
    D_800F9A78,
    D_800F9AA4,
    D_800F9AA8,
    D_800F9AAC,
    D_800F9AB0,
    D_800F9AB4,
};

u8 D_800F9AE4[8] = { 6, 7, 8, 9, 10, 0, 0, 0 };

void (*D_800F9AEC[])(struct MainObj*) = {
    func_80042170,
    func_80042248,
    func_8004234C,
};

void (*D_800F9AF8[7])(struct MainObj*) = {
    func_8009216C,
    func_80042384,
    func_800423A0,
    func_80042414,
    func_800424CC,
    func_8004258C,
    func_8004272C,
};

void (*D_800F9B14[3])() = { func_800425C8, func_80042648, func_800426BC };
