#include "common.h"
#include "func_tables.h"

void (*D_800FFC4C[2])() = {
    func_8009216C,
    func_80069A8C,
};

struct Unk_unk68 D_800FFC54 = { -27, -35, 62, 66 };

struct Unk_unk68 D_800FFC58 = { -27, -32, 58, 66 };

struct Unk_unk68 D_800FFC5C = { 3, 0, 27, 32 };

union AnimationStep D_800FFC60[] = {
    { 0x00010015 },
    { 0x01010016 },
    { 0x00010015 },
    { 0x02FD0014 },
};

union AnimationStep D_800FFC70[] = {
    { 0x00010001 },
    { 0x03010002 },
    { 0x04010004 },
    { 0x05000007 },
};

union AnimationStep D_800FFC80[] = {
    { 0x00010001 },
    { 0x06010002 },
    { 0x07010004 },
    { 0x05000007 },
};

union AnimationStep D_800FFC90[] = {
    { 0x08010004 },
    { 0x09010004 },
    { 0x0A010004 },
    { 0x0B010004 },
    { 0x0C010006 },
    { 0x0D000008 },
};

union AnimationStep D_800FFCA8[] = {
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11FD0002 },
};

union AnimationStep D_800FFCB8[] = {
    { 0x00010005 },
    { 0x12010006 },
    { 0x13010007 },
    { 0x12010006 },
    { 0x00010007 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x1600000A },
};

union AnimationStep D_800FFCF0[] = {
    { 0x16010004 },
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010005 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x00000003 },
};

union AnimationStep D_800FFD0C[] = {
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1FFD0001 },
};

union AnimationStep D_800FFD1C[] = {
    { 0x20000001 },
};

union AnimationStep D_800FFD20[] = {
    { 0x21000001 },
};

union AnimationStep D_800FFD24[] = {
    { 0x22000001 },
};

union AnimationStep D_800FFD28[] = {
    { 0x23000001 },
};

union AnimationStep D_800FFD2C[] = {
    { 0x24000001 },
};

union AnimationStep D_800FFD30[] = {
    { 0x25010003 },
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010003 },
    { 0x29FC0003 },
};

union AnimationStep* D_800FFD44[14] = {
    D_800FFC60,
    D_800FFC70,
    D_800FFC80,
    D_800FFC90,
    D_800FFCA8,
    D_800FFCB8,
    D_800FFCF0,
    D_800FFD0C,
    D_800FFD1C,
    D_800FFD20,
    D_800FFD24,
    D_800FFD28,
    D_800FFD2C,
    D_800FFD30,
};

u8 D_800FFD7C[8] = { 8, 9, 10, 11, 12, 0, 0, 0 };

void (*D_800FFD84[4])() = {
    func_80069AD0,
    func_80069BE4,
    func_80069CE4,
    func_80069D74,
};

void (*D_800FFD94[7])() = {
    func_8009216C,
    func_80069D94,
    func_80069DA0,
    func_80069E28,
    func_80069FDC,
    func_8006A130,
    func_8006A208,
};

void (*D_800FFDB0[1])() = {
    func_80069DDC,
};

void (*D_800FFDB4[2])() = {
    func_80069E64,
    func_80069F28,
};

void (*D_800FFDBC[3])() = {
    func_8006A018,
    func_8006A078,
    func_8006A0E4,
};

void (*D_800FFDC8[2])() = {
    func_8006A16C,
    func_8006A1B4,
};

struct Unk_unk68 D_800FFDD0 = { -14, -19, 25, 33 };

struct Unk_unk68 D_800FFDD4 = { -10, -18, 16, 30 };

struct Unk_unk68 D_800FFDD8 = { 0, 0, 6, 15 };

union AnimationStep D_800FFDDC[] = {
    { 0x0F010008 },
    { 0x10010008 },
    { 0x11010007 },
    { 0x12010008 },
    { 0x13010008 },
    { 0x14FB0107 },
};

union AnimationStep D_800FFDF4[] = {
    { 0x00010008 },
    { 0x01010006 },
    { 0x02010003 },
    { 0x02010201 },
    { 0x03010006 },
    { 0x04000106 },
};

union AnimationStep D_800FFE0C[] = {
    { 0x16010001 },
    { 0x15010006 },
    { 0x15000101 },
};

union AnimationStep D_800FFE18[] = {
    { 0x18010001 },
    { 0x17010006 },
    { 0x17000101 },
};

