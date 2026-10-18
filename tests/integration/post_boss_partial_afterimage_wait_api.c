#include "test_runtime.h"
void post_boss_cutscene_update(struct MiscObj*);
void object_afterimage_update(struct VisualObj*);
void object_afterimage_wait(struct VisualObj*);
static u32 metadata[8], menu[64];
static struct VisualObj expected[32];
union OwnerStorage {
    struct MiscObj misc;
    struct PlayerObj player;
};
static u32 partial_wait_api(u32 row)
{
    union OwnerStorage owner_storage, owner_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before, entity_before;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u16 rng;
    u32 i;
    u32* old_metadata = D_801406A8;
    u8* old_menu = TEST_MENU_FRAMES;
    (void)row;
    c_test_zero_words((u32*)&owner_storage, sizeof(owner_storage) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(menu); i++)
        menu[i] = i < 8 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)menu;
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 120;
    background_objects[0].x_pos.i.hi = 112;
    for (i = 0; i < 31; i++)
        visual_objects[i].active = 1;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    owner_storage.misc.active = 0x41;
    owner_storage.misc.id = 46;
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.state == 1 && owner_storage.misc.unk5 == 0 && visual_objects[31].active == 0x41 && visual_objects[31].id == 5 && visual_objects[31].unk2 == 0 && visual_objects[31].unk5C.owner == PLAYER_OBJECT(&owner_storage.misc));
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.unk5 == 1);
    for (i = 0; i < 60; i++) {
        post_boss_cutscene_update(&owner_storage.misc);
        object_afterimage_update(&visual_objects[31]);
    }
    assert(owner_storage.misc.unk5 == 2 && owner_storage.player.pad4B[0] == 1 && visual_objects[31].state == 1);
    for (i = 0; i < 100 && !(visual_objects[31].unk5 == 2 && visual_objects[31].unk58 == 0); i++) {
        post_boss_cutscene_update(&owner_storage.misc);
        object_afterimage_update(&visual_objects[31]);
    }
    assert(i < 100 && owner_storage.misc.unk5 == 4 && owner_storage.player.pad4B[0] == -1 && visual_objects[31].state == 1);
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.unk5 == 4);
    object_afterimage_update(&visual_objects[31]);
    assert(visual_objects[31].state == 0 && visual_objects[31].on_screen == 0 && owner_storage.player.pad4B[0] == -1);
    object_afterimage_update(&visual_objects[31]);
    assert(owner_storage.player.pad4B[0] == 0 && visual_objects[31].state == 0);
    c_test_copy_words((u32*)expected, (u32*)visual_objects, sizeof(expected) / 4);
    owner_before = owner_storage;
    engine_before = engine_obj;
    player_before = g_Player;
    entity_before = g_Entity;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    object_afterimage_wait(&visual_objects[31]);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)&owner_storage, (u32*)&owner_before, sizeof(owner_storage) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine_before, sizeof(engine_before) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player_before, sizeof(player_before) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity_before, sizeof(entity_before) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && D_8013E198[2] == -1 && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)menu);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(menu); i++)
        assert(menu[i] == (i < 8 ? 64u : 0));
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_menu;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "supported_wait_helper_noop_after_real_partial_image_cancel", NULL, NULL, 1, partial_wait_api } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
