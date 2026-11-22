// 80016334..80016FF4
#include "common.h"
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/xa_sequence_data.h"
#include "main/323C.h"
#include "main/3A6C.h"
#include "main/main_palette_data.h"
#include "main/movie_hud_data.h"

#ifdef __MWERKS__
void func_80016420(arg_u8 arg0);
#endif

#ifndef MMX4_SATURN

extern s8 D_801307F8;

#ifdef MMX4_PC
extern s32 func_80018AD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
#endif

#ifdef MMX4_WIN32
void func_80016420(arg_u8 arg0);
#endif
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
extern /* The final record continues into g_BootTransitionDataRegion. */ s16 D_800F1C08[2];

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

extern void (*D_800F1AB0[])(void);
#endif

#ifndef MMX4_SATURN
#ifdef VERSION_DEMO
extern s32 D_8013A4F4_demo; // D_80171EA9
extern s32 D_800FBCB8_demo; // D_80141BD0
extern s32 D_801062AC_demo; // D_801441B8
extern s32 D_8010403C_demo; // D_80141F4A
#endif

void func_80016334(void)
{
    func_80016420(0);
#ifdef VERSION_EU
    D_801419AC = 0;
    D_8013956C = 0;
    D_801307F8 = 0;
#endif
    DEMO_ALT(D_80171EA9, D_8013A4F4_demo) = 1;
#ifndef VERSION_EU
#ifndef VERSION_DEMO
    D_8013956C = 1;
#endif
    D_801419AC = 0;
    DEMO_ALT(D_801441B8, D_801062AC_demo) = 0;
#endif
#ifdef VERSION_EU
    D_80141F4A = 1;
#else
    DEMO_ALT(D_80141F4A, D_8010403C_demo) = 0;
#endif
    D_8013952C = 0;
    D_80141BD4 = 0;
    D_80139524 = 0x80;
    D_80139530 = 0;
    DEMO_ALT(D_80141BD0, D_800FBCB8_demo) = 0;
    D_80139564 = 0;
    D_801441B0 = 0;
}

void func_800163BC(s32 arg0)
{
    DEMO_ALT(D_80171EA9, D_8013A4F4_demo) = 0;
    func_80016420(D_80139524);
}

void func_800163EC(void)
{
    DEMO_ALT(D_80171EA9, D_8013A4F4_demo) = 1;
    func_80016420(D_80139524);
}

void func_80016448(u8 arg0);

extern u8 D_80139524;

void func_80016420(arg_u8 arg0)
{
    D_80139524 = arg0;
    func_80016448(arg0);
}

#ifdef MMX4_WIN32
void pc_cd_set_volume(s32 volume);
#endif

