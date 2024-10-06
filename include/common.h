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

typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} f32;

struct Unk {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 unk3;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 : 8;
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

struct Unk_unk68 {
    s8 unk0;
    s8 unk1;
    u8 unk2;
    u8 unk3;
};

struct MiscObj {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 unk3;
    s8 state;
    s8 unk5;
    s8 unk6;
    u8 pad5[3];
    s16 x_pos; // 0x0A
    s16 padc;
    s16 y_pos; // 0x0E
    u8 pad6[0x10];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s16 unk38;
    u8 pad39[5];
    u16 unk40;
    u16 unk42;
    s8 pad43[9];
    s32 unk50;
    s32 unk54;
    s8 pad55[5];
    s8 unk5D;
}; // size 0x60

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
    u32 unk70;
    u8 pad2[0x25];
    u32 unk9C;
};

extern struct DrawInfo draw_infos[2];

struct QuadObj {
    s8 pad[4];
    s8 state;
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

struct MainObj {
    u8 pad0[4];
    s8 unk4;
};

struct EffectObj {
    s8 active;
    u8 pad0[3];
    s8 state;
    u8 pad[0x30 - 5];
};

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

typedef struct {
    s8 first_byte;
    u8 padding[95];
} QuadObj;

extern QuadObj g_QuadObjects[];
extern u8 D_800F8B30[];
extern s8 D_801721CF;
extern s8 D_80141BDC;
extern struct Unk5 D_800F0E18[];
extern s32 D_80137CC0;
extern s32 D_801418C8;
extern s8 D_801419B3;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern s8 D_80141BDC;
extern struct DrawInfo* cur_draw_info;
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
extern void (*g_TitleScalingXUpdateFuncs[1])();
extern void (*D_8010B4C4[1])();
extern void (*D_8010BEC8[1])();
extern s16* D_801F8300;
extern u16 D_801419BA[];
extern u16 D_801419BE[];
extern void (*g_MegamanRelatedUpdateFuncs[1])();
extern void (*g_MegamanInBriefingRoomUpdateFuncs[1])();
extern void (*D_8010E6FC[1])();
extern void (*g_TitleUpdateFuncs[1])();
extern void (*D_8010EB84[1])();
extern void (*g_SelectACharacterUpdateFuncs[1])();
extern struct Unk game_objects[0x30]; // D_8013BED0
extern void (*g_TitleLogoUpdateFuncs[1])();
extern void (*g_SearchLightUpdateFuncs[1])();
extern void (*D_8010FC84[1])();
extern void (*g_TitleUpdate2Funcs[1])();
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
extern u8 D_8013BC34;
extern s16 D_80173C7A;
extern struct EffectObj effect_objects[0x20];
extern struct MiscObj misc_objects[0x40];
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
extern s32 D_80166D68;
extern s32 D_8012F46C;
extern RECT D_800EE450;
extern u16 D_8013E2E8;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern void (*func_8001D064)(void);
extern s8 D_80139528;
extern CdlATV D_80139520;
extern s32 D_80137CD8;
extern RECT D_800F1658;
extern u32 D_80141F70;
extern u8 D_80166BB0;
extern u8 D_80139524;
extern s8 D_8013952C;
extern s32 D_80139530;
extern s32 D_80139564;
extern s8 D_8013956C;
extern s32 D_801419AC;
extern s8 D_80141BD0;
extern s32 D_80141BD4;
extern s8 D_80141F4A;
extern s8 D_801441B0;
extern s8 D_801441B8;
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
void ZeroObjectState(struct Unk18* arg0);
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
struct Unk* func_800AFAB4(s8, s16, s16, s8);
void func_80027FA8();
void func_8002F048();
void func_800D46F4();
void func_80015930(u8, u8);
void func_80016F0C();
void func_80023D30();
void func_8002AB20();
void func_8001D230();
void func_8001D284();
void func_80022730(s32*);
void func_8002B718();
void func_8002B288(struct Unk*);
s32 func_8002CF98(struct Unk*, u8, s16, s16);
s32 func_8002D32C(struct Unk*, s16, s8);
s32 func_8002D5E4(struct Unk*, s16);
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
