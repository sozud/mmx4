#include "test_runtime.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/55C4.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_animations.h"
#include "main/player_weapon.h"
#include "main/player_common.h"
#include "main/collision.h"
#include "main/sprite_animations.h"
void player_zero_attack_finish(struct PlayerObj* self);
void player_zero_ryuenjin_fall(struct PlayerObj*);
void player_zero_ryuenjin_peak(struct PlayerObj*);
void player_zero_ryuenjin_rise(struct PlayerObj*);
void player_zero_ryuenjin_spawn_flame(struct PlayerObj* self);
void player_zero_ryuenjin_start(struct PlayerObj*);
void player_zero_hyouretsuzan_land(struct PlayerObj*);
s32 func_80039F28(struct PlayerObj*);
void player_zero_hyouretsuzan_drop(struct PlayerObj*);

static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static s32 gfx_archive[4] = { 8, 12, 0x11223344, 0x55667788 };
static s32 zero_shippuuga_cancel_context_sprite_archive[12] = { 24, 28, 32, 36, 40, 44, 1, 2, 3, 4, 5, 6 };
static Palette zero_shippuuga_cancel_context_palette_bank[1];
static u16 zero_shippuuga_cancel_context_palette_storage[18];
static u32 cancel_case(u32 mode, u32 observation)
{
    struct PlayerObj* obj = &g_Player;
    struct PlayerObj before;
    struct EngineObj engine_before;
    struct WeaponObj pool_before[16];
    struct BackgroundObj bg_before[3];
    struct Unk_unk68 bounds = { 0, 0, 4, 4 };
    s32 result;
    u32 i, actual;
    memset(obj, 0, sizeof(*obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = 1;
    obj->active = 0x41;
    obj->unk2 = 1;
    obj->state = 1;
    obj->unk5 = PLAYER_ZERO_SHIPPUUGA;
    obj->unk6 = 1;
    obj->attacking = 1;
    obj->voice_timer = 1;
    obj->unk68 = &bounds;
    obj->x_pos.val = 100 * 65536 + 0x1234;
    obj->y_pos.val = 200 * 65536 + 0x5678;
    obj->animation_table = (u32**)D_8011AFF0;
    set_animation(obj, 0x68);
    obj->animation_step.fields.event = 0x40;
    if (mode == 0)
        obj->input_locked = 1;
    if (mode == 1)
        obj->input.buttons.held = PLAYER_INPUT_UP;
    if (mode == 2) {
        obj->boss_flags = 1;
        obj->pressed_input = PLAYER_INPUT_SPECIAL;
    }
    if (mode == 3)
        obj->pressed_input = PLAYER_INPUT_SHOOT;
    need_palette_load = 0x80;
    for (i = 0; i < 16; i++)
        zero_shippuuga_cancel_context_palette_bank[0][i] = 0x1200 + i;
    for (i = 0; i < 18; i++)
        zero_shippuuga_cancel_context_palette_storage[i] = 0xBEEF;
    for (i = 0; i < 2; i++)
        D_8013E198[i] = -1;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0x20;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    TEST_PLAYER_GFX = (u8*)gfx_archive;
    TEST_SPRITE_FRAMES = (u8*)zero_shippuuga_cancel_context_sprite_archive;
    TEST_PALETTE = (u8*)&zero_shippuuga_cancel_context_palette_storage[1];
    TEST_PALETTE_BANK = (u8*)zero_shippuuga_cancel_context_palette_bank;
    before = *obj;
    engine_before = engine_obj;
    memcpy(pool_before, weapon_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    result = player_zero_shippuuga_cancel(obj);
    if (mode != 0) {
        before.unk5 = obj->unk5;
        before.unk6 = obj->unk6;
        before.attacking = obj->attacking;
        before.air_state = obj->air_state;
        before.dash_momentum = obj->dash_momentum;
        before.air_action = obj->air_action;
        before.x_pos = obj->x_pos;
        before.y_pos = obj->y_pos;
        before.x_vel = obj->x_vel;
        before.y_vel = obj->y_vel;
        before.unk28 = obj->unk28;
        before.unk2C = obj->unk2C;
        before.unk17 = obj->unk17;
        before.previous_animation_index = 0xFF;
        before.animation_step = obj->animation_step;
        before.animation_cursor = obj->animation_cursor;
        before.unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, D_8011AF60[obj->unk17] ? 1 : 0);
        before.unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, D_8011AF60[obj->unk17] ? 5 : 0);
    }
    for (i = 0; i < sizeof(*obj); i++)
        assert(((u8*)obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    for (i = 0; i < sizeof(pool_before); i++)
        assert(((u8*)weapon_objects)[i] == ((u8*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before); i++)
        assert(((u8*)background_objects)[i] == ((u8*)bg_before)[i]);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == 0x20 && gfx_archive[0] == 8 && gfx_archive[1] == 12);
    assert(bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    for (i = 0; i < 6; i++)
        assert(zero_shippuuga_cancel_context_sprite_archive[i] == 24 + i * 4 && zero_shippuuga_cancel_context_sprite_archive[i + 6] == i + 1);
    assert(zero_shippuuga_cancel_context_palette_storage[0] == 0xBEEF && zero_shippuuga_cancel_context_palette_storage[17] == 0xBEEF);
    for (i = 0; i < 16; i++) {
        assert(zero_shippuuga_cancel_context_palette_bank[0][i] == 0x1200 + i);
        assert(zero_shippuuga_cancel_context_palette_storage[i + 1] == (mode == 1 ? 0x1200 + i : 0xBEEF));
    }
    assert(need_palette_load == (mode == 1 ? 0x81 : 0x80));
    switch (observation) {
    case 0:
        actual = (u8)result | ((u32)(u8)obj->unk5 << 8) | ((u32)(u8)obj->unk6 << 16) | ((u32)(u8)obj->attacking << 24);
        break;
    case 1:
        actual = obj->x_pos.val;
        break;
    case 2:
        actual = obj->y_pos.val;
        break;
    case 3:
        actual = obj->x_vel.val;
        break;
    case 4:
        actual = obj->y_vel.val;
        break;
    case 5:
        actual = (u8)obj->air_state | ((u32)(u8)obj->air_action << 8) | ((u32)(u8)obj->dash_momentum << 16);
        break;
    case 6:
        actual = obj->animation_step.packed;
        break;
    case 7:
        actual = obj->unk28;
        break;
    case 8:
        actual = obj->unk2C;
        break;
    default:
        actual = (u8)obj->unk17 | ((u32)obj->previous_animation_index << 8) | ((u32)(obj->animation_cursor - (u32*)D_8011AFF0[(u8)obj->unk17]) << 16);
        break;
    }
    for (i = 0; i < 2; i++)
        assert(D_8013E198[i] == -1);
    return actual;
}
static const u32 zero_shippuuga_cancel_context_cases_expected[] = { 0x1013B00u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x9B014001u, 0x0u, 0x0u, 0xFF68u, 0xE01u, 0x680000u, 0xC80000u, 0x0u, 0x10000u, 0x1u, 0xC2010003u, 0x0u, 0x0u, 0xFF1Bu, 0x1013501u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x56010002u, 0x0u, 0x0u, 0xFF5Fu, 0x1013001u, 0x641234u, 0xC85678u, 0x0u, 0x0u, 0x0u, 0x3D010001u, 0x0u, 0x0u, 0xFF58u };
static u32 zero_shippuuga_cancel_context_cases_row(u32 row)
{
    return cancel_case(row / 10, row % 10);
}

static const u32 player_hover_steer_expected[] = { 0u, 1u, 0u, 0u };
static u32 test_player_hover_steer(u32 row)
{
    u32 observed_values[4];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.input.buttons.held = 514;
    obj.unk88.bytes.collision_flags = 2;
    return_value = player_hover_steer(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.hover_bob;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, player_hover_steer_expected, 4);
}

struct player_nova_strike_hit_wall_case {
    u32 collision_flags, unk15;
    u32 expected[5];
};
static const struct player_nova_strike_hit_wall_case player_nova_strike_hit_wall_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 5, 255, { 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_player_nova_strike_hit_wall(u32 row)
{
    const struct player_nova_strike_hit_wall_case* c = &player_nova_strike_hit_wall_cases[row];
    u32 observed_values[5];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.unk88.bytes.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    return_value = player_nova_strike_hit_wall(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk28;
    observed_values[2] = (u32)obj.unk2C;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct player_zero_hyouretsuzan_start_case {
    u32 input_locked, held, event;
    u32 expected[8];
};
static const struct player_zero_hyouretsuzan_start_case player_zero_hyouretsuzan_start_cases[] = {
    { -1, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 771, 16, { 0xFFFFFFFFu, 0u, 0x40u, 0u, 0x4200u, 1u, 0u, 0xFFFD0000u } },
};
static u32 test_player_zero_hyouretsuzan_start(u32 row)
{
    const struct player_zero_hyouretsuzan_start_case* c = &player_zero_hyouretsuzan_start_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.input_locked = c->input_locked;
    obj.input.buttons.held = c->held;
    obj.animation_step.fields.event = c->event;
    player_zero_hyouretsuzan_start(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.animation_step.fields.event;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk28;
    observed_values[4] = (u32)obj.unk2C;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.x_vel.val;
    observed_values[7] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

#include "support/player_archive_context.h"
ARCHIVE_CLONE(0, 0)
ARCHIVE_CLONE(0, 1)
ARCHIVE_CLONE(1, 0)
ARCHIVE_CLONE(1, 1)
ARCHIVE_CLONE(2, 0)
ARCHIVE_CLONE(2, 1)
ARCHIVE_CLONE(3, 0)
ARCHIVE_CLONE(3, 1)
static const CTestCase soul_body_clone_archive_cases[]
    = { ARCHIVE_CLONE_ENTRY(0, 0) ARCHIVE_CLONE_ENTRY(0, 1) ARCHIVE_CLONE_ENTRY(1, 0) ARCHIVE_CLONE_ENTRY(1, 1) ARCHIVE_CLONE_ENTRY(2, 0) ARCHIVE_CLONE_ENTRY(2, 1) ARCHIVE_CLONE_ENTRY(3, 0) ARCHIVE_CLONE_ENTRY(3, 1) };

static const u32 soul_body_clone_archive_cases_expected[] = { 0x6C2468u, 0x100907u, 0x12C2468u, 0x80007u, 0x12C2468u, 0x80002u, 0x242468u, 0x400007u };
#include "support/player_cases.h"
#define HOLD(e) (pl.animation_step.fields.event = e, pl.animation_step.fields.duration = 9)
static void ps_ryuenjin_locked(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    player_extra = player_zero_check_ryuenjin(&pl);
}
static void ps_ryuenjin(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 8;
    pl.input.buttons.held = PLAYER_INPUT_UP;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    player_extra = player_zero_check_ryuenjin(&pl);
}
static void ps_ryuenjin_launch_left(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 0, 0x65);
    HOLD(0x20);
    player_zero_ryuenjin_start(&pl);
}
static void ps_ryuenjin_launch_right(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 0, 0x65);
    pl.unk15 = 0x40;
    HOLD(0x20);
    player_zero_ryuenjin_start(&pl);
}
static void ps_ryuenjin_rise(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 1, 0x65);
    pl.y_vel.val = 0x40000;
    main_bss_state.frame_counter = 2;
    player_zero_ryuenjin_rise(&pl);
}
static void ps_ryuenjin_peak(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 2, 0x65);
    pl.y_vel.val = 0x10000;
    main_bss_state.frame_counter = 2;
    player_zero_ryuenjin_peak(&pl);
}
static void ps_flame_odd(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 2, 0x65);
    main_bss_state.frame_counter = 1;
    player_zero_ryuenjin_spawn_flame(&pl);
}
static void ps_ryuenjin_land(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 3, 0x65);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    player_zero_ryuenjin_fall(&pl);
}
static void ps_ryuenjin_fall(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 3, 0x65);
    pl.animation_step.fields.relative_step = 0;
    pl.y_vel.val = -0x10000;
    player_zero_ryuenjin_fall(&pl);
}
static void ps_ryuenjin_falling(void)
{
    player_reset(PLAYER_ZERO_RYUENJIN, 3, 0x65);
    pl.animation_step.fields.relative_step = 1;
    pl.y_vel.val = -0x10000;
    player_zero_ryuenjin_fall(&pl);
}
static void ps_raijin_start(void)
{
    player_reset(0x35, 0, 0x60);
    pl.input_locked = 1;
    player_zero_raijingeki(&pl);
}
static void ps_raijin_voice(void)
{
    player_reset(0x35, 1, 0x60);
    HOLD(0x10);
    pl.input_locked = 1;
    player_zero_raijingeki(&pl);
}
static void ps_raijin_cancel(void)
{
    player_reset(0x35, 1, 0x60);
    HOLD(0x40);
    player_zero_raijingeki(&pl);
}
static void ps_raijin_hold(void)
{
    player_reset(0x35, 1, 0x60);
    player_zero_raijingeki(&pl);
}
static void ps_fall_slash_land_saber(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 1, 0x5B);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.attacking = 1;
    player_zero_fall_slash(&pl);
}
static void ps_fall_slash_land_spin(void)
{
    player_reset(PLAYER_ZERO_SPIN_FALL_SLASH, 1, 0x64);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.attacking = 1;
    player_zero_fall_slash(&pl);
}
static void ps_fall_slash_land(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 1, 0x5B);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    player_zero_fall_slash(&pl);
}
static void ps_fall_slash_start(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 0, 0x5B);
    pl.attacking = 1;
    player_zero_fall_slash(&pl);
}
static void ps_fall_slash_spin(void)
{
    player_reset(PLAYER_ZERO_SPIN_FALL_SLASH, 1, 0x64);
    pl.attacking = 1;
    HOLD(0);
    pl.animation_step.fields.relative_step = 1;
    player_zero_fall_slash(&pl);
}
static void ps_fall_slash_end(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 1, 0x5B);
    pl.attacking = 1;
    HOLD(0);
    pl.animation_step.fields.relative_step = 0;
    player_zero_fall_slash(&pl);
}
static void ps_check_fall_x(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.unk2 = 0;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_check_fall_locked(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.input_locked = 1;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_hyouretsuzan_left(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.boss_flags = 2;
    pl.input.buttons.held = PLAYER_INPUT_DOWN | PLAYER_INPUT_LEFT;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_hyouretsuzan_right(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.boss_flags = 2;
    pl.input.buttons.held = PLAYER_INPUT_DOWN | PLAYER_INPUT_RIGHT;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_spin_slash(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.boss_flags = 4;
    pl.pressed_input = PLAYER_INPUT_SHOOT;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_air_slash(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.pressed_input = PLAYER_INPUT_SHOOT;
    player_extra = player_zero_check_fall_slash(&pl);
}
static void ps_finish_idle(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    pl.attacking = 1;
    pl.animation_step.fields.relative_step = 0;
    player_zero_attack_finish(&pl);
}
static void ps_finish_wait(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    pl.attacking = 1;
    pl.animation_step.fields.relative_step = 1;
    player_zero_attack_finish(&pl);
}
static void ps_double_jump(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.boss_flags = 4;
    pl.pressed_input = PLAYER_INPUT_JUMP;
    player_extra = player_zero_check_double_jump(&pl);
}
static void ps_double_jump_no(void)
{
    player_reset(PLAYER_FALL, 0, 0);
    pl.boss_flags = 4;
    player_extra = player_zero_check_double_jump(&pl);
}
static void ps_combo(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    HOLD(0x20);
    pl.pressed_input = 0x10;
    player_extra = func_8003A1DC(&pl);
}
static void ps_combo_locked(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    pl.input_locked = 1;
    player_extra = func_8003A1DC(&pl);
}
static void ps_combo_early(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    player_extra = func_8003A1DC(&pl);
}
static void ps_combo_raijin(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    HOLD(0x20);
    pl.boss_flags = 1;
    pl.pressed_input = 0x20;
    player_extra = func_8003A1DC(&pl);
}
static void ps_combo_none(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    HOLD(0x20);
    player_extra = func_8003A1DC(&pl);
}
static void ps_saber_start(void)
{
    player_reset(PLAYER_ZERO_SABER, 0, 0x58);
    pl.input_locked = 1;
    player_zero_saber(&pl);
}
static void ps_saber_cancel(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    HOLD(0x40);
    player_zero_saber(&pl);
}
static void ps_saber_hold(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x58);
    HOLD(0);
    player_zero_saber(&pl);
}
static void ps_rising_x(void)
{
    player_reset(PLAYER_IDLE, 0, 0x62);
    pl.unk2 = 0;
    HOLD(0x80);
    player_rising_fire(&pl);
}
static void ps_rising_charged(void)
{
    player_reset(PLAYER_IDLE, 0, 0x63);
    pl.unk2 = 0;
    HOLD(0x80);
    pl.attacking = 1;
    player_rising_fire(&pl);
}
static void ps_rising_air(void)
{
    player_reset(PLAYER_IDLE, 0, 0x63);
    pl.unk2 = 0;
    player_rising_fire(&pl);
}

static void (*const player_special_states_cases[])(void) = {
    ps_ryuenjin_locked,
    ps_ryuenjin,
    ps_ryuenjin_launch_left,
    ps_ryuenjin_launch_right,
    ps_ryuenjin_rise,
    ps_ryuenjin_peak,
    ps_flame_odd,
    ps_ryuenjin_land,
    ps_ryuenjin_fall,
    ps_ryuenjin_falling,
    ps_raijin_start,
    ps_raijin_voice,
    ps_raijin_cancel,
    ps_raijin_hold,
    ps_fall_slash_land_saber,
    ps_fall_slash_land_spin,
    ps_fall_slash_land,
    ps_fall_slash_start,
    ps_fall_slash_spin,
    ps_fall_slash_end,
    ps_check_fall_x,
    ps_check_fall_locked,
    ps_hyouretsuzan_left,
    ps_hyouretsuzan_right,
    ps_spin_slash,
    ps_air_slash,
    ps_finish_idle,
    ps_finish_wait,
    ps_double_jump,
    ps_double_jump_no,
    ps_combo,
    ps_combo_locked,
    ps_combo_early,
    ps_combo_raijin,
    ps_combo_none,
    ps_saber_start,
    ps_saber_cancel,
    ps_saber_hold,
    ps_rising_x,
    ps_rising_charged,
    ps_rising_air,
};
static const u32 player_special_states_expected[] = { 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1010039u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 1u, 0x139u, 0x640000u, 0xC80000u, 0xFFFC0000u, 0x6C000u, 0xFFBDC000u, 0xFFu, 0u, 0x139u, 0x640000u, 0xC80000u, 0x40000u, 0x6C000u, 0xFFBDC000u, 0x40FFu, 0u, 0x239u, 0x640000u, 0xC40000u, 0u, 0x40000u, 0u, 0xFFu, 0x2100u, 0x239u, 0x640000u, 0xC70000u, 0u, 0x10000u, 0u, 0xFFu, 0x2100u, 0x239u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 8u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 7u, 0x640000u, 0xC90000u, 0u, 0xFFFF0000u, 0u, 0xFFu, 0u, 0x339u, 0x640000u, 0xC90000u, 0u, 0xFFFF0000u, 0u, 0xFFu, 0u, 0x135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 8u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 8u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10138u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 7u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 7u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 7u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10036u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10036u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 1u, 0x10138u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 6u, 0x640000u, 0xC23000u, 0u, 0x58E00u, 0x420000u, 0xFFu, 1u, 7u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x10000FFu, 0u, 0x130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x10000FFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10002u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u };

static u32 test_player_special_states(u32 row)
{
    return player_run(player_special_states_cases[row], row, &player_special_states_expected[row * 8]);
}

#include "support/state_cases.h"

#define RAI(phase, setup) (player_reset(PLAYER_ZERO_RAIJINGEKI, phase, 0x60), pl.unk2 = 1, setup, player_zero_raijingeki(&pl))
static void psx_rai_start(void)
{
    RAI(0, pl.animation_step.fields.relative_step = 1);
}
static void psx_rai_voice(void) { RAI(1, (pl.animation_step.fields.event = 0x10, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rai_locked(void) { RAI(1, (pl.input_locked = 1, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rai_cancel(void) { RAI(1, (pl.animation_step.fields.event = 0x40, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rai_cancel_walk(void) { RAI(1, (pl.animation_step.fields.event = 0x40, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1, pl.input.buttons.held = PLAYER_INPUT_RIGHT)); }
static void psx_rai_jump(void) { RAI(1, (pl.pressed_input = PLAYER_INPUT_JUMP, pl.input.buttons.held = PLAYER_INPUT_JUMP, pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rai_slash(void) { RAI(1, (pl.pressed_input = PLAYER_INPUT_SHOOT, pl.animation_step.fields.event = 0x40, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rai_ryuenjin(void) { RAI(1, (pl.boss_flags = 8, pl.input.buttons.held = PLAYER_INPUT_UP, pl.pressed_input = PLAYER_INPUT_SPECIAL, pl.animation_step.fields.event = 0x40, pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)); }
static void psx_rising_fire_script(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.script_state = 1;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_rising_fire_shoot(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.pressed_input = PLAYER_INPUT_SHOOT;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_rising_fire_jump(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.pressed_input = PLAYER_INPUT_JUMP;
    pl.input.buttons.held = PLAYER_INPUT_JUMP;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_finish_script(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x60);
    pl.script_state = 1;
    pl.animation_step.fields.relative_step = 0;
    player_zero_attack_finish(&pl);
    player_extra = pl.attacking;
}
static void psx_finish_wait(void)
{
    player_reset(PLAYER_ZERO_SABER, 1, 0x60);
    pl.attacking = 1;
    pl.animation_step.fields.relative_step = 1;
    player_zero_attack_finish(&pl);
}
static void psx_ground_clone(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.unk2 = 0;
    player_extra = player_zero_check_ground_technique(&pl);
}
static void psx_ground_locked(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.input_locked = 1;
    player_extra = player_zero_check_ground_technique(&pl);
}
static void psx_fall_land_slash(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 1, 0x5C);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.attacking = 1;
    pl.air_state = 1;
    player_zero_fall_slash(&pl);
}
static void psx_fall_land_spin(void)
{
    player_reset(PLAYER_ZERO_SPIN_FALL_SLASH, 1, 0x5C);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.attacking = 1;
    pl.air_state = 1;
    player_zero_fall_slash(&pl);
}
static void psx_fall_spin(void)
{
    player_reset(PLAYER_ZERO_SPIN_FALL_SLASH, 1, 0x5C);
    pl.attacking = 1;
    pl.air_state = 1;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_zero_fall_slash(&pl);
}
static void psx_fall_slash_start(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 0, 0x5C);
    pl.attacking = 1;
    pl.air_state = 1;
    pl.animation_step.fields.relative_step = 1;
    player_zero_fall_slash(&pl);
}
static void psx_fall_slash_end(void)
{
    player_reset(PLAYER_ZERO_FALL_SLASH, 1, 0x5C);
    pl.attacking = 1;
    pl.air_state = 1;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 0;
    player_zero_fall_slash(&pl);
}
static void psx_rising_fire_shot(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x62);
    pl.animation_step.fields.event = (s8)0x80;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
    player_extra = pl.shot_count | pl.special_shot_count << 8;
}
static void psx_rising_fire_land(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_rising_fire_walk(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_rising_fire_shoot_pose(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.shot_fired = 1;
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}
static void psx_rising_fire_fall(void)
{
    player_reset(PLAYER_RISING_FIRE, 1, 0x63);
    pl.animation_step.fields.duration = 9;
    pl.animation_step.fields.relative_step = 1;
    player_rising_fire(&pl);
}

static void (*const player_special_extra_cases[])(void) = {
    psx_rai_start,
    psx_rai_voice,
    psx_rai_locked,
    psx_rai_cancel,
    psx_rai_cancel_walk,
    psx_finish_script,
    psx_rai_jump,
    psx_rai_slash,
    psx_rai_ryuenjin,
    psx_rising_fire_script,
    psx_rising_fire_shoot,
    psx_rising_fire_jump,
    psx_finish_wait,
    psx_ground_clone,
    psx_ground_locked,
    psx_fall_land_slash,
    psx_fall_land_spin,
    psx_fall_spin,
    psx_fall_slash_start,
    psx_fall_slash_end,
    psx_rising_fire_shot,
    psx_rising_fire_land,
    psx_rising_fire_walk,
    psx_rising_fire_shoot_pose,
    psx_rising_fire_fall,
};
static const u32 player_special_extra_expected[] = { 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x10135u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 3u, 0x648000u, 0xC80000u, 0x8000u, 0u, 0u, 0x40FFu, 0u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1000006u, 0x640000u, 0xC23000u, 0u, 0x58E00u, 0x420000u, 0xFFu, 1u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1010039u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 0u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1000127u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1000006u, 0x640000u, 0xC23000u, 0u, 0x58E00u, 0x420000u, 0xFFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10130u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 8u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1010138u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x1010132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0x1000007u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x127u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x100u, 0x1000127u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 3u, 0x648000u, 0xC80000u, 0x8000u, 0u, 0u, 0x40FFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u };

static u32 test_player_special_extra(u32 row)
{
    return player_run(player_special_extra_cases[row], row, &player_special_extra_expected[row * 8]);
}

#define LONG() (pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)
static void psz_drop_land(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    pl.air_state = 1;
    player_zero_hyouretsuzan_drop(&pl);
    player_extra = misc_objects[0].id | misc_objects[7].x_pos.i.hi << 16;
}
static void psz_drop_land_right(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.unk15 = 0x40;
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    player_zero_hyouretsuzan_drop(&pl);
    player_extra = misc_objects[0].x_pos.i.hi;
}
static void psz_drop_fall(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.air_state = 1;
    pl.y_vel.val = -0x40000;
    player_zero_hyouretsuzan_drop(&pl);
}
static void psz_drop_left(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.air_state = 1;
    pl.y_vel.val = -0x40000;
    pl.input.buttons.held = PLAYER_INPUT_LEFT;
    player_zero_hyouretsuzan_drop(&pl);
}
static void psz_drop_right(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.air_state = 1;
    pl.y_vel.val = -0x40000;
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_zero_hyouretsuzan_drop(&pl);
}
static void psz_drop_locked(void)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 1, 0x61);
    pl.air_state = 1;
    pl.y_vel.val = -0x40000;
    pl.input_locked = 1;
    pl.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_zero_hyouretsuzan_drop(&pl);
}
static void psz_rakuhouha_glow(void)
{
    player_reset(PLAYER_ZERO_RAKUHOUHA, 1, 0x69);
    LONG();
    pl.animation_step.fields.event = (s8)0x80;
    player_zero_rakuhouha(&pl);
    player_extra = visual_objects[0].id | visual_objects[0].unk2 << 8;
}
static void psz_rakuhouha_burst(void)
{
    player_reset(PLAYER_ZERO_RAKUHOUHA, 1, 0x69);
    LONG();
    pl.animation_step.fields.event = 0x40;
    player_zero_rakuhouha(&pl);
    player_extra = weapon_objects[8].id | weapon_objects[8].unk2 << 8;
}
static void psz_rakuhouha_end(void)
{
    player_reset(PLAYER_ZERO_RAKUHOUHA, 1, 0x69);
    pl.spike_immune = 1;
    pl.attacking = 1;
    pl.animation_step.fields.relative_step = 0;
    player_zero_rakuhouha(&pl);
}
static void psz_shippuuga_start(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 0, 0x68);
    LONG();
    pl.x_vel.val = 0x40000;
    pl.unk15 = 0x40;
    player_zero_shippuuga(&pl);
}
static void psz_shippuuga_stop(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 1, 0x68);
    LONG();
    pl.x_vel.val = 0x40000;
    pl.unk15 = 0x40;
    pl.animation_step.fields.event = 0x20;
    player_zero_shippuuga(&pl);
}
static void psz_shippuuga_back(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 1, 0x68);
    LONG();
    pl.x_vel.val = -0x40000;
    pl.unk15 = 0x40;
    player_zero_shippuuga(&pl);
}
static void psz_shippuuga_wall(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 1, 0x68);
    LONG();
    pl.x_vel.val = 0x40000;
    pl.unk15 = 0x40;
    pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
    player_zero_shippuuga(&pl);
}
static void psz_shippuuga_left(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 1, 0x68);
    LONG();
    pl.x_vel.val = -0x40000;
    player_zero_shippuuga(&pl);
}
static void psz_shippuuga_left_back(void)
{
    player_reset(PLAYER_ZERO_SHIPPUUGA, 1, 0x68);
    LONG();
    pl.x_vel.val = 0x40000;
    player_zero_shippuuga(&pl);
}
static void psz_check_shippuuga_x(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.unk2 = 0;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga_locked(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.input_locked = 1;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga_missing(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga_idle(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x80;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga_busy(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x80;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    pl.attacking = 1;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x80;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_check_shippuuga_right(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.unk15 = 0x40;
    pl.boss_flags = 0x80;
    pl.pressed_input = PLAYER_INPUT_SPECIAL;
    player_extra = player_zero_check_shippuuga(&pl);
}
static void psz_ladder_slash_start(void)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, 0, 0x1F);
    LONG();
    player_zero_ladder_slash(&pl);
}
static void psz_ladder_slash_turn_left(void)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, 1, 0x1F);
    LONG();
    pl.unk15 = 0x40;
    pl.pressed_input = PLAYER_INPUT_LEFT;
    player_zero_ladder_slash(&pl);
}
static void psz_ladder_slash_turn_right(void)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, 1, 0x1F);
    LONG();
    pl.pressed_input = PLAYER_INPUT_RIGHT;
    player_zero_ladder_slash(&pl);
}
static void psz_ladder_slash_cancel(void)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, 1, 0x1F);
    LONG();
    pl.animation_step.fields.event = 0x40;
    player_zero_ladder_slash(&pl);
}
static void psz_ladder_slash_end(void)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, 1, 0x1F);
    pl.animation_step.fields.relative_step = 0;
    player_zero_ladder_slash(&pl);
}

static void (*const player_zero_techniques_cases[])(void) = {
    psz_drop_land,
    psz_drop_land_right,
    psz_drop_fall,
    psz_drop_left,
    psz_drop_right,
    psz_drop_locked,
    psz_rakuhouha_glow,
    psz_rakuhouha_burst,
    psz_rakuhouha_end,
    psz_shippuuga_start,
    psz_shippuuga_stop,
    psz_shippuuga_back,
    psz_shippuuga_wall,
    psz_shippuuga_left,
    psz_shippuuga_left_back,
    psz_check_shippuuga_x,
    psz_check_shippuuga_locked,
    psz_check_shippuuga_missing,
    psz_check_shippuuga_idle,
    psz_check_shippuuga_busy,
    psz_check_shippuuga,
    psz_check_shippuuga_right,
    psz_ladder_slash_start,
    psz_ladder_slash_turn_left,
    psz_ladder_slash_turn_right,
    psz_ladder_slash_cancel,
    psz_ladder_slash_end,
};
static const u32 player_zero_techniques_expected[] = { 0x236u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x54212Fu, 0x236u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0x2174u, 0x1010136u, 0x640000u, 0xCC0000u, 0u, 0xFFFC0000u, 0u, 0xFFu, 0u, 0x1010136u, 0x628000u, 0xCC0000u, 0xFFFE8000u, 0xFFFC0000u, 0u, 0xFFu, 0u, 0x1010136u, 0x658000u, 0xCC0000u, 0x18000u, 0xFFFC0000u, 0u, 0xFFu, 0u, 0x1010136u, 0x640000u, 0xCC0000u, 0u, 0xFFFC0000u, 0u, 0xFFu, 0u, 0x13Au, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0xD03u, 0x13Au, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0x805u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0x13Bu, 0x680000u, 0xC80000u, 0x40000u, 0u, 0u, 0x40FFu, 0u, 0x13Bu, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x13Bu, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x13Bu, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x40FFu, 0u, 0x13Bu, 0x600000u, 0xC80000u, 0xFFFC0000u, 0u, 0u, 0xFFu, 0u, 0x13Bu, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10002u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1013Bu, 0x5FE000u, 0xC80000u, 0xFFFC1800u, 0u, 0xFFFFC800u, 0xFFu, 1u, 0x1013Bu, 0x682000u, 0xC80000u, 0x3E800u, 0u, 0xFFFFC800u, 0x40FFu, 1u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0x40FFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u };

static u32 test_player_zero_techniques(u32 row)
{
    return player_run(player_zero_techniques_cases[row], row, &player_zero_techniques_expected[row * 8]);
}

#define HOLD9() (pl.animation_step.fields.duration = 9, pl.animation_step.fields.relative_step = 1)
#define NOVA(phase, setup) (player_reset(PLAYER_NOVA_STRIKE, phase, 0), HOLD9(), pl.nova_strike_active = 1, pl.spike_immune = 1, pl.air_state = 1, setup, player_nova_strike(&pl), player_extra = pl.nova_strike_active | pl.nova_strike_timer << 8 | engine_obj.gameplay_locked << 16)
static void pns_locked(void)
{
    NOVA(1, pl.input_locked = 1);
}
static void pns_windup(void) { NOVA(0, 0); }
static void pns_windup_go(void) { NOVA(0, pl.animation_step.fields.event = (s8)0x80); }
static void pns_dash_wait(void) { NOVA(1, 0); }
static void pns_dash_launch(void) { NOVA(1, pl.animation_step.fields.event = 0x20); }
static void pns_dash_launch_right(void) { NOVA(1, (pl.unk15 = 0x40, pl.animation_step.fields.event = 0x20)); }
static void pns_dash_wall(void) { NOVA(1, (engine_obj.gameplay_locked = 1, pl.x_vel.val = -0x80000, pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT, pl.animation_step.fields.event = 0x40)); }
static void pns_end_fly(void) { NOVA(2, (pl.nova_strike_timer = 3, pl.x_vel.val = -0x80000)); }
static void pns_end_timeout(void) { NOVA(2, (engine_obj.gameplay_locked = 1, pl.nova_strike_timer = 0)); }
static void pns_end_wall(void) { NOVA(2, (pl.nova_strike_timer = 3, pl.x_vel.val = -0x80000, pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT)); }
#define JUMP(step, phase, setup) (player_reset(step, phase, 0x5C), HOLD9(), pl.air_state = 1, pl.y_vel.val = 0x40000, pl.input.buttons.held = PLAYER_INPUT_JUMP, setup, player_zero_jump_slash(&pl))
static void pzj_start(void)
{
    JUMP(PLAYER_ZERO_JUMP_SLASH, 0, pl.attacking = 1);
}
static void pzj_spin(void) { JUMP(PLAYER_ZERO_SPIN_JUMP_SLASH, 1, pl.attacking = 1); }
static void pzj_locked(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.input_locked = 1)); }
static void pzj_ceiling(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_CEILING)); }
static void pzj_released(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.input.buttons.held = 0)); }
static void pzj_released_spin(void) { JUMP(PLAYER_ZERO_SPIN_JUMP_SLASH, 1, (pl.attacking = 1, pl.input.buttons.held = 0)); }
static void pzj_done(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.input.buttons.held = 0, pl.animation_step.fields.relative_step = 0)); }
static void pzj_rising(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.unk8A.bytes.high = 2)); }
static void pzj_cancel(void) { JUMP(PLAYER_ZERO_JUMP_SLASH, 1, (pl.attacking = 1, pl.animation_step.fields.event = 0x40)); }
#define WALL(flags, setup) (player_reset(PLAYER_ZERO_WALL_SLASH, 1, 0x5D), HOLD9(), pl.air_state = 1, pl.unk88.bytes.collision_flags = flags, pl.attacking = 1, setup, player_zero_wall_slash(&pl))
static void pzw_landed(void)
{
    WALL(PLAYER_COLLIDE_GROUND, 0);
}
static void pzw_locked(void) { WALL(PLAYER_COLLIDE_LEFT, pl.input_locked = 1); }
static void pzw_off_wall(void) { WALL(0, 0); }
static void pzw_wall_jump(void) { WALL(PLAYER_COLLIDE_LEFT, (pl.input.buttons.held = PLAYER_INPUT_LEFT, pl.pressed_input = PLAYER_INPUT_JUMP)); }
static void pzw_slide(void) { WALL(PLAYER_COLLIDE_LEFT, pl.input.buttons.held = PLAYER_INPUT_LEFT); }
static void pzw_slide_start(void) { WALL(PLAYER_COLLIDE_LEFT, (pl.unk6 = 0, pl.input.buttons.held = PLAYER_INPUT_LEFT)); }
static void pzw_slide_cancel(void) { WALL(PLAYER_COLLIDE_LEFT, (pl.input.buttons.held = PLAYER_INPUT_LEFT, pl.animation_step.fields.event = 0x40)); }
static void pzw_slide_end(void) { WALL(PLAYER_COLLIDE_LEFT, (pl.input.buttons.held = PLAYER_INPUT_LEFT, pl.animation_step.fields.relative_step = 0)); }
static void pzw_let_go(void) { WALL(PLAYER_COLLIDE_LEFT, 0); }
static void pgr_rakuhouha_missing(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    player_extra = func_80039F28(&pl);
}
static void pgr_rakuhouha_low(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x20;
    pl.weapon_energy[0] = 4;
    pl.pressed_input = 0x40;
    player_extra = func_80039F28(&pl);
}
static void pgr_rakuhouha_busy(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x20;
    pl.weapon_energy[0] = 0x20;
    pl.pressed_input = 0x40;
    pl.attacking = 1;
    player_extra = func_80039F28(&pl);
}
static void pgr_rakuhouha(void)
{
    player_reset(PLAYER_IDLE, 0, 0);
    pl.boss_flags = 0x20;
    pl.weapon_energy[0] = 0x20;
    pl.pressed_input = 0x40;
    pl.invincibility_timer = 5;
    player_extra = func_80039F28(&pl) | pl.weapon_energy[0] << 8;
}

