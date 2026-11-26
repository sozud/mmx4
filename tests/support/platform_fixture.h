#ifndef MMX4_TESTS_PLATFORM_FIXTURE_H
#define MMX4_TESTS_PLATFORM_FIXTURE_H
#include "test_runtime.h"
#include "support/test_pad.h"
#include "main/2824.h"

#ifdef MMX4_SATURN
#define TEST_PAD_PREVIOUS saturn_pad_previous
#else
#define TEST_PAD_PREVIOUS controller_input.previous
#endif

#define TEST_DRAWN_LAYER VISUAL_SATURN_LAYER(5)
#define TEST_FACING(psx) ((u8)(psx)&0x40 ? ((u8)(psx) & ~0x40) | PLAYER_FACING_RIGHT : (u8)(psx))
#define TEST_FADE_AMOUNT(amount, before) TEST_FADE_OUT_AMOUNT(amount, before)
#ifdef MMX4_SATURN
#define TEST_PSX_LAYER(layer) ((u8)(layer)&0x40 ? ((u8)(layer) & ~0x40) | 4 : (u8)(layer))
#else
#define TEST_PSX_LAYER(layer) ((u8)(layer))
#endif

#ifdef MMX4_SATURN
void saturn_sprite_reset_queues(void);
#define test_next_frame() saturn_sprite_reset_queues()
#else
#define test_next_frame() ((void)0)
#endif

#ifdef MMX4_SATURN
#define TEST_PSX_HALF(value) ((u16)((((value) >> 8) & 0xFF) | (((value)&0xFF) << 8)))
#else
#define TEST_PSX_HALF(value) ((u16)(value))
#endif
#define TEST_LE_HALVES(pointer) ((u32)((const u16*)(pointer))[0] | (u32)((const u16*)(pointer))[1] << 16)
#define TEST_SET_HALVES(field, first, second) \
    (((s16*)&(field))[0] = (s16)(first), ((s16*)&(field))[1] = (s16)(second))

static void test_stage_graphics(u32* offsets)
{
    D_801406A8 = offsets;
#ifdef MMX4_SATURN
    saturn_stage_graphics_offsets_pointer = offsets;
#endif
}

static void test_stage_screen(void* tilemap, void* pixels, void* attrs)
{
    SP_BG_TILEMAP = (u8*)tilemap;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
}

static void test_layer_screens(u32 layer, u32 columns, u32 rows)
{
#ifdef MMX4_SATURN
    background_objects[layer].unk4D = 0;
    background_objects[layer].unk4E = columns - 1;
    background_objects[layer].min_y = 0;
    background_objects[layer].max_y = rows - 1;
#else
    (void)layer;
    (void)columns;
    (void)rows;
#endif
}

static u16 test_pad_bits(u16 game)
{
    u16 raw = 0;
    u32 i;
    for (i = 0; i < 16; i++)
        if (game & (1u << i))
            raw |= D_800EE430[i];
    return raw;
}

#ifdef MMX4_SATURN
static u16 test_pad_from_psx(u16 psx)
{
    static const u16 psx_table[11] = { 0x2000, 0x8000, 0x1000, 0x4000, 0x0080, 0x0010, 0x0002, 0x0040, 0x0020, 0x0008, 0x0004 };
    u16 raw = 0;
    u32 i;
    for (i = 0; i < 11; i++)
        if (psx & psx_table[i])
            raw |= D_800EE430[i];
    return raw;
}
#else
#define test_pad_from_psx(psx) ((u16)(psx))
#endif

static void test_pad_game(u16 held, u16 previous, u16 pressed)
{
    TEST_PAD_HELD = test_pad_bits(held);
    TEST_PAD_PREVIOUS = test_pad_bits(previous);
    TEST_PAD_PRESSED = test_pad_bits(pressed);
}
#endif
