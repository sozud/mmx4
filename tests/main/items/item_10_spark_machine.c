#include "test_runtime.h"
#include "main/items/item_10_spark_machine.h"

#include "support/pool_full.h"
static u32 pool_full_spark_machine_spawn_spark_a(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_a(&pf_item);
    pf_item_expected.tail_ext.unk2.timer = 10;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spark_machine_spawn_spark_b(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_b(&pf_item);
    pf_item_expected.tail_ext.unk2.previous_value = 15;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spark_machine_spawn_spark_c(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_c(&pf_item);
    pf_item_expected.tail_ext.unk2.value = 12;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_spark_machine_spawn_spark_a,
    pool_full_spark_machine_spawn_spark_b,
    pool_full_spark_machine_spawn_spark_c,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u };
#include "support/state_cases.h"

static u32 spark_pages[0x100];
static s32 spark_frames[0x100];
#define si state_room.item
#define SPARK(s) (state_reset(0, 0, 0), si.state = s, si.x_pos.i.hi = 0x80, si.y_pos.i.hi = 0x60)
#define SPARK_SEEN() (state_extra = si.tail_ext.unk1.unk84.bytes[3] | (u32)(u8)si.tail_ext.unk2.timer << 8 | (u32)(u8)misc_objects[1].active << 16 | (u32)(u8)misc_objects[2].id << 24)
static void sp_init(void)
{
    SPARK(0);
    D_801406A8 = spark_pages;
    TEST_MENU_FRAMES = (u8*)spark_frames;
    spark_machine_update(&si);
    SPARK_SEEN();
}
static void sp_idle(void)
{
    SPARK(1);
    spark_machine_update(&si);
}
static void sp_hit(void)
{
    SPARK(1);
    so.hp = 5;
    state_hit((struct MainObj*)&si, 0, 0, 1);
    spark_machine_update(&si);
    state_extra = (u8)so.hp;
}
static void sp_deflect(void)
{
    SPARK(1);
    so.hp = 5;
    si.unk42 = 0x8000;
    state_hit((struct MainObj*)&si, 0, 0xFF, 1);
    spark_machine_update(&si);
}
static void sp_destroyed(void)
{
    SPARK(1);
    so.hp = 1;
    state_hit((struct MainObj*)&si, 0, 0, 1);
    cur_random = 1;
    spark_machine_update(&si);
    si.unk42 = 0;
    SPARK_SEEN();
}
static void sp_sparking_done(void)
{
    SPARK(2);
    si.tail_ext.unk1.unk84.bytes[3] = 1;
    si.tail_ext.unk2.timer = 2;
    si.tail_ext.unk2.previous_value = 2;
    si.tail_ext.unk2.value = 2;
    spark_machine_update(&si);
    SPARK_SEEN();
}
static void sp_sparking_a(void)
{
    SPARK(2);
    si.tail_ext.unk1.unk84.bytes[3] = 3;
    si.tail_ext.unk2.previous_value = 2;
    si.tail_ext.unk2.value = 2;
    cur_random = 1;
    spark_machine_update(&si);
    SPARK_SEEN();
}
static void sp_sparking_b(void)
{
    SPARK(2);
    si.tail_ext.unk1.unk84.bytes[3] = 3;
    si.tail_ext.unk2.timer = 2;
    si.tail_ext.unk2.value = 2;
    cur_random = 2;
    spark_machine_update(&si);
    SPARK_SEEN();
}
static void sp_sparking_c(void)
{
    SPARK(2);
    si.tail_ext.unk1.unk84.bytes[3] = 3;
    si.tail_ext.unk2.timer = 2;
    si.tail_ext.unk2.previous_value = 2;
    cur_random = 3;
    spark_machine_update(&si);
    SPARK_SEEN();
}
static void sp_broken(void)
{
    SPARK(4);
    spark_machine_update(&si);
}

static void (*const spark_machine_states_cases[])(void) = {
    sp_init,
    sp_idle,
    sp_hit,
    sp_deflect,
    sp_destroyed,
    sp_sparking_done,
    sp_sparking_a,
    sp_sparking_b,
    sp_sparking_c,
    sp_broken,
};
static const u32 spark_machine_states_expected[] = { 1u, 0xFF000041u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x37986u, 0x1000u, 0u, 1u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 4u, 0x2100u, 1u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x2100u, 2u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x9410078u, 0x41002100u, 3u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x100u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0xA02u, 0x41000000u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x102u, 0x41000000u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x102u, 0x41000000u, 4u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_spark_machine_states(u32 row)
{
    return object_run(spark_machine_states_cases[row], row, &spark_machine_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "spark_machine_states", 0, 0, COUNT(spark_machine_states_cases), test_spark_machine_states },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(spark_machine_states_cases) + COUNT(pool_full_cases);
