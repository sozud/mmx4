#include "test_runtime.h"
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
    JUMP_RIGHT };
static const struct JumpInput inputs[] = {
    { 1, 1, 5, 0, 0, 0 },
    { 0, 0, 5, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0 },
    { 0, 1, 5, 0, 0, 1 },
    { 0, 1, 5, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 0 },
    { 0, 1, 7, 0, 0x40, 0 },
};
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[2] = { 0, 0x39 };
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
        expected.unk15 = 0x40;
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
    assert(tilemap[0] == 1 && attributes[0] == 0 && attributes[1] == 0x39 && layout_width == 16 && layout_size == 256);

    if (observation == 0)
        return soldier.collision_flags | ((u32)(u8)soldier.unk5 << 8) | ((u32)(u8)soldier.air_state << 16)
            | ((u32)(u8)soldier.unk15 << 24);
    return (u16)soldier.y_pos.i.hi | ((u32)(u8)soldier.unk6C << 16) | ((u32)(u8)soldier.unk6E << 24);
}

#define OBSERVE(name, field)                                   \
    static u32 shell_crawler_check_jump_##name##_##field(void) \
    {                                                          \
        return check(name, field);                             \
    }
#define CASE(name) OBSERVE(name, 0) OBSERVE(name, 1)
CASE(AIRBORNE)
CASE(FALL)
CASE(GROUND_AHEAD)
CASE(TURN)
CASE(WALL)
CASE(JUMP_LEFT)
CASE(JUMP_RIGHT)
#define ENTRY(name) shell_crawler_check_jump_##name##_0, shell_crawler_check_jump_##name##_1,
static const CTestCase shell_crawler_check_jump_cases[]
    = {
          ENTRY(AIRBORNE) ENTRY(FALL) ENTRY(GROUND_AHEAD) ENTRY(TURN) ENTRY(WALL) ENTRY(JUMP_LEFT) ENTRY(JUMP_RIGHT)
      };
static const u32 shell_crawler_check_jump_cases_expected[] = { 0x10200u, 0x6Bu, 0xFF0200u, 0x8006Bu, 0x208u, 0x8006Bu, 0x40000208u, 0x8006Bu, 0x20Eu, 0x8006Bu, 0x10508u, 0x8006Bu, 0x40010508u, 0x8006Bu };
#undef OBSERVE
#undef CASE
#undef ENTRY

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
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 7;
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
    obj.unk15 = 0x40;
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
                s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 0;
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
#define CASE(m)                                           \
    static u32 shell_crawler_shoot_events_shell_##m(void) \
    {                                                     \
        return shell_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) shell_crawler_shoot_events_shell_##m,
static const CTestCase shell_crawler_shoot_events_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 shell_crawler_shoot_events_cases_expected[] = { 0x10202u, 0x410202u, 0x10101u, 0x10202u, 0x410202u };
#undef CASE
#undef ENTRY

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

