#include "test_runtime.h"
#include "main/misc/misc_57_falling_piece.h"

static u32 falling(s16 x)
{
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 1;
    obj.state = 1;
    obj.x_pos.i.hi = x;
    obj.y_pos.i.hi = 0x60;
    obj.y_vel.val = 0x20000;
    obj.unk2C = 0x4200;
    falling_piece_update(&obj);
    assert(obj.y_pos.i.hi == 0x5E && obj.y_vel.val == 0x20000 - 0x4200);
    return obj.state | (u32)(u8)obj.on_screen << 8;
}
static u32 fp_falling(void) { return falling(0x80); }
static u32 fp_gone(void) { return falling(0x1000); }
static const CTestCase falling_piece_fall_cases[] = {
    fp_falling,
    fp_gone,
};
static const u32 falling_piece_fall_cases_expected[] = { 0x101u, 0x2u };

const struct CTestGroup c_test_groups[] = {
    { "falling_piece_fall", falling_piece_fall_cases, falling_piece_fall_cases_expected, COUNT(falling_piece_fall_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(falling_piece_fall_cases);
