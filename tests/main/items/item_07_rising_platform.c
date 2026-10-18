#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/player_common.h"
void func_800C16F0(struct ItemObj*);
void rising_platform_rise(struct ItemObj*);
static struct ItemObj expected_items[32];
static u8 map[3 * 512];
static u16 tiles[256];
static u32 attributes[1], frames[64], resources[64];
static u32 grow(u32 row)
{
    struct ItemObj* self = &item_objects[0];
    struct EngineObj engine;
    struct PlayerObj player, entity;
    struct RideArmorObj ride;
    struct BackgroundObj backgrounds[3];
    u32 i, resource;
    u16 rng = cur_random;
    (void)row;
    engine_obj.state = 6;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    engine = engine_obj;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.state = 1;
    g_Player.animation_table = (u32**)D_80119DF0;
    g_Player.x_pos.i.hi = 5000;
    g_Player.y_pos.i.hi = 1456;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    player = g_Player;
    g_Entity.active = 0;
    entity = g_Entity;
    qux_object.active = 0;
    ride = qux_object;
    background_objects[0].x_pos.i.hi = 5300;
    background_objects[0].y_pos.i.hi = 1328;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    memset(map, 0, sizeof(map));
    memset(tiles, 0, sizeof(tiles));
    attributes[0] = 0;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = 32;
    layout_height = 16;
    layout_size = 512;
    memset(frames, 0, sizeof(frames));
    memset(resources, 0, sizeof(resources));
    resource = (u8)func_8002938C(0x87);
    assert(resource < 32);
    frames[resource] = 128;
    TEST_MENU_FRAMES = (u8*)frames;
    D_801406A8 = resources;
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    for (i = 0; i < COUNT(item_objects); i++)
        item_objects[i].active = 1;
    self->id = 7;
    self->unk2 = 1;
    self->x_pos.i.hi = 0x1550;
    self->y_pos.i.hi = 0x5B0;
    func_800C16F0(self);
    assert(self->state == 1 && self->y_vel.val == 0x8000);
    memcpy(expected_items, item_objects, sizeof(expected_items));
    expected_items[0].unk18 = self->x_pos;
    expected_items[0].unk1C = self->y_pos;
    expected_items[0].y_pos.val -= 0x8000;
    expected_items[0].on_screen = 1;
    rising_platform_rise(self);
    assert(c_test_word_difference((u32*)item_objects, (u32*)expected_items, sizeof(expected_items) / 4) == 0);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&g_Entity, &entity, sizeof(entity));
    c_test_same_words(&qux_object, &ride, sizeof(ride));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(cur_random == rng && attributes[0] == 0);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 0);
    for (i = 0; i < COUNT(tiles); i++)
        assert(tiles[i] == 0);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i == resource ? 128u : 0) && resources[i] == 0);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "original_frost_shaft_first_rising_platform_full_Item_pool", NULL, NULL, 1, grow } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