void func_80016448(u8 arg0)
{
#ifdef MMX4_WIN32
    D_80139528 = arg0;
    pc_cd_set_volume(arg0);
#else
    D_80139528 = arg0;
    if (DEMO_ALT(D_80171EA9, D_8013A4F4_demo) == 1) {
        D_80139520.val0 = arg0;
        D_80139520.val1 = 0;
        D_80139520.val2 = arg0;
        D_80139520.val3 = 0;
    } else {
        D_80139520.val0 = arg0 >> 1;
        D_80139520.val1 = D_80139520.val0;
        D_80139520.val2 = D_80139520.val0;
        D_80139520.val3 = D_80139520.val0;
    }
    CdMix(&D_80139520);
#endif
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/cd_music", func_800164D8);
#else
void func_800164D8(void)
{
    s8 pad[2];
    s32 a = engine_obj.stage * 8;
    s32 b = engine_obj.substage * 4;
    s32 c = engine_obj.cur_character * 2;
    s32 temp_v0;

    temp_v0 = a + b + c;
    func_8001663C(((u8*)stage_music)[temp_v0],
        ((u8*)stage_music)[temp_v0 + 1]);
}
#endif

#ifdef VERSION_DEMO
void func_8002DB00_demo(void)
{
    func_8001663C(alternate_stage_music[engine_obj.stage * 2], alternate_stage_music[engine_obj.stage * 2 + 1]);
}
#else
void func_8001653C(void)
{
    s32 track;
    s16 volume;

    if (engine_obj.stage >= 0xB && engine_obj.stage < 0xD) {
        if (engine_obj.stage == 0xB) {
            if (engine_obj.substage == 0) {
                if (engine_obj.cur_character == 0) {
                    track = MUSIC_DOUBLE_BATTLE;
                    volume = 0x75;
                } else {
                    track = MUSIC_IRIS_BATTLE;
                    volume = 0x7F;
                }
            } else {
                track = MUSIC_REPLIFORCE_BATTLE;
                volume = 0x7F;
            }
        } else if (engine_obj.stage == 0xC) {
            if (engine_obj.substage == 0) {
                track = MUSIC_BOSS_BATTLE;
                volume = 0x70;
            } else if (D_80171EA8 == 0) {
                track = MUSIC_SIGMA_BATTLE;
                volume = 0x7F;
            } else {
                track = MUSIC_SIGMA_FINAL_BATTLE;
                volume = 0x75;
            }
        }
    } else {
        track = alternate_stage_music[engine_obj.stage * 2];
        volume = alternate_stage_music[engine_obj.stage * 2 + 1];
    }

    func_8001663C(track, volume);
}
#endif

extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;
extern s32 D_80139530, D_80141BD4;

#ifdef VERSION_DEMO
void func_8001663C(u8 selection, u8 volume)
{
    u16 base;
    const u16* entry;
    s32 channel;
    CdlLOC* location;

    base = 0;
    channel = 0;
    D_80139560 = selection < 8 ? XA_ARCHIVE_BGM1 : XA_ARCHIVE_BGM2;
    switch (selection >> 3) {
    case 0:
        entry = D_800F19E0;
        D_80139560 = XA_ARCHIVE_BGM1;
        break;

    case 1:
        selection %= 8;
        entry = D_800F19E4;
        D_80139560 = XA_ARCHIVE_BGM2;
        break;
    }

    while (base++ < selection) {
        if ((*entry) & 0x8000) {
            channel++;
            entry++;
        }
        entry++;
    }

    ((u8*)D_80175EE8)[0] = 1;
    ((u8*)D_80175EE8)[1] = channel;
    D_80139544 = func_80013614(D_80139560, &D_80139538) + ((u8*)D_80175EE8)[1];
    D_80139540 = D_80139544;
    do {
        D_80139540 += ((entry[0] & 0x7FFF) * 8);
        location = (CdlLOC*)&D_80139514;
    } while (0);
    D_80139544 += ((entry[1] & 0x7FFF) * 8);
    CdIntToPos(D_80139540, location);
    SsSetSerialAttr(0, 0, 1);
    D_8013A4F4_demo = 1;
    func_80016420(volume);
    D_80141BD4 = 2;
    D_80139530 = 7;
}
#elif defined(MMX4_GAMECUBE)
s32 fn_800158E4(void* player);
void fn_8001586C(void* player, s32 volume);
void fn_800159B4(void* player, u8 track, s32 flags);
extern u8 gc_music_player[0x18];
extern s32 gc_music_pending_volume;
extern s32 gc_music_fade;
extern s32 gc_music_volume;
extern s32 gc_music_target_volume;

void func_8001663C(u8 selection, u8 volume)
{
    if (fn_800158E4(gc_music_player) == 0x30001) {
        gc_music_target_volume = volume;
        gc_music_volume = volume;
        fn_8001586C(gc_music_player, volume * 100 / 128);
    } else {
        gc_music_pending_volume = volume;
    }
    gc_music_fade = 0;
    D_80173C84 = 1;
    if (selection != 0 && selection < 0x20) {
        fn_800159B4(gc_music_player, selection, 0x10);
    } else {
        fn_800159B4(gc_music_player, selection, 0);
    }
}
#else
void func_8001663C(u8 selection, u8 volume)
{
    u16 base;
    const u16* entry;
    s32 channel;
    CdlLOC* location;
#ifdef MMX4_PC
    mmx4_pc_saturn_music_select(selection);
#endif
    base = 0;
    channel = 0;
    D_80139568 = 0;
    switch (selection >> 3) {
    case 0:
        D_80139560 = XA_ARCHIVE_BGM1;
        entry = D_800F19E0;
        if (selection == 0) {
            D_80139568 = 1;
        }
        break;

    case 1:
        entry = D_800F19E4;
        D_80139560 = XA_ARCHIVE_BGM2;
        selection &= 7;
        break;

    case 2:
        entry = D_800F19E8;
        D_80139560 = XA_ARCHIVE_BGM3;
        selection &= 7;
        break;

    case 3:
        entry = D_800F19EC;
        D_80139560 = XA_ARCHIVE_BGM4;
        selection &= 7;
        break;

    case 4:
        selection &= 7;
        entry = D_800F19F0;
        D_80139560 = XA_ARCHIVE_BGM5;
        D_80139568 = 1;
        break;

    case 5:
        selection &= 7;
        entry = D_800F19F4;
        D_80139560 = XA_ARCHIVE_VOICE1;
        D_80139568 = 1;
        break;

    case 6:
        selection &= 7;
        entry = D_800F19F8;
        D_80139560 = XA_ARCHIVE_VOICE2;
        D_80139568 = 1;
        break;

    case 7:
        selection &= 7;
        entry = D_800F19FC;
        D_80139560 = XA_ARCHIVE_VOICE3;
        D_80139568 = 1;
        break;

    case 8:
        selection &= 7;
        entry = D_800F1A00;
        D_80139560 = XA_ARCHIVE_VOICE4;
        D_80139568 = 1;
        break;

    case 9:
        selection &= 7;
        entry = D_800F1A04;
        D_80139560 = XA_ARCHIVE_VOICE5;
        D_80139568 = 1;
        break;

    case 10:
        selection &= 7;
        entry = D_800F1A08;
        D_80139560 = XA_ARCHIVE_BOSS_INTRO;
        D_80139568 = 1;
        break;

    default:
        break;
    }

    while (base++ < selection) {
        if ((*entry) & 0x8000) {
            channel++;
            entry++;
        }
        entry++;
    }

    ((u8*)D_80175EE8)[0] = 1;
    ((u8*)D_80175EE8)[1] = channel;
    D_80139544 = func_80013614(D_80139560, &D_80139538) + ((u8*)D_80175EE8)[1];
    D_80139540 = D_80139544;
    do {
        D_80139540 += ((entry[0] & 0x7FFF) * 8);
        location = (CdlLOC*)&D_80139514;
    } while (0);
    D_80139544 += ((entry[1] & 0x7FFF) * 8);
    CdIntToPos(D_80139540, location);
    SsSetSerialAttr(0, 0, 1);
    func_80016420(volume);
    D_80141BD4 = 2;
    D_80173C84 = 1;
    D_80139530 = 7;
}
#endif

void func_80016F0C();

extern s32 D_80139530;

extern u32 D_8013953C;

extern s32 D_80139544;

extern s16 D_8013955C;

extern s32 D_80141BD4;

#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern u32 mmx4_pc_xa_stops;
extern u32 mmx4_pc_xa_stop_sample;
extern u32 mmx4_pc_xa_starts;
extern u32 mmx4_pc_xa_start_sample;
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
#ifdef VERSION_DEMO
                    D_80139530 = 5;
#else
                    if (*(u8*)&D_80139568 == 0) {
                        D_80139530 = 5;
                    } else {
                        func_80016F0C();
                    }
#endif
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

#ifdef VERSION_DEMO
s32 func_800169D8(void)
{
    if (D_80141BD4 == 2) {
        if (*(u8*)&D_8013952C != 0) {
            return -1;
        }
        D_800F1AB0[D_80139530]();
        if (D_800FBCB8_demo == 0) {
            return 0;
        }
        if (D_800F1AAC != 0) {
            D_800F1AAC = 0;
            D_80139510 = D_80139528 - D_80139534;
        } else {
            D_800F1AAC = 1;
        }
        if (D_80139510 < 4) {
            D_80139510 = 0;
            D_800F1AAC = 1;
            func_80016F0C();
            D_800FBCB8_demo = 0;
        }
        func_80016448(D_80139510);
        return 0;
    }
    return -1;
}
#else
s32 func_800169D8(void)
{
    u8 temp_a0;

#ifdef MMX4_PC
    mmx4_pc_saturn_music_set_playing(D_80141BD4 == 2 && D_80139530 != 0 && D_80139530 != 3 && D_80139530 != 4);
#endif
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
                    D_80139510 = D_80139528 - D_80139534;
                } else {
                    D_800F1AAC = 1;
                }
                func_80016448(D_80139510);
            }
