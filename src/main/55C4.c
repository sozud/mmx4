// 80014DC4..80015D60
#include "common.h"
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/xa_sequence_data.h"
#include "main/323C.h"
#include "main/3A6C.h"
#include "main/main_palette_data.h"
#include "main/movie_hud_data.h"

#ifdef __MWERKS__
#endif

#ifndef MMX4_SATURN

#ifdef MMX4_PC
extern s32 func_80018AD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
#endif

#ifdef MMX4_WIN32
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

extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern u8 D_800F1654[4];
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

extern void (*D_800F1640[3])(void);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifndef MMX4_SATURN
#endif

extern s8 D_8013E198[];

#ifndef MMX4_PC
void func_80014A90(s32 arg0, s32 arg1);
#endif

#ifndef MMX4_PC
void func_80014C70(void);
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

u8 D_800F164C[4] = { 1, 2, 0, 0 };

s16 D_800F1650[2] = { 1, 0 };

#ifndef VERSION_DEMO
u8 D_800F1654[4] = { CD_AUDIO_FIRST_TRACK, CD_AUDIO_LAST_TRACK, 0, 0 };
#endif

extern void (*D_800F1AB0[])(void);

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
        D_8013924C[var_v1] = 0xFF;
    }
    for (var_v1 = 0; var_v1 < 24; var_v1++) {
        D_80139234[var_v1] = -1;
    }

#ifdef VERSION_EU
    SsFCALL.noteon = &_SsNoteOn;
    SsFCALL.programchange = &_SsSetProgramChange;
    SsFCALL.metaevent = &dmy_SsGetMetaEvent;
    SsFCALL.pitchbend = &dmy_SsSetPitchBend;
    SsFCALL.control[0] = &_SsSetControlChange;
    SsFCALL.control[1] = &dmy_SsContBankChange;
    SsFCALL.control[3] = &_SsContMainVol;
    SsFCALL.control[4] = &dmy_SsContPanpot;
    SsFCALL.control[5] = &dmy_SsContExpression;
    SsFCALL.control[6] = &dmy_SsContDamper;
    SsFCALL.control[7] = &dmy_SsContNrpn1;
    SsFCALL.control[8] = &dmy_SsContNrpn2;
    SsFCALL.control[9] = &_SsContRpn1;
    SsFCALL.control[10] = &dmy_SsContRpn2;
    SsFCALL.control[11] = &dmy_SsContExternal;
    SsFCALL.control[12] = &dmy_SsContResetAll;
    SsFCALL.control[2] = &dmy_SsContDataEntry;
    SsFCALL.ccentry[0] = &dmy_SsSetNrpnVabAttr0;
    SsFCALL.ccentry[1] = &dmy_SsSetNrpnVabAttr1;
    SsFCALL.ccentry[2] = &dmy_SsSetNrpnVabAttr2;
    SsFCALL.ccentry[3] = &dmy_SsSetNrpnVabAttr3;
    SsFCALL.ccentry[4] = &dmy_SsSetNrpnVabAttr4;
    SsFCALL.ccentry[5] = &dmy_SsSetNrpnVabAttr5;
    SsFCALL.ccentry[6] = &dmy_SsSetNrpnVabAttr6;
    SsFCALL.ccentry[7] = &dmy_SsSetNrpnVabAttr7;
    SsFCALL.ccentry[8] = &dmy_SsSetNrpnVabAttr8;
    SsFCALL.ccentry[9] = &dmy_SsSetNrpnVabAttr9;
    SsFCALL.ccentry[10] = &dmy_SsSetNrpnVabAttr10;
    SsFCALL.ccentry[11] = &dmy_SsSetNrpnVabAttr11;
    SsFCALL.ccentry[12] = &dmy_SsSetNrpnVabAttr12;
    SsFCALL.ccentry[13] = &dmy_SsSetNrpnVabAttr13;
    SsFCALL.ccentry[14] = &dmy_SsSetNrpnVabAttr14;
    SsFCALL.ccentry[15] = &dmy_SsSetNrpnVabAttr15;
    SsFCALL.ccentry[16] = &dmy_SsSetNrpnVabAttr16;
    SsFCALL.ccentry[17] = &dmy_SsSetNrpnVabAttr17;
    SsFCALL.ccentry[18] = &dmy_SsSetNrpnVabAttr18;
    SsFCALL.ccentry[19] = &dmy_SsSetNrpnVabAttr19;
