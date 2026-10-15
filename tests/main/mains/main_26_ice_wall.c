#include "test_runtime.h"
extern struct TileEffectRecord** tile_effect_tables[26];
extern struct TileEffectRecord* D_8011919C[33];

struct func_800583B0_0_case {
    u32 base, upper_effect, lower_effect, upper_two, lower_two, attrs_1, attrs_2;
    u32 expected[5];
};
static const struct func_800583B0_0_case func_800583B0_0_cases[] = {
    { 5, 9, 24, 0, 1, 56, 56, { 1u, 0xC005u, 0xC00Bu, 0xC01Bu, 0xC03Cu } },
    { 10, 14, 29, 0, 1, 58, 58, { 1u, 0u, 0u, 0u, 0xC035u } },
    { 0, 2, 17, 0, 1, 49, 49, { 1u, 0xC00Fu, 0xC008u, 0xC018u, 0xC01Fu } },
    { 5, 6, 21, 0, 0, 48, 48, { 1u, 0xC00Fu, 0xC00Bu, 0xC01Bu, 0u } },
    { 10, 13, 28, 1, 1, 0, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 10, 10, 25, 0, 1, 60, 60, { 1u, 0xC028u, 0u, 0x4031u, 0xC033u } },
};
static u32 test_func_800583B0_0(u32 row)
{
    const struct func_800583B0_0_case* c = &func_800583B0_0_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u16 pixels[512], expected_pixels[512];
    u16 expected_cache[3][32][32];
    u32 attrs[4], attrs_before[4];
    u8 tiles[4], tiles_before[4];
    s16 probe_x, probe_y;
    s32 base, upper_effect, lower_effect;
    u8 upper_two, lower_two;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 26;
    obj.state = 1;
    obj.hp = 9;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00801234;
    obj.y_pos.val = 0x00805678;
    expected = obj;
    probe_x = 128;
    probe_y = 128;
    base = c->base;
    upper_effect = c->upper_effect;
    lower_effect = c->lower_effect;
    upper_two = c->upper_two;
    lower_two = c->lower_two;
    memset(pixels, 0, sizeof(pixels));
    pixels[344] = 1;
    pixels[360] = 1;
    pixels[440] = 2;
    attrs[0] = 0;
    attrs[1] = c->attrs_1;
    attrs[2] = c->attrs_2;
    attrs[3] = 0xCAFE1234;
    tiles[0] = 1;
    tiles[1] = 1;
    tiles[2] = 1;
    tiles[3] = 0xA5;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(tiles_before, tiles, sizeof(tiles));
    memcpy(attrs_before, attrs, sizeof(attrs));
    memcpy(expected_pixels, pixels, sizeof(pixels));
    memcpy(expected_cache, D_801441C8, sizeof(expected_cache));
    assert(tile_effect_tables[5] == D_8011919C);
    expected_pixels[375] = D_8011919C[upper_effect][upper_two].tiles[0];
    expected_cache[0][7][7] = D_8011919C[upper_effect][upper_two].tiles[0];
    if (upper_two) {
        expected_pixels[359] = D_8011919C[upper_effect][0].tiles[0];
    }
    if (upper_two) {
        expected_cache[0][6][7] = D_8011919C[upper_effect][0].tiles[0];
    }
    expected_pixels[391] = D_8011919C[30 + base / 5][0].tiles[0];
    expected_cache[0][8][7] = D_8011919C[30 + base / 5][0].tiles[0];
    expected_pixels[407] = D_8011919C[lower_effect][0].tiles[0];
    expected_cache[0][9][7] = D_8011919C[lower_effect][0].tiles[0];
    if (lower_two) {
        expected_pixels[423] = D_8011919C[lower_effect][1].tiles[0];
    }
    if (lower_two) {
        expected_cache[0][10][7] = D_8011919C[lower_effect][1].tiles[0];
    }
    expected_pixels[376] = D_8011919C[upper_effect][upper_two].tiles[1];
    expected_cache[0][7][8] = D_8011919C[upper_effect][upper_two].tiles[1];
    if (upper_two) {
        expected_pixels[360] = D_8011919C[upper_effect][0].tiles[1];
    }
    if (upper_two) {
        expected_cache[0][6][8] = D_8011919C[upper_effect][0].tiles[1];
    }
    expected_pixels[392] = D_8011919C[30 + base / 5][0].tiles[1];
    expected_cache[0][8][8] = D_8011919C[30 + base / 5][0].tiles[1];
    expected_pixels[408] = D_8011919C[lower_effect][0].tiles[1];
    expected_cache[0][9][8] = D_8011919C[lower_effect][0].tiles[1];
    if (lower_two) {
        expected_pixels[424] = D_8011919C[lower_effect][1].tiles[1];
    }
    if (lower_two) {
        expected_cache[0][10][8] = D_8011919C[lower_effect][1].tiles[1];
    }
    expected_pixels[377] = D_8011919C[upper_effect][upper_two].tiles[2];
    expected_cache[0][7][9] = D_8011919C[upper_effect][upper_two].tiles[2];
    if (upper_two) {
        expected_pixels[361] = D_8011919C[upper_effect][0].tiles[2];
    }
    if (upper_two) {
        expected_cache[0][6][9] = D_8011919C[upper_effect][0].tiles[2];
    }
    expected_pixels[393] = D_8011919C[30 + base / 5][0].tiles[2];
    expected_cache[0][8][9] = D_8011919C[30 + base / 5][0].tiles[2];
    expected_pixels[409] = D_8011919C[lower_effect][0].tiles[2];
    expected_cache[0][9][9] = D_8011919C[lower_effect][0].tiles[2];
    if (lower_two) {
        expected_pixels[425] = D_8011919C[lower_effect][1].tiles[2];
    }
    if (lower_two) {
        expected_cache[0][10][9] = D_8011919C[lower_effect][1].tiles[2];
    }
    func_800583B0(&obj, probe_x, probe_y, base);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(pixels, expected_pixels, sizeof(pixels));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(D_801441C8, expected_cache, sizeof(expected_cache));
    observed_values[0] = (u32)pixels[360];
    observed_values[1] = (u32)pixels[376];
    observed_values[2] = (u32)pixels[392];
    observed_values[3] = (u32)pixels[408];
    observed_values[4] = (u32)pixels[424];
    return c_test_observe(0, row, observed_values, c->expected, 5);
}
static const u32 func_800583B0_1_expected[] = { 1u, 0xC01Fu, 0u, 0xC01Bu, 0xC00Fu };
static u32 test_func_800583B0_1(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u16 pixels[512], expected_pixels[512];
    u16 expected_cache[3][32][32];
    u32 attrs[4], attrs_before[4];
    u8 tiles[4], tiles_before[4];
    s16 probe_x, probe_y;
    s32 base, upper_effect, lower_effect, middle_effect;
    u8 upper_two, lower_two;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 26;
    obj.state = 1;
    obj.hp = 9;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00801234;
    obj.y_pos.val = 0x00805678;
    expected = obj;
    probe_x = 128;
    probe_y = 128;
    base = 1;
    middle_effect = 32;
    upper_effect = 5;
    lower_effect = 20;
    upper_two = 0;
    lower_two = 1;
    memset(pixels, 0, sizeof(pixels));
    pixels[344] = 1;
    pixels[360] = 1;
    pixels[440] = 2;
    attrs[0] = 0;
    attrs[1] = 36;
    attrs[2] = 36;
    attrs[3] = 0xCAFE1234;
    tiles[0] = 1;
    tiles[1] = 1;
    tiles[2] = 1;
    tiles[3] = 0xA5;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(tiles_before, tiles, sizeof(tiles));
    memcpy(attrs_before, attrs, sizeof(attrs));
    memcpy(expected_pixels, pixels, sizeof(pixels));
    memcpy(expected_cache, D_801441C8, sizeof(expected_cache));
    assert(tile_effect_tables[5] == D_8011919C);
    expected_pixels[375] = D_8011919C[upper_effect][upper_two].tiles[0];
    expected_cache[0][7][7] = D_8011919C[upper_effect][upper_two].tiles[0];
    if (upper_two) {
        expected_pixels[359] = D_8011919C[upper_effect][0].tiles[0];
    }
    if (upper_two) {
        expected_cache[0][6][7] = D_8011919C[upper_effect][0].tiles[0];
    }
    expected_pixels[391] = D_8011919C[middle_effect][0].tiles[0];
    expected_cache[0][8][7] = D_8011919C[middle_effect][0].tiles[0];
    expected_pixels[407] = D_8011919C[lower_effect][0].tiles[0];
    expected_cache[0][9][7] = D_8011919C[lower_effect][0].tiles[0];
    if (lower_two) {
        expected_pixels[423] = D_8011919C[lower_effect][1].tiles[0];
    }
    if (lower_two) {
        expected_cache[0][10][7] = D_8011919C[lower_effect][1].tiles[0];
    }
    expected_pixels[376] = D_8011919C[upper_effect][upper_two].tiles[1];
    expected_cache[0][7][8] = D_8011919C[upper_effect][upper_two].tiles[1];
    if (upper_two) {
        expected_pixels[360] = D_8011919C[upper_effect][0].tiles[1];
    }
    if (upper_two) {
        expected_cache[0][6][8] = D_8011919C[upper_effect][0].tiles[1];
    }
    expected_pixels[392] = D_8011919C[middle_effect][0].tiles[1];
    expected_cache[0][8][8] = D_8011919C[middle_effect][0].tiles[1];
    expected_pixels[408] = D_8011919C[lower_effect][0].tiles[1];
    expected_cache[0][9][8] = D_8011919C[lower_effect][0].tiles[1];
    if (lower_two) {
        expected_pixels[424] = D_8011919C[lower_effect][1].tiles[1];
    }
    if (lower_two) {
        expected_cache[0][10][8] = D_8011919C[lower_effect][1].tiles[1];
    }
    expected_pixels[377] = D_8011919C[upper_effect][upper_two].tiles[2];
    expected_cache[0][7][9] = D_8011919C[upper_effect][upper_two].tiles[2];
    if (upper_two) {
        expected_pixels[361] = D_8011919C[upper_effect][0].tiles[2];
    }
    if (upper_two) {
        expected_cache[0][6][9] = D_8011919C[upper_effect][0].tiles[2];
    }
    expected_pixels[393] = D_8011919C[middle_effect][0].tiles[2];
    expected_cache[0][8][9] = D_8011919C[middle_effect][0].tiles[2];
    expected_pixels[409] = D_8011919C[lower_effect][0].tiles[2];
    expected_cache[0][9][9] = D_8011919C[lower_effect][0].tiles[2];
    if (lower_two) {
        expected_pixels[425] = D_8011919C[lower_effect][1].tiles[2];
    }
    if (lower_two) {
        expected_cache[0][10][9] = D_8011919C[lower_effect][1].tiles[2];
    }
    func_800583B0(&obj, probe_x, probe_y, base);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(pixels, expected_pixels, sizeof(pixels));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(D_801441C8, expected_cache, sizeof(expected_cache));
    observed_values[0] = (u32)pixels[360];
    observed_values[1] = (u32)pixels[376];
    observed_values[2] = (u32)pixels[392];
    observed_values[3] = (u32)pixels[408];
    observed_values[4] = (u32)pixels[424];
    return c_test_observe(1, row, observed_values, func_800583B0_1_expected, 5);
}
static u32 test_func_800583B0(u32 index)
{
    if (index < 6)
        return test_func_800583B0_0(index);
    index -= 6;
    return test_func_800583B0_1(index);
}

