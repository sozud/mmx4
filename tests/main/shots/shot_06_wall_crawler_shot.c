#include "test_runtime.h"
#include "main/shots/shot_06_wall_crawler_shot.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
extern union AnimationStep* wall_crawler_animations[25];
extern u8 wall_crawler_shot_hit_boxes[8], wall_crawler_shot_terrain_box[4];
extern s8 wall_crawler_shot_spawn_offsets[16];

static u32 default_case(u32 observation)
{
    struct ShotObj obj, before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 6;
    obj.state = 1;
    obj.unk2 = 0;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk42 = 0x9234;
    obj.unk28 = 0x27;
    obj.unk2C = 0x28;
    obj.unk67 = 0x25;
    obj.unk16 = 0x26;
    obj.animation_table = (u32**)wall_crawler_animations;
    set_animation(&obj, 0);
    before = obj;
    func_8009A9E4(&obj);
    before.unk68 = (struct Unk_unk68*)wall_crawler_shot_terrain_box;
    before.unk54 = wall_crawler_shot_hit_boxes;
    before.unk50.data = wall_crawler_shot_hit_boxes;
    before.on_screen = 1;
    before.unk58.data = (const u8*)D_80105FF0;
    before.state = 2;
    before.unk28 = before.unk2C = 0;
    before.unk5C = 1;
    before.unk67 = before.unk16 = 0;
    before.unk60 = 2;
    before.unk42 = 0x1234;
    before.x_vel.val = 3 * 65536;
    before.y_vel.val = -3 * 65536;
    before.x_pos.i.hi += wall_crawler_shot_spawn_offsets[2];
    before.y_pos.i.hi += wall_crawler_shot_spawn_offsets[3];
    before.unk17 = 11;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)wall_crawler_animations[11];
    before.animation_step = *wall_crawler_animations[11];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    if (observation == 0)
        return (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
    return obj.animation_step.packed;
}
static const u32 wall_crawler_shot_default_cases_expected[] = { 0xC80071u, 0x10010001u };

extern union AnimationStep* wall_crawler_animations[25];
extern u8 wall_crawler_shot_hit_boxes[8], wall_crawler_shot_terrain_box[4];
static const s32 quadrant[9][2] = {
    { 65536, 0 },
    { 0xFB14, 0x31F1 },
    { 0xEC83, 0x61F7 },
    { 0xD4DB, 0x8E39 },
    { 0xB505, 0xB505 },
    { 0x8E39, 0xD4DB },
    { 0x61F7, 0xEC83 },
    { 0x31F1, 0xFB14 },
    { 0, 65536 },
};
static const s8 offsets[16][2] = {
    { 0, 0 },
    { 10, -12 },
    { 10, -12 },
    { 10, -12 },
    { 0, -16 },
    { -10, -12 },
    { -10, -12 },
    { -10, -12 },
    { 0, 0 },
    { -10, 12 },
    { -10, 12 },
    { -10, 12 },
    { 0, 16 },
    { 10, 12 },
    { 10, 12 },
    { 10, 12 },
};
static u32 direction(u32 row)
{
    struct ShotObj obj, expected;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    u32 angle = row % 32, facing = row / 32, quarter = angle / 8, phase = angle % 8;
    s32 x = quadrant[phase][0], y = quadrant[phase][1], vx, vy;
    if (quarter == 0) {
        vx = x;
        vy = y;
    } else if (quarter == 1) {
        vx = -y;
        vy = x;
    } else if (quarter == 2) {
        vx = -x;
        vy = -y;
    } else {
        vx = y;
        vy = -x;
    }
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 6;
    obj.unk2 = angle;
    obj.unk15 = facing * 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk42 = 0x9234;
    obj.unk28 = 0x27;
    obj.unk2C = 0x28;
    obj.unk67 = 0x25;
    obj.unk16 = 0x26;
    obj.animation_table = (u32**)wall_crawler_animations;
    set_animation(&obj, 0);
    set_velocity_from_angle(MOVING_OBJECT(&obj), angle);
    assert(obj.x_vel.val == vx && obj.y_vel.val == vy);
    expected = obj;
    expected.unk68 = (struct Unk_unk68*)wall_crawler_shot_terrain_box;
    expected.unk54 = wall_crawler_shot_hit_boxes;
    expected.unk50.data = wall_crawler_shot_hit_boxes;
    expected.on_screen = 1;
    expected.unk58.data = (const u8*)D_80105FF0;
    expected.state = 1;
    expected.unk28 = expected.unk2C = 0;
    expected.unk5C = 1;
    expected.unk67 = expected.unk16 = 0;
    expected.unk60 = 2;
    expected.unk42 = 0x1234;
    expected.x_vel.val = vx * 3;
    expected.y_vel.val = vy * 3;
    expected.x_pos.i.hi += angle / 2 == 0 || angle / 2 == 8 ? facing ? 13 : -13 : offsets[angle / 2][0];
    expected.y_pos.i.hi += offsets[angle / 2][1];
    expected.unk17 = 11;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)wall_crawler_animations[11];
    expected.animation_step.packed = 0x10010001;
    func_8009A9E4(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "wall_crawler_shot_default", NULL, wall_crawler_shot_default_cases_expected, COUNT(wall_crawler_shot_default_cases_expected), default_case },
    { "shot_spawn_directions", NULL, NULL, 64, direction },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wall_crawler_shot_default_cases_expected) + 64;
