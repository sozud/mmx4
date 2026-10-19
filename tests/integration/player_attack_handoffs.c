#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/player_weapon.h"
#include "main/player_special.h"
#include "main/player.h"
#include "main/player_enter.h"
#include "main/player_check.h"
#include "main/55C4.h"
extern s8 player_shot_counts_as_shot[];
extern s8 player_shot_counts_as_special[];
extern s8 player_shot_is_charged_special[];
extern s8 player_shot_limits[];
extern struct PlayerShotTiming player_shot_timings[];
extern s8 player_shot_waits_for_specials[];
void player_update_shooting(struct PlayerObj* self);

void player_script_jump(struct PlayerObj*);
void player_wall_jump_push(struct PlayerObj*);
void player_wall_jump_rise(struct PlayerObj*);
void player_wall_slide_down(struct PlayerObj*);
void player_wall_slide_release(struct PlayerObj*);
void player_dash_start(struct PlayerObj*);
void player_dash_move(struct PlayerObj*);
void player_dash_end(struct PlayerObj*);
void player_ladder_shoot(struct PlayerObj*);
void player_hover(struct PlayerObj*);
void player_rising_fire(struct PlayerObj*);
void func_80037484(struct PlayerObj*, s32);

static struct Unk_unk68 bounds = { 0, 0, 4, 4 };
static u32 gfx[16] = { 0x20, 0x24 };
static u32 sprites[16] = { 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34 };
static u8 tilemap[3 * 256], sound_commands[32];
static u16 pixels[512];
static u32 attributes[1];
static Palette bank[12];
static u16 palette[0x152], palette_expected[0x152];
static struct PlayerObj expected, entity_before;
static struct EngineObj engine_expected;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_expected[32];
static u32 palette_dirty;
static u16 expected_random;

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
    cur_random = expected_random = 0x1234;
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
        assert(pixels[i] == 0);
    for (i = 0; i < COUNT(sound_commands); i++)
        assert(sound_commands[i] == 0);
    for (i = 0; i < 16; i++) {
        assert(gfx[i] == (i < 2 ? 0x20 + 4 * i : 0));
        assert(sprites[i] == (i < 6 ? 0x20 + 4 * i : 0));
    }
    assert(attributes[0] == 0x20 && bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(cur_random == expected_random && need_palette_load == palette_dirty);
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
    assert(D_80119DF0[animation][0] == word);
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (u32*)D_80119DF0[animation];
    expected.animation_step.packed = word;
    expected.unk3C = (u8*)sprites + 0x20;
}

struct Handoff {
    void (*run)(struct PlayerObj*);
    u8 action, phase, animation, ground;
};
static const struct Handoff nova_handoffs[] = {
    { player_enter_land, PLAYER_FALL, 0, 0xB, 1 },
    { player_script_jump, PLAYER_SCRIPT_JUMP, 1, 0xB, 1 },
    { player_walk_start, PLAYER_WALK_START, 0, 7, 1 },
    { player_walk, PLAYER_WALK, 0, 8, 1 },
    { player_land, PLAYER_LAND, 0, 0xC, 1 },
    { player_idle, PLAYER_IDLE, 0, 5, 1 },
    { player_dash_start, PLAYER_DASH, 0, 0x10, 1 },
    { player_dash_move, PLAYER_DASH, 1, 0x10, 1 },
    { player_dash_end, PLAYER_DASH, 2, 0x11, 1 },
    { player_wall_cling, PLAYER_WALL_CLING, 0, 0xD, 0 },
    { player_wall_jump_push, PLAYER_WALL_JUMP, 0, 0xE, 0 },
    { player_wall_jump_rise, PLAYER_WALL_JUMP, 1, 0xE, 0 },
    { player_wall_slide_down, PLAYER_WALL_SLIDE, 0, 0xF, 0 },
    { player_wall_slide_release, PLAYER_WALL_SLIDE, 1, 0xB, 0 },
    { player_air_dash, PLAYER_AIR_DASH, 0, 0x13, 0 },
    { player_hover, PLAYER_HOVER, 0, 0x15, 0 },
    { player_rising_fire, PLAYER_RISING_FIRE, 0, 0x63, 1 },
    { player_ladder_up, PLAYER_LADDER_UP, 0, 0x1F, 0 },
    { player_ladder_down, PLAYER_LADDER_DOWN, 0, 0x20, 0 },
    { player_ladder_shoot, PLAYER_LADDER_SHOOT, 0, 0x5C, 0 },
};

