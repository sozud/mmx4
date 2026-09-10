#include "common.h"
#include "func_tables.h"

void (*D_800FDF64[7])() = {
    func_8009216C,
    func_8005D844,
    func_8005D850,
    func_8005DAB8,
    func_8005DB84,
    func_8005E0CC,
    func_8005E3E8,
};

void (*D_800FDF80[3])() = {
    func_8005D88C,
    func_8005D8B8,
    func_8005D9C4,
};

void (*D_800FDF8C[5])() = {
    func_8005DBC0,
    func_8005DC58,
    func_8005DED4,
    func_8005DF84,
    func_8005E044,
};

void (*D_800FDFA0[3])() = {
    func_8005E108,
    func_8005E1BC,
    func_8005E298,
};

void (*D_800FDFAC[3])() = {
    func_8005E424,
    func_8005E47C,
    func_8005E500,
};

struct Unk_unk68 D_800FDFB8 = { 0, 0, 16, 21 };

u16 D_800FDFBC[4] = { 0x09D0, 0x0E28, 0x14D8, 0x1B48 };

union AnimationStep D_800FDFC4[] = {
    { 0x00000001 },
};

union AnimationStep D_800FDFC8[] = {
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010004 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08F90003 },
};

union AnimationStep D_800FDFE8[] = {
    { 0x09010002 },
    { 0x0A010004 },
    { 0x0B010003 },
    { 0x0C010102 },
    { 0x0D000212 },
};

union AnimationStep D_800FDFFC[] = {
    { 0x0D010006 },
    { 0x0EFF0004 },
};

union AnimationStep D_800FE004[] = {
    { 0x0F010004 },
    { 0x10FF0004 },
};

union AnimationStep D_800FE00C[] = {
    { 0x10000004 },
};

union AnimationStep D_800FE010[] = {
    { 0x11000004 },
};

union AnimationStep D_800FE014[] = {
    { 0x0001000F },
    { 0x1201000E },
    { 0x0001000F },
    { 0x13FD0010 },
};

union AnimationStep D_800FE024[] = {
    { 0x0001000B },
    { 0x1401000A },
    { 0x1501000A },
    { 0x1601000B },
    { 0x1501000A },
    { 0x14FD000A },
};

union AnimationStep D_800FE03C[] = {
    { 0x17010102 },
    { 0x18010003 },
    { 0x19010005 },
    { 0x1A010006 },
    { 0x1B000007 },
};

union AnimationStep D_800FE050[] = {
    { 0x1C010008 },
    { 0x27FF0009 },
};

union AnimationStep D_800FE058[] = {
    { 0x1D01000A },
    { 0x1E010007 },
    { 0x18000006 },
};

union AnimationStep D_800FE064[] = {
    { 0x1F010006 },
    { 0x2000000A },
};

union AnimationStep D_800FE06C[] = {
    { 0x2001000A },
    { 0x1F000006 },
};

union AnimationStep D_800FE074[] = {
    { 0x21010014 },
    { 0x22010310 },
    { 0x22000010 },
};

union AnimationStep D_800FE080[] = {
    { 0x23010014 },
    { 0x24010310 },
    { 0x24000010 },
};

union AnimationStep D_800FE08C[] = {
    { 0x25010014 },
    { 0x26010310 },
    { 0x26000010 },
};

union AnimationStep D_800FE098[] = {
    { 0x28010002 },
    { 0x29010003 },
    { 0x2AFF0005 },
};

union AnimationStep D_800FE0A4[] = {
    { 0x2B010004 },
    { 0x2C010005 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010005 },
    { 0x30000004 },
};

union AnimationStep D_800FE0BC[] = {
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x3AFD0002 },
};

union AnimationStep D_800FE0CC[] = {
    { 0x34000002 },
};

union AnimationStep D_800FE0D0[] = {
    { 0x35000002 },
};

union AnimationStep D_800FE0D4[] = {
    { 0x36000002 },
};

union AnimationStep D_800FE0D8[] = {
    { 0x37000002 },
};

union AnimationStep D_800FE0DC[] = {
    { 0x38000002 },
};

union AnimationStep D_800FE0E0[] = {
    { 0x39000002 },
};

union AnimationStep D_800FE0E4[] = {
    { 0x09010008 },
    { 0x0A010005 },
    { 0x0B010004 },
    { 0x0C010003 },
    { 0x0D010112 },
    { 0x0D000003 },
};

