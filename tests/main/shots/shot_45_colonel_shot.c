#include "test_runtime.h"
#include "main/shots/shot_45_colonel_shot.h"
#include "main/55C4.h"
extern void* D_80104770[25];
extern s8 colonel_shot_box_10[4];

static u32 bolt_case(u32 observation)
{
    struct ShotObj obj, before;
    u8 box[4] = { 1, 2, 3, 4 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 45;
    obj.state = 1;
    obj.unk2 = 1;
    obj.unk5 = 3;
    obj.unk6 = 0x27;
    obj.unk5C = 0x25;
    obj.unk60 = 0x26;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk28 = 0x1234;
    obj.unk2C = 0x5678;
    obj.unk58.data = obj.unk54 = obj.unk50.data = box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_80104770;
    set_animation(&obj, 0);
    before = obj;
    colonel_bolt_start(&obj);
    before.unk17 = 15;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = D_80104770[15];
    before.animation_step = *(union AnimationStep*)D_80104770[15];
    before.unk5C = 5;
    before.unk60 = 9;
    before.x_vel.val = 0;
    before.y_vel.val = 8 * 65536;
    before.unk28 = before.unk2C = 0;
    before.unk58.data = before.unk54 = NULL;
    before.unk50.data = (const u8*)colonel_shot_box_10;
    before.unk6 = 0x28;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < 4; i++)
        assert(box[i] == i + 1);
    return observation == 0 ? obj.animation_step.packed : (u8)obj.unk6 | ((u32)obj.unk5C << 8) | ((u32)obj.unk60 << 16);
}
static const u32 colonel_bolt_animation_context_cases_expected[] = { 0x43010001u, 0x90528u };

static const u32 colonel_marker_wait_expected[] = { 2u, 0u, 0u, 1u, 0u, 0u, 0u };
static u32 test_colonel_marker_wait(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    struct ShotObj child_0;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&shot_objects, 0, sizeof(shot_objects));
    child_0.state = 2;
    pool_0_full = 255;
    obj.unk7C = &child_0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    colonel_marker_wait(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].timer;
    observed_values[6] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, colonel_marker_wait_expected, 7);
}

