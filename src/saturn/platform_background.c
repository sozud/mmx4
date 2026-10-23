#include "common.h"
#include "saturn/platform.h"

void saturn_sprite_draw_passes(void);

#define BG_CAMERA_STRIDE 84
#define BG_CAMERA_COUNT 3
#define BG_ACTIVE 0x00
#define BG_LAYER 0x02
#define BG_X 0x08
#define BG_Y 0x0C
#define BG_PREVIOUS_X 0x14
#define BG_PREVIOUS_Y 0x18
#define BG_PLANE 0x4B
#define BG_REDRAW 0x4C
#define BG_FIRST_COLUMN 0x4D
#define BG_LAST_COLUMN 0x4E
#define BG_FIRST_ROW 0x4F
#define BG_LAST_ROW 0x50
#define BG_SCREEN_SHIFT 9
#define BG_SCREEN_TILES 16
#define BG_PAGE_COLUMNS 32
#define BG_PAGE_ROWS 32
#define BG_ROW_BYTES 0x80
#define BG_NEXT_PAGE 0xF80
#define BG_WRAP_PAGE (-0x420)
#define BG_PAGE_UP (-0x400)
#define BG_TILE_MASK 0x3FFF
#define BG_FLIP_MASK 0xC000
#define BG_CELL_MASK 0xFFFFFF
#define BG_REDRAW_COLUMNS 23
#define BG_REDRAW_ROWS 18
#define BG_RIGHT_EDGE 0x14F
#define BG_BOTTOM_EDGE 0xFF
#define BG_EDGE 16
#define BG_RUN_IDLE 0
#define BG_RUN_OPEN 1
#define BG_RUN_FULL 2
#define BG_TRANSFER_ADD 0x100
#define VDP2_SCXIN0 0x70
#define VDP2_SCYIN0 0x74
#define VDP2_SCXIN1 0x80
#define VDP2_SCYIN1 0x84
#define VDP2_SCXN2 0x90
#define VDP2_SCYN2 0x92
#define STAGE_RIDE_CHASE 0x0200
#define STAGE_SPACE_PORT 0x0300
#define STAGE_SPACE_PORT_2 0x0301
#define STAGE_FINAL_WEAPON 0x0B01
#define ENGINE_MODE 0x00
#define ENGINE_STAGE_WORD 0x0C
#define ENGINE_CHECKPOINT 0x1D
#define ENGINE_MODE_DEMO 5
#define DISPLAY_MODE_DEMO 11

extern u8 saturn_engine_bytes[];
extern u8 saturn_sprite_cameras[];
extern u8 saturn_display_mode;
extern u8 saturn_stage_layout_width;
extern u8 saturn_stage_layout_height;
extern s16 saturn_stage_layout_size;
extern u8* saturn_stage_screens;
extern u8* saturn_stage_screen_tiles;
extern u32* saturn_stage_tile_cells;
extern u32 saturn_background_planes[3];
extern u32 saturn_background_tile_planes[3];
extern u8* saturn_background_layouts[];
extern u8 saturn_background_layout[];
extern u32 saturn_background_scroll_word;
extern u16 saturn_background_redraw_word;
extern u16 saturn_background_staging_offset;
extern u16 saturn_background_tile_column;
extern u16 saturn_background_tile_row;
extern u32 saturn_background_run_destination;
extern u32* saturn_background_staging_cursor;
extern u8 saturn_background_staging[];
extern u16* saturn_background_tile_source;
extern u16 saturn_background_run_start;
extern u8 saturn_background_run_state;
extern u16 saturn_background_run_bytes;
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, u32 attribute_index);

#define CAMERA(index) (saturn_sprite_cameras + (u8)((index)*BG_CAMERA_STRIDE))
#define CAMERA_WORD(camera, offset) (*(s16*)((camera) + (offset)))
#define CAMERA_LONG(camera, offset) (*(s32*)((camera) + (offset)))
#define SHADOW_WORD(offset) (*(s16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW_LONG(offset) (*(s32*)((u8*)saturn_vdp2_shadow + (offset)))

u32 saturn_background_planes[3] = {
    0x25e70000,
    0x25e74000,
    0x25e78000,
};

