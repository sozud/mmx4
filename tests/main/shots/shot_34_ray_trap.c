#include "test_runtime.h"
#include "main/shots/shot_34_ray_trap.h"
#include "main/55C4.h"
#include "main/mains/main_56_jet_stingray.h"
void ray_trap_ride(struct ShotObj*);
extern union AnimationStep jet_stingray_anim_17[2];
struct AnimationTable12 {
    union AnimationStep* entries[12];
    s32 count;
};
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
static const u32 ray_chase_context_cases_expected[] = { 0x651234u, 0x50D678u, 0x45010002u, 0x400102u, 0x0u, 0xFF11u, 0x651234u, 0x50D678u, 0x45010002u, 0x102u, 0x0u, 0xFF11u };
static u32 ray_chase_context_cases_row(u32 row)
{
    return chase_case(row / 6, row % 6);
}

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
static const u32 ray_trap_ride_owner_defaults_cases_expected[] = { 0x301u, 0x302u, 0xFF01u, 0x101u, 0x201u, 0x10001u };

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

static const u32 func_800A1B1C_0_expected[] = { 1u, 0u, 0u, 0x27u, 0x20u, 0x20u };
static u32 test_func_800A1B1C_0(u32 row)
{
    u32 observed_values[6];
    struct ShotObj before;
    struct MainObj owner_before;
    struct PlayerObj player_before;
    struct ShotObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    child_0.ext.main_55.unk88 = 247;
    obj.unk8A = 7;
    child_0.active = 1;
    obj.unk7C = &child_0;
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
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk7C = &child_0;
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

#include "support/state_cases.h"

void ray_trap_check_airborne(struct ShotObj*);
static struct MainObj ray_owner;
#define ss state_room.shot
#define RAY(st, step, phase) (state_reset(step, phase, 0), memset(&ray_owner, 0, sizeof(ray_owner)), ray_owner.active = 1, ray_owner.x_pos.i.hi = 0x100, ray_owner.y_pos.i.hi = 0x80, ss.state = st, ss.unk7C = (struct WeaponObj*)&ray_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define RAY_SEEN() (state_extra = ss.unk8C.word ^ (u32)(u16)ss.timer << 16 ^ (u32)ray_owner.ext.main_55.unk85 << 8)
static void rt_init_hunter(void)
{
    RAY(0, 0, 0);
    g_Player.x_pos.i.hi = 0x100;
    ray_trap_update(&ss);
    RAY_SEEN();
}
static void rt_init_rider(void)
{
    RAY(0, 0, 0);
    ss.unk2 = 1;
    ray_trap_update(&ss);
    RAY_SEEN();
}
static void rt_init_crawler_left(void)
{
    RAY(0, 0, 0);
    ss.unk2 = 2;
    ray_trap_update(&ss);
    RAY_SEEN();
}
static void rt_init_crawler_right(void)
{
    RAY(0, 0, 0);
    ss.unk2 = 3;
    ss.unk15 = 0x40;
    ray_trap_update(&ss);
    RAY_SEEN();
}
static void rt_airborne(void)
{
    RAY(1, 4, 0);
    ss.unk70 = 0;
    ray_trap_check_airborne(&ss);
}
static void rt_grounded(void)
{
    RAY(1, 4, 0);
    ss.unk70 = 8;
    ray_trap_check_airborne(&ss);
}
static void rt_fall_land(void)
{
    RAY(1, 1, 0);
    ss.unk70 = 8;
    ray_trap_fall(&ss);
}
static void rt_fall_wall_hunter(void)
{
    RAY(1, 1, 0);
    ss.unk70 = 1;
    ray_trap_fall(&ss);
}
static void rt_fall_wall_crawler(void)
{
    RAY(1, 1, 0);
    ss.unk70 = 2;
    ss.unk8C.bytes[3] = 1;
    ray_trap_fall(&ss);
}
static void rt_fall(void)
{
    RAY(1, 1, 0);
    ss.y_vel.val = 0x10000;
    ray_trap_fall(&ss);
}
static void rt_ride_launch(void)
{
    RAY(1, 5, 0);
    ray_trap_ride(&ss);
    RAY_SEEN();
}
static void rt_ride_climb(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 1;
    ss.unk8C.bytes[1] = 1;
    ray_trap_ride(&ss);
    RAY_SEEN();
}
static void rt_ride_top(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 1;
    ray_trap_ride(&ss);
    RAY_SEEN();
}
static void rt_ride_orbit(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 2;
    ss.unk8C.bytes[0] = 3;
    ray_trap_ride(&ss);
    RAY_SEEN();
}
static void rt_ride_orbit_count(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 2;
    ss.timer = 2;
    ray_trap_ride(&ss);
    RAY_SEEN();
}
static void rt_ride_release(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 2;
    ray_owner.ext.main_55.unk87 = 1;
    ray_trap_ride(&ss);
}
static void rt_ride_owner_gone(void)
{
    RAY(1, 5, 0);
    ss.unk7 = 2;
    ray_owner.active = 0;
    ray_trap_ride(&ss);
}
static void rt_despawn_rider(void)
{
    RAY(2, 0, 0);
    ss.active = 1;
    ss.unk2 = 1;
    ss.unk8A = 2;
    ray_owner.ext.main_55.unk85 = 3;
    ray_owner.ext.main_55.unk88 = 0xFF;
    ray_trap_update(&ss);
    state_extra = ray_owner.ext.main_55.unk85 | ray_owner.ext.main_55.unk88 << 8;
}
static void rt_despawn_crawler(void)
{
    RAY(2, 0, 0);
    ss.active = 1;
    ss.unk2 = 2;
    ray_trap_update(&ss);
}
static void rt_run_expire(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 2;
    ss.animation_step.fields.relative_step = 1;
    ray_trap_update(&ss);
}
static void rt_run_owner_down(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 3;
    ss.timer = 5;
    ray_owner.state = 2;
    ray_trap_update(&ss);
}
static void rt_run_timer(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 2;
    ss.timer = 5;
    ss.animation_step.fields.relative_step = 1;
    ray_trap_update(&ss);
    RAY_SEEN();
}
static void rt_run_shot(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 1;
    ss.animation_step.fields.relative_step = 1;
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    ray_trap_update(&ss);
}
static void rt_run_away(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 1;
    ss.animation_step.fields.relative_step = 1;
    ss.x_pos.i.hi = 0x1000;
    ray_trap_update(&ss);
}
static void rt_crawl_land(void)
{
    RAY(1, 4, 0);
    ss.unk2 = 1;
    ss.unk70 = 8;
    func_800A1E3C(&ss);
}
static void rt_crawl_start_hunter(void)
{
    RAY(1, 4, 1);
    g_Player.x_pos.i.hi = 0x100;
    func_800A1E3C(&ss);
}
static void rt_crawl_start_crawler(void)
{
    RAY(1, 4, 1);
    ss.unk2 = 2;
    func_800A1E3C(&ss);
}

static void (*const ray_trap_states_cases[])(void) = {
    rt_init_hunter,
    rt_init_rider,
    rt_init_crawler_left,
    rt_init_crawler_right,
    rt_airborne,
    rt_grounded,
    rt_fall_land,
    rt_fall_wall_hunter,
    rt_fall_wall_crawler,
    rt_fall,
    rt_ride_launch,
    rt_ride_climb,
    rt_ride_top,
    rt_ride_orbit,
    rt_ride_orbit_count,
    rt_ride_release,
    rt_ride_owner_gone,
    rt_despawn_rider,
    rt_despawn_crawler,
    rt_run_expire,
    rt_run_owner_down,
    rt_run_timer,
    rt_run_shot,
    rt_run_away,
    rt_crawl_land,
    rt_crawl_start_hunter,
    rt_crawl_start_crawler,
};
static const u32 ray_trap_states_expected[] = { 0x401u, 0xFF400000u, 0x800000u, 0x600000u, 0x60000u, 0u, 0u, 0x50000u, 7u, 0u, 0x501u, 0xFF000100u, 0x800000u, 0x600000u, 0x60000u, 0u, 0u, 0x50000u, 7u, 0u, 0x301u, 0xFF000200u, 0x800000u, 0x600000u, 0xFFFD0000u, 0u, 0u, 0x50000u, 0xF100007u, 0u, 0x201u, 0xFF400300u, 0x800000u, 0x600000u, 0x30000u, 0u, 0u, 0x50000u, 0xF100007u, 0u, 0x101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0x420000u, 0x50000u, 0u, 0u, 0x401u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10401u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x401u, 0u, 0x800000u, 0x600000u, 0u, 0xFFFD0000u, 0u, 0x40000u, 0u, 0u, 0x10301u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0u, 0u, 0x1000501u, 0u, 0x800000u, 0x560000u, 0u, 0xA0000u, 0u, 0x40000u, 0x100u, 0u, 0x1000501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x2000501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x2000501u, 0u, 0x1290000u, 0x6E0000u, 0u, 0u, 0u, 0x40000u, 0x30002u, 0u, 0x2000501u, 0u, 0x1200000u, 0xA00000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u, 0x10501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x2000502u, 0u, 0x1200000u, 0xA00000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0xFB02u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10402u, 0x200u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0x41002100u, 0x10402u, 0x300u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0x41002100u, 0x10401u, 0x200u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x50000u, 0u, 0x10402u, 0x100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x41002100u, 0x10402u, 0x100u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10401u, 0xFF000100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 0xFF400000u, 0x800000u, 0x700000u, 0x90000u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 0xFF000200u, 0x800000u, 0x700000u, 0xFFFD0000u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_ray_trap_states(u32 row)
{
    return object_run(ray_trap_states_cases[row], row, &ray_trap_states_expected[row * 10]);
}

void ray_trap_ride(struct ShotObj*);
static const u32 fly_words[] = { 0x23010002, 0x24010002, 0x25010002, 0x26FD0002 };
static const s32 player_dx[] = { -65536, -1, 0, 1, 65536 };
static u32 ray_return(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 offset = row % 5, frame = row / 5 % 4, started = row / 20 % 2, last_tick = row / 40, next = (frame + 1) % 4, i;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.val = 100 * 65536 + 0x1234 + player_dx[offset];
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    player_before = g_Player;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 34;
    obj.unk2 = 1;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 55;
    owner.state = 1;
    owner.animation_table = (const u8* const*)jet_stingray_flyby_animations.entries;
    owner_before = owner;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.unk7 = started;
    obj.unk15 = 0x40;
    obj.unk16 = 5;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = g_Player.y_pos.val;
    obj.x_vel.val = 0x18000;
    obj.y_vel.val = -0x24000;
    obj.animation_table = (u32**)jet_stingray_flyby_animations.entries;
    set_animation_frame(ANIMATED_OBJECT(&obj), 6, frame);
    for (i = 0; i < 4; i++)
        assert(((u32*)jet_stingray_flyby_animations.entries[6])[i] == fly_words[i]);
    assert(obj.animation_step.packed == fly_words[frame]);
    if (last_tick)
        obj.animation_step.fields.duration = 1;
    obj.previous_animation_index = 0x35;
    expected = obj;
    if (!started) {
        expected.unk7 = 1;
        expected.unk15 = offset >= 2 ? 0x40 : 0;
        expected.x_vel.val = 65536;
        expected.y_vel.val = -0x30000;
    }
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    if (last_tick) {
        expected.animation_cursor = (u32*)jet_stingray_flyby_animations.entries[6] + next;
        expected.animation_step.packed = fly_words[next];
    } else
        expected.animation_step.fields.duration = 1;
    ray_trap_ride(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ray_trap_states", 0, 0, COUNT(ray_trap_states_cases), test_ray_trap_states },
    { "ray_chase_context", NULL, ray_chase_context_cases_expected, COUNT(ray_chase_context_cases_expected), ray_chase_context_cases_row },
    { "ray_trap_ride_owner_defaults", NULL, ray_trap_ride_owner_defaults_cases_expected, COUNT(ray_trap_ride_owner_defaults_cases_expected), ride_case },
    { "ray_trap_wall_rebound", ray_trap_wall_rebound_cases, ray_trap_wall_rebound_cases_expected, COUNT(ray_trap_wall_rebound_cases), 0 },
    { "ray_trap_wall_stick", ray_trap_wall_stick_cases, ray_trap_wall_stick_cases_expected, COUNT(ray_trap_wall_stick_cases), 0 },
    { "func_800A1B1C", 0, 0, 2, test_func_800A1B1C },
    { "ray_trap_chase", 0, 0, 1, test_ray_trap_chase },
    { "ray_trap_return", NULL, NULL, 80, ray_return },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ray_trap_states_cases) + COUNT(ray_chase_context_cases_expected) + COUNT(ray_trap_ride_owner_defaults_cases_expected) + COUNT(ray_trap_wall_rebound_cases) + COUNT(ray_trap_wall_stick_cases) + 2 + 1 + 80;
