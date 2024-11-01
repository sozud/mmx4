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
#define FIXED(x) ((s32)((x)*0x10000))
#define COUNT(x) (sizeof(x) / sizeof(x[0]))

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
#include "psy-q-4.0/LIBSND.H"
#include "psy-q-4.0/LIBETC.H"
#include "psy-q-4.0/KERNEL.H"
#include "psy-q-4.0/LIBCD.H"
#include "psy-q-4.0/LIBPRESS.H"

#include "scratchpad.h"

typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} f32;

struct BaseObj {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 on_screen; // 0x03
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos; // 0x8 and 0xA
    f32 y_pos; // 0xC and 0xE
    s32 unk10;
    s8 bg_offset;
    u8 unk15;
    u8 unk16;
    u8 unk17;
};

struct Unk {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s16 animation_speed;
    u8 pad39[5];
    u16 unk40;
    u16 unk42;
    s8 pad43[9];
    s32 unk50;
    s32 unk54;
    s8 pad55[4];
    s8 unk5C;
    s8 unk5D;
    u8 pad2f[3];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s16 : 16;
    s16 unk6E;
    u8 unk70;
    s8 : 8;
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 unk79;
    s8 unk7A;
    u8 pad68[0x10];
    u16 unk8C;
    u32 unk90;
    u32 unk94;
    u32 pad98;
}; // size 0x9c

struct BackgroundObj {
    u8 pad[2];
    s8 unk2;
    s8 unk3;
    s8 unk4;
    u8 pad4[3];
    f32 x_pos;
    f32 y_pos;
    u8 pad10[4];
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    u8 pad32[10];
    u16 unk40;
    u16 unk42;
    s8 unk44;
    u8 pad42[2];
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 pad49[2];
    u8 unk4C;
    s8 unk4D;
    s8 unk4E;
    s8 : 8;
    s8 pad50[4];
}; // size 0x54

// similar to Unk
struct PlayerObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s16 animation_speed;
    u8 pad39[5];
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    u8 unk47;
    s8 pad48[0x4A - 0x48];
    s8 unk4A;
    s8 pad4B[0x50 - 0x4B];
    s32 unk50;
    s32 unk54;
    s8 pad55[4];
    s8 unk5C;
    s8 unk5D;
    u8 pad2f[3];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s16 : 16;
    s16 unk6E;
    u8 unk70;
    s8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 unk79;
    s8 unk7A;
    u32 unk7C;
    u16 unk80;
    u16 unk82;
    s8 unk84;
    s8 : 8;
    s8 unk86;
    u8 unk87;
    s8 unk88;
    u8 unk89;
    s8 : 8;
    s8 : 8;
    s8 unk8C;
    s8 : 8;
    s8 unk8E;
    s8 unk8F;
    s8 unk90;
    u8 unk91;
    u8 unk92;
    s8 unk93;
    u8 unk94;
    s8 unk95;
    s8 unk96;
    s8 unk97;
    u8 pad98[0x9B - 0x98];
    s8 unk9B;
    s8 unk9C;
    u8 unk9D;
    u8 unk9E;
    s8 unk9F;
    s8 unkA0;
    s8 unkA1;
    s8 unkA2;
    s8 : 8;
    s8 unkA4;
    s8 : 8;
    s8 unkA6;
    s8 unkA7;
    s8 unkA8;
    u8 padA9[0xB8 - 0xA9];
    u8 unkB8;
    s8 unkB9;
    s8 unkBA;
    s8 unkBB;
    s8 unkBC;
    s8 : 8;
    s8 unkBE;
    s8 unkBF;
    s8 unkC0;
    s8 unkC1;
    s8 unkC2;
    s8 unkC3;
    s8 unkC4;
    s8 unkC5;
    s8 padC6[0xC8 - 0xC6];
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s8 unkD4;
    s8 padD5[0xD7 - 0xD5];
    s8 unkD7;
    s8 : 8;
    s8 unkD9;
    s8 padDA[0xDE - 0xDA];
    s8 unkDE;
    s8 : 8;
    s8 unkE0;
    s8 unkE1;
    s8 padE2[0xE4 - 0xE2];
}; // size 0xE4

