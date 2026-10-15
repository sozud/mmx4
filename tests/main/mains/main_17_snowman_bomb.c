#include "test_runtime.h"
extern struct Unk_unk68 item_carrier_hitboxes;
extern struct Unk_unk68 item_carrier_capsule_hurtbox;

static const u32 snowman_bomb_main_expected[] = { 2u, 6u, 1u, 6u, 0x640000u, 0x500000u, 6u, 0u };
static u32 test_snowman_bomb_main(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    struct VisualObj visual_before[32];
    struct MiscObj misc_before[64];
    u32 map_words[64], pixels_words[256], attributes[1];
    u32 map_before[64], pixels_before[256], attributes_before[1];
    u8 pool_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 17;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    snowman_bomb_init(&obj);
    memset(&map_words, 0, sizeof(map_words));
    memset(&pixels_words, 0, sizeof(pixels_words));
    memset(&attributes, 0, sizeof(attributes));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (void*)pixels_words;
    TEST_BG_TILE_ATTRS = (void*)attributes;
    layout_width = 16;
    layout_size = 256;
    map_words[0] = 0x01010101;
    attributes[0] = 0x3E;
    memcpy(map_before, map_words, sizeof(map_before));
    memcpy(pixels_before, pixels_words, sizeof(pixels_before));
    memcpy(attributes_before, attributes, sizeof(attributes_before));
    pool_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_full ? 1 : 0;
    }
    memcpy(visual_before, visual_objects, sizeof(visual_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    obj.unk5 = 6;
    obj.unk7C = 2;
    obj.air_state = 1;
    snowman_bomb_main(&obj);
    assert(obj.terrain_box == &snowman_bomb_terrain_box);
    c_test_same_words(map_words, map_before, sizeof(map_words));
    c_test_same_words(pixels_words, pixels_before, sizeof(pixels_words));
    c_test_same_words(attributes, attributes_before, sizeof(attributes));
    c_test_same_words(visual_objects, visual_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)(u8)obj.hp;
    observed_values[4] = (u32)obj.x_pos.val;
    observed_values[5] = (u32)obj.y_pos.val;
    observed_values[6] = (u32)obj.ext.main_17.unk90;
    observed_values[7] = (u32)obj.collision_flags;
    return c_test_observe(0, row, observed_values, snowman_bomb_main_expected, 8);
}

const struct CTestGroup c_test_groups[] = {
    { "snowman_bomb_main", 0, 0, 1, test_snowman_bomb_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
