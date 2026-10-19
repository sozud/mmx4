#include "test_runtime.h"
#include "main/effects/effect_42_sigma_sequencer_fx.h"

static const u32 sigma_sequencer_fx_wait_player_expected[] = { 0u, 0u };
static u32 test_sigma_sequencer_fx_wait_player(u32 row)
{
    u32 observed_values[2];
    struct EffectObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.update_delay = -1;
    obj.ext.effect_42.owner.main = NULL;
    sigma_sequencer_fx_wait_player(&obj);
    observed_values[0] = (u32)child_0.ext.main_73_parts.effect_state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, sigma_sequencer_fx_wait_player_expected, 2);
}

static const u8 modes[] = { 0, 1, 2, 3, 5, 6, 7 };
static u32 start(u32 row)
{
    struct EffectObj obj, expected;
    struct MainObj owner, owner_expected;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_before = main_bss_state;
    u32 mode = modes[row % COUNT(modes)], initial = row / COUNT(modes);
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 1;
    obj.id = 42;
    obj.ext.effect_42.owner.main = &owner;
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    owner.ext.main_73_parts.object_id = mode;
    owner.ext.main_73_parts.unk8E = 9;
    owner.ext.main_73_parts.effect_state = initial;
    expected = obj;
    owner_expected = owner;
    owner_expected.ext.main_73_parts.unk8E = 0;
    expected.state = mode < 3 ? 1 : 2;
    if (mode >= 3)
        owner_expected.ext.main_73_parts.effect_state = 1;
    sigma_sequencer_fx_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_sequencer_fx_wait_player", 0, 0, 1, test_sigma_sequencer_fx_wait_player },
    { "every_sequencer_mode_passed_by_real_sigma_callers", NULL, NULL, COUNT(modes) * 2, start },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(modes) * 2;
