#include "test_runtime.h"
#include "support/platform_fixture.h"

s16 get_layout_screen(s16 arg0, s16 arg1, s16 arg2);

static u8 tilemap[128];

static u32 wrap_left_and_above(u32 row)
{
    u32 i;
    s16 screen;
    (void)row;
    for (i = 0; i < COUNT(tilemap); i++)
        tilemap[i] = i ^ 0x80;
    test_stage_screen(tilemap, NULL, NULL);
    layout_width = 8;
    layout_size = 64;
    memset(&background_objects[1], 0, sizeof(background_objects[1]));
    background_objects[1].unk4D = 2;
    background_objects[1].unk4E = 3;
    background_objects[1].min_y = 1;
    background_objects[1].max_y = 1;
    screen = get_layout_screen(1, -40, 0);
    assert(screen == (75 ^ 0x80));
    return (u16)screen;
}

const struct CTestGroup c_test_groups[] = {
    { "wrap_left_and_above", 0, 0, 1, wrap_left_and_above },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
