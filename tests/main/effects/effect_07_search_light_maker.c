#include "test_runtime.h"
#include "main/effects/effect_07_search_light_maker.h"
extern struct SearchLightSpawner search_light_spawners[12];

static u32 search_case(u32 mode, u32 observation)
{
    struct SearchLightSpawner records_expected[12];
    struct QuadObj pool_before[32];
    u32 i, actual;
    for (i = 0; i < 12; i++)
        search_light_spawners[i].active = 0;
    if (mode == 0)
        search_light_spawners[0].type = 0xFF;
    memcpy(records_expected, search_light_spawners, sizeof(records_expected));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = 1;
        g_QuadObjects[i].id = 0x27;
        g_QuadObjects[i].state = 0x28;
    }
    if (mode == 2)
        g_QuadObjects[17].active = 0;
    memcpy(pool_before, g_QuadObjects, sizeof(pool_before));
    assert(search_light_spawners[0].x == 1072 && search_light_spawners[0].y == 512);
    search_light_maker_spawn_in_rect(1000, 1080, 500, 600, 0);
    if (mode == 2) {
        pool_before[17].active = 1;
        pool_before[17].id = 0;
        pool_before[17].unk2 = records_expected[0].type;
        pool_before[17].bg_offset = records_expected[0].background_index;
        pool_before[17].x_pos.i.hi = 1072;
        pool_before[17].y_pos.i.hi = 512;
        pool_before[17].backref = &search_light_spawners[0];
        records_expected[0].active = 1;
    }
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(records_expected) / 4; i++)
        assert(((u32*)search_light_spawners)[i] == ((u32*)records_expected)[i]);
    actual = observation == 0 ? (u16)g_QuadObjects[17].x_pos.i.hi | ((u32)(u16)g_QuadObjects[17].y_pos.i.hi << 16) : search_light_spawners[0].active;
    return actual;
}
static const u32 search_light_spawner_pool_cases_expected[] = { 0x0u, 0x0u };
static u32 search_light_spawner_pool_cases_row(u32 row)
{
    return search_case(row, 0);
}

#include "support/state_cases.h"
static struct SearchLightSpawner sl_saved[12];
#define sle state_room.effect
#define SL(st, dx, dy, setup) (memcpy(sl_saved, search_light_spawners, sizeof(sl_saved)), sl_clear(), state_reset(0, 0, 0), background_objects[0].x_pos.i.hi = 0x400, background_objects[0].y_pos.i.hi = 0x180, background_objects[0].unk14.i.hi = 0x400 - (dx), background_objects[0].unk18.i.hi = 0x180 - (dy), sle.active = 1, sle.state = st, setup, search_light_maker_update(&sle), state_extra = sl_active_mask() | sl_quads() << 16, memcpy(search_light_spawners, sl_saved, sizeof(sl_saved)))
static void sl_clear(void)
{
    u32 i;
    for (i = 0; i < 12; i++)
        search_light_spawners[i].active = 0;
}
static u32 sl_active_mask(void)
{
    u32 i, mask = 0;
    for (i = 0; i < 12; i++)
        mask |= (u32)(search_light_spawners[i].active != 0) << i;
    return mask;
}
static u32 sl_quads(void)
{
    u32 i, count = 0;
    for (i = 0; i < 32; i++)
        count += g_QuadObjects[i].active != 0;
    return count;
}
static void sl_init(void) { SL(0, 0, 0, 0); }
static void sl_scroll_right_down(void) { SL(1, 0x10, 0x10, 0); }
static void sl_scroll_left_up(void) { SL(1, -0x10, -0x10, search_light_spawners[0].active = 1); }
static void sl_idle(void) { SL(2, 0, 0, 0); }
static void (*const sl_cases[])(void) = {
    sl_init,
    sl_scroll_right_down,
    sl_scroll_left_up,
    sl_idle,
};
static const u32 sl_expected[] = {
    0x1u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20021u,
    0x0u,
    0x1u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10201u,
    0x0u,
    0x2u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_sl(u32 row)
{
    return object_run(sl_cases[row], row, &sl_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "search_light_spawner_pool", NULL, search_light_spawner_pool_cases_expected, COUNT(search_light_spawner_pool_cases_expected), search_light_spawner_pool_cases_row },
    { "search_light_maker_states", 0, 0, COUNT(sl_cases), test_sl },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(search_light_spawner_pool_cases_expected) + COUNT(sl_cases);
