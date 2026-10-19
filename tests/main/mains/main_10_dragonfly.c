#include "test_runtime.h"
#include "main/mains/main_10_dragonfly.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void dragonfly_resume_step(struct MainObj* arg0);

static u32 carry_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u32 i, actual, right = mode == 1 || mode == 3 || mode == 6;
    u32 moving = mode < 4;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 7;
    obj.unk15 = right ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.unk62 = 7;
    obj.attack_box = (const u8*)&obj;
    obj.ext.main_10.timer = mode == 4 ? 1 : 2;
    obj.ext.main_10.hold_state = mode == 6 ? 1 : 0;
    obj.animation_table = (const u8* const*)dragonfly_animations;
    set_animation(&obj, 0);
    g_Player.x_pos.val = (right || mode == 5 ? 132 : 68) * 65536 + 0x1234;
    g_Player.y_pos.val = 144 * 65536 + 0x5678;
    g_Player.stun_timer = mode == 2 || mode == 3 || mode == 6 ? 1 : 0;
    player_before = g_Player;
    expected = obj;
    if (mode != 5)
        expected.ext.main_10.timer--;
    if (moving) {
        expected.x_speed = right ? 0x18000 : -0x18000;
        expected.y_speed = 0;
        expected.x_pos.val += expected.x_speed;
        if (mode == 2 || mode == 3) {
            expected.x_speed = 0;
            expected.unk6 = 2;
            expected.unk17 = 3;
            expected.animation_cursor = (const u8*)dragonfly_animations[3];
            expected.animation_step = *(const union AnimationStep*)dragonfly_animations[3];
        }
        expected.animation_cursor += 4;
        expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    } else {
        expected.y_speed = 0x20000;
        expected.x_speed = 0;
        expected.unk62 = 0;
        expected.attack_box = NULL;
        expected.unk5 = 5;
        expected.unk6 = 0;
    }
    func_8004A178(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
    return actual;
}
static const u32 dragonfly_carry_cardinal_motion_cases_expected[] = { 0x620704u, 0x650704u, 0x620204u, 0x650204u, 0x640005u, 0x640005u, 0x640005u };

