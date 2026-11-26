#include "test_runtime.h"
#include "main/misc/misc_14_frame_ghost.h"

static u32 ghost(u8 count)
{
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 1;
    obj.state = 1;
    obj.unk7 = count;
    obj.x_pos.i.hi = 0x80;
    obj.y_pos.i.hi = 0x60;
    frame_ghost_update(&obj);
    return (u8)obj.active | (u32)obj.unk7 << 8 | (u32)(u8)obj.on_screen << 16;
}
static u32 fg_showing(void) { return ghost(2); }
static u32 fg_gone(void) { return ghost(1); }
static const CTestCase frame_ghost_fade_cases[] = {
    fg_showing,
    fg_gone,
};
static const u32 frame_ghost_fade_cases_expected[] = { 0x10101u, 0u };

const struct CTestGroup c_test_groups[] = {
    { "frame_ghost_fade", frame_ghost_fade_cases, frame_ghost_fade_cases_expected, COUNT(frame_ghost_fade_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frame_ghost_fade_cases);
