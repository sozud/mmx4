#include "saturn.h"
#include <stddef.h>

typedef char command_stride_is_12[sizeof(SaturnTransferCommand) == 12 ? 1 : -1];
typedef char profile_stride_is_16[sizeof(SaturnTransferProfile) == 16 ? 1 : -1];
typedef char counts_at_2240[offsetof(SaturnTransferBank, command_count) == 2240 ? 1 : -1];
typedef char bank_stride_is_2244[sizeof(SaturnTransferBank) == 2244 ? 1 : -1];
typedef char thread_stride_is_24[sizeof(SaturnThread) == 24 ? 1 : -1];
typedef char thread_stack_at_16[offsetof(SaturnThread, saved_stack_pointer) == 16 ? 1 : -1];
typedef char archive_record_stride_is_16[sizeof(SaturnArchiveRecord) == 16 ? 1 : -1];
typedef char archive_queue_stride_is_68[sizeof(SaturnArchiveQueue) == 68 ? 1 : -1];
typedef char archive_queue_indices_at_64[offsetof(SaturnArchiveQueue, read_index) == 64 ? 1 : -1];
typedef char sprite_command_stride_is_32[sizeof(SaturnSpriteCommand) == 32 ? 1 : -1];

extern volatile u16 saturn_gameplay_reset_word, saturn_gameplay_limit_word;

extern void saturn_exception_vector_4(void);
extern void saturn_exception_vector_6(void);
extern void saturn_exception_vector_9(void);
extern void saturn_exception_vector_10(void);
#define SCHEDULER_POINT(name) __asm__ volatile(".global _saturn_scheduler_" #name "\n_saturn_scheduler_" #name ":" :: \
                                                   : "memory")

#ifdef SATURN_EXPANDED_THREAD_STACKS
static u32 saturn_thread_stacks[SATURN_THREAD_COUNT][4096] __attribute__((aligned(16)));
#endif

#define STARTUP_POINT(name) __asm__ volatile(".global _saturn_startup_" #name "\n_saturn_startup_" #name ":" \
                                             :                                                               \
                                             :                                                               \
                                             : "memory")
extern volatile u8 saturn_warm_start, saturn_reset_inhibit, saturn_soft_reset_mode;
extern volatile u8 saturn_runtime_flag_0, saturn_runtime_flag_1;
#define CUR_RANDOM (*(volatile u16*)&cur_random)
extern u8 _engine_bss_start[], _engine_end[], _retail_bss_start[], _retail_bss_end[];
extern volatile u16 saturn_warm_buffer[144], saturn_warm_buffer_copy[144];
extern volatile u16 saturn_low_warm_buffer[144], saturn_runtime_header_words[2048];

extern void (*volatile saturn_bios_scu_mask)(u32, u32);
extern void saturn_set_scu_interrupt(u32, u32);
extern void saturn_scu_dma_initialize(void), saturn_cd_initialize(void);
extern void saturn_video_initialize(void), saturn_video_configure(u32, u32, u32);
extern void saturn_video_start(void), saturn_vdp2_initialize(u32);
extern void saturn_peripheral_initialize(void), saturn_sound_initialize(void);
extern const u8 saturn_interrupt_vblank_in[], saturn_interrupt_vblank_out[];
extern const u8 saturn_interrupt_hblank[], saturn_interrupt_dma[];
extern const u8 saturn_interrupt_timer_0[], saturn_interrupt_timer_1[];

