#include "common.h"
#ifdef MMX4_SHC
typedef char* debug_va_list;
#define debug_va_start(ap, last) ((ap) = (char*)(&(last) + 1))
#define debug_va_arg(ap, type) (*(type*)(((ap) += sizeof(type)) - sizeof(type)))
#define debug_va_end(ap)
#else
#include <stdarg.h>
#define debug_va_list va_list
#define debug_va_start va_start
#define debug_va_arg va_arg
#define debug_va_end va_end
#endif
#include "saturn/platform.h"

int vsprintf(char* out, const char* format, debug_va_list args);

#define VDP2_SHADOW(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define VDP2_SHADOW_LONG(offset) (*(s32*)((u8*)saturn_vdp2_shadow + (offset)))
#define VDP2_COPY(offset) (*(u16*)((u8*)saturn_vdp2_shadow_copy + (offset)))
#define VDP2_COPY_LONG(offset) (*(s32*)((u8*)saturn_vdp2_shadow_copy + (offset)))
#define VDP2_SHADOW_WORDS 0x90
#define VDP2_SHADOW_BYTES 0x120
#define VDP2_TVMD 0x00
#define VDP2_RAMCTL 0x0E
#define VDP2_CYCLE 0x10
#define VDP2_CYCLE_WORDS 8
#define VDP2_BGON 0x20
#define VDP2_CHCTLA 0x28
#define VDP2_CHCTLB 0x2A
#define VDP2_PLSZ 0x3A
#define VDP2_MPOFN 0x3C
#define VDP2_MPABN0 0x40
#define VDP2_MPCDN0 0x42
#define VDP2_MPABN1 0x44
#define VDP2_MPCDN1 0x46
#define VDP2_MPABN2 0x48
#define VDP2_MPCDN2 0x4A
#define VDP2_MPABN3 0x4C
#define VDP2_MPCDN3 0x4E
#define VDP2_SCXIN0 0x70
#define VDP2_SCYIN0 0x74
#define VDP2_ZMXN0 0x78
#define VDP2_ZMYN0 0x7C
#define VDP2_SCXIN1 0x80
#define VDP2_SCYIN1 0x84
#define VDP2_ZMXN1 0x88
#define VDP2_ZMYN1 0x8C
#define VDP2_SCXN2 0x90
#define VDP2_SCYN2 0x92
#define VDP2_SCXN3 0x94
#define VDP2_SCYN3 0x96
#define VDP2_DISPLAY_ON 0x8000
#define VDP2_ZOOM_ONE 0x10000
#define VDP2_VRAM_BASE 0x25E00000
#define VDP2_MAP_MASK 0x3F
#define VDP2_MAP_HIGH 0x1C0
#define VDP2_PLANE_NBG0 1
#define VDP2_PLANE_NBG1 2
#define VDP2_PLANE_NBG2 4
#define VDP2_PLANE_NBG3 8
#define VDP2_PLANE_RBG0 1
#define VDP2_PLANE_NBG4 16
#define VDP2_PLANE_NBG5 32
#define COLOR_RAM_BYTES 0x400
#define DMA_BUSY 2
#define DEBUG_TEXT_COLUMNS 43
#define DEBUG_TEXT_ROWS 29
#define DEBUG_TEXT_PITCH 64
#define DEBUG_TEXT_TILE_BASE 0x3000
#define DEBUG_TEXT_BACKSPACE 1
#define DEBUG_TEXT_NEWLINE 10
#define DEBUG_TEXT_RETURN 13
#define DEBUG_TEXT_SPACE 32
#define DEBUG_TEXT_CHCTLA 0x0101
#define DEBUG_TEXT_PLSZ 21
#define DEBUG_TEXT_MAP_NARROW 30
#define DEBUG_TEXT_MAP_WIDE 56
#define DEBUG_TEXT_MPOFN 0x100

#define VDP1_EWLR (*(volatile u16*)0x25D00008)
#define VDP1_EWRR (*(volatile u16*)0x25D0000A)
#define VDP1_ERASE_LOWER_RIGHT 0x50F0
#define VDP1_VRAM 0x25C00000
#define VDP1_COMMAND_BYTES 32

