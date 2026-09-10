#include "common.h"
#include "func_tables.h"

void (*D_800FBA08[6])() = {
    func_8009216C,
    func_8004D1C8,
    func_8004D1D4,
    func_8004D2E0,
    func_8004D408,
    func_8004D5E0,
};

void (*D_800FBA20[2])() = {
    func_8004D210,
    func_8004D290,
};

void (*D_800FBA28[3])() = {
    func_8004D31C,
    func_8004D370,
    func_8004D3C8,
};

void (*D_800FBA34[4])() = {
    func_8004D444,
    func_8004D480,
    func_8004D4D0,
    func_8004D580,
};

void (*D_800FBA44[2])() = {
    func_8004D61C,
    func_8004D69C,
};

struct Unk_unk68 D_800FBA4C = { 0, 1, 11, 12 };

struct Unk_unk68 D_800FBA50 = { -11, -16, 21, 29 };

struct Unk_unk68 D_800FBA54 = { -12, -4, 21, 18 };

union AnimationStep D_800FBA58[] = {
    { 0x00000001 },
};

union AnimationStep D_800FBA5C[] = {
    { 0x01010008 },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010003 },
    { 0x05010005 },
    { 0x06010008 },
    { 0x07010008 },
    { 0x08010008 },
    { 0x09010003 },
    { 0x0AF70005 },
};

union AnimationStep D_800FBA84[] = {
    { 0x00010006 },
    { 0x0B01000A },
    { 0x0C010102 },
    { 0x0D010002 },
    { 0x0E010003 },
    { 0x0E000001 },
};

union AnimationStep D_800FBA9C[] = {
    { 0x0F010002 },
    { 0x10FF0002 },
};

union AnimationStep D_800FBAA4[] = {
    { 0x11010003 },
    { 0x0B01000A },
    { 0x12010002 },
    { 0x00010003 },
    { 0x12010002 },
    { 0x12000001 },
};

union AnimationStep D_800FBABC[] = {
    { 0x00010006 },
    { 0x12010001 },
    { 0x13010002 },
    { 0x14010102 },
    { 0x15010001 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18000001 },
};

union AnimationStep D_800FBAE4[] = {
    { 0x18010006 },
    { 0x17010001 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010001 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x00010002 },
    { 0x12010002 },
    { 0x00000001 },
};

union AnimationStep D_800FBB0C[] = {
    { 0x00010006 },
    { 0x19010006 },
    { 0x1A010008 },
    { 0x1B010102 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x0001000A },
    { 0x00000001 },
};

union AnimationStep D_800FBB2C[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20FE0002 },
};

union AnimationStep D_800FBB38[] = {
    { 0x21000001 },
};

union AnimationStep D_800FBB3C[] = {
    { 0x22000001 },
};

union AnimationStep D_800FBB40[] = {
    { 0x23000001 },
};

union AnimationStep D_800FBB44[] = {
    { 0x24000001 },
};

union AnimationStep D_800FBB48[] = {
    { 0x25000001 },
};

union AnimationStep* D_800FBB4C[14] = {
    D_800FBA58,
    D_800FBA5C,
    D_800FBA84,
    D_800FBA9C,
    D_800FBAA4,
    D_800FBABC,
    D_800FBAE4,
    D_800FBB0C,
    D_800FBB2C,
    D_800FBB38,
    D_800FBB3C,
    D_800FBB40,
    D_800FBB44,
    D_800FBB48,
};

u8 D_800FBB84[4] = { 9, 10, 11, 12 };

void (*D_800FBB88[6])() = {
    func_8009216C,
    func_8004E218,
    func_8004DF40,
    func_8004DFEC,
    func_8004E128,
    func_8004DEA0,
};

void (*D_800FBBA0[6])() = {
    func_8004E55C,
    func_8004E6A4,
    func_8004E810,
    func_8004E300,
    func_8004E490,
    func_8004D930,
};

struct Unk_unk68 D_800FBBB8 = { -14, -28, 30, 59 };

struct Unk_unk68 D_800FBBBC = { -16, -8, 34, 37 };

struct Unk_unk68 D_800FBBC0 = { -11, -17, 19, 47 };

struct Unk_unk68 D_800FBBC4 = { -89, -1, 69, 13 };

struct Unk_unk68 D_800FBBC8 = { 2, 2, 18, 26 };

union AnimationStep D_800FBBCC[] = {
    { 0x00010007 },
    { 0x00000101 },
};

