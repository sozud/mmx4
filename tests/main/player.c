#include "test_runtime.h"
#include "support/player_cases.h"
#include "main/player.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/player_animations.h"
#include "main/collision.h"
#include "main/player_animations_2.h"
#include "main/player_weapon.h"
#include "main/player_common.h"
#include "main/player_enter.h"
#include "main/55C4.h"
void player_hurt_slide(struct PlayerObj*);

static const u32 player_hurt_slide_expected[] = { 0u, 0u };
static u32 test_player_hurt_slide(u32 row)
{
    u32 observed_values[2];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.capsule_state = -1;
    player_hurt_slide(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, player_hurt_slide_expected, 2);
}

static const struct {
    u8 facing, collision, event, timer;
    s32 velocity, delta, remaining;
} dash_braking[] = {
    { 0, 0, 0x40, 0, FIXED(-2), FIXED(-2), FIXED(-1) },
    { 0x40, 0, 0x40, 0, FIXED(2), FIXED(2), FIXED(1) },
    { 0, 0, 0x40, 0, FIXED(-0.5), FIXED(-0.5), 0 },
    { 0x40, 0, 0x40, 0, FIXED(0.5), FIXED(0.5), 0 },
    { 0, PLAYER_COLLIDE_LEFT, 0x40, 0, FIXED(-2), 0, 0 },
    { 0x40, PLAYER_COLLIDE_RIGHT, 0x40, 0, FIXED(2), 0, 0 },
    { 0, PLAYER_COLLIDE_RIGHT, 0x40, 0, FIXED(-2), FIXED(-2), FIXED(-1) },
    { 0x40, PLAYER_COLLIDE_LEFT, 0x40, 0, FIXED(2), FIXED(2), FIXED(1) },
    { 0, 0, 0x40, 0, 0, 0, 0 },
    { 0, 0, 0, 0, FIXED(-2), 0, FIXED(-2) },
    { 0, 0, 0x80, 0, FIXED(-2), 0, FIXED(-2) },
    { 0x40, 0, 0xC0, 1, FIXED(2), 0, FIXED(2) },
    { 0x40, 0, 0xC0, 0, FIXED(2), FIXED(2), FIXED(1) },
};

static u32 test_dash_braking(u32 row)
{
    player_reset(PLAYER_DASH, 2, 0x11);
    pl.input_locked = 1;
    pl.unk15 = dash_braking[row].facing;
    pl.unk88.bytes.collision_flags = dash_braking[row].collision;
    pl.animation_step.fields.event = dash_braking[row].event;
    pl.animation_step.fields.relative_step = 1;
    pl.dash_timer = dash_braking[row].timer;
    pl.x_vel.val = dash_braking[row].velocity;
    pl.unk28 = FIXED(-1);

    player_dash_end(&pl);

    assert(pl.x_pos.val == FIXED(100) + dash_braking[row].delta);
    assert(pl.y_pos.val == FIXED(200));
    assert(pl.x_vel.val == dash_braking[row].remaining);
    assert(pl.unk15 == dash_braking[row].facing);
    assert(pl.unk88.bytes.collision_flags == dash_braking[row].collision);
    assert(pl.animation_step.fields.event == (dash_braking[row].event & 0x7F));
    assert(pl.unk5 == PLAYER_DASH && pl.unk6 == 2);
    return pl.x_vel.val;
}

static const struct {
    u16 pressed, held;
    u8 technique, ladder, expected_step;
} dash_cancels[] = {
    { 0, PLAYER_INPUT_UP, 0, 1, PLAYER_LADDER_TRANSITION },
    { PLAYER_INPUT_SPECIAL, 0, 1, 0, PLAYER_ZERO_RAIJINGEKI },
    { PLAYER_INPUT_SHOOT, 0, 0, 0, PLAYER_ZERO_SABER },
    { PLAYER_INPUT_JUMP, 0, 0, 0, PLAYER_JUMP },
    { PLAYER_INPUT_DASH, 0, 0, 0, PLAYER_DASH },
};

static u32 test_dash_cancels(u32 row)
{
    player_reset(PLAYER_DASH, 2, 0x11);
    pl.pressed_input = dash_cancels[row].pressed;
    pl.input.buttons.held = dash_cancels[row].held;
    pl.boss_flags = dash_cancels[row].technique;
    player_attrs[0] = C_TEST_PSX_WORD(dash_cancels[row].ladder ? 0x20 : 0);
    player_dash_end(&pl);
    assert(pl.unk5 == dash_cancels[row].expected_step);
    assert(pl.unk6 != 2);
    return (u8)pl.unk5;
}

#ifndef VERSION_DEMO
static u32 test_dash_nova_strike(u32 row)
{
    static u8 sound_commands[32];
    player_reset(PLAYER_DASH, 2, 0x11);
    D_80141F50[1] = sound_commands;
    pl.unk2 = 0;
    pl.animation_table = (u32**)D_80119DF0;
    pl.unk15 = row ? PLAYER_FACING_RIGHT : 0;
    pl.armor_parts = 2;
    pl.weapon_energy[0] = 0x30;
    pl.pressed_input = PLAYER_INPUT_GIGA;
    player_dash_end(&pl);
    assert(pl.unk5 == PLAYER_NOVA_STRIKE && pl.unk6 == 0);
    assert(pl.nova_strike_active == 1 && pl.nova_strike_timer == 0x18);
    assert(pl.weapon_energy[0] == 0 && SPIKE_IMMUNE(pl) == 1);
    assert(pl.air_action == 5 && pl.air_state == 1 && engine_obj.gameplay_locked == 1);
    assert(pl.x_vel.val == (row ? FIXED(2.5) : FIXED(-2.5)));
    assert(pl.y_vel.val == FIXED(3.5));
    return (u8)pl.unk5;
}
#endif

void player_ladder_up(struct PlayerObj*);
void player_ladder_down(struct PlayerObj*);
void player_ladder_step_off_bottom(struct PlayerObj*);
void player_set_collision_bounds(struct PlayerObj*);
void player_settle(struct PlayerObj*);
void player_dash(struct PlayerObj*);
void player_ride(struct PlayerObj*);

static struct Unk_unk68 bounds = { 0, 0, 4, 4 };
static u32 gfx[16] = { 0x20, 0x24 };
static u32 sprites[16] = { 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34 };
static u8 tilemap[3 * 256], sound_commands[32];
static u16 pixels[512];
static u32 attributes[2];
static Palette bank[16];
static u16 palette[0x152], palette_expected[0x152];
static struct PlayerObj expected, entity_before;
static struct EngineObj engine_expected;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_expected[32];
static u32 palette_dirty;

static void prepare(u32 profile)
{
    u32 i;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)sound_commands, sizeof(sound_commands) / 4);
    c_test_zero_words((u32*)pixels, sizeof(pixels) / 4);
    for (i = 0; i < COUNT(tilemap); i++)
        tilemap[i] = 1;
    for (i = 0; i < sizeof(bank) / 2; i++)
        ((u16*)bank)[i] = 0x1200 + i;
    for (i = 0; i < COUNT(palette); i++)
        palette[i] = palette_expected[i] = 0xBEEF;
    attributes[0] = C_TEST_PSX_WORD(0x20);
    attributes[1] = C_TEST_PSX_WORD(0x38);
    for (i = 480; i < COUNT(pixels); i++)
        pixels[i] = 1;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    TEST_PALETTE = (u8*)&palette[1];
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    SP_BG_TILEMAP = tilemap;
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
    g_Player.unk15 = profile % 2 ? PLAYER_FACING_RIGHT : 0;
    g_Player.bg_offset = profile % 3;
    g_Player.x_pos.val = (100 + profile % 3 * 16) * 65536 + 0x1234;
    g_Player.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.x_vel.val = ((s32)(profile % 3) - 1) * 0x20000;
    g_Player.y_vel.val = 0x38000;
    g_Player.unk28 = 0x1000;
    g_Player.unk2C = 0x4200;
    g_Player.unk38 = (u8*)gfx + 0x24;
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
    c_test_copy_words((u32*)weapons_expected, (const u32*)weapon_objects, sizeof(weapons_expected) / 4);
    c_test_copy_words((u32*)visuals_expected, (const u32*)visual_objects, sizeof(visuals_expected) / 4);
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
    SAME(&weapon_objects, &weapons_expected);
    SAME(&visual_objects, &visuals_expected);
    for (i = 0; i < COUNT(palette); i++)
        assert(palette[i] == palette_expected[i]);
    for (i = 0; i < sizeof(bank) / 2; i++)
        assert(((u16*)bank)[i] == 0x1200 + i);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == (i >= 480));
    for (i = 0; i < COUNT(sound_commands); i++)
        assert(sound_commands[i] == 0);
    for (i = 0; i < 16; i++) {
        assert(gfx[i] == (i < 2 ? 0x20 + 4 * i : 0));
        assert(sprites[i] == (i < 6 ? 0x20 + 4 * i : 0));
    }
    assert(attributes[0] == C_TEST_PSX_WORD(0x20) && attributes[1] == C_TEST_PSX_WORD(0x38) && bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(cur_random == 0x1234 && need_palette_load == palette_dirty);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(D_80141F50[1] == sound_commands);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)sprites);
    assert(TEST_PALETTE == (u8*)&palette[1] && TEST_PALETTE_BANK == (u8*)bank);
    assert(SP_BG_TILEMAP == tilemap && TEST_BG_TILE_PIXELS == (u8*)pixels && TEST_BG_TILE_ATTRS == (u8*)attributes);
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
}

static void expect_animation(u32 animation, u32 word)
{
    const u32* const* table = expected.unk2 ? D_8011AFF0 : D_80119DF0;
    u32 resource = expected.unk2 && animation == 0x41 ? 1 : 0;
    assert(table[animation][0] == C_TEST_STEP(word));
    if (expected.unk2)
        assert(D_8011AF60[animation] == resource);
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (u32*)table[animation];
    expected.animation_step.packed = C_TEST_STEP(word);
    if (expected.unk2)
        expected.unk38 = (u8*)gfx + (resource ? 0x24 : 0x20);
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
            palette_expected[1 + i] = 0x1270 + i;
            palette_expected[1 + 0x130 + i] = 0x1290 + i;
        }
    } else {
        for (i = 0; i < 16; i++)
            palette_expected[1 + i] = 0x1200 + source + i;
        if (!expected.unk2)
            for (i = 0; i < 32; i++)
                palette_expected[1 + 0x130 + i] = 0x1210 + i;
    }
#ifdef VERSION_SATURN_PROTO
    palette_dirty = 1;
#else
    palette_dirty |= 1;
#endif
}

