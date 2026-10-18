#include "test_runtime.h"
#include "main/mains/main_12_hover_sentry.h"
#include "main/mains/main_23_slope_skier.h"
#include "main/55C4.h"
extern union AnimationStep* hover_sentry_animations[];
extern struct Unk_unk68 D_800FB684;
extern struct Unk_unk68 D_800FB688;
extern struct Unk_unk68 D_800FB68C;
extern struct Unk_unk68 D_800FB690;

static const s16 distances[4] = { 31, 32, -31, -32 };
static u32 height_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 12;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.unk7 = 7;
    obj.unk15 = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_accel = 0x2000;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)hover_sentry_animations;
    set_animation(&obj, 0);
    g_Player.x_pos.val = 101 * 65536 + 0x1234;
    g_Player.y_pos.i.hi = 200 - distances[mode];
    player_before = g_Player;
    cur_random = 1;
    expected = obj;
    expected.unk6 = 0;
    expected.unk15 = mode & 1 ? 0 : 0x40;
    expected.x_speed = mode & 1 ? -0x2000 : 0x2000;
    expected.y_speed = -0x1000;
    expected.animation_step.fields.duration = 9;
    func_8004C394(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 1 && hover_sentry_animations[0][0].packed == 0x0001000A);
    actual = (u8)obj.unk6 | ((u32)obj.unk15 << 8) | ((u32)(u16)(obj.x_speed / 0x2000) << 16);
    return actual;
}
#define CASE(m)                                            \
    static u32 hover_sentry_player_height_height_##m(void) \
    {                                                      \
        return height_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) hover_sentry_player_height_height_##m,
static const CTestCase hover_sentry_player_height_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 hover_sentry_player_height_cases_expected[] = { 0x14000u, 0xFFFF0000u, 0x14000u, 0xFFFF0000u };
#undef CASE
#undef ENTRY

static const u32 func_8004B8FC_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x40u, 0u, 0u, 0u, 0u, 0u, 0x90u, 0u, 0u, 0u, 0u };
static u32 test_func_8004B8FC(u32 row)
{
    u32 observed_values[22];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800FB684, 0, sizeof(D_800FB684));
    memset(&D_800FB688, 0, sizeof(D_800FB688));
    memset(&D_800FB68C, 0, sizeof(D_800FB68C));
    memset(&D_800FB690, 0, sizeof(D_800FB690));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = -1;
    func_8004B8FC(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.contact_damage;
    observed_values[3] = (u32)obj.ext.main_12.unk81;
    observed_values[4] = (u32)obj.ext.main_12.unk86;
    observed_values[5] = (u32)obj.ext.main_12.unk88;
    observed_values[6] = (u32)obj.ext.main_12.unk8A;
    observed_values[7] = (u32)obj.gravity;
    observed_values[8] = (u32)obj.hp;
    observed_values[9] = (u32)obj.invincibility_timer;
    observed_values[10] = (u32)obj.state;
    observed_values[11] = (u32)obj.unk15;
    observed_values[12] = (u32)obj.unk16;
    observed_values[13] = (u32)obj.unk18.val;
    observed_values[14] = (u32)obj.unk1C.val;
    observed_values[15] = (u32)obj.unk5;
    observed_values[16] = (u32)obj.unk6;
    observed_values[17] = (u32)obj.unk7C;
    observed_values[18] = (u32)obj.unk7E;
    observed_values[19] = (u32)obj.x_accel;
    observed_values[20] = (u32)obj.x_speed;
    observed_values[21] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_8004B8FC_expected, 22);
}

static const u32 func_8004C394_expected[] = { 1u, 0u, 0x40u, 4u, 0u, 0u, 0u, 1u, 0u, 0xFFFFFFFFu, 0u };
static u32 test_func_8004C394(u32 row)
{
    u32 observed_values[11];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_800FB684, 0, sizeof(D_800FB684));
    memset(&D_800FB688, 0, sizeof(D_800FB688));
    memset(&D_800FB68C, 0, sizeof(D_800FB68C));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.unk6 = -1;
    obj.unk15 = 64;
    obj.x_speed = -1;
    g_Player.y_pos.i.hi = 65;
    obj.x_pos.val = -1;
    child_0_present = 255;
    obj.collision_flags = 2;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    func_8004C394(&obj);
    observed_values[0] = (u32)child_0.ext.main_12.unk81;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk7;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.unk7E;
    observed_values[8] = (u32)obj.x_accel;
    observed_values[9] = (u32)obj.x_speed;
    observed_values[10] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_8004C394_expected, 11);
}

#include "support/pool_full.h"
static u32 pool_full_hover_sentry_idle(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk6 = 4;
    pf_snapshot();
    func_8004C210(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_hover_sentry_idle,
};
static const u32 pool_full_cases_expected[] = { 0x50400u };

#include "support/signed_init_defaults.h"
DEFAULTS_CASE(0, 0)
DEFAULTS_CASE(1, 0)
DEFAULTS_CASE(2, 0)
static const CTestCase hover_sentry_signed_init_defaults_cases[] = { DEFAULTS_ENTRY(0, 0) DEFAULTS_ENTRY(1, 0) DEFAULTS_ENTRY(2, 0) };

static const u32 hover_sentry_signed_init_defaults_cases_expected[] = { 0x9080001u, 0x9080001u, 0x9080001u };
const struct CTestGroup c_test_groups[] = {
    { "hover_sentry_player_height", hover_sentry_player_height_cases, hover_sentry_player_height_cases_expected, COUNT(hover_sentry_player_height_cases), 0 },
    { "func_8004B8FC", 0, 0, 1, test_func_8004B8FC },
    { "func_8004C394", 0, 0, 1, test_func_8004C394 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "hover_sentry_signed_init_defaults", hover_sentry_signed_init_defaults_cases, hover_sentry_signed_init_defaults_cases_expected, COUNT(hover_sentry_signed_init_defaults_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hover_sentry_player_height_cases) + 1 + 1 + COUNT(pool_full_cases) + COUNT(hover_sentry_signed_init_defaults_cases);
