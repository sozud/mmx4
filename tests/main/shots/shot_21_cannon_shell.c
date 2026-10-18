#include "test_runtime.h"
#include "main/shots/shot_21_cannon_shell.h"
#include "main/collision_bounds.h"
#include "main/mains/main_38_train_cannon.h"
#include "main/55C4.h"
extern u8 cannon_shell_hit_box[4], cannon_shell_flat_hit_box[4], cannon_shell_steep_hit_box[4];
extern u8 cannon_shell_terrain_box[4], cannon_shell_flat_terrain_box[4], cannon_shell_steep_terrain_box[4];

static u32 cannon_shell_animation_shell_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    const u8* terrain;
    const u8* hit;
    u32 i, actual, original_step, next_animation;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 1;
    obj.animation_table = (u32**)train_cannon_animations;
    obj.animation_cursor = (u8*)train_cannon_animations[7];
    obj.animation_step.packed = *(u32*)train_cannon_animations[7];
    obj.unk17 = 7;
    obj.previous_animation_index = 0x27;
    obj.unk84.value = mode == 3 ? -1 : mode;
    obj.x_vel.val = mode == 0 ? 4 * 65536 : mode == 1 ? 2 * 65536
                                                      : 65536;
    obj.y_vel.val = mode == 2 ? 4 * 65536 : 65536;
    obj.unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    obj.unk54 = obj.unk50.data = cannon_shell_hit_box;
    before = obj;
    original_step = *(u32*)train_cannon_animations[7];
    func_8009D588(&obj);
    if (mode == 3) {
        for (i = 0; i < sizeof(obj); i++)
            assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
        actual = observation == 0 ? (u32)obj.unk84.value : obj.animation_step.packed;
    } else {
        terrain = mode == 0 ? cannon_shell_flat_terrain_box : mode == 1 ? cannon_shell_terrain_box
                                                                        : cannon_shell_steep_terrain_box;
        hit = mode == 0 ? cannon_shell_flat_hit_box : mode == 1 ? cannon_shell_hit_box
                                                                : cannon_shell_steep_hit_box;
        next_animation = mode + 8;
        assert(obj.unk68 == (struct Unk_unk68*)terrain && obj.unk54 == hit && obj.unk50.data == hit);
        assert(obj.animation_cursor == (u8*)train_cannon_animations[next_animation]);
        before.unk84.value = obj.unk84.value;
        before.unk68 = (struct Unk_unk68*)terrain;
        before.unk54 = before.unk50.data = hit;
        before.animation_cursor = (u8*)train_cannon_animations[next_animation];
        before.animation_step = obj.animation_step;
        before.unk17 = next_animation;
        before.previous_animation_index = 0xFF;
        for (i = 0; i < sizeof(obj); i++)
            assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
        actual = observation == 0 ? (u32)obj.unk84.value : obj.animation_step.packed;
    }
    assert(*(u32*)train_cannon_animations[7] == original_step);
    return actual;
}
static const u32 cannon_shell_animation_cases_expected[] = { 0x1u, 0x29000001u, 0x2u, 0x2A000001u, 0x3u, 0x2B000001u, 0xFFFFFFFFu, 0x28000001u };
static u32 cannon_shell_animation_cases_row(u32 row)
{
    return cannon_shell_animation_shell_case(row / 2, row % 2);
}

static u32 cannon_shell_distance_animation_start_shell_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_expected;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 38;
    owner.state = 1;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 0;
    obj.unk2 = mode == 4 ? 3 : mode & 1;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 50 * 65536 + 0xBEEF;
    obj.y_pos.val = 60 * 65536 + 0xCAFE;
    obj.unk7C = &owner;
    obj.animation_table = (u32**)train_cannon_animations;
    obj.unk28 = 123;
    obj.unk2C = 456;
    obj.unk70 = 7;
    obj.unk84.value = 9;
    expected = obj;
    owner_before = owner;
    expected.x_pos.i.hi = mode == 0 || mode == 2 ? 118 : 110;
    expected.y_pos.i.hi = mode == 0 || mode == 2 ? 200 : 184;
    g_Player.x_pos.val = expected.x_pos.val + (mode == 4 ? -192 * 65536 : mode == 0 ? -16 * 65536
                                 : mode == 1                                        ? 16 * 65536
                                 : mode == 2                                        ? -160 * 65536
                                                                                    : 160 * 65536);
    player_expected = g_Player;
    expected.unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    expected.unk58.animation_steps = D_80105FF0;
    expected.unk60 = 3;
    expected.on_screen = 1;
    expected.unk5C = 1;
    expected.unk54 = cannon_shell_hit_box;
    expected.state = 1;
    expected.unk42 = 0x123;
    expected.unk50.data = mode == 0 || mode == 2 ? cannon_shell_hit_box : cannon_shell_flat_hit_box;
    expected.x_vel.val = -0x28000;
    expected.y_vel.val = 0x28000;
    expected.unk28 = 0;
    expected.unk84.value = 0;
    expected.unk70 = 0;
    expected.unk7 = 1;
    expected.unk2C = mode < 2 ? 0x28000 / 9 : mode == 2 ? 0x28000 / 32
        : mode == 3                                     ? 0x28000 / 19
                                                        : 0x28000;
    expected.unk17 = 7;
    expected.previous_animation_index = 0xFF;
    ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)train_cannon_animations[7];
    expected.animation_step.packed = *(u32*)train_cannon_animations[7];
    func_8009D23C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    return (u32)obj.unk2C;
}
static const u32 cannon_shell_distance_animation_start_cases_expected[] = { 0x471Cu, 0x471Cu, 0x1400u, 0x21AFu, 0x28000u };