static u32 test_ladder_floor_lifecycle(u32 row)
{
    u32 down = row / 36, i;
    prepare_character(row % 36);
    g_Player.unk5 = down ? PLAYER_LADDER_DOWN : PLAYER_LADDER_UP;
    g_Player.unk6 = 0;
    g_Player.dash_momentum = g_Player.air_action = g_Player.afterimage = 0;
    g_Player.x_pos.val = 104 * 65536;
    g_Player.y_pos.val = (g_Player.unk2 ? 202 : 203) * 65536 + 0x5678;
    g_Player.x_vel.val = g_Player.unk28 = g_Player.unk2C = 0;
    g_Player.y_vel.val = down ? -0x18000 : 0x18000;
    player_set_collision_bounds(&g_Player);
    g_Player.unk18 = g_Player.x_pos;
    g_Player.unk1C = g_Player.y_pos;
    set_animation(&g_Player, down ? 0x20 : 0x1F);
    CollisionRelated(&g_Player);
    assert(g_Player.unk70 == 8);
    assert(g_Player.y_pos.val == (g_Player.unk2 ? 202 : 203) * 65536);
    g_Player.unk88.bytes.collision_flags = g_Player.unk70;
    capture();
    expect_animation(0x1E, expected.unk2 ? 0xC2010005 : 0x8F010005);
    expect_clear_attack();
    expected.unk5 = PLAYER_LADDER_TRANSITION;
    expected.unk6 = 3;
    if (down)
        player_ladder_down(&g_Player);
    else
        player_ladder_up(&g_Player);
    check();
    for (i = 0; i < 5; i++) {
        if (i < 4)
            expected.animation_step.fields.duration--;
        else {
            assert(expected.animation_table[0x1E][1] == C_TEST_PSX_WORD(expected.unk2 ? 0xC2FF0060 : 0x8FFF0060));
            expected.air_state = 0;
            expect_animation(expected.unk2 ? 9 : 5, expected.unk2 ? 0x05010004 : 0x0001000B);
            expected.unk5 = expected.unk2 ? PLAYER_SETTLE : PLAYER_IDLE;
            expected.unk6 = 0;
        }
        player_ladder_step_off_bottom(&g_Player);
        SAME(&g_Player, &expected);
    }
    check();
    return 1;
}

static u32 test_ladder_slash_entry(u32 row)
{
    u32 down = row / 12 % 2, side = row / 24;
    prepare_character(row % 6 * 3 + 2 + row / 6 % 2 * 18);
    g_Player.input_locked = 0;
    g_Player.attacking = 0;
    g_Player.dash_momentum = g_Player.air_action = g_Player.afterimage = 0;
    g_Player.combo = 2;
    g_Player.unk5 = down ? PLAYER_LADDER_DOWN : PLAYER_LADDER_UP;
    g_Player.unk6 = 0;
    g_Player.y_pos.val = 160 * 65536;
    g_Player.x_pos.val = 104 * 65536;
    g_Player.input.buttons.held = down ? PLAYER_INPUT_DOWN : PLAYER_INPUT_UP;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT | (side ? PLAYER_INPUT_RIGHT : PLAYER_INPUT_LEFT);
    set_animation(&g_Player, down ? 0x20 : 0x1F);
    capture();
    expected.attacking = 1;
    expected.combo = 0;
    expected.unk5 = PLAYER_ZERO_LADDER_SLASH;
    expected.unk6 = 1;
    expected.unk15 = side ? PLAYER_FACING_RIGHT : 0;
    expect_animation(0x5D, 0xC3010002);
    if (down)
        player_ladder_down(&g_Player);
    else
        player_ladder_up(&g_Player);
    check();
    return 1;
}

static void expect_script_jump(void)
{
    expected.unk5 = PLAYER_SCRIPT_JUMP;
    expected.unk6 = 0;
    expected.dash_momentum = expected.air_action = expected.afterimage = 0;
    expect_clear_attack();
    expect_animation(0xA, expected.unk2 ? 0x15010003 : 0x21010002);
    expected.unk68 = expected.unk2 ? &player_zero_collision_bounds : &player_x_collision_bounds;
    expected.y_vel.val = 0x5D000;
    expected.unk2C = 0x4200;
    expected.x_vel.val = expected.unk28 = 0;
    expected.air_state = 1;
    expected.unk15 = expected.script_facing;
}

static u32 test_ride_script(u32 row)
{
    u32 request = row % 4;
    prepare_character(row);
    g_Player.unk5 = PLAYER_RIDE;
    g_Player.unk6 = 1;
    g_Player.ride_state = request == 3 ? 0 : -1;
    g_Player.unk68 = NULL;
    g_Player.ride_animation = 0x41;
    g_Player.script_state = request == 0 ? -1 : request == 1 ? 0
                                                             : 1;
    g_Player.script_action = request == 2 ? 0x14 : 0x17;
    g_Player.script_facing = g_Player.unk15 ^ PLAYER_FACING_RIGHT;
    set_animation(&g_Player, 0x41);
    capture();
    assert(expected.animation_step.packed == C_TEST_STEP(expected.unk2 ? 0x10010003 : 0xA2000060));
    if (request == 3)
        expect_script_jump();
    else
        expected.animation_step.fields.duration--;
    player_ride(&g_Player);
    check();
    return 1;
}

static u32 test_script_interrupt(u32 row)
{
    static void (*const callbacks[])(struct PlayerObj*) = { player_settle, player_land, player_dash };
    static const u8 states[] = { PLAYER_SETTLE, PLAYER_LAND, PLAYER_DASH };
    u32 callback = row / 36;
    prepare_character(row % 36);
    g_Player.unk5 = states[callback];
    g_Player.unk6 = 0;
    g_Player.script_state = 1;
    g_Player.script_action = 0x17;
    g_Player.script_facing = g_Player.unk15 ^ PLAYER_FACING_RIGHT;
    set_animation(&g_Player, 0xA);
    capture();
    expect_script_jump();
    callbacks[callback](&g_Player);
    check();
    return 1;
}

void player_script_jump(struct PlayerObj*);
void player_wall_cling(struct PlayerObj*);
void player_wall_jump_push(struct PlayerObj*);
void player_wall_slide_down(struct PlayerObj*);
void player_wall_slide_release(struct PlayerObj*);
void player_air_dash(struct PlayerObj*);
void player_air_dash_end(struct PlayerObj*);
void player_hover(struct PlayerObj*);
void player_ladder_step_off_bottom(struct PlayerObj*);
void player_ladder_up(struct PlayerObj*);
void player_ladder_down(struct PlayerObj*);
void player_set_animation_frame(struct PlayerObj*, s32, s32);
void player_enter_fall_shooting(struct PlayerObj*);

struct AnimationReference {
    u8 character, animation, count, bank;
    u32 words[45];
};
static const struct AnimationReference references[] = {
    { 0, 5, 14, 0, { 0x0001000B, 0x7301000D, 0x0001000B, 0x7701000D, 0x0001000B, 0x7301000D, 0x0001000B, 0x7701000D, 0x0001000B, 0x74010004, 0x75010005, 0x76010004, 0x0001000B, 0x77F3000D } },
    { 0, 0x1E, 2, 0, { 0x8F010005, 0x8FFF0060 } },
    { 0, 0x1F, 8, 0, { 0x94010705, 0x97010604, 0x91010504, 0x93010404, 0x95010305, 0x98010204, 0x90010104, 0x92F90004 } },
    { 0, 0x20, 8, 0, { 0x92010704, 0x90010604, 0x98010504, 0x95010405, 0x93010304, 0x91010204, 0x97010104, 0x94F90005 } },
    { 0, 0x7B, 8, 0, { 0x2A010004, 0x2C010104, 0x2E010204, 0x30000360, 0x32010003, 0x34010103, 0x36010202, 0x36FF0360 } },
    { 1, 9, 3, 0, { 0x05010004, 0x06010104, 0x06FF0260 } },
    { 1, 0x1E, 2, 0, { 0xC2010005, 0xC2FF0060 } },
    { 1, 0x1F, 10, 0, { 0xAE010002, 0xAF010104, 0xB2010905, 0xB6010805, 0xBA010705, 0xB0010602, 0xB1010504, 0xB4010405, 0xB8010305, 0xBBF70205 } },
    { 1, 0x20, 10, 0, { 0xAE010002, 0xAF010104, 0xBD010905, 0xB9010805, 0xB5010705, 0xB0010602, 0xB1010504, 0xBC010405, 0xB7010305, 0xB3F70205 } },
    { 0, 0xA, 4, 0, { 0x21010002, 0x23018104, 0x25010206, 0x27000360 } },
    { 0, 0xB, 4, 0, { 0x29010004, 0x2B010104, 0x2D010204, 0x2F000360 } },
    { 0, 0xC, 4, 0, { 0x31010003, 0x33010103, 0x35010202, 0x35FF0360 } },
    { 0, 0x7C, 4, 0, { 0x32010003, 0x34010103, 0x36010202, 0x36FF0360 } },
    { 0, 0x84, 5, 0, { 0x28010005, 0x2A010103, 0x2C010204, 0x2E010304, 0x30000460 } },
    { 1, 0xA, 5, 0, { 0x15010003, 0x16018104, 0x17010203, 0x16010304, 0x17FF0403 } },
    { 1, 0xB, 9, 0, { 0x18010003, 0x19010103, 0x1A010203, 0x1B010303, 0x1C010403, 0x1D010504, 0x1E010603, 0x1F010704, 0x20FD0803 } },
    { 1, 0xC, 3, 0, { 0x21010004, 0x22010105, 0x22FF0260 } },
    { 1, 0x58, 18, 0, { 0x3D010001, 0x3E010001, 0x3F018001, 0x41010001, 0x43010001, 0x45010001, 0x47010002, 0x49012002, 0x4B012002, 0x4D012003, 0x4F012004, 0x51010002, 0x52014002, 0x83014002, 0x84014004, 0x85014006, 0x86014004, 0x86004060 } },
    { 1, 0x5F, 45, 1, { 0x56010002, 0x57010002, 0x58010002, 0x5B018002, 0x57010002, 0x57010002, 0x5D010002, 0x57010002, 0x57010002, 0x5D010002, 0x60011002, 0x63010002, 0x65010002, 0x67010002, 0x69010002, 0x6C010002, 0x6E010002, 0x70010002, 0x72010002, 0x74010002, 0x77010002, 0x7A010002, 0x7D010002, 0x74010002, 0x77010002, 0x7A010002, 0x7D010002, 0x74010002, 0x77010002, 0x7A010002, 0x7D010002, 0x74010002, 0x77010002, 0x7A010002, 0x7D010002, 0x80010002, 0x81010002, 0x82010003, 0x83010004, 0x6B014002, 0x62014002, 0x5F014004, 0x57014006, 0x56014004, 0x56004060 } },
};

static u32 gfx_player_script_motion[64], sprites_player_script_motion[64];
static struct PlayerObj expected_player_script_motion, entity_before_player_script_motion;
static struct EngineObj engine_before;
static struct MainBssState main_before_player_script_motion;
static struct BackgroundObj backgrounds_before_player_script_motion[3];
static struct WeaponObj weapons_before[16];
static struct VisualObj visuals_before[32];

static const struct AnimationReference* reference(u32 character, u32 animation)
{
    u32 i;
    for (i = 0; i < COUNT(references); i++)
        if (references[i].character == character && references[i].animation == animation)
            return &references[i];
    assert(0);
    return &references[0];
}

