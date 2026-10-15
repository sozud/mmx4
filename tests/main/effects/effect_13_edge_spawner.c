#include "test_runtime.h"
void func_800B887C(s16, s16, s16, s16);

static u32 spawn_case(u32 observation)
{
    struct Effect1314ItemSpawn before_table[19];
    struct ItemObj before[32];
    u32 i, j, actual, reservation_mask = 0, allocated_mask = 0, entry_index[32];
    for (i = 0; i < 18; i++)
        edge_spawner_items[i].reserved = i == 10;
    assert(edge_spawner_items[18].id == 0xFF);
    memcpy(before_table, edge_spawner_items, sizeof(before_table));
    memset(item_objects, 0, sizeof(item_objects));
    for (i = 0; i < 32; i++) {
        item_objects[i].active = i == 3 || i == 17 || i == 31 ? 0 : 0x41;
        item_objects[i].id = 3;
        item_objects[i].unk2 = 0x25;
        item_objects[i].unk5 = i;
        item_objects[i].x_pos.val = 0x12345678;
        item_objects[i].y_pos.val = 0x23456789;
    }
    memcpy(before, item_objects, sizeof(before));
    func_800B887C(0x1510, 0x15A0, 0x620, 0x820);
    for (i = 0; i < 19; i++) {
        if (i < 18 && edge_spawner_items[i].reserved)
            reservation_mask |= 1u << i;
        before_table[i].reserved = edge_spawner_items[i].reserved;
        assert(edge_spawner_items[i].reserved <= 1);
    }
    for (i = 0; i < sizeof(before_table); i++)
        assert(((u8*)before_table)[i] == ((u8*)edge_spawner_items)[i]);
    for (i = 0; i < 32; i++) {
        entry_index[i] = 0;
        if (!before[i].active && item_objects[i].active) {
            allocated_mask |= 1u << i;
            for (j = 0; j < 18; j++)
                if (item_objects[i].backref == &edge_spawner_items[j])
                    entry_index[i] = j + 1;
            assert(entry_index[i] != 0);
            before[i].active = item_objects[i].active;
            before[i].id = item_objects[i].id;
            before[i].unk2 = item_objects[i].unk2;
            before[i].x_pos = item_objects[i].x_pos;
            before[i].y_pos = item_objects[i].y_pos;
            before[i].backref = item_objects[i].backref;
        }
        for (j = 0; j < sizeof(struct ItemObj) / 4; j++)
            assert(((u32*)&item_objects[i])[j] == ((u32*)&before[i])[j]);
    }
    if (observation == 0)
        actual = reservation_mask;
    else if (observation == 1)
        actual = allocated_mask;
    else {
        i = observation < 6 ? 3 : 17;
        switch ((observation - 2) % 4) {
        case 0:
            actual = ((u32*)&item_objects[i])[0];
            break;
        case 1:
            actual = item_objects[i].x_pos.val;
            break;
        case 2:
            actual = item_objects[i].y_pos.val;
            break;
        default:
            actual = entry_index[i];
            break;
        }
    }
    return actual;
}
#define SPAWN_CASE(n)                              \
    static u32 edge_spawner_bounds_spawn_##n(void) \
    {                                              \
        return spawn_case(n);                      \
    }
SPAWN_CASE(0)
SPAWN_CASE(1)
SPAWN_CASE(2)
SPAWN_CASE(3)
SPAWN_CASE(4)
SPAWN_CASE(5)
SPAWN_CASE(6)
SPAWN_CASE(7)
SPAWN_CASE(8)
SPAWN_CASE(9)
#define SPAWN_ENTRY(n) edge_spawner_bounds_spawn_##n,
static const CTestCase edge_spawner_bounds_cases[]
    = { SPAWN_ENTRY(0) SPAWN_ENTRY(1) SPAWN_ENTRY(2) SPAWN_ENTRY(3) SPAWN_ENTRY(4) SPAWN_ENTRY(5) SPAWN_ENTRY(6) SPAWN_ENTRY(7) SPAWN_ENTRY(8) SPAWN_ENTRY(9) };
static const u32 edge_spawner_bounds_cases_expected[] = { 0x2480u, 0x20008u, 0x10741u, 0x15800000u, 0x6B00000u, 0x8u, 0x10741u, 0x15400000u, 0x7C00000u, 0xEu };
#undef SPAWN_CASE
#undef SPAWN_ENTRY

struct func_800B887C_case {
    u32 id, reserved, pool_0_full, x_max, y_max;
    u32 expected[6];
};
static const struct func_800B887C_case func_800B887C_cases[] = {
    { 255, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 255, 0, 5632, 2244, { 0xFFu, 0x41u, 7u, 1u, 0x15100000u, 0x5D00000u } },
    { 0, 255, 255, 5632, 2244, { 0xFFu, 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800B887C(u32 row)
{
    const struct func_800B887C_case* c = &func_800B887C_cases[row];
    u32 observed_values[6];
    u8 pool_0_full;
    s16 x_min;
    s16 x_max;
    s16 y_min;
    s16 y_max;
    memset(&item_objects, 0, sizeof(item_objects));
    edge_spawner_items[0].id = c->id;
    edge_spawner_items[0].reserved = c->reserved;
    edge_spawner_items[0].x = 0;
    edge_spawner_items[0].y = 0;
    pool_0_full = c->pool_0_full;
    x_min = 0;
    x_max = c->x_max;
    y_min = 0;
    y_max = c->y_max;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_800B887C(x_min, x_max, y_min, y_max);
    observed_values[0] = (u32)edge_spawner_items[0].reserved;
    observed_values[1] = (u32)item_objects[0].active;
    observed_values[2] = (u32)item_objects[0].id;
    observed_values[3] = (u32)item_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].x_pos.val;
    observed_values[5] = (u32)item_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "edge_spawner_bounds", edge_spawner_bounds_cases, edge_spawner_bounds_cases_expected, COUNT(edge_spawner_bounds_cases), 0 },
    { "func_800B887C", 0, 0, 3, test_func_800B887C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(edge_spawner_bounds_cases) + 3;
