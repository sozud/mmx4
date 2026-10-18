#include "test_runtime.h"
#include "main/misc/misc_23_explosion_puff.h"
void func_800B10E4(u8, s32, s32, s32, s32, s32);
void dust_puff_update(struct VisualObj*);
static u32 frames[32];
static struct VisualObj expected[32];
static u32 priority_override(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u8* old_frames = TEST_SPRITE_FRAMES;
    u16 rng, high;
    u8 dirty;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = i == 2 ? 64 : 0;
    TEST_SPRITE_FRAMES = (u8*)frames;
    g_Player.bg_offset = 0;
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    cur_random = 0x1234;
    func_800B10E4(0x11, 160, 120, 160, 120, 1);
    assert(visual_objects[0].active == 0x21 && visual_objects[0].id == 9 && visual_objects[0].state == 0 && visual_objects[0].unk5C.value == 1);
    visual_objects[0].unk7 = 1;
    visual_objects[0].unk16 = 3;
    c_test_copy_words((u32*)expected, (u32*)visual_objects, sizeof(expected) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    dirty = need_palette_load;
    rng = cur_random;
    high = (u16)(rng * 3) >> 8;
    rng = ((rng + high) & 0xFF) | (high << 8);
    expected[0].on_screen = 1;
    expected[0].unk38 = 0;
    expected[0].unk3C = (u8*)frames + 64;
    expected[0].animation_table = explosion_animations;
    expected[0].bg_offset = 0;
    expected[0].unk40 = 0;
    expected[0].unk42 = 0x7805;
    expected[0].unk17 = 1;
    expected[0].previous_animation_index = 0xFF;
    expected[0].animation_cursor = explosion_animations[1];
    expected[0].animation_step.packed = 0x19010004;
    expected[0].state = 1;
    expected[0].unk7 = rng & 1;
    dust_puff_update(&visual_objects[0]);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i == 2 ? 64u : 0));
    TEST_SPRITE_FRAMES = old_frames;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "supported_dust_init_flag_preserves_caller_priority3", NULL, NULL, 1, priority_override } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
