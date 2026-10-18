#include "test_runtime.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
void frost_tower_charged_spawn_part(s8);

static u32 shard_case(u32 mode, u32 observation)
{
    struct MiscObj obj;
    u32 actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 0x25;
    obj.on_screen = 1;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x2468;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 2 * 65536;
    obj.unk2C = 0x5000;
    g_Player.weapon = mode == 3 ? 0 : 2;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.shot_type = mode == 4 ? 0xB : 0;
    frost_shard_update(&obj);
    assert(g_Player.weapon == (mode == 3 ? 0 : 2));
    assert(g_Player.input_locked == (mode == 1));
    assert(g_Player.capsule_state == (mode == 2));
    assert(g_Player.shot_type == (mode == 4 ? 0xB : 0));
    assert(obj.bg_offset == -1 && obj.x_vel.val == 65536 && obj.unk2C == 0x5000);
    if (observation == 1)
        return (u32)obj.x_pos.val;
    if (observation == 2)
        return (u32)obj.y_pos.val;
    if (observation == 3)
        return (u32)obj.y_vel.val;
    actual = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.id << 16) | ((u32)(u8)obj.on_screen << 24);
    return actual;
}
#define OBSERVE(mode, field)                                  \
    static u32 frost_shard_gates_shard_##mode##_##field(void) \
    {                                                         \
        return shard_case(mode, field);                       \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) OBSERVE(mode, 3)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
#define ENTRY(mode, field) frost_shard_gates_shard_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) ENTRY(mode, 3)
static const CTestCase frost_shard_gates_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) };
static const u32 frost_shard_gates_cases_expected[] = { 0x250101u, 0x651234u, 0xC62468u, 0x1B000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u, 0x0u, 0x641234u, 0xC82468u, 0x20000u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 cancel_case(u32 mode)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u8 palette_before = need_palette_load;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 2;
    obj.unk2 = 7;
    obj.on_screen = 1;
    obj.state = mode ? 1 : 2;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.unk50 = (const u8*)&box;
    obj.unk68 = &box;
    obj.unk70 = 0xA5;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.weapon = mode == 3 ? 0 : 2;
    g_Player.hp = 16;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.shot_type = mode == 4 ? 11 : 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    expected = obj;
    player_before = g_Player;
    expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
    expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    expected.unk50 = NULL;
    expected.unk68 = NULL;
    expected.unk70 = 0;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    player_before.shot_count = 2;
    player_before.special_shot_count = 1;
    frost_tower_update(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(need_palette_load == palette_before);
    return (u8)obj.state | ((u32)(u8)player_before.shot_count << 8) | ((u32)(u8)player_before.special_shot_count << 16);
}
#define CASE(m)                                                   \
    static u32 frost_tower_cancellation_dispatch_cancel_##m(void) \
    {                                                             \
        return cancel_case(m);                                    \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) frost_tower_cancellation_dispatch_cancel_##m,
static const CTestCase frost_tower_cancellation_dispatch_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 frost_tower_cancellation_dispatch_cases_expected[] = { 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u };
#undef CASE
#undef ENTRY

static const u32 frost_tower_charged_spawn_part_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u };
static u32 test_frost_tower_charged_spawn_part(u32 row)
{
    u32 observed_values[6];
    u8 pool_0_full;
    s8 arg0;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    pool_0_full = 255;
    arg0 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pool_0_full ? 1 : 0;
    }
    frost_tower_charged_spawn_part(arg0);
    observed_values[0] = (u32)g_Player.shot_count;
    observed_values[1] = (u32)g_Player.special_shot_count;
    observed_values[2] = (u32)weapon_objects[0].active;
    observed_values[3] = (u32)weapon_objects[0].bg_offset;
    observed_values[4] = (u32)weapon_objects[0].id;
    observed_values[5] = (u32)weapon_objects[0].unk2;
    return c_test_observe(0, row, observed_values, frost_tower_charged_spawn_part_expected, 6);
}

static const u32 frost_tower_spawn_shard_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_frost_tower_spawn_shard(u32 row)
{
    u32 observed_values[6];
    struct WeaponObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    frost_tower_spawn_shard(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].bg_offset;
    observed_values[2] = (u32)misc_objects[0].id;
    observed_values[3] = (u32)misc_objects[0].unk2;
    observed_values[4] = (u32)misc_objects[0].x_pos.val;
    observed_values[5] = (u32)misc_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, frost_tower_spawn_shard_expected, 6);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(1)
CHARGED_CASE(1, 6)
static const CTestCase frost_tower_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(1) CHARGED_ENTRIES(1, 6) };

static const u32 frost_tower_charged_dispatch_cases_expected[] = { 0x1000191u, 0x605u, 0x0u, 0x504u, 0x0u, 0x504u, 0x0u, 0x504u, 0x0u, 0x504u };
const struct CTestGroup c_test_groups[] = {
    { "frost_shard_gates", frost_shard_gates_cases, frost_shard_gates_cases_expected, COUNT(frost_shard_gates_cases), 0 },
    { "frost_tower_cancellation_dispatch", frost_tower_cancellation_dispatch_cases, frost_tower_cancellation_dispatch_cases_expected, COUNT(frost_tower_cancellation_dispatch_cases), 0 },
    { "frost_tower_charged_spawn_part", 0, 0, 1, test_frost_tower_charged_spawn_part },
    { "frost_tower_spawn_shard", 0, 0, 1, test_frost_tower_spawn_shard },
    { "frost_tower_charged_dispatch", frost_tower_charged_dispatch_cases, frost_tower_charged_dispatch_cases_expected, COUNT(frost_tower_charged_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frost_shard_gates_cases) + COUNT(frost_tower_cancellation_dispatch_cases) + 1 + 1 + COUNT(frost_tower_charged_dispatch_cases);