static void (*const player_zero_air_techniques_cases[])(void) = {
    pns_locked,
    pns_windup,
    pns_windup_go,
    pns_dash_wait,
    pns_dash_launch,
    pns_dash_launch_right,
    pns_dash_wall,
    pns_end_fly,
    pns_end_timeout,
    pns_end_wall,
    pzj_start,
    pzj_spin,
    pzj_locked,
    pzj_ceiling,
    pzj_released,
    pzj_released_spin,
    pzj_done,
    pzj_rising,
    pzj_cancel,
    pzw_landed,
    pzw_locked,
    pzw_off_wall,
    pzw_wall_jump,
    pzw_slide,
    pzw_slide_start,
    pzw_slide_cancel,
    pzw_slide_end,
    pzw_let_go,
    pgr_rakuhouha_missing,
    pgr_rakuhouha_low,
    pgr_rakuhouha_busy,
    pgr_rakuhouha,
};
static const u32 player_zero_air_techniques_expected[] = { 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0x1000022u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 1u, 0x1000122u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 1u, 0x1000122u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 1u, 0x1000222u, 0x640000u, 0xC80000u, 0xFFF80000u, 0u, 0u, 0x100FFu, 0u, 0x1000222u, 0x640000u, 0xC80000u, 0x80000u, 0u, 0u, 0x140FFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0x1000222u, 0x5C0000u, 0xC80000u, 0xFFF80000u, 0u, 0u, 0x100FFu, 0x201u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0x300u, 0x1010131u, 0x640000u, 0xC40000u, 0u, 0x40000u, 0u, 0xFFu, 1u, 0x1010137u, 0x640000u, 0xC40000u, 0u, 0x40000u, 0u, 0xFFu, 1u, 0xFF010132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0xFF010132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0xFF010132u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0xFF010138u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x1010131u, 0x640000u, 0xC40000u, 0u, 0x40000u, 0u, 0xFFu, 0u, 0x1010131u, 0x640000u, 0xC40000u, 0u, 0x40000u, 0u, 0xFFu, 0u, 8u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF000007u, 0x640000u, 0xC80000u, 0u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 0xFF00010Bu, 0x640000u, 0xC80000u, 0x20000u, 0u, 0x420000u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x10002u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 0x101003Au, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x100FFu, 0x1401u };

