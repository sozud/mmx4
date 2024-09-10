#define INCLUDE_ASM(FOLDER, NAME)                   \
    __asm__(".pushsection .text\n"                  \
            "\t.align\t2\n"                         \
            "\t.globl\t" #NAME "\n"                 \
            "\t.ent\t" #NAME "\n" #NAME ":\n"       \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            "\t.set reorder\n"                      \
            "\t.set at\n"                           \
            "\t.end\t" #NAME "\n"                   \
            ".popsection");

__asm__(".include \"macro.inc\"\n");

#define NULL ((void*)0)

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Unk {
    u8 pad[5];
    u8 unk5;
    u8 pad6[0x86];
    u16 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Unk2 {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    s16 unk4;
    u8 pad5[6];
    u8 unkC;
    u8 unkD;
};

struct Unk3 {
    u8 pad[0xc0];
    s8 unkC0;
};

struct Unk5 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Unk6 {
    u8 pad0[5];
    u8 unk5;
    u8 pad6[0x19];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad2f[0x37];
    s8 unk67;
};

struct Unk7 {
    u8 pad[0x80];
    u16 unk80;
};

struct Unk9 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    u32 unk8;
    u32 unkC;
    u8 padd[1];
    u32 unk14;
    u32 unk18;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    u8 pad33[19];
    s8 unk47;
    s8 unk48;
    s8 unk49;
};

struct Unk10 {
    u8 pad[0x2A];
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 pad2[8];
}; /* size 0x35 */

struct Unk11 {
    u8 unk00;
    u8 unk01;
    s8 unk02;
    u8 padding03[3];
    u8 unk06;
    u8 padding07[13];
    u8 unk14;
    u8 padding15[11];
    u32 unk20;
    s32 unk24;
    u32 unk28;
    u8 padding2C[59];
    s8 unk67;
    u8 padding68[33];
    u8 unk89;
};

struct Unk12 {
    u8 pad0[2];
    s8 unk2;
    u8 pad3[0xc0];
    s8 unkC3;
};

struct Unk15 {
    u8 pad[5];
    u8 unk5;
    u8 pad10[0x79];
    u16 unk80;
    u16 unk82;
    u8 pad82[3];
    u8 unk87;
    s8 unk88;
    u8 pad5[0x3a];
    s8 unkC3;
};

extern u8 D_800F8B30[];
extern s8 D_801721CF;
extern s8 D_80141BDC;
extern struct Unk5 D_800F0E18[];
extern s32 D_80137CC0;
extern s8 D_801419B3;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern s8 D_80141BDC;

s32 func_80034E2C();
s32 func_80034F7C();
void func_800129F0(s32);
void func_800127C8(s32);
void func_80013404(s32);
s32 func_8001540C(s32, s32, struct Unk6*);
s32 func_800350A4(struct Unk6*, s32);
s32 func_80033694();
void func_80034538(struct Unk7*);
void func_80034754(struct Unk7*);
void func_80027A5C(struct Unk9*, s32);
void func_80027AAC(struct Unk9*);
void func_80027AFC(struct Unk9*);
void func_80027B70(struct Unk9*);
void func_80027BE4(struct Unk9*);
s32 func_80039C34(struct Unk12*);
s32 func_80039E5C(struct Unk12*);
s32 func_80039F28(struct Unk12*);
void func_80012EB8();
void func_8001D134();
void func_8002A7D0();