u32 saturn_background_tile_planes[3] = {
    0x25e70000,
    0x25e74000,
    0x25e78000,
};

static void background_redraw_at(u8* camera, s32 x, s32 y)
{
    CAMERA_LONG(camera, BG_X) = x;
    CAMERA_LONG(camera, BG_Y) = y;
    saturn_background_redraw(1);
}

void saturn_background_refresh(void)
{
    u8* camera;
    s32 x;
    s32 y;
    u16 stage;
    saturn_background_redraw(0);
    stage = *(u16*)(saturn_engine_bytes + ENGINE_STAGE_WORD);
    camera = CAMERA(1);
    if (stage == STAGE_SPACE_PORT || stage == STAGE_SPACE_PORT_2) {
        if (saturn_engine_bytes[ENGINE_CHECKPOINT] == 0) {
            x = CAMERA_LONG(camera, BG_X);
            y = CAMERA_LONG(camera, BG_Y);
            background_redraw_at(camera, 0, 0x3000000);
            CAMERA_LONG(camera, BG_Y) = 0x2000000;
            saturn_background_redraw(1);
            CAMERA_LONG(camera, BG_X) = 0x2000000;
            saturn_background_redraw(1);
            CAMERA_LONG(camera, BG_X) = x;
            CAMERA_LONG(camera, BG_Y) = y;
        } else {
            saturn_background_redraw(1);
        }
    } else if (stage == STAGE_FINAL_WEAPON) {
        x = CAMERA_LONG(camera, BG_X);
        y = CAMERA_LONG(camera, BG_Y);
        background_redraw_at(camera, 0, 0x2000000);
        CAMERA_LONG(camera, BG_X) = 0x2000000;
        saturn_background_redraw(1);
        CAMERA_LONG(camera, BG_Y) = 0x1000000;
        saturn_background_redraw(1);
        CAMERA_LONG(camera, BG_X) = 0;
        saturn_background_redraw(1);
        CAMERA_LONG(camera, BG_X) = x;
        CAMERA_LONG(camera, BG_Y) = y;
    } else {
        saturn_background_redraw(1);
    }
    if (stage == STAGE_RIDE_CHASE) {
        camera = CAMERA(2);
        CAMERA_LONG(camera, BG_X) = 0;
        CAMERA_LONG(camera, BG_Y) = 0x1000000;
        saturn_background_redraw(2);
        CAMERA_LONG(camera, BG_Y) = 0x1F00000;
        saturn_background_redraw(2);
        CAMERA_LONG(camera, BG_X) = 0x1400000;
        CAMERA_LONG(camera, BG_Y) = 0x1000000;
        saturn_background_redraw(2);
        CAMERA_LONG(camera, BG_Y) = 0x1F00000;
        saturn_background_redraw(2);
        if (saturn_engine_bytes[ENGINE_MODE] == ENGINE_MODE_DEMO) {
            saturn_display_mode = DISPLAY_MODE_DEMO;
        }
        return;
    }
    saturn_background_redraw(2);
}

static void background_set_scroll(u8* camera)
{
    switch (camera[BG_PLANE]) {
    case 0:
        SHADOW_LONG(VDP2_SCXIN0) = CAMERA_LONG(camera, BG_X);
        SHADOW_LONG(VDP2_SCYIN0) = CAMERA_LONG(camera, BG_Y);
        break;
    case 1:
        SHADOW_LONG(VDP2_SCXIN1) = CAMERA_LONG(camera, BG_X);
        SHADOW_LONG(VDP2_SCYIN1) = CAMERA_LONG(camera, BG_Y);
        break;
    case 2:
        SHADOW_WORD(VDP2_SCXN2) = CAMERA_WORD(camera, BG_X);
        SHADOW_WORD(VDP2_SCYN2) = CAMERA_WORD(camera, BG_Y);
        break;
    }
}