union AnimationStep D_800FBBD4[] = {
    { 0x01010007 },
    { 0x01000101 },
};

union AnimationStep D_800FBBDC[] = {
    { 0x0A010003 },
    { 0x0BFF0103 },
};

union AnimationStep D_800FBBE4[] = {
    { 0x0C010001 },
    { 0x0D010002 },
    { 0x0C000101 },
};

union AnimationStep D_800FBBF0[] = {
    { 0x0C010008 },
    { 0x0D010008 },
    { 0x0C01001B },
    { 0x0C000101 },
};

union AnimationStep D_800FBC00[] = {
    { 0x02010003 },
    { 0x03000101 },
};

union AnimationStep D_800FBC08[] = {
    { 0x04010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x07010001 },
    { 0x05010001 },
    { 0x06FB0101 },
};

union AnimationStep D_800FBC20[] = {
    { 0x11010002 },
    { 0x11000101 },
};

union AnimationStep D_800FBC28[] = {
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0FFE0101 },
};

union AnimationStep D_800FBC34[] = {
    { 0x12010001 },
    { 0x13FF0101 },
};

union AnimationStep D_800FBC3C[] = {
    { 0x14010001 },
    { 0x15FF0101 },
};

union AnimationStep D_800FBC44[] = {
    { 0x16010001 },
    { 0x17FF0101 },
};

union AnimationStep D_800FBC4C[] = {
    { 0x18010014 },
    { 0x1A010002 },
    { 0x19010201 },
    { 0x19010001 },
    { 0x1B010001 },
    { 0x1C010013 },
    { 0x1C000101 },
};

union AnimationStep D_800FBC68[] = {
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010001 },
    { 0x1E000101 },
};

union AnimationStep D_800FBC84[] = {
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21FE0002 },
};

union AnimationStep D_800FBC90[] = {
    { 0x00010008 },
    { 0x23010002 },
    { 0x22010022 },
    { 0x22000101 },
};

union AnimationStep D_800FBCA0[] = {
    { 0x24010002 },
    { 0x2501000E },
    { 0x25000101 },
};

union AnimationStep D_800FBCAC[] = {
    { 0x26010002 },
    { 0x2701000E },
    { 0x27000101 },
};

union AnimationStep D_800FBCB8[] = {
    { 0x28010002 },
    { 0x29FF0102 },
};

union AnimationStep D_800FBCC0[] = {
    { 0x2A010002 },
    { 0x2BFF0002 },
};

union AnimationStep D_800FBCC8[] = {
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010003 },
    { 0x30010003 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x33000101 },
};

union AnimationStep D_800FBCEC[] = {
    { 0x34000101 },
};

union AnimationStep D_800FBCF0[] = {
    { 0x35000101 },
};

union AnimationStep D_800FBCF4[] = {
    { 0x36000101 },
};

union AnimationStep D_800FBCF8[] = {
    { 0x37000101 },
};

union AnimationStep D_800FBCFC[] = {
    { 0x38000101 },
};

union AnimationStep D_800FBD00[] = {
    { 0x39000101 },
};

union AnimationStep D_800FBD04[] = {
    { 0x3A000101 },
};

union AnimationStep D_800FBD08[] = {
    { 0x3B000101 },
};

union AnimationStep* D_800FBD0C[29] = {
    D_800FBBCC,
    D_800FBBD4,
    D_800FBBDC,
    D_800FBBF0,
    D_800FBC00,
    D_800FBC08,
    D_800FBC20,
    D_800FBC28,
    D_800FBC44,
    D_800FBC3C,
    D_800FBC34,
    D_800FBCB8,
    D_800FBCC0,
    D_800FBC4C,
    D_800FBC68,
    D_800FBC84,
    D_800FBBE4,
    D_800FBC90,
    D_800FBCA0,
    D_800FBCAC,
    D_800FBCC8,
    D_800FBCEC,
    D_800FBCF0,
    D_800FBCF4,
    D_800FBCF8,
    D_800FBCFC,
    D_800FBD00,
    D_800FBD04,
    D_800FBD08,
};

u8 D_800FBD80[12] = { 21, 22, 23, 24, 25, 25, 25, 25, 26, 27, 28, 0 };

void (*D_800FBD8C[4])() = {
    func_8004E8E0,
    func_8004EA88,
    func_8004EC44,
    func_8004ECB0,
};