static u32 test_player_zero_air_techniques(u32 row)
{
    return player_run(player_zero_air_techniques_cases[row], row, &player_zero_air_techniques_expected[row * 8]);
}

static const struct {
    u16 pressed, held;
    u8 locked, event, technique;
    s8 relative_step;
    u8 expected_step, expected_attack;
} hyo_land_cases[] = {
    { 0, 0, 1, 0, 0, 1, PLAYER_ZERO_HYOURETSUZAN, 1 },
    { 0, 0, 0, 0, 0, 1, PLAYER_ZERO_HYOURETSUZAN, 1 },
    { 0, 0, 0, 0x40, 0, 1, PLAYER_ZERO_HYOURETSUZAN, 1 },
    { PLAYER_INPUT_DASH, 0, 0, 0x40, 0, 1, PLAYER_DASH, 0 },
    { PLAYER_INPUT_JUMP, 0, 0, 0x40, 0, 1, PLAYER_JUMP, 0 },
    { PLAYER_INPUT_SHOOT, 0, 0, 0x40, 0, 1, PLAYER_ZERO_SABER, 1 },
    { PLAYER_INPUT_SPECIAL, 0, 0, 0x40, 1, 1, PLAYER_ZERO_RAIJINGEKI, 1 },
    { 0, PLAYER_INPUT_RIGHT, 0, 0x40, 0, 1, PLAYER_WALK_START, 0 },
    { 0, 0, 0, 0, 0, 0, PLAYER_IDLE, 0 },
};

