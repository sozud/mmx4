#include "test_runtime.h"
#include "main/visuals/visual_24_frost_walrus_fx.h"
#include "support/state_cases.h"
void frost_walrus_fx_blizzard(struct VisualObj*);
void frost_walrus_fx_breath_start(struct VisualObj*);

#define BURST_CASE(name, field)            \
    static u32 name(void)                  \
    {                                      \
        struct VisualObj obj;              \
        u32 actual;                        \
        memset(&obj, 0, sizeof(obj));      \
        obj.unk2 = 4;                      \
        obj.unk15 = 42;                    \
        obj.unk6 = 5;                      \
        obj.x_vel.val = 123456;            \
        obj.y_vel.val = -654321;           \
        frost_walrus_fx_burst_start(&obj); \
        actual = (u32)obj.field;           \
        return actual;                     \
    }
BURST_CASE(burst_default_x, x_vel.val)
BURST_CASE(burst_default_y, y_vel.val)
BURST_CASE(burst_default_facing, unk15)
BURST_CASE(burst_default_phase, unk6)
#undef BURST_CASE
static const CTestCase burst_start_default_cases[] = {
    burst_default_x,
    burst_default_y,
    burst_default_facing,
    burst_default_phase,
};

static const u32 burst_start_default_cases_expected[] = { 0x1E240u, 0xFFF6040Fu, 0x0u, 0x6u };
#define sv state_room.visual
#define FX(sub, setup) (state_reset(0, sub, 0), sv.active = 1, sv.state = 1, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, cur_random = 0x1234, setup, frost_walrus_fx_blizzard(&sv))
static void fwf_blizzard_left(void)
{
    FX(0, 0);
}
static void fwf_blizzard_right(void) { FX(0, sv.unk15 = 0x40); }
static void fwf_blizzard_drift(void) { FX(1, (sv.x_vel.val = 0x10000, sv.animation_step.fields.relative_step = 1)); }
static void fwf_blizzard_end(void) { FX(1, sv.animation_step.fields.relative_step = 0); }
static void fwf_breath_left(void)
{
    state_reset(0, 0, 0);
    cur_random = 0x1234;
    frost_walrus_fx_breath_start(&sv);
}
static void fwf_breath_right(void)
{
    state_reset(0, 0, 0);
    cur_random = 0x1234;
    sv.unk15 = 0x40;
    frost_walrus_fx_breath_start(&sv);
}

static void (*const frost_walrus_fx_states_cases[])(void) = {
    fwf_blizzard_left,
    fwf_blizzard_right,
    fwf_blizzard_drift,
    fwf_blizzard_end,
    fwf_breath_left,
    fwf_breath_right,
};
static const u32 frost_walrus_fx_states_expected[] = { 0x10001u, 1u, 0x800000u, 0x600000u, 0xFFFC4000u, 0x28000u, 0u, 0x50000u, 0u, 0u, 0x10001u, 0x400001u, 0x800000u, 0x600000u, 0x3C000u, 0x28000u, 0u, 0x50000u, 0u, 0u, 0x10001u, 1u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10000u, 0u, 0u, 0u, 0xFFFC4000u, 0xFFFD8000u, 0u, 0x50000u, 0u, 0u, 0x10000u, 0x400000u, 0u, 0u, 0x3C000u, 0xFFFD8000u, 0u, 0x50000u, 0u, 0u };

static u32 test_frost_walrus_fx_states(u32 row)
{
    return object_run(frost_walrus_fx_states_cases[row], row, &frost_walrus_fx_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "frost_walrus_fx_states", 0, 0, COUNT(frost_walrus_fx_states_cases), test_frost_walrus_fx_states },
    { "burst_start_default", burst_start_default_cases, burst_start_default_cases_expected, COUNT(burst_start_default_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frost_walrus_fx_states_cases) + COUNT(burst_start_default_cases);
