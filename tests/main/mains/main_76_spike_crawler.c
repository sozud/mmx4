#include "test_runtime.h"
#include "main/mains/main_20_ice_block.h"
#include "main/mains/main_76_spike_crawler.h"
#include "main/55C4.h"
extern union AnimationStep* ice_block_animations[9];
extern struct Unk_unk68 D_800FC84C, D_80106C74[];

struct enemy_hit_reaction_case {
    u32 obj_unk6, obj_invincibility_timer, unk5, expected_unk6, expected_invincibility_timer, unk42;
};
static const struct enemy_hit_reaction_case enemy_hit_reaction_cases[] = {
    { 0, 0, 0, 1, 39, 37428 },
    { 1, 1, 1, 0, 0, 4660 },
    { 1, 7, 0, 1, 6, 4660 },
    { 1, 8, 0, 1, 7, 37428 },
};
static u32 test_enemy_hit_reaction(u32 row)
{
    const struct enemy_hit_reaction_case* c = &enemy_hit_reaction_cases[row];
    struct MainObj obj, input, expected;
    struct PlayerObj player_expected;
    void (*reaction)(struct MainObj*);
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 20;
    obj.state = 1;
    obj.unk6 = c->obj_unk6;
    obj.unk63 = 1;
    obj.hp = 9;
    obj.unk42 = 0x9234;
    obj.invincibility_timer = c->obj_invincibility_timer;
    obj.x_pos.val = 0x00681234;
    obj.y_pos.val = 0x00845678;
    obj.unk16 = 6;
    obj.contact_damage = 3;
    obj.animation_table = (const u8* const*)ice_block_animations;
    obj.hurt_box = &D_800FC84C;
    obj.collision_data = D_80106C74;
    obj.ext.main_20.unk80 = 9;
    obj.ext.main_20.unk81 = 2;
    set_animation(&obj, 0);
    player_expected = g_Player;
    input = obj;
    expected = obj;
    expected.unk5 = c->unk5;
    expected.unk6 = c->expected_unk6;
    expected.invincibility_timer = c->expected_invincibility_timer;
    expected.unk42 = c->unk42;
    reaction = ice_block_step_funcs[0];
    reaction(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    obj = input;
    enemy_hit_reaction(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    return 1;
}

struct func_80091B1C_case {
    u32 collision_flags, x_speed;
    u32 expected[14];
};
static const struct func_80091B1C_case func_80091B1C_cases[] = {
    { 9, 131072, { 1u, 0u, 0u, 0u, 0x620000u, 0x500000u, 0xFFFE0000u, 0u, 0u, 0u, 9u, 0x20000u, 0x10001u, 0u } },
    { 10, -131072, { 1u, 0u, 0u, 0u, 0x660000u, 0x500000u, 0x20000u, 0u, 0u, 0u, 0xAu, 0x20000u, 0x10001u, 0u } },
};
static u32 test_func_80091B1C(u32 row)
{
    const struct func_80091B1C_case* c = &func_80091B1C_cases[row];
    u32 observed_values[14];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    u8 tiles[256], tiles_before[256];
    memset(&obj, 0, sizeof(obj));
    memset(&tiles, 0, sizeof(tiles));
    SP_BG_TILEMAP = tiles;
    layout_size = 256;
    layout_width = 16;
    obj.active = 0x41;
    obj.id = 76;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    spike_crawler_init(&obj);
    obj.collision_flags = c->collision_flags;
    obj.x_speed = c->x_speed;
    player_before = g_Player;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    assert(obj.terrain_box == (struct Unk_unk68*)spike_crawler_terrain_box);
    assert(obj.animation_table == (const u8* const*)spike_crawler_animations);
    func_80091B1C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.x_pos.val;
    observed_values[5] = (u32)obj.y_pos.val;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.y_speed;
    observed_values[8] = (u32)obj.x_accel;
    observed_values[9] = (u32)obj.gravity;
    observed_values[10] = (u32)obj.collision_flags;
    observed_values[11] = (u32)obj.ext.main_76.saved_x_velocity;
    observed_values[12] = (u32)obj.animation_step.packed;
    observed_values[13] = (u32)obj.animation_speed;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

struct func_80091EC4_0_case {
    u32 unk6, invincibility_timer;
    u32 expected[8];
};
static const struct func_80091EC4_0_case func_80091EC4_0_cases[] = {
    { -1, 0, { 0u, 0xFFFFFFFFu, 0x8000u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u } },
    { -1, 1, { 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u } },
    { 0, 0, { 0xFFFFFFFEu, 2u, 0u, 0u, 1u, 0u, 2u, 0u } },
};
static u32 test_func_80091EC4_0(u32 row)
{
    const struct func_80091EC4_0_case* c = &func_80091EC4_0_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = c->unk6;
    obj.invincibility_timer = c->invincibility_timer;
    func_80091EC4(&obj);
    observed_values[0] = (u32)obj.ext.main_76.bounce_step;
    observed_values[1] = (u32)obj.invincibility_timer;
    observed_values[2] = (u32)obj.unk42;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.x_accel;
    observed_values[6] = (u32)obj.x_pos.u.hi;
    observed_values[7] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 func_80091EC4_1_expected[] = { 3u, 1u, 0x11u, 0xFFFFFFFEu, 0x9234u, 0x661234u, 0u, 0u };
static u32 test_func_80091EC4_1(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 76;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk63 = 3;
    obj.x_pos.val = 6558260;
    obj.x_speed = 131072;
    obj.x_accel = 12288;
    obj.unk42 = 0x9234;
    player_before = g_Player;
    func_80091EC4(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.invincibility_timer;
    observed_values[3] = (u32)obj.ext.main_76.bounce_step;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.x_accel;
    return c_test_observe(0, row, observed_values, func_80091EC4_1_expected, 8);
}

struct spike_crawler_hit_knockback_case {
    u32 x_pos, unk63;
    u32 expected[8];
};
static const struct spike_crawler_hit_knockback_case spike_crawler_hit_knockback_cases[] = {
    { 0, 5, { 0u, 0x11u, 0x8000u, 0u, 1u, 0u, 0u, 0u } },
    { -1, 6, { 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_spike_crawler_hit_knockback(u32 row)
{
    const struct spike_crawler_hit_knockback_case* c = &spike_crawler_hit_knockback_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.val = c->x_pos;
    obj.unk63 = c->unk63;
    obj.collision_flags = 3;
    spike_crawler_hit_knockback(&obj);
    observed_values[0] = (u32)obj.gravity;
    observed_values[1] = (u32)obj.invincibility_timer;
    observed_values[2] = (u32)obj.unk42;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.x_accel;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

const struct CTestGroup c_test_groups[] = {
    { "enemy_hit_reaction", 0, 0, 4, test_enemy_hit_reaction },
    { "func_80091B1C", 0, 0, 2, test_func_80091B1C },
    { "func_80091EC4_0", 0, 0, 3, test_func_80091EC4_0 },
    { "func_80091EC4_1", 0, 0, 1, test_func_80091EC4_1 },
    { "spike_crawler_hit_knockback", 0, 0, 2, test_spike_crawler_hit_knockback },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 + 2 + 3 + 1 + 2;
