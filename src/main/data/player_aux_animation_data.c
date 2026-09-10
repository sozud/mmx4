#include "common.h"

struct FixedPointPosition D_800F99D4[2] = {
    { -0x800000, 0xB30000 },
    { -0x800000, 0x1700000 },
};
struct FixedPointPosition D_800F99E4[4] = {
    { -0x800000, -0x800000 },
    { -0x800000, 0x1700000 },
    { 0x1C00000, -0x800000 },
    { 0x1C00000, 0x1700000 },
};
u8 D_800F9A04[4] = { 0, 2, 18, 20 };
s8 D_800F9A08[4] = { -19, -16, 46, 38 };

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
