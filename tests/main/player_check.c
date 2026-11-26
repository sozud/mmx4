#include "test_runtime.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/player.h"
#include "support/player_cases.h"
#include "main/player_animations_2.h"
#include "main/player_animations.h"
#include "main/55C4.h"
void player_leap_check_wall(struct PlayerObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 player_check_wall_jump_expected[] = { 0u };
static u32 test_player_check_wall_jump(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.input_locked = -1;
    obj.pressed_input = 0;
    obj.wall_climbable = 0;
    return_value = player_check_wall_jump(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, player_check_wall_jump_expected, 1);
}

static const u32 player_is_pushing_wall_expected[] = { 0u };
static u32 test_player_is_pushing_wall(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.input_locked = -1;
    observed_values[0] = (u32)player_is_pushing_wall(&obj);
    return c_test_observe(0, row, observed_values, player_is_pushing_wall_expected, 1);
}

#include "support/player_archive_context.h"
ARCHIVE_CAPSULE(CAPSULE_ANIM_5, 5)
ARCHIVE_CAPSULE(CAPSULE_ANIM_6, 6)
ARCHIVE_CAPSULE(CAPSULE_ANIM_C, 0xC)
ARCHIVE_CAPSULE(CAPSULE_NO_TURN, 0xA)
static const CTestCase player_check_capsule_archive_cases[]
    = {
          CAPSULE_ANIM_5,
          CAPSULE_ANIM_6,
          CAPSULE_ANIM_C,
          CAPSULE_NO_TURN,
          capsule_hurt_blocked,
      };

static const u32 player_check_capsule_archive_cases_expected[] = { 0x40001326u, 0x40001326u, 0x40001326u, 0x4000130Au, 0x101u };
#include "support/state_cases.h"

#define PC(flags) (player_reset(2, 1, 0), pl.unk88.bytes.collision_flags = flags, pl.hp = 8)
#ifndef VERSION_DEMO
#define PC_FIRST 0
static void pc_peak_ceiling(void)
{
    PC(PLAYER_COLLIDE_CEILING);
    pl.y_vel.val = 0x10000;
    player_extra = player_leap_check_peak(&pl);
}
static void pc_peak_fall(void)
{
    PC(0);
    pl.unk2 = 1;
    player_extra = player_leap_check_peak(&pl) | visual_objects[0].id << 8;
}
static void pc_peak_rise(void)
{
    PC(0);
    pl.y_vel.val = 0x10000;
    pl.unk2C = 0x1000;
    player_extra = player_leap_check_peak(&pl);
}
static void pc_wall_right_hit(void)
{
    PC(PLAYER_COLLIDE_RIGHT);
    pl.unk15 = PLAYER_FACING_RIGHT;
    pl.x_vel.val = 0x10000;
    player_leap_check_wall(&pl);
}
static void pc_wall_right_stop(void)
{
    PC(0);
    pl.unk15 = PLAYER_FACING_RIGHT;
    player_leap_check_wall(&pl);
}
static void pc_wall_right_go(void)
{
    PC(0);
    pl.unk15 = PLAYER_FACING_RIGHT;
    pl.x_vel.val = 0x10000;
    player_leap_check_wall(&pl);
}
static void pc_wall_left_hit(void)
{
    PC(PLAYER_COLLIDE_LEFT);
    pl.x_vel.val = -0x10000;
    player_leap_check_wall(&pl);
}
static void pc_wall_left_stop(void)
{
    PC(0);
    player_leap_check_wall(&pl);
}
static void pc_wall_left_go(void)
{
    PC(0);
    pl.x_vel.val = -0x10000;
    player_leap_check_wall(&pl);
}
#else
#define PC_FIRST 9
#endif
static void pc_damage_clone(void)
{
    PC(0xC);
    pl.is_clone = 1;
    player_check_damage(&pl);
    player_extra = (u8)pl.hp;
}
static void pc_damage_idle(void)
{
    PC(0xC);
    pl.unk5 = 0;
    player_check_damage(&pl);
    player_extra = (u8)pl.hp;
}
static void pc_damage_beam(void)
{
    PC(0xC);
    pl.unk5 = PLAYER_BEAM_OUT;
    player_check_damage(&pl);
    player_extra = (u8)pl.hp;
}
static void pc_damage_crushed(void)
{
    PC(0xC);
    player_check_damage(&pl);
    player_extra = (u8)pl.hp | pl.state << 8 | engine_obj.gameplay_locked << 16;
}
static void pc_damage_squeezed(void)
{
    PC(3);
    player_check_damage(&pl);
    player_extra = (u8)pl.hp | pl.state << 8;
}
static void pc_damage_spikes(void)
{
    PC(0);
    pl.touching_spikes = 1;
    player_check_damage(&pl);
    player_extra = (u8)pl.hp | pl.state << 8;
}
static void pc_damage_spikes_blink(void)
{
    PC(0);
    pl.touching_spikes = 1;
    pl.invincibility_timer = 3;
    player_check_damage(&pl);
    player_extra = (u8)pl.hp | (u8)pl.invincibility_timer << 8;
}
static void pc_damage_spikes_immune(void)
{
    PC(0);
    pl.touching_spikes = 1;
    SPIKE_IMMUNE_SET(pl, 1);
    player_check_damage(&pl);
    player_extra = (u8)pl.hp;
}
static void pc_damage_blink_end(void)
{
    PC(0);
    pl.invincibility_timer = 1;
    pl.hurt_phase = 2;
    player_check_damage(&pl);
    player_extra = (u8)pl.invincibility_timer | pl.hurt_phase << 8;
}
static void pc_walk_locked(void)
{
    PC(0);
    pl.input_locked = 1;
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_extra = player_check_walk_start(&pl);
}
static void pc_walk_none(void)
{
    PC(0);
    player_extra = player_check_walk_start(&pl);
}
static void pc_walk_right(void)
{
    PC(0);
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_extra = player_check_walk_start(&pl);
}
static void pc_walk_right_wall(void)
{
    PC(PLAYER_COLLIDE_RIGHT);
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_extra = player_check_walk_start(&pl);
}
static void pc_walk_left(void)
{
    PC(0);
    pl.input.buttons.held = PLAYER_INPUT_LEFT;
    player_extra = player_check_walk_start(&pl);
}
static void pc_walk_left_wall(void)
{
    PC(PLAYER_COLLIDE_LEFT);
    pl.input.buttons.held = PLAYER_INPUT_LEFT;
    player_extra = player_check_walk_start(&pl);
}
static void pc_ladder_cooldown(void)
{
    PC(0);
    pl.shot_cooldown = 1;
    player_extra = player_check_ladder(&pl);
}

static void (*const player_check_states_cases[])(void) = {
#ifndef VERSION_DEMO
    pc_peak_ceiling,
    pc_peak_fall,
    pc_peak_rise,
    pc_wall_right_hit,
    pc_wall_right_stop,
    pc_wall_right_go,
    pc_wall_left_hit,
    pc_wall_left_stop,
    pc_wall_left_go,
#endif
    pc_damage_clone,
    pc_damage_idle,
    pc_damage_beam,
    pc_damage_crushed,
    pc_damage_squeezed,
    pc_damage_spikes,
    pc_damage_spikes_blink,
    pc_damage_spikes_immune,
    pc_damage_blink_end,
    pc_walk_locked,
    pc_walk_none,
    pc_walk_right,
    pc_walk_right_wall,
    pc_walk_left,
    pc_walk_left_wall,
    pc_ladder_cooldown,
};
static const u32 player_check_states_expected[] = { 0xFF000302u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0xFF000302u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x2701u, 0x102u, 0x640000u, 0xC70000u, 0u, 0xF000u, 0x100000u, 0xFFu, 0u, 0x202u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x202u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0x10000u, 0u, 0u, 0x40FFu, 0u, 0x202u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x202u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0xFFFF0000u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 8u, 0x100u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 8u, 0x101u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 8u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x10200u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x200u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x200u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x208u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 8u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0x8000u, 0u, 0u, 0x40FFu, 1u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0xFFFF8000u, 0u, 0u, 0xFFu, 1u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x102u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u };

static u32 test_player_check_states(u32 row)
{
    return player_run(player_check_states_cases[row], row, &player_check_states_expected[(row + PC_FIRST) * 8]);
}

#ifndef VERSION_DEMO
static u32 gfx[16], frames[16];
static struct VisualObj expected_pool[32];
static u32 peak(u32 row)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_before;
    u32 full = row % 2, ceiling = row / 2 % 2, face = row / 4 % 2, layer = row / 8, i;
    engine_obj.cur_character = 1;
    engine_before = engine_obj;
    for (i = 0; i < COUNT(gfx); i++)
        gfx[i] = frames[i] = i < 8 ? 32 + i * 4 : 0x24680000 + i;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && !full ? 0 : 1;
    memcpy(expected_pool, visual_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = 1;
    obj.unk5 = PLAYER_ZERO_RYUENJIN;
    obj.unk6 = 1;
    obj.hp = 24;
    obj.boss_flags = 8;
    obj.attacking = obj.air_state = 1;
    SPIKE_IMMUNE_SET(obj, 1);
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.bg_offset = layer;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    obj.x_vel.val = 0x20000;
    obj.unk28 = 0x1000;
    obj.y_vel.val = ceiling ? 0x10000 : 0;
    obj.unk88.bytes.collision_flags = ceiling ? PLAYER_COLLIDE_CEILING : 0;
    obj.animation_table = (u32**)D_8011AFF0;
    set_animation(ANIMATED_OBJECT(&obj), 0x65);
    expected = obj;
    expected.unk38 = (u8*)gfx + 36;
    expected.unk3C = (u8*)frames + 52;
    expected.unk17 = 0x66;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)D_8011AFF0[0x66];
    expected.animation_step.packed = C_TEST_STEP(0x9C010003);
    expected.y_vel.val = 0;
    expected.x_vel.val = expected.unk28 = 0;
    expected.air_state = -1;
    expected.unk6 = 3;
    if (!full) {
        expected_pool[31].active = 1;
        expected_pool[31].id = 39;
        expected_pool[31].bg_offset = layer;
    }
    assert(player_leap_check_peak(&obj) == 1);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i < 8 ? 32 + i * 4 : 0x24680000 + i) && frames[i] == gfx[i]);
    return 1;
}
#define PEAK_CASES 24
#define HELPER_CASES COUNT(check_helpers)
#else
#define PEAK_CASES 0
#define HELPER_CASES (COUNT(check_helpers) - 5)
#endif