void saturn_background_redraw(u32 index)
{
    struct SaturnBackgroundStrip strip;
    u8* camera = CAMERA(index);
    s16 column;
    s16 row;
    s16 i;
    strip.camera = camera;
    if (camera[BG_ACTIVE] == 0) {
        return;
    }
    column = (s16)(CAMERA_WORD(camera, BG_X) / 16 - 1);
    row = (s16)(CAMERA_WORD(camera, BG_Y) / 16 - 1);
    strip.width = BG_REDRAW_COLUMNS;
    strip.height = 0;
    for (i = 0; i < BG_REDRAW_ROWS; i++) {
        strip.column = column;
        strip.row = row++;
        saturn_background_draw_strip(&strip);
    }
    CAMERA_LONG(camera, BG_PREVIOUS_X) = CAMERA_LONG(camera, BG_X);
    CAMERA_LONG(camera, BG_PREVIOUS_Y) = CAMERA_LONG(camera, BG_Y);
    background_set_scroll(camera);
}

static void background_edge(struct SaturnBackgroundStrip* strip, s32 x, s32 y, s16 width, s16 height)
{
    strip->column = (s16)(x / 16);
    strip->row = (s16)(y / 16);
    strip->width = width;
    strip->height = height;
    saturn_background_draw_strip(strip);
}

void saturn_background_scroll(u8* camera)
{
    struct SaturnBackgroundStrip strip;
    strip.camera = camera;
    if (CAMERA_WORD(camera, BG_X) > CAMERA_WORD(camera, BG_PREVIOUS_X)) {
        background_edge(&strip, CAMERA_WORD(camera, BG_X) + BG_RIGHT_EDGE, CAMERA_WORD(camera, BG_Y) - BG_EDGE, 0, BG_REDRAW_ROWS);
    }
    if (CAMERA_WORD(camera, BG_X) < CAMERA_WORD(camera, BG_PREVIOUS_X)) {
        background_edge(&strip, CAMERA_WORD(camera, BG_X) - BG_EDGE, CAMERA_WORD(camera, BG_Y) - BG_EDGE, 0, BG_REDRAW_ROWS);
    }
    if (CAMERA_WORD(camera, BG_Y) > CAMERA_WORD(camera, BG_PREVIOUS_Y)) {
        background_edge(&strip, CAMERA_WORD(camera, BG_X) - BG_EDGE, CAMERA_WORD(camera, BG_Y) + BG_BOTTOM_EDGE, BG_REDRAW_COLUMNS, 0);
    }
    if (CAMERA_WORD(camera, BG_Y) < CAMERA_WORD(camera, BG_PREVIOUS_Y)) {
        background_edge(&strip, CAMERA_WORD(camera, BG_X) - BG_EDGE, CAMERA_WORD(camera, BG_Y) - BG_EDGE, BG_REDRAW_COLUMNS, 0);
    }
    background_set_scroll(camera);
}

static u16* background_screen_tiles(s32 screen)
{
    return (u16*)(saturn_stage_screen_tiles + (saturn_stage_screens[(s16)screen] << BG_SCREEN_SHIFT));
}

static s32 background_screen(u8* camera, s32 column, s32 row)
{
    return saturn_stage_layout_width * (s16)row + column + (s8)camera[BG_LAYER] * saturn_stage_layout_size;
}

static u32 background_cell(u16 tile)
{
    return (saturn_stage_tile_cells[tile & BG_TILE_MASK] & BG_CELL_MASK) | ((u32)(tile & BG_FLIP_MASK) << 14);
}