struct func_8004E300_0_case {
    u32 unk6;
    u32 expected[7];
};
static const struct func_8004E300_0_case func_8004E300_0_cases[] = {
    { -1, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u } },
    { 1, { 0u, 0u, 0u, 1u, 0u, 0u, 0u } },
};
static u32 test_func_8004E300_0(u32 row)
{
    const struct func_8004E300_0_case* c = &func_8004E300_0_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.unk6 = c->unk6;
    obj.collision_flags = 0;
    func_8004E300(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct func_8004E300_1_0_case {
    u32 unk6, collision_flags, hi, x_pos, y_pos, y_speed, gravity, air_state, state, on_screen;
    u32 expected[4];
};
static const struct func_8004E300_1_0_case func_8004E300_1_0_cases[] = {
    { -1, 0, 100, 6558260, 6575736, -65536, 16896, -1, 3, 1, { 3u, 0x641234u, 0x645678u, 0xFFFF0000u } },
    { 3, 0, 500, 32772660, 6575736, -65536, 16896, -1, 2, 0, { 2u, 0x1F41234u, 0x645678u, 0xFFFF0000u } },
    { 1, 0, 100, 6623796, 6641272, -82432, 16896, -1, 3, 1, { 3u, 0x651234u, 0x655678u, 0xFFFEBE00u } },
    { 1, 8, 100, 6623796, 6641272, -65536, 0, 0, 3, 1, { 3u, 0x651234u, 0x655678u, 0xFFFF0000u } },
};
static u32 test_func_8004E300_1_0(u32 row)
{
    const struct func_8004E300_1_0_case* c = &func_8004E300_1_0_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    u8 pools_full;
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
    g_Player.spike_immune = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
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
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.y_pos.val;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
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
        shots_expected[31].unk42 = 0x7885;
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

static const u32 func_8004E490_expected[] = { 2u, 0xAu };
static u32 test_func_8004E490(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    obj.unk7C = 1;
    func_8004E490(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, func_8004E490_expected, 2);
}

struct shell_crawler_main_0_case {
    u32 hi;
    u32 expected[3];
};
static const struct shell_crawler_main_0_case shell_crawler_main_0_cases[] = {
    { 3087, { 3u, 0u, 0xC0F1234u } },
    { 3568, { 3u, 0u, 0xDF01234u } },
    { 4111, { 3u, 0u, 0x100F1234u } },
    { 4592, { 3u, 0u, 0x11F01234u } },
    { 4885, { 3u, 0u, 0x13151234u } },
    { 5360, { 3u, 0u, 0x14F01234u } },
    { 5651, { 3u, 0u, 0x16131234u } },
    { 6097, { 3u, 0u, 0x17D11234u } },
};
static u32 test_shell_crawler_main_0(u32 row)
{
    const struct shell_crawler_main_0_case* c = &shell_crawler_main_0_cases[row];
    u32 observed_values[3];
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
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
static const u32 shell_crawler_main_1_expected[] = { 1u, 9u, 0x10005u, 1u };
static u32 test_shell_crawler_main_1(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    u8 pools_full;
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
    g_Player.spike_immune = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
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

static const u32 shell_crawler_shell_0_expected[] = { 0u, 0u, 0u, 0xFFFFFFFFu, 0u };
static u32 test_shell_crawler_shell_0(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shell_crawler_body_box, 0, sizeof(shell_crawler_body_box));
    memset(&shell_crawler_shell_box, 0, sizeof(shell_crawler_shell_box));
    obj.unk6 = -1;
    shell_crawler_shell(&obj);
    observed_values[0] = (u32)obj.ext.main_0.background_relative;
    observed_values[1] = (u32)obj.ext.main_0.flags[0];
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, shell_crawler_shell_0_expected, 5);
}

struct shell_crawler_shell_1_0_case {
    u32 obj_unk6, expected_unk6;
    u32 expected[5];
};
static const struct shell_crawler_shell_1_0_case shell_crawler_shell_1_0_cases[] = {
    { -1, -1, { 0xFFFFFFFFu, 7u, 0x10005u, 0xFFu, 0u } },
    { 3, 3, { 3u, 7u, 0x10005u, 0xFFu, 0u } },
};
static u32 test_shell_crawler_shell_1_0(u32 row)
{
    const struct shell_crawler_shell_1_0_case* c = &shell_crawler_shell_1_0_cases[row];
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
    reset_anim = 0;
    if (reset_anim) {
        set_animation(&expected, 6);
    }
    expected.animation_step.fields.duration = 5;
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
    return c_test_observe(0, row, observed_values, c->expected, 5);
}
struct shell_crawler_shell_1_1_case {
    u32 obj_unk7C, unk6, expected_unk7C, reset_anim, duration;
    u32 expected[5];
};
static const struct shell_crawler_shell_1_1_case shell_crawler_shell_1_1_cases[] = {
    { 2, 1, 1, 0, 1, { 1u, 1u, 0x14010101u, 0xFFu, 0u } },
    { 1, 2, 0, 1, 5, { 2u, 0u, 0x18010005u, 0xFFu, 0u } },
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
static const u32 shell_crawler_shell_1_2_expected[] = { 0u, 7u, 0x1010007u, 0xFEu, 0x78u };
static u32 test_shell_crawler_shell_1_2(u32 row)
{
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
    reset_anim = 1;
    if (reset_anim) {
        set_animation(&expected, 1);
    }
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

const struct CTestGroup c_test_groups[] = {
    { "shell_crawler_check_jump", shell_crawler_check_jump_cases, shell_crawler_check_jump_cases_expected, COUNT(shell_crawler_check_jump_cases), 0 },
    { "shell_crawler_shoot_events", shell_crawler_shoot_events_cases, shell_crawler_shoot_events_cases_expected, COUNT(shell_crawler_shoot_events_cases), 0 },
    { "shell_expiry_full_pool", shell_expiry_full_pool_cases, shell_expiry_full_pool_cases_expected, COUNT(shell_expiry_full_pool_cases), 0 },
    { "func_8004E300_0", 0, 0, 2, test_func_8004E300_0 },
    { "func_8004E300_1", 0, 0, 6, test_func_8004E300_1 },
    { "func_8004E490", 0, 0, 1, test_func_8004E490 },
    { "shell_crawler_main", 0, 0, 9, test_shell_crawler_main },
    { "shell_crawler_shell_0", 0, 0, 1, test_shell_crawler_shell_0 },
    { "shell_crawler_shell_1", 0, 0, 5, test_shell_crawler_shell_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(shell_crawler_check_jump_cases) + COUNT(shell_crawler_shoot_events_cases) + COUNT(shell_expiry_full_pool_cases) + 2 + 6 + 1 + 9 + 1 + 5;
