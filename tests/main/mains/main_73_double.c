#include "test_runtime.h"
#include "main/mains/main_73_double.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
void double_face_player(struct MainObj*);
void double_spawn_afterimage(struct MainObj*, s8);

static u32 wall_left(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.collision_flags = 1;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 wall_right(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.collision_flags = 2;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 player_right(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 100;
    g_Player.x_pos.i.hi = 101;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 player_level(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 100;
    g_Player.x_pos.i.hi = 100;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}
static const CTestCase double_cases[] = {
    wall_left,
    wall_right,
    player_right,
    player_level,
};
static const u32 double_cases_expected[] = { 0x0u, 0x40u, 0x40u, 0x0u };

static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct EffectObj linked, linked_before, pool_expected[32];
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&linked, 0, sizeof(linked));
    memset(effect_objects, 0, sizeof(effect_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i == 31 && (mode == 0 || mode == 8) ? 0 : 1;
        effect_objects[i].id = 39;
        effect_objects[i].state = 40;
        effect_objects[i].unk2 = 9;
        effect_objects[i].unk5 = 3;
        effect_objects[i].unk6 = 4;
    }
    linked.active = mode == 3 ? 1 : 0;
    linked.id = 24;
    linked.state = 2;
    obj.active = 0x41;
    obj.id = 73;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk7 = 17;
    obj.unk6 = mode < 2 || mode == 8 ? 0 : mode < 4 ? 1
        : mode < 6                                  ? 2
        : mode == 6                                 ? -1
                                                    : 3;
    obj.unk7C = mode == 4 ? 1 : 2;
    obj.ext.main_73.unk80.effect = &linked;
    obj.hp = 127;
    obj.contact_damage = 7;
    obj.invincibility_timer = 3;
    obj.unk62 = 4;
    obj.unk63 = 5;
    obj.bg_offset = -1;
    obj.x_pos.val = (mode == 7 ? 1000 : 100) * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    g_Player.capsule_state = mode == 8 ? 1 : 0;
    g_Player.hp = 27;
    g_Player.script_state = 0;
    g_Player.script_action = 0;
    g_Player.script_facing = 0x22;
    g_Player.spike_immune = 0;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 0x33;
    engine_obj.boss_ptr = NULL;
    engine_obj.gameplay_locked = 0x77;
    expected = obj;
    linked_before = linked;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, effect_objects, sizeof(pool_expected));
    expected.on_screen = mode != 7;
    if (mode < 2) {
        if (mode == 0) {
            pool_expected[31].active = 1;
            pool_expected[31].id = 24;
            expected.ext.main_73.unk80.effect = &effect_objects[31];
        }
        expected.unk6 = 1;
        expected.unk7 = 0;
        player_expected.script_state = 1;
        player_expected.script_action = 0x14;
        player_expected.script_facing = 0x40;
        player_expected.spike_immune = 1;
        engine_expected.gameplay_locked = 1;
    } else if (mode == 2) {
        expected.contact_damage = 6;
        expected.invincibility_timer = -128;
        expected.unk6 = 2;
        expected.hp = 0;
        expected.unk62 = 0;
        expected.unk63 = 2;
        expected.unk7C = 0x20;
        engine_expected.enable_boss = 0;
        engine_expected.unk25 = 0;
        engine_expected.boss_ptr = &obj;
    } else if (mode == 4 || mode == 5) {
        expected.unk7C--;
        if (mode == 4) {
            expected.unk5 = 2;
            expected.unk6 = 0;
            expected.unk7 = 0;
        }
    }
    func_8008BB6C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_before)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    i = (u8)obj.unk6 | ((u32)(u16)obj.unk7C << 8) | ((u32)(u8)obj.hp << 24);
    return i;
}
static const u32 double_intro_effect_pool_defaults_cases_expected[] = { 0x7F000201u, 0x7F000201u, 0x2002u, 0x7F000201u, 0x7F000000u, 0x7F000102u, 0x7F0002FFu, 0x7F000203u, 0x7F000200u };