#ifdef VERSION_EU
            if ((u8)D_80141F4A != (temp_a0 = D_80171EA9 & 0xFF)) {
                D_80141F4A = D_80171EA9;
#else
            if ((u8)D_8013956C != (temp_a0 = D_80171EA9 & 0xFF)) {
                D_8013956C = D_80171EA9;
#endif
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
#endif

void func_80016B38(void)
{
    DEMO_ALT(D_80141BD0, D_800FBCB8_demo) = 0;
    D_80141BD4 = 0;
    D_80139564 = 0;
}

void func_80016B58(void)
{
#ifdef MMX4_WIN32
    D_80173C84 = 2;
    D_80139530 = 2;
#else
    s32 temp_v0;
    u8* ptr = &D_80139554;

#ifdef MMX4_PC
    if (!mmx4_pc_replay_xa_start_ready())
        return;
#endif
    temp_v0 = CdSync(1, ptr);
    if ((temp_v0 == 2) && !(*ptr & 0x40) && (CdControl(CdlReadS, 0, ptr) != 0)) {
#ifndef VERSION_DEMO
        D_80173C84 = 2;
#endif
        D_80139530 = temp_v0;
#ifdef MMX4_PC
        mmx4_pc_xa_starts++;
        mmx4_pc_xa_start_sample = mmx4_pc_replay_consumed();
        mmx4_pc_replay_xa_start_done();
#endif
    }
#endif
}

void func_80016BDC(void)
{
#ifdef MMX4_WIN32
    if (D_8013955C & DEMO_ALT(D_801441B8, D_801062AC_demo)) {
        D_80139530 = 3;
    }
#else
    if (D_8013955C & DEMO_ALT(D_801441B8, D_801062AC_demo)) {
        while (CdControl(CdlPause, 0, &D_80139554) == 5)
            ;
        D_80139530 = 3;
        if (D_80139554[0] & 0x10) {
            D_8013952C = 1;
        }
    }
#endif
}

void func_80016C5C(void)
{
#ifdef MMX4_WIN32
    if (D_80139564 != 0 && D_801441B8 == 0) {
        D_8013955C = 0;
        D_80139530 = 2;
    }
#else
    s32 status;

    status = CdSync(1, 0);
    if ((status == 2) && (D_80139564 != 0) && (DEMO_ALT(D_801441B8, D_801062AC_demo) == 0) && (CdControl(CdlReadS, 0, D_80139554) != 0)) {
        D_8013955C = 0;
        D_80139530 = status;
        if (D_80139554[0] & 0x10) {
            D_8013952C = 1;
        }
    }
#endif
}

void func_80016D0C(void)
{
#ifdef MMX4_WIN32
    if (D_80139564 == 2) {
        func_80016420(0);
        D_80139564 = 0;
    } else {
        func_80016420(0);
    }
    D_80139530 = 0;
#else
    s32 status;

    status = CdSync(1, 0);
    if (status == 2) {
        if (D_80139564 == DEMO_ALT(status, 1)) {
            if (CdControlB(CdlPause, 0, 0) == 0) {
                return;
            }
            SsSetSerialAttr(0, 0, 0);
            func_80016420(0);
            D_80139564 = 0;
            D_80139530 = 0;
        } else {
            SsSetSerialAttr(0, 0, 0);
            func_80016420(0);
            D_80139530 = 0;
        }
    }
#endif
}

void func_80016DAC()
{
#ifdef MMX4_WIN32
    D_80139530 = 1;
    D_80139564 = 2;
#else
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
        D_80139564 = DEMO_ALT(2, 1);
    }
#endif
}

void func_80016E34()
{
#ifdef MMX4_WIN32
    D_80139530 = 5;
#else
    if (CdSync(1, 0) == CdlComplete && CdControl(CdlSetfilter, &D_80175EE8, 0) != 0) {
        D_80139530 = 5;
    }
#endif
}

extern s8 D_8013952C;

extern s32 D_80139530;

extern u8 D_80139554[];

#ifdef MMX4_GAMECUBE
void fn_80015978(void* player);
void fn_80015934(void* player);

s32 func_80016E84(void)
{
    if (fn_800158E4(gc_music_player) == 0x30000) {
        D_80173C84 = 2;
        if (gc_music_fade != 0) {
            gc_music_volume -= gc_music_fade;
            if (gc_music_volume < 0) {
                gc_music_volume = 0;
                gc_music_fade = 0;
                fn_80015978(gc_music_player);
            } else {
                fn_8001586C(gc_music_player, gc_music_volume * 100 / 128);
            }
        }
    } else {
        D_80173C84 = 0;
    }
    return 0;
}

void gc_music_update(void)
{
    if (gc_music_pending_volume != -1 && fn_800158E4(gc_music_player) == 0x30001) {
        gc_music_target_volume = (u8)gc_music_pending_volume;
        gc_music_volume = (u8)gc_music_pending_volume;
        fn_8001586C(gc_music_player, (u8)gc_music_pending_volume * 100 / 128);
        gc_music_pending_volume = -1;
    }
    fn_80015934(gc_music_player);
}

void func_80016F0C()
{
    fn_80015978(gc_music_player);
}

void func_80016FB4(s32 arg0)
{
    if (fn_800158E4(gc_music_player) == 0x30000) {
        gc_music_fade = arg0;
    }
}
#else
void func_80016E84(void)
{
#ifdef MMX4_WIN32
    D_80139530 = 6;
#else
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
#endif
}
#ifdef VERSION_DEMO
u8 func_8002E2AC_demo(void)
{
    u8 result[8];

    while (CdControlB(CdlNop, 0, result) == 0)
        ;
    if (result[0] & 0x10) {
        D_801419AC = 0;
        D_8013952C = 1;
    }
    return result[0];
}
#endif

#ifdef MMX4_WIN32
void pc_cd_stop(void);
#endif

#ifdef VERSION_DEMO
void func_80016F0C()
{
    if (D_80141BD4 == 2) {
        func_80016420(0);
        if (D_80139564 == 1) {
            if (D_8013955C != 0) {
                while (CdControlB(CdlPause, 0, NULL) == 0)
                    ;
                VSync(1);
            }
        }
        SsSetSerialAttr(0, 0, 0);
        D_80139564 = 0;
        D_80139530 = 0;
    }
}

void func_80016FB4(s32 arg0)
{
    D_80139534 = arg0;
    D_800FBCB8_demo = 1;
}
#else
void func_80016F0C()
{
#ifdef MMX4_WIN32
    if (D_80141BD4 == 2) {
        func_80016420(0);
        pc_cd_stop();
        D_80139564 = 0;
        D_80139568 = 0;
        D_80173C84 = 0;
        D_80139530 = 0;
    }
#else
    s32 temp_s0 = D_80141BD4;
    if (temp_s0 == 2) {
#ifdef MMX4_PC
        mmx4_pc_saturn_music_select(-1);
#endif
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
#endif
}

void func_80016FB4(s32 arg0)
{
    if ((engine_obj.stage == 0xC && engine_obj.substage == 1) || D_80173C84 != 0) {
        D_80139534 = arg0;
        D_80141BD0 = 1;
    }
}
#endif
#endif
#endif
