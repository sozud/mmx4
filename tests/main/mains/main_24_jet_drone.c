#include "test_runtime.h"
#include "main/mains/main_24_jet_drone.h"
#include "main/55C4.h"
extern union AnimationStep* jet_drone_animations[11];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern struct Unk_unk68 jet_drone_hurt_box[];
extern struct Unk_unk68 jet_drone_terrain_box[];

static u8 sprite_data[4];
static u32 bomb_case(u32 mode)
{
    struct MainObj obj, before;
    struct MiscObj misc_before[64];
    struct ShotObj shots_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i, fire = mode != 0, free_trail = mode == 2 || mode == 4, free_shot = mode == 2 || mode == 3;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    if (free_trail)
        misc_objects[63].active = 0;
    if (free_shot)
        shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 24;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x9234;
    obj.bg_offset = 1;
    obj.unk15 = 0x40;
    obj.ext.main_24.unk80 = fire ? 3 : 2;
    obj.unk7E = fire ? 1 : 2;
    obj.unk7C = mode == 2 ? 1 : 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)jet_drone_animations;
    obj.sprite_frames = (void*)sprite_data;
    set_animation(&obj, 8);
    before = obj;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    jet_drone_fly_bomb(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val += 32768;
    before.y_speed -= 0x1000;
    before.ext.main_24.unk80++;
    before.unk7E = fire ? (mode == 2 ? 0x7FFF : 8) : 1;
    if (fire) {
        before.unk7C--;
        before.unk17 = 9;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)jet_drone_animations[9];
        before.animation_step = *jet_drone_animations[9];
    }
    if (free_trail) {
        struct MiscObj* trail = &misc_before[63];
        trail->active = 0x41;
        trail->id = 7;
        trail->unk2 = 1;
        trail->state = 0;
        trail->unk40 = obj.unk40;
        trail->unk42 = 0x1234;
        trail->animation_table = (u32**)jet_drone_animations;
        trail->unk3C = (void*)sprite_data;
        trail->bg_offset = 1;
        trail->x_pos.val = before.x_pos.val;
        trail->y_pos.val = before.y_pos.val;
        trail->unk15 = 0;
        trail->ext.misc_7.position = &obj.x_pos;
    }
    if (free_shot) {
        struct ShotObj* shot = &shots_before[31];
        shot->active = 0x41;
        shot->id = 13;
        shot->unk2 = 0;
        shot->state = 0;
        shot->unk40 = obj.unk40;
        shot->unk42 = obj.unk42;
        shot->animation_table = (u32**)jet_drone_animations;
        shot->unk3C = (void*)sprite_data;
        shot->bg_offset = 1;
        shot->x_pos.val = before.x_pos.val;
        shot->y_pos.val = before.y_pos.val;
        shot->unk15 = 0x40;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(misc_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_before)[i]);
    for (i = 0; i < sizeof(shots_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.unk7E | ((u32)(u8)obj.unk7C << 16) | ((u32)obj.unk17 << 24);
}
#define CASE(m)                                    \
    static u32 jet_drone_bomb_pools_bomb_##m(void) \
    {                                              \
        return bomb_case(m);                       \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) jet_drone_bomb_pools_bomb_##m,
static const CTestCase jet_drone_bomb_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 jet_drone_bomb_pools_cases_expected[] = { 0x8020001u, 0x9010008u, 0x9007FFFu, 0x9010008u, 0x9010008u };
#undef CASE
#undef ENTRY

static const u32 func_800567C4_0_expected[] = { 0u, 0u, 3u, 0u, 0u, 2u, 0u, 1u, 0u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800567C4_0(u32 row)
{
    u32 observed_values[19];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk2 = -128;
    func_800567C4(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.contact_damage;
    observed_values[3] = (u32)obj.ext.main_24.unk80;
    observed_values[4] = (u32)obj.gravity;
    observed_values[5] = (u32)obj.hp;
    observed_values[6] = (u32)obj.invincibility_timer;
    observed_values[7] = (u32)obj.state;
    observed_values[8] = (u32)obj.unk15;
    observed_values[9] = (u32)obj.unk16;
    observed_values[10] = (u32)obj.unk18.val;
    observed_values[11] = (u32)obj.unk1C.val;
    observed_values[12] = (u32)obj.unk5;
    observed_values[13] = (u32)obj.unk6;
    observed_values[14] = (u32)obj.unk7A;
    observed_values[15] = (u32)obj.unk7C;
    observed_values[16] = (u32)obj.x_accel;
    observed_values[17] = (u32)obj.x_speed;
    observed_values[18] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_800567C4_0_expected, 19);
}

static const u32 inputs_0[8][11] = {
    { 0x41, 24, 6553600, 5242880, 0, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 1, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 2, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 3, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 4, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 5, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 6, -1, -1, -1, -1, -1, -1 },
    { 0x41, 24, 6553600, 5242880, 7, -1, -1, -1, -1, -1, -1 },
};
struct func_800567C4_1_case {
    u32 expected[14];
};
static const struct func_800567C4_1_case func_800567C4_1_cases[] = {
    { { 2u, 3u, 1u, 2u, 0u, 0xFFFB0000u, 0xFFFE4000u, 0xFFFF8000u, 0xFFFFC000u, 0x14u, 0u, 0u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 2u, 0u, 0xFFFB0000u, 0xFFFF4000u, 0xFFFF8000u, 0xFFFFE000u, 0x24u, 0u, 0u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 2u, 0u, 0xFFFB0000u, 0x1C000u, 0xFFFF8000u, 0x4000u, 0x14u, 0u, 0u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 2u, 0u, 0xFFFB0000u, 0xC000u, 0xFFFF8000u, 0x2000u, 0x24u, 0u, 0u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 3u, 0u, 0x50000u, 0xFFFE4000u, 0xFFFF8000u, 0xFFFFC000u, 0x14u, 0x40u, 1u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 3u, 0u, 0x50000u, 0xFFFF4000u, 0xFFFF8000u, 0xFFFFE000u, 0x24u, 0x40u, 1u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 3u, 0u, 0x50000u, 0x1C000u, 0xFFFF8000u, 0x4000u, 0x14u, 0x40u, 1u, 0x10006u, 0u } },
    { { 2u, 3u, 1u, 3u, 0u, 0x50000u, 0xC000u, 0xFFFF8000u, 0x2000u, 0x24u, 0x40u, 1u, 0x10006u, 0u } },
};
static u32 test_func_800567C4_1(u32 row)
{
    const struct func_800567C4_1_case* c = &func_800567C4_1_cases[row];
    u32 observed_values[14];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = inputs_0[row][0];
    obj.id = inputs_0[row][1];
    obj.x_pos.val = inputs_0[row][2];
    obj.y_pos.val = inputs_0[row][3];
    obj.unk2 = inputs_0[row][4];
    D_8013E198[0] = inputs_0[row][5];
    D_8013E198[1] = inputs_0[row][6];
    D_8013E198[2] = inputs_0[row][7];
    D_8013E198[3] = inputs_0[row][8];
    D_8013E198[4] = inputs_0[row][9];
    D_8013E198[5] = inputs_0[row][10];
    func_800567C4(&obj);
    assert(obj.hurt_box == jet_drone_hurt_box);
    assert(obj.attack_box == jet_drone_terrain_box);
    assert(obj.terrain_box == 0);
    assert(obj.unk18.val == obj.x_pos.val);
    assert(obj.unk1C.val == obj.y_pos.val);
    observed_values[0] = (u32)(u8)obj.hp;
    observed_values[1] = (u32)(u8)obj.contact_damage;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    observed_values[7] = (u32)obj.x_accel;
    observed_values[8] = (u32)obj.gravity;
    observed_values[9] = (u32)obj.unk7C;
    observed_values[10] = (u32)obj.unk15;
    observed_values[11] = (u32)obj.unk7A;
    observed_values[12] = obj.animation_step.packed;
    observed_values[13] = (u32)(u8)obj.unk17;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

static const u32 jet_drone_fly_dash_expected[] = { 0x5F0000u, 0x51C000u, 4u, 1u, 0u, 0x10005u, 1u };
static u32 test_jet_drone_fly_dash(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    struct MiscObj before[64];
    u8 pool_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 24;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    D_8013E198[0] = -1;
    D_8013E198[1] = -1;
    D_8013E198[2] = -1;
    D_8013E198[3] = -1;
    D_8013E198[4] = -1;
    D_8013E198[5] = -1;
    func_800567C4(&obj);
    assert(obj.hurt_box == jet_drone_hurt_box);
    assert(obj.attack_box == jet_drone_terrain_box);
    assert(obj.terrain_box == 0);
    assert(obj.unk18.val == obj.x_pos.val);
    assert(obj.unk1C.val == obj.y_pos.val);
    pool_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_full ? 1 : 0;
    }
    memcpy(before, misc_objects, sizeof(before));
    obj.ext.main_24.unk80 = 3;
    obj.unk7C = 2;
    jet_drone_fly_dash(&obj);
    c_test_same_words(misc_objects, before, sizeof(misc_objects));
    observed_values[0] = (u32)obj.x_pos.val;
    observed_values[1] = (u32)obj.y_pos.val;
    observed_values[2] = (u32)obj.ext.main_24.unk80;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = obj.animation_step.packed;
    observed_values[6] = (u32)misc_objects[0].active;
    return c_test_observe(0, row, observed_values, jet_drone_fly_dash_expected, 7);
}

static const u32 jet_drone_fly_turn_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 0u, 3u, 1u, 8u, 0xFFFE0000u };
static u32 test_jet_drone_fly_turn(u32 row)
{
    u32 observed_values[16];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.ext.main_24.unk80 = 3;
    pool_0_full = 255;
    obj.unk7C = 1;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    jet_drone_fly_turn(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].bg_offset;
    observed_values[2] = (u32)misc_objects[0].id;
    observed_values[3] = (u32)misc_objects[0].state;
    observed_values[4] = (u32)misc_objects[0].unk15;
    observed_values[5] = (u32)misc_objects[0].unk2;
    observed_values[6] = (u32)misc_objects[0].unk40;
    observed_values[7] = (u32)misc_objects[0].unk42;
    observed_values[8] = (u32)misc_objects[0].x_pos.val;
    observed_values[9] = (u32)misc_objects[0].y_pos.val;
    observed_values[10] = (u32)obj.ext.main_24.unk80;
    observed_values[11] = (u32)obj.gravity;
    observed_values[12] = (u32)obj.unk6;
    observed_values[13] = (u32)obj.unk7C;
    observed_values[14] = (u32)obj.unk7E;
    observed_values[15] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, jet_drone_fly_turn_expected, 16);
}

const struct CTestGroup c_test_groups[] = {
    { "jet_drone_bomb_pools", jet_drone_bomb_pools_cases, jet_drone_bomb_pools_cases_expected, COUNT(jet_drone_bomb_pools_cases), 0 },
    { "func_800567C4_0", 0, 0, 1, test_func_800567C4_0 },
    { "func_800567C4_1", 0, 0, 8, test_func_800567C4_1 },
    { "jet_drone_fly_dash", 0, 0, 1, test_jet_drone_fly_dash },
    { "jet_drone_fly_turn", 0, 0, 1, test_jet_drone_fly_turn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jet_drone_bomb_pools_cases) + 1 + 8 + 1 + 1;
