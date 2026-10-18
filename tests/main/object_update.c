#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/object_update.h"

#define QUADS(paused, flags, shown)                                              \
    do {                                                                         \
        u8 pause = engine_obj.unk18;                                             \
        struct QuadObj* cursor = SP_CUR_QUAD_OBJ;                                \
        state_reset(0, 0, 0);                                                    \
        engine_obj.unk18 = paused;                                               \
        g_QuadObjects[0].active = flags;                                         \
        g_QuadObjects[0].on_screen = shown;                                      \
        update_quad_objects();                                                   \
        state_extra = g_QuadObjects[0].active | g_QuadObjects[0].on_screen << 8; \
        engine_obj.unk18 = pause;                                                \
        SP_CUR_QUAD_OBJ = cursor;                                                \
    } while (0)
static void uq_paused_hidden(void) { QUADS(1, 1, 0); }
static void uq_paused_shown(void) { QUADS(1, 1, 1); }
static void uq_paused_idle(void) { QUADS(1, 0, 0); }

static void (*const quad_update_paused_cases[])(void) = {
    uq_paused_hidden,
    uq_paused_shown,
    uq_paused_idle,
};
static const u32 quad_update_paused_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_quad_update_paused(u32 row)
{
    return state_run(quad_update_paused_cases[row], row, &quad_update_paused_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "quad_update_paused", 0, 0, COUNT(quad_update_paused_cases), test_quad_update_paused },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(quad_update_paused_cases);