static u32 test_nova_handoff(u32 row)
{
    u32 kind = row, profile = (row + 2) % 8, i;
    const struct Handoff* handoff = &nova_handoffs[kind];
    u32 weapon = profile / 4 % 2 ? 2 : 0;
    prepare(profile);
    g_Player.unk5 = handoff->action;
    g_Player.unk6 = handoff->phase;
    g_Player.unk88.bytes.collision_flags = handoff->ground ? PLAYER_COLLIDE_GROUND : 0;
    g_Player.armor_parts = 2;
    g_Player.weapon = weapon;
    g_Player.weapon_energy[0] = 48;
    g_Player.pressed_input = PLAYER_INPUT_GIGA;
    g_Player.script_state = kind == 1 ? 2 : 0;
    g_Player.attacking = kind == 16 ? 0 : 1;
    engine_obj.unk37 = profile / 2 % 2;
    set_animation(&g_Player, handoff->animation);
    capture();
    expect_animation(0x6A, 0xD5010003);
    expected.script_state = 0;
    expected.attacking = expected.shot_fired = expected.attack_ended = expected.attack_pose_timer = 0;
    expected.shot_cooldown = expected.shot_palette_timer = 0;
    expected.weapon = expected.stock_charge = expected.charge_state[0] = expected.charge_state[1] = 0;
    expected.charge_timer = expected.special_charge_timer = expected.flash_palette = 0;
    expected.shot_types[0] = expected.shot_types[1] = 0;
    expected.dash_momentum = expected.afterimage = expected.hurt_phase = expected.invincibility_timer = 0;
    expected.air_action = 5;
    expected.air_state = expected.spike_immune = expected.nova_strike_active = 1;
    expected.nova_strike_timer = 24;
    expected.weapon_energy[0] = engine_obj.unk37 ? 48 : 0;
    expected.x_vel.val = g_Player.unk15 ? 0x28000 : -0x28000;
    expected.y_vel.val = 0x38000;
    expected.unk28 = 0;
    expected.unk2C = 0x4200;
    expected.unk5 = PLAYER_NOVA_STRIKE;
    expected.unk6 = 0;
    engine_expected.gameplay_locked = 1;
    if (weapon)
        for (i = 0; i < 32; i++)
            palette_expected[1 + i] = 0x1200 + 112 + i;
    for (i = 0; i < 16; i++)
        palette_expected[1 + i] = 0x1200 + i;
    for (i = 0; i < 32; i++)
        palette_expected[0x131 + i] = 0x1210 + i;
    palette_dirty |= 1;
    handoff->run(&g_Player);
    check();
    assert(D_80119DF0[0x6A][0] == 0xD5010003 && D_80119DF0[0x63][0] == 0xE7010002);
    return 1;
}

