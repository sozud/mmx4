#include "test_runtime.h"
#include "main/player_weapon.h"
#include "main/player_animations.h"
#include "main/player_special.h"
#include "main/player_check.h"
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
#define CASE(m)                                                   \
    static u32 player_independent_charge_release_charge_##m(void) \
    {                                                             \
        return charge_case(m);                                    \
    }
CASE(0)
CASE(1)
CASE(2)
static const CTestCase player_independent_charge_release_cases[] = { player_independent_charge_release_charge_0, player_independent_charge_release_charge_1, player_independent_charge_release_charge_2 };
static const u32 player_independent_charge_release_cases_expected[] = { 0x70015u, 0x72200u, 0x72215u };
#undef CASE

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
#define CASE(m)                                              \
    static u32 player_ladder_attack_context_ladder_##m(void) \
    {                                                        \
        return ladder_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) player_ladder_attack_context_ladder_##m,
static const CTestCase player_ladder_attack_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 player_ladder_attack_context_cases_expected[] = { 0x6A2201u, 0x15C2001u, 0x15F2601u, 0x70F00u, 0x6A2201u };
#undef CASE
#undef ENTRY

struct func_80036F50_case {
    u32 pressed_input, held;
    u32 expected[2];
};
static const struct func_80036F50_case func_80036F50_cases[] = {
    { 0, 1542, { 0u, 0u } },
    { 1028, 0, { 0u, 0u } },
};
static u32 test_func_80036F50(u32 row)
{
    const struct func_80036F50_case* c = &func_80036F50_cases[row];
    u32 observed_values[2];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.pressed_input = c->pressed_input;
    obj.input.buttons.held = c->held;
    func_80036F50(&obj);
    observed_values[0] = (u32)obj.stock_charge;
    observed_values[1] = (u32)obj.weapon;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

static const u32 player_cancel_released_charge_expected[] = { 0u, 0u, 0xFFu, 0u };
static u32 test_player_cancel_released_charge(u32 row)
{
    u32 observed_values[4];
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&need_palette_load, 0, sizeof(need_palette_load));

    g_Player.input.buttons.held = 12336;
    g_Player.charge_timer = 255;
    g_Player.special_charge_timer = 0;
    player_cancel_released_charge();
    observed_values[0] = (u32)g_Player.charge_state[0];
    observed_values[1] = (u32)g_Player.charge_state[1];
    observed_values[2] = (u32)g_Player.charge_timer;
    observed_values[3] = (u32)g_Player.special_charge_timer;
    return c_test_observe(0, row, observed_values, player_cancel_released_charge_expected, 4);
}

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

struct player_charge_shoot_button_case {
    u32 charge_state_0, weapon, armor_parts, charge_timer, arm_type, stock_charge;
    u32 expected[3];
};
static const struct player_charge_shoot_button_case player_charge_shoot_button_cases[] = {
    { -3, 7, 4, 0, 0, 0, { 0xFFFFFFFDu, 0u, 0u } },
    { 0, 0, 0, 0, 1, 4, { 0u, 1u, 4u } },
    { 0, 0, 0, 89, 1, 2, { 0u, 0x5Au, 2u } },
};
static u32 test_player_charge_shoot_button(u32 row)
{
    const struct player_charge_shoot_button_case* c = &player_charge_shoot_button_cases[row];
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
    obj.input.buttons.held = 4112;
    obj.charge_state[0] = c->charge_state_0;
    obj.weapon = c->weapon;
    obj.armor_parts = c->armor_parts;
    obj.charge_timer = c->charge_timer;
    obj.arm_type = c->arm_type;
    obj.stock_charge = c->stock_charge;
    player_charge_shoot_button(&obj);
    observed_values[0] = (u32)obj.charge_state[0];
    observed_values[1] = (u32)obj.charge_timer;
    observed_values[2] = (u32)obj.stock_charge;
    return c_test_observe(0, row, observed_values, c->expected, 3);
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

struct player_check_special_button_case {
    u32 shot_types_1;
    u32 expected[1];
};
static const struct player_check_special_button_case player_check_special_button_cases[] = {
    { 19, { 0xFFFFFFFFu } },
    { -1, { 0xFFFFFFFFu } },
};
static u32 test_player_check_special_button(u32 row)
{
    const struct player_check_special_button_case* c = &player_check_special_button_cases[row];
    u32 observed_values[1];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.shot_type = -1;
    obj.shot_types[1] = c->shot_types_1;
    obj.input.buttons.previous = 8224;
    player_check_special_button(&obj);
    observed_values[0] = (u32)obj.shot_type;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 player_has_weapon_energy_expected[] = { 0u };
static u32 test_player_has_weapon_energy(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&player_weapon_energy, 0, sizeof(player_weapon_energy));
    return_value = player_has_weapon_energy(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, player_has_weapon_energy_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "player_independent_charge_release", player_independent_charge_release_cases, player_independent_charge_release_cases_expected, COUNT(player_independent_charge_release_cases), 0 },
    { "player_ladder_attack_context", player_ladder_attack_context_cases, player_ladder_attack_context_cases_expected, COUNT(player_ladder_attack_context_cases), 0 },
    { "func_80036F50", 0, 0, 2, test_func_80036F50 },
    { "player_cancel_released_charge", 0, 0, 1, test_player_cancel_released_charge },
    { "player_charge_released", 0, 0, 1, test_player_charge_released },
    { "player_charge_shoot_button", 0, 0, 3, test_player_charge_shoot_button },
    { "player_charge_special_button", 0, 0, 7, test_player_charge_special_button },
    { "player_check_shoot_ladder", 0, 0, 1, test_player_check_shoot_ladder },
    { "player_check_special_button", 0, 0, 2, test_player_check_special_button },
    { "player_has_weapon_energy", 0, 0, 1, test_player_has_weapon_energy },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(player_independent_charge_release_cases) + COUNT(player_ladder_attack_context_cases) + 2 + 1 + 1 + 3 + 7 + 1 + 2 + 1;