static u32 test_hyo_land(u32 row)
{
    player_reset(PLAYER_ZERO_HYOURETSUZAN, 3, 0);
    pl.attacking = 1;
    pl.input_locked = hyo_land_cases[row].locked;
    pl.pressed_input = hyo_land_cases[row].pressed;
    pl.input.buttons.held = hyo_land_cases[row].held;
    pl.animation_step.fields.event = hyo_land_cases[row].event;
    pl.animation_step.fields.relative_step = hyo_land_cases[row].relative_step;
    pl.boss_flags = hyo_land_cases[row].technique;

    player_zero_hyouretsuzan_land(&pl);

    assert(pl.unk5 == hyo_land_cases[row].expected_step);
    assert(pl.attacking == hyo_land_cases[row].expected_attack);
    assert(pl.unk2 == 1);
    return (u8)pl.unk5;
}

static const struct {
    u16 pressed;
    u8 phase, event, ladder, expected_step, expected_attack, facing;
    s8 relative_step;
} ladder_slashes[] = {
    { PLAYER_INPUT_LEFT, 0, 0, 1, PLAYER_ZERO_LADDER_SLASH, 1, 0, 1 },
    { PLAYER_INPUT_RIGHT, 0, 0, 1, PLAYER_ZERO_LADDER_SLASH, 1, 0x40, 1 },
    { 0, 1, 0, 1, PLAYER_ZERO_LADDER_SLASH, 1, 0, 1 },
    { 0, 0, 0x40, 1, PLAYER_ZERO_LADDER_SLASH, 1, 0, 1 },
    { PLAYER_INPUT_SHOOT, 0, 0x40, 1, PLAYER_ZERO_LADDER_SLASH, 1, 0, 1 },
    { 0, 0, 0, 1, PLAYER_LADDER_UP, 0, 0, 0 },
    { 0, 0, 0, 0, PLAYER_FALL, 0, 0, 1 },
};

