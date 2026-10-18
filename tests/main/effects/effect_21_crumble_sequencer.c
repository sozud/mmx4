#include "test_runtime.h"
#include "main/effects/effect_21_crumble_sequencer.h"

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
    obj.unk2 = c->unk2;
    child_0.flags = c->flags;
    pool_1_full = c->pool_1_full;
    obj.ext.effect_21.cursor = &child_0;
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

static struct EffectObj expected_effects[32];
static struct MiscObj expected_misc[64];
static u32 phases(u32 row)
{
    struct EngineObj engine;
    struct PlayerObj player;
    struct BackgroundObj backgrounds[3];
    u32 i, phase;
    u16 rng = cur_random;
    struct EffectObj* self = &effect_objects[0];
    (void)row;
    engine_obj.state = 6;
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    engine = engine_obj;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.bg_offset = 0;
    g_Player.y_pos.i.hi = 592;
    g_Player.x_pos.i.hi = 1700;
    player = g_Player;
    background_objects[0].x_pos.i.hi = 1552;
    background_objects[0].y_pos.i.hi = 512;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 32; i++)
        effect_objects[i].active = 1;
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    effect_objects[31].active = 0;
    self->id = 21;
    crumble_sequencer_update(self);
    assert(self->state == 1 && self->ext.effect_21.spawned == 0 && self->ext.effect_21.phase == 0);
    crumble_sequencer_update(self);
    assert(self->ext.effect_21.spawned == 4 && self->ext.effect_21.phase == 1 && self->ext.effect_21.timer == 150);
    assert(effect_objects[31].active == 1 && effect_objects[31].id == 21 && effect_objects[31].unk2 == 1 && effect_objects[31].ext.effect_21.index == 2);
    crumble_sequencer_update(&effect_objects[31]);
    assert(effect_objects[31].state == 1 && effect_objects[31].ext.effect_21.cursor == crumble_sequencer_sequences[2]);
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    crumble_sequencer_update(&effect_objects[31]);
    assert(c_test_word_difference((u32*)effect_objects, (u32*)expected_effects, sizeof(expected_effects) / 4) == 0);
    for (phase = 1; phase < 3; phase++) {
        for (i = 150; i > 0; i--) {
            assert(self->ext.effect_21.timer == i);
            crumble_sequencer_update(self);
        }
        assert(self->ext.effect_21.timer == 0 && self->ext.effect_21.phase == phase);
        crumble_sequencer_update(self);
        assert(self->ext.effect_21.spawned == 4 && self->ext.effect_21.phase == phase + 1 && self->ext.effect_21.timer == 150);
    }
    expected_effects[0].ext.effect_21.phase = 3;
    expected_effects[0].ext.effect_21.was_inside = 1;
    assert(c_test_word_difference((u32*)effect_objects, (u32*)expected_effects, sizeof(expected_effects) / 4) == 0);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected_misc, sizeof(expected_misc) / 4) == 0);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(cur_random == rng);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "crumble_chain_raw_default", crumble_chain_raw_default_cases, crumble_chain_raw_default_cases_expected, COUNT(crumble_chain_raw_default_cases), 0 },
    { "crumble_sequencer_chain", 0, 0, 3, test_crumble_sequencer_chain },
    { "func_800B9EC0", 0, 0, 1, test_func_800B9EC0 },
    { "func_800BA178", 0, 0, 3, test_func_800BA178 },
    { "real_crumble_phase_birth_and_retirement_full_effect_pool", NULL, NULL, 1, phases },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(crumble_chain_raw_default_cases) + 3 + 1 + 3 + 1;
