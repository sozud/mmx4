#include "test_runtime.h"
#include "main/effects/effect_20_bg_zone_controller_d.h"
#include "main/effects/effect_22_bg_zone_controller_e.h"

#include "support/background_zone.h"
ZONE_CASE(0, 0)
ZONE_CASE(0, 1)
static const CTestCase zone_d_dispatch_cases[] = { ZONE_ENTRY(0, 0) ZONE_ENTRY(0, 1) };

static const u32 zone_d_dispatch_cases_expected[] = { 0x900124u, 0x77770003u };
static u32 zone_d_steps(u32 index);
const struct CTestGroup c_test_groups[] = {
    { "zone_d_steps", 0, 0, 5, zone_d_steps },
    { "zone_d_dispatch", zone_d_dispatch_cases, zone_d_dispatch_cases_expected, COUNT(zone_d_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_d_dispatch_cases) + 5;

s32 func_800B9E54(struct Effect21SpawnRecord*);
static u32 zone_d_steps(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 4, 5 };
    static const s16 player_x[] = { 0x100, 0x100, 0xB00, 0, 0xB00 };
    u32 row = scenarios[index];
    struct EffectObj obj;
    struct Effect21SpawnRecord record = { 0x120, 0x700, 0, 0 };
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    if (row == 5) {
        background_objects[0].x_pos.i.hi = 0x100;
        background_objects[0].y_pos.i.hi = 0x100;
        assert(func_800B9E54(&record) == 0);
        record.y = 0x180;
        assert(func_800B9E54(&record) == 1);
        return 1;
    }
    g_Player.x_pos.i.hi = player_x[row];
    obj.active = 1;
    obj.id = 20;
    obj.state = row == 0 ? 0 : 1;
    obj.unk5 = row == 1 ? 0 : 2;
    obj.unk6 = row == 1 || row == 2;
    obj.ext.effect_20.unk14 = row == 1 ? 0 : 2;
    bg_zone_controller_d_update(&obj);
    assert(obj.state == 1 && obj.ext.effect_20.unk14 == (row <= 1 ? 0 : 2));
    assert(obj.unk5 == (row == 1 || row == 2 ? 3 : row == 0 ? 0 : 2) && obj.unk6 == !(row == 1 || row == 2));
    assert(background_objects[0].unk2E == (row == 0 ? 0xC0 : 0));
    return 1;
}
