#include "test_runtime.h"

static const u32 sigma_sequencer_fx_wait_player_expected[] = { 0u, 0u };
static u32 test_sigma_sequencer_fx_wait_player(u32 row)
{
    u32 observed_values[2];
    struct EffectObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.update_delay = -1;
    child_0_present = 0;
    obj.ext.effect_42.owner.main = child_0_present ? &child_0 : NULL;
    sigma_sequencer_fx_wait_player(&obj);
    observed_values[0] = (u32)child_0.ext.main_73_parts.effect_state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, sigma_sequencer_fx_wait_player_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_sequencer_fx_wait_player", 0, 0, 1, test_sigma_sequencer_fx_wait_player },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
