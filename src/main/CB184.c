// 800DA984..800DAE8C
#include "common.h"
#include "main/layers/layer_07_space_port_parallax.h"
#include "main/CB184.h"
#include "main/tile_effects.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#include "saturn/game_low.h"
#endif

extern struct TileEffectRecord** tile_effect_tables[26];

u8 tile_effect_is_visible(s16, s16, s16, s16);
void tile_effect_write_tile(struct TileEffectRecord*, s32, s32, s32);
void func_800DADA0(struct TileEffectRecord*, u16, u16, u8, u8);

void space_port_parallax_update(struct LayerObj* arg0);

void space_port_parallax_init(struct LayerObj* arg0);

void space_port_parallax_main(struct LayerObj* arg0);

void space_port_parallax_despawn(struct LayerObj* arg0);

#define UPDATE_XY(C)   \
    do {               \
        if (C) {       \
            x += 0x10; \
        } else {       \
            y += 0x10; \
        }              \
    } while (0)

#ifdef MMX4_SATURN
static u8* tile_effect_staging(void)
{
    return saturn_tile_staging + (s16)(saturn_vdp2_field * SATURN_TILE_STAGING_BANK_BYTES);
}

static void tile_effect_flush(u32 horizontal)
{
    u8* staging = tile_effect_staging();

    if (horizontal) {
        saturn_transfer_profile_secondary(SATURN_TILE_TRANSFER_ADD, SATURN_TILE_TRANSFER_ROW, 1);
        saturn_transfer_enqueue_secondary((u32)(staging + saturn_tile_run_start), saturn_tile_run_destination, saturn_tile_run_length);
    } else {
        saturn_transfer_profile_secondary(SATURN_TILE_TRANSFER_ADD, SATURN_TILE_TRANSFER_COLUMN, 1);
        saturn_transfer_enqueue_secondary((u32)(staging + saturn_tile_run_start), saturn_tile_run_destination, saturn_tile_run_length);
        saturn_transfer_enqueue_secondary((u32)(staging + saturn_tile_column_start), saturn_tile_run_destination + 2, saturn_tile_run_length);
    }
}

static void tile_effect_run(u8 effect_id, s16 x_offset, s16 y_offset, u32 alternate)
{
    struct TileEffectRecord* record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][effect_id];

    while (1) {
        u32 horizontal = record->packed_count & 1;
        u8 count = record->packed_count >> 1;
        s16 bg_x = background_objects[record->layer].x_pos.i.hi;
        s16 bg_y = background_objects[record->layer].y_pos.i.hi;
        s16 x = x_offset + record->x;
        s16 y = y_offset + record->y;
        u8* staging;
        u8 index;

        saturn_tile_run_state = 0;
        saturn_tile_run_length = 0;
        if (alternate) {
            saturn_tile_screen_state = 0;
        }
        staging = tile_effect_staging();
        if (horizontal) {
            if (saturn_tile_staging_offset & 3) {
                saturn_tile_staging_offset += 2;
            }
            saturn_tile_staging_cursor = (u32*)(staging + saturn_tile_staging_offset);
        } else {
            saturn_tile_column_high = (u16*)(staging + saturn_tile_staging_offset);
            saturn_tile_column_low = (u16*)(staging + saturn_tile_column_offset);
        }
        for (index = 0; index != count; index++) {
            u8 visible = tile_effect_is_visible(bg_x, bg_y, x, y);

            if (visible) {
                if (alternate) {
                    saturn_tile_effect_write_alternate((struct SaturnTileEffect*)record, (u16)(x / 16), (u16)(y / 16), index);
                } else {
                    saturn_tile_effect_write((struct SaturnTileEffect*)record, (u16)(x / 16), (u16)(y / 16), index);
                }
                saturn_tile_run_length += horizontal ? 4 : 2;
            } else if (alternate) {
                saturn_tile_effect_set((struct SaturnTileEffect*)record, (u16)(x / 16), (u16)(y / 16), index);
            }
            if (horizontal) {
                x += 0x10;
            } else {
                y += 0x10;
            }
            if (saturn_tile_run_state == 2) {
                tile_effect_flush(horizontal);
                saturn_tile_run_state = 0;
                saturn_tile_run_length = 0;
            }
        }
        if (saturn_tile_run_state != 0) {
            tile_effect_flush(horizontal);
        }
        if (!record->has_next) {
            break;
        }
        record++;
    }
}

void refresh_visible_tile_effect(s32 effect_id, s32 x_offset, s32 y_offset)
{
    tile_effect_run((u8)effect_id, (s16)x_offset, (s16)y_offset, 0);
}

#define TILE_CAMERA_STRIDE 84
#define TILE_CAMERA_PLANE 0x4B
#define TILE_PAGE_COLUMNS 32
#define TILE_NEXT_PAGE 0xF80
#define TILE_INDEX_MASK 0x3FFF
#define TILE_FLIP_MASK 0xC000
#define TILE_CELL_MASK 0xFFFFFF
#define TILE_SCREEN_SHIFT 9
#define TILE_HORIZONTAL 1
#define RUN_IDLE 0
#define RUN_OPEN 1
#define RUN_FULL 2

