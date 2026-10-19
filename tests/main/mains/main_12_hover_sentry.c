#include "test_runtime.h"
#include "main/mains/main_12_hover_sentry.h"
#include "main/mains/main_23_slope_skier.h"
#include "main/55C4.h"
#include "main/195B4.h"
void hover_sentry_check_player_near(struct MainObj*);
extern union AnimationStep* hover_sentry_animations[];
extern struct Unk_unk68 D_800FB684;
extern struct Unk_unk68 D_800FB688;
extern struct Unk_unk68 D_800FB68C;
extern struct Unk_unk68 D_800FB690;

static const s16 distances[4] = { 31, 32, -31, -32 };
static u32 height_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 12;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.unk7 = 7;
    obj.unk15 = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_accel = 0x2000;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)hover_sentry_animations;
    set_animation(&obj, 0);
    g_Player.x_pos.val = 101 * 65536 + 0x1234;
    g_Player.y_pos.i.hi = 200 - distances[mode];
    player_before = g_Player;
    cur_random = 1;
    expected = obj;
    expected.unk6 = 0;
    expected.unk15 = mode & 1 ? 0 : 0x40;
    expected.x_speed = mode & 1 ? -0x2000 : 0x2000;
    expected.y_speed = -0x1000;
    expected.animation_step.fields.duration = 9;
    func_8004C394(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 1 && hover_sentry_animations[0][0].packed == 0x0001000A);
    actual = (u8)obj.unk6 | ((u32)obj.unk15 << 8) | ((u32)(u16)(obj.x_speed / 0x2000) << 16);
    return actual;
}
static const u32 hover_sentry_player_height_cases_expected[] = { 0x14000u, 0xFFFF0000u, 0x14000u, 0xFFFF0000u };

static const u32 func_8004C394_expected[] = { 1u, 0u, 0x40u, 4u, 0u, 0u, 0u, 1u, 0u, 0xFFFFFFFFu, 0u };
static u32 test_func_8004C394(u32 row)
{
    u32 observed_values[11];
    struct MainObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_800FB684, 0, sizeof(D_800FB684));
    memset(&D_800FB688, 0, sizeof(D_800FB688));
    memset(&D_800FB68C, 0, sizeof(D_800FB68C));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.unk6 = -1;
    obj.unk15 = 64;
    obj.x_speed = -1;
    g_Player.y_pos.i.hi = 65;
    obj.x_pos.val = -1;
    obj.collision_flags = 2;
    SP_CUR_MAIN_OBJ = &child_0;
    func_8004C394(&obj);
    observed_values[0] = (u32)child_0.ext.main_12.unk81;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk7;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.unk7E;
    observed_values[8] = (u32)obj.x_accel;
    observed_values[9] = (u32)obj.x_speed;
    observed_values[10] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_8004C394_expected, 11);
}

