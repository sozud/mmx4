#include "test_runtime.h"
#include "main/mains/main_34_highway_trooper.h"
#include "main/195B4.h"
#include "main/55C4.h"
extern union AnimationStep* highway_trooper_animations[27];

struct func_8005E5C0_case {
    u32 unk2;
    u32 expected[16];
};
static const struct func_8005E5C0_case func_8005E5C0_cases[] = {
    { 0, { 1u, 0u, 1u, 6u, 0x2Du, 0x788Eu, 0xA481234u, 0x1405678u, 0xA481234u, 0x1405678u, 0xFFFE4000u, 0u, 0x1010004u, 0u, 1u, 1u } },
    { 1, { 1u, 0u, 1u, 6u, 0x2Du, 0x788Eu, 0xEA81234u, 0x1705678u, 0xEA81234u, 0x1705678u, 0xFFFE4000u, 0u, 0x1010004u, 0u, 1u, 1u } },
    { 2, { 1u, 0u, 1u, 6u, 0x2Du, 0x788Eu, 0x15281234u, 0x14A5678u, 0x15281234u, 0x14A5678u, 0xFFFE4000u, 0u, 0x1010004u, 1u, 1u, 1u } },
    { 3, { 1u, 0u, 1u, 6u, 0x2Du, 0x788Eu, 0x1BC81234u, 0x1705678u, 0x1BC81234u, 0x1705678u, 0xFFFE4000u, 0u, 0x1010004u, 0u, 1u, 1u } },
};
static u32 test_func_8005E5C0(u32 row)
{
    const struct func_8005E5C0_case* c = &func_8005E5C0_cases[row];
    u32 observed_values[16];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    s32 frames[32], frames_before[32];
    u32 metadata[16], metadata_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 26219060;
    obj.y_pos.val = 13129336;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 2);
    obj.state = 0;
    obj.unk2 = c->unk2;
    obj.terrain_box = NULL;
    memset(&frames, 0, sizeof(frames));
    memset(&metadata, 0, sizeof(metadata));
    frames[5] = 64;
    metadata[5] = 0x1680;
    TEST_MENU_FRAMES = (u8*)frames;
    D_801406A8 = metadata;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    g_Player.bg_offset = 1;
    assert(s_StageMainIds[0][0][5] == 0x22);
    assert((u8)func_8002938C(0x22) == 5);
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(metadata_before, metadata, sizeof(metadata_before));
    func_8005E5C0(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(metadata, metadata_before, sizeof(metadata));
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.bg_offset;
    observed_values[3] = (u32)obj.unk16;
    observed_values[4] = (u32)obj.unk40;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.x_pos.val;
    observed_values[7] = (u32)obj.y_pos.val;
    observed_values[8] = (u32)obj.unk18.val;
    observed_values[9] = (u32)obj.unk1C.val;
    observed_values[10] = (u32)obj.x_speed;
    observed_values[11] = (u32)obj.y_speed;
    observed_values[12] = (u32)obj.animation_step.packed;
    observed_values[13] = (u32)(obj.terrain_box == NULL);
    observed_values[14] = (u32)(obj.sprite_frames == (u8*)frames + 64);
    observed_values[15] = (u32)obj.hp;
    return c_test_observe(0, row, observed_values, c->expected, 16);
}

struct highway_trooper_attack_fire_1_case {
    u32 free_last;
};
static const struct highway_trooper_attack_fire_1_case highway_trooper_attack_fire_1_cases[] = {
    { 0 },
    { 1 },
};
static u32 test_highway_trooper_attack_fire_1(u32 row)
{
    const struct highway_trooper_attack_fire_1_case* c = &highway_trooper_attack_fire_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    struct WeaponObj owner_before;
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 26219060;
    obj.y_pos.val = 13129336;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 2);
    obj.animation_step = highway_trooper_animations[2][3];
    obj.animation_cursor = (const u8*)(highway_trooper_animations[2] + 3);
    assert(obj.animation_step.fields.event == 1);
    obj.ext.main_34.unk82 = 2;
    obj.backref = &weapon_objects[15];
    SP_CUR_MAIN_OBJ = &obj;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        shot_objects[31].active = 0;
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (free_last) {
        shots_expected[31].active = 0x41;
    }
    if (free_last) {
        shots_expected[31].id = 0x13;
    }
    if (free_last) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        shots_expected[31].animation_table = (const u8* const*)highway_trooper_animations;
    }
    if (free_last) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (free_last) {
        shots_expected[31].unk2 = 0;
    }
    if (free_last) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        shots_expected[31].x_pos.val = obj.x_pos.val - 0x10;
    }
    if (free_last) {
        shots_expected[31].y_pos.val = obj.y_pos.val - 0x20;
    }
    if (free_last) {
        shots_expected[31].unk7C = (struct WeaponObj*)obj.backref;
    }
    expected = obj;
    if (free_last) {
        expected.unk6 = 1;
    }
    if (free_last) {
        expected.ext.main_34.unk82 = 0;
    }
    owner_before = weapon_objects[15];
    player_before = g_Player;
    engine_before = engine_obj;
    highway_trooper_attack_fire(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shot_objects));
    c_test_same_words(&weapon_objects[15], &owner_before, sizeof(weapon_objects[15]));
    return 1;
}

