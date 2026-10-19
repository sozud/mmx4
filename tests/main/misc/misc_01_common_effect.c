#include "test_runtime.h"
#include "main/misc/misc_00_static_sprite.h"
void common_effect_update(struct MiscObj*);
extern u32* common_effect_animations[];
static struct MiscObj expected[64];
static u32 metadata[12], frames[64];
static u32 subtype_five(u32 row)
{
    struct MainObj owner, owner_before;
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u8* old_frames = TEST_MENU_FRAMES;
    u32* old_metadata = D_801406A8;
    u16 rng;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    owner.active = 0x41;
    owner.unk15 = 1;
    owner.x_pos.i.hi = 160;
    owner.y_pos.i.hi = 120;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = i < 12 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    assert(func_8002938C(0x84) == 4);
    spawn_common_effect(&owner, 5);
    assert(misc_objects[0].active == 0x41 && misc_objects[0].id == 1 && misc_objects[0].unk2 == 5 && misc_objects[0].state == 0);
    c_test_copy_words((u32*)expected, (u32*)misc_objects, sizeof(expected) / 4);
    owner_before = owner;
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    expected[0].state = 1;
    expected[0].unk6 = 0;
    expected[0].bg_offset = 0;
    expected[0].animation_table = common_effect_animations;
    expected[0].unk40 = 5;
    expected[0].unk42 = 0x7888;
    expected[0].unk3C = (u8*)frames + 64;
    expected[0].unk16 = 5;
    expected[0].unk17 = 5;
    expected[0].previous_animation_index = 0xFF;
    expected[0].animation_cursor = common_effect_animations[5];
    expected[0].animation_step.packed = 0x19010003;
    common_effect_update(&misc_objects[0]);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)&owner, (u32*)&owner_before, sizeof(owner) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 12 ? 64u : 0));
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "supported_common_effect_subtype5_own_animation_and_priority5", NULL, NULL, 1, subtype_five } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