static const u32 colonel_slash_start_expected[] = { 5u, 0u, 1u, 9u };
static u32 test_colonel_slash_start(u32 row)
{
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    colonel_slash_start(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk5C;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk60;
    return c_test_observe(0, row, observed_values, colonel_slash_start_expected, 4);
}

#include "support/state_cases.h"

static struct MainObj bolt_owner;
static struct ShotObj bolt_marker;
#define ss state_room.shot
#define BOLT(kind, phase) (state_reset(kind, phase, 0), memset(&bolt_owner, 0, sizeof(bolt_owner)), ss.state = 1, ss.unk8C.object = OBJECT_HEADER(&bolt_owner), ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define SHOT_TIMERS() (state_extra = (u16)ss.timer | (u32)(u16)ss.unk8A << 16)
static void cs_wave_left(void)
{
    BOLT(0, 0);
    ss.unk2 = 1;
    colonel_shot_update(&ss);
}
static void cs_wave_right_port(void)
{
    BOLT(0, 0);
    ss.unk15 = 0x40;
    engine_obj.stage = 0xA;
    colonel_shot_update(&ss);
}
static void cs_wave_away(void)
{
    BOLT(0, 1);
    ss.x_pos.i.hi = 0x1000;
    colonel_shot_update(&ss);
}
static void cs_streak_left(void)
{
    BOLT(1, 0);
    colonel_shot_update(&ss);
    SHOT_TIMERS();
}
static void cs_streak_right(void)
{
    BOLT(1, 0);
    ss.unk2 = 1;
    colonel_shot_update(&ss);
    SHOT_TIMERS();
}
static void cs_streak_spawn(void)
{
    BOLT(1, 1);
    ss.timer = 1;
    ss.unk8A = 5;
    colonel_shot_update(&ss);
    SHOT_TIMERS();
}
static void cs_streak_end(void)
{
    BOLT(1, 1);
    ss.timer = 3;
    ss.unk8A = 1;
    colonel_shot_update(&ss);
    SHOT_TIMERS();
}
static void cs_marker_start(void)
{
    BOLT(2, 0);
    colonel_shot_update(&ss);
}
static void cs_marker_follow(void)
{
    BOLT(2, 1);
    memset(&bolt_marker, 0, sizeof(bolt_marker));
    bolt_marker.state = 2;
    ss.unk7C = (struct WeaponObj*)&bolt_marker;
    ss.timer = 3;
    colonel_shot_update(&ss);
}
static void cs_marker_wait(void)
{
    BOLT(2, 1);
    memset(&bolt_marker, 0, sizeof(bolt_marker));
    ss.unk7C = (struct WeaponObj*)&bolt_marker;
    colonel_shot_update(&ss);
}
static void cs_marker_away(void)
{
    BOLT(2, 1);
    memset(&bolt_marker, 0, sizeof(bolt_marker));
    ss.unk7C = (struct WeaponObj*)&bolt_marker;
    ss.x_pos.i.hi = 0x1000;
    colonel_shot_update(&ss);
}
static void cs_bolt_first(void)
{
    BOLT(3, 0);
    colonel_shot_update(&ss);
}
static void cs_bolt_next(void)
{
    BOLT(3, 0);
    ss.unk2 = 1;
    colonel_shot_update(&ss);
}
static void cs_bolt_fall(void)
{
    BOLT(3, 1);
    ss.y_vel.val = 0x80000;
    colonel_shot_update(&ss);
}
static void cs_bolt_away(void)
{
    BOLT(3, 1);
    ss.y_pos.i.hi = 0x1000;
    colonel_shot_update(&ss);
}
static void cs_quake_small_left(void)
{
    BOLT(5, 0);
    ss.unk2 = 2;
    colonel_shot_update(&ss);
}
static void cs_quake_mid_right(void)
{
    BOLT(5, 0);
    ss.unk2 = 6;
    ss.unk15 = 0x40;
    colonel_shot_update(&ss);
}
static void cs_quake_big_left(void)
{
    BOLT(5, 0);
    ss.unk2 = 9;
    colonel_shot_update(&ss);
}
static void cs_quake_big_right(void)
{
    BOLT(5, 0);
    ss.unk2 = 9;
    ss.unk15 = 0x40;
    colonel_shot_update(&ss);
}
static void cs_quake_spread(void)
{
    BOLT(5, 1);
    ss.animation_step.fields.event = 1;
    ss.animation_step.fields.relative_step = 1;
    ss.animation_step.fields.frame_index = 0x38;
    ss.timer = 3;
    colonel_shot_update(&ss);
}
static void cs_quake_spread_last(void)
{
    BOLT(5, 1);
    ss.animation_step.fields.event = 1;
    ss.animation_step.fields.frame_index = 0x40;
    ss.timer = 0x10;
    colonel_shot_update(&ss);
}
static void cs_owner_gone(void)
{
    BOLT(3, 1);
    ss.active = 1;
    bolt_owner.state = 2;
    colonel_shot_update(&ss);
}

static void (*const colonel_shot_states_cases[])(void) = {
    cs_wave_left,
    cs_wave_right_port,
    cs_wave_away,
    cs_streak_left,
    cs_streak_right,
    cs_streak_spawn,
    cs_streak_end,
    cs_marker_start,
    cs_marker_follow,
    cs_marker_wait,
    cs_marker_away,
    cs_bolt_first,
    cs_bolt_next,
    cs_bolt_fall,
    cs_bolt_away,
    cs_quake_small_left,
    cs_quake_mid_right,
    cs_quake_big_left,
    cs_quake_big_right,
    cs_quake_spread,
    cs_quake_spread_last,
    cs_owner_gone,
};
static const u32 colonel_shot_states_expected[] = { 0x10001u, 0xFF000100u, 0x3B0000u, 0x700000u, 0xFFFB0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10001u, 0xFF400000u, 0xC50000u, 0x4E0000u, 0x60000u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10101u, 0xFF000000u, 0x800000u, 0x800000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0x320005u, 0u, 0x10101u, 0xFF400100u, 0x800000u, 0x800000u, 0x60000u, 0u, 0u, 0x50000u, 0x320005u, 0u, 0x10101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x4000Au, 0x410000u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 0x10201u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x410000u, 0x10201u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10301u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0x80000u, 0u, 0x50000u, 0u, 0u, 0x10301u, 0xFF000100u, 0x800000u, 0x600000u, 0u, 0x80000u, 0u, 0x50000u, 0u, 0u, 0x10301u, 0u, 0x800000u, 0x580000u, 0u, 0x80000u, 0u, 0x40000u, 0u, 0u, 2u, 0u, 0x800000u, 0x10000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10501u, 0xFF000200u, 0x700000u, 0x600000u, 0xFFFE8000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10501u, 0xFF400600u, 0x940000u, 0x600000u, 0x18000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10501u, 0xFF000900u, 0x680000u, 0x600000u, 0xFFFE8000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10501u, 0xFF400900u, 0x980000u, 0x600000u, 0x18000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x410000u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_colonel_shot_states(u32 row)
{
    return object_run(colonel_shot_states_cases[row], row, &colonel_shot_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "colonel_shot_states", 0, 0, COUNT(colonel_shot_states_cases), test_colonel_shot_states },
    { "colonel_bolt_animation_context", NULL, colonel_bolt_animation_context_cases_expected, COUNT(colonel_bolt_animation_context_cases_expected), bolt_case },
    { "colonel_marker_wait", 0, 0, 1, test_colonel_marker_wait },
    { "colonel_slash_start", 0, 0, 1, test_colonel_slash_start },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(colonel_shot_states_cases) + COUNT(colonel_bolt_animation_context_cases_expected) + 1 + 1;
