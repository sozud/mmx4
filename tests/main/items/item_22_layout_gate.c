#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_layout_gate_spawn_alarm(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    layout_gate_spawn_alarm(&pf_item);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_layout_gate_spawn_alarm,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

#define LAYOUT_CASE(name, subtype, tile)                     \
    static u32 name(void)                                    \
    {                                                        \
        struct ItemObj obj;                                  \
        u32 actual;                                          \
        memset(&obj, 0, sizeof(obj));                        \
        obj.unk2 = subtype;                                  \
        obj.tail_ext.unk1.unk84.bytes[0] = 0xFF;             \
        layout_width = 0;                                    \
        D_80141BE8[6] = tile;                                \
        layout_gate_check_layout(&obj);                      \
        assert(obj.tail_ext.unk1.unk84.bytes[0] == subtype); \
        actual = (u32)obj.unk2;                              \
        return actual;                                       \
    }
LAYOUT_CASE(layout_0_match, 0, 0x44)
LAYOUT_CASE(layout_0_other, 0, 0)
LAYOUT_CASE(layout_1_match, 1, 0x43)
LAYOUT_CASE(layout_1_other, 1, 0)
#undef LAYOUT_CASE
static const CTestCase layout_gate_check_layout_tiles_cases[] = {
    layout_0_match,
    layout_0_other,
    layout_1_match,
    layout_1_other,
};

static const u32 layout_gate_check_layout_tiles_cases_expected[] = { 0x2u, 0x0u, 0x2u, 0x1u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "layout_gate_check_layout_tiles", layout_gate_check_layout_tiles_cases, layout_gate_check_layout_tiles_cases_expected, COUNT(layout_gate_check_layout_tiles_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases) + COUNT(layout_gate_check_layout_tiles_cases);