extern volatile u16 saturn_frame_request, saturn_frame_ready, saturn_peripheral_ready;
extern volatile u16 saturn_present_inhibit, saturn_pad_held, saturn_pad_pressed;
extern volatile u16 saturn_vdp1_tvmr, saturn_vdp1_fbcr, saturn_vdp1_status;
extern volatile u16 saturn_vdp1_command_0, saturn_vdp1_command_1;
extern volatile u8 saturn_controller_refresh, saturn_frame_dma_pending;
extern volatile u32 saturn_frame_dma_count, saturn_frame_dma_arg_0, saturn_frame_dma_arg_1;
extern volatile u32 saturn_gfx_staging_cursor, saturn_soft_reset_request;
extern volatile u32 saturn_peripheral_result, saturn_peripheral_poll_count;
extern volatile u32 saturn_peripheral_data, saturn_peripheral_work, saturn_frame_counter;
extern void saturn_transfer_flush(void), saturn_frame_dma_copy(u32, u32, u32);
extern u32 saturn_frame_dma_result(void);
extern u32 saturn_peripheral_query(volatile u32*, volatile u32*);
extern void saturn_controller_update(void), saturn_stream_reset(void), saturn_soft_restart(void);
extern void saturn_audio_frame(void), saturn_stream_frame(void), saturn_boot_worker(void);

extern volatile u16 saturn_vdp1_uploaded_pending, saturn_vdp1_phase, saturn_vdp1_submitted_phase;
extern volatile u16 saturn_sprite_pending;
extern void (*volatile saturn_cd_error_hook)(void);

volatile u8* volatile saturn_runtime_clear_begin[1] = { _retail_bss_start };

volatile u8* volatile saturn_runtime_clear_end[1] = { _retail_bss_end };

volatile u8* volatile saturn_platform_clear_begin[1] = { _engine_bss_start };

volatile u8* volatile saturn_platform_clear_end[1] = { _engine_end };

void saturn_gameplay_prepare(void)
{
    saturn_gameplay_reset_word = 0;
    saturn_gameplay_limit_word = 0x400;
}

void saturn_threads_init(void)
{
#ifndef SATURN_EXPANDED_THREAD_STACKS
    static const u32 stacks[SATURN_THREAD_COUNT] = {
        0x0600A000U, 0x0600B000U, 0x0600B800U,
        0x0600C000U, 0x0600C800U, 0x0600CC00U
    };
#endif
    for (unsigned i = SATURN_THREAD_COUNT; i--;) {
        saturn_threads[i].state = 0;
        saturn_threads[i].sleep_timer = 0;
    }
    for (unsigned i = 0; i < SATURN_THREAD_COUNT; ++i) {
#ifdef SATURN_EXPANDED_THREAD_STACKS
        saturn_threads[i].initial_stack_pointer = (u32)(u32)&saturn_thread_stacks[i][4096];
#else
        saturn_threads[i].initial_stack_pointer = stacks[i];
#endif
    }
    volatile u32* vectors;
    __asm__ volatile("stc vbr,%0"
                     : "=r"(vectors));
    vectors[4] = (u32)(u32)&saturn_exception_vector_4;
    vectors[6] = (u32)(u32)&saturn_exception_vector_6;
    vectors[9] = (u32)(u32)&saturn_exception_vector_9;
    vectors[10] = (u32)(u32)&saturn_exception_vector_10;
    SCHEDULER_POINT(initialized);
}

void saturn_threads_run(void)
{
    for (unsigned i = 0; i < SATURN_THREAD_COUNT; ++i) {
        volatile SaturnThread* thread = &saturn_threads[i];
        saturn_current_thread = thread;
        SCHEDULER_POINT(selected);
        u32 state = thread->state;
        if (state == 1) {
            thread->context_argument = saturn_thread_context_prepare(
                thread->entry, thread->initial_stack_pointer, saturn_current_thread);
        } else if (state == 2) {
            thread->sleep_timer -= 1;
            if (thread->sleep_timer != 0) {
                continue;
            }
        } else if (state != 4) {
            continue;
        }
        thread->state = 3;
        SCHEDULER_POINT(dispatch);
        saturn_thread_context_resume(thread->context_argument);
    }
    SCHEDULER_POINT(run_done);
}

static volatile SaturnThread* thread_slot(volatile SaturnThread* table, u32 slot)
{
    return (volatile SaturnThread*)((volatile u8*)table + ((slot * 24U) & 0xFFU));
}

