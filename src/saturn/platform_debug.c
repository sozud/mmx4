#include "common.h"
#include "saturn/platform.h"

#define DEBUG_QUERY_RETRIES 3
#define PAD_RESET_HELD 0x0700
#define PAD_RESET_PRESSED 0x0800
#define PAD_START 0x0800
#define DEBUG_SAVE_WORDS 0x780
#define DEBUG_RESTORE_WORDS 0xF00
#define DEBUG_CLEAR_WORDS 0x4000
#define DEBUG_MAGIC 0x48415255
#define DEBUG_DUMP_BYTES 128
#define DEBUG_DUMP_DEFAULT 64
#define DEBUG_LINE_BYTES 8
#define DEBUG_SAVE_BUFFER ((u16*)0x002F0000)
#define VDP2_BGON 0x20
#define VDP2_MPABN3 0x4C
#define VDP2_CLOFEN 0x110
#define VDP2_VRAM 0x25E00000
#define DEBUG_BGON 8
#define ERROR_FRAME_OFFSET 20
#define VIEW_BUTTONS 0x07F8
#define VIEW_DIRECTIONS 0xF000
#define VIEW_REPEAT 0x0080
#define VIEW_UP 0x1000
#define VIEW_DOWN 0x2000
#define VIEW_LEFT 0x4000
#define VIEW_RIGHT 0x8000
#define VIEW_PAGE 0x0200
#define VIEW_ROW 0x0100
#define VIEW_JUMP 0x0400
#define VIEW_LOW_RAM 0x00200000
#define VIEW_HIGH_RAM 0x06000000
#define DUMP_BYTES 0
#define DUMP_WORDS 1
#define DUMP_LONGS 2
#define PRINTABLE_FIRST 32
#define PRINTABLE_LAST 127

extern volatile u16 saturn_frame_request;
extern volatile u16 saturn_frame_ready;
extern volatile u16 saturn_peripheral_ready;
extern u16 saturn_vdp1_uploaded_pending;
extern u8 saturn_reset_flag_a;
extern u8 saturn_reset_flag_b;
extern void (*saturn_cd_error_hook)(void);
extern u32 saturn_debug_vram_save;
extern u16 saturn_debug_register_save[];
extern u32 saturn_debug_query_attempts;
extern volatile s32 saturn_debug_query_result;
extern u32 saturn_debug_reset_request;
extern u32 saturn_debug_dump_address;
extern u8* saturn_error_context;
s32 saturn_peripheral_query(void* data, void* work);
void saturn_stage_commit_video(void);
void saturn_frame_finish(void);
void saturn_vdp1_present(void);
void saturn_transfer_flush(void);
void saturn_entry(void);
void saturn_debug_printf(const char* format, ...);
void saturn_debug_dump_registers(u32* context);
u32 saturn_debug_dump(u32 address, u32 end, u32 count, u32 width);
void saturn_debug_viewer_input(void);
void saturn_debug_error_message(void);
void saturn_debug_frame(void);

char saturn_error_message_0[] = "\n!!! GENERAL OPERATION ERROR !!!\n\n";

char saturn_error_message_1[] = "\n!!! SLOT OPERATION ERROR !!!\n\n";

char saturn_error_message_2[] = "\n!!! CPU ADDRESS ERROR !!!\n\n";

char saturn_error_message_3[] = "\n!!! DMA ADDRESS ERROR !!!\n\n";

char saturn_debug_dump_header[] = "<ADDR>       <D A T A>\n";

char saturn_debug_format_long[] = "%08lX ";

char saturn_debug_format_byte[] = "%02X ";

char saturn_debug_format_byte_pad[] = "   ";

char saturn_debug_format_word[] = "%04X ";

char saturn_debug_format_word_pad[] = "     ";

char saturn_debug_format_long_pad[] = "         ";

char saturn_debug_format_ascii_short[] = "%s";

char saturn_debug_format_ascii[] = "%s\n";

char saturn_debug_registers_0[] = "PC =%08lX SR =%08lX SP =%08lX\n";

char saturn_debug_registers_1[] = "PR =%08lX GBR=%08lX VBR=%08lX\n";

char saturn_debug_registers_2[] = "MCH=%08lX MCL=%08lX\n";

char saturn_debug_registers_3[] = "R0 =%08lX %08lX %08lX\n";

char saturn_debug_registers_4[] = "R3 =%08lX %08lX %08lX\n";

char saturn_debug_registers_5[] = "R6 =%08lX %08lX %08lX\n";

char saturn_debug_registers_6[] = "R9 =%08lX %08lX %08lX\n";

char saturn_debug_registers_7[] = "R12=%08lX %08lX %08lX\n";

s32 saturn_error_code = 0;

static s32 start_pressed(void)
{
    return ((saturn_pads[0].pressed | saturn_pads[1].pressed) & PAD_START) == PAD_START;
}

