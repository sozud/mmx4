#include "test_runtime.h"
extern union AnimationStep jet_stingray_anim_17[2];
extern struct AnimationTable12 jet_stingray_flyby_animations;

static u32 chase_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before;
    struct Unk_unk68 bounds = { 0, 0, 8, 8 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0;
    obj.unk70 = mode;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    obj.animation_table = (u32**)jet_stingray_animations;
    obj.animation_cursor = (u8*)&jet_stingray_anim_17[0];
    obj.animation_step = jet_stingray_anim_17[0];
    obj.unk68 = &bounds;
    g_Player.x_pos.i.hi = mode ? 140 : 99;
    before = obj;
    player_before = g_Player;
    ray_trap_chase(&obj);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.animation_step = obj.animation_step;
    before.unk6 = obj.unk6;
    before.unk15 = obj.unk15;
    before.x_vel = obj.x_vel;
    before.unk17 = obj.unk17;
    before.previous_animation_index = obj.previous_animation_index;
    assert(obj.animation_table == (u32**)jet_stingray_animations && obj.animation_cursor == (u8*)&jet_stingray_anim_17[0]);
    assert(jet_stingray_animations[17] == jet_stingray_anim_17);
    assert(jet_stingray_anim_17[0].packed == 0x45010002 && jet_stingray_anim_17[1].packed == 0x46000002);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(obj.unk68 == &bounds && bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 8 && bounds.unk3 == 8);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = obj.animation_step.packed;
        break;
    case 3:
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk15 << 16);
        break;
    case 4:
        actual = obj.x_vel.val;
        break;
    default:
        actual = obj.unk17 | ((u32)obj.previous_animation_index << 8);
        break;
    }
    return actual;
}
#define CHASE_CASE(m, n)                               \
    static u32 ray_chase_context_chase_##m##_##n(void) \
    {                                                  \
        return chase_case(m, n);                       \
    }
#define CHASE_MODE(m) CHASE_CASE(m, 0) CHASE_CASE(m, 1) CHASE_CASE(m, 2) CHASE_CASE(m, 3) CHASE_CASE(m, 4) CHASE_CASE(m, 5)
CHASE_MODE(0)
CHASE_MODE(1)
#define CHASE_ENTRY(m, n) ray_chase_context_chase_##m##_##n,
#define CHASE_ENTRIES(m) CHASE_ENTRY(m, 0) CHASE_ENTRY(m, 1) CHASE_ENTRY(m, 2) CHASE_ENTRY(m, 3) CHASE_ENTRY(m, 4) CHASE_ENTRY(m, 5)
static const CTestCase ray_chase_context_cases[]
    = { CHASE_ENTRIES(0) CHASE_ENTRIES(1) };
static const u32 ray_chase_context_cases_expected[] = { 0x651234u, 0x50D678u, 0x45010002u, 0x400102u, 0x0u, 0xFF11u, 0x651234u, 0x50D678u, 0x45010002u, 0x102u, 0x0u, 0xFF11u };
#undef CHASE_CASE
#undef CHASE_MODE
#undef CHASE_ENTRY
#undef CHASE_ENTRIES

static struct AnimationTable12 {
    union AnimationStep* entries[12];
    s32 count;
};

