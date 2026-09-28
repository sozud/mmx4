// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"
#include "func_tables.h"

void func_8005A4CC(struct MainObj* arg0)
{
    if (arg0->unk2 >= 0) {
        D_800FD838[arg0->state](arg0);
    } else {
        D_800FD848[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A538);

void func_8005A6C0(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FD858[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x68, 0x68);
    } else {
        arg0->state = 2;
    }
}

void func_8005A750(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A758);

void func_8005AA0C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AA14);

u8 func_8005AB34(struct MainObj* arg0)
{
    s32 state;

    state = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    if ((u8)(state - 4) >= 24) {
        state = 1;
    }
    if ((u8)(state - 4) < 8) {
        state = 2;
    }
    if ((u8)(state - 12) < 8) {
        state = 0;
    }
    if ((u8)(state - 20) < 8) {
        state = 3;
    }
    return state;
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005ABC0);

void func_8005ACA0(struct MainObj* arg0)
{
    struct Main29Ext* context;
    struct Main29Record* record;
    struct Main29Record* target;

    context = &SP_CUR_MAIN_OBJ->ext.main_29;
    record = context->slots.controller.record;
    target = context->slots.controller.target;
    if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
        record->unk4 = 2;
    }
    target->unk4 = 2;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AD00);

void func_8005AEB4(struct MainObj* arg0)
{
    struct MainObj* source = arg0->ext.main_29.source;

    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->on_screen = 1;
    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = source->animation_table;
    __builtin_memcpy(&arg0->animation_speed, &source->animation_speed, sizeof(u32));
    arg0->sprite_frames = source->sprite_frames;
    arg0->unk40 = source->unk40;
    arg0->unk42 = source->unk42;
    arg0->unk16 = 7;
    arg0->unk7C = 0;
    arg0->ext.main_29.unk94 = 0;
    func_80015D60(arg0, 5);
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B24C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B2C8);

union AnimationStep D_800FD658[] = {
    { 0x00000001 },
};

union AnimationStep D_800FD65C[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00000002 },
};

union AnimationStep D_800FD688[] = {
    { 0x00010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010003 },
    { 0x09000003 },
};

union AnimationStep D_800FD69C[] = {
    { 0x08010003 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x00000003 },
};

union AnimationStep D_800FD6AC[] = {
    { 0x0A010001 },
    { 0x14010001 },
    { 0x0B010001 },
    { 0x14010001 },
    { 0x0C010001 },
    { 0x14010001 },
    { 0x0D010001 },
    { 0x0E000001 },
};

union AnimationStep D_800FD6CC[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x13010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x11010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x12010001 },
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0EF10001 },
};

union AnimationStep D_800FD70C[] = {
    { 0x20010102 },
    { 0x1F010202 },
    { 0x1E010302 },
    { 0x1D010402 },
    { 0x1C010402 },
    { 0x1B000402 },
};

union AnimationStep D_800FD724[] = {
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x16010002 },
    { 0x1A010002 },
    { 0x18F90002 },
};

union AnimationStep D_800FD744[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20000002 },
};

union AnimationStep D_800FD75C[] = {
    { 0x2C010502 },
    { 0x2B010602 },
    { 0x2A010702 },
    { 0x29010802 },
    { 0x28010802 },
    { 0x27000802 },
};

union AnimationStep D_800FD774[] = {
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x22010002 },
    { 0x26010002 },
    { 0x24F90002 },
};

union AnimationStep D_800FD794[] = {
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C000002 },
};

union AnimationStep D_800FD7AC[] = {
    { 0x3A010902 },
    { 0x39010A02 },
    { 0x38010B02 },
    { 0x37010C02 },
    { 0x36010C02 },
    { 0x35000C02 },
};

union AnimationStep D_800FD7C4[] = {
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x30010002 },
    { 0x34010002 },
    { 0x31F90002 },
};

union AnimationStep D_800FD7E4[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FD7E8[] = {
    { 0x2E000001 },
};

union AnimationStep* D_800FD7EC[] = {
    D_800FD658,
    D_800FD65C,
    D_800FD688,
    D_800FD6AC,
    D_800FD69C,
    D_800FD6CC,
    D_800FD70C,
    D_800FD724,
    D_800FD744,
    D_800FD75C,
    D_800FD774,
    D_800FD794,
    D_800FD7AC,
    D_800FD7C4,
    D_800FD7E4,
    D_800FD7E8,
};

u8 D_800FD82C[4] = { 0x0E, 0x0F, 0, 0 };

struct Unk_unk68 D_800FD830[] = {
    { -20, -18, 0x27, 0x24 },
};

struct Unk_unk68 D_800FD834[] = {
    { -13, -14, 0x1A, 0x1B },
};

void (*D_800FD838[])() = {
    func_8005A538,
    func_8005A6C0,
    func_8005ACA0,
    func_8005AD00,
};

void (*D_800FD848[])(struct MainObj*) = {
    func_8005AEB4,
    func_8005AF5C,
    func_8005B24C,
    func_8005B2C8,
};

void (*D_800FD858[])(struct MainObj*) = {
    func_8009216C,
    func_8005A750,
    func_8005A758,
    func_8005AA0C,
    func_8005AA14,
};

s16 D_800FD86C[] = {
    0x0001,
    0x0002,
    0x0003,
    0x0003,
    0x0002,
    0x0001,
    -1,
    -2,
    -3,
    -3,
    -2,
    -1,
};

s16 D_800FD884[] = {
    -3,
    -2,
    -1,
    0x0001,
    0x0002,
    0x0003,
    0x0003,
    0x0002,
    0x0001,
    -1,
    -2,
    -3,
};

u8 D_800FD89C[] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
};
