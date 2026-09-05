#ifdef __APPLE__
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#endif

#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

#ifdef MMX4_PC_ASAN
#include <sanitizer/common_interface_defs.h>
#endif

#define PC_THREAD_COUNT 4
#define PC_THREAD_STACK_SIZE (256 * 1024)

struct PcThread {
    ucontext_t context;
    void (*entry)(void);
    unsigned char* stack;
    int initialized;
    int restart;
#ifdef MMX4_PC_ASAN
    void* asan_fake_stack;
#endif
};

static struct GameThread game_threads[PC_THREAD_COUNT];
static struct PcThread pc_threads[PC_THREAD_COUNT];
static ucontext_t scheduler_context;
static int current_thread = -1;
static int debug_threads = -1;
#ifdef MMX4_PC_ASAN
static void* scheduler_asan_fake_stack;
static const void* scheduler_stack_bottom;
static size_t scheduler_stack_size;
#endif

static int thread_debug_enabled(void)
{
    if (debug_threads < 0)
        debug_threads = getenv("MMX4_THREAD_DEBUG") != NULL;
    return debug_threads;
}

struct GameThread* D_801F8300;

static void thread_trampoline(int slot)
{
#ifdef MMX4_PC_ASAN
    __sanitizer_finish_switch_fiber(
        NULL, &scheduler_stack_bottom, &scheduler_stack_size);
#endif
    pc_threads[slot].entry();
    game_threads[slot].state = 0;
    pc_threads[slot].initialized = 0;
    current_thread = -1;
#ifdef MMX4_PC_ASAN
    __sanitizer_start_switch_fiber(
        NULL, scheduler_stack_bottom, scheduler_stack_size);
#endif
}

static void prepare_thread(int slot)
{
    struct PcThread* thread = &pc_threads[slot];
    if (thread->stack == NULL) {
        thread->stack = malloc(PC_THREAD_STACK_SIZE);
        if (thread->stack == NULL)
            abort();
    }
    getcontext(&thread->context);
    thread->context.uc_stack.ss_sp = thread->stack;
    thread->context.uc_stack.ss_size = PC_THREAD_STACK_SIZE;
    thread->context.uc_link = &scheduler_context;
    makecontext(&thread->context, (void (*)(void))thread_trampoline, 1, slot);
    thread->initialized = 1;
    thread->restart = 0;
}

void mmx4_pc_threads_init(void)
{
    s32 slot;
    for (slot = 0; slot < PC_THREAD_COUNT; slot++) {
        game_threads[slot].state = 0;
        pc_threads[slot].entry = NULL;
        pc_threads[slot].initialized = 0;
        pc_threads[slot].restart = 0;
#ifdef MMX4_PC_ASAN
        pc_threads[slot].asan_fake_stack = NULL;
#endif
    }
    D_801F8300 = &game_threads[0];
}

struct GameThread* mmx4_pc_thread_slot(s32 slot)
{
    return &game_threads[slot];
}

void mmx4_pc_thread_create(s32 slot, void (*entry)(void))
{
    if (thread_debug_enabled())
        fprintf(stderr, "MMX4 PC: thread %d create entry=%p\n", slot,
            (void*)entry);
    pc_threads[slot].entry = entry;
    game_threads[slot].state = 2;
    prepare_thread(slot);
}

void mmx4_pc_thread_run(s32 slot)
{
    struct PcThread* thread = &pc_threads[slot];
    if (thread->entry == NULL || game_threads[slot].state == 0)
        return;
    if (!thread->initialized || thread->restart)
        prepare_thread(slot);
    if (thread_debug_enabled())
        fprintf(stderr, "MMX4 PC: thread %d run state=%u entry=%p\n", slot,
            game_threads[slot].state, (void*)thread->entry);
    current_thread = slot;
    D_801F8300 = &game_threads[slot];
#ifdef MMX4_PC_ASAN
    __sanitizer_start_switch_fiber(
        &scheduler_asan_fake_stack, thread->stack, PC_THREAD_STACK_SIZE);
#endif
    swapcontext(&scheduler_context, &thread->context);
#ifdef MMX4_PC_ASAN
    __sanitizer_finish_switch_fiber(
        scheduler_asan_fake_stack, NULL, NULL);
#endif
    current_thread = -1;
}

void mmx4_pc_thread_yield(void)
{
    int slot = current_thread;
    if (slot < 0)
        abort();
    if (thread_debug_enabled())
        fprintf(stderr, "MMX4 PC: thread %d yield state=%u timer=%u\n", slot,
            game_threads[slot].state, game_threads[slot].timer);
#ifdef MMX4_PC_ASAN
    __sanitizer_start_switch_fiber(
        &pc_threads[slot].asan_fake_stack,
        scheduler_stack_bottom, scheduler_stack_size);
#endif
    swapcontext(&pc_threads[slot].context, &scheduler_context);
#ifdef MMX4_PC_ASAN
    __sanitizer_finish_switch_fiber(
        pc_threads[slot].asan_fake_stack, NULL, NULL);
#endif
}

void mmx4_pc_thread_close(void)
{
    int slot = current_thread;
    if (slot < 0)
        abort();
    pc_threads[slot].initialized = 0;
#ifdef MMX4_PC_ASAN
    __sanitizer_start_switch_fiber(
        NULL, scheduler_stack_bottom, scheduler_stack_size);
#endif
    swapcontext(&pc_threads[slot].context, &scheduler_context);
    abort();
}
void mmx4_pc_thread_replace(void (*entry)(void))
{
    int slot = current_thread;
    if (slot < 0)
        abort();
    if (thread_debug_enabled())
        fprintf(stderr, "MMX4 PC: thread %d replace entry=%p\n", slot,
            (void*)entry);
    pc_threads[slot].entry = entry;
    pc_threads[slot].restart = 1;
    game_threads[slot].state = 2;
#ifdef MMX4_PC_ASAN
    __sanitizer_start_switch_fiber(
        NULL, scheduler_stack_bottom, scheduler_stack_size);
#endif
    swapcontext(&pc_threads[slot].context, &scheduler_context);
    abort();
}
