#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_02_gunner_shot.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"

static struct WeaponObj gunner_owner;
#define ss state_room.shot
#define GS(kind, facing, setup) (state_reset(0, 0, 0), memset(&gunner_owner, 0, sizeof(gunner_owner)), gunner_owner.unk15 = facing, ss.active = 1, ss.state = 1, ss.unk2 = kind, ss.unk7C = &gunner_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, setup, func_8009A10C(&ss))
static void gs_spread_left(void)
{
    GS(1, 0, 0);
}
static void gs_spread_right(void) { GS(3, 0x40, 0); }
static void gs_straight(void) { GS(0, 0, ss.x_vel.val = 0x20000); }
static void gs_grounded(void) { GS(0, 0, ss.unk70 = 8); }
static struct PlayerObj gunner_player;
static void gs_hit_player(void)
{
    gunner_player = g_Player;
    GS(0, 0, (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, g_Player.unk68 = &state_hit_box, ss.unk68 = &state_hit_box));
    g_Player = gunner_player;
}
static void gs_away(void) { GS(0, 0, ss.x_pos.i.hi = 0x1000); }

static void (*const gunner_shot_fly_cases[])(void) = {
    gs_spread_left,
    gs_spread_right,
    gs_straight,
    gs_grounded,
    gs_hit_player,
    gs_away,
};
static const u32 gunner_shot_fly_expected[] = { 1u, 0x101u, 0x800000u, 0x680000u, 0u, 0xFFF80000u, 0u, 0x40000u, 0u, 0u, 1u, 0x301u, 0x800000u, 0x680000u, 0u, 0xFFF80000u, 0u, 0x40000u, 0u, 0u, 1u, 1u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u, 3u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_gunner_shot_fly(u32 row)
{
    return object_run(gunner_shot_fly_cases[row], row, &gunner_shot_fly_expected[row * 10]);
}

extern union AnimationStep* dash_gunner_animations[];
extern u8 gunner_shot_hit_box[4];
static const struct {
    u8 stage, substage;
    s16 x;
    u8 clear;
} scenes[] = {
    { 0, 1, 0xF41, 1 },
    { 0, 1, 0xF40, 0 },
    { 0, 1, 0xF3F, 0 },
    { 0, 0, 0xF41, 0 },
    { 1, 1, 0xF41, 0 },
};
static struct WeaponObj weapons_before[16];
static u32 opening_guard(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 scene = row % COUNT(scenes), facing = row / COUNT(scenes) % 2, layer = row / COUNT(scenes) / 2;
    s32 velocity = facing ? 3 * 65536 : -3 * 65536;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    engine_obj.stage = scenes[scene].stage;
    engine_obj.substage = scenes[scene].substage;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[layer].x_pos.val = (scenes[scene].x - 160) * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.unk15 = facing ? 0x40 : 0;
    obj.bg_offset = layer;
    obj.unk42 = 0x9234;
    obj.x_pos.val = scenes[scene].x * 65536 + 0x1234 - velocity;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = velocity;
    obj.unk50.data = obj.unk54 = gunner_shot_hit_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.unk5C = 1;
    obj.unk60 = 2;
    obj.animation_table = (u32**)dash_gunner_animations;
    set_animation(&obj, 8);
    assert(obj.animation_step.packed == 0x38000101);
    expected = obj;
    expected.x_pos.val += velocity;
    if (scenes[scene].clear) {
        expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
        expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    } else {
        expected.on_screen = 1;
        expected.unk42 = 0x1234;
    }
    gunner_shot_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "gunner_shot_fly", 0, 0, COUNT(gunner_shot_fly_cases), test_gunner_shot_fly },
    { "opening_cleanup_boundary_and_other_scenes", NULL, NULL, COUNT(scenes) * 6, opening_guard },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunner_shot_fly_cases) + COUNT(scenes) * 6;
