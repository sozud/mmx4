#include "test_runtime.h"
#include "main/shots/shot_44_iris_shot.h"
#include "main/55C4.h"
#include "main/player_animations_2.h"
#include "main/player_common.h"
extern void* iris_animations[37];

static u32 drone_case(u32 burst, u32 observation)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk5 = burst ? 4 : 1;
    obj.unk61 = 0x27;
    obj.timer = 0x7777;
    obj.unk28 = 0x1000;
    obj.unk2C = 0x1000;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = -32768;
    obj.y_vel.val = 32768;
    obj.animation_table = (u32**)iris_animations;
    set_animation_frame(&obj, 14, burst ? 8 : 0);
    before = obj;
    player_before = g_Player;
    if (burst) {
        iris_drone_burst(&obj);
        before.unk5 = 5;
        before.unk17 = 15;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = iris_animations[15];
        before.animation_step = *(union AnimationStep*)iris_animations[15];
    } else {
        iris_drone_brake(&obj);
        before.x_pos.val -= 32768;
        before.y_pos.val -= 32768;
        before.animation_step.fields.duration = 1;
        before.unk5 = 2;
        before.unk61 = 0;
        before.timer = 0x3C;
        before.x_vel.val = before.y_vel.val = before.unk28 = before.unk2C = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u16)obj.timer << 8) | ((u32)obj.unk17 << 24) : obj.animation_step.packed;
}
static const u32 iris_drone_animation_context_cases_expected[] = { 0xE003C02u, 0x47010001u, 0xF777705u, 0x4A010003u };
static u32 iris_drone_animation_context_cases_row(u32 row)
{
    return drone_case(row / 2, row % 2);
}

static const u32 iris_drone_brake_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0xFFF98000u };
static u32 test_iris_drone_brake(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.y_vel.val = -1048576;
    iris_drone_brake(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk28;
    observed_values[2] = (u32)obj.unk2C;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk61;
    observed_values[5] = (u32)obj.x_vel.val;
    observed_values[6] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, iris_drone_brake_expected, 7);
}

static const u32 iris_drone_burst_expected[] = { 0u };
static u32 test_iris_drone_burst(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    iris_drone_burst(&obj);
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, iris_drone_burst_expected, 1);
}

static const u32 iris_drone_explode_0_expected[] = { 0xFF0002u };
static u32 test_iris_drone_explode_0(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj, before;
    u8 marker[] = { 1, 2, 3, 4 };
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk50.data = marker;
    obj.animation_step.fields.event = 1;
    before = obj;
    iris_drone_explode(&obj);
    before.state = 2;
    before.animation_step.fields.duration = -1;
    c_test_same_words(&obj, &before, sizeof(obj));
    assert(marker[0] == 1 && marker[1] == 2 && marker[2] == 3 && marker[3] == 4);
    observed_values[0] = (u8)obj.state | ((obj.unk50.data == iris_drone_explode_box ? 1u : 0u) << 8) | ((u32)(u8)obj.animation_step.fields.duration << 16);
    return c_test_observe(0, row, observed_values, iris_drone_explode_0_expected, 1);
}
static const u32 iris_drone_explode_1_expected[] = { 0xFF0101u };
static u32 test_iris_drone_explode_1(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj, before;
    u8 marker[] = { 1, 2, 3, 4 };
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk50.data = marker;
    obj.animation_step.fields.event = 2;
    before = obj;
    iris_drone_explode(&obj);
    before.unk50.data = iris_drone_explode_box;
    before.animation_step.fields.duration = -1;
    c_test_same_words(&obj, &before, sizeof(obj));
    assert(marker[0] == 1 && marker[1] == 2 && marker[2] == 3 && marker[3] == 4);
    observed_values[0] = (u8)obj.state | ((obj.unk50.data == iris_drone_explode_box ? 1u : 0u) << 8) | ((u32)(u8)obj.animation_step.fields.duration << 16);
    return c_test_observe(1, row, observed_values, iris_drone_explode_1_expected, 1);
}
static u32 test_iris_drone_explode(u32 index)
{
    if (index < 1)
        return test_iris_drone_explode_0(index);
    index -= 1;
    return test_iris_drone_explode_1(index);
}