static const struct {
    u8 check, step, unk2, facing;
    u16 held, pressed, collide;
    s8 hurt, ride, timer;
    s32 speed;
    u8 capsule, attribute;
} check_helpers[] = {
    { 0, 2, 1, 0, PLAYER_INPUT_RIGHT, 0, 0, 0, 0, 0, 0 },
    { 0, 2, 1, 0, PLAYER_INPUT_RIGHT, 0, PLAYER_COLLIDE_RIGHT, 0, 0, 0, 0 },
    { 0, 2, 1, 0, PLAYER_INPUT_LEFT, 0, PLAYER_COLLIDE_LEFT, 0, 0, 0, 0 },
    { 0, 2, 1, 0, PLAYER_INPUT_LEFT, 0, 0, 0, 0, 0, 0 },
    { 1, PLAYER_BEAM_IN, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, PLAYER_BEAM_OUT, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 1, 2, 0, 0, 0, 0, 0, 0, -1, 0, 0 },
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 2, 2, 0, 1, 0, 0, PLAYER_COLLIDE_RIGHT, 0, 0, 5, FIXED(6.5) },
    { 2, 2, 0, 1, PLAYER_INPUT_RIGHT, 0, 0, 0, 0, 1, FIXED(1) },
    { 2, 2, 0, 0, PLAYER_INPUT_DASH, 0, 0, 0, 0, 5, FIXED(-6.5) },
    { 2, 2, 0, 0, PLAYER_INPUT_RIGHT | PLAYER_INPUT_DASH, 0, 0, 0, 0, 5, FIXED(-6.5) },
    { 2, 2, 0, 1, PLAYER_INPUT_LEFT, 0, 0, 0, 0, 5, FIXED(6.5) },
    { 3, PLAYER_BEAM_IN, 0, 0, 0, PLAYER_INPUT_RIGHT, 0, 0, 0, 5, 0 },
    { 3, PLAYER_BEAM_OUT, 0, 0, 0, PLAYER_INPUT_RIGHT, 0, 0, 0, 5, 0 },
    { 3, 2, 0, 0, 0, PLAYER_INPUT_RIGHT, 0, 0, 0, 5, 0 },
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 4, 2, 0, 0, PLAYER_INPUT_RIGHT, PLAYER_INPUT_DASH, PLAYER_COLLIDE_RIGHT, 0, 0, 0, 0 },
    { 4, 2, 0, 0, 0, PLAYER_INPUT_DASH, PLAYER_COLLIDE_LEFT, 0, 0, 0, 0 },
    { 5, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 6, 2, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
    { 6, 2, 0, 0, 0, 0, PLAYER_COLLIDE_LEFT, 0, 0, 0, 0 },
    { 7, 0x11, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 8, 2, 0, 0, PLAYER_INPUT_DOWN, 0, 0, 0, 0, 0, 0, 0, 0x21 },
    { 9, 2, 0, 0, PLAYER_INPUT_UP, 0, 0, 0, 0, 0, 0, 0, 0x20 },
    { 10, 2, 0, 0, PLAYER_INPUT_UP, 0, 0, 0, 0, 0, 0, 0, 0x21 },
    { 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x22 },
    { 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x21 },
    { 10, 2, 0, 0, 0, 0x80, 0, 0, 0, 0, 0, 0, 0x20 },
    { 11, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 12, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 12, 2, 0, 0, 0, 0, 0, 0, 0, -5, 0 },
    { 12, 2, 0, 0, 0, 0, 0, 0, 0, -1, 0 },
    { 8, 2, 0, 0, PLAYER_INPUT_DOWN, 0, 0, 0, 0, 0, 0, 0, 0x20 },
};
static const u32 check_helpers_expected[COUNT(check_helpers)][2] = {
#include "player_check_helpers_expected.inc"
};

