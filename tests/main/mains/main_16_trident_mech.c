#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_16_trident_mech.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/weapons/weapon_24_zero_saber.h"
void trident_mech_charge_attack(struct MainObj*);
extern union AnimationStep* trident_mech_animations[29];
extern struct Unk_unk68 D_800FBBC8;
extern struct Unk_unk68 D_80106A74[];
extern struct Misc01AnimationStep* common_effect_animations[8];
void trident_mech_fire_tracked_shot(struct MainObj*);

static void spawn(struct MainObj* obj)
{
    memset(obj, 0, sizeof(*obj));
    obj->active = 0x41;
    obj->id = 16;
    obj->state = 1;
    obj->unk5 = 8;
    obj->unk6 = 1;
    obj->x_pos.val = 0x00641234;
    obj->y_pos.val = 0x00645678;
    obj->hp = 16;
    obj->contact_damage = 3;
    obj->unk40 = 0x56;
    obj->unk42 = 0x1234;
    obj->animation_table = (const u8* const*)trident_mech_animations;
    obj->terrain_box = &D_800FBBC8;
    obj->hurt_box = &trident_mech_stunned_hurt_box;
    obj->attack_box = &trident_mech_attack_box;
    obj->collision_data = (const u16*)D_80106A74;
    set_animation(obj, 1);
    obj->air_state = 1;
    obj->unk42 = 0x9234;
}