static void prepare_player_script_motion(u32 character, u32 facing, u32 profile)
{
    u32 i;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words(gfx_player_script_motion, COUNT(gfx_player_script_motion));
    c_test_zero_words(sprites_player_script_motion, COUNT(sprites_player_script_motion));
    gfx_player_script_motion[0] = sprites_player_script_motion[0] = 0x40;
    gfx_player_script_motion[1] = sprites_player_script_motion[5] = 0x80;
    TEST_PLAYER_GFX = (u8*)gfx_player_script_motion;
    TEST_SPRITE_FRAMES = (u8*)sprites_player_script_motion;
    g_Entity.hp = 17;
    g_Entity.x_pos.val = 0x12345678;
    engine_obj.cur_character = character;
    engine_obj.stage = 4;
    engine_obj.max_hp = 24;
    for (i = 0; i < COUNT(weapon_objects); i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].owner = &g_Entity;
    }
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].unk50 = &g_Entity;
    }
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = (i + 1) * 0x1000000;
        background_objects[i].y_pos.val = (i + 1) * 0x800000;
    }
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.unk2 = character;
    g_Player.unk5 = PLAYER_SCRIPT_JUMP;
    g_Player.hp = 24;
    g_Player.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    g_Player.bg_offset = profile % 3;
    g_Player.unk38 = (u8*)gfx_player_script_motion + 0xC0;
    g_Player.unk3C = (u8*)sprites_player_script_motion + 0xC0;
    g_Player.animation_table = (u32**)(character ? D_8011AFF0 : D_80119DF0);
    g_Player.x_pos.val = profile % 2 ? -0x1234567 : 0xA01234;
    g_Player.y_pos.val = profile % 3 ? 0x780567 : -0x123567;
    g_Player.x_vel.val = ((s32)(profile % 3) - 1) * 0x20000;
    g_Player.y_vel.val = 0x38000;
    g_Player.unk28 = 0x1000;
    g_Player.unk2C = 0x4200;
    g_Player.input_locked = 1;
    g_Player.script_state = 2;
    g_Player.air_state = 1;
    g_Player.air_action = 1;
    g_Player.dash_momentum = 1;
    g_Player.afterimage = (s32)(profile % 3) - 1;
    g_Player.combo = 2;
    g_Player.voice_timer = 1;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture_player_script_motion(void)
{
    expected_player_script_motion = g_Player;
    entity_before_player_script_motion = g_Entity;
    engine_before = engine_obj;
    main_before_player_script_motion = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before_player_script_motion, (const u32*)background_objects, sizeof(backgrounds_before_player_script_motion) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)visuals_before, (const u32*)visual_objects, sizeof(visuals_before) / 4);
}

#define SAME_player_script_motion(actual, wanted) assert(c_test_word_difference((const u32*)(actual), (const u32*)(wanted), sizeof(*(wanted)) / 4) == 0)
static void check_player_script_motion(void)
{
    u32 i, j;
    SAME_player_script_motion(&g_Player, &expected_player_script_motion);
    SAME_player_script_motion(&g_Entity, &entity_before_player_script_motion);
    SAME_player_script_motion(&engine_obj, &engine_before);
    SAME_player_script_motion(&main_bss_state, &main_before_player_script_motion);
    SAME_player_script_motion(&background_objects, &backgrounds_before_player_script_motion);
    SAME_player_script_motion(&weapon_objects, &weapons_before);
    SAME_player_script_motion(&visual_objects, &visuals_before);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(need_palette_load == 0x20 && cur_random == 0x1234);
    assert(TEST_PLAYER_GFX == (u8*)gfx_player_script_motion && TEST_SPRITE_FRAMES == (u8*)sprites_player_script_motion);
    for (i = 0; i < COUNT(gfx_player_script_motion); i++) {
        assert(gfx_player_script_motion[i] == (i == 0 ? 0x40 : i == 1 ? 0x80
                                                                      : 0));
        assert(sprites_player_script_motion[i] == (i == 0 ? 0x40 : i == 5 ? 0x80
                                                                          : 0));
    }
    for (i = 0; i < COUNT(references); i++) {
        const struct AnimationReference* ref = &references[i];
        const u32* words = ref->character ? D_8011AFF0[ref->animation] : D_80119DF0[ref->animation];
        for (j = 0; j < ref->count; j++)
            assert(words[j] == C_TEST_STEP(ref->words[j]));
        if (ref->character)
            assert(D_8011AF60[ref->animation] == ref->bank);
    }
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static void expect_animation_player_script_motion(u32 animation, u32 frame, u32 explicit_frame)
{
    const struct AnimationReference* ref = reference(expected_player_script_motion.unk2, animation);
    assert(frame < ref->count);
    expected_player_script_motion.unk17 = animation;
    expected_player_script_motion.previous_animation_index = 0xFF;
    expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[animation] + frame;
    expected_player_script_motion.animation_step.packed = C_TEST_STEP(ref->words[frame]);
    if (expected_player_script_motion.unk2 || explicit_frame)
        expected_player_script_motion.unk38 = (u8*)gfx_player_script_motion + (ref->bank ? 0x80 : 0x40);
    expected_player_script_motion.unk3C = (u8*)sprites_player_script_motion + (ref->bank ? 0x80 : 0x40);
}

static void expect_tick(void)
{
    const struct AnimationReference* ref = reference(expected_player_script_motion.unk2, expected_player_script_motion.unk17);
    u32 frame = expected_player_script_motion.animation_cursor - expected_player_script_motion.animation_table[expected_player_script_motion.unk17];
    u32 duration = (u8)expected_player_script_motion.animation_step.fields.duration;
    assert(duration != 0 && frame < ref->count);
    if (duration == 1) {
        s32 next = (s32)frame + expected_player_script_motion.animation_step.fields.relative_step;
        assert(next >= 0 && next < ref->count);
        expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[expected_player_script_motion.unk17] + next;
        expected_player_script_motion.animation_step.packed = C_TEST_STEP(ref->words[next]);
    } else
        expected_player_script_motion.animation_step.fields.duration = duration - 1;
    expected_player_script_motion.x_pos.val += expected_player_script_motion.x_vel.val;
    expected_player_script_motion.y_pos.val -= expected_player_script_motion.y_vel.val;
    expected_player_script_motion.x_vel.val += expected_player_script_motion.unk15 ? expected_player_script_motion.unk28 : -expected_player_script_motion.unk28;
    expected_player_script_motion.y_vel.val -= expected_player_script_motion.unk2C;
    if (expected_player_script_motion.y_vel.val < -0x68000)
        expected_player_script_motion.y_vel.val = -0x68000;
}

static void expect_landing(void)
{
    expected_player_script_motion.script_state = 0;
    expected_player_script_motion.air_state = 0;
    expected_player_script_motion.air_action = 0;
    expected_player_script_motion.dash_momentum = 0;
    if (expected_player_script_motion.afterimage > 0)
        expected_player_script_motion.afterimage = -1;
}

static u32 test_script_jump(u32 row)
{
    static const s32 ascending[] = { 0, 0x41FF, 0x4200, 0x4201, 0x10000, 0x60000 };
    static const s32 falling[] = { 0, -1, -0x4200, -0x63DFF, -0x63E00, -0x68000 };
    u32 phase = row % 2, ground = row / 2 % 2, last_frame = row / 4 % 2, short_duration = row / 8 % 2;
    u32 acceleration = row / 16 % 2, velocity = row % 6;
    u32 character = (phase + ground) % 2, facing = (last_frame + short_duration) % 2;
    const struct AnimationReference* ref = reference(character, phase ? 0xB : 0xA);
    u32 frame = last_frame ? ref->count - 1 : 0;
    prepare_player_script_motion(character, facing, velocity);
    set_animation_frame(ANIMATED_OBJECT(&g_Player), ref->animation, frame);
    if (short_duration)
        g_Player.animation_step.fields.duration = 1;
    g_Player.unk6 = phase;
    g_Player.unk88.bytes.collision_flags = ground ? PLAYER_COLLIDE_GROUND : 0;
    g_Player.y_vel.val = phase ? falling[velocity] : ascending[velocity];
    g_Player.unk28 = acceleration ? 0x1000 : 0;
    g_Player.attacking = acceleration;
    capture_player_script_motion();
    if (phase && ground) {
        expect_landing();
        expect_animation_player_script_motion(!character && acceleration ? 0x7C : 0xC, 0, 0);
        expected_player_script_motion.unk5 = PLAYER_LAND;
        expected_player_script_motion.unk6 = 0;
    } else {
        expect_tick();
        if (!phase && expected_player_script_motion.y_vel.val <= 0) {
            expect_animation_player_script_motion(0xB, 0, 0);
            expected_player_script_motion.air_state = -1;
            expected_player_script_motion.y_vel.val = 0;
            expected_player_script_motion.unk6 = 1;
        }
    }
    player_script_jump(&g_Player);
    check_player_script_motion();
    return 1;
}

static u32 test_animation_frames(u32 row)
{
    u32 frame = row % 101, variant = row / 101, i = 0;
    const struct AnimationReference* ref;
    while (frame >= references[i].count)
        frame -= references[i++].count;
    ref = &references[i];
    prepare_player_script_motion(ref->character, variant % 2, variant);
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0xA, 1);
    capture_player_script_motion();
    expect_animation_player_script_motion(ref->animation, frame, 1);
    player_set_animation_frame(&g_Player, ref->animation, frame);
    check_player_script_motion();
    return 1;
}

static u32 test_fall_shooting(u32 row)
{
    prepare_player_script_motion(0, row % 2, row / 2);
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0xA, row / 2 % 4);
    g_Player.attacking = 1;
    g_Player.unk6 = 1;
    capture_player_script_motion();
    expect_animation_player_script_motion(0x84, 0, 0);
    expected_player_script_motion.x_vel.val = expected_player_script_motion.y_vel.val = expected_player_script_motion.unk28 = 0;
    expected_player_script_motion.unk2C = 0x4200;
    expected_player_script_motion.air_state = -1;
    expected_player_script_motion.dash_momentum = expected_player_script_motion.afterimage = 0;
    expected_player_script_motion.unk5 = PLAYER_FALL;
    expected_player_script_motion.unk6 = 0;
    player_enter_fall_shooting(&g_Player);
    check_player_script_motion();
    return 1;
}

static u32 test_zero_landing_attack(u32 row)
{
    u32 technique = row % 2;
    prepare_player_script_motion(1, row / 2 % 2, row / 4);
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0xB, row / 4 % 9);
    g_Player.input_locked = 0;
    g_Player.unk6 = 1;
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    g_Player.boss_flags = technique ? 1 : 0;
    g_Player.pressed_input = technique ? PLAYER_INPUT_SPECIAL : PLAYER_INPUT_SHOOT;
    capture_player_script_motion();
    expect_landing();
    expect_animation_player_script_motion(technique ? 0x5F : 0x58, 0, 0);
    expected_player_script_motion.attacking = 1;
    expected_player_script_motion.combo = expected_player_script_motion.afterimage = 0;
    expected_player_script_motion.unk5 = technique ? PLAYER_ZERO_RAIJINGEKI : PLAYER_ZERO_SABER;
    expected_player_script_motion.unk6 = 1;
    player_script_jump(&g_Player);
    check_player_script_motion();
    return 1;
}

static void prepare_transition(u32 row, u32 state, u32 substate)
{
    u32 character = row % 2, facing = row / 2 % 2;
    prepare_player_script_motion(character, facing, row / 8 % 3);
    g_Player.unk5 = state;
    g_Player.unk6 = substate;
    g_Player.script_state = 0;
    g_Player.dash_momentum = row / 4 % 2;
    g_Player.afterimage = (s32)(row / 8 % 3) - 1;
    g_Player.attacking = row / 24;
    g_Player.input.buttons.held = PLAYER_INPUT_JUMP | PLAYER_INPUT_RIGHT;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT | PLAYER_INPUT_DASH;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0xA, 0);
}

static u32 test_locked_fall(u32 row)
{
    static void (*const callbacks[])(struct PlayerObj*) = {
        player_wall_cling,
        player_wall_jump_push,
        player_wall_slide_down,
        player_wall_slide_release,
        player_air_dash,
        player_hover,
    };
    static const u8 states[] = {
        PLAYER_WALL_CLING,
        PLAYER_WALL_JUMP,
        PLAYER_WALL_SLIDE,
        PLAYER_WALL_SLIDE,
        PLAYER_AIR_DASH,
        PLAYER_HOVER,
    };
    u32 callback = row % 6;
    prepare_transition(row / 6 * 5, states[callback], callback == 3);
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT | PLAYER_COLLIDE_RIGHT;
    capture_player_script_motion();
    expect_animation_player_script_motion(!expected_player_script_motion.unk2 && expected_player_script_motion.attacking ? 0x7B : 0xB, 0, 0);
    expected_player_script_motion.x_vel.val = expected_player_script_motion.y_vel.val = expected_player_script_motion.unk28 = 0;
    expected_player_script_motion.unk2C = 0x4200;
    expected_player_script_motion.air_state = -1;
    if (expected_player_script_motion.dash_momentum) {
        expected_player_script_motion.dash_momentum = 0;
        expected_player_script_motion.afterimage = -1;
    }
    expected_player_script_motion.unk5 = PLAYER_FALL;
    expected_player_script_motion.unk6 = 0;
    callbacks[callback](&g_Player);
    check_player_script_motion();
    return 1;
}

