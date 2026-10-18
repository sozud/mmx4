#include "test_runtime.h"
#include "main/items/item_02_pickup.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 pickup_case(u32 mode)
{
    struct ItemObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual;
    u8 kind;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    for (i = 0; i < COUNT(g_Player.weapon_energy); i++)
        g_Player.weapon_energy[i] = 24;
    g_Player.hp = 20;
    g_Player.boss_flags = 1;
    g_Player.weapon_energy[0] = mode == 0 ? 40 : 20;
    g_Player.weapon_energy[1] = mode == 0 ? 3 : 7;
    g_Player.weapon_energy[2] = 11;
    engine_obj.collected_upgrades = mode == 2 ? 0 : 0x4000;
    engine_obj.sub_tanks[2] = 32;
    if (mode == 2)
        g_Player.weapon = 2;
    kind = mode == 0 ? 3 : mode == 1 ? 2
                                     : 0;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    func_800BFCC0(&obj, kind);
    actual = (u8)g_Player.weapon_energy[0] | ((u32)(u8)g_Player.weapon_energy[1] << 8)
        | ((u32)(u8)engine_obj.sub_tanks[2] << 16);
    player_before.weapon_energy[0] = g_Player.weapon_energy[0];
    player_before.weapon_energy[1] = g_Player.weapon_energy[1];
    engine_before.sub_tanks[2] = engine_obj.sub_tanks[2];
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    return actual;
}
#define PICKUP_CASE(m)                                   \
    static u32 energy_selection_context_pickup_##m(void) \
    {                                                    \
        return pickup_case(m);                           \
    }
PICKUP_CASE(0)
PICKUP_CASE(1)
PICKUP_CASE(2)
#define PICKUP_ENTRY(m) energy_selection_context_pickup_##m,
static const CTestCase energy_selection_context_cases[]
    = { PICKUP_ENTRY(0) PICKUP_ENTRY(1) PICKUP_ENTRY(2) };
static const u32 energy_selection_context_cases_expected[] = { 0x201330u, 0x200B18u, 0x200714u };
#undef PICKUP_CASE
#undef PICKUP_ENTRY

static u32 health_case(u32 mode)
{
    struct ItemObj item, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual;
    s8 energy = mode == 2 ? 0 : 4;
    s32 tank_gain = mode == 1 ? 20 : mode == 3 ? 2
                                               : 4;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&item, 0, sizeof(item));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    item.active = 1;
    item.id = 2;
    item.state = 1;
    item.unk5 = 3;
    item.unk6 = 4;
    item.x_pos.val = 100 * 65536 + 0x1234;
    item.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.hp = mode == 0 ? 10 : mode == 2 ? 0x92
                                             : 16;
    g_Player.weapon_energy[0] = mode == 0 ? 47 : mode == 2 ? 49
                                                           : 10;
    engine_obj.max_hp = 16;
    engine_obj.collected_upgrades = 0x3000;
    engine_obj.sub_tanks[0] = mode == 0 ? 0 : mode == 1 ? 16
                                                        : 32;
    engine_obj.sub_tanks[1] = mode == 3 ? 30 : 32;
    expected = item;
    player_before = g_Player;
    engine_before = engine_obj;
    if (mode == 0) {
        expected.active = 9;
        expected.state = 2;
        expected.unk5 = expected.unk6 = 0;
        expected.ext.item_2.unk80 = energy;
        expected.ext.item_2.unk81 = 2;
        engine_before.unk10 = engine_before.unk11 = engine_before.unk12 = engine_before.unk13 = 1;
        engine_before.unk14 = engine_before.unk15 = engine_before.unk16 = engine_before.unk17 = 1;
    } else {
        expected.state = 3;
        player_before.hp = mode == 2 ? 0x90 : 16;
    }
    player_before.weapon_energy[0] = mode == 0 || mode == 2 ? 48 : 14;
    if (mode == 0)
        engine_before.sub_tanks[0] = 0x84;
    if (mode == 1)
        engine_before.sub_tanks[0] = 0xA0;
    if (mode == 3)
        engine_before.sub_tanks[1] = 0xA0;
    pickup_collect_health(&item, energy, tank_gain);
    for (i = 0; i < sizeof(item) / 4; i++)
        assert(((u32*)&item)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    actual = (u8)item.state | ((u32)g_Player.weapon_energy[0] << 8) | ((u32)engine_obj.sub_tanks[0] << 16) | ((u32)engine_obj.sub_tanks[1] << 24);
    return actual;
}
#define CASE(m)                                           \
    static u32 pickup_health_tank_limits_health_##m(void) \
    {                                                     \
        return health_case(m);                            \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) pickup_health_tank_limits_health_##m,
static const CTestCase pickup_health_tank_limits_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 pickup_health_tank_limits_cases_expected[] = { 0xFF843002u, 0xFFA00E03u, 0x20203003u, 0xA0200E03u };
#undef CASE
#undef ENTRY