void DMA_ScuMemCopy(void* destination, void* source, u32 count);
u32 DMA_ScuResult(void);
void DMA_CpuMemCopy1(void* destination, void* source, u32 count);
void DMA_CpuMemCopy4(void* destination, void* source, u32 count);
u32 DMA_CpuResult(void);
void saturn_transfer_use_secondary(void);

#define VDP2_HRESO_MASK 0xFFF0
#define VDP2_VRESO_MASK 0xFFCF
#define VDP2_LSMD_MASK 0xFF3F
#define VDP2_VRESO_240 0x10
#define VDP2_VRESO_256 0x20
#define VDP2_LSMD_SINGLE 0x80
#define VDP2_LSMD_DOUBLE 0xC0

typedef void (*SaturnClockChange)(s32 mode);
extern SaturnClockChange saturn_bios_change_clock;
extern u32 saturn_bios_clock_mode;

#define SCREEN_HEIGHT_240 240
#define SCREEN_HEIGHT_256 256
#define SCREEN_WIDTH_320 320
#define SCREEN_WIDTH_352 352

#define VDP2_REGISTERS ((volatile u16*)0x25F80000)
#define VDP2_SCROLL_REGISTERS ((volatile u16*)0x25F80070)
#define VDP2_REGISTER_WORDS 0x90
#define VDP2_SCROLL_WORDS 20
#define VRAM_TEXT_LAYER 0x25E78000
#define VRAM_DEBUG_LAYER 0x25E7C000
#define COLOR_RAM 0x25F00000
#define TEXT_LAYER_BYTES 0x2000
#define COLOR_RAM_UPLOAD_BYTES 0x1000
#define TRANSFER_ADD 0x100
#define RAMCTL_COLOR_MASK 0x0FFF
#define RAMCTL_COLOR_2048 0x1000
#define RAMCTL_COLOR_1024_32 0x2000

extern u8 saturn_movie_active;
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, u32 attribute_index);

#define DEBUG_TEXT_BYTES 256

