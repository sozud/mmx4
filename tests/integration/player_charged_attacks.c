#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/player.h"
#include "main/player_special.h"
#include "main/55C4.h"

void player_fire_lightning_web_charged(struct PlayerObj*);
void player_enter_rising_fire_charged(struct PlayerObj*, s32);
void player_enter_soul_body(struct PlayerObj*);
void player_soul_body(struct PlayerObj*);
void player_soul_body_clone_vanish(struct PlayerObj*);
void player_rising_fire_charged(struct PlayerObj*);
void player_init_clone(void);
extern struct Unk_unk68 player_x_collision_bounds;

static u32 gfx[16] = { 0x20, 0x24 };
static u32 frames[16] = { 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34 };
static u8 tilemap[3 * 256];
static u16 tiles[512], palettes[512];
static u32 attributes[1];
static struct PlayerObj player_expected, entity_expected;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_expected[32];

static void prepare(u32 facing, u32 background)
{
    u32 i;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0x35, sizeof(g_Entity));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0x25, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0x35, sizeof(weapon_objects));
    memset(visual_objects, 0x45, sizeof(visual_objects));
    for (i = 0; i < COUNT(weapon_objects); i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].owner = &g_Entity;
    }
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].unk50 = &g_Entity;
    }
    memset(tilemap, 1, sizeof(tilemap));
    memset(tiles, 0, sizeof(tiles));
    memset(palettes, 0x53, sizeof(palettes));
    attributes[0] = 0;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_height = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    TEST_PALETTE = (u8*)palettes;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.unk5 = PLAYER_IDLE;
    g_Player.hp = 24;
    g_Player.bg_offset = background;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.unk16 = 2;
    g_Player.unk38 = (u8*)gfx + 0x20;
    g_Player.unk3C = (u8*)frames + 0x20;
    g_Player.unk68 = &player_x_collision_bounds;
    g_Player.animation_table = (u32**)D_80119DF0;
    g_Player.x_pos.val = 160 * 65536 + 0x1234;
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    g_Player.voice_timer = 1;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    g_Player.weapon = 4;
    g_Player.weapon_energy[4] = 48;
    engine_obj.max_hp = 24;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    set_animation(&g_Player, 5);
}

static void capture(void)
{
    player_expected = g_Player;
    entity_expected = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
}

static void check(void)
{
    u32 i;
    c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
    c_test_same_words(&g_Entity, &entity_expected, sizeof(entity_expected));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects,
               (const u32*)weapons_expected, sizeof(weapons_expected) / 4)
        == 0);
    assert(c_test_word_difference((const u32*)visual_objects,
               (const u32*)visuals_expected, sizeof(visuals_expected) / 4)
        == 0);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678
        && controller_input.pressed == 0x840);
    assert(need_palette_load == 0x20 && cur_random == 0x1234);
    for (i = 0; i < COUNT(palettes); i++)
        assert(palettes[i] == 0x5353);
    assert(gfx[0] == 0x20 && gfx[1] == 0x24);
    for (i = 0; i < 6; i++) {
        assert(frames[i] == 0x20 + i * 4);
        assert(D_8013E198[i] == -1);
    }
}

static void expect_animation(u32 animation, u32 frame)
{
    player_expected.unk17 = animation;
    player_expected.previous_animation_index = 0xFF;
    player_expected.animation_cursor = (u32*)D_80119DF0[animation] + frame;
    player_expected.animation_step.packed = D_80119DF0[animation][frame];
    player_expected.unk3C = (u8*)frames + 0x20;
}

static void expect_weapon(u32 slot, u32 id, u32 subtype)
{
    struct WeaponObj* obj = &weapons_expected[slot];
    obj->unk50 = obj->unk54 = obj->unk68 = NULL;
    obj->unk98 = obj->unk61 = obj->unk64 = obj->unk65 = obj->unk66 = 0;
    obj->unk72 = obj->unk73 = obj->unk74 = obj->unk75 = 0;
    obj->unk76 = obj->unk77 = obj->unk78 = obj->unk7A = 0;
    obj->unk62 = obj->unk63 = 0;
    obj->active = 1;
    obj->id = id;
    obj->unk2 = subtype;
    obj->bg_offset = player_expected.bg_offset;
}

