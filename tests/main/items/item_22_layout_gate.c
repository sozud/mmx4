#include "test_runtime.h"
#include "main/items/item_22_layout_gate.h"
#include "support/state_cases.h"

#include "support/pool_full.h"
void layout_gate_despawn(struct ItemObj*);
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
static u8 gate_record;
static void lg_despawn(void)
{
    state_reset(0, 0, 0);
    gate_record = 0;
    state_room.item.active = 1;
    state_room.item.backref = (void*)&gate_record;
    layout_gate_despawn(&state_room.item);
    state_extra = gate_record;
    state_room.item.backref = NULL;
}

static void (*const layout_gate_misc_cases[])(void) = {
    lg_despawn,
};
static const u32 layout_gate_misc_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_layout_gate_misc(u32 row)
{
    return object_run(layout_gate_misc_cases[row], row, &layout_gate_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "layout_gate_misc", 0, 0, COUNT(layout_gate_misc_cases), test_layout_gate_misc },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "layout_gate_check_layout_tiles", layout_gate_check_layout_tiles_cases, layout_gate_check_layout_tiles_cases_expected, COUNT(layout_gate_check_layout_tiles_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(layout_gate_misc_cases) + COUNT(pool_full_cases) + COUNT(layout_gate_check_layout_tiles_cases);
