#include "test_runtime.h"

#include "support/zone_controller_rows.h"
#include "main/effects/effect_19_bg_zone_controller_c.h"

static const struct ZoneRow zone_c_rows[] = {
    { 0, 0, 0, 0, 0x100, 0x100 },
    { 1, 3, 0, 3, 0x1000, 0x100 },
    { 1, 3, 0, 3, 0x1800, 0x100 },
    { 1, 0, 1, 0, 0x100, 0x100 },
    { 1, 1, 1, 1, 0x1000, 0x100 },
    { 1, 2, 1, 2, 0x1800, 0x100 },
    { 1, 3, 0, 1, 0x1000, 0x100 },
};
static const u32 zone_c_expected[] = {
    0x00010001u, 0xC0u, 0u, 0u,
    0x01010101u, 0x90u, 0u, 0u,
    0x02010201u, 0x90u, 0u, 0u,
    0x00000301u, 0u, 0u, 0u,
    0x01000301u, 0u, 0u, 0u,
    0x02000301u, 0u, 0u, 0u,
    0x01000301u, 0u, 0u, 0u,
};
static u32 test_zone_c(u32 row)
{
    return zone_row_run(bg_zone_controller_c_update, &zone_c_rows[row], row, &zone_c_expected[row * 4]);
}

const struct CTestGroup c_test_groups[] = {
    { "bg_zone_controller_c_zones", 0, 0, COUNT(zone_c_rows), test_zone_c },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_c_rows);