struct Unk_unk68 {
    s8 unk0;
    s8 unk1;
    u8 unk2;
    u8 unk3;
};

struct VisualObj {
    struct BaseObj base;
    s8 pad18[0x50 - 0x18];
    s32 unk50;
    s32 unk54;
    u8 pa5A[0x70 - 0x5A];
}; // size 0x70

struct ShotObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s8 pad20[0x42 - 0x20];
    u16 unk42;
    s8 pad44[0x50 - 0x44];
    s32 unk50;
    s32 unk54;
    s32 : 32;
    s8 unk5C;
    s8 pad5D[0x61 - 0x5D];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 : 8;
    struct WeaponObj* unk7C; // might be something else
    s32 : 32;
    s32 unk84;
    s32 : 32;
    s8 unk8C;
    s8 pad8D[0x98 - 0x8D];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

struct WeaponObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s8 pad20[0x42 - 0x20];
    u16 unk42;
    s8 pad44[0x50 - 0x44];
    s32 unk50;
    s32 unk54;
    s8 pad58[0x61 - 0x58];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B[0x8C - 0x7B];
    s8 unk8C;
    s8 pad8D[0x94 - 0x8D];
    u8 unk94;
    s8 pad95[0x98 - 0x95];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

struct UnkObj {
    s8 active;
    s8 id;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos; // 0x8 and 0xA
    f32 y_pos; // 0xC and 0xE
    u8 pad10[0x4];
    s8 unk14;
    u8 unk15;
    u8 unk16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s8** unk30;
    s32 : 32;
    s16 unk38;
    s16 : 16;
    s32 unk3C;
    u16 unk40;
    u16 unk42;
    s8 pad44[0x47 - 0x44];
    s8 unk47;
    s8 pad48[0x50 - 0x48];
    u8* unk50;
    u8 unk54;
    u8 pad55[0x60 - 0x55];
}; // size 0x60

struct ItemObj {
    struct BaseObj base;
    f32 unk18;
    f32 unk1C;
    s8 pad20[0x50 - 0x20];
    s32 unk50;
    s32 unk54;
    s8 pad58[0x61 - 0x58];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B[0x8C - 0x7B];
}; // size 0x8C

struct LayerObj {
    struct BaseObj base;
    f32 unk18;
    f32 unk1C;
    s8 pad20[0x30 - 0x20];
}; // size 0x30

struct MiscUnk50 {
    u8 pad[0x16];
    u8 unk16;
};

struct ReadyTextExt {
    struct MiscUnk50* unk50;
    u16 unk54;
    u16 stay_up_timer; // 0x56
    u16 palette_pos;
    u16 unk58;
    u16 palette_cycle_done; // 0x5C
};

struct TitleLogoExt {
    s32 unk50;
    s8 palette_shift_speed;
    u8 palette_shift_value; // 0x55
    s8 unk56;
    u8 unk57;
    s32 palette1; // 0x58
    s32 palette2; // 0x5C
};

struct SelectACharacterExt {
    s8 pad50[5];
    u8 blast_timer; // 0x55
    s8 unk56;
    u8 unk57;
};

union MiscExt {
    struct ReadyTextExt ready_text;
    struct TitleLogoExt title_logo;
    struct SelectACharacterExt sel_char;
};

struct MiscObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    f32 x_vel; // 0x20
    f32 y_vel;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad30[0x4];
    s16 unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    s8 unk47;
    s8 pad47[5];
    union MiscExt ext;
}; // size 0x60

struct BarObj {
    struct BaseObj base;
    s8 pad18[0x34 - 0x18];
}; // size 0x43

struct BazObj {
    struct BaseObj base;
    s8 pad18[0x50 - 0x18];
}; // size 0x50

struct QuxObj {
    struct BaseObj base;
    s8 pad18[0xB0 - 0x18];
}; // size 0xB0

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

struct BgDrawRelated {
    u8 pad[0x4000];
};

