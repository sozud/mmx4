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

static const u8 modes[] = { 0, 1, 2, 3 };
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

#include "support/state_cases.h"
void func_800BE364(struct EffectObj*);
static struct MainObj seq_owner, seq_parts[3];
static struct PlayerObj seq_player;
#define se state_room.effect
#define SEQ_OWNER ((struct Main73PartsExt*)&seq_owner.ext)
#define SEQ(st, step, a, b, c, setup) (seq_player = g_Player, state_reset(step, 0, 0), memset(&seq_owner, 0, sizeof(seq_owner)), memset(seq_parts, 0, sizeof(seq_parts)), SEQ_OWNER->parts[0] = &seq_parts[0], SEQ_OWNER->parts[1] = &seq_parts[1], SEQ_OWNER->parts[2] = &seq_parts[2], SEQ_OWNER->object_id = 2, SEQ_OWNER->effect_state = 7, seq_parts[0].unk5 = a, seq_parts[1].unk5 = b, seq_parts[2].unk5 = c, seq_parts[0].unk2 = 0, seq_parts[1].unk2 = 1, seq_parts[2].unk2 = 3, g_Player.update_delay = 0, se.active = 1, se.state = st, se.ext.effect_42.owner.main = &seq_owner, se.ext.effect_42.timer = 5, setup, sigma_sequencer_fx_update(&se), state_extra = SEQ_OWNER->effect_state | (u32)se.ext.effect_42.timer << 8, se.ext.effect_42.owner.main = NULL, g_Player = seq_player)
static void seq_start(void)
{
    SEQ(1, 0, 0, 0, 0, 0);
}
static void seq_player_ready(void) { SEQ(1, 1, 0, 0, 0, 0); }
static void seq_parts_pending(void) { SEQ(1, 2, 3, 3, 0, 0); }
static void seq_right_part(void) { SEQ(1, 2, 3, 3, 3, seq_parts[2].unk2 = 2); }
static void seq_wrong_parts(void) { SEQ(1, 2, 3, 3, 3, 0); }
static void seq_wait_pending(void) { SEQ(1, 3, 3, 0, 3, 0); }
static void seq_wait_done(void) { SEQ(1, 3, 3, 3, 3, 0); }
static void seq_hold(void) { SEQ(1, 4, 0, 0, 0, 0); }
static void seq_hold_ends(void) { SEQ(1, 4, 0, 0, 0, se.ext.effect_42.timer = 1); }
static void seq_finish_waits(void) { SEQ(2, 0, 0, 0, 0, g_Player.update_delay = 1); }
static void seq_finish(void) { SEQ(2, 0, 0, 0, 0, 0); }
static void (*const seq_cases[])(void) = {
    seq_start,
    seq_player_ready,
    seq_parts_pending,
    seq_right_part,
    seq_wrong_parts,
    seq_wait_pending,
    seq_wait_done,
    seq_hold,
    seq_hold_ends,
    seq_finish_waits,
    seq_finish,
};
static const u32 seq_expected[] = {
    0x101u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x501u,
    0x0u,
    0x201u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x500u,
    0x0u,
    0x201u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x507u,
    0x0u,
    0x301u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x502u,
    0x0u,
    0x401u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0xC803u,
    0x0u,
    0x301u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x507u,
    0x0u,
    0x401u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0xC803u,
    0x0u,
    0x401u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x407u,
    0x0u,
    0x2u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x7u,
    0x0u,
    0x2u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x507u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x500u,
    0x0u,
};
static u32 test_seq(u32 row)
{
    return object_run(seq_cases[row], row, &seq_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_sequencer_fx_wait_player", 0, 0, 1, test_sigma_sequencer_fx_wait_player },
    { "every_sequencer_mode_passed_by_real_sigma_callers", NULL, NULL, COUNT(modes), start },
    { "sigma_sequencer_fx_steps", 0, 0, COUNT(seq_cases), test_seq },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(modes) + COUNT(seq_cases);