static u32 test_ladder_slash(u32 row)
{
    player_reset(PLAYER_ZERO_LADDER_SLASH, ladder_slashes[row].phase, 0x5D);
    pl.attacking = 1;
    pl.pressed_input = ladder_slashes[row].pressed;
    pl.animation_step.fields.event = ladder_slashes[row].event;
    pl.animation_step.fields.relative_step = ladder_slashes[row].relative_step;
    pl.animation_step.fields.duration = 2;
    player_attrs[0] = ladder_slashes[row].ladder ? 0x20 : 0;

    player_zero_ladder_slash(&pl);

    assert(pl.unk5 == ladder_slashes[row].expected_step);
    assert(pl.attacking == ladder_slashes[row].expected_attack);
    assert(pl.unk15 == ladder_slashes[row].facing);
    if (pl.unk5 == PLAYER_ZERO_LADDER_SLASH)
        assert(pl.unk6 == 1);
    return (u8)pl.unk5;
}

void player_hover_rise(struct PlayerObj*);
void player_hover_back_stop(struct PlayerObj*);
static u32 frames[4] = { 8, 12, 0x12345678, 0x23456789 };
static Palette bank[3];
static u16 palette[0x152], palette_expected[0x152];
static const s8 bob_offsets[] = { 0, 1, -1 };
static const u8 bob_indices[] = { 0, 1, 9 };
static const u16 directions[] = { 0, PLAYER_INPUT_LEFT, PLAYER_INPUT_RIGHT };
static const u32 animation_words[] = { 0x29010004, 0x37010003, 0x5D010003, 0xE5000060, 0xDD010004, 0xE1010004 };
static void animation(struct PlayerObj* p, u32 index, u32 word)
{
    p->unk17 = index;
    p->previous_animation_index = 0xFF;
    p->animation_cursor = (u32*)D_80119DF0[index];
    p->animation_step.packed = word;
    p->unk3C = (u8*)frames + 8;
}
static u32 hover_handoff(u32 row)
{
    struct PlayerObj expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 9, facing = row / 9 % 2, direction = row / 18 % 3, bob = row / 54, i;
    u32 rise = mode < 3 || mode > 6, dash = mode == 0 || mode == 1 || mode > 6;
    u32 can_dash = mode == 0 || mode == 7, changed = 0;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 48; i++)
        ((u16*)bank)[i] = 0x1200 + i;
    for (i = 0; i < COUNT(palette); i++)
        palette[i] = palette_expected[i] = 0xBEEF;
    TEST_SPRITE_FRAMES = (u8*)frames;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    need_palette_load = 0x20;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.state = 1;
    g_Player.unk5 = PLAYER_HOVER;
    g_Player.unk6 = rise ? 1 : 6;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.hover_timer = mode == 3 ? 1 : 2;
    g_Player.hover_bob = bob_indices[bob];
    g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    g_Player.x_vel.val = 0x12345;
    g_Player.y_vel.val = 0x23456;
    g_Player.unk28 = 0x3456;
    g_Player.unk2C = 0x4567;
    g_Player.input.buttons.held = directions[direction];
    g_Player.shot_cooldown = mode == 1 || mode == 8;
    if (dash) {
        if (mode > 6)
            g_Player.double_tap_dash = 1;
        else
            g_Player.pressed_input = PLAYER_INPUT_DASH;
    }
    if (mode == 4) {
        g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT;
        g_Player.wall_climbable = 1;
        g_Player.input.buttons.held = PLAYER_INPUT_LEFT;
    }
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), rise ? 21 : 26, mode == 5 ? 2 : 0);
    g_Player.unk3C = (u8*)frames + 12;
    expected = g_Player;
    expected.hover_timer--;
    if (mode == 3) {
        animation(&expected, 11, animation_words[0]);
        expected.x_vel.val = expected.y_vel.val = expected.unk28 = 0;
        expected.unk2C = 0x4200;
        expected.air_state = -1;
        expected.unk5 = PLAYER_FALL;
        expected.unk6 = 0;
    } else if (mode == 4) {
        animation(&expected, 13, animation_words[1]);
        expected.x_vel.val = expected.y_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.afterimage = -1;
        expected.unk8A.bytes.low = 8;
        expected.unk15 = 0;
        expected.unk5 = PLAYER_WALL_CLING;
        expected.unk6 = 0;
    } else if (can_dash) {
        if (direction)
            expected.unk15 = direction == 2 ? 0x40 : 0;
        expected.x_vel.val = expected.unk15 ? 0x68000 : -0x68000;
        animation(&expected, 18, animation_words[2]);
        expected.unk28 = -0x3000;
        expected.y_vel.val = expected.unk2C = 0;
        expected.dash_momentum = -1;
        expected.dash_timer = 18;
        expected.air_action = 3;
        expected.shot_cooldown = 0;
        expected.unk5 = PLAYER_AIR_DASH;
        expected.unk6 = 0;
        changed = 1;
        for (i = 0; i < 16; i++)
            palette_expected[1 + i] = 0x1200 + i;
        for (i = 0; i < 32; i++)
            palette_expected[1 + 0x130 + i] = 0x1210 + i;
    } else {
        if (dash && direction)
            expected.unk15 = direction == 2 ? 0x40 : 0;
        expected.y_pos.val += bob_offsets[bob] * 65536;
        expected.hover_bob = bob_indices[bob] + 1;
        expected.x_vel.val = direction == 0 ? 0 : direction == 1 ? -0x20000
                                                                 : 0x20000;
        if (direction) {
            u32 forward = (direction == 2) == (expected.unk15 != 0);
            animation(&expected, forward ? 23 : 25, animation_words[forward ? 4 : 5]);
            expected.unk6 = forward ? 3 : 5;
            if (rise)
                expected.hover_timer = 40;
        } else if (mode == 5) {
            animation(&expected, 22, animation_words[3]);
            expected.unk6 = 2;
        }
    }
    D_8013E198[1] = -1;
    if (rise)
        player_hover_rise(&g_Player);
    else
        player_hover_back_stop(&g_Player);
    c_test_same_words(&g_Player, &expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < COUNT(palette); i++)
        assert(palette[i] == palette_expected[i]);
    for (i = 0; i < 48; i++)
        assert(((u16*)bank)[i] == 0x1200 + i);
    assert(need_palette_load == (changed ? 0x21 : 0x20));
    assert(frames[0] == 8 && frames[1] == 12 && frames[2] == 0x12345678 && frames[3] == 0x23456789);
    return 1;
}

