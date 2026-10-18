#include "test_runtime.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/player.h"
#include "support/player_cases.h"
#include "main/player_animations_2.h"
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
    pl.unk15 = 0x40;
    pl.x_vel.val = 0x10000;
    player_leap_check_wall(&pl);
}
static void pc_wall_right_stop(void)
{
    PC(0);
    pl.unk15 = 0x40;
    player_leap_check_wall(&pl);
}
static void pc_wall_right_go(void)
{
    PC(0);
    pl.unk15 = 0x40;
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
    pl.spike_immune = 1;
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
    pc_peak_ceiling,
    pc_peak_fall,
    pc_peak_rise,
    pc_wall_right_hit,
    pc_wall_right_stop,
    pc_wall_right_go,
    pc_wall_left_hit,
    pc_wall_left_stop,
    pc_wall_left_go,
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
    return player_run(player_check_states_cases[row], row, &player_check_states_expected[row * 8]);
}

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
    obj.attacking = obj.air_state = obj.spike_immune = 1;
    obj.unk15 = face ? 0x40 : 0;
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
    expected.animation_step.packed = 0x9C010003;
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

const struct CTestGroup c_test_groups[] = {
    { "player_check_states", 0, 0, COUNT(player_check_states_cases), test_player_check_states },
    { "player_check_wall_jump", 0, 0, 1, test_player_check_wall_jump },
    { "player_is_pushing_wall", 0, 0, 1, test_player_is_pushing_wall },
    { "player_check_capsule_archive", player_check_capsule_archive_cases, player_check_capsule_archive_cases_expected, COUNT(player_check_capsule_archive_cases), 0 },
    { "Zero_own_Ryuenjin_peak_and_ceiling_full_last_visual_slot", NULL, NULL, 24, peak },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(player_check_states_cases) + 1 + 1 + COUNT(player_check_capsule_archive_cases) + 24;