struct func_8009D588_case {
    u32 value, y_vel, x_vel;
    u32 expected[1];
};
static const struct func_8009D588_case func_8009D588_cases[] = {
    { 1, 22024, 541486, { 1u } },
    { 0, 0, 0, { 0u } },
    { 2, 0, 0, { 2u } },
    { 0, -744641, -260177, { 0u } },
};
static u32 test_func_8009D588(u32 row)
{
    const struct func_8009D588_case* c = &func_8009D588_cases[row];
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk84.value = c->value;
    obj.y_vel.val = c->y_vel;
    obj.x_vel.val = c->x_vel;
    func_8009D588(&obj);
    observed_values[0] = (u32)obj.unk84.value;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

void cannon_shell_fly(struct ShotObj*);
extern u8 cannon_shell_hit_box[4], cannon_shell_terrain_box[4];
static const struct {
    s16 x, y;
    u8 bottom, far;
} positions[] = {
    { 160, 223, 0, 0 },
    { 160, 224, 1, 0 },
    { -289, 120, 0, 1 },
    { -288, 120, 0, 0 },
    { 607, 120, 0, 0 },
    { 608, 120, 0, 1 },
};
static struct MiscObj misc_expected[64];
static struct VisualObj visuals_before[32];
static struct WeaponObj weapons_before[16];
static u32 viewport(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 position = row % COUNT(positions), full = row / COUNT(positions) % 2, timer = row / COUNT(positions) / 2 % 2, facing = row / COUNT(positions) / 4, i;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = full || i != 63;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
    }
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk7 = timer;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x1234;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.x_pos.val = (positions[position].x - 1) * 65536 + 0x1234;
    obj.y_pos.val = (positions[position].y + 1) * 65536 + 0x5678;
    obj.x_vel.val = obj.y_vel.val = 65536;
    obj.unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    obj.unk50.data = obj.unk54 = cannon_shell_hit_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.animation_table = (u32**)train_cannon_animations;
    set_animation(&obj, 7);
    assert(obj.animation_step.packed == 0x28000001);
    expected = obj;
    expected.x_pos.val += 65536;
    expected.y_pos.val -= 65536;
    if (positions[position].bottom) {
        expected.unk70 = 1;
        expected.state = 2;
    } else {
        expected.unk7 = !timer;
        if (!timer && !full) {
            struct MiscObj* m = &misc_expected[63];
            m->active = 0x21;
            m->id = 23;
            m->unk2 = 0;
            m->unk15 = 0x40;
            m->ext.unk.unk54 = 0;
            m->x_pos.i.hi = positions[position].x;
            m->y_pos.i.hi = positions[position].y;
            m->x_vel.val = m->y_vel.val = 0;
            m->unk7 = 1;
            m->unk16 = 7;
        }
        if (positions[position].far)
            expected.state = 2;
        else
            expected.on_screen = position == 0;
    }
    D_8013E198[1] = -1;
    cur_random = 0x1234;
    cannon_shell_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    assert(cur_random == (positions[position].bottom || (!timer && !full) ? 0x366A : 0x1234));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_shell_animation", NULL, cannon_shell_animation_cases_expected, COUNT(cannon_shell_animation_cases_expected), cannon_shell_animation_cases_row },
    { "cannon_shell_distance_animation_start", NULL, cannon_shell_distance_animation_start_cases_expected, COUNT(cannon_shell_distance_animation_start_cases_expected), cannon_shell_distance_animation_start_shell_case },
    { "func_8009D588", 0, 0, 4, test_func_8009D588 },
    { "bottom_margin_trail_pool_and_despawn_edges", NULL, NULL, COUNT(positions) * 8, viewport },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cannon_shell_animation_cases_expected) + COUNT(cannon_shell_distance_animation_start_cases_expected) + 4 + COUNT(positions) * 8;