struct highway_trooper_attack_ready_jump_0_case {
    u32 unk2;
};
static const struct highway_trooper_attack_ready_jump_0_case highway_trooper_attack_ready_jump_0_cases[] = {
    { 0 },
    { 2 },
};
static u32 test_highway_trooper_attack_ready_jump_0(u32 row)
{
    const struct highway_trooper_attack_ready_jump_0_case* c = &highway_trooper_attack_ready_jump_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct Unk_unk68 terrain_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 26219060;
    obj.y_pos.val = 13129336;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 2);
    obj.unk2 = c->unk2;
    obj.unk6 = 1;
    obj.animation_step = highway_trooper_animations[2][4];
    obj.animation_cursor = (const u8*)(highway_trooper_animations[2] + 4);
    expected = obj;
    if (obj.animation_step.fields.event == 2 && obj.unk2 == 2) {
        expected.terrain_box = &highway_trooper_terrain_box;
    }
    if (obj.animation_step.fields.event == 2) {
        expected.unk6 = 2;
    }
    if (obj.animation_step.fields.event == 2) {
        set_animation(&expected, 3);
    }
    player_before = g_Player;
    engine_before = engine_obj;
    terrain_before = highway_trooper_terrain_box;
    highway_trooper_attack_ready_jump(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&highway_trooper_terrain_box, &terrain_before, sizeof(highway_trooper_terrain_box));
    return 1;
}
static const u32 highway_trooper_attack_ready_jump_1_expected[] = { 1u, 2u, 0xC010102u, 0u };
static u32 test_highway_trooper_attack_ready_jump_1(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct Unk_unk68 terrain_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 26219060;
    obj.y_pos.val = 13129336;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 2);
    obj.unk2 = 2;
    obj.unk6 = 1;
    obj.animation_step = highway_trooper_animations[2][3];
    obj.animation_cursor = (const u8*)(highway_trooper_animations[2] + 3);
    expected = obj;
    if (obj.animation_step.fields.event == 2 && obj.unk2 == 2) {
        expected.terrain_box = &highway_trooper_terrain_box;
    }
    if (obj.animation_step.fields.event == 2) {
        expected.unk6 = 2;
    }
    if (obj.animation_step.fields.event == 2) {
        set_animation(&expected, 3);
    }
    player_before = g_Player;
    engine_before = engine_obj;
    terrain_before = highway_trooper_terrain_box;
    highway_trooper_attack_ready_jump(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&highway_trooper_terrain_box, &terrain_before, sizeof(highway_trooper_terrain_box));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk17;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)(obj.terrain_box == &highway_trooper_terrain_box);
    return c_test_observe(1, row, observed_values, highway_trooper_attack_ready_jump_1_expected, 4);
}
static u32 test_highway_trooper_attack_ready_jump(u32 index)
{
    if (index < 2)
        return test_highway_trooper_attack_ready_jump_0(index);
    index -= 2;
    return test_highway_trooper_attack_ready_jump_1(index);
}

struct highway_trooper_wait_1_case {
    u32 obj_main_34_unk80, expected_main_34_unk80;
};
static const struct highway_trooper_wait_1_case highway_trooper_wait_1_cases[] = {
    { 1, 0 },
    { 2, 1 },
    { 0, -1 },
    { -128, 127 },
    { -127, -128 },
};
static u32 test_highway_trooper_wait_1(u32 row)
{
    const struct highway_trooper_wait_1_case* c = &highway_trooper_wait_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 26219060;
    obj.y_pos.val = 13129336;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 2);
    obj.unk5 = 1;
    set_animation(&obj, 0);
    obj.ext.main_34.unk80 = c->obj_main_34_unk80;
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    expected.ext.main_34.unk80 = c->expected_main_34_unk80;
    if (expected.ext.main_34.unk80 <= 0) {
        set_animation(&expected, 2);
    }
    if (expected.ext.main_34.unk80 <= 0) {
        expected.unk5 = 2;
    }
    player_before = g_Player;
    engine_before = engine_obj;
    highway_trooper_wait(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "func_8005E5C0", 0, 0, 4, test_func_8005E5C0 },
    { "highway_trooper_attack_fire_1", 0, 0, 2, test_highway_trooper_attack_fire_1 },
    { "highway_trooper_attack_ready_jump", 0, 0, 3, test_highway_trooper_attack_ready_jump },
    { "highway_trooper_wait_1", 0, 0, 5, test_highway_trooper_wait_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 + 2 + 3 + 5;