static u32 test_emitted_shot_pose(u32 row)
{
    static const u8 types[] = { 0, 2, 4, 7, 11, 12, 13, 16 };
    u32 type = types[row % COUNT(types)], airborne = row / COUNT(types) % 2;
    u32 profile = row / (2 * COUNT(types)), allocation = profile % 3;
    s32 result;
    prepare(profile);
    set_animation(&g_Player, airborne ? 0xB : 5);
    g_Player.unk5 = airborne ? PLAYER_FALL : PLAYER_IDLE;
    g_Player.air_action = 2;
    g_Player.shot_cooldown = 1;
    g_Player.shot_type = g_Player.last_shot_type = type;
    g_Player.shot_count = 2;
    g_Player.special_shot_count = 1;
    if (allocation)
        weapon_objects[15].active = 0;
    if (allocation == 2)
        visual_objects[31].active = 0;
    capture();
    if (type != 0) {
        expected.dash_momentum = expected.afterimage = 0;
        if (!airborne)
            expected.air_action = 0;
        expected.air_state = 1;
        expected.unk5 = PLAYER_WEAPON_POSE;
        expected.unk6 = 0;
        if (type == 2 || type == 11)
            expect_animation(0x5F, 0x8A010004);
        else if (type == 4) {
            expect_animation(airborne ? 0x64 : 0x63, airborne ? 0x67010002 : 0xE7010002);
            expected.unk5 = PLAYER_RISING_FIRE;
        } else if (type == 7 || type == 16)
            expect_animation(type == 7 ? 0x68 : 0x69, 0x61010002);
        else if (type == 12) {
            expect_animation(0x60, 0x8A010004);
            expected.controlling_clone = expected.spike_immune = 1;
            expected.invincibility_timer = expected.hurt_phase = 0;
            expected.unk5 = PLAYER_SOUL_BODY;
        } else {
            expect_animation(airborne ? 0x66 : 0x65, airborne ? 0x64010001 : 0x51010002);
            expected.shot_count = 3;
            expected.special_shot_count = 2;
            expected.spike_immune = 1;
            expected.unk5 = PLAYER_RISING_FIRE_CHARGED;
            if (allocation) {
                weapons_expected[15].active = 1;
                weapons_expected[15].id = 13;
                weapons_expected[15].unk2 = airborne;
                weapons_expected[15].bg_offset = g_Player.bg_offset;
                if (allocation == 2) {
                    visuals_expected[31].active = 1;
                    visuals_expected[31].id = 26;
                    visuals_expected[31].unk2 = airborne + 2;
                    visuals_expected[31].bg_offset = g_Player.bg_offset;
                    visuals_expected[31].unk50 = (struct PlayerObj*)&weapon_objects[15];
                }
            }
        }
    }
    result = airborne ? player_check_shoot_air(&g_Player) : player_check_shoot(&g_Player);
    assert(result == (type != 0));
    check();
    return result;
}

static u32 test_nonpose_dispatch(u32 row)
{
    static const u8 types[] = { 0, 6, 9 };
    prepare(row / 6);
    set_animation(&g_Player, 5);
    g_Player.shot_type = types[row % 3];
    capture();
    func_80037484(&g_Player, row / 3 % 2);
    check();
    return 1;
}

