#ifndef MMX4_TESTS_PLAYER_CASES_H
#define MMX4_TESTS_PLAYER_CASES_H
#include "main/player_animations_2.h"
#include "main/55C4.h"

static struct Unk_unk68 player_box = { 0, 0, 4, 4 };
static u8 player_tiles[256];
static u16 player_pixels[512];
static u32 player_attrs[1];
static s32 player_gfx[4] = { 8, 12, 0x11223344, 0x55667788 };
static s32 player_sprites[12] = { 24, 28, 32, 36, 40, 44, 1, 2, 3, 4, 5, 6 };
static Palette player_bank[8];
static u16 player_palettes[0x200];
static u32 player_extra;
#define pl g_Player

static void player_reset(u8 step, u8 phase, u8 animation)
{
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(player_tiles, 1, sizeof(player_tiles));
    pl.active = 0x41;
    pl.unk2 = 1;
    pl.state = 1;
    pl.unk68 = &player_box;
    pl.x_pos.i.hi = 100;
    pl.y_pos.i.hi = 200;
    pl.animation_table = (u32**)D_8011AFF0;
    set_animation(&pl, animation);
    pl.unk5 = step;
    pl.unk6 = phase;
    D_8013E198[0] = D_8013E198[1] = -1;
    SP_BG_TILEMAP = player_tiles;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)player_pixels;
    TEST_BG_TILE_ATTRS = (u8*)player_attrs;
    TEST_PLAYER_GFX = (u8*)player_gfx;
    TEST_SPRITE_FRAMES = (u8*)player_sprites;
    TEST_PALETTE = (u8*)&player_palettes[1];
    TEST_PALETTE_BANK = (u8*)player_bank;
}

static u32 player_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[8];
    player_extra = 0;
    run();
    seen[0] = (u8)pl.unk5 | (u8)pl.unk6 << 8 | (u8)pl.attacking << 16 | (u32)(u8)pl.air_state << 24;
    seen[1] = pl.x_pos.val;
    seen[2] = pl.y_pos.val;
    seen[3] = pl.x_vel.val;
    seen[4] = pl.y_vel.val;
    seen[5] = pl.unk28 ^ (u32)pl.unk2C << 8;
    seen[6] = pl.previous_animation_index | (u8)pl.unk15 << 8 | (u8)pl.spike_immune << 16 | (u32)(u8)pl.combo << 24;
    seen[7] = player_extra ^ (weapon_objects[0].active | misc_objects[0].active << 8);
    return c_test_observe(0, row, seen, expected, 8);
}

#endif