static u32 ride_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = mode == 1 ? 0 : 0x41;
    owner.id = 55;
    owner.state = 1;
    owner.ext.main_55.unk87 = 1;
    owner.x_pos.val = 120 * 65536 + 0x1111;
    owner.y_pos.val = 80 * 65536 + 0x2222;
    owner.animation_table = (const u8* const*)jet_stingray_flyby_animations.entries;
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 0;
    obj.unk7 = mode < 2 ? 3 : mode == 2 ? -1
        : mode == 3                     ? 0
        : mode == 4                     ? 1
                                        : 2;
    obj.unk7C = &owner;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk8C.bytes[0] = 7;
    obj.unk8C.bytes[1] = 0;
    obj.animation_table = (u32**)jet_stingray_flyby_animations.entries;
    obj.unk17 = 8;
    obj.previous_animation_index = 0x27;
    ANIMATED_OBJECT(&obj)->animation_cursor = (u32*)jet_stingray_flyby_animations.entries[8];
    obj.animation_step = jet_stingray_flyby_animations.entries[8][0];
    expected = obj;
    owner_before = owner;
    assert(obj.animation_step.packed == 0x2B010002);
    expected.animation_step.fields.duration = 1;
    if (mode == 1)
        expected.state = 2;
    else if (mode == 3) {
        expected.unk7 = 1;
        expected.x_vel.val = 0;
        expected.y_vel.val = 10 * 65536;
        expected.unk8C.bytes[1] = 1;
        expected.y_pos.val -= 10 * 65536;
    } else if (mode == 4) {
        expected.unk7 = 2;
        expected.y_vel.val = 0;
        expected.x_pos.val += 65536;
    } else if (mode == 5) {
        expected.unk7 = 0;
        expected.unk6 = 1;
    }
    func_800A19A8(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(jet_stingray_flyby_animations.count == 0x52);
    return obj.state | ((u32)(u8)obj.unk7 << 8) | ((u32)(u8)obj.unk6 << 16);
}
#define CASE(m)                                            \
    static u32 ray_trap_ride_owner_defaults_ride_##m(void) \
    {                                                      \
        return ride_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) ray_trap_ride_owner_defaults_ride_##m,
static const CTestCase ray_trap_ride_owner_defaults_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 ray_trap_ride_owner_defaults_cases_expected[] = { 0x301u, 0x302u, 0xFF01u, 0x101u, 0x201u, 0x10001u };
#undef CASE
#undef ENTRY

static u32 rebound(void)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 32768;
    obj.unk2C = 0x1000;
    obj.unk70 = 1;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    before = obj;
    ray_trap_fall(&obj);
    before.animation_step.fields.duration--;
    before.x_pos.val += 65536;
    before.y_pos.val -= 32768;
    before.unk5 = 4;
    before.unk6 = 0;
    before.x_vel.val = 0;
    before.y_vel.val = -3 * 65536;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.animation_step.fields.duration << 16);
}
static u32 rebound_test(void)
{
    return rebound();
}
static const CTestCase ray_trap_wall_rebound_cases[] = { rebound_test };
static const u32 ray_trap_wall_rebound_cases_expected[] = { 0x80004u };

static u32 stick(void)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 32768;
    obj.unk2C = 0x1000;
    obj.unk70 = 1;
    obj.unk8C.bytes[3] = 1;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    before = obj;
    ray_trap_fall(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val -= 32768;
    before.unk5 = 3;
    before.unk6 = 1;
    before.y_vel.val = 0;
    before.unk2C = 0;
    before.unk17 = 8;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = jet_stingray_animations[8];
    before.animation_step = *(union AnimationStep*)jet_stingray_animations[8];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.animation_step.fields.duration << 16);
}
static u32 stick_test(void)
{
    return stick();
}
static const CTestCase ray_trap_wall_stick_cases[] = { stick_test };
static const u32 ray_trap_wall_stick_cases_expected[] = { 0x20103u };

