#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", func_800E9040);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetGeomOffset);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetGeomScreen);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _patch_gte);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", func_800E9168);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", LoadTPage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", LoadClut);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", LoadClut2);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDefDrawEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDefDispEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetTPage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetClut);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DumpTPage);

INCLUDE_RODATA("asm/us/main/nonmatchings/D9840", D_80011C74);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DumpClut);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", NextPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", IsEndPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", AddPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", AddPrims);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", CatPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", TermPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetSemiTrans);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetShadeTex);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyF3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyFT3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyG3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyGT3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyF4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyFT4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyG4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPolyGT4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetSprt8);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetSprt16);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetSprt);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetTile1);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetTile8);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetTile16);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetTile);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineF2);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineG2);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineF3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineG3);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineF4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetLineG4);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawTPage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawMove);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawLoad);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MargePrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DumpDrawEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DumpDispEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", ResetGraph);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetGraphReverse);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetGraphDebug);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetGraphQueue);

extern u8 D_8011E188;

u8 GetGraphType(void)
{
    return D_8011E188;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetGraphDebug);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DrawSyncCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDispMask);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DrawSync);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", checkRECT);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", ClearImage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", ClearImage2);

INCLUDE_RODATA("asm/us/main/nonmatchings/D9840", D_80011E6C);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", LoadImage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", StoreImage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MoveImage);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", ClearOTag);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", ClearOTagR);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DrawPrim);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DrawOTag);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", PutDrawEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DrawOTagEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetDrawEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", PutDispEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetDispEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", GetODE);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetTexWindow);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawArea);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawOffset);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetPriority);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawMode);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", SetDrawEnv2);

extern u8 D_8011E188;

s32 get_mode(s32 dfe, s32 dtd, s32 tpage)
{
    u8 version;

    version = D_8011E188;
    if (version == 1 || version == 2) {
        return 0xE1000000 | (dtd ? 0x800 : 0) | (dfe ? 0x1000 : 0) | (tpage & 0x27FF);
    } else {
        return 0xE1000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", get_cs);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", get_ce);

extern u8 D_8011E188;

u32 get_ofs(s32 arg0, u16 arg1)
{
    if ((u32)(D_8011E188 - 1) < 2U) {
        return 0xe5000000 | ((arg1 & 0xfff) << 0xC) | (arg0 & 0xfff);
    }
    return 0xe5000000 | ((arg1 & 0x7ff) << 0xB) | (arg0 & 0x7ff);
}

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", get_tw);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", get_dx);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _status);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _otc);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _clr);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _dws);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _drs);

extern u32* D_8011E25C;
extern s8 D_8013BAF4[];

void _ctl(u32 arg0)
{
    *D_8011E25C = arg0;
    D_8013BAF4[arg0 >> 0x18] = (s8)arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _getctl);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _cwb);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _cwc);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _param);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _addque);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _addque2);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _exeque);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _reset);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _sync);

extern s32 D_8011E2A0;
extern s32 D_8011E2A4;

void set_alarm(void)
{
    D_8011E2A0 = VSync(-1) + 0xF0;
    D_8011E2A4 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", get_alarm);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", _version);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", memset2);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTReset);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTGetEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTPutEnv);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTBufSize);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTin);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTout);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTinSync);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCToutSync);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCTinCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", DecDCToutCallback);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_reset);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_in);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_out);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_in_sync);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_out_sync);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", MDEC_status);

INCLUDE_ASM("asm/us/main/nonmatchings/D9840", timeout);
