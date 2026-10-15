#include "test_runtime.h"

static const u32 frost_walrus_fx_burst_start_expected[] = { 0u, 1u, 0u, 0u };
static u32 test_frost_walrus_fx_burst_start(u32 row)
{
    u32 observed_values[4];
    struct VisualObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    frost_walrus_fx_burst_start(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, frost_walrus_fx_burst_start_expected, 4);
}

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
const struct CTestGroup c_test_groups[] = {
    { "frost_walrus_fx_burst_start", 0, 0, 1, test_frost_walrus_fx_burst_start },
    { "burst_start_default", burst_start_default_cases, burst_start_default_cases_expected, COUNT(burst_start_default_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(burst_start_default_cases);
