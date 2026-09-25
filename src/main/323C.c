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
extern struct CdImageOrigin D_800F1614[11];
extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern u8 D_800F1654[4];
extern RECT D_800F1860;
extern u16 D_800F1868[18];
extern u16 D_800F188C[];
extern const u16* D_800F19E0;
extern const u16* D_800F19E4;
extern const u16* D_800F19E8;
extern const u16* D_800F19EC;
extern const u16* D_800F19F0;
extern const u16* D_800F19F4;
extern const u16* D_800F19F8;
extern const u16* D_800F19FC;
extern const u16* D_800F1A00;
extern const u16* D_800F1A04;
extern const u16* D_800F1A08;
extern s32 D_800F1AAC;
extern RECT D_800F1AD0;
extern struct HudLayoutData D_800F1AD8[38];
extern /* The final record continues into g_BootTransitionDataRegion. */ s16 D_800F1C08[2];
extern struct MovieHudQuad D_800F1C18[13];
extern struct MoviePlaybackData D_800F1D04[11];
extern u32 D_800F1D88;

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

        temp_s1->code[0] = var_v0;
        catPrim(temp_s1, temp_s0);
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

void func_8001326C(u8 arg0)
{
    DR_MODE* draw_mode;
    u8 temp_a0;
    SPRT* sprt;
    struct Prim* prim;
    s32 tpage;

    if ((arg0 != 0) || !(D_80141BD8.unk0 & 0x10)) {
        sprt = SP_PRIM_CURSOR;
        draw_mode = SP_DRAW_MODE_CURSOR;
        prim = &D_800EE504[arg0];
        tpage = GetTPage(0, 0, 0x380, 0x100);
        SetDrawMode(draw_mode, 0, 0, tpage, 0);
        setSprt(sprt);
        setXY0(sprt, prim->x, prim->y);
        setUV0(sprt, (prim->uv & 0xF) * 0x10, prim->uv & 0xF0);
        temp_a0 = prim->clut;
        setShadeTex(sprt, 1);
        setSemiTrans(sprt, 0);
        // this ought to be setClut but can't figure it out
        sprt->clut = ((temp_a0 & 0xF) | (((temp_a0 >> 4) + 0x1E0) << 6));
        setWH(sprt, prim->w * 0x10, prim->h * 0x10);
        catPrim(draw_mode, sprt);
        addPrims(&cur_draw_info->ordering_table.mid, draw_mode, sprt);
        SP_PRIM_CURSOR = ++sprt;
        SP_DRAW_MODE_CURSOR = ++draw_mode;
    }
}

void func_80013404(u8 arg0)
{
    s32 temp_v1;
    u8 var_s0;
    s8* a0;
    s8* var_v0;
    struct EngineObj* ptr = &engine_obj;
    SP_PRIM_CURSOR = temp1[SP_DRAW_BUFFER].data;
    SP_DRAW_MODE_CURSOR = temp2[SP_DRAW_BUFFER].data;

    func_800160F4();

    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        func_8001326C(var_s0);
    }
    if (arg0) {
        if (ptr->cur_character != CHARACTER_X) {
            func_8001326C(4);
        } else {
            func_8001326C(3);
        }
        func_8001326C(5);

        a0 = &D_800EE54C;
        if (ptr->stage == 0xC) {
            var_v0 = a0 + 0xB;
        } else {
            var_v0 = a0 + ptr->stage;
        }
        ((u8*)D_800EE504)[0x34] = *var_v0;

        func_8001326C(6);

        if (ptr->stage < 9) {
            if (ptr->substage != 0) {
                func_8001326C(8);
            } else {
                func_8001326C(7);
            }
        }
    }
}

#ifndef MMX4_PC
void func_80013530(void)
{
    func_800129F0(0x10);
    if (D_80141BDC[0] != 0) {
        do {
            func_80013404(0);
            func_800127C8(1);
        } while (D_80141BDC[0] != 0);
    }
}
#endif

void func_80013588(s32 arg0)
{
    u8 sp10;
    sp10 = 0xA0;
#ifdef MMX4_PC
    CdInit();
    CdControl(CdlSetmode, &sp10, 0);
#else
    do {
    } while (CdInit() == 0);
    do {

    } while (CdControl(CdlSetmode, &sp10, 0) == 0);
#endif
    VSync(3);
    D_80137CE4 = 0;
    D_801406AC = 0;
    D_8013BD40 = 0;
    D_801374B8 = 0;
    D_801374B4 = 0;
    D_80137CF0 = 0;
    D_80137CF4 = 0;
    func_80016334();
}

s32 func_80013614(s32 arg0, s32* arg1)
{
    struct Unk5* temp_v0;
    temp_v0 = &D_800F0E18[arg0];
    *arg1 = temp_v0->unk4;
    D_80137CC0 = temp_v0->unk8;
    return temp_v0->unk0;
}

void func_80013650(void)
{
    if (D_80137CD8 == 0) {
        CdReadyCallback(MyCdReadyCallback);
    } else {
        CdReadyCallback(func_80013E68);
    }
    while (CdControl(CdlReadN, 0, 0) == 0)
        ;
    D_801406AC = 1;
}

extern u8 D_801374BC[0x800];

extern s32 D_80137CCC;

extern CdlLOC D_80137DE8;

s8 func_800136B0(void)
{
    s32 temp_v0_2;
    s32 temp_v0_3;
    u32 temp_v0;
    u32 var_v0;

    if ((u32)D_80137CBC >= 0x801U) {
        CdGetSector(&D_80137DE8, 3);
        temp_v0_2 = CdPosToInt(&D_80137DE8);
        if (temp_v0_2 == (D_80137CCC + 1)) {
            D_80137CCC = temp_v0_2;
            CdGetSector(D_80137CC4, 0x200);
            temp_v0 = D_80137CBC - 0x800;
            D_80137CBC = temp_v0;
            D_80137CC4 += 0x800;
        } else {
            return -1;
        }
    } else {
        CdGetSector(&D_80137DE8, 3);
        temp_v0_3 = CdPosToInt(&D_80137DE8);
        if (temp_v0_3 != (D_80137CCC + 1)) {
            return -1;
        }
        D_80137CCC = temp_v0_3;
        CdGetSector(D_80137CC4, ((u32)(D_80137CBC + 3) >> 2));
        var_v0 = (u32)(D_80137CBC + 3) >> 2;
        if (var_v0 != 0x200) {
            var_v0 = CdGetSector(&D_801374BC, 0x200 - var_v0);
        }
        D_80137CBC = 0;
    }
#ifdef MMX4_PC
    return 0;
#endif
}

void func_800137F0(void)
{
    CdReadyCallback(0);
    D_801406AC = 0;
    do {

    } while (CdControl(CdlPause, 0, 0) == 0);
    D_801406AC = 2;
    D_8015D9C8 = D_80137DC4;
    D_80142F70 = D_80137DD0;
}

u8 func_8001385C(void)
{
#ifdef MMX4_PC
    u8 result[4] = { 0 };
    do {
    } while (CdControlB(CdlNop, 0, result) == 0);
    return result[0];
#else
    u8 sp10;

    do {

    } while (CdControlB(CdlNop, 0, &sp10) == 0);
    return sp10;
#endif
}

extern s32 D_80137CBC;

extern u8* D_80137CC4;

extern s32 D_80137CC8;

extern s32 D_80137CCC;

extern s32 D_80137CD8;

extern u8 D_80137DD8;

extern u8* D_80137DE0;

extern s32 D_80137DE4;

extern u8 D_801406AC;

void func_80013890(u32 arg0, u8* arg1)
{
    if (CdReady(1, NULL) != 0) {
        CdControlB(9U, NULL, NULL);
    }
    if (D_801406AC != 0x80) {
        D_80137DE4 = 0;
    }
    D_801406AC = 0;
    D_80137DD8 = arg0;
    D_80137DE0 = arg1;
    do {

    } while (func_8001385C() & 0x40);
    D_80137CD8 = 0;
    D_80137CCC = func_80013614(arg0, &D_80137CC8);
    D_80137CC4 = (u8*)arg1;
    D_80137CBC = D_80137CC8;
    func_80013968();
}

void func_80013968(void)
{
    u8 sp10;

    sp10 = 0xA0;
    D_801406AC = 0;
    D_80137CEC = 0;
    CdIntToPos(D_80137CCC, &D_80137CF8);
    D_80137CCC -= 1;
    do {
    loop_1:
        if (CdReady(1, NULL) != 0) {
            goto loop_1;
        }
        if (CdControl(CdlSetmode, &sp10, NULL) == 0) {
            goto loop_1;
        }
        VSync(3);
    } while (CdControl(CdlSetloc, &D_80137CF8.minute, NULL) == 0);
    func_80013650();
}

void MyCdReadyCallback(u8 status, u8* result)
{
    (void)status;
    (void)result;

    if (D_801406AC != 0) {
        D_80137CEC += 1;
        if (CdReady(1, NULL) != 1) {
        pos:
            CdReadyCallback(NULL);
            CdControlB(CdlPause, NULL, NULL);
            D_801406AC = 0x80;
        } else {
            if (func_800136B0() != -1) {
                if (D_80137CBC == 0) {
                    func_800137F0();
                }
            } else {
                goto pos;
            }
        }
    }
}

extern struct CdCompletionSlot D_80137D04[16];

extern u8* D_80137DC4;

extern u8* D_80137DCC;

void func_80013AD8(s32 arg0, u8 arg1, CdLoadAddress arg2)
{
    u8 i;
    s8 temp_a0;
    s8 temp_a0_2;
    if (CdReady(1, 0) != 0) {
        CdControlB(9U, 0, 0);
    }
    i = 0;
    if (D_801406AC != 0x80) {
        D_80137DE4 = 0;
    }
    D_801406AC = 0;
    D_80137DD8 = arg0;
    D_80137DDC = arg1;
    D_80137DE0 = (u8*)arg2;
    D_8013BD40 = 0;
    D_801374B8 = 0;
    D_801374B4 = 0;
    D_80137CF0 = 0;
    D_80137CF4 = 0;
    do {
        D_80137D04[i].pending = 0;
        i += 1;
    } while (i < 0x10U);
    switch (D_80137DDC) {
    case 0:
        D_80137DCC = MAIN_ARCHIVE_ARENA;
        i = 0;
        D_80137DD0 = 0x1010;
        do {
            if (i != 2) {
                temp_a0 = D_8013E198[i];
                if (temp_a0 != (-1)) {
                    SsVabClose((s16)temp_a0);
                    D_8013E198[i] = -1;
                }
            }
            i += 1;
        } while (i < 6U);
        break;

    case 1:
        D_80137DCC = D_80137DC4;
        break;

    case 2:
        D_80137DCC = (u8*)arg2;
        break;

    case 3:
        i = 2;
        D_80137DCC = D_80173C80;
        D_80137DD0 = D_80166BB4;
        do {
            if (i != 3) {
                temp_a0_2 = D_8013E198[i];
                if (temp_a0_2 != (-1)) {
                    SsVabClose((s16)temp_a0_2);
                    D_8013E198[i] = -1;
                }
            }
            i += 1;
        } while (i < 6U);
        break;

    case 4:
        D_80137DD0 = (s32)arg2;
        D_80137DCC = D_8015D9C8;
        if (D_8013E198[2] != (-1)) {
            SsVabClose((s16)D_8013E198[2]);
            D_8013E198[2] = -1;
        }
        break;
    }

    D_80137CD8 = 1;
    D_80137CCC = func_80013614((s32)arg0, &D_80137CBC);
    CdReadyCallback(func_80013E68);
    func_80013DA8();
}

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

const D_80010014_t D_80010014 = {
    func_80014140, func_800142BC, func_80014514, func_800141BC
};

extern s32 D_80137CCC;

extern s32 D_80137CEC;

extern CdlLOC D_80137CF8;

