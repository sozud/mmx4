#include "test_runtime.h"
#include "main/quads/quad_10_aiming_laser_charged_beam.h"

static u32 cancel_case(u32 mode)
{
    struct QuadObj obj;
    struct WeaponObj owner, before_owner;
    struct PlayerObj before_player;
    u8* history;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.weapon = mode == 3 ? 0 : 6;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.hp = mode == 4 ? 0 : 16;
    g_Player.actions_reset = mode == 5;
    obj.active = 0x93;
    obj.id = 0xA;
    obj.state = 3;
    obj.unk2 = 3;
    obj.on_screen = 1;
    obj.unk5C = PLAYER_OBJECT(&owner);
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x2468;
    obj.ext.quad_10.progress = 120;
    history = (u8*)&obj + ((u8*)obj.ext.quad_10.history - (u8*)&obj);
    assert(history + 16 <= (u8*)&obj + sizeof(obj));
    for (i = 0; i < 16; i++)
        history[i] = i;
    owner.ext.weapon_6.adjusted_direction = 13;
    before_owner = owner;
    before_player = g_Player;
    aiming_laser_charged_beam_update(&obj);
    assert(obj.id == 0 && obj.unk2 == 0);
    assert(obj.x_pos.val == 100 * 65536 + 0x1234);
    assert(obj.y_pos.val == 200 * 65536 + 0x2468);
    assert(obj.unk5C == PLAYER_OBJECT(&owner));
    assert(obj.ext.quad_10.progress == 120 && obj.ext.quad_10.counter == 0);
    for (i = 0; i < 4; i++)
        assert(obj.vertices[i].x.val == 0 && obj.vertices[i].y.val == 0);
    assert(history[0] == (mode == 0 ? 5 : 0));
    for (i = 1; i < 16; i++)
        assert(history[i] == (mode == 0 ? i - 1 : i));
    for (i = 0; i < sizeof(owner); i++)
        assert(((u8*)&owner)[i] == ((u8*)&before_owner)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&before_player)[i]);
    actual = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.on_screen << 16);
    return actual;
}
#define MODE(mode)                                           \
    static u32 charged_beam_cancellation_cancel_##mode(void) \
    {                                                        \
        return cancel_case(mode);                            \
    }
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
#define ENTRY(mode) charged_beam_cancellation_cancel_##mode,
static const CTestCase charged_beam_cancellation_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 charged_beam_cancellation_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u };
#undef MODE
#undef ENTRY