static u8 check_sound_rows[0x40];

static u32 test_check_helpers(u32 row)
{
    u32 seen[2], result = 0xFF;
#ifdef VERSION_DEMO
    if (row >= 10)
        row += 5;
#endif
    player_reset(check_helpers[row].step, 0, 0);
    pl.unk2 = check_helpers[row].unk2;
    pl.animation_table = (u32**)(pl.unk2 ? D_8011AFF0 : D_80119DF0);
    pl.unk15 = check_helpers[row].facing ? PLAYER_FACING_RIGHT : 0;
    pl.input.buttons.held = check_helpers[row].held;
    pl.pressed_input = check_helpers[row].pressed;
    pl.unk88.bytes.collision_flags = check_helpers[row].collide;
    pl.hurt_phase = check_helpers[row].hurt;
    pl.ride_state = check_helpers[row].ride;
    pl.x_vel.val = check_helpers[row].speed;
    pl.attacking = 1;
    pl.capsule_state = check_helpers[row].capsule;
    player_attrs[0] = C_TEST_PSX_WORD(check_helpers[row].attribute);
#ifndef MMX4_SATURN
    D_80141F50[1] = check_sound_rows;
#endif
    switch (check_helpers[row].check) {
    case 0:
        result = player_check_walk(&pl);
        break;
    case 1:
        player_check_fall(&pl);
        break;
#ifndef VERSION_DEMO
    case 2:
        pl.dash_timer = check_helpers[row].timer;
        result = player_dash_should_end(&pl);
        break;
#endif
    case 3:
        pl.unk88.bytes.timer = check_helpers[row].timer;
        pl.double_tap_direction = PLAYER_INPUT_RIGHT;
        player_update_double_tap(&pl);
        result = pl.double_tap_dash | (u32)pl.unk88.bytes.timer << 4;
        break;
    case 4:
        result = player_check_dash_input(&pl);
        break;
    case 5:
        player_check_ride(&pl);
        result = (u8)pl.ride_state;
        break;
    case 6:
        pl.shot_cooldown = check_helpers[row].timer;
        pl.armor_parts = 8;
        result = player_check_air_move(&pl);
        break;
    case 8:
        result = player_check_ladder(&pl);
        break;
    case 9:
        result = player_check_ladder_air(&pl);
        break;
    case 10:
        result = func_80033FF0(&pl);
        break;
    case 11:
        engine_obj.unkF = 1;
        result = player_check_script(&pl);
        break;
    case 12:
        pl.x_pos.i.hi = 0x40 + check_helpers[row].timer;
        pl.script_state = 1;
        player_script_walk_to_mark(&pl);
        result = (u8)pl.script_state;
        pl.x_vel.val = pl.x_pos.i.hi;
        break;
    case 7:
        pl.hit_facing = pl.unk15;
        pl.hurt_type = 1;
        func_80033D54(&pl);
        result = (u8)pl.hurt_phase;
        break;
    }
    seen[0] = (result & 0xFF) | (u32)(u8)pl.unk5 << 8 | (u32)(u8)pl.attacking << 16 | (u32)C_TEST_PSX_FACING(pl.unk15) << 24;
    seen[1] = pl.x_vel.val;
    return c_test_observe(0, row, seen, check_helpers_expected[row], 2);
}

