#include "test_runtime.h"
#include "saturn/platform.h"

typedef struct {
    u32 state;
    u32 sleep_timer;
    u32 context_argument;
    u32 entry;
    u32 saved_stack_pointer;
    u32 initial_stack_pointer;
} SaturnThread;
extern volatile SaturnThread saturn_threads[6];
extern u8 saturn_fade_state;
extern s16 saturn_fade_level_b;
extern s16 saturn_fade_out_step;
extern u8 saturn_transfer_command_count;
extern u8 saturn_transfer_profile_count;
void saturn_threads_init(void);
void saturn_threads_run(void);
void saturn_thread_create(u32 slot, u32 entry);
void saturn_thread_kill(u32 slot);
void saturn_thread_kill_all(void);
void saturn_thread_suspend(u32 slot);
void saturn_thread_resume(u32 slot);
void saturn_fade_start_in(void);
void saturn_fade_start_out(void);
void saturn_fade_set(s16 select, s16 level);
void saturn_vram_clear_banks(u32 banks);

#define SHADOW(offset) (*(s16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SELECT 0x112
#define A_RED 0x114
#define A_GREEN 0x116
#define A_BLUE 0x118
#define B_RED 0x11A

static u32 frames;

static void run_fade(void)
{
    frames = 0;
    while (saturn_fade_state != 0 && frames < 40) {
        saturn_threads_run();
        frames++;
    }
}

static void fade_in(s16 level_a, s16 level_b)
{
    saturn_threads_init();
    SHADOW(A_RED) = level_a;
    saturn_fade_level_b = level_b;
    saturn_fade_start_in();
    run_fade();
}

static void fade_out(s16 level_a, s16 level_b)
{
    saturn_threads_init();
    SHADOW(A_RED) = level_a;
    saturn_fade_level_b = level_b;
    saturn_fade_start_out();
    run_fade();
}

static void fade_in_a_bright(void) { fade_in(0x20, -0x40); }
static void fade_in_a_dark(void) { fade_in(-0x20, -0x40); }
static void fade_out_a_bright(void) { fade_out(0x30, 0); }
static void thread_controls(void)
{
    saturn_threads_init();
    saturn_thread_create(1, 0x06001000);
    saturn_thread_create(1, 0x06002000);
    saturn_thread_create(3, 0x06003000);
    saturn_thread_suspend(1);
    saturn_thread_suspend(2);
    frames = saturn_threads[1].state | saturn_threads[2].state << 8 | (saturn_threads[1].entry == 0x06001000) << 16;
    saturn_thread_resume(1);
    saturn_thread_kill(2);
    saturn_thread_kill(3);
    frames |= saturn_threads[1].state << 24 | saturn_threads[3].state << 20;
    saturn_thread_kill_all();
}

static void fade_set_and_clear(void)
{
    saturn_fade_level_b = -0x20;
    saturn_fade_set(5, -0x10);
    frames = (u16)SHADOW(SELECT);
    SHADOW(SELECT) = 0x55;
    saturn_fade_set(0, 0x08);
    saturn_vram_clear_banks(0);
    saturn_vram_clear_banks(0xF);
}

static void (*const thread_cases[])(void) = {
    fade_in_a_bright,
    fade_in_a_dark,
    fade_out_a_bright,
    thread_controls,
    fade_set_and_clear,
};

#define WORDS 7
static const u32 thread_expected[][WORDS] = {
#include "platform_threads_expected.inc"
};

static u32 thread_run(u32 row)
{
    u32 observed[WORDS];
    u32 i, states = 0;
    frames = 0xFFFF;
    thread_cases[row]();
    for (i = 0; i < 6; i++)
        states |= (saturn_threads[i].state & 0xF) << (i * 4);
    observed[0] = (u16)saturn_fade_level_b | (u32)(u16)SHADOW(A_RED) << 16;
    observed[1] = (u16)SHADOW(A_GREEN) | (u32)(u16)SHADOW(A_BLUE) << 16;
    observed[2] = (u16)SHADOW(B_RED) | (u32)(u16)SHADOW(SELECT) << 16;
    observed[3] = saturn_fade_state | (u32)(u16)saturn_fade_out_step << 16;
    observed[4] = frames;
    observed[5] = states;
    observed[6] = saturn_transfer_command_count | saturn_transfer_profile_count << 8;
    return c_test_observe(0, row, observed, thread_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_threads", 0, 0, COUNT(thread_cases), thread_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(thread_cases);
