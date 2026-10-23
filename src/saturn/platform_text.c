#include "common.h"
#include "saturn/platform.h"

#define TEXT_MASKED 0x80
#define TEXT_MODE_MASK 0x7F
#define TEXT_MODE_BYTE 0
#define TEXT_MODE_TALL 1
#define TEXT_MODE_LARGE 2
#define TEXT_MODE_FONT 3
#define TEXT_MODE_TABLE 4
#define TEXT_END 0
#define TEXT_TABLE_END 0xFF
#define TEXT_ROW_CELLS 0x40
#define TEXT_PITCH 64
#define TEXT_SAVE_MASKS 16

extern u8 saturn_engine_bytes[];

u16 saturn_text_table_tiles[] = {
    0x0,
    0x3ec6,
    0x3e8a,
    0xb24,
    0xa42,
    0x806,
    0x3e8e,
    0x3e88,
    0x3ea0,
    0x3ea2,
    0x3ecc,
    0x3e82,
    0x3f00,
    0x3e84,
    0x3f02,
    0x3ea6,
    0xfce,
    0xfe0,
    0xfe2,
    0xfe4,
    0xfe6,
    0xfe8,
    0xfea,
    0xfec,
    0xfee,
    0x3e80,
    0x3eea,
    0x3ec2,
    0x3ea4,
    0x3ec4,
    0x3ec8,
    0x3ee2,
    0x3e86,
    0xf06,
    0xf08,
    0xf0a,
    0xf0c,
    0xf0e,
    0xf20,
    0xf22,
    0xf24,
    0xf26,
    0xf28,
    0xf2a,
    0xf2c,
    0xf2e,
    0xf40,
    0xf42,
    0xf44,
    0xf46,
    0xf48,
    0xf4a,
    0xf4c,
    0xf4e,
    0xf60,
    0xf62,
    0xf64,
    0xf66,
    0xf68,
    0xdc4,
    0x888,
    0xaa2,
    0x3f00,
    0x3eec,
    0xf04,
    0xf6a,
    0xf6c,
    0xf6e,
    0xf80,
    0xf82,
    0xf84,
    0xf86,
    0xf88,
    0xf8a,
    0xf8c,
    0xf8e,
    0xfa0,
    0xfa2,
    0xfa4,
    0xfa6,
    0xfa8,
    0xfaa,
    0xfac,
    0xfae,
    0xfc0,
    0xfc2,
    0xfc4,
    0xfc6,
    0xfc8,
    0xfca,
    0xfcc,
    0x3f02,
    0x3ea6,
    0x3ee8,
    0xc86,
    0xc88,
    0xc8a,
    0xc8c,
    0xc8e,
    0xca0,
    0xca2,
    0xca4,
    0xca6,
    0xca8,
    0xcaa,
    0xcac,
    0xcae,
    0xcc0,
    0xcc2,
    0xcc4,
    0xcc6,
    0xcc8,
    0xcca,
    0xccc,
    0xcce,
    0xce0,
    0xce2,
    0xce4,
    0xce6,
    0xce8,
    0xcea,
    0xcec,
    0xcee,
    0xd00,
    0xd02,
    0xd04,
    0xd06,
    0xd08,
    0xd0a,
    0xd0c,
    0xd0e,
    0xd20,
    0xd22,
    0xd24,
    0xd26,
    0xd28,
    0xd2a,
    0xd2c,
    0xd2e,
    0xd40,
    0xd42,
    0xd44,
    0xd46,
    0xd48,
    0xd4a,
    0xd4c,
    0xd4e,
    0xd60,
    0xd62,
    0xd64,
    0xd66,
    0xd68,
    0xd6a,
    0xd6c,
    0xd6e,
    0xd80,
    0xd82,
    0xd84,
    0xd86,
    0xd88,
    0xd8a,
    0xd8c,
    0xd8e,
    0xda0,
    0xda2,
    0xda4,
    0xda6,
    0xda8,
    0xdaa,
    0xdac,
    0xdae,
    0xdc0,
    0xdc2,
    0xdc6,
    0xdc8,
    0xdca,
    0xdcc,
    0xdce,
    0xde0,
    0xde2,
    0xde4,
    0xde6,
    0xde8,
    0xdea,
    0xdec,
    0xdee,
    0xe00,
    0xe02,
    0xe04,
    0xe06,
    0xe08,
    0xe0a,
    0xe0c,
    0xe0e,
    0xe20,
    0xe22,
    0xe24,
    0xe26,
    0xe28,
    0xe2a,
    0xe2c,
    0xe2e,
    0xe40,
    0xe42,
    0xe44,
    0xe46,
    0xe48,
    0xe4a,
    0xe4c,
    0xe4e,
    0xe60,
    0xe62,
    0xe64,
    0xe66,
    0xe68,
    0xe6a,
    0xe6c,
    0xe6e,
    0xe80,
    0xe82,
    0xe84,
    0xe86,
    0xe88,
    0xe8a,
    0xe8c,
    0xe8e,
    0xea0,
    0xea2,
    0xea4,
    0xca6,
    0xea8,
    0xeaa,
    0xeac,
    0xeae,
    0xec0,
    0xec2,
    0xec4,
    0xec6,
    0xec8,
    0xeca,
    0xecc,
    0xece,
    0xee0,
    0xee2,
    0xee4,
    0xee6,
    0xee8,
    0xeea,
    0xeec,
    0xeee,
    0xf00,
    0xf02,
    0x840,
    0xa66,
    0x9ca,
    0xffff,
};