struct func_8004E8E0_case {
    u32 unk2, g_Player_bg_offset, x_pos, expected_bg_offset, unk15;
};
static const struct func_8004E8E0_case func_8004E8E0_cases[] = {
    { -1, 1, 6492724, 1, 0 },
    { 6, 2, 6623796, 2, 64 },
};
static u32 test_func_8004E8E0(u32 row)
{
    const struct func_8004E8E0_case* c = &func_8004E8E0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    spawn(&obj);
    obj.state = 0;
    obj.unk2 = c->unk2;
    obj.unk5 = 8;
    obj.unk6 = 3;
    obj.unk7 = 1;
    obj.ext.main_16.unk88 = 0x55;
    g_Player.bg_offset = c->g_Player_bg_offset;
    g_Player.x_pos.val = c->x_pos;
    expected = obj;
    expected.unk16 = VISUAL_SATURN_LAYER(6);
    expected.air_state = 0;
    expected.bg_offset = c->expected_bg_offset;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk15 = TEST_FACING(c->unk15);
    expected.ext.main_16.shot_09_active = 1;
    expected.state = 1;
    expected.unk6 = 0;
    expected.unk7 = 0;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004E8E0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct func_8004ED60_0_case {
    u32 active, x_pos, cur_random, unk15, unk80;
    u32 expected[5];
};
static const struct func_8004ED60_0_case func_8004ED60_0_cases[] = {
    { 0, 12849716, 5, 64, 1, { 4u, 1u, 0u, 0x40u, 5u } },
    { 1, 12915252, 12, 64, 1, { 4u, 1u, 0u, 0x40u, 0xCu } },
    { 0, 12915252, 12, 64, 1, { 4u, 1u, 0u, 0x40u, 0xCu } },
    { 1, 201268, 11, 0, 0, { 4u, 0u, 0u, 0u, 0xBu } },
};
static u32 test_func_8004ED60_0(u32 row)
{
    const struct func_8004ED60_0_case* c = &func_8004ED60_0_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct ShotObj shots_before[32];
    spawn(&obj);
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.ext.main_16.unk80 = 0x55;
    obj.ext.main_16.unk8C = 2;
    obj.ext.main_16.unk90 = 0xA5;
    set_animation(&obj, 0);
    FILL_ACTIVE(shot_objects, 32, 1);
    FILL_ACTIVE(weapon_objects, 16, 0);
    weapon_objects[0].active = c->active;
    g_Player.x_pos.val = c->x_pos;
    engine_obj.cur_character = 1;
    cur_random = c->cur_random;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk15 = TEST_FACING(c->unk15);
    expected.unk7C = 0;
    expected.unk6 = 0;
    expected.unk5 = 4;
    expected.ext.main_16.unk80 = c->unk80;
    expected.ext.main_16.unk90 = 1;
    expected.ext.main_16.unk8C = 0;
    expected.invincibility_timer = 0;
    expected.animation_step.fields.duration = 6;
    set_animation(&expected, 16);
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004ED60(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.ext.main_16.unk80;
    observed_values[2] = (u32)obj.ext.main_16.unk8C;
    observed_values[3] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[4] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}
struct func_8004ED60_1_case {
    u32 x_pos, cur_random;
    u32 expected[5];
};
static const struct func_8004ED60_1_case func_8004ED60_1_cases[] = {
    { 12915252, 14, { 6u, 0x55u, 1u, 0x40u, 0xEu } },
    { 12849716, 5, { 6u, 0x55u, 1u, 0x40u, 5u } },
};
static u32 test_func_8004ED60_1(u32 row)
{
    const struct func_8004ED60_1_case* c = &func_8004ED60_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct ShotObj shots_before[32];
    spawn(&obj);
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.ext.main_16.unk80 = 0x55;
    obj.ext.main_16.unk8C = 2;
    obj.ext.main_16.unk90 = 0xA5;
    set_animation(&obj, 0);
    FILL_ACTIVE(shot_objects, 32, 1);
    FILL_ACTIVE(weapon_objects, 16, 0);
    weapon_objects[0].active = 1;
    g_Player.x_pos.val = c->x_pos;
    engine_obj.cur_character = 1;
    cur_random = c->cur_random;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk15 = PLAYER_FACING_RIGHT;
    expected.unk7C = 0;
    expected.unk6 = 0;
    expected.unk5 = 6;
    expected.ext.main_16.unk80 = 85;
    expected.ext.main_16.unk90 = 165;
    expected.ext.main_16.unk8C = 1;
    expected.invincibility_timer = 1;
    expected.animation_step.fields.duration = 6;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004ED60(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.ext.main_16.unk80;
    observed_values[2] = (u32)obj.ext.main_16.unk8C;
    observed_values[3] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[4] = (u32)cur_random;
    return c_test_observe(1, row, observed_values, c->expected, 5);
}
static u32 test_func_8004ED60(u32 index)
{
    if (index < 4)
        return test_func_8004ED60_0(index);
    index -= 4;
    return test_func_8004ED60_1(index);
}

static struct Misc01AnimationStep;

struct func_8004FD38_case {
    u32 full;
    u32 expected[3];
};
static const struct func_8004FD38_case func_8004FD38_cases[] = {
    { 1, { 1u, 0u, 0u } },
    { 0, { 0x41u, 2u, 0x571234u } },
};
static u32 test_func_8004FD38(u32 row)
{
    const struct func_8004FD38_case* c = &func_8004FD38_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct MiscObj misc_expected[64];
    u8 tiles[4], tiles_before[4];
    u16 pixels[512], pixels_before[512];
    u32 attrs[2], attrs_before[2], resources[8], resources_before[8];
    s32 frames[16], frames_before[16];
    u8 pools_full, full;
    spawn(&obj);
    obj.air_state = 0;
    obj.unk15 = PLAYER_FACING_RIGHT;
    memset(tiles, 0, sizeof(tiles));
    memset(pixels, 0, sizeof(pixels));
    memset(frames, 0, sizeof(frames));
    memset(resources, 0, sizeof(resources));
    tiles[0] = 1;
    pixels[374] = 1;
    attrs[0] = 0;
    attrs[1] = C_TEST_PSX_WORD(0x24);
    frames[4] = 16;
    resources[4] = 0x2B00;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    TEST_MENU_FRAMES = (u8*)frames;
    test_stage_graphics(resources);
    layout_size = 1;
    layout_width = 1;
    assert(func_8002D724(PLAYER_OBJECT(&obj), 102, 124) == 0x24);
    FILL_ACTIVE(misc_objects, 64, 1);
    full = c->full;
    if (!full) {
        memset(&misc_objects[63], 0, sizeof(misc_objects[63]));
    }
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    if (!full) {
        misc_expected[63].active = 0x41;
    }
    if (!full) {
        misc_expected[63].id = 5;
    }
    if (!full) {
        misc_expected[63].animation_table = (u32**)common_effect_animations;
    }
    if (!full) {
        misc_expected[63].unk40 = OBJECT_STAGE_TEXTURE(4);
    }
    if (!full) {
        misc_expected[63].unk42 = OBJECT_CLUT(0x7888);
    }
    if (!full) {
        misc_expected[63].unk3C = (u8*)frames + 16;
    }
    if (!full) {
        misc_expected[63].bg_offset = obj.bg_offset;
    }
    if (!full) {
        misc_expected[63].y_pos.val = obj.y_pos.val + 0x60000;
    }
    if (!full) {
        misc_expected[63].x_pos.val = obj.x_pos.val - 0xD0000;
    }
    if (!full) {
        misc_expected[63].unk15 = obj.unk15;
    }
    if (!full) {
        misc_expected[63].unk2 = 1;
    }
    if (!full) {
        misc_expected[63].ext.misc_5.owner = &obj;
    }
    if (!full) {
        misc_expected[63].ext.misc_5.animation = 2;
    }
    if (!full) {
        misc_expected[63].state = 3;
    }
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memcpy(pixels_before, pixels, sizeof(pixels_before));
    memcpy(attrs_before, attrs, sizeof(attrs_before));
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(resources_before, resources, sizeof(resources_before));
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004FD38(&obj, 2);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(pixels, pixels_before, sizeof(pixels));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(resources, resources_before, sizeof(resources));
    observed_values[0] = (u32)misc_objects[63].active;
    observed_values[1] = (u32)misc_objects[63].ext.misc_5.animation;
    observed_values[2] = (u32)misc_objects[63].x_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct trident_mech_double_shot_first_0_case {
    u32 full;
};
static const struct trident_mech_double_shot_first_0_case trident_mech_double_shot_first_0_cases[] = {
    { 1 },
    { 0 },
};
static u32 test_trident_mech_double_shot_first_0(u32 row)
{
    const struct trident_mech_double_shot_first_0_case* c = &trident_mech_double_shot_first_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    spawn(&obj);
    obj.unk6 = 0;
    obj.unk15 = 0;
    set_animation(&obj, 17);
    obj.animation_cursor = (const u8*)&trident_mech_animations[17][3];
    obj.animation_step = trident_mech_animations[17][3];
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 9;
    }
    if (!full) {
        shots_expected[31].unk2 = 3;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full) {
        shots_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        shots_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].state = 3;
    }
    if (!full) {
        shots_expected[31].x_vel.val = -65536;
    }
    expected = obj;
    set_animation(&expected, 18);
    expected.unk6 = 1;
    expected.unk7C = 20;
    expected.unk15 = 0;
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_double_shot_first(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    assert(D_8013E198[2] == -1);
    return 1;
}
struct trident_mech_double_shot_first_1_case {
    u32 full;
    u32 expected[4];
};
static const struct trident_mech_double_shot_first_1_case trident_mech_double_shot_first_1_cases[] = {
    { 1, { 1u, 0x14u, 1u, 0u } },
    { 0, { 1u, 0x14u, 0x41u, 0x10000u } },
};
static u32 test_trident_mech_double_shot_first_1(u32 row)
{
    const struct trident_mech_double_shot_first_1_case* c = &trident_mech_double_shot_first_1_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    spawn(&obj);
    obj.unk6 = 0;
    obj.unk15 = PLAYER_FACING_RIGHT;
    set_animation(&obj, 17);
    obj.animation_cursor = (const u8*)&trident_mech_animations[17][3];
    obj.animation_step = trident_mech_animations[17][3];
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 9;
    }
    if (!full) {
        shots_expected[31].unk2 = 3;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full) {
        shots_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        shots_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].state = 3;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 65536;
    }
    expected = obj;
    set_animation(&expected, 18);
    expected.unk6 = 1;
    expected.unk7C = 20;
    expected.unk15 = PLAYER_FACING_RIGHT;
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_double_shot_first(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)shot_objects[31].active;
    observed_values[3] = (u32)shot_objects[31].x_vel.val;
    return c_test_observe(1, row, observed_values, c->expected, 4);
}
static u32 test_trident_mech_double_shot_first(u32 index)
{
    if (index < 2)
        return test_trident_mech_double_shot_first_0(index);
    index -= 2;
    return test_trident_mech_double_shot_first_1(index);
}

struct trident_mech_double_shot_second_case {
    u32 unk2, full, unk7C, unk15;
};
static const struct trident_mech_double_shot_second_case trident_mech_double_shot_second_cases[] = {
    { 3, 1, 20, 64 },
    { 4, 1, 60, 0 },
    { 3, 0, 20, 64 },
    { 4, 0, 60, 0 },
};
static u32 test_trident_mech_double_shot_second(u32 row)
{
    const struct trident_mech_double_shot_second_case* c = &trident_mech_double_shot_second_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    spawn(&obj);
    obj.unk2 = c->unk2;
    obj.unk6 = 1;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.unk7C = 1;
    set_animation(&obj, 18);
    g_Player.x_pos.i.hi = 0;
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 9;
    }
    if (!full) {
        shots_expected[31].unk2 = 4;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full) {
        shots_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        shots_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].state = 3;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 65536;
    }
    expected = obj;
    set_animation(&expected, 19);
    expected.unk6 = 2;
    expected.unk7C = c->unk7C;
    expected.unk15 = TEST_FACING(c->unk15);
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_double_shot_second(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    assert(D_8013E198[2] == -1);
    return 1;
}

