#include "test_runtime.h"
extern u8 cannon_shell_hit_box[4], cannon_shell_flat_hit_box[4], cannon_shell_steep_hit_box[4];
extern u8 cannon_shell_terrain_box[4], cannon_shell_flat_terrain_box[4], cannon_shell_steep_terrain_box[4];

static u32 cannon_shell_animation_shell_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    const u8* terrain;
    const u8* hit;
    u32 i, actual, original_step, next_animation;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 1;
    obj.animation_table = (u32**)train_cannon_animations;
    obj.animation_cursor = (u8*)train_cannon_animations[7];
    obj.animation_step.packed = *(u32*)train_cannon_animations[7];
    obj.unk17 = 7;
    obj.previous_animation_index = 0x27;
    obj.unk84.value = mode == 3 ? -1 : mode;
    obj.x_vel.val = mode == 0 ? 4 * 65536 : mode == 1 ? 2 * 65536
                                                      : 65536;
    obj.y_vel.val = mode == 2 ? 4 * 65536 : 65536;
    obj.unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    obj.unk54 = obj.unk50.data = cannon_shell_hit_box;
    before = obj;
    original_step = *(u32*)train_cannon_animations[7];
    func_8009D588(&obj);
    if (mode == 3) {
        for (i = 0; i < sizeof(obj); i++)
            assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
        actual = observation == 0 ? (u32)obj.unk84.value : obj.animation_step.packed;
    } else {
        terrain = mode == 0 ? cannon_shell_flat_terrain_box : mode == 1 ? cannon_shell_terrain_box
                                                                        : cannon_shell_steep_terrain_box;
        hit = mode == 0 ? cannon_shell_flat_hit_box : mode == 1 ? cannon_shell_hit_box
                                                                : cannon_shell_steep_hit_box;
        next_animation = mode + 8;
        assert(obj.unk68 == (struct Unk_unk68*)terrain && obj.unk54 == hit && obj.unk50.data == hit);
        assert(obj.animation_cursor == (u8*)train_cannon_animations[next_animation]);
        before.unk84.value = obj.unk84.value;
        before.unk68 = (struct Unk_unk68*)terrain;
        before.unk54 = before.unk50.data = hit;
        before.animation_cursor = (u8*)train_cannon_animations[next_animation];
        before.animation_step = obj.animation_step;
        before.unk17 = next_animation;
        before.previous_animation_index = 0xFF;
        for (i = 0; i < sizeof(obj); i++)
            assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
        actual = observation == 0 ? (u32)obj.unk84.value : obj.animation_step.packed;
    }
    assert(*(u32*)train_cannon_animations[7] == original_step);
    return actual;
}
#define SHELL_CASE(m, n)                                    \
    static u32 cannon_shell_animation_shell_##m##_##n(void) \
    {                                                       \
        return cannon_shell_animation_shell_case(m, n);     \
    }
#define SHELL_MODE(m) SHELL_CASE(m, 0) SHELL_CASE(m, 1)
SHELL_MODE(0)
SHELL_MODE(1)
SHELL_MODE(2)
SHELL_MODE(3)
#define SHELL_ENTRY(m, n) cannon_shell_animation_shell_##m##_##n,
#define SHELL_ENTRIES(m) SHELL_ENTRY(m, 0) SHELL_ENTRY(m, 1)
static const CTestCase cannon_shell_animation_cases[]
    = { SHELL_ENTRIES(0) SHELL_ENTRIES(1) SHELL_ENTRIES(2) SHELL_ENTRIES(3) };
static const u32 cannon_shell_animation_cases_expected[] = { 0x1u, 0x29000001u, 0x2u, 0x2A000001u, 0x3u, 0x2B000001u, 0xFFFFFFFFu, 0x28000001u };
#undef SHELL_CASE
#undef SHELL_MODE
#undef SHELL_ENTRY
#undef SHELL_ENTRIES