void (*D_800FBD9C[11])() = {
    func_8009216C,
    func_8004FAE4,
    func_8004ECE4,
    func_8004EF14,
    func_8004EFA4,
    func_8004F1A0,
    func_8004F228,
    func_8004F424,
    func_8004F67C,
    func_8004F9B4,
    func_8004FAAC,
};

void (*D_800FBDC8[2])() = {
    func_8004ED20,
    func_8004ED60,
};

void (*D_800FBDD0[3])() = {
    func_8004EFE0,
    func_8004F0C4,
    func_8004F118,
};

void (*D_800FBDDC[3])() = {
    func_8004F264,
    func_8004F2A0,
    func_8004F34C,
};

void (*D_800FBDE8[3])() = {
    func_8004F460,
    func_8004F4D4,
    func_8004F62C,
};

void (*D_800FBDF4[3])() = {
    func_8004F6B8,
    func_8004F7D0,
    func_8004F910,
};

struct Unk_unk68 D_800FBE00 = { -8, -13, 15, 26 };

struct Unk_unk68 D_800FBE04 = { -7, -11, 12, 22 };

struct Unk_unk68 D_800FBE08 = { 0, 0, 5, 13 };

struct Unk_unk68 D_800FBE0C = { -12, -1, 25, 13 };

struct Unk_unk68 D_800FBE10 = { -10, 1, 21, 10 };

struct Unk_unk68 D_800FBE14 = { 0, 5, 13, 8 };

union AnimationStep D_800FBE18[] = {
    { 0x00010008 },
    { 0x03010003 },
    { 0x04010004 },
    { 0x05010006 },
    { 0x04010004 },
    { 0x03010002 },
    { 0x03000101 },
};

union AnimationStep D_800FBE34[] = {
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000B },
    { 0x0000010C },
};

union AnimationStep D_800FBE5C[] = {
    { 0x06010005 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x07010204 },
    { 0x0901003C },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0901001D },
    { 0x09000101 },
};

union AnimationStep D_800FBE84[] = {
    { 0x0B000101 },
};

union AnimationStep D_800FBE88[] = {
    { 0x0C000101 },
};

union AnimationStep D_800FBE8C[] = {
    { 0x0D000101 },
};

union AnimationStep D_800FBE90[] = {
    { 0x0E000101 },
};

union AnimationStep* D_800FBE94[7] = {
    D_800FBE18,
    D_800FBE34,
    D_800FBE5C,
    D_800FBE84,
    D_800FBE88,
    D_800FBE8C,
    D_800FBE90,
};

u8 D_800FBEB0[4] = { 3, 4, 5, 6 };

void (*D_800FBEB4[3])() = {
    func_8004FFE0,
    func_800500D4,
    func_80050238,
};

void (*D_800FBEC0[7])() = {
    func_8009216C,
    func_8005026C,
    func_80050278,
    func_80050418,
    func_80050480,
    func_80050540,
    func_80050644,
};

s16 D_800FBEDC[12] = {
    (s16)0x0001,
    (s16)0x0002,
    (s16)0x0004,
    (s16)0x0008,
    (s16)0x0010,
    (s16)0x0020,
    (s16)0x0040,
    (s16)0x0080,
    (s16)0x0100,
    (s16)0x0200,
    (s16)0xF3F8,
    (s16)0x1A0F,
};

struct Unk_unk68 D_800FBEF4 = { -18, -33, 38, 70 };

struct Unk_unk68 D_800FBEF8 = { -16, -19, 34, 34 };

struct Unk_unk68 D_800FBEFC = { -24, -66, 29, 111 };

struct Unk_unk68 D_800FBF00 = { -26, -15, 33, 30 };

struct Unk_unk68 D_800FBF04 = { -14, -9, 24, 19 };

struct Unk_unk68 D_800FBF08 = { -16, -22, 27, 51 };

struct Unk_unk68 D_800FBF0C = { 0, -17, 24, 39 };

struct Unk_unk68 D_800FBF10 = { 0, -3, 24, 20 };

union AnimationStep D_800FBF14[] = {
    { 0x00010008 },
    { 0x01010009 },
    { 0x0201000A },
    { 0x03FD0109 },
};

union AnimationStep D_800FBF24[] = {
    { 0x00010002 },
    { 0x04010004 },
    { 0x00010001 },
    { 0x05010002 },
    { 0x0601021D },
    { 0x06000101 },
};

union AnimationStep D_800FBF3C[] = {
    { 0x00010012 },
    { 0x0701000E },
    { 0x04010010 },
    { 0x07FD000E },
};

