// 80013588..80014DC4
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

void func_8001326C(u8 arg0);

void func_80013404(u8 arg0);

#ifndef MMX4_PC
void func_80013530(void);
#endif

void func_80013588(void)
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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_800137F0);
#else
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
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80013968);
#else
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
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80013AD8);
#else
void func_80013AD8(s32 arg0, u8 arg1, CdLoadAddress arg2)
{
    u8 i;
    s16 temp_a0;
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
#endif

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

extern s32 D_80137CCC;

extern s32 D_80137CEC;

extern CdlLOC D_80137CF8;

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80013DA8);
#else
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
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80013E68);
#else
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
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_800141BC);
#else
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
#endif

extern struct CdImageOrigin D_800F1614[];

extern u16 D_8012F4A8;

extern u16 D_8012F4AC;

extern u16 D_8012F4B0;

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_800142BC);
#else
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
#endif

extern u32 D_80137CE0;

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80014514);
#else
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
#endif

void func_800147AC(void);

extern u8 D_8013BD40;

void func_80014780(void)
{
    if (D_8013BD40 != 0) {
        func_800147AC();
    }
}

extern void (*D_800F1640[3])(void);
const D_80010014_t D_80010014 = {
    func_80014140, func_800142BC, func_80014514, func_800141BC
};

#ifdef VERSION_JP
struct Unk5 D_800F0E18[] = {
#include "archive_data.jp.inc"
};
#elif defined(VERSION_EU)
struct Unk5 D_800F0E18[] = {
#include "archive_data.eu.inc"
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

#ifndef MMX4_WIN32
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
#endif

struct CdImageOrigin D_800F1614[] = {
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
#ifdef MMX4_WIN32
    { 0x002, 0x000 },
#endif
};

#ifndef MMX4_WIN32
void (*D_800F1640[3])(void) = {
    func_800148E4,
    func_800148EC,
    func_80014968,
};
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_800148EC);
#else
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
#endif
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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80014A90);
#else
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
#endif
#ifndef MMX4_PC
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/3D88", func_80014C70);
#else
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
#endif
