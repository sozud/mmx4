#include "test_runtime.h"
#include "main/quads/quad_08_flash_band.h"

static u32 flash_band(s16 edge)
{
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.vertices[0].x.i.hi = edge;
    obj.vertices[3].x.i.hi = edge;
    obj.ext.ready_line.x_vel.val = 0x40000;
    flash_band_update(&obj);
    assert(obj.ext.ready_line.x_vel.val == 0x80000 && obj.vertices[3].x.i.hi == edge - 4);
    return obj.state | (u32)(u16)obj.vertices[0].x.i.hi << 16;
}
static u32 fb_widening(void) { return flash_band(0x100); }
static u32 fb_wide(void) { return flash_band(0x147); }
static const CTestCase flash_band_widen_cases[] = {
    fb_widening,
    fb_wide,
};
static const u32 flash_band_widen_cases_expected[] = { 0x01040001u, 0x014B0002u };

const struct CTestGroup c_test_groups[] = {
    { "flash_band_widen", flash_band_widen_cases, flash_band_widen_cases_expected, COUNT(flash_band_widen_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flash_band_widen_cases);