#include "support/pool_full.h"
static u32 pool_full_hover_sentry_idle(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk6 = 4;
    pf_snapshot();
    func_8004C210(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_hover_sentry_idle,
};
static const u32 pool_full_cases_expected[] = { 0x50400u };

#include "support/signed_init_defaults.h"
DEFAULTS_CASE(0, 0)
DEFAULTS_CASE(1, 0)
DEFAULTS_CASE(2, 0)
static const CTestCase hover_sentry_signed_init_defaults_cases[] = { DEFAULTS_ENTRY(0, 0) DEFAULTS_ENTRY(1, 0) DEFAULTS_ENTRY(2, 0) };

static const u32 hover_sentry_signed_init_defaults_cases_expected[] = { 0x9080001u, 0x9080001u, 0x9080001u };
#include "support/state_cases.h"

static struct Unk_unk68 sentry_feet = { 0, 0, 8, 8 };
#define HS(step, phase) (state_reset(step, phase, 0), SP_CUR_MAIN_OBJ = &so, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
#define SENTRY() (state_extra = so.ext.main_12.unk8A | so.ext.main_12.unk81 << 8 | (u32)(u16)so.unk7C << 16)
static void hs_init_hover(void)
{
    HS(0, 0);
    g_Player.x_pos.i.hi = 0x100;
    func_8004B8FC(&so);
    SENTRY();
}
static void hs_init_drop(void)
{
    HS(0, 0);
    so.unk2 = 1;
    func_8004B8FC(&so);
    SENTRY();
}
static void hs_init_lift(void)
{
    HS(0, 0);
    so.unk2 = 2;
    func_8004B8FC(&so);
    SENTRY();
}
static void hs_drop_release(void)
{
    HS(6, 0);
    so.ext.main_12.unk86 = 0x80;
    func_8004C210(&so);
    SENTRY();
}
static void hs_drop_hold(void)
{
    HS(6, 0);
    so.ext.main_12.unk86 = 0x60;
    so.y_speed = 0x4000;
    func_8004C210(&so);
    SENTRY();
}
static void hs_drop_unfold(void)
{
    HS(6, 1);
    so.animation_step.fields.event = -1;
    func_8004C210(&so);
}
static void hs_drop_falling(void)
{
    HS(6, 1);
    so.y_speed = 0x10000;
    func_8004C210(&so);
}
static void hs_drop_ready(void)
{
    HS(6, 2);
    so.unk7C = 1;
    func_8004C210(&so);
    SENTRY();
}
static void hs_drop_wait(void)
{
    HS(6, 2);
    so.unk7C = 2;
    func_8004C210(&so);
    SENTRY();
}
static void hs_dash_left(void)
{
    HS(7, 0);
    func_8004C394(&so);
}
static void hs_dash_right(void)
{
    HS(7, 0);
    so.unk15 = 0x40;
    func_8004C394(&so);
}
static void hs_dash_turn_a(void)
{
    HS(7, 1);
    so.unk15 = 0x40;
    so.x_speed = -1;
    g_Player.x_pos.i.hi = 0x100;
    g_Player.y_pos.i.hi = 0x60;
    cur_random = 1;
    func_8004C394(&so);
    SENTRY();
}
static void hs_dash_turn_b(void)
{
    HS(7, 1);
    so.x_speed = 1;
    cur_random = 4;
    func_8004C394(&so);
    SENTRY();
}
static void hs_dash_turn_c(void)
{
    HS(7, 1);
    so.x_speed = 1;
    cur_random = 8;
    func_8004C394(&so);
    SENTRY();
}
static void hs_dash_wall_right(void)
{
    HS(7, 1);
    so.unk15 = 0x40;
    so.x_speed = 0x10000;
    so.collision_flags = 1;
    func_8004C394(&so);
}
static void hs_dash_wall_left(void)
{
    HS(7, 1);
    so.x_speed = -0x10000;
    so.collision_flags = 2;
    func_8004C394(&so);
}
static void hs_sink_splash(void)
{
    HS(8, 0);
    so.terrain_box = &sentry_feet;
    state_terrain(0x24);
    func_8004C56C(&so);
}
static void hs_sink_air(void)
{
    HS(8, 0);
    so.terrain_box = &sentry_feet;
    so.y_pos.i.hi = -0x200;
    func_8004C56C(&so);
}
static void hs_sink_land(void)
{
    HS(8, 0);
    so.terrain_box = &sentry_feet;
    so.y_pos.i.hi = -0x200;
    so.collision_flags = 8;
    func_8004C56C(&so);
}
static void hs_sink_done(void)
{
    HS(8, 1);
    func_8004C56C(&so);
}
static void hs_near_busy(void)
{
    HS(3, 0);
    so.unk7C = 1;
    hover_sentry_check_player_near(&so);
}

static void (*const hover_sentry_states_cases[])(void) = {
    hs_init_hover,
    hs_init_drop,
    hs_init_lift,
    hs_drop_release,
    hs_drop_hold,
    hs_drop_unfold,
    hs_drop_falling,
    hs_drop_ready,
    hs_drop_wait,
    hs_dash_left,
    hs_dash_right,
    hs_dash_turn_a,
    hs_dash_turn_b,
    hs_dash_turn_c,
    hs_dash_wall_right,
    hs_dash_wall_left,
    hs_sink_splash,
    hs_sink_air,
    hs_sink_land,
    hs_sink_done,
    hs_near_busy,
};
static const u32 hover_sentry_states_expected[] = { 0x201u, 0xFF400000u, 0x800000u, 0x600000u, 0u, 0xFFFF8000u, 0xFFF80000u, 0xA0000u, 0x900000u, 0u, 0x601u, 0xFF000100u, 0x800000u, 0x600000u, 0u, 0x4000u, 0u, 0x60000u, 0x900000u, 0u, 0x401u, 0xFF000200u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x10000u, 0x900000u, 0u, 0x10600u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0x40000u, 0u, 0x40000u, 0x50001u, 0u, 0x600u, 0u, 0x800000u, 0x5FC000u, 0u, 0x4000u, 0u, 0x40000u, 0u, 0u, 0x20600u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10600u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0u, 0u, 0x500u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20600u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u, 0x10700u, 0xFF000000u, 0x7C0000u, 0x600000u, 0xFFFC2000u, 0u, 0xFFFFE000u, 0x40000u, 0u, 0u, 0x10700u, 0xFF400000u, 0x840000u, 0x600000u, 0x3E000u, 0u, 0xFFFFE000u, 0x40000u, 0u, 0u, 0x700u, 0x400000u, 0x7FFFFFu, 0x600000u, 0xFFFFFFFFu, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0x800001u, 0x600000u, 1u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0x800001u, 0x600000u, 1u, 0u, 0u, 0x40000u, 0u, 0u, 0x10700u, 0u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10700u, 0x400000u, 0x7F0000u, 0x600000u, 0xFFFF0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000800u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 0x800u, 0u, 0x800000u, 0xFE000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0x800000u, 0xFE000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10800u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_hover_sentry_states(u32 row)
{
    return object_run(hover_sentry_states_cases[row], row, &hover_sentry_states_expected[row * 10]);
}

extern union AnimationStep* hover_sentry_animations[];
static const struct {
    s32 dx, dy, vx, vy;
    u8 facing;
} aims[] = {
    { -12582912, 0, 393216, 0, 64 },
    { -5242880, 1048576, 385656, 76710, 64 },
    { -2621440, 1048576, 363282, 150474, 64 },
    { -1572864, 1048576, 326946, 218454, 64 },
    { -1048576, 1048576, 278046, 278046, 64 },
    { -655360, 1048576, 278046, 278046, 64 },
    { -393216, 1048576, 278046, 278046, 64 },
    { -196608, 1048576, 278046, 278046, 64 },
    { 0, 1048576, -278046, 278046, 0 },
    { 196608, 1048576, -278046, 278046, 0 },
    { 393216, 1048576, -278046, 278046, 0 },
    { 655360, 1048576, -278046, 278046, 0 },
    { 1048576, 1048576, -278046, 278046, 0 },
    { 1572864, 1048576, -326946, 218454, 0 },
    { 2621440, 1048576, -363282, 150474, 0 },
    { 5242880, 1048576, -385656, 76710, 0 },
    { 12582912, 0, -393216, 0, 0 },
    { 5242880, -1048576, -385656, -76710, 0 },
    { 2621440, -1048576, -363282, -150474, 0 },
    { 1572864, -1048576, -326946, -218454, 0 },
    { 1048576, -1048576, -278046, -278046, 0 },
    { 655360, -1048576, -278046, -278046, 0 },
    { 393216, -1048576, -278046, -278046, 0 },
    { 196608, -1048576, -278046, -278046, 0 },
    { 0, -1048576, 278046, -278046, 64 },
    { -196608, -1048576, 278046, -278046, 64 },
    { -393216, -1048576, 278046, -278046, 64 },
    { -655360, -1048576, 278046, -278046, 64 },
    { -1048576, -1048576, 278046, -278046, 64 },
    { -1572864, -1048576, 326946, -218454, 64 },
    { -2621440, -1048576, 363282, -150474, 64 },
    { -5242880, -1048576, 385656, -76710, 64 },
};
static u32 launch_aim(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 aim = row % COUNT(aims), waiting = row / COUNT(aims) % 2, facing = row / COUNT(aims) / 2;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 12;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 3;
    obj.unk7E = waiting ? 2 : 1;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = -0x23456;
    obj.x_accel = 0x3456;
    obj.gravity = -0x4567;
    obj.ext.main_12.unk8C = 0x1234;
    obj.animation_table = (const u8* const*)hover_sentry_animations;
    set_animation(&obj, 7);
    g_Player.x_pos.val = obj.x_pos.val - aims[aim].dx;
    g_Player.y_pos.val = obj.y_pos.val - aims[aim].dy;
    player_before = g_Player;
    expected = obj;
    expected.unk7E--;
    if (!waiting) {
        expected.unk6 = 4;
        expected.ext.main_12.unk8C = 0;
        expected.unk15 = aims[aim].facing;
        expected.x_speed = aims[aim].vx;
        expected.y_speed = aims[aim].vy;
        expected.x_accel = expected.gravity = 0;
        expected.unk17 = 8;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)hover_sentry_animations[8];
        expected.animation_step.packed = 0x1C010002;
    }
    expected.animation_step.fields.duration = 1;
    SP_CUR_MAIN_OBJ = &obj;
    func_8004BF5C(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(hover_sentry_animations[7][0].packed == 0x19010002 && hover_sentry_animations[8][0].packed == 0x1C010002);
    return 1;
}

void hover_sentry_update(struct MainObj*);
void hover_sentry_check_player_near(struct MainObj*);
void func_8004C210(struct MainObj*);
extern struct Unk_unk68 D_800FB694, D_800FB698;
extern union AnimationStep* hover_sentry_animations[];
static struct StageObjectRecord records[2] = { { 0, 12, 1, 0, 160, 120 }, { 0, 0, 0, 255, 0, 0 } };
static struct MainObj expected[48];
static u32 timer_zero(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* previous = SP_CUR_MAIN_OBJ;
    u16 high, rng;
    u32 i, record_before[4];
    (void)row;
    c_test_copy_words(record_before, (u32*)records, COUNT(record_before));
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    engine_obj.checkpoint = 0;
    g_Player.bg_offset = 0;
    g_Player.x_pos.i.hi = 200;
    g_Player.y_pos.i.hi = 120;
    cur_random = 0x1234;
    func_800292D0(records);
    SP_CUR_MAIN_OBJ = &main_objects[0];
    hover_sentry_update(&main_objects[0]);
    assert(main_objects[0].state == 1 && main_objects[0].unk5 == 6 && main_objects[0].unk6 == 0 && main_objects[0].unk7C == 144 && main_objects[0].y_speed == 16384 && main_objects[0].animation_step.packed == 0x08010006);
    c_test_copy_words((u32*)expected, (u32*)main_objects, sizeof(expected) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    for (i = 0; i < 61; i++)
        func_8004C210(&main_objects[0]);
    assert(main_objects[0].unk6 == 1 && main_objects[0].unk7C == 5 && main_objects[0].y_pos.val == 104 * 65536 + 49152 && main_objects[0].animation_step.packed == 0x0E010005);
    for (i = 0; i < 26; i++)
        func_8004C210(&main_objects[0]);
    assert(main_objects[0].unk6 == 2 && main_objects[0].unk7C == 5 && main_objects[0].y_pos.val == 49152 && main_objects[0].animation_step.packed == 0x07010001);
    for (i = 0; i < 5; i++)
        func_8004C210(&main_objects[0]);
    rng = 0x1234;
    high = (u16)(rng * 3) >> 8;
    rng = ((rng + high) & 255) | (high << 8);
    expected[0].y_pos.val = -20 * 65536 + 49152;
    expected[0].y_speed = 4 * 65536;
    expected[0].unk5 = 5;
    expected[0].unk6 = 0;
    expected[0].unk7C = 0;
    expected[0].ext.main_12.unk8A = 1;
    expected[0].hurt_box = &D_800FB698;
    expected[0].attack_box = &D_800FB694;
    expected[0].unk17 = 10;
    expected[0].animation_cursor = (const u8*)hover_sentry_animations[10];
    expected[0].animation_step.packed = 0x0D010006;
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    hover_sentry_check_player_near(&main_objects[0]);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && SP_CUR_MAIN_OBJ == &main_objects[0]);
    SP_CUR_MAIN_OBJ = previous;
    assert(c_test_word_difference((u32*)records, record_before, COUNT(record_before)) == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "hover_sentry_states", 0, 0, COUNT(hover_sentry_states_cases), test_hover_sentry_states },
    { "hover_sentry_player_height", NULL, hover_sentry_player_height_cases_expected, COUNT(hover_sentry_player_height_cases_expected), height_case },
    { "func_8004C394", 0, 0, 1, test_func_8004C394 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "hover_sentry_signed_init_defaults", hover_sentry_signed_init_defaults_cases, hover_sentry_signed_init_defaults_cases_expected, COUNT(hover_sentry_signed_init_defaults_cases), 0 },
    { "all_compass_launch_clamps_and_countdown", NULL, NULL, COUNT(aims) + 1, launch_aim },
    { "supported_subtype1_constructor_92_own_steps_reach_timer_zero_guard", NULL, NULL, 1, timer_zero },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hover_sentry_states_cases) + COUNT(hover_sentry_player_height_cases_expected) + 1 + COUNT(pool_full_cases) + COUNT(hover_sentry_signed_init_defaults_cases) + COUNT(aims) + 1 + 1;
