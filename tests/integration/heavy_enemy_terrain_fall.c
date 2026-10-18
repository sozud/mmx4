#include "test_runtime.h"
#include "main/mains/main_06_bulldozer.h"
#include "main/mains/main_51_fortress_cannon.h"
static u32 falling(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 fortress = row % 2, airborne = row / 2 % 2, grounded = row / 4 % 2, face = row / 8;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = fortress ? 51 : 6;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.air_state = airborne;
    obj.collision_flags = grounded ? 8 : 0;
    obj.unk15 = face ? 0x40 : 0;
    obj.hp = 20;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -0x8000;
    obj.x_accel = 0x400;
    obj.gravity = 0x800;
    expected = obj;
    if (!airborne && !grounded) {
        expected.unk5 = fortress ? 6 : 4;
        expected.unk6 = 0;
        expected.y_speed = expected.x_speed = expected.x_accel = 0;
        expected.gravity = 0x4200;
        expected.air_state = 1;
    }
    if (fortress)
        fortress_cannon_check_fall(&obj);
    else
        bulldozer_check_fall(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_heavy_enemy_fall_guards_clear_motion_once_and_keep_fractional_position", NULL, NULL, 16, falling } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16;