static const u32 inputs_0[3][22] = {
    { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16448, 0, 2 },
    { -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16448, 32, 2 },
    { -1, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 16448, 32, 2 },
};
struct func_800BFCC0_case {
    u32 expected[17];
};
static const struct func_800BFCC0_case func_800BFCC0_cases[] = {
    { { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x20u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x20u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800BFCC0(u32 row)
{
    const struct func_800BFCC0_case* c = &func_800BFCC0_cases[row];
    u32 observed_values[17];
    struct ItemObj obj;
    u8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    engine_obj.cur_character = inputs_0[row][0];
    g_Player.weapon = inputs_0[row][1];
    g_Player.boss_flags = inputs_0[row][2];
    g_Player.weapon_energy[0] = inputs_0[row][3];
    g_Player.weapon_energy[1] = inputs_0[row][4];
    g_Player.weapon_energy[2] = inputs_0[row][5];
    g_Player.weapon_energy[3] = inputs_0[row][6];
    g_Player.weapon_energy[4] = inputs_0[row][7];
    g_Player.weapon_energy[5] = inputs_0[row][8];
    g_Player.weapon_energy[6] = inputs_0[row][9];
    g_Player.weapon_energy[7] = inputs_0[row][10];
    g_Player.weapon_energy[8] = inputs_0[row][11];
    g_Player.weapon_energy[9] = inputs_0[row][12];
    g_Player.weapon_energy[10] = inputs_0[row][13];
    g_Player.weapon_energy[11] = inputs_0[row][14];
    g_Player.weapon_energy[12] = inputs_0[row][15];
    g_Player.weapon_energy[13] = inputs_0[row][16];
    g_Player.weapon_energy[14] = inputs_0[row][17];
    g_Player.weapon_energy[15] = inputs_0[row][18];
    engine_obj.collected_upgrades = inputs_0[row][19];
    engine_obj.sub_tanks[2] = inputs_0[row][20];
    arg1 = inputs_0[row][21];
    func_800BFCC0(&obj, arg1);
    observed_values[0] = (u32)engine_obj.sub_tanks[2];
    observed_values[1] = (u32)g_Player.weapon_energy[0];
    observed_values[2] = (u32)g_Player.weapon_energy[10];
    observed_values[3] = (u32)g_Player.weapon_energy[11];
    observed_values[4] = (u32)g_Player.weapon_energy[12];
    observed_values[5] = (u32)g_Player.weapon_energy[13];
    observed_values[6] = (u32)g_Player.weapon_energy[14];
    observed_values[7] = (u32)g_Player.weapon_energy[15];
    observed_values[8] = (u32)g_Player.weapon_energy[1];
    observed_values[9] = (u32)g_Player.weapon_energy[2];
    observed_values[10] = (u32)g_Player.weapon_energy[3];
    observed_values[11] = (u32)g_Player.weapon_energy[4];
    observed_values[12] = (u32)g_Player.weapon_energy[5];
    observed_values[13] = (u32)g_Player.weapon_energy[6];
    observed_values[14] = (u32)g_Player.weapon_energy[7];
    observed_values[15] = (u32)g_Player.weapon_energy[8];
    observed_values[16] = (u32)g_Player.weapon_energy[9];
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

static const u32 pickup_collect_health_expected[] = { 0u, 0xFFFFFFA0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u };
static u32 test_pickup_collect_health(u32 row)
{
    u32 observed_values[11];
    struct ItemObj obj;
    s8 arg1;
    s32 arg2;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    engine_obj.collected_upgrades = 8224;
    engine_obj.sub_tanks[1] = 28;
    engine_obj.sub_tanks[2] = 0;
    arg1 = 0;
    arg2 = 28;
    pickup_collect_health(&obj, arg1, arg2);
    observed_values[0] = (u32)engine_obj.sub_tanks[0];
    observed_values[1] = (u32)engine_obj.sub_tanks[1];
    observed_values[2] = (u32)engine_obj.sub_tanks[2];
    observed_values[3] = (u32)g_Player.hp;
    observed_values[4] = (u32)g_Player.weapon_energy[0];
    observed_values[5] = (u32)obj.active;
    observed_values[6] = (u32)obj.ext.item_2.unk80;
    observed_values[7] = (u32)obj.ext.item_2.unk81;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk5;
    observed_values[10] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, pickup_collect_health_expected, 11);
}

const struct CTestGroup c_test_groups[] = {
    { "energy_selection_context", energy_selection_context_cases, energy_selection_context_cases_expected, COUNT(energy_selection_context_cases), 0 },
    { "pickup_health_tank_limits", pickup_health_tank_limits_cases, pickup_health_tank_limits_cases_expected, COUNT(pickup_health_tank_limits_cases), 0 },
    { "func_800BFCC0", 0, 0, 3, test_func_800BFCC0 },
    { "pickup_collect_health", 0, 0, 1, test_pickup_collect_health },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(energy_selection_context_cases) + COUNT(pickup_health_tank_limits_cases) + 3 + 1;