struct Prim {
    u16 x;
    u16 y;
    s8 uv;
    u8 w;
    u8 h;
    s8 clut;
}; // size 0x8

extern struct PlayerObj g_Player;
extern struct PlayerObj g_Entity;
extern struct Unk16 D_80141BD8;
extern struct BackgroundObj background_objects[];
extern struct BgDrawRelated D_8015D9D0[];

struct DrawInfo {
    DISPENV dispenv;
    DRAWENV drawenv; // 0x14
    u32 unk70;
    u8 pad70[12];
    u32 unk80;
    u8 pad80[24];
    u32 unk9C;
};

extern struct DrawInfo draw_infos[2];

typedef union {
    s32* ptr;
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } two;
    struct {
        u16 lo;
        u16 hi;
    } utwo;
    struct {
        s8 a;
        s8 b;
        s8 c;
        s8 d;
    } one;
} Multi;

struct ReadyLineExt {
    f32 x_vel;
    f32 y_vel;
    f32 x_accel;
    f32 y_accel;
};

struct QuadUnkExt {
    u16 unk38;
};

struct QuadUnkExt2 {
    u16 unk38;
    s16 : 16;
    s16 unk3C;
    s16 : 16;
    s16 : 16;
    u8 unk42;
    u8 unk43;
};

struct QuadUnkExt3 {
    u8 unk38;
};

struct QuadUnkExt4 {
    s32 : 32;
    u16 unk3C;
};

union QuadExt {
    struct ReadyLineExt ready_line;
    struct QuadUnkExt unk_ext;
    struct QuadUnkExt2 unk_ext2;
    struct QuadUnkExt3 unk_ext3;
    struct QuadUnkExt4 unk_ext4;
    u32 unk38;
};

struct QuadObj {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 on_screen;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos;
    f32 y_pos;
    s8 pad10[4];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    u16 unk34;
    s8 unk36;
    s8 bg_offset;
    union QuadExt ext;
    u8 unk48;
    s8 pad_[3];
    s8 unk4C;
    s8 unk4D;
    s8 unk4E;
    s8 unk4F;
    u16 unk50;
    s16 unk52;
    s8 unk54;
    s8 unk55;
    struct BaseObj* unk58; // might be something else
    struct PlayerObj* unk5C; // might be something else
}; // size 0x60

// D_801721C0
struct EngineObj {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 pad3;
    s16 unk4;
    s8 pad2[6];
    s8 stage; // 0xc
    s8 substage; // 0xd
    s8 unkE;
    s8 unkF;
    s8 unk10;
    s8 unk11;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
    s8 unk18;
    s8 unk19;
    s8 pad1A[0x1C - 0x1A];
    s8 unk1C;
    s8 checkpoint; // 0x1d
    s8 unk1E;
    s8 unk1F;
    s32 boss_ptr; // 0x20
    s8 enable_boss; // 0x24
    s8 unk25;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    s8 pad28[0xe];
    s8 unk37;
    s8 pad37[0x8];
    u8 unk40;
    s8 pad40[2];
    s8 unk43;
    s8 unk44;
    u8 pad45;
    s8 unk46;
    s8 unk47;
    s8 unk48;
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
    s8 unk9[4];
    u8* unk10;
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
    /* 0x00 */ u8 pad;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad3[3];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 padD[1];
    /* 0x0D */ u8 unkD;
};

struct Unk80139690 {
    u8 pad;
    s8 unk1;
};

struct MainObj {
    u8 pad0[4];
    s8 unk4;
};

struct Unk14 {
    u16 unk0;
    s8 unk2;
    u8 unk3;
};

struct EffectObj {
    s8 active;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos; // 0x8 and 0xA
    f32 y_pos; // 0xC and 0xE
    s32 unk10;
    struct Unk14* unk14;
    Multi unk18;
    u8 pad18[4];
    s8 unk20;
    s8 pad20[12];
}; // size 0x30

