#include "common.h"
#include "func_tables.h"

void (*D_800FCFB4[])() = {
    func_8009216C,
    func_80056BD0,
    func_80056BDC,
    func_800570A4,
};

void (*D_800FCFC4[])() = {
    func_80056C18,
    func_80056D20,
    func_80056DB4,
    func_80056EF4,
};

struct Unk_unk68 D_800FCFD4[] = {
    { -3, -5, 0x29, 8 },
};

struct Unk_unk68 D_800FCFD8[] = {
    { -2, -24, 0xC, 0x1C },
};

struct Unk_unk68 D_800FCFDC[] = {
    { -16, -16, 0x13, 0x14 },
};

struct Unk_unk68 D_800FCFE0[] = {
    { -23, -6, 0x12, 0xA },
};

struct Unk_unk68 D_800FCFE4[] = {
    { -6, -28, 0xC, 0x37 },
};

struct Unk_unk68 D_800FCFE8[] = {
    { -10, -5, 0xF, 0x15 },
};

struct Unk_unk68 D_800FCFEC[] = {
    { 8, -20, 0xE, 0x13 },
};

struct Unk_unk68 D_800FCFF0[] = {
    { -2, -19, 0x13, 0x15 },
};

struct Unk_unk68 D_800FCFF4[] = {
    { 0, -2, 0x24, 5 },
};

struct Unk_unk68 D_800FCFF8[] = {
    { -1, -21, 9, 0x18 },
};

struct Unk_unk68 D_800FCFFC[] = {
    { -12, -13, 0xE, 0x10 },
};

struct Unk_unk68 D_800FD000[] = {
    { -20, -4, 0x11, 7 },
};

struct Unk_unk68 D_800FD004[] = {
    { -4, -26, 8, 0x33 },
};

struct Unk_unk68 D_800FD008[] = {
    { -8, -3, 0xD, 0x13 },
};

struct Unk_unk68 D_800FD00C[] = {
    { 9, -18, 0xB, 0x10 },
};

struct Unk_unk68 D_800FD010[] = {
    { 0, -16, 0xF, 0x11 },
};

struct Unk_unk68 D_800FD014[] = {
    { 0, -4, 0xD, 8 },
};

struct Unk_unk68* D_800FD018[] = {
    D_800FCFD4,
    D_800FCFD8,
    D_800FCFD4,
    D_800FCFDC,
    D_800FCFE4,
    D_800FCFE4,
    D_800FCFE8,
    D_800FCFEC,
    D_800FCFD4,
    D_800FCFF0,
    D_800FCFD4,
    D_800FCFE0,
};

struct Unk_unk68* D_800FD048[] = {
    D_800FCFF4,
};

struct Unk_unk68* D_800FD04C[] = {
    D_800FCFF8,
    D_800FCFF4,
    D_800FCFFC,
    D_800FD004,
    D_800FD004,
    D_800FD008,
    D_800FD00C,
    D_800FCFF4,
    D_800FD010,
    D_800FCFF4,
    D_800FD000,
};

union AnimationStep D_800FD078[] = {
    { 0x0001000C },
    { 0x0101020C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x04FC010C },
};

union AnimationStep D_800FD08C[] = {
    { 0x00010006 },
    { 0x01010206 },
    { 0x02010006 },
    { 0x03010006 },
    { 0x04FC0106 },
};

union AnimationStep D_800FD0A0[] = {
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010002 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010009 },
    { 0x05000101 },
};

union AnimationStep D_800FD0C0[] = {
    { 0x05010002 },
    { 0x09010201 },
    { 0x09010005 },
    { 0x0A010003 },
    { 0x0A000101 },
};

union AnimationStep D_800FD0D4[] = {
    { 0x0B010006 },
    { 0x0CFF0106 },
};

union AnimationStep D_800FD0DC[] = {
    { 0x0D010201 },
    { 0x0D010003 },
    { 0x0E010301 },
    { 0x0E010004 },
    { 0x0F010401 },
    { 0x0F010504 },
    { 0x10010601 },
    { 0x10010004 },
    { 0x11010007 },
    { 0x11000101 },
};

union AnimationStep D_800FD104[] = {
    { 0x12000101 },
};

union AnimationStep D_800FD108[] = {
    { 0x13000101 },
};

union AnimationStep D_800FD10C[] = {
    { 0x14000101 },
};

union AnimationStep D_800FD110[] = {
    { 0x15000101 },
};

union AnimationStep* D_800FD114[] = {
    D_800FD078,
    D_800FD08C,
    D_800FD0A0,
    D_800FD0C0,
    D_800FD0D4,
    D_800FD0DC,
    D_800FD104,
    D_800FD108,
    D_800FD10C,
    D_800FD110,
};

u8 D_800FD13C[] = {
    0x06,
    0x07,
    0x08,
    0x09,
};

void (*D_800FD140[])() = {
    func_80057160,
    func_80057308,
    func_80057488,
};

void (*D_800FD14C[])() = {
    func_8009216C,
    func_800574B4,
    func_800574C0,
    func_800577E8,
    func_80057A44,
    func_80057D58,
    func_80058044,
};

void (*D_800FD168[])() = {
    func_800574FC,
    func_8005754C,
    func_800576F4,
};

void (*D_800FD174[])() = {
    func_80057824,
    func_80057874,
    func_80057978,
};

void (*D_800FD180[])() = {
    func_80057A80,
    func_80057AE8,
    func_80057C00,
};

void (*D_800FD18C[])() = {
    func_80057D94,
    func_80057DDC,
    func_80057E34,
    func_80057F34,
};

struct Unk_unk68 D_800FD19C[] = {
    { -16, -16, 0x30, 0x30 },
};

union AnimationStep D_800FD1A0[] = {
    { 0x00000001 },
};

union AnimationStep D_800FD1A4[] = {
    { 0x01000001 },
};

union AnimationStep D_800FD1A8[] = {
    { 0x02000001 },
};

union AnimationStep D_800FD1AC[] = {
    { 0x03000001 },
};

union AnimationStep D_800FD1B0[] = {
    { 0x04000001 },
};

union AnimationStep D_800FD1B4[] = {
    { 0x05000001 },
};

union AnimationStep* D_800FD1B8[] = {
    D_800FD1A0,
    D_800FD1A4,
    D_800FD1A8,
    D_800FD1AC,
    D_800FD1B0,
    D_800FD1B4,
};

u8 D_800FD1D0[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
};
