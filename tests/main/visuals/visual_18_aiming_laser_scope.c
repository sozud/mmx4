#include "test_runtime.h"

#include "support/aiming_cancellation.h"
AIMING_CANCEL_MODE(3, 0)
static const CTestCase aiming_laser_scope_cancellation_cases[] = { AIMING_CANCEL_ENTRIES(3, 0) };

static const u32 aiming_laser_scope_cancellation_cases_expected[] = { 0x0u, 0x641234u, 0xC82468u, 0x6u };
const struct CTestGroup c_test_groups[] = {
    { "aiming_laser_scope_cancellation", aiming_laser_scope_cancellation_cases, aiming_laser_scope_cancellation_cases_expected, COUNT(aiming_laser_scope_cancellation_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(aiming_laser_scope_cancellation_cases);
