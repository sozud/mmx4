#include "test_runtime.h"
#include "main/mains/main_04_drill_copter.h"
#include "main/55C4.h"
#include "main/weapons/weapon_00_lemon.h"
void drill_copter_despawn(struct MainObj*);
void drill_copter_sway_move(struct MainObj*);
void drill_copter_approach(struct MainObj* arg0);
void drill_copter_drop(struct MainObj* arg0);
void drill_copter_fire(struct MainObj* arg0);
void drill_copter_rise(struct MainObj* arg0);
void drill_copter_sway(struct MainObj* arg0);
extern union AnimationStep* drill_copter_animations[15];
extern struct Unk_unk68 D_801064F0[];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void func_80044DE4(struct MainObj*);
extern struct Unk_unk68 D_800F9EBC;

static const u32 drill_copter_fire_shots_expected[] = { 0x38010001u, 3u, 2u, 1u };
static u32 test_drill_copter_fire_shots(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct ShotObj shots_before[32];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    set_animation(&obj, 7);
    obj.animation_cursor = &drill_copter_animations[7][5];
    obj.animation_step = drill_copter_animations[7][5];
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.unk7E = 3;
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    expected = obj;
    expected.animation_step.fields.duration = 1;
    expected.animation_step.fields.event = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_fire_shots(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.animation_step.packed;
    observed_values[1] = (u32)obj.unk7E;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[31].active;
    return c_test_observe(0, row, observed_values, drill_copter_fire_shots_expected, 4);
}

struct func_80044508_case {
    u32 unk2;
    u32 expected[6];
};
static const struct func_80044508_case func_80044508_cases[] = {
    { 0, { 2u, 0u, 0u, 0x9234u, 0x630063u, 0xA30Du } },
    { 2, { 2u, 0u, 2u, 0x9234u, 0x630063u, 0x366Au } },
};
static u32 test_func_80044508(u32 row)
{
    const struct func_80044508_case* c = &func_80044508_cases[row];
    u32 observed_values[6];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct WeaponObj weapons_expected[16];
    struct ShotObj shots_before[32];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct ItemObj items_before[32];
    u8 pools_full, fatal;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    D_8013E198[0] = -1;
    D_8013E198[1] = -1;
    D_8013E198[2] = -1;
    D_8013E198[3] = -1;
    D_8013E198[4] = -1;
    D_8013E198[5] = -1;
    g_Player.bg_offset = 0;
    g_Player.x_pos.val = 0;
    g_Player.y_pos.val = 0;
    g_Player.spike_immune = 1;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    cur_random = 0x1234;
    func_80044458(&obj);
    obj.unk5 = 1;
    obj.unk2 = c->unk2;
    obj.hp = 3;
    fatal = 1;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 0;
    weapon_objects[0].unk50 = (const u8*)lemon_hit_box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.hp = 0;
    expected.unk42 = 0x9234;
    expected.on_screen = 1;
    if (fatal) {
        expected.state = 2;
    }
    if (fatal) {
        expected.on_screen = 0;
    }
    player_before = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    weapons_expected[0].unk98 = 1;
    weapons_expected[0].unk80.word = 0x00630063;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(items_before, item_objects, sizeof(items_before));
    assert(((const u8*)D_801064F0)[1] == 3);
    func_80044508(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_before));
    c_test_same_words(item_objects, items_before, sizeof(items_before));
    assert(D_8013E198[0] == -1 && D_8013E198[1] == -1 && D_8013E198[2] == -1 && D_8013E198[3] == -1 && D_8013E198[4] == -1 && D_8013E198[5] == -1);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.hp;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)weapon_objects[0].unk80.word;
    observed_values[5] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

