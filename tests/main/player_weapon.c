#include "test_runtime.h"
#include "main/player_weapon.h"
#include "main/player_animations.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "support/player_cases.h"
#include "main/player.h"
void player_update_charged_shot_type(struct PlayerObj* self, s32 button);
void player_cancel_released_charge(void);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 charge_case(u32 mode)
{
    struct PlayerObj expected;
    struct EngineObj engine_before = engine_obj;
    u8 palette_before = need_palette_load;
    u32 i;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 16;
    g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.input.buttons.held = mode == 0 ? PLAYER_INPUT_SHOOT : mode == 1 ? PLAYER_INPUT_SPECIAL
                                                                             : PLAYER_INPUT_SHOOT | PLAYER_INPUT_SPECIAL;
    g_Player.charge_state[0] = PLAYER_CHARGE_FULL;
    g_Player.charge_state[1] = PLAYER_CHARGE_PARTIAL;
    g_Player.charge_timer = 21;
    g_Player.special_charge_timer = 34;
    g_Player.flash_palette = 7;
    expected = g_Player;
    if (mode == 0) {
        expected.charge_state[1] = 0;
        expected.special_charge_timer = 0;
    }
    if (mode == 1) {
        expected.charge_state[0] = 0;
        expected.charge_timer = 0;
    }
    player_cancel_released_charge();
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(need_palette_load == palette_before);
    return expected.charge_timer | ((u32)expected.special_charge_timer << 8) | ((u32)expected.flash_palette << 16);
}
static const u32 player_independent_charge_release_cases_expected[] = { 0x70015u, 0x72200u, 0x72215u };

