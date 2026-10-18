#include "test_runtime.h"
extern s32 func_8001CEDC(void);
extern s32 func_8001CF74(void);
static u32 poll_events(u32 hardware, u32 ready_mask)
{
    static const u8 first_ready[16] = { 3, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };
    s32* slots[7] = { &D_80139670, &D_80139674, &D_80139678, &D_8013967C, &D_80139680, &D_80139684, &D_80139688 };
    s32 original[7], expected[7], ready, pending, result;
    struct EngineObj engine_before;
    struct MemcardMenuState menu_before;
    u32 i, start = hardware ? 4 : 0, count = hardware ? 3 : 4;
    unsigned long descriptor = hardware ? HwCARD : SwCARD;
    EnterCriticalSection();
    ready = OpenEvent(descriptor, EvSpIOE, EvMdNOINTR, NULL);
    pending = OpenEvent(descriptor, EvSpTIMOUT, EvMdNOINTR, NULL);
    assert(ready != -1 && pending != -1 && ready != pending);
    assert(EnableEvent(ready) != 0 && EnableEvent(pending) != 0);
    if (ready_mask) {
        DeliverEvent(descriptor, EvSpIOE);
        assert(TestEvent(ready) != 0);
        DeliverEvent(descriptor, EvSpIOE);
    }
    assert(TestEvent(pending) == 0);
    engine_before = engine_obj;
    menu_before = memcard_menu;
    for (i = 0; i < 7; i++) {
        original[i] = *slots[i];
        expected[i] = pending;
    }
    for (i = 0; i < count; i++)
        if (ready_mask & (1u << i))
            expected[start + i] = ready;
    for (i = 0; i < 7; i++)
        *slots[i] = expected[i];
    result = hardware ? func_8001CF74() : func_8001CEDC();
    assert(result == first_ready[ready_mask]);
    for (i = 0; i < 7; i++) {
        assert(*slots[i] == expected[i]);
        *slots[i] = original[i];
    }
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&memcard_menu, &menu_before, sizeof(memcard_menu));
    assert(CloseEvent(ready) != 0 && CloseEvent(pending) != 0);
    ExitCriticalSection();
    return result;
}