static u32 gfx[16], frames_player_special_shot_capacity[16];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_expected[32];
static u32 special(u32 row)
{
    struct PlayerObj expected, clone_before = g_Entity;
    struct EngineObj engine_before;
    u32 kind = row % 4, weapon_free = row / 4 % 2, visual_free = row / 8 % 2, face = row / 16 % 2, layer = row / 32, animation = kind < 2 ? 0x5F : kind == 2 ? 0x63
                                                                                                                                                             : 0x64,
        id = kind == 0 ? 2 : kind == 1 ? 11
                                       : 4,
        i;
    engine_obj.cur_character = 0;
    engine_before = engine_obj;
    for (i = 0; i < COUNT(gfx); i++)
        gfx[i] = frames_player_special_shot_capacity[i] = i < 8 ? 32 + i * 4 : 0x13570000 + i;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames_player_special_shot_capacity;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = i == 15 && weapon_free ? 0 : 1;
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && visual_free ? 0 : 1;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.unk5 = kind < 2 ? PLAYER_WEAPON_POSE : PLAYER_RISING_FIRE;
    g_Player.hp = 24;
    g_Player.weapon = kind < 2 ? 2 : 4;
    g_Player.weapon_energy[g_Player.weapon] = 48;
    g_Player.shot_type = g_Player.last_shot_type = id;
    g_Player.attacking = g_Player.air_state = 1;
    g_Player.unk15 = face ? 0x40 : 0;
    g_Player.bg_offset = layer;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 120;
    g_Player.unk38 = (u8*)gfx + 32;
    g_Player.unk3C = (u8*)frames_player_special_shot_capacity + 32;
    g_Player.unk40 = 0x500;
    g_Player.unk42 = 0x7800;
    g_Player.unk16 = 2;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), animation, 1);
    assert(g_Player.animation_step.packed == (kind < 2 ? 0x8B018003 : kind == 2 ? 0xE8018030
                                                                                : 0x68018008));
    expected = g_Player;
    expected.animation_step.packed = kind < 2 ? 0x8B010002 : kind == 2 ? 0xE801002F
                                                                       : 0x68010007;
    expected.shot_count = expected.special_shot_count = 1;
    if (weapon_free) {
        struct WeaponObj* w = &weapons_expected[15];
        w->active = 1;
        w->id = id;
        w->unk2 = kind == 3;
        w->bg_offset = layer;
        if (visual_free && kind != 1) {
            struct VisualObj* v = &visuals_expected[31];
            v->active = 1;
            v->id = 26;
            v->unk2 = kind == 0;
            v->bg_offset = layer;
            v->unk50 = (void*)&weapon_objects[15];
        }
    }
    if (kind < 2)
        player_weapon_pose(&g_Player);
    else
        player_rising_fire(&g_Player);
    c_test_same_words(&g_Player, &expected, sizeof(g_Player));
    c_test_same_words(&g_Entity, &clone_before, sizeof(g_Entity));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames_player_special_shot_capacity);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i < 8 ? 32 + i * 4 : 0x13570000 + i) && frames_player_special_shot_capacity[i] == gfx[i]);
    return 1;
}

void player_zero_jump_slash(struct PlayerObj*);
void player_zero_fall_slash(struct PlayerObj*);
void player_set_animation_frame(struct PlayerObj*, s32, s32);
void player_clear_attack(struct PlayerObj*);

static struct Unk_unk68 bounds = { 0, 0, 4, 4 };
static u32 gfx_player_zero_air_handoffs[16] = { 0x20, 0x24 };
static u32 sprites[16] = { 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34 };
static u8 tilemap_player_zero_air_handoffs[3 * 256], sound_commands[32];
static u16 pixels_player_zero_air_handoffs[512];
static u32 attributes_player_zero_air_handoffs[2];
static Palette bank_player_zero_air_handoffs[16];
static u16 palette_player_zero_air_handoffs[0x152], palette_expected_player_zero_air_handoffs[0x152];
static struct PlayerObj expected, entity_before;
static struct EngineObj engine_expected;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_expected_player_zero_air_handoffs[16];
static struct VisualObj visuals_expected_player_zero_air_handoffs[32];
static u32 palette_dirty;
static s32 wall_column;

static void prepare(u32 profile)
{
    u32 i;
    wall_column = -1;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)sound_commands, sizeof(sound_commands) / 4);
    c_test_zero_words((u32*)pixels_player_zero_air_handoffs, sizeof(pixels_player_zero_air_handoffs) / 4);
    for (i = 0; i < COUNT(tilemap_player_zero_air_handoffs); i++)
        tilemap_player_zero_air_handoffs[i] = 1;
    for (i = 0; i < sizeof(bank_player_zero_air_handoffs) / 2; i++)
        ((u16*)bank_player_zero_air_handoffs)[i] = 0x1200 + i;
    for (i = 0; i < COUNT(palette_player_zero_air_handoffs); i++)
        palette_player_zero_air_handoffs[i] = palette_expected_player_zero_air_handoffs[i] = 0xBEEF;
    attributes_player_zero_air_handoffs[0] = 0x20;
    attributes_player_zero_air_handoffs[1] = 0x38;
    for (i = 480; i < COUNT(pixels_player_zero_air_handoffs); i++)
        pixels_player_zero_air_handoffs[i] = 1;
    TEST_PLAYER_GFX = (u8*)gfx_player_zero_air_handoffs;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    TEST_PALETTE = (u8*)&palette_player_zero_air_handoffs[1];
    TEST_PALETTE_BANK = (u8*)bank_player_zero_air_handoffs;
    TEST_BG_TILE_PIXELS = (u8*)pixels_player_zero_air_handoffs;
    TEST_BG_TILE_ATTRS = (u8*)attributes_player_zero_air_handoffs;
    SP_BG_TILEMAP = tilemap_player_zero_air_handoffs;
    layout_width = layout_height = 16;
    layout_size = 256;
    D_80141F50[1] = sound_commands;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    g_Entity.hp = 17;
    g_Entity.x_pos.val = 0x12345678;
    for (i = 0; i < COUNT(weapon_objects); i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].owner = &g_Entity;
    }
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].unk50 = &g_Entity;
    }
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.unk15 = profile % 2 ? 0x40 : 0;
    g_Player.bg_offset = profile % 3;
    g_Player.x_pos.val = (100 + profile % 3 * 16) * 65536 + 0x1234;
    g_Player.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.x_vel.val = ((s32)(profile % 3) - 1) * 0x20000;
    g_Player.y_vel.val = 0x38000;
    g_Player.unk28 = 0x1000;
    g_Player.unk2C = 0x4200;
    g_Player.unk38 = (u8*)gfx_player_zero_air_handoffs + 0x24;
    g_Player.unk3C = (u8*)sprites + 0x24;
    g_Player.animation_table = (u32**)D_80119DF0;
    g_Player.unk68 = &bounds;
    g_Player.air_state = 1;
    g_Player.dash_momentum = 1;
    g_Player.afterimage = (s32)(profile % 3) - 1;
    g_Player.attacking = 1;
    g_Player.shot_fired = 1;
    g_Player.attack_ended = 1;
    g_Player.attack_pose_timer = 20;
    g_Player.shot_palette_timer = 9;
    g_Player.stock_charge = 2;
    g_Player.charge_state[0] = g_Player.charge_state[1] = PLAYER_CHARGE_FULL;
    g_Player.charge_timer = 44;
    g_Player.special_charge_timer = 55;
    g_Player.flash_palette = 7;
    g_Player.hurt_phase = 2;
    g_Player.invincibility_timer = 9;
    g_Player.voice_timer = 1;
    engine_obj.max_hp = 24;
    engine_obj.stage = 4;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = palette_dirty = 0x20;
    cur_random = 0x1234;
}

static void capture(void)
{
    expected = g_Player;
    entity_before = g_Entity;
    engine_expected = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_expected_player_zero_air_handoffs, (const u32*)weapon_objects, sizeof(weapons_expected_player_zero_air_handoffs) / 4);
    c_test_copy_words((u32*)visuals_expected_player_zero_air_handoffs, (const u32*)visual_objects, sizeof(visuals_expected_player_zero_air_handoffs) / 4);
}