static const u32 double_death_blink_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 5u, 0u, 5u };
static u32 test_double_death_blink(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    FILL_ACTIVE(effect_objects, 32, 255 ? 1 : 0);
    double_death_blink(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.u.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.u.hi;
    observed_values[4] = (u32)obj.ext.main_73.blink_delay;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, double_death_blink_expected, 9);
}

#include "support/state_cases.h"

static s8 double_script[8];
#define AERIAL(n) state_reset(0, n, 0)
#define DEATH(n) state_reset(n, 0, 0)
static void d_shot_jump(void)
{
    AERIAL(0);
    double_aerial_shot(&so);
}
static void d_shot_fire(void)
{
    AERIAL(1);
    so.y_speed = -1;
    double_aerial_shot(&so);
}
static void d_shot_rise(void)
{
    AERIAL(1);
    so.y_speed = 0x10000;
    double_aerial_shot(&so);
}
static void d_shot_hang_again(void)
{
    AERIAL(2);
    so.y_pos.i.hi = 0x40;
    double_aerial_shot(&so);
}
static void d_shot_hang_last(void)
{
    AERIAL(2);
    so.ext.main_73.shot_count = 2;
    double_aerial_shot(&so);
}
static void d_shot_hang_wait(void)
{
    AERIAL(2);
    so.unk7C = 2;
    double_aerial_shot(&so);
}
static void d_shot_again_fire(void)
{
    AERIAL(3);
    so.unk7C = 1;
    double_aerial_shot(&so);
}
static void d_shot_again_climb(void)
{
    AERIAL(3);
    so.unk7C = 2;
    so.ext.main_73.effect.position.y = 0x40;
    so.y_speed = -0x50000;
    double_aerial_shot(&so);
}
static void d_shot_again_level(void)
{
    AERIAL(3);
    so.unk7C = 2;
    so.y_pos.i.hi = 0x40;
    double_aerial_shot(&so);
}
static void d_shot_third(void)
{
    AERIAL(4);
    so.unk7C = 1;
    double_aerial_shot(&so);
}
static void d_shot_third_wait(void)
{
    AERIAL(4);
    so.unk7C = 2;
    double_aerial_shot(&so);
}
static void d_shot_drop(void)
{
    AERIAL(5);
    so.unk7C = 1;
    double_aerial_shot(&so);
}
static void d_shot_drop_wait(void)
{
    AERIAL(5);
    so.unk7C = 2;
    double_aerial_shot(&so);
}
static void d_shot_land(void)
{
    AERIAL(6);
    so.collision_flags = 8;
    double_aerial_shot(&so);
}
static void d_shot_land_fall(void)
{
    AERIAL(6);
    double_aerial_shot(&so);
}
static void d_death_start_left(void)
{
    DEATH(0);
    so.x_pos.val = -0x10000;
    double_death(&so);
}
static void d_death_start_right(void)
{
    DEATH(0);
    double_death(&so);
}
static void d_death_fall_land(void)
{
    DEATH(1);
    so.collision_flags = 8;
    double_death(&so);
}
static void d_death_fall(void)
{
    DEATH(1);
    so.unk7C = 3;
    double_death(&so);
}
static void d_death_wait_done(void)
{
    DEATH(2);
    so.unk7E = 1;
    abc_object.unkC = 0x80;
    double_death(&so);
}
static void d_death_wait(void)
{
    DEATH(2);
    so.unk7E = 2;
    double_death(&so);
}
static void d_death_dialogue_done(void)
{
    DEATH(3);
    abc_object.unkC = 0;
    double_death(&so);
}
static void d_death_dialogue(void)
{
    DEATH(3);
    abc_object.unkC = 0x80;
    double_death(&so);
}
static void d_death_blink_spawn(void)
{
    DEATH(4);
    so.unk7C = 1;
    so.unk7E = 1;
    so.x_pos.u.hi = 0x50;
    double_death(&so);
}
static void d_death_blink(void)
{
    DEATH(4);
    so.unk7C = 2;
    so.ext.main_73.blink_delay = 0x19;
    double_death(&so);
}
static void d_death_blink_last(void)
{
    DEATH(4);
    so.unk7C = 2;
    so.ext.main_73.blink_delay = 3;
    double_death(&so);
}
static void d_death_exploding(void)
{
    DEATH(5);
    double_script[0] = 1;
    double_script[7] = 0;
    so.ext.main_73.unk80.script = double_script;
    double_death(&so);
}
static void d_death_exploding_hold(void)
{
    DEATH(5);
    double_script[0] = 1;
    double_script[7] = 1;
    so.ext.main_73.unk80.script = double_script;
    double_death(&so);
}
static void d_death_exploded(void)
{
    DEATH(5);
    double_script[0] = 0;
    so.ext.main_73.unk80.script = double_script;
    double_death(&so);
}
static void d_death_finish(void)
{
    DEATH(6);
    so.unk7C = 1;
    double_death(&so);
}
static void d_death_finish_wait(void)
{
    DEATH(6);
    so.unk7C = 2;
    double_death(&so);
}
static void d_afterimage(void)
{
    state_reset(0, 0, 0);
    so.x_pos.val = 0x123456;
    double_spawn_afterimage(&so, 2);
}

static void (*const double_states_cases[])(void) = {
    d_shot_jump,
    d_shot_fire,
    d_shot_rise,
    d_shot_hang_again,
    d_shot_hang_last,
    d_shot_hang_wait,
    d_shot_again_fire,
    d_shot_again_climb,
    d_shot_again_level,
    d_shot_third,
    d_shot_third_wait,
    d_shot_drop,
    d_shot_drop_wait,
    d_shot_land,
    d_shot_land_fall,
    d_death_start_left,
    d_death_start_right,
    d_death_fall_land,
    d_death_fall,
    d_death_wait_done,
    d_death_wait,
    d_death_dialogue_done,
    d_death_dialogue,
    d_death_blink_spawn,
    d_death_blink,
    d_death_blink_last,
    d_death_exploding,
    d_death_exploding_hold,
    d_death_exploded,
    d_death_finish,
    d_death_finish_wait,
    d_afterimage,
};
static const u32 double_states_expected[] = { 0x100u, 0u, 0u, 0u, 0x50000u, 0x420000u, 2u, 0u, 0u, 0u, 0x200u, 0x32u, 0u, 0u, 0xFFFFFFFFu, 0u, 9u, 0u, 0u, 0x410000u, 0x100u, 0u, 0u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x300u, 0x14u, 0u, 0u, 0u, 0x420000u, 2u, 0u, 0u, 0u, 0x500u, 0x1Eu, 0u, 0u, 0u, 0x420000u, 0xAu, 0u, 0u, 0u, 0x200u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0x32u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0x410000u, 0x300u, 1u, 0u, 0u, 0xFFFC0000u, 0u, 0u, 0u, 0u, 0u, 0x300u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0x5Au, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0x410000u, 0x400u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0x500u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x100010u, 0xFFFF0000u, 0u, 0u, 0x420000u, 0x400Bu, 0u, 0x1401u, 0u, 1u, 0x100010u, 0u, 0u, 0u, 0x420000u, 0xBu, 0u, 0x1401u, 0u, 2u, 0x3C0010u, 0u, 0u, 0u, 0u, 0x8000001Eu, 0u, 0u, 0u, 1u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0x10u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 2u, 0x10010u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 4u, 0x19u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0x10u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 5u, 0u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 4u, 0x140001u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 4u, 0x50001u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 5u, 0x50000u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 6u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x123456u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_double_states(u32 row)
{
    return state_run(double_states_cases[row], row, &double_states_expected[row * 10]);
}

extern void* double_animations[];
extern struct Unk_unk68 double_slide_hurt_box, double_slide_attack_box;
static u32 slide(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 right = row % 2, wall = row / 2 % 3, waiting = row / 6 % 2, face = row / 12;
    u32 direction_right = wall ? wall == 2 : right;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 73;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 5;
    obj.unk7C = waiting ? 2 : 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = -0x23456;
    obj.x_accel = 0x3456;
    obj.gravity = 0x4567;
    obj.animation_table = (const u8* const*)double_animations;
    set_animation(&obj, 6);
    assert(obj.animation_step.packed == 0x23010004);
    obj.collision_flags = wall;
    g_Player.hp = 30;
    g_Player.x_pos.val = obj.x_pos.val + (right ? 16 : -16) * 65536;
    g_Player.y_pos.val = obj.y_pos.val + 16 * 65536;
    player_before = g_Player;
    expected = obj;
    expected.unk7C--;
    if (waiting)
        expected.animation_step.fields.duration = 3;
    else {
        expected.unk6 = 6;
        expected.unk15 = direction_right ? 0x40 : 0;
        expected.x_speed = direction_right ? 0x80000 : -0x80000;
        expected.y_speed = expected.x_accel = expected.gravity = 0;
        expected.x_pos.val += expected.x_speed;
        expected.unk17 = 7;
        expected.previous_animation_index = 255;
        expected.animation_cursor = (const u8*)double_animations[7];
        expected.animation_step.packed = 0x25010002;
        expected.hurt_box = &double_slide_hurt_box;
        expected.attack_box = &double_slide_attack_box;
    }
    SP_CUR_MAIN_OBJ = &obj;
    func_8008C664(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

extern void* double_animations[31];
extern struct Unk_unk68 double_terrain_box, D_80108204[];
static const struct {
    u8 weapon, damage, blink, lethal;
    s8 kind, weapon_flag;
} inputs[] = {
    { 255, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, -1, -1 },
    { 7, 5, 0, 0, 0, 1 },
    { 16, 5, 0, 0, 0, 0 },
    { 18, 2, 0, 0, 0, 1 },
    { 20, 2, 0, 0, 0, 1 },
    { 22, 6, 0, 0, 0, 0 },
    { 7, 5, 0, 1, 0, 0 },
    { 58, 127, 0, 1, 0, 0 },
    { 0, 0, 1, 0, -1, -1 },
    { 0, 0, 2, 0, -1, -1 },
    { 0, 0, 3, 0, -1, -1 },
    { 56, 1, 1, 0, 0, 1 },
    { 57, 1, 2, 0, 0, 1 },
    { 255, 0, 64, 0, 0, 0 },
};
static const u8 free_slots[] = { 0, 1, 4 };
static struct ShotObj shots_expected[32];
static struct MiscObj misc_expected[64];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static u8 tilemap[256];
static u16 pixels[2][16][16];
static u32 attributes[1];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 weapon_blink(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 input = row % COUNT(inputs), phase = row / COUNT(inputs), free = free_slots[phase % 3], facing = phase % 2;
    u32 seed = phase / 2, i, retaliation = !inputs[input].blink && !inputs[input].lethal && inputs[input].weapon < 18 && inputs[input].kind == 0 && inputs[input].weapon != 255;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i < 32 - free;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        visual_objects[i].active = 1;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i < 64 - free;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
    }
    c_test_copy_words((u32*)shots_expected, (const u32*)shot_objects, sizeof(shots_expected) / 4);
    c_test_copy_words((u32*)misc_expected, (const u32*)misc_objects, sizeof(misc_expected) / 4);
    c_test_copy_words((u32*)visuals_before, (const u32*)visual_objects, sizeof(visuals_before) / 4);
    obj.active = 0x41;
    obj.id = 73;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk7 = 9;
    obj.on_screen = 7;
    obj.bg_offset = 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = 0x1234;
    obj.unk1C.val = 0x5678;
    obj.unk40 = 0x2345;
    obj.unk42 = 0x9234;
    obj.unk16 = 6;
    obj.hp = inputs[input].lethal ? 1 : 48;
    obj.attack_box = &double_attack_box;
    obj.hurt_box = &double_hurt_box;
    obj.terrain_box = &double_terrain_box;
    obj.collision_data = inputs[input].blink ? D_801060F0 : D_80108204;
    obj.ext.main_73.blink_delay = inputs[input].blink;
    obj.animation_table = (const u8* const*)double_animations;
    set_animation(&obj, 0);
    g_Player.hp = 24;
    g_Player.x_pos.val = (facing ? 200 : 120) * 65536;
    player_expected = g_Player;
    if (inputs[input].weapon != 255) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = inputs[input].weapon;
        weapon_objects[0].unk15 = facing ? 0x40 : 0;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)&double_hurt_box;
    }
    c_test_copy_words((u32*)weapons_expected, (const u32*)weapon_objects, sizeof(weapons_expected) / 4);
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk15 = facing ? 0x40 : 0;
    expected.unk6 = 1;
    expected.unk7 = 0;
    expected.unk7C = 60;
    expected.on_screen = 1;
    expected.unk42 = 0x1234;
    expected.unk17 = 1;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)double_animations[1];
    expected.animation_step.packed = 0x0C01000C;
    expected.unk6C = 0;
    expected.unk6E = 11;
    if (inputs[input].weapon != 255) {
        ((s16*)&weapons_expected[0].unk80)[0] = facing ? 157 : 163;
        ((s16*)&weapons_expected[0].unk80)[1] = 108;
        weapons_expected[0].unk98 = inputs[input].weapon_flag;
        expected.unk63 = inputs[input].kind;
        if (inputs[input].kind == 0) {
            expected.hp = inputs[input].lethal ? 0 : 48 - inputs[input].damage;
            expected.unk42 |= 0x8000;
        }
    }
    if (inputs[input].blink) {
        expected.ext.main_73.blink_delay--;
        if (inputs[input].blink == 1)
            expected.collision_data = D_80108204;
        if (expected.ext.main_73.blink_delay & 1)
            expected.unk42 |= 0x8000;
        else
            expected.unk42 &= 0x7FFF;
    } else if (inputs[input].lethal) {
        expected.state = 2;
        expected.unk5 = expected.unk6 = 0;
        expected.unk42 &= 0x7FFF;
        player_expected.spike_immune = 1;
    } else if (inputs[input].kind == 0 && inputs[input].weapon != 255) {
        expected.collision_data = D_801060F0;
        expected.ext.main_73.blink_delay = 64;
    }
    if (retaliation) {
        for (i = 0; i < free && i < 2; i++) {
            struct ShotObj* s = &shots_expected[32 - free + i];
            s->active = 0x41;
            s->id = seed ? 50 : 51;
            s->unk2 = i;
            s->unk7C = WEAPON_OBJECT(&obj);
            s->unk15 = expected.unk15;
            s->x_pos = obj.x_pos;
            s->y_pos = obj.y_pos;
            s->animation_table = (u32**)double_animations;
            s->unk40 = obj.unk40;
            s->unk42 = 0x1234;
            s->unk16 = 6;
        }
        for (i = 0; i < free; i++) {
            struct MiscObj* m = &misc_expected[64 - free + i];
            m->active = 0x41;
            m->id = 49;
            m->unk2 = i;
            m->x_pos = obj.x_pos;
            m->y_pos = obj.y_pos;
            m->animation_table = (u32**)double_animations;
            m->unk40 = obj.unk40;
            m->unk42 = 0x1234;
            m->unk16 = 6;
            m->ext.pointer.unk50 = &obj;
        }
    }
    D_8013E198[0] = D_8013E198[1] = D_8013E198[2] = D_8013E198[5] = -1;
    cur_random = seed ? 0x1235 : 0x1234;
    func_8008CD80(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(shot_objects, shots_expected);
    SAME(misc_objects, misc_expected);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == (retaliation ? seed ? 0x366B : 0x366A : seed ? 0x1235
                                                                      : 0x1234));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "double_states", 0, 0, COUNT(double_states_cases), test_double_states },
    { "double", double_cases, double_cases_expected, COUNT(double_cases), 0 },
    { "double_intro_effect_pool_defaults", NULL, double_intro_effect_pool_defaults_cases_expected, COUNT(double_intro_effect_pool_defaults_cases_expected), intro_case },
    { "double_death_blink", 0, 0, 1, test_double_death_blink },
    { "dive_slide_wall_facing_overrides_both_downward_aims", NULL, NULL, 24, slide },
    { "weapon_blink_retaliation_and_death", NULL, NULL, COUNT(inputs) * 4, weapon_blink },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_states_cases) + COUNT(double_cases) + COUNT(double_intro_effect_pool_defaults_cases_expected) + 1 + 24 + COUNT(inputs) * 4;
