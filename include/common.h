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

#include "psy-q-4.0/SYS/TYPES.H"
#include "psy-q-4.0/LIBGTE.H"
#include "psy-q-4.0/LIBGPU.H"

struct Unk {
    u8 pad0[2];
    s8 unk2;
    s8 unk3;
    s8 unk4;
    u8 unk5;
    s8 unk6;
    u8 pad5[3];
    s16 unkA;
    s16 padc;
    s16 unkE;
    u8 pad6[0x10];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x10];
    u16 unk40;
    u16 unk42;
    u8 pad2f[0x23];
    s8 unk67;
    u8 pad68[0x23];
    u16 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Unk2 {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad2[1];
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
    u8 pad5[4];
    s16 unkA;
    s16 padc;
    s16 unkE;
    u8 pad6[0x19];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x3];
    u16 unk40;
    u16 unk42;
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

struct Unk16 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18[0x70 - 0x18];
    s32 unk70;
    u8 unk74[0x9C - 0x74];
    u32 unk9C;
};

extern struct Unk16 D_80141BD8;
extern struct Unk16 D_80166C10[];

struct Unk17 {
    u8 pad0[0xA];
    u16 unkA;
    u16 : 16;
    u16 unkE;
    u8 pad[68];
}; /* size 0x54 */

extern struct Unk17 D_801419B0[];

struct DrawInfo {
    DISPENV dispenv;
    DRAWENV drawenv; // 0x14
    u32 unk70; // 0x70
    u8 pad[0x28];
    u32 unk9C; //  0x9c
};

struct Unk8001FB50 {
    s8 unk0;
    s8 unk1;
    u8 pad1[0x1b];
    s8 unk1D;
    s8 unk1E;
    u8 pad[0x25];
    s8 unk44;
    u8 pad45;
    s8 unk46;
};

struct Unk18 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    s8 unk8;
};

struct Unk19 {
    u8 pad[0x7];
    s32 unk8;
    s32 unkC;
    u8 pad6[0x7];
    s8 unk17;
    s8 pad2[0x6];
    s32 unk20;
    s32 unk24;
    u8 pad345[5];
    u32* unk30;
    u32* unk34;
    s8 pad3[0xc];
    u32 unk44;
    u8 unk48;
};

struct Unk20 {
    u8 unk0;
    u8 unk1;
};

struct Unk21 {
    u8 pad[4];
    u8 unk4;
    u8 unk5;
    u8 pad2[0xe];
    u8 unk14;
    u8 unk15;
    u8 unk16;
};

struct Unk800F2294 {
    u8 pad;
    u8 unk1;
    u8 pad2[2];
    s16 unk4;
    u8 pad3[3];
    u16 unkA;
};

struct Unk80139690 {
    u8 pad;
    s8 unk1;
};

struct Unk800F24A4 {
    u8 pad0[4];
    s8 unk4;
};

struct Unk800F285C {
    u8 pad0[4];
    s8 unk4;
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
extern struct DrawInfo* D_80142F80;
extern struct Unk8001FB50 D_801721C0;
extern void (*D_800F23E8[1])(void*);
extern s8 D_80171EA8;
extern void (*D_800F44A8[1])();
extern void (*D_800F48A4[1])(struct Unk8001FB50* arg0);
extern void (*D_800F241C[1])(void);
extern u8 D_800F32D4[1][1];
extern s8 D_801721CC;
extern s8 D_801721CD;
extern s32 D_800EE458;
extern s32 D_8012F490;
extern s8 D_80173C6C;
extern s8 D_80173C6D;
extern s8 D_80173C6E;
extern s8 D_80173C6F;
extern s32 D_801395E4;
extern s32 D_801395E8;
extern volatile s32 D_80139634;
extern struct Unk80139690* D_80139690;
extern u8 D_8013E470;
extern void (*D_800F43A8[1])(s32);
extern void (*D_800F4498[1])(void);
extern void (*D_800FB0F4[1])();
extern void (*D_8010B34C[1])();
extern void (*D_8010B4C4[1])();
extern void (*D_8010BEC8[1])();
extern s16* D_801F8300;
extern u16 D_801419BA;
extern u16 D_801419BE;
extern void (*D_8010E6F0[1])();
extern void (*D_8010E578[1])();
extern void (*D_8010E6FC[1])();
extern void (*D_8010E824[1])();
extern void (*D_8010EB84[1])();
extern void (*D_8010EBF4[1])();

#include "func_tables.h"

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
void func_8001FBB8(struct Unk8001FB50* arg0);
void func_800299EC(struct Unk8001FB50* arg0);
void func_8001FBD4(struct Unk8001FB50* arg0);
void func_8002FC38(struct Unk8001FB50* arg0);
void func_8001FBE0(struct Unk8001FB50* arg0);
void func_8001FC20(struct Unk8001FB50* arg0);
void func_8001FF50(struct Unk8001FB50* arg0);
void func_8001FAFC(struct Unk8001FB50* arg0);
void func_80020AC8(struct Unk8001FB50* arg0);
void func_80020D98(struct Unk8001FB50* arg0);
void func_80020464(struct Unk8001FB50* arg0);
void func_80023A54(struct Unk8001FB50* arg0);
void func_800204AC(struct Unk8001FB50* arg0);
void func_80013014();
void func_80021858();
void func_80023D68();
void func_8002A484();
void func_8002B460();
void func_8002166C();
void func_80021858();
void func_80021A20();
void func_80023D68();
void func_8002A484();
void func_8002B460();
void func_800B6C9C(s32 arg0);
void func_800B6D1C(s32, s8, s32);
void func_800B6EB4(s16, s16, s16, s16, s32);
s8 func_800B6FF4(s32, s8);
void func_8002B13C(struct Unk18* arg0);
void func_80023DB8();
void func_80026648();

// D_800F2294 table
void func_8001DCCC(struct Unk800F2294* arg0);
void func_8001E690(struct Unk800F2294* arg0);
void func_8001DDB0(struct Unk800F2294* arg0);
void func_8001DE20(struct Unk800F2294* arg0);
void func_8001DE54(struct Unk800F2294* arg0);
void func_8001DF48(struct Unk800F2294* arg0);
void func_8001DF7C(struct Unk800F2294* arg0);
void func_8001E000(struct Unk800F2294* arg0);
void func_8001E130(struct Unk800F2294* arg0);
void func_8001E3FC(struct Unk800F2294* arg0);
void func_8001E458(struct Unk800F2294* arg0);
void func_8001E4F0(struct Unk800F2294* arg0);
void func_8001E54C(struct Unk800F2294* arg0);
void func_8001E638(struct Unk800F2294* arg0);
void func_8001E6BC(struct Unk800F2294* arg0);

s32 func_800E5FF4(s32, s32, u8*);
void func_800AE6B4(s32*);
void func_80027FA8();