static s32 sprites[4] = { 8, 12, 0x11223344, 0x55667788 };
static Palette palette_bank[3];
static u16 palette_storage[0x152];
static u8 stop_entries[8 * 4];
static u32 ladder_case(u32 mode)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_before[3];
    struct VisualObj visuals_before[32];
    struct WeaponObj weapons_before[16];
    u32 i, animation = mode == 2 ? 0x5F : mode == 1 ? 0x5C
                                                    : 0x6A;
    s32 result;
    memset(&obj, 0, sizeof(obj));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memset(stop_entries, 0, sizeof(stop_entries));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[1] = stop_entries;
    need_palette_load = 0x80;
    for (i = 0; i < 48; i++)
        ((u16*)palette_bank)[i] = 0x1200 + i;
    for (i = 0; i < COUNT(palette_storage); i++)
        palette_storage[i] = 0xBEEF;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    TEST_PALETTE = (u8*)&palette_storage[1];
    TEST_PALETTE_BANK = (u8*)palette_bank;
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = 0;
    obj.unk5 = PLAYER_LADDER_UP;
    obj.unk6 = 3;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_80119DF0;
    obj.unk17 = 7;
    obj.previous_animation_index = 8;
    obj.shot_cooldown = mode == 0 || mode == 4 ? 0 : 1;
    obj.shot_fired = mode == 3 ? 0 : 1;
    obj.shot_type = obj.last_shot_type = mode == 2 ? 2 : 0;
    obj.afterimage = 7;
    obj.voice_timer = 1;
    obj.attacking = 1;
    obj.attack_ended = 1;
    obj.attack_pose_timer = 20;
    obj.shot_palette_timer = 9;
    obj.stock_charge = 2;
    obj.charge_state[0] = obj.charge_state[1] = PLAYER_CHARGE_FULL;
    obj.charge_timer = 44;
    obj.special_charge_timer = 55;
    obj.flash_palette = 7;
    obj.dash_momentum = 1;
    obj.hurt_phase = 2;
    obj.invincibility_timer = 9;
    obj.unk15 = mode == 4 ? 0x40 : 0;
    obj.armor_parts = 2;
    obj.weapon_energy[0] = 0x30;
    obj.pressed_input = PLAYER_INPUT_GIGA;
    engine_obj.unk37 = mode == 4;
    expected = obj;
    engine_expected = engine_obj;
    if (mode != 3) {
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (u32*)D_80119DF0[animation];
        expected.animation_step = *(union AnimationStep*)D_80119DF0[animation];
        expected.unk3C = (u8*)sprites + 8;
    }
    if (mode == 1) {
        assert(player_ladder_shoot_animations[0] == 0x5C);
        expected.x_pos.val = 104 * 65536;
        expected.y_pos.u.lo = 0;
        expected.unk5 = PLAYER_LADDER_SHOOT;
        expected.unk6 = 0;
    } else if (mode == 2) {
        expected.afterimage = 0;
        expected.air_state = 1;
        expected.unk5 = PLAYER_WEAPON_POSE;
        expected.unk6 = 0;
    } else if (mode == 0 || mode == 4) {
        expected.attacking = expected.shot_fired = expected.attack_ended = expected.attack_pose_timer = expected.shot_cooldown = expected.shot_palette_timer = 0;
        expected.weapon = expected.stock_charge = expected.charge_state[0] = expected.charge_state[1] = 0;
        expected.charge_timer = expected.special_charge_timer = expected.flash_palette = 0;
        expected.shot_types[0] = expected.shot_types[1] = 0;
        expected.dash_momentum = 0;
        expected.air_action = 5;
        expected.afterimage = 0;
        expected.hurt_phase = 0;
        expected.invincibility_timer = 0;
        expected.air_state = 1;
        expected.spike_immune = 1;
        expected.nova_strike_active = 1;
        expected.nova_strike_timer = 24;
        expected.weapon_energy[0] = mode == 4 ? 0x30 : 0;
        expected.x_vel.val = mode == 4 ? 163840 : -163840;
        expected.y_vel.val = 229376;
        expected.unk28 = 0;
        expected.unk2C = 0x4200;
        expected.unk5 = PLAYER_NOVA_STRIKE;
        expected.unk6 = 0;
        engine_expected.gameplay_locked = 1;
    }
    result = player_check_shoot_ladder(&obj);
    assert(result == (mode == 3 ? 0 : 1));
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < 48; i++)
        assert(((u16*)palette_bank)[i] == 0x1200 + i);
    for (i = 0; i < COUNT(palette_storage); i++) {
        u16 value = 0xBEEF;
        if (mode == 0 || mode == 4) {
            if (i >= 1 && i <= 16)
                value = 0x1200 + i - 1;
            if (i >= 0x131 && i <= 0x150)
                value = 0x1210 + i - 0x131;
        }
        assert(palette_storage[i] == value);
    }
    assert(need_palette_load == (mode == 0 || mode == 4 ? 0x81 : 0x80));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < sizeof(stop_entries); i++)
        assert(stop_entries[i] == 0);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    i = result | ((u32)(u8)obj.unk5 << 8) | ((u32)obj.unk17 << 16) | ((u32)(u8)obj.shot_fired << 24);
    return i;
}
static const u32 player_ladder_attack_context_cases_expected[] = { 0x6A2201u, 0x15C2001u, 0x15F2601u, 0x70F00u, 0x6A2201u };

static const u32 player_charge_released_expected[] = { 1u };
static u32 test_player_charge_released(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    obj.input.buttons.held = 8224;
    obj.input.buttons.previous = 0;
    obj.charge_timer = 255;
    return_value = player_charge_released(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, player_charge_released_expected, 1);
}