void saturn_background_draw_strip(struct SaturnBackgroundStrip* strip)
{
    u32 planes[3];
    u8* camera = strip->camera;
    s32 columns;
    s32 rows;
    s32 column;
    s16 row_cell;
    s16 row_limit;
    s16 row_page;
    s16 column_limit;
    s16 column_page;
    s32 screen_column;
    s32 screen_row;
    s32 screen;
    s32 tile_column;
    u32* cell;
    u16* tile;
    s16 i;
    planes[0] = saturn_background_planes[0];
    planes[1] = saturn_background_planes[1];
    planes[2] = saturn_background_planes[2];
    columns = (u8)camera[BG_LAST_COLUMN] - (u8)camera[BG_FIRST_COLUMN] + 1;
    rows = (s16)((u8)camera[BG_LAST_ROW] - (u8)camera[BG_FIRST_ROW] + 1);
    column = strip->column & 63;
    row_cell = (s16)(strip->row & 31);
    strip->column -= camera[BG_FIRST_COLUMN] * 16;
    strip->row -= camera[BG_FIRST_ROW] * 16;
    while (strip->column < 0) {
        strip->column += (s16)columns * 16;
    }
    while (strip->row < 0) {
        strip->row += rows * 16;
    }
    screen_column = camera[BG_FIRST_COLUMN] + (s16)(strip->column >> 4) % (s16)columns;
    screen_row = camera[BG_FIRST_ROW] + (s16)(strip->row >> 4) % rows;
    screen = background_screen(camera, screen_column, screen_row);
    if ((s16)column >= BG_PAGE_COLUMNS) {
        column_limit = 64;
        column_page = BG_WRAP_PAGE;
        cell = (u32*)(planes[camera[BG_PLANE]] + (s16)column * 4 + BG_NEXT_PAGE);
    } else {
        column_limit = 32;
        column_page = 0x3E0;
        cell = (u32*)(planes[camera[BG_PLANE]] + (s16)column * 4);
    }
    if (row_cell >= BG_SCREEN_TILES) {
        row_limit = 32;
        row_page = BG_PAGE_UP;
    } else {
        row_limit = 16;
        row_page = 0;
    }
    cell = (u32*)((u8*)cell + (row_cell << 7));
    tile_column = (column & 15) << 1;
    tile = (u16*)((u8*)background_screen_tiles(screen) + ((row_cell & 15) << 5) + tile_column);
    for (i = 0; i < strip->height; i++) {
        *cell = background_cell(*tile);
        cell = (u32*)((u8*)cell + BG_ROW_BYTES);
        row_cell++;
        tile += 16;
        if (row_cell == row_limit) {
            cell = (u32*)((u8*)cell + row_page * 4);
            if (row_limit == 16) {
                row_limit = 32;
                row_page = BG_PAGE_UP;
            } else {
                row_cell = 0;
                row_limit = 16;
                row_page = 0;
            }
            if ((s16)screen_row == camera[BG_LAST_ROW]) {
                screen_row = camera[BG_FIRST_ROW];
                screen = background_screen(camera, screen_column, screen_row);
            } else {
                screen_row++;
                screen += saturn_stage_layout_width;
            }
            tile = (u16*)((u8*)background_screen_tiles(screen) + tile_column);
        }
    }
    tile_column = (row_cell & 15) << 5;
    for (i = 0; i < strip->width; i++) {
        u16 value = *tile;
        column++;
        tile++;
        *cell++ = background_cell(value);
        if (((s16)column & 15) == 0) {
            if ((s16)column == column_limit) {
                cell = (u32*)((u8*)cell + column_page * 4);
            }
            if ((s16)screen_column == camera[BG_LAST_COLUMN]) {
                screen_column = camera[BG_FIRST_COLUMN];
                screen = background_screen(camera, screen_column, screen_row);
            } else {
                screen_column++;
                screen++;
            }
            tile = (u16*)((u8*)background_screen_tiles(screen) + tile_column);
        }
    }
}

static void background_flush_run(void)
{
    saturn_transfer_profile(BG_TRANSFER_ADD, 1, 1);
    saturn_transfer_enqueue((u32)(saturn_background_staging + saturn_background_run_start),
        saturn_background_run_destination, saturn_background_run_bytes);
}

void saturn_background_redraw_queued(u8* camera)
{
    u16 stage = *(u16*)(saturn_engine_bytes + ENGINE_STAGE_WORD);
    s16 first_column;
    s16 row;
    s16 rows;
    s16 column;
    s16 i;
    if (stage != STAGE_RIDE_CHASE && stage != STAGE_SPACE_PORT && stage != STAGE_SPACE_PORT_2 && stage != STAGE_FINAL_WEAPON) {
        first_column = (s16)(CAMERA_WORD(camera, BG_X) / 16 - 1);
        row = (s16)(CAMERA_WORD(camera, BG_Y) / 16 - 1);
        saturn_background_staging_offset = 0;
        saturn_background_staging_cursor = (u32*)saturn_background_staging;
        for (rows = 0; rows < BG_REDRAW_ROWS; rows++) {
            saturn_background_run_state = BG_RUN_IDLE;
            column = first_column;
            saturn_background_run_bytes = 0;
            for (i = 0; i < BG_REDRAW_COLUMNS; i++) {
                saturn_background_queue_tile(camera, column, row);
                saturn_background_run_bytes += 4;
                column++;
                if (saturn_background_run_state == BG_RUN_FULL) {
                    background_flush_run();
                    saturn_background_run_state = BG_RUN_IDLE;
                    saturn_background_run_bytes = 0;
                }
            }
            if (saturn_background_run_state != BG_RUN_IDLE) {
                background_flush_run();
            }
            row++;
        }
        CAMERA_LONG(camera, BG_PREVIOUS_X) = CAMERA_LONG(camera, BG_X);
        CAMERA_LONG(camera, BG_PREVIOUS_Y) = CAMERA_LONG(camera, BG_Y);
    }
    background_set_scroll(camera);
}

