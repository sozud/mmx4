// 80015D60..80016334
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

extern RECT D_800F1860;
extern u16 D_800F1868[18];
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

extern RECT D_800F1658;

extern union MainPaletteData D_800F1660;

extern RECT D_800F1860;

extern u16 D_800F1868[18];

extern void (*D_800F1AB0[])(void);
#endif

s32 set_animation(void* object, s32 animation)
{
    struct AnimatedObj* arg0 = object;

    arg0->animation_cursor = arg0->animation_table[animation];
    arg0->previous_animation_index = 0xFF;
    arg0->unk17 = animation;
    arg0->animation_step.packed = *arg0->animation_cursor;
}

void set_animation_frame(struct AnimatedObj* arg0, s32 arg1, s32 arg2)
{
    arg0->animation_cursor = arg0->animation_table[arg1] + arg2;
    arg0->previous_animation_index = 0xFF;
    arg0->unk17 = arg1;
    arg0->animation_step.packed = *arg0->animation_cursor;
}

void animate_object(struct AnimatedObj* arg0)
{
    if (--arg0->animation_step.fields.duration == 0) {
        arg0->animation_cursor = &arg0->animation_cursor[arg0->animation_step.fields.relative_step];
        arg0->animation_step.packed = *arg0->animation_cursor;
    }
}

#ifndef MMX4_SATURN
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
#ifdef VERSION_DEMO
        if (need_palette_load == 1) {
            LoadImage(&D_800F1658, (u_long*)SP_PALETTE);
        } else {
#else
        if (need_palette_load & 1) {
            LoadImage(&D_800F1658, (u_long*)SP_PALETTE);
        } else if (need_palette_load & 2) {
#endif
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
    for (var_v1 = 0; var_v1 < 0x800U; var_v1++) {
        *var_a1++ = *var_a0++;
    }
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

#endif

#ifdef MMX4_SATURN
#define SCREEN_RESET_BANKS 3

void saturn_vram_clear_banks(u32 banks);
void saturn_thread_sleep(u32 frames);
void saturn_debug_text_setup(s16 wide, s16 bitmap);
extern u8 saturn_text_dirty_a;
extern u16 saturn_vdp2_shadow[];

void func_800160F4(void)
{
    u8* shadow = (u8*)saturn_vdp2_shadow;

    saturn_vram_clear_banks(SCREEN_RESET_BANKS);
    saturn_thread_sleep(1);
    saturn_debug_text_setup(0, 1);
    saturn_text_dirty_a = 1;
    need_palette_load |= 1;
    saturn_thread_sleep(1);
    *(u32*)(shadow + 0x70) = 0;
    *(u32*)(shadow + 0x80) = 0;
    *(u16*)(shadow + 0x90) = 0;
    *(u32*)(shadow + 0x74) = 0;
    *(u32*)(shadow + 0x84) = 0;
    *(u16*)(shadow + 0x92) = 0;
}
#else
void func_800160F4(void)
{
    LoadImage(&D_800F1860, &D_800F1660);
}
#endif

#ifdef VERSION_DEMO
extern DR_MODE D_800F37A0_demo[2][2];
extern SPRT D_800F37D0_demo[2][2];

void func_80018000(void)
{
    u8 i;

    for (i = 0; i < 2; i++) {
        SetDrawMode(&D_800F37A0_demo[SP_DRAW_BUFFER][i], 0, 0, GetTPage(1, 0, i != 0 ? 0x1C0 : 0x140, 0), 0);
        SetSprt(&D_800F37D0_demo[SP_DRAW_BUFFER][i]);
        setXY0(&D_800F37D0_demo[SP_DRAW_BUFFER][i], i != 0 ? 0x100 : 0, 0);
        setUV0(&D_800F37D0_demo[SP_DRAW_BUFFER][i], 0, 0);
        D_800F37D0_demo[SP_DRAW_BUFFER][i].clut = GetClut(0, 0x1E0);
        setShadeTex(&D_800F37D0_demo[SP_DRAW_BUFFER][i], 1);
        setSemiTrans(&D_800F37D0_demo[SP_DRAW_BUFFER][i], 0);
        D_800F37D0_demo[SP_DRAW_BUFFER][i].w = i != 0 ? 0x40 : 0x100;
        D_800F37D0_demo[SP_DRAW_BUFFER][i].h = 0xF0;
        catPrim(&D_800F37A0_demo[SP_DRAW_BUFFER][i], &D_800F37D0_demo[SP_DRAW_BUFFER][i]);
        addPrims(cur_draw_info->ordering_table.mid, &D_800F37A0_demo[SP_DRAW_BUFFER][i],
            &D_800F37D0_demo[SP_DRAW_BUFFER][i]);
    }
}
#elif !defined(MMX4_SATURN)

extern DR_MODE D_80139250[2];
extern SPRT D_80139268[2][17];
void func_80016124(void)
{
    SPRT* sprite = D_80139268[SP_DRAW_BUFFER];
    DR_MODE* draw_mode = &D_80139250[SP_DRAW_BUFFER];
    u16 x = 0;
    s16 y = 0;
    u8 i;

    for (i = 0; i < 17; sprite++, i++) {
        setSprt(sprite);
        switch ((s16)D_800F1868[i]) {
        case 0:
            setUV0(sprite, 0x00, 0xD0);
            sprite->w = 0x70;
            break;
        case 1:
            setUV0(sprite, 0x70, 0xD0);
            sprite->w = 0x60;
            break;
        case 2:
            setUV0(sprite, 0x00, 0xD0);
            sprite->w = 0x10;
            break;
        }
        sprite->clut = 0x784C;
        sprite->h = 0x30;
        setXY0(sprite, x, y);
        setShadeTex(sprite, 1);
        setSemiTrans(sprite, 0);
        x += sprite->w;
        if (x >= 0x140) {
            y += 0x30;
            x = 0;
        }
        addPrim(&cur_draw_info->ordering_table.ui, sprite);
    }

    SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x380, 0x100), 0);
    addPrim(&cur_draw_info->ordering_table.ui, draw_mode);
}
#endif
