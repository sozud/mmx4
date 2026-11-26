#include "test_runtime.h"
#include "main/mains/main_15_shell_crawler.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void shell_crawler_hop(struct MainObj*);
void shell_crawler_land(struct MainObj*);
void shell_crawler_walk(struct MainObj*);
extern u8 D_800FFB5C[4];
extern union AnimationStep* shell_crawler_animations[];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern struct Unk_unk68 shell_crawler_terrain_box;

static struct JumpInput {
    s8 air;
    u8 floor, pit, wall, facing, patrol;
};
enum { AIRBORNE,
    FALL,
    GROUND_AHEAD,
    TURN,
    WALL,
    JUMP_LEFT,
    JUMP_RIGHT,
    TURN_BACK };
static const struct JumpInput inputs[] = {
    { 1, 1, 5, 0, 0, 0 },
    { 0, 0, 5, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0 },
    { 0, 1, 5, 0, 0, 1 },
    { 0, 1, 5, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 0 },
    { 0, 1, 7, 0, 0x40, 0 },
    { 0, 1, 7, 0, 0x40, 1 },
};
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[2] = { 0, C_TEST_PSX_WORD(0x39) };
static u32 steps[2];
static u32* table[0x20];
static struct MainObj soldier, expected;

static void terrain(const struct JumpInput* input)
{
    u32 row, column;
    memset(tilemap, 0, sizeof(tilemap));
    memset(tiles, 0, sizeof(tiles));
    tilemap[0] = 1;
    for (row = 8; row < 16 && input->floor; row++)
        for (column = 0; column < 16; column++)
            tiles[1][row][column] = column != input->pit || input->pit == 0;
    for (row = 5; row < 8 && input->wall; row++)
        tiles[1][row][input->pit] = 1;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
}

static u32 check(u32 mode, u32 observation)
{
    const struct JumpInput* input = &inputs[mode];
    union AnimationStep value;
    u32 i;
    terrain(input);
    memset(&soldier, 0, sizeof(soldier));
    value.fields.duration = 4;
    value.fields.event = 0;
    value.fields.relative_step = 0;
    value.fields.frame_index = 9;
    steps[0] = steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    soldier.active = 0x41;
    soldier.id = 0x31;
    soldier.state = 1;
    soldier.unk2 = input->patrol;
    soldier.unk5 = 2;
    soldier.unk6 = 1;
    soldier.unk15 = input->facing;
    soldier.air_state = input->air;
    soldier.x_pos.val = 104 << 16;
    soldier.y_pos.val = 107 << 16;
    soldier.unk18.val = soldier.x_pos.val;
    soldier.unk1C.val = soldier.y_pos.val;
    soldier.x_speed = 0x8000;
    soldier.terrain_box = (struct Unk_unk68*)D_800FFB5C;
    soldier.animation_table = table;
    soldier.animation_cursor = &steps[0];
    soldier.animation_step.packed = steps[0];
    expected = soldier;
    func_8004DB10(&soldier);

    if (!input->air) {
        expected.x_pos = soldier.x_pos;
        expected.y_pos = soldier.y_pos;
        expected.collision_flags = soldier.collision_flags;
        expected.unk6C = soldier.unk6C;
        expected.unk6E = soldier.unk6E;
        ((u8*)&expected)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = ((u8*)&soldier)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)];
        ((u8*)&expected)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)] = ((u8*)&soldier)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)];
    }
    if (mode == FALL || mode == JUMP_LEFT || mode == JUMP_RIGHT) {
        expected.animation_cursor = &steps[1];
        expected.animation_step.packed = steps[1];
        expected.unk17 = mode == FALL ? 3 : 2;
        expected.previous_animation_index = 0xFF;
        expected.unk6 = 0;
    }
    if (mode == FALL) {
        expected.unk5 = 2;
        expected.gravity = FIXED(0.2578125);
        expected.y_speed = 0;
        expected.x_accel = 0;
        expected.air_state = -1;
    } else if (mode == TURN) {
        expected.unk15 = PLAYER_FACING_RIGHT;
        expected.x_speed = -0x8000;
    } else if (mode == TURN_BACK) {
        expected.unk15 = 0;
        expected.x_speed = -0x8000;
    } else if (mode == JUMP_LEFT || mode == JUMP_RIGHT) {
        expected.unk5 = 5;
        expected.y_speed = FIXED(3.5);
        expected.gravity = FIXED(0.2578125);
        expected.x_speed = mode == JUMP_RIGHT ? FIXED(1) : FIXED(-1);
        expected.air_state = 1;
    }
    for (i = 0; i < sizeof(soldier) / 4; i++)
        assert(((u32*)&soldier)[i] == ((u32*)&expected)[i]);
    assert(tilemap[0] == 1 && attributes[0] == 0 && attributes[1] == C_TEST_PSX_WORD(0x39) && layout_width == 16 && layout_size == 256);

    if (observation == 0)
        return soldier.collision_flags | ((u32)(u8)soldier.unk5 << 8) | ((u32)(u8)soldier.air_state << 16)
            | ((u32)C_TEST_PSX_FACING(soldier.unk15) << 24);
    return (u16)soldier.y_pos.i.hi | ((u32)(u8)soldier.unk6C << 16) | ((u32)(u8)soldier.unk6E << 24);
}

