#include "test_runtime.h"

#include "support/background_zone.h"
ZONE_CASE(0, 0)
ZONE_CASE(0, 1)
static const CTestCase zone_d_dispatch_cases[] = { ZONE_ENTRY(0, 0) ZONE_ENTRY(0, 1) };

static const u32 zone_d_dispatch_cases_expected[] = { 0x900124u, 0x77770003u };
const struct CTestGroup c_test_groups[] = {
    { "zone_d_dispatch", zone_d_dispatch_cases, zone_d_dispatch_cases_expected, COUNT(zone_d_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_d_dispatch_cases);
