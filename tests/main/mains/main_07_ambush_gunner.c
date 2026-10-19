#include "test_runtime.h"
#include "main/mains/main_07_ambush_gunner.h"
#include "main/55C4.h"
extern union AnimationStep* ambush_gunner_animations[9];
extern struct Unk_unk68 ambush_gunner_terrain_box;
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern union AnimationStep ambush_gunner_anim_2[31];

static const u32 ambush_gunner_aim_wait_0_expected[] = { 0u, 0u, 0u, 0u, 0x3Cu, 0u, 0u };
static u32 test_ambush_gunner_aim_wait_0(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk15 = 255;
    ambush_gunner_aim_wait(&obj);
    observed_values[0] = (u32)obj.ext.main_7.saved_x_velocity;
    observed_values[1] = (u32)obj.ext.main_7.saved_y_velocity;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, ambush_gunner_aim_wait_0_expected, 7);
}

struct ambush_gunner_fire_1_case {
    u32 pools_full;
    u32 expected[16];
};
static const struct ambush_gunner_fire_1_case ambush_gunner_fire_1_cases[] = {
    { 1, { 4u, 2u, 0u, 0u, 0x2A010001u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, { 4u, 2u, 0u, 0u, 0x2A010001u, 0x41u, 2u, 0x40u, 0xBAu, 0x798Fu, 0x640000u, 0x500000u, 0xFFFE0000u, 0x10000u, 0xFFFFFFFFu, 1u } },
};
static u32 test_ambush_gunner_fire_1(u32 row)
{
    const struct ambush_gunner_fire_1_case* c = &ambush_gunner_fire_1_cases[row];
    u32 observed_values[16];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct ShotObj shots_before[32];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.val = 0;
    g_Player.y_pos.val = 5242880;
    player_before = g_Player;
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    pools_full = c->pools_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    FILL_ACTIVE(shot_objects, 31, 1);
    func_80047404(&obj);
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk40 = 0xBA;
    obj.unk42 = 0x798F;
    obj.ext.main_7.saved_x_velocity = -131072;
    obj.ext.main_7.saved_y_velocity = 65536;
    set_animation(&obj, 2);
    obj.animation_step = ambush_gunner_anim_2[23];
    obj.animation_cursor = (const u8*)&ambush_gunner_anim_2[24];
    assert(obj.animation_step.fields.event == 2);
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    if (pools_full == 0) {
        shots_before[31].active = 0x41;
    }
    if (pools_full == 0) {
        shots_before[31].id = 2;
    }
    if (pools_full == 0) {
        shots_before[31].unk40 = obj.unk40;
    }
    if (pools_full == 0) {
        shots_before[31].unk42 = obj.unk42;
    }
    if (pools_full == 0) {
        shots_before[31].animation_table = (u32**)obj.animation_table;
    }
    if (pools_full == 0) {
        shots_before[31].unk3C = (void*)obj.sprite_frames;
    }
    if (pools_full == 0) {
        shots_before[31].unk2 = obj.unk2 & 1;
    }
    if (pools_full == 0) {
        shots_before[31].unk15 = obj.unk15;
    }
    if (pools_full == 0) {
        shots_before[31].bg_offset = obj.bg_offset;
    }
    if (pools_full == 0) {
        shots_before[31].x_pos = obj.x_pos;
    }
    if (pools_full == 0) {
        shots_before[31].y_pos = obj.y_pos;
    }
    if (pools_full == 0) {
        shots_before[31].x_vel.val = obj.ext.main_7.saved_x_velocity;
    }
    if (pools_full == 0) {
        shots_before[31].y_vel.val = obj.ext.main_7.saved_y_velocity;
    }
    ambush_gunner_fire(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    observed_values[4] = (u32)obj.animation_step.packed;
    observed_values[5] = (u32)shot_objects[31].active;
    observed_values[6] = (u32)shot_objects[31].id;
    observed_values[7] = (u32)shot_objects[31].unk15;
    observed_values[8] = (u32)shot_objects[31].unk40;
    observed_values[9] = (u32)shot_objects[31].unk42;
    observed_values[10] = (u32)shot_objects[31].x_pos.val;
    observed_values[11] = (u32)shot_objects[31].y_pos.val;
    observed_values[12] = (u32)shot_objects[31].x_vel.val;
    observed_values[13] = (u32)shot_objects[31].y_vel.val;
    observed_values[14] = (u32)shot_objects[31].bg_offset;
    observed_values[15] = (u32)shot_objects[31].unk2;
    return c_test_observe(0, row, observed_values, c->expected, 16);
}

struct func_80047404_case {
    u32 unk2;
    u32 expected[15];
};
static const struct func_80047404_case func_80047404_cases[] = {
    { 1, { 6u, 3u, 0u, 1u, 3u, 0u, 0x40u, 0u, 0u, 0u, 1u, 0u, 0u, 0x1B000101u, 0xFFFFFFFFu } },
    { 4, { 6u, 3u, 1u, 1u, 2u, 0u, 0u, 1u, 0u, 0x8Cu, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 5, { 6u, 3u, 1u, 1u, 2u, 0u, 0x40u, 1u, 0u, 0x8Cu, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 6, { 6u, 3u, 1u, 1u, 2u, 0u, 0u, 1u, 1u, 0x28u, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
    { 7, { 6u, 3u, 1u, 1u, 2u, 0u, 0x40u, 1u, 1u, 0x28u, 0u, 0u, 0u, 0x10002u, 0xFFFFFFFFu } },
};
static u32 test_func_80047404(u32 row)
{
    const struct func_80047404_case* c = &func_80047404_cases[row];
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = c->unk2;
    g_Player.bg_offset = -1;
    player_before = g_Player;
    func_80047404(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(obj.animation_table == (const u8* const*)ambush_gunner_animations);
    assert(obj.hurt_box == &ambush_gunner_terrain_box);
    assert(obj.attack_box == &ambush_gunner_terrain_box);
    observed_values[0] = (u32)obj.hp;
    observed_values[1] = (u32)obj.contact_damage;
    observed_values[2] = (u32)obj.invincibility_timer;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.unk15;
    observed_values[7] = (u32)obj.unk7A;
    observed_values[8] = (u32)obj.ext.main_7.unk80;
    observed_values[9] = (u32)obj.ext.main_7.unk84;
    observed_values[10] = (u32)obj.ext.main_7.unk90;
    observed_values[11] = (u32)obj.x_speed;
    observed_values[12] = (u32)obj.y_speed;
    observed_values[13] = (u32)obj.animation_step.packed;
    observed_values[14] = (u32)obj.bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 15);
}

struct func_80047818_0_case {
    u32 g_Player_x_pos, obj_x_pos, obj_x_pos_hi, g_Player_x_pos_hi, unk80, unk84;
    u32 expected[2];
};
static const struct func_80047818_0_case func_80047818_0_cases[] = {
    { -983042, -1048576, -32128, -32698, 1048576, 570, { 0u, 0u } },
    { -983168, -1048575, 0, -16368, 1048576, 16367, { 1u, 0u } },
    { 0, 16842753, -32768, -32768, 65280, 0, { 0u, 0u } },
    { -2, 16842753, 0, -32768, 65280, 32767, { 1u, 0u } },
};
static u32 test_func_80047818_0(u32 row)
{
    const struct func_80047818_0_case* c = &func_80047818_0_cases[row];
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.val = c->g_Player_x_pos;
    obj.x_pos.val = c->obj_x_pos;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.ext.main_7.unk80 = c->unk80;
    obj.ext.main_7.unk84 = c->unk84;
    func_80047818(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7A;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

static const u32 func_80047818_1_expected[] = { 1u, 0u, 0x640000u, 0x500000u };
static u32 test_func_80047818_1(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 7;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = 5;
    g_Player.bg_offset = -1;
    g_Player.x_pos.val = 13107200;
    player_before = g_Player;
    func_80047404(&obj);
    expected = obj;
    expected.unk6 = 1;
    expected.unk7A = 0;
    func_80047818(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7A;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, func_80047818_1_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "ambush_gunner_aim_wait_0", 0, 0, 1, test_ambush_gunner_aim_wait_0 },
    { "ambush_gunner_fire_1", 0, 0, 2, test_ambush_gunner_fire_1 },
    { "func_80047404", 0, 0, 5, test_func_80047404 },
    { "func_80047818_0", 0, 0, 4, test_func_80047818_0 },
    { "func_80047818_1", 0, 0, 1, test_func_80047818_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2 + 5 + 4 + 1;