struct dragonfly_carry_rise_0_case {
    u32 unk15, struggle, pressed_input, hi;
    u32 expected[7];
};
static const struct dragonfly_carry_rise_0_case dragonfly_carry_rise_0_cases[] = {
    { 0, 20, 1, 76, { 0x15u, 0x20000u, 5u, 0u, 0u, 0x4C1234u, 0x7C5678u } },
    { 64, 19, 17, 124, { 0x15u, 0x20000u, 5u, 0u, 0u, 0x7C1234u, 0x7C5678u } },
};
static u32 test_dragonfly_carry_rise_0(u32 row)
{
    const struct dragonfly_carry_rise_0_case* c = &dragonfly_carry_rise_0_cases[row];
    u32 observed_values[7];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    set_animation(&obj, 3);
    obj.unk5 = 4;
    obj.unk6 = 3;
    obj.unk15 = c->unk15;
    obj.unk62 = 3;
    obj.attack_box = dragonfly_grab_box;
    obj.y_speed = 0x18000;
    obj.ext.main_10.timer = 50;
    obj.ext.main_10.struggle = c->struggle;
    obj.unk7E = 2;
    g_Player.x_pos.val = 0x00321234;
    g_Player.y_pos.val = 0x00325678;
    g_Player.stun_timer = 120;
    g_Player.pressed_input = c->pressed_input;
    expected = obj;
    expected.ext.main_10.struggle = 21;
    expected.attack_box = NULL;
    expected.unk62 = 0;
    set_animation(&expected, 5);
    expected.y_speed = 0x20000;
    expected.unk5 = 5;
    expected.unk6 = 0;
    player_expected = g_Player;
    player_expected.x_pos.i.hi = c->hi;
    player_expected.y_pos.i.hi = 124;
    player_expected.stun_timer = 0;
    engine_before = engine_obj;
    dragonfly_carry_rise(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.ext.main_10.struggle;
    observed_values[1] = (u32)obj.y_speed;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)g_Player.stun_timer;
    observed_values[5] = (u32)g_Player.x_pos.val;
    observed_values[6] = (u32)g_Player.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct dragonfly_carry_rise_1_0_case {
    u32 unk15, obj_main_10_timer, expected_main_10_timer, hi;
};
static const struct dragonfly_carry_rise_1_0_case dragonfly_carry_rise_1_0_cases[] = {
    { 0, 2, 1, 76 },
    { 64, 1, 10, 124 },
};
static u32 test_dragonfly_carry_rise_1_0(u32 row)
{
    const struct dragonfly_carry_rise_1_0_case* c = &dragonfly_carry_rise_1_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 tiles[4], tiles_before[4];
    u16 pixels[512], pixels_before[512];
    u32 attrs[2], attrs_before[2];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    set_animation(&obj, 3);
    obj.unk5 = 4;
    obj.unk6 = 3;
    obj.unk15 = c->unk15;
    obj.attack_box = dragonfly_grab_box;
    obj.unk62 = 3;
    obj.x_speed = 0x8000;
    obj.y_speed = 0x18000;
    obj.ext.main_10.struggle = 20;
    obj.ext.main_10.timer = c->obj_main_10_timer;
    g_Player.x_pos.val = 0x00321234;
    g_Player.y_pos.val = 0x00325678;
    g_Player.pressed_input = 0;
    g_Player.stun_timer = 120;
    memset(pixels, 0, sizeof(pixels));
    pixels[356] = 1;
    attrs[0] = 0;
    attrs[1] = 36;
    tiles[0] = 1;
    tiles[1] = 0;
    tiles[2] = 0;
    tiles[3] = 0;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    expected = obj;
    expected.animation_cursor = obj.animation_cursor + 4;
    expected.animation_step.packed = 0x2F010001;
    expected.ext.main_10.timer = c->expected_main_10_timer;
    if (obj.ext.main_10.timer == 1) {
        set_animation(&expected, 4);
    }
    if (obj.ext.main_10.timer == 1) {
        expected.y_speed = 0;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk7E = 1;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk6 = 4;
    }
    expected.x_pos.val = 6558260;
    expected.y_pos.val = 6575736;
    player_expected = g_Player;
    player_expected.x_pos.i.hi = c->hi;
    player_expected.y_pos.i.hi = 124;
    engine_before = engine_obj;
    memcpy(pixels_before, pixels, sizeof(pixels_before));
    memcpy(attrs_before, attrs, sizeof(attrs_before));
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    assert(dragonfly_tile_above(&obj) == 36);
    dragonfly_carry_rise(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(pixels, pixels_before, sizeof(pixels));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    return 1;
}
static const u32 dragonfly_carry_rise_1_1_expected[] = { 0x649234u, 0x62D678u, 1u, 3u, 0x2F010001u };
static u32 test_dragonfly_carry_rise_1_1(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 tiles[4], tiles_before[4];
    u16 pixels[512], pixels_before[512];
    u32 attrs[2], attrs_before[2];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    set_animation(&obj, 3);
    obj.unk5 = 4;
    obj.unk6 = 3;
    obj.unk15 = 64;
    obj.attack_box = dragonfly_grab_box;
    obj.unk62 = 3;
    obj.x_speed = 0x8000;
    obj.y_speed = 0x18000;
    obj.ext.main_10.struggle = 20;
    obj.ext.main_10.timer = 2;
    g_Player.x_pos.val = 0x00321234;
    g_Player.y_pos.val = 0x00325678;
    g_Player.pressed_input = 0;
    g_Player.stun_timer = 120;
    memset(pixels, 0, sizeof(pixels));
    pixels[356] = 1;
    attrs[0] = 0;
    attrs[1] = 0;
    tiles[0] = 1;
    tiles[1] = 0;
    tiles[2] = 0;
    tiles[3] = 0;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    expected = obj;
    expected.animation_cursor = obj.animation_cursor + 4;
    expected.animation_step.packed = 0x2F010001;
    expected.ext.main_10.timer = 1;
    if (obj.ext.main_10.timer == 1) {
        set_animation(&expected, 4);
    }
    if (obj.ext.main_10.timer == 1) {
        expected.y_speed = 0;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk7E = 1;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk6 = 4;
    }
    expected.x_pos.val = 6591028;
    expected.y_pos.val = 6477432;
    player_expected = g_Player;
    player_expected.x_pos.i.hi = 124;
    player_expected.y_pos.i.hi = 124;
    engine_before = engine_obj;
    memcpy(pixels_before, pixels, sizeof(pixels_before));
    memcpy(attrs_before, attrs, sizeof(attrs_before));
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    assert(dragonfly_tile_above(&obj) == 0);
    dragonfly_carry_rise(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(pixels, pixels_before, sizeof(pixels));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    observed_values[0] = (u32)obj.x_pos.val;
    observed_values[1] = (u32)obj.y_pos.val;
    observed_values[2] = (u32)obj.ext.main_10.timer;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.animation_step.packed;
    return c_test_observe(1, row, observed_values, dragonfly_carry_rise_1_1_expected, 5);
}
static u32 test_dragonfly_carry_rise_1(u32 index)
{
    if (index < 2)
        return test_dragonfly_carry_rise_1_0(index);
    index -= 2;
    return test_dragonfly_carry_rise_1_1(index);
}

struct dragonfly_carry_squeeze_case {
    u32 unk15, struggle, pressed_input, hi;
    u32 expected[7];
};
static const struct dragonfly_carry_squeeze_case dragonfly_carry_squeeze_cases[] = {
    { 0, 20, 1, 76, { 0x15u, 0x20000u, 5u, 0u, 0u, 0x4C1234u, 0x7C5678u } },
    { 64, 19, 17, 124, { 0x15u, 0x20000u, 5u, 0u, 0u, 0x7C1234u, 0x7C5678u } },
};
static u32 test_dragonfly_carry_squeeze(u32 row)
{
    const struct dragonfly_carry_squeeze_case* c = &dragonfly_carry_squeeze_cases[row];
    u32 observed_values[7];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 sound[64], sound_before[64];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    set_animation(&obj, 3);
    obj.unk5 = 4;
    obj.unk6 = 4;
    obj.unk15 = c->unk15;
    obj.unk62 = 3;
    obj.attack_box = dragonfly_grab_box;
    obj.y_speed = 0x18000;
    obj.ext.main_10.timer = 50;
    obj.ext.main_10.struggle = c->struggle;
    obj.unk7E = 2;
    g_Player.x_pos.val = 0x00321234;
    g_Player.y_pos.val = 0x00325678;
    g_Player.stun_timer = 120;
    g_Player.pressed_input = c->pressed_input;
    memset(sound, 0, sizeof(sound));
    D_80141F50[2] = sound;
    expected = obj;
    expected.ext.main_10.struggle = 21;
    expected.attack_box = NULL;
    expected.unk62 = 0;
    set_animation(&expected, 5);
    expected.y_speed = 0x20000;
    expected.unk5 = 5;
    expected.unk6 = 0;
    player_expected = g_Player;
    player_expected.x_pos.i.hi = c->hi;
    player_expected.y_pos.i.hi = 124;
    player_expected.stun_timer = 0;
    engine_before = engine_obj;
    expected.unk7E = 1;
    memcpy(sound_before, sound, sizeof(sound_before));
    dragonfly_carry_squeeze(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(sound, sound_before, sizeof(sound));
    assert(D_80141F50[2] == sound);
    observed_values[0] = (u32)obj.ext.main_10.struggle;
    observed_values[1] = (u32)obj.y_speed;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)g_Player.stun_timer;
    observed_values[5] = (u32)g_Player.x_pos.val;
    observed_values[6] = (u32)g_Player.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct dragonfly_init_case {
    u32 unk2;
};
static const struct dragonfly_init_case dragonfly_init_cases[] = {
    { 1 },
    { 2 },
    { -1 },
};
static u32 test_dragonfly_init(u32 row)
{
    const struct dragonfly_init_case* c = &dragonfly_init_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    obj.unk2 = c->unk2;
    obj.state = 0;
    obj.unk15 = 0x20;
    obj.contact_damage = 5;
    obj.invincibility_timer = 3;
    obj.unk62 = 3;
    obj.ext.main_10.hold_state = 7;
    obj.ext.main_10.can_grab = 8;
    obj.ext.main_10.turn_delay = 9;
    obj.ext.main_10.struggle = 11;
    obj.ext.main_10.timer = 17;
    obj.ext.main_10.saved_unk5 = 6;
    g_Player.bg_offset = 1;
    expected = obj;
    expected.hp = 6;
    expected.contact_damage = 3;
    expected.invincibility_timer = 0;
    expected.collision_data = D_80106770;
    expected.bg_offset = 1;
    expected.unk16 = 6;
    expected.unk62 = 0;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk7C = 1;
    expected.state = 1;
    expected.ext.main_10.turn_delay = 0;
    expected.unk5 = 2;
    expected.unk6 = 0;
    if (obj.unk2 == 1) {
        expected.unk7A = 1;
    }
    if (obj.unk2 == 1) {
        expected.unk15 = 0x40;
    }
    if (obj.unk2 == 1) {
        expected.ext.main_10.hold_state = 0;
    }
    if (obj.unk2 == 1) {
        expected.ext.main_10.can_grab = 1;
    }
    if (obj.unk2 == 2) {
        expected.unk7A = 1;
    }
    if (obj.unk2 == 2) {
        expected.unk15 = 0;
    }
    if (obj.unk2 == 2) {
        expected.ext.main_10.hold_state = 0;
    }
    if (obj.unk2 == 2) {
        expected.ext.main_10.can_grab = 1;
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    assert(dragonfly_terrain_box.unk0 == -24 && dragonfly_terrain_box.unk1 == 3);
    dragonfly_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(dragonfly_terrain_box.unk0 == -24 && dragonfly_terrain_box.unk1 == 3);
    return 1;
}

static const u32 func_80049E68_0_expected[] = { 0x14u, 5u, 2u, 0u, 0u, 0x20000u };
static u32 test_func_80049E68_0(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.main_10.timer = 1;
    g_Player.x_pos.i.hi = 48;
    func_80049E68(&obj);
    observed_values[0] = (u32)obj.ext.main_10.timer;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk62;
    observed_values[4] = (u32)obj.x_speed;
    observed_values[5] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_80049E68_0_expected, 6);
}

struct func_80049E68_1_case {
    u32 unk15, x_speed, obj_main_10_timer, expected_main_10_timer;
};
static const struct func_80049E68_1_case func_80049E68_1_cases[] = {
    { 0, -65536, 1, 0 },
    { 64, 65536, 1, 0 },
    { 0, -65536, 2, 1 },
    { 64, 65536, 0, 4294967295 },
};
static u32 test_func_80049E68_1(u32 row)
{
    const struct func_80049E68_1_case* c = &func_80049E68_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = dragonfly_animations;
    obj.terrain_box = &dragonfly_terrain_box;
    obj.hurt_box = dragonfly_body_boxes;
    obj.attack_box = dragonfly_body_boxes;
    obj.unk42 = 0x1234;
    obj.hp = 7;
    set_animation(&obj, 0);
    obj.unk15 = c->unk15;
    obj.x_speed = c->x_speed;
    obj.y_speed = -0x10000;
    obj.ext.main_10.timer = c->obj_main_10_timer;
    obj.unk62 = 3;
    obj.attack_box = dragonfly_grab_box;
    g_Player.x_pos.val = 0x00640000;
    expected = obj;
    expected.x_pos.val = obj.x_pos.val + obj.x_speed;
    expected.y_pos.val = obj.y_pos.val - obj.y_speed;
    expected.animation_cursor = obj.animation_cursor + 4;
    expected.animation_step.packed = 0x01010001;
    expected.ext.main_10.timer = c->expected_main_10_timer;
    if (obj.ext.main_10.timer == 1) {
        expected.y_speed = 0x20000;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.x_speed = 0;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk62 = 0;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.attack_box = NULL;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk5 = 5;
    }
    if (obj.ext.main_10.timer == 1) {
        expected.unk6 = 0;
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    func_80049E68(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

static void df_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_10.saved_unk5 = 3;
    dragonfly_resume_step(&so);
}

static void (*const dragonfly_misc_cases[])(void) = {
    df_resume,
};
static const u32 dragonfly_misc_expected[] = { 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_dragonfly_misc(u32 row)
{
    return state_run(dragonfly_misc_cases[row], row, &dragonfly_misc_expected[row * 10]);
}

void dragonfly_hunt(struct MainObj* arg0);
void dragonfly_wait(struct MainObj* arg0);

static struct MainObj obj, expected;
static struct PlayerObj player_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_before[16];
static struct VisualObj visuals_before[32];
static u16 expected_random;
static const s16 cameras[3][2] = { { 0, 0 }, { 1024, 512 }, { -320, -240 } };

static void prepare(u32 subtype, u32 facing, u32 layer)
{
    u32 i;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i][0] * 65536;
        background_objects[i].y_pos.val = cameras[i][1] * 65536;
    }
    obj.active = 0x41;
    obj.id = 10;
    obj.unk2 = subtype;
    obj.unk15 = facing ? 0x40 : 0;
    obj.bg_offset = 2;
    obj.x_pos.val = (cameras[layer][0] + 160) * 65536 + 0x1234;
    obj.y_pos.val = (cameras[layer][1] + 120) * 65536 + 0x5678;
    obj.unk42 = 0x9234;
    obj.unk40 = 0x4567;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.bg_offset = layer;
    g_Player.x_pos.val = obj.x_pos.val - 65536;
    g_Player.y_pos.val = obj.y_pos.val + 24 * 65536;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    cur_random = expected_random = 0x1234;
    need_palette_load = 0x20;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)visuals_before, (const u32*)visual_objects, sizeof(visuals_before) / 4);
}

static void check(void)
{
    u32 i;
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects, (const u32*)weapons_before, sizeof(weapons_before) / 4) == 0);
    assert(c_test_word_difference((const u32*)visual_objects, (const u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    assert(cur_random == expected_random && need_palette_load == 0x20);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static void expect_animation(u32 animation, u32 frame)
{
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = dragonfly_animations[animation] + 4 * frame;
    memcpy(&expected.animation_step, expected.animation_cursor, sizeof(expected.animation_step));
}

static void expect_init(void)
{
    u32 subtype = expected.unk2;
    expected.hp = 6;
    expected.contact_damage = 3;
    expected.invincibility_timer = 0;
    expected.collision_data = D_80106770;
    expected.bg_offset = g_Player.bg_offset;
    expected.unk16 = 6;
    expected.animation_table = dragonfly_animations;
    expected.terrain_box = &dragonfly_terrain_box;
    expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
    expected.air_state = 0;
    expected.hurt_box = expected.attack_box = dragonfly_body_boxes;
    expected.unk62 = 0;
    expected.unk18 = expected.x_pos;
    expected.unk1C = expected.y_pos;
    expect_animation(0, 0);
    expected.ext.main_10.hold_state = subtype == 0;
    expected.ext.main_10.can_grab = subtype < 3;
    if (subtype == 0)
        expected.unk15 = expected.x_pos.val > g_Player.x_pos.val ? 0 : 0x40;
    else {
        expected.unk7A = 1;
        if (subtype < 3)
            expected.unk15 = subtype == 1 ? 0x40 : 0;
        if (subtype == 5 || subtype == 6 || subtype == 11 || subtype == 12)
            expected.gravity = -0x600;
        if (subtype == 7 || subtype == 8 || subtype == 13 || subtype == 14)
            expected.gravity = 0x600;
    }
    expected.unk7C = 1;
    expected.state = 1;
    expected.ext.main_10.turn_delay = 0;
    expected.unk5 = 2;
    expected.unk6 = 0;
}

static void initialize(void)
{
    capture();
    expect_init();
    dragonfly_update(&obj);
}

static u32 test_init(u32 row)
{
    u32 subtype = row % 15, facing = (row / 15) % 2;
    s32 relation = (s32)(row / 30) - 1;
    prepare(subtype, facing, subtype % 3);
    g_Player.x_pos.val = obj.x_pos.val + relation;
    initialize();
    check();
    return 1;
}

static const s16 distances[] = { -194, -193, -192, 0, 192, 193, 194 };
static u32 test_wait(u32 row)
{
    u32 subtype = row % 15, distance = (row / 15) % 7;
    u32 facing = (row / 105) % 2, fraction = row / 210;
    s32 dx = distances[distance];
    prepare(subtype, facing, subtype % 3);
    initialize();
    g_Player.x_pos.i.hi = obj.x_pos.i.hi + dx;
    g_Player.x_pos.u.lo = fraction ? 0xFFFF : 0;
    capture();
    if (subtype == 0) {
        expected.unk7A = 0;
        expected.unk5 = 3;
    } else if (subtype >= 9 || (subtype == 2 ? dx <= -193 : dx >= 193)) {
        expected.unk7A = 0;
        expected.ext.main_10.hold_state = 1;
        expected.unk5 = subtype < 3 ? 3 : 6;
        if (subtype >= 3) {
            expected.unk15 = subtype >= 9 ? 0 : 0x40;
            expected.x_speed = (subtype >= 9 ? -1 : 1) * (subtype % 2 ? 6 : 8) * 65536;
        }
    }
    dragonfly_wait(&obj);
    check();
    return 1;
}

static void expect_face(void)
{
    u32 face = expected.unk15;
    if (g_Player.x_pos.val > expected.x_pos.val)
        face = 0x40;
    if (g_Player.x_pos.val < expected.x_pos.val)
        face = 0;
    if (face != (u8)expected.unk15) {
        expected.unk15 = face;
        expected.ext.main_10.turn_delay = 16;
    }
}

static const s32 delays[] = { 0, 1, 16 };
static const s32 timers[] = { 1, 2, 180 };
static const u16 seeds[] = { 0, 1, 0x1234, 0x1235 };
static const u16 next_seeds[] = { 0, 1, 0x366A, 0x366B };
static u32 test_hover(u32 row)
{
    u32 x = row % 3, delay = (row / 3) % 3, timer = (row / 9) % 3, y = row / 27;
    u32 facing = (x + delay + timer + y) % 2, seed = (timer + x) % 4;
    prepare(0, facing, y);
    initialize();
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.ext.main_10.turn_delay = delays[delay];
    obj.ext.main_10.timer = timers[timer];
    obj.x_speed = facing ? 0x40000 : -0x40000;
    g_Player.x_pos.val = obj.x_pos.val + (s32)x - 1;
    g_Player.y_pos.i.hi = obj.y_pos.i.hi + 24 + (s32)y - 1;
    cur_random = expected_random = seeds[seed];
    capture();
    if (expected.ext.main_10.turn_delay)
        expected.ext.main_10.turn_delay--;
    else
        expect_face();
    expected.ext.main_10.timer--;
    if (timers[timer] == 1) {
        expected_random = next_seeds[seed];
        if (expected_random & 1) {
            expect_face();
            expect_animation(1, 0);
            expected.unk5 = 4;
            expected.unk6 = 0;
        } else {
            expected.y_speed = y == 0 ? 0x30000 : -0x30000;
            expected.unk6 = 3;
        }
    }
    if (!(timers[timer] == 1 && (expected_random & 1)))
        expect_animation(0, 1);
    dragonfly_hunt(&obj);
    check();
    return 1;
}

static u32 test_close(u32 row)
{
    u32 facing = row % 2, rising = (row / 2) % 2, x = (row / 4) % 3;
    u32 y = (row / 12) % 3, delay = (row / 36) % 3, place = row / 108;
    s32 px = place ? -512 : 512, py = place ? -256 : 256;
    u32 transition;
    prepare(0, facing, place);
    initialize();
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk5 = 3;
    obj.unk6 = 3;
    obj.ext.main_10.turn_delay = delays[delay];
    obj.x_speed = facing ? 0x40000 : -0x40000;
    obj.y_speed = rising ? 0x30000 : -0x30000;
    obj.x_pos.val = (px - 25 + (s32)x) * 65536 + 0x1234 - obj.x_speed;
    obj.y_pos.val = (py - 25 + (s32)y) * 65536 + 0x5678 + obj.y_speed;
    g_Player.x_pos.val = px * 65536 + 0x9876;
    g_Player.y_pos.val = py * 65536 + 0x4321;
    capture();
    expected.x_pos.val += expected.x_speed;
    expected.y_pos.val -= expected.y_speed;
    if (expected.ext.main_10.turn_delay)
        expected.ext.main_10.turn_delay--;
    else
        expect_face();
    transition = rising ? x == 0 : y == 2;
    if (transition) {
        expect_face();
        expected.unk5 = 4;
        expected.unk6 = 0;
    }
    expect_animation(transition ? 1 : 0, 1);
    dragonfly_hunt(&obj);
    check();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "dragonfly_misc", 0, 0, COUNT(dragonfly_misc_cases), test_dragonfly_misc },
    { "dragonfly_carry_cardinal_motion", NULL, dragonfly_carry_cardinal_motion_cases_expected, COUNT(dragonfly_carry_cardinal_motion_cases_expected), carry_case },
    { "dragonfly_carry_rise_0", 0, 0, 2, test_dragonfly_carry_rise_0 },
    { "dragonfly_carry_rise_1", 0, 0, 3, test_dragonfly_carry_rise_1 },
    { "dragonfly_carry_squeeze", 0, 0, 2, test_dragonfly_carry_squeeze },
    { "dragonfly_init", 0, 0, 3, test_dragonfly_init },
    { "func_80049E68_0", 0, 0, 1, test_func_80049E68_0 },
    { "func_80049E68_1", 0, 0, 4, test_func_80049E68_1 },
    { "dragonfly_init_subtypes", 0, 0, 45, test_init },
    { "dragonfly_wait_boundaries", 0, 0, 90, test_wait },
    { "dragonfly_hover_decisions", 0, 0, 30, test_hover },
    { "dragonfly_close_boundaries", 0, 0, 38, test_close },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragonfly_misc_cases) + COUNT(dragonfly_carry_cardinal_motion_cases_expected) + 2 + 3 + 2 + 3 + 1 + 4 + 45 + 90 + 30 + 38;