struct SaturnTextItem saturn_text_items[] = {
    { 15, 3, 0x0000, 0x0000, 0x0000, (u8*)"SEGASATURN" },
    { 3, 16, 0x0001, 0x0000, 0x0000, (u8*)"STREET FIGHTER ZERO" },
    { 12, 16, 0x0001, 0x0000, 0x0000, (u8*)"TITLE DEMO" },
    { 12, 16, 0x0001, 0x0000, 0x0000, (u8*)"PLAY DEMO" },
    { 12, 16, 0x0001, 0x0000, 0x0000, (u8*)"RANKING DEMO" },
    { 12, 16, 0x0000, 0x0000, 0x0000, (u8*)"PLAYER SELECT" },
    { 12, 16, 0x0000, 0x0000, 0x0000, (u8*)"  GAME BODY  " },
    { 12, 16, 0x0000, 0x0000, 0x0000, (u8*)"           " },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"FREE PLAY  " },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"PRESS START" },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"CONTINUE   " },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"GAME OVER  " },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"           " },
    { 12, 16, 0x0004, 0x0000, 0x0000, (u8*)"PLEASE WAIT" },
    { 0, 0, 0x0013, 0x0600, 0x0000, (u8*)"NO" },
    { 16, 23, 0x0000, 0x0000, 0x0000, (u8*)"            " },
    { 8, 25, 0x0000, 0x0000, 0x0000, (u8*)"@CAPCOM U.S.A.,INC.1995,1996" },
    { 12, 26, 0x0000, 0x0000, 0x0000, (u8*)"ALL RIGHTS RESERVED." },
    { 16, 20, 0x0000, 0x0000, 0x0000, (u8*)"PRESS  START" },
    { 34, 21, 0x0000, 0x0000, 0x0000, (u8*)" " },
    { 9, 24, 0x0000, 0x0000, 0x0000, (u8*)"@CAPCOM CO.,LTD.1995,1996" },
    { 15, 10, 0x2000, 0x0000, 0x0000, (u8*)"VITAL        0" },
    { 15, 13, 0x2000, 0x0000, 0x0000, (u8*)"TIME     VITALx  " },
    { 15, 16, 0x2000, 0x0000, 0x0000, (u8*)"BONUS        0" },
    { 15, 16, 0x2000, 0x0000, 0x0000, (u8*)"COMPLETE 30000" },
    { 15, 19, 0x2000, 0x0000, 0x0000, (u8*)"BONUS        0" },
    { 14, 1, 0x0000, 0x0000, 0x0000, (u8*)"TRAINING" },
    { 14, 7, 0x0004, 0x0000, 0x0000, (u8*)"SELECT" },
    { 18, 9, 0x0004, 0x0000, 0x0000, (u8*)"PLAYER" },
    { 14, 9, 0x0004, 0x0000, 0x0000, (u8*)"OPPONENT" },
    { 17, 12, 0x001B, 0x0000, 0x0000, (u8*)"BEGIN" },
    { 14, 14, 0x001B, 0x0000, 0x0000, (u8*)"TRAINING!" },
    { 9, 13, 0x001B, 0x0000, 0x0000, (u8*)"END TRAINING!" },
    { 16, 20, 0x2000, 0x0000, 0x0000, (u8*)"PRESS  START" },
    { 9, 18, 0x0004, 0x0000, 0x0000, (u8*)" " },
    { 9, 20, 0x0004, 0x0000, 0x0000, (u8*)" " },
    { 9, 22, 0x0004, 0x0000, 0x0000, (u8*)" " },
    { 6, 24, 0x0000, 0x0000, 0x0000, (u8*)" " },
    { 14, 6, 0x0002, 0x0000, 0x0000, (u8*)" " },
    { 14, 6, 0x0002, 0x0000, 0x0000, (u8*)" " },
    { 14, 8, 0x0002, 0x0000, 0x0000, (u8*)" " },
    { 14, 8, 0x0002, 0x0000, 0x0000, (u8*)" " },
    { 16, 22, 0x0000, 0x0000, 0x0000, (u8*)" " },
    { 16, 22, 0x0000, 0x0000, 0x0000, (u8*)" " },
    { 1, 10, 0x0002, 0x0000, 0x0000, (u8*)"SCORE" },
    { 1, 13, 0x0002, 0x0000, 0x0000, (u8*)"WINS" },
    { 1, 16, 0x0002, 0x0000, 0x0000, (u8*)"MAX COMBO" },
    { 30, 10, 0x0002, 0x0000, 0x0000, (u8*)"SCORE" },
    { 30, 13, 0x0002, 0x0000, 0x0000, (u8*)"WINS" },
    { 30, 16, 0x0002, 0x0000, 0x0000, (u8*)"MAX COMBO" },
    { 1, 3, 0x0001, 0x0000, 0x0000, (u8*)"BG1 PosX = " },
    { 18, 3, 0x0001, 0x0000, 0x0000, (u8*)"BG1 PosY = " },
    { 1, 4, 0x0001, 0x0000, 0x0000, (u8*)"BG2 PosX = " },
    { 18, 4, 0x0001, 0x0000, 0x0000, (u8*)"BG2 PosY = " },
    { 1, 5, 0x0001, 0x0000, 0x0000, (u8*)"PL1 PosX = " },
    { 18, 5, 0x0001, 0x0000, 0x0000, (u8*)"PL1 PosY = " },
    { 1, 6, 0x0001, 0x0000, 0x0000, (u8*)"PL2 PosX = " },
    { 18, 6, 0x0001, 0x0000, 0x0000, (u8*)"PL2 PosY = " },
};

