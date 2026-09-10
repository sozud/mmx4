#include "common.h"
#include "func_tables.h"

void (*D_800FB6B4[9])() = {
    func_8009216C,
    func_8004BC14,
    func_8004BC2C,
    func_8004BCC8,
    func_8004BCFC,
    func_8004BF5C,
    func_8004C210,
    func_8004C394,
    func_8004C56C,
};

u16 D_800FB6D8[18] = {
    0x0010,
    0x0010,
    0x0010,
    0x0010,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0080,
    0x0080,
    0x0080,
    0x0080,
    0x00A0,
    0x00A0,
    0x00C0,
    0x0000,
};

struct Unk_unk68 D_800FB6FC = { -21, -23, 39, 50 };

struct Unk_unk68 D_800FB700 = { -18, -21, 33, 46 };

struct Unk_unk68 D_800FB704 = { 0, 27, 26, 3 };

union AnimationStep D_800FB708[] = {
    { 0x0001000C },
    { 0x0101000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0001000C },
    { 0x0101000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0401000C },
    { 0x0501000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0401000C },
    { 0x0501000C },
    { 0x0201000C },
    { 0x03F1010C },
};

union AnimationStep D_800FB748[] = {
    { 0x0601000A },
    { 0x07010006 },
    { 0x0801000E },
    { 0x0901000D },
    { 0x0D010201 },
    { 0x0D010004 },
    { 0x0A01000E },
    { 0x0B010009 },
    { 0x0B000101 },
};

union AnimationStep D_800FB76C[] = {
    { 0x0601000A },
    { 0x0E010008 },
    { 0x0F010010 },
    { 0x10010008 },
    { 0x11010201 },
    { 0x11010001 },
    { 0x1201000E },
    { 0x13010009 },
    { 0x13000101 },
};

union AnimationStep D_800FB790[] = {
    { 0x1B010010 },
    { 0x1C010212 },
    { 0x1B01000C },
    { 0x1A010212 },
    { 0x1B01000C },
    { 0x1C010212 },
    { 0x1B01000C },
    { 0x1A010211 },
    { 0x1A000101 },
};

union AnimationStep D_800FB7B4[] = {
    { 0x14010003 },
    { 0x15010010 },
    { 0x16010004 },
    { 0x17010005 },
    { 0x18010006 },
    { 0x19010006 },
    { 0x19000101 },
};

union AnimationStep D_800FB7D0[] = {
    { 0x0C000101 },
};

union AnimationStep D_800FB7D4[] = {
    { 0x1D000101 },
};

union AnimationStep D_800FB7D8[] = {
    { 0x1E000101 },
};

union AnimationStep D_800FB7DC[] = {
    { 0x1F000101 },
};

union AnimationStep D_800FB7E0[] = {
    { 0x20000101 },
};

union AnimationStep D_800FB7E4[] = {
    { 0x21000101 },
};

union AnimationStep D_800FB7E8[] = {
    { 0x22000101 },
};

union AnimationStep D_800FB7EC[] = {
    { 0x24000101 },
};

union AnimationStep D_800FB7F0[] = {
    { 0x25000101 },
};

union AnimationStep D_800FB7F4[] = {
    { 0x26000101 },
};

union AnimationStep D_800FB7F8[] = {
    { 0x23000101 },
};

union AnimationStep D_800FB7FC[] = {
    { 0x27000101 },
};

union AnimationStep D_800FB800[] = {
    { 0x28000101 },
};

union AnimationStep* D_800FB804[] = {
    D_800FB708,
    D_800FB748,
    D_800FB76C,
    D_800FB790,
    D_800FB7B4,
    D_800FB7D0,
    D_800FB7D4,
    D_800FB7D8,
    D_800FB7DC,
    D_800FB7E0,
    D_800FB7E4,
    D_800FB7E8,
    D_800FB7EC,
    D_800FB7F0,
    D_800FB7F4,
    D_800FB7F8,
    D_800FB7FC,
    D_800FB800,
};

u8 D_800FB84C[] = {
    0x06,
    0x07,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x00,
    0x00,
    0x00,
};

void (*D_800FB858[])() = {
    func_8004C784,
    func_8004C860,
    func_8004C97C,
    func_8004C9E8,
};

void (*D_800FB868[])() = {
    func_8009216C,
    func_8004CA14,
    func_8004CA20,
    func_8004CBD4,
    func_8004CC64,
    func_8004CDC8,
};

void (*D_800FB880[])() = {
    func_8004CA5C,
    func_8004CA94,
};

void (*D_800FB888[])() = {
    func_8004CCA0,
};

struct Unk_unk68 D_800FB88C = { -10, -15, 32, 25 };

struct Unk_unk68 D_800FB890[3] = {
    { -9, -25, 28, 48 },
    { -27, -25, 33, 52 },
    { -10, 27, 26, 3 },
};

s32 D_800FB89C[] = {
    (s32)0xFFFE0000,
    (s32)0x00020000,
};

union AnimationStep D_800FB8A4[] = {
    { 0x00010005 },
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010004 },
    { 0x04010005 },
    { 0x03010004 },
    { 0x05010003 },
    { 0x01F90004 },
};

union AnimationStep D_800FB8C4[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010006 },
    { 0x0A010008 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010003 },
    { 0x10010005 },
    { 0x0F010003 },
    { 0x0E000003 },
};

union AnimationStep D_800FB8F8[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x11010001 },
    { 0x12FD0001 },
};

union AnimationStep D_800FB908[] = {
    { 0x13010006 },
    { 0x14010006 },
    { 0x15010006 },
    { 0x16FD0006 },
};

union AnimationStep D_800FB918[] = {
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010004 },
    { 0x1AFD0004 },
};

union AnimationStep D_800FB928[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1EFD0002 },
};

union AnimationStep D_800FB938[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22FD0001 },
};

union AnimationStep D_800FB948[] = {
    { 0x28010003 },
    { 0x23010003 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x3A010002 },
    { 0x39010002 },
    { 0x3B000002 },
};

union AnimationStep D_800FB96C[] = {
    { 0x29000001 },
};

union AnimationStep D_800FB970[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FB974[] = {
    { 0x2B000001 },
};

union AnimationStep D_800FB978[] = {
    { 0x2C000001 },
};

union AnimationStep D_800FB97C[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FB980[] = {
    { 0x2E000001 },
};

union AnimationStep D_800FB984[] = {
    { 0x2F010005 },
    { 0x30010004 },
    { 0x31010003 },
    { 0x32FD0004 },
};

union AnimationStep D_800FB994[] = {
    { 0x33000001 },
};

union AnimationStep D_800FB998[] = {
    { 0x34000001 },
};

union AnimationStep D_800FB99C[] = {
    { 0x35010005 },
    { 0x36010005 },
    { 0x37010005 },
    { 0x38FD0005 },
};

union AnimationStep* D_800FB9AC[] = {
    D_800FB8A4,
    D_800FB8C4,
    D_800FB8F8,
    D_800FB908,
    D_800FB918,
    D_800FB928,
    D_800FB938,
    D_800FB948,
    D_800FB96C,
    D_800FB970,
    D_800FB974,
    D_800FB978,
    D_800FB97C,
    D_800FB980,
    D_800FB984,
    D_800FB994,
    D_800FB998,
    D_800FB99C,
};

u8 D_800FB9F4[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
};