#else
    SsFCALL.noteon = &_SsNoteOn;
    SsFCALL.programchange = &_SsSetProgramChange;
    SsFCALL.metaevent = &dmy_SsGetMetaEvent;
    SsFCALL.pitchbend = &dmy_SsSetPitchBend;
    SsFCALL.control[0] = &_SsSetControlChange;
    SsFCALL.control[1] = &dmy_SsContBankChange;
    SsFCALL.control[3] = &_SsContMainVol;
    SsFCALL.control[4] = &dmy_SsContPanpot;
    SsFCALL.control[5] = &dmy_SsContDamper;
    SsFCALL.control[6] = &dmy_SsContNrpn1;
    SsFCALL.control[7] = &dmy_SsContNrpn2;
    SsFCALL.control[8] = &_SsContRpn1;
    SsFCALL.control[9] = &dmy_SsContRpn2;
    SsFCALL.control[10] = &dmy_SsContExternal;
    SsFCALL.control[11] = &dmy_SsContResetAll;
    SsFCALL.control[2] = &dmy_SsContDataEntry;
    SsFCALL.ccentry[0] = &dmy_SsSetNrpnVabAttr0;
    SsFCALL.ccentry[1] = &dmy_SsSetNrpnVabAttr1;
    SsFCALL.ccentry[2] = &dmy_SsSetNrpnVabAttr2;
    SsFCALL.ccentry[3] = &dmy_SsSetNrpnVabAttr3;
    SsFCALL.ccentry[4] = &dmy_SsSetNrpnVabAttr4;
    SsFCALL.ccentry[5] = &dmy_SsSetNrpnVabAttr5;
    SsFCALL.ccentry[6] = &dmy_SsSetNrpnVabAttr6;
    SsFCALL.ccentry[7] = &dmy_SsSetNrpnVabAttr7;
    SsFCALL.ccentry[8] = &dmy_SsSetNrpnVabAttr8;
    SsFCALL.ccentry[9] = &dmy_SsSetNrpnVabAttr9;
    SsFCALL.ccentry[10] = &dmy_SsSetNrpnVabAttr10;
    SsFCALL.ccentry[11] = &dmy_SsSetNrpnVabAttr11;
    SsFCALL.ccentry[12] = &dmy_SsSetNrpnVabAttr12;
    SsFCALL.ccentry[13] = &dmy_SsSetNrpnVabAttr13;
    SsFCALL.ccentry[14] = &dmy_SsSetNrpnVabAttr14;
    SsFCALL.ccentry[15] = &dmy_SsSetNrpnVabAttr15;
    SsFCALL.ccentry[16] = &dmy_SsSetNrpnVabAttr16;
    SsFCALL.ccentry[17] = &dmy_SsSetNrpnVabAttr17;
    SsFCALL.ccentry[18] = &dmy_SsSetNrpnVabAttr18;
    SsFCALL.ccentry[19] = &dmy_SsSetNrpnVabAttr19;
#endif

    SsInit();
    SsSetTableSize(&D_80137E0C, DEMO_ALT(3, 2), DEMO_ALT(0xA, 3));
#ifdef VERSION_EU
    SsSetTickMode(4);
#else
    SsSetTickMode(1);
#endif
    SsUtSetReverbType(2);
    while (SpuClearReverbWorkArea(2) == -1)
        ;
    SsUtReverbOn();
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

    SsUtReverbOff();
    SsUtSetReverbType(0);
    SsUtSetReverbDepth(0, 0);
    SsEnd();
    SsQuit();
}

void func_80015284(void)
{
    s8 i;

    for (i = 0; i < 4; i++) {
        if (D_8013E1C8[i] != -1) {
            SsSepClose(D_8013E1C8[i]);
            D_8013E1C8[i] = -1;
        }
    }

    for (i = 0; i < 6; i++) {
        if (D_8013E198[i] != -1) {
            SsVabClose(D_8013E198[i]);
            D_8013E198[i] = -1;
        }
    }

    for (i = 0; i < 4; i++) {
        D_8013924C[i] = 0xFF;
    }

    for (i = 0; i < 24; i++) {
        D_80139234[i] = -1;
    }
}