struct ShotRule {
    u8 limit, pose, cooldown, cost, counted, special, charged, waits;
};
static const struct ShotRule shot_rules[21] = {
    { 3, 20, 6, 0, 1, 0, 0, 0 },
    { 3, 25, 15, 4, 1, 1, 0, 1 },
    { 3, 1, 1, 3, 0, 0, 0, 1 },
    { 3, 20, 15, 6, 1, 1, 0, 1 },
    { 3, 10, 10, 3, 0, 0, 0, 1 },
    { 3, 20, 10, 1, 1, 1, 0, 0 },
    { 3, 70, 70, 1, 0, 0, 0, 0 },
    { 3, 1, 1, 1, 0, 0, 0, 1 },
    { 4, 20, 6, 1, 0, 0, 0, 0 },
    { 3, 25, 15, 0, 1, 0, 0, 0 },
    { 4, 25, 20, 12, 1, 1, 1, 0 },
    { 4, 1, 1, 12, 0, 0, 1, 0 },
    { 4, 1, 1, 12, 0, 0, 1, 0 },
    { 4, 1, 1, 12, 0, 0, 1, 0 },
    { 4, 25, 20, 6, 1, 1, 1, 0 },
    { 1, 250, 250, 12, 0, 1, 1, 0 },
    { 4, 1, 1, 12, 0, 0, 1, 0 },
    { 4, 35, 20, 6, 0, 0, 1, 0 },
    { 3, 35, 15, 0, 1, 0, 0, 0 },
    { 4, 25, 6, 0, 1, 0, 0, 0 },
    { 4, 35, 15, 0, 1, 0, 0, 0 },
};
enum {
    SHOOT_PRESS,
    SHOOT_AT_LIMIT,
    SHOOT_BELOW_LIMIT,
    SHOOT_SAME_SPECIAL,
    SHOOT_OTHER_SPECIAL,
    SHOOT_COOLDOWN,
    SHOOT_NO_INPUT,
    SHOOT_CLONE,
    SHOOT_HURT,
    SHOOT_SECONDARY,
    SHOOT_BOTH,
    SHOOT_NO_ENERGY,
    SHOOT_LOW_ENERGY,
    SHOOT_RELEASE,
    SHOOT_RELEASE_SPECIAL,
    SHOOT_STILL_HELD,
    SHOOT_RELEASE_BOTH,
    SHOOT_RELEASE_EMPTY,
    SHOOT_MODES
};
#define SHOOT_SWEEP 126
#define SHOOT_ROWS (SHOOT_SWEEP + 2 * (SHOOT_MODES - SHOOT_RELEASE))
static u32 test_shooting(u32 row)
{
    u32 extra = row >= SHOOT_SWEEP, index = row - SHOOT_SWEEP;
    u32 type = extra ? (index % 2 ? 19 : 0) : row % 21;
    u32 mode = extra ? SHOOT_RELEASE + index / 2 : row % SHOOT_MODES, cycle = (type + mode) % 2;
    u32 available = (type + mode) / 2 % 2, weapon = type < 9 ? type : type < 18 ? type - 9
                                                                                : 0;
    const struct ShotRule* c = &shot_rules[type];
    u32 energy = mode == SHOOT_NO_ENERGY || mode == SHOOT_RELEASE_EMPTY ? 0 : mode == SHOOT_LOW_ENERGY ? 1
                                                                                                       : 48,
        enough, selected, primary;
    u32 fire, basic = type == 0 || type == 1 || type == 3 || type == 5 || type == 14 || type == 15 || type == 19;
    prepare(row % 6);
    set_animation(&g_Player, 5);
    g_Player.weapon = weapon;
    g_Player.weapon_energy[weapon] = energy;
    g_Player.shot_types[0] = g_Player.shot_types[1] = type;
    g_Player.pressed_input = mode == SHOOT_NO_INPUT ? 0 : mode == SHOOT_SECONDARY ? PLAYER_INPUT_SPECIAL
                                                                                  : PLAYER_INPUT_SHOOT | (mode == SHOOT_BOTH ? PLAYER_INPUT_SPECIAL : 0);
    if (mode >= SHOOT_RELEASE) {
        g_Player.pressed_input = 0;
        g_Player.input.buttons.previous = mode == SHOOT_RELEASE_SPECIAL ? PLAYER_INPUT_SPECIAL : (mode == SHOOT_RELEASE_BOTH || mode == SHOOT_STILL_HELD) ? PLAYER_INPUT_SHOOT | PLAYER_INPUT_SPECIAL
                                                                                                                                                          : PLAYER_INPUT_SHOOT;
        g_Player.input.buttons.held = mode == SHOOT_STILL_HELD ? PLAYER_INPUT_SHOOT | PLAYER_INPUT_SPECIAL : 0;
    }
    g_Player.shot_cooldown = mode == SHOOT_COOLDOWN ? 1 : 0;
    g_Player.shot_count = mode == SHOOT_AT_LIMIT ? c->limit : mode == SHOOT_BELOW_LIMIT ? c->limit - 1
                                                                                        : 0;
    g_Player.special_shot_count = mode == SHOOT_SAME_SPECIAL || mode == SHOOT_OTHER_SPECIAL;
    g_Player.last_shot_type = mode == SHOOT_OTHER_SPECIAL ? (type + 1) % 21 : type;
    g_Player.shot_cycle = cycle * 2;
    g_Player.is_clone = mode == SHOOT_CLONE;
    g_Player.hurt_phase = mode == SHOOT_HURT;
    g_Player.armor_parts = row % 2;
    if (available)
        weapon_objects[15].active = visual_objects[31].active = 0;
    capture();
    enough = !weapon || mode == SHOOT_SECONDARY || (energy && ((type < 9 && g_Player.armor_parts) || energy >= c->cost));
    selected = mode != SHOOT_NO_INPUT;
    if (mode >= SHOOT_RELEASE)
        selected = mode != SHOOT_STILL_HELD && type != 0 && type != 19
            && (mode == SHOOT_RELEASE_SPECIAL || mode == SHOOT_RELEASE_BOTH || type >= 9);
    primary = mode != SHOOT_SECONDARY && mode != SHOOT_RELEASE_SPECIAL && (mode < SHOOT_RELEASE || type >= 9);
    fire = selected && enough && mode != SHOOT_AT_LIMIT && mode != SHOOT_COOLDOWN
        && (!c->waits || !g_Player.special_shot_count)
        && (!c->charged || !g_Player.special_shot_count || mode == SHOOT_OTHER_SPECIAL)
        && (type != 6 || g_Player.special_shot_count);
    if (mode != SHOOT_COOLDOWN) {
        expected.shot_type = !selected || !enough ? -1 : type;
        if (weapon && selected && primary)
            expected.stock_charge = 0;
    }
    if (fire) {
        expected.last_shot_type = type;
        expected.attacking = expected.shot_fired = 1;
        expected.attack_ended = 0;
        expected.attack_pose_timer = c->pose;
        expected.shot_cooldown = c->cooldown;
        expected.shot_count += c->counted + (type == 8 ? 2 : type == 17 ? 8
                                                                        : 0);
        expected.special_shot_count += c->special + (type == 8 ? 2 : type == 17 ? 8
                                                                                : 0);
        expected.shot_cycle = cycle ? 0 : 1;
        if (type == 19)
            expected.stock_charge--;
        if (c->cost && (type > 8 || !g_Player.armor_parts))
            expected.weapon_energy[weapon] -= c->cost;
        if (!g_Player.is_clone && !weapon && !g_Player.hurt_phase) {
            if (type == 0)
                expected.shot_palette_timer = 6;
            if (type == 9)
                expected.shot_palette_timer = 5;
            if (type == 18)
                expected.shot_palette_timer = 7;
        }
        if (type == 18)
            expected_random = 0x366A;
        if (available && (basic || type == 8 || type == 10 || type == 17)) {
            weapons_expected[15].active = 1;
            weapons_expected[15].id = type;
            weapons_expected[15].unk2 = 0;
            weapons_expected[15].bg_offset = g_Player.bg_offset;
            if (basic)
                weapons_expected[15].owner = &g_Player;
        }
        if (available && (type == 9 || type == 18 || type == 20)) {
            visuals_expected[31].active = 0x21;
            visuals_expected[31].id = 2;
            visuals_expected[31].unk2 = type;
            visuals_expected[31].bg_offset = g_Player.bg_offset;
        }
    }
    player_update_shooting(&g_Player);
    check();
    assert(player_shot_limits[type] == c->limit && player_shot_timings[type].pose_time == c->pose
        && player_shot_timings[type].cooldown == c->cooldown);
    assert(player_shot_counts_as_shot[type] == c->counted && player_shot_counts_as_special[type] == c->special);
    assert(player_shot_is_charged_special[type] == c->charged && player_shot_waits_for_specials[type] == c->waits);
    assert(((const s8*)&player_weapon_energy)[type] == c->cost);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "shooting_dispatch", 0, 0, SHOOT_ROWS, test_shooting },
    { "nova_handoff", 0, 0, COUNT(nova_handoffs), test_nova_handoff },
    { "emitted_shot_pose", 0, 0, 40, test_emitted_shot_pose },
    { "nonpose_dispatch", 0, 0, 3, test_nonpose_dispatch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = SHOOT_ROWS + COUNT(nova_handoffs) + 40 + 3;
