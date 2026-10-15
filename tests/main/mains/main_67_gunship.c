#include "test_runtime.h"

static u32 wait_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 script_before, i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 67;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0x27;
    obj.unk72 = 8;
    obj.ext.main_67.unk8D = 1;
    obj.unk7C = mode ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.animation_table = (u32**)gunship_animations;
    obj.animation_cursor = gunship_animations[1];
    obj.animation_step.packed = *(u32*)gunship_animations[1];
    g_Player.x_pos.i.hi = mode ? -93 : 100;
    g_Player.y_pos.i.hi = 51;
    before = obj;
    player_before = g_Player;
    script_before = *(u32*)gunship_animations[1];
    func_800828B4(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7C = obj.unk7C;
    before.ext.main_67.unk8D = obj.ext.main_67.unk8D;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(obj.animation_table == (u32**)gunship_animations && obj.animation_cursor == gunship_animations[1]);
    assert(*(u32*)gunship_animations[1] == script_before);
    if (observation == 0)
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.ext.main_67.unk8D << 16);
    else if (observation == 1)
        actual = (u16)obj.unk7C;
    else
        actual = obj.animation_step.packed;
    return actual;
}
#define WAIT_CASE(m, n)                                  \
    static u32 gunship_wait_context_wait_##m##_##n(void) \
    {                                                    \
        return wait_case(m, n);                          \
    }
#define WAIT_MODE(m) WAIT_CASE(m, 0) WAIT_CASE(m, 1) WAIT_CASE(m, 2)
WAIT_MODE(0)
WAIT_MODE(1)
#define WAIT_ENTRY(m, n) gunship_wait_context_wait_##m##_##n,
#define WAIT_ENTRIES(m) WAIT_ENTRY(m, 0) WAIT_ENTRY(m, 1) WAIT_ENTRY(m, 2)
static const CTestCase gunship_wait_context_cases[]
    = { WAIT_ENTRIES(0) WAIT_ENTRIES(1) };
static const u32 gunship_wait_context_cases_expected[] = { 0x4u, 0x0u, 0x10001u, 0x12702u, 0x1u, 0x10001u };
#undef WAIT_CASE
#undef WAIT_MODE
#undef WAIT_ENTRY
#undef WAIT_ENTRIES

struct func_800828B4_case {
    u32 g_Player_x_pos_hi, obj_x_pos_hi, unk7C, unk8D;
    u32 expected[4];
};
static const struct func_800828B4_case func_800828B4_cases[] = {
    { 194, 0, 0, 255, { 0xFFu, 0u, 0u, 0xFFFFFFFFu } },
    { 194, 0, 1, 0, { 0u, 4u, 0u, 0u } },
    { 0, 0, 0, 255, { 1u, 4u, 0u, 0xFFFFFFFFu } },
    { -28704, -28528, 0, 255, { 1u, 4u, 0u, 0xFFFFFFFFu } },
    { 0, 0, 1, 0, { 0u, 3u, 0u, 0u } },
};
static u32 test_func_800828B4(u32 row)
{
    const struct func_800828B4_case* c = &func_800828B4_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    obj.unk7C = c->unk7C;
    obj.unk72 = 8;
    obj.ext.main_67.unk8D = c->unk8D;
    func_800828B4(&obj);
    observed_values[0] = (u32)obj.ext.main_67.unk8D;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct gunship_is_within_case {
    u32 x_pos, y_pos, arg1, arg2;
    u32 expected[1];
};
static const struct gunship_is_within_case gunship_is_within_cases[] = {
    { 196608, 0, -65528, 0, { 0u } },
    { 0, -1048576, 0, -524287, { 0u } },
    { 0, -790679, 0, -781643, { 1u } },
};
static u32 test_gunship_is_within(u32 row)
{
    const struct gunship_is_within_case* c = &gunship_is_within_cases[row];
    u32 observed_values[1];
    struct MainObj obj;
    s32 arg1;
    s32 arg2;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.val = c->x_pos;
    obj.y_pos.val = c->y_pos;
    arg1 = c->arg1;
    arg2 = c->arg2;
    observed_values[0] = (u32)gunship_is_within(&obj, arg1, arg2);
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

#include "support/pool_full.h"
static u32 pool_full_gunship_spawn_bullet(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_bullet(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_gunship_spawn_missiles(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_missiles(VISUAL_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_gunship_spawn_exhaust(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_exhaust(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_gunship_spawn_bullet,
    pool_full_gunship_spawn_missiles,
    pool_full_gunship_spawn_exhaust,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "gunship_wait_context", gunship_wait_context_cases, gunship_wait_context_cases_expected, COUNT(gunship_wait_context_cases), 0 },
    { "func_800828B4", 0, 0, 5, test_func_800828B4 },
    { "gunship_is_within", 0, 0, 3, test_gunship_is_within },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunship_wait_context_cases) + 5 + 3 + COUNT(pool_full_cases);