union AnimationStep D_800FFE24[] = {
    { 0x1A010001 },
    { 0x19010006 },
    { 0x19000101 },
};

union AnimationStep D_800FFE30[] = {
    { 0x1C010001 },
    { 0x1B010006 },
    { 0x1B000101 },
};

union AnimationStep D_800FFE3C[] = {
    { 0x1E010001 },
    { 0x1D010006 },
    { 0x1D000101 },
};

union AnimationStep D_800FFE48[] = {
    { 0x06010001 },
    { 0x05010006 },
    { 0x05000101 },
};

union AnimationStep D_800FFE54[] = {
    { 0x08010001 },
    { 0x07010006 },
    { 0x07000101 },
};

union AnimationStep D_800FFE60[] = {
    { 0x0A010001 },
    { 0x09010006 },
    { 0x09000101 },
};

union AnimationStep D_800FFE6C[] = {
    { 0x0C010001 },
    { 0x0B010006 },
    { 0x0B000101 },
};

union AnimationStep D_800FFE78[] = {
    { 0x0E010001 },
    { 0x0D010006 },
    { 0x0D000101 },
};

union AnimationStep D_800FFE84[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21FE0001 },
};

union AnimationStep D_800FFE90[] = {
    { 0x22000101 },
};

union AnimationStep D_800FFE94[] = {
    { 0x23000101 },
};

union AnimationStep D_800FFE98[] = {
    { 0x24000101 },
};

union AnimationStep D_800FFE9C[] = {
    { 0x25000101 },
};

union AnimationStep D_800FFEA0[] = {
    { 0x03010006 },
    { 0x01010005 },
    { 0x01000101 },
};

union AnimationStep D_800FFEAC[] = {
    { 0x17010002 },
    { 0x15010001 },
    { 0x15000101 },
};

union AnimationStep D_800FFEB8[] = {
    { 0x17000101 },
};

union AnimationStep D_800FFEBC[] = {
    { 0x17010002 },
    { 0x19010001 },
    { 0x19000101 },
};

union AnimationStep D_800FFEC8[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010001 },
    { 0x1B000101 },
};

union AnimationStep D_800FFED8[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010002 },
    { 0x1D010001 },
    { 0x1D000101 },
};

union AnimationStep D_800FFEEC[] = {
    { 0x07010002 },
    { 0x05010001 },
    { 0x05000101 },
};

union AnimationStep D_800FFEF8[] = {
    { 0x07000101 },
};

union AnimationStep D_800FFEFC[] = {
    { 0x07010002 },
    { 0x09010001 },
    { 0x09000101 },
};

union AnimationStep D_800FFF08[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010001 },
    { 0x0B000101 },
};

union AnimationStep D_800FFF18[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010002 },
    { 0x0D010001 },
    { 0x0D000101 },
};

union AnimationStep* D_800FFF2C[28] = {
    D_800FFDDC,
    D_800FFDF4,
    D_800FFE0C,
    D_800FFE18,
    D_800FFE24,
    D_800FFE30,
    D_800FFE3C,
    D_800FFE48,
    D_800FFE54,
    D_800FFE60,
    D_800FFE6C,
    D_800FFE78,
    D_800FFE84,
    D_800FFE90,
    D_800FFE94,
    D_800FFE98,
    D_800FFE9C,
    D_800FFEA0,
    D_800FFEAC,
    D_800FFEB8,
    D_800FFEBC,
    D_800FFEC8,
    D_800FFED8,
    D_800FFEEC,
    D_800FFEF8,
    D_800FFEFC,
    D_800FFF08,
    D_800FFF18,
};

u8 D_800FFF9C[4] = { 13, 14, 15, 16 };

void (*D_800FFFA0[3])() = {
    func_8006A55C,
    func_8006A638,
    func_8006A70C,
};

void (*D_800FFFAC[5])() = {
    func_8009216C,
    func_8006A740,
    func_8006A74C,
    func_8006AA18,
    func_8006AC8C,
};

void (*D_800FFFC0[4])() = {
    func_8006A788,
    func_8006A7F0,
    func_8006A83C,
    func_8006A998,
};

void (*D_800FFFD0[2])() = {
    func_8006AA54,
    func_8006AAB4,
};

void (*D_800FFFD8[3])() = {
    func_8006ACC8,
    func_8006AD84,
    func_8006AE0C,
};