#define SAME(a, b) assert(c_test_word_difference((const u32*)(a), (const u32*)(b), sizeof(*(b)) / 4) == 0)
static void check(void)
{
    u32 i;
    SAME(&g_Player, &expected);
    SAME(&g_Entity, &entity_before);
    SAME(&engine_obj, &engine_expected);
    SAME(&main_bss_state, &main_before);
    SAME(&background_objects, &backgrounds_before);
    SAME(&weapon_objects, &weapons_expected_player_zero_air_handoffs);
    SAME(&visual_objects, &visuals_expected_player_zero_air_handoffs);
    for (i = 0; i < COUNT(palette_player_zero_air_handoffs); i++)
        assert(palette_player_zero_air_handoffs[i] == palette_expected_player_zero_air_handoffs[i]);
    for (i = 0; i < sizeof(bank_player_zero_air_handoffs) / 2; i++)
        assert(((u16*)bank_player_zero_air_handoffs)[i] == 0x1200 + i);
    for (i = 0; i < COUNT(tilemap_player_zero_air_handoffs); i++)
        assert(tilemap_player_zero_air_handoffs[i] == 1);
    for (i = 0; i < COUNT(pixels_player_zero_air_handoffs); i++)
        assert(pixels_player_zero_air_handoffs[i] == (i >= 480 || (i >= 256 && (s32)(i % 16) == wall_column)));
    for (i = 0; i < COUNT(sound_commands); i++)
        assert(sound_commands[i] == 0);
    for (i = 0; i < 16; i++) {
        assert(gfx_player_zero_air_handoffs[i] == (i < 2 ? 0x20 + 4 * i : 0));
        assert(sprites[i] == (i < 6 ? 0x20 + 4 * i : 0));
    }
    assert(attributes_player_zero_air_handoffs[0] == 0x20 && attributes_player_zero_air_handoffs[1] == 0x38 && bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(cur_random == 0x1234 && need_palette_load == palette_dirty);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(D_80141F50[1] == sound_commands);
    assert(TEST_PLAYER_GFX == (u8*)gfx_player_zero_air_handoffs && TEST_SPRITE_FRAMES == (u8*)sprites);
    assert(TEST_PALETTE == (u8*)&palette_player_zero_air_handoffs[1] && TEST_PALETTE_BANK == (u8*)bank_player_zero_air_handoffs);
    assert(SP_BG_TILEMAP == tilemap_player_zero_air_handoffs && TEST_BG_TILE_PIXELS == (u8*)pixels_player_zero_air_handoffs && TEST_BG_TILE_ATTRS == (u8*)attributes_player_zero_air_handoffs);
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
}

static void expect_animation(u32 animation, u32 word)
{
    const u32* const* table = expected.unk2 ? D_8011AFF0 : D_80119DF0;
    u32 resource = expected.unk2 && (animation == 0x41 || animation == 0x64) ? 1 : 0;
    assert(table[animation][0] == word);
    if (expected.unk2)
        assert(D_8011AF60[animation] == resource);
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (u32*)table[animation];
    expected.animation_step.packed = word;
    if (expected.unk2)
        expected.unk38 = (u8*)gfx_player_zero_air_handoffs + (resource ? 0x24 : 0x20);
    expected.unk3C = (u8*)sprites + (resource ? 0x34 : 0x20);
}

static void prepare_character(u32 row)
{
    u32 kind = row % 3;
    prepare(row / 3);
    g_Player.unk2 = kind == 2;
    g_Player.weapon = kind == 1 ? 2 : 0;
    g_Player.animation_table = (u32**)(g_Player.unk2 ? D_8011AFF0 : D_80119DF0);
    g_Player.unk68 = g_Player.unk2 ? &player_zero_collision_bounds : &player_x_collision_bounds;
    g_Player.bg_offset = row / 6 % 3;
    engine_obj.cur_character = g_Player.unk2;
    engine_obj.unk37 = row / 18;
}

static void expect_clear_attack(void)
{
    u32 i, source = expected.unk2 && engine_obj.unk37 ? 13 * 16 : 0;
    expected.attacking = expected.shot_fired = expected.attack_ended = 0;
    expected.attack_pose_timer = expected.shot_cooldown = expected.shot_palette_timer = 0;
    if (!expected.unk2 && expected.weapon) {
        for (i = 0; i < 32; i++) {
            palette_expected_player_zero_air_handoffs[1 + i] = 0x1270 + i;
            palette_expected_player_zero_air_handoffs[1 + 0x130 + i] = 0x1290 + i;
        }
    } else {
        for (i = 0; i < 16; i++)
            palette_expected_player_zero_air_handoffs[1 + i] = 0x1200 + source + i;
        if (!expected.unk2)
            for (i = 0; i < 32; i++)
                palette_expected_player_zero_air_handoffs[1 + 0x130 + i] = 0x1210 + i;
    }
    palette_dirty |= 1;
}

static const u32 slash_words[2][11] = {
    { 0xD5018001, 0xD7010101, 0xD9010201, 0xDB010301, 0xDD010401,
        0xDF010501, 0xE1010601, 0xE3010702, 0xE5014804, 0xE5004960 },
    { 0x84010002, 0xA1018002, 0xA3010002, 0xA5010002, 0xA7010002,
        0xA9010002, 0xAB010002, 0xAD010002, 0xAF010002, 0xA0010002, 0xA0000060 },
};

static void prepare_zero(u32 profile, u32 falling, u32 spin, u32 frame)
{
    prepare_character(profile % 6 * 3 + 2 + profile / 6 * 18);
    g_Player.input_locked = 0;
    g_Player.unk5 = falling ? (spin ? PLAYER_ZERO_SPIN_FALL_SLASH : PLAYER_ZERO_FALL_SLASH)
                            : (spin ? PLAYER_ZERO_SPIN_JUMP_SLASH : PLAYER_ZERO_JUMP_SLASH);
    g_Player.unk6 = 1;
    g_Player.air_state = falling ? -1 : 1;
    g_Player.unk8A.bytes.high = 0;
    g_Player.y_pos.val = 160 * 65536 + 0x5678;
    g_Player.input.buttons.held = PLAYER_INPUT_JUMP;
    g_Player.pressed_input = 0;
    player_set_animation_frame(&g_Player, spin ? 0x64 : 0x5B, frame);
    assert(g_Player.animation_step.packed == slash_words[spin][frame]);
    if (!spin && frame == 0)
        g_Player.animation_step.fields.event &= 0x7F;
}

static void check_slash_tables(void)
{
    u32 kind, frame;
    for (kind = 0; kind < 2; kind++)
        for (frame = 0; frame < (kind ? 11 : 10); frame++)
            assert(D_8011AFF0[kind ? 0x64 : 0x5B][frame] == slash_words[kind][frame]);
    assert(D_8011AF60[0x5B] == 0 && D_8011AF60[0x64] == 1);
}

static u32 air_handoff(u32 row, u32 mode)
{
    u32 profile = row % 12, spin = mode == 1 ? 0 : row % 2;
    u32 falling = mode == 1 ? row / 12 % 2 : row / 2 % 2;
    u32 action = mode == 1 ? row / 24 : row / 4, i;
    prepare_zero(profile, falling, spin, mode == 1 ? 8 : 0);
    if (action == 0) {
        g_Player.input.buttons.held |= PLAYER_INPUT_UP;
    } else if (action == 1) {
        g_Player.unk68 = &player_zero_collision_bounds;
        g_Player.x_pos.val = ((g_Player.unk15 ? 102 : 106) + g_Player.bg_offset * 16) * 65536;
        wall_column = (g_Player.unk15 ? 7 : 5) + g_Player.bg_offset;
        for (i = 0; i < 14; i++)
            pixels_player_zero_air_handoffs[256 + i * 16 + wall_column] = 1;
        g_Player.unk18 = g_Player.x_pos;
        g_Player.unk1C = g_Player.y_pos;
        CollisionRelated(&g_Player);
        assert(g_Player.unk70 == (g_Player.unk15 ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT));
        assert(g_Player.wall_climbable == 1);
        g_Player.unk88.bytes.collision_flags = g_Player.unk70;
        g_Player.input.buttons.held |= g_Player.unk15 ? PLAYER_INPUT_RIGHT : PLAYER_INPUT_LEFT;
    } else {
        g_Player.air_action = 0;
        g_Player.boss_flags = 0x10;
        g_Player.pressed_input = PLAYER_INPUT_DASH;
    }
    capture();
    if (mode == 2) {
        expect_clear_attack();
        player_clear_attack(&g_Player);
        check();
    }
    expected.attacking = 0;
    if (action == 0) {
        expect_animation(0x1F, 0xAE010002);
        expected.x_pos.i.hi = (expected.x_pos.u.hi & 0xFFF0) + 8;
        expected.x_pos.u.lo = expected.y_pos.u.lo = 0;
        expected.x_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.y_vel.val = 0x18000;
        expected.dash_momentum = expected.air_action = 0;
        if (expected.afterimage > 0)
            expected.afterimage = -1;
        expected.unk5 = PLAYER_LADDER_UP;
        expected.unk6 = 0;
    } else if (action == 1) {
        expect_animation(0xD, 0x23010002);
        expected.x_vel.val = expected.y_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.dash_momentum = expected.air_action = 0;
        expected.afterimage = -1;
        expected.unk8A.bytes.low = 8;
        expected.unk5 = PLAYER_WALL_CLING;
        expected.unk6 = 0;
    } else {
        expect_animation(0x12, 0x2C010003);
        expected.x_vel.val = expected.unk15 ? 0x68000 : -0x68000;
        expected.unk28 = -0x3000;
        expected.y_vel.val = expected.unk2C = 0;
        expected.dash_momentum = -1;
        expected.dash_timer = 0x12;
        expected.air_action = 3;
        expect_clear_attack();
        expected.unk5 = PLAYER_AIR_DASH;
        expected.unk6 = 0;
    }
    if (falling)
        player_zero_fall_slash(&g_Player);
    else
        player_zero_jump_slash(&g_Player);
    check();
    check_slash_tables();
    return 1;
}

static u32 combo_restart(u32 profile, u32 next_spin, u32 falling, u32 old_spin, u32 available, u32 cancellation)
{
    u32 frame = cancellation ? 8 : old_spin ? 10
                                            : 9;
    prepare_zero(profile, falling, old_spin, frame);
    g_Player.boss_flags = next_spin ? 4 : 0;
    g_Player.unk8A.bytes.high = 1;
    g_Player.input.buttons.held |= g_Player.unk15 ? PLAYER_INPUT_RIGHT : PLAYER_INPUT_LEFT;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    if (available)
        weapon_objects[15].active = 0;
    capture();
    expected.attacking = 1;
    expected.combo = expected.afterimage = 0;
    expected.unk5 = falling ? (next_spin ? PLAYER_ZERO_SPIN_FALL_SLASH : PLAYER_ZERO_FALL_SLASH)
                            : (next_spin ? PLAYER_ZERO_SPIN_JUMP_SLASH : PLAYER_ZERO_JUMP_SLASH);
    expected.unk6 = 1;
    expect_animation(next_spin ? 0x64 : 0x5B, next_spin ? 0x84010002 : 0xD5018001);
    if (!next_spin) {
        expected.animation_step.fields.event = 0;
        if (available) {
            weapons_expected_player_zero_air_handoffs[15].active = 1;
            weapons_expected_player_zero_air_handoffs[15].id = 0x1B;
            weapons_expected_player_zero_air_handoffs[15].unk2 = 0;
            weapons_expected_player_zero_air_handoffs[15].bg_offset = expected.bg_offset;
            weapons_expected_player_zero_air_handoffs[15].unk84.word = 0x5B;
        }
    }
    if (!falling)
        expected.unk8A.bytes.high = 0;
    expected.x_vel.val = expected.unk15 ? 0x42000 : -0x42000;
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    expected.x_vel.val += expected.unk15 ? expected.unk28 : -expected.unk28;
    expected.y_vel.val -= expected.unk2C;
    if (falling)
        player_zero_fall_slash(&g_Player);
    else
        player_zero_jump_slash(&g_Player);
    check();
    check_slash_tables();
    return 1;
}

static u32 test_air_handoff(u32 row) { return air_handoff(row, 0); }
static u32 test_cancel_window_handoff(u32 row) { return air_handoff(row, 1); }
static u32 test_cancelled_attack_handoff(u32 row) { return air_handoff(row, 2); }
static u32 test_combo_end(u32 row) { return combo_restart(row % 12, row % 2, row / 2 % 2, row / 4 % 2, row / 8, 0); }
static u32 test_combo_cancel(u32 row) { return combo_restart(row % 12, row / 12 % 2, row / 24 % 2, 0, row / 48, 1); }

static u32 map_words[192], tiles_words[34 * 128], attributes_rising_fire_ladder_handoff[962], gfx_rising_fire_ladder_handoff[16], frames_rising_fire_ladder_handoff[16], bank_words[256], palette_words[171];
static u32 expected_map[192], expected_tiles[34 * 128], expected_attributes[962];
static u32 handoff(u32 row)
{
    struct PlayerObj expected, clone_before = g_Entity;
    struct EngineObj engine_before;
    u32 down = row % 2, face = row / 2 % 2, fraction = row / 4, i, tile = down ? 957 : 961, anim = down ? 29 : 27;
    u8* map = (u8*)map_words;
    u16* tiles = (u16*)tiles_words;
    u16* bank = (u16*)bank_words;
    u16* palette = (u16*)palette_words;
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.unkF = 0;
    engine_before = engine_obj;
    layout_width = 28;
    layout_height = 9;
    layout_size = 252;
    c_test_zero_words(map_words, COUNT(map_words));
    c_test_zero_words(tiles_words, COUNT(tiles_words));
    c_test_zero_words(attributes_rising_fire_ladder_handoff, COUNT(attributes_rising_fire_ladder_handoff));
    map[50] = 33;
    tiles[33 * 256 + (down ? 12 : 13) * 16 + 6] = tile;
    attributes_rising_fire_ladder_handoff[tile] = down ? 0x03720021 : 0x03760020;
    c_test_copy_words(expected_map, map_words, COUNT(map_words));
    c_test_copy_words(expected_tiles, tiles_words, COUNT(tiles_words));
    c_test_copy_words(expected_attributes, attributes_rising_fire_ladder_handoff, COUNT(attributes_rising_fire_ladder_handoff));
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes_rising_fire_ladder_handoff;
    for (i = 0; i < COUNT(gfx_rising_fire_ladder_handoff); i++)
        gfx_rising_fire_ladder_handoff[i] = frames_rising_fire_ladder_handoff[i] = i < 8 ? 32 + i * 4 : 0x13570000 + i;
    for (i = 0; i < sizeof(bank_words) / 2; i++)
        bank[i] = 0x1200 + i;
    for (i = 0; i < sizeof(palette_words) / 2; i++)
        palette[i] = 0xBEEF;
    TEST_PLAYER_GFX = (u8*)gfx_rising_fire_ladder_handoff;
    TEST_SPRITE_FRAMES = (u8*)frames_rising_fire_ladder_handoff;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    need_palette_load = 0x20;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.unk5 = PLAYER_RISING_FIRE;
    g_Player.hp = 24;
    g_Player.weapon = 4;
    g_Player.weapon_energy[4] = 48;
    g_Player.shot_count = g_Player.special_shot_count = 1;
    g_Player.air_state = 1;
    g_Player.unk15 = face ? 0x40 : 0;
    g_Player.x_pos.i.hi = 5731;
    g_Player.y_pos.i.hi = down ? 427 : 481;
    g_Player.x_pos.u.lo = fraction ? 0x1234 : 0;
    g_Player.y_pos.u.lo = fraction ? 0x5678 : 0;
    g_Player.unk68 = &player_x_collision_bounds;
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    g_Player.input.buttons.held = down ? PLAYER_INPUT_DOWN : PLAYER_INPUT_UP;
    g_Player.unk38 = (u8*)gfx_rising_fire_ladder_handoff + 32;
    g_Player.unk3C = (u8*)frames_rising_fire_ladder_handoff + 32;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 99, 2);
    assert(g_Player.animation_step.packed == 0xE8000060);
    expected = g_Player;
    expected.x_pos.i.hi = 5736;
    expected.x_pos.u.lo = expected.y_pos.u.lo = 0;
    expected.unk17 = anim;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)D_80119DF0[anim];
    expected.animation_step.packed = down ? 0x9A010005 : 0x8F010003;
    expected.unk5 = PLAYER_LADDER_TRANSITION;
    expected.unk6 = down ? 2 : 0;
    if (down)
        expected.unk68 = NULL;
    else
        expected.y_vel.val = 0x10000;
    player_rising_fire(&g_Player);
    c_test_same_words(&g_Player, &expected, sizeof(g_Player));
    c_test_same_words(&g_Entity, &clone_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(need_palette_load == 0x21 && layout_width == 28 && layout_height == 9 && layout_size == 252 && SP_BG_TILEMAP == map && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes_rising_fire_ladder_handoff && TEST_PALETTE == (u8*)&palette[1] && TEST_PALETTE_BANK == (u8*)bank);
    for (i = 0; i < sizeof(palette_words) / 2; i++)
        assert(palette[i] == (i >= 1 && i <= 32 ? 0x1200 + 240 + i - 1 : i >= 305 && i <= 336 ? 0x1200 + 272 + i - 305
                                                                                              : 0xBEEF));
    for (i = 0; i < sizeof(bank_words) / 2; i++)
        assert(bank[i] == 0x1200 + i);
    c_test_same_words(map_words, expected_map, sizeof(map_words));
    c_test_same_words(tiles_words, expected_tiles, sizeof(tiles_words));
    c_test_same_words(attributes_rising_fire_ladder_handoff, expected_attributes, sizeof(attributes_rising_fire_ladder_handoff));
    for (i = 0; i < COUNT(gfx_rising_fire_ladder_handoff); i++)
        assert(gfx_rising_fire_ladder_handoff[i] == (i < 8 ? 32 + i * 4 : 0x13570000 + i) && frames_rising_fire_ladder_handoff[i] == gfx_rising_fire_ladder_handoff[i]);
    return 1;
}