static const u32 inputs_0[2][12] = {
    { 255, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 },
    { 255, 2, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0 },
};
struct func_800A19A8_case {
    u32 expected[10];
};
static const struct func_800A19A8_case func_800A19A8_cases[] = {
    { { 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 2u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800A19A8(u32 row)
{
    const struct func_800A19A8_case* c = &func_800A19A8_cases[row];
    u32 observed_values[10];
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = inputs_0[row][0];
    obj.unk7 = inputs_0[row][1];
    obj.unk8C.bytes[1] = inputs_0[row][2];
    child_0.ext.main_55.unk87 = inputs_0[row][3];
    obj.unk6 = inputs_0[row][4];
    obj.timer = inputs_0[row][5];
    obj.unk8C.bytes[0] = inputs_0[row][6];
    child_0.x_pos.i.hi = inputs_0[row][7];
    obj.unk84.halves[0] = inputs_0[row][8];
    child_0.y_pos.i.hi = inputs_0[row][9];
    obj.unk84.halves[1] = inputs_0[row][10];
    child_0.active = inputs_0[row][11];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800A19A8(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.timer;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk8C.bytes[0];
    observed_values[5] = (u32)obj.unk8C.bytes[1];
    observed_values[6] = (u32)obj.x_pos.i.hi;
    observed_values[7] = (u32)obj.x_vel.val;
    observed_values[8] = (u32)obj.y_pos.i.hi;
    observed_values[9] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

static const u32 func_800A1B1C_0_expected[] = { 1u, 0u, 0u, 0x27u, 0x20u, 0x20u };
static u32 test_func_800A1B1C_0(u32 row)
{
    u32 observed_values[6];
    struct ShotObj before;
    struct MainObj owner_before;
    struct PlayerObj player_before;
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    child_0_present = 255;
    child_0.ext.main_55.unk88 = 247;
    obj.unk8A = 7;
    child_0.active = 1;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk7 = 0x27;
    before = obj;
    owner_before = child_0;
    player_before = g_Player;
    func_800A1B1C(&obj);
    before.unk84.halves[0] = 0x20;
    before.unk84.halves[1] = 0x20;
    before.x_pos.i.hi = 0x20;
    before.y_pos.i.hi = 0x20;
    before.animation_step.fields.duration = -1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&child_0, &owner_before, sizeof(child_0));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk15;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_800A1B1C_0_expected, 6);
}
static const u32 func_800A1B1C_1_expected[] = { 2u, 0x40u, 1u, 0u, 0x20u, 0x20u };
static u32 test_func_800A1B1C_1(u32 row)
{
    u32 observed_values[6];
    struct ShotObj before;
    struct MainObj owner_before;
    struct PlayerObj player_before;
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    child_0_present = 255;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk7 = 0x27;
    before = obj;
    owner_before = child_0;
    player_before = g_Player;
    func_800A1B1C(&obj);
    before.unk84.halves[0] = 0x20;
    before.unk84.halves[1] = 0x20;
    before.x_pos.i.hi = 0x20;
    before.y_pos.i.hi = 0x20;
    before.animation_step.fields.duration = -1;
    before.state = 2;
    before.unk7 = 0;
    before.unk15 = 0x40;
    before.unk6 = 1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&child_0, &owner_before, sizeof(child_0));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk15;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.y_pos.i.hi;
    return c_test_observe(1, row, observed_values, func_800A1B1C_1_expected, 6);
}
static u32 test_func_800A1B1C(u32 index)
{
    if (index < 1)
        return test_func_800A1B1C_0(index);
    index -= 1;
    return test_func_800A1B1C_1(index);
}

static const u32 ray_trap_chase_expected[] = { 0u, 0u, 0u, 0u, 0u };
static u32 test_ray_trap_chase(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.x_pos.i.hi = -28528;
    g_Player.x_pos.i.hi = -28704;
    obj.unk70 = 11;
    ray_trap_chase(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, ray_trap_chase_expected, 5);
}

static const u32 ray_trap_fall_expected[] = { 0u, 4u, 0u, 0u, 0xFFFD0000u };
static u32 test_ray_trap_fall(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk70 = 3;
    ray_trap_fall(&obj);
    observed_values[0] = (u32)obj.unk2C;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_vel.val;
    observed_values[4] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, ray_trap_fall_expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "ray_chase_context", ray_chase_context_cases, ray_chase_context_cases_expected, COUNT(ray_chase_context_cases), 0 },
    { "ray_trap_ride_owner_defaults", ray_trap_ride_owner_defaults_cases, ray_trap_ride_owner_defaults_cases_expected, COUNT(ray_trap_ride_owner_defaults_cases), 0 },
    { "ray_trap_wall_rebound", ray_trap_wall_rebound_cases, ray_trap_wall_rebound_cases_expected, COUNT(ray_trap_wall_rebound_cases), 0 },
    { "ray_trap_wall_stick", ray_trap_wall_stick_cases, ray_trap_wall_stick_cases_expected, COUNT(ray_trap_wall_stick_cases), 0 },
    { "func_800A19A8", 0, 0, 2, test_func_800A19A8 },
    { "func_800A1B1C", 0, 0, 2, test_func_800A1B1C },
    { "ray_trap_chase", 0, 0, 1, test_ray_trap_chase },
    { "ray_trap_fall", 0, 0, 1, test_ray_trap_fall },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ray_chase_context_cases) + COUNT(ray_trap_ride_owner_defaults_cases) + COUNT(ray_trap_wall_rebound_cases) + COUNT(ray_trap_wall_stick_cases) + 2 + 2 + 1 + 1;
