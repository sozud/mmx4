#include "common.h"
#include "func_tables.h"

extern struct Unk_unk68 D_800F9B24[];
extern u8 D_800F9C44[];
extern u8 D_800F9C48[];

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

struct Unk_unk68 D_800F9CCC = { 0, -1, 11, 18 };

struct Unk_unk68 D_800F9CD0 = { -7, -16, 18, 33 };

struct Unk_unk68 D_800F9CD4 = { -14, -20, 32, 37 };

struct Unk_unk68 D_800F9CD8 = { -7, -10, 15, 25 };

struct Unk_unk68 D_800F9CDC = { -13, -19, 26, 36 };

union AnimationStep D_800F9CE0[] = {
    { 0x00000001 },
};

union AnimationStep D_800F9CE4[] = {
    { 0x01010006 },
    { 0x02010004 },
    { 0x01010006 },
    { 0x03010006 },
    { 0x04010004 },
    { 0x03010006 },
    { 0x0501000E },
    { 0x06010006 },
    { 0x07010004 },
    { 0x06010006 },
    { 0x08010006 },
    { 0x09010004 },
    { 0x08010006 },
    { 0x0AF3000E },
};

union AnimationStep D_800F9D1C[] = {
    { 0x0B01000E },
    { 0x0C010006 },
    { 0x0D010004 },
    { 0x0C010008 },
    { 0x0E01000D },
    { 0x0E000101 },
};

union AnimationStep D_800F9D34[] = {
    { 0x0F010002 },
    { 0x10010002 },
    { 0x00010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x00010002 },
    { 0x11010004 },
    { 0x12010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x12010006 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010301 },
    { 0x16010001 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1A010002 },
    { 0x1B010406 },
    { 0x1C010002 },
    { 0x1D010005 },
    { 0x1D010201 },
    { 0x1D010004 },
    { 0x1E010006 },
    { 0x1F010002 },
    { 0x1D01000E },
    { 0x1D000101 },
};

union AnimationStep D_800F9DB0[] = {
    { 0x1D010002 },
    { 0x1C010002 },
    { 0x1B010006 },
    { 0x1A010302 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x16010002 },
    { 0x15010202 },
    { 0x12010006 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x11010001 },
    { 0x11000101 },
};

union AnimationStep D_800F9DF4[] = {
    { 0x1D010003 },
    { 0x20010003 },
    { 0x21FE0003 },
};

union AnimationStep D_800F9E00[] = {
    { 0x22000002 },
};

union AnimationStep D_800F9E04[] = {
    { 0x23000001 },
};

union AnimationStep D_800F9E08[] = {
    { 0x24000001 },
};

union AnimationStep D_800F9E0C[] = {
    { 0x25000001 },
};

union AnimationStep D_800F9E10[] = {
    { 0x26000001 },
};

union AnimationStep D_800F9E14[] = {
    { 0x27000001 },
};

union AnimationStep D_800F9E18[] = {
    { 0x28000001 },
};

union AnimationStep* D_800F9E1C[] = {
    D_800F9CE0,
    D_800F9CE4,
    D_800F9D1C,
    D_800F9D34,
    D_800F9DB0,
    D_800F9DF4,
    D_800F9E00,
    D_800F9E04,
    D_800F9E08,
    D_800F9E0C,
    D_800F9E10,
    D_800F9E14,
    D_800F9E18,
};

#ifdef VERSION_JP
u8 D_800F9F8C_jp[] = { 6, 7, 8, 9, 10, 11, 12, 0 };
#endif
