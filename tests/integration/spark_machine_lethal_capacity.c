#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/weapons/weapon_04_rising_fire.h"
#include "main/items/item_10_spark_machine.h"
#include "main/player_common.h"
static struct {
    u32 root[8];
    u32 bank[13];
    u16 stream[4];
} fire_archive;
static struct MiscObj misc_before[64];
static struct VisualObj visuals_before[32];
static struct WeaponObj weapons_expected[16];
static u32 archive[64], metadata[16], sprites[32];
static u32 full(u32 row)
{
    struct ItemObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.stage = 1;
    engine_obj.substage = 1;
    background_objects[0].x_pos.i.hi = 2192;
    background_objects[0].y_pos.i.hi = 1280;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.weapon = 4;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    g_Player.shot_count = 1;
    g_Player.special_shot_count = 1;
    g_Player.x_pos.i.hi = 2363;
    g_Player.y_pos.i.hi = 1410;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 16 ? 64 + i * 4 : 0x13570000 + i;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = metadata;
    assert(func_8002938C(0x9D) == 9);
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 10;
    obj.x_pos.i.hi = 2352;
    obj.y_pos.i.hi = 1400;
    func_800C2528(&obj);
    assert(obj.state == 1 && obj.unk5C == 16 && obj.unk17 == 13);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    sprites[13] = 64;
    fire_archive.root[5] = 0x20;
    for (i = 0; i < 13; i++)
        fire_archive.bank[i] = 1 << 20 | ((u8*)fire_archive.stream - (u8*)fire_archive.bank);
    fire_archive.stream[0] = 0x8000;
    TEST_PLAYER_GFX = (u8*)&fire_archive;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    vram_rect_ptr = vram_rect_ptrs;
    weapon_objects[0].active = 0x41;
    weapon_objects[0].id = 4;
    weapon_objects[0].owner = &g_Player;
    func_80095254(&weapon_objects[0]);
    assert(weapon_objects[0].state == 1 && weapon_objects[0].x_pos.i.hi == 2352 && weapon_objects[0].y_pos.i.hi == 1400);
    expected = obj;
    expected.unk5C = 0;
    expected.unk63 = 0;
    expected.unk65 = 1;
    expected.unk42 = 0x78CC;
    expected.state = 2;
    expected.on_screen = 1;
    expected.tail_ext.unk1.unk84.bytes[3] = 120;
    set_animation(&expected, 0);
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    ((s16*)&weapons_expected[0].unk80)[0] = 2351;
    ((s16*)&weapons_expected[0].unk80)[1] = 1399;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    player = g_Player;
    engine = engine_obj;
    cur_random = 0x1234;
    func_800C2638(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons_expected, sizeof(weapons_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc_before, sizeof(misc_before) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && TEST_MENU_FRAMES == (u8*)archive && D_801406A8 == metadata);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 16 ? 64 + i * 4 : 0x13570000 + i));
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "stage1_real_spark_machine_and_rising_fire_ctor_lethal_hit_full_misc_pool", NULL, NULL, 1, full } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