static const u32 func_80044DE4_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80044DE4(u32 row)
{
    u32 observed_values[27];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800F9EBC, 0, sizeof(D_800F9EBC));
    memset(&main_objects, 0, sizeof(main_objects));
    obj.unk7C = 1;
    FILL_ACTIVE(main_objects, 48, 255 ? 1 : 0);
    func_80044DE4(&obj);
    observed_values[0] = (u32)main_objects[0].active;
    observed_values[1] = (u32)main_objects[0].air_state;
    observed_values[2] = (u32)main_objects[0].bg_offset;
    observed_values[3] = (u32)main_objects[0].contact_damage;
    observed_values[4] = (u32)main_objects[0].gravity;
    observed_values[5] = (u32)main_objects[0].hp;
    observed_values[6] = (u32)main_objects[0].id;
    observed_values[7] = (u32)main_objects[0].on_screen;
    observed_values[8] = (u32)main_objects[0].state;
    observed_values[9] = (u32)main_objects[0].unk15;
    observed_values[10] = (u32)main_objects[0].unk16;
    observed_values[11] = (u32)main_objects[0].unk18.val;
    observed_values[12] = (u32)main_objects[0].unk1C.val;
    observed_values[13] = (u32)main_objects[0].unk2;
    observed_values[14] = (u32)main_objects[0].unk40;
    observed_values[15] = (u32)main_objects[0].unk42;
    observed_values[16] = (u32)main_objects[0].unk5;
    observed_values[17] = (u32)main_objects[0].x_accel;
    observed_values[18] = (u32)main_objects[0].x_pos.val;
    observed_values[19] = (u32)main_objects[0].x_speed;
    observed_values[20] = (u32)main_objects[0].y_pos.val;
    observed_values[21] = (u32)main_objects[0].y_speed;
    observed_values[22] = (u32)obj.unk2;
    observed_values[23] = (u32)obj.unk5;
    observed_values[24] = (u32)obj.unk6;
    observed_values[25] = (u32)obj.unk7C;
    observed_values[26] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, func_80044DE4_expected, 27);
}

#include "support/state_cases.h"

