#include "test_runtime.h"
#include "main/mains/main_33_spike_sled.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "support/state_cases.h"
extern u8 D_800FDD98[8];
extern struct StageObjectRecord stage_object_records_3_0[58];

static u32 turn_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i, right = mode == 1, intro = mode != 2;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7C = 2;
    obj.unk15 = right ? PLAYER_FACING_RIGHT : 0;
    obj.ext.main_33.intro_laps = 1;
    obj.ext.main_33.intro_active = intro;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.y_speed = -32768;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)spike_sled_animations;
    set_animation(&obj, 0);
    before = obj;
    spike_sled_patrol_turn(&obj);
    before.y_pos.val += 32768;
    before.y_speed -= 0x1000;
    before.unk15 = right ? 0 : PLAYER_FACING_RIGHT;
    before.x_speed = intro ? 65536 : 0x28000;
    before.ext.main_33.intro_laps = 0;
    before.unk7C = intro ? 0x40 : 1;
    before.unk5 = intro ? 6 : 2;
    before.unk6 = intro ? 0 : 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)C_TEST_PSX_FACING(obj.unk15) << 16) | ((u32)(u8)obj.unk7C << 24);
}
static const u32 spike_sled_intro_turn_animation_cases_expected[] = { 0x40400006u, 0x40000006u, 0x1400102u };

static u32 patrol_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    u32 i, actual, cursor = ~0u;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.ext.main_33.intro_active = 0;
    obj.unk15 = mode ? PLAYER_FACING_RIGHT : 0;
    obj.x_pos.val = (mode ? 0x130F : 0x1231) * 65536 + 0x2468;
    obj.y_pos.val = 0x2E8 * 65536 + 0x1357;
    obj.x_speed = 0x1000;
    obj.y_speed = -0x1000;
    obj.x_accel = 0x2468;
    obj.unk17 = 0;
    obj.previous_animation_index = 0xA5;
    obj.animation_table = (u32**)spike_sled_animations;
    obj.animation_cursor = (u32*)spike_sled_animations[0];
    obj.animation_step.packed = *obj.animation_cursor;
    obj.animation_step.fields.duration = 1;
    before = obj;
    spike_sled_patrol_drive(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7C = obj.unk7C;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_accel = obj.x_accel;
    before.unk17 = obj.unk17;
    before.previous_animation_index = obj.previous_animation_index;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(obj.animation_table == (u32**)spike_sled_animations);
    assert(obj.unk17 == 2);
    for (i = 0; i < 4; i++)
        if (obj.animation_cursor == (u32*)spike_sled_animations[2] + i)
            cursor = i;
    assert(cursor != ~0u);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = C_TEST_LE_WORD((u32*)&obj + 1);
        break;
    case 3:
        actual = (u16)obj.unk7C;
        break;
    case 4:
        actual = obj.x_accel;
        break;
    case 5:
        actual = C_TEST_STEP(obj.animation_step.packed);
        break;
    default:
        actual = cursor | ((u32)obj.unk17 << 8) | ((u32)obj.previous_animation_index << 16);
        break;
    }
    return actual;
}
static const u32 spike_sled_patrol_context_cases_expected[] = { 0x12313468u, 0x2E82357u, 0x401u, 0x1u, 0x2468u, 0xD010006u, 0xFF0200u, 0x130F3468u, 0x2E82357u, 0x401u, 0x1u, 0x2468u, 0xD010006u, 0xFF0200u };
static u32 spike_sled_patrol_context_cases_row(u32 row)
{
    return patrol_case(row / 7, row % 7);
}

static u32 sled_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u8 masks_before[8];
    u32 i, actual, original_step;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.x_pos.val = (mode == 3 ? 0x1330 : 0x1210) * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.unk15 = mode == 3 ? PLAYER_FACING_RIGHT : 0;
    obj.ext.main_33.unk80 = mode == 0 ? 8 : mode == 2 ? 2
                                                      : 0;
    g_Player.x_pos.i.hi = mode < 2 ? 0x1321 : mode == 2 ? 0x1240
                                                        : 0x1241;
    obj.animation_table = (u32**)spike_sled_animations;
    obj.animation_cursor = (u8*)spike_sled_animations[2];
    obj.animation_step.packed = *(u32*)spike_sled_animations[2];
    before = obj;
    player_before = g_Player;
    original_step = *(u32*)spike_sled_animations[2];
    memcpy(masks_before, D_800FDD98, sizeof(masks_before));
    func_8005DC58(&obj);
    before.unk6 = obj.unk6;
    before.unk7C = 0;
    before.x_accel = obj.x_accel;
    before.ext.main_33.variant = obj.ext.main_33.variant;
    before.ext.main_33.target_x = obj.ext.main_33.target_x;
    before.unk17 = 4;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (u8*)spike_sled_animations[4];
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(masks_before); i++)
        assert(D_800FDD98[i] == masks_before[i]);
    assert(*(u32*)spike_sled_animations[2] == original_step);
    if (observation == 0)
        actual = (u16)obj.ext.main_33.target_x | ((u32)obj.ext.main_33.variant << 16) | ((u32)(u8)obj.unk6 << 24);
    else if (observation == 1)
        actual = C_TEST_STEP(obj.animation_step.packed);
    else
        actual = obj.x_accel;
    return actual;
}
static const u32 spike_sled_selection_cases_expected[] = { 0x20312E0u, 0x15010002u, 0xFFFFC000u, 0x2041320u, 0x15010002u, 0xFFFFC000u, 0x2011260u, 0x15010002u, 0xFFFFC000u, 0x2011260u, 0x15010002u, 0xFFFFC000u };
static u32 spike_sled_selection_cases_row(u32 row)
{
    return sled_case(row / 3, row % 3);
}

struct func_8005D4E0_case {
    u32 unk5;
    u32 expected[8];
};
static const struct func_8005D4E0_case func_8005D4E0_cases[] = {
    { -1, { 2u, 0xFFFFFFFFu, 2u, 7u, 0x1101u, 0x1234u, 0x640000u, 0x500000u } },
    { 3, { 2u, 3u, 2u, 7u, 0x1101u, 0x1234u, 0x640000u, 0x500000u } },
    { 2, { 2u, 2u, 1u, 7u, 0x1100u, 0x1100u, 0x640000u, 0x500000u } },
};
static u32 test_func_8005D4E0(u32 row)
{
    const struct func_8005D4E0_case* c = &func_8005D4E0_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 2;
    obj.unk5 = c->unk5;
    obj.unk7C = 2;
    obj.unk7E = 7;
    obj.ext.main_33.unk88 = 0x1101;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    player_before = g_Player;
    engine_before = engine_obj;
    background_objects[0].unk26 = 0x1234;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    if (obj.unk5 == 2) {
        backgrounds_before[0].unk26 = 0x1100;
    }
    func_8005D4E0(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.unk7E;
    observed_values[4] = (u32)obj.ext.main_33.unk88;
    observed_values[5] = (u32)background_objects[0].unk26;
    observed_values[6] = (u32)obj.x_pos.val;
    observed_values[7] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

struct func_8005DC58_case {
    u32 hi;
    u32 expected[7];
};
static const struct func_8005DC58_case func_8005DC58_cases[] = {
    { 4640, { 0u, 0x1220u, 0xFFFFC000u, 2u, 0u, 0x12500000u, C_TEST_STEP(0x15010002u) } },
    { 4896, { 4u, 0x1320u, 0u, 1u, 0u, 0x12500000u, C_TEST_STEP(0xF010001u) } },
};
static u32 test_func_8005DC58(u32 row)
{
    const struct func_8005DC58_case* c = &func_8005DC58_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.state = 1;
    obj.unk15 = 64;
    obj.x_pos.val = 307232768;
    obj.animation_table = (const u8* const*)spike_sled_animations;
    obj.y_pos.val = 48758784;
    obj.unk5 = 4;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.ext.main_33.unk80 = 0x7F;
    obj.ext.main_33.target_x = 0;
    set_animation(&obj, 3);
    g_Player.x_pos.i.hi = c->hi;
    player_before = g_Player;
    func_8005DC58(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.ext.main_33.variant;
    observed_values[1] = (u32)obj.ext.main_33.target_x;
    observed_values[2] = (u32)obj.x_accel;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct spike_sled_patrol_drive_0_case {
    u32 unk15, hi, unk7C;
    u32 expected[4];
};
static const struct spike_sled_patrol_drive_0_case spike_sled_patrol_drive_0_cases[] = {
    { 255, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 255, 4896, 1, { 0u, 0u, 1u, 0u } },
    { 0, 4640, 1, { 0u, 0u, 1u, 0u } },
};
static u32 test_spike_sled_patrol_drive_0(u32 row)
{
    const struct spike_sled_patrol_drive_0_case* c = &spike_sled_patrol_drive_0_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk15 = c->unk15;
    obj.x_pos.i.hi = c->hi;
    obj.unk7C = c->unk7C;
    spike_sled_patrol_drive(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_accel;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/enemy_world.h"
static const u32 spike_sled_patrol_drive_1_expected[] = { 0x12128000u };
static u32 test_spike_sled_patrol_drive_1(u32 row)
{
    struct MainObj* obj = world_spawn(33, 3, 0, 0, &stage_object_records_3_0[49]);
    u32 observed;
    obj->x_pos.i.hi = 4624;
    obj->y_pos.i.hi = 640;
    main_bss_state.frame_counter = 1;
    g_Player.x_pos.i.hi = 4704;
    g_Player.y_pos.i.hi = 744;
    cur_random = 200;
    spike_sled_init(obj);
    assert(obj->state == 1 && obj->unk5 == 2 && obj->unk6 == 0);
    assert(obj->hp == 0 && obj->contact_damage == 6 && obj->y_pos.i.hi == 744);
    assert(obj->ext.main_33.unk80 == 127 && obj->ext.main_33.intro_active == 1 && obj->ext.main_33.intro_laps == 2);
    assert(engine_obj.enable_boss == 1 && engine_obj.unk25 == 2 && engine_obj.boss_ptr == obj);
    assert(g_Player.script_state == 1 && g_Player.script_action == 20 && g_Player.script_facing == 0 && SPIKE_IMMUNE(g_Player) == 1);
    spike_sled_patrol_start(obj);
    assert(obj->unk6 == 1 && obj->unk7C == 180 && obj->x_speed == 163840);
    world_snapshot();
    move_object(MOVING_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    spike_sled_patrol_drive(obj);
    world_check();
    observed = obj->x_pos.val;
    return c_test_observe(0, row, &observed, spike_sled_patrol_drive_1_expected, 1);
}

static const u32 spike_sled_patrol_turn_expected[] = { 0u, 0xFFu, 0u, 0u, 1u, 0u, 0xFFu };
static u32 test_spike_sled_patrol_turn(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7C = 1;
    obj.x_speed = 255;
    obj.unk15 = 255;
    spike_sled_patrol_turn(&obj);
    observed_values[0] = (u32)obj.ext.main_33.intro_laps;
    observed_values[1] = (u32)obj.unk15;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_accel;
    observed_values[6] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, spike_sled_patrol_turn_expected, 7);
}

#define SLED(sub) (state_reset(1, sub, 0), so.x_pos.i.hi = 0x1200, so.y_pos.i.hi = 0x300)
#define AIM(px, mask, timer, facing, x) (SLED(1), so.ext.main_33.unk80 = mask, so.unk7C = timer, so.unk15 = facing, so.x_pos.i.hi = x, g_Player.x_pos.i.hi = px, func_8005DC58(&so), so.unk7E = so.ext.main_33.variant | so.ext.main_33.target_x << 4)
#define RISE(v, y, timer) (SLED(2), so.ext.main_33.variant = v, so.y_pos.i.hi = y, so.unk7C = timer, so.y_speed = 0x10000, spike_sled_bomb_rise(&so))
#define DROP(v, mask) (SLED(0), so.ext.main_33.variant = v, so.ext.main_33.unk80 = mask, func_8005E108(&so), so.unk7E ^= so.ext.main_33.variant << 8)
static void ss_aim_locked(void)
{
    SLED(1);
    so.ext.main_33.target_x = 0x1220;
    func_8005DC58(&so);
}
static void ss_aim_wait_left(void) { AIM(0x1000, 1, 3, 0, 0x1200); }
static void ss_aim_wait_right(void) { AIM(0x1000, 1, 3, 0x40, 0x1400); }
static void ss_aim_wait_hold(void) { AIM(0x1300, 1, 3, 0, 0x1300); }
static void ss_aim_wait_hold_right(void) { AIM(0x1200, 1, 3, 0x40, 0x1300); }
static void ss_aim_far_left(void) { AIM(0x1000, 1, 1, 0, 0x1200); }
static void ss_aim_far_left_next(void) { AIM(0x1000, 2, 1, 0, 0x1200); }
static void ss_aim_far_left_none(void) { AIM(0x1000, 0x80, 1, 0, 0x1200); }
static void ss_aim_far_right(void) { AIM(0x1400, 0x10, 1, 0x40, 0x1400); }
static void ss_aim_far_right_next(void) { AIM(0x1400, 8, 1, 0x40, 0x1400); }
static void ss_aim_far_right_none(void) { AIM(0x1400, 0x80, 1, 0x40, 0x1400); }
static void ss_aim_mid_low(void) { AIM(0x1230, 1, 1, 0, 0x1200); }
static void ss_aim_mid_low_next(void) { AIM(0x1230, 2, 1, 0, 0x1200); }
static void ss_aim_mid_low_none(void) { AIM(0x1230, 0x80, 1, 0, 0x1200); }
static void ss_aim_mid_high(void) { AIM(0x1250, 2, 1, 0, 0x1200); }
static void ss_aim_mid_high_back(void) { AIM(0x1250, 1, 1, 0, 0x1200); }
static void ss_rise(void) { RISE(0, 0x300, 3); }
static void ss_rise_top(void) { RISE(2, 0x200, 3); }
static void ss_rise_mid(void) { RISE(5, 0x2B0, 3); }
static void ss_rise_mid_top(void) { RISE(5, 0x200, 3); }
static void ss_rise_high(void) { RISE(6, 0x290, 3); }
static void ss_rise_high_top(void) { RISE(6, 0x200, 3); }
static void ss_rise_fall(void) { RISE(0xFF, 0x200, 1); }
static void ss_drop_slot(void) { DROP(0, 1); }
static void ss_drop_left(void) { DROP(1, 0x20); }
static void ss_drop_right(void) { DROP(3, 0x40); }
static void ss_drop_center(void) { DROP(2, 0x40); }
static void ss_drop_none(void) { DROP(4, 0); }

void spike_sled_despawn(struct MainObj*);
void spike_sled_patrol(struct MainObj*);
void spike_sled_fall(struct MainObj*);
void spike_sled_charge(struct MainObj*);
void spike_sled_charge_approach(struct MainObj*);
void spike_sled_charge_leap(struct MainObj*);
void spike_sled_bomb(struct MainObj*);
void spike_sled_intro(struct MainObj*);
void spike_sled_intro_fill_health(struct MainObj*);
void spike_sled_intro_start_fight(struct MainObj*);
#define SX(step, sub) (SLED(sub), so.unk5 = step, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
static void ss_run_intro_patrol(void) { SX(2, 0), so.state = 1, so.ext.main_33.intro_active = 1, spike_sled_update(&so); }
static void ss_run_flash(u8 count)
{
    SX(1, 0);
    so.state = 1;
    so.ext.main_33.saved_unk5 = 1;
    so.ext.main_33.flash_timer = 2;
    so.ext.main_33.unk91 = count;
    so.ext.main_33.unk87 = 2;
    spike_sled_update(&so);
    state_extra = so.ext.main_33.flash_timer | so.ext.main_33.unk91 << 8;
}
static void ss_run_flash_burst(void) { ss_run_flash(1); }
static void ss_run_flash_wait(void) { ss_run_flash(3); }
#define DEATH(step, timer, count, mask, scroll) (SX(step, 0), so.state = 2, so.unk7C = timer, so.unk7E = count, so.ext.main_33.unk80 = mask, so.ext.main_33.unk88 = scroll, func_8005D4E0(&so), state_extra = so.state | (u16)so.ext.main_33.unk88 << 8)
static void ss_death_rumble(void) { DEATH(0, 5, 2, 0, 0); }
static void ss_death_rumble_burst(void) { DEATH(0, 5, 1, 0, 0); }
static void ss_death_debris_done(void) { DEATH(1, 1, 0, 0, 0); }
static void ss_death_debris_wait(void) { DEATH(1, 5, 2, 0, 0); }
static void ss_death_debris_burst(void) { DEATH(1, 5, 1, 5, 0); }
static void ss_death_scroll_done(void) { DEATH(2, 1, 0, 0, 0x1200); }
static void ss_death_scroll(void) { DEATH(2, 5, 0, 0, 0x1200); }
static void ss_despawn(void)
{
    SX(1, 1);
    so.state = 3;
    so.active = 0x41;
    so.ext.main_33.unk80 = 0x7F;
    g_Player.invincibility_timer = 5;
    spike_sled_despawn(&so);
    state_extra = (u16)background_objects[0].unk26 | (u8)g_Player.invincibility_timer << 16 | so.ext.main_33.unk80 << 24;
}
static void ss_patrol_edge_left(void) { SX(2, 1), spike_sled_patrol(&so); }
static void ss_patrol_turn_lap(void) { SX(2, 2), so.unk7C = 5, so.ext.main_33.intro_laps = 3, spike_sled_patrol_turn(&so), state_extra = so.ext.main_33.intro_laps; }
#define FALL(sub, y, saved_y, landed, timer) (SX(3, sub), so.y_pos.i.hi = y, so.unk1C.i.hi = saved_y, so.ext.main_33.unk84 = landed, so.unk7C = timer, spike_sled_fall(&so), state_extra = (u16)so.y_pos.i.hi | so.ext.main_33.unk84 << 16)
static void ss_fall_floor(void) { FALL(0, 0x2F0, 0, 0, 0); }
static void ss_fall_hang(void) { FALL(0, 0x200, 0x200, 0, 0); }
static void ss_fall_hang_done(void) { FALL(0, 0x200, 0x200, 1, 0); }
static void ss_fall_hold(void) { FALL(1, 0x300, 0, 0, 2); }
static void ss_fall_release(void) { FALL(1, 0x300, 0, 0, 1); }
#define CHARGE(ev, face) (SX(4, 0), so.ext.main_33.target_x = 5, so.animation_step.fields.event = ev, so.unk15 = face, spike_sled_charge(&so), state_extra = (u16)so.ext.main_33.target_x)
static void ss_charge_rev(void) { CHARGE(2, 0); }
static void ss_charge_go_left(void) { CHARGE(1, 0); }
static void ss_charge_go_right(void) { CHARGE(1, PLAYER_FACING_RIGHT); }
static void ss_charge_braking(void) { SX(4, 2), so.unk7C = 5, so.unk15 = PLAYER_FACING_RIGHT, so.x_speed = 0x10000, so.x_accel = -0x4000, func_8005DED4(&so); }
static void ss_charge_turn_right(void) { SX(4, 2), so.unk7C = 1, func_8005DED4(&so); }
static void ss_charge_turn_left(void) { SX(4, 2), so.unk7C = 1, so.unk15 = PLAYER_FACING_RIGHT, func_8005DED4(&so); }
#define APPROACH(target, face, vx) (SX(4, 3), so.ext.main_33.target_x = target, so.unk15 = face, so.x_speed = vx, spike_sled_charge_approach(&so), state_extra = (u16)so.ext.main_33.target_x)
static void ss_approach_arrived(void) { APPROACH(0x1200, 0, 0); }
static void ss_approach_creep_left(void) { APPROACH(0x11FD, 0, 0); }
static void ss_approach_creep_right(void) { APPROACH(0x1203, PLAYER_FACING_RIGHT, 0); }
static void ss_approach_slow_left(void) { APPROACH(0x11F0, 0, 0); }
static void ss_approach_slow_right(void) { APPROACH(0x1210, PLAYER_FACING_RIGHT, 0); }
static void ss_approach_far(void) { APPROACH(0x1230, PLAYER_FACING_RIGHT, 0x40000); }
static void ss_leap_rev(void) { SX(4, 4), so.animation_step.fields.event = 2, spike_sled_charge_leap(&so); }
static void ss_leap_jump(void) { SX(4, 4), so.animation_step.fields.event = 1, so.x_speed = 0x10000, spike_sled_charge_leap(&so); }
static void ss_bomb_no_slot(void) { SX(5, 0), so.ext.main_33.variant = 1, spike_sled_bomb(&so), state_extra = so.ext.main_33.variant; }
static void ss_rise_slot_1_top(void) { RISE(1, 0x200, 3); }
static void ss_rise_slot_3(void) { RISE(3, 0x300, 3); }
static void ss_rise_slot_4_top(void) { RISE(4, 0x200, 3); }
static void ss_intro_drive(void) { SX(6, 0), so.unk7C = 2, so.x_speed = 0x10000, spike_sled_intro(&so); }
static void ss_intro_drive_done(void) { SX(6, 0), so.unk7C = 1, spike_sled_intro(&so); }
static void ss_intro_fill(void) { SX(6, 1), so.unk7E = 2, so.hp = 0x10, spike_sled_intro_fill_health(&so); }
static void ss_intro_fill_done(void) { SX(6, 1), so.unk7E = 1, so.hp = 0x2F, spike_sled_intro_fill_health(&so); }
static void ss_intro_wait(void) { SX(6, 2), so.unk7C = 2, spike_sled_intro_start_fight(&so); }
static void (*const spike_sled_states_cases[])(void) = {
    ss_aim_locked,
    ss_aim_wait_left,
    ss_aim_wait_right,
    ss_aim_wait_hold,
    ss_aim_wait_hold_right,
    ss_aim_far_left,
    ss_aim_far_left_next,
    ss_aim_far_left_none,
    ss_aim_far_right,
    ss_aim_far_right_next,
    ss_aim_far_right_none,
    ss_aim_mid_low,
    ss_aim_mid_low_next,
    ss_aim_mid_low_none,
    ss_aim_mid_high,
    ss_aim_mid_high_back,
    ss_rise,
    ss_rise_top,
    ss_rise_mid,
    ss_rise_mid_top,
    ss_rise_high,
    ss_rise_high_top,
    ss_rise_fall,
    ss_drop_slot,
    ss_drop_left,
    ss_drop_right,
    ss_drop_center,
    ss_drop_none,
    ss_run_intro_patrol,
    ss_run_flash_burst,
    ss_run_flash_wait,
    ss_death_rumble,
    ss_death_rumble_burst,
    ss_death_debris_done,
    ss_death_debris_wait,
    ss_death_debris_burst,
    ss_death_scroll_done,
    ss_death_scroll,
    ss_despawn,
    ss_patrol_edge_left,
    ss_patrol_turn_lap,
    ss_fall_floor,
    ss_fall_hang,
    ss_fall_hang_done,
    ss_fall_hold,
    ss_fall_release,
    ss_charge_rev,
    ss_charge_go_left,
    ss_charge_go_right,
    ss_charge_braking,
    ss_charge_turn_right,
    ss_charge_turn_left,
    ss_approach_arrived,
    ss_approach_creep_left,
    ss_approach_creep_right,
    ss_approach_slow_left,
    ss_approach_slow_right,
    ss_approach_far,
    ss_leap_rev,
    ss_leap_jump,
    ss_bomb_no_slot,
    ss_rise_slot_1_top,
    ss_rise_slot_3,
    ss_rise_slot_4_top,
    ss_intro_drive,
    ss_intro_drive_done,
    ss_intro_fill,
    ss_intro_fill_done,
    ss_intro_wait,
};
static const u32 spike_sled_states_expected[] = { 0x301u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x201u, 2u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 2u, 0x14000000u, 0u, 0u, 0xFFFFC000u, 0x4004u, 0u, 0u, 0u, 0x101u, 2u, 0x13000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x201u, 2u, 0x13000000u, 0u, 0u, 0xFFFFC000u, 0x4004u, 0u, 0u, 0u, 0x201u, 0x22000000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x26010000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x22000000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x32040000u, 0x14000000u, 0u, 0u, 0xFFFFC000u, 0x4004u, 0u, 0u, 0u, 0x201u, 0x2E030000u, 0x14000000u, 0u, 0u, 0xFFFFC000u, 0x4004u, 0u, 0u, 0u, 0x201u, 0x32040000u, 0x14000000u, 0u, 0u, 0xFFFFC000u, 0x4004u, 0u, 0u, 0u, 0x201u, 0x22000000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x26010000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x22000000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x26010000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 0x22000000u, 0x12000000u, 0u, 0u, 0xFFFFC000u, 4u, 0u, 0u, 0u, 0x201u, 2u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 0x40003u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 2u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 0x40003u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 2u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 0x40003u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x12000000u, 0u, 0x10000u, 0x420000u, 7u, 0u, 0u, 0u, 0x101u, 0xCu, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0x5000022u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0x6000022u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0xFF000026u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0xFF000026u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x102u, 0xB4u, 0x12000000u, 0xFFFD8000u, 0u, 0u, 0u, 0u, 0u, 0u,
    1u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x601u, 0x2100u,
    1u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x201u, 0u,
    0u, 0x10004u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 2u, 0u,
    0u, 0x60004u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 2u, 0x2100u,
    2u, 0x80u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x120002u, 0u,
    1u, 0x10004u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 2u, 0u,
    1u, 0x60004u, 0x12A00000u, 0u, 0u, 0u, 0u, 0u, 2u, 0x2100u,
    2u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x120003u, 0u,
    2u, 4u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x11FE02u, 0u,
    0u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x1100u, 0u,
    0x202u, 0u, 0x12000000u, 0u, 0u, 0xFFFFE000u, 1u, 0u, 0u, 0u,
    0x102u, 4u, 0x12000000u, 0x28000u, 0u, 0u, 0x4000u, 0u, 2u, 0u,
    4u, 0u, 0x12000000u, 0u, 0u, 0u, 2u, 0u, 0x2E8u, 0u,
    0x103u, 0x1Eu, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0u,
    3u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x10200u, 0u,
    0x103u, 1u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x300u, 0u,
    3u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0x10300u, 0u,
    4u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x104u, 0xB4u, 0x12000000u, 0xFFFC0000u, 0u, 0u, 3u, 0u, 0u, 0u,
    0x104u, 0xB4u, 0x12000000u, 0x40000u, 0u, 0u, 0x4003u, 0u, 0u, 0u,
    0x204u, 4u, 0x12010000u, 0xC000u, 0u, 0xFFFFC000u, 0x4000u, 0u, 0u, 0u,
    0x104u, 1u, 0x12000000u, 0x40000u, 0u, 0u, 0x4003u, 0u, 0u, 0u,
    0x104u, 1u, 0x12000000u, 0xFFFC0000u, 0u, 0u, 3u, 0u, 0u, 0u,
    0x404u, 0x1Eu, 0x12000000u, 0u, 0u, 0u, 5u, 0u, 0x1200u, 0u,
    0x304u, 0u, 0x11FF0000u, 0xFFFF0000u, 0u, 0u, 0u, 0u, 0x11FDu, 0u,
    0x304u, 0u, 0x12010000u, 0x10000u, 0u, 0u, 0x4000u, 0u, 0x1203u, 0u,
    0x304u, 0u, 0x11FE0000u, 0xFFFE0000u, 0u, 0u, 0u, 0u, 0x11F0u, 0u,
    0x304u, 0u, 0x12020000u, 0x20000u, 0u, 0u, 0x4000u, 0u, 0x1210u, 0u,
    0x304u, 0u, 0x12040000u, 0x40000u, 0u, 0u, 0x4000u, 0u, 0x1230u, 0u,
    0x404u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    5u, 0u, 0x12000000u, 0u, 0x40000u, 0u, 6u, 0u, 0u, 0u,
    0x105u, 0x26u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0xFFu, 0u,
    0x201u, 0x40003u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u,
    0x201u, 2u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u,
    0x201u, 0x40003u, 0x12000000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u,
    6u, 1u, 0x12010000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x106u, 0x30000u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x106u, 0x10000u, 0x12000000u, 0u, 0u, 0u, 0u, 0x110000u, 0u, 0u,
    0x206u, 0x3003Cu, 0x12000000u, 0u, 0u, 0u, 0u, 0x300000u, 0u, 0u,
    0x206u, 1u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
};

static u32 test_spike_sled_states(u32 row)
{
    return state_run(spike_sled_states_cases[row], row, &spike_sled_states_expected[row * 10]);
}

#include "support/tile_writes.h"
void func_8005E298(struct MainObj*);
#define ST(step, sub) (SX(step, sub), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 3, tile_writes_begin())
#define STX() (state_extra ^= tile_writes_end() ^ (u32)SPIKE_IMMUNE(g_Player) << 31 ^ (u8)g_Player.invincibility_timer << 20, engine_obj.stage = 0)
static void sst_killed(void)
{
    ST(1, 0), so.state = 1, so.hp = 1, state_hit(&so, 0, 0, 1), SPIKE_IMMUNE_SET(g_Player, 0), g_Player.invincibility_timer = 0;
    tile_writes_expect(1, 0, 0, 1), spike_sled_update(&so), STX();
}
static void sst_death_slots(void)
{
    ST(0, 0), so.state = 2, so.unk7C = 1, so.ext.main_33.unk80 = 0x09;
    tile_writes_expect(0, D_800FDDA0[0], D_800FDDA0[1], 1), tile_writes_expect(0, D_800FDDA0[6], D_800FDDA0[7], 1);
    func_8005D4E0(&so), assert(so.unk42 == OBJECT_CLUT(0x798F)), so.unk42 = 0, STX();
}
#define DROPT(timer, expect) (ST(5, 1), expect, so.unk7E = timer, so.ext.main_33.variant = 2, so.ext.main_33.unk80 = 0x7F, func_8005E298(&so), state_extra = so.ext.main_33.unk80 | so.ext.main_33.variant << 8)
static void sst_drop_wait(void) { DROPT(2, 0), STX(); }
static void sst_drop(void) { DROPT(1, tile_writes_expect(0, D_800FDDA0[4], D_800FDDA0[5], 1)), STX(); }
static void sst_intro_end(void) { ST(6, 3), g_Player.script_state = 1, so.unk7C = 1, so.ext.main_33.intro_active = 1, tile_writes_expect(0, 0x1340, 0x2A0, 1), spike_sled_intro_start_fight(&so), state_extra = so.ext.main_33.intro_active | (u8)g_Player.script_state << 8, STX(); }
static void (*const spike_sled_tiles_cases[])(void) = {
    sst_killed,
    sst_death_slots,
    sst_drop_wait,
    sst_drop,
    sst_intro_end,
};
static const u32 spike_sled_tiles_expected[] = {
    0x0u, 0x4005Au, 0x12000000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x0u, 0x85C565CCu, 0x2100u,
    0x1u, 0x10050u, 0x12E00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x53D30018u, 0x0u,
    0x105u, 0x10000u, 0x12000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x8000027Fu, 0x0u,
    0x105u, 0x0u, 0x12000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x69E97F77u, 0x0u,
    0x4u, 0x0u, 0x12000000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x0u, 0xE9E9800Cu, 0x0u,
};
static u32 test_spike_sled_tiles(u32 row)
{
    return state_run(spike_sled_tiles_cases[row], row, &spike_sled_tiles_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "spike_sled_states", 0, 0, COUNT(spike_sled_states_cases), test_spike_sled_states },
    { "spike_sled_intro_turn_animation", NULL, spike_sled_intro_turn_animation_cases_expected, COUNT(spike_sled_intro_turn_animation_cases_expected), turn_case },
    { "spike_sled_patrol_context", NULL, spike_sled_patrol_context_cases_expected, COUNT(spike_sled_patrol_context_cases_expected), spike_sled_patrol_context_cases_row },
    { "spike_sled_selection", NULL, spike_sled_selection_cases_expected, COUNT(spike_sled_selection_cases_expected), spike_sled_selection_cases_row },
    { "func_8005D4E0", 0, 0, 3, test_func_8005D4E0 },
    { "func_8005DC58", 0, 0, 2, test_func_8005DC58 },
    { "spike_sled_patrol_drive_0", 0, 0, 3, test_spike_sled_patrol_drive_0 },
    { "spike_sled_patrol_drive_1", 0, 0, 1, test_spike_sled_patrol_drive_1 },
    { "spike_sled_patrol_turn", 0, 0, 1, test_spike_sled_patrol_turn },
    { "spike_sled_tiles", 0, 0, COUNT(spike_sled_tiles_cases), test_spike_sled_tiles },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(spike_sled_states_cases) + COUNT(spike_sled_intro_turn_animation_cases_expected) + COUNT(spike_sled_patrol_context_cases_expected) + COUNT(spike_sled_selection_cases_expected) + 3 + 2 + 3 + 1 + 1 + COUNT(spike_sled_tiles_cases);
