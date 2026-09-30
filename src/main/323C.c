#include "common.h"
#include "scratchpad.h"

struct HudLayoutData {
    s16 x;
    s16 y;
    u8 tile;
    u8 character;
    u8 clut;
    u8 alternate_clut;
};

struct MovieHudQuad {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 index;
};

struct MoviePlaybackData {
    u32 file_id;
    u16 arg2;
    u16 arg8;
    u16 arg9;
    u16 skip_button;
};

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

// uncomment to skip movies
// #define SKIP_MDEC
void func_80012A3C(void)
{
    struct Func80012A3C_FadeState {
        s16 unk0;
        s16 unk2;
        u16 unk4;
    }* dea0;
    struct Func80012A3C_FadeParams {
        u8 pad[4];
        s8 unk4;
        u8 unk5;
    }* d80141BD8;
    s32 temp_a0;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v1;
    TILE* temp_s0;
    DR_TPAGE* temp_s1;
    u8 color;

    *(s16*)&D_8016DEA0 = 0;
    D_8016DEA2 = 0;
    if (*D_80141BDC > 0) {
        D_8016DEA4 = 0xFF;
    } else {
        D_8016DEA4 = 0;
    }

    dea0 = (struct Func80012A3C_FadeState*)&D_8016DEA0;
    d80141BD8 = (struct Func80012A3C_FadeParams*)&D_80141BD8;

    for (;;) {
        func_800127C8(1);
        temp_a0 = SP_DRAW_BUFFER;
        temp_s0 = (TILE*)D_80169D78 + temp_a0;
        color = D_8016DEA4;

        setlen((TILE*)temp_s0, 3);
        setcode((TILE*)temp_s0, 0x62);
        setWH((TILE*)temp_s0, 320, 240);

        temp_s1 = D_8012F498 + temp_a0;
        setXY0((TILE*)temp_s0, 0, 0);
        setRGB0((TILE*)temp_s0, color, color, color);
        setlen(temp_s1, 1);

        if (GetGraphType() == 1 || GetGraphType() == 2) {
            if (GetGraphType() == 1 || GetGraphType() == 2) {
                var_v0 = 0xE1000105;
            } else {
                var_v0 = 0xE1000045;
            }
        } else if (GetGraphType() == 1 || GetGraphType() == 2) {
            var_v0 = 0xE1000105;
        } else {
            var_v0 = 0xE1000045;
        }

        catPrim(temp_s1, temp_s0);
        temp_s1->code[0] = var_v0;
        addPrims(&cur_draw_info->ordering_table.fade, temp_s1, temp_s0);

        if (dea0->unk0 == 0) {
            if (d80141BD8->unk4 > 0) {
                temp_v1 = dea0->unk4 - (s8)d80141BD8->unk5;
                dea0->unk4 = temp_v1;
                if ((temp_v1 << 0x10) <= 0) {
                    dea0->unk4 = 0U;
                    d80141BD8->unk5 = 2U;
                    dea0->unk0 = (s16)((u16)dea0->unk0 + 1);
                }
                if (dea0->unk2 == 2) {
                    SetDispMask(1);
                }
                dea0->unk2 = (s16)((u16)dea0->unk2 + 1);
            } else {
                temp_v0 = dea0->unk4 + (s8)d80141BD8->unk5;
                dea0->unk4 = temp_v0;
                if ((s16)temp_v0 >= 0x100) {
                    dea0->unk4 = 0xFFU;
                    d80141BD8->unk5 = 2U;
                    dea0->unk0 = (s16)((u16)dea0->unk0 + 1);
                }
            }
            continue;
        }

        if ((s8)d80141BD8->unk5 == 0) {
            if (d80141BD8->unk4 < 0) {
                SetDispMask(0);
            }
            d80141BD8->unk4 = 0;
            func_800127FC();
        } else {
            d80141BD8->unk5 = (u8)((s8)d80141BD8->unk5 - 1);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/323C", func_80012D28);

INCLUDE_ASM("main/nonmatchings/323C", func_80012D4C);

void func_80012D68(u32* src, u32* dst, s32 count)
{
    do {
        *dst++ = *src++;
    } while (--count);
}

INCLUDE_ASM("main/nonmatchings/323C", func_80012D88);

INCLUDE_ASM("main/nonmatchings/323C", func_80012DC0);

INCLUDE_ASM("main/nonmatchings/323C", func_80012E18);

INCLUDE_ASM("main/nonmatchings/323C", func_80012E2C);

void func_80012E38(void)
{
#ifdef VERSION_JP
    func_80013AD8(0x41, 0, 0);
#else
    func_80013AD8(0x40, 0, 0);
#endif
    func_80014C70();
#ifdef VERSION_JP
    func_80013890(0x42, WINDOW_ARCHIVE_DATA);
#else
    func_80013890(0x41, WINDOW_ARCHIVE_DATA);
#endif
    func_80014C70();
}

void func_80012E80()
{
    func_80013AD8(0, 0, 0);
    func_80014C70();
}

void func_80012EB0(void)
{
}

void func_80012EB8(void)
{
    s32 var_a0;

    if (engine_obj.cur_character == CHARACTER_X) { // g_GameVars.unk43
#ifdef VERSION_JP
        var_a0 = 0x4F;
#else
        var_a0 = 0x4E;
#endif
        if (engine_obj.unk37 == 0) { // g_GameVars.unk37
            var_a0 = 0x4B;
        }
    } else {
        var_a0 = 0x4D;
    }
    func_80013AD8(var_a0, 0, 0);
    func_80014A90(0, 0);
    func_80013530();
    D_80173C80 = D_8015D9C8;
    D_80166BB4 = D_80142F70;
    func_80015C10();
}

void func_80012F44(void)
{
    u8* saved_data;
    s32* dst;
    s32* src;
    u32 i;

    saved_data = D_8015D9C8;
#ifdef MMX4_PC
    {
        extern struct ArchiveSelectionData D_800EE480;
        static const u8 pointer_high_bytes[2] = { 0x01, 0x80 };
        u8 checkpoint = engine_obj.checkpoint;
        func_80013AD8(checkpoint < 2 ? pointer_high_bytes[checkpoint]
                                     : ((u8*)&D_800EE480)[checkpoint - 2],
            4, D_80141F38);
    }
#else
    func_80013AD8(D_800EE47E[engine_obj.checkpoint], 4, D_80141F38);
#endif
    func_80014C70();

    i = 0;
    dst = SP_PALETTE_WORDS + 0x500 / 4;
    src = SP_ARC_30 + ((engine_obj.checkpoint << 5) + 0x280 / 4);
    do {
        *dst++ = *src++;
        i++;
    } while (i < 0x80U);

    D_8015D9C8 = saved_data;
    need_palette_load |= 1;
    D_80171EA8 = (u8)engine_obj.checkpoint;
}

INCLUDE_ASM("main/nonmatchings/323C", func_80013014);

extern u8 D_801374BC[0x800];

extern s32 D_80137CCC;

extern CdlLOC D_80137DE8;

extern s32 D_80137CBC;

extern u8* D_80137CC4;

extern s32 D_80137CC8;

extern s32 D_80137CCC;

extern s32 D_80137CD8;

extern u8 D_80137DD8;

extern u8* D_80137DE0;

extern s32 D_80137DE4;

extern u8 D_801406AC;

extern struct CdCompletionSlot D_80137D04[16];

extern u8* D_80137DC4;

extern u8* D_80137DCC;

typedef struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
} D_80010014_t;

void func_80014140(void);

void func_800141BC(void);

void func_800142BC(void);

void func_80014514(void);

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

struct ArchiveSelectionData D_800EE480 = {
    { JP_VALUE(0x45, 0x46), JP_VALUE(0x47, 0x48), JP_VALUE(0x44, 0x45), JP_VALUE(0x46, 0x47),
        JP_VALUE(0x48, 0x49), JP_VALUE(0x42, 0x43), JP_VALUE(0x49, 0x4A), JP_VALUE(0x43, 0x44) },
    {
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x5B,
        0x5C,
        0x5D,
        0x5E,
        0x5F,
        0x60,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x00,
        0x67,
        0x00,
        0x00,
        JP_VALUE(0x69, 0x68),
        JP_VALUE(0x6C, 0x6B),
        JP_VALUE(0x6D, 0x6C),
        JP_VALUE(0x6F, 0x6D),
        JP_VALUE(0x00, 0x81),
        JP_VALUE(0x71, 0x6F),
        JP_VALUE(0x72, 0x70),
        JP_VALUE(0x74, 0x73),
        JP_VALUE(0x73, 0x72),
        JP_VALUE(0x6F, 0x6D),
        JP_VALUE(0x70, 0x6E),
        0x00,
        0x00,
        JP_VALUE(0x74, 0x73),
        JP_VALUE(0x75, 0x74),
        0x00,
        0x00,
        JP_VALUE(0x6A, 0x69),
        JP_VALUE(0x6B, 0x6A),
        0x00,
        0x00,
#ifdef MMX4_WIN32
        0x00,
        0x00,
        0x00,
        0x00,
#endif
        JP_VALUE(0x82, 0x81),
        JP_VALUE(0x83, 0x82),
        JP_VALUE(0x84, 0x83),
        JP_VALUE(0x85, 0x84),
        JP_VALUE(0x86, 0x85),
        JP_VALUE(0x87, 0x86),
        JP_VALUE(0x88, 0x87),
        JP_VALUE(0x89, 0x88),
        0x01,
        0x03,
        0x05,
        0x07,
        0x09,
        0x0B,
        0x0D,
        0x0F,
        0x11,
        0x13,
        0x15,
        0x17,
        0x19,
        0x1B,
        0x1D,
        0x1F,
        0x21,
        0x23,
        0x25,
        0x00,
        0x27,
        0x00,
        0x29,
        0x2B,
        0x2D,
        0x2F,
        0x31,
        JP_VALUE(0x00, 0x38),
        0x33,
        0x34,
        JP_VALUE(0x35, 0x36),
        JP_VALUE(0x36, 0x37),
        0x02,
        0x04,
        0x06,
        0x08,
        0x0A,
        0x0C,
        0x0E,
        0x10,
        0x12,
        0x14,
        0x16,
        0x18,
        0x1A,
        0x1C,
        0x1E,
        0x20,
        0x22,
        0x24,
        0x26,
        0x00,
        0x28,
        0x00,
        0x2A,
        0x2C,
        0x2E,
        0x30,
        0x32,
        JP_VALUE(0x00, 0x38),
        0x33,
        0x34,
        JP_VALUE(0x35, 0x36),
        JP_VALUE(0x36, 0x37),
        JP_VALUE(0x37, 0x38),
        JP_VALUE(0x38, 0x39),
        JP_VALUE(0x39, 0x3A),
        JP_VALUE(0x3A, 0x3B),
        JP_VALUE(0x3B, 0x3C),
        JP_VALUE(0x3C, 0x3D),
        JP_VALUE(0x3D, 0x3E),
        JP_VALUE(0x3E, 0x3F),
    },
};

#undef JP_VALUE

extern s32 D_80137CCC;

extern s32 D_80137CEC;

extern CdlLOC D_80137CF8;

extern void func_800137F0(void);

extern u8 D_801406AC;

extern s32 D_80137CBC;

extern s32 D_80137CC8;

extern s32 D_80137CCC;

extern s32* D_80137CD0;

extern s32 D_80137CDC;

extern s32 D_80137CEC;

extern u8* D_80137DC4;

extern s32 D_80137DC8;

extern u8* D_80137DCC;

extern CdlLOC D_80137DE8;

extern union TitleScratch D_80169498;

extern u16 D_8012F4A8;

extern u16 D_8012F4AC;

extern u16 D_8012F4B0;

extern u32 D_80137CE0;

void func_800147AC(void);

extern u8 D_8013BD40;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

s16 SsVabTransCompleted();

extern u8 D_801374B4;

extern u32 D_80137CE0;

extern s8 D_8013E198[];

// play_sound

s32 SpuGetKeyStatus(s32);

extern union SepBundle D_801459C8;

extern s32 player_gfx_buf_0[];

extern s32 player_gfx_buf_1[];

void func_80016448(u8 arg0);

extern u8 D_80139524;

void func_80016F0C();

extern s32 D_80139530;

extern u32 D_8013953C;

extern s32 D_80139544;

extern s16 D_8013955C;

extern s32 D_80141BD4;

#ifdef MMX4_PC
extern u32 mmx4_pc_xa_stops;
extern u32 mmx4_pc_xa_stop_sample;
#endif

void func_800163BC(s32);

void func_800163EC(void);

void func_80016448(u8);

void func_80016F0C();

extern u32 D_80139510;

extern s32 D_80139530;

extern s32 D_80139534;

extern s32 D_80141BD4;

extern u8 D_80171EA9;

extern s8 D_8013952C;

extern s32 D_80139530;

extern u8 D_80139554[];

extern s32 func_80013614(s32, s32*);

extern void func_80018788(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

extern s32 D_80139614;

extern s32 D_801395E4;

extern s32 D_80139614;

extern RECT D_80139618;

extern u32* D_80139620;

extern s32 D_80139624;

extern s32 D_80139628;

extern u32 D_8013962C;

extern u32 D_80139630;

extern s32 D_801410B8;

extern s32 D_80139610;

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

#undef JP_VALUE

/* The final record continues into g_BootTransitionDataRegion. */

extern struct BootTransitionDataRegion g_BootTransitionDataRegion;

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif
