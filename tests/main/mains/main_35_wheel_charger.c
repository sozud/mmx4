#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_35_wheel_charger.h"
#include "main/55C4.h"
extern union AnimationStep* wheel_charger_animations[9];
extern struct Unk_unk68 D_800FE1B8;
extern struct Unk_unk68 D_800FE1B0;
extern struct Unk_unk68 D_800FE1B4;
extern union AnimationStep wheel_charger_anim_2[24];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 wheel_charger_crash_expiry_pool_crash_case(u32 free_visual)
{
    struct MainObj obj, before;
    struct MiscObj misc_before[64];
    struct VisualObj visual_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
        visual_objects[i].unk5 = 0x29;
        visual_objects[i].unk6 = 0x2A;
    }
    if (free_visual)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 35;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk7E = 2;
    obj.unk7C = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wheel_charger_animations;
    set_animation(&obj, 8);
    before = obj;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(visual_before, visual_objects, sizeof(visual_before));
    cur_random = 0x1234;
    wheel_charger_crash(&obj);
    before.unk7E = 1;
    before.unk7C = 0;
    before.state = 2;
    if (free_visual) {
        struct VisualObj* effect = &visual_before[31];
        effect->active = 0x21;
        effect->id = 4;
        effect->unk2 = 0;
        effect->state = effect->unk5 = effect->unk6 = 0;
        effect->unk5C.value = 1;
        effect->x_pos.val = 100 * 65536;
        effect->y_pos.val = 200 * 65536;
        effect->unk15 = 0;
        effect->bg_offset = 0;
        effect->unk16 = VISUAL_SATURN_LAYER(1);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(misc_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_before)[i]);
    for (i = 0; i < sizeof(visual_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visual_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 0x366A);
    return (u8)obj.state | ((u32)(u16)obj.unk7C << 8) | ((u32)visual_objects[31].active << 24);
}
static const u32 wheel_charger_crash_expiry_pool_cases_expected[] = { 0x1000002u, 0x21000002u };

static u32 wheel_charger_crash_pulse_pool_crash_case(u32 free_visual)
{
    struct MainObj obj, before;
    struct MiscObj misc_before[64];
    struct VisualObj visual_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
        visual_objects[i].unk5 = 0x29;
        visual_objects[i].unk6 = 0x2A;
    }
    if (free_visual)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 35;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk7E = 1;
    obj.unk7C = 1;
    obj.terrain_box = &D_800FE1B8;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wheel_charger_animations;
    set_animation(&obj, 8);
    before = obj;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(visual_before, visual_objects, sizeof(visual_before));
    cur_random = 0x1234;
    wheel_charger_crash(&obj);
    before.unk7E = 2;
    before.unk7C = 0;
    before.state = 2;
    if (free_visual) {
        struct VisualObj* effect = &visual_before[31];
        effect->active = 0x21;
        effect->id = 4;
        effect->unk2 = 0;
        effect->state = effect->unk5 = effect->unk6 = 0;
        effect->unk5C.value = 1;
        effect->x_pos.val = 100 * 65536;
        effect->y_pos.val = 200 * 65536;
        effect->unk15 = 0;
        effect->bg_offset = 0;
        effect->unk16 = VISUAL_SATURN_LAYER(1);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(misc_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_before)[i]);
    for (i = 0; i < sizeof(visual_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visual_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 0x366A);
    return (u8)obj.state | ((u32)(u16)obj.unk7C << 8) | ((u32)visual_objects[31].active << 24);
}
static const u32 wheel_charger_crash_pulse_pool_cases_expected[] = { 0x1000002u };

