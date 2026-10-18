#include "test_runtime.h"
#include "main/shots/shot_55_general_shot.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern void* general_animations[46];
extern s8 general_shot_attack_boxes[][4];
extern s8 general_shot_boxes[3][4];
extern u8 D_8013B8DC[4];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 general_dust_animation_start_dust_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    u32 i, animation = mode == 0 ? 0x19 : 0x1C;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = mode == 0 ? 6 : 7;
    obj.unk5 = 0;
    obj.timer = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.relative_step = 0;
    before = obj;
    general_dust_start(&obj);
    before.unk5 = 1;
    before.timer = 0x19;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = general_animations[animation];
    before.animation_step = *(union AnimationStep*)general_animations[animation];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u16)obj.timer << 8) | ((u32)obj.unk17 << 24) : obj.animation_step.packed;
}
#define CASE(m, n)                                               \
    static u32 general_dust_animation_start_dust_##m##_##n(void) \
    {                                                            \
        return general_dust_animation_start_dust_case(m, n);     \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
#define ENTRY(m, n) general_dust_animation_start_dust_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase general_dust_animation_start_cases[]
    = { ENTRIES(0) ENTRIES(1) };
static const u32 general_dust_animation_start_cases_expected[] = { 0x19001901u, 0x47010001u, 0x1C001901u, 0x51010001u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 general_dust_event_expiry_dust_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk2 = mode == 2 ? 7 : 6;
    obj.timer = mode == 0 ? 2 : 1;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 25);
    if (mode != 3) {
        obj.animation_cursor = (void*)((u8*)general_animations[25] + 4);
        obj.animation_step = *(const union AnimationStep*)obj.animation_cursor;
        assert(obj.animation_step.packed == 0x48010001);
    }
    expected = obj;
    expected.animation_cursor = (void*)((u8*)obj.animation_cursor + 4);
    expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    if (mode != 3) {
        assert(expected.animation_step.packed == 0x49FE0101);
        expected.animation_step.fields.event = 0;
        expected.unk50.data = (u8*)&general_shot_attack_boxes[2];
        expected.timer--;
        if (mode == 1 || mode == 2) {
            u32 end = mode == 1 ? 26 : 29;
            expected.unk50.data = NULL;
            expected.unk5 = 2;
            expected.unk17 = end;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = general_animations[end];
            expected.animation_step = *(union AnimationStep*)general_animations[end];
        }
    }
    general_dust_burst(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.timer | ((u32)(u8)obj.unk5 << 16) | ((u32)obj.unk17 << 24);
}
#define CASE(m)                                         \
    static u32 general_dust_event_expiry_dust_##m(void) \
    {                                                   \
        return general_dust_event_expiry_dust_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) general_dust_event_expiry_dust_##m,
static const CTestCase general_dust_event_expiry_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 general_dust_event_expiry_cases_expected[] = { 0x19010001u, 0x1A020000u, 0x1D020000u, 0x19010001u };
#undef CASE
#undef ENTRY

static u32 wait_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    struct WeaponObj owner, owner_before;
    struct PlayerObj player_before;
    u32 i, orb = mode & 1;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = orb ? 4 : 3;
    obj.unk5 = 3;
    obj.unk90.u.lo = 0x7777;
    obj.unk8A = mode == 3 ? 1 : 2;
    obj.unk15 = mode == 3 ? 0x40 : 0;
    D_8013E198[2] = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    owner.x_pos.i.hi = mode == 2 ? 50 : 300;
    owner.active = 0x41;
    obj.unk7C = &owner;
    obj.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    before = obj;
    owner_before = owner;
    player_before = g_Player;
    if (orb) {
        general_orb_aim(&obj);
        before.unk8A = mode == 3 ? 0 : 1;
        if (mode == 3) {
            before.unk5 = 4;
            before.x_vel.val = 5 * 65536;
            before.y_vel.val = 0;
        }
    } else {
        general_fist_approach(&obj);
        before.x_pos.val += 65536;
        before.y_pos.val += 32768;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return observation == 0 ? (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16) : (u8)obj.unk5 | ((u32)(u16)obj.unk8A << 8);
}
#define CASE(m, n)                                                  \
    static u32 general_projectile_wait_context_wait_##m##_##n(void) \
    {                                                               \
        return wait_case(m, n);                                     \
    }
CASE(0, 0)
CASE(0, 1)
CASE(1, 0)
CASE(1, 1)
CASE(2, 0)
CASE(2, 1)
CASE(3, 0)
CASE(3, 1)
#define ENTRY(m, n) general_projectile_wait_context_wait_##m##_##n,
static const CTestCase general_projectile_wait_context_cases[]
    = { ENTRY(0, 0) ENTRY(0, 1) ENTRY(1, 0) ENTRY(1, 1) ENTRY(2, 0) ENTRY(2, 1) ENTRY(3, 0) ENTRY(3, 1) };
static const u32 general_projectile_wait_context_cases_expected[] = { 0xC80065u, 0x203u, 0xC80064u, 0x103u, 0xC80065u, 0x203u, 0xC80064u, 0x4u };
#undef CASE
#undef ENTRY

static const s8 subtypes[] = { 2, 9, 10, 11 };
static u32 thruster_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    struct MainObj parent, parent_before;
    u8 flags_before[4];
    u32 i, actual, animation;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memset(D_8013B8DC, 0x27, sizeof(D_8013B8DC));
    parent.active = 0x41;
    parent.id = 75;
    parent.state = 1;
    parent.unk15 = mode == 0 ? 0x40 : 0;
    parent.unk40 = 0x1A00;
    parent.unk42 = 0xD234;
    parent.bg_offset = -1;
    parent.unk16 = 5;
    parent.x_pos.val = 100 * 65536 + 0x1234;
    parent.y_pos.val = 200 * 65536 + 0x5678;
    parent.animation_table = (u32**)general_animations;
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = subtypes[mode];
    obj.unk7C = (struct WeaponObj*)&parent;
    obj.timer = mode == 3 ? 5 : 0;
    obj.unk84.shot_55.x = 3;
    obj.unk84.shot_55.y = -4;
    before = obj;
    parent_before = parent;
    memcpy(flags_before, D_8013B8DC, sizeof(flags_before));
    func_800AC8C4(&obj);
    animation = mode == 0 ? 0xD : mode == 1 ? 0x1E
                                            : 0x1F;
    before.state = obj.state;
    before.unk40 = parent.unk40;
    before.unk42 = parent.unk42;
    before.bg_offset = parent.bg_offset;
    before.unk15 = parent.unk15;
    before.animation_table = (u32**)general_animations;
    before.unk3C = (void*)parent.sprite_frames;
    before.unk16 = obj.unk16;
    before.unk60 = obj.unk60;
    before.unk75 = obj.unk75;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.unk18 = obj.unk18;
    before.unk1C = obj.unk1C;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.timer = obj.timer;
    before.unk8A = obj.unk8A;
    before.unk84 = obj.unk84;
    before.animation_step = obj.animation_step;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = general_animations[animation];
    before.unk50.data = mode == 0 ? (u8*)general_shot_boxes[1] : NULL;
    before.unk54 = mode == 0 ? (u8*)general_shot_boxes[2] : NULL;
    before.unk58.collision_bounds = mode == 0 ? D_801060F0 : NULL;
    before.unk68 = NULL;
    if (mode == 1)
        flags_before[0] = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(parent) / 4; i++)
        assert(((u32*)&parent)[i] == ((u32*)&parent_before)[i]);
    for (i = 0; i < sizeof(flags_before); i++)
        assert(D_8013B8DC[i] == flags_before[i]);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk16 << 8) | ((u32)(u8)obj.unk60 << 16) | ((u32)obj.unk75 << 24);
        break;
    case 1:
        actual = obj.x_pos.val;
        break;
    case 2:
        actual = obj.y_pos.val;
        break;
    case 3:
        actual = obj.x_vel.val;
        break;
    case 4:
        actual = obj.y_vel.val;
        break;
    case 5:
        actual = (u16)obj.timer | ((u32)(u16)obj.unk8A << 16);
        break;
    case 6:
        actual = obj.animation_step.packed;
        break;
    case 7:
        actual = obj.unk18.val;
        break;
    case 8:
        actual = obj.unk1C.val;
        break;
    default:
        actual = obj.unk84.value;
        break;
    }
    return actual;
}
#define THRUSTER_CASE(m, n)                                   \
    static u32 general_thruster_init_thruster_##m##_##n(void) \
    {                                                         \
        return thruster_case(m, n);                           \
    }
#define THRUSTER_MODE(m) THRUSTER_CASE(m, 0) THRUSTER_CASE(m, 1) THRUSTER_CASE(m, 2) THRUSTER_CASE(m, 3) THRUSTER_CASE(m, 4) THRUSTER_CASE(m, 5) THRUSTER_CASE(m, 6) THRUSTER_CASE(m, 7) THRUSTER_CASE(m, 8) THRUSTER_CASE(m, 9)
THRUSTER_MODE(0)
THRUSTER_MODE(1)
THRUSTER_MODE(2)
THRUSTER_MODE(3)
#define THRUSTER_ENTRY(m, n) general_thruster_init_thruster_##m##_##n,
#define THRUSTER_ENTRIES(m) THRUSTER_ENTRY(m, 0) THRUSTER_ENTRY(m, 1) THRUSTER_ENTRY(m, 2) THRUSTER_ENTRY(m, 3) THRUSTER_ENTRY(m, 4) THRUSTER_ENTRY(m, 5) THRUSTER_ENTRY(m, 6) THRUSTER_ENTRY(m, 7) THRUSTER_ENTRY(m, 8) THRUSTER_ENTRY(m, 9)
static const CTestCase general_thruster_init_cases[]
    = { THRUSTER_ENTRIES(0) THRUSTER_ENTRIES(1) THRUSTER_ENTRIES(2) THRUSTER_ENTRIES(3) };
