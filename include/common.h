#define INCLUDE_ASM(FOLDER, NAME)                                              \
    __asm__(".pushsection .text\n"                                             \
            "\t.align\t2\n"                                                    \
            "\t.globl\t" #NAME "\n"                                            \
            "\t.ent\t" #NAME "\n" #NAME ":\n"                                  \
            ".include \"" FOLDER "/" #NAME ".s\"\n"                            \
            "\t.set reorder\n"                                                 \
            "\t.set at\n"                                                      \
            "\t.end\t" #NAME "\n"                                              \
            ".popsection");

__asm__(".include \"macro.inc\"\n");

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Unk
{
    u8 pad[5];
    u8 unk5;
    u8 pad6[0x86];
    u16 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Unk2
{
    u8 pad0;
    u8 unk1;
    u8 pad2[2];
    s16 unk4;
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

extern s8 D_801721CF;
extern s8 D_80141BDC;
extern struct Unk5 D_800F0E18[];
extern s32 D_80137CC0;

s32 func_80034E2C();
s32 func_80034F7C();
void func_800129F0(s32);
void func_800127C8(s32); 
void func_800129F0(s32);
void func_80013404(s32); 
s32 func_8001540C(s32, s32, struct Unk6*);
s32 func_800350A4(struct Unk6*, s32);
