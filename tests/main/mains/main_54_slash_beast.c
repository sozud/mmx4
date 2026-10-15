#include "test_runtime.h"

static const u32 slash_beast_death_blink_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_slash_beast_death_blink(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    obj.invincibility_timer = 31;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    slash_beast_death_blink(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, slash_beast_death_blink_expected, 9);
}

static const u32 slash_beast_intro_wait_warning_expected[] = { 0u };
static u32 test_slash_beast_intro_wait_warning(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    struct EffectObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    child_0_present = 255;
    obj.ext.main_54.effect = child_0_present ? &child_0 : NULL;
    slash_beast_intro_wait_warning(&obj);
    observed_values[0] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, slash_beast_intro_wait_warning_expected, 1);
}

#include "support/boss_death_flash.h"
BOSS_DEATH_FLASH_TESTS(slash_beast_death_flash, slash_beast_death_blink, 0)

#include "support/pool_full.h"
static u32 pool_full_slash_beast_intro_wait_player(void)
{
    u32 actual;
    pf_prepare();
    engine_obj.stage = 0xC;
    pf_snapshot();
    slash_beast_intro_wait_player(&pf_self);
    pf_expected.unk7C = 3;
    pf_expected.unk7E = 1;
    pf_expected.unk6 = 1;
    pf_script(0x14, 0x40);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_slash_beast_intro_wait_player,
};

static const u32 slash_beast_death_flash_cases_expected[] = { 0x10501u, 0x10502u, 0x10502u, 0x50001u, 0xF0F01u, 0x5FB01u, 0x50001u };
static const u32 pool_full_cases_expected[] = { 0x30100u };
const struct CTestGroup c_test_groups[] = {
    { "slash_beast_death_blink", 0, 0, 1, test_slash_beast_death_blink },
    { "slash_beast_intro_wait_warning", 0, 0, 1, test_slash_beast_intro_wait_warning },
    { "slash_beast_death_flash", slash_beast_death_flash_cases, slash_beast_death_flash_cases_expected, COUNT(slash_beast_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + COUNT(slash_beast_death_flash_cases) + COUNT(pool_full_cases);
