// 8001326C..80013588
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

extern struct CdImageOrigin D_800F1614[];
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

void func_80012A3C(void);

void func_80012D68(u32* src, u32* dst, s32 count);

void func_80012E38(void);

void func_80012E80();

void func_80012EB0(void);

void func_80012EB8(void);

void func_80012F44(void);

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

#ifdef VERSION_JP
#define ARCHIVE_PATH(path) "E:\\ROCKX4\\JAPAN\\" path
#else
#define ARCHIVE_PATH(path) "E:\\ROCKX4\\USA\\" path
#endif

struct Prim D_800EE504[9] = {
    { 0x60, 0x60, 0x00, 0x08, 0x01, 0x01 },
    { JP_VALUE(0xD0, 0xC8), 0xC0, 0x70, 0x05, 0x02, 0x02 },
    { 0x100, 0xC0, 0x75, 0x04, 0x02, 0x03 },
    { 0x20, 0xC0, 0x08, 0x01, 0x01, 0x00 },
    { 0x10, 0xC0, 0x0A, 0x02, 0x01, 0x00 },
    { 0x30, 0xC0, 0x0C, 0x04, 0x01, 0x00 },
    { 0x10, 0xD0, 0x20, 0x06, 0x01, 0x00 },
    { 0x78, 0xD0, 0x79, 0x03, 0x01, 0x00 },
    { 0x78, 0xD0, 0x89, 0x03, 0x01, 0x00 },
};

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
