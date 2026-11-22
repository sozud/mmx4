// 800170B0..80017340
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

extern RECT D_800F1AD0;
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

extern RECT D_800F1AD0;
#endif

#ifndef MMX4_SATURN
extern RECT D_800F1AD0;

#ifndef VERSION_DEMO
void func_800170B0(void)
{
    LoadImage(&D_800F1AD0, SP_VRAM_IMAGE);
}

void func_800170E0(void)
{
    need_palette_load |= 1;
}

#endif
extern u16* D_80139578;
extern SPRT_16* D_8013957C;
extern DR_TPAGE D_80139580[2];
void func_80017268(s16 x_start);
void func_80017100(void)
{
    DR_TPAGE* page;

#ifdef VERSION_DEMO
    LoadImage(&D_800F1AD0, SP_VRAM_IMAGE);
#endif
    D_80139578 = (u16*)SP_ARC_34;
    D_8013957C = D_8015D9D0[SP_DRAW_BUFFER].sprites;
    page = &D_80139580[SP_DRAW_BUFFER];
    setlen(page, 1);
#ifdef VERSION_EU
    page->code[0] = 0xE100001D;
#else
    page->code[0] = (GetGraphType() == 1 || GetGraphType() == 2)
        ? ((GetGraphType() == 1 || GetGraphType() == 2) ? 0xE100002D : 0xE100001D)
        : ((GetGraphType() == 1 || GetGraphType() == 2) ? 0xE100002D : 0xE100001D);
#endif
    setaddr(page, D_8013957C);
    func_80017268(0);
    func_80017268(0x100);
    setaddr(D_8013957C - 1, getaddr(&cur_draw_info->ordering_table.ui));
    setaddr(&cur_draw_info->ordering_table.ui, page);
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/image_load", func_80017268);
#else
void func_80017268(s16 x_start)
{
    SPRT_16* sprite = D_8013957C;
    u32 row;
    u32 column;
    s16 x;
    s16 y = 0;
    u16 tile;
    u8 lo;
    u8 u;

    for (row = 0; row < 16; row++, y += 16) {
        x = x_start;
        for (column = 0; column < 16; column++, x += 16) {
            tile = *D_80139578++;
            if (x >= 0x140)
                continue;
            lo = tile;
            do {
            } while (0);
            u = (lo & 0xF) << 4;
            sprite->x0 = x;
            sprite->clut = (tile >> 12) | 0x7900;
            sprite->code &= 0xFD;
            sprite->v0 = lo & 0xF0;
            sprite->u0 = u;
            sprite->y0 = y;
            setaddr(sprite, sprite + 1);
            sprite++;
        }
    }
    D_8013957C = sprite;
}
#endif
#endif