void saturn_fatal_error(void)
{
    s16 i;
    u16* source;
    u16* destination;
    u32 base;
    saturn_cd_error_hook();
    base = ((saturn_vdp2_shadow[VDP2_MPABN3 / 2] & 0xFF) << 14) + VDP2_VRAM;
    source = (u16*)base;
    saturn_debug_vram_save = base;
    destination = DEBUG_SAVE_BUFFER;
    for (i = 0; i < DEBUG_SAVE_WORDS; i += 3) {
        destination[0] = source[0];
        destination[1] = source[1];
        destination[2] = source[2];
        source += 3;
        destination += 3;
    }
    for (i = 1; i < 0x90; i++) {
        saturn_debug_register_save[i - 1] = saturn_vdp2_shadow[i - 1];
    }
    saturn_vdp2_shadow[VDP2_BGON / 2] = 0;
    saturn_debug_frame();
    destination = (u16*)saturn_debug_text;
    for (i = 1; i < DEBUG_CLEAR_WORDS; i += 3) {
        destination[0] = 0;
        destination[1] = 0;
        destination[2] = 0;
        destination += 3;
    }
    saturn_debug_dump_address = *(u32*)(saturn_error_context + ERROR_FRAME_OFFSET);
    for (;;) {
        saturn_debug_error_message();
        for (;;) {
            saturn_debug_frame();
            saturn_check_soft_reset();
            if (start_pressed()) {
                break;
            }
            saturn_debug_viewer_input();
        }
        saturn_debug_restore_screen();
        do {
            saturn_debug_frame();
            saturn_check_soft_reset();
        } while (!start_pressed());
    }
}

void saturn_debug_error_message(void)
{
    saturn_debug_set_cursor(1, 1);
    saturn_vdp2_shadow[VDP2_BGON / 2] = DEBUG_BGON;
    saturn_vdp2_shadow[VDP2_CLOFEN / 2] = 0;
    switch (saturn_error_code) {
    case 0:
        saturn_debug_printf(saturn_error_message_0);
        break;
    case 1:
        saturn_debug_printf(saturn_error_message_1);
        break;
    case 2:
        saturn_debug_printf(saturn_error_message_2);
        break;
    case 3:
        saturn_debug_printf(saturn_error_message_3);
        break;
    }
    saturn_debug_dump_registers((u32*)saturn_error_context);
    saturn_debug_dump(saturn_debug_dump_address, DEBUG_MAGIC, DEBUG_DUMP_BYTES, 1);
}

void saturn_debug_frame(void)
{
    saturn_frame_request = 1;
    saturn_frame_ready = 0;
    while (saturn_frame_ready == 0) {
    }
    saturn_transfer_flush();
    while (saturn_peripheral_ready == 0) {
    }
    saturn_debug_query_attempts = 0;
    do {
        saturn_debug_query_result = saturn_peripheral_query(&saturn_peripheral_data, &saturn_peripheral_work);
        saturn_debug_query_attempts++;
        if (saturn_debug_query_attempts - 1 > DEBUG_QUERY_RETRIES) {
            break;
        }
    } while (saturn_debug_query_result != 0);
    if (saturn_vdp1_uploaded_pending) {
        saturn_vdp1_present();
    }
    saturn_controller_update();
    saturn_frame_finish();
    saturn_vdp2_commit_frame();
}

void saturn_debug_restore_screen(void)
{
    s16 i;
    u16* source;
    u16* destination;
    saturn_vdp2_shadow[VDP2_BGON / 2] = 0;
    saturn_debug_frame();
    source = DEBUG_SAVE_BUFFER;
    destination = (u16*)saturn_debug_vram_save;
    for (i = 0; i < DEBUG_RESTORE_WORDS; i += 3) {
        destination[0] = source[0];
        destination[1] = source[1];
        destination[2] = source[2];
        source += 3;
        destination += 3;
    }
    for (i = 1; i < 0x90; i++) {
        saturn_vdp2_shadow[i - 1] = saturn_debug_register_save[i - 1];
    }
}

void saturn_check_soft_reset(void)
{
    saturn_debug_reset_request = 0;
    if ((saturn_pads[0].held & PAD_RESET_HELD) == PAD_RESET_HELD && (saturn_pads[0].pressed & PAD_RESET_PRESSED) == PAD_RESET_PRESSED) {
        saturn_debug_reset_request |= 1;
    }
    if ((saturn_pads[1].held & PAD_RESET_HELD) == PAD_RESET_HELD && (saturn_pads[1].pressed & PAD_RESET_PRESSED) == PAD_RESET_PRESSED) {
        saturn_debug_reset_request |= 1;
    }
    if (saturn_debug_reset_request == 0) {
        return;
    }
    saturn_stream_reset();
    saturn_reset_flag_a = 1;
    saturn_reset_flag_b = 1;
    saturn_stage_commit_video();
    saturn_frame_finish();
    saturn_frame_request = 1;
    saturn_frame_ready = 0;
    saturn_debug_frame();
    saturn_vdp2_set_display(0);
    saturn_frame_finish();
    saturn_frame_request = 1;
    saturn_frame_ready = 0;
    saturn_debug_frame();
    saturn_frame_finish();
    saturn_entry();
}

