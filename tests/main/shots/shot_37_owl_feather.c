#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_37_owl_feather.h"
extern u16 owl_feather_velocities[11][2];

static struct MainObj feather_owner;
#define ss state_room.shot
#define FEATHER(st, kind) (state_reset(0, 0, 0), memset(&feather_owner, 0, sizeof(feather_owner)), feather_owner.active = 1, feather_owner.x_pos.i.hi = 0x100, feather_owner.y_pos.i.hi = 0x80, ss.active = 1, ss.state = st, ss.unk2 = kind, ss.unk7C = (struct WeaponObj*)&feather_owner, ss.x_pos.i.hi = 0x100, ss.y_pos.i.hi = 0x80, background_objects[0].x_pos.i.hi = 0xC0, background_objects[0].y_pos.i.hi = 0x40, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0xA0, cur_random = 0x1234)
#define SEEN() (state_extra = ss.unk84.value | feather_owner.ext.main_60.feather_mask << 8 | (u32)ss.unk8C.word << 24)
static void of_init_aim(void)
{
    FEATHER(0, 0);
    owl_feather_update(&ss);
    SEEN();
}
static void of_init_aim_right(void)
{
    FEATHER(0, 0);
    feather_owner.unk15 = 0x40;
    owl_feather_update(&ss);
    SEEN();
}
static void of_init_nearest(void)
{
    FEATHER(0, 1);
    owl_feather_update(&ss);
    SEEN();
}
static void of_init_scatter(void)
{
    FEATHER(0, 2);
    feather_owner.ext.main_60.feather_mask = 0x3F0;
    owl_feather_update(&ss);
    SEEN();
}
static void of_init_storm(void)
{
    FEATHER(0, 5);
    feather_owner.ext.main_60.storm_timer = 3;
    owl_feather_update(&ss);
    SEEN();
}
static void of_init_storm_b(void)
{
    FEATHER(0, 7);
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_hold(void)
{
    FEATHER(1, 1);
    ss.unk84.value = 2;
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_arrived(void)
{
    FEATHER(1, 1);
    ss.unk84.value = 0;
    ss.x_pos.i.hi = background_objects[0].x_pos.i.hi + owl_feather_velocities[0][0];
    ss.y_pos.i.hi = background_objects[0].y_pos.i.hi + owl_feather_velocities[0][1];
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_release(void)
{
    FEATHER(1, 2);
    feather_owner.ext.main_60.feathers_holding = 1;
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_released(void)
{
    FEATHER(1, 2);
    feather_owner.ext.main_60.feathers_holding = 1;
    ss.unk8C.word = 1;
    ss.x_vel.val = 0x10000;
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_aimed(void)
{
    FEATHER(1, 0);
    ss.x_vel.val = 0x10000;
    owl_feather_update(&ss);
    SEEN();
}
static void of_fly_owner_gone(void)
{
    FEATHER(1, 0);
    feather_owner.state = 2;
    owl_feather_update(&ss);
}
static void of_fly_owner_dead(void)
{
    FEATHER(1, 0);
    feather_owner.active = 0;
    owl_feather_update(&ss);
}
static void of_fly_away(void)
{
    FEATHER(1, 0);
    ss.x_pos.i.hi = 0x1000;
    owl_feather_update(&ss);
}
static void of_despawn_held(void)
{
    FEATHER(2, 3);
    ss.unk84.value = 4;
    feather_owner.ext.main_60.feather_mask = 0x31;
    owl_feather_update(&ss);
    SEEN();
}
static void of_despawn_aimed(void)
{
    FEATHER(2, 0);
    feather_owner.ext.main_60.feather_mask = 0x31;
    owl_feather_update(&ss);
    SEEN();
}

static void (*const owl_feather_states_cases[])(void) = {
    of_init_aim,
    of_init_aim_right,
    of_init_nearest,
    of_init_scatter,
    of_init_storm,
    of_init_storm_b,
    of_fly_hold,
    of_fly_arrived,
    of_fly_release,
    of_fly_released,
    of_fly_aimed,
    of_fly_owner_gone,
    of_fly_owner_dead,
    of_fly_away,
    of_despawn_held,
    of_despawn_aimed,
};
static const u32 owl_feather_states_expected[] = { 1u, 0xFF000001u, 0xDA0000u, 0x860000u, 0xFFFC13B0u, 0xFFFF383Cu, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000001u, 0x1260000u, 0x860000u, 0xFFFC13B0u, 0xFFFF383Cu, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000101u, 0xDA0000u, 0x860000u, 0x1A9B6u, 0xFFFEE38Eu, 0u, 0x50000u, 0x1004u, 0u, 1u, 0xFF000201u, 0xDA0000u, 0x860000u, 0x1F628u, 0x63E2u, 0u, 0x50000u, 0x3F402u, 0u, 1u, 0xFF000501u, 0x1000000u, 0x800000u, 0x18F88u, 0x7D8A0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000701u, 0x1000000u, 0x800000u, 0xFFFA57D8u, 0xFFFA57D8u, 0u, 0x50000u, 0u, 0u, 1u, 0x101u, 0x1000000u, 0x800000u, 0x1F628u, 0x63E2u, 0u, 0x40000u, 2u, 0u, 1u, 0x101u, 0x1030000u, 0x680000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x201u, 0x1000000u, 0x800000u, 0xFFFB189Cu, 0xFFFF064Bu, 0u, 0x40000u, 0x1000000u, 0u, 1u, 0x201u, 0x1010000u, 0x800000u, 0x10000u, 0u, 0u, 0x40000u, 0x1000000u, 0u, 1u, 1u, 0x1010000u, 0x800000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x1000000u, 0x800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x1000000u, 0x800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x10000000u, 0x800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x1000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2104u, 0u, 0u, 0u, 0x1000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x3100u, 0u };

static u32 test_owl_feather_states(u32 row)
{
    return object_run(owl_feather_states_cases[row], row, &owl_feather_states_expected[row * 10]);
}

void storm_owl_spawn_volley_feather(struct MainObj*, s8);
void owl_feather_update(struct ShotObj*);
extern void* storm_owl_animations[];
static struct ShotObj expected[32];
static struct WeaponObj weapons[16];
static u32 frames[32];
static u32 storm_cleanup(u32 row)
{
    struct MainObj owner, before;
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u16 rng;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    owner.active = 0x41;
    owner.id = 60;
    owner.state = 1;
    owner.x_pos.i.hi = 160;
    owner.y_pos.i.hi = 120;
    owner.animation_table = (const u8* const*)storm_owl_animations;
    frames[0] = 64;
    owner.sprite_frames = (u8*)frames;
    owner.unk42 = 0x7804;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = g_Player.y_pos.i.hi = -512;
    storm_owl_spawn_volley_feather(&owner, 5);
    assert(shot_objects[0].active == 0x41 && shot_objects[0].id == 37 && shot_objects[0].unk2 == 5 && shot_objects[0].state == 0);
    owl_feather_update(&shot_objects[0]);
    assert(shot_objects[0].state == 1 && shot_objects[0].animation_step.packed == 0x3E010001 && shot_objects[0].x_vel.val == 370728 && shot_objects[0].y_vel.val == 370728 && owner.ext.main_60.feather_mask == 0);
    background_objects[0].x_pos.i.hi = 1000;
    owl_feather_update(&shot_objects[0]);
    assert(shot_objects[0].state == 2 && shot_objects[0].x_pos.val == 160 * 65536 + 370728 && shot_objects[0].y_pos.val == 120 * 65536 - 370728);
    c_test_copy_words((u32*)expected, (u32*)shot_objects, sizeof(expected) / 4);
    c_test_zero_words((u32*)&expected[0], 2);
    before = owner;
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    owl_feather_update(&shot_objects[0]);
    assert(c_test_word_difference((u32*)shot_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0);
    assert(c_test_word_difference((u32*)&owner, (u32*)&before, sizeof(owner) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i == 0 ? 64u : 0));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "owl_feather_states", 0, 0, COUNT(owl_feather_states_cases), test_owl_feather_states },
    { "supported_storm_feather5_real_spawner_init_flight_and_cleanup", NULL, NULL, 1, storm_cleanup },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(owl_feather_states_cases) + 1;
