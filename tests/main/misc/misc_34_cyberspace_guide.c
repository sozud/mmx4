#include "test_runtime.h"
#include "main/misc/misc_34_cyberspace_guide.h"

struct func_800CEFC0_case {
    u32 variant, checkpoint, unk58, unk57, unk17;
    u32 expected[4];
};
static const struct func_800CEFC0_case func_800CEFC0_cases[] = {
    { 2, 0, 0, 0, 0, { 0u, 0u, 0u, 2u } },
    { 240, -115, 0, 254, 0, { 0u, 1u, 0u, 2u } },
    { 242, -117, 60, 31, 3, { 0x20u, 0u, 0u, 0xF2u } },
};
static u32 test_func_800CEFC0(u32 row)
{
    const struct func_800CEFC0_case* c = &func_800CEFC0_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.ext.misc_34.enabled = 255;
    obj.ext.misc_34.variant = c->variant;
    engine_obj.checkpoint = c->checkpoint;
    obj.ext.misc_34.unk58 = c->unk58;
    obj.ext.misc_34.unk57 = c->unk57;
    obj.unk17 = c->unk17;
    func_800CEFC0(&obj);
    observed_values[0] = (u32)obj.ext.misc_34.unk57;
    observed_values[1] = (u32)obj.ext.misc_34.unk58;
    observed_values[2] = (u32)obj.ext.misc_34.unk5A;
    observed_values[3] = (u32)obj.ext.misc_34.variant;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

void cyberspace_guide_leave_finish(struct MiscObj*);
static u32 finish(u32 row)
{
    struct MiscObj obj, expected;
    struct EffectObj related, related_expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u32 checkpoint = row % 6, wait = row / 6;
    memset(&obj, 0, sizeof(obj));
    memset(&related, 0, sizeof(related));
    engine_obj.stage = 6;
    engine_obj.checkpoint = checkpoint;
    engine_before = engine_obj;
    related.active = 1;
    related.id = 38;
    related.state = 1;
    related.ext.effect_38.variant = 2;
    related_expected = related;
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 3 * 65536;
    obj.unk28 = -0x1000;
    obj.ext.misc_34.timer = wait ? 2 : 1;
    obj.ext.misc_34.related = &related;
    obj.ext.misc_34.variant = 0;
    expected = obj;
    expected.x_pos.val += 3 * 65536;
    expected.x_vel.val += 0x1000;
    expected.ext.misc_34.timer--;
    if (!wait) {
        related_expected.ext.effect_38.active = 1;
        related_expected.ext.effect_38.variant = checkpoint % 2 ? 3 : 0;
        expected.state = 2;
        expected.unk5 = expected.unk6 = 0;
    }
    cyberspace_guide_leave_finish(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&related, &related_expected, sizeof(related));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "func_800CEFC0", 0, 0, 3, test_func_800CEFC0 },
    { "real_trial_entry_exit_checkpoint_parity_and_last_drift_tick", NULL, NULL, 12, finish },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + 12;
