#include "test_runtime.h"
#include "main/shots/shot_10_dragon_spread_shot.h"
#include "main/shots/shot_35_walrus_ice.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 dragon_spread_shot_fly_expected[] = { 0u, 1u };
static u32 test_dragon_spread_shot_fly(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.unk84.value = 0;
    obj.state = 0;
    dragon_spread_shot_fly(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk84.value;
    return c_test_observe(0, row, observed_values, dragon_spread_shot_fly_expected, 2);
}

#include "support/projectile_damage.h"
DAMAGE_CASE(0)
DAMAGE_CASE(1)
static const CTestCase dragon_spread_shot_damage_cases[] = { DAMAGE_ENTRY(0) DAMAGE_ENTRY(1) };

static const u32 dragon_spread_shot_damage_cases_expected[] = { 0x12340A02u, 0x92340002u };
const struct CTestGroup c_test_groups[] = {
    { "dragon_spread_shot_fly", 0, 0, 1, test_dragon_spread_shot_fly },
    { "dragon_spread_shot_damage", dragon_spread_shot_damage_cases, dragon_spread_shot_damage_cases_expected, COUNT(dragon_spread_shot_damage_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(dragon_spread_shot_damage_cases);
