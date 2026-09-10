#include "common.h"
#include "func_tables.h"

void (*D_800FDC58[10])() = {
    func_8009216C,
    func_8005BA24,
    func_8005BA2C,
    func_8005BB70,
    func_8005BC50,
    func_8005BCA0,
    func_8005BD6C,
    func_8005BDE4,
    func_8005BF48,
    func_8005BFC0,
};

struct Unk_unk68 D_800FDC80 = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FDC84 = { -9, 13, 16, 19 };

struct Unk_unk68 D_800FDC88[2] = {
    { -11, -10, 20, 42 },
    { -10, 27, 26, 3 },
};

s32 D_800FDC90[2] = { (s32)0xFFFD0000, (s32)0x00030000 };

s32 D_800FDC98[2] = { (s32)0xFFFC8000, (s32)0x00038000 };

union AnimationStep D_800FDCA0[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05FB0005 },
};

union AnimationStep D_800FDCB8[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x03010002 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A000003 },
};

union AnimationStep D_800FDCD0[] = {
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0DFD0002 },
};

union AnimationStep D_800FDCE0[] = {
    { 0x0E010005 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010005 },
    { 0x12010003 },
    { 0x13FB0003 },
};

union AnimationStep D_800FDCF8[] = {
    { 0x14000001 },
};

union AnimationStep D_800FDCFC[] = {
    { 0x15000001 },
};

union AnimationStep D_800FDD00[] = {
    { 0x16000001 },
};

union AnimationStep D_800FDD04[] = {
    { 0x17000001 },
};

union AnimationStep* D_800FDD08[8] = {
    D_800FDCA0,
    D_800FDCB8,
    D_800FDCD0,
    D_800FDCE0,
    D_800FDCF8,
    D_800FDCFC,
    D_800FDD00,
    D_800FDD04,
};

u8 D_800FDD28[4] = { 0x04, 0x05, 0x06, 0x07 };

void (*D_800FDD2C[3])() = {
    func_8005C860,
    func_8005C960,
    func_8005CADC,
};

struct Unk_unk68* D_800FDD38[2] = {
    &D_800FDC80,
    &D_800FDC84,
};

void (*D_800FDD40[7])() = {
    func_8009216C,
    func_8005CAFC,
    func_8005CB08,
    func_8005CC6C,
    func_8005CDB0,
    func_8005CE80,
    func_8005CF60,
};

void (*D_800FDD5C[2])() = {
    func_8005CB54,
    func_8005CB90,
};

void (*D_800FDD64[2])() = {
    func_8005CCA8,
    func_8005CCFC,
};

void (*D_800FDD6C[2])() = {
    func_8005CDEC,
    func_8005CE50,
};

void (*D_800FDD74[2])() = {
    func_8005CEBC,
    func_8005CF30,
};

void (*D_800FDD7C[3])() = {
    func_8005CF9C,
    func_8005D0A0,
    func_8005D0D8,
};

struct Unk_unk68 D_800FDD88 = { -26, -17, 52, 42 };

struct Unk_unk68 D_800FDD8C = { -18, -14, 35, 30 };

u8 D_800FDD90[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00 };

u8 D_800FDD98[8] = {
    0x21,
    0x22,
    0x04,
    0x48,
    0x50,
    0x00,
    0x00,
    0x00,
};

u16 D_800FDDA0[14] = {
    0x1200,
    0x02A0,
    0x1240,
    0x02A0,
    0x1280,
    0x02A0,
    0x12C0,
    0x02A0,
    0x1300,
    0x02A0,
    0x1230,
    0x0240,
    0x12D0,
    0x0240,
};

union AnimationStep D_800FDDBC[] = {
    { 0x17010001 },
    { 0x18010001 },
    { 0x19FE0001 },
};

union AnimationStep D_800FDDC8[] = {
    { 0x1A010005 },
    { 0x1B010004 },
    { 0x1B000101 },
};

union AnimationStep D_800FDDD4[] = {
    { 0x0D010006 },
    { 0x0E010201 },
    { 0x0E010003 },
    { 0x0E000101 },
};

union AnimationStep D_800FDDE4[] = {
    { 0x0F010002 },
    { 0x10FF0002 },
};

union AnimationStep D_800FDDEC[] = {
    { 0x15010002 },
    { 0x16010001 },
    { 0x16000101 },
};

union AnimationStep D_800FDDF8[] = {
    { 0x0E010006 },
    { 0x0D010002 },
    { 0x0C010002 },
    { 0x0B010201 },
    { 0x0B010001 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08010002 },
    { 0x11010004 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x07010004 },
    { 0x07000101 },
};

union AnimationStep D_800FDE5C[] = {
    { 0x00010005 },
    { 0x01010004 },
    { 0x02010004 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x00010003 },
    { 0x01010003 },
    { 0x02F90003 },
};

union AnimationStep D_800FDE88[] = {
    { 0x00010005 },
    { 0x01010005 },
    { 0x02010005 },
    { 0x03010005 },
    { 0x04010005 },
    { 0x05010005 },
    { 0x06010005 },
    { 0x07F90005 },
};

union AnimationStep D_800FDEA8[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FDEAC[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FDEB0[] = {
    { 0x1E000001 },
};

union AnimationStep D_800FDEB4[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FDEB8[] = {
    { 0x20000001 },
};

union AnimationStep D_800FDEBC[] = {
    { 0x21000001 },
};

union AnimationStep D_800FDEC0[] = {
    { 0x22000001 },
};

union AnimationStep D_800FDEC4[] = {
    { 0x23000001 },
};

union AnimationStep D_800FDEC8[] = {
    { 0x24000001 },
};

union AnimationStep D_800FDECC[] = {
    { 0x25000001 },
};

union AnimationStep D_800FDED0[] = {
    { 0x26000001 },
};

union AnimationStep D_800FDED4[] = {
    { 0x27000001 },
};

union AnimationStep D_800FDED8[] = {
    { 0x28000001 },
};

union AnimationStep D_800FDEDC[] = {
    { 0x29000001 },
};

union AnimationStep D_800FDEE0[] = {
    { 0x2A000001 },
};

union AnimationStep* D_800FDEE4[23] = {
    D_800FDDBC,
    D_800FDDC8,
    D_800FDDD4,
    D_800FDDE4,
    D_800FDDEC,
    D_800FDDF8,
    D_800FDE5C,
    D_800FDE88,
    D_800FDEA8,
    D_800FDEAC,
    D_800FDEB0,
    D_800FDEB4,
    D_800FDEB8,
    D_800FDEBC,
    D_800FDEC0,
    D_800FDEC4,
    D_800FDEC8,
    D_800FDECC,
    D_800FDED0,
    D_800FDED4,
    D_800FDED8,
    D_800FDEDC,
    D_800FDEE0,
};

u8 D_800FDF40[12] = { 0x08, 0x09, 0x0D, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x00, 0x00, 0x00 };

u8 D_800FDF4C[8] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x00, 0x00 };
