// 80018000..800193D8
#include "common.h"
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/xa_sequence_data.h"
#include "main/323C.h"
#include "main/3A6C.h"
#include "main/main_palette_data.h"
#include "main/movie_hud_data.h"

#ifdef __MWERKS__
void func_80018E50(void);
void func_80018EEC(void);
void func_80018FD0(u32 arg0);
void func_80019058(s8 arg0);
void func_800190F0(s32 arg0);
#endif

#ifndef MMX4_SATURN

#ifdef MMX4_PC
extern s32 func_80018AD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
extern void func_80018E50(void);
extern void func_80018EEC(void);
extern void func_80018FD0(u32 arg0);
extern void func_80019058(s8 arg0);
extern void func_800190F0(s32 arg0);
#endif
extern void func_80019100(void);
extern void func_80019208(void);
extern void func_80019228(void);

#ifdef MMX4_WIN32
#endif
void func_800192F8(void);
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

extern /* The final record continues into g_BootTransitionDataRegion. */ s16 D_800F1C08[2];
extern struct MoviePlaybackData D_800F1D04[11];
extern u32 D_800F1D88;

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef MMX4_PC
#endif

s32 func_80013614(s32 arg0, s32* arg1);

void func_80013890(u32 arg0, u8* arg1);

void MyCdReadyCallback(u8 status, u8* result);

void func_80013AD8(s32 arg0, u8 arg1, CdLoadAddress arg2);

typedef struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
} D_80010014_t;

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif
#undef JP_VALUE

void func_80013E68(u8 status, u8* result);

extern void (*D_800F1640[3])(void);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifndef MMX4_SATURN
#endif

#ifndef MMX4_PC
void func_80014A90(s32 arg0, s32 arg1);
#endif

#ifndef MMX4_PC
#endif

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

#ifdef VERSION_JP
#define CD_AUDIO_FIRST_TRACK 0x4C
#define CD_AUDIO_LAST_TRACK 0x4E
#elif defined(VERSION_EU)
#define CD_AUDIO_FIRST_TRACK 0x4B
#define CD_AUDIO_LAST_TRACK 0x4D
#else
#define CD_AUDIO_FIRST_TRACK 0x4A
#define CD_AUDIO_LAST_TRACK 0x4C
#endif

#define XA(sequence_, volume_) \
    {                          \
        sequence_, volume_     \
    }

extern void (*D_800F1AB0[])(void);

extern struct MoviePlaybackData D_800F1D04[11];

extern u32 D_800F1D88;

extern u32 D_800F1D8C;
#endif

#ifndef MMX4_SATURN
extern s32 D_80139590;
extern s32 D_80139598, D_8013959C, D_801395A0, D_801395A4;
void Set24BitDisp(s32 w, s32 h);
s32 func_80018B88(s32 arg0, s32 arg1);