void saturn_debug_viewer_input(void)
{
    s16 held = (s16)(saturn_pads[1].held | saturn_pads[0].held);
    u16 keys = (u16)((held & VIEW_BUTTONS) | ((saturn_pads[1].pressed | saturn_pads[0].pressed) & VIEW_DIRECTIONS));
    if (keys & VIEW_REPEAT) {
        keys = (u16)((keys & VIEW_BUTTONS) | (held & VIEW_DIRECTIONS));
    }
    switch (keys & VIEW_DIRECTIONS) {
    case VIEW_UP:
        if (keys & VIEW_PAGE) {
            saturn_debug_dump_address += 128;
        } else if (keys & VIEW_ROW) {
            saturn_debug_dump_address += 64;
        } else {
            saturn_debug_dump_address += 16;
        }
        break;
    case VIEW_DOWN:
        if (keys & VIEW_PAGE) {
            saturn_debug_dump_address -= 128;
        } else if (keys & VIEW_ROW) {
            saturn_debug_dump_address -= 64;
        } else {
            saturn_debug_dump_address -= 16;
        }
        break;
    case VIEW_LEFT:
        if (keys & VIEW_JUMP) {
            saturn_debug_dump_address = VIEW_LOW_RAM;
        }
        break;
    case VIEW_RIGHT:
        if (keys & VIEW_JUMP) {
            saturn_debug_dump_address = VIEW_HIGH_RAM;
        }
        break;
    }
    if (keys != 0) {
        saturn_debug_dump(saturn_debug_dump_address, DEBUG_MAGIC, DEBUG_DUMP_BYTES, 1);
    }
}

u32 saturn_debug_dump(u32 address, u32 end, u32 count, u32 width)
{
    u32 line;
    if (end != DEBUG_MAGIC) {
        if (address > end) {
            for (;;) {
            }
        }
        count = end - address + 1;
    }
    if (count == 0) {
        count = DEBUG_DUMP_DEFAULT;
    }
    saturn_debug_set_cursor(1, 12);
    saturn_debug_printf(saturn_debug_dump_header);
    while (count != 0) {
        line = count >= DEBUG_LINE_BYTES ? DEBUG_LINE_BYTES : count;
        saturn_debug_dump_line((u8*)address, (s32)line, (s32)width);
        address += line;
        count -= line;
    }
    saturn_text_dirty_b = 1;
    return address;
}

s32 saturn_debug_dump_line(u8* address, s32 count, s32 width)
{
    char text[16];
    u8* cursor = address;
    s32 i;
    s32 n;
    s32 pad;
    if ((width == DUMP_LONGS && ((u32)address & 3)) || (width == DUMP_WORDS && ((u32)address & 1))) {
        return 1;
    }
    saturn_debug_printf(saturn_debug_format_long, address);
    switch (width) {
    case DUMP_BYTES:
        for (i = 0; i < count; i++) {
            saturn_debug_printf(saturn_debug_format_byte, *cursor++);
        }
        pad = DEBUG_LINE_BYTES - count;
        for (i = 0; i < pad; i++) {
            saturn_debug_printf(saturn_debug_format_byte_pad);
        }
        if (count >= DEBUG_LINE_BYTES) {
            count--;
        }
        break;
    case DUMP_WORDS:
        n = (count + 1) >> 1;
        count = n * 2;
        for (i = 0; i < n; i++) {
            saturn_debug_printf(saturn_debug_format_word, *(u16*)cursor);
            cursor += 2;
        }
        pad = 4 - n;
        for (i = 0; i < pad; i++) {
            saturn_debug_printf(saturn_debug_format_word_pad);
        }
        break;
    case DUMP_LONGS:
        n = (count + 3) >> 2;
        count = n * 4;
        for (i = 0; i < n; i++) {
            saturn_debug_printf(saturn_debug_format_long, *(u32*)cursor);
            cursor += 4;
        }
        pad = 2 - n;
        for (i = 0; i < pad; i++) {
            saturn_debug_printf(saturn_debug_format_long_pad);
        }
        break;
    }
    memcpy(text, address, count);
    for (i = 0; i < count; i++) {
        if ((u8)text[i] < PRINTABLE_FIRST || (u8)text[i] > PRINTABLE_LAST) {
            text[i] = '.';
        }
    }
    text[i] = 0;
    if (width == DUMP_BYTES && count == 7) {
        saturn_debug_printf(saturn_debug_format_ascii_short, text);
    } else {
        saturn_debug_printf(saturn_debug_format_ascii, text);
    }
    return 0;
}

void saturn_debug_dump_registers(u32* context)
{
    saturn_debug_printf(saturn_debug_registers_0, context[21], context[22], context[5]);
    saturn_debug_printf(saturn_debug_registers_1, context[0], context[1], context[2]);
    saturn_debug_printf(saturn_debug_registers_2, context[3], context[4]);
    saturn_debug_printf(saturn_debug_registers_3, context[20], context[19], context[18]);
    saturn_debug_printf(saturn_debug_registers_4, context[17], context[16], context[15]);
    saturn_debug_printf(saturn_debug_registers_5, context[14], context[13], context[12]);
    saturn_debug_printf(saturn_debug_registers_6, context[11], context[10], context[9]);
    saturn_debug_printf(saturn_debug_registers_7, context[8], context[7], context[6]);
}