union AnimationStep D_800FBF4C[] = {
    { 0x00010002 },
    { 0x08010006 },
    { 0x01010004 },
    { 0x09010203 },
    { 0x0A010002 },
    { 0x0BFF0102 },
};

union AnimationStep D_800FBF64[] = {
    { 0x06010003 },
    { 0x0C010007 },
    { 0x0D010206 },
    { 0x0E010005 },
    { 0x0D000101 },
};

union AnimationStep D_800FBF78[] = {
    { 0x0D010001 },
    { 0x0E010007 },
    { 0x0D01001D },
    { 0x0D000101 },
};

union AnimationStep D_800FBF88[] = {
    { 0x0C010003 },
    { 0x06010005 },
    { 0x05010002 },
    { 0x40010201 },
    { 0x04010006 },
    { 0x40000101 },
};

union AnimationStep D_800FBFA0[] = {
    { 0x00010004 },
    { 0x10010204 },
    { 0x11010003 },
    { 0x12010002 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x13010007 },
    { 0x14010004 },
    { 0x15010003 },
    { 0x16010002 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17000101 },
};

union AnimationStep D_800FBFF4[] = {
    { 0x18010003 },
    { 0x19010005 },
    { 0x18010003 },
    { 0x17010014 },
    { 0x1A010005 },
    { 0x1B010005 },
    { 0x17010005 },
    { 0x1A010004 },
    { 0x1B010004 },
    { 0x17010004 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x17010003 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x17010001 },
    { 0x1C010201 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010301 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010401 },
    { 0x2C010001 },
    { 0x2D010001 },
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x2B010001 },
    { 0x2C010001 },
    { 0x2D010001 },
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D000101 },
};

union AnimationStep D_800FC130[] = {
    { 0x0601000A },
    { 0x05010001 },
    { 0x40010001 },
    { 0x04010006 },
    { 0x40010201 },
    { 0x3E010002 },
    { 0x3F010304 },
    { 0x3E010001 },
    { 0x3E000101 },
};

union AnimationStep D_800FC154[] = {
    { 0x13010008 },
    { 0x2E010001 },
    { 0x41010202 },
    { 0x42010305 },
    { 0x41010002 },
    { 0x2E000101 },
};

union AnimationStep D_800FC16C[] = {
    { 0x2E010005 },
    { 0x3A010006 },
    { 0x3B010207 },
    { 0x3A010006 },
    { 0x2E010005 },
    { 0x3C010006 },
    { 0x3D010007 },
    { 0x3CF90006 },
};

union AnimationStep D_800FC18C[] = {
    { 0x0B010004 },
    { 0x0A010005 },
    { 0x0F010007 },
    { 0x09010205 },
    { 0x02010004 },
    { 0x01010003 },
    { 0x0001000E },
    { 0x00000101 },
};

union AnimationStep D_800FC1AC[] = {
    { 0x2F010004 },
    { 0x30010005 },
    { 0x31010006 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x31010001 },
    { 0x32000101 },
};

union AnimationStep D_800FC1D4[] = {
    { 0x33010004 },
    { 0x34010005 },
    { 0x35010006 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36010001 },
    { 0x35010001 },
    { 0x36000101 },
};

union AnimationStep D_800FC1FC[] = {
    { 0x37010004 },
    { 0x38010005 },
    { 0x39010006 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010001 },
    { 0x39010001 },
    { 0x13010007 },
    { 0x14010004 },
    { 0x15010003 },
    { 0x16010002 },
    { 0x17010201 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17010001 },
    { 0x16010001 },
    { 0x17000101 },
};

union AnimationStep D_800FC24C[] = {
    { 0x3B000101 },
};

union AnimationStep D_800FC250[] = {
    { 0x45000101 },
};

union AnimationStep D_800FC254[] = {
    { 0x44000101 },
};

union AnimationStep D_800FC258[] = {
    { 0x43000101 },
};

union AnimationStep D_800FC25C[] = {
    { 0x4A000101 },
};

union AnimationStep D_800FC260[] = {
    { 0x49000101 },
};

union AnimationStep D_800FC264[] = {
    { 0x48000101 },
};

union AnimationStep D_800FC268[] = {
    { 0x47000101 },
};

union AnimationStep D_800FC26C[] = {
    { 0x46000101 },
};

union AnimationStep D_800FC270[] = {
    { 0x4B000101 },
};