void func_800153D4(u8 arg0)
{
    arg0 ? SsSetStereo() : SsSetMono();
}

extern u32* D_80137E08;
s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source);
// play_sound
#ifndef MMX4_PC
#ifdef MMX4_WIN32
s8 func_800154E8(u8 arg0, u8 arg1, s32 id, struct BaseObj* source);
#else
s32 func_800154E8(u8 arg0, u8 arg1, struct BaseObj* source);
#endif
// clang-format off
s32 func_8001540C(arg0, arg1, arg2)
    u8 arg0;
    u8 arg1;
    void* arg2;
// clang-format on
{
    u8 group;
    s8 ret;
    u8 type;
    u8 count;
    u8 id;
    u8 cmd;

    if (D_8013E198[arg0 & 0x7F] == -1) {
        return -1;
    }
    group = arg0 & 0xF;
    count = ((u32)D_80141EE8[group] - (u32)D_80141F50[group]) >> 2;
    if (count - 1 < arg1) {
        return -2;
    }
    D_80137E08 = (u32*)D_80141F50[group] + arg1;
    if (*D_80137E08 == 0) {
        return -5;
    }
    cmd = *(u8*)D_80137E08;
    type = D_800F164C[cmd >> 6];
    id = cmd & 0x3F;
    if (type != 0) {
#ifdef VERSION_EU
        ret = func_800157AC(type, id, arg2);
#else
        ret = func_800157AC(type, arg1, arg2);
#endif
    } else {
#ifdef MMX4_WIN32
        ret = func_800154E8(arg0, arg1, id, arg2);
#else
        ret = func_800154E8(arg0, id, arg2);
#endif
    }
    return ret;
}
#else
INCLUDE_ASM("main/nonmatchings/55C4", func_8001540C);
#endif

#ifdef MMX4_WIN32
s8 sub_403980(u8 bank, u16 id, s32 a3, s8 pan, u8 mode, u8 priority, s16 program, s16 vag, s8 remaining, u8 ch);
void sub_403BA0(u8 ch);
u8 pc_spu_key_status(u8 voice);

s8 func_800154E8(u8 arg0, u8 arg1, s32 id, struct BaseObj* source)
{
    s8 pan;
    u8 priority;
    u8 fixed_pan;
    u8 voice;
    u8 packed3;
    u8 packed2;
    s16 vag;
    u8 packed1;
    s8 remaining;
    s16 program;

    packed1 = ((u8*)D_80137E08)[1];
    fixed_pan = packed1 >> 7;
    packed2 = ((u8*)D_80137E08)[2];
    priority = packed2 & 0xF;
    program = packed2 >> 4;
    vag = packed1 & 0x7F;
    packed3 = ((u8*)D_80137E08)[3];
    remaining = (packed3 & 0x60) >> 5;
    voice = packed3 & 0x1F;
    if (source != NULL) {
        if (arg0 & 0x80) {
            pan = source->unk2;
        } else {
            s16 x = source->x_pos.i.hi;
            s8 background = source->bg_offset;

            if (background >= 0) {
                x -= background_objects[background].x_pos.i.hi;
            }
            pan = x / 10;
            if (pan < 5) {
                pan = 5;
            }
            if (pan > 0x1B) {
                pan = 0x1B;
            }
        }
    } else {
        fixed_pan = 1;
    }
    if (!pc_spu_key_status(voice)) {
        sub_403980(arg0, arg1, id, pan, fixed_pan, priority, program, vag, remaining, voice);
        D_80139234[voice] = priority;
        return 0;
    }
    if (priority >= D_80139234[voice]) {
        sub_403BA0(voice);
        sub_403980(arg0, arg1, id, pan, fixed_pan, priority, program, vag, remaining, voice);
        D_80139234[voice] = priority;
        return 0;
    }
    return -4;
}
#elif !defined(MMX4_PC)
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
struct CollectionVagAtr {
    u32 note;
    u32 vol;
};
#ifdef MMX4_GAMECUBE
void fn_80055704(struct CollectionVagAtr* tone, s32 vab, s32 prog, s32 tone_index);
s16 fn_8005543C(s32 voice, s32 vab, s32 prog, s32 tone, s32 note, s32 fine, s32 voll, s32 volr);
s32 fn_4_D659C(s32 voice_bit);
#define collection_get_vag_attr fn_80055704
#define collection_key_on fn_8005543C
#define SpuGetKeyStatus fn_4_D659C
#else
void func_16DB20(struct CollectionVagAtr* tone, s32 vab, s32 prog, s32 tone_index);
s16 func_16DCF0(s32 voice, s32 vab, s32 prog, s32 tone, s32 note, s32 fine, s32 voll, s32 volr);
s32 func_1198A0(s64 voice_bit);
void func_16DE80(s32 voice);
#define collection_get_vag_attr func_16DB20
#define collection_key_on func_16DCF0
#define SpuGetKeyStatus func_1198A0
#define SsUtKeyOffV func_16DE80
#endif
#endif