struct Unk_unk68 D_800FFFE4 = { -7, 15, 33, 11 };

struct Unk_unk68 D_800FFFE8 = { -40, -5, 50, 29 };

struct Unk_unk68 D_800FFFEC[2] = {
    { -14, -16, 39, 39 },
    { -40, -16, 65, 41 },
};

struct Unk_unk68 D_800FFFF4 = { -30, -10, 49, 30 };

union AnimationStep D_800FFFF8[] = {
    { 0x00010002 },
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010001 },
    { 0x00010001 },
    { 0x06010003 },
    { 0x00000101 },
};

union AnimationStep D_80100014[] = {
    { 0x01010002 },
    { 0x07010002 },
    { 0x08010006 },
    { 0x07010001 },
    { 0x01010001 },
    { 0x09010003 },
    { 0x01000001 },
};

union AnimationStep D_80100030[] = {
    { 0x02010002 },
    { 0x0A010002 },
    { 0x0B010006 },
    { 0x0A010001 },
    { 0x02010001 },
    { 0x0C010003 },
    { 0x02000101 },
};

union AnimationStep D_8010004C[] = {
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100058[] = {
    { 0x01010002 },
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100068[] = {
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep D_80100070[] = {
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0FFE0001 },
};

union AnimationStep D_8010007C[] = {
    { 0x10010002 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010002 },
    { 0x15010001 },
    { 0x15FA0001 },
};

union AnimationStep D_80100098[] = {
    { 0x16010002 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010002 },
    { 0x1B010001 },
    { 0x1BFA0001 },
};

union AnimationStep D_801000B4[] = {
    { 0x1C010002 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010002 },
    { 0x21010001 },
    { 0x21FA0001 },
};

union AnimationStep D_801000D0[] = {
    { 0x22010002 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010002 },
    { 0x27010001 },
    { 0x27FA0001 },
};

union AnimationStep D_801000EC[] = {
    { 0x28010003 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x2FF80001 },
};

union AnimationStep D_80100110[] = {
    { 0x30000001 },
};

union AnimationStep D_80100114[] = {
    { 0x31000001 },
};

union AnimationStep D_80100118[] = {
    { 0x32000001 },
};

union AnimationStep D_8010011C[] = {
    { 0x33000001 },
};

union AnimationStep D_80100120[] = {
    { 0x34000001 },
};

union AnimationStep D_80100124[] = {
    { 0x35000001 },
};

union AnimationStep D_80100128[] = {
    { 0x36000001 },
};

union AnimationStep D_8010012C[] = {
    { 0x37000001 },
};

union AnimationStep D_80100130[] = {
    { 0x38000001 },
};

union AnimationStep D_80100134[] = {
    { 0x39000001 },
};

union AnimationStep D_80100138[] = {
    { 0x3A000001 },
};

union AnimationStep D_8010013C[] = {
    { 0x3B000001 },
};

union AnimationStep D_80100140[] = {
    { 0x3C000001 },
};

union AnimationStep D_80100144[] = {
    { 0x3D000001 },
};

union AnimationStep D_80100148[] = {
    { 0x3E000001 },
};

union AnimationStep* D_8010014C[27] = {
    D_800FFFF8,
    D_80100014,
    D_80100030,
    D_8010004C,
    D_80100058,
    D_80100068,
    D_8010007C,
    D_80100098,
    D_801000B4,
    D_801000D0,
    D_801000EC,
    D_80100070,
    D_80100110,
    D_80100114,
    D_80100118,
    D_8010011C,
    D_80100120,
    D_80100124,
    D_80100128,
    D_8010012C,
    D_80100130,
    D_80100134,
    D_80100138,
    D_8010013C,
    D_80100140,
    D_80100144,
    D_80100148,
};

u8 D_801001B8[8] = { 12, 13, 14, 15, 16, 17, 18, 19 };

u8 D_801001C0[8] = { 20, 21, 22, 23, 24, 25, 26, 0 };

void (*D_801001C8[2])() = {
    func_8006AF70,
    func_8006B114,
};

void (*D_801001D0[7])() = {
    func_8009216C,
    func_8006B1BC,
    func_8006B5F8,
    func_8006B6B0,
    func_8006B79C,
    func_8006B848,
    func_8006B8BC,
};

void (*D_801001EC[3])() = {
    func_8006B180,
    func_8006B8F4,
    func_8006BAA4,
};

union AnimationStep D_801001F8[] = {
    { 0x2225F1EF },
};

union AnimationStep D_801001FC[] = {
    { 0x313AEBE5 },
};

struct Unk_unk68 D_80100200 = { -28, -16, 34, 38 };

struct Unk_unk68 D_80100204 = { -37, -24, 64, 48 };

struct Unk_unk68 D_80100208 = { -11, -30, 29, 57 };

struct Unk_unk68 D_8010020C = { -17, -32, 43, 66 };

struct Unk_unk68 D_80100210 = { -16, -38, 31, 81 };

struct Unk_unk68 D_80100214 = { -22, -43, 43, 93 };

struct Unk_unk68 D_80100218 = { -42, -19, 33, 27 };

struct Unk_unk68 D_8010021C = { -66, -10, 26, 6 };

struct Unk_unk68 D_80100220 = { -15, -29, 26, 50 };

struct Unk_unk68 D_80100224 = { -22, -36, 40, 64 };

struct Unk_unk68 D_80100228 = { -11, -13, 39, 27 };

struct Unk_unk68 D_8010022C = { -20, -22, 57, 46 };

union AnimationStep D_80100230[] = {
    { 0x2244F5C4 },
};

union AnimationStep D_80100234[] = {
    { 0x3959E8C2 },
};

union AnimationStep D_80100238[] = {
    { 0x1F47D0B1 },
};

struct Unk_unk68 D_8010023C = { -48, -73, 49, 48 };

struct Unk_unk68 D_80100240 = { -74, -69, 105, 90 };

struct Unk_unk68 D_80100244 = { -6, -68, 32, 80 };

struct Unk_unk68 D_80100248 = { -15, -71, 48, 96 };

struct Unk_unk68 D_8010024C = { 0, 0, 28, 26 };

u8 D_80100250[4] = { 0, 1, 1, 255 };

u8 D_80100254[4] = { 0, 7, 2, 255 };

u8 D_80100258[4] = { 0, 3, 4, 255 };

u8 D_8010025C[4] = { 0, 7, 2, 255 };

u8 D_80100260[8] = { 5, 3, 4, 6, 255, 0, 0, 0 };

u8 D_80100268[8] = { 0, 7, 2, 2, 255, 0, 0, 0 };

u8 D_80100270[4] = { 5, 6, 6, 255 };

u8* D_80100274[4] = {
    D_80100250,
    D_80100254,
    0x00000000,
    0x00000000,
};

u8* D_80100284[4] = {
    D_80100258,
    D_8010025C,
    0x00000000,
    0x00000000,
};

u8* D_80100294[4] = {
    D_80100260,
    D_80100268,
    D_80100270,
    0x00000000,
};

u8** D_801002A4[3] = {
    D_80100274,
    D_80100284,
    D_80100294,
};

u8 D_801002B0[12] = { 0x07, 0x10, 0x00, 0x09, 0x10, 0x00, 0x07, 0x0A, 0x10, 0x00, 0x00, 0x00 };

union AnimationStep D_801002BC[] = {
    { 0x00000101 },
};

union AnimationStep D_801002C0[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010004 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_801002D8[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010202 },
    { 0x06FF0102 },
};

union AnimationStep D_80100308[] = {
    { 0x02010002 },
    { 0x01010002 },
    { 0x0201000C },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100320[] = {
    { 0x07010002 },
    { 0x08FF0102 },
};

union AnimationStep D_80100328[] = {
    { 0x09010013 },
    { 0x09000101 },
};

union AnimationStep D_80100330[] = {
    { 0x02010002 },
    { 0x01010002 },
    { 0x0201001C },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100348[] = {
    { 0x0A000101 },
};

union AnimationStep D_8010034C[] = {
    { 0x01010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x1F010202 },
    { 0x20010010 },
    { 0x20000101 },
};

union AnimationStep D_80100364[] = {
    { 0x1F010002 },
    { 0x21010002 },
    { 0x22010402 },
    { 0x23010002 },
    { 0x24010201 },
    { 0x25010301 },
    { 0x26010501 },
    { 0x27010001 },
    { 0x28010002 },
    { 0x2701000A },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010602 },
    { 0x2C010702 },
    { 0x2B010001 },
    { 0x2B000101 },
};

union AnimationStep D_801003A4[] = {
    { 0x01010002 },
    { 0x0201001E },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_801003B8[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x1B010201 },
    { 0x1B010007 },
    { 0x1A010002 },
    { 0x00010002 },
    { 0x17010001 },
    { 0x18FF0101 },
};

union AnimationStep D_801003D8[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x0B010001 },
    { 0x0D010001 },
    { 0x0CFE0101 },
};

union AnimationStep D_801003EC[] = {
    { 0x02010001 },
    { 0x0E010001 },
    { 0x09000101 },
};

union AnimationStep D_801003F8[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11FE0101 },
};

union AnimationStep D_80100404[] = {
    { 0x12010002 },
    { 0x13010202 },
    { 0x14010002 },
    { 0x15010014 },
    { 0x14010002 },
    { 0x13010001 },
    { 0x13000101 },
};

union AnimationStep D_80100420[] = {
    { 0x16010001 },
    { 0x0A000101 },
};

union AnimationStep D_80100428[] = {
    { 0x33010002 },
    { 0x34FF0102 },
};

union AnimationStep D_80100430[] = {
    { 0x35010002 },
    { 0x36010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x35010002 },
    { 0x36010018 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100460[] = {
    { 0x37000101 },
};

union AnimationStep D_80100464[] = {
    { 0x30010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x1BFD0101 },
};

union AnimationStep D_80100474[] = {
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2FFE0101 },
};

union AnimationStep D_80100480[] = {
    { 0x03010002 },
    { 0x04FF0102 },
};

union AnimationStep D_80100488[] = {
    { 0x05010002 },
    { 0x06010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x1C010002 },
    { 0x1DFF0102 },
};

union AnimationStep D_801004A0[] = {
    { 0x19000101 },
};

union AnimationStep D_801004A4[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x1B010014 },
    { 0x1A010002 },
    { 0x00010002 },
    { 0x17010001 },
    { 0x18FF0101 },
};

union AnimationStep D_801004C0[] = {
    { 0x38010001 },
    { 0x39FF0101 },
};

union AnimationStep D_801004C8[] = {
    { 0x3A010001 },
    { 0x3BFF0101 },
};

union AnimationStep D_801004D0[] = {
    { 0x74000101 },
};

union AnimationStep D_801004D4[] = {
    { 0x75000101 },
};

union AnimationStep D_801004D8[] = {
    { 0x76000101 },
};

union AnimationStep D_801004DC[] = {
    { 0x77000101 },
};

union AnimationStep D_801004E0[] = {
    { 0x78000101 },
};

union AnimationStep D_801004E4[] = {
    { 0x79000101 },
};

union AnimationStep D_801004E8[] = {
    { 0x7A000101 },
};

union AnimationStep D_801004EC[] = {
    { 0x7B000101 },
};

union AnimationStep D_801004F0[] = {
    { 0x7C000101 },
};

union AnimationStep D_801004F4[] = {
    { 0x05010002 },
    { 0x06FF0102 },
};

union AnimationStep D_801004FC[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010006 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000101 },
};