static u32 archive[16];
static struct VisualObj visuals_expected_zero_rakuhouha_capacity[32];
static struct WeaponObj weapons_expected_zero_rakuhouha_capacity[16];
static u32 rakuhouha(u32 row)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_before;
    u32 event = row % 2, slots = row / 2 % 3, face = row / 6 % 2, layer = row / 12, available = slots == 2 ? 9 : slots, i;
    engine_obj.cur_character = 1;
    engine_before = engine_obj;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 7 ? 28 + i * 4 : 0x13570000 + i;
    TEST_SPRITE_FRAMES = (u8*)archive;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && slots != 0 ? 0 : 1;
    memcpy(visuals_expected_zero_rakuhouha_capacity, visual_objects, sizeof(visuals_expected_zero_rakuhouha_capacity));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    for (i = 0; i < COUNT(weapon_objects); i++)
        weapon_objects[i].active = i >= 16 - available ? 0 : 1;
    memcpy(weapons_expected_zero_rakuhouha_capacity, weapon_objects, sizeof(weapons_expected_zero_rakuhouha_capacity));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = 1;
    obj.unk5 = 0x3A;
    obj.unk15 = face ? 0x40 : 0;
    obj.bg_offset = layer;
    obj.hp = 24;
    obj.boss_flags = 0x20;
    obj.attacking = obj.air_state = obj.spike_immune = 1;
    obj.weapon_energy[0] = 36;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_8011AFF0;
    set_animation_frame(ANIMATED_OBJECT(&obj), 0x67, event ? 9 : 4);
    assert(obj.animation_step.packed == (event ? 0xB6014002 : 0xB5010002));
    if (!event)
        obj.animation_step.fields.duration = 1;
    expected = obj;
    if (!event)
        expected.animation_cursor++;
    expected.animation_step.packed = 0xB6010001;
    if (!event && slots) {
        struct VisualObj* v = &visuals_expected_zero_rakuhouha_capacity[31];
        v->active = 0x21;
        v->id = 3;
        v->unk2 = 13;
        v->bg_offset = layer;
        v->unk3C = (u8*)archive + 52;
        v->animation_table = D_8011C018;
        v->unk42 = 0x7803;
        v->x_pos = obj.x_pos;
        v->y_pos = obj.y_pos;
        v->unk15 = obj.unk15;
    }
    if (event)
        for (i = 0; i < available; i++) {
            struct WeaponObj* w = &weapons_expected_zero_rakuhouha_capacity[16 - available + i];
            w->active = 0x21;
            w->id = 36;
            w->unk2 = i;
            w->bg_offset = layer;
        }
    player_zero_rakuhouha(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, visuals_expected_zero_rakuhouha_capacity, sizeof(visuals_expected_zero_rakuhouha_capacity));
    c_test_same_words(weapon_objects, weapons_expected_zero_rakuhouha_capacity, sizeof(weapons_expected_zero_rakuhouha_capacity));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(TEST_SPRITE_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 7 ? 28 + i * 4 : 0x13570000 + i));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "hyouretsuzan_land", 0, 0, COUNT(hyo_land_cases), test_hyo_land },
    { "ladder_slash", 0, 0, COUNT(ladder_slashes), test_ladder_slash },
    { "player_zero_air_techniques", 0, 0, COUNT(player_zero_air_techniques_cases), test_player_zero_air_techniques },
    { "player_zero_techniques", 0, 0, COUNT(player_zero_techniques_cases), test_player_zero_techniques },
    { "player_special_extra", 0, 0, COUNT(player_special_extra_cases), test_player_special_extra },
    { "player_special_states", 0, 0, COUNT(player_special_states_cases), test_player_special_states },
    { "zero_shippuuga_cancel_context", NULL, zero_shippuuga_cancel_context_cases_expected, COUNT(zero_shippuuga_cancel_context_cases_expected), zero_shippuuga_cancel_context_cases_row },
    { "player_hover_steer", 0, 0, 1, test_player_hover_steer },
    { "player_nova_strike_hit_wall", 0, 0, 2, test_player_nova_strike_hit_wall },
    { "player_zero_hyouretsuzan_start", 0, 0, 2, test_player_zero_hyouretsuzan_start },
    { "soul_body_clone_archive", soul_body_clone_archive_cases, soul_body_clone_archive_cases_expected, COUNT(soul_body_clone_archive_cases), 0 },
    { "hover_dash_cooldown_fall_wall_and_stop_handoffs", NULL, NULL, 54, hover_handoff },
    { "X_normal_charged_Frost_Tower_and_ground_air_Rising_Fire_original_events_capacity", NULL, NULL, 96, special },
    { "air_handoff", 0, 0, 12, test_air_handoff },
    { "cancel_window_handoff", 0, 0, 72, test_cancel_window_handoff },
    { "cancelled_attack_handoff", 0, 0, 12, test_cancelled_attack_handoff },
    { "combo_end", 0, 0, 16, test_combo_end },
    { "combo_cancel", 0, 0, 96, test_combo_cancel },
    { "ground_Rising_Fire_terminal_to_real_stage1_ladder_body_and_top", NULL, NULL, 8, handoff },
    { "Zero_own_animation_visual_and_nine_shot_events_capacity_faces_layers", NULL, NULL, 36, rakuhouha },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hyo_land_cases) + COUNT(ladder_slashes) + COUNT(player_zero_air_techniques_cases) + COUNT(player_zero_techniques_cases) + COUNT(player_special_extra_cases) + COUNT(player_special_states_cases) + COUNT(zero_shippuuga_cancel_context_cases_expected) + 1 + 2 + 2 + COUNT(soul_body_clone_archive_cases) + 54 + 96 + 12 + 72 + 12 + 16 + 96 + 8 + 36;
