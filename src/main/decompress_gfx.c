// 80016FF4..800170B0
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

void decompress_gfx(u16* src, u16* dest);
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

extern /* The final record continues into g_BootTransitionDataRegion. */ s16 D_800F1C08[2];

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

void func_80012D68(u32* src, u32* dst, s32 count);

#ifndef MMX4_PC
#endif

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

#ifndef MMX4_PC
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
#endif

#ifndef MMX4_SATURN
void decompress_gfx(u16* src, u16* dest)
{
    u16* copy_src;
    s32 arg2;
    u32 var_v1;
    u32 var_t1;
    u32 var_t0;
    u32 upper_bits;
    s32 var_a3;
start:
    var_t1 = *(src++);

    var_t0 = 0x8000;
    for (var_a3 = 0x10; var_a3 != 0; var_t0 >>= 1, var_a3--) {
        if (!(var_t0 & var_t1)) {
            *(dest++) = *(src++);
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
#endif
