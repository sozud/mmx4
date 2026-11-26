#ifndef MMX4_TESTS_SATURN_DISC_H
#define MMX4_TESTS_SATURN_DISC_H
#include "test_runtime.h"
#include "saturn/platform.h"

extern void (*volatile saturn_bios_scu_mask)(u32, u32);
void INT_SetScuFunc(u32 vector, u32 handler);

void saturn_cd_initialize(void);
void saturn_video_initialize(void);
void saturn_sound_initialize(void);

void saturn_threads_run(void);
void saturn_thread_create(u32 slot, u32 entry);
void saturn_thread_exit(void);
extern s32 saturn_cd_error;

static void test_disc_interrupt_mask(u32 mask)
{
    u32 sr;
    __asm__ volatile("stc sr,%0"
                     : "=r"(sr));
    sr = (sr & ~0xF0u) | mask;
    __asm__ volatile("ldc %0,sr"
                     :
                     : "r"(sr)
                     : "memory");
}

static void test_disc_startup(void)
{
    saturn_bios_scu_mask(0, 0xBFFF);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x201F);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x0E00);
    INT_SetScuFunc(77, (u32)saturn_interrupt_dma);
    INT_SetScuFunc(75, 0);
    INT_SetScuFunc(74, 0);
    INT_SetScuFunc(73, 0);
    test_disc_interrupt_mask(0);

    saturn_cd_initialize();
    assert(saturn_cd_error >= 0);
    saturn_video_initialize();
    saturn_sound_initialize();
}

extern u8 saturn_archive_queue_busy;
void saturn_audio_frame(void);
void saturn_stream_frame(void);
static void (*test_disc_thread_fn)(void);
static void test_disc_thread_entry(void)
{
    test_disc_thread_fn();
    saturn_thread_exit();
}
extern volatile struct {
    u32 state, sleep_timer, context_argument, entry, saved_stack_pointer, initial_stack_pointer;
} saturn_threads[6];
#define TEST_DISC_STACK_WORDS 1024
static u32 test_disc_stacks[6][TEST_DISC_STACK_WORDS];
static u32 test_disc_run_thread_in(u32 host, void (*fn)(void), u32 drain)
{
    u32 passes = 0, i;
    test_disc_thread_fn = fn;
    for (i = 0; i < 6; i++) {
        saturn_threads[i].state = 0;
        saturn_threads[i].sleep_timer = 0;
        saturn_threads[i].initial_stack_pointer = (u32)&test_disc_stacks[i][TEST_DISC_STACK_WORDS];
    }
    saturn_thread_create(host, (u32)test_disc_thread_entry);
    while ((saturn_threads[host].state != 0 || (drain && saturn_archive_queue_busy)) && passes < 900) {
        u32 delay;
        for (delay = 0; delay < 110000; delay++)
            __asm__ volatile("nop");
        saturn_interrupt_vblank_in();
        saturn_interrupt_vblank_out();
        saturn_audio_frame();
        saturn_threads_run();
        saturn_stream_frame();
        passes++;
    }
    assert(saturn_threads[host].state == 0 && !(drain && saturn_archive_queue_busy));
    return passes;
}
static __attribute__((unused)) u32 test_disc_run_thread(void (*fn)(void), u32 drain)
{
    return test_disc_run_thread_in(1, fn, drain);
}

void saturn_interrupt_timer_0(void);
void saturn_interrupt_timer_1(void);
void saturn_video_configure(u32, u32, u32);
void saturn_vdp2_initialize(u32);
static void test_vblank_startup(void)
{
    test_disc_interrupt_mask(0xF0);
    saturn_bios_scu_mask(0, 0xBFFF);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x201F);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x0E00);
    INT_SetScuFunc(64, (u32)saturn_interrupt_vblank_in);
    INT_SetScuFunc(65, (u32)saturn_interrupt_vblank_out);
    INT_SetScuFunc(66, (u32)saturn_interrupt_hblank);
    INT_SetScuFunc(77, (u32)saturn_interrupt_dma);
    INT_SetScuFunc(67, (u32)saturn_interrupt_timer_0);
    INT_SetScuFunc(68, (u32)saturn_interrupt_timer_1);
    INT_SetScuFunc(75, 0);
    INT_SetScuFunc(74, 0);
    INT_SetScuFunc(73, 0);
    saturn_bios_scu_mask(0xFFFFDFE0u, 0);
    saturn_bios_scu_mask(0xFFFFFE7Fu, 0);
    test_disc_interrupt_mask(0);
    saturn_cd_initialize();
    assert(saturn_cd_error >= 0);
    saturn_video_initialize();
    saturn_video_configure(0, 1, 0);
    saturn_video_start();
    saturn_vdp2_initialize(1);
    saturn_peripheral_initialize();
    saturn_sound_initialize();
}