struct player_charge_special_button_case {
    u32 charge_state_1, special_charge_timer, arm_type, stock_charge;
    u32 expected[3];
};
static const struct player_charge_special_button_case player_charge_special_button_cases[] = {
    { 2, 0, 0, 0, { 2u, 0u, 0u } },
    { 0, 24, 0, 0, { 1u, 0x19u, 0u } },
    { 0, 0, 1, 4, { 0u, 1u, 4u } },
    { 0, 149, 1, 0, { 2u, 0x96u, 4u } },
    { 0, 89, 1, 2, { 0u, 0x5Au, 2u } },
    { 0, 119, 1, 0, { 0u, 0x78u, 3u } },
    { 0, 89, 1, 0, { 0u, 0x5Au, 2u } },
};
static u32 test_player_charge_special_button(u32 row)
{
    const struct player_charge_special_button_case* c = &player_charge_special_button_cases[row];
    u32 observed_values[3];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.input.buttons.held = 8224;
    obj.charge_state[1] = c->charge_state_1;
    obj.special_charge_timer = c->special_charge_timer;
    obj.arm_type = c->arm_type;
    obj.stock_charge = c->stock_charge;
    player_charge_special_button(&obj);
    observed_values[0] = (u32)obj.charge_state[1];
    observed_values[1] = (u32)obj.special_charge_timer;
    observed_values[2] = (u32)obj.stock_charge;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 player_check_shoot_ladder_expected[] = { 0u, 0u };
static u32 test_player_check_shoot_ladder(u32 row)
{
    u32 observed_values[2];
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
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&need_palette_load, 0, sizeof(need_palette_load));

    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.input_locked = -1;
    obj.unk2 = 0;
    obj.shot_fired = 0;
    obj.shot_type = 0;
    return_value = player_check_shoot_ladder(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.afterimage;
    return c_test_observe(0, row, observed_values, player_check_shoot_ladder_expected, 2);
}

#include "support/state_cases.h"

static u32 weapon_sound_rows[0x20];
static u8* weapon_saved_rows;
#define SWAP(cur, flags, press, keys, setup) (weapon_saved_rows = D_80141F50[1], player_reset(1, 0, 0), D_80141F50[1] = (u8*)weapon_sound_rows, pl.weapon = cur, pl.boss_flags = flags, pl.pressed_input = press, pl.input.buttons.held = keys, setup, func_80036F50(&pl), D_80141F50[1] = weapon_saved_rows, player_extra = (u8)pl.weapon | (u8)pl.stock_charge << 8)
static void pw_locked(void)
{
    SWAP(1, 0xFF, 0x200, 0, pl.input_locked = 1);
}
static void pw_clone(void) { SWAP(1, 0xFF, 0x200, 0, pl.is_clone = 1); }
static void pw_specials(void) { SWAP(1, 0xFF, 0x200, 0, pl.special_shot_count = 1); }
static void pw_riding(void) { SWAP(1, 0xFF, 0x200, 0, pl.ride_state = 1); }
static void pw_nova(void) { SWAP(1, 0xFF, 0x200, 0, pl.nova_strike_active = 1); }
static void pw_frozen(void) { SWAP(1, 0xFF, 0x200, 0, engine_obj.gameplay_locked = 1); }
static void pw_both_held(void) { SWAP(3, 0xFF, 0, 0x600, 0); }
static void pw_both_pressed(void) { SWAP(3, 0xFF, 0x600, 0, 0); }
static void pw_both_buster(void) { SWAP(0, 0xFF, 0x600, 0, 0); }
static void pw_none(void) { SWAP(2, 0xFF, 0, 0, 0); }
static void pw_next(void) { SWAP(0, 5, 0x200, 0, pl.stock_charge = 2); }
static void pw_next_skip(void) { SWAP(1, 5, 0x200, 0, 0); }
static void pw_next_wrap(void) { SWAP(3, 5, 0x200, 0, 0); }
static void pw_prev_wrap(void) { SWAP(0, 0x80, 0x400, 0, 0); }
static void pw_prev_skip(void) { SWAP(3, 1, 0x400, 0, 0); }
static void pw_prev_buster(void) { SWAP(1, 0, 0x400, 0, 0); }
static void pw_same(void) { SWAP(0, 0, 0x200, 0, 0); }
static void pw_update_equip(void)
{
    weapon_saved_rows = D_80141F50[1];
    player_reset(1, 0, 0);
    D_80141F50[1] = (u8*)weapon_sound_rows;
    pl.unk2 = 0;
    pl.pressed_input = 0x200;
    pl.boss_flags = 1;
    player_update_weapon(&pl);
    D_80141F50[1] = weapon_saved_rows;
    player_extra = pl.weapon;
}
static void pw_update_clone(void)
{
    player_reset(1, 0, 0);
    pl.unk2 = 1;
    pl.pressed_input = 0x200;
    pl.boss_flags = 1;
    player_update_weapon(&pl);
    player_extra = pl.weapon;
}

static void (*const player_weapon_switch_cases[])(void) = {
    pw_locked,
    pw_clone,
    pw_specials,
    pw_riding,
    pw_nova,
    pw_frozen,
    pw_both_held,
    pw_both_pressed,
    pw_both_buster,
    pw_none,
    pw_next,
    pw_next_skip,
    pw_next_wrap,
    pw_prev_wrap,
    pw_prev_skip,
    pw_prev_buster,
    pw_same,
    pw_update_clone,
    pw_update_equip,
};
static const u32 player_weapon_switch_expected[] = { 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 2u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 3u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 8u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 0u, 1u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFFu, 1u };

static u32 test_player_weapon_switch(u32 row)
{
    return player_run(player_weapon_switch_cases[row], row, &player_weapon_switch_expected[row * 8]);
}

static u32 test_charge_inhibition(u32 row)
{
    struct PlayerObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u8 palette_before = need_palette_load;
    u32 mode = row / 2;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.state = PLAYER_STATE_NORMAL;
    obj.unk5 = PLAYER_IDLE;
    obj.hp = 24;
    obj.charge_state[0] = PLAYER_CHARGE_PARTIAL;
    obj.charge_state[1] = PLAYER_CHARGE_FULL;
    obj.charge_timer = 26;
    obj.special_charge_timer = 92;
    obj.flash_palette = 7;
    obj.input.buttons.held = PLAYER_INPUT_SHOOT | PLAYER_INPUT_SPECIAL;
    obj.pressed_input = row % 2 ? PLAYER_INPUT_SHOOT : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    switch (mode) {
    case 0:
        obj.unk2 = 1;
        break;
    case 1:
        obj.is_clone = 1;
        obj.unk5 = PLAYER_SOUL_BODY_CLONE;
        break;
    case 2:
        obj.nova_strike_active = 1;
        obj.unk5 = PLAYER_NOVA_STRIKE;
        break;
    case 3:
        obj.unk5 = PLAYER_BEAM_IN;
        break;
    case 4:
        obj.unk5 = PLAYER_BEAM_OUT;
        break;
    case 5:
        obj.unk5 = PLAYER_STAGE_CLEAR;
        break;
    case 6:
        obj.unk5 = PLAYER_SCRIPT_VICTORY;
        break;
    case 7:
        obj.ride_state = -1;
        obj.unk5 = PLAYER_RIDE;
        break;
    }
    expected = obj;
    player_update_charge(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(need_palette_load == palette_before);
    return 1;
}

static u32 test_stored_charge_priority(u32 row)
{
    static const u8 stored_shots[3] = { 2, 3, 4 };
    static const u8 charge_types[3][3] = {
        { 0, 9, 18 },
        { 0, 9, 20 },
        { 0, 9, 20 },
    };
    struct PlayerObj obj, expected;
    struct EngineObj engine_before = engine_obj;
    u8 palette_before = need_palette_load;
    u32 stored = row >= 18, index = row % 18;
    u32 button = index % 2, charge = index / 2 % 3, arm = index / 6;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.state = PLAYER_STATE_NORMAL;
    obj.unk5 = PLAYER_IDLE;
    obj.hp = 24;
    obj.arm_type = stored ? 1 : arm;
    obj.stock_charge = stored ? stored_shots[arm] : 0;
    obj.charge_state[0] = obj.charge_state[1] = charge;
    obj.charge_timer = 26;
    obj.special_charge_timer = 92;
    obj.shot_types[0] = 3;
    obj.shot_types[1] = 5;
    expected = obj;
    if (stored)
        expected.shot_types[button] = 19;
    else if (charge != PLAYER_CHARGE_NONE)
        expected.shot_types[button] = charge_types[arm][charge];
    player_update_charged_shot_type(&obj, button);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(need_palette_load == palette_before);
    return 1;
}

static const struct {
    u8 weapon, arm, armor, energy, allowed, full_time;
} variants[] = {
    { 0, 0, 0, 0, 1, 90 },
    { 0, 1, 0, 0, 1, 150 },
    { 0, 2, 0, 0, 1, 90 },
    { 1, 0, 0, 12, 0, 90 },
    { 1, 0, 4, 11, 0, 90 },
    { 1, 0, 4, 12, 1, 90 },
    { 1, 0, 4, 13, 1, 90 },
    { 8, 0, 4, 5, 0, 90 },
    { 8, 0, 4, 6, 1, 90 },
};
static const struct {
    u8 variant, timer, stock, state, held;
} cases[] = {
    { 0, 24, 0, 0, 0 },
    { 0, 24, 0, 2, 1 },
    { 3, 24, 0, 0, 1 },
    { 4, 24, 0, 0, 1 },
    { 5, 24, 0, 0, 1 },
    { 6, 24, 0, 0, 1 },
    { 7, 24, 0, 0, 1 },
    { 8, 24, 0, 0, 1 },
    { 0, 24, 0, 0, 1 },
    { 0, 89, 0, 1, 1 },
    { 2, 89, 0, 1, 1 },
    { 1, 89, 0, 1, 1 },
    { 1, 89, 2, 1, 1 },
    { 1, 119, 2, 1, 1 },
    { 1, 149, 3, 1, 1 },
    { 1, 149, 4, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 0, 255, 0, 1, 1 },
    { 1, 24, 0, 0, 1 },
    { 1, 119, 4, 1, 1 },
};
static u32 charge(u32 row)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    union PlayerChargeData costs_before = player_weapon_energy;
    u32 variant = cases[row].variant, stock = cases[row].stock, state = cases[row].state, held = cases[row].held;
    assert(PLAYER_CHARGE_NONE == 0 && PLAYER_CHARGE_PARTIAL == 1 && PLAYER_CHARGE_FULL == 2);
    assert(player_weapon_energy.charge.linked_thresholds[1] == 12 && player_weapon_energy.charge.linked_thresholds[8] == 6);
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.hp = 24;
    obj.state = 1;
    obj.weapon = variants[variant].weapon;
    obj.arm_type = variants[variant].arm;
    obj.armor_parts = variants[variant].armor;
    obj.weapon_energy[obj.weapon] = variants[variant].energy;
    obj.charge_timer = cases[row].timer;
    obj.stock_charge = stock;
    obj.charge_state[0] = state;
    obj.charge_state[1] = 1;
    obj.special_charge_timer = 37;
    obj.input.buttons.held = held ? PLAYER_INPUT_SHOOT : 0;
    obj.x_pos.val = 0x641234;
    obj.y_pos.val = 0x785678;
    expected = obj;
    if (held && state != 2 && variants[variant].allowed) {
        u8 next = cases[row].timer + 1;
        expected.charge_timer = next;
        if (next == 25)
            expected.charge_state[0] = 1;
        else {
            if (next == variants[variant].full_time)
                expected.charge_state[0] = 2;
            if (variant == 1 && stock != 4) {
                if (next == 90 && stock < 2)
                    expected.stock_charge = 2;
                if (next == 120)
                    expected.stock_charge = 3;
                if (next == 150)
                    expected.stock_charge = 4;
            }
        }
    }
    D_8013E198[1] = -1;
    player_charge_shoot_button(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&player_weapon_energy, &costs_before, sizeof(costs_before));
    assert(D_8013E198[1] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "charge_inhibition", 0, 0, 16, test_charge_inhibition },
    { "stored_charge_priority", 0, 0, 36, test_stored_charge_priority },
    { "player_weapon_switch", 0, 0, COUNT(player_weapon_switch_cases), test_player_weapon_switch },
    { "player_independent_charge_release", NULL, player_independent_charge_release_cases_expected, COUNT(player_independent_charge_release_cases_expected), charge_case },
    { "player_ladder_attack_context", NULL, player_ladder_attack_context_cases_expected, COUNT(player_ladder_attack_context_cases_expected), ladder_case },
    { "player_charge_released", 0, 0, 1, test_player_charge_released },
    { "player_charge_special_button", 0, 0, 7, test_player_charge_special_button },
    { "player_check_shoot_ladder", 0, 0, 1, test_player_check_shoot_ladder },
    { "charge_energy_stock_and_timer_boundaries", NULL, NULL, COUNT(cases), charge },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16 + 36 + COUNT(player_weapon_switch_cases) + COUNT(player_independent_charge_release_cases_expected) + COUNT(player_ladder_attack_context_cases_expected) + 1 + 7 + 1 + COUNT(cases);
