#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

void* mmx4_pc_fiber_scheduler(void)
{
    void* scheduler;
    if (IsThreadAFiber())
        return GetCurrentFiber();
    scheduler = ConvertThreadToFiber(NULL);
    if (scheduler == NULL)
        abort();
    return scheduler;
}

void* mmx4_pc_fiber_create(size_t stack_size, void (*entry)(void*), void* parameter)
{
    return CreateFiber(stack_size, (LPFIBER_START_ROUTINE)entry, parameter);
}

void mmx4_pc_fiber_delete(void* fiber) { DeleteFiber(fiber); }

void mmx4_pc_fiber_switch(void* fiber) { SwitchToFiber(fiber); }
#endif