static const u32 general_thruster_init_cases_expected[] = { 0x1060502u, 0xB41234u, 0xA05678u, 0x0u, 0x0u, 0x0u, 0x21000001u, 0x641234u, 0xC85678u, 0xA000B4u, 0x30502u, 0x491234u, 0xAE5678u, 0x0u, 0x0u, 0x0u, 0x52010001u, 0x641234u, 0xC85678u, 0xFFFC0003u, 0x30502u, 0x671234u, 0xC45678u, 0xFFFF0000u, 0x18000u, 0x1E0000u, 0x55010001u, 0x641234u, 0xC85678u, 0xFFFC0003u, 0x30502u, 0x671234u, 0xC45678u, 0xFFFF0000u, 0xFFFE8000u, 0xF0005u, 0x55010001u, 0x641234u, 0xC85678u, 0xFFFC0003u };
#undef THRUSTER_CASE
#undef THRUSTER_MODE
#undef THRUSTER_ENTRY
#undef THRUSTER_ENTRIES

static const u32 func_800AC8C4_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800AC8C4(u32 row)
{
    u32 observed_values[22];
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_8013B8DC, 0, sizeof(D_8013B8DC));
    child_0_present = 255;
    obj.unk2 = -1;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800AC8C4(&obj);
    observed_values[0] = (u32)D_8013B8DC[0];
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.timer;
    observed_values[4] = (u32)obj.unk15;
    observed_values[5] = (u32)obj.unk16;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.unk40;
    observed_values[9] = (u32)obj.unk42;
    observed_values[10] = (u32)obj.unk60;
    observed_values[11] = (u32)obj.unk75;
    observed_values[12] = (u32)obj.unk84.shot_55.x;
    observed_values[13] = (u32)obj.unk84.shot_55.y;
    observed_values[14] = (u32)obj.unk84.value;
    observed_values[15] = (u32)obj.unk8A;
    observed_values[16] = (u32)obj.x_pos.i.hi;
    observed_values[17] = (u32)obj.x_pos.val;
    observed_values[18] = (u32)obj.x_vel.val;
    observed_values[19] = (u32)obj.y_pos.i.hi;
    observed_values[20] = (u32)obj.y_pos.val;
    observed_values[21] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_800AC8C4_expected, 22);
}

