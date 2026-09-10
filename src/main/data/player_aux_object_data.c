#include "common.h"
#include "func_tables.h"

void (*D_800F9AF8[7])() = {
    func_8009216C,
    func_80042384,
    func_800423A0,
    func_80042414,
    func_800424CC,
    func_8004258C,
    func_8004272C,
};
void (*D_800F9B14[3])() = { func_800425C8, func_80042648, func_800426BC };
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