u8 saturn_text_mask_glyph[] = {
    0x20,
    0x00,
    0xFF,
    0xFF,
    0x06,
    0x00,
    0xE0,
    0x00,
    0x06,
    0x0F,
    0xA0,
    0x00,
    0x06,
    0x06,
    0x9F,
    0x78,
    0x06,
    0x06,
    0x9F,
    0x79,
};

void saturn_save_capture_options(void)
{
    u32 i;
    u8* record = saturn_save_options;
    record[0] = saturn_engine_bytes[0x43];
    record[0x24] = saturn_engine_bytes[0x59];
    record[0x25] = saturn_engine_bytes[0x5F];
    *(u16*)(record + 0x22) = *(u16*)(saturn_engine_bytes + 0x5A);
    record[0x26] = saturn_engine_bytes[0x47];
    record[0x27] = saturn_engine_bytes[0x48];
    record[0x28] = saturn_engine_bytes[0x46];
    record[0x29] = saturn_engine_bytes[0x37];
    record[1] = saturn_sound_output;
    for (i = 0; i < TEXT_SAVE_MASKS; i++) {
        ((u16*)(record + 2))[i] = saturn_button_masks[i];
    }
}

static void text_dirty(void)
{
    saturn_text_dirty_a = 1;
    saturn_text_dirty_b = 1;
}

