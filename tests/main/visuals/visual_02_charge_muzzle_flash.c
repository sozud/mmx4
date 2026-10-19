#include "test_runtime.h"
#include "main/sprite_animations.h"
#include "main/55C4.h"
void charge_muzzle_flash_spawn_shot(struct VisualObj* arg0);
static const u8 types[3] = { 9, 18, 20 }, animations[3] = { 22, 23, 25 }, frames[3] = { 3, 4, 4 };
static u32 archive[12];
static struct WeaponObj expected_pool[16];
static u32 muzzle(u32 row)
{
    struct VisualObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 3, full = row / 3 % 2, face = row / 6, i;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 4 ? 16 + i * 4 : 0x24680000 + i;
    TEST_SPRITE_FRAMES = (u8*)archive;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    for (i = 0; i < COUNT(weapon_objects); i++) {
        weapon_objects[i].active = i == 15 && !full ? 0 : 1;
        weapon_objects[i].id = 0;
    }
    memcpy(expected_pool, weapon_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    obj.unk2 = types[kind];
    obj.animation_table = D_8011BF40;
    obj.unk3C = (u8*)archive + (kind ? 24 : 28);
    obj.unk42 = 0x7802;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    set_animation_frame(&obj, animations[kind], frames[kind]);
    assert(obj.animation_step.packed == (kind ? 0x24010101 : 0x79010101));
    expected = obj;
    expected.unk5 = 1;
    expected.on_screen = 1;
    if (!full) {
        struct WeaponObj* w = &expected_pool[15];
        w->active = 0x21;
        w->id = types[kind];
        w->x_pos = obj.x_pos;
        w->y_pos = obj.y_pos;
        w->unk15 = obj.unk15;
        w->unk3C = obj.unk3C;
        w->animation_table = obj.animation_table;
        w->unk42 = obj.unk42;
    }
    charge_muzzle_flash_spawn_shot(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(weapon_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(TEST_SPRITE_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 4 ? 16 + i * 4 : 0x24680000 + i));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "canonical_charge_events_both_facings_full_and_last_weapon_slot", NULL, NULL, 12, muzzle } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