static u32 test_lightning_web(u32 row)
{
    static const u16 free_masks[] = {
        0,
        1,
        3,
        0x55,
        0xFF,
        0x1FF,
        0x3FF,
        0xFFFF,
        0xFE00,
        0xAAAA,
    };
    u32 plan = row % COUNT(free_masks), i, first = 0, created = 0;
    prepare(row / (3 * COUNT(free_masks)), row / COUNT(free_masks) % 3);
    g_Player.shot_type = 10;
    for (i = 0; i < COUNT(weapon_objects); i++)
        if (free_masks[plan] & (1u << i))
            weapon_objects[i].active = 0;
    capture();
    for (i = 0; i < COUNT(weapon_objects) && created < 9; i++) {
        if (free_masks[plan] & (1u << i)) {
            expect_weapon(i, 10, created);
            if (created == 0)
                first = i;
            else
                weapons_expected[i].owner = (struct PlayerObj*)&weapon_objects[first];
            created++;
        }
    }
    player_fire_lightning_web_charged(&g_Player);
    check();
    return created;
}

static u32 test_rising_fire_entry(u32 row)
{
    u32 weapon = row % 3, visual = row / 3 % 3, airborne = row / 9 % 2;
    u32 weapon_slot = weapon == 1 ? 0 : 15, visual_slot = visual == 1 ? 0 : 31;
    prepare(row / 18, row % 3);
    if (weapon)
        weapon_objects[weapon_slot].active = 0;
    if (visual)
        visual_objects[visual_slot].active = 0;
    capture();
    expect_animation(airborne ? 0x66 : 0x65, 0);
    player_expected.shot_count = 4;
    player_expected.special_shot_count = 3;
    player_expected.air_state = player_expected.spike_immune = 1;
    player_expected.unk5 = PLAYER_RISING_FIRE_CHARGED;
    player_expected.unk6 = 0;
    if (weapon) {
        expect_weapon(weapon_slot, 13, airborne);
        if (visual) {
            visuals_expected[visual_slot].active = 1;
            visuals_expected[visual_slot].id = 26;
            visuals_expected[visual_slot].unk2 = airborne + 2;
            visuals_expected[visual_slot].bg_offset = g_Player.bg_offset;
            visuals_expected[visual_slot].unk50 = (struct PlayerObj*)&weapon_objects[weapon_slot];
        }
    }
    player_enter_rising_fire_charged(&g_Player, airborne);
    check();
    return 1;
}

static u32 test_soul_body_entry(u32 row)
{
    prepare(row % 2, row / 2);
    g_Player.invincibility_timer = 17;
    g_Player.hurt_phase = 2;
    g_Player.unk6 = 3;
    capture();
    expect_animation(0x60, 0);
    player_expected.controlling_clone = player_expected.spike_immune = 1;
    player_expected.invincibility_timer = player_expected.hurt_phase = 0;
    player_expected.air_state = 1;
    player_expected.unk5 = PLAYER_SOUL_BODY;
    player_expected.unk6 = 0;
    player_enter_soul_body(&g_Player);
    check();
    return 1;
}

static const u32 cast_frames[] = {
    0x8A010004,
    0x8B010003,
    0x60018002,
    0x5F010002,
    0x60000060,
};

static void expect_clone(void)
{
    memset(&entity_expected, 0, sizeof(entity_expected));
    entity_expected.is_clone = 1;
    entity_expected.animation_table = (u32**)D_80119DF0;
    entity_expected.hp = entity_expected.hud_hp = entity_expected.spawn_hp = 24;
    entity_expected.unk38 = entity_expected.unk3C = (u8*)gfx + 0x20;
    entity_expected.unk40 = 0x540;
    entity_expected.unk16 = 2;
    entity_expected.unk42 = 0x7800;
    entity_expected.unk49 = 1;
    entity_expected.active = 1;
    entity_expected.x_pos = player_expected.x_pos;
    entity_expected.y_pos = player_expected.y_pos;
    entity_expected.unk15 = player_expected.unk15;
    entity_expected.air_state = 1;
    entity_expected.clone_timer = 240;
    entity_expected.unk68 = &player_x_collision_bounds;
}