union AnimationStep D_800FC274[] = {
    { 0x4C000101 },
};

union AnimationStep D_800FC278[] = {
    { 0x4D000101 },
};

union AnimationStep D_800FC27C[] = {
    { 0x4E000101 },
};

union AnimationStep D_800FC280[] = {
    { 0x62010001 },
    { 0x63010009 },
    { 0x64010009 },
    { 0x65010009 },
    { 0x66010009 },
    { 0x67010009 },
    { 0x68010009 },
    { 0x69010009 },
    { 0x5E000101 },
};

union AnimationStep D_800FC2A4[] = {
    { 0x5F000101 },
};

union AnimationStep D_800FC2A8[] = {
    { 0x60000101 },
};

union AnimationStep D_800FC2AC[] = {
    { 0x61000101 },
};

union AnimationStep D_800FC2B0[] = {
    { 0x18000101 },
};

union AnimationStep* D_800FC2B4[34] = {
    D_800FBF14,
    D_800FBF24,
    D_800FBF3C,
    D_800FBF4C,
    D_800FBF64,
    D_800FBF78,
    D_800FBF88,
    D_800FBFA0,
    D_800FBFF4,
    D_800FC130,
    D_800FC154,
    D_800FC16C,
    D_800FC18C,
    D_800FC1AC,
    D_800FC1D4,
    D_800FC1FC,
    D_800FC24C,
    D_800FC250,
    D_800FC254,
    D_800FC258,
    D_800FC25C,
    D_800FC260,
    D_800FC264,
    D_800FC268,
    D_800FC26C,
    D_800FC270,
    D_800FC274,
    D_800FC278,
    D_800FC27C,
    D_800FC280,
    D_800FC2A4,
    D_800FC2A8,
    D_800FC2AC,
    D_800FC2B0,
};

u8 D_800FC33C[4] = { 25, 26, 27, 28 };

u8 D_800FC340[4] = { 31, 32, 0, 0 };

void (*D_800FC344[5])() = {
    func_8005077C,
    func_80050874,
    func_80050A9C,
    func_80050BC4,
    func_80050BFC,
};

void (*D_800FC358[12])() = {
    func_8009216C,
    func_80050C64,
    func_80050C70,
    func_80050E08,
    func_80050FE4,
    func_80051338,
    func_800523EC,
    func_80052444,
    func_8005172C,
    func_80051C94,
    func_80052008,
    func_800521DC,
};

void (*D_800FC388[2])() = {
    func_80050CAC,
    func_80050D14,
};

void (*D_800FC390[3])() = {
    func_80050E44,
    func_80050EB0,
    func_80050F60,
};

void (*D_800FC39C[6])() = {
    func_80051020,
    func_80051060,
    func_800510D4,
    func_8005115C,
    func_800511E8,
    func_800512BC,
};

void (*D_800FC3B4[6])() = {
    func_80051374,
    func_800513DC,
    func_800514A4,
    func_80051564,
    func_80051630,
    func_80051678,
};

void (*D_800FC3CC[4])() = {
    func_80051768,
    func_800517D0,
    func_80051A4C,
    func_80051B74,
};

void (*D_800FC3DC[4])() = {
    func_80051CD0,
    func_80051D60,
    func_80051F68,
    func_80051F94,
};

void (*D_800FC3EC[3])() = {
    func_80052044,
    func_8005216C,
    func_800521B0,
};

void (*D_800FC3F8[5])() = {
    func_80052218,
    func_800522A8,
    func_800522C8,
    func_80052324,
    func_80052374,
};

union AnimationStep D_800FC40C[] = {
    { 0x00000001 },
};

union AnimationStep D_800FC410[] = {
    { 0x01000001 },
};

union AnimationStep D_800FC414[] = {
    { 0x0001000A },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010009 },
    { 0x05010101 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F30002 },
};

union AnimationStep D_800FC450[] = {
    { 0x0101000A },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0C010008 },
    { 0x0D010009 },
    { 0x0D010101 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F30002 },
};

union AnimationStep D_800FC48C[] = {
    { 0x0101000A },
    { 0x40010008 },
    { 0x41010008 },
    { 0x42010008 },
    { 0x43010009 },
    { 0x43010101 },
    { 0x44010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F30002 },
};

union AnimationStep D_800FC4C8[] = {
    { 0x00010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18F70002 },
};

union AnimationStep D_800FC4F0[] = {
    { 0x01010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1FF70002 },
};

