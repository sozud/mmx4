#include "support/memcard_polling_fixture.h"
static u32 software_ready(u32 row) { return poll_events(0, row + 1); }
static u32 hardware_ready(u32 row) { return poll_events(1, row + 1); }

#ifdef MMX4_PC
static u32 deadline(u32 row)
{
    return poll_events(row, 0);
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "software_event_priority", NULL, NULL, 15, software_ready },
    { "hardware_event_priority", NULL, NULL, 7, hardware_ready },
#ifdef MMX4_PC
    { "no_event_deadline", NULL, NULL, 2, deadline },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 15 + 7
#ifdef MMX4_PC
    + 2
#endif
    ;
