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
    player_attrs[0] = dash_cancels[row].ladder ? 0x20 : 0;
    player_dash_end(&pl);
    assert(pl.unk5 == dash_cancels[row].expected_step);
    assert(pl.unk6 != 2);
    return (u8)pl.unk5;
}

static u32 test_dash_nova_strike(u32 row)
{
    static u8 sound_commands[32];
    player_reset(PLAYER_DASH, 2, 0x11);
    D_80141F50[1] = sound_commands;
    pl.unk2 = 0;
    pl.animation_table = (u32**)D_80119DF0;
    pl.unk15 = row ? 0x40 : 0;
    pl.armor_parts = 2;
    pl.weapon_energy[0] = 0x30;
    pl.pressed_input = PLAYER_INPUT_GIGA;
    player_dash_end(&pl);
    assert(pl.unk5 == PLAYER_NOVA_STRIKE && pl.unk6 == 0);
    assert(pl.nova_strike_active == 1 && pl.nova_strike_timer == 0x18);
    assert(pl.weapon_energy[0] == 0 && pl.spike_immune == 1);
    assert(pl.air_action == 5 && pl.air_state == 1 && engine_obj.gameplay_locked == 1);
    assert(pl.x_vel.val == (row ? FIXED(2.5) : FIXED(-2.5)));
    assert(pl.y_vel.val == FIXED(3.5));
    return (u8)pl.unk5;
}

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
    attributes[0] = 0x20;
    attributes[1] = 0x38;
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
    g_Player.unk15 = profile % 2 ? 0x40 : 0;
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
    assert(attributes[0] == 0x20 && attributes[1] == 0x38 && bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
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
    assert(table[animation][0] == word);
    if (expected.unk2)
        assert(D_8011AF60[animation] == resource);
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (u32*)table[animation];
    expected.animation_step.packed = word;
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
    palette_dirty |= 1;
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
            assert(expected.animation_table[0x1E][1] == (expected.unk2 ? 0xC2FF0060 : 0x8FFF0060));
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
    expected.unk15 = side ? 0x40 : 0;
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
    g_Player.script_facing = g_Player.unk15 ^ 0x40;
    set_animation(&g_Player, 0x41);
    capture();
    assert(expected.animation_step.packed == (expected.unk2 ? 0x10010003 : 0xA2000060));
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
    g_Player.script_facing = g_Player.unk15 ^ 0x40;
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
    g_Player.unk15 = facing ? 0x40 : 0;
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
            assert(words[j] == ref->words[j]);
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
    expected_player_script_motion.animation_step.packed = ref->words[frame];
    if (expected_player_script_motion.unk2 || explicit_frame)
        expected_player_script_motion.unk38 = (u8*)gfx_player_script_motion + (ref->bank ? 0x80 : 0x40);
    expected_player_script_motion.unk3C = (u8*)sprites_player_script_motion + (ref->bank ? 0x80 : 0x40);
}

static void expect_tick(void)
{
    const struct AnimationReference* ref = reference(expected_player_script_motion.unk2, expected_player_script_motion.unk17);
    u32 frame = expected_player_script_motion.animation_cursor - expected_player_script_motion.animation_table[expected_player_script_motion.unk17];
    u32 duration = expected_player_script_motion.animation_step.packed & 255;
    assert(duration != 0 && frame < ref->count);
    if (duration == 1) {
        s32 next = (s32)frame + (s8)(expected_player_script_motion.animation_step.packed >> 16);
        assert(next >= 0 && next < ref->count);
        expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[expected_player_script_motion.unk17] + next;
        expected_player_script_motion.animation_step.packed = ref->words[next];
    } else
        expected_player_script_motion.animation_step.packed = (expected_player_script_motion.animation_step.packed & ~255u) | (duration - 1);
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
        expected_player_script_motion.animation_step.packed = ref->words[next];
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
static u32 ladder_attributes[1] = { 0x20 };

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
        expected_player_script_motion.unk15 = 0x40;
    duration = expected_player_script_motion.animation_step.fields.duration;
    if (held == 1) {
        if (duration == 1) {
            next = (s32)frame + (s8)(ref->words[frame] >> 16);
            expected_player_script_motion.animation_cursor = expected_player_script_motion.animation_table[animation] + next;
            expected_player_script_motion.animation_step.packed = ref->words[next];
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
    assert(TEST_BG_TILE_ATTRS == (u8*)ladder_attributes && ladder_attributes[0] == 0x20);
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
    for (i = 0; i < COUNT(ladder_map); i++)
        assert(ladder_map[i] == 1);
    for (i = 0; i < sizeof(ladder_tiles) / 4; i++)
        assert(((u32*)ladder_tiles)[i] == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "player_hurt_slide", 0, 0, 1, test_player_hurt_slide },
    { "dash_braking", 0, 0, COUNT(dash_braking), test_dash_braking },
    { "dash_cancels", 0, 0, COUNT(dash_cancels), test_dash_cancels },
    { "dash_nova_strike", 0, 0, 2, test_dash_nova_strike },
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
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(dash_braking) + COUNT(dash_cancels) + 2 + 72 + 30 + 36 + 108 + 108 + 12 + 48 + 6 + 32 + 101 + 2 + 2;