struct ice_wall_break_case {
    u32 x_pos, remove;
    u32 expected[4];
};
static const struct ice_wall_break_case ice_wall_break_cases[] = {
    { 6558260, 0, { 0x41u, 2u, 1u, 0x21u } },
    { 52433460, 1, { 0u, 0u, 0u, 0x80u } },
    { 4289663540, 1, { 0u, 0u, 0u, 0x80u } },
    { 26219060, 1, { 0u, 0u, 0u, 0x80u } },
};
static u32 test_ice_wall_break(u32 row)
{
    const struct ice_wall_break_case* c = &ice_wall_break_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct BackgroundObj background_before;
    struct EngineObj engine_before;
    u8 flag, remove;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 26;
    obj.unk2 = 2;
    obj.on_screen = 1;
    obj.state = 2;
    obj.unk5 = 1;
    obj.unk6 = 0x35;
    obj.unk7 = 0x46;
    obj.unk42 = 0x1234;
    obj.hp = 1;
    obj.x_pos.val = c->x_pos;
    obj.y_pos.val = 0x00645678;
    flag = 0x21;
    obj.backref = &flag;
    remove = c->remove;
    expected = obj;
    if (remove) {
        expected.active = 0;
    }
    if (remove) {
        expected.id = 0;
    }
    if (remove) {
        expected.unk2 = 0;
    }
    if (remove) {
        expected.on_screen = 0;
    }
    if (remove) {
        expected.state = 0;
    }
    if (remove) {
        expected.unk5 = 0;
    }
    if (remove) {
        expected.unk6 = 0;
    }
    if (remove) {
        expected.unk7 = 0;
    }
    g_Player.spike_immune = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    player_before = g_Player;
    background_before = background_objects[0];
    engine_before = engine_obj;
    ice_wall_break(BASE_OBJECT(&obj));
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    assert(flag == (remove ? 0x80 : 0x21));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)flag;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800583B0", 0, 0, 7, test_func_800583B0 },
    { "ice_wall_break", 0, 0, 4, test_ice_wall_break },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 7 + 4;