union AnimationStep* D_800FE0FC[27] = {
    D_800FDFC4,
    D_800FDFC8,
    D_800FDFE8,
    D_800FDFFC,
    D_800FE004,
    D_800FE00C,
    D_800FE010,
    D_800FE014,
    D_800FE024,
    D_800FE050,
    D_800FE064,
    D_800FE06C,
    D_800FE074,
    D_800FE080,
    D_800FE08C,
    D_800FE098,
    D_800FE0BC,
    D_800FE0CC,
    D_800FE0D0,
    D_800FE0D4,
    D_800FE0D8,
    D_800FE0DC,
    D_800FE0E0,
    D_800FE058,
    D_800FE0A4,
    D_800FE03C,
    D_800FE0E4,
};

void (*D_800FE168[3])() = {
    func_8005E5C0,
    func_8005E754,
    func_8005E7CC,
};

void (*D_800FE174[6])() = {
    func_8005E7EC,
    func_8005E860,
    func_8005E8B4,
    func_8005EB40,
    func_8005EBF4,
    func_8005EC38,
};

u16 D_800FE18C[8] = {
    0x0A48,
    0x0140,
    0x0EA8,
    0x0170,
    0x1528,
    0x014A,
    0x1BC8,
    0x0170,
};

void (*D_800FE19C[5])() = {
    func_8005E8F0,
    func_8005E9C0,
    func_8005EA18,
    func_8005EA78,
    func_8005EAF8,
};

struct Unk_unk68 D_800FE1B0 = { -16, -15, 29, 28 };

struct Unk_unk68 D_800FE1B4 = { -12, -11, 22, 20 };

struct Unk_unk68 D_800FE1B8 = { 0, 0, 14, 13 };

struct Unk_unk68 D_800FE1BC = { -16, -2, 29, 15 };

struct Unk_unk68 D_800FE1C0 = { -13, 0, 23, 11 };

union AnimationStep D_800FE1C4[] = {
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x00FB0001 },
};

union AnimationStep D_800FE1DC[] = {
    { 0x00010006 },
    { 0x06010005 },
    { 0x07010004 },
    { 0x08010203 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0E010003 },
    { 0x0D010004 },
    { 0x0C010005 },
    { 0x0E000101 },
};

union AnimationStep D_800FE20C[] = {
    { 0x0E010001 },
    { 0x14010002 },
    { 0x15010003 },
    { 0x1B010004 },
    { 0x15010003 },
    { 0x14010002 },
    { 0x0E01000E },
    { 0x0F010003 },
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010102 },
};

union AnimationStep D_800FE254[] = {
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13FB0001 },
};

union AnimationStep D_800FE26C[] = {
    { 0x16000101 },
};

union AnimationStep D_800FE270[] = {
    { 0x17000101 },
};

union AnimationStep D_800FE274[] = {
    { 0x18000101 },
};

union AnimationStep D_800FE278[] = {
    { 0x19000101 },
};

union AnimationStep D_800FE27C[] = {
    { 0x1A000101 },
};

union AnimationStep* D_800FE280[9] = {
    D_800FE1C4,
    D_800FE1DC,
    D_800FE20C,
    D_800FE254,
    D_800FE26C,
    D_800FE270,
    D_800FE274,
    D_800FE278,
    D_800FE27C,
};

u8 D_800FE2A4[8] = { 4, 5, 6, 7, 8, 0, 0, 0 };

void (*D_800FE2AC[3])() = {
    func_8005ECA8,
    func_8005EE2C,
    func_8005EF40,
};

void (*D_800FE2B8[7])() = {
    func_8009216C,
    func_8005EF6C,
    func_8005EF78,
    func_8005EFB0,
    func_8005F0F4,
    func_8005F124,
    func_8005F3D4,
};

void (*D_800FE2D4[4])() = {
    func_8005F160,
    func_8005F1A4,
    func_8005F230,
    func_8005F2F4,
};

struct Unk_unk68 D_800FE2E4 = { -20, -20, 38, 38 };

struct Unk_unk68 D_800FE2E8 = { -14, -14, 28, 28 };

union AnimationStep D_800FE2EC[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07F90002 },
};

union AnimationStep D_800FE30C[] = {
    { 0x00010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1AED0002 },
};

union AnimationStep D_800FE35C[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x11010002 },
    { 0x10010002 },
    { 0x0F010002 },
    { 0x0E010002 },
    { 0x0D010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08ED0002 },
};

union AnimationStep D_800FE3AC[] = {
    { 0x00010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F000102 },
};

