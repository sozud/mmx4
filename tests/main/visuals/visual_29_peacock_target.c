#include "test_runtime.h"
#include "main/visuals/visual_29_peacock_target.h"
#include "main/mains/main_64_cyber_peacock.h"
#include "main/55C4.h"

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
static const u32 peacock_tracking_context_cases_expected[] = { 0x641234u, 0x5E2345u, 0x100u, 0x3FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x572345u, 0x100u, 0x2FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x542345u, 0x100u, 0x1FE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x522345u, 0x100u, 0xFE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x661234u, 0x512345u, 0xFFFF0100u, 0xFFFFFE00u, 0x1003Bu, 0x350001u, 0x59FF0001u, 0xA50A01u, 0x641234u, 0x502345u, 0x2468u, 0xFFFFEDCCu, 0x10000u, 0x350101u, 0x58010002u, 0xFF0B00u };
static u32 peacock_tracking_context_cases_row(u32 row)
{
    return track_case(row / 8, row % 8);
}

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
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&shot_objects, 0, sizeof(shot_objects));
    child_0.input.buttons.previous = c->previous;
    pool_0_full = c->pool_0_full;
    obj.unk50 = &child_0;
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

void peacock_target_main(struct VisualObj*);
static const s16 positions[5][2] = { { 160, 120 }, { -32, 120 }, { 352, 120 }, { 160, -32 }, { 160, 272 } };
static const u32 hold_words[] = { 0x58010001, 0x59FF0001 };
static u32 target_lifecycle(u32 row)
{
    struct VisualObj obj, expected;
    struct WeaponObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 edge = row % 5, state = row / 5 % 3, frame = row / 15;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 8;
    owner.state = state;
    owner.x_pos.val = 0x24681357;
    owner.y_pos.val = 0x13572468;
    owner_before = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 7;
    obj.on_screen = 7;
    obj.bg_offset = -1;
    obj.unk50 = &owner;
    obj.x_pos.val = positions[edge][0] * 65536 + 0x1234;
    obj.y_pos.val = positions[edge][1] * 65536 + 0x5678;
    obj.animation_table = (u32**)cyber_peacock_animations;
    set_animation_frame(ANIMATED_OBJECT(&obj), 10, frame);
    assert(obj.animation_step.packed == hold_words[frame]);
    obj.previous_animation_index = 0x35;
    expected = obj;
    if (state != 1)
        memset(&expected, 0, 8);
    else {
        expected.animation_cursor = (u32*)cyber_peacock_animations[10] + (frame ^ 1);
        expected.animation_step.packed = hold_words[frame ^ 1];
        expected.on_screen = edge == 0 || edge == 1 || edge == 3;
    }
    peacock_target_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "peacock_tracking_context", NULL, peacock_tracking_context_cases_expected, COUNT(peacock_tracking_context_cases_expected), peacock_tracking_context_cases_row },
    { "peacock_target_fire", 0, 0, 3, test_peacock_target_fire },
    { "peacock_target_track", 0, 0, 5, test_peacock_target_track },
    { "target_owner_lifecycle", NULL, NULL, 30, target_lifecycle },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(peacock_tracking_context_cases_expected) + 3 + 5 + 30;