static const u32 shell_crawler_check_jump_cases_expected[] = { 0x10200u, 0x6Bu, 0xFF0200u, 0x8006Bu, 0x208u, 0x8006Bu, 0x40000208u, 0x8006Bu, 0x20Eu, 0x8006Bu, 0x10508u, 0x8006Bu, 0x40010508u, 0x8006Bu, 0x208u };
static u32 shell_crawler_check_jump_cases_row(u32 row)
{
    return check(row / 2, row % 2);
}

static const u32 frames[] = { 0x11223344, 0x55667788 };
static u32 shell_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj shots[32];
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, step = mode < 2 ? 2 : mode == 2 ? 5
        : mode == 3                        ? 0
                                           : 1;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = 1;
        s->id = 39;
        s->state = 40;
        s->unk2 = 9;
        s->unk5 = 3;
        s->unk6 = 4;
        s->unk7 = 5;
        s->x_pos.val = 50 * 65536 + 0xBEEF;
        s->y_pos.val = 60 * 65536 + 0xCAFE;
        s->unk50.data = (const u8*)&box;
        s->unk54 = (const u8*)&box;
        s->unk68 = &box;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 7;
        s->unk72 = s->unk73 = s->unk76 = s->unk77 = 7;
        OBJ_UNK78_SET(*s, 7);
        OBJ_UNK74_SET(*s, 7);
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 7;
    }
    if (mode == 1 || mode == 4)
        shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.bg_offset = 2;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x5678;
    obj.sprite_frames = (const u8*)frames;
    obj.ext.main_0.flags[1] = 7;
    obj.ext.main_0.background_relative = 0xFF;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    set_animation(&obj, 2);
    obj.animation_cursor = (const u8*)&shell_crawler_animations[2][step];
    obj.animation_step = shell_crawler_animations[2][step];
    if (mode == 4)
        obj.animation_step.fields.duration = 1;
    expected = obj;
    memcpy(shots, shot_objects, sizeof(shots));
    if (mode == 2) {
        expected.unk5 = 1;
        expected.unk6 = 0;
        expected.unk17 = 1;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)shell_crawler_animations[1];
        expected.animation_step = shell_crawler_animations[1][0];
        expected.ext.main_0.flags[1] = 0x78;
        expected.ext.main_0.background_relative = 0xFD;
    } else {
        if (mode == 4) {
            expected.animation_cursor = (const u8*)&shell_crawler_animations[2][2];
            expected.animation_step = shell_crawler_animations[2][2];
        } else
            expected.animation_step.fields.duration--;
        if (mode < 2 || mode == 4) {
            expected.animation_step.fields.event = 0;
            if (mode) {
                struct ShotObj* s = &shots[31];
                s->active = 0x41;
                s->id = 8;
                s->x_pos = obj.x_pos;
                s->y_pos = obj.y_pos;
                s->unk3C = (void*)obj.sprite_frames;
                s->unk40 = obj.unk40;
                s->unk42 = obj.unk42;
                s->bg_offset = obj.bg_offset;
                s->animation_table = (u32**)obj.animation_table;
                s->unk15 = obj.unk15;
                s->unk50.data = NULL;
                s->unk54 = NULL;
                s->unk68 = NULL;
                s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
                s->unk72 = s->unk73 = s->unk76 = s->unk77 = 0;
                OBJ_UNK78_SET(*s, 0);
                OBJ_UNK74_SET(*s, 0);
                s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
            }
        }
    }
    shell_crawler_shoot(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(frames[0] == 0x11223344 && frames[1] == 0x55667788);
    return (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)(u8)shot_objects[31].active << 16);
}
static const u32 shell_crawler_shoot_events_cases_expected[] = { 0x10202u, 0x410202u, 0x10101u, 0x10202u, 0x410202u };