union AnimationStep D_800FC518[] = {
    { 0x18010003 },
    { 0x21010003 },
    { 0x20FE0003 },
};

union AnimationStep D_800FC524[] = {
    { 0x1F010003 },
    { 0x22010003 },
    { 0x23FE0003 },
};

union AnimationStep D_800FC530[] = {
    { 0x1F010003 },
    { 0x23010003 },
    { 0x22FE0003 },
};

union AnimationStep D_800FC53C[] = {
    { 0x1801000A },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x00010002 },
    { 0x13010002 },
    { 0x00FA000A },
};

union AnimationStep D_800FC558[] = {
    { 0x1F01000A },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x1A010002 },
    { 0x01010002 },
    { 0x1A010002 },
    { 0x01FA000A },
};

union AnimationStep D_800FC574[] = {
    { 0x24010006 },
    { 0x25010006 },
    { 0x26010006 },
    { 0x27010003 },
    { 0x28010012 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010002 },
    { 0x29010003 },
    { 0x2A010103 },
    { 0x2B010002 },
    { 0x2801000F },
    { 0x27010003 },
    { 0x26010006 },
    { 0x25010006 },
    { 0x24F10006 },
};

union AnimationStep D_800FC5B4[] = {
    { 0x2C010006 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010003 },
    { 0x30010012 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x31010003 },
    { 0x32010103 },
    { 0x33010002 },
    { 0x3001000F },
    { 0x2F010003 },
    { 0x2E010006 },
    { 0x2D010006 },
    { 0x2CF10006 },
};

union AnimationStep D_800FC5F4[] = {
    { 0x06010102 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F80002 },
};

union AnimationStep D_800FC618[] = {
    { 0x0E010102 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F80002 },
};

union AnimationStep D_800FC63C[] = {
    { 0x44010102 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F80002 },
};

union AnimationStep D_800FC660[] = {
    { 0x34010002 },
    { 0x35010001 },
    { 0x36010002 },
    { 0x37FD0001 },
};

union AnimationStep D_800FC670[] = {
    { 0x38000001 },
};

union AnimationStep D_800FC674[] = {
    { 0x39000001 },
};

union AnimationStep D_800FC678[] = {
    { 0x3A000001 },
};

union AnimationStep D_800FC67C[] = {
    { 0x3B000001 },
};

union AnimationStep D_800FC680[] = {
    { 0x3C000001 },
};

union AnimationStep D_800FC684[] = {
    { 0x3D000001 },
};

union AnimationStep D_800FC688[] = {
    { 0x3E000001 },
};

union AnimationStep D_800FC68C[] = {
    { 0x3F000001 },
};

union AnimationStep D_800FC690[] = {
    { 0x45010003 },
    { 0x46010003 },
    { 0x47FE0003 },
};

union AnimationStep* D_800FC69C[27] = {
    D_800FC40C,
    D_800FC410,
    D_800FC414,
    D_800FC450,
    D_800FC48C,
    D_800FC4C8,
    D_800FC4F0,
    D_800FC518,
    D_800FC524,
    D_800FC530,
    D_800FC53C,
    D_800FC558,
    D_800FC574,
    D_800FC5B4,
    D_800FC5F4,
    D_800FC618,
    D_800FC63C,
    D_800FC660,
    D_800FC670,
    D_800FC674,
    D_800FC678,
    D_800FC67C,
    D_800FC680,
    D_800FC684,
    D_800FC688,
    D_800FC68C,
    D_800FC690,
};

u8 D_800FC708[8] = { 18, 19, 20, 21, 22, 23, 24, 25 };

struct Unk_unk68 D_800FC710 = { 0, -9, 27, 18 };

struct Unk_unk68 D_800FC714 = { -10, 0, 20, 25 };

struct Unk_unk68 D_800FC718 = { 0, -16, 39, 30 };

struct Unk_unk68 D_800FC71C = { -18, 0, 35, 36 };

struct Unk_unk68 D_800FC720 = { 22, 0, 22, 18 };

struct Unk_unk68 D_800FC724 = { 0, 21, 18, 21 };

struct Unk_unk68 D_800FC728 = { 16, 0, 16, 16 };

struct Unk_unk68 D_800FC72C = { 0, 16, 16, 16 };

struct Unk_unk68 D_800FC730 = { 0, -16, 16, 16 };

struct Unk_unk68 D_800FC734 = { -10, -25, 20, 25 };

