#include "test_runtime.h"
#include "main/misc/misc_00_static_sprite.h"

#include "support/pool_full.h"
static u32 pool_full_spawn_common_effect(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spawn_common_effect(&pf_self, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_spawn_common_effect,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
void static_sprite_main(struct MiscObj*);
static u32 static_sprite(s16 x)
{
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 1;
    obj.state = 1;
    obj.x_pos.i.hi = x;
    obj.y_pos.i.hi = 0x60;
    static_sprite_main(&obj);
    return obj.state | (u32)(u8)obj.on_screen << 8;
}
static u32 ss_near(void) { return static_sprite(0x80); }
static u32 ss_far(void) { return static_sprite(0x1000); }
static const CTestCase static_sprite_main_cases[] = {
    ss_near,
    ss_far,
};
static const u32 static_sprite_main_cases_expected[] = { 0x101u, 0x2u };

const struct CTestGroup c_test_groups[] = {
    { "static_sprite_main", static_sprite_main_cases, static_sprite_main_cases_expected, COUNT(static_sprite_main_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases) + COUNT(static_sprite_main_cases);
