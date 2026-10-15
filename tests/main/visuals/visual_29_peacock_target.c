#include "test_runtime.h"

static u32 track_case(u32 mode, u32 observation)
{
    struct VisualObj obj, before;
    struct PlayerObj player_before;
    u32 i, actual, cursor = ~0u;
    s16 dy[6] = { 18, 10, 6, 3, 1, 0 };
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.val = 100 * 65536 + 0x3210;
    g_Player.y_pos.val = 80 * 65536 + 0x4321;
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = 0x35;
    obj.unk54 = mode == 5 ? 1 : 60;
    obj.unk56 = 1;
    obj.x_pos.val = (mode == 4 ? 103 : 100) * 65536 + 0x1234;
    obj.y_pos.val = (80 + dy[mode]) * 65536 + 0x2345;
    obj.x_vel.val = 0x2468;
    obj.y_vel.val = -0x1234;
    obj.unk28 = 0x100;
    obj.unk2C = 0x200;
    obj.unk15 = 0x40;
    obj.unk17 = 10;
    obj.previous_animation_index = 0xA5;
    obj.animation_table = (u32**)cyber_peacock_animations;
    obj.animation_cursor = (u32*)cyber_peacock_animations[10];
    obj.animation_step.packed = *obj.animation_cursor;
    before = obj;
    player_before = g_Player;
    peacock_target_track(&obj);
    before.unk5 = obj.unk5;
    before.unk54 = obj.unk54;
    before.unk56 = obj.unk56;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.unk17 = obj.unk17;
    before.previous_animation_index = obj.previous_animation_index;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(obj.animation_table == (u32**)cyber_peacock_animations);
    assert(obj.unk17 == 10 || obj.unk17 == 11);
    for (i = 0; i < (obj.unk17 == 10 ? 2 : 4); i++)
        if (obj.animation_cursor == (u32*)cyber_peacock_animations[obj.unk17] + i)
            cursor = i;
    assert(cursor != ~0u);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = obj.x_vel.val;
        break;
    case 3:
        actual = obj.y_vel.val;
        break;
    case 4:
        actual = obj.unk54 | ((u32)obj.unk56 << 16);
        break;
    case 5:
        actual = ((u32*)&obj)[1];
        break;
    case 6:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = cursor | ((u32)obj.unk17 << 8) | ((u32)obj.previous_animation_index << 16);
        break;
    }
    return actual;
}
#define TRACK_CASE(m, n)                                      \
    static u32 peacock_tracking_context_track_##m##_##n(void) \
    {                                                         \
        return track_case(m, n);                              \
    }
#define TRACK_MODE(m) TRACK_CASE(m, 0) TRACK_CASE(m, 1) TRACK_CASE(m, 2) TRACK_CASE(m, 3) TRACK_CASE(m, 4) TRACK_CASE(m, 5) TRACK_CASE(m, 6) TRACK_CASE(m, 7)
TRACK_MODE(0)
TRACK_MODE(1)
TRACK_MODE(2)
TRACK_MODE(3)
TRACK_MODE(4)
TRACK_MODE(5)
#define TRACK_ENTRY(m, n) peacock_tracking_context_track_##m##_##n,
#define TRACK_ENTRIES(m) TRACK_ENTRY(m, 0) TRACK_ENTRY(m, 1) TRACK_ENTRY(m, 2) TRACK_ENTRY(m, 3) TRACK_ENTRY(m, 4) TRACK_ENTRY(m, 5) TRACK_ENTRY(m, 6) TRACK_ENTRY(m, 7)
static const CTestCase peacock_tracking_context_cases[]
    = { TRACK_ENTRIES(0) TRACK_ENTRIES(1) TRACK_ENTRIES(2) TRACK_ENTRIES(3) TRACK_ENTRIES(4) TRACK_ENTRIES(5) };
static const u32 peacock_tracking_context_cases_expected[] = { 0x641234u, 0x5E2345u, 0x100u, 0x3FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x572345u, 0x100u, 0x2FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x542345u, 0x100u, 0x1FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x522345u, 0x100u, 0xFE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x661234u, 0x512345u, 0xFFFF0100u, 0xFFFFFE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x502345u, 0x2468u, 0xFFFFEDCCu, 0x10000u, 0x350101u, 0x58010002u, 0xFF0B00u };
#undef TRACK_CASE
#undef TRACK_MODE
#undef TRACK_ENTRY
#undef TRACK_ENTRIES

struct peacock_target_fire_case {
    u32 previous, pool_0_full;
    u32 expected[10];
};
static const struct peacock_target_fire_case peacock_target_fire_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 257, 0, { 1u, 0u, 0x2Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 257, 255, { 1u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_peacock_target_fire(u32 row)
{
    const struct peacock_target_fire_case* c = &peacock_target_fire_cases[row];
    u32 observed_values[10];
    struct VisualObj obj;
    struct PlayerObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&shot_objects, 0, sizeof(shot_objects));
    child_0_present = 255;
    child_0.input.buttons.previous = c->previous;
    pool_0_full = c->pool_0_full;
    obj.unk50 = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    peacock_target_fire(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)shot_objects[0].active;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    observed_values[8] = (u32)shot_objects[0].x_pos.val;
    observed_values[9] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

struct peacock_target_track_case {
    u32 unk56, x_pos_hi, y_pos_hi, x_pos, y_pos;
    u32 expected[7];
};
static const struct peacock_target_track_case peacock_target_track_cases[] = {
    { 0, 0, 0, 0, 0, { 0u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, 0u, 0u } },
    { 1, -24061, 0, -777963, 13207, { 0u, 0xFFFFFFFFu, 1u, 0xA2070000u, 0x40000u, 0u, 0u } },
    { 1, -1, -16, -9477, -925696, { 0u, 0xFFFFFFFFu, 1u, 0x9000u, 0xB505u, 0xFFF29505u, 0xFFFF4AFBu } },
    { 1, -15, 0, 0, 13207, { 0u, 0xFFFFFFFFu, 1u, 0xFFF40000u, 0x30000u, 0u, 0u } },
    { 1, 0, 0, 458752, 13207, { 0u, 0xFFFFFFFFu, 1u, 0x20000u, 0x20000u, 0u, 0u } },
};
static u32 test_peacock_target_track(u32 row)
{
    const struct peacock_target_track_case* c = &peacock_target_track_cases[row];
    u32 observed_values[7];
    struct VisualObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk56 = c->unk56;
    obj.x_pos.i.hi = c->x_pos_hi;
    obj.y_pos.i.hi = c->y_pos_hi;
    g_Player.x_pos.val = c->x_pos;
    g_Player.y_pos.val = c->y_pos;
    peacock_target_track(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk54;
    observed_values[2] = (u32)obj.unk56;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.x_vel.val;
    observed_values[5] = (u32)obj.y_pos.val;
    observed_values[6] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

const struct CTestGroup c_test_groups[] = {
    { "peacock_tracking_context", peacock_tracking_context_cases, peacock_tracking_context_cases_expected, COUNT(peacock_tracking_context_cases), 0 },
    { "peacock_target_fire", 0, 0, 3, test_peacock_target_fire },
    { "peacock_target_track", 0, 0, 5, test_peacock_target_track },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(peacock_tracking_context_cases) + 3 + 5;