static u32 test_soul_body_cast(u32 row)
{
    u32 tick, index = 0, count = row % 12 + 1, i;
    prepare(row / 36 % 2, row / 12 % 3);
    if (row / 72)
        memset(&g_Entity, 0, sizeof(g_Entity));
    g_Player.weapon = 3;
    player_enter_soul_body(&g_Player);
    capture();
    for (tick = 0; tick < count; tick++) {
        if (--player_expected.animation_step.fields.duration == 0) {
            if (index != 4)
                index++;
            player_expected.animation_cursor = (u32*)D_80119DF0[0x60] + index;
            player_expected.animation_step.packed = cast_frames[index];
        }
        if (player_expected.unk6 == 0
            && (player_expected.animation_step.fields.event & 0x80)) {
            player_expected.animation_step.fields.event = 0;
            player_expected.unk6 = 1;
            expect_clone();
        }
        player_soul_body(&g_Player);
        c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
        c_test_same_words(&g_Entity, &entity_expected, sizeof(entity_expected));
    }
    check();
    for (i = 0; i < COUNT(cast_frames); i++)
        assert(D_80119DF0[0x60][i] == cast_frames[i]);
    return 1;
}

static u32 test_soul_body_release(u32 row)
{
    u32 ground = row % 2, dash = row / 2 % 2, low_hp = row / 4 % 2;
    prepare(row / 8, row % 3);
    g_Player.weapon = 3;
    player_enter_soul_body(&g_Player);
    g_Player.unk6 = 1;
    g_Player.hp = low_hp ? 7 : 24;
    g_Player.dash_momentum = dash;
    g_Player.afterimage = 1;
    g_Player.air_action = 3;
    g_Player.x_vel.val = 0x12345;
    g_Player.y_vel.val = -0x23456;
    g_Player.unk28 = -0x4000;
    g_Player.unk2C = 0x4200;
    g_Player.unk88.bytes.collision_flags = ground ? PLAYER_COLLIDE_GROUND : 0;
    player_init_clone();
    g_Entity.active = g_Entity.on_screen = 1;
    g_Entity.state = PLAYER_STATE_NORMAL;
    g_Entity.unk5 = PLAYER_SOUL_BODY_VANISH;
    set_animation_frame(ANIMATED_OBJECT(&g_Entity), 0x62, 5);
    capture();
    entity_expected.animation_step.fields.duration--;
    entity_expected.active = entity_expected.on_screen = 0;
    player_expected.controlling_clone = player_expected.spike_immune = 0;
    player_expected.unk6 = 0;
    if (ground) {
        expect_animation(low_hp ? 6 : 5, 0);
        player_expected.unk5 = PLAYER_IDLE;
        player_expected.air_state = player_expected.air_action = 0;
    } else {
        expect_animation(0xB, 0);
        player_expected.unk5 = PLAYER_FALL;
        player_expected.air_state = -1;
        player_expected.x_vel.val = player_expected.y_vel.val = player_expected.unk28 = 0;
        if (dash) {
            player_expected.dash_momentum = 0;
            player_expected.afterimage = -1;
        }
    }
    player_soul_body_clone_vanish(&g_Entity);
    player_soul_body(&g_Player);
    check();
    return 1;
}

static void expect_gravity(void)
{
    player_expected.x_pos.val += player_expected.x_vel.val;
    player_expected.y_pos.val -= player_expected.y_vel.val;
    player_expected.x_vel.val += player_expected.unk15 ? -0x4000 : 0x4000;
    player_expected.y_vel.val -= 0x4200;
    if (player_expected.y_vel.val < -0x68000)
        player_expected.y_vel.val = -0x68000;
}

static u32 test_rising_fire_start(u32 row)
{
    static const u32 ground_frames[] = {
        0x51010002,
        0x43010002,
        0x64010001,
        0x64010101,
        0x65000060,
    };
    static const u32 air_frames[] = { 0x64010001, 0x64010101, 0x65000060 };
    u32 airborne = row % 2, index = 0, tick;
    const u32* sequence = airborne ? air_frames : ground_frames;
    prepare(row / 2, row % 3);
    player_enter_rising_fire_charged(&g_Player, airborne);
    capture();
    for (tick = 0; tick < (airborne ? 1 : 5); tick++) {
        if (--player_expected.animation_step.fields.duration == 0) {
            index++;
            player_expected.animation_cursor++;
            player_expected.animation_step.packed = sequence[index];
        }
        if (tick == (airborne ? 0 : 4)) {
            player_expected.x_vel.val = row / 2 ? 0x40000 : -0x40000;
            player_expected.y_vel.val = 0x6C000;
            player_expected.unk28 = -0x4000;
            player_expected.unk2C = 0x4200;
            player_expected.unk6 = 1;
        }
        player_rising_fire_charged(&g_Player);
        c_test_same_words(&g_Player, &player_expected, sizeof(player_expected));
    }
    check();
    return 1;
}