struct Unk_unk68 D_800FC738 = { -18, -35, 35, 35 };

struct Unk_unk68* D_800FC73C[2] = {
    &D_800FC720,
    &D_800FC724,
};

struct Unk_unk68* D_800FC744[2] = {
    &D_800FC718,
    &D_800FC71C,
};

struct Unk_unk68* D_800FC74C[2] = {
    &D_800FC710,
    &D_800FC714,
};

struct Unk_unk68* D_800FC754[4] = {
    &D_800FC738,
    &D_800FC718,
    &D_800FC71C,
    &D_800FC718,
};

struct Unk_unk68* D_800FC764[4] = {
    &D_800FC734,
    &D_800FC710,
    &D_800FC714,
    &D_800FC710,
};

struct Unk_unk68* D_800FC774[4] = {
    &D_800FC730,
    &D_800FC728,
    &D_800FC72C,
    &D_800FC728,
};

void (*D_800FC784[3])() = {
    func_800528BC,
    func_80052A68,
    func_80053D04,
};

void (*D_800FC790[3])() = {
    func_80053D24,
    func_80053EB8,
    func_80053D04,
};

void (*D_800FC79C[6])() = {
    func_8009216C,
    func_80052B94,
    func_80052C2C,
    func_80052C2C,
    func_80053604,
    func_80052C70,
};

u8 D_800FC7B4[4] = { 0x0E, 0x0F, 0x10, 0x00 };

void (*D_800FC7B8[7])() = {
    func_80052CB8,
    func_80052E94,
    func_800531B4,
    func_80053224,
    func_80053274,
    func_80053338,
    func_800535CC,
};

u8 D_800FC7D4[4] = { 0x03, 0x04, 0x00, 0x00 };

u8 D_800FC7D8[4] = { 0x00, 0x40, 0x00, 0x00 };

void (*D_800FC7DC[2])() = {
    func_80053640,
    func_8005368C,
};

u8 D_800FC7E4[4] = { 0x0D, 0x0C, 0x00, 0x00 };

s16 D_800FC7E8[6] = {
    (s16)0xFFE2,
    (s16)0x0000,
    (s16)0x001E,
    (s16)0x0000,
    (s16)0x0000,
    (s16)0x001C,
};

void (*D_800FC7F4[6])() = {
    func_8009216C,
    func_80054518,
    func_8005402C,
    func_8005402C,
    func_8005402C,
    func_80052C70,
};

u8 D_800FC80C[8] = { 0x02, 0x08, 0x01, 0x04, 0x01, 0x04, 0x02, 0x08 };

s16 D_800FC814[8] = {
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
};

s16 D_800FC824[8] = {
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
};

u8 D_800FC834[8] = { 0x00, 0x40, 0x40, 0x00, 0x40, 0x40, 0x00, 0x00 };

u8 D_800FC83C[8] = { 0x1A, 0x09, 0x07, 0x08, 0x1A, 0x08, 0x07, 0x09 };

struct Unk_unk68 D_800FC844 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC848 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC84C = { -24, -36, 48, 48 };

struct Unk_unk68 D_800FC850 = { -15, -16, 29, 64 };

struct Unk_unk68 D_800FC854 = { -15, -48, 29, 64 };

struct Unk_unk68 D_800FC858 = { -15, -16, 29, 32 };

struct Unk_unk68 D_800FC85C = { -15, -48, 29, 96 };

struct Unk_unk68 D_800FC860 = { 0, 0, 0, 0 };

union AnimationStep D_800FC864[] = {
    { 0x0001000C },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x01F40001 },
};

union AnimationStep D_800FC898[] = {
    { 0x04010003 },
    { 0x05010002 },
    { 0x06010003 },
    { 0x07010008 },
    { 0x00010002 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x09010001 },
    { 0x08F60002 },
};

union AnimationStep D_800FC8C8[] = {
    { 0x10010003 },
    { 0x11010004 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010003 },
    { 0x17010103 },
    { 0x18010003 },
    { 0x19010004 },
    { 0x1A010004 },
    { 0x1AF50001 },
};

union AnimationStep D_800FC8F8[] = {
    { 0x1B010003 },
    { 0x1C010004 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010003 },
    { 0x22010103 },
    { 0x23010003 },
    { 0x24010004 },
    { 0x25010004 },
    { 0x25F50001 },
};

union AnimationStep D_800FC928[] = {
    { 0x26010003 },
    { 0x27010004 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010003 },
    { 0x2D010103 },
    { 0x2E010003 },
    { 0x2F010004 },
    { 0x30010004 },
    { 0x30F50001 },
};

