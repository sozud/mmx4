#include "test_runtime.h"
#include "main/weapons/weapon_03_soul_body.h"
extern s32 player_gfx_buf_0[1024];

static u32 cancel_case(u32 mode)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    u8 palette_before = need_palette_load;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 3;
    obj.unk2 = 7;
    obj.on_screen = 1;
    obj.state = mode ? 1 : 2;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.unk50 = (const u8*)soul_body_hit_box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.weapon = mode == 3 ? 0 : 3;
    g_Player.hp = mode == 5 ? 0 : 16;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.actions_reset = mode == 4;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    expected = obj;
    player_before = g_Player;
    expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
    expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    expected.unk50 = NULL;
    player_before.shot_count = 2;
    player_before.special_shot_count = 1;
    soul_body_update(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(need_palette_load == palette_before);
    return (u8)obj.state | ((u32)(u8)player_before.shot_count << 8) | ((u32)(u8)player_before.special_shot_count << 16);
}
#define CASE(m)                                                 \
    static u32 soul_body_cancellation_dispatch_cancel_##m(void) \
    {                                                           \
        return cancel_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) soul_body_cancellation_dispatch_cancel_##m,
static const CTestCase soul_body_cancellation_dispatch_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 soul_body_cancellation_dispatch_cases_expected[] = { 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u, 0x10200u };
#undef CASE
#undef ENTRY

static u32 clone_case(u32 mode, u32 observation)
{
    struct PlayerObj player_before, entity_before;
    struct EngineObj engine_before;
    struct BackgroundObj bg_before[3];
    u32 i, actual;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    g_Player.bg_offset = 0;
    g_Player.weapon = 3;
    g_Player.hp = 20;
    g_Player.controlling_clone = 1;
    g_Player.spike_immune = 1;
    g_Entity.active = 0x41;
    g_Entity.on_screen = 1;
    g_Entity.state = 3;
    g_Entity.unk5 = 0x25;
    g_Entity.clone_timer = 60;
    g_Entity.unk70 = 0x35;
    g_Entity.touching_spikes = 0x27;
    g_Entity.x_pos.val = 5 * 65536 + 0x1357;
    g_Entity.y_pos.val = 10 * 65536 + 0x2468;
    g_Entity.unk18.val = 0x24681357;
    g_Entity.unk1C.val = 0x13572468;
    g_Entity.previous_animation_index = 0x2A;
    g_Entity.animation_step.fields.frame_index = 0x2A;
    background_objects[0].x_pos.i.hi = 10;
    background_objects[0].y_pos.i.hi = 20;
    engine_obj.controlled_player = &g_Player;
    if (mode == 0) {
        g_Player.capsule_state = 1;
        g_Player.weapon = 0;
        g_Player.actions_reset = 1;
        g_Player.hp = 0;
        g_Entity.y_pos.i.hi = 348;
    }
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    soul_body_clone_update();
    player_before.controlling_clone = g_Player.controlling_clone;
    player_before.spike_immune = g_Player.spike_immune;
    entity_before.active = g_Entity.active;
    entity_before.on_screen = g_Entity.on_screen;
    entity_before.x_pos = g_Entity.x_pos;
    entity_before.y_pos = g_Entity.y_pos;
    entity_before.unk18 = g_Entity.unk18;
    entity_before.unk1C = g_Entity.unk1C;
    entity_before.unk70 = g_Entity.unk70;
    entity_before.touching_spikes = g_Entity.touching_spikes;
    engine_before.controlled_player = engine_obj.controlled_player;
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(g_Entity) / 4; i++)
        assert(((u32*)&g_Entity)[i] == ((u32*)&entity_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(engine_obj.controlled_player == &g_Player || engine_obj.controlled_player == &g_Entity);
    switch (observation) {
    case 0:
        actual = (u8)g_Entity.active | ((u32)g_Entity.on_screen << 8) | ((u32)(u8)g_Player.controlling_clone << 16) | ((u32)(u8)g_Player.spike_immune << 24);
        break;
    case 1:
        actual = g_Entity.x_pos.val;
        break;
    case 2:
        actual = g_Entity.y_pos.val;
        break;
    case 3:
        actual = g_Entity.unk18.val;
        break;
    case 4:
        actual = g_Entity.unk1C.val;
        break;
    default:
        actual = (u8)g_Entity.unk70 | ((u32)(u8)g_Entity.touching_spikes << 8) | ((u32)(engine_obj.controlled_player == &g_Entity) << 16);
        break;
    }
    return actual;
}
#define CLONE_CASE(m, n)                                \
    static u32 soul_clone_context_clone_##m##_##n(void) \
    {                                                   \
        return clone_case(m, n);                        \
    }
#define CLONE_MODE(m) CLONE_CASE(m, 0) CLONE_CASE(m, 1) CLONE_CASE(m, 2) CLONE_CASE(m, 3) CLONE_CASE(m, 4) CLONE_CASE(m, 5)
CLONE_MODE(0)
CLONE_MODE(1)
#define CLONE_ENTRY(m, n) soul_clone_context_clone_##m##_##n,
#define CLONE_ENTRIES(m) CLONE_ENTRY(m, 0) CLONE_ENTRY(m, 1) CLONE_ENTRY(m, 2) CLONE_ENTRY(m, 3) CLONE_ENTRY(m, 4) CLONE_ENTRY(m, 5)
static const CTestCase soul_clone_context_cases[]
    = { CLONE_ENTRIES(0) CLONE_ENTRIES(1) };
static const u32 soul_clone_context_cases_expected[] = { 0x0u, 0x51357u, 0x15C2468u, 0x24681357u, 0x13572468u, 0x2735u, 0x1010141u, 0xA1357u, 0x142468u, 0x51357u, 0xA2468u, 0x10000u };
#undef CLONE_CASE
#undef CLONE_MODE
#undef CLONE_ENTRY
#undef CLONE_ENTRIES

const struct CTestGroup c_test_groups[] = {
    { "soul_body_cancellation_dispatch", soul_body_cancellation_dispatch_cases, soul_body_cancellation_dispatch_cases_expected, COUNT(soul_body_cancellation_dispatch_cases), 0 },
    { "soul_clone_context", soul_clone_context_cases, soul_clone_context_cases_expected, COUNT(soul_clone_context_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(soul_body_cancellation_dispatch_cases) + COUNT(soul_clone_context_cases);