struct trident_mech_fan_shot_fire_case {
    u32 full;
};
static const struct trident_mech_fan_shot_fire_case trident_mech_fan_shot_fire_cases[] = {
    { 1 },
    { 0 },
};
static u32 test_trident_mech_fan_shot_fire(u32 row)
{
    const struct trident_mech_fan_shot_fire_case* c = &trident_mech_fan_shot_fire_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    spawn(&obj);
    obj.unk5 = 7;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.ext.main_16.unk80 = 24;
    obj.ext.main_16.unk84 = -4;
    set_animation(&obj, 7);
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 9;
    }
    if (!full) {
        shots_expected[31].unk2 = 0;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full) {
        shots_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        shots_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].state = 3;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 0;
    }
    if (!full) {
        shots_expected[31].y_vel.val = -65536;
    }
    expected = obj;
    expected.animation_cursor = (const u8*)&trident_mech_animations[7][1];
    expected.animation_step = trident_mech_animations[7][1];
    expected.unk7C = 8;
    expected.ext.main_16.unk80 = 20;
    expected.ext.main_16.unk88 = 1;
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_fan_shot_fire(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    assert(D_8013E198[2] == -1);
    return 1;
}

struct trident_mech_fan_shot_start_case {
    u32 unk15, unk84;
};
static const struct trident_mech_fan_shot_start_case trident_mech_fan_shot_start_cases[] = {
    { 0, -4 },
    { 64, 4 },
};
static u32 test_trident_mech_fan_shot_start(u32 row)
{
    const struct trident_mech_fan_shot_start_case* c = &trident_mech_fan_shot_start_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    spawn(&obj);
    obj.unk5 = 7;
    obj.unk6 = 0;
    obj.unk15 = TEST_FACING(c->unk15);
    set_animation(&obj, 6);
    obj.animation_cursor = (const u8*)&trident_mech_animations[6][1];
    obj.animation_step = trident_mech_animations[6][1];
    expected = obj;
    set_animation(&expected, 7);
    expected.unk6 = 1;
    expected.unk7C = 8;
    expected.ext.main_16.unk80 = 24;
    expected.ext.main_16.unk84 = c->unk84;
    expected.ext.main_16.unk88 = 0;
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_fan_shot_start(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct trident_mech_jump_launch_pod_case {
    u32 full;
};
static const struct trident_mech_jump_launch_pod_case trident_mech_jump_launch_pod_cases[] = {
    { 1 },
    { 0 },
};
static u32 test_trident_mech_jump_launch_pod(u32 row)
{
    const struct trident_mech_jump_launch_pod_case* c = &trident_mech_jump_launch_pod_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct MiscObj misc_expected[64];
    u8 full;
    spawn(&obj);
    obj.unk5 = 4;
    obj.unk6 = 0;
    obj.unk15 = PLAYER_FACING_RIGHT;
    set_animation(&obj, 16);
    obj.animation_cursor = (const u8*)&trident_mech_animations[16][2];
    obj.animation_step = trident_mech_animations[16][2];
    FILL_ACTIVE(misc_objects, 64, 1);
    full = c->full;
    if (!full) {
        memset(&misc_objects[63], 0, sizeof(misc_objects[63]));
    }
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    if (!full) {
        misc_expected[63].active = 0x41;
    }
    if (!full) {
        misc_expected[63].id = 5;
    }
    if (!full) {
        misc_expected[63].unk40 = obj.unk40;
    }
    if (!full) {
        misc_expected[63].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full) {
        misc_expected[63].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        misc_expected[63].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        misc_expected[63].bg_offset = obj.bg_offset;
    }
    if (!full) {
        misc_expected[63].x_pos = obj.x_pos;
    }
    if (!full) {
        misc_expected[63].y_pos = obj.y_pos;
    }
    if (!full) {
        misc_expected[63].unk15 = obj.unk15;
    }
    if (!full) {
        misc_expected[63].ext.misc_7.position = &obj.ext.main_16.unk90;
    }
    expected = obj;
    set_animation(&expected, 2);
    expected.unk6 = 1;
    player_expected = g_Player;
    engine_before = engine_obj;
    trident_mech_jump_launch_pod(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    return 1;
}

struct trident_mech_main_0_case {
    u32 state, unk8C, on_screen, stun;
    u32 expected[5];
};
static const struct trident_mech_main_0_case trident_mech_main_0_cases[] = {
    { 1, 1, 1, 0, { 2u, 1u, 0xCu, 0xA5u, 1u } },
    { 1, 2, 1, 1, { 1u, 0u, 0xCu, 0u, 1u } },
    { 2, 1, 0, 0, { 2u, 1u, 0xCu, 0xA5u, 1u } },
};
static u32 test_trident_mech_main_0(u32 row)
{
    const struct trident_mech_main_0_case* c = &trident_mech_main_0_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_expected[16];
    struct VisualObj visuals_before[32];
    struct BackgroundObj background_before;
    u8 stun;
    spawn(&obj);
    obj.state = c->state;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7 = 1;
    obj.unk7C = 2;
    obj.collision_flags = 8;
    obj.unk42 = 0x1234;
    obj.hurt_box = &trident_mech_hurt_box;
    obj.ext.main_16.unk8C = c->unk8C;
    obj.ext.main_16.unk90 = 0xA5;
    set_animation(&obj, 0);
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    SPIKE_IMMUNE_SET(g_Player, 1);
    engine_obj.character_state.bytes[0] = 0;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memset(D_8013E198, -1, sizeof(D_8013E198));
    FILL_ACTIVE(visual_objects, 32, 1);
    FILL_ACTIVE(weapon_objects, 16, 0);
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 0x41;
    weapon_objects[0].id = 26;
    weapon_objects[0].unk64 = 1;
    weapon_objects[0].unk50 = (const u8*)&zero_saber_hit_boxes[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos.val = 0x008C5678;
    assert(((const u8*)D_80106A74)[52] == 0);
    assert(((const u8*)D_80106A74)[53] == 4);
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    TEST_SET_HALVES(weapons_expected[0].unk80, 0x60, 0x70);
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk15 = 0;
    expected.unk7C = 1;
    expected.animation_step.fields.duration = 6;
    expected.hp = 12;
    expected.unk42 = 0x9234;
    expected.unk65 = 1;
    expected.on_screen = c->on_screen;
    stun = c->stun;
    if (stun) {
        expected.hurt_box = &trident_mech_stunned_hurt_box;
    }
    if (stun) {
        set_animation(&expected, 14);
    }
    if (stun) {
        expected.ext.main_16.unk90 = 0;
    }
    if (stun) {
        expected.unk5 = 1;
    }
    if (stun) {
        expected.unk6 = 0;
    }
    player_expected = g_Player;
    player_expected.update_delay_request = 1;
    engine_before = engine_obj;
    background_before = background_objects[0];
    trident_mech_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.hp;
    observed_values[3] = (u32)obj.ext.main_16.unk90;
    observed_values[4] = (u32)g_Player.update_delay_request;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}
struct trident_mech_main_1_case {
    u32 unk8C, stun;
    u32 expected[5];
};
static const struct trident_mech_main_1_case trident_mech_main_1_cases[] = {
    { 1, 0, { 2u, 1u, 0xCu, 0xA5u, 1u } },
    { 2, 1, { 1u, 0u, 0xCu, 0u, 1u } },
};
static u32 test_trident_mech_main_1(u32 row)
{
    const struct trident_mech_main_1_case* c = &trident_mech_main_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_expected[16];
    struct VisualObj visuals_before[32];
    struct BackgroundObj background_before;
    u8 stun;
    spawn(&obj);
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7 = 1;
    obj.unk7C = 2;
    obj.collision_flags = 8;
    obj.unk42 = 0x1234;
    obj.hurt_box = &trident_mech_hurt_box;
    obj.ext.main_16.unk8C = c->unk8C;
    obj.ext.main_16.unk90 = 0xA5;
    set_animation(&obj, 0);
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    SPIKE_IMMUNE_SET(g_Player, 1);
    engine_obj.character_state.bytes[0] = 0;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memset(D_8013E198, -1, sizeof(D_8013E198));
    FILL_ACTIVE(visual_objects, 32, 1);
    FILL_ACTIVE(weapon_objects, 16, 0);
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 0x41;
    weapon_objects[0].id = 27;
    weapon_objects[0].unk64 = 1;
    weapon_objects[0].unk50 = (const u8*)&zero_saber_hit_boxes[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos.val = 0x008C5678;
    assert(((const u8*)D_80106A74)[54] == 0);
    assert(((const u8*)D_80106A74)[55] == 4);
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    TEST_SET_HALVES(weapons_expected[0].unk80, 0x60, 0x70);
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk15 = 0;
    expected.unk7C = 1;
    expected.animation_step.fields.duration = 6;
    expected.hp = 12;
    expected.unk42 = 0x9234;
    expected.unk65 = 1;
    expected.on_screen = 1;
    stun = c->stun;
    if (stun) {
        expected.hurt_box = &trident_mech_stunned_hurt_box;
    }
    if (stun) {
        set_animation(&expected, 14);
    }
    if (stun) {
        expected.ext.main_16.unk90 = 0;
    }
    if (stun) {
        expected.unk5 = 1;
    }
    if (stun) {
        expected.unk6 = 0;
    }
    player_expected = g_Player;
    player_expected.update_delay_request = 1;
    engine_before = engine_obj;
    background_before = background_objects[0];
    trident_mech_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.hp;
    observed_values[3] = (u32)obj.ext.main_16.unk90;
    observed_values[4] = (u32)g_Player.update_delay_request;
    return c_test_observe(1, row, observed_values, c->expected, 5);
}
static u32 test_trident_mech_main(u32 index)
{
    if (index < 3)
        return test_trident_mech_main_0(index);
    index -= 3;
    return test_trident_mech_main_1(index);
}

static const u32 trident_mech_throw_pod_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 4u, 0u, 0u };
static u32 test_trident_mech_throw_pod(u32 row)
{
    u32 observed_values[16];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.unk7C = 1;
    FILL_ACTIVE(misc_objects, 64, 255 ? 1 : 0);
    trident_mech_throw_pod(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].bg_offset;
    observed_values[2] = (u32)misc_objects[0].ext.misc_5.animation;
    observed_values[3] = (u32)misc_objects[0].id;
    observed_values[4] = (u32)misc_objects[0].state;
    observed_values[5] = C_TEST_PSX_FACING(misc_objects[0].unk15);
    observed_values[6] = (u32)misc_objects[0].unk2;
    observed_values[7] = (u32)misc_objects[0].unk40;
    observed_values[8] = (u32)misc_objects[0].unk42;
    observed_values[9] = (u32)misc_objects[0].x_pos.val;
    observed_values[10] = (u32)misc_objects[0].y_pos.val;
    observed_values[11] = (u32)obj.ext.main_16.unk80;
    observed_values[12] = (u32)obj.ext.main_16.unk90;
    observed_values[13] = (u32)obj.unk5;
    observed_values[14] = (u32)obj.unk6;
    observed_values[15] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, trident_mech_throw_pod_expected, 16);
}

#include "support/state_cases.h"

#define MECH(step) (state_reset(step, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, memset(&weapon_objects[0], 0, sizeof(weapon_objects[0])))
#define MECH_SEEN() (state_extra = so.ext.main_16.unk8C | so.ext.main_16.unk88 << 8 | so.ext.main_16.unk80 << 16 | (u32)so.ext.main_16.unk90 << 24)
void func_8004FAE4(struct MainObj*);
static struct Unk_unk68 mech_feet = { 0, 0, 16, 16 };
static u32 mech_pages[0x100];
static s32 mech_frames[0x100];
#define DUST() (so.terrain_box = &mech_feet, test_stage_graphics(mech_pages), TEST_MENU_FRAMES = (u8*)mech_frames, state_terrain(0))
void func_8004ED60(struct MainObj*);
static void tm_stun_wait(void)
{
    MECH(7);
    func_8004FAE4(&so);
}
static void tm_stun_big_land(void)
{
    MECH(7);
    so.unk2 = 4;
    so.collision_flags = 8;
    so.animation_step.fields.event = 1;
    func_8004FAE4(&so);
}
static void tm_stun_big_air(void)
{
    MECH(7);
    so.unk2 = 4;
    so.animation_step.fields.event = 1;
    func_8004FAE4(&so);
}
static void tm_stun_air(void)
{
    MECH(7);
    so.animation_step.fields.event = 1;
    func_8004FAE4(&so);
}
static void tm_stun_land_fire(void)
{
    MECH(7);
    DUST();
    so.collision_flags = 8;
    so.animation_step.fields.event = 1;
    so.ext.main_16.unk8C = 1;
    cur_random = 2;
    engine_obj.cur_character = 0;
    func_8004FAE4(&so);
    MECH_SEEN();
}
static void tm_stun_land_idle(void)
{
    MECH(7);
    DUST();
    so.collision_flags = 8;
    so.animation_step.fields.event = 1;
    func_8004FAE4(&so);
    MECH_SEEN();
}
static void tm_charge_hot(void)
{
    MECH(4);
    so.unk7C = 1;
    trident_mech_charge_attack(&so);
    MECH_SEEN();
}
static void tm_charge_cool(void)
{
    MECH(4);
    so.unk7C = 1;
    so.ext.main_16.unk88 = 1;
    trident_mech_charge_attack(&so);
    MECH_SEEN();
}
static void tm_charge_spark(void)
{
    MECH(4);
    so.animation_step.fields.event = 2;
    trident_mech_charge_attack(&so);
    MECH_SEEN();
}
static void tm_charge_end(void)
{
    MECH(4);
    so.animation_step.fields.event = 1;
    so.ext.main_16.unk8C = 1;
    trident_mech_charge_attack(&so);
    MECH_SEEN();
}
static void tm_pick_wait(void)
{
    MECH(3);
    so.unk7C = 2;
    func_8004ED60(&so);
}
static void tm_pick_near_busy(void)
{
    MECH(3);
    so.unk7C = 1;
    weapon_objects[0].active = 1;
    g_Player.x_pos.i.hi = 0x80;
    cur_random = 1;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_near_a(void)
{
    MECH(3);
    so.unk7C = 1;
    g_Player.x_pos.i.hi = 0x80;
    cur_random = 1;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_near_b(void)
{
    MECH(3);
    so.unk7C = 1;
    g_Player.x_pos.i.hi = 0x80;
    cur_random = 6;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_busy_a(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    weapon_objects[0].active = 1;
    cur_random = 1;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_busy_b(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    weapon_objects[0].active = 1;
    cur_random = 9;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_busy_c(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    weapon_objects[0].active = 1;
    cur_random = 13;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_a(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    cur_random = 2;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_b(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    cur_random = 11;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}
static void tm_pick_far_c(void)
{
    MECH(3);
    so.unk7C = 1;
    so.x_pos.i.hi = 0x200;
    cur_random = 17;
    engine_obj.cur_character = 0;
    func_8004ED60(&so);
    MECH_SEEN();
}

static void (*const trident_mech_states_cases[])(void) = {
    tm_stun_wait,
    tm_stun_big_land,
    tm_stun_big_air,
    tm_stun_air,
    tm_stun_land_fire,
    tm_stun_land_idle,
    tm_charge_hot,
    tm_charge_cool,
    tm_charge_spark,
    tm_charge_end,
    tm_pick_wait,
    tm_pick_near_busy,
    tm_pick_near_a,
    tm_pick_near_b,
    tm_pick_far_busy_a,
    tm_pick_far_busy_b,
    tm_pick_far_busy_c,
    tm_pick_far_a,
    tm_pick_far_b,
    tm_pick_far_c,
};
static const u32 trident_mech_states_expected[] = { 0x700u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x800u, 0xFF000400u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x200u, 0x400u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x400u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x100u, 0u, 0x400u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x100u, 0u, 0x200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x600u, 0x400000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0x410000u, 0x600u, 0x400000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0x410000u, 0x400u, 0xFF400000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1010000u, 0u, 0x400u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1000000u, 0u, 0x400u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1000000u, 0u, 0x400u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1010000u, 0u, 0x800u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x800u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x800u, 0xFF000000u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_trident_mech_states(u32 row)
{
    return object_run(trident_mech_states_cases[row], row, &trident_mech_states_expected[row * 10]);
}

#define STUN(kind, flags, setup) (MECH(5), DUST(), so.unk2 = kind, so.collision_flags = flags, so.animation_step.fields.event = 1, setup, func_8004FAE4(&so), MECH_SEEN())
static void tms_wait(void)
{
    MECH(5);
    func_8004FAE4(&so);
}
static void tms_big_land(void) { STUN(4, 8, 0); }
static void tms_big_air(void) { STUN(4, 0, 0); }
static void tms_air(void) { STUN(1, 0, 0); }
static void tms_land(void) { STUN(1, 8, 0); }
static void tms_land_fire(void)
{
    u8 who = engine_obj.cur_character;
    STUN(1, 8, (so.ext.main_16.unk8C = 2, cur_random = 0x5B, engine_obj.cur_character = 1));
    engine_obj.cur_character = who;
}

static void (*const trident_mech_stun_cases[])(void) = {
    tms_wait,
    tms_big_land,
    tms_big_air,
    tms_air,
    tms_land,
    tms_land_fire,
};
static const u32 trident_mech_stun_expected[] = { 5u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 0x800000u, 0u, 0u, 0u, 0x11u, 1u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0x101u, 1u, 0x410000u };

static u32 test_trident_mech_stun(u32 row)
{
    return state_run(trident_mech_stun_cases[row], row, &trident_mech_stun_expected[row * 10]);
}

void trident_mech_update(struct MainObj*);
void trident_mech_explode(struct MainObj*);
void trident_mech_jump_launch_pod(struct MainObj*);
void trident_mech_jump_rise(struct MainObj*);
void func_8004F1A0(struct MainObj*);
void trident_mech_charge_wind_up(struct MainObj*);
void trident_mech_fan_shot_start(struct MainObj*);
void trident_mech_fan_shot_fire(struct MainObj*);
void trident_mech_fan_shot_end(struct MainObj*);
void trident_mech_double_shot_first(struct MainObj*);
void trident_mech_double_shot_second(struct MainObj*);
void trident_mech_double_shot_recover(struct MainObj*);
void trident_mech_throw_pod(struct MainObj*);
void trident_mech_wait_behind(struct MainObj*);
void trident_mech_fall(struct MainObj*);
void func_8004FD38(struct MainObj*, s8);
#define TM2(step, sub) (MECH(step), so.unk6 = sub, memset(weapon_objects, 0, sizeof(weapon_objects)), DUST(), state_terrain(0), so.active = 0x41, so.state = 1, so.unk7 = 1, so.collision_flags = 8, so.collision_data = D_80106A74)
#define TM2_INIT(kind) (TM2(0, 0), so.state = 0, so.unk2 = kind, trident_mech_update(&so), state_extra = so.state | so.unk17 << 8)
static void tm2_init_0(void) { TM2_INIT(0); }
static void tm2_init_1(void) { TM2_INIT(1); }
static void tm2_init_2(void) { TM2_INIT(2); }
static void tm2_init_3(void) { TM2_INIT(3); }
static void tm2_init_4(void) { TM2_INIT(4); }
static void tm2_init_5(void) { TM2_INIT(5); }
#define TM2_MAIN(setup) (TM2(9, 0), so.unk7C = 5, setup, trident_mech_update(&so), state_extra = so.state | so.unk7 << 8)
static void tm2_main_parts(void) { TM2_MAIN(so.unk7 = 0); }
static void tm2_main_behind(void) { TM2_MAIN((so.unk5 = 0xA, g_Player.x_pos.i.hi = 0x40)); }
static void tm2_main_core_gone(void) { TM2_MAIN(engine_obj.character_state.bytes[0] = 1), engine_obj.character_state.bytes[0] = 0; }
static void tm2_main_defeat(void) { TM2_MAIN((so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void tm2_main_off_screen(void) { TM2_MAIN(so.x_pos.i.hi = 0x400); }
static void tm2_main_drop(void) { TM2_MAIN(so.collision_flags = 0); }
static void tm2_explode_done(void) { TM2(0, 0), so.state = 2, so.unk7C = 1, trident_mech_explode(&so), state_extra = so.state; }
static void tm2_explode_burst(void) { TM2(0, 0), so.state = 2, so.unk7C = 5, so.unk7E = 1, trident_mech_explode(&so), state_extra = so.state; }
static void tm2_explode_wait(void) { TM2(0, 0), so.state = 2, so.unk7C = 5, so.unk7E = 3, trident_mech_explode(&so), state_extra = so.state; }
static void tm2_pick_far_volley(void) { TM2(2, 1), so.unk7C = 1, so.x_pos.i.hi = 0x200, cur_random = 14, func_8004ED60(&so), MECH_SEEN(); }
static void tm2_fall_land(void) { TM2(3, 0), so.air_state = 1, so.gravity = 0x4200, trident_mech_fall(&so), MECH_SEEN(); }
static void tm2_jump_wind_up(void) { TM2(4, 0), trident_mech_jump_launch_pod(&so), MECH_SEEN(); }
static void tm2_jump_rise(void) { TM2(4, 2), so.air_state = 1, so.y_speed = 0x10000, so.gravity = 0x6000, trident_mech_jump_rise(&so), MECH_SEEN(); }
static void tm2_jump_top(void) { TM2(4, 2), so.air_state = 1, so.y_speed = 0x6000, so.gravity = 0x6000, so.ext.main_16.unk90 = 1, trident_mech_jump_rise(&so), MECH_SEEN(); }
static void tm2_jump_top_shoot(void) { TM2(4, 2), so.air_state = 1, so.y_speed = 0x6000, so.gravity = 0x6000, so.ext.main_16.unk80 = 1, g_Player.x_pos.i.hi = 0x100, trident_mech_jump_rise(&so), MECH_SEEN(); }
static void tm2_land_wait(void) { TM2(5, 0), func_8004F1A0(&so), MECH_SEEN(); }
static void tm2_land_big(void) { TM2(5, 0), so.unk2 = 4, so.animation_step.fields.event = 1, func_8004F1A0(&so), MECH_SEEN(); }
static void tm2_land(void) { TM2(5, 0), so.animation_step.fields.event = 1, func_8004F1A0(&so), MECH_SEEN(); }
static void tm2_charge_hum(void) { TM2(6, 1), so.unk7C = 10, trident_mech_charge_wind_up(&so), MECH_SEEN(); }
static void tm2_charge_go(void) { TM2(6, 1), so.unk7C = 1, so.invincibility_timer = 1, trident_mech_charge_wind_up(&so), MECH_SEEN(); }
static void tm2_fan_aim(void) { TM2(7, 0), trident_mech_fan_shot_start(&so), MECH_SEEN(); }
static void tm2_fan_charge(void) { TM2(7, 1), so.unk7C = 8, trident_mech_fan_shot_fire(&so), MECH_SEEN(); }
static void tm2_fan_last(void) { TM2(7, 1), so.unk7C = 1, so.ext.main_16.unk80 = 0x10, so.ext.main_16.unk84 = -4, trident_mech_fan_shot_fire(&so), MECH_SEEN(); }
static void tm2_fan_end(void) { TM2(7, 2), so.animation_step.fields.event = 1, so.air_state = 1, trident_mech_fan_shot_end(&so), MECH_SEEN(); }
static void tm2_fan_end_wait(void) { TM2(7, 2), trident_mech_fan_shot_end(&so), MECH_SEEN(); }
static void tm2_double_wait(void) { TM2(8, 0), trident_mech_double_shot_first(&so), MECH_SEEN(); }
static void tm2_double_second_wait(void) { TM2(8, 1), so.unk7C = 2, trident_mech_double_shot_second(&so), MECH_SEEN(); }
static void tm2_double_second_left(void) { TM2(8, 1), so.unk7C = 1, trident_mech_double_shot_second(&so), MECH_SEEN(), state_extra ^= shot_objects[0].x_vel.val; }
#define RECOVER(timer, kind, count) (TM2(8, 2), so.unk7C = timer, so.unk2 = kind, so.unk7E = count, trident_mech_double_shot_recover(&so), MECH_SEEN())
static void tm2_recover_wait(void) { RECOVER(2, 0, 0); }
static void tm2_recover(void) { RECOVER(1, 0, 0); }
static void tm2_recover_again(void) { RECOVER(1, 4, 2); }
static void tm2_recover_jump(void) { RECOVER(1, 4, 1); }
static void tm2_throw(void) { TM2(9, 0), so.unk7C = 1, trident_mech_throw_pod(&so), MECH_SEEN(), state_extra ^= misc_objects[0].id << 8 | misc_objects[0].state << 16; }
static void tm2_behind_rise(void) { TM2(0xA, 0), g_Player.x_pos.i.hi = 0x91, trident_mech_wait_behind(&so), MECH_SEEN(); }
static void tm2_part_dust(void) { TM2(2, 0), state_terrain(0x24), func_8004FD38(&so, 5), state_extra = misc_objects[0].unk2 | misc_objects[0].ext.misc_5.animation << 8 | misc_objects[1].active << 16; }
static void tm2_part_pair(void) { TM2(2, 0), state_terrain(0x24), func_8004FD38(&so, 2), state_extra = misc_objects[0].unk2 | misc_objects[1].unk2 << 8 | misc_objects[1].active << 16; }
static void (*const tm2_cases[])(void) = {
    tm2_init_0,
    tm2_init_1,
    tm2_init_2,
    tm2_init_3,
    tm2_init_4,
    tm2_init_5,
    tm2_main_parts,
    tm2_main_behind,
    tm2_main_core_gone,
    tm2_main_defeat,
    tm2_main_off_screen,
    tm2_main_drop,
    tm2_explode_done,
    tm2_explode_burst,
    tm2_explode_wait,
    tm2_pick_far_volley,
    tm2_fall_land,
    tm2_jump_wind_up,
    tm2_jump_rise,
    tm2_jump_top,
    tm2_jump_top_shoot,
    tm2_land_wait,
    tm2_land_big,
    tm2_land,
    tm2_charge_hum,
    tm2_charge_go,
    tm2_fan_aim,
    tm2_fan_charge,
    tm2_fan_last,
    tm2_fan_end,
    tm2_fan_end_wait,
    tm2_double_wait,
    tm2_double_second_wait,
    tm2_double_second_left,
    tm2_recover_wait,
    tm2_recover,
    tm2_recover_again,
    tm2_recover_jump,
    tm2_throw,
    tm2_behind_rise,
    tm2_part_dust,
    tm2_part_pair,
};
static const u32 tm2_expected[] = {
    0x2u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x100003u, 0x1u, 0x41000000u,
    0x2u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x100003u, 0x201u, 0x41000000u,
    0x9u, 0x14u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x1u, 0x100003u, 0x101u, 0x41000000u,
    0xAu, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x100003u, 0x201u, 0x41000000u,
    0x8u, 0x30000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x20011u, 0x100003u, 0x1101u, 0x41000000u,
    0x2u, 0x30000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x20002u, 0x100003u, 0x201u, 0x41000000u,
    0x10009u, 0x4u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x101u, 0x41000000u,
    0x1000Au, 0x5u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x101u, 0x41000000u,
    0x10009u, 0x60020u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x102u, 0x41002100u,
    0x10009u, 0x60020u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x102u, 0x41002100u,
    0x10009u, 0x4u, 0x4000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x103u, 0x41000000u,
    0x1010003u, 0x5u, 0x800000u, 0x0u, 0xFFFFBE00u, 0x420000u, 0x0u, 0x0u, 0x101u, 0x41000000u,
    0x10000u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x3u, 0x41000000u,
    0x10000u, 0x60004u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x2u, 0x41002100u,
    0x10000u, 0x20004u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x2u, 0x41000000u,
    0x10006u, 0x0u, 0x2000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x41410000u,
    0x10005u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x3u, 0x1u, 0x0u, 0x41000000u,
    0x10004u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x1010204u, 0x0u, 0x800000u, 0x0u, 0xA000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x1010007u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x600000u, 0x4006u, 0x0u, 0x0u, 0x41000000u,
    0x10005u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10008u, 0x30000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x11u, 0x1u, 0x0u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x0u, 0x41000000u,
    0x10106u, 0x9u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10206u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0xDu, 0x0u, 0x0u, 0x41000000u,
    0x10007u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10107u, 0x7u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10207u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x7u, 0x0u, 0xC0000u, 0x41410000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x0u, 0x0u, 0x41000000u,
    0x10207u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10008u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10108u, 0x1u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10208u, 0x14u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x13u, 0x0u, 0xFFFF0000u, 0x41410000u,
    0x10208u, 0x1u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10008u, 0x10000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10004u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x10u, 0x0u, 0x1010000u, 0x41000000u,
    0x10004u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1030500u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x500u, 0x41000000u,
    0x10002u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x410101u, 0x41000000u,
};
static u32 tm2_run(u32 row)
{
    return state_run(tm2_cases[row], row, &tm2_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "trident_mech_branch_steps", 0, 0, COUNT(tm2_cases), tm2_run },
    { "trident_mech_stun", 0, 0, COUNT(trident_mech_stun_cases), test_trident_mech_stun },
    { "trident_mech_states", 0, 0, COUNT(trident_mech_states_cases), test_trident_mech_states },
    { "func_8004E8E0", 0, 0, 2, test_func_8004E8E0 },
    { "func_8004ED60", 0, 0, 6, test_func_8004ED60 },
    { "func_8004FD38", 0, 0, 2, test_func_8004FD38 },
    { "trident_mech_double_shot_first", 0, 0, 4, test_trident_mech_double_shot_first },
    { "trident_mech_double_shot_second", 0, 0, 4, test_trident_mech_double_shot_second },
    { "trident_mech_fan_shot_fire", 0, 0, 2, test_trident_mech_fan_shot_fire },
    { "trident_mech_fan_shot_start", 0, 0, 2, test_trident_mech_fan_shot_start },
    { "trident_mech_jump_launch_pod", 0, 0, 2, test_trident_mech_jump_launch_pod },
    { "trident_mech_main", 0, 0, 5, test_trident_mech_main },
    { "trident_mech_throw_pod", 0, 0, 1, test_trident_mech_throw_pod },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tm2_cases) + COUNT(trident_mech_stun_cases) + COUNT(trident_mech_states_cases) + 2 + 6 + 2 + 4 + 4 + 2 + 2 + 2 + 5 + 1;
