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