s32 func_800154E8(u8 arg0, u8 arg1, struct BaseObj* source)
{
    s16 program;
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
    struct CollectionVagAtr tone;
#else
    VagAtr tone;
#endif
    u8 priority;
    u8 fixed_pan;
    s32 fine;
    s16 vag;
    s8 balance;
    u8 packed3;
    u8 packed2;
    s16 left;
    u8 packed1;
    s16 right;
    u8 vab;
    u8 voice;
    s8 remaining;
    s16 note;
    u8 key;
    s8 pan;

    if (source != NULL) {
        if (arg0 & 0x80) {
            pan = source->unk2;
        } else {
            s16 x = source->x_pos.i.hi;
            s8 background = source->bg_offset;

            if (background >= 0) {
                x -= background_objects[background].x_pos.i.hi;
            }
            pan = x / 10;
            if (pan < 5) {
                pan = 5;
            }
            if (pan > 0x1B) {
                pan = 0x1B;
            }
        }
    }
#ifdef MMX4_GAMECUBE
    vab = arg1 & 0xFF;
    balance = pan;
#endif
    packed1 = ((u8*)D_80137E08)[1];
    fixed_pan = (packed1 & 0x80) >> 7;
    packed2 = ((u8*)D_80137E08)[2];
    priority = packed2 & 0xF;
    program = (packed2 & 0xF0) >> 4;
    vag = packed1 & 0x7F;
    packed3 = ((u8*)D_80137E08)[3];
    remaining = (packed3 & 0x60) >> 5;
    voice = packed3 & 0x1F;
#if !defined(MMX4_GAMECUBE) && !defined(MMX4_COLLECTION)
    if (remaining >= 0) {
#endif
#ifndef MMX4_GAMECUBE
        vab = arg1;
        balance = pan;
#endif
        for (; remaining >= 0; remaining--, voice++) {
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
            collection_get_vag_attr(&tone, vab, vag, program);
            key = tone.note;
#ifdef MMX4_GAMECUBE
            note = key;
#endif
            right = left = (u8)tone.vol;
#ifdef MMX4_GAMECUBE
            fine = 0;
#endif
#else
        SsUtGetVagAtr(vab, vag, program, &tone);
        left = right = tone.vol;
#endif
            if (!fixed_pan && source != NULL) {
                if (balance < 0x10) {
                    left = (left >> 4) * balance;
                } else if (balance > 0x10) {
                    right = (left >> 4) * (0x20 - balance);
                }
            }
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
#ifndef MMX4_GAMECUBE
            note = key;
#endif
#ifndef MMX4_GAMECUBE
            fine = 0;
#endif
#else
        note = tone.min;
        fine = tone.shift;
#endif
            if (SpuGetKeyStatus(1L << voice) == 0) {
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
                SsUtKeyOffV(voice);
                collection_key_on(voice, vab, vag, program, note, fine, right, left);
#else
            SsUtKeyOnV(voice, vab, vag, program, note, fine, right, left);
#endif
                D_80139234[voice] = priority;
            } else if (priority >= D_80139234[voice]) {
#if defined(MMX4_GAMECUBE) || defined(MMX4_PS2)
                SsUtKeyOffV(voice);
                collection_key_on(voice, vab, vag, program, note, fine, right, left);
#else
            SsUtKeyOnV(voice, vab, vag, program, note, fine, right, left);
#endif
                D_80139234[voice] = priority;
            } else {
                return -4;
            }
            if (++program > 0xF) {
                vag++;
                program = 0;
            }
        }
#if !defined(MMX4_GAMECUBE) && !defined(MMX4_COLLECTION)
    }
#endif
    return 0;
}
#endif

s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source)
{
    s32 access;
    u8 slot;
    u8 priority;
    u8 fixed_pan;
    s32 sequence;

    fixed_pan = ((u8*)D_80137E08)[1] >> 7;
    priority = ((u8*)D_80137E08)[2] & 0xF;
    slot = ((u8*)D_80137E08)[2] >> 4;
    access = ((u8*)D_80137E08)[1] & 0x7F;

    if (D_8013924C[slot] != 0xFF && SsIsEos(access, D_8013924C[slot] & 0x1F) != 0) {
        if (priority < (D_8013924C[slot] >> 5)) {
            return -1;
        }
        if ((D_8013924C[slot] & 0x1F) == 0x1F) {
            SsSeqStop(access);
        } else {
            SsSepStop(access, D_8013924C[slot] & 0xF);
        }
    }
    if (type == 2) {
        sequence = ((u8*)D_80137E08)[3] & 0x1F;
        SsSepPlay(access, sequence, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = sequence | (priority << 5);
    } else {
        SsSeqPlay(access, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = (priority << 5) | 0x1F;
    }
    return 0;
}
void stop_sound(u8 arg0, u8 arg1)
{
    u8* entry;
    u8 var_s1;
    s8 var_s2;
    u8 temp_v0;

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

#ifdef MMX4_WIN32
u8 pc_spu_key_status(u8 voice);
#endif

s32 is_sound_finished(s32 arg0, struct MainObj* owner)
{
#ifdef MMX4_WIN32
    return pc_spu_key_status(D_80141F50[2][(arg0 & 0xFF) * 4 + 3] & 0x1F) == 0;
#elif defined(MMX4_GAMECUBE)
    return 0;
#else
    u8* entry = D_80141F50[2];

    entry += (arg0 & 0xFF) * 4;
    return SpuGetKeyStatus(1 << (entry[3] & 0x1F)) == 0;
#endif
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/55C4", func_80015A50);
#else
s32 func_80015A50(u8 slot)
{
    u8* state;
    s32 remaining;
    s32 amount;
    s16 result;
    s8 vab_id;
    u8* archive;
    u32 header;
    u8* vab_data;

    state = &D_80137DFC;
    if (*state != 0) {
        if (*state == 1) {
            goto transfer;
        }
        goto complete;
    }

    archive = cur_draw_info_drawenv;
    header = *(u32*)archive;
    D_80137E00.offset = 0;
    D_80137E00.remaining = ((struct SoundArchive*)archive)->unk4;
    D_80137DFD = header >> 24;
    vab_data = archive + (header & 0xFFFFFF);
    SsVabClose(D_8013E198[slot]);
    vab_id = SsVabOpenHeadSticky(vab_data, D_80137DFD, D_80141F30[slot]);
    if (vab_id == -1) {
        return -1;
    }
    D_8013E198[slot] = vab_id;
    D_80141EE8[slot] = vab_data;
    D_80141F50[slot] = ((struct SoundArchive*)cur_draw_info_drawenv)->sound_entries;
    (*state)++;

transfer:
    remaining = D_80137E00.remaining;
    amount = 0x1000;
    if (remaining < 0x1001) {
        amount = remaining;
    }
    result = SsVabTransBodyPartly(cur_draw_info_dispenv_screen_w + D_80137E00.offset, amount, D_80137DFD);
    if (result == -1) {
        return -1;
    }
    SsVabTransCompleted(1);
    D_80137E00.remaining -= amount;
    D_80137E00.offset += amount;

complete:
    if (result == D_80137DFD) {
        D_80137DFC = 0;
    }
    return result;
}
#endif

extern u8 D_800F1654[];

extern union SepBundle D_801459C8;

#ifndef VERSION_DEMO
void func_80015C10(void)
{
    u8 var_s1;
    s8 temp_a0;
    s32* offset;

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

    offset = &D_801459C8.offsets[1];
    D_8013E1C8[1] = SsSepOpenJ((u_long*)&D_801459C8.raw[*offset], D_8013E198[1], 2);

    for (var_s1 = 0; var_s1 < 2; var_s1++) {
        SsSepSetVol(D_8013E1C8[1], var_s1, 0x7F, 0x7F);
    }
}
#endif

#endif