void saturn_background_queue_tile(u8* camera, s32 column, s32 row)
{
    u32 planes[3];
    u8 width;
    u8 height;
    s32 screen;
    u16 tile;
    u32* cursor;
    planes[0] = saturn_background_tile_planes[0];
    planes[1] = saturn_background_tile_planes[1];
    planes[2] = saturn_background_tile_planes[2];
    if (saturn_background_run_state == BG_RUN_IDLE) {
        saturn_background_tile_column = (u16)(column & 63);
        saturn_background_tile_row = (u16)(row & 31);
        width = saturn_stage_layout_width;
        while ((s16)column < 0) {
            column += width * 16;
        }
        height = saturn_stage_layout_height;
        while ((s16)row < 0) {
            row += height * 16;
        }
        screen = width * (s16)(((s16)row >> 4) % height) + (s16)(((s16)column >> 4) % width) + (s8)camera[BG_LAYER] * saturn_stage_layout_size;
        if ((s16)saturn_background_tile_column >= BG_PAGE_COLUMNS) {
            saturn_background_run_destination = planes[camera[BG_PLANE]] + (s16)saturn_background_tile_column * 4 + BG_NEXT_PAGE;
        } else {
            saturn_background_run_destination = planes[camera[BG_PLANE]] + (s16)saturn_background_tile_column * 4;
        }
        saturn_background_run_destination += (s16)saturn_background_tile_row << 7;
        saturn_background_tile_source = (u16*)(saturn_stage_screen_tiles + (saturn_stage_screens[(s16)screen] << BG_SCREEN_SHIFT) + ((saturn_background_tile_row & 15) << 5) + ((saturn_background_tile_column & 15) << 1));
        saturn_background_run_start = saturn_background_staging_offset;
        saturn_background_run_state = BG_RUN_OPEN;
    }
    saturn_background_tile_column++;
    if (((s16)saturn_background_tile_column & 15) == 0) {
        saturn_background_run_state = BG_RUN_FULL;
    }
    cursor = saturn_background_staging_cursor;
    saturn_background_staging_cursor = cursor + 1;
    tile = *saturn_background_tile_source;
    *cursor = background_cell(tile);
    saturn_background_staging_offset += 4;
    saturn_background_tile_source++;
}

void saturn_background_load_layout(void)
{
    u8* source = saturn_background_layouts[(s8)saturn_engine_bytes[ENGINE_STAGE_WORD] * 2 + (s8)saturn_engine_bytes[ENGINE_STAGE_WORD + 1]];
    s16 i;
    for (i = 0; i < (u16)saturn_stage_layout_size * 3; i++) {
        saturn_background_layout[i] = *source++;
    }
    saturn_background_scroll_word = 0;
    saturn_background_refresh();
    saturn_background_redraw_word = 0;
}

void saturn_render_frame(void)
{
    saturn_sprite_draw_passes();
    saturn_background_update();
    saturn_hud_draw();
}

void saturn_background_update(void)
{
    u8* camera;
    for (camera = saturn_sprite_cameras; camera < saturn_sprite_cameras + BG_CAMERA_COUNT * BG_CAMERA_STRIDE;
         camera += BG_CAMERA_STRIDE) {
        if (camera[BG_ACTIVE] == 0) {
            continue;
        }
        if (camera[BG_REDRAW] == 0) {
            saturn_background_scroll(camera);
        } else {
            saturn_background_redraw_queued(camera);
            camera[BG_REDRAW] = 0;
        }
    }
}