static u32 beam_case(u32 mode, u32 observation)
{
    struct {
        u32 before;
        struct QuadObj obj;
        u32 after;
    } storage;
    struct QuadObj* obj = &storage.obj;
    struct PlayerObj player, before_player;
    struct WeaponObj owner, before_owner;
    u8* history;
    u8 initial_history[16];
    u32 i;

    memset(&storage, 0, sizeof(storage));
    memset(&player, 0, sizeof(player));
    memset(&owner, 0, sizeof(owner));
    storage.before = 0x12345678;
    storage.after = 0x9ABCDEF0;
    obj->active = 0x93;
    obj->id = 0xA;
    obj->state = mode == 0 ? 2 : 3;
    obj->unk2 = mode == 2 ? 0 : 3;
    obj->on_screen = 1;
    obj->bg_offset = -1;
    obj->unk5C = PLAYER_OBJECT(&owner);
    obj->x_pos.val = 100 * 65536 + 0x1234;
    obj->y_pos.val = 200 * 65536 + 0x2468;
    obj->ext.quad_10.counter = mode == 0 ? 30 : mode == 1 ? 0
                                                          : 1;
    obj->ext.quad_10.progress = 120;
    obj->ext.quad_10.x_step = 123;
    obj->ext.quad_10.y_step = -456;
    history = (u8*)obj + ((u8*)obj->ext.quad_10.history - (u8*)obj);
    assert(history + 16 <= (u8*)obj + sizeof(*obj));
    for (i = 0; i < 16; i++)
        history[i] = initial_history[i] = (i * 3 + 1) & 31;
    for (i = 0; i < 4; i++) {
        obj->vertices[i].x.val = (100 + i) * 65536 + 0x1357;
        obj->vertices[i].y.val = (200 + i) * 65536 + 0x2468;
    }
    player.unk15 = mode == 0 ? 0 : 0x40;
    player.animation_step.fields.frame_index = 4;
    player.x_pos.val = 300 * 65536 + 0x5678;
    player.y_pos.val = 400 * 65536 + 0x6789;
    owner.ext.weapon_6.adjusted_direction = 13;
    before_player = player;
    before_owner = owner;
    if (mode == 0)
        aiming_laser_charged_beam_sweep(obj, &player, PLAYER_OBJECT(&owner));
    else
        aiming_laser_charged_beam_retract(obj, &player, PLAYER_OBJECT(&owner));

    assert(storage.before == 0x12345678 && storage.after == 0x9ABCDEF0);
    assert(obj->id == (mode == 1 ? 0 : 0xA));
    assert(obj->bg_offset == -1 && obj->unk5C == PLAYER_OBJECT(&owner));
    assert(history[0] == 5);
    for (i = 1; i < 16; i++)
        assert(history[i] == initial_history[i - 1]);
    for (i = 0; i < sizeof(player); i++)
        assert(((u8*)&player)[i] == ((u8*)&before_player)[i]);
    for (i = 0; i < sizeof(owner); i++)
        assert(((u8*)&owner)[i] == ((u8*)&before_owner)[i]);
    assert(obj->vertices[0].x.val == (mode == 1 ? 100 * 65536 + 0x1357 : 0));
    assert(obj->vertices[0].y.val == (mode == 1 ? 200 * 65536 + 0x2468 : 0));
    if (observation == 0)
        return (u8)obj->active | ((u32)(u8)obj->state << 8) | ((u32)(u8)obj->unk2 << 16) | ((u32)(u8)obj->on_screen << 24);
    if (observation == 1)
        return (u32)obj->ext.quad_10.counter;
    if (observation == 2)
        return obj->ext.quad_10.progress;
    if (observation == 3)
        return (u32)obj->x_pos.val;
    if (observation == 4)
        return (u32)obj->y_pos.val;
    if (observation == 5)
        return (u32)obj->ext.quad_10.x_step;
    if (observation == 6)
        return (u32)obj->ext.quad_10.y_step;
    i = 1 + (observation - 7) / 2;
    return (u32)((observation & 1) ? obj->vertices[i].x.val : obj->vertices[i].y.val);
}
#define OBSERVE(mode, field)                                  \
    static u32 charged_beam_edges_beam_##mode##_##field(void) \
    {                                                         \
        return beam_case(mode, field);                        \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) OBSERVE(mode, 3) \
    OBSERVE(mode, 4) OBSERVE(mode, 5) OBSERVE(mode, 6) OBSERVE(mode, 7)                \
        OBSERVE(mode, 8) OBSERVE(mode, 9) OBSERVE(mode, 10) OBSERVE(mode, 11) OBSERVE(mode, 12)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(mode, field) charged_beam_edges_beam_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) ENTRY(mode, 3) \
    ENTRY(mode, 4) ENTRY(mode, 5) ENTRY(mode, 6) ENTRY(mode, 7) ENTRY(mode, 8)    \
        ENTRY(mode, 9) ENTRY(mode, 10) ENTRY(mode, 11) ENTRY(mode, 12)
static const CTestCase charged_beam_edges_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 charged_beam_edges_cases_expected[] = { 0x1030393u, 0x1Eu, 0x78u, 0x1121234u, 0x1862468u, 0x61F7u, 0xEC83u, 0x54DA58u, 0x54DA58u, 0x495564u, 0x6DC0ECu, 0x2DEBC8u, 0x6EDD68u, 0x0u, 0x0u, 0x78u, 0x641234u, 0xC82468u, 0x7Bu, 0xFFFFFE38u, 0x651357u, 0xC92468u, 0x661357u, 0xCA2468u, 0x671357u, 0xCB2468u, 0x1000393u, 0x0u, 0x74u, 0x1461234u, 0x1862468u, 0x61F7u, 0xFFFF137Du, 0x0u, 0xFF8C0000u, 0x18F880u, 0xFF827600u, 0x2C63ECu, 0xFF94D4A4u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

const struct CTestGroup c_test_groups[] = {
    { "charged_beam_cancellation", charged_beam_cancellation_cases, charged_beam_cancellation_cases_expected, COUNT(charged_beam_cancellation_cases), 0 },
    { "charged_beam_edges", charged_beam_edges_cases, charged_beam_edges_cases_expected, COUNT(charged_beam_edges_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(charged_beam_cancellation_cases) + COUNT(charged_beam_edges_cases);