static u32 air_move_hover(u32 row)
{
    player_reset(2, 0, 0);
    pl.unk2 = 0;
    pl.animation_table = (u32**)D_80119DF0;
    pl.armor_parts = 8;
    pl.pressed_input = PLAYER_INPUT_JUMP;
    pl.x_vel.val = pl.y_vel.val = 0x12345;
    assert(player_check_air_move(&pl) == 1);
    assert(pl.unk5 == PLAYER_HOVER && pl.unk6 == 0 && pl.air_action == 4 && pl.hover_timer == 0xB4);
    assert(pl.x_vel.val == 0 && pl.y_vel.val == 0);
    return 1;
}

static u32 damage_without_health(u32 row)
{
#ifndef MMX4_SATURN
    D_80141F50[1] = check_sound_rows;
#endif
    PC(0);
    pl.hp = 0;
    player_check_damage(&pl);
    assert(pl.unk5 == 0x11);
    assert(pl.unk6 == 0);
    assert(pl.hurt_phase == 1);
    assert(pl.hp == 0);
    assert(pl.state == 1 && engine_obj.gameplay_locked == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "player_check_states", 0, 0, COUNT(player_check_states_cases), test_player_check_states },
    { "check_helpers", 0, 0, HELPER_CASES, test_check_helpers },
    { "player_check_wall_jump", 0, 0, 1, test_player_check_wall_jump },
    { "player_is_pushing_wall", 0, 0, 1, test_player_is_pushing_wall },
    { "player_check_capsule_archive", player_check_capsule_archive_cases, player_check_capsule_archive_cases_expected, COUNT(player_check_capsule_archive_cases), 0 },
#ifndef VERSION_DEMO
    { "Zero_own_Ryuenjin_peak_and_ceiling_full_last_visual_slot", NULL, NULL, 24, peak },
#endif
    { "air_move_hover", NULL, NULL, 1, air_move_hover },
    { "damage_without_health", NULL, NULL, 1, damage_without_health },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(player_check_states_cases) + HELPER_CASES + 1 + 1 + COUNT(player_check_capsule_archive_cases) + PEAK_CASES + 2;