u16 saturn_vdp2_default_cycles[] = {
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

u16 saturn_debug_text_cycles[] = {
    0xffff,
    0x4567,
    0x123,
    0x4567,
    0xffff,
    0x4567,
    0x123,
    0x4567,
    0x466f,
    0xff57,
    0x123,
    0xfff7,
    0x466f,
    0xff57,
    0x123,
    0xfff7,
};

s32 saturn_debug_text_attribute = 4;

void saturn_video_initialize(void)
{
    u32 i;
    saturn_vdp2_shadow_init();
    for (i = 0; i < VDP2_SHADOW_WORDS; i++)
        ((u16*)saturn_vdp2_shadow_copy)[i] = ((u16*)saturn_vdp2_shadow)[i];
    saturn_scroll_positions.nbg0_zoom[0] = VDP2_ZOOM_ONE;
    saturn_scroll_positions.nbg0_zoom[1] = VDP2_ZOOM_ONE;
    saturn_scroll_positions.nbg1_zoom[0] = VDP2_ZOOM_ONE;
    saturn_scroll_positions.nbg1_zoom[1] = VDP2_ZOOM_ONE;
    VDP1_EWLR = 0;
    VDP1_EWRR = VDP1_ERASE_LOWER_RIGHT;
    saturn_vdp1_erase_setup();
    DMA_ScuMemCopy((void*)VDP1_VRAM, saturn_sprite_commands, (u32)saturn_sprite_command_count * VDP1_COMMAND_BYTES);
    while (DMA_ScuResult() == DMA_BUSY) { }
}

static void upload(u32 source, u32 destination, u32 bytes)
{
    saturn_transfer_profile(TRANSFER_ADD, 1, 0);
    saturn_transfer_enqueue(source, destination, bytes);
}

void saturn_vdp2_frame_upload(void)
{
    u32 i;
    u16* source;
    if (saturn_movie_active == 0) {
        if (saturn_text_dirty_a) {
            upload((u32)saturn_text_cells, VRAM_TEXT_LAYER, TEXT_LAYER_BYTES);
            saturn_text_dirty_a = 0;
        }
        if (saturn_text_dirty_b) {
            upload((u32)saturn_debug_text, VRAM_DEBUG_LAYER, TEXT_LAYER_BYTES);
            saturn_text_dirty_b = 0;
        }
        if (saturn_color_ram_pending) {
            upload((u32)saturn_color_ram_copy, COLOR_RAM, COLOR_RAM_UPLOAD_BYTES);
            saturn_color_ram_pending = 0;
        }
    }
    source = saturn_vdp2_shadow_copy;
    for (i = 0; i < VDP2_REGISTER_WORDS; i++) {
        VDP2_REGISTERS[i] = source[i];
    }
    if (saturn_movie_active == 0) {
        source = (u16*)&saturn_scroll_positions;
        for (i = 0; i < VDP2_SCROLL_WORDS; i++) {
            VDP2_SCROLL_REGISTERS[i] = source[i];
        }
    }
}

void saturn_vdp2_set_color_ram_mode(u32 mode)
{
    u16 ramctl = (u16)(*(u16*)((u8*)saturn_vdp2_shadow + VDP2_RAMCTL) & RAMCTL_COLOR_MASK);
    switch (mode) {
    case 0:
        *(u16*)((u8*)saturn_vdp2_shadow + VDP2_RAMCTL) = ramctl;
        break;
    case 1:
        *(u16*)((u8*)saturn_vdp2_shadow + VDP2_RAMCTL) = (u16)(RAMCTL_COLOR_2048 | ramctl);
        break;
    case 2:
        *(u16*)((u8*)saturn_vdp2_shadow + VDP2_RAMCTL) = (u16)(RAMCTL_COLOR_1024_32 | ramctl);
        break;
    }
}

void saturn_video_configure(u8 interlace, u8 vertical, u8 horizontal)
{
    u32 clock = saturn_bios_clock_mode;
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_VRESO_MASK;
    switch (vertical) {
    case 0:
        saturn_screen_height = SCREEN_HEIGHT_240;
        break;
    case 1:
        saturn_screen_height = SCREEN_HEIGHT_240;
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_VRESO_240;
        VDP2_COPY(VDP2_TVMD) |= VDP2_VRESO_240;
        break;
    case 2:
        saturn_screen_height = SCREEN_HEIGHT_256;
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_VRESO_256;
        VDP2_COPY(VDP2_TVMD) |= VDP2_VRESO_256;
        break;
    }
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_LSMD_MASK;
    switch (interlace) {
    case 2:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_LSMD_SINGLE;
        VDP2_COPY(VDP2_TVMD) |= VDP2_LSMD_SINGLE;
        break;
    case 3:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_LSMD_DOUBLE;
        VDP2_COPY(VDP2_TVMD) |= VDP2_LSMD_DOUBLE;
        break;
    }
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_HRESO_MASK;
    switch (horizontal) {
    case 0:
        saturn_screen_width = SCREEN_WIDTH_320;
        if (clock != 0)
            saturn_bios_change_clock(0);
        return;
    case 1:
        saturn_screen_width = SCREEN_WIDTH_352;
    case 3:
    case 5:
    case 7:
        if (clock != 1)
            saturn_bios_change_clock(1);
        break;
    case 2:
    case 4:
    case 6:
        if (clock != 0)
            saturn_bios_change_clock(0);
        break;
    default:
        return;
    }
    VDP2_SHADOW(VDP2_TVMD) |= horizontal;
    VDP2_COPY(VDP2_TVMD) |= horizontal;
}

void saturn_vdp2_shadow_init(void)
{
    u32 i;
    for (i = 0; i < VDP2_SHADOW_WORDS; i++) {
        ((u16*)saturn_vdp2_shadow)[i] = 0;
    }
    for (i = 0; i < VDP2_CYCLE_WORDS; i++) {
        VDP2_SHADOW(VDP2_CYCLE + i * 2) = saturn_vdp2_default_cycles[i];
    }
    VDP2_SHADOW_LONG(VDP2_ZMXN0) = VDP2_ZOOM_ONE;
    VDP2_SHADOW_LONG(VDP2_ZMYN0) = VDP2_ZOOM_ONE;
    VDP2_SHADOW_LONG(VDP2_ZMXN1) = VDP2_ZOOM_ONE;
    VDP2_SHADOW_LONG(VDP2_ZMYN1) = VDP2_ZOOM_ONE;
    saturn_vdp2_init_sprite_control();
    saturn_vdp2_init_sprite_priority();
    saturn_vdp2_init_bg_priority();
    saturn_vdp2_init_sprite_ratio();
    saturn_vdp2_init_bg_ratio();
    saturn_vdp2_init_color_offset();
    saturn_player_palette_destination = saturn_color_ram;
}

void saturn_vdp2_set_ram_control(u8* config)
{
    VDP2_SHADOW(VDP2_RAMCTL) &= 0x7FFF;
    if (config[0] == 1) {
        VDP2_SHADOW(VDP2_RAMCTL) |= 0x0100;
    } else {
        VDP2_SHADOW(VDP2_RAMCTL) &= 0xFEFF;
    }
    if (config[1] == 1) {
        VDP2_SHADOW(VDP2_RAMCTL) |= 0x0200;
    } else {
        VDP2_SHADOW(VDP2_RAMCTL) &= 0xFDFF;
    }
    VDP2_SHADOW(VDP2_RAMCTL) = (u16)((VDP2_SHADOW(VDP2_RAMCTL) & 0xFFFC) | config[2]);
    VDP2_SHADOW(VDP2_RAMCTL) = (u16)((VDP2_SHADOW(VDP2_RAMCTL) & 0xFFF3) | (config[3] << 2));
    VDP2_SHADOW(VDP2_RAMCTL) = (u16)((VDP2_SHADOW(VDP2_RAMCTL) & 0xFFCF) | (config[4] << 4));
    VDP2_SHADOW(VDP2_RAMCTL) = (u16)((VDP2_SHADOW(VDP2_RAMCTL) & 0xFF3F) | (config[5] << 6));
}

void saturn_vdp2_set_display(u8 enable)
{
    if (enable) {
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_DISPLAY_ON;
        VDP2_COPY(VDP2_TVMD) |= VDP2_DISPLAY_ON;
    } else {
        VDP2_SHADOW(VDP2_TVMD) &= (u16)~VDP2_DISPLAY_ON;
        VDP2_COPY(VDP2_TVMD) &= (u16)~VDP2_DISPLAY_ON;
    }
}

static void vdp2_set_map(u32 offset, u32 map)
{
    u16 value = (u16)((map & VDP2_MAP_MASK) | ((map & VDP2_MAP_MASK) << 8));
    VDP2_SHADOW(offset) = value;
    VDP2_SHADOW(offset + 2) = value;
}

void saturn_vdp2_set_map_offset(u32 plane, u32 address)
{
    u32 offset = address - VDP2_VRAM_BASE;
    u32 small = offset >> 12;
    u32 large = offset >> 14;
    switch (plane) {
    case VDP2_PLANE_NBG0:
        vdp2_set_map(VDP2_MPABN0, small);
        VDP2_SHADOW(VDP2_MPOFN) |= (u16)(((small & VDP2_MAP_HIGH) >> 6) & 0x7);
        break;
    case VDP2_PLANE_NBG1:
        vdp2_set_map(VDP2_MPABN1, small);
        VDP2_SHADOW(VDP2_MPOFN) |= (u16)(((small & VDP2_MAP_HIGH) >> 2) & 0x70);
        break;
    case VDP2_PLANE_NBG2:
        vdp2_set_map(VDP2_MPABN2, large);
        VDP2_SHADOW(VDP2_MPOFN) |= (u16)(((large & VDP2_MAP_HIGH) << 2) & 0x700);
        break;
    case VDP2_PLANE_NBG3:
        vdp2_set_map(VDP2_MPABN3, large);
        VDP2_SHADOW(VDP2_MPOFN) |= (u16)(((large & VDP2_MAP_HIGH) << 6) & 0x7000);
        break;
    }
}

void saturn_vdp2_commit_frame(void)
{
    u8 mode = saturn_display_mode;
    s16 x;
    s16 y;
    if (mode != 0) {
        VDP2_SHADOW(VDP2_BGON) = mode;
        saturn_display_mode = 0;
    }
    saturn_transfer_use_secondary();
    saturn_vdp2_field ^= 1;
    if (need_palette_load) {
        DMA_CpuMemCopy4(saturn_color_ram_copy, saturn_color_ram, COLOR_RAM_BYTES);
        while (DMA_CpuResult() == DMA_BUSY) {
        }
        saturn_color_ram_pending = 1;
        need_palette_load = 0;
    }
    DMA_CpuMemCopy1(saturn_vdp2_shadow_copy, saturn_vdp2_shadow, VDP2_SHADOW_BYTES);
    while (DMA_CpuResult() == DMA_BUSY) {
    }
    x = saturn_vdp1_local_x;
    y = saturn_vdp1_local_y;
    saturn_scroll_positions.nbg0_x = VDP2_COPY_LONG(VDP2_SCXIN0) - (s32)((u32)x << 16);
    saturn_scroll_positions.nbg0_y = VDP2_COPY_LONG(VDP2_SCYIN0) - (s32)((u32)y << 16);
    saturn_scroll_positions.nbg1_x = VDP2_COPY_LONG(VDP2_SCXIN1) - (s32)((u32)x << 16);
    saturn_scroll_positions.nbg1_y = VDP2_COPY_LONG(VDP2_SCYIN1) - (s32)((u32)y << 16);
    saturn_scroll_positions.nbg2_x = (s16)(VDP2_COPY(VDP2_SCXN2) - x);
    saturn_scroll_positions.nbg2_y = (s16)(VDP2_COPY(VDP2_SCYN2) - y);
    saturn_scroll_positions.nbg3_x = (s16)(VDP2_COPY(VDP2_SCXN3) - x);
    saturn_scroll_positions.nbg3_y = (s16)(VDP2_COPY(VDP2_SCYN3) - y);
}

void saturn_vdp2_init_sprite_control(void)
{
    VDP2_SHADOW(0x0E0) = (u16)((VDP2_SHADOW(0x0E0) & 0x0FC0) | 0x0023);
    VDP2_SHADOW(0x0EC) &= 0x0880;
    VDP2_SHADOW(0x0E4) = 0x0000;
    VDP2_SHADOW(0x0E6) &= 0xFF00;
    VDP2_SHADOW(0x0E8) &= 0xFFC0;
    VDP2_SHADOW(0x0EA) &= 0xFC00;
    VDP2_SHADOW(0x0EE) &= 0xFC00;
    VDP2_SHADOW(0x0E2) &= 0xFEC0;
}

void saturn_vdp2_init_sprite_priority(void)
{
    VDP2_SHADOW(0x0F0) = (u16)((VDP2_SHADOW(0x0F0) & 0xF0F0) | 0x0606);
    VDP2_SHADOW(0x0F2) = (u16)((VDP2_SHADOW(0x0F2) & 0xF0F0) | 0x0606);
    VDP2_SHADOW(0x0F4) = (u16)((VDP2_SHADOW(0x0F4) & 0xF0F0) | 0x0606);
    VDP2_SHADOW(0x0F6) = (u16)((VDP2_SHADOW(0x0F6) & 0xF0F0) | 0x0606);
}

void saturn_vdp2_init_bg_priority(void)
{
    VDP2_SHADOW(0x0F8) = 0x0505;
    VDP2_SHADOW(0x0FA) = 0x0706;
    VDP2_SHADOW(0x0FC) = 0x0000;
}

void saturn_vdp2_init_sprite_ratio(void)
{
    VDP2_SHADOW(0x100) = 0x0000;
    VDP2_SHADOW(0x102) = 0x0000;
    VDP2_SHADOW(0x104) = 0x0000;
    VDP2_SHADOW(0x106) &= 0xFF00;
}

void saturn_vdp2_init_bg_ratio(void)
{
    VDP2_SHADOW(0x108) = 0x0000;
    VDP2_SHADOW(0x10A) = 0x0000;
    VDP2_SHADOW(0x10C) = 0x0000;
    VDP2_SHADOW(0x10E) = 0x0000;
}

void saturn_vdp2_init_color_offset(void)
{
    VDP2_SHADOW(0x110) = (u16)((VDP2_SHADOW(0x110) & 0xFF80) | 0x007F);
    VDP2_SHADOW(0x112) &= 0xFF80;
    VDP2_SHADOW(0x114) = 0x0000;
    VDP2_SHADOW(0x116) = 0x0000;
    VDP2_SHADOW(0x118) = 0x0000;
    VDP2_SHADOW(0x11A) = 0x0000;
    VDP2_SHADOW(0x11C) = 0x0000;
    VDP2_SHADOW(0x11E) = 0x0000;
}

void saturn_debug_printf(const char* format, ...)
{
    char text[DEBUG_TEXT_BYTES];
    char* out;
    debug_va_list args;

    debug_va_start(args, format);
    vsprintf(text, format, args);
    debug_va_end(args);
    for (out = text; *out != 0; out++)
        saturn_debug_putchar((u8)*out);
    saturn_text_dirty_b = 1;
}

static void debug_next_row(void)
{
    if (saturn_debug_row >= DEBUG_TEXT_ROWS) {
        saturn_debug_row = 0;
    } else {
        saturn_debug_row++;
    }
}

void saturn_debug_putchar(u8 character)
{
    s8 value = (s8)character;
    if (value == DEBUG_TEXT_BACKSPACE) {
        if (saturn_debug_column > 0) {
            saturn_debug_column--;
        } else if (saturn_debug_row > 0) {
            saturn_debug_row--;
        }
        saturn_debug_column = DEBUG_TEXT_COLUMNS;
        saturn_debug_put_tile(DEBUG_TEXT_COLUMNS, saturn_debug_row, saturn_debug_text_attribute, DEBUG_TEXT_SPACE);
        return;
    }
    if (value == DEBUG_TEXT_NEWLINE) {
        saturn_debug_column = saturn_debug_margin;
        debug_next_row();
        return;
    }
    if (value == DEBUG_TEXT_RETURN) {
        saturn_debug_column = 0;
        return;
    }
    saturn_debug_put_tile(saturn_debug_column, saturn_debug_row, saturn_debug_text_attribute, value);
    if (saturn_debug_column >= DEBUG_TEXT_COLUMNS) {
        saturn_debug_column = 0;
        debug_next_row();
    } else {
        saturn_debug_column++;
    }
}

void saturn_debug_put_tile(s32 column, s32 row, s32 attribute, s32 character)
{
    *(s32*)(saturn_debug_text + (column + row * DEBUG_TEXT_PITCH) * 4) = (attribute << 16) + (s8)character + DEBUG_TEXT_TILE_BASE;
}

void saturn_debug_set_cursor(u16 column, u16 row)
{
    saturn_debug_column = column;
    saturn_debug_margin = column;
    saturn_debug_row = row;
    saturn_debug_top = row;
}

void saturn_debug_text_setup(s16 wide, s16 bitmap)
{
    u32 i;
    s16 map;
    VDP2_SHADOW(VDP2_CHCTLA) = DEBUG_TEXT_CHCTLA;
    VDP2_SHADOW(VDP2_PLSZ) = DEBUG_TEXT_PLSZ;
    VDP2_SHADOW(VDP2_CHCTLB) = 0;
    if (wide) {
        VDP2_SHADOW(VDP2_CHCTLB) |= 2;
    }
    if (bitmap == 0) {
        map = DEBUG_TEXT_MAP_NARROW;
    } else {
        VDP2_SHADOW(VDP2_CHCTLB) |= 1;
        map = DEBUG_TEXT_MAP_WIDE;
        VDP2_SHADOW(VDP2_MPOFN) |= DEBUG_TEXT_MPOFN;
    }
    map |= map << 8;
    VDP2_SHADOW(VDP2_MPABN2) = map;
    VDP2_SHADOW(VDP2_MPCDN2) = map;
    for (i = 0; i < VDP2_CYCLE_WORDS; i++) {
        VDP2_SHADOW(VDP2_CYCLE + i * 2) = saturn_debug_text_cycles[wide * VDP2_CYCLE_WORDS + i];
    }
}

void saturn_transfer_reset_counts(void)
{
    saturn_transfer_command_count = 0;
    saturn_transfer_profile_count = 0;
    saturn_transfer_command_count_secondary = 0;
    saturn_transfer_profile_count_secondary = 0;
}

void saturn_vdp2_set_ram_control_stage(u8* config)
{
    saturn_vdp2_set_ram_control(config);
}

void saturn_vdp2_set_char_control(u16 plane, u16 colors, u16 bitmap, u16 size)
{
    u16 size_bit = (u16)((size << 8) & 0x100);
    u16 bitmap_bit = (u16)((bitmap << 9) & 0x200);
    u16 low_size = (u16)(size & 1);
    switch (plane) {
    case VDP2_PLANE_RBG0:
        VDP2_SHADOW(VDP2_CHCTLB) &= 0x88FF;
        VDP2_SHADOW(VDP2_CHCTLB) |= (u16)((colors << 12) & 0x7000);
        VDP2_SHADOW(VDP2_CHCTLB) |= bitmap_bit;
        if (bitmap != 0) {
            VDP2_SHADOW(VDP2_CHCTLB) |= (u16)((size << 10) & 0x400);
        } else {
            VDP2_SHADOW(VDP2_CHCTLB) |= size_bit;
        }
        break;
    case VDP2_PLANE_NBG2:
        VDP2_SHADOW(VDP2_CHCTLA) &= 0xFF80;
        VDP2_SHADOW(VDP2_CHCTLA) |= (u16)((colors << 4) & 0x70);
        VDP2_SHADOW(VDP2_CHCTLA) |= (u16)((bitmap << 1) & 2);
        if (bitmap != 0) {
            VDP2_SHADOW(VDP2_CHCTLA) |= (u16)((size << 2) & 0xC);
        } else {
            VDP2_SHADOW(VDP2_CHCTLA) |= low_size;
        }
        break;
    case VDP2_PLANE_NBG3:
        VDP2_SHADOW(VDP2_CHCTLA) &= 0xC0FF;
        VDP2_SHADOW(VDP2_CHCTLA) |= (u16)((colors << 12) & 0x3000);
        VDP2_SHADOW(VDP2_CHCTLA) |= bitmap_bit;
        if (bitmap != 0) {
            VDP2_SHADOW(VDP2_CHCTLA) |= (u16)((size << 10) & 0xC00);
        } else {
            VDP2_SHADOW(VDP2_CHCTLA) |= size_bit;
        }
        break;
    case VDP2_PLANE_NBG4:
        VDP2_SHADOW(VDP2_CHCTLB) &= 0xFFFC;
        VDP2_SHADOW(VDP2_CHCTLB) |= (u16)((colors << 1) & 2);
        VDP2_SHADOW(VDP2_CHCTLB) |= low_size;
        break;
    case VDP2_PLANE_NBG5:
        VDP2_SHADOW(VDP2_CHCTLB) &= 0xFFCF;
        VDP2_SHADOW(VDP2_CHCTLB) |= (u16)((colors << 5) & 0x20);
        VDP2_SHADOW(VDP2_CHCTLB) |= (u16)((size << 4) & 0x10);
        break;
    }
}

void saturn_vdp2_set_cycles(u16* cycles)
{
    u32 i;
    for (i = 0; i < VDP2_CYCLE_WORDS; i++) {
        VDP2_SHADOW(VDP2_CYCLE + i * 2) = cycles[i];
    }
}

void saturn_vdp2_set_screen_mode(u8 interlace, u8 vertical, u8 horizontal)
{
    u32 clock = saturn_bios_clock_mode;
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_VRESO_MASK;
    switch (vertical) {
    case 1:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_VRESO_240;
        break;
    case 2:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_VRESO_256;
        break;
    }
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_LSMD_MASK;
    switch (interlace) {
    case 2:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_LSMD_SINGLE;
        break;
    case 3:
        VDP2_SHADOW(VDP2_TVMD) |= VDP2_LSMD_DOUBLE;
        break;
    }
    VDP2_SHADOW(VDP2_TVMD) &= VDP2_HRESO_MASK;
    switch (horizontal) {
    case 0:
        if (clock != 0) {
            saturn_bios_change_clock(0);
        }
        return;
    case 1:
    case 3:
    case 5:
    case 7:
        if (clock != 1) {
            saturn_bios_change_clock(1);
        }
        break;
    case 2:
    case 4:
    case 6:
        if (clock != 0) {
            saturn_bios_change_clock(0);
        }
        break;
    default:
        return;
    }
    VDP2_SHADOW(VDP2_TVMD) |= horizontal;
}