extern u8 saturn_sprite_cameras[];
extern u8 saturn_stage_layout_width;
extern u8 saturn_stage_layout_height;
extern s16 saturn_stage_layout_size;
extern u8* saturn_stage_screens;
extern u8* saturn_stage_screen_tiles;
extern u32* saturn_stage_tile_cells;
u32 saturn_tile_planes[3] = {
    0x25e70000,
    0x25e74000,
    0x25e78000,
};
u32 saturn_tile_planes_alternate[3] = {
    0x25e70000,
    0x25e74000,
    0x25e78000,
};
extern u32 saturn_tile_run_destination;
extern u32* saturn_tile_staging_cursor;
extern u16 saturn_tile_staging_offset;
extern u16 saturn_tile_column_offset;
extern u16* saturn_tile_column_high;
extern u16* saturn_tile_column_low;
extern u16* saturn_tile_source;
extern u16 saturn_tile_run_start;
extern u16 saturn_tile_column_start;
extern u16 saturn_tile_column;
extern u16 saturn_tile_row;
extern u8 saturn_tile_run_state;
extern u8 saturn_tile_screen_state;

static u32 tile_cell(u16 tile)
{
    return (saturn_stage_tile_cells[tile & TILE_INDEX_MASK] & TILE_CELL_MASK) | ((u32)(tile & TILE_FLIP_MASK) << 14);
}

static s16 tile_screen(struct SaturnTileEffect* effect, u16 column, u16 row)
{
    s16 screen = (s16)(saturn_stage_layout_width * ((s32)(row >> 4) % saturn_stage_layout_height) + (s32)(column >> 4) % saturn_stage_layout_width);
    return (s16)(screen + effect->camera * saturn_stage_layout_size);
}

static u16* tile_pointer(s16 screen)
{
    return (u16*)(saturn_stage_screen_tiles + (saturn_stage_screens[screen] << TILE_SCREEN_SHIFT) + ((saturn_tile_row & 15) << 5) + ((saturn_tile_column & 15) << 1));
}

static void tile_open_run(struct SaturnTileEffect* effect, u16 column, u16 row, u32* planes)
{
    s16 screen;
    u8* camera;
    saturn_tile_column = (u16)(column & 63);
    saturn_tile_row = (u16)(row & 31);
    screen = tile_screen(effect, column, row);
    camera = saturn_sprite_cameras + (u8)(effect->camera * TILE_CAMERA_STRIDE);
    if ((s16)saturn_tile_column < TILE_PAGE_COLUMNS) {
        saturn_tile_run_destination = planes[(s8)camera[TILE_CAMERA_PLANE]] + (s16)saturn_tile_column * 4;
    } else {
        saturn_tile_run_destination = planes[(s8)camera[TILE_CAMERA_PLANE]] + (s16)saturn_tile_column * 4 + TILE_NEXT_PAGE;
    }
    saturn_tile_run_destination += (s16)saturn_tile_row << 7;
    saturn_tile_source = tile_pointer(screen);
    saturn_tile_run_start = saturn_tile_staging_offset;
    saturn_tile_column_start = saturn_tile_column_offset;
    saturn_tile_run_state = RUN_OPEN;
}

static void tile_stage(struct SaturnTileEffect* effect, u8 tile, u32 clear_screen)
{
    u32* cursor;
    u32 cell;
    *saturn_tile_source = effect->tiles[tile];
    if (effect->flags & TILE_HORIZONTAL) {
        saturn_tile_column++;
        if (((s16)saturn_tile_column & 15) == 0) {
            if (clear_screen) {
                saturn_tile_screen_state = 0;
            }
            saturn_tile_run_state = RUN_FULL;
        }
        cursor = saturn_tile_staging_cursor;
        saturn_tile_staging_cursor = cursor + 1;
        *cursor = tile_cell(*saturn_tile_source);
        saturn_tile_staging_offset += 4;
        saturn_tile_source++;
    } else {
        saturn_tile_row++;
        if (((s16)saturn_tile_row & 15) == 0) {
            if (clear_screen) {
                saturn_tile_screen_state = 0;
            }
            saturn_tile_run_state = RUN_FULL;
        }
        cell = tile_cell(*saturn_tile_source);
        *saturn_tile_column_high++ = (u16)(cell >> 16);
        *saturn_tile_column_low++ = (u16)cell;
        saturn_tile_staging_offset += 2;
        saturn_tile_column_offset += 2;
        saturn_tile_source += 16;
    }
}

