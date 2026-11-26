#include "test_runtime.h"

#include "support/zone_controller_rows.h"
#include "main/effects/effect_15_bg_zone_controller_b.h"

static const struct ZoneRow zone_b_rows[] = {
    { 0, 0, 0, 0, 0x100, 0x100 },
    { 1, 6, 0, 6, 0xC00, 0x100 },
    { 1, 6, 0, 6, 0x1000, 0x600 },
    { 1, 6, 0, 6, 0x1500, 0x600 },
    { 1, 6, 0, 6, 0x1720, 0x600 },
    { 1, 6, 0, 6, 0x1800, 0x600 },
    { 1, 0, 1, 0, 0x100, 0x100 },
    { 1, 1, 1, 1, 0x800, 0x100 },
    { 1, 2, 1, 2, 0x1000, 0x600 },
    { 1, 3, 1, 3, 0x1500, 0x600 },
    { 1, 4, 1, 4, 0x1720, 0x600 },
    { 1, 5, 1, 5, 0x1800, 0x600 },
    { 1, 6, 0, 3, 0x1500, 0x600 },
};
static const u32 zone_b_expected[] = {
    0x00010001u, 0xC0u, 0u, 0u,
    0x01010101u, 0x80u, 0u, 0u,
    0x02010201u, 0xC0u, 0u, 0u,
    0x03010301u, 0x70u, 0x1660u, 0u,
    0x04010401u, 0xC0u, 0u, 0u,
    0x05010501u, 0u, 0u, SATURN_ALT(9, 4),
    0x00000601u, 0u, 0u, 0u,
    0x01000601u, 0u, 0u, 0u,
    0x02000601u, 0u, 0u, 0u,
    0x03000601u, 0u, 0u, 0u,
    0x04000601u, 0u, 0u, 0u,
    0x05000601u, 0u, 0u, 0u,
    0x03000601u, 0u, 0u, 0u,
};
static u32 test_zone_b(u32 row)
{
    return zone_row_run(bg_zone_controller_b_update, &zone_b_rows[row], row, &zone_b_expected[row * 4]);
}

const struct CTestGroup c_test_groups[] = {
    { "bg_zone_controller_b_zones", 0, 0, COUNT(zone_b_rows), test_zone_b },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_b_rows);