static u32 test_rising_fire_rise(u32 row)
{
    static const s32 speeds[] = { 0x6C000, 1, 0, -1 };
    static const u8 collisions[] = {
        0,
        PLAYER_COLLIDE_RIGHT,
        PLAYER_COLLIDE_LEFT,
        PLAYER_COLLIDE_CEILING,
        PLAYER_COLLIDE_CEILING | PLAYER_COLLIDE_LEFT | PLAYER_COLLIDE_RIGHT,
    };
    u32 speed = row % 4, collision = row / 4 % 5, facing = row / 20 % 2;
    u32 phase = row / 40 + 1;
    prepare(facing, row % 3);
    g_Player.unk5 = PLAYER_RISING_FIRE_CHARGED;
    g_Player.unk6 = phase;
    g_Player.air_state = g_Player.spike_immune = 1;
    g_Player.x_vel.val = (facing ? 1 : -1) * (speed == 1 ? 0x2000 : 0x40000);
    g_Player.y_vel.val = speeds[speed];
    g_Player.unk28 = -0x4000;
    g_Player.unk2C = 0x4200;
    g_Player.unk88.bytes.collision_flags = collisions[collision];
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0x65, 4);
    capture();
    player_expected.animation_step.fields.duration--;
    if (speed >= 2 || collision >= 3) {
        expect_animation(0x67, 0);
        if (collision >= 3)
            player_expected.y_vel.val = 0;
        player_expected.x_vel.val = player_expected.unk28 = 0;
        player_expected.air_state = -1;
        player_expected.unk6 = 3;
    } else {
        expect_gravity();
        if (phase == 1 && (speed == 1 || (facing && collision == 1) || (!facing && collision == 2))) {
            player_expected.x_vel.val = player_expected.unk28 = 0;
            player_expected.unk6 = 2;
        }
    }
    player_rising_fire_charged(&g_Player);
    check();
    return 1;
}

static u32 test_rising_fire_fall(u32 row)
{
    static const s32 speeds[] = { 1, -0x64000, -0x68000 };
    u32 speed = row % 3, terminal = row / 3 % 2, attacking = row / 6 % 2;
    u32 facing = row / 12 % 2, ground = row / 24;
    prepare(facing, row % 3);
    g_Player.unk5 = PLAYER_RISING_FIRE_CHARGED;
    g_Player.unk6 = 3;
    g_Player.air_state = g_Player.spike_immune = 1;
    g_Player.dash_momentum = g_Player.afterimage = g_Player.air_action = 1;
    g_Player.input_locked = 1;
    g_Player.attacking = attacking;
    g_Player.x_vel.val = facing ? 0x40000 : -0x40000;
    g_Player.y_vel.val = speeds[speed];
    g_Player.unk28 = -0x4000;
    g_Player.unk2C = 0x4200;
    g_Player.unk88.bytes.collision_flags = ground ? PLAYER_COLLIDE_GROUND : 0;
    set_animation_frame(ANIMATED_OBJECT(&g_Player), 0x67, terminal ? 2 : 0);
    capture();
    player_expected.animation_step.fields.duration--;
    if (ground) {
        expect_animation(attacking ? 0x7C : 0xC, 0);
        player_expected.spike_immune = player_expected.air_state = 0;
        player_expected.dash_momentum = player_expected.air_action = 0;
        player_expected.afterimage = -1;
        player_expected.unk5 = PLAYER_LAND;
        player_expected.unk6 = 0;
    } else {
        expect_gravity();
        if (terminal) {
            expect_animation(attacking ? 0x7B : 0xB, 0);
            player_expected.spike_immune = 0;
            player_expected.unk5 = PLAYER_FALL;
            player_expected.unk6 = 0;
        }
    }
    player_rising_fire_charged(&g_Player);
    check();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "charged_lightning_web_allocation", 0, 0, 3, test_lightning_web },
    { "charged_rising_fire_entry", 0, 0, 12, test_rising_fire_entry },
    { "soul_body_entry", 0, 0, 4, test_soul_body_entry },
    { "soul_body_cast_timeline", 0, 0, 12, test_soul_body_cast },
    { "soul_body_clone_release", 0, 0, 6, test_soul_body_release },
    { "charged_rising_fire_start", 0, 0, 4, test_rising_fire_start },
    { "charged_rising_fire_ascent", 0, 0, 28, test_rising_fire_rise },
    { "charged_rising_fire_descent", 0, 0, 27, test_rising_fire_fall },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + 12 + 4 + 12 + 6 + 4 + 28 + 27;