static u32 full_pool(void)
{
    struct MainObj obj, before;
    struct ShotObj pool_before[32];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < COUNT(shot_objects); i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk7C = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    before = obj;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    func_8004E490(&obj);
    before.unk7C = obj.unk7C;
    before.state = obj.state;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    actual = (u16)obj.unk7C | ((u32)(u8)obj.state << 16);
    return actual;
}
static const CTestCase shell_expiry_full_pool_cases[] = { full_pool };
static const u32 shell_expiry_full_pool_cases_expected[] = { 0x20000u };

struct func_8004E300_1_0_case {
    u32 unk6, collision_flags, hi, x_pos, y_pos, y_speed, gravity, air_state, state, on_screen;
};
static const struct func_8004E300_1_0_case func_8004E300_1_0_cases[] = {
    { -1, 0, 100, 6558260, 6575736, -65536, 16896, -1, 3, 1 },
    { 3, 0, 500, 32772660, 6575736, -65536, 16896, -1, 2, 0 },
    { 1, 0, 100, 6623796, 6641272, -82432, 16896, -1, 3, 1 },
    { 1, 8, 100, 6623796, 6641272, -65536, 0, 0, 3, 1 },
};
static u32 test_func_8004E300_1_0(u32 row)
{
    const struct func_8004E300_1_0_case* c = &func_8004E300_1_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.state = 3;
    obj.unk6 = c->unk6;
    obj.collision_flags = c->collision_flags;
    obj.air_state = -1;
    obj.x_speed = 0x10000;
    obj.y_speed = -0x10000;
    obj.gravity = 0x4200;
    obj.x_pos.i.hi = c->hi;
    SPIKE_IMMUNE_SET(g_Player, 1);
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    FILL_ACTIVE(weapon_objects, 16, 0);
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.x_pos.val = c->x_pos;
    expected.y_pos.val = c->y_pos;
    expected.y_speed = c->y_speed;
    expected.gravity = c->gravity;
    expected.air_state = c->air_state;
    expected.state = c->state;
    expected.on_screen = c->on_screen;
    player_expected = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    func_8004E300(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    return 1;
}
struct func_8004E300_1_1_case {
    u32 full;
    u32 expected[6];
};
static const struct func_8004E300_1_1_case func_8004E300_1_1_cases[] = {
    { 1, { 2u, 0xBu, 0xFFFFFF8Fu, 1u, 1u, 0x366Au } },
    { 0, { 2u, 0xAu, 0xFFFFFF8Fu, 1u, 0x41u, 0x366Au } },
};
static u32 test_func_8004E300_1_1(u32 row)
{
    const struct func_8004E300_1_1_case* c = &func_8004E300_1_1_cases[row];
    u32 observed_values[6];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    u8 pools_full;
    struct ShotObj shots_expected[32];
    struct VisualObj visuals_before[32];
    u8 full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.state = 3;
    obj.unk6 = 1;
    obj.collision_flags = 8;
    obj.unk7C = 11;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos = obj.y_pos;
    g_Player.unk54 = (const u32*)&shell_crawler_body_box;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    cur_random = 0x1234;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 0xA;
    }
    if (!full) {
        shots_expected[31].unk42 = OBJECT_CLUT(0x7885);
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
        shots_expected[31].x_vel.val = 0x10000;
    }
    expected = obj;
    expected.state = 2;
    expected.on_screen = 1;
    if (!full) {
        expected.unk7C = 10;
    }
    player_expected = g_Player;
    player_expected.hp = -113;
    player_expected.hurt_type = 1;
    engine_before = engine_obj;
    background_before = background_objects[0];
    func_8004E300(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    assert(cur_random == 0x366A);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)g_Player.hp;
    observed_values[3] = (u32)g_Player.hurt_type;
    observed_values[4] = (u32)shot_objects[31].active;
    observed_values[5] = (u32)cur_random;
    return c_test_observe(1, row, observed_values, c->expected, 6);
}
static u32 test_func_8004E300_1(u32 index)
{
    if (index < 4)
        return test_func_8004E300_1_0(index);
    index -= 4;
    return test_func_8004E300_1_1(index);
}

