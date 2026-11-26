#include "test_runtime.h"
#include "saturn/platform.h"

#define MAGIC 0x48415255
#define DATA ((u8*)0x06004000)
#define CONTEXT ((u32*)0x06004800)

extern s32 saturn_error_code;
extern u32 saturn_debug_dump_address;
extern u8* saturn_error_context;
extern u32 saturn_debug_reset_request;
void saturn_debug_viewer_input(void);
u32 saturn_debug_dump(u32 address, u32 end, u32 count, u32 width);
s32 saturn_debug_dump_line(u8* address, s32 count, s32 width);
void saturn_debug_error_message(void);
void saturn_check_soft_reset(void);

static u32 results;

static void data(void)
{
    u32 i;
    for (i = 0; i < 64; i++)
        DATA[i] = (u8)(i * 7 + 0x1C);
}

static void keys(u16 held, u16 pressed)
{
    saturn_pads[0].held = held;
    saturn_pads[0].pressed = pressed;
    saturn_debug_viewer_input();
}

static void viewer_scroll(void)
{
    saturn_debug_dump_address = 0x06004000;
    keys(0x0200, 0x1000);
    keys(0x0100, 0x1000);
    keys(0, 0x1000);
    keys(0x0200, 0x2000);
    keys(0x0100, 0x2000);
    keys(0, 0x2000);
    results = saturn_debug_dump_address;
    keys(0, 0);
}

static void viewer_jump(void)
{
    saturn_debug_dump_address = 0x06004010;
    keys(0, 0x4000);
    keys(0, 0x8000);
    results = saturn_debug_dump_address;
    keys(0x0400, 0x4000);
    results ^= saturn_debug_dump_address << 4;
    keys(0x0400, 0x8000);
    keys(0x1080, 0);
    results ^= saturn_debug_dump_address;
}

static void dump_widths(void)
{
    data();
    results = saturn_debug_dump(0x06004000, MAGIC, 13, 0);
    results ^= saturn_debug_dump(0x06004000, 0x06004009, 0, 1) << 8;
    results ^= saturn_debug_dump(0x06004000, MAGIC, 6, 2) << 16;
    results ^= saturn_debug_dump(0x06004000, MAGIC, 0, 0);
}

static void dump_lines(void)
{
    data();
    saturn_debug_set_cursor(1, 2);
    results = saturn_debug_dump_line(DATA + 1, 8, 1);
    results |= saturn_debug_dump_line(DATA + 2, 8, 2) << 1;
    results |= saturn_debug_dump_line(DATA, 7, 0) << 2;
    results |= saturn_debug_dump_line(DATA, 3, 1) << 3;
    results |= saturn_debug_dump_line(DATA + 4, 5, 2) << 4;
}

static void error_screen(s32 code)
{
    u32 i;
    data();
    for (i = 0; i < 23; i++)
        CONTEXT[i] = 0x11111111u * (i & 15) + i;
    saturn_error_context = (u8*)CONTEXT;
    saturn_debug_dump_address = 0x06004000;
    saturn_error_code = code;
    saturn_debug_error_message();
}

static void error_general(void) { error_screen(0); }

static void soft_reset_partial(void)
{
    saturn_pads[0].held = 0x0700;
    saturn_pads[0].pressed = 0;
    saturn_pads[1].held = 0x0300;
    saturn_pads[1].pressed = 0x0800;
    saturn_check_soft_reset();
    results = saturn_debug_reset_request;
}

static void (*const debug_cases[])(void) = {
    viewer_scroll,
    viewer_jump,
    dump_widths,
    dump_lines,
    error_general,
    soft_reset_partial,
};

#define WORDS 4
static const u32 debug_expected[][WORDS] = {
#include "platform_debug_expected.inc"
};

static u32 debug_run(u32 row)
{
    u32 observed[WORDS];
    u32 i, sum = 0, used = 0;
    results = 0xFFFF;
    debug_cases[row]();
    for (i = 0; i < 0x2000; i += 4) {
        u32 word = *(u32*)(saturn_debug_text + i);
        sum = sum * 33 + word;
        used += word != 0;
    }
    observed[0] = results;
    observed[1] = sum;
    observed[2] = used | (u32)saturn_debug_row << 16 | (u32)saturn_debug_column << 24;
    observed[3] = saturn_debug_dump_address;
    return c_test_observe(0, row, observed, debug_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_debug", 0, 0, COUNT(debug_cases), debug_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(debug_cases);