extern volatile u16 saturn_frame_request, saturn_frame_ready;
extern volatile u8 saturn_frame_dma_pending;
extern volatile u32 saturn_frame_dma_count, saturn_frame_dma_arg_0, saturn_frame_dma_arg_1, saturn_gfx_staging_cursor;
void saturn_transfer_flush(void);
void DMA_CpuMemCopy4(u32 destination, u32 source, u32 count);
u32 DMA_CpuResult(void);
static __attribute__((unused)) u32 test_vblank_run_thread(void (*fn)(void), void (*step)(u32 pass), u32 drain)
{
    u32 passes = 0, i;
    test_disc_thread_fn = fn;
    for (i = 0; i < 6; i++) {
        saturn_threads[i].state = 0;
        saturn_threads[i].sleep_timer = 0;
        saturn_threads[i].initial_stack_pointer = (u32)&test_disc_stacks[i][TEST_DISC_STACK_WORDS];
    }
    saturn_thread_create(1, (u32)test_disc_thread_entry);
    while ((saturn_threads[1].state != 0 || (drain && saturn_archive_queue_busy)) && passes < 1800) {
        saturn_frame_request = 1;
        while (!saturn_frame_ready) { }
        saturn_transfer_flush();
        if (saturn_frame_dma_pending) {
            saturn_frame_dma_pending = 0;
            DMA_CpuMemCopy4(saturn_frame_dma_arg_0, saturn_frame_dma_arg_1, saturn_frame_dma_count);
            while (DMA_CpuResult() == 2) { }
        }
        saturn_gfx_staging_cursor = 0;
        if (step)
            step(passes);
        saturn_audio_frame();
        saturn_threads_run();
        saturn_stream_frame();
        saturn_frame_ready = 0;
        passes++;
    }
    assert(saturn_threads[1].state == 0 && !(drain && saturn_archive_queue_busy));
    return passes;
}

#define TEST_DISC_HARNESS_STACK 0x060F0000u
static u32 test_disc_case_stack[2048], test_disc_harness_frames[256];
static u32 (*test_disc_case_body)(u32);
static u32 test_disc_case_wrapper(u32 row, u32* harness)
{
    u32 result, *p, i = 0;
    assert(TEST_DISC_HARNESS_STACK - (u32)harness <= sizeof(test_disc_harness_frames));
    for (p = harness; p < (u32*)TEST_DISC_HARNESS_STACK; p++)
        test_disc_harness_frames[i++] = *p;
    result = test_disc_case_body(row);
    for (p = harness, i = 0; p < (u32*)TEST_DISC_HARNESS_STACK; p++)
        *p = test_disc_harness_frames[i++];
    return result;
}
static __attribute__((noinline)) u32 test_disc_switch_stack(u32 row)
{
    register u32 (*fn)(u32, u32*) __asm__("r8") = test_disc_case_wrapper;
    register u32 arg __asm__("r4") = row;
    register u32* top __asm__("r9") = &test_disc_case_stack[COUNT(test_disc_case_stack)];
    register u32 result __asm__("r0");
    __asm__ volatile("mov.l r14,@-r15\n\t"
                     "mov r15,r14\n\t"
                     "mov r15,r5\n\t"
                     "mov r9,r15\n\t"
                     "jsr @r8\n\t"
                     "nop\n\t"
                     "mov r14,r15\n\t"
                     "mov.l @r15+,r14"
                     : "=r"(result), "+r"(arg)
                     : "r"(fn), "r"(top)
                     : "r1", "r2", "r3", "r5", "r6", "r7", "pr", "t", "mach", "macl", "memory");
    return result;
}
static __attribute__((unused)) u32 test_disc_on_fixture_stack(u32 (*body)(u32), u32 row)
{
    test_disc_case_body = body;
    return test_disc_switch_stack(row);
}

#endif
