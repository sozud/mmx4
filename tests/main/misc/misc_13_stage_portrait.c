#include "test_runtime.h"
#include "main/misc/misc_13_stage_portrait.h"
#include "main/55C4.h"
extern union AnimationStep* stage_portrait_animations[1];
static u32 metadata[2], archive[8];
static u32 enter(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 fixed = row % 2, resource = row / 2 % 4, fraction = row / 8, i;
    metadata[0] = 0x12345678;
    metadata[1] = (resource + 1) * 128 + 0x5A;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 2 ? 8 + i * 4 : 0x13570000 + i;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.unk2 = fixed;
    obj.unk15 = 0x40;
    obj.x_pos.val = 99 * 65536 + fraction * 0x1234;
    obj.y_pos.val = 101 * 65536 + fraction * 0x5678;
    expected = obj;
    expected.unk42 = fixed ? 0x784F : 0x780B;
    expected.unk40 = resource + 1;
    expected.animation_table = (u32**)stage_portrait_animations;
    expected.bg_offset = 0;
    expected.unk15 = 0;
    expected.unk16 = 1;
    expected.unk3C = (u8*)archive + 12;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)(stage_portrait_animations[0] + (fixed ? 10 : 1));
    expected.animation_step.packed = fixed ? 0x0A01001E : 0x0101001E;
    if (fixed) {
        expected.x_pos.i.hi = 96;
        expected.y_pos.i.hi = 384;
        expected.state = 2;
    } else {
        expected.x_pos.val = 228 * 65536;
        expected.y_pos.val = 392 * 65536;
        expected.unk7 = 1;
        expected.state = 1;
    }
    func_800CA52C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(metadata[0] == 0x12345678 && metadata[1] == (resource + 1) * 128 + 0x5A && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 2 ? 8 + i * 4 : 0x13570000 + i));
    return 1;
}

void stage_portrait_select(struct MiscObj*);
extern union AnimationStep* stage_portrait_animations[1];
static const u8 stages[10] = { 1, 6, 7, 4, 5, 3, 8, 2, 9, 10 };
static u32 portrait(u32 row)
{
    struct MiscObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 selection = row % 9, late = row / 9 % 2, unchanged = row / 18, stage = stages[selection < 8 ? selection : late ? 9
                                                                                                                       : 8],
        frame = stage - 1, i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].y_pos.i.hi = 256;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    engine_obj.unk3 = selection;
    engine_obj.unk5F = late ? 7 : 6;
    engine_before = engine_obj;
    obj.active = 1;
    obj.id = 13;
    obj.state = 1;
    obj.unk7 = unchanged ? selection : (selection + 1) % 9;
    obj.unk16 = 1;
    obj.unk42 = 0x780B;
    obj.x_pos.val = 228 * 65536 + 0x1234;
    obj.y_pos.val = 392 * 65536 + 0x5678;
    obj.animation_table = (u32**)stage_portrait_animations;
    set_animation_frame(ANIMATED_OBJECT(&obj), 0, 1);
    expected = obj;
    expected.on_screen = 1;
    if (!unchanged) {
        expected.unk7 = selection;
        expected.unk17 = 0;
        expected.previous_animation_index = 255;
        expected.animation_cursor = (u32*)(stage_portrait_animations[0] + frame);
        expected.animation_step.packed = (frame << 24) | 0x0001001E;
        expected.unk42 = (2 * (stage - 1) + 11) % 16 | (((stage + 4) / 8 + 480) << 6);
    }
    stage_portrait_select(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < COUNT(stages); i++)
        assert(mission_stage_order[i] == stages[i]);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "actual_selectable_and_fixed_portrait_constructors_with_backed_archive", NULL, NULL, 16, enter },
    { "actual_mission_order_late_stage_threshold_and_unchanged_selection", NULL, NULL, 36, portrait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16 + 36;