// general movie playing code
#ifndef VERSION_DEMO
#ifndef SKIP_MDEC
void func_80018000(arg_u8 movie)
{
    RECT rect;
    s32 status;
    s32 display_y;
    s32 finished;

    D_80139598 = (s32)D_80173C80;
    D_8013959C = (s32)(D_80173C80 + 0x4000);
    D_801395A0 = D_8013959C + 0xE000;
    D_801395A4 = D_801395A0 + 0xE000;
    Set24BitDisp(0x140, 0xF0);
    func_80018FD0(0x80);
    func_80019058(D_80171EA9);
    movie = (u8)movie;
    ((u8*)D_80175EE8)[1] = 1;
    status = func_80018AD0(
        D_800F1D04[movie].file_id, 1, D_800F1D04[movie].arg2,
        D_801395A4, D_800F1D04[movie].arg8,
        D_8013959C, D_801395A0, D_80139598, 1, 1);
    D_80139590 = 0;
    if (status == 0) {
        do {
            VSync(0);
            PutDispEnv(&draw_infos[D_80139590].dispenv);
            D_80139590 ^= 1;
#ifdef VERSION_EU
            display_y = D_80139590 != 0 ? 0xF0 : 0;
            finished = func_80018B88(0, display_y);
#else
            display_y = -(D_80139590 != 0);
            finished = func_80018B88(0, display_y & 0xF0);
#endif
            func_80018EEC();
            func_80012328();
            if (controller_input.pressed & D_800F1D04[movie].skip_button) {
                finished = 1;
            }
        } while (finished == 0);
    }
    SetDispMask(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x1E0;
    rect.h = 0x1E0;
    ClearImage(&rect, 0U, 0U, 0U);
    DrawSync(0);
    func_80018E50();
    draw_infos[0].dispenv = old_dispenv[0];
    draw_infos[1].dispenv = old_dispenv[1];
    D_80139590 ^= 1;
    PutDispEnv(&draw_infos[D_80139590].dispenv);
    DrawSync(0);
}
#else
void func_80018000(arg_u8 temp)
{
#ifndef _MSC_VER
    asm(".rept 184 ; nop ; .endr");
#endif
}
#endif

// capcom logo playing code
#ifndef SKIP_MDEC
#ifdef VERSION_JP
#define CAPCOM_LOGO_FILE 0x89
#else
#define CAPCOM_LOGO_FILE 0x8A
#endif
extern s32 D_80139594;
#ifdef VERSION_EU
// clang-format off
void func_800182E8(movie)
    u8 movie;
// clang-format on
{
    RECT rect = { 0, 0, 0x1E0, 0xF0 };
    s32 status;
    s32 finished;

    D_80139598 = (s32)MAIN_ARCHIVE_ARENA;
    D_8013959C = (s32)(MAIN_ARCHIVE_ARENA + 0x4000);
    D_801395A0 = (s32)(MAIN_ARCHIVE_ARENA + 0x11000);
    D_801395A4 = (s32)(MAIN_ARCHIVE_ARENA + 0x1E000);
    Set24BitDisp(0x140, 0xF0);
    func_80018FD0(0x80);
    func_80019058(1);
    ((u8*)D_80175EE8)[1] = 1;
    status = func_80018AD0(D_800F1D04[movie].file_id, 1, D_800F1D04[movie].arg2,
        D_801395A4, D_800F1D04[movie].arg8, D_8013959C, D_801395A0,
        D_80139598, 1, 1);
    D_80139594 = 0;
    if (status == 0) {
        do {
            D_80139594 ^= 1;
            finished = func_80018B88(0, D_80139594 != 0 ? 0xF0 : 0);
            func_80018EEC();
            VSync(0);
            func_80012328();
            if (controller_input.pressed & D_800F1D04[movie].skip_button)
                finished = 1;
            PutDispEnv(&draw_infos[D_80139594].dispenv);
        } while (finished == 0);
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x1E0;
    rect.h = 0x1E0;
    ClearImage(&rect, 0U, 0U, 0U);
    DrawSync(0);
    func_80018E50();
    SetDispMask(0);
    controller_input.pressed = 0;
    controller_input.held = 0;
    draw_infos[0].dispenv = old_dispenv[0];
    draw_infos[1].dispenv = old_dispenv[1];
    D_80139594 ^= 1;
    PutDispEnv(&draw_infos[D_80139594].dispenv);
    DrawSync(0);
    VSync(0);
    DrawSync(0);
}
#else
void func_800182E8(void)
{
    RECT rect = { 0, 0, 0x1E0, 0xF0 };
    s32 status;
    s32 display_y;
    s32 finished;
    s32 movie;

    D_80139598 = (s32)MAIN_ARCHIVE_ARENA;
    D_8013959C = (s32)(MAIN_ARCHIVE_ARENA + 0x4000);
    D_801395A0 = (s32)(MAIN_ARCHIVE_ARENA + 0xF000);
    D_801395A4 = (s32)(MAIN_ARCHIVE_ARENA + 0x1A000);
    Set24BitDisp(0x140, 0xF0);
    func_80018FD0(0x80);
    func_80019058(1);
    ((u8*)D_80175EE8)[1] = 1;
    status = func_80018AD0(CAPCOM_LOGO_FILE, 1, D_800F1D04[0].arg2,
        D_801395A4, D_800F1D04[0].arg8, D_8013959C, D_801395A0,
        D_80139598, 1, 1);
    D_80139594 = 0;
    if (status == 0) {
        movie = 0;
        do {
            display_y = -(D_80139594 != 1);
            D_80139594 ^= 1;
            finished = func_80018B88(0, display_y & 0xF0);
            func_80018EEC();
            VSync(0);
            func_80012328();
            if (controller_input.pressed & D_800F1D04[movie].skip_button)
                finished = 1;
            PutDispEnv(&draw_infos[D_80139594].dispenv);
        } while (finished == 0);
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x1E0;
    rect.h = 0x1E0;
    ClearImage(&rect, 0U, 0U, 0U);
    DrawSync(0);
    func_80018E50();
    SetDispMask(0);
    draw_infos[0].dispenv = old_dispenv[0];
    draw_infos[1].dispenv = old_dispenv[1];
    controller_input.pressed = 0;
    controller_input.held = 0;
    D_80139594 ^= 1;
    PutDispEnv(&draw_infos[D_80139594].dispenv);
    DrawSync(0);
    VSync(0);
    DrawSync(0);
}
#endif
#else
#ifdef VERSION_EU
void func_800182E8(s32 arg0)
#else
void func_800182E8(void)
#endif
{
#ifndef _MSC_VER
    asm(".rept 194 ; nop ; .endr");
#endif
}
#endif
#endif
void Set24BitDisp(s32 w, s32 h)
{
    RECT rect;
    old_dispenv[0] = draw_infos[0].dispenv;
    old_dispenv[1] = draw_infos[1].dispenv;
    ResetGraph(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = DEMO_ALT(480, 320);
    rect.h = 480;
    VSync(0);
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0, w, h);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 240, w, h);
    draw_infos[1].dispenv.isrgb24 = 1;
    draw_infos[0].dispenv.isrgb24 = 1;
#ifdef VERSION_EU
    draw_infos[1].dispenv.screen.y = 28;
    draw_infos[0].dispenv.screen.y = 28;
#endif
    draw_infos[1].dispenv.isinter = 0;
    draw_infos[0].dispenv.isinter = 0;
#ifdef VERSION_EU
    draw_infos[1].dispenv.screen.x = 0;
    draw_infos[0].dispenv.screen.x = 0;
    draw_infos[1].dispenv.screen.h = 240;
    draw_infos[0].dispenv.screen.h = 240;
    draw_infos[1].dispenv.screen.w = 0;
    draw_infos[0].dispenv.screen.w = 0;
#endif
}
#ifndef VERSION_DEMO

extern u32* D_801395D4[];
extern s32 D_801395DC;
extern s32 D_801395E0;
extern s32 D_801395EC;
extern StHEADER D_801395F0;
extern s32 D_80139610;
extern u8 D_80139648;
extern CdlLOC D_8013964D;
extern s32 D_80139650;
extern CdlLOC D_80139654;
extern s32 D_801441C0;

s32 func_80018788(s32 pos, u32 channel, s32 arg2, u32* ring, u32 ring_size, u32* dest, s32 arg6, s32 arg7, s32 arg8,
    s32 rgb24)
{
    u32* addr;
    StHEADER* header;
    s32 mode;
    u32 i;
    s32 complete;

    D_801395E0 = arg2;
    D_801395EC = 0;
    D_80139634 = 0;
    D_801441C0 = 0;
    D_80139610 = 0;
    D_801395D4[0] = dest;
    ((s32*)D_801395D4)[1] = arg6;
    D_801395DC = arg7;
    D_801395E4 = rgb24;
    D_801395E8 = rgb24;
    D_800F1D88 = arg8;
    func_800190F0(0);
    DecDCTReset(0);
    DecDCToutCallback(func_80019100);
    StSetRing(ring, ring_size);
    StSetStream(D_801395E4, channel, 0x0FFFFFFF, func_80019208, 0);
    mode = 0x148;
    func_800192F8();
    ((u8*)D_80175EE8)[0] = 1;
    func_80018FD0(0x7F);
    CdIntToPos(pos, &D_80139654);
    D_80139650 = pos;
    if (D_800F1D88 != 0)
        mode = 0x1C8;
    complete = CdlComplete;

    while (1) {
        if (CdSync(0, 0) != complete) {
            while (CdReset(0) == 0) {
            }
            VSync(3);
            continue;
        }
        if (CdControl(CdlSetfilter, (u8*)D_80175EE8, 0) == 0)
            continue;
        VSync(3);
        if (CdControlB(CdlSeekL, &D_80139654.minute, 0) == 0)
            continue;
        if (CdRead2(mode) != 0)
            break;
    }

    VSync(3);
    while (CdControl(CdlGetlocP, 0, &D_80139648) == 0) {
    }
    pos = CdPosToInt(&D_8013964D);
    if ((u32)pos < (u32)(D_80139650 - 0x14) || (u32)(D_80139650 + 5) < (u32)pos)
        return 1;

    i = 0;
    func_80019228();
    while (StGetNext(&addr, &header) != 0) {
        VSync(0);
        if (++i >= 0x259)
            return 1;
    }
    D_80139610--;
    D_801395F0 = *header;
    D_801395F0.width = (D_801395F0.width + 8) / 16 * 16;
    D_801395F0.height = (D_801395F0.height + 8) / 16 * 16;
    DecDCTvlc(addr, D_801395D4[D_801395EC]);
    StFreeRing(addr);
    return 0;
}

s32 func_80018AD0(
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

    return func_80018788(
        func_80013614(arg0, &local),
        arg1,
        arg2,
        (u32*)arg3,
        arg4,
        (u32*)arg5,
        arg6,
        arg7,
        arg8,
        arg9);
}

extern s32 D_80139614;
extern RECT D_80139618;
extern u32* D_80139620;
extern s32 D_80139628;
extern u32 D_8013962C;
extern u32 D_80139630;
extern u32 D_80139638;
extern u32 D_8013963C;

s32 func_80018B88(s32 x, s32 y)
{
    u32* addr;
    StHEADER* header;
    u32 i;
    u32 width;
    s16 w;
    s32 result;

    i = 0;
    while (StGetNext(&addr, &header) != 0) {
        VSync(0);
        if (++i >= 0x259)
            return 1;
    }
    w = 0x10;
    D_80139618.x = x;
    D_80139618.y = y;
    D_80139610--;
    width = D_801395F0.width;
    D_80139638 = width;
    D_8013963C = D_801395F0.height;
    D_801441C0 = D_801395F0.frameCount;
    result = (u32)D_801395F0.frameCount >= (u32)D_801395E0;
    if (D_801395E4 != 0)
        w = 0x18;
    D_80139618.w = w;
    D_80139618.h = D_8013963C;
    D_8013962C = 0;
    D_80139630 = width >> 4;
    D_80139620 = (u32*)D_801395DC;
    D_80139628 = D_801395F0.height * 16 * (D_801395E4 ? 3 : 2) / 4;
    if (D_80139614 == 0) {
        movie_slice_offset = 0;
    } else {
        movie_slice_offset = D_8013963C * 16 * (D_801395E4 ? 3 : 2) / 4;
    }
    DecDCTReset(1);
    DecDCTin(D_801395D4[D_801395EC], D_801395E4);
    DecDCTout((u32*)D_801395DC, D_80139628);
    D_801395EC = D_801395EC == 0;
    D_801395F0 = *header;
    D_801395F0.width = (D_801395F0.width + 8) / 16 * 16;
    D_801395F0.height = (D_801395F0.height + 8) / 16 * 16;
    DecDCTvlc(addr, D_801395D4[D_801395EC]);
    StFreeRing(addr);
    return result;
}

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

void func_80018F18(u_long* data, s16 x, s16 y, u32 w, s32 h, s32 wide)
{
    RECT rect;
    s32 width;
    u32 words;
    u32 i;

    width = 0x10;
    if (wide != 0) {
        width = 0x18;
    }
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = h;
    words = (u32)(width * h) >> 1;
    for (i = 0; i < (w >> 4); i++) {
        LoadImage(&rect, data);
        DrawSync(0);
        rect.x += width;
        data += words;
    }
}
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

extern s32 D_80139628;

extern u32 D_8013962C;

extern u32 D_80139630;

extern s32 StCdIntrFlag;

void func_80019100(void)
{
    u32* temp_a0;

    D_8013962C += 1;
    if (StCdIntrFlag != 0) {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }
    if (D_80139614 == 0) {
        LoadImage(&D_80139618, D_80139620);
    }
    if ((u32)D_8013962C < (u32)D_80139630) {
        D_80139618.x += (D_801395E4 ? 0x18 : 0x10);
        temp_a0 = &D_80139620[movie_slice_offset];
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
#endif
#endif
