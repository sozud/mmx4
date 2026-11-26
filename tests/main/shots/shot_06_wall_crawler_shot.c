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
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk42 = 0x9234;
    obj.unk28 = 0x27;
    obj.unk2C = 0x28;
    obj.unk67 = 0x25;
    obj.unk16 = VISUAL_SATURN_LAYER(0x26);
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
    before.unk67 = before.unk16 = VISUAL_SATURN_LAYER(0);
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
    return C_TEST_STEP(obj.animation_step.packed);
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
    obj.unk15 = facing * PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk42 = 0x9234;
    obj.unk28 = 0x27;
    obj.unk2C = 0x28;
    obj.unk67 = 0x25;
    obj.unk16 = VISUAL_SATURN_LAYER(0x26);
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
    expected.unk67 = expected.unk16 = VISUAL_SATURN_LAYER(0);
    expected.unk60 = 2;
    expected.unk42 = 0x1234;
    expected.x_vel.val = vx * 3;
    expected.y_vel.val = vy * 3;
    expected.x_pos.i.hi += angle / 2 == 0 || angle / 2 == 8 ? facing ? 13 : -13 : offsets[angle / 2][0];
    expected.y_pos.i.hi += offsets[angle / 2][1];
    expected.unk17 = 11;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)wall_crawler_animations[11];
    expected.animation_step.packed = C_TEST_STEP(0x10010001);
    func_8009A9E4(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}


#include "support/state_cases.h"
void wall_crawler_shot_fly(struct ShotObj*);
static struct Unk_unk68 wc_player_box = { 0, 0, 12, 24 };
#define ss state_room.shot
#define WC(arm, setup) (state_reset(0, 0, 0), memset(&g_Player, 0, sizeof(g_Player)), g_Player.x_pos.i.hi = 0x400, ss.active = 0x41, ss.state = 1, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.x_vel.val = 0x20000, ss.unk84.value = arm, ss.unk50.data = wall_crawler_shot_hit_boxes, setup)
static void wc_arming(void) { WC(5, ss.unk70 = 8), wall_crawler_shot_update(&ss), state_extra = ss.unk70; }
static void wc_destroyed(void) { WC(0, (so.hp = 1, state_hit(&so, 0, 0, 1))), wall_crawler_shot_fly(&ss); }
static void wc_on_player(void) { WC(0, (g_Player.x_pos.i.hi = 0x82, g_Player.y_pos.i.hi = 0x60, g_Player.unk54 = (const u32*)&wc_player_box)), wall_crawler_shot_fly(&ss); }
static void wc_on_terrain(void) { WC(0, ss.unk70 = 8), wall_crawler_shot_fly(&ss); }
static void wc_flying(void) { WC(0, ss.unk70 = 0xA0), wall_crawler_shot_update(&ss); }

static void (*const wc_cases[])(void) = {
    wc_arming,
    wc_destroyed,
    wc_on_player,
    wc_on_terrain,
    wc_flying,
};
static const u32 wc_expected[] = {
    0x1u, 0x41u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0x8u, 0u,
    0x2u, 0x41u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x48000u, 0u, 0x2100u,
    0x2u, 0x41u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u,
    0x2u, 0x41u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0x2100u,
    0x1u, 0x41u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u,
};
static u32 test_wc(u32 row)
{
    return object_run(wc_cases[row], row, &wc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "wall_crawler_shot_flight", 0, 0, COUNT(wc_cases), test_wc },
    { "wall_crawler_shot_default", NULL, wall_crawler_shot_default_cases_expected, COUNT(wall_crawler_shot_default_cases_expected), default_case },
    { "shot_spawn_directions", NULL, NULL, 64, direction },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wall_crawler_shot_default_cases_expected) + 64 + COUNT(wc_cases);
