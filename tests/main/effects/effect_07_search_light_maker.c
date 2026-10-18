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
#define CASE(m, n)                    \
    static u32 search_##m##_##n(void) \
    {                                 \
        return search_case(m, n);     \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) search_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase search_light_spawner_pool_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 search_light_spawner_pool_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x0u, 0x2000430u, 0x1u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

const struct CTestGroup c_test_groups[] = {
    { "search_light_spawner_pool", search_light_spawner_pool_cases, search_light_spawner_pool_cases_expected, COUNT(search_light_spawner_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(search_light_spawner_pool_cases);