#define DC(a, b) state_reset(a, b, 0)
static void dc_update_noop(void)
{
    DC(0, 0);
    so.state = 3;
    drill_copter_update(&so);
}
static void dc_approach_left(void)
{
    DC(1, 0);
    drill_copter_approach(&so);
}
static void dc_approach_right(void)
{
    DC(1, 0);
    so.unk15 = 0x40;
    drill_copter_approach(&so);
}
static void dc_approach_far(void)
{
    DC(1, 1);
    so.x_pos.val = 0x100000;
    drill_copter_approach(&so);
}
static void dc_approach_near(void)
{
    DC(1, 1);
    drill_copter_approach(&so);
}
static void dc_sway_start(void)
{
    DC(2, 0);
    drill_copter_sway(&so);
}
static void dc_sway_turn(void)
{
    DC(2, 1);
    so.x_pos.val = 0x500000;
    so.x_speed = 0x10000;
    drill_copter_sway(&so);
}
static void dc_sway_near(void)
{
    DC(2, 1);
    so.x_speed = 0x10000;
    so.unk15 = 0x40;
    drill_copter_sway(&so);
}
static void dc_drop_start(void)
{
    DC(3, 0);
    drill_copter_drop(&so);
}
static void dc_drop_wait_done(void)
{
    DC(3, 1);
    so.unk7C = 1;
    drill_copter_drop(&so);
}
static void dc_drop_wait(void)
{
    DC(3, 1);
    so.unk7C = 2;
    drill_copter_drop(&so);
}
static void dc_drop_fall_land(void)
{
    DC(3, 2);
    so.collision_flags = 8;
    drill_copter_drop(&so);
}
static void dc_drop_fall(void)
{
    DC(3, 2);
    so.gravity = 0x3000;
    drill_copter_drop(&so);
}
static void dc_drop_land_done(void)
{
    DC(3, 3);
    drill_copter_drop(&so);
}
static void dc_drop_land(void)
{
    DC(3, 3);
    so.animation_step.fields.relative_step = 1;
    drill_copter_drop(&so);
}
static void dc_rise_start(void)
{
    DC(4, 0);
    drill_copter_rise(&so);
}
static void dc_rise_wait_done(void)
{
    DC(4, 1);
    so.unk7C = 1;
    drill_copter_rise(&so);
}
static void dc_rise_wait(void)
{
    DC(4, 1);
    so.unk7C = 2;
    drill_copter_rise(&so);
}
static void dc_rise_fly(void)
{
    DC(4, 2);
    so.y_speed = 0x30000;
    drill_copter_rise(&so);
}
static void dc_fire_start(void)
{
    DC(5, 0);
    drill_copter_fire(&so);
}
static void dc_fire_wait_done(void)
{
    DC(5, 1);
    so.unk7C = 1;
    drill_copter_fire(&so);
}
static void dc_fire_wait(void)
{
    DC(5, 1);
    so.unk7C = 2;
    drill_copter_fire(&so);
}
static void dc_fire_shots_again(void)
{
    DC(5, 2);
    so.animation_step.fields.event = 1;
    so.unk7E = 2;
    so.x_pos.val = 0x340000;
    drill_copter_fire(&so);
}
static void dc_fire_shots_done(void)
{
    DC(5, 2);
    so.unk7E = 1;
    drill_copter_fire(&so);
}
static void dc_fire_shots_wait(void)
{
    DC(5, 2);
    so.animation_step.fields.relative_step = 1;
    drill_copter_fire(&so);
}
static void dc_fire_reload_done(void)
{
    DC(5, 3);
    so.unk7C = 1;
    drill_copter_fire(&so);
}
static void dc_fire_reload(void)
{
    DC(5, 3);
    so.unk7C = 2;
    drill_copter_fire(&so);
}
static void dc_despawn_clone(void)
{
    DC(0, 0);
    so.active = 1;
    so.unk2 = 2;
    drill_copter_despawn(&so);
}
static void dc_clone(void)
{
    DC(0, 0);
    main_objects[0x2F].active = 0;
    so.unk7C = 1;
    so.id = 4;
    func_80044DE4(&so);
}
static void dc_clone_wait(void)
{
    DC(0, 0);
    so.unk7C = 2;
    func_80044DE4(&so);
}
static void dc_main_child(void)
{
    DC(4, 2);
    so.state = 1;
    so.unk2 = 1;
    so.x_pos.i.hi = 0x80;
    so.y_pos.i.hi = 0x60;
    func_80044508(&so);
}
static void dc_main_parent(void)
{
    DC(4, 2);
    so.state = 1;
    so.unk7C = 2;
    so.x_pos.i.hi = 0x80;
    so.y_pos.i.hi = 0x60;
    func_80044508(&so);
}
static void dc_main_away(void)
{
    DC(4, 2);
    so.state = 1;
    so.unk2 = 1;
    so.x_pos.i.hi = 0x400;
    func_80044508(&so);
}

