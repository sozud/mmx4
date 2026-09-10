#include "common.h"
#include "func_tables.h"

struct Main28InitData {
    u8 unk84;
    u8 unk15;
};

struct Main28InitData D_800FD5FC[4] = {
    { 5, 0x00 },
    { 5, 0x40 },
    { 1, 0x00 },
    { 9, 0x40 },
};

void (*D_800FD604[])() = {
    func_8009216C,
    func_80059E38,
    func_80059E40,
    func_80059F60,
    func_8005A3DC,
};

struct FixedPointPosition D_800FD618[4] = {
    { (s32)0xFFFD0000, 0 },
    { (s32)0x00030000, 0 },
    { 0, (s32)0xFFFD0000 },
    { 0, (s32)0x00030000 },
};

struct FixedPointPosition D_800FD638[4] = {
    { (s32)0xFFFF0000, 0 },
    { (s32)0x00010000, 0 },
    { 0, (s32)0xFFFF0000 },
    { 0, (s32)0x00010000 },
};

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

void (*D_800FD848[])() = {
    func_8005AEB4,
    func_8005AF5C,
    func_8005B24C,
    func_8005B2C8,
};

void (*D_800FD858[])() = {
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
