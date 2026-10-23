#include "test_runtime.h"
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
    observed_values[12] = (u32)obj.animation_step.packed;
    observed_values[13] = (u32)obj.animation_speed;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80091B1C", 0, 0, 2, test_func_80091B1C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