union AnimationStep* D_80100514[39] = {
    D_801002BC,
    D_801002C0,
    D_801002D8,
    D_80100308,
    D_80100320,
    D_80100328,
    D_80100330,
    D_80100348,
    D_8010034C,
    D_80100364,
    D_801003A4,
    D_801003B8,
    D_801003D8,
    D_801003EC,
    D_801003F8,
    D_80100404,
    D_80100420,
    D_80100428,
    D_80100430,
    D_80100460,
    D_80100464,
    D_80100474,
    D_80100480,
    D_80100488,
    D_801004A0,
    D_801004A4,
    D_801004C0,
    D_801004C8,
    D_801004D0,
    D_801004D4,
    D_801004D8,
    D_801004DC,
    D_801004E0,
    D_801004E4,
    D_801004E8,
    D_801004EC,
    D_801004F0,
    D_801004F4,
    D_801004FC,
};

u8 D_801005B0[4] = { 29, 30, 31, 32 };

char D_801005B4[] = "\"#$";

u16 D_801005B8[8] = {
    0x0070,
    0x0072,
    0x0074,
    0x0076,
    0x0065,
    0x0067,
    0x0069,
    0x006B,
};

u16 D_801005C8[14] = {
    0x0388,
    0x038D,
    0x03AC,
    0x03AF,
    0x03B2,
    0x03B5,
    0x03C3,
    0x0380,
    0x0383,
    0x0390,
    0x0392,
    0x0394,
    0x0396,
    0x03A0,
};