void iris_drone_run(struct ShotObj*);
void iris_laser_init(struct ShotObj*);
void iris_laser_run(struct ShotObj*);
void iris_pillar_run(struct ShotObj*);
extern void* iris_animations[37];
static struct VisualObj visuals_before[32];
static struct WeaponObj weapons_before[16];
static u32 owner_death(u32 row)
{
    struct MainObj owner, owner_expected;
    struct ShotObj obj, expected;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct PlayerObj player_before;
    u32 kind = row % 4, dead = row / 4 % 2, face = row / 8, i;
    engine_obj.stage = 11;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_ZERO;
    engine_before = engine_obj;
    background_objects[0].x_pos.val = 2144 << 16;
    background_objects[0].y_pos.val = 266 << 16;
    background_before = background_objects[0];
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.unk2 = CHARACTER_ZERO;
    g_Player.animation_table = (u32**)D_8011AFF0;
    g_Player.state = 1;
    g_Player.hp = 24;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    g_Player.x_pos.i.hi = g_Player.y_pos.i.hi = 1000;
    g_Player.spike_immune = 1;
    g_Player.invincibility_timer = 17;
    player_before = g_Player;
    cur_random = 119;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 66;
    owner.state = 1;
    owner.hp = 48;
    owner.unk15 = face ? 0x40 : 0;
    owner.unk2 = kind == 3;
    owner.x_pos.i.hi = 2304;
    owner.y_pos.i.hi = 446;
    owner.animation_table = (const u8* const*)iris_animations;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.unk2 = kind == 2;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.animation_table = (u32**)iris_animations;
    obj.x_pos.val = owner.x_pos.val;
    obj.y_pos.val = owner.y_pos.val;
    obj.unk84.value = 8;
    if (kind == 0)
        func_800A7008(&obj);
    else if (kind < 3)
        iris_laser_init(&obj);
    else
        func_800A73C4(&obj);
    assert(obj.unk5 == 0 && obj.timer == (kind == 0 ? 16 : kind < 3 ? 60
                                                                    : 120)
        && obj.animation_step.packed == (kind == 0 ? 0x41010003 : kind == 1 ? 0x7C010001
                   : kind == 2                                              ? 0x8A010001
                                                                            : 0xBB010002));
    owner.state = dead ? 2 : 1;
    owner_expected = owner;
    expected = obj;
    expected.unk18.val = obj.x_pos.val;
    expected.unk1C.val = obj.y_pos.val;
    expected.timer--;
    expected.animation_step.packed = kind == 0 ? 0x41010002 : kind == 1 ? 0x7D010001
        : kind == 2                                                     ? 0x89010001
                                                                        : 0xBB010001;
    if (kind == 0) {
        assert(obj.x_vel.val == 0 && obj.y_vel.val == 0x50000);
        expected.y_pos.val -= 0x50000;
    } else if (kind < 3)
        expected.animation_cursor++;
    if (dead)
        expected.state = kind == 0 ? 2 : kind < 3 ? 5
                                                  : 8;
    if (kind == 0)
        iris_drone_run(&obj);
    else if (kind < 3)
        iris_laser_run(&obj);
    else
        iris_pillar_run(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    assert(cur_random == (kind == 0 && dead ? 376 : 119));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "iris_drone_animation_context", NULL, iris_drone_animation_context_cases_expected, COUNT(iris_drone_animation_context_cases_expected), iris_drone_animation_context_cases_row },
    { "iris_drone_brake", 0, 0, 1, test_iris_drone_brake },
    { "iris_drone_burst", 0, 0, 1, test_iris_drone_burst },
    { "iris_drone_explode", 0, 0, 2, test_iris_drone_explode },
    { "own_Iris_drone_both_lasers_pillar_cleanup_after_owner_death", NULL, NULL, 16, owner_death },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(iris_drone_animation_context_cases_expected) + 1 + 1 + 2 + 16;
