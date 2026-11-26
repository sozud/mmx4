#include "test_runtime.h"
#include "main/misc/misc_34_cyberspace_guide.h"
#include "main/55C4.h"

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

static u32 guide_counter(u32 row);
static u32 guide_main(u32 row);
const struct CTestGroup c_test_groups[] = {
    { "guide_counter", 0, 0, 6, guide_counter },
    { "guide_main", 0, 0, 10, guide_main },
    { "real_trial_entry_exit_checkpoint_parity_and_last_drift_tick", NULL, NULL, 12, finish },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 6 + 10 + 12;

struct GuideCounter {
    u8 enabled, variant, unk57, unk58, unk17;
    u8 out_variant, out_unk57, out_unk58, out_unk17;
    u16 out_unk5A;
};
static const struct GuideCounter guide_counters[] = {
    { 0, 0, 11, 0x3C, 0, 0, 11, 0x3C, 0, 0 },
    { 1, 2, 11, 0x3C, 0, 2, 11, 0x3C, 0, 0 },
    { 1, 0, 11, 0x3C, 0, 0, 12, 0, 2, 0xB4 },
    { 1, 0, 11, 0x3C, 3, 0, 12, 0, 3, 0 },
    { 1, 0, 14, 0x3C, 0, 1, 0, 0, 0, 0 },
    { 1, 1, 15, 0, 0, 2, 0, 1, 0, 0 },
};
extern union AnimationStep* cyberspace_guide_animations[5];
static u32 guide_counter(u32 row)
{
    const struct GuideCounter* c = &guide_counters[row];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.animation_table = (u32**)cyberspace_guide_animations;
    set_animation(&obj, c->unk17);
    obj.ext.misc_34.enabled = c->enabled;
    obj.ext.misc_34.variant = c->variant;
    obj.ext.misc_34.unk57 = c->unk57;
    obj.ext.misc_34.unk58 = c->unk58;
    func_800CEFC0(&obj);
    assert(obj.ext.misc_34.variant == c->out_variant && obj.ext.misc_34.unk57 == c->out_unk57);
    assert(obj.ext.misc_34.unk58 == c->out_unk58 && obj.unk17 == c->out_unk17);
    assert(obj.ext.misc_34.unk5A == c->out_unk5A && obj.ext.misc_34.enabled == c->enabled);
    return 1;
}

void cyberspace_guide_update(struct MiscObj*);
static u32 guide_main(u32 row)
{
    static const u8 steps[] = { 0, 0, 1, 1, 3, 3 }, animations[] = { 0, 0, 1, 2, 4, 3 }, timers[] = { 2, 1, 2, 1, 2, 1 };
    static const s16 follow_x[] = { 100, 300, 200, 200 }, follow_y[] = { 100, 200, 151, 166 };
    static const u8 related_states[] = { 3, 4, 2, 2 };
    struct MiscObj obj;
    struct EffectObj related;
    memset(&obj, 0, sizeof(obj));
    memset(&related, 0, sizeof(related));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.checkpoint = 2;
    engine_obj.unk10 = engine_obj.unk11 = engine_obj.unk12 = engine_obj.unk13 = 1;
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.animation_table = (u32**)cyberspace_guide_animations;
    obj.ext.misc_34.related = &related;
    if (row >= 6) {
        g_Player.x_pos.i.hi = 200;
        g_Player.y_pos.i.hi = 150;
        obj.x_pos.i.hi = follow_x[row - 6];
        obj.y_pos.i.hi = follow_y[row - 6];
        obj.unk5 = 2;
        related.state = related_states[row - 6];
        set_animation(&obj, 1);
        func_800CEBC0(&obj);
        if (row == 8) {
            assert(obj.x_pos.val == g_Player.x_pos.val && obj.y_pos.val == g_Player.y_pos.val);
        } else if (row == 9) {
            assert(obj.x_pos.i.hi == 200 && obj.y_vel.val == 0x30000);
            assert(obj.y_pos.val == (166 << 16) - obj.y_vel.val);
        } else {
            s32 side = row == 6 ? -0x20 : 0x20;
            assert(obj.x_pos.val == ((200 + side) << 16) + obj.x_vel.val);
            assert(obj.y_pos.val == ((150 + side) << 16) - obj.y_vel.val);
        }
        assert(obj.ext.misc_34.enabled == (related.state >= 3));
        assert(obj.unk5 == (related.state >= 4 ? 3 : 2));
        return 1;
    }
    obj.x_pos.i.hi = row == 3 ? 0x300 : 100;
    obj.y_pos.i.hi = 100;
    obj.unk5 = steps[row];
    obj.unk6 = 1;
    set_animation(&obj, animations[row]);
    obj.ext.misc_34.timer = timers[row];
    obj.ext.misc_34.unk5A = row == 0 ? 2 : 1;
    if (row >= 4)
        obj.x_vel.val = 0x10000;
    cyberspace_guide_update(&obj);
    assert(obj.state == (row == 3 ? 2 : 1));
    switch (row) {
    case 0:
    case 2:
    case 4:
        assert(obj.ext.misc_34.timer == 1 && obj.unk5 == steps[row]);
        assert(obj.ext.misc_34.unk5A == 1 && obj.unk17 == animations[row]);
        assert(row != 4 || (obj.x_pos.i.hi == 101 && obj.unk6 == 1));
        break;
    case 1:
        assert(obj.unk5 == 1 && obj.ext.misc_34.timer == 0x24);
        assert(obj.unk17 == 3 && obj.ext.misc_34.unk5A == 0x24 && obj.ext.misc_34.enabled == 0);
        break;
    case 3:
        assert(obj.unk5 == 2 && obj.ext.misc_34.enabled == 1 && obj.unk17 == 1);
        assert(engine_obj.unk10 == 0 && engine_obj.unk11 == 0 && engine_obj.unk12 == 0 && engine_obj.unk13 == 0);
        assert(obj.ext.misc_34.unk58 == 1);
        break;
    default:
        assert(obj.unk6 == 2 && obj.ext.misc_34.timer == 0x1E && obj.x_vel.val == 0x30000);
        assert(obj.unk17 == 1 && obj.ext.misc_34.enabled == 1);
        break;
    }
    return 1;
}
