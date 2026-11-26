#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/mains/main_76_spike_crawler.h"
#include "main/55C4.h"

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
    observed_values[12] = C_TEST_STEP(obj.animation_step.packed);
    observed_values[13] = (u32)obj.animation_speed;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

#include "support/state_cases.h"
void spike_crawler_main(struct MainObj*);
#define SC2(step, setup) (state_reset(step, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.hp = 3, so.terrain_box = (struct Unk_unk68*)spike_crawler_terrain_box, so.collision_flags = 8, so.x_speed = 0x20000, g_Player.x_pos.i.hi = 0x200, g_Player.y_pos.i.hi = 0x200, state_terrain(0x38), SPIKE_IMMUNE_SET(g_Player, 1), setup, spike_crawler_main(&so), state_extra = so.state | (u32)so.ext.main_76.saved_x_velocity << 8)
static void sc2_cooling_near(void)
{
    SC2(0, (so.unk7C = 2, so.x_speed = -0x20000, g_Player.y_pos.i.hi = 0x58));
}
static void sc2_edge_fall(void) { SC2(0, so.collision_flags = 0); }
static void sc2_wall_left(void) { SC2(0, (so.collision_flags = 0xA, so.x_speed = -0x20000, so.unk7E = 5)); }
static void sc2_left_near_above(void) { SC2(0, (so.x_speed = -0x20000, g_Player.y_pos.i.hi = 0x53)); }
static void sc2_fall_land(void) { SC2(1, (so.ext.main_76.saved_x_velocity = -0x20000, so.x_speed = 0)); }
static void sc2_fall(void) { SC2(1, (so.collision_flags = 0, so.x_speed = 0, so.gravity = 0x4200, state_terrain(0))); }
static void sc2_defeat(void) { SC2(0, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void sc2_hit(void) { SC2(0, state_hit(&so, 0, 0, 1)); }
static void sc2_away(void) { SC2(0, so.x_pos.i.hi = 0x400); }
static void sc2_near_right(void) { SC2(0, g_Player.y_pos.i.hi = 0x58); }
static void sc2_slow_left(void) { SC2(0, (so.x_speed = -0x40000, so.collision_flags = 0xA)); }
static void (*const spike_crawler_states_cases[])(void) = {
    sc2_cooling_near,
    sc2_edge_fall,
    sc2_wall_left,
    sc2_left_near_above,
    sc2_fall_land,
    sc2_fall,
    sc2_defeat,
    sc2_hit,
    sc2_away,
    sc2_near_right,
    sc2_slow_left,
};
static const u32 spike_crawler_states_expected[] = {
    0x0u,
    0x780001u,
    0x800000u,
    0xFFFC0000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x420000u,
    0x0u,
    0x30000u,
    0x2000001u,
    0x41000000u,
    0x0u,
    0x40000u,
    0x760000u,
    0x20000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
    0x0u,
    0x780000u,
    0x8C0000u,
    0xFFFC0000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
    0x0u,
    0x0u,
    0x800000u,
    0xFFFE0000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0xFE000001u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
    0x0u,
    0x0u,
    0x760000u,
    0x20000u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x2u,
    0x41002100u,
    0x0u,
    0x3Cu,
    0x760000u,
    0x20000u,
    0x0u,
    0x0u,
    0x80000000u,
    0x20001u,
    0x1u,
    0x41002100u,
    0x0u,
    0x0u,
    0x3F60000u,
    0x20000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x2u,
    0x41000000u,
    0x0u,
    0x780000u,
    0x760000u,
    0x40000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
    0x0u,
    0x0u,
    0x760000u,
    0x20000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x1u,
    0x41000000u,
};
static u32 test_spike_crawler_states(u32 row)
{
    return state_run(spike_crawler_states_cases[row], row, &spike_crawler_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "spike_crawler_states", 0, 0, COUNT(spike_crawler_states_cases), test_spike_crawler_states },
    { "func_80091B1C", 0, 0, 2, test_func_80091B1C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(spike_crawler_states_cases) + 2;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
