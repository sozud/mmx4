#include "test_runtime.h"
#include "main/mains/main_10_dragonfly.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"

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
#define CASE(m)                                                \
    static u32 dragonfly_carry_cardinal_motion_carry_##m(void) \
    {                                                          \
        return carry_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) dragonfly_carry_cardinal_motion_carry_##m,
static const CTestCase dragonfly_carry_cardinal_motion_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 dragonfly_carry_cardinal_motion_cases_expected[] = { 0x620704u, 0x650704u, 0x620204u, 0x650204u, 0x640005u, 0x640005u, 0x640005u };
#undef CASE
#undef ENTRY

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
    u32 expected[5];
};
static const struct dragonfly_carry_rise_1_0_case dragonfly_carry_rise_1_0_cases[] = {
    { 0, 2, 1, 76, { 0x641234u, 0x645678u, 1u, 3u, 0x2F010001u } },
    { 64, 1, 10, 124, { 0x641234u, 0x645678u, 0xAu, 4u, 0x37010001u } },
};
static u32 test_dragonfly_carry_rise_1_0(u32 row)
{
    const struct dragonfly_carry_rise_1_0_case* c = &dragonfly_carry_rise_1_0_cases[row];
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
    observed_values[0] = (u32)obj.x_pos.val;
    observed_values[1] = (u32)obj.y_pos.val;
    observed_values[2] = (u32)obj.ext.main_10.timer;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
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

static const u32 dragonfly_hunt_close_0_expected[] = { 0xFEFFu, 0u, 0u };
static u32 test_dragonfly_hunt_close_0(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.main_10.turn_delay = 65280;
    obj.y_speed = -133955584;
    g_Player.y_pos.i.hi = 22831;
    obj.y_pos.i.hi = 5;
    dragonfly_hunt_close(&obj);
    observed_values[0] = (u32)obj.ext.main_10.turn_delay;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, dragonfly_hunt_close_0_expected, 3);
}

struct dragonfly_hunt_close_1_case {
    u32 obj_main_10_turn_delay, expected_main_10_turn_delay;
    u32 expected[3];
};
static const struct dragonfly_hunt_close_1_case dragonfly_hunt_close_1_cases[] = {
    { 0, 0, { 0u, 0x655678u, 0x1010001u } },
    { 1, 0, { 0u, 0x655678u, 0x1010001u } },
    { 16, 15, { 0xFu, 0x655678u, 0x1010001u } },
};
static u32 test_dragonfly_hunt_close_1(u32 row)
{
    const struct dragonfly_hunt_close_1_case* c = &dragonfly_hunt_close_1_cases[row];
    u32 observed_values[3];
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
    obj.unk6 = 3;
    obj.y_speed = -0x10000;
    obj.ext.main_10.turn_delay = c->obj_main_10_turn_delay;
    g_Player.x_pos.val = 0x00640000;
    g_Player.y_pos.val = 0x00960000;
    expected = obj;
    expected.y_pos.val = obj.y_pos.val - obj.y_speed;
    expected.ext.main_10.turn_delay = c->expected_main_10_turn_delay;
    expected.animation_cursor = obj.animation_cursor + 4;
    expected.animation_step.packed = 0x01010001;
    player_expected = g_Player;
    engine_before = engine_obj;
    dragonfly_hunt_close(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.ext.main_10.turn_delay;
    observed_values[1] = (u32)obj.y_pos.val;
    observed_values[2] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct dragonfly_init_case {
    u32 unk2;
    u32 expected[6];
};
static const struct dragonfly_init_case dragonfly_init_cases[] = {
    { 1, { 0x40u, 1u, 0u, 1u, 2u, 0x10001u } },
    { 2, { 0u, 1u, 0u, 1u, 2u, 0x10001u } },
    { -1, { 0x20u, 0u, 7u, 8u, 2u, 0x10001u } },
};
static u32 test_dragonfly_init(u32 row)
{
    const struct dragonfly_init_case* c = &dragonfly_init_cases[row];
    u32 observed_values[6];
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
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk7A;
    observed_values[2] = (u32)obj.ext.main_10.hold_state;
    observed_values[3] = (u32)obj.ext.main_10.can_grab;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 6);
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
    u32 expected[5];
};
static const struct func_80049E68_1_case func_80049E68_1_cases[] = {
    { 0, -65536, 1, 0, { 0u, 5u, 0u, 0u, 0x20000u } },
    { 64, 65536, 1, 0, { 0u, 5u, 0u, 0u, 0x20000u } },
    { 0, -65536, 2, 1, { 1u, 3u, 1u, 0xFFFF0000u, 0xFFFF0000u } },
    { 64, 65536, 0, 4294967295, { 0xFFFFFFFFu, 3u, 1u, 0x10000u, 0xFFFF0000u } },
};
static u32 test_func_80049E68_1(u32 row)
{
    const struct func_80049E68_1_case* c = &func_80049E68_1_cases[row];
    u32 observed_values[5];
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
    observed_values[0] = (u32)obj.ext.main_10.timer;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct func_8004A178_case {
    u32 unk15, obj_x_pos, g_Player_x_pos, hold_state, stun_timer;
    u32 expected[10];
};
static const struct func_8004A178_case func_8004A178_cases[] = {
    { 255, -524288, -2, 0, 0, { 0u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x20000u } },
    { 0, 0, 0, 1, -1, { 0xFFFFFFFFu, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x20000u } },
};
static u32 test_func_8004A178(u32 row)
{
    const struct func_8004A178_case* c = &func_8004A178_cases[row];
    u32 observed_values[10];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk15 = c->unk15;
    obj.x_pos.val = c->obj_x_pos;
    g_Player.x_pos.val = c->g_Player_x_pos;
    obj.ext.main_10.hold_state = c->hold_state;
    g_Player.stun_timer = c->stun_timer;
    obj.x_pos.i.hi = 0;
    func_8004A178(&obj);
    observed_values[0] = (u32)obj.ext.main_10.timer;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk62;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.y_pos.i.hi;
    observed_values[8] = (u32)obj.y_pos.val;
    observed_values[9] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

const struct CTestGroup c_test_groups[] = {
    { "dragonfly_carry_cardinal_motion", dragonfly_carry_cardinal_motion_cases, dragonfly_carry_cardinal_motion_cases_expected, COUNT(dragonfly_carry_cardinal_motion_cases), 0 },
    { "dragonfly_carry_rise_0", 0, 0, 2, test_dragonfly_carry_rise_0 },
    { "dragonfly_carry_rise_1", 0, 0, 3, test_dragonfly_carry_rise_1 },
    { "dragonfly_carry_squeeze", 0, 0, 2, test_dragonfly_carry_squeeze },
    { "dragonfly_hunt_close_0", 0, 0, 1, test_dragonfly_hunt_close_0 },
    { "dragonfly_hunt_close_1", 0, 0, 3, test_dragonfly_hunt_close_1 },
    { "dragonfly_init", 0, 0, 3, test_dragonfly_init },
    { "func_80049E68_0", 0, 0, 1, test_func_80049E68_0 },
    { "func_80049E68_1", 0, 0, 4, test_func_80049E68_1 },
    { "func_8004A178", 0, 0, 2, test_func_8004A178 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragonfly_carry_cardinal_motion_cases) + 2 + 3 + 2 + 1 + 3 + 3 + 1 + 4 + 2;