struct shell_crawler_main_0_case {
    u32 hi;
};
static const struct shell_crawler_main_0_case shell_crawler_main_0_cases[] = {
    { 3087 },
    { 3568 },
    { 4111 },
    { 4592 },
    { 4885 },
    { 5360 },
    { 5651 },
    { 6097 },
};
static u32 test_shell_crawler_main_0(u32 row)
{
    const struct shell_crawler_main_0_case* c = &shell_crawler_main_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.x_pos.i.hi = c->hi;
    obj.unk6 = 1;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    engine_obj.character_state.bytes[0] = 1;
    expected = obj;
    expected.state = 3;
    expected.unk6 = 0;
    player_expected = g_Player;
    engine_before = engine_obj;
    shell_crawler_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
static const u32 shell_crawler_main_1_expected[] = { 1u, 9u, C_TEST_STEP(0x10005u), 1u };
static u32 test_shell_crawler_main_1(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.air_state = 1;
    obj.unk7C = 10;
    set_animation(&obj, 5);
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    engine_obj.character_state.bytes[0] = 1;
    SPIKE_IMMUNE_SET(g_Player, 1);
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    FILL_ACTIVE(weapon_objects, 16, 0);
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk7C = 9;
    expected.animation_step.fields.duration = 5;
    expected.on_screen = 1;
    player_expected = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    shell_crawler_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)obj.on_screen;
    return c_test_observe(1, row, observed_values, shell_crawler_main_1_expected, 4);
}
static u32 test_shell_crawler_main(u32 index)
{
    if (index < 8)
        return test_shell_crawler_main_0(index);
    index -= 8;
    return test_shell_crawler_main_1(index);
}