void func_80013DA8(void)
{
    u8 sp10;

    sp10 = 0xA0;
    D_80137CEC = 0;
    CdIntToPos(D_80137CCC, &D_80137CF8);
    do {
        do {
            while (func_8001385C() & 0x40) {
            }
            while (CdReady(1, NULL) != 0) {
            }
        } while (CdControl(CdlSetmode, &sp10, NULL) == 0);
        VSync(3);
    } while (CdControl(CdlSetloc, &D_80137CF8, NULL) == 0);
    do {

    } while (CdControl(CdlReadN, NULL, NULL) == 0);
    D_801406AC = 1;
}

extern void func_800137F0(void);

extern const D_80010014_t D_80010014;

extern u8** D_800F15BC[];

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

void func_80013E68(u8 status, u8* result)
{
    D_80010014_t sp10;
    s32 temp_a1;
    s32 temp_v0;
    u32 temp_v1_2;

    (void)status;
    (void)result;
    sp10 = D_80010014;

    if (D_801406AC != 0x80) {
        if (CdReady(1, NULL) != 1) {
            goto block_4;
        }
        if (D_80137CEC == 0) {
            D_80137CD0 = D_80169498.sector;
            CdGetSector(&D_80137DE8, 3);
            if (CdPosToInt(&D_80137DE8) == D_80137CCC) {
                goto block_5;
            }
        } else {
            goto block_6;
        }
    block_4:
        CdReadyCallback(NULL);
        CdControlB(9U, NULL, NULL);
        D_801406AC = 0x80;
        return;

    block_5:
        CdGetSector(D_80137CD0, 0x200);
        D_80137CDC = *D_80137CD0++;
        D_80137CC8 = *D_80137CD0++;
        D_80137CD4.word = *D_80137CD0++;
        temp_a1 = *D_80137CD0++;
        D_80137CE8 = 1;
        D_80137DC4 = D_80137DCC;
        D_80137CEC += 1;
        D_80137CBC = temp_a1;
        D_80137DC8 = temp_a1;
        return;

    block_6:
        (&sp10.unk0)[D_80137CD4.f.handler]();
        if (D_80137CBC == 0) {
            if ((D_80137CD4.word >> 16) == 0) {
                *D_800F15BC[D_80137CD4.word] = D_80137DC4;
                D_80137DC4 += D_80137DC8;
            }
            D_80137CDC -= 1;
            temp_v1_2 = *D_80137CD0++;
            D_80137CD4.word = temp_v1_2;
            temp_v0 = *D_80137CD0++;
            D_80137CBC = temp_v0;
            if ((temp_v1_2 >> 16) == 0) {
                D_80137DC8 = temp_v0;
            }
            D_80137CE8 = 1;
        }
        D_80137CEC += 1;
        if (D_80137CDC == 0) {
            func_800137F0();
        }
    }
}

void func_80014140(void)
{
    if (D_80137CE8 != 0) {
        D_80137CE8 = 0;
        D_80137CC4 = D_80137DC4;
    }
    if (func_800136B0() == -1) {
        CdReadyCallback(0);
        CdControlB(CdlPause, NULL, NULL);
        D_801406AC = 0x80;
    }
}

void func_800141BC(void)
{
    u8 index;

    if (D_80137CE8 != 0) {
        D_80137CE8 = 0;
        D_80137CC4 = D_80137DC4;
    }
    if (func_800136B0() == -1) {
        CdReadyCallback(0);
        CdControlB(CdlPause, NULL, NULL);
        D_801406AC = 0x80;
        return;
    }
    if (D_80137CBC == 0) {
        index = D_80137CD4.f.op;
        if (D_8013E1C8[index] != -1) {
            SsSepClose(D_8013E1C8[index]);
            D_8013E1C8[index] = -1;
        }
        D_8013E1C8[index] = SsSepOpenJ((unsigned long*)D_80137DC4, D_8013E198[index], 3);
    }
}

extern struct CdImageOrigin D_800F1614[];

extern u16 D_8012F4A8;

extern u16 D_8012F4AC;

extern u16 D_8012F4B0;

void func_800142BC(void)
{
    s32 temp_a1;
    struct CdCompletionSlot* slot;
    u8 temp_a0;
    u8 temp_v0;
    u16 temp_v0_3;
    u16* temp_v0_2;
    temp_v0 = D_80137CF4 + 1;
    D_80137CF4 = temp_v0;
    if (temp_v0 - D_80137CF0 < 7) {
        if (D_80137CE8 != 0) {
            temp_v0_2 = &D_800F1614[D_80137CD4.f.arg].x;
            D_8012F4A8 = *temp_v0_2++;
            temp_v0_3 = *temp_v0_2;
            D_80137CE8 = 0;
            D_8012F4AC = temp_v0_3;
            D_8012F4B0 = temp_v0_3 & 0x100;
        }
        D_80137CC4 = D_8012F4B4.sectors[D_801374B8];
    } else
        goto fail;
    if (func_800136B0() == -1) {
    fail:
        CdReadyCallback(0);
        CdControlB(9U, 0, 0);
        D_801406AC = 0x80;
    } else {
        D_8013BD40 = 1;
        D_80137D04[D_801374B8].pending = 1;
        D_80137D04[D_801374B8].callback = 1;
        temp_a0 = D_801374B8 + 1;
        slot = &D_80137D04[D_801374B8];
        temp_a1 = (D_8012F4A8 << 16) | D_8012F4AC;
        D_801374B8 = temp_a0;
        slot->callback_arg = temp_a1;
        if (temp_a0 == 0x10) {
            D_801374B8 = 0;
        }
        switch ((D_80137CD4.word >> 8) & 0xFF) {
        case 0:
            if (D_8012F4AC == D_8012F4B0 + 0xF0) {
                D_8012F4A8 += 0x40;
                D_8012F4AC = D_8012F4B0;
            } else {
                D_8012F4AC += 0x10;
            }
            return;
        case 1:
            if (D_8012F4AC == D_8012F4B0 + 0xA0) {
                D_8012F4A8 += 0x40;
                D_8012F4AC = D_8012F4B0;
            } else {
                D_8012F4AC += 0x10;
            }
            return;
        case 2:
            if (D_8012F4AC == 0xF0) {
                D_8012F4A8 += 0x40;
                D_8012F4AC = 0xB0;
            } else {
                D_8012F4AC += 0x10;
            }
            return;
        }
    }
}

extern u32 D_80137CE0;

extern u8* D_80141EE8[];

void func_80014514(void)
{
    s32 temp_s0;
    s32 slot;
    s32 var_a0;
    s32 var_a1;
    s8 temp_v0_2;
    u8 temp_s1;
    u8 temp_a0_2;
    u8 temp_v0;
    void* temp_a0;
    struct SoundArchive* archive;
    temp_v0 = D_80137CF4 + 1;
    D_80137CF4 = temp_v0;
    if (temp_v0 - D_80137CF0 >= 7) {
        CdReadyCallback(0);
        CdControlB(9, 0, 0);
        D_801406AC = 0x80;
        return;
    }
    temp_s1 = D_80137CD4.word >> 8;
    D_80137D04[D_801374B8].transfer_pending = 0;
    if (D_80137CE8 != 0) {
        archive = (struct SoundArchive*)D_80141F00;
        temp_s0 = temp_s1 & 0xFF;
        D_80141F30[temp_s0] = D_80137DD0;
        D_80141F50[temp_s0] = archive->sound_entries;
        temp_a0 = (u8*)archive + archive->vab_offset;
        D_80141EE8[temp_s0] = temp_a0;
        temp_v0_2 = SsVabOpenHeadSticky(temp_a0, archive->vab_id, D_80137DD0);
        D_8013E198[temp_s0] = temp_v0_2;
        if (temp_v0_2 == -1) {
            CdReadyCallback(0);
            CdControlB(9, 0, 0);
            D_801406AC = 0x80;
            return;
        }
        SpuSetTransferMode(0);
        var_a1 = D_80137CBC;
        D_80137CE8 = 0;
        var_a0 = D_80137DD0 + var_a1;
        D_80137D04[D_801374B8].transfer_pending = 0xFFFF;
        D_80137CE0 = var_a1;
        D_80137DD0 = var_a0;
    }
    D_80137CC4 = D_8012F4B4.sectors[D_801374B8];

    if (func_800136B0() == -1) {
        CdReadyCallback(0);
        CdControlB(9, 0, 0);
        D_801406AC = 0x80;
        return;
    }
    D_8013BD40 = 1;
    D_80137D04[D_801374B8].pending = 1;
    D_80137D04[D_801374B8].callback = 2;
    temp_a0_2 = D_801374B8 + 1;
    slot = D_801374B8;
    D_801374B8 = temp_a0_2;
    D_80137D04[slot].callback_arg = temp_s1 & 0xFF;
    if (temp_a0_2 == 0x10) {
        D_801374B8 = 0;
    }
}

void func_800147AC(void);

extern u8 D_8013BD40;

void func_80014780(void)
{
    if (D_8013BD40 != 0) {
        func_800147AC();
    }
}

extern void (*D_800F1640[3])(void);

void func_800147AC(void)
{
    while (D_80137D04[D_801374B4].pending != 0) {
        D_800F1640[D_80137D04[D_801374B4].callback]();
        D_80137D04[D_801374B4].pending = 0;
        if (++D_801374B4 == 0x10) {
            D_801374B4 = 0;
        }
        D_80137CF0++;
    }
    if (D_80137CF4 == D_80137CF0) {
        D_8013BD40 = 0;
    }
}

void func_800148E4(void)
{
}