void saturn_thread_create_state(volatile SaturnThread* table, u32 slot, u32 entry)
{
    volatile SaturnThread* thread = thread_slot(table, slot);
    if (!thread->state) {
        thread->entry = entry;
        thread->state = 1;
    }
}

void saturn_thread_create(unsigned int slot, unsigned int entry)
{
    saturn_thread_create_state(saturn_threads, slot, entry);
    SCHEDULER_POINT(create_done);
}

void saturn_thread_sleep(unsigned int frames)
{
    saturn_current_thread->sleep_timer = frames;
    saturn_current_thread->state = 2;
    saturn_thread_context_resume(0xFF000000U);
}

void saturn_thread_exit(void)
{
    saturn_current_thread->state = 0;
    saturn_thread_context_resume(0xFF000000U);
}

void saturn_thread_kill(u32 slot)
{
    volatile SaturnThread* thread = thread_slot(saturn_threads, slot);
    if (thread != saturn_current_thread && thread->state) {
        thread->state = 0;
    }
    SCHEDULER_POINT(kill_done);
}

void saturn_thread_kill_all(void)
{
    for (unsigned i = 0; i < SATURN_THREAD_COUNT; ++i) {
        if (saturn_threads[i].state) {
            saturn_threads[i].state = 0;
        }
    }
    SCHEDULER_POINT(kill_all_done);
}

void saturn_thread_suspend_state(volatile SaturnThread* table, u32 slot)
{
    volatile SaturnThread* thread = thread_slot(table, slot);
    if (thread->state) {
        thread->state |= 0x80U;
    }
}

void saturn_thread_suspend(u32 slot)
{
    saturn_thread_suspend_state(saturn_threads, slot);
    SCHEDULER_POINT(suspend_done);
}

void saturn_thread_resume_state(volatile SaturnThread* table, u32 slot)
{
    thread_slot(table, slot)->state &= ~0x80U;
}

void saturn_thread_resume(u32 slot)
{
    saturn_thread_resume_state(saturn_threads, slot);
    SCHEDULER_POINT(resume_done);
}

void saturn_thread_restart(u32 entry)
{
    saturn_current_thread->state = 1;
    saturn_current_thread->entry = entry;
    saturn_thread_context_resume(0xFF000000U);
}

void saturn_main_frame(void)
{
    saturn_frame_request = 1;
    while (!saturn_frame_ready) { }
    if (saturn_vdp1_phase != 3) {
        saturn_transfer_flush();
        if (saturn_frame_dma_pending) {
            saturn_frame_dma_pending = 0;
            u32 count = saturn_frame_dma_count;
            u32 arg_1 = saturn_frame_dma_arg_1;
            u32 arg_0 = saturn_frame_dma_arg_0;
            saturn_frame_dma_copy(arg_0, arg_1, count);
            while (saturn_frame_dma_result() == 2) { }
        }
        saturn_gfx_staging_cursor = 0;
    }
    while (!saturn_peripheral_ready) { }
    saturn_peripheral_poll_count = 0;
    do {
        saturn_peripheral_result = saturn_peripheral_query(&saturn_peripheral_data, &saturn_peripheral_work);
        u32 before = saturn_peripheral_poll_count;
        saturn_peripheral_poll_count = before + 1;
        if (before > 3)
            break;
    } while (saturn_peripheral_result);
    if (saturn_vdp1_submitted_phase == 1)
        saturn_sprite_pending = 1;
    saturn_controller_update();
    if (!saturn_present_inhibit && saturn_vdp1_uploaded_pending)
        saturn_vdp1_present();
    saturn_soft_reset_request = 0;
    if ((saturn_pad_held & 0x0700) == 0x0700 && (saturn_pad_pressed & 0x0800) == 0x0800)
        saturn_soft_reset_request |= 1;
    if (!saturn_reset_inhibit && saturn_soft_reset_request) {
        saturn_stream_reset();
        if (!saturn_soft_reset_mode)
            saturn_cd_error_hook();
        else
            saturn_soft_restart();
    }
    if (saturn_vdp1_submitted_phase != 3) {
        saturn_audio_frame();
        saturn_threads_run();
        saturn_stream_frame();
    }
    saturn_frame_finish();
    saturn_frame_ready = 0;
}

