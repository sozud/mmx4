#include "test_runtime.h"
#include "main/misc/misc_07_attached_effect.h"
extern union AnimationStep* jet_drone_animations[];
static u32 trail(u32 row)
{
    struct MiscObj obj, expected;
    struct FixedPointPosition position, position_before;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 2, face = row / 2 % 2, layer = row / 4;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    position.x = 160 * 65536 + 0x1234;
    position.y = 120 * 65536 + 0x5678;
    obj.active = 0x41;
    obj.id = 7;
    obj.unk2 = kind;
    obj.unk15 = face ? 0x40 : 0;
    obj.bg_offset = layer;
    obj.animation_table = (u32**)jet_drone_animations;
    obj.ext.misc_7.position = &position;
    expected = obj;
    expected.state = 1;
    expected.x_pos.val = position.x + (kind ? (face ? 3 : -3) * 65536 : 0);
    expected.y_pos.val = position.y;
    expected.unk17 = 10;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)jet_drone_animations[10];
    expected.animation_step.packed = 0x10010001;
    attached_effect_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    position.x += 65536;
    position.y += 2 * 65536;
    position_before = position;
    expected.x_pos.val += 65536;
    expected.y_pos.val += 2 * 65536;
    expected.animation_cursor++;
    expected.animation_step.packed = 0x1C010001;
    expected.on_screen = 1;
    attached_effect_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&position, &position_before, sizeof(position));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "actual_jet_drone_trail_facing_and_moving_position_source", NULL, NULL, 12, trail } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
