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
