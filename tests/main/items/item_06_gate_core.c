#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/195B4.h"
#include "main/items/gate_core_box_data.h"
void gate_core_update(struct ItemObj*);
extern u8* gate_core_hurt_boxes[];
static struct StageObjectRecord records[2] = { { 0, 6, 1, 4, 160, 120 }, { 0, 0, 0, 255, 0, 0 } };
static struct ItemObj expected[32];
static u32 metadata[12], frames[64];
static u32 subtype_one(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u32* old_metadata = D_801406A8;
    u8* old_frames = TEST_MENU_FRAMES;
    u16 rng;
    u32 i, record_before[4];
    (void)row;
    c_test_copy_words(record_before, (u32*)records, COUNT(record_before));
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.checkpoint = 0;
    g_Player.bg_offset = 0;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = i < 12 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    assert(func_8002938C(0x98) == 8);
    func_800292D0(records);
    assert(item_objects[0].active == 1 && item_objects[0].id == 6 && item_objects[0].unk2 == 1 && item_objects[0].state == 0);
    c_test_copy_words((u32*)expected, (u32*)item_objects, sizeof(expected) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    expected[0].unk18 = expected[0].x_pos;
    expected[0].unk1C = expected[0].y_pos;
    expected[0].active = 0x41;
    expected[0].unk75 = 1;
    expected[0].unk16 = 5;
    expected[0].unk5C = 32;
    expected[0].unk68 = (struct Unk_unk68*)gate_core_terrain_boxes[1];
    expected[0].unk54 = gate_core_hurt_boxes[1];
    expected[0].unk58 = (u8*)D_80108504;
    expected[0].unk40 = 9;
    expected[0].sprite_frames = (u8*)frames + 64;
    expected[0].unk42 = 0x7946;
    expected[0].animation_table = (const u8* const*)gate_core_animations;
    expected[0].state = 1;
    gate_core_update(&item_objects[0]);
    assert(c_test_word_difference((u32*)item_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)frames);
    assert(records[0].flags == 0 && records[0].id == 6 && records[0].subtype == 1 && records[0].object_type == 4 && records[0].x == 160 && records[0].y == 120 && records[1].object_type == 255);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 12 ? 64u : 0));
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    assert(c_test_word_difference((u32*)records, record_before, COUNT(record_before)) == 0);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "supported_gate_core_subtype1_real_record_loader_constructor", NULL, NULL, 1, subtype_one } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
