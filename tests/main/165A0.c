#include "test_runtime.h"

static u32 tile_case(u32 mode)
{
    struct BackgroundObj before[3];
    u32 i;
    memset(background_objects, 0, sizeof(background_objects));
    if (mode == 2)
        for (i = 0; i < 3; i++)
            background_objects[i].y_pos.i.hi = -512;
    if (mode == 1)
        for (i = 0; i < 3; i++)
            background_objects[i].x_pos.i.hi = -512;
    memcpy(before, background_objects, sizeof(before));
    for (i = 0; i < sizeof(D_801441C8) / 4; i++)
        ((u32*)D_801441C8)[i] = 0x42424242;
    func_800261B4(mode == 0 ? -32 : 0);
    for (i = 0; i < sizeof(before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)before)[i]);
    for (i = 0; i < sizeof(D_801441C8) / 4; i++)
        assert(((u32*)D_801441C8)[i] == 0x42424242);
    return D_801441C8[0][0][0] | ((u32)D_801441C8[2][31][31] << 16);
}
#define CASE(m)               \
    static u32 tile_##m(void) \
    {                         \
        return tile_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) tile_##m,
static const CTestCase background_negative_tile_guards_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 background_negative_tile_guards_cases_expected[] = { 0x42424242u, 0x42424242u, 0x42424242u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "background_negative_tile_guards", background_negative_tile_guards_cases, background_negative_tile_guards_cases_expected, COUNT(background_negative_tile_guards_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(background_negative_tile_guards_cases);