void saturn_tile_effect_write(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile)
{
    if (saturn_tile_run_state == RUN_IDLE) {
        tile_open_run(effect, column, row, saturn_tile_planes);
    }
    tile_stage(effect, tile, 0);
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/CB184", refresh_visible_tile_effect);
#else
void refresh_visible_tile_effect(s32 effect_id, s32 x_offset, s32 y_offset)
{
    struct TileEffectRecord* record;
    u16 origin_x = x_offset;
    u16 origin_y = y_offset;

    record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][effect_id & 0xFF];
    while (1) {
        s16 x = (u16)record->x + origin_x;
        s16 y = (u16)record->y + origin_y;
        u8 index = record->layer; /* Reused as the tile index below. */
        u8 horizontal = record->packed_count;
        u32 tile_count = horizontal >> 1;
        s32 byte_mask = 0xFF;
        s16 bg_x = background_objects[index].x_pos.u.hi;
        s16 bg_y = background_objects[index].y_pos.u.hi;

        horizontal &= 1; /* Low bit selects horizontal (1) or vertical (0). */
        for (index = 0; index != tile_count; index++) {
            s16 tile_x = x;
            s16 tile_y = y;
            if (tile_effect_is_visible(bg_x, bg_y, tile_x, tile_y)) {
                tile_effect_write_tile(record, (u16)(tile_x / 16), (u16)(tile_y / 16), (u8)index);
            }
            UPDATE_XY(horizontal & byte_mask);
        }
        if (!record->has_next) {
            break;
        }
        record++;
    }
}
#endif

u8 tile_effect_is_visible(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    if (((arg0 - 0x20) <= arg2) && ((arg0 + 0x160) > arg2) && ((arg1 - 0x20) <= arg3) && ((arg1 + 0x110) > arg3)) {
        return 1;
    }
    return 0;
}

#ifndef MMX4_SATURN
void tile_effect_write_tile(struct TileEffectRecord* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    D_801441C8[arg0->layer][arg2 & 0x1F][arg1 & 0x1F] = arg0->tiles[arg3 & 0xFF];
}
#endif

#ifdef MMX4_SATURN
void apply_tile_effect(u8 effect_id, s32 x_offset, s32 y_offset)
{
    tile_effect_run(effect_id, (s16)x_offset, (s16)y_offset, 1);
}

void saturn_tile_effect_write_alternate(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile)
{
    if (saturn_tile_run_state == RUN_IDLE) {
        tile_open_run(effect, column, row, saturn_tile_planes_alternate);
        saturn_tile_screen_state = 1;
    }
    tile_stage(effect, tile, 1);
}

void saturn_tile_effect_set(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile)
{
    if (saturn_tile_screen_state == 0) {
        saturn_tile_column = (u16)(column & 63);
        saturn_tile_row = (u16)(row & 31);
        saturn_tile_source = tile_pointer(tile_screen(effect, column, row));
        saturn_tile_screen_state = 1;
    }
    *saturn_tile_source = effect->tiles[tile];
    if (effect->flags & TILE_HORIZONTAL) {
        saturn_tile_column++;
        if (((s16)saturn_tile_column & 15) == 0) {
            saturn_tile_run_state = saturn_tile_run_state == RUN_OPEN ? RUN_FULL : RUN_IDLE;
            saturn_tile_screen_state = 0;
        }
        saturn_tile_source++;
    } else {
        saturn_tile_row++;
        if (((s16)saturn_tile_row & 15) == 0) {
            saturn_tile_run_state = saturn_tile_run_state == RUN_OPEN ? RUN_FULL : RUN_IDLE;
            saturn_tile_screen_state = 0;
        }
        saturn_tile_source += 16;
    }
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/CB184", apply_tile_effect);
#else
void apply_tile_effect(u8 effect_id, s32 x_offset, s32 y_offset)
{
    struct TileEffectRecord* record;
    u16 origin_x = x_offset;
    u16 origin_y = y_offset;

    record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][effect_id & 0xFF];
    while (1) {
        s16 x = (u16)record->x + origin_x;
        s16 y = (u16)record->y + origin_y;
        u8 index = record->layer; /* Reused as the tile index below. */
        s16 bg_x = background_objects[index].x_pos.u.hi;
        u8 horizontal = record->packed_count;
        u32 tile_count = horizontal >> 1;
        s32 byte_mask = 0xFF;
        s16 bg_y = background_objects[index].y_pos.u.hi;

        horizontal &= 1; /* Low bit selects horizontal (1) or vertical (0). */
        for (index = 0; index != tile_count; index++) {
            s16 tile_x = x;
            s16 tile_y = y;
            u8 visible = tile_effect_is_visible(bg_x, bg_y, tile_x, tile_y);
            func_800DADA0(record, (u16)(tile_x / 16), (u16)(tile_y / 16), (u8)index, (u8)visible);
            UPDATE_XY(horizontal & byte_mask);
        }
        if (!record->has_next) {
            break;
        }
        record++;
    }
}
#endif
#undef UPDATE_XY

// tile_effect_apply_tile
INCLUDE_ASM("main/nonmatchings/CB184", func_800DADA0);
void tile_effect_nop(void)
{
}
