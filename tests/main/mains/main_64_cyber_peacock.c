#include "test_runtime.h"

static u32 peacock_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct EffectObj child, child_before, pool_before[32];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 resources[1] = { 0x10000 }, i;
    s32 archive[128];
    memset(&obj, 0, sizeof(obj));
    memset(&child, 0, sizeof(child));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(archive, 0, sizeof(archive));
    archive[4] = 64;
    D_801406A8 = resources;
    TEST_MENU_FRAMES = (u8*)archive;
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = 64;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk7 = 0x25;
    obj.unk6 = mode == 6 ? -1 : mode == 7 ? 3
        : mode < 2                        ? 0
        : mode < 4                        ? 1
                                          : 2;
    obj.unk7C = mode == 4 ? 1 : 2;
    obj.ext.main_64.object = &child;
    child.id = 0x18;
    obj.hp = 0x27;
    obj.contact_damage = 0x26;
    obj.invincibility_timer = 0x25;
    obj.bg_offset = 0;
    obj.unk40 = 0x7777;
    obj.unk42 = 0x6666;
    obj.unk16 = 0x24;
    obj.unk62 = 0x23;
    obj.unk63 = 0x22;
    g_Player.capsule_state = mode == 0 ? 1 : 0;
    g_Player.bg_offset = 2;
    g_Player.script_state = -1;
    g_Player.script_action = 0x25;
    g_Player.script_facing = 0x26;
    engine_obj.stage = mode == 3 ? 12 : 6;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 7;
    before = obj;
    child_before = child;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    cyber_peacock_intro_wait_player(&obj);
    if (mode == 1) {
        before.unk6 = 1;
        before.unk7 = 0;
        player_before.script_state = 1;
        player_before.script_action = 0x14;
        player_before.script_facing = 0x40;
        player_before.spike_immune = 1;
        engine_before.gameplay_locked = 1;
    } else if (mode == 2 || mode == 3) {
        before.unk6 = 2;
        before.bg_offset = 2;
        before.unk40 = (0x10000 >> 7) + (mode == 3 ? 0x160 : 0xB0);
        if (mode == 3) {
            before.sprite_frames = (u8*)archive + 64;
            before.unk42 = 0x7888;
        }
        before.animation_table = (const u8* const*)cyber_peacock_animations;
        before.unk16 = 4;
        before.hp = 0;
        before.contact_damage = 5;
        before.invincibility_timer = -0x80;
        before.unk62 = 0;
        before.unk63 = 2;
        before.unk7C = 0x20;
        engine_before.enable_boss = 0;
        engine_before.unk25 = 0;
        engine_before.boss_ptr = &obj;
    } else if (mode == 4 || mode == 5) {
        before.unk7C = mode == 4 ? 0 : 1;
        if (mode == 4) {
            before.unk5 = 2;
            before.unk6 = 0;
            before.unk7 = 0;
        }
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(child) / 4; i++)
        assert(((u32*)&child)[i] == ((u32*)&child_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(resources[0] == 0x10000);
    for (i = 0; i < 128; i++)
        assert(archive[i] == (i == 4 ? 64 : 0));
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.unk7C << 16) : (u16)obj.unk40 | ((u32)(u16)obj.unk42 << 16);
}
#define CASE(m, n)                     \
    static u32 peacock_##m##_##n(void) \
    {                                  \
        return peacock_case(m, n);     \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
MODE(7)
#define ENTRY(m, n) peacock_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase cyber_peacock_intro_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) };
static const u32 cyber_peacock_intro_context_cases_expected[] = { 0x20001u, 0x66667777u, 0x20101u, 0x66667777u, 0x200201u, 0x666602B0u, 0x200201u, 0x78880360u, 0x2u, 0x66667777u, 0x10201u, 0x66667777u, 0x2FF01u, 0x66667777u, 0x20301u, 0x66667777u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

#include "support/pool_full.h"
static u32 pool_full_cyber_peacock_spawn_laser_target(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    cyber_peacock_spawn_laser_target(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_cyber_peacock_spawn_missile(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    cyber_peacock_spawn_missile(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_cyber_peacock_death_explode(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    cyber_peacock_death_explode(&pf_self);
    pf_expected.unk5 = 2;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_cyber_peacock_spawn_laser_target,
    pool_full_cyber_peacock_spawn_missile,
    pool_full_cyber_peacock_death_explode,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x2u };
const struct CTestGroup c_test_groups[] = {
    { "cyber_peacock_intro_context", cyber_peacock_intro_context_cases, cyber_peacock_intro_context_cases_expected, COUNT(cyber_peacock_intro_context_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cyber_peacock_intro_context_cases) + COUNT(pool_full_cases);