struct shell_crawler_shell_1_0_case {
    u32 obj_unk6, expected_unk6;
};
static const struct shell_crawler_shell_1_0_case shell_crawler_shell_1_0_cases[] = {
    { -1, -1 },
    { 3, 3 },
};
static u32 test_shell_crawler_shell_1_0(u32 row)
{
    const struct shell_crawler_shell_1_0_case* c = &shell_crawler_shell_1_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 change_box;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.unk5 = 3;
    obj.unk6 = c->obj_unk6;
    obj.unk7C = 7;
    obj.ext.main_0.background_relative = 0xFF;
    set_animation(&obj, 5);
    obj.animation_cursor = (const u8*)&shell_crawler_animations[5][0];
    obj.animation_step = shell_crawler_animations[5][0];
    expected = obj;
    expected.unk6 = c->expected_unk6;
    expected.unk7C = 7;
    expected.unk5 = 3;
    expected.ext.main_0.background_relative = 255;
    expected.ext.main_0.flags[0] = 0;
    change_box = 0;
    if (change_box) {
        expected.collision_data = D_801060F0;
    }
    if (change_box) {
        expected.hurt_box = &shell_crawler_shell_box;
    }
    if (change_box) {
        expected.attack_box = &shell_crawler_shell_box;
    }
    expected.animation_step.fields.duration = 5;
    player_expected = g_Player;
    engine_before = engine_obj;
    shell_crawler_shell(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
struct shell_crawler_shell_1_1_case {
    u32 obj_unk7C, unk6, expected_unk7C, reset_anim, duration;
    u32 expected[5];
};
static const struct shell_crawler_shell_1_1_case shell_crawler_shell_1_1_cases[] = {
    { 2, 1, 1, 0, 1, { 1u, 1u, C_TEST_STEP(0x14010101u), 0xFFu, 0u } },
    { 1, 2, 0, 1, 5, { 2u, 0u, C_TEST_STEP(0x18010005u), 0xFFu, 0u } },
};
static u32 test_shell_crawler_shell_1_1(u32 row)
{
    const struct shell_crawler_shell_1_1_case* c = &shell_crawler_shell_1_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 change_box, reset_anim;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.unk7C = c->obj_unk7C;
    obj.ext.main_0.background_relative = 0xFF;
    set_animation(&obj, 5);
    obj.animation_cursor = (const u8*)&shell_crawler_animations[5][3];
    obj.animation_step = shell_crawler_animations[5][3];
    expected = obj;
    expected.unk6 = c->unk6;
    expected.unk7C = c->expected_unk7C;
    expected.unk5 = 3;
    expected.ext.main_0.background_relative = 255;
    expected.ext.main_0.flags[0] = 0;
    change_box = 1;
    if (change_box) {
        expected.collision_data = D_801060F0;
    }
    if (change_box) {
        expected.hurt_box = &shell_crawler_shell_box;
    }
    if (change_box) {
        expected.attack_box = &shell_crawler_shell_box;
    }
    reset_anim = c->reset_anim;
    if (reset_anim) {
        set_animation(&expected, 6);
    }
    expected.animation_step.fields.duration = c->duration;
    player_expected = g_Player;
    engine_before = engine_obj;
    shell_crawler_shell(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)obj.ext.main_0.background_relative;
    observed_values[4] = (u32)obj.ext.main_0.flags[0];
    return c_test_observe(1, row, observed_values, c->expected, 5);
}
static const u32 shell_crawler_shell_1_2_expected[] = { 0u, 7u, C_TEST_STEP(0x1010007u), 0xFEu, 0x78u };
static u32 test_shell_crawler_shell_1_2(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 change_box;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)shell_crawler_animations;
    obj.terrain_box = &shell_crawler_terrain_box;
    obj.hurt_box = &shell_crawler_body_box;
    obj.attack_box = &shell_crawler_body_box;
    obj.collision_data = D_801069F4;
    set_animation(&obj, 1);
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7C = 7;
    obj.ext.main_0.background_relative = 0xFF;
    set_animation(&obj, 6);
    obj.animation_cursor = (const u8*)&shell_crawler_animations[6][9];
    obj.animation_step = shell_crawler_animations[6][9];
    expected = obj;
    expected.unk6 = 0;
    expected.unk7C = 7;
    expected.unk5 = 1;
    expected.ext.main_0.background_relative = 254;
    expected.ext.main_0.flags[0] = 120;
    change_box = 0;
    if (change_box) {
        expected.collision_data = D_801060F0;
    }
    if (change_box) {
        expected.hurt_box = &shell_crawler_shell_box;
    }
    if (change_box) {
        expected.attack_box = &shell_crawler_shell_box;
    }
    set_animation(&expected, 1);
    expected.animation_step.fields.duration = 7;
    player_expected = g_Player;
    engine_before = engine_obj;
    shell_crawler_shell(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)obj.ext.main_0.background_relative;
    observed_values[4] = (u32)obj.ext.main_0.flags[0];
    return c_test_observe(2, row, observed_values, shell_crawler_shell_1_2_expected, 5);
}
static u32 test_shell_crawler_shell_1(u32 index)
{
    if (index < 2)
        return test_shell_crawler_shell_1_0(index);
    index -= 2;
    if (index < 2)
        return test_shell_crawler_shell_1_1(index);
    index -= 2;
    return test_shell_crawler_shell_1_2(index);
}

#define SC(step, sub) (state_reset(step, sub, 0), so.id = 15, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
#define SC_TIMERS() (state_extra = so.ext.main_0.index | so.ext.main_0.flags[1] << 8 | so.ext.main_0.background_relative << 16 | (u32)so.ext.main_0.flags[0] << 24)
#define SC_PLAYER(x, y) (g_Player.x_pos.i.hi = x, g_Player.y_pos.i.hi = y)
#define HOP(count, face, px, py) (SC(1, 1), so.ext.main_0.index = count, so.unk15 = face, SC_PLAYER(px, py), func_8004D9CC(&so), SC_TIMERS())
static void sc_hop_busy(void) { SC(1, 1), so.ext.main_0.background_relative = 2, func_8004D9CC(&so), SC_TIMERS(); }
static void sc_hop_cooldown(void) { SC(1, 1), so.ext.main_0.flags[1] = 3, func_8004D9CC(&so), SC_TIMERS(); }
static void sc_hop_player_level_far(void) { HOP(9, 0, 0x80, 0); }
static void sc_hop_fires(void) { HOP(0x3C, PLAYER_FACING_RIGHT, 0x80, 0x70); }
static void sc_hop_right_far(void) { HOP(5, PLAYER_FACING_RIGHT, 0xD0, 0x60); }
static void sc_hop_left_near(void) { HOP(5, 0, 0x40, 0x60); }
static void sc_hop_left_far(void) { HOP(5, 0, 0x30, 0x60); }
static void sc_weapon(u32 slot, u32 id, s16 x, s16 y)
{
    weapon_objects[slot].active = 1;
    weapon_objects[slot].id = id;
    weapon_objects[slot].x_pos.i.hi = x;
    weapon_objects[slot].y_pos.i.hi = y;
}
#define GUARD(face, player_face, px) (SC(1, 1), so.unk15 = face, g_Player.unk15 = player_face, SC_PLAYER(px, 0x60))
static void sc_guard_busy(void) { SC(1, 1), so.ext.main_0.background_relative = 1, func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_cooldown(void) { SC(1, 1), so.ext.main_0.flags[0] = 4, func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_right_player_turned(void) { GUARD(PLAYER_FACING_RIGHT, PLAYER_FACING_RIGHT, 0x100), sc_weapon(0, 0, 0x90, 0x60), func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_right_player_level(void) { GUARD(PLAYER_FACING_RIGHT, 0, 0x80), sc_weapon(0, 0, 0x90, 0x60), func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_right_shot(void)
{
    GUARD(PLAYER_FACING_RIGHT, 0, 0x100);
    sc_weapon(1, 1, 0x90, 0x60);
    sc_weapon(2, 0, 0x90, 0x78);
    sc_weapon(3, 0, 0x100, 0x5C);
    sc_weapon(4, 0, 0xFF, 0x60);
    func_8004DCB0(&so);
    SC_TIMERS();
}
static void sc_guard_left_player_turned(void) { GUARD(0, 0, 0), sc_weapon(0, 0, 0x70, 0x60), func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_left_player_level(void) { GUARD(0, PLAYER_FACING_RIGHT, 0x80), sc_weapon(0, 0, 0x70, 0x60), func_8004DCB0(&so), SC_TIMERS(); }
static void sc_guard_left_shot(void)
{
    GUARD(0, PLAYER_FACING_RIGHT, 0);
    sc_weapon(1, 1, 0x70, 0x60);
    sc_weapon(2, 0, 0x70, 0x48);
    sc_weapon(3, 0, 0, 0x64);
    sc_weapon(4, 0, 1, 0x60);
    func_8004DCB0(&so);
    SC_TIMERS();
}
static void sc_jump_takeoff(void) { SC(5, 0), so.animation_step.fields.event = 1, shell_crawler_hop(&so); }
static void sc_jump_rising(void) { SC(5, 1), so.y_speed = 0x10000, so.gravity = 0x4200, shell_crawler_hop(&so); }
static void sc_jump_apex(void) { SC(5, 1), so.y_speed = 0x1000, so.gravity = 0x4200, shell_crawler_hop(&so); }
static void sc_land_falling(void) { SC(2, 0), so.gravity = 0x4200, shell_crawler_land(&so); }
static void sc_land_touchdown(void) { SC(2, 0), so.x_speed = 0x10000, so.collision_flags = 8, shell_crawler_land(&so); }
static void sc_land_recovered(void) { SC(2, 1), so.air_state = -1, shell_crawler_land(&so); }
static void sc_land_recovering(void) { SC(2, 1), so.air_state = -1, so.animation_step.fields.relative_step = 1, shell_crawler_land(&so); }
static void sc_walk_start_right(void) { SC(1, 0), so.unk15 = PLAYER_FACING_RIGHT, shell_crawler_walk(&so); }
static void sc_walk_start_left_wall(void) { SC(1, 0), so.collision_flags = 2, shell_crawler_walk(&so); }
static void sc_walk_right_wall(void) { SC(1, 1), so.unk15 = PLAYER_FACING_RIGHT, so.x_speed = 0x6000, so.collision_flags = 1, shell_crawler_walk(&so); }
static void sc_walk_left(void) { SC(1, 1), so.x_speed = -0x6000, shell_crawler_walk(&so); }
static void sc_shell_close(void) { SC(3, 0), shell_crawler_shell(&so); }
static void sc_shell_opening(void) { SC(3, 2), so.animation_step.fields.relative_step = 1, shell_crawler_shell(&so); }
static void sc_frozen_start(void) { SC(1, 0), so.state = 3, func_8004E300(&so), state_extra = so.state; }
static void sc_frozen_shattered(void)
{
    SC(1, 1);
    so.state = 3;
    so.hp = 3;
    so.collision_flags = 8;
    state_hit(&so, 0, 0, 1);
    func_8004E300(&so);
    state_extra = so.state;
}
static void sc_thaw_wait(void) { SC(1, 0), so.state = 4, so.unk7C = 5, func_8004E490(&so), state_extra = so.state; }
static void sc_thaw_burst(void) { SC(1, 0), so.state = 4, so.unk7C = 1, func_8004E490(&so), state_extra = so.state; }
#define INIT(kind, px) (SC(1, 0), so.state = 0, so.unk2 = kind, SC_PLAYER(px, 0), func_8004E55C(&so), state_extra = so.state)
static void sc_init_walker(void) { INIT(0, 0); }
static void sc_init_buried(void) { INIT(2, 0x80); }
static void sc_init_kind_4(void) { INIT(4, 0); }
#define BURIED(x, attribute) (SC(0, 0), so.state = 5, so.unk2 = 2, so.x_pos.i.hi = x, state_terrain(attribute), shell_crawler_update(&so), state_extra = so.state)
static void sc_buried_wait(void) { BURIED(0x80, 0x38); }
static void sc_buried_emerge(void) { BURIED(0x80, 0); }
static void sc_buried_off_screen(void) { BURIED(0x200, 0x38); }
static void sc_despawn(void) { SC(3, 1), so.active = 0x41, so.state = 2, shell_crawler_update(&so), state_extra = so.state; }
#define MAIN(x, stage_id, flag) (SC(5, 0), so.air_state = 1, so.x_pos.i.hi = x, engine_obj.stage = stage_id, engine_obj.substage = 1, engine_obj.character_state.bytes[0] = flag, shell_crawler_main(&so), state_extra = so.state)
static void sc_main_above_zones(void) { MAIN(0x17D2, 2, 1); }
static void sc_main_flag_clear(void) { MAIN(0x80, 2, 0); }
static void sc_main_defeated(void)
{
    SC(5, 0);
    so.active = 0x41;
    so.air_state = 1;
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    engine_obj.stage = 0;
    shell_crawler_main(&so);
    state_extra = so.state | misc_objects[3].active << 8;
}

static void (*const shell_crawler_states_cases[])(void) = {
    sc_hop_busy,
    sc_hop_cooldown,
    sc_hop_player_level_far,
    sc_hop_fires,
    sc_hop_right_far,
    sc_hop_left_near,
    sc_hop_left_far,
    sc_guard_busy,
    sc_guard_cooldown,
    sc_guard_right_player_turned,
    sc_guard_right_player_level,
    sc_guard_right_shot,
    sc_guard_left_player_turned,
    sc_guard_left_player_level,
    sc_guard_left_shot,
    sc_jump_takeoff,
    sc_jump_rising,
    sc_jump_apex,
    sc_land_falling,
    sc_land_touchdown,
    sc_land_recovered,
    sc_land_recovering,
    sc_walk_start_right,
    sc_walk_start_left_wall,
    sc_walk_right_wall,
    sc_walk_left,
    sc_shell_close,
    sc_shell_opening,
    sc_frozen_start,
    sc_frozen_shattered,
    sc_thaw_wait,
    sc_thaw_burst,
    sc_init_walker,
    sc_init_buried,
    sc_init_kind_4,
    sc_buried_wait,
    sc_buried_emerge,
    sc_buried_off_screen,
    sc_despawn,
    sc_main_above_zones,
    sc_main_flag_clear,
    sc_main_defeated,
};
static const u32 shell_crawler_states_expected[] = {
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x20000u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 0x4007u, 0u, 0x20000u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 6u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x3000000u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u,
    3u, 0u, 0x800000u, 0u, 0u, 0u, 0x4005u, 0u, 0x10000u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    3u, 0u, 0x800000u, 0u, 0u, 0u, 5u, 0u, 0x10000u, 0u,
    0x105u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x105u, 0u, 0x800000u, 0u, 0xBE00u, 0x420000u, 0u, 0u, 0u, 0u,
    0xFF000002u, 0u, 0x800000u, 0u, 0u, 0x420000u, 3u, 0u, 0u, 0u,
    2u, 0u, 0x800000u, 0u, 0xFFFFBE00u, 0x420000u, 0u, 0u, 0u, 0u,
    0x102u, 0u, 0x810000u, 0u, 0u, 0u, 4u, 0u, 0u, 0u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u,
    0xFF000102u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x101u, 0u, 0x806000u, 0x6000u, 0u, 0u, 0x4001u, 3u, 0u, 0u,
    0x101u, 0u, 0x7FA000u, 0x6000u, 0u, 0u, 0x4001u, 3u, 0u, 0u,
    0x101u, 0u, 0x806000u, 0xFFFFA000u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x101u, 0u, 0x7FA000u, 0xFFFFA000u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x103u, 0x3Bu, 0x800000u, 0u, 0u, 0u, 5u, 0u, 0u, 0u,
    0x203u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0xFF000101u, 0u, 0x800000u, 0u, 0xFFFFBE00u, 0x420000u, 0xDu, 0u, 3u, 0u,
    0x101u, 0xAu, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x20001u, 2u, 0x412100u,
    1u, 4u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 4u, 0u,
    1u, 0xAu, 0x800000u, 0u, 0u, 0u, 0u, 0u, 2u, 0x410000u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 1u, 0x30003u, 1u, 0u,
    1u, 0u, 0x880000u, 0u, 0u, 0u, 0x4000u, 0x30000u, 5u, 0u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 1u, 0x30003u, 1u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 5u, 0u,
    1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 3u, 1u, 0u,
    0u, 0u, 0x2000000u, 0u, 0u, 0u, 0u, 0u, 2u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x1000005u, 0u, 0x17D20000u, 0u, 0u, 0u, 0u, 0u, 2u, 0u,
    0x1000005u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 1u, 0u,
    0x1000005u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 1u, 0x4102u, 0x41002100u,
};
static u32 test_shell_crawler_states(u32 row)
{
    return state_run(shell_crawler_states_cases[row], row, &shell_crawler_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "shell_crawler_states", 0, 0, COUNT(shell_crawler_states_cases), test_shell_crawler_states },
    { "shell_crawler_check_jump", NULL, shell_crawler_check_jump_cases_expected, COUNT(shell_crawler_check_jump_cases_expected), shell_crawler_check_jump_cases_row },
    { "shell_crawler_shoot_events", NULL, shell_crawler_shoot_events_cases_expected, COUNT(shell_crawler_shoot_events_cases_expected), shell_case },
    { "shell_expiry_full_pool", shell_expiry_full_pool_cases, shell_expiry_full_pool_cases_expected, COUNT(shell_expiry_full_pool_cases), 0 },
    { "func_8004E300_1", 0, 0, 6, test_func_8004E300_1 },
    { "shell_crawler_main", 0, 0, 9, test_shell_crawler_main },
    { "shell_crawler_shell_1", 0, 0, 5, test_shell_crawler_shell_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(shell_crawler_states_cases) + COUNT(shell_crawler_check_jump_cases_expected) + COUNT(shell_crawler_shoot_events_cases_expected) + COUNT(shell_expiry_full_pool_cases) + 6 + 9 + 5;