static void (*const drill_copter_states_cases[])(void) = {
    dc_update_noop,
    dc_approach_left,
    dc_approach_right,
    dc_approach_far,
    dc_approach_near,
    dc_sway_start,
    dc_sway_turn,
    dc_sway_near,
    dc_drop_start,
    dc_drop_wait_done,
    dc_drop_wait,
    dc_drop_fall_land,
    dc_drop_fall,
    dc_drop_land_done,
    dc_drop_land,
    dc_rise_start,
    dc_rise_wait_done,
    dc_rise_wait,
    dc_rise_fly,
    dc_fire_start,
    dc_fire_wait_done,
    dc_fire_wait,
    dc_fire_shots_again,
    dc_fire_shots_done,
    dc_fire_shots_wait,
    dc_fire_reload_done,
    dc_fire_reload,
    dc_despawn_clone,
    dc_clone,
    dc_clone_wait,
    dc_main_child,
    dc_main_parent,
    dc_main_away,
};
static const u32 drill_copter_states_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0u, 0u, 0xFFFE0000u, 0u, 0u, 2u, 0u, 0u, 0u, 0x101u, 0u, 0u, 0x20000u, 0u, 0u, 0x4002u, 0u, 0u, 0u, 0x101u, 0u, 0x100000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 1u, 0u, 0x510000u, 0xFFFF0000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x102u, 0u, 0x10000u, 0x10000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0xFF000103u, 0x1Eu, 0u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 0x203u, 0u, 0u, 0u, 0u, 0x300000u, 0u, 0u, 0u, 0u, 0x103u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x303u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0x203u, 0u, 0u, 0u, 0xFFFFD000u, 0x300000u, 0u, 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x303u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0x3Cu, 0u, 0u, 0u, 0u, 8u, 0u, 0u, 0u, 0x204u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0x104u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0x105u, 0x28u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0x30000u, 0u, 0u, 0u, 0u, 7u, 0u, 0u, 0u, 0x105u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0x10000u, 0x340000u, 0u, 0u, 0u, 7u, 0u, 0u, 0x410000u, 0x305u, 0x5Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0x30000u, 0u, 0u, 0u, 0u, 7u, 0u, 0u, 0u, 0x305u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0u, 0x4000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_drill_copter_states(u32 row)
{
    return state_run(drill_copter_states_cases[row], row, &drill_copter_states_expected[row * 10]);
}

static u8 copter_record;
#define SWAY(x, speed) (state_reset(3, 1, 0), so.x_pos.i.hi = x, so.y_pos.i.hi = 0x60, so.x_speed = speed, g_Player.x_pos.i.hi = 0x80, drill_copter_sway_move(&so))
static void dcs_sway(void)
{
    SWAY(0x90, 0x10000);
}
static void dcs_sway_turn(void) { SWAY(0xD0, 0x10000); }
static void dcs_sway_leave(void) { SWAY(0xD0, -0x10000); }
static void dcs_sway_left(void) { SWAY(0x30, -0x10000); }
static void dcs_sway_left_near(void) { SWAY(0x70, -0x10000); }
static void dcs_despawn_child(void)
{
    state_reset(6, 0, 0);
    so.unk2 = 2;
    so.active = 1;
    drill_copter_despawn(&so);
}
static void dcs_despawn(void)
{
    state_reset(6, 0, 0);
    copter_record = 0;
    so.backref = (void*)&copter_record;
    so.active = 1;
    drill_copter_despawn(&so);
    state_extra = copter_record;
    so.backref = NULL;
}

static void (*const drill_copter_sway_cases[])(void) = {
    dcs_sway,
    dcs_sway_turn,
    dcs_sway_leave,
    dcs_sway_left,
    dcs_sway_left_near,
    dcs_despawn_child,
    dcs_despawn,
};
static const u32 drill_copter_sway_expected[] = { 0x103u, 0u, 0x910000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0xD10000u, 0xFFFF0000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 1u, 0u, 0xCF0000u, 0x10000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 1u, 0u, 0x2F0000u, 0x10000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x103u, 0u, 0x6F0000u, 0xFFFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_drill_copter_sway(u32 row)
{
    return state_run(drill_copter_sway_cases[row], row, &drill_copter_sway_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "drill_copter_sway", 0, 0, COUNT(drill_copter_sway_cases), test_drill_copter_sway },
    { "drill_copter_states", 0, 0, COUNT(drill_copter_states_cases), test_drill_copter_states },
    { "drill_copter_fire_shots", 0, 0, 1, test_drill_copter_fire_shots },
    { "func_80044508", 0, 0, 2, test_func_80044508 },
    { "func_80044DE4", 0, 0, 1, test_func_80044DE4 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(drill_copter_sway_cases) + COUNT(drill_copter_states_cases) + 1 + 2 + 1;