static u32 wheel_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 i, landing = mode < 4;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 35;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.unk15 = mode == 3 || mode == 5 ? PLAYER_FACING_RIGHT : 0;
    obj.collision_flags = landing ? 8 : mode == 4 ? 2
        : mode == 5                               ? 1
        : mode == 7                               ? 3
                                                  : 0;
    obj.ext.main_35.unk80 = mode == 0 ? 0 : mode == 1 ? 1
        : landing || mode == 7                        ? 2
                                                      : 1;
    obj.ext.main_35.sound_timer = 17;
    obj.contact_damage = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 2 * 65536;
    obj.y_speed = -65536;
    obj.x_accel = 123;
    obj.gravity = 0x4000;
    obj.animation_table = (const u8* const*)wheel_charger_animations;
    ANIMATED_OBJECT(&obj)->animation_cursor = (u32*)wheel_charger_animations[0];
    obj.animation_step = wheel_charger_animations[0][0];
    obj.unk17 = 0;
    obj.previous_animation_index = 0x27;
    expected = obj;
    assert(obj.animation_step.packed == C_TEST_STEP(0x05010001));
    ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)(wheel_charger_animations[0] + 1);
    expected.animation_step = wheel_charger_animations[0][1];
    if (landing) {
        expected.y_speed = 0;
        expected.gravity = 0;
        if (mode == 0)
            expected.unk5 = 2;
        else if (mode == 1) {
            expected.ext.main_35.unk80 = 2;
            expected.contact_damage = 4;
            expected.ext.main_35.sound_timer = 1;
            expected.unk5 = 5;
            expected.unk17 = 1;
            expected.previous_animation_index = 0xFF;
            ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)wheel_charger_animations[1];
            expected.animation_step = wheel_charger_animations[1][0];
        } else {
            expected.x_speed = mode == 3 ? 4 * 65536 : -4 * 65536;
            expected.ext.main_35.sound_timer = 1;
            expected.unk5 = 5;
            expected.unk6 = 3;
        }
    } else {
        expected.x_pos.val += 2 * 65536;
        expected.y_pos.val += 65536;
        expected.x_speed += mode == 5 ? 123 : -123;
        expected.y_speed -= 0x4000;
        if (mode == 4) {
            expected.unk15 = PLAYER_FACING_RIGHT;
            expected.x_speed = 0x28000;
        } else if (mode == 5) {
            expected.unk15 = 0;
            expected.x_speed = -0x28000;
        }
    }
    func_8005EFB0(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)C_TEST_PSX_FACING(obj.unk15) << 16);
}
static const u32 wheel_charger_landing_wall_context_cases_expected[] = { 0x102u, 0x105u, 0x305u, 0x400305u, 0x400103u, 0x103u, 0x103u, 0x103u };

struct func_8005ECA8_0_case {
    u32 unk2;
    u32 expected[18];
};
static const struct func_8005ECA8_0_case func_8005ECA8_0_cases[] = {
    { -1, { 0u, 0u, 3u, 0u, 0u, 4u, 0u, 1u, 0u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0u, 0u, 3u, 0u, 0u, 4u, 0u, 1u, 0x40u, 6u, 0u, 0u, 4u, 0u, 1u, 0u, 0x28000u, 0u } },
};
static u32 test_func_8005ECA8_0(u32 row)
{
    const struct func_8005ECA8_0_case* c = &func_8005ECA8_0_cases[row];
    u32 observed_values[18];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800FE1B0, 0, sizeof(D_800FE1B0));
    memset(&D_800FE1B4, 0, sizeof(D_800FE1B4));
    memset(&D_800FE1B8, 0, sizeof(D_800FE1B8));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = c->unk2;
    func_8005ECA8(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.contact_damage;
    observed_values[3] = (u32)obj.ext.main_35.unk80;
    observed_values[4] = (u32)obj.gravity;
    observed_values[5] = (u32)obj.hp;
    observed_values[6] = (u32)obj.invincibility_timer;
    observed_values[7] = (u32)obj.state;
    observed_values[8] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[9] = TEST_PSX_LAYER(obj.unk16);
    observed_values[10] = (u32)obj.unk18.val;
    observed_values[11] = (u32)obj.unk1C.val;
    observed_values[12] = (u32)obj.unk5;
    observed_values[13] = (u32)obj.unk6;
    observed_values[14] = (u32)obj.unk7A;
    observed_values[15] = (u32)obj.x_accel;
    observed_values[16] = (u32)obj.x_speed;
    observed_values[17] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 18);
}