static u32 test_grounded_transition(u32 row)
{
    static void (*const callbacks[])(struct PlayerObj*) = {
        player_wall_cling,
        player_air_dash,
        player_air_dash_end,
    };
    static const u8 states[] = { PLAYER_WALL_CLING, PLAYER_AIR_DASH, PLAYER_AIR_DASH };
    u32 callback = row % 3;
    prepare_transition(row, states[callback], callback == 2 ? 2 : 0);
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND | PLAYER_COLLIDE_LEFT;
    capture_player_script_motion();
    expected_player_script_motion.air_state = expected_player_script_motion.air_action = expected_player_script_motion.dash_momentum = 0;
    if (expected_player_script_motion.afterimage > 0)
        expected_player_script_motion.afterimage = -1;
    expect_animation_player_script_motion(!expected_player_script_motion.unk2 && expected_player_script_motion.attacking ? 0x7C : 0xC, 0, 0);
    expected_player_script_motion.unk5 = PLAYER_LAND;
    expected_player_script_motion.unk6 = 0;
    callbacks[callback](&g_Player);
    check_player_script_motion();
    return 1;
}

static u32 test_ladder_step_off(u32 row)
{
    u32 character = row % 2, facing = row / 2 % 2;
    u32 frame = row / 4 % 2, short_duration = row / 8 % 2;
    const struct AnimationReference* ref = reference(character, 0x1E);
    s32 next;
    prepare_player_script_motion(character, facing, row / 16);
    g_Player.unk5 = PLAYER_LADDER_TRANSITION;
    g_Player.unk6 = 3;
    g_Player.script_state = 0;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0x1E, frame);
    if (short_duration)
        g_Player.animation_step.fields.duration = 1;
    capture_player_script_motion();
    if (short_duration) {
        next = (s32)frame + (s8)(ref->words[frame] >> 16);
        expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[0x1E] + next;
        expected_player_script_motion.animation_step.packed = C_TEST_STEP(ref->words[next]);
    } else
        expected_player_script_motion.animation_step.fields.duration--;
    if (expected_player_script_motion.animation_step.fields.relative_step < 0) {
        expected_player_script_motion.air_state = 0;
        expect_animation_player_script_motion(character ? 9 : 5, 0, 0);
        expected_player_script_motion.unk5 = character ? PLAYER_SETTLE : PLAYER_IDLE;
        expected_player_script_motion.unk6 = 0;
    }
    player_ladder_step_off_bottom(&g_Player);
    check_player_script_motion();
    return 1;
}

static u8 ladder_map[3 * 256];
static u16 ladder_tiles[2][16][16];
static u32 ladder_attributes[1] = { C_TEST_PSX_WORD(0x20) };

static u32 test_ladder_navigation(u32 row)
{
    u32 entry = row % 18, character = entry >= 8;
    u32 frame = character ? entry - 8 : entry;
    static const u8 inputs[3][2] = { { 0, 0 }, { 3, 1 }, { 0, 2 } };
    u32 down = row / 18 % 2, press = inputs[row / 36][0], held = inputs[row / 36][1];
    u32 facing = (entry + press) % 2;
    u32 animation = down ? 0x20 : 0x1F;
    u32 duration, target, i;
    s32 next;
    const struct AnimationReference* ref = reference(character, animation);
    prepare_player_script_motion(character, facing, row % 3);
    c_test_zero_words((u32*)ladder_tiles, sizeof(ladder_tiles) / 4);
    for (i = 0; i < COUNT(ladder_map); i++)
        ladder_map[i] = 1;
    SP_BG_TILEMAP = ladder_map;
    TEST_BG_TILE_PIXELS = (u8*)ladder_tiles;
    TEST_BG_TILE_ATTRS = (u8*)ladder_attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    g_Player.x_pos.val = (104 + row % 3 * 16) * 65536;
    g_Player.y_pos.val = 120 * 65536 + (row % 2 ? 0x8000 : 0);
    g_Player.x_vel.val = g_Player.unk28 = g_Player.unk2C = 0;
    g_Player.y_vel.val = down ? -0x18000 : 0x18000;
    g_Player.unk5 = down ? PLAYER_LADDER_DOWN : PLAYER_LADDER_UP;
    g_Player.unk6 = 0;
    g_Player.script_state = 0;
    g_Player.input_locked = 0;
    g_Player.shot_cooldown = 1;
    g_Player.pressed_input = (press & 1 ? PLAYER_INPUT_LEFT : 0) | (press & 2 ? PLAYER_INPUT_RIGHT : 0);
    g_Player.input.buttons.held = held == 0 ? 0 : (held == 1) != down ? PLAYER_INPUT_UP
                                                                      : PLAYER_INPUT_DOWN;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), animation, frame);
    if ((press + facing + down) % 2)
        g_Player.animation_step.fields.duration = 1;
    capture_player_script_motion();
    if (press & 1)
        expected_player_script_motion.unk15 = 0;
    if (press & 2)
        expected_player_script_motion.unk15 = PLAYER_FACING_RIGHT;
    duration = expected_player_script_motion.animation_step.fields.duration;
    if (held == 1) {
        if (duration == 1) {
            next = (s32)frame + (s8)(ref->words[frame] >> 16);
            expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[animation] + next;
            expected_player_script_motion.animation_step.packed = C_TEST_STEP(ref->words[next]);
        } else
            expected_player_script_motion.animation_step.fields.duration--;
        expected_player_script_motion.y_pos.val += down ? 0x18000 : -0x18000;
    } else if (held == 2) {
        target = (ref->words[frame] >> 8) & 255;
        expect_animation_player_script_motion(down ? 0x1F : 0x20, target, 1);
        expected_player_script_motion.animation_step.fields.duration = duration;
        expected_player_script_motion.y_pos.u.lo = 0;
        expected_player_script_motion.y_vel.val = down ? 0x18000 : -0x18000;
        expected_player_script_motion.dash_momentum = expected_player_script_motion.air_action = 0;
        if (expected_player_script_motion.afterimage > 0)
            expected_player_script_motion.afterimage = -1;
        expected_player_script_motion.unk5 = down ? PLAYER_LADDER_UP : PLAYER_LADDER_DOWN;
    }
    if (down)
        player_ladder_down(&g_Player);
    else
        player_ladder_up(&g_Player);
    check_player_script_motion();
    assert(SP_BG_TILEMAP == ladder_map && TEST_BG_TILE_PIXELS == (u8*)ladder_tiles);
    assert(TEST_BG_TILE_ATTRS == (u8*)ladder_attributes && ladder_attributes[0] == C_TEST_PSX_WORD(0x20));
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
    for (i = 0; i < COUNT(ladder_map); i++)
        assert(ladder_map[i] == 1);
    for (i = 0; i < sizeof(ladder_tiles) / 4; i++)
        assert(((u32*)ladder_tiles)[i] == 0);
    return 1;
}

enum { P_BEAM_OUT, P_CLIMB_OFF, P_CLIMB_ON, P_LET_GO, P_STUN, P_SLIDE, P_CAPSULE, P_SCRIPT_WAIT, P_SCRIPT_WALK,
    P_VANISH, P_RIDE, P_IDLE, P_WALK };