struct Unk22 {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    u8 pad[0x28];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

struct Unk23 {
    s8 pad[0xc];
    s8 unkC;
    s8 unkD;
    s8 pad2[0xf];
    s8 unk1D;
};

struct Unk24 {
    s8 pad[2];
    s8 unk2;
    s8 pad2[0x3d];
    s8 unk40;
};

struct GameInfo {
    u8 unk0;
    u8 mode;
    u8 pad[0xb];
    u8 unkD;
};

struct OffsetInfo {
    u16 x_offset;
    u8 pad2[2];
    u16 y_offset;
    u8 pad[77];
};

struct RectPtrPair {
    RECT rect;
    u_long* ptr;
};

extern struct QuadObj g_QuadObjects[0x20];
extern s8 D_800EE538;
extern s8 D_800EE54C[];
extern u8 D_800F8B30[];
extern struct Unk_unk68 D_800F8BC4;
extern struct Unk_unk68 D_800F8BC8;
extern s8 D_800F8BF8[];
extern s8 D_800F8C10[];
extern s8* D_8010ECD4[];
extern void (*D_8010F5E8[4])();
extern void (*D_8010F5F8[2])();
extern s8 D_8010FE38[];
extern u8 D_8010FED4[];
extern u8 D_801193F0[];
extern u32 D_801194F0[];
extern u8 D_8011A030[];
extern u8 D_8011A130[];
extern u32 D_8011A230[];
extern u8 D_8011AF60[];
extern s8 D_80141BDC[];
extern u8 D_80141BDF[];
extern u8 D_80141BE0;
extern struct Unk5 D_800F0E18[];
extern s32 D_80137CC0;
extern s8 D_801419B3;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern struct DrawInfo* cur_draw_info;
extern struct EngineObj engine_obj;
extern void (*D_800F23E8[1])(void*);
extern s8 D_80171EA8;
extern void (*D_800F44A8[1])();
extern void (*D_800F48A4[1])(struct EngineObj* arg0);
extern void (*D_800F241C[1])(void);
extern u8 D_800F32D4[1][1];
extern s32 D_800EE458;
extern s32 D_8012F490;
extern s8 D_80173C6C;
extern s8 D_80173C6D;
extern s8 D_80173C6E;
extern s8 D_80173C6F;
extern s8 D_80137DFC;
extern void* D_80137E0C;
extern s8 D_80139234[24];
extern u8 D_8013924C[4];
extern void* D_8013DC10;
extern void* D_8013DC14;
extern void* D_8013DC18;
extern void* D_8013DC1C;
extern void* D_8013DC20;
extern void* D_8013DC24;
extern void* D_8013DC28;
extern void* D_8013DC2C;
extern void* D_8013DC30;
extern void* D_8013DC34;
extern void* D_8013DC38;
extern void* D_8013DC3C;
extern void* D_8013DC40;
extern void* D_8013DC44;
extern void* D_8013DC48;
extern void* D_8013DC4C;
extern void* D_8013DC54;
extern void* D_8013DC58;
extern void* D_8013DC5C;
extern void* D_8013DC60;
extern void* D_8013DC64;
extern void* D_8013DC68;
extern void* D_8013DC6C;
extern void* D_8013DC70;
extern void* D_8013DC74;
extern void* D_8013DC78;
extern void* D_8013DC7C;
extern void* D_8013DC80;
extern void* D_8013DC84;
extern void* D_8013DC88;
extern void* D_8013DC8C;
extern void* D_8013DC90;
extern void* D_8013DC94;
extern void* D_8013DC98;
extern void* D_8013DC9C;
extern void* D_8013DCA0;
extern s8 D_8013E198[6];
extern s8 D_8013E1C8[4];
extern s32 D_801395E4;
extern s32 D_801395E8;
extern volatile s32 D_80139634;
extern struct Unk80139690* D_80139690;
extern void (*D_800F43A8[1])(s32);
extern void (*D_800FB0F4[1])();
extern void (*g_TitleScalingXUpdateFuncs[1])();
extern void (*D_8010B4C4[1])();
extern void (*D_8010BEC8[1])();
extern s16* D_801F8300;
extern u16 D_801419BE[];
extern void (*g_MegamanInBriefingRoomUpdateFuncs[1])();
extern void (*g_TitleUpdateFuncs[1])();
extern void (*D_8010EB84[1])();
extern void (*g_SelectACharacterUpdateFuncs[1])();
extern struct Unk main_objects[0x30]; // D_8013BED0
extern void (*g_TitleLogoUpdateFuncs[1])();
extern void (*g_SearchLightUpdateFuncs[1])();
extern void (*D_8010FC84[1])();
extern void (*g_TitleUpdate2Funcs[1])(struct QuadObj*);
extern u8 D_8013B7D8;
extern u8 D_8013B7DC;
extern s16 D_8013B7E0;
extern s16 D_8013B7E4;
extern s16 D_8013B7E8;
extern s16 D_8013B7EC;
extern s16 D_8013B7F0;
extern s16 D_8013B7F4;
extern s16 D_8013B7F8;
extern s16 D_8013B7FC;
extern s16 D_8013B804;
extern u8 D_8013BC34[];
extern s16 D_80173C7A;
extern struct BarObj bar_object;
extern struct BazObj baz_objects[2];
extern struct VisualObj visual_objects[0x20];
extern struct ShotObj shot_objects[0x20];
extern struct WeaponObj weapon_objects[0x10];
extern struct UnkObj unk_objects[0x14];
extern struct UnkObj foo_objects[3];
extern struct EffectObj effect_objects[0x20];
extern struct ItemObj item_objects[0x20];
extern struct MiscObj misc_objects[0x40];
extern struct LayerObj layer_objects[4];
extern struct QuxObj qux_object;
extern void (*D_800F485C[1])();
extern s32 D_8013BC28;
extern void (*ReadyTextUpdateFuncs[1])(void);
extern s32 D_80137DC4;
extern s32 D_80137DD0;
extern u8 D_801406AC;
extern s32 D_80142F70;
extern s32 D_8015D9C8;
extern s8 D_801374B4;
extern s8 D_801374B8;
extern s8 D_80137CE4;
extern s8 D_80137CF0;
extern s8 D_80137CF4;
extern u8 D_8013BD40;
extern u32 D_800F1D8C;
extern CdlATV D_80139644;
extern s8 D_80139645;
extern s8 D_80139646;
extern s8 D_80139647;
extern u8 D_80171EA9;
extern s32 D_80166BB4;
extern s32 D_80166D68;
extern s32 D_8012F46C;
extern RECT D_800EE450;
extern u16 cur_random;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern void (*func_8001D064)(void);
extern s8 D_80139528;
extern CdlATV D_80139520;
extern s32 D_80137CD8;
extern RECT D_800F1658;
extern u32 D_80141F70;
extern u8 D_80139524;
extern s8 D_8013952C;
extern s32 D_80139530;
extern s32 D_80139564;
extern s8 D_8013956C;
extern s32 D_801419AC;
extern s8 D_80141BD0;
extern s32 D_80141BD4;
extern s8 D_80141F4A;
extern u8 D_801441B0;
extern u16* D_801441B4;
extern u8 D_801441B8;
extern s32 D_80137CCC;
extern s32 D_80137CEC;
extern CdlLOC D_80137CF8;
extern DISPENV old_dispenv[2];
extern s8 D_80166C20;
extern s8 D_80166C21;
extern s8 D_80166CC0;
extern s8 D_80166CC1;
extern s32 D_80137CBC;
extern s32 D_80137CEC;
extern s32 D_80139670;
extern s32 D_80139674;
extern s32 D_80139678;
extern s32 D_8013967C;
extern s32 D_80139680;
extern s32 D_80139684;
extern s32 D_80139688;
extern s32 D_80173C80;
extern void (*D_8010EBB4[1])();
extern void (*D_8010EB98[])();
extern void (*D_8010EBA0[])();
extern u8 need_palette_load;
extern void (*D_8010EBA8[])();
extern s8 D_801721F7;
extern void (*D_8010FC90[])();
extern s32 D_8010B1F8[];
extern s32 D_8010B23C[][4];
extern s32 D_8013E188[];
extern s32 D_8013E18C;
extern s32 D_8013E190;
extern s32 D_8013E194;
extern s8 D_8013E1BC;
extern s16 D_8013E1BE;
extern s8 D_80141BE4;
extern s16 D_80141BE6;
extern s8 D_801754A0;
extern s8 D_80175E9C;
extern s16 D_80175EA0;
extern s8 D_80175E9C;
extern s16 D_80175EA0;
extern u16 D_80166C0C;
extern s8 D_801419FC;
extern s32 D_8013B80C;
extern s32 D_800F4830[];
extern u16 D_800F4776[];
extern void (*D_800F3134[])(struct BackgroundObj* arg0);
extern struct Prim D_800EE504[];
extern struct RectPtrPair vram_rect_ptrs[];
extern struct RectPtrPair* vram_rect_ptr;
extern u8 D_800F30D4[][1]; // unknown size
extern u8 D_800F1A0C[1];
extern s16 D_8013BC38;

#include "func_tables.h"

s32 func_80034E2C();
s32 func_80034F7C();
void func_800129F0(s32);
void func_800127C8(s32);
void func_80012A3C();
s32 func_8001540C(s32, s32, struct Unk6*);
s32 func_800350A4(struct Unk6*, s32);
s32 func_80033694();
void func_80034538(struct Unk7*);
void func_80034754(struct Unk7*);
void func_80025188(s32, u8);
void func_80025588(s16, s16, s16, s16, s32);
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
void reset_objects();
void func_8001FBB8(struct EngineObj* arg0);
void func_800299EC(struct EngineObj* arg0);
void func_8001FBD4(struct EngineObj* arg0);
void func_8002FC38(struct EngineObj* arg0);
void func_8001FBE0(struct EngineObj* arg0);
void func_8001FC20(struct EngineObj* arg0);
void func_8001FF50(struct EngineObj* arg0);
void func_8001FAFC(struct EngineObj* arg0);
void func_80020AC8(struct EngineObj* arg0);
void func_80020D98(struct EngineObj* arg0);
void func_80020464(struct EngineObj* arg0);
void func_80023A54(struct EngineObj* arg0);
void func_800204AC(struct EngineObj* arg0);
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
void func_800B6D1C(s32, s8, s8);
void func_800B6EB4(s16, s16, s16, s16, s32);
s8 func_800B6FF4(s32, s8);
void ZeroObjectState(struct Unk18* arg0);
void init_objects();
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

s16 func_8002BAD0(s16, s16, s16);
u8 func_800D8E94(struct LayerObj*);
u8 func_800D9B08(struct LayerObj*);
s32 func_800E5FF4(s32, s32, u8*);
void func_800AE6B4(struct BazObj*);
struct Unk* func_800AFAB4(s8, s16, s16, u8);
void func_80027FA8();
void func_8002F048();
void quad_is_on_screen(struct QuadObj*);
void func_80015930(u8, u8);
void func_80016F0C();
void func_80023D30();
void func_8002AB20();
void func_8001D230();
void func_8001D284();
void func_80022730(s32*);
void func_8002B718();
void is_on_screen(struct BaseObj*);
s32 func_8002CF98(struct Unk*, u8, s16, s16);
s32 func_8002D32C(struct PlayerObj*, s16, s32);
s32 func_8002D5E4(struct PlayerObj*, s16);
u8 func_8002D724(struct PlayerObj*, s16, s16);
s32 func_8002D7E4(struct Unk*, s16, s16);
void func_800E5D78(s32);
s32 func_800E5D90(s32, s32, s32);
void func_80016334(void);
s32 func_800E5ACC(void);
void func_800E6138(s8*);
void func_8001213C(void);
void func_800122E0(struct DrawInfo* arg0);
extern void func_80013A20(void);
extern void func_80013E68(void);
void func_80013650(void);
s8 func_800136B0();
void func_800137F0();
void MyCdReadyCallback(void);
void func_80018000(s32);