union AnimationStep D_800FC958[] = {
    { 0x0C000001 },
};

union AnimationStep D_800FC95C[] = {
    { 0x0D000001 },
};

union AnimationStep D_800FC960[] = {
    { 0x0E000001 },
};

union AnimationStep D_800FC964[] = {
    { 0x0F000001 },
};

union AnimationStep* D_800FC968[9] = {
    D_800FC864,
    D_800FC898,
    D_800FC958,
    D_800FC95C,
    D_800FC960,
    D_800FC964,
    D_800FC8C8,
    D_800FC8F8,
    D_800FC928,
};

u8 D_800FC98C[4] = { 2, 3, 4, 5 };

void (*D_800FC990[3])() = {
    func_800545EC,
    func_80054758,
    func_80054BBC,
};

void (*D_800FC99C[3])() = {
    func_8009216C,
    func_80054710,
    func_80054738,
};

void (*D_800FC9A8[3])() = {
    func_800548B8,
    func_80054B38,
    func_80054B98,
};

union AnimationStep D_800FC9B4[] = {
    { 0x01010003 },
    { 0x02010005 },
    { 0x03010003 },
    { 0x00000150 },
};

union AnimationStep D_800FC9C4[] = {
    { 0x04000001 },
};

union AnimationStep D_800FC9C8[] = {
    { 0x05000001 },
};

union AnimationStep D_800FC9CC[] = {
    { 0x06000001 },
};

union AnimationStep D_800FC9D0[] = {
    { 0x07010006 },
    { 0x08010006 },
    { 0x09000106 },
};

union AnimationStep* D_800FC9DC[5] = {
    D_800FC9B4,
    D_800FC9C4,
    D_800FC9C8,
    D_800FC9CC,
    D_800FC9D0,
};

u8 D_800FC9F0[4] = { 1, 2, 3, 0 };

struct Unk_unk68 D_800FC9F4 = { -8, -16, 16, 32 };

struct Unk_unk68 D_800FC9F8 = { 0, 0, 8, 16 };

void (*D_800FC9FC[4])() = {
    func_80054CA8,
    func_80054D8C,
    func_80054EF8,
    func_80054F14,
};

void (*D_800FCA0C[5])() = {
    func_8009216C,
    func_80054FDC,
    func_80054F34,
    func_80054F98,
    func_80054FBC,
};

struct Unk_unk68 D_800FCA20 = { -19, -48, 37, 92 };

union AnimationStep D_800FCA24[] = {
    { 0x00000001 },
};

union AnimationStep D_800FCA28[] = {
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010005 },
    { 0x02010004 },
    { 0x01010003 },
    { 0x00010014 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A000001 },
};

union AnimationStep D_800FCA5C[] = {
    { 0x09010003 },
    { 0x08010003 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010003 },
    { 0x04000003 },
};

union AnimationStep D_800FCA74[] = {
    { 0x0B000003 },
};

union AnimationStep D_800FCA78[] = {
    { 0x0C000003 },
};

union AnimationStep D_800FCA7C[] = {
    { 0x0D000003 },
};

union AnimationStep D_800FCA80[] = {
    { 0x0E000003 },
};

union AnimationStep D_800FCA84[] = {
    { 0x0F000003 },
};

union AnimationStep* D_800FCA88[8] = {
    D_800FCA24,
    D_800FCA28,
    D_800FCA5C,
    D_800FCA74,
    D_800FCA78,
    D_800FCA7C,
    D_800FCA80,
    D_800FCA84,
};

u8 D_800FCAA8[8] = { 4, 5, 6, 7, 4, 5, 6, 7 };

s16 D_800FCAB0 = (s16)0xFFD0;

s16 D_800FCAB2 = (s16)0x000A;

u8 D_800FCAB4[56] = { 0x03, 0x00, 0x30, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xEA, 0xFF, 0x45, 0x00, 0x04, 0x00, 0x16, 0x00, 0x45, 0x00, 0x04, 0x00, 0xD8, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x28, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xD8, 0xFF, 0x24, 0x00, 0x04, 0x00, 0x28, 0x00, 0x24, 0x00, 0x04, 0x00, 0xE6, 0xFF, 0xE4, 0xFF, 0x03, 0x00, 0x1A, 0x00, 0xE4, 0xFF, 0x03, 0x00 };
