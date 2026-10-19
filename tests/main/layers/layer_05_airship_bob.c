#include "test_runtime.h"
void func_800DA358(struct LayerObj*);
static u32 end(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 crossed = row % 2, down = row / 2 % 2, camera = row / 4, scroll = 0x8000;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 7;
    engine_obj.substage = 0;
    engine_obj.unkF = 0;
    engine_expected = engine_obj;
    if (crossed)
        engine_expected.unkF = 1;
    g_Player.x_pos.val = (crossed ? 0x18D0 : 0x18CF) * 65536 + 0x1234;
    player_before = g_Player;
    background_objects[0].x_pos.val = 0x1800 * 65536 + 0x1234;
    background_objects[0].unk14.val = background_objects[0].x_pos.val + (camera ? 0x10004 : 0);
    background_objects[1].x_pos.val = 0x2345;
    background_objects[2].x_pos.val = 0x3456;
    background_objects[1].y_pos.val = 0x1234;
    background_objects[2].y_pos.val = 0x2345;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 1;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk7 = down;
    obj.unk24 = obj.unk25 = 2;
    memcpy(&obj.bg_offset, &scroll, 4);
    expected = obj;
    expected.unk18.val = down ? -0x400 : 0x400;
    backgrounds_expected[1].x_pos.val += 0x8000 - (camera ? 0x8002 : 0);
    backgrounds_expected[2].x_pos.val -= 0x4000 + (camera ? 0x4001 : 0);
    backgrounds_expected[1].y_pos.val += down ? 0x200 : -0x200;
    backgrounds_expected[2].y_pos.val += down ? 0x400 : -0x400;
    func_800DA358(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "shipped_airship_layer_end_position_and_fractional_camera_motion_both_sway_phases", NULL, NULL, 8, end } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 8;
