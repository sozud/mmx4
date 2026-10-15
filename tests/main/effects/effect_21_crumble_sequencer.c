#include "test_runtime.h"

static u32 chain_default(void)
{
    struct EffectObj obj, before;
    struct PlayerObj player_before;
    u32 actual, i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 1;
    obj.unk5 = 3;
    obj.ext.effect_21.index = 13;
    obj.ext.effect_21.cursor = crumble_sequencer_sequences[13];
    obj.ext.effect_21.timer = 0x27;
    before = obj;
    player_before = g_Player;
    crumble_sequencer_chain(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    actual = (u8)obj.unk5 | ((u32)obj.ext.effect_21.index << 8) | ((u32)obj.ext.effect_21.timer << 16);
    return actual;
}
static const CTestCase crumble_chain_raw_default_cases[] = { chain_default };
static const u32 crumble_chain_raw_default_cases_expected[] = { 0x270D03u };

struct crumble_sequencer_chain_case {
    u32 unk5, index, pool_1_full, child_0_present, flags, pool_0_full;
    u32 expected[12];
};
static const struct crumble_sequencer_chain_case crumble_sequencer_chain_cases[] = {
    { -1, 0, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu } },
    { 2, 13, 0, 255, 128, 255, { 1u, 0u, 0u, 0x41u, 8u, 0u, 0u, 0u, 0xDu, 1u, 1u, 2u } },
    { 2, 0, 255, 0, 0, 0, { 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u } },
};
static u32 test_crumble_sequencer_chain(u32 row)
{
    const struct crumble_sequencer_chain_case* c = &crumble_sequencer_chain_cases[row];
    u32 observed_values[12];
    struct EffectObj obj;
    struct Effect21SpawnRecord child_0;
    u8 child_0_present;
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.unk5 = c->unk5;
    obj.ext.effect_21.index = c->index;
    obj.ext.effect_21.timer = 0;
    pool_1_full = c->pool_1_full;
    child_0_present = c->child_0_present;
    child_0.flags = c->flags;
    pool_0_full = c->pool_0_full;
    obj.ext.effect_21.cursor = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    crumble_sequencer_chain(&obj);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].id;
    observed_values[2] = (u32)item_objects[0].unk2;
    observed_values[3] = (u32)misc_objects[0].active;
    observed_values[4] = (u32)misc_objects[0].id;
    observed_values[5] = (u32)misc_objects[0].unk2;
    observed_values[6] = (u32)misc_objects[0].x_pos.i.hi;
    observed_values[7] = (u32)misc_objects[0].y_pos.i.hi;
    observed_values[8] = (u32)obj.ext.effect_21.index;
    observed_values[9] = (u32)obj.ext.effect_21.timer;
    observed_values[10] = (u32)obj.state;
    observed_values[11] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

static const u32 func_800B9EC0_expected[] = { 0u, 0u, 0u, 0u, 1u };
static u32 test_func_800B9EC0(u32 row)
{
    u32 observed_values[5];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    func_800B9EC0(&obj);
    observed_values[0] = (u32)obj.ext.effect_21.index;
    observed_values[1] = (u32)obj.ext.effect_21.phase;
    observed_values[2] = (u32)obj.ext.effect_21.spawned;
    observed_values[3] = (u32)obj.ext.effect_21.timer;
    observed_values[4] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, func_800B9EC0_expected, 5);
}

struct func_800BA178_case {
    u32 unk5, timer, pool_0_full, pool_2_full, unk2, flags, pool_1_full;
    u32 expected[15];
};
static const struct func_800BA178_case func_800BA178_cases[] = {
    { -1, 1, 255, 0, 0, 0, 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0xFFFFFFFFu } },
    { 0, 0, 0, 0, 5, 128, 255, { 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0x41u, 8u, 0u, 0u, 0u, 3u, 1u, 0u } },
    { 0, 0, 0, 255, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800BA178(u32 row)
{
    const struct func_800BA178_case* c = &func_800BA178_cases[row];
    u32 observed_values[15];
    struct EffectObj obj;
    struct Effect21SpawnRecord child_0;
    u8 child_0_present;
    u8 pool_0_full;
    u8 pool_2_full;
    u8 pool_1_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.unk5 = c->unk5;
    obj.ext.effect_21.timer = c->timer;
    pool_0_full = c->pool_0_full;
    obj.ext.effect_21.index = 0;
    pool_2_full = c->pool_2_full;
    child_0_present = 255;
    obj.unk2 = c->unk2;
    child_0.flags = c->flags;
    pool_1_full = c->pool_1_full;
    obj.ext.effect_21.cursor = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_2_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_1_full ? 1 : 0;
    }
    func_800BA178(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].ext.effect_21.index;
    observed_values[2] = (u32)effect_objects[0].id;
    observed_values[3] = (u32)effect_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].active;
    observed_values[5] = (u32)item_objects[0].id;
    observed_values[6] = (u32)item_objects[0].unk2;
    observed_values[7] = (u32)misc_objects[0].active;
    observed_values[8] = (u32)misc_objects[0].id;
    observed_values[9] = (u32)misc_objects[0].unk2;
    observed_values[10] = (u32)misc_objects[0].x_pos.i.hi;
    observed_values[11] = (u32)misc_objects[0].y_pos.i.hi;
    observed_values[12] = (u32)obj.ext.effect_21.timer;
    observed_values[13] = (u32)obj.state;
    observed_values[14] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 15);
}

const struct CTestGroup c_test_groups[] = {
    { "crumble_chain_raw_default", crumble_chain_raw_default_cases, crumble_chain_raw_default_cases_expected, COUNT(crumble_chain_raw_default_cases), 0 },
    { "crumble_sequencer_chain", 0, 0, 3, test_crumble_sequencer_chain },
    { "func_800B9EC0", 0, 0, 1, test_func_800B9EC0 },
    { "func_800BA178", 0, 0, 3, test_func_800BA178 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(crumble_chain_raw_default_cases) + 3 + 1 + 3;