static u32 cannon_shell_distance_animation_start_shell_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_expected;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 38;
    owner.state = 1;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    obj.active = 0x41;
    obj.id = 21;
    obj.state = 0;
    obj.unk2 = mode == 4 ? 3 : mode & 1;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 50 * 65536 + 0xBEEF;
    obj.y_pos.val = 60 * 65536 + 0xCAFE;
    obj.unk7C = &owner;
    obj.animation_table = (u32**)train_cannon_animations;
    obj.unk28 = 123;
    obj.unk2C = 456;
    obj.unk70 = 7;
    obj.unk84.value = 9;
    expected = obj;
    owner_before = owner;
    expected.x_pos.i.hi = mode == 0 || mode == 2 ? 118 : 110;
    expected.y_pos.i.hi = mode == 0 || mode == 2 ? 200 : 184;
    g_Player.x_pos.val = expected.x_pos.val + (mode == 4 ? -192 * 65536 : mode == 0 ? -16 * 65536
                                 : mode == 1                                        ? 16 * 65536
                                 : mode == 2                                        ? -160 * 65536
                                                                                    : 160 * 65536);
    player_expected = g_Player;
    expected.unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    expected.unk58.animation_steps = D_80105FF0;
    expected.unk60 = 3;
    expected.on_screen = 1;
    expected.unk5C = 1;
    expected.unk54 = cannon_shell_hit_box;
    expected.state = 1;
    expected.unk42 = 0x123;
    expected.unk50.data = mode == 0 || mode == 2 ? cannon_shell_hit_box : cannon_shell_flat_hit_box;
    expected.x_vel.val = -0x28000;
    expected.y_vel.val = 0x28000;
    expected.unk28 = 0;
    expected.unk84.value = 0;
    expected.unk70 = 0;
    expected.unk7 = 1;
    expected.unk2C = mode < 2 ? 0x28000 / 9 : mode == 2 ? 0x28000 / 32
        : mode == 3                                     ? 0x28000 / 19
                                                        : 0x28000;
    expected.unk17 = 7;
    expected.previous_animation_index = 0xFF;
    ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)train_cannon_animations[7];
    expected.animation_step.packed = *(u32*)train_cannon_animations[7];
    func_8009D23C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    return (u32)obj.unk2C;
}
#define CASE(m)                                                      \
    static u32 cannon_shell_distance_animation_start_shell_##m(void) \
    {                                                                \
        return cannon_shell_distance_animation_start_shell_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) cannon_shell_distance_animation_start_shell_##m,
static const CTestCase cannon_shell_distance_animation_start_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 cannon_shell_distance_animation_start_cases_expected[] = { 0x471Cu, 0x471Cu, 0x1400u, 0x21AFu, 0x28000u };
#undef CASE
#undef ENTRY

struct func_8009D588_case {
    u32 value, y_vel, x_vel;
    u32 expected[1];
};
static const struct func_8009D588_case func_8009D588_cases[] = {
    { 1, 22024, 541486, { 1u } },
    { 0, 0, 0, { 0u } },
    { 2, 0, 0, { 2u } },
    { 0, -744641, -260177, { 0u } },
};
static u32 test_func_8009D588(u32 row)
{
    const struct func_8009D588_case* c = &func_8009D588_cases[row];
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk84.value = c->value;
    obj.y_vel.val = c->y_vel;
    obj.x_vel.val = c->x_vel;
    func_8009D588(&obj);
    observed_values[0] = (u32)obj.unk84.value;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_shell_animation", cannon_shell_animation_cases, cannon_shell_animation_cases_expected, COUNT(cannon_shell_animation_cases), 0 },
    { "cannon_shell_distance_animation_start", cannon_shell_distance_animation_start_cases, cannon_shell_distance_animation_start_cases_expected, COUNT(cannon_shell_distance_animation_start_cases), 0 },
    { "func_8009D588", 0, 0, 4, test_func_8009D588 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cannon_shell_animation_cases) + COUNT(cannon_shell_distance_animation_start_cases) + 4;