static void (*const player_handler_fns[])(struct PlayerObj*) = {
    player_beam_out, player_ladder_climb_off_top, player_ladder_climb_on_top, player_ladder_let_go, player_hurt_stun,
    player_hurt_slide, player_capsule, player_script_wait, func_80033108, player_script_vanish, player_ride,
    player_idle, player_walk,
};
#define PLAYER_STEP(event, relative) C_TEST_STEP(5 | (event) << 8 | (u8)(relative) << 16)
#define P_KEEP 0xFF
static const struct {
    u8 fn, unk6, coll, right, capsule, unkF, script_facing, ride, ride_animation, offscreen, hurt, event, relative;
    u16 held;
    s8 stun, air, script;
    s32 vx, vy;
    u8 e5, e6, e_state, hidden, e_anim, e_dur, e_facing;
    s8 e_stun, e_air;
    u32 e_x, e_y, e_vx, e_vy;
} player_handler_rows[] = {
    { .fn = P_BEAM_OUT, .relative = 0, .e5 = 0x3F, .e6 = 1, .e_anim = 4, .e_dur = P_KEEP },
    { .fn = P_BEAM_OUT, .relative = 1, .e5 = 0x3F, .e_dur = 4 },
    { .fn = P_BEAM_OUT, .unk6 = 1, .relative = 1, .vx = 0x10000, .e5 = 0x3F, .e6 = 1, .e_dur = 4, .e_x = 0x650000, .e_vx = 0x10000 },
    { .fn = P_BEAM_OUT, .unk6 = 1, .relative = 1, .offscreen = 1, .e5 = 0, .e6 = 0, .e_state = PLAYER_STATE_INACTIVE, .hidden = 1, .e_dur = 4, .e_x = 0x4000000 },
    { .fn = P_CLIMB_OFF, .unk6 = 1, .event = 0x80, .relative = 1, .e5 = 0x3F, .e6 = 1, .e_dur = 4, .e_y = 0xB80000 },
    { .fn = P_CLIMB_OFF, .unk6 = 1, .relative = -1, .air = 1, .e5 = PLAYER_SETTLE, .e6 = 0, .e_anim = 9, .e_dur = P_KEEP, .e_air = 0 },
    { .fn = P_CLIMB_ON, .unk6 = 2, .event = 0x80, .relative = 1, .e5 = 0x3F, .e6 = 2, .e_dur = 4, .e_y = 0xE00000 },
    { .fn = P_CLIMB_ON, .unk6 = 2, .relative = -1, .e5 = PLAYER_LADDER_DOWN, .e6 = 0, .e_anim = 0x20, .e_dur = P_KEEP, .e_x = 0x680000, .e_y = 0xD80000, .e_vy = 0xFFFE8000 },
    { .fn = P_LET_GO, .unk6 = 4, .relative = -1, .e5 = PLAYER_FALL, .e6 = 0, .e_anim = 0xB, .e_dur = P_KEEP, .e_air = -1 },
    { .fn = P_LET_GO, .unk6 = 4, .relative = 1, .e5 = 0x3F, .e6 = 4, .e_dur = 4 },
    { .fn = P_STUN, .held = PLAYER_INPUT_LEFT, .right = 1, .stun = 5, .relative = 1, .e5 = 0x3F, .e_dur = 5, .e_stun = 5 },
    { .fn = P_STUN, .held = PLAYER_INPUT_RIGHT, .coll = PLAYER_COLLIDE_GROUND, .hurt = 1, .relative = 1, .e5 = PLAYER_IDLE, .e_anim = P_KEEP, .e_dur = P_KEEP, .e_facing = 1 },
    { .fn = P_STUN, .stun = -1, .relative = 1, .e5 = 0x3F, .e_anim = 0x25, .e_dur = P_KEEP, .e_stun = -2 },
    { .fn = P_STUN, .stun = -2, .relative = -1, .e5 = 0x3F, .e_anim = 0x24, .e_dur = P_KEEP, .e_stun = 1 },
    { .fn = P_STUN, .stun = -2, .relative = 1, .e5 = 0x3F, .e_dur = 5, .e_stun = -2 },
    { .fn = P_SLIDE, .right = 1, .vx = 0x10000, .relative = 1, .e5 = 0x3F, .e_dur = 5, .e_facing = 1, .e_x = 0x650000 },
    { .fn = P_SLIDE, .right = 1, .vx = -0x10000, .relative = 1, .e5 = 0x3F, .e_dur = 5, .e_facing = 1, .e_x = 0x630000, .e_vx = 0xFFFF0000 },
    { .fn = P_SLIDE, .vx = 0x10000, .coll = PLAYER_COLLIDE_RIGHT, .relative = 1, .e5 = 0x3F, .e_dur = 5 },
    { .fn = P_CAPSULE, .coll = PLAYER_COLLIDE_GROUND, .relative = 1, .e5 = PLAYER_SETTLE, .e6 = 0, .e_anim = 9, .e_dur = P_KEEP },
    { .fn = P_CAPSULE, .relative = 1, .e5 = 0x3F, .e6 = 1, .e_anim = 0xB, .e_dur = P_KEEP, .e_air = -1 },
    { .fn = P_CAPSULE, .capsule = 1, .relative = 1, .e5 = 0x3F, .e_dur = 4 },
    { .fn = P_CAPSULE, .capsule = 1, .air = 1, .relative = 1, .e5 = 0x3F, .e_dur = 5, .e_air = 1 },
    { .fn = P_CAPSULE, .unk6 = 1, .coll = PLAYER_COLLIDE_GROUND, .relative = 1, .e5 = PLAYER_LAND, .e6 = 0, .e_anim = 0xC, .e_dur = P_KEEP },
    { .fn = P_CAPSULE, .unk6 = 1, .vy = 0x10000, .relative = 1, .e5 = 0x3F, .e6 = 1, .e_dur = 4, .e_y = 0xC70000, .e_vy = 0x10000 },
    { .fn = P_SCRIPT_WAIT, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
    { .fn = P_SCRIPT_WAIT, .relative = 1, .e5 = PLAYER_IDLE, .e_dur = 5 },
    { .fn = P_SCRIPT_WAIT, .script = -1, .relative = 1, .e5 = 0x3F, .e_dur = 4 },
    { .fn = P_SCRIPT_WALK, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
    { .fn = P_SCRIPT_WALK, .script_facing = 1, .relative = 1, .e5 = 0x3F, .e_dur = 4, .e_x = 0x638000, .e_vx = 0xFFFF8000 },
    { .fn = P_SCRIPT_WALK, .script_facing = 1, .right = 1, .event = 1, .relative = 1, .e5 = 0x3F, .e_dur = 4, .e_facing = 1, .e_x = 0x660000, .e_vx = 0x20000 },
    { .fn = P_SCRIPT_WALK, .right = 1, .relative = 1, .e5 = 0x3F, .e_dur = 4, .e_x = 0x648000, .e_vx = 0x8000 },
    { .fn = P_VANISH, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
    { .fn = P_VANISH, .unk6 = 1, .relative = 0, .e5 = 0x3F, .e6 = 1, .e_dur = 5 },
    { .fn = P_VANISH, .relative = 0, .e5 = 0x3F, .e6 = 1, .hidden = 1, .e_dur = 4 },
    { .fn = P_VANISH, .relative = 1, .e5 = 0x3F, .e_dur = 4 },
    { .fn = P_RIDE, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
    { .fn = P_RIDE, .relative = 1, .e5 = PLAYER_JUMP, .e_anim = 0xA, .e_dur = P_KEEP, .e_air = 1, .e_y = 0xC23000, .e_vy = 0x58E00 },
    { .fn = P_RIDE, .ride = 1, .ride_animation = 0x2A, .relative = 1, .e5 = 0x3F, .e6 = 1, .e_anim = 0x2A, .e_dur = P_KEEP },
    { .fn = P_IDLE, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
    { .fn = P_WALK, .unkF = 0x40, .relative = 1, .e5 = 0, .e_state = PLAYER_STATE_INACTIVE, .e_anim = P_KEEP, .e_dur = P_KEEP },
};

static u32 test_player_handlers(u32 row)
{
    u8 e_state, e_screen;
    player_reset(0x3F, player_handler_rows[row].unk6, 0);
    pl.on_screen = 1;
    pl.animation_step.packed = PLAYER_STEP(player_handler_rows[row].event, player_handler_rows[row].relative);
    pl.unk88.bytes.collision_flags = player_handler_rows[row].coll;
    pl.input.buttons.held = player_handler_rows[row].held;
    pl.unk15 = player_handler_rows[row].right ? PLAYER_FACING_RIGHT : 0;
    pl.capsule_state = player_handler_rows[row].capsule;
    pl.stun_timer = player_handler_rows[row].stun;
    pl.air_state = player_handler_rows[row].air;
    pl.script_state = player_handler_rows[row].script;
    pl.script_facing = player_handler_rows[row].script_facing;
    pl.ride_state = player_handler_rows[row].ride;
    pl.ride_animation = player_handler_rows[row].ride_animation;
    pl.hurt_phase = player_handler_rows[row].hurt;
    pl.x_vel.val = player_handler_rows[row].vx;
    pl.y_vel.val = player_handler_rows[row].vy;
    if (player_handler_rows[row].offscreen)
        pl.x_pos.i.hi = 0x400;
    engine_obj.unkF = player_handler_rows[row].unkF;
    player_handler_fns[player_handler_rows[row].fn](&pl);
    e_state = player_handler_rows[row].e_state ? player_handler_rows[row].e_state : PLAYER_STATE_NORMAL;
    e_screen = !player_handler_rows[row].hidden;
    assert(pl.unk5 == player_handler_rows[row].e5 && pl.unk6 == player_handler_rows[row].e6);
    assert(pl.state == e_state && pl.on_screen == e_screen);
    if (player_handler_rows[row].e_anim != P_KEEP)
        assert(pl.unk17 == player_handler_rows[row].e_anim);
    if (player_handler_rows[row].e_dur != P_KEEP)
        assert(pl.animation_step.fields.duration == player_handler_rows[row].e_dur);
    assert(C_TEST_PSX_FACING(pl.unk15) == (player_handler_rows[row].e_facing ? 0x40 : 0));
    assert(pl.stun_timer == player_handler_rows[row].e_stun && pl.air_state == player_handler_rows[row].e_air);
    assert((u32)pl.x_pos.val == (player_handler_rows[row].e_x ? player_handler_rows[row].e_x : 0x640000));
    assert((u32)pl.y_pos.val == (player_handler_rows[row].e_y ? player_handler_rows[row].e_y : 0xC80000));
    assert((u32)pl.x_vel.val == player_handler_rows[row].e_vx && (u32)pl.y_vel.val == player_handler_rows[row].e_vy);
    assert(engine_obj.gameplay_locked == (player_handler_rows[row].unkF != 0));
    return 1;
}

static u8 script_sound_rows[0x40];
static u32 script_actions(u32 row)
{
    static const u8 actions[] = { 0x14, 0x15, 0x15, 0x16, 0x18 };
    player_reset(2, 3, 0);
    pl.unk2 = 0;
#ifndef MMX4_SATURN
    D_80141F50[1] = script_sound_rows;
#endif
    pl.animation_table = (u32**)D_80119DF0;
    pl.script_action = actions[row];
    pl.script_facing = row == 1 ? 0 : PLAYER_FACING_RIGHT;
    pl.script_state = 1;
    pl.unk17 = 5;
    pl.unk15 = 0;
    pl.y_vel.val = 0x12345;
    pl.weapon = 0;
    pl.stock_charge = 1;
    func_80034E2C(&pl);
    assert(pl.unk5 == actions[row] && pl.unk6 == 0);
    assert(pl.unk15 == (row == 1 ? (pl.x_pos.i.hi > 0x40 ? 0 : PLAYER_FACING_RIGHT) : PLAYER_FACING_RIGHT));
    if (row == 0 || row == 3)
        assert(pl.script_state == -1);
    if (row == 0)
        assert(pl.unk17 == 5);
    if (row == 1 || row == 2)
        assert(pl.y_vel.val == 0);
    if (row == 4)
        assert(pl.stock_charge == 0);
    return (u8)pl.unk15;
}


#include "support/sound_probe.h"
void player_hover_rise(struct PlayerObj*);
void player_hover_hold(struct PlayerObj*);
void player_hover_forward(struct PlayerObj*);
void player_hover_forward_stop(struct PlayerObj*);
void player_hover_back(struct PlayerObj*);
void player_rising_fire_charged_peak(struct PlayerObj*);
void player_dash_move(struct PlayerObj*);
void player_dash_end(struct PlayerObj*);
void player_air_dash_move(struct PlayerObj*);
void player_air_dash_end(struct PlayerObj*);
void player_hurt_launch(struct PlayerObj*);
s32 player_set_charge_flash(struct PlayerObj*, s8);
void player_enter_stand(struct PlayerObj*);
void player_enter_land(struct PlayerObj*);
void player_enter_dash(struct PlayerObj*);
u8 get_random();
static u16 branch_palettes[0x50][16];

enum { B_DEAD, B_VOICE, B_IDLE_LADDER, B_WALK_START_LADDER, B_WALK_START_JUMP, B_WALK_START_SABER,
    B_WALK_LADDER, B_SETTLE_WALK, B_JUMP_LOCKED, B_JUMP_CEILING, B_JUMP_LADDER,
    B_FALL_LADDER, B_FALL_WALL_JUMP, B_CLING_FREE, B_CLING_JUMP, B_CLING_TURN, B_WJ_LOCKED, B_WJ_RISE,
    B_WJ_CEILING, B_WJ_BACK_WALL, B_WJ_PUSH_END, B_WJ_RISE_CEILING, B_WS_GROUND, B_WS_SLASH, B_WS_FREE,
    B_WS_PUSH, B_WS_LET_GO, B_WSR_GROUND, B_WSR_SLASH, B_WSR_END, B_WSR_FALLING, B_DASH_START_JUMP,
    B_DASH_MOVE_JUMP, B_DASH_MOVE_WALL, B_DASH_MOVE_WALL_RIGHT, B_DASH_END_DONE, B_AIR_DASH_SHOOTING,
    B_AIR_DASH_DUST, B_AIR_DASH_END_STEER,
    B_KNOCK_LOCKED, B_LAUNCH_LAND_RIGHT, B_LAUNCH_IDLE, B_LAUNCH_SPIN,
    B_LAUNCH_LOCKED, B_CLEAR_WAIT, B_CLEAR_POSE,
    B_CLEAR_SOUND, B_CLEAR_END, B_ENTER_IDLE_EARLY, B_ENTER_IDLE_LATE, B_ENTER_STAND_SCRIPT,
    B_JUMP_DASH_HELD, B_ENTER_LAND_SCRIPT, B_ENTER_DASH_JUMP, B_SLIDE_WALL_JUMP, B_CLEAR_X, B_IDLE_SHOT_ENDED,
    B_IDLE_LOW_HP, B_IDLE_HIGH_HP, B_RISING_END, B_RAIJINGEKI_BUSY, B_HYOURETSUZAN_NO_SPECIAL, B_RYUENJIN_BUSY,
    B_WALL_SLASH_JUMP, B_WALL_SLASH_AGAIN, B_RELEASE_FLASH, B_FLASH_PARTIAL, B_FRAME_ENDED, B_FRAME_ATTACK,
    B_AIR_DASH_X, B_KNOCK_END,
#ifndef VERSION_DEMO
    B_BEAM_IN_EVENT, B_JUMP_DOUBLE, B_KNOCK_FLASH, B_KNOCK_PALETTE, B_JUMP_NOVA, B_FALL_NOVA, B_WS_NOVA, B_VICTORY_WAIT, B_VICTORY_POSE, B_VICTORY_SOUND, B_VICTORY_END,
    B_AIR_DASH_MOVE_WALL, B_AIR_DASH_MOVE_DUST, B_AIR_DASH_MOVE_ON, B_LADDER_SHOOT_OFF, B_LADDER_SHOOT_END,
    B_HOVER_RISE_END, B_HOVER_RISE_WALL, B_HOVER_HOLD_END, B_HOVER_HOLD_WALL, B_HOVER_HOLD_TURN, B_HOVER_HOLD_BLOCKED,
    B_HOVER_FWD_END, B_HOVER_FWD_WALL, B_HOVER_FWD_BACK, B_HOVER_FSTOP_END, B_HOVER_FSTOP_TURN, B_HOVER_BACK_END,
    B_HOVER_BACK_WALL, B_HOVER_BACK_FWD, B_HOVER_BACK_ON, B_HOVER_BACK_STOP, B_POSE_SPLIT, B_POSE_END,
    B_PEAK_RISING, B_PEAK_FALLING, B_BUSTER_VOICE, B_FLASH_FULL_14, B_FLASH_FULL_OTHER, B_RELEASE_SPECIAL,
    B_RELEASE_SPECIAL_UP, B_HOLD_SPECIAL, B_RELEASE_SPECIAL_TIMER, B_SPECIAL_ARM_2,
#endif
    B_COUNT };
static void branch_x(void)
{
    pl.unk2 = 0;
    pl.animation_table = (u32**)D_80119DF0;
}
static void branch_nova(void)
{
    branch_x();
    pl.armor_parts = 2;
    pl.weapon_energy[0] = 0x30;
    pl.pressed_input = PLAYER_INPUT_GIGA;
}
static void branch_hover(u8 phase)
{
    player_reset(PLAYER_HOVER, phase, 0);
    branch_x();
    pl.hover_timer = 10;
    pl.unk15 = PLAYER_FACING_RIGHT;
}
static u32 state_branch(u32 row)
{
    s32 sound = -2, result;
    u8 state = PLAYER_IDLE;
    player_reset(PLAYER_IDLE, 0, 0);
    player_attrs[0] = 0;
    pl.animation_step.packed = PLAYER_STEP(0, 1);
    pl.hp = 16;
    engine_obj.max_hp = 16;
#ifndef MMX4_SATURN
    D_80141F50[1] = script_sound_rows;
#endif
    switch (row) {
    case B_DEAD:
        pl.unk70 = PLAYER_COLLIDE_CEILING | PLAYER_COLLIDE_GROUND;
        pl.voice_timer = 2;
        player_update_normal(&pl);
        assert(pl.state == PLAYER_STATE_DEATH && pl.hp == 0 && pl.voice_timer == 2);
        state = 0;
        break;
    case B_VOICE:
        pl.unk70 = PLAYER_COLLIDE_GROUND;
        pl.voice_timer = 2;
        player_update_normal(&pl);
        assert(pl.voice_timer == 1);
        break;
#ifndef VERSION_DEMO
    case B_BEAM_IN_EVENT:
        pl.unk5 = state = PLAYER_BEAM_IN;
        pl.unk6 = 1;
        pl.animation_step.packed = PLAYER_STEP(1, 1);
        engine_obj.armor_parts = 5;
        engine_obj.arm_type = 2;
        player_beam_in(&pl);
        assert(pl.armor_parts == 5 && pl.arm_type == 2 && pl.animation_step.fields.event == 0);
        break;
#endif
    case B_IDLE_LADDER:
    case B_WALK_START_LADDER:
    case B_WALK_LADDER:
        player_attrs[0] = C_TEST_PSX_WORD(0x20);
        pl.input.buttons.held = PLAYER_INPUT_UP;
        if (row == B_IDLE_LADDER)
            player_idle(&pl);
        else if (row == B_WALK_LADDER)
            player_walk(&pl);
        else
            player_walk_start(&pl);
        state = PLAYER_LADDER_TRANSITION;
        break;
    case B_WALK_START_JUMP:
        pl.pressed_input = PLAYER_INPUT_JUMP;
        player_walk_start(&pl);
        state = PLAYER_JUMP;
        break;
    case B_WALK_START_SABER:
        pl.pressed_input = PLAYER_INPUT_SHOOT;
        player_walk_start(&pl);
        state = PLAYER_ZERO_SABER;
        break;
    case B_SETTLE_WALK:
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        player_settle(&pl);
        state = PLAYER_WALK_START;
        break;
    case B_JUMP_LOCKED:
    case B_JUMP_CEILING:
        pl.input_locked = row == B_JUMP_LOCKED;
        pl.unk88.bytes.collision_flags = row == B_JUMP_CEILING ? PLAYER_COLLIDE_CEILING : 0;
        pl.input.buttons.held = PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x30000;
        player_jump(&pl);
        state = PLAYER_FALL;
        break;
#ifndef VERSION_DEMO
    case B_JUMP_NOVA:
    case B_FALL_NOVA:
        branch_nova();
        pl.input.buttons.held = PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x30000;
        if (row == B_JUMP_NOVA)
            player_jump(&pl);
        else
            player_fall(&pl);
        state = PLAYER_NOVA_STRIKE;
        break;
#endif
    case B_JUMP_LADDER:
    case B_FALL_LADDER:
        player_attrs[0] = C_TEST_PSX_WORD(0x20);
        pl.input.buttons.held = PLAYER_INPUT_UP | PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x30000;
        if (row == B_JUMP_LADDER)
            player_jump(&pl);
        else
            player_fall(&pl);
        state = PLAYER_LADDER_UP;
        break;
#ifndef VERSION_DEMO
    case B_JUMP_DOUBLE:
        pl.boss_flags = 4;
        pl.pressed_input = pl.input.buttons.held = PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x10000;
        player_jump(&pl);
        assert(pl.air_action == 6 && pl.y_vel.val == FIXED(5.8125) - 0x4200);
        state = PLAYER_JUMP;
        break;
#endif
    case B_FALL_WALL_JUMP:
    case B_CLING_JUMP:
    case B_SLIDE_WALL_JUMP:
        pl.unk88.bytes.collision_flags = row == B_SLIDE_WALL_JUMP ? PLAYER_COLLIDE_LEFT : PLAYER_COLLIDE_RIGHT;
        pl.pressed_input = PLAYER_INPUT_JUMP;
        pl.input.buttons.held = row == B_CLING_JUMP ? 0 : PLAYER_INPUT_DASH;
        pl.wall_climbable = 1;
        if (row == B_FALL_WALL_JUMP)
            player_fall(&pl);
        else if (row == B_CLING_JUMP)
            player_wall_cling(&pl);
        else {
            pl.unk5 = PLAYER_WALL_SLIDE;
            player_wall_slide(&pl);
        }
        assert(pl.x_vel.val == (row == B_SLIDE_WALL_JUMP ? FIXED(4.125) : row == B_CLING_JUMP ? FIXED(-2) : FIXED(-4.125)));
        assert(pl.dash_momentum == (row != B_CLING_JUMP));
        state = PLAYER_WALL_JUMP;
        break;
    case B_CLING_FREE:
        player_wall_cling(&pl);
        state = PLAYER_FALL;
        break;
    case B_CLING_TURN:
        pl.unk5 = state = PLAYER_WALL_CLING;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT;
        pl.animation_step.packed = PLAYER_STEP(0x80, 1);
        pl.unk8A.bytes.low = 5;
        player_wall_cling(&pl);
        assert(pl.unk15 == PLAYER_FACING_RIGHT && pl.unk8A.bytes.low == 4);
        break;
    case B_WJ_LOCKED:
        pl.unk5 = PLAYER_WALL_JUMP;
        pl.input_locked = 1;
        player_wall_jump(&pl);
        state = PLAYER_FALL;
        break;
    case B_WJ_RISE:
        pl.unk5 = state = PLAYER_WALL_JUMP;
        pl.unk6 = 1;
        pl.input.buttons.held = PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x30000;
        player_wall_jump(&pl);
        assert(pl.unk6 == 1 && pl.y_vel.val == 0x30000);
        break;
    case B_WJ_CEILING:
    case B_WJ_BACK_WALL:
        pl.unk15 = PLAYER_FACING_RIGHT;
        pl.unk88.bytes.collision_flags = row == B_WJ_CEILING ? PLAYER_COLLIDE_CEILING : PLAYER_COLLIDE_LEFT;
        player_wall_jump(&pl);
        state = PLAYER_FALL;
        break;
    case B_WJ_PUSH_END:
        pl.unk5 = state = PLAYER_WALL_JUMP;
        pl.unk15 = PLAYER_FACING_RIGHT;
        pl.unk8A.bytes.low = 1;
        pl.x_vel.val = FIXED(2);
        player_wall_jump(&pl);
        assert(pl.unk6 == 1 && pl.x_vel.val == 0);
        break;
    case B_WJ_RISE_CEILING:
        pl.unk6 = 1;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_CEILING;
        pl.input.buttons.held = PLAYER_INPUT_JUMP;
        pl.y_vel.val = 0x30000;
        player_wall_jump(&pl);
        state = PLAYER_FALL;
        break;
    case B_WS_GROUND:
    case B_WSR_GROUND:
        pl.unk5 = PLAYER_WALL_SLIDE;
        pl.unk6 = row == B_WSR_GROUND;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
        player_wall_slide(&pl);
        state = PLAYER_LAND;
        break;
#ifndef VERSION_DEMO
    case B_WS_NOVA:
        branch_nova();
        pl.unk5 = PLAYER_WALL_SLIDE;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        player_wall_slide(&pl);
        state = PLAYER_NOVA_STRIKE;
        break;
#endif
    case B_WS_SLASH:
        pl.unk5 = PLAYER_WALL_SLIDE;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.pressed_input = PLAYER_INPUT_SHOOT;
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        pl.wall_climbable = 1;
        player_wall_slide(&pl);
        state = PLAYER_ZERO_WALL_SLASH;
        break;
    case B_WS_FREE:
        pl.unk5 = PLAYER_WALL_SLIDE;
        player_wall_slide(&pl);
        state = DEMO_ALT(PLAYER_FALL, PLAYER_WALL_SLIDE);
        assert(pl.unk6 == DEMO_ALT(0, 1));
        break;
    case B_WS_PUSH:
    case B_WS_LET_GO:
        pl.unk5 = state = PLAYER_WALL_SLIDE;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.input.buttons.held = row == B_WS_PUSH ? PLAYER_INPUT_RIGHT : 0;
        pl.wall_climbable = 1;
        pl.y_vel.val = -0x20000;
        player_wall_slide(&pl);
        if (row == B_WS_LET_GO) {
            assert(pl.unk6 == 1 && pl.x_vel.val == FIXED(-2) && pl.unk8A.bytes.low == 4);
        } else
            assert(pl.unk6 == 0 && pl.y_pos.i.hi != 200);
        break;
    case B_WSR_SLASH:
        pl.unk5 = PLAYER_WALL_SLIDE;
        pl.unk6 = 1;
        pl.pressed_input = PLAYER_INPUT_SHOOT;
        player_wall_slide(&pl);
        state = PLAYER_ZERO_FALL_SLASH;
        break;
    case B_WSR_END:
    case B_WSR_FALLING:
        pl.unk5 = PLAYER_WALL_SLIDE;
        pl.unk6 = 1;
        pl.unk8A.bytes.low = row == B_WSR_END ? 1 : 5;
        pl.x_vel.val = FIXED(-2);
        player_wall_slide(&pl);
        state = row == B_WSR_END ? PLAYER_FALL : PLAYER_WALL_SLIDE;
        assert(pl.x_vel.val == (row == B_WSR_END ? 0 : FIXED(-2)) && pl.unk6 == (row == B_WSR_END ? 0 : 1));
        break;
    case B_DASH_START_JUMP:
    case B_DASH_MOVE_JUMP:
        pl.unk5 = PLAYER_DASH;
        pl.pressed_input = PLAYER_INPUT_JUMP;
        if (row == B_DASH_START_JUMP)
            player_dash_start(&pl);
        else
            player_dash_move(&pl);
        state = PLAYER_JUMP;
        break;
    case B_DASH_MOVE_WALL:
    case B_DASH_MOVE_WALL_RIGHT:
        pl.unk5 = state = PLAYER_DASH;
        pl.unk6 = 1;
        pl.unk15 = row == B_DASH_MOVE_WALL_RIGHT ? PLAYER_FACING_RIGHT : 0;
        pl.unk88.bytes.collision_flags = row == B_DASH_MOVE_WALL_RIGHT ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT;
        player_dash_move(&pl);
        assert(pl.unk6 == 2 && pl.x_vel.val == (row == B_DASH_MOVE_WALL_RIGHT ? FIXED(4.125) : FIXED(-4.125)));
        break;
    case B_DASH_END_DONE:
        pl.unk5 = PLAYER_DASH;
        pl.unk6 = 2;
        pl.animation_step.packed = PLAYER_STEP(0, -1);
        player_dash_end(&pl);
        break;
    case B_AIR_DASH_SHOOTING:
        branch_x();
        pl.unk5 = PLAYER_AIR_DASH;
        pl.attacking = 1;
        player_air_dash(&pl);
        state = PLAYER_FALL;
        break;
    case B_AIR_DASH_DUST:
#ifndef VERSION_DEMO
    case B_AIR_DASH_MOVE_DUST:
    case B_AIR_DASH_MOVE_ON:
#endif
        pl.unk5 = state = PLAYER_AIR_DASH;
        pl.unk6 = row != B_AIR_DASH_DUST;
        pl.animation_step.packed = PLAYER_STEP(0x40, 1);
        pl.dash_timer = 10;
        pl.input.buttons.held = PLAYER_INPUT_DASH;
        if (row == B_AIR_DASH_DUST)
            player_air_dash_start(&pl);
#ifndef VERSION_DEMO
        else {
            if (row == B_AIR_DASH_MOVE_ON)
                pl.animation_step.packed = PLAYER_STEP(0, 1);
            player_air_dash_move(&pl);
        }
#endif
        assert(pl.animation_step.fields.event == 0 && pl.unk6 == (row != B_AIR_DASH_DUST));
        break;
#ifndef VERSION_DEMO
    case B_AIR_DASH_MOVE_WALL:
        pl.unk5 = state = PLAYER_AIR_DASH;
        pl.unk6 = 1;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_LEFT;
        player_air_dash_move(&pl);
        assert(pl.unk6 == 2);
        break;
#endif
    case B_AIR_DASH_END_STEER:
        pl.unk5 = PLAYER_AIR_DASH;
        pl.unk6 = 2;
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        player_air_dash_end(&pl);
        state = PLAYER_FALL;
        break;
#ifndef VERSION_DEMO
    case B_KNOCK_FLASH:
    case B_KNOCK_PALETTE:
        branch_x();
        pl.unk5 = state = PLAYER_HURT;
        pl.unk17 = 0x80;
        pl.animation_step.fields.frame_index = row == B_KNOCK_FLASH ? 0xEC : 0x10;
        TEST_PALETTE_BANK = (u8*)branch_palettes;
        branch_palettes[0x49][0] = 0x4949;
        branch_palettes[0][0] = 0x1111;
        player_palettes[1] = 0;
        player_hurt_knockback(&pl);
        assert(player_palettes[1] == (row == B_KNOCK_FLASH ? 0x4949 : 0x1111));
        break;
#endif
    case B_KNOCK_END:
        pl.unk5 = PLAYER_HURT;
        pl.invincibility_timer = 0x3C;
        pl.hurt_phase = 1;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
        player_hurt_knockback(&pl);
        assert(pl.hurt_phase == -1 && pl.invincibility_timer == 0x3C);
        break;
    case B_AIR_DASH_X:
        branch_x();
        pl.unk5 = state = PLAYER_AIR_DASH;
        player_air_dash(&pl);
        assert(pl.unk6 == 0 && pl.animation_step.fields.duration == 4);
        break;
    case B_KNOCK_LOCKED:
    case B_LAUNCH_LOCKED:
        pl.unk5 = PLAYER_HURT;
        pl.unk6 = 1;
        pl.invincibility_timer = 0x3C;
        pl.hurt_phase = 1;
        pl.input_locked = 1;
        if (row == B_KNOCK_LOCKED)
            player_hurt_knockback(&pl);
        else
            player_hurt_launch(&pl);
        assert(pl.hurt_phase == 0 && pl.invincibility_timer == 0);
        state = DEMO_ALT(PLAYER_FALL, PLAYER_IDLE);
        break;
    case B_LAUNCH_LAND_RIGHT:
        pl.unk5 = state = PLAYER_HURT;
        pl.unk6 = 1;
        pl.air_state = 1;
        pl.unk15 = PLAYER_FACING_RIGHT;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
        pl.invincibility_timer = 10;
        player_hurt_launch(&pl);
        assert(pl.air_state == 0 && pl.y_vel.val == 0);
        break;
    case B_LAUNCH_IDLE:
    case B_LAUNCH_SPIN:
        pl.unk5 = PLAYER_HURT;
        pl.unk6 = 1;
        pl.invincibility_timer = 0x3C;
        pl.unk88.bytes.collision_flags = row == B_LAUNCH_IDLE ? PLAYER_COLLIDE_GROUND : 0;
        pl.unk2C = row == B_LAUNCH_SPIN ? 0x4200 : 0;
        pl.air_state = row == B_LAUNCH_SPIN;
        player_hurt_launch(&pl);
        assert(pl.hurt_phase == -1);
        if (row == B_LAUNCH_SPIN)
            assert(pl.unk17 == 0xB && pl.air_state == -1);
        state = row == B_LAUNCH_IDLE ? PLAYER_IDLE : PLAYER_FALL;
        break;
#ifndef VERSION_DEMO
    case B_VICTORY_WAIT:
    case B_VICTORY_POSE:
    case B_VICTORY_SOUND:
    case B_VICTORY_END:
        sound_probe_begin_group(0);
        pl.unk5 = state = PLAYER_SCRIPT_VICTORY;
        pl.unk6 = row >= B_VICTORY_SOUND;
        pl.item_step = row == B_VICTORY_POSE ? 4 : 0;
        pl.animation_step.packed = PLAYER_STEP(row == B_VICTORY_SOUND ? 0x80 : 0, row == B_VICTORY_END ? 0 : 1);
        player_script_victory(&pl);
        if (row == B_VICTORY_POSE)
            assert(pl.unk6 == 1 && pl.unk17 == 0x27);
        if (row == B_VICTORY_END)
            state = PLAYER_IDLE;
        sound = row == B_VICTORY_SOUND ? 0x21 : -1;
        break;
#endif
    case B_CLEAR_WAIT:
    case B_CLEAR_POSE:
    case B_CLEAR_SOUND:
    case B_CLEAR_END:
        sound_probe_begin_group(0);
        pl.unk5 = state = PLAYER_STAGE_CLEAR;
        pl.unk6 = row >= B_CLEAR_SOUND;
        D_80173C84 = row != B_CLEAR_POSE;
        pl.animation_step.packed = PLAYER_STEP(row == B_CLEAR_SOUND ? 0x80 : 0, row == B_CLEAR_END ? 0 : 1);
        player_stage_clear(&pl);
        if (row == B_CLEAR_POSE)
            assert(DEMO_ALT(pl.unk6 == 1 && pl.unk17 == 0x27, pl.unk6 == 0));
        if (row == B_CLEAR_END)
            state = PLAYER_BEAM_OUT;
        D_80173C84 = 0;
        sound = row == B_CLEAR_SOUND ? 0x21 : -1;
        break;
    case B_ENTER_IDLE_EARLY:
    case B_ENTER_IDLE_LATE:
        branch_x();
        pl.attacking = 1;
        pl.attack_pose_timer = row == B_ENTER_IDLE_EARLY ? 3 : 10;
        player_enter_idle(&pl);
        assert(pl.unk17 == PLAYER_ANIM(0x5E));
        if (row == B_ENTER_IDLE_LATE)
            assert(pl.animation_step.fields.duration == 2);
        break;
    case B_ENTER_STAND_SCRIPT:
    case B_ENTER_LAND_SCRIPT:
        engine_obj.unkF = 0x40;
        if (row == B_ENTER_STAND_SCRIPT)
            player_enter_stand(&pl);
        else
            player_enter_land(&pl);
        if (DEMO_ALT(1, row == B_ENTER_LAND_SCRIPT)) {
            assert(pl.state == PLAYER_STATE_INACTIVE && engine_obj.gameplay_locked == DEMO_ALT(1, 0));
            state = 0;
        } else
            state = PLAYER_SETTLE;
        break;
    case B_JUMP_DASH_HELD:
        pl.dash_momentum = 0;
        pl.input.buttons.held = PLAYER_INPUT_DASH;
        player_enter_jump(&pl);
        assert(pl.dash_momentum == 1 && pl.air_action == DEMO_ALT(2, 1) && pl.afterimage == 1);
        state = PLAYER_JUMP;
        break;
    case B_ENTER_DASH_JUMP:
        pl.pressed_input = PLAYER_INPUT_JUMP;
        player_enter_dash(&pl);
        assert(pl.dash_momentum == 1 && pl.air_action == DEMO_ALT(2, 1));
        state = PLAYER_JUMP;
        break;
    case B_CLEAR_X:
        branch_x();
        engine_obj.unkF = 0x10;
        player_start_stage_clear(&pl);
        assert(engine_obj.gameplay_locked == DEMO_ALT(1, 0));
        state = pl.unk5;
        break;
    case B_IDLE_SHOT_ENDED:
        branch_x();
        pl.attack_ended = 1;
        pl.unk17 = 0x80;
        player_idle_animate(&pl);
        assert(pl.unk17 != 0x80);
        break;
    case B_IDLE_LOW_HP:
    case B_IDLE_HIGH_HP:
        pl.unk17 = 6;
        pl.hp = row == B_IDLE_LOW_HP ? 5 : 6;
        engine_obj.max_hp = 18;
        player_idle_animate(&pl);
        assert(pl.unk17 == (DEMO_ALT(row == B_IDLE_LOW_HP, 1) ? 6 : 5));
        break;
#ifndef VERSION_DEMO
    case B_LADDER_SHOOT_OFF:
        pl.unk5 = PLAYER_LADDER_SHOOT;
        player_ladder_shoot(&pl);
        state = PLAYER_FALL;
        break;
    case B_LADDER_SHOOT_END:
        player_attrs[0] = C_TEST_PSX_WORD(0x20);
        pl.unk5 = PLAYER_LADDER_SHOOT;
        pl.pressed_input = PLAYER_INPUT_RIGHT;
        pl.attack_ended = 1;
        player_ladder_shoot(&pl);
        assert(pl.unk15 == PLAYER_FACING_RIGHT);
        state = PLAYER_LADDER_DOWN;
        break;
    case B_HOVER_RISE_END:
    case B_HOVER_HOLD_END:
    case B_HOVER_FWD_END:
    case B_HOVER_FSTOP_END:
    case B_HOVER_BACK_END:
        branch_hover(row == B_HOVER_RISE_END ? 1 : row == B_HOVER_HOLD_END ? 2 : row == B_HOVER_FWD_END ? 3 : row == B_HOVER_FSTOP_END ? 4 : 5);
        pl.pressed_input = PLAYER_INPUT_JUMP;
        if (row == B_HOVER_RISE_END)
            player_hover_rise(&pl);
        else if (row == B_HOVER_HOLD_END)
            player_hover_hold(&pl);
        else if (row == B_HOVER_FWD_END)
            player_hover_forward(&pl);
        else if (row == B_HOVER_FSTOP_END)
            player_hover_forward_stop(&pl);
        else
            player_hover_back(&pl);
        state = PLAYER_FALL;
        break;
    case B_HOVER_RISE_WALL:
    case B_HOVER_HOLD_WALL:
    case B_HOVER_FWD_WALL:
    case B_HOVER_BACK_WALL:
        branch_hover(row == B_HOVER_RISE_WALL ? 1 : row == B_HOVER_HOLD_WALL ? 2 : row == B_HOVER_FWD_WALL ? 3 : 5);
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        pl.wall_climbable = 1;
        if (row == B_HOVER_RISE_WALL)
            player_hover_rise(&pl);
        else if (row == B_HOVER_HOLD_WALL)
            player_hover_hold(&pl);
        else if (row == B_HOVER_FWD_WALL)
            player_hover_forward(&pl);
        else
            player_hover_back(&pl);
        state = PLAYER_WALL_CLING;
        break;
    case B_HOVER_HOLD_TURN:
    case B_HOVER_FSTOP_TURN:
    case B_HOVER_BACK_FWD:
        branch_hover(row == B_HOVER_HOLD_TURN ? 2 : row == B_HOVER_FSTOP_TURN ? 4 : 5);
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        if (row == B_HOVER_HOLD_TURN)
            player_hover_hold(&pl);
        else if (row == B_HOVER_FSTOP_TURN)
            player_hover_forward_stop(&pl);
        else
            player_hover_back(&pl);
        state = PLAYER_HOVER;
        assert(pl.unk6 == 3 && pl.x_vel.val == FIXED(2));
        break;
    case B_HOVER_HOLD_BLOCKED:
        branch_hover(2);
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        player_hover_hold(&pl);
        state = PLAYER_HOVER;
        assert(pl.unk6 == 2 && pl.x_vel.val == 0);
        break;
    case B_HOVER_FWD_BACK:
    case B_HOVER_BACK_ON:
        branch_hover(row == B_HOVER_FWD_BACK ? 3 : 5);
        pl.input.buttons.held = PLAYER_INPUT_LEFT;
        if (row == B_HOVER_FWD_BACK)
            player_hover_forward(&pl);
        else
            player_hover_back(&pl);
        state = PLAYER_HOVER;
        assert(pl.unk6 == 5 && (row == B_HOVER_BACK_ON ? pl.x_vel.val == FIXED(-2) : pl.unk17 == 0x19));
        break;
    case B_HOVER_BACK_STOP:
        branch_hover(5);
        player_hover_back(&pl);
        state = PLAYER_HOVER;
        assert(pl.unk6 == 6 && pl.unk17 == 0x1A);
        break;
    case B_POSE_SPLIT:
        branch_x();
        pl.unk5 = state = PLAYER_WEAPON_POSE;
        pl.shot_type = 7;
        pl.animation_step.packed = PLAYER_STEP(0x80, 1);
        player_weapon_pose(&pl);
        assert(pl.shot_count == 2 && pl.special_shot_count == 2);
        break;
    case B_POSE_END:
        branch_x();
        pl.unk5 = PLAYER_WEAPON_POSE;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
        pl.animation_step.packed = PLAYER_STEP(0, 0);
        player_weapon_pose(&pl);
        break;
    case B_PEAK_RISING:
    case B_PEAK_FALLING:
        branch_x();
        pl.unk5 = state = PLAYER_RISING_FIRE_CHARGED;
        pl.unk6 = 2;
        pl.y_vel.val = row == B_PEAK_RISING ? 0x20000 : -0x10000;
        player_rising_fire_charged_peak(&pl);
        assert(pl.unk6 == (row == B_PEAK_RISING ? 2 : 3) && pl.air_state == (row == B_PEAK_RISING ? 0 : -1));
        break;
#endif
    case B_RISING_END:
        branch_x();
        pl.unk5 = PLAYER_RISING_FIRE;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
        pl.animation_step.packed = PLAYER_STEP(0, 0);
        player_rising_fire(&pl);
        break;
    case B_RAIJINGEKI_BUSY:
    case B_RYUENJIN_BUSY:
        pl.boss_flags = row == B_RAIJINGEKI_BUSY ? 1 : 8;
        pl.input.buttons.held = row == B_RYUENJIN_BUSY ? PLAYER_INPUT_UP : 0;
        pl.pressed_input = PLAYER_INPUT_SPECIAL;
        pl.attacking = 1;
        player_idle(&pl);
        assert(pl.attacking == 1);
        break;
    case B_HYOURETSUZAN_NO_SPECIAL:
        pl.unk5 = state = PLAYER_FALL;
        pl.boss_flags = 2;
        pl.input.buttons.held = PLAYER_INPUT_DOWN;
        player_fall(&pl);
        assert(pl.attacking == 0);
        break;
    case B_WALL_SLASH_JUMP:
        pl.unk5 = PLAYER_ZERO_WALL_SLASH;
        pl.attacking = 1;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.pressed_input = PLAYER_INPUT_JUMP;
        pl.wall_climbable = 1;
        player_zero_wall_slash(&pl);
        assert(pl.attacking == 0);
        state = PLAYER_WALL_JUMP;
        break;
    case B_WALL_SLASH_AGAIN:
        pl.unk5 = state = PLAYER_ZERO_WALL_SLASH;
        pl.unk6 = 1;
        pl.attacking = 1;
        pl.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        pl.input.buttons.held = PLAYER_INPUT_RIGHT;
        pl.pressed_input = PLAYER_INPUT_SHOOT;
        pl.wall_climbable = 1;
        pl.animation_step.packed = PLAYER_STEP(0x40, 1);
        player_zero_wall_slash(&pl);
        assert(pl.attacking == 1 && pl.unk17 == PLAYER_ZERO_ANIM(0x5E));
        break;
#ifndef VERSION_DEMO
    case B_BUSTER_VOICE: {
        u16 seed = 0;
        branch_x();
        sound_probe_begin_group(3);
        pl.shot_type = 0x12;
        do {
            cur_random = ++seed;
            result = get_random();
        } while (!(result & 1));
        cur_random = seed;
        player_fire_charged_buster(&pl);
        sound = 8;
        break;
    }
#endif
    case B_RELEASE_FLASH:
        branch_x();
        TEST_PALETTE_BANK = (u8*)branch_palettes;
        branch_palettes[0x32][0] = 0x3232;
        player_palettes[1] = 0;
        pl.pressed_input = PLAYER_INPUT_SHOOT;
        pl.shot_palette_timer = 4;
        pl.charge_timer = 30;
        player_update_charge(&pl);
        assert(pl.charge_timer == 0 && player_palettes[1] == 0x3232);
        break;
    case B_FLASH_PARTIAL:
        branch_x();
        pl.input.buttons.held = pl.input.buttons.previous = PLAYER_INPUT_SHOOT;
        pl.charge_state[0] = PLAYER_CHARGE_PARTIAL;
        pl.charge_state[1] = PLAYER_CHARGE_FULL;
        pl.shot_types[1] = 0x13;
        pl.charge_timer = 30;
        player_update_charge(&pl);
        assert(pl.flash_palette == DEMO_ALT(0x26, 0x29));
        break;
#ifndef VERSION_DEMO
    case B_FLASH_FULL_14:
    case B_FLASH_FULL_OTHER:
        pl.charge_state[1] = PLAYER_CHARGE_FULL;
        pl.shot_types[1] = row == B_FLASH_FULL_14 ? 0x14 : 0x12;
        assert(player_set_charge_flash(&pl, 1) == 1);
        assert(pl.flash_palette == (row == B_FLASH_FULL_14 ? 0x2F : 0x29));
        break;
    case B_RELEASE_SPECIAL:
    case B_RELEASE_SPECIAL_UP:
    case B_HOLD_SPECIAL:
    case B_RELEASE_SPECIAL_TIMER:
        pl.pressed_input = row == B_RELEASE_SPECIAL ? PLAYER_INPUT_SPECIAL : 0;
        pl.input.buttons.previous = row == B_RELEASE_SPECIAL_UP ? PLAYER_INPUT_SPECIAL : 0;
        pl.input.buttons.held = row == B_HOLD_SPECIAL ? PLAYER_INPUT_SPECIAL : 0;
        pl.charge_timer = 0;
        pl.special_charge_timer = row >= B_HOLD_SPECIAL ? 5 : 0;
        assert(player_charge_released(&pl) == (row != B_HOLD_SPECIAL));
        break;
    case B_SPECIAL_ARM_2:
        branch_x();
        pl.arm_type = 2;
        pl.special_charge_timer = 0x59;
        pl.input.buttons.held = PLAYER_INPUT_SPECIAL;
        player_charge_special_button(&pl);
        assert(pl.charge_state[1] == PLAYER_CHARGE_FULL && pl.stock_charge == 0);
        break;
#endif
    case B_FRAME_ENDED:
    case B_FRAME_ATTACK:
        branch_x();
        pl.attack_ended = row == B_FRAME_ENDED;
        pl.attacking = row == B_FRAME_ATTACK;
        pl.unk17 = row == B_FRAME_ENDED ? 0xA + PLAYER_ATTACK_ANIM_OFFSET : 0xA;
        func_80038568(&pl, 0xA);
        assert(pl.unk17 == (row == B_FRAME_ENDED ? 0xA : 0xA + PLAYER_ATTACK_ANIM_OFFSET));
        break;
    }
    assert(pl.unk5 == state);
    if (sound != -2)
        SOUND_CHECK(sound_probe_id() == sound);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "player_hurt_slide", 0, 0, 1, test_player_hurt_slide },
    { "dash_braking", 0, 0, COUNT(dash_braking), test_dash_braking },
    { "dash_cancels", 0, 0, COUNT(dash_cancels), test_dash_cancels },
#ifndef VERSION_DEMO
    { "dash_nova_strike", 0, 0, 2, test_dash_nova_strike },
#endif
    { "ladder_floor_lifecycle", 0, 0, 72, test_ladder_floor_lifecycle },
    { "ladder_slash_entry", 0, 0, 30, test_ladder_slash_entry },
    { "ride_script", 0, 0, 36, test_ride_script },
    { "script_interrupt", 0, 0, 108, test_script_interrupt },
    { "ladder_navigation", 0, 0, 108, test_ladder_navigation },
    { "locked_fall", 0, 0, 12, test_locked_fall },
    { "grounded_transition", 0, 0, 48, test_grounded_transition },
    { "ladder_step_off", 0, 0, 6, test_ladder_step_off },
    { "script_jump", 0, 0, 32, test_script_jump },
    { "animation_frames", 0, 0, 101, test_animation_frames },
    { "fall_shooting", 0, 0, 2, test_fall_shooting },
    { "zero_landing_attack", 0, 0, 2, test_zero_landing_attack },
    { "player_handlers", 0, 0, COUNT(player_handler_rows), test_player_handlers },
    { "script_actions", 0, 0, 5, script_actions },
    { "state_branches", 0, 0, B_COUNT, state_branch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(dash_braking) + COUNT(dash_cancels) + DEMO_ALT(2, 0) + 72 + 30 + 36 + 108 + 108 + 12 + 48 + 6 + 32 + 101 + 2 + 2 + COUNT(player_handler_rows) + 5 + B_COUNT;
