#include "test_runtime.h"
#include "main/effects/effect_38_cyberspace_trial.h"
#include "main/items/item_27_boss_teleporter.h"
#include "main/mains/main_60_storm_owl.h"
void cyberspace_trial_delete_unused_items(void);

static u32 warp_case(u32 mode)
{
    struct EffectObj owner, before;
    struct MiscObj expected[64];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, actual, available = mode == 3 ? 2 : mode;
    void* link = mode == 3 ? NULL : &owner;
    memset(misc_objects, 0x5A, sizeof(misc_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    if (available >= 1)
        misc_objects[60].active = 0;
    if (available >= 2)
        misc_objects[63].active = 0;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 38;
    owner.state = 1;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    before = owner;
    memcpy(expected, misc_objects, sizeof(expected));
    if (available >= 1) {
        expected[60].active = 0x41;
        expected[60].id = 33;
        expected[60].unk2 = 0;
        expected[60].ext.pointer.unk50 = link;
    }
    if (available >= 2) {
        expected[63].active = 0x41;
        expected[63].id = 33;
        expected[63].unk2 = 1;
        expected[63].ext.pointer.unk50 = link;
    }
    cyberspace_trial_spawn_warps(link);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(expected) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    actual = misc_objects[60].active | ((u32)misc_objects[63].active << 8);
    return actual;
}
static const u32 cyberspace_warp_pair_pool_cases_expected[] = { 0x101u, 0x141u, 0x4141u, 0x4141u };

static const u32 inputs_0[2][4] = {
    { 1, 2, 6, 0 },
    { 1, 255, 0, 0 },
};
struct cyberspace_trial_advance_case {
    u32 expected[4];
};
static const struct cyberspace_trial_advance_case cyberspace_trial_advance_cases[] = {
    { { 6u, 0x40u, 0u, 1u } },
    { { 2u, 0xFFFFFFC0u, 0u, 1u } },
};
static u32 test_cyberspace_trial_advance(u32 row)
{
    const struct cyberspace_trial_advance_case* c = &cyberspace_trial_advance_cases[row];
    u32 observed_values[4];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.ext.effect_38.timer = inputs_0[row][0];
    obj.ext.effect_38.variant = inputs_0[row][1];
    engine_obj.checkpoint = inputs_0[row][2];
    obj.state = inputs_0[row][3];
    cyberspace_trial_advance(&obj);
    observed_values[0] = (u32)engine_obj.checkpoint;
    observed_values[1] = (u32)engine_obj.unkF;
    observed_values[2] = (u32)obj.ext.effect_38.timer;
    observed_values[3] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 cyberspace_trial_spawn_guide_expected[] = { 1u, 0u, 0u };
static u32 test_cyberspace_trial_spawn_guide(u32 row)
{
    u32 observed_values[3];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    FILL_ACTIVE(misc_objects, 64, 255 ? 1 : 0);
    cyberspace_trial_spawn_guide(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].id;
    observed_values[2] = (u32)misc_objects[0].unk2;
    return c_test_observe(0, row, observed_values, cyberspace_trial_spawn_guide_expected, 3);
}

#include "support/pool_cleanup.h"
CLEANUP_DELETE_CASE(delete_matches, 1, 0x1u)
CLEANUP_DELETE_CASE(delete_others, 0, 0x1u)
static const CTestCase delete_items_pool_cases[] = {
    delete_matches,
    delete_others,
};
static const u32 delete_items_pool_cases_expected[] = { 0x1u, 0x1u };

#include "support/warp_spawns.h"
WARP_TRIAL_CASE(trial_inactive, 0, 0, 0, 0, 0)
WARP_TRIAL_CASE(trial_odd, 1, 1, 0, 0, 0)
WARP_TRIAL_CASE(trial_other_stage, 1, 0, 1, 0, 0)
WARP_TRIAL_CASE(trial_full, 1, 0, 0, 0, 1)
WARP_TRIAL_CASE(trial_rank0, 1, 0, 0, 0, 0)
WARP_TRIAL_CASE(trial_rank1, 1, 0, 0, 1, 0)
WARP_TRIAL_CASE(trial_rank2, 1, 0, 0, 2, 0)
WARP_TRIAL_CASE(trial_default, 1, 0, 0, 3, 0)
static const CTestCase rank_warp_spawn_cases[] = { WARP_ENTRY(trial_inactive) WARP_ENTRY(trial_odd) WARP_ENTRY(trial_other_stage) WARP_ENTRY(trial_full) WARP_ENTRY(trial_rank0) WARP_ENTRY(trial_rank1) WARP_ENTRY(trial_rank2) WARP_ENTRY(trial_default) };

static const u32 rank_warp_spawn_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x1u, 0x1022141u, 0x1032141u, 0x1042141u, 0x1002141u };
static u32 test_trial_item_selection(u32 row)
{
    static const u8 removed_items[7][2] = {
        { 0, 0 },
        { 0xD, 0x6 },
        { 0, 0 },
        { 0xB, 0x5 },
        { 0, 0 },
        { 0x7, 0x3 },
        { 0, 0 },
    };
    static const u8 ids[8] = { 2, 2, 2, 26, 2, 26, 1, 3 };
    static const u8 subtypes[8] = { 4, 12, 15, 0, 0, 1, 4, 15 };
    struct ItemObj expected[32];
    struct StageObjectRecord records[32], records_before[32];
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u32 i, kind, checkpoint = row / 2, character = row % 2;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.checkpoint = checkpoint;
    engine_obj.cur_character = character;
    engine_obj.unk4 = 0x1234;
    engine_before = engine_obj;
    memset(records, 0xD7, sizeof(records));
    memset(item_objects, 0x5A, sizeof(item_objects));
    for (i = 0; i < COUNT(item_objects); i++) {
        kind = i % COUNT(ids);
        item_objects[i].active = i < 16 ? 0x41 : 0;
        item_objects[i].id = ids[kind];
        item_objects[i].unk2 = subtypes[kind];
        item_objects[i].backref = &records[i];
        records[i].id = ids[kind];
        records[i].subtype = subtypes[kind];
    }
    memcpy(expected, item_objects, sizeof(expected));
    memcpy(records_before, records, sizeof(records_before));
    for (i = 0; i < COUNT(expected); i++) {
        kind = i % COUNT(ids);
        if (kind < 4 && (removed_items[checkpoint][character] & (1 << kind)))
            memset(&expected[i], 0, sizeof(expected[i]));
    }
    cyberspace_trial_delete_unused_items();
    c_test_same_words(item_objects, expected, sizeof(expected));
    c_test_same_words(records, records_before, sizeof(records));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "trial_item_selection", 0, 0, 14, test_trial_item_selection },
    { "cyberspace_warp_pair_pool", NULL, cyberspace_warp_pair_pool_cases_expected, COUNT(cyberspace_warp_pair_pool_cases_expected), warp_case },
    { "cyberspace_trial_advance", 0, 0, 2, test_cyberspace_trial_advance },
    { "cyberspace_trial_spawn_guide", 0, 0, 1, test_cyberspace_trial_spawn_guide },
    { "delete_items_pool", delete_items_pool_cases, delete_items_pool_cases_expected, COUNT(delete_items_pool_cases), 0 },
    { "rank_warp_spawn", rank_warp_spawn_cases, rank_warp_spawn_cases_expected, COUNT(rank_warp_spawn_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 14 + COUNT(cyberspace_warp_pair_pool_cases_expected) + 2 + 1 + COUNT(delete_items_pool_cases) + COUNT(rank_warp_spawn_cases);