struct wheel_charger_charge_roll_1_case {
    u32 unk15, collision_flags;
    u32 expected[10];
};
static const struct wheel_charger_charge_roll_1_case wheel_charger_charge_roll_1_cases[] = {
    { 64, 9, { 6u, 0u, 0x3Cu, 1u, 1u, 0x680000u, 0x500000u, 0x40000u, 9u, 0x14010002u } },
    { 64, 8, { 5u, 3u, 7u, 1u, 1u, 0x680000u, 0x500000u, 0x40000u, 8u, 0x14010002u } },
    { 0, 10, { 6u, 0u, 0x3Cu, 1u, 1u, 0x680000u, 0x500000u, 0x40000u, 0xAu, 0x14010002u } },
};
static u32 test_wheel_charger_charge_roll_1(u32 row)
{
    const struct wheel_charger_charge_roll_1_case* c = &wheel_charger_charge_roll_1_cases[row];
    u32 observed_values[10];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 35;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    g_Player.bg_offset = -1;
    player_before = g_Player;
    func_8005ECA8(&obj);
    obj.unk5 = 5;
    obj.unk15 = c->unk15;
    obj.unk7E = 2;
    obj.ext.main_35.sound_timer = 2;
    set_animation(&obj, 2);
    obj.unk6 = 3;
    obj.unk7C = 7;
    obj.x_speed = 262144;
    obj.collision_flags = c->collision_flags;
    wheel_charger_charge_roll(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.unk7E;
    observed_values[4] = (u32)obj.ext.main_35.sound_timer;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.y_pos.val;
    observed_values[7] = (u32)obj.x_speed;
    observed_values[8] = (u32)obj.collision_flags;
    observed_values[9] = C_TEST_STEP(obj.animation_step.packed);
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

struct wheel_charger_charge_spin_1_case {
    u32 unk15;
    u32 expected[6];
};
static const struct wheel_charger_charge_spin_1_case wheel_charger_charge_spin_1_cases[] = {
    { 0, { 5u, 3u, 0xFFFC0000u, 1u, 1u, 0x13010101u } },
    { 64, { 5u, 3u, 0x40000u, 1u, 1u, 0x13010101u } },
};
static u32 test_wheel_charger_charge_spin_1(u32 row)
{
    const struct wheel_charger_charge_spin_1_case* c = &wheel_charger_charge_spin_1_cases[row];
    u32 observed_values[6];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 35;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    g_Player.bg_offset = -1;
    player_before = g_Player;
    func_8005ECA8(&obj);
    obj.unk5 = 5;
    obj.unk15 = c->unk15;
    obj.unk7E = 2;
    obj.ext.main_35.sound_timer = 2;
    set_animation(&obj, 2);
    obj.unk6 = 2;
    obj.animation_step = wheel_charger_anim_2[17];
    obj.animation_cursor = (const u8*)&wheel_charger_anim_2[17];
    assert(obj.animation_step.fields.event == 1);
    wheel_charger_charge_spin(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.unk7E;
    observed_values[4] = (u32)obj.ext.main_35.sound_timer;
    observed_values[5] = C_TEST_STEP(obj.animation_step.packed);
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

struct wheel_charger_crash_case {
    u32 unk7C;
    u32 expected[3];
};
static const struct wheel_charger_crash_case wheel_charger_crash_cases[] = {
    { 0, { 0u, 0xFFFFFFFFu, 0xFFFFFFFFu } },
    { 1, { 2u, 0u, 0xFFFFFFFFu } },
};
static u32 test_wheel_charger_crash(u32 row)
{
    const struct wheel_charger_crash_case* c = &wheel_charger_crash_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.unk7C = c->unk7C;
    wheel_charger_crash(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 wheel_charger_main_expected[] = { 1u, 2u, 2u, 0x9AD8000u, 0x4A0000u, 0x9B00000u, 0x500000u, 0xFFFD8000u, 0x60000u, 1u, 0u, 8u };
static u32 test_wheel_charger_main(u32 row)
{
    u32 observed_values[12];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    struct WeaponObj weapons_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 35;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    FILL_ACTIVE(weapon_objects, 16, 0);
    engine_obj.stage = 3;
    g_Player.bg_offset = 0;
    g_Player.x_pos.val = 162988032;
    g_Player.y_pos.val = 5242880;
    background_objects[0].x_pos.val = 150994944;
    background_objects[0].y_pos.val = 0;
    obj.x_pos.val = 162529280;
    obj.unk2 = 0;
    func_8005ECA8(&obj);
    obj.collision_flags = 8;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    wheel_charger_main(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapon_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.ext.main_35.saved_unk5;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_pos.val;
    observed_values[5] = (u32)obj.unk18.val;
    observed_values[6] = (u32)obj.unk1C.val;
    observed_values[7] = (u32)obj.x_speed;
    observed_values[8] = (u32)obj.y_speed;
    observed_values[9] = (u32)obj.on_screen;
    observed_values[10] = (u32)obj.unk65;
    observed_values[11] = (u32)obj.collision_flags;
    return c_test_observe(0, row, observed_values, wheel_charger_main_expected, 12);
}

#include "support/state_cases.h"
void wheel_charger_charge_ready(struct MainObj*);
void wheel_charger_charge_open(struct MainObj*);
void wheel_charger_wait_for_player(struct MainObj*);
#define WC(step, sub) (state_reset(step, sub, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), memset(&engine_obj, 0, sizeof(engine_obj)), state_terrain(0), g_Player.unk68 = NULL, so.active = 0x41, so.id = 0x23, so.state = 1, so.x_pos.i.hi = 0x900, so.y_pos.i.hi = 0x100, so.collision_flags = 8, background_objects[0].x_pos.i.hi = 0x880, background_objects[0].y_pos.i.hi = 0x80, g_Player.x_pos.i.hi = 0x950)
#define WCX() (state_extra = so.ext.main_35.unk80 | so.ext.main_35.sound_timer << 8 | (u32)so.unk7A << 16 | (u32)(so.hurt_box == (const u8*)&wheel_charger_open_hurt_box) << 24, engine_obj.stage = 0)
extern struct Unk_unk68 wheel_charger_open_hurt_box;
static void wc_init(u8 kind) { WC(0, 0), so.state = 0, so.unk2 = kind, func_8005ECA8(&so), WCX(); }
static void wc_init_bounce(void) { wc_init(2); }
static void wc_init_wait(void) { wc_init(3); }
static void wc_main_waiting(void) { WC(4, 0), wheel_charger_main(&so), WCX(); }
static void wc_main_stage3_killed(void) { WC(2, 0), engine_obj.stage = 3, so.hp = 1, state_hit(&so, 0, 0, 1), wheel_charger_main(&so), WCX(); }
static void wc_main_stage3_off_screen(void) { WC(2, 0), engine_obj.stage = 3, g_Player.x_pos.i.hi = 0xA00, background_objects[0].x_pos.i.hi = 0x400, wheel_charger_main(&so), WCX(); }
static void wc_main_fall_right(void) { WC(3, 0), so.collision_flags = 0, so.unk15 = PLAYER_FACING_RIGHT, so.ext.main_35.unk80 = 1, wheel_charger_main(&so), WCX(); }
static void wc_main_lost_floor(void) { WC(2, 0), so.collision_flags = 0, wheel_charger_main(&so), WCX(); }
static void wc_wait_player_past(void) { WC(4, 0), so.unk7A = 1, g_Player.x_pos.i.hi = 0x9C0, wheel_charger_wait_for_player(&so), WCX(); }
static void wc_ready(u8 event) { WC(5, 0), so.animation_step.fields.event = event, wheel_charger_charge_ready(&so), WCX(); }
static void wc_ready_wait(void) { wc_ready(0); }
static void wc_ready_go(void) { wc_ready(1); }
static void wc_open(u8 event, u8 timer, s16 px) { WC(5, 1), so.animation_step.fields.event = event, so.unk7C = timer, g_Player.x_pos.i.hi = px, wheel_charger_charge_open(&so), WCX(); }
static void wc_open_wait(void) { wc_open(0, 5, 0x800); }
static void wc_open_face_left(void) { wc_open(2, 1, 0x800); }
static void wc_open_face_right(void) { wc_open(0, 1, 0xA00); }
static void wc_spin_timers(void) { WC(5, 2), so.terrain_box = &state_hit_box, so.ext.main_35.sound_timer = 1, so.unk7E = 1, wheel_charger_charge_spin(&so), WCX(); }
static void wc_roll_timers(void) { WC(5, 3), so.terrain_box = &state_hit_box, so.ext.main_35.sound_timer = 1, so.unk7E = 1, so.x_speed = 0x40000, wheel_charger_charge_roll(&so), WCX(); }
static void (*const wheel_charger_states_cases[])(void) = {
    wc_init_bounce,
    wc_init_wait,
    wc_main_waiting,
    wc_main_stage3_killed,
    wc_main_stage3_off_screen,
    wc_main_fall_right,
    wc_main_lost_floor,
    wc_wait_player_past,
    wc_ready_wait,
    wc_ready_go,
    wc_open_wait,
    wc_open_face_left,
    wc_open_face_right,
    wc_spin_timers,
    wc_roll_timers,
};
static const u32 wheel_charger_states_expected[] = {
    0x2u, 0x0u, 0x9000000u, 0xFFFD8000u, 0x0u, 0x0u, 0x0u, 0x40003u, 0x1u, 0x41000000u,
    0x4u, 0x0u, 0x9000000u, 0x28000u, 0x0u, 0x0u, 0x4000u, 0x40003u, 0x10001u, 0x41000000u,
    0x4u, 0x0u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x2u, 0x0u, 0x9000000u, 0x0u, 0x60000u, 0x0u, 0x80000000u, 0x1u, 0x0u, 0x41002100u,
    0x2u, 0x0u, 0x9000000u, 0x0u, 0x60000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x3u, 0x0u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x4000u, 0x0u, 0x1u, 0x41000000u,
    0x3u, 0x0u, 0x9000000u, 0x0u, 0xFFFFC400u, 0x3C0000u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x2u, 0x0u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x5u, 0x0u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x105u, 0xAu, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x105u, 0x4u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x205u, 0x30000u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x3u, 0x1000000u, 0x41000000u,
    0x205u, 0x30000u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x4002u, 0x0u, 0x0u, 0x41000000u,
    0x205u, 0x30000u, 0x9000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1400u, 0x41002100u,
    0x305u, 0x20000u, 0x9040000u, 0x40000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1400u, 0x41002100u,
};
static u32 test_wheel_charger_states(u32 row)
{
    return state_run(wheel_charger_states_cases[row], row, &wheel_charger_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "wheel_charger_crash_expiry_pool", NULL, wheel_charger_crash_expiry_pool_cases_expected, COUNT(wheel_charger_crash_expiry_pool_cases_expected), wheel_charger_crash_expiry_pool_crash_case },
    { "wheel_charger_crash_pulse_pool", NULL, wheel_charger_crash_pulse_pool_cases_expected, COUNT(wheel_charger_crash_pulse_pool_cases_expected), wheel_charger_crash_pulse_pool_crash_case },
    { "wheel_charger_landing_wall_context", NULL, wheel_charger_landing_wall_context_cases_expected, COUNT(wheel_charger_landing_wall_context_cases_expected), wheel_case },
    { "func_8005ECA8_0", 0, 0, 2, test_func_8005ECA8_0 },
    { "wheel_charger_charge_roll_1", 0, 0, 3, test_wheel_charger_charge_roll_1 },
    { "wheel_charger_charge_spin_1", 0, 0, 2, test_wheel_charger_charge_spin_1 },
    { "wheel_charger_crash", 0, 0, 2, test_wheel_charger_crash },
    { "wheel_charger_main", 0, 0, 1, test_wheel_charger_main },
    { "wheel_charger_states", 0, 0, COUNT(wheel_charger_states_cases), test_wheel_charger_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wheel_charger_crash_expiry_pool_cases_expected) + COUNT(wheel_charger_crash_pulse_pool_cases_expected) + COUNT(wheel_charger_landing_wall_context_cases_expected) + 2 + 3 + 2 + 2 + 1 + COUNT(wheel_charger_states_cases);
