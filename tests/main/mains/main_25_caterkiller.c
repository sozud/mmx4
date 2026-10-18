#include "test_runtime.h"
#include "main/mains/main_25_caterkiller.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/object_motion.h"
extern union AnimationStep* caterkiller_animations[];
void caterkiller_check_fall(struct MainObj*);
extern struct StageObjectRecord stage_object_records_1_1[88];

static u32 end_case(u32 mode, u32 lunge)
{
    static const s16 height[] = { 26, -26, 25, -25, 26, 26, 25, -26 };
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u32 i, facing = mode == 1 || mode == 3 || mode == 7;
    u32 step = mode == 1 || mode == 3 ? 4 : mode == 7 ? 3
        : mode == 6                                   ? 0
                                                      : 1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 25;
    obj.state = 1;
    obj.unk5 = lunge ? 3 : 2;
    obj.unk6 = 2;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = mode == 5 ? 0 : facing ? -65536
        : mode == 4                      ? 2 * 65536
                                         : 65536;
    obj.x_accel = mode == 5 ? 0 : 65536;
    obj.y_speed = mode == 7 ? -7 * 65536 : 65536;
    obj.gravity = mode == 7 ? 0 : 32768;
    obj.ext.main_25.unk84 = 9;
    obj.ext.main_25.unk80 = 11;
    obj.animation_table = (const u8* const*)caterkiller_animations;
    set_animation(&obj, lunge ? 1 : 0);
    obj.animation_cursor = (const u8*)&caterkiller_animations[lunge ? 1 : 0][step];
    obj.animation_step = caterkiller_animations[lunge ? 1 : 0][step];
    if (mode >= 6)
        obj.animation_step.fields.duration = 1;
    g_Player.y_pos.val = ((mode == 7 ? 207 : 199) + height[mode]) * 65536 + 0x9ABC;
    player_before = g_Player;
    expected = obj;
    if (mode >= 6) {
        step++;
        expected.animation_cursor = (const u8*)&caterkiller_animations[lunge ? 1 : 0][step];
        expected.animation_step = caterkiller_animations[lunge ? 1 : 0][step];
    } else
        expected.animation_step.fields.duration--;
    expected.ext.main_25.unk84 = expected.animation_step.fields.event == 2 ? 1 : 0;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    expected.x_speed += facing ? obj.x_accel : -obj.x_accel;
    expected.y_speed = mode == 7 ? -425984 : 32768;
    if (mode != 4) {
        if (!lunge)
            expected.x_accel = 0;
        if (height[mode] >= -25 && height[mode] <= 25) {
            expected.unk6 = 0;
            if (!lunge) {
                expected.unk5 = 3;
                expected.ext.main_25.unk84 = 0;
                expected.unk17 = 1;
                expected.previous_animation_index = 0xFF;
                expected.animation_cursor = (const u8*)caterkiller_animations[1];
                expected.animation_step = caterkiller_animations[1][0];
            }
        } else if (!lunge) {
            expected.unk15 = facing ? 0 : 0x40;
            expected.x_speed = facing ? -65536 : 65536;
            expected.unk6 = 1;
        } else {
            expected.unk5 = 2;
            expected.unk6 = 0;
            expected.ext.main_25.unk80 = 0x40;
            expected.ext.main_25.unk84 = 0;
            expected.unk17 = 0;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = (const u8*)caterkiller_animations[0];
            expected.animation_step = caterkiller_animations[0][0];
        }
    }
    if (lunge)
        caterkiller_lunge_end(&obj);
    else
        caterkiller_crawl_end(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk15 << 16) | ((u32)obj.ext.main_25.unk84 << 24);
}
#define CASE(m, n)                                            \
    static u32 caterkiller_end_boundaries_end_##m##_##n(void) \
    {                                                         \
        return end_case(m, n);                                \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
MODE(7)
#define ENTRY(m, n) caterkiller_end_boundaries_end_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase caterkiller_end_boundaries_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) };
static const u32 caterkiller_end_boundaries_cases_expected[] = { 0x1400102u, 0x2u, 0x102u, 0x400002u, 0x3u, 0x1000003u, 0x400003u, 0x400003u, 0x1000202u, 0x1000203u, 0x1400102u, 0x2u, 0x3u, 0x1000003u, 0x102u, 0x400002u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

enum { NONE,
    NEAR,
    FAR,
    DROP_SMALL,
    DROP_LARGE,
    LEAP,
    LAND,
    FALL,
    SETTLE,
    UNKNOWN };
static const s8 events[] = { 0, 1, 1, 2, 3, 4, 5, 5, 6, 7 };
static u32 steps[2];
static u32* table[4];
static struct MainObj worm, expected;

static u32 caterkiller_events_run(u32 mode)
{
    union AnimationStep value;
    u32 i, difference = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.y_pos.i.hi = mode == NEAR ? 0x70 : 0x20;
    value.fields.duration = 3;
    value.fields.event = events[mode];
    value.fields.relative_step = 1;
    value.fields.frame_index = 4;
    steps[0] = value.packed;
    value.fields.duration = 9;
    value.fields.event = 0;
    steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    memset(&worm, 0, sizeof(worm));
    worm.active = 0x41;
    worm.id = 0x19;
    worm.state = 1;
    worm.unk5 = 4;
    worm.unk6 = 2;
    worm.air_state = 1;
    worm.collision_flags = mode == LAND ? 8 : 0;
    worm.x_pos.val = 0x00901234;
    worm.y_pos.val = 0x00605678;
    worm.x_speed = 0x18000;
    worm.y_speed = 0x24000;
    worm.animation_table = table;
    worm.animation_cursor = &steps[0];
    worm.animation_step.packed = steps[0];
    worm.ext.main_25.unk80 = 0x11;
    worm.ext.main_25.unk84 = 0x22;
    expected = worm;
    func_80057C00(&worm);

    expected.animation_step.fields.duration = 2;
    switch (mode) {
    case NEAR:
    case FAR:
        expected.unk17 = mode == NEAR ? 1 : 0;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = &steps[1];
        expected.animation_step.packed = steps[1];
        expected.unk5 = mode == NEAR ? 3 : 2;
        expected.unk6 = 0;
        if (mode == FAR)
            expected.ext.main_25.unk80 = 0x40;
        expected.ext.main_25.unk84 = 0;
        break;
    case DROP_SMALL:
        expected.y_pos.u.hi += 5;
        break;
    case DROP_LARGE:
        expected.ext.main_25.unk84 = 3;
        expected.y_pos.u.hi += 0xC;
        break;
    case LEAP:
        expected.ext.main_25.unk84 = 4;
        expected.y_speed = -0x50000;
        expected.y_pos.u.hi += 0xC;
        break;
    case LAND:
        expected.air_state = 0;
        expected.y_speed = 0;
        break;
    case FALL:
        expected.x_pos.val += expected.x_speed;
        expected.y_pos.val -= expected.y_speed;
        break;
    case SETTLE:
        expected.ext.main_25.unk84 = 5;
        break;
    }
    for (i = 0; i < sizeof(worm) / 4; i++)
        difference |= ((u32*)&worm)[i] ^ ((u32*)&expected)[i];
    assert(difference == 0);
    return (u8)worm.unk5 | ((u32)(u8)worm.ext.main_25.unk84 << 8) | ((u32)(u16)worm.y_pos.u.hi << 16);
}

#define CASE(name)                                    \
    static u32 caterkiller_events_##name##_case(void) \
    {                                                 \
        return caterkiller_events_run(name);          \
    }
CASE(NONE)
CASE(NEAR)
CASE(FAR)
CASE(DROP_SMALL)
CASE(DROP_LARGE)
CASE(LEAP)
CASE(LAND)
CASE(FALL)
CASE(SETTLE)
CASE(UNKNOWN)
#define ENTRY(name) caterkiller_events_##name##_case,
static const CTestCase caterkiller_events_cases[]
    = {
          ENTRY(NONE) ENTRY(NEAR) ENTRY(FAR) ENTRY(DROP_SMALL) ENTRY(DROP_LARGE) ENTRY(LEAP) ENTRY(LAND) ENTRY(FALL) ENTRY(SETTLE) ENTRY(UNKNOWN)
      };
static const u32 caterkiller_events_cases_expected[] = { 0x602204u, 0x600003u, 0x600002u, 0x652204u, 0x6C0304u, 0x6C0404u, 0x602204u, 0x5E2204u, 0x600504u, 0x602204u };
#undef CASE
#undef ENTRY

static u32 fall_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.active = 0x41;
    obj.id = 25;
    obj.state = 1;
    obj.unk5 = mode == 3 ? 4 : mode == 4 ? 6
                                         : 1;
    obj.unk6 = 7;
    obj.unk15 = mode == 1 ? 0x40 : mode == 2 ? 0x80
                                             : 0;
    obj.collision_flags = mode == 5 ? 8 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.gravity = 789;
    obj.x_accel = 987;
    obj.animation_table = (const u8* const*)caterkiller_animations;
    set_animation(&obj, 0);
    expected = obj;
    if (mode < 3) {
        expected.unk5 = 4;
        expected.unk6 = 0;
        expected.x_pos.i.hi += obj.unk15 ? 2 : -2;
        expected.x_speed = expected.y_speed = expected.x_accel = 0;
        expected.gravity = 0x4200;
        expected.ext.main_25.unk84 = 2;
        expected.air_state = 1;
        expected.unk17 = 3;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)caterkiller_animations[3];
        expected.animation_step = *caterkiller_animations[3];
    }
    caterkiller_check_fall(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
}
#define CASE(m)                                          \
    static u32 caterkiller_fall_animation_fall_##m(void) \
    {                                                    \
        return fall_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) caterkiller_fall_animation_fall_##m,
static const CTestCase caterkiller_fall_animation_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 caterkiller_fall_animation_cases_expected[] = { 0x620304u, 0x660304u, 0x660304u, 0x640004u, 0x640006u, 0x640001u };
#undef CASE
#undef ENTRY

#include "support/enemy_world.h"

static struct MainObj* cat_spawn(u32 kind, u32 record)
{
    struct MainObj* obj = world_spawn(25, 1, 1, kind, &stage_object_records_1_1[record]);
    obj->x_pos.i.hi = 104;
    obj->y_pos.i.hi = 132;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 132;
    return obj;
}

static struct MainObj* cat_climb(s32 y, s32 y_player)
{
    struct MainObj* obj = cat_spawn(0, 25);
    u32 i;
    g_Player.x_pos.i.hi = 104;
    g_Player.y_pos.i.hi = y_player;
    obj->y_pos.i.hi = y;
    func_80057160(obj);
    obj->collision_flags = 8;
    caterkiller_crawl_start(obj);
    func_8005754C(obj);
    assert(obj->unk5 == 5 && obj->unk6 == 0);
    for (i = 0; i < 26; i++)
        caterkiller_climb_start(obj);
    assert(obj->unk6 == 1);
    caterkiller_climb_hop(obj);
    caterkiller_climb_hop(obj);
    assert(obj->unk6 == 2);
    obj->collision_flags = 0;
    world_pixels[373] = 1;
    world_pixels[374] = 1;
    world_pixels[375] = 1;
    return obj;
}
static const u32 caterkiller_climb_cling_expected[] = { 1u };
static u32 test_caterkiller_climb_cling(u32 row)
{
    struct MainObj* obj = cat_climb(139, 244);
    u32 observed;
    world_attrs[1] = 16;
    world_attrs[2] = 36;
    world_pixels[389] = 2;
    world_pixels[390] = 2;
    world_pixels[391] = 2;
    caterkiller_climb_rise(obj);
    assert(obj->unk6 == 3);
    caterkiller_climb_cling(obj);
    caterkiller_climb_cling(obj);
    assert(obj->unk6 == 3);
    world_snapshot();
    move_with_gravity(ANIMATED_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    assert(world_expected->y_pos.i.hi == 140);
    assert(func_8002D724(PLAYER_OBJECT(world_expected), 104, world_expected->y_pos.i.hi - 12) == 36);
    world_expected->ext.main_25.unk88 = 0;
    world_expected->unk5 = 4;
    world_expected->unk6 = 1;
    caterkiller_climb_cling(obj);
    world_check();
    observed = obj->unk6;
    return c_test_observe(0, row, &observed, caterkiller_climb_cling_expected, 1);
}

static const u32 caterkiller_climb_rise_expected[] = { 2u };
static u32 test_caterkiller_climb_rise(u32 row)
{
    struct MainObj* obj = cat_climb(132, 244);
    u32 observed;
    world_attrs[1] = 36;
    world_snapshot();
    move_with_gravity(ANIMATED_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    assert(func_8002D724(PLAYER_OBJECT(world_expected), 104, world_expected->y_pos.i.hi - 12) == 36);
    caterkiller_climb_rise(obj);
    world_check();
    observed = obj->unk6;
    return c_test_observe(0, row, &observed, caterkiller_climb_rise_expected, 1);
}

static const u32 caterkiller_fall_drop_expected[] = { 1u };
static u32 test_caterkiller_fall_drop(u32 row)
{
    struct MainObj* obj = cat_spawn(1, 27);
    u32 observed, i;
    func_80057160(obj);
    world_attrs[1] = 36;
    world_pixels[421] = 1;
    world_pixels[422] = 1;
    world_pixels[423] = 1;
    for (i = 0; i < 6; i++)
        caterkiller_fall_start(obj);
    assert(obj->unk5 == 4 && obj->unk6 == 1);
    world_snapshot();
    move_with_gravity(ANIMATED_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    assert(func_8002D724(PLAYER_OBJECT(world_expected), 104, world_expected->y_pos.i.hi + 31) == 36);
    caterkiller_fall_drop(obj);
    world_check();
    observed = obj->unk6;
    return c_test_observe(0, row, &observed, caterkiller_fall_drop_expected, 1);
}

static const u32 func_80057874_expected[] = { 2u };
static u32 test_func_80057874(u32 row)
{
    struct MainObj* obj = cat_spawn(0, 25);
    u32 observed;
    func_80057160(obj);
    obj->collision_flags = 8;
    caterkiller_crawl_start(obj);
    func_8005754C(obj);
    assert(obj->unk5 == 3 && obj->unk6 == 0);
    caterkiller_lunge_start(obj);
    assert(obj->unk6 == 1);
    g_Player.y_pos.i.hi = obj->y_pos.i.hi + 26;
    world_snapshot();
    animate_object(ANIMATED_OBJECT(world_expected));
    move_object(MOVING_OBJECT(world_expected));
    set_animation(world_expected, 0);
    world_expected->unk5 = 2;
    world_expected->unk6 = 0;
    world_expected->ext.main_25.unk80 = 64;
    world_expected->ext.main_25.unk84 = 0;
    func_80057874(obj);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, func_80057874_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "caterkiller_end_boundaries", caterkiller_end_boundaries_cases, caterkiller_end_boundaries_cases_expected, COUNT(caterkiller_end_boundaries_cases), 0 },
    { "caterkiller_events", caterkiller_events_cases, caterkiller_events_cases_expected, COUNT(caterkiller_events_cases), 0 },
    { "caterkiller_fall_animation", caterkiller_fall_animation_cases, caterkiller_fall_animation_cases_expected, COUNT(caterkiller_fall_animation_cases), 0 },
    { "caterkiller_climb_cling", 0, 0, 1, test_caterkiller_climb_cling },
    { "caterkiller_climb_rise", 0, 0, 1, test_caterkiller_climb_rise },
    { "caterkiller_fall_drop", 0, 0, 1, test_caterkiller_fall_drop },
    { "func_80057874", 0, 0, 1, test_func_80057874 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(caterkiller_end_boundaries_cases) + COUNT(caterkiller_events_cases) + COUNT(caterkiller_fall_animation_cases) + 1 + 1 + 1 + 1;
