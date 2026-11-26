#include "test_runtime.h"

#ifndef MMX4_SATURN
void load_palette(void);

static u32 neither_palette_bit(u32 row)
{
    ResetGraph(0);
    need_palette_load = 4;
    load_palette();
    assert(need_palette_load == 0);
    return 1;
}
#define PALETTE_CASES 1
#else
#define neither_palette_bit NULL
#define PALETTE_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "palette_request_without_a_palette", 0, 0, PALETTE_CASES, neither_palette_bit },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = PALETTE_CASES;