void func_800148EC()
{
    u32 temp_a1;

    temp_a1 = D_80137D04[D_801374B4].callback_arg;
    D_80137CFC.x = temp_a1 >> 0x10;
    D_80137CFC.y = temp_a1;
    D_80137CFC.w = 0x40;
    D_80137CFC.h = 0x10;
    LoadImage(&D_80137CFC, (u_long*)D_8012F4B4.sectors[D_801374B4]);
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

s16 SsVabTransCompleted();

extern u8 D_801374B4;

extern u32 D_80137CE0;

extern s8 D_8013E198[];

void func_80014968(void)
{
    s16 temp_v0;
    u8 temp_s1;
    u32 var_s0;

    if (D_80137D04[D_801374B4].transfer_pending != 0xFFFF) {
        while (!SsVabTransCompleted(0))
            ;
    } else {
        D_80137D04[D_801374B4].transfer_pending = 0;
    }

    temp_s1 = D_80137D04[D_801374B4].callback_arg;
    var_s0 = MIN(0x800, D_80137CE0);
    temp_v0 = SsVabTransBodyPartly(
        D_8012F4B4.sectors[D_801374B4],
        var_s0,
        D_8013E198[temp_s1]);
    D_80137CE0 -= var_s0;
    if ((D_80137CE0 == 0) && (temp_v0 == D_8013E198[temp_s1])) {
        while (!SsVabTransCompleted(0))
            ;
    }
}

#ifndef MMX4_PC
void func_80014A90(s32 arg0, s32 arg1)
{
    u8 sp10;
    u32 temp_v0;
    u32 temp_v1;

    temp_v1 = D_801406AC;
    sp10 = 0xA0;
    D_80137DD4 = 0;
    D_8013BD44 = 0;
    while ((temp_v1 != 2) || (D_8013BD40 != 0)) {
        if ((D_80137DD4 == 0) && !(arg1 & 0xFF) && (D_80141BDC[0] == 0)) {
            func_800129A4(8);
            D_80137DD4 += 1;
        }
        func_80013404(arg0 & 0xFF);
        if (D_801406AC & 0xC0) {
            if (D_80137CD8 == 0) {
                func_80013890(D_80137DD8, D_80137DE0);
            } else {
                func_80013AD8(D_80137DD8, D_80137DDC, D_80137DE0);
            }
        } else {
            temp_v0 = D_80137DE4 + 1;
            D_80137DE4 = temp_v0;
            if (temp_v0 >= 0x259U) {
                CdReadyCallback(0);
                do {
                } while (CdReset(0) == 0);
                do {
                } while (CdControlB(0xE, &sp10, 0) == 0);
                VSync(3);
                D_801406AC = 0xC0;
            }
        }
        func_800127C8(1);
        temp_v1 = D_801406AC;
    }
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
    if (arg1 & 0xFF) {
        func_80013530();
    }
}
#endif

#ifndef MMX4_PC
void func_80014C70(void)
{
    u8 sp10;
    u32 temp_v0;
    s32 temp_v1;

    temp_v1 = D_801406AC;
    sp10 = 0xA0;
    D_8013BD44 = 0;
    while (temp_v1 != 2 || D_8013BD40 != 0) {
        if (D_801406AC & 0xC0) {
            if (D_80137CD8 == 0) {
                func_80013890(D_80137DD8, D_80137DE0);
            } else {
                func_80013AD8(D_80137DD8, D_80137DDC, D_80137DE0);
            }
        } else {
            temp_v0 = D_80137DE4 + 1;
            D_80137DE4 = temp_v0;
            if (temp_v0 >= 0x259U) {
                CdReadyCallback(NULL);
                do {
                } while (CdReset(0) == 0);
                do {
                } while (CdControlB(0xE, &sp10, NULL) == 0);
                VSync(3);
                D_801406AC = 0xC0;
            }
        }
        func_800127C8(1);
        temp_v1 = D_801406AC;
    }
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
}
#endif

void func_80014DC4(void)
{
    u8 var_v1;

    D_80137DFC = 0;

    for (var_v1 = 0; var_v1 < 6; var_v1++) {
        D_8013E198[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 4; var_v1++) {
        D_8013E1C8[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 4; var_v1++) {
        D_8013924C[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 24; var_v1++) {
        D_80139234[var_v1] = -1;
    }

    D_8013DC10 = &_SsNoteOn;
    D_8013DC14 = &_SsSetProgramChange;
    D_8013DC1C = &dmy_SsGetMetaEvent;
    D_8013DC18 = &dmy_SsSetPitchBend;
    D_8013DC20 = &_SsSetControlChange;
    D_8013DC24 = &dmy_SsContBankChange;
    D_8013DC2C = &_SsContMainVol;
    D_8013DC30 = &dmy_SsContPanpot;
    D_8013DC34 = &dmy_SsContDamper;
    D_8013DC38 = &dmy_SsContNrpn1;
    D_8013DC3C = &dmy_SsContNrpn2;
    D_8013DC40 = &_SsContRpn1;
    D_8013DC44 = &dmy_SsContRpn2;
    D_8013DC48 = &dmy_SsContExternal;
    D_8013DC4C = &dmy_SsContResetAll;
    D_8013DC28 = &dmy_SsContDataEntry;
    D_8013DC54 = &dmy_SsSetNrpnVabAttr0;
    D_8013DC58 = &dmy_SsSetNrpnVabAttr1;
    D_8013DC5C = &dmy_SsSetNrpnVabAttr2;
    D_8013DC60 = &dmy_SsSetNrpnVabAttr3;
    D_8013DC64 = &dmy_SsSetNrpnVabAttr4;
    D_8013DC68 = &dmy_SsSetNrpnVabAttr5;
    D_8013DC6C = &dmy_SsSetNrpnVabAttr6;
    D_8013DC70 = &dmy_SsSetNrpnVabAttr7;
    D_8013DC74 = &dmy_SsSetNrpnVabAttr8;
    D_8013DC78 = &dmy_SsSetNrpnVabAttr9;
    D_8013DC7C = &dmy_SsSetNrpnVabAttr10;
    D_8013DC80 = &dmy_SsSetNrpnVabAttr11;
    D_8013DC84 = &dmy_SsSetNrpnVabAttr12;
    D_8013DC88 = &dmy_SsSetNrpnVabAttr13;
    D_8013DC8C = &dmy_SsSetNrpnVabAttr14;
    D_8013DC90 = &dmy_SsSetNrpnVabAttr15;
    D_8013DC94 = &dmy_SsSetNrpnVabAttr16;
    D_8013DC98 = &dmy_SsSetNrpnVabAttr17;
    D_8013DC9C = &dmy_SsSetNrpnVabAttr18;
    D_8013DCA0 = &dmy_SsSetNrpnVabAttr19;

    SsInit();
    SsSetTableSize(&D_80137E0C, 3, 0xA);
    SsSetTickMode(1);
    SsUtSetReverbType(2);
    while (SpuClearReverbWorkArea(2) == -1)
        ;
    func_800E0D0C();
    SsUtSetReverbDepth(8, 8);
#ifdef MMX4_PC
    {
        extern const char* mmx4_pc_sfx_raw;
        if (mmx4_pc_sfx_raw == NULL && Psyz_AudioInit() != 0)
            fprintf(stderr, "MMX4 PC: unable to initialize audio output\n");
    }
#endif
}

void func_8001512C(void)
{
    SsStart();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0x4A, 0x4A);
}

void func_80015178(void)
{
    s8 i;

    for (i = 0; i < 6; i++) {
        if (D_8013E198[i] != -1) {
            SsVabClose(D_8013E198[i]);
            D_8013E198[i] = -1;
        }
    }

    for (i = 0; i < 4; i++) {
        if (D_8013E1C8[i] != -1) {
            SsSepClose(D_8013E1C8[i]);
            D_8013E1C8[i] = -1;
        }
    }

    func_800E0CEC();
    SsUtSetReverbType(0);
    SsUtSetReverbDepth(0, 0);
    SsEnd();
    func_800DCF40();
}

INCLUDE_ASM("main/nonmatchings/323C", func_80015284);

void func_800153D4(u8 arg0)
{
    arg0 ? SsSetStereo() : SsSetMono();
}

INCLUDE_ASM("main/nonmatchings/323C", func_8001540C);

INCLUDE_ASM("main/nonmatchings/323C", func_800154E8);

INCLUDE_ASM("main/nonmatchings/323C", func_800157AC);

void func_80015930(u8 arg0, u8 arg1)
{
    u8* entry;
    u8 var_s1;
    s8 var_s2;
    s8 temp_v0;

    if (arg0 == 0xFF) {
        for (var_s1 = 0; var_s1 < 0x18; var_s1++) {
            SsUtSetVVol(var_s1, 0, 0);
            SsUtKeyOffV(var_s1);
        }
        return;
    }

    entry = D_80141F50[arg0] + arg1 * 4;
    temp_v0 = entry[3];
    var_s1 = temp_v0 & 0x1F;
    for (var_s2 = (temp_v0 & 0x60) >> 5; var_s2 >= 0; var_s2--) {
        SsUtSetVVol(var_s1, 0, 0);
        SsUtKeyOffV(var_s1);
        var_s1++;
    }
}

s32 SpuGetKeyStatus(s32);

s32 func_80015A10(s32 arg0, struct MainObj* owner)
{
    u8* entry = D_80141F50[2];

    entry += (arg0 & 0xFF) * 4;
    return SpuGetKeyStatus(1 << (entry[3] & 0x1F)) == 0;
}

INCLUDE_ASM("main/nonmatchings/323C", func_80015A50);

extern u8 D_800F1654[];

extern union SepBundle D_801459C8;

void func_80015C10(void)
{
    u8 var_s1;
    s8 temp_a0;

    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        temp_a0 = D_8013E1C8[var_s1];
        if (temp_a0 != -1) {
            SsSepClose(temp_a0);
            D_8013E1C8[var_s1] = -1;
        }
    }

    func_80013890(D_800F1654[engine_obj.cur_character], D_801459C8.raw);
    func_80014C70();
    D_8013E1C8[0] = SsSepOpenJ((u_long*)&D_801459C8.raw[D_801459C8.offsets[0]], D_8013E198[0], 8);

    for (var_s1 = 0; var_s1 < 8; var_s1++) {
        SsSepSetVol(D_8013E1C8[0], var_s1, 0x7F, 0x7F);
    }

    D_8013E1C8[1] = SsSepOpenJ((u_long*)&D_801459C8.raw[D_801459C8.offsets[1]], D_8013E198[1], 2);

    for (var_s1 = 0; var_s1 < 2; var_s1++) {
        SsSepSetVol(D_8013E1C8[1], var_s1, 0x7F, 0x7F);
    }
}

s32 func_80015D60(void* object, s32 animation)
{
    struct AnimatedObj* arg0 = object;

    arg0->animation_cursor = arg0->animation_table[animation];
    arg0->unk17 = animation;
    arg0->previous_animation_index = 0xFF;
    __builtin_memcpy(&arg0->animation_step, arg0->animation_cursor, sizeof(arg0->animation_step));
}

void func_80015D90(struct AnimatedObj* arg0, s32 arg1, s32 arg2)
{
    arg0->animation_cursor = arg0->animation_table[arg1] + arg2;
    arg0->unk17 = arg1;
    arg0->previous_animation_index = 0xFF;
    arg0->animation_step.packed = *arg0->animation_cursor;
}

void func_80015DC8(struct AnimatedObj* arg0)
{
    if (--arg0->animation_step.fields.duration == 0) {
        arg0->animation_cursor = &arg0->animation_cursor[arg0->animation_step.fields.relative_step];
        __builtin_memcpy(&arg0->animation_step, arg0->animation_cursor, sizeof(arg0->animation_step));
    }
}

void clear_vram_rect_ptrs(void)
{
    u32 i;
    struct RectPtrPair* ptr;

    ptr = &vram_rect_ptrs[0];
    vram_rect_ptr = ptr;

    for (i = 0; i < 8; i++) {
        ptr->rect.x = 0;
        ptr->rect.y = 0;
        ptr->rect.w = 0;
        ptr->rect.h = 0;
        ptr->ptr = NULL;
        ptr++;
    }
}

void load_vram_rect_ptrs(void)
{
    struct RectPtrPair* cur;
    for (cur = &vram_rect_ptrs[0]; cur < &vram_rect_ptrs[8]; cur++) {
        if (cur->ptr != NULL) {
            LoadImage(&cur->rect, cur->ptr);
        }
    }
    vram_rect_ptr = &vram_rect_ptrs[0];
}

extern s32 player_gfx_buf_0[];

extern s32 player_gfx_buf_1[];

void decompress_player_gfx(struct GraphicsObj* arg0, s16 x, s16 y)
{
    u8* src;
    u8* dst;
    s32* new_var;
    struct RectPtrPair* gfx;
    u32 temp_a1;
    s16 size;

    if (arg0->previous_animation_index == arg0->animation_step.fields.frame_index) {
        return;
    }

    src = arg0->unk38;
    new_var = arg0->unk38;
    arg0->previous_animation_index = arg0->animation_step.fields.frame_index;
    temp_a1 = new_var[arg0->animation_step.fields.frame_index];
    size = temp_a1 >> 0x14;
    if (arg0->unk49 == 3) {
        dst = player_gfx_buf_0;
    } else {
        dst = &player_gfx_buf_1[arg0->unk49 * 1024];
    }
    decompress_gfx(&src[temp_a1 & 0xFFFFF], dst);

    gfx = vram_rect_ptr;
    do {
        gfx->rect.x = x;
        gfx->rect.y = y;
        gfx->ptr = dst;
        if (size < 16) {
            gfx->rect.w = size * 4;
            gfx->rect.h = 16;
            size = 0;
        } else {
            gfx->rect.w = 64;
            gfx->rect.h = size / 16 * 16; // quantize to a multiple of 16
            y += gfx->rect.h;
            size -= gfx->rect.h;
            dst += 2048;
        }
        gfx++;
    } while (size != 0);

    gfx->ptr = NULL;
    vram_rect_ptr = gfx;
}

void load_palette(void)
{
    if (need_palette_load != 0) {
        if (need_palette_load & 1) {
            LoadImage(&D_800F1658, (u_long*)SP_PALETTE);
        } else if (need_palette_load & 2) {
            LoadImage(&D_800F1658, (u_long*)D_80141F70); // D_80141F70 is in vram_rect_ptr but can't figure out a match
        }

        need_palette_load = 0;
    }
}

// copy scratchpad to memory location
void func_80016074(void)
{
    u16* var_a0;
    u16* var_a1;
    u32 var_v1;

    var_a1 = D_80141F70;
    var_a0 = SP_PALETTE;
    var_v1 = 0;
    do {
        *var_a1++ = *var_a0++;
        var_v1 += 1;
    } while (var_v1 < 0x800U);
}

void func_800160AC(void)
{
    u16* src = D_801441B4;
    u16* dst = SP_BG_TILE_PIXELS;
    s32 count = (u32)((u8*)SP_BG_TILE_ATTRS - (u8*)dst) >> 1;

    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

extern union MainPaletteData D_800F1660;

extern RECT D_800F1860;

void func_800160F4(void)
{
    LoadImage(&D_800F1860, &D_800F1660);
}

INCLUDE_ASM("main/nonmatchings/323C", func_80016124);

void func_80016334(void)
{
    func_80016420(0);
    D_80171EA9 = 1;
    D_8013956C = 1;
    D_801419AC = 0;
    D_801441B8 = 0;
    D_80141F4A = 0;
    D_8013952C = 0;
    D_80141BD4 = 0;
    D_80139524 = 0x80;
    D_80139530 = 0;
    D_80141BD0 = 0;
    D_80139564 = 0;
    D_801441B0 = 0;
}

void func_800163BC(s32 arg0)
{
    D_80171EA9 = 0;
    func_80016420(D_80139524);
}

void func_800163EC(void)
{
    D_80171EA9 = 1;
    func_80016420(D_80139524);
}

void func_80016448(u8 arg0);

extern u8 D_80139524;

void func_80016420(s8 arg0)
{
    D_80139524 = arg0;
    func_80016448(arg0);
}

void func_80016448(u8 arg0)
{
    s32 temp_v0;
    D_80139528 = arg0;
    if (D_80171EA9 == 1) {
        D_80139520.val0 = arg0;
        D_80139520.val1 = 0;
        D_80139520.val2 = arg0;
        D_80139520.val3 = 0;
    } else {
        temp_v0 = arg0 >> 1;
        D_80139520.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139520.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139520.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139520.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139520);
}

void func_800164D8(void)
{
    s8 pad[2];
    s32 a = engine_obj.stage * 8;
    s32 b = engine_obj.substage * 4;
    s32 c = engine_obj.cur_character * 2;
    s32 temp_v0;

    temp_v0 = a + b + c;
    func_8001663C(((u8*)&D_800F1A0C)[temp_v0],
        ((u8*)&D_800F1A0C)[temp_v0 + 1]);
}

void func_8001653C(void)
{
    s8 pad[8];
    s32 track;
    s32 volume;

    if ((u32)((u8)engine_obj.stage - 0xB) < 2U) {
        if (engine_obj.stage == 0xB) {
            if (engine_obj.substage == 0) {
                if (engine_obj.cur_character == 0) {
                    track = 0xF;
                    volume = 0x75;
                } else {
                    track = 0xD;
                    volume = 0x7F;
                }
            } else {
                track = 0xB;
                volume = 0x7F;
            }
        } else if (engine_obj.stage == 0xC) {
            if (engine_obj.substage == 0) {
                track = 7;
                volume = 0x70;
            } else if (D_80171EA8 == 0) {
                track = 2;
                volume = 0x7F;
            } else {
                track = 1;
                volume = 0x75;
            }
        }
    } else {
        track = D_800F1A0C.alternate[engine_obj.stage].sequence;
        volume = D_800F1A0C.alternate[engine_obj.stage].volume;
    }

    func_8001663C(track, volume);
}

INCLUDE_ASM("main/nonmatchings/323C", func_8001663C);

INCLUDE_RODATA("main/nonmatchings/323C", D_80010050);

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

void func_800168D8(void)
{
    s32 temp_s2;
    s32 temp_v0;
    u32 temp_v0_2;

    if (D_80141BD4 == 2) {
        temp_s2 = D_80139530;
#ifdef MMX4_PC
        if (mmx4_pc_replay_active()) {
            if (temp_s2 == D_80141BD4)
                D_8013955C = 1;
            if (mmx4_pc_replay_xa_stop_due()) {
                mmx4_pc_replay_xa_stop_consume();
                if (*(u8*)&D_80139568 == 0) {
                    D_80139530 = 5;
                } else {
                    mmx4_pc_xa_stops++;
                    mmx4_pc_xa_stop_sample = mmx4_pc_replay_consumed();
                    func_80016F0C();
                }
            }
            return;
        }
#endif
        if ((temp_s2 == D_80141BD4) && ((D_8013955C = 1, temp_v0 = CdLastCom(), (temp_v0 == 0x1B)) || (temp_v0 == 0x11)) && (CdSync(1, D_80139554) == temp_s2)) {
            if (temp_v0 == 0x11) {
                temp_v0_2 = CdPosToInt(D_80139554 + 5);
                D_8013953C = temp_v0_2;
                if ((D_80139544 - 8) < temp_v0_2) {
                    if (*(u8*)&D_80139568 == 0) {
                        D_80139530 = 5;
                    } else {
                        func_80016F0C();
                    }
                }
            }
            CdControlF(0x11, 0);
        }
    }
}

void func_800163BC(s32);

void func_800163EC(void);

void func_80016448(u8);

void func_80016F0C();

extern s32 D_800F1AAC;

extern u32 D_80139510;

extern s32 D_80139530;

extern s32 D_80139534;

extern s32 D_80141BD4;

extern u8 D_80171EA9;

s32 func_800169D8(void)
{
    s32 temp_a0;

    if (D_80141BD4 == 2) {
        if (*(u8*)&D_8013952C == 0) {
            D_800F1AB0[D_80139530]();
            if (*(u8*)&D_80141BD0 != 0) {
                if (D_80139510 >= 0 && D_80139510 < 4) {
                    D_80139510 = 0;
                    D_800F1AAC = 1;
                    func_80016F0C();
                    D_80141BD0 = 0;
                } else if (D_800F1AAC != 0) {
                    D_800F1AAC = 0;
                    D_80139510 = (u8)D_80139528 - D_80139534;
                } else {
                    D_800F1AAC = 1;
                }
                func_80016448(D_80139510);
            }
            temp_a0 = D_80171EA9 & 0xFF;
            if ((u8)D_8013956C != temp_a0) {
                D_8013956C = D_80171EA9;
                if (temp_a0 == 1) {
                    func_800163EC();
                } else {
                    func_800163BC(temp_a0);
                }
            }
            return 0;
        }
    }
    return -1;
}

void func_80016B38(void)
{
    D_80141BD0 = 0;
    D_80141BD4 = 0;
    D_80139564 = 0;
}

void func_80016B58(void)
{
    s32 temp_v0;
    u8* ptr = &D_80139554;

    temp_v0 = CdSync(1, ptr);
    if ((temp_v0 == 2) && !(*ptr & 0x40) && (CdControl(CdlReadS, 0, ptr) != 0)) {
        D_80173C84 = 2;
        D_80139530 = temp_v0;
    }
}

void func_80016BDC(void)
{
    if (D_8013955C & D_801441B8) {
        while (CdControl(CdlPause, 0, &D_80139554) == 5)
            ;
        D_80139530 = 3;
        if (D_80139554[0] & 0x10) {
            D_8013952C = 1;
        }
    }
}

void func_80016C5C(void)
{
    s32 status;

    status = CdSync(1, 0);
    if ((status == 2) && (D_80139564 != 0) && (D_801441B8 == 0) && (CdControl(CdlReadS, 0, D_80139554) != 0)) {
        D_8013955C = 0;
        D_80139530 = status;
        if (D_80139554[0] & 0x10) {
            D_8013952C = 1;
        }
    }
}

void func_80016D0C(void)
{
    s32 status;

    status = CdSync(1, 0);
    if (status == 2) {
        if (D_80139564 == status) {
            if (CdControlB(CdlPause, 0, 0) == 0) {
                return;
            }
            SsSetSerialAttr(0, 0, 0);
            func_80016420(0);
            D_80139564 = 0;
        } else {
            SsSetSerialAttr(0, 0, 0);
            func_80016420(0);
        }
        D_80139530 = 0;
    }
}

void func_80016DAC()
{
    s32 var_v0;

    if (CdSync(1, 0) == 2) {
        if (D_801441B0 == 0) {
            var_v0 = CdControl(CdlSeekL, &D_80139514, 0);
        } else {
            var_v0 = CdControlF(CdlSeekL, &D_80139514);
        }
        if (var_v0 != 0) {
            D_80139530 = 1;
        }
        D_80139564 = 2;
    }
}

void func_80016E34()
{
    if (CdSync(1, 0) == CdlComplete && CdControl(CdlSetfilter, &D_80175EE8, 0) != 0) {
        D_80139530 = 5;
    }
}

extern s8 D_8013952C;

extern s32 D_80139530;

extern u8 D_80139554[];

void func_80016E84(void)
{
    u8 sp10;

    if (CdSync(1, 0) == CdlComplete) {
        sp10 = CdlModeSpeed | CdlModeRT | CdlModeSF;
        if (CdControl(CdlSetmode, &sp10, &D_80139554) != 0) {
            VSync(3);
            D_80139530 = 6;
            if (D_80139554[0] & 0x10) {
                D_8013952C = 1;
            }
        }
    }
}

void func_80016F0C()
{
    s32 temp_s0 = D_80141BD4;
    if (temp_s0 == 2) {
        func_80016420(0);
        if (D_80139564 == temp_s0) {
            if (D_8013955C != 0) {
                while (CdControlB(CdlPause, 0, NULL) == 0)
                    ;
            }
        }
        SsSetSerialAttr(0, 0, 0);
        D_80139564 = 0;
        D_80139568 = 0;
        D_80173C84 = 0;
        D_80139530 = 0;
    }
}

void func_80016FB4(s32 arg0)
{
    if (ENGINE_STAGE_ID == 0x10C || D_80173C84 != 0) {
        D_80139534 = arg0;
        D_80141BD0 = 1;
    }
}

void decompress_gfx(u16* src, u16* dest)
{
    s32 var_a3;
    u32 upper_bits;
    u16 var_t0;
    u16 var_t1;
    u32 var_v1;
    s32 arg2;
    u16* copy_src;
start:
    var_t1 = *(src++);

    var_t0 = 0x8000;
    for (var_a3 = 0x10; var_a3 != 0; var_t0 >>= 1, var_a3--) {
        if (!(var_t1 & var_t0)) {
            // v1 assignment probably fake, found by permuter
            *(dest++) = (var_v1 = *(src++));
            continue;
        }
        arg2 = *(src++);
        upper_bits = arg2 & 0xF800;
        if (upper_bits != 0) {
            var_v1 = upper_bits >> 0xB;
            arg2 &= 0x7FF;
        } else {
            var_v1 = *(src++);
        }
        if ((var_v1 | arg2) != 0) {
            if (arg2 == 0) {
                do {
                    *(dest++) = 0;
                    var_v1 -= 1;
                } while (var_v1 != 0);
                continue;
            } else {
                copy_src = dest - arg2;
                do {
                    *(dest++) = *(copy_src++);
                    var_v1 -= 1;
                } while (var_v1 != 0);
            }
        } else {
            return;
        }
    }

    goto start;
}

extern RECT D_800F1AD0;

void func_800170B0(void)
{
    LoadImage(&D_800F1AD0, SP_VRAM_IMAGE);
}

void func_800170E0(void)
{
    need_palette_load |= 1;
}

INCLUDE_ASM("main/nonmatchings/323C", func_80017100);

INCLUDE_ASM("main/nonmatchings/323C", func_80017268);

void func_80017340(void)
{
    u8 start;
    s8 end;
    u8 var_v0;

    SP_PRIM_CURSOR = temp1[SP_DRAW_BUFFER].data;
    SP_DRAW_MODE_CURSOR = temp2[SP_DRAW_BUFFER].data;
    SP_AUX_CURSOR = &temp1[SP_DRAW_BUFFER];

    func_80017E84();

    if (engine_obj.cur_character == CHARACTER_X) {
        end = 10;
    } else {
        end = 8;
    }

    if (engine_obj.cur_character == CHARACTER_X) {
        func_800175AC(0x14);
        func_800175AC(0);
        func_800175AC(1);
        if (bar_object.unk16[1] != 0) {
            func_800175AC(0x15);
            func_800175AC(2);
            func_800175AC(3);
        }
    }

    if (engine_obj.cur_character == CHARACTER_X) {
        start = 2;
    } else {
        start = 0;
    }

    while (start < end) {
        if (bar_object.unk16[start] != 0) {
            func_800175AC(start + 0x14);
            func_800175AC(start * 2);
            func_800175AC(start * 2 + 1);
        }
        start++;
    }

    if (bar_object.unk20 != 0) {
        func_800175AC(0x23);
    }
    if (bar_object.unk21 != 0) {
        func_800175AC(0x24);
    }
    if (bar_object.unk22 != 0) {
        func_800175AC(0x25);
    }
    func_800175AC(0x1F);
    if (bar_object.unk25 != 0) {
        func_800175AC(0x26);
    }
    func_800175AC(0x1E);
    func_800175AC(0x20);
    if (engine_obj.stage > 0 && engine_obj.stage < 9) {
        if (engine_obj.cur_character == CHARACTER_X) {
            var_v0 = bar_object.unk16[engine_obj.stage + 1];
        } else {
            var_v0 = bar_object.unk16[D_800F1C0F[engine_obj.stage]];
        }
        if (var_v0 != 0) {
            func_800175AC(0x21);
        }
    }
    func_800175AC(0x22);
    func_800179BC();
    func_80017F2C();
}

INCLUDE_ASM("main/nonmatchings/323C", func_800175AC);

INCLUDE_ASM("main/nonmatchings/323C", func_800179BC);

INCLUDE_ASM("main/nonmatchings/323C", func_80017E84);

INCLUDE_ASM("main/nonmatchings/323C", func_80017F2C);

// general movie playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("main/nonmatchings/323C", func_80018000);
#else
void func_80018000(s32 temp)
{
    asm(".rept 184 ; nop ; .endr");
}
#endif

// capcom logo playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("main/nonmatchings/323C", func_800182E8);
#else
void func_800182E8(void)
{
    asm(".rept 194 ; nop ; .endr");
}
#endif

void Set24BitDisp(s32 w, s32 h)
{
    RECT rect;
    old_dispenv[0] = draw_infos[0].dispenv;
    old_dispenv[1] = draw_infos[1].dispenv;
    ResetGraph(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = 480;
    rect.h = 480;
    VSync(0);
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0, w, h);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 240, w, h);
    draw_infos[1].dispenv.isrgb24 = 1;
    draw_infos[0].dispenv.isrgb24 = 1;
    draw_infos[1].dispenv.isinter = 0;
    draw_infos[0].dispenv.isinter = 0;
}

INCLUDE_ASM("main/nonmatchings/323C", func_80018788);

extern s32 func_80013614(s32, s32*);

extern void func_80018788(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_80018AD0(
    s32 arg0,
    s32 arg1,
    s32 arg2,
    s32 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6,
    s32 arg7,
    s32 arg8,
    s32 arg9)
{
    s32 local;

    func_80018788(
        func_80013614(arg0, &local),
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7,
        arg8,
        arg9);
}

INCLUDE_ASM("main/nonmatchings/323C", func_80018B88);

void func_80018E50(void)
{
    u8 sp10 = 0x80;
    func_800192F8();
    while (CdControlB(CdlPause, 0, NULL) == 0)
        ;
    VSync(0);
    CdDataCallback(0);
    CdReadyCallback(0);
    DecDCToutCallback(0);
    StUnSetRing();
    while (CdReset(0) == 0)
        ;
    VSync(3);
    while (CdControl(CdlSetmode, &sp10, 0) == 0)
        ;
    VSync(3);
}

void func_80018EEC(void)
{
    do {

    } while (D_80139634 != 0);
    D_801395E4 = D_801395E8;
}

INCLUDE_ASM("main/nonmatchings/323C", func_80018F18);

void func_80018FD0(u32 arg0)
{
    D_800F1D8C = arg0;
    if (D_80171EA9 != 0) {
        D_80139644.val0 = arg0;
        D_80139644.val1 = 0;
        D_80139644.val2 = arg0;
        D_80139644.val3 = 0;
    } else {
        D_80139644.val0 = arg0 >> 1; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = arg0 >> 1; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = arg0 >> 1; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = arg0 >> 1; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

void func_80019058(s8 arg0)
{
    u32 temp_v0;

    D_80171EA9 = arg0;
    if (arg0 & 0xFF) {
        D_80139644.val1 = 0;
        D_80139644.val3 = 0;
        D_80139644.val0 = D_800F1D8C;
        D_80139644.val2 = D_800F1D8C;
    } else {
        temp_v0 = D_800F1D8C >> 1;
        D_80139644.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

extern s32 D_80139614;

void func_800190F0(s32 arg0)
{
    D_80139614 = arg0;
}

extern s32 D_801395E4;

extern s32 D_80139614;

extern RECT D_80139618;

extern u32* D_80139620;

extern s32 D_80139624;

extern s32 D_80139628;

extern u32 D_8013962C;

extern u32 D_80139630;

extern s32 D_801410B8;

void func_80019100(void)
{
    u32* temp_a0;

    D_8013962C += 1;
    if (D_801410B8 != 0) {
        StCdInterrupt();
        D_801410B8 = 0;
    }
    if (D_80139614 == 0) {
        LoadImage(&D_80139618, D_80139620);
    }
    if ((u32)D_8013962C < (u32)D_80139630) {
        D_80139618.x += (D_801395E4 ? 0x18 : 0x10);
        temp_a0 = &D_80139620[D_80139624];
        D_80139620 = temp_a0;
        DecDCTout(temp_a0, D_80139628);
        D_80139634 = 1;
        return;
    }
    D_80139634 = 0;
}

extern s32 D_80139610;

void func_80019208(void)
{
    D_80139610 += 1;
}

void func_80019228(void)
{
    s32 temp_v0;
    s32 var_s0;

    SsSetSerialAttr(0, 0, 1);
    var_s0 = 0;
    if (D_80171EA9 != 0) {
        do {
            D_80139644.val0 = var_s0;
            D_80139644.val1 = 0;
            D_80139644.val2 = var_s0;
            D_80139644.val3 = 0;
            CdMix(&D_80139644);
            var_s0 += 2;
        } while (D_800F1D8C >= var_s0);
        return;
    }
    do {
        temp_v0 = var_s0 / 2;
        D_80139644.val0 = temp_v0;
        D_80139644.val1 = temp_v0;
        D_80139644.val2 = temp_v0;
        D_80139644.val3 = temp_v0;
        CdMix(&D_80139644);
        var_s0 += 2;
    } while (D_800F1D8C >= var_s0);
}

void func_800192F8(void)
{
    s32 temp_v0;
    s32 var_s0;

    SsSetSerialAttr(0, 0, 0);
    if (D_80171EA9 != 0) {
        var_s0 = D_800F1D8C;
        if (var_s0 >= 0) {
            do {
                D_80139644.val0 = var_s0;
                D_80139644.val1 = 0;
                D_80139644.val2 = var_s0;
                D_80139644.val3 = 0;
                CdMix(&D_80139644);
                var_s0 -= 2;
            } while (var_s0 >= 0);
        }
    } else {
        var_s0 = D_800F1D8C;
        if (var_s0 >= 0) {
            do {
                temp_v0 = var_s0 / 2;
                D_80139644.val0 = temp_v0;
                D_80139644.val1 = temp_v0;
                D_80139644.val2 = temp_v0;
                D_80139644.val3 = temp_v0;
                CdMix(&D_80139644);
                var_s0 -= 2;
            } while (var_s0 >= 0);
        }
    }
}

#ifdef VERSION_JP
#define ARCHIVE_PATH(path) "E:\\ROCKX4\\JAPAN\\" path
#else
#define ARCHIVE_PATH(path) "E:\\ROCKX4\\USA\\" path
#endif

struct ArchivePathData D_800EE54C = {
    { 0x10, 0x16, 0x20, 0x26, 0x30, 0x36, 0x40, 0x46, 0x50, 0x56, 0x60, 0x66 },
    {
        ARCHIVE_PATH("ARC\\CAPCOM.ARC"),
        ARCHIVE_PATH("ARC\\COL00_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL00_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL00_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL00_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL01_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL01_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL01_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL01_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL02_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL02_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL02_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL02_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL03_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL03_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL03_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL03_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL04_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL04_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL04_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL04_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL05_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL05_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL05_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL05_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL06_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL06_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL06_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL06_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL07_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL07_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL07_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL07_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL08_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL08_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL08_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL08_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL09_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL09_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0A_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL0A_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0B_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL0B_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0B_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL0B_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0C_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL0C_0Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0C_1X.ARC"),
        ARCHIVE_PATH("ARC\\COL0C_1Z.ARC"),
        ARCHIVE_PATH("ARC\\COL0D_0X.ARC"),
        ARCHIVE_PATH("ARC\\COL0D_0Z.ARC"),
#ifdef VERSION_JP
        ARCHIVE_PATH("ARC\\COL0E_00.ARC"),
        ARCHIVE_PATH("ARC\\COL0E_01.ARC"),
        ARCHIVE_PATH("ARC\\COL0E_U0.ARC"),
        ARCHIVE_PATH("ARC\\COL0F_00.ARC"),
        ARCHIVE_PATH("ARC\\COL0F_01.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_1.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_2.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_3.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_4.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_5.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_6.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_7.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1_8.ARC"),
#else
        ARCHIVE_PATH("ARC\\COL0E_U0.ARC"),
        ARCHIVE_PATH("ARC\\COL0E_U1.ARC"),
        ARCHIVE_PATH("ARC\\COL0F_U0.ARC"),
        ARCHIVE_PATH("ARC\\COL0F_U1.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U1.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U2.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U3.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U4.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U5.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U6.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U7.ARC"),
        ARCHIVE_PATH("ARC\\COLD_1U8.ARC"),
#endif
        ARCHIVE_PATH("ARC\\FONT8X8.ARC"),
#ifdef VERSION_JP
        ARCHIVE_PATH("ARC\\LOAD.ARC"),
#else
        ARCHIVE_PATH("ARC\\LOAD_U.ARC"),
#endif
        ARCHIVE_PATH("ARC\\MOJIPAT.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE1.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE2.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE3.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE4.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE5.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE6.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE7.ARC"),
        ARCHIVE_PATH("ARC\\ONPARE8.ARC"),
#ifdef VERSION_JP
        ARCHIVE_PATH("ARC\\PL00.ARC"),
        ARCHIVE_PATH("ARC\\PL00SEP.ARC"),
        ARCHIVE_PATH("ARC\\PL01.ARC"),
        ARCHIVE_PATH("ARC\\PL01SEP.ARC"),
        ARCHIVE_PATH("ARC\\PL02.ARC"),
#else
        ARCHIVE_PATH("ARC\\PL00SEP.ARC"),
        ARCHIVE_PATH("ARC\\PL00_U.ARC"),
        ARCHIVE_PATH("ARC\\PL01SEP.ARC"),
        ARCHIVE_PATH("ARC\\PL01_U.ARC"),
        ARCHIVE_PATH("ARC\\PL02_U.ARC"),
        ARCHIVE_PATH("ARC\\PLDEMO.ARC"),
#endif
        ARCHIVE_PATH("ARC\\PLDEMO00.ARC"),
        ARCHIVE_PATH("ARC\\PLDEMO01.ARC"),
        ARCHIVE_PATH("ARC\\PLDEMO02.ARC"),
        ARCHIVE_PATH("ARC\\PLDEMO03.ARC"),
        ARCHIVE_PATH("ARC\\ST00_00.ARC"),
        ARCHIVE_PATH("ARC\\ST00_01.ARC"),
        ARCHIVE_PATH("ARC\\ST01_00.ARC"),
        ARCHIVE_PATH("ARC\\ST01_01.ARC"),
        ARCHIVE_PATH("ARC\\ST02_00.ARC"),
        ARCHIVE_PATH("ARC\\ST02_01.ARC"),
        ARCHIVE_PATH("ARC\\ST03_00.ARC"),
        ARCHIVE_PATH("ARC\\ST03_01.ARC"),
        ARCHIVE_PATH("ARC\\ST04_00.ARC"),
        ARCHIVE_PATH("ARC\\ST04_01.ARC"),
        ARCHIVE_PATH("ARC\\ST05_00.ARC"),
        ARCHIVE_PATH("ARC\\ST05_01.ARC"),
        ARCHIVE_PATH("ARC\\ST06_00.ARC"),
        ARCHIVE_PATH("ARC\\ST06_01.ARC"),
        ARCHIVE_PATH("ARC\\ST07_00.ARC"),
        ARCHIVE_PATH("ARC\\ST07_01.ARC"),
        ARCHIVE_PATH("ARC\\ST08_00.ARC"),
        ARCHIVE_PATH("ARC\\ST08_01.ARC"),
        ARCHIVE_PATH("ARC\\ST09_00.ARC"),
        ARCHIVE_PATH("ARC\\ST0A_00.ARC"),
#ifndef VERSION_JP
        ARCHIVE_PATH("ARC\\ST0B_00.ARC"),
#endif
        ARCHIVE_PATH("ARC\\ST0B_01.ARC"),
        ARCHIVE_PATH("ARC\\ST0B_0X.ARC"),
        ARCHIVE_PATH("ARC\\ST0B_0Z.ARC"),
        ARCHIVE_PATH("ARC\\ST0C_00.ARC"),
        ARCHIVE_PATH("ARC\\ST0C_01.ARC"),
#ifndef VERSION_JP
        ARCHIVE_PATH("ARC\\ST0C_U1.ARC"),
#endif
        ARCHIVE_PATH("ARC\\ST0D_0X.ARC"),
        ARCHIVE_PATH("ARC\\ST0D_0Z.ARC"),
#ifdef VERSION_JP
        ARCHIVE_PATH("ARC\\ST0E_00.ARC"),
        ARCHIVE_PATH("ARC\\ST0E_01.ARC"),
        ARCHIVE_PATH("ARC\\ST0E_U0.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_01.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_0X.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_0Z.ARC"),
#else
        ARCHIVE_PATH("ARC\\ST0E_U0.ARC"),
        ARCHIVE_PATH("ARC\\ST0E_U1.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_U1.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_UX.ARC"),
        ARCHIVE_PATH("ARC\\ST0F_UZ.ARC"),
#endif
        ARCHIVE_PATH("ARC\\ST0_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST1_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST2_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST3_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST4_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST5_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST6_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST7_1_1.ARC"),
        ARCHIVE_PATH("ARC\\ST8_1_1.ARC"),
        ARCHIVE_PATH("ARC\\STA_0_1.ARC"),
        ARCHIVE_PATH("ARC\\STB_1_1.ARC"),
        ARCHIVE_PATH("ARC\\STC_1_1.ARC"),
#ifdef VERSION_JP
        ARCHIVE_PATH("ARC\\STD_1_1.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_2.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_3.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_4.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_5.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_6.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_7.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_8.ARC"),
#else
        ARCHIVE_PATH("ARC\\STD_1_1U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_2U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_3U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_4U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_5U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_6U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_7U.ARC"),
        ARCHIVE_PATH("ARC\\STD_1_8U.ARC"),
#endif
        ARCHIVE_PATH("STR\\CAPCOM20.STR"),
#ifdef VERSION_JP
        ARCHIVE_PATH("STR\\OP.STR"),
        ARCHIVE_PATH("STR\\X1.STR"),
        ARCHIVE_PATH("STR\\X2.STR"),
        ARCHIVE_PATH("STR\\X3.STR"),
        ARCHIVE_PATH("STR\\X4.STR"),
        ARCHIVE_PATH("STR\\Z1.STR"),
        ARCHIVE_PATH("STR\\Z2.STR"),
        ARCHIVE_PATH("STR\\Z3.STR"),
        ARCHIVE_PATH("STR\\Z4.STR"),
        ARCHIVE_PATH("STR\\Z5.STR"),
        ARCHIVE_PATH("XA\\BGM1.XA"),
#else
        ARCHIVE_PATH("STR\\OP_U.STR"),
        ARCHIVE_PATH("STR\\X1_U.STR"),
        ARCHIVE_PATH("STR\\X2_U.STR"),
        ARCHIVE_PATH("STR\\X3_U.STR"),
        ARCHIVE_PATH("STR\\X4_U.STR"),
        ARCHIVE_PATH("STR\\Z1_U.STR"),
        ARCHIVE_PATH("STR\\Z2_U.STR"),
        ARCHIVE_PATH("STR\\Z3_U.STR"),
        ARCHIVE_PATH("STR\\Z4_U.STR"),
        ARCHIVE_PATH("STR\\Z5_U.STR"),
        ARCHIVE_PATH("XA\\BGM1_U.XA"),
#endif
        ARCHIVE_PATH("XA\\BGM2.XA"),
        ARCHIVE_PATH("XA\\BGM3.XA"),
        ARCHIVE_PATH("XA\\BGM4.XA"),
#ifdef VERSION_JP
        ARCHIVE_PATH("XA\\BGM5.XA"),
        ARCHIVE_PATH("XA\\BOSSINT.XA"),
        ARCHIVE_PATH("XA\\VOICE1.XA"),
        ARCHIVE_PATH("XA\\VOICE2.XA"),
        ARCHIVE_PATH("XA\\VOICE3.XA"),
        ARCHIVE_PATH("XA\\VOICE4.XA"),
        ARCHIVE_PATH("XA\\VOICE5.XA"),
        "E:\\ROCKX4\\0616\\PROG\\SLPS_009.01",
        "E:\\PSX\\00901.CNF",
#else
        ARCHIVE_PATH("XA\\BGM5_U.XA"),
        ARCHIVE_PATH("XA\\BOSINT_U.XA"),
        ARCHIVE_PATH("XA\\VOICE1_U.XA"),
        ARCHIVE_PATH("XA\\VOICE2_U.XA"),
        ARCHIVE_PATH("XA\\VOICE3_U.XA"),
        ARCHIVE_PATH("XA\\VOICE4_U.XA"),
        ARCHIVE_PATH("XA\\VOICE5_U.XA"),
        "E:\\PSX\\00561.CNF",
        "E:\\ROCKX4\\0801US\\PROG\\ROCKX4.EXE",
#endif
        "E:\\PSX\\ZNULL.DAT",
    },
};

#ifdef VERSION_JP
struct Unk5 D_800F0E18[] = {
#include "data/archive_data.jp.inc"
};
#else
struct Unk5 D_800F0E18[] = {
    { (s32)0x0000001Cu, (s32)0x00002000u, (s32)0x00000002u },
    { (s32)0x00000020u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000023u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000026u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000029u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000002Cu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000002Fu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000032u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000035u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000038u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000003Bu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000003Eu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000041u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000044u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000047u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000004Au, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000004Du, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000050u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000053u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000056u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000059u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000005Cu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000005Fu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000062u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000065u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000068u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000006Bu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000006Eu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000071u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000074u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000077u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000007Au, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000007Du, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000080u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000083u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000086u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000089u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000008Cu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000008Fu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000092u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000095u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x00000098u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000009Bu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x0000009Eu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000A1u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000A4u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000A7u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000AAu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000ADu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000B0u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000B3u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000B6u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000B9u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000BCu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000BFu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000C2u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000C5u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000C8u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000CBu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000CEu, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000D1u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000D4u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000D7u, (s32)0x00001800u, (s32)0x00000001u },
    { (s32)0x000000DAu, (s32)0x00002000u, (s32)0x00000002u },
    { (s32)0x000000DEu, (s32)0x00018800u, (s32)0x00000003u },
    { (s32)0x0000010Fu, (s32)0x00002C9Cu, (s32)0x00000010u },
    { (s32)0x00000115u, (s32)0x0002A800u, (s32)0x00000004u },
    { (s32)0x0000016Au, (s32)0x0003D800u, (s32)0x00000004u },
    { (s32)0x000001E5u, (s32)0x0002F000u, (s32)0x00000004u },
    { (s32)0x00000243u, (s32)0x00039800u, (s32)0x00000004u },
    { (s32)0x000002B6u, (s32)0x0003D000u, (s32)0x00000004u },
    { (s32)0x00000330u, (s32)0x00038800u, (s32)0x00000004u },
    { (s32)0x000003A1u, (s32)0x00031000u, (s32)0x00000004u },
    { (s32)0x00000403u, (s32)0x00035800u, (s32)0x00000004u },
    { (s32)0x0000046Eu, (s32)0x000004E8u, (s32)0x00000008u },
    { (s32)0x0000046Fu, (s32)0x000C2800u, (s32)0x00000010u },
    { (s32)0x000005F4u, (s32)0x000004E8u, (s32)0x00000008u },
    { (s32)0x000005F5u, (s32)0x000B5000u, (s32)0x00000010u },
    { (s32)0x0000075Fu, (s32)0x000C2800u, (s32)0x00000010u },
    { (s32)0x000008E4u, (s32)0x00002000u, (s32)0x00000E10u },
    { (s32)0x000008E8u, (s32)0x00002000u, (s32)0x00000E10u },
    { (s32)0x000008ECu, (s32)0x00002000u, (s32)0x00000E10u },
    { (s32)0x000008F0u, (s32)0x00002000u, (s32)0x00000E10u },
    { (s32)0x000008F4u, (s32)0x00002000u, (s32)0x00000E10u },
    { (s32)0x000008F8u, (s32)0x000B0000u, (s32)0x0000000Cu },
    { (s32)0x00000A58u, (s32)0x00080000u, (s32)0x0000000Cu },
    { (s32)0x00000B58u, (s32)0x0009B800u, (s32)0x0000000Cu },
    { (s32)0x00000C8Fu, (s32)0x00099800u, (s32)0x0000000Cu },
    { (s32)0x00000DC2u, (s32)0x000B2000u, (s32)0x0000000Cu },
    { (s32)0x00000F26u, (s32)0x000A3000u, (s32)0x0000000Cu },
    { (s32)0x0000106Cu, (s32)0x0008D800u, (s32)0x0000000Cu },
    { (s32)0x00001187u, (s32)0x00093000u, (s32)0x0000000Cu },
    { (s32)0x000012ADu, (s32)0x00090000u, (s32)0x0000000Au },
    { (s32)0x000013CDu, (s32)0x000A6800u, (s32)0x0000000Cu },
    { (s32)0x0000151Au, (s32)0x0006C000u, (s32)0x0000000Au },
    { (s32)0x000015F2u, (s32)0x00084800u, (s32)0x0000000Cu },
    { (s32)0x000016FBu, (s32)0x00087000u, (s32)0x0000000Cu },
    { (s32)0x00001809u, (s32)0x0008A800u, (s32)0x0000000Au },
    { (s32)0x0000191Eu, (s32)0x0009B800u, (s32)0x0000000Bu },
    { (s32)0x00001A55u, (s32)0x00064000u, (s32)0x0000000Au },
    { (s32)0x00001B1Du, (s32)0x00080000u, (s32)0x0000000Bu },
    { (s32)0x00001C1Du, (s32)0x000A2800u, (s32)0x0000000Cu },
    { (s32)0x00001D62u, (s32)0x00051000u, (s32)0x0000000Au },
    { (s32)0x00001E04u, (s32)0x00071800u, (s32)0x0000000Au },
    { (s32)0x00001EE7u, (s32)0x0005C800u, (s32)0x00000008u },
    { (s32)0x00001FA0u, (s32)0x00095800u, (s32)0x0000000Cu },
    { (s32)0x000020CBu, (s32)0x0007A000u, (s32)0x0000000Au },
    { (s32)0x000021BFu, (s32)0x00075000u, (s32)0x0000000Au },
    { (s32)0x000022A9u, (s32)0x00072800u, (s32)0x0000000Cu },
    { (s32)0x0000238Eu, (s32)0x0007F800u, (s32)0x0000000Cu },
    { (s32)0x0000248Du, (s32)0x0007F800u, (s32)0x0000000Cu },
    { (s32)0x0000258Cu, (s32)0x00043800u, (s32)0x0000000Au },
    { (s32)0x00002613u, (s32)0x00042800u, (s32)0x0000000Au },
    { (s32)0x00002698u, (s32)0x0004D000u, (s32)0x00000009u },
    { (s32)0x00002732u, (s32)0x00035000u, (s32)0x00000009u },
    { (s32)0x0000279Cu, (s32)0x0001F800u, (s32)0x00000007u },
    { (s32)0x000027DBu, (s32)0x00048000u, (s32)0x0000000Au },
    { (s32)0x0000286Bu, (s32)0x00044800u, (s32)0x0000000Au },
    { (s32)0x000028F4u, (s32)0x00041800u, (s32)0x00000004u },
    { (s32)0x00002977u, (s32)0x00026000u, (s32)0x00000003u },
    { (s32)0x000029C3u, (s32)0x00036000u, (s32)0x00000003u },
    { (s32)0x00002A2Fu, (s32)0x0002B800u, (s32)0x00000003u },
    { (s32)0x00002A86u, (s32)0x00034000u, (s32)0x00000003u },
    { (s32)0x00002AEEu, (s32)0x00038000u, (s32)0x00000003u },
    { (s32)0x00002B5Eu, (s32)0x00032800u, (s32)0x00000003u },
    { (s32)0x00002BC3u, (s32)0x0002C800u, (s32)0x00000003u },
    { (s32)0x00002C1Cu, (s32)0x00032000u, (s32)0x00000003u },
    { (s32)0x00002C80u, (s32)0x00040000u, (s32)0x00000004u },
    { (s32)0x00002D00u, (s32)0x00040800u, (s32)0x00000004u },
    { (s32)0x00002D81u, (s32)0x0004D000u, (s32)0x00000004u },
    { (s32)0x00002E1Bu, (s32)0x00040800u, (s32)0x00000007u },
    { (s32)0x00002E9Cu, (s32)0x0004E000u, (s32)0x00000007u },
    { (s32)0x00002F38u, (s32)0x00041800u, (s32)0x00000007u },
    { (s32)0x00002FBBu, (s32)0x0004B800u, (s32)0x00000007u },
    { (s32)0x00003052u, (s32)0x0004A000u, (s32)0x00000007u },
    { (s32)0x000030E6u, (s32)0x0004C800u, (s32)0x00000007u },
    { (s32)0x0000317Fu, (s32)0x0003F800u, (s32)0x00000007u },
    { (s32)0x000031FEu, (s32)0x0004A000u, (s32)0x00000007u },
    { (s32)0x00003293u, (s32)0x002ACF20u, (s32)0x80420100u },
    { (s32)0x00003744u, (s32)0x01E217A0u, (s32)0x00480100u },
    { (s32)0x00006C19u, (s32)0x0174E0A0u, (s32)0x00480100u },
    { (s32)0x000094F6u, (s32)0x01D1F200u, (s32)0x00480100u },
    { (s32)0x0000C806u, (s32)0x017D1360u, (s32)0x00480100u },
    { (s32)0x0000F1C9u, (s32)0x01DCC800u, (s32)0x00480100u },
    { (s32)0x00012609u, (s32)0x01523200u, (s32)0x00480100u },
    { (s32)0x00014B19u, (s32)0x01B69200u, (s32)0x00480100u },
    { (s32)0x00017B29u, (s32)0x01650400u, (s32)0x00480100u },
    { (s32)0x0001A249u, (s32)0x046E5A00u, (s32)0x00480100u },
    { (s32)0x00021E99u, (s32)0x016E6D00u, (s32)0x00480100u },
    { (s32)0x000246C2u, (s32)0x039D9E00u, (s32)0x01640001u },
    { (s32)0x0002AC32u, (s32)0x03418300u, (s32)0x01640001u },
    { (s32)0x0003078Au, (s32)0x02775600u, (s32)0x01640001u },
    { (s32)0x00034CBAu, (s32)0x016FDA00u, (s32)0x01640001u },
    { (s32)0x0003750Au, (s32)0x00370900u, (s32)0x01640001u },
    { (s32)0x00037B12u, (s32)0x004DD900u, (s32)0x01640001u },
    { (s32)0x0003839Au, (s32)0x000E8B00u, (s32)0x01640001u },
    { (s32)0x00038532u, (s32)0x000F1D00u, (s32)0x01640001u },
    { (s32)0x000386DAu, (s32)0x0013F600u, (s32)0x01640001u },
    { (s32)0x0003890Au, (s32)0x0015F500u, (s32)0x01640001u },
    { (s32)0x00038B72u, (s32)0x0017F400u, (s32)0x01640001u },
    { (s32)0x00038E12u, (s32)0x00000044u, (s32)0x544F4F42u },
    { (s32)0x00038E13u, (s32)0x00120000u, (s32)0x582D5350u },
    { (s32)0x00039053u, (s32)0x02353F20u, (s32)0x00000000u },
};
#endif

u8** D_800F15BC[22] = {
#ifdef MMX4_PC
    &pc_archive_slots[0],
    &pc_archive_slots[1],
    &pc_archive_slots[2],
    &pc_archive_slots[3],
    &D_80141F00,
    &pc_archive_slots[5],
    &D_80141F00,
    &D_80141F00,
    &D_80141F00,
    &pc_archive_slots[9],
    &pc_archive_slots[10],
    &pc_archive_slots[11],
    (u8**)&D_801406A8,
    &pc_archive_slots[13],
    &cur_draw_info_drawenv,
    &cur_draw_info_dispenv_screen_w,
    &pc_archive_slots[16],
    &pc_archive_slots[17],
    &pc_archive_slots[18],
    &pc_archive_slots[19],
    &pc_archive_slots[20],
    &pc_archive_slots[21],
#else
    (u8**)0x1F800008,
    (u8**)0x1F80000C,
    (u8**)0x1F800014,
    (u8**)0x1F80001C,
    &D_80141F00,
    (u8**)0x1F800028,
    &D_80141F00,
    &D_80141F00,
    &D_80141F00,
    (u8**)0x1F800024,
    (u8**)0x1F800020,
    (u8**)0x1F80002C,
    (u8**)&D_801406A8,
    (u8**)0x1F800030,
    &cur_draw_info_drawenv,
    &cur_draw_info_dispenv_screen_w,
    (u8**)0x1F800034,
    (u8**)0x1F800038,
    (u8**)0x1F80003C,
    (u8**)0x1F800040,
    (u8**)0x1F800044,
    (u8**)0x1F800048,
#endif
};

#ifdef VERSION_JP
#define CD_AUDIO_FIRST_TRACK 0x4C
#define CD_AUDIO_LAST_TRACK 0x4E
#else
#define CD_AUDIO_FIRST_TRACK 0x4A
#define CD_AUDIO_LAST_TRACK 0x4C
#endif

struct CdImageOrigin D_800F1614[11] = {
    { 0x140, 0x100 },
    { 0x3C0, 0x100 },
    { 0x180, 0x000 },
    { 0x240, 0x000 },
    { 0x280, 0x000 },
    { 0x2C0, 0x000 },
    { 0x140, 0x0B0 },
    { 0x340, 0x100 },
    { 0x380, 0x100 },
    { 0x1C0, 0x000 },
    { 0x200, 0x000 },
};

void (*D_800F1640[3])(void) = {
    func_800148E4,
    func_800148EC,
    func_80014968,
};

u8 D_800F164C[4] = { 1, 2, 0, 0 };

s16 D_800F1650[2] = { 1, 0 };

u8 D_800F1654[4] = { CD_AUDIO_FIRST_TRACK, CD_AUDIO_LAST_TRACK, 0, 0 };

RECT D_800F1658 = { 0, 480, 256, 8 };

union MainPaletteData D_800F1660 = { .raw = {
                                         0x00, 0x00, 0x21, 0x84, 0x63, 0x8c, 0xa5, 0x94, 0x08, 0xa1, 0x6b, 0xad, 0xad, 0xb5, 0x10, 0xc2,
                                         0x31, 0xc6, 0x73, 0xce, 0xd6, 0xda, 0xf7, 0xde, 0x39, 0xe7, 0x7b, 0xef, 0xbd, 0xf7, 0xff, 0xff,
                                         0x00, 0x00, 0x22, 0x80, 0x63, 0x80, 0xa5, 0x84, 0xc7, 0x84, 0x09, 0x85, 0x6d, 0x89, 0xaf, 0x8d,
                                         0xf1, 0x8d, 0x13, 0x8e, 0x55, 0x92, 0x97, 0x92, 0xb9, 0x92, 0xfb, 0x96, 0x3d, 0x97, 0x5f, 0x97,
#ifdef VERSION_JP
                                         0x00, 0x00, 0xb5, 0xce, 0x31, 0xc6, 0x6b, 0xad, 0x08, 0xa1, 0x6e, 0xe6, 0xcc, 0xc5, 0xb5, 0xff,
                                         0x6e, 0xff, 0xe6, 0xfe, 0x20, 0xfe, 0x40, 0xf5, 0xc0, 0xd8, 0x71, 0xe4, 0x53, 0xa0, 0x9f, 0x80,
                                         0x00, 0x00, 0xb5, 0xce, 0x31, 0xc6, 0xad, 0xb1, 0x08, 0xa1, 0xa5, 0x90, 0x3e, 0xab, 0xb9, 0x83,
                                         0x9a, 0x82, 0xdb, 0x81, 0x3d, 0x81, 0x9f, 0x80, 0x91, 0x99, 0x55, 0x89, 0xce, 0x88, 0x00, 0x80,
#else
                                         0x00, 0x00, 0x83, 0xf8, 0xc4, 0xfc, 0x48, 0xfd, 0xcd, 0xfd, 0x31, 0xfe, 0xb5, 0xfa, 0xf7, 0xfa,
                                         0x9c, 0xf7, 0xc7, 0xa8, 0x4a, 0xb9, 0x52, 0xd2, 0x41, 0xbc, 0xa5, 0xc8, 0x08, 0xad, 0x28, 0xd9,
                                         0x00, 0x00, 0x5f, 0x80, 0x1f, 0x81, 0xde, 0x85, 0x9e, 0x86, 0xfe, 0x96, 0xbf, 0xd7, 0xbe, 0xfb,
                                         0xc7, 0xa8, 0x4a, 0xb9, 0x74, 0xd2, 0x62, 0xcc, 0xab, 0xd8, 0xf3, 0xe8, 0xde, 0x91, 0x19, 0xb2,
#endif
                                         0x00, 0x00, 0xde, 0xfb, 0x7a, 0x91, 0xfc, 0x81, 0x5e, 0x82, 0xdf, 0x82, 0x58, 0x81, 0x00, 0x00,
                                         0x97, 0xfb, 0x60, 0xfa, 0xa0, 0xed, 0x40, 0xd9, 0x00, 0xc9, 0xc0, 0xbc, 0xde, 0x83, 0xda, 0x82,
                                         0x00, 0x00, 0x00, 0x80, 0x21, 0x84, 0x63, 0x8c, 0x08, 0xa1, 0x4a, 0xa9, 0x6b, 0xad, 0x8c, 0xb1,
                                         0xef, 0xbd, 0x31, 0xc6, 0xb5, 0xd6, 0x18, 0xe3, 0x5a, 0xeb, 0x9c, 0xf3, 0xff, 0xff, 0x67, 0x8c,
                                         0x00, 0x00, 0xde, 0xfb, 0x00, 0xc1, 0xe0, 0xbc, 0xc0, 0xb8, 0xc0, 0xb4, 0xa0, 0xb0, 0xa0, 0xac,
                                         0x80, 0xa8, 0x80, 0xa4, 0x60, 0xa0, 0x60, 0x9c, 0x40, 0x98, 0x40, 0x98, 0x91, 0xfb, 0xe6, 0xcd,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

RECT D_800F1860 = { 0, 480, 256, 1 };

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

u16 D_800F1868[18] = {
    0,
    1,
    0,
    1,
    0,
    1,
    2,
    0,
    1,
    0,
    1,
    0,
    1,
    2,
    0,
    1,
    0,
    0,
};

u16 D_800F188C[] = {
    0x8000,
    JP_VALUE(0x0c8a, 0x0cc7),
    0x8000,
    0x0cae,
    0x8000,
    0x0c55,
    0x8000,
    0x0c02,
    0x8000,
    0x0c01,
    0x8000,
    0x0bd9,
    0x8000,
    0x0bae,
    0x8000,
    0x0ba5,
    0x8000,
    0x0b6b,
    0x8000,
    0x0af2,
    0x8000,
    0x0aac,
    0x8000,
    0x0a82,
    0x8000,
    0x0a03,
    0x8000,
    0x09d8,
    0x8000,
    0x0951,
    0x8000,
    0x090e,
    0x8000,
    0x08a6,
    0x8000,
    0x0839,
    0x8000,
    0x07e3,
    0x8000,
    0x06cd,
    0x8000,
    0x067e,
    0x8000,
    0x0644,
    0x8000,
    0x05ff,
    0x8000,
    0x0552,
    0x8000,
    0x050a,
    0x8000,
    0x04bb,
    0x8000,
    0x0490,
    0x8000,
    0x0478,
    0x8000,
    0x03db,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x8000,
    JP_VALUE(0x00c1, 0x00eb),
    0x8000,
    0x0083,
    0x8000,
    0x007c,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x8000,
    JP_VALUE(0x0030, 0x0012),
    0x8000,
    0x0021,
    0x8000,
    0x0022,
    0x8000,
    0x0025,
    0x8000,
    JP_VALUE(0x0025, 0x0022),
    0x8000,
    0x0033,
    0x8000,
    JP_VALUE(0x0032, 0x0030),
    0x8000,
    JP_VALUE(0x0027, 0x002e),
    0x8000,
    0x0030,
    0x8000,
    JP_VALUE(0x002b, 0x0028),
    0x8000,
    0x002d,
    0x8000,
    0x0032,
    0x8000,
    0x0034,
    0x8000,
    0x0035,
    0x8000,
    0x0032,
    0x8000,
    0x0032,
    0x8000,
    0x0037,
    0x8000,
    0x0038,
    0x8000,
    0x0038,
    0x8000,
    JP_VALUE(0x0026, 0x003c),
    0x8000,
    0x0039,
    0x8000,
    0x003c,
    0x8000,
    JP_VALUE(0x0041, 0x003b),
    0x8000,
    0x0046,
    0x8000,
    JP_VALUE(0x004b, 0x0039),
    0x8000,
    0x003d,
    0x8000,
    JP_VALUE(0x004d, 0x003c),
    0x8000,
    JP_VALUE(0x0033, 0x003a),
    0x8000,
    0x003f,
    0x8000,
    0x003f,
    0x8000,
    0x003e,
    0x8000,
    0x003e,
    0x8000,
    JP_VALUE(0x003a, 0x0040),
    0x8000,
    JP_VALUE(0x0034, 0x0041),
    0x8000,
    JP_VALUE(0x0042, 0x0044),
    0x8000,
    0x004a,
    0x8000,
    JP_VALUE(0x0054, 0x0046),
    0x8000,
    JP_VALUE(0x0048, 0x0047),
    0x8000,
    0x004f,
    0x8000,
    0x0042,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
    0x8000,
    0x0111,
};

const u16* D_800F19E0 = &D_800F188C[0];

const u16* D_800F19E4 = &D_800F188C[16];

const u16* D_800F19E8 = &D_800F188C[32];

const u16* D_800F19EC = &D_800F188C[48];

const u16* D_800F19F0 = &D_800F188C[62];

const u16* D_800F19F4 = &D_800F188C[74];

const u16* D_800F19F8 = &D_800F188C[90];

const u16* D_800F19FC = &D_800F188C[106];

const u16* D_800F1A00 = &D_800F188C[122];

const u16* D_800F1A04 = &D_800F188C[138];

const u16* D_800F1A08 = &D_800F188C[154];

#undef JP_VALUE

#define XA(sequence_, volume_) \
    {                          \
        sequence_, volume_     \
    }

struct XaSequenceData D_800F1A0C = {
    {
        { { XA(0x10, 0x75), XA(0x13, 0x70) }, { XA(0x10, 0x75), XA(0x13, 0x70) } },
        { { XA(0x03, 0x7F), XA(0x03, 0x7F) }, { XA(0x03, 0x7F), XA(0x03, 0x7F) } },
        { { XA(0x0E, 0x7F), XA(0x0E, 0x7F) }, { XA(0x09, 0x7F), XA(0x09, 0x7F) } },
        { { XA(0x06, 0x75), XA(0x06, 0x75) }, { XA(0x06, 0x75), XA(0x06, 0x75) } },
        { { XA(0x11, 0x78), XA(0x11, 0x78) }, { XA(0x11, 0x78), XA(0x11, 0x78) } },
        { { XA(0x12, 0x75), XA(0x12, 0x75) }, { XA(0x12, 0x75), XA(0x12, 0x75) } },
        { { XA(0x0A, 0x7F), XA(0x0A, 0x7F) }, { XA(0x0A, 0x7F), XA(0x0A, 0x7F) } },
        { { XA(0x0C, 0x7F), XA(0x0C, 0x7F) }, { XA(0x0C, 0x7F), XA(0x0C, 0x7F) } },
        { { XA(0x05, 0x7F), XA(0x05, 0x7F) }, { XA(0x05, 0x7F), XA(0x05, 0x7F) } },
        { { XA(0x03, 0x00), XA(0x03, 0x00) }, { XA(0x03, 0x00), XA(0x03, 0x00) } },
        { { XA(0x14, 0x7F), XA(0x14, 0x7F) }, { XA(0x14, 0x7F), XA(0x14, 0x7F) } },
        { { XA(0x04, 0x7F), XA(0x04, 0x7F) }, { XA(0x04, 0x7F), XA(0x04, 0x7F) } },
        { { XA(0x04, 0x7F), XA(0x04, 0x7F) }, { XA(0x04, 0x7F), XA(0x04, 0x7F) } },
        { { XA(0x03, 0x7F), XA(0x03, 0x7F) }, { XA(0x03, 0x7F), XA(0x03, 0x7F) } },
        { { XA(0x03, 0x7F), XA(0x03, 0x7F) }, { XA(0x03, 0x7F), XA(0x03, 0x7F) } },
        { { XA(0x03, 0x7F), XA(0x03, 0x7F) }, { XA(0x03, 0x7F), XA(0x03, 0x7F) } },
    },
    {
        XA(0x15, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
        XA(0x0B, 0x7F),
        XA(0x0B, 0x7F),
        XA(0x0B, 0x7F),
        XA(0x14, 0x7F),
        XA(0x04, 0x75),
        XA(0x07, 0x70),
        XA(0x07, 0x70),
    },
};

#undef XA

s32 D_800F1AAC = 1;

void (*D_800F1AB0[])(void) = {
    func_80016B38,
    func_80016B58,
    func_80016BDC,
    func_80016C5C,
    func_80016D0C,
    func_80016DAC,
    func_80016E34,
    func_80016E84,
};

RECT D_800F1AD0 = { 0, 484, 256, 2 };

struct HudLayoutData D_800F1AD8[38] = {
    { 104, 40, 0x00, 0x00, 0x44, 0x45 },
    { 44, 36, 0x19, 0x00, 0x4C, 0x56 },
    { 232, 40, 0x01, 0x01, 0x44, 0x45 },
    { 172, 36, 0x1A, 0x01, 0x4D, 0x57 },
    { 104, 64, 0x02, 0x02, 0x44, 0x45 },
    { 44, 60, 0x1B, 0x02, 0x4E, 0x58 },
    { 232, 64, 0x03, 0x03, 0x44, 0x45 },
    { 172, 60, 0x1C, 0x03, 0x4F, 0x59 },
    { 104, 88, 0x04, 0x04, 0x44, 0x45 },
    { 44, 84, 0x1D, 0x04, 0x50, 0x5A },
    { 232, 88, 0x05, 0x05, 0x44, 0x45 },
    { 173, 85, 0x1E, 0x05, 0x51, 0x5B },
    { 104, 112, 0x06, 0x06, 0x44, 0x45 },
    { 44, 108, 0x1F, 0x06, 0x52, 0x5C },
    { 232, 112, 0x07, 0x07, 0x44, 0x45 },
    { 173, 109, 0x20, 0x07, 0x53, 0x5D },
    { 104, 136, 0x08, 0x08, 0x44, 0x45 },
    { 44, 132, 0x21, 0x08, 0x54, 0x5E },
    { 232, 136, 0x09, 0x09, 0x44, 0x45 },
    { 172, 132, 0x22, 0x09, 0x55, 0x5F },
    { 44, 36, 0x25, 0xFF, 0x48, 0x49 },
    { 172, 36, 0x25, 0xFF, 0x48, 0x49 },
    { 44, 60, 0x25, 0xFF, 0x48, 0x49 },
    { 172, 60, 0x25, 0xFF, 0x48, 0x49 },
    { 44, 84, 0x25, 0xFF, 0x48, 0x49 },
    { 172, 84, 0x25, 0xFF, 0x48, 0x49 },
    { 44, 108, 0x25, 0xFF, 0x48, 0x49 },
    { 172, 108, 0x25, 0xFF, 0x48, 0x49 },
    { 44, 132, 0x25, 0xFF, 0x48, 0x49 },
    { 172, 132, 0x25, 0xFF, 0x48, 0x49 },
    { 64, 192, 0x0A, 0xFF, 0x4A, 0x4A },
    { 92, 216, 0x0D, 0xFF, 0x44, 0x44 },
    { 136, 208, 0x18, 0x0E, 0x40, 0x40 },
    { 280, 168, 0x0B, 0x0D, 0x48, 0x49 },
    { 280, 200, 0x0C, 0x0E, 0x48, 0x49 },
    { 128, 176, 0x23, 0x0A, 0x46, 0x47 },
    { 176, 176, 0x23, 0x0B, 0x46, 0x47 },
    { 224, 176, 0x24, 0x0C, 0x46, 0x47 },
};

/* The final record continues into g_BootTransitionDataRegion. */
s16 D_800F1C08[2] = { 76, 216 };

struct BootTransitionDataRegion g_BootTransitionDataRegion = {
    { 0x0D, 0xFF, 0x44 },
    { 0x44, 0x02, 0x06, 0x01, 0x04, 0x03, 0x00, 0x05, 0x07 },
};

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

struct MovieHudQuad D_800F1C18[13] = {
    { 60, 27, 156, 27, 56, 32, 152, 32, 0 },
    { 188, 27, 284, 27, 184, 32, 280, 32, 1 },
    { 60, 51, 156, 51, 56, 56, 152, 56, 2 },
    { 188, 51, 284, 51, 184, 56, 280, 56, 3 },
    { 60, 75, 156, 75, 56, 80, 152, 80, 4 },
    { 188, 75, 284, 75, 184, 80, 280, 80, 5 },
    { 60, 99, 156, 99, 56, 104, 152, 104, 6 },
    { 188, 99, 284, 99, 184, 104, 280, 104, 7 },
    { 60, 123, 156, 123, 56, 128, 152, 128, 8 },
    { 188, 123, 284, 123, 184, 128, 280, 128, 9 },
    { 110, 196, 142, 196, 107, 200, 139, 200, 10 },
    { 157, 196, 190, 196, 155, 200, 187, 200, 11 },
    { 206, 196, 238, 196, 203, 200, 235, 200, 12 },
};

struct MoviePlaybackData D_800F1D04[11] = {
    { JP_VALUE(0x8A, 0x89), 0x0092, 0x001D, 1, 0x0800 },
    { JP_VALUE(0x8B, 0x8A), 0x0542, 0x0019, 1, 0x08F0 },
    { JP_VALUE(0x8C, 0x8B), 0x0412, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8D, 0x8C), 0x04F3, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8E, 0x8D), 0x0422, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8F, 0x8E), 0x0536, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x90, 0x8F), 0x03B0, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x91, 0x90), 0x04C0, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x92, 0x91), 0x03E4, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x93, 0x92), 0x0C64, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x94, 0x93), 0x03CB, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
};

u32 D_800F1D88 = 1;

u32 D_800F1D8C = 0x80;