union AnimationStep D_800FE3C4[] = {
    { 0x20010002 },
    { 0x24010002 },
    { 0x23010002 },
    { 0x25010002 },
    { 0x21010002 },
    { 0x26010002 },
    { 0x22010002 },
    { 0x27F90002 },
};

union AnimationStep D_800FE3E4[] = {
    { 0x28010002 },
    { 0x3D010002 },
    { 0x24010002 },
    { 0x3D010002 },
    { 0x28010002 },
    { 0x3D010002 },
    { 0x25010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x36010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x37010002 },
    { 0x3DF10002 },
};

union AnimationStep D_800FE424[] = {
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010002 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D000102 },
};

union AnimationStep* D_800FE48C[7] = {
    D_800FE2EC,
    D_800FE30C,
    D_800FE35C,
    D_800FE3AC,
    D_800FE3C4,
    D_800FE3E4,
    D_800FE424,
};

void (*D_800FE4A8[3])() = {
    func_8005F558,
    func_8005F758,
    func_8005F844,
};

void (*D_800FE4B4[4])() = {
    func_8009216C,
    func_8005F864,
    func_8005F87C,
    func_8005F9A4,
};

void (*D_800FE4C4[4])() = {
    func_8005F9F4,
    func_8005FB38,
    func_8005FBBC,
    func_8005FCAC,
};

struct Unk_unk68 D_800FE4D4 = { -19, -18, 37, 28 };

struct Unk_unk68 D_800FE4D8 = { -14, -12, 26, 17 };

struct Unk_unk68 D_800FE4DC = { -23, -14, 37, 31 };

struct Unk_unk68 D_800FE4E0 = { -18, -13, 22, 27 };

struct Unk_unk68 D_800FE4E4 = { 0, 0, 23, 20 };

union AnimationStep D_800FE4E8[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08FE0002 },
};

union AnimationStep D_800FE4F4[] = {
    { 0x20010002 },
    { 0x21010002 },
    { 0x22FE0002 },
};

union AnimationStep D_800FE500[] = {
    { 0x09010009 },
    { 0x0A010009 },
    { 0x0A000101 },
};

union AnimationStep D_800FE50C[] = {
    { 0x20010004 },
    { 0x20000101 },
};

union AnimationStep D_800FE514[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep D_800FE520[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};

union AnimationStep D_800FE538[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1E010002 },
    { 0x1E010101 },
};

union AnimationStep D_800FE5EC[] = {
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1EF90003 },
};

union AnimationStep D_800FE60C[] = {
    { 0x23000101 },
};

union AnimationStep D_800FE610[] = {
    { 0x24000101 },
};

union AnimationStep D_800FE614[] = {
    { 0x25000101 },
};

union AnimationStep D_800FE618[] = {
    { 0x26000101 },
};

union AnimationStep D_800FE61C[] = {
    { 0x27000101 },
};

union AnimationStep D_800FE620[] = {
    { 0x28000101 },
};

union AnimationStep D_800FE624[] = {
    { 0x29000101 },
};

union AnimationStep D_800FE628[] = {
    { 0x2A000101 },
};

union AnimationStep D_800FE62C[] = {
    { 0x2B000101 },
};

union AnimationStep D_800FE630[] = {
    { 0x2C000101 },
};

union AnimationStep D_800FE634[] = {
    { 0x2D000101 },
};

union AnimationStep D_800FE638[] = {
    { 0x2E000101 },
};

union AnimationStep D_800FE63C[] = {
    { 0x2F000101 },
};

union AnimationStep D_800FE640[] = {
    { 0x30000101 },
};

union AnimationStep D_800FE644[] = {
    { 0x31000101 },
};

union AnimationStep D_800FE648[] = {
    { 0x32000101 },
};

union AnimationStep D_800FE64C[] = {
    { 0x33000101 },
};

union AnimationStep D_800FE650[] = {
    { 0x34000101 },
};

union AnimationStep D_800FE654[] = {
    { 0x35000101 },
};

union AnimationStep D_800FE658[] = {
    { 0x36000101 },
};

union AnimationStep* D_800FE65C[28] = {
    D_800FE4E8,
    D_800FE4F4,
    D_800FE500,
    D_800FE50C,
    D_800FE514,
    D_800FE520,
    D_800FE538,
    D_800FE5EC,
    D_800FE60C,
    D_800FE610,
    D_800FE614,
    D_800FE618,
    D_800FE61C,
    D_800FE620,
    D_800FE624,
    D_800FE628,
    D_800FE62C,
    D_800FE630,
    D_800FE634,
    D_800FE638,
    D_800FE63C,
    D_800FE640,
    D_800FE644,
    D_800FE648,
    D_800FE64C,
    D_800FE650,
    D_800FE654,
    D_800FE658,
};

u8 D_800FE6CC[12] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0 };

u8 D_800FE6D8[12] = { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 0, 0 };

void (*D_800FE6E4[3])() = {
    func_8005FE1C,
    func_80060144,
    func_80060228,
};

void (*D_800FE6F0[5])() = {
    func_8009216C,
    func_8006025C,
    func_80060268,
    func_800603A0,
    func_80060538,
};

void (*D_800FE704[2])() = {
    func_800602A4,
    func_80060354,
};

void (*D_800FE70C[3])() = {
    func_800603DC,
    func_800604A0,
    func_800604EC,
};

void (*D_800FE718[7])() = {
    func_80060574,
    func_800606D8,
    func_80060870,
    func_800608CC,
    func_8006097C,
    func_800609C4,
    func_80060A10,
};

struct Unk_unk68 D_800FE734 = { -54, -9, 90, 25 };

struct Unk_unk68 D_800FE738 = { -52, -11, 86, 25 };

struct Unk_unk68 D_800FE73C = { -10, 8, 45, 11 };

union AnimationStep D_800FE740[] = {
    { 0x00000001 },
};

union AnimationStep D_800FE744[] = {
    { 0x00010001 },
    { 0x01010006 },
    { 0x02010005 },
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07FD0004 },
};

union AnimationStep D_800FE764[] = {
    { 0x0C010002 },
    { 0x0DFF0002 },
};

union AnimationStep D_800FE76C[] = {
    { 0x0F01000A },
    { 0x10010008 },
    { 0x11010004 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15FD0001 },
};

union AnimationStep D_800FE788[] = {
    { 0x1601000A },
    { 0x17010008 },
    { 0x18010004 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1CFD0001 },
};

union AnimationStep D_800FE7A4[] = {
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010002 },
    { 0x20010003 },
    { 0x21010004 },
    { 0x22000005 },
};

union AnimationStep D_800FE7DC[] = {
    { 0x22010005 },
    { 0x23010005 },
    { 0x2401000A },
    { 0x25010005 },
    { 0x2601000A },
    { 0x27000005 },
};

union AnimationStep D_800FE7F4[] = {
    { 0x28000001 },
};

union AnimationStep D_800FE7F8[] = {
    { 0x29000001 },
};

union AnimationStep D_800FE7FC[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FE800[] = {
    { 0x2B000001 },
};

union AnimationStep D_800FE804[] = {
    { 0x14010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x11010004 },
    { 0x10010008 },
    { 0x0F00000A },
};

union AnimationStep D_800FE81C[] = {
    { 0x1B010001 },
    { 0x1A010001 },
    { 0x19010001 },
    { 0x18010004 },
    { 0x17010008 },
    { 0x1600000A },
};

union AnimationStep D_800FE834[] = {
    { 0x2C000001 },
};

union AnimationStep D_800FE838[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FE83C[] = {
    { 0x2E000001 },
};

union AnimationStep D_800FE840[] = {
    { 0x2F000001 },
};

union AnimationStep D_800FE844[] = {
    { 0x30000001 },
};

union AnimationStep D_800FE848[] = {
    { 0x31000001 },
};

union AnimationStep D_800FE84C[] = {
    { 0x08010003 },
    { 0x09010004 },
    { 0x0A010005 },
    { 0x09010004 },
    { 0x08FC0003 },
};

union AnimationStep D_800FE860[] = {
    { 0x37010003 },
    { 0x0B010003 },
    { 0x37010003 },
    { 0x32010003 },
    { 0x37010003 },
    { 0x33010003 },
    { 0x37010003 },
    { 0x34010003 },
    { 0x37010003 },
    { 0x35010003 },
    { 0x37010003 },
    { 0x36F60003 },
};

union AnimationStep* D_800FE890[21] = {
    D_800FE740,
    D_800FE744,
    D_800FE764,
    D_800FE76C,
    D_800FE788,
    D_800FE7A4,
    D_800FE7DC,
    D_800FE7F4,
    D_800FE7F8,
    D_800FE7FC,
    D_800FE800,
    D_800FE804,
    D_800FE81C,
    D_800FE834,
    D_800FE838,
    D_800FE83C,
    D_800FE840,
    D_800FE844,
    D_800FE848,
    D_800FE84C,
    D_800FE860,
};

u8 D_800FE8E4[8] = { 13, 14, 15, 16, 17, 18, 0, 0 };