static const u32 general_dust_burst_0_expected[] = { 0u, 0xFFu, 0u };
static u32 test_general_dust_burst_0(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.timer = 255;
    general_dust_burst(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.event;
    observed_values[1] = (u32)obj.timer;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, general_dust_burst_0_expected, 3);
}

static const u32 general_dust_burst_1_expected[] = { 0u, 0xFFu, 0u };
static u32 test_general_dust_burst_1(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.timer = 255;
    general_dust_burst(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.event;
    observed_values[1] = (u32)obj.timer;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, general_dust_burst_1_expected, 3);
}

static const u32 inputs_0[2][2] = {
    { -1, 0 },
    { 0, 0 },
};
struct general_dust_end_case {
    u32 expected[1];
};
static const struct general_dust_end_case general_dust_end_cases[] = {
    { { 0u } },
    { { 1u } },
};
static u32 test_general_dust_end(u32 row)
{
    const struct general_dust_end_case* c = &general_dust_end_cases[row];
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.relative_step = inputs_0[row][0];
    obj.state = inputs_0[row][1];
    general_dust_end(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 general_dust_start_expected[] = { 0u, 0u };
static u32 test_general_dust_start(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.relative_step = -1;
    general_dust_start(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, general_dust_start_expected, 2);
}

static const u32 general_fist_approach_expected[] = { 1u, 0x3Cu, 0u };
static u32 test_general_fist_approach(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    general_fist_approach(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk90.u.lo;
    observed_values[2] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, general_fist_approach_expected, 3);
}

static const u32 general_orb_aim_expected[] = { 1u, 0u, 0xFFFB0000u, 0u };
static u32 test_general_orb_aim(u32 row)
{
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk8A = 1;
    general_orb_aim(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk8A;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, general_orb_aim_expected, 4);
}

static const u32 general_orb_fly_expected[] = { 0u };
static u32 test_general_orb_fly(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    general_orb_fly(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, general_orb_fly_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "general_dust_animation_start", general_dust_animation_start_cases, general_dust_animation_start_cases_expected, COUNT(general_dust_animation_start_cases), 0 },
    { "general_dust_event_expiry", general_dust_event_expiry_cases, general_dust_event_expiry_cases_expected, COUNT(general_dust_event_expiry_cases), 0 },
    { "general_projectile_wait_context", general_projectile_wait_context_cases, general_projectile_wait_context_cases_expected, COUNT(general_projectile_wait_context_cases), 0 },
    { "general_thruster_init", general_thruster_init_cases, general_thruster_init_cases_expected, COUNT(general_thruster_init_cases), 0 },
    { "func_800AC8C4", 0, 0, 1, test_func_800AC8C4 },
    { "general_dust_burst_0", 0, 0, 1, test_general_dust_burst_0 },
    { "general_dust_burst_1", 0, 0, 1, test_general_dust_burst_1 },
    { "general_dust_end", 0, 0, 2, test_general_dust_end },
    { "general_dust_start", 0, 0, 1, test_general_dust_start },
    { "general_fist_approach", 0, 0, 1, test_general_fist_approach },
    { "general_orb_aim", 0, 0, 1, test_general_orb_aim },
    { "general_orb_fly", 0, 0, 1, test_general_orb_fly },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(general_dust_animation_start_cases) + COUNT(general_dust_event_expiry_cases) + COUNT(general_projectile_wait_context_cases) + COUNT(general_thruster_init_cases) + 1 + 1 + 1 + 2 + 1 + 1 + 1 + 1;