void saturn_main(void)
{
    saturn_platform_initialize();
    saturn_threads_init();
    saturn_thread_create(0, (u32)(u32)saturn_boot_worker);
    saturn_vdp1_submitted_phase = 1;
    saturn_sprite_pending = 1;
    saturn_controller_refresh = 1;
    saturn_vdp1_tvmr = 0;
    saturn_vdp1_fbcr = 3;
    STARTUP_POINT(main_ready);
    for (;;)
        saturn_main_frame();
}

static void startup_interrupt_mask(u32 mask)
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

void saturn_platform_initialize(void)
{
    saturn_runtime_initialize();
    startup_interrupt_mask(0xF0);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x201F);
    saturn_bios_scu_mask(0xFFFFFFFFU, 0x0E00);
    saturn_set_scu_interrupt(64, (u32)saturn_interrupt_vblank_in);
    saturn_set_scu_interrupt(65, (u32)saturn_interrupt_vblank_out);
    saturn_set_scu_interrupt(66, (u32)saturn_interrupt_hblank);
    saturn_set_scu_interrupt(77, (u32)saturn_interrupt_dma);
    saturn_set_scu_interrupt(67, (u32)saturn_interrupt_timer_0);
    saturn_set_scu_interrupt(68, (u32)saturn_interrupt_timer_1);
    saturn_set_scu_interrupt(75, 0);
    saturn_set_scu_interrupt(74, 0);
    saturn_set_scu_interrupt(73, 0);
    saturn_bios_scu_mask(0xFFFFDFE0u, 0);
    saturn_bios_scu_mask(0xFFFFFE7Fu, 0);
    startup_interrupt_mask(0);
    saturn_scu_dma_initialize();
    saturn_cd_initialize();
    saturn_video_initialize();
    saturn_video_configure(0, 1, 0);
    saturn_video_start();
    saturn_vdp2_initialize(1);
    saturn_peripheral_initialize();
    saturn_sound_initialize();
    STARTUP_POINT(platform_ready);
}

void saturn_runtime_initialize(void)
{
    u16 random = 0;
    if (saturn_warm_start) {
        for (unsigned i = 0; i < 144; ++i)
            saturn_low_warm_buffer[i] = saturn_warm_buffer[i];
        random = CUR_RANDOM;
    }
    volatile u8* p = *saturn_platform_clear_begin;
    while ((u32)p < (u32)*saturn_platform_clear_end)
        *p++ = 0;
    p = *saturn_runtime_clear_begin;
    while ((u32)p < (u32)*saturn_runtime_clear_end)
        *p++ = 0;
    for (unsigned i = 0; i < 2048; ++i)
        saturn_runtime_header_words[i] = 0;
    if (!saturn_warm_start) {
        CUR_RANDOM = 0x0D37;
        saturn_reset_inhibit = 1;
    } else {
        saturn_reset_inhibit = 0;
        CUR_RANDOM = random;
    }
    saturn_runtime_flag_0 = 0;
    STARTUP_POINT(runtime_first);
    saturn_runtime_flag_1 = 0;
    STARTUP_POINT(runtime_second);
    if (saturn_warm_start) {
        for (unsigned i = 0; i < 144; ++i)
            saturn_warm_buffer[i] = saturn_low_warm_buffer[i];
        for (unsigned i = 0; i < 144; ++i)
            saturn_warm_buffer_copy[i] = saturn_warm_buffer[i];
    }
}

void saturn_frame_wait(void)
{
    while (!saturn_frame_ready) { }
    while (!saturn_peripheral_ready) { }
    if (saturn_vdp1_uploaded_pending)
        saturn_vdp1_present();
}