void saturn_text_clear(u32* cells, u16 width, u16 height)
{
    u32 row;
    u32 column;
    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            *cells++ = 0;
        }
        cells += TEXT_PITCH - width;
    }
    text_dirty();
}

static u32* text_cells(u32* base, struct SaturnTextItem* item)
{
    return base + item->column + item->row * TEXT_PITCH;
}

void saturn_text_draw_item(u32 index, u32 flags)
{
    struct SaturnTextItem* item = &saturn_text_items[index];
    saturn_text_render(item, text_cells((u32*)saturn_text_cells, item), flags);
}

void saturn_text_draw_item_on(u32 index, u32 flags, u32 debug_layer)
{
    struct SaturnTextItem* item = &saturn_text_items[index];
    saturn_text_render(item, text_cells(debug_layer ? (u32*)saturn_debug_text : (u32*)saturn_text_cells, item), flags);
}

static u32 text_font_cell(s8 character)
{
    if (character >= 65 && character <= 94) {
        return (u32)((character >= 81 ? 16 : 0) + character + 0x63F);
    }
    if (character >= 48 && character <= 58) {
        return (u32)((character >= 50 ? 16 : 0) + character + 0x67E);
    }
    if (character == 32) {
        return 0x80;
    }
    if (character == 45) {
        return 0x6AD;
    }
    if (character == 39) {
        return 0x87;
    }
    return (u32)character;
}

static u32 text_large_cell(s8 character)
{
    s32 cell;
    if (character >= 41 && character <= 63) {
        cell = character - 1;
    } else if (character == 40) {
        cell = 63;
    } else {
        cell = character;
    }
    cell = cell * 2 + 0x3C0;
    return (u32)(cell + ((cell - 0x400) / 16) * 16);
}

void saturn_text_render(struct SaturnTextItem* item, u32* cells, u32 flags)
{
    u32 masked = flags & TEXT_MASKED;
    u32 mode = flags & TEXT_MODE_MASK;
    u8* glyph;
    u8* text;
    u32 high;
    u32 value;
    u16 tile;
    if (masked) {
        glyph = saturn_text_mask_glyph;
        text = item->text;
    } else {
        glyph = item->text;
        text = glyph;
    }
    if (mode == TEXT_MODE_TABLE) {
        for (; *text != TEXT_TABLE_END; text++) {
            high = (u32)item->attribute_high << 16;
            if (*text == 0) {
                cells[0] = high;
                cells[1] = high;
                cells[TEXT_ROW_CELLS] = high;
                cells[TEXT_ROW_CELLS + 1] = high;
            } else {
                tile = saturn_text_table_tiles[*glyph];
                cells[0] = high | tile;
                cells[1] = (u32)(tile + 1) | high;
                cells[TEXT_ROW_CELLS] = (u32)(tile + 16) | high;
                cells[TEXT_ROW_CELLS + 1] = (u32)(tile + 17) | high;
            }
            cells += 2;
            if (!masked) {
                glyph++;
            }
        }
        text_dirty();
        return;
    }
    for (; *text != TEXT_END; text++) {
        high = (u32)item->attribute_high << 16;
        if (item->attribute_low != 0) {
            high |= item->attribute_low;
        }
        switch (mode) {
        case TEXT_MODE_BYTE:
            *cells++ = high | (u8)*glyph;
            break;
        case TEXT_MODE_TALL:
            value = (u32)(((s8)*glyph / 16) * 16 + (s8)*glyph + 64) | high;
            cells[0] = value;
            cells[TEXT_ROW_CELLS] = value + 16;
            cells++;
            break;
        case TEXT_MODE_LARGE:
            value = text_large_cell((s8)*glyph) | high;
            cells[0] = value;
            cells[1] = value + 1;
            cells[TEXT_ROW_CELLS] = value + 16;
            cells[TEXT_ROW_CELLS + 1] = value + 17;
            cells += 2;
            break;
        case TEXT_MODE_FONT:
            value = text_font_cell((s8)*glyph) | high;
            cells[0] = value;
            cells[TEXT_ROW_CELLS] = value + 16;
            cells++;
            break;
        }
        if (!masked) {
            glyph++;
        }
    }
    text_dirty();
}
