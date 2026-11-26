#include "test_runtime.h"
#include "main/mains/main_25_caterkiller.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "support/state_cases.h"
void caterkiller_wait_above(struct MainObj* arg0);
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
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
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
            expected.unk15 = facing ? 0 : PLAYER_FACING_RIGHT;
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
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)C_TEST_PSX_FACING(obj.unk15) << 16) | ((u32)obj.ext.main_25.unk84 << 24);
}
static const u32 caterkiller_end_boundaries_cases_expected[] = { 0x1400102u, 0x2u, 0x102u, 0x400002u, 0x3u, 0x1000003u, 0x400003u, 0x400003u, 0x1000202u, 0x1000203u, 0x1400102u, 0x2u, 0x3u, 0x1000003u, 0x102u, 0x400002u };
static u32 caterkiller_end_boundaries_cases_row(u32 row)
{
    return end_case(row / 2, row % 2);
}

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

static const u32 caterkiller_events_cases_expected[] = { 0x602204u, 0x600003u, 0x600002u, 0x652204u, 0x6C0304u, 0x6C0404u, 0x602204u, 0x5E2204u, 0x600504u, 0x602204u };

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
static const u32 caterkiller_fall_animation_cases_expected[] = { 0x620304u, 0x660304u, 0x660304u, 0x640004u, 0x640006u, 0x640001u };

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
    world_attrs[1] = C_TEST_PSX_WORD(16);
    world_attrs[2] = C_TEST_PSX_WORD(36);
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
    world_attrs[1] = C_TEST_PSX_WORD(36);
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
    world_attrs[1] = C_TEST_PSX_WORD(36);
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

#define CK(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
static void ck_init_crawl(void)
{
    CK(0, 0);
    func_80057160(&so);
    state_extra = so.ext.main_25.unk80 | so.ext.main_25.unk84 << 8;
}
static void ck_init_drop(void)
{
    CK(0, 0);
    so.unk2 = 1;
    func_80057160(&so);
    state_extra = so.ext.main_25.unk84;
}
static void ck_init_hang(void)
{
    CK(0, 0);
    so.unk2 = 2;
    func_80057160(&so);
    state_extra = so.ext.main_25.unk84;
}
static void ck_init_other(void)
{
    CK(0, 0);
    so.unk2 = 3;
    func_80057160(&so);
}
static void ck_wait(void)
{
    CK(3, 0);
    g_Player.x_pos.i.hi = 0x88;
    caterkiller_wait_above(&so);
}
static void ck_wait_drop(void)
{
    CK(3, 0);
    g_Player.x_pos.i.hi = 0xA0;
    caterkiller_wait_above(&so);
}
static void ck_fall(void)
{
    CK(4, 0);
    caterkiller_fall_start(&so);
}
static void ck_fall_push(void)
{
    CK(4, 0);
    so.animation_step.fields.event = 2;
    caterkiller_fall_start(&so);
}
static void ck_fall_curl(void)
{
    CK(4, 0);
    so.animation_table = (void*)caterkiller_animations;
    so.animation_step.fields.event = 1;
    caterkiller_fall_start(&so);
    state_extra = so.ext.main_25.unk84;
}

void caterkiller_update(struct MainObj*);
void func_80057308(struct MainObj*);
void caterkiller_crawl_start(struct MainObj*);
void func_8005754C(struct MainObj*);
void caterkiller_lunge_start(struct MainObj*);
void func_80057874(struct MainObj*);
void caterkiller_fall_drop(struct MainObj*);
void caterkiller_climb_rise(struct MainObj*);
void caterkiller_climb_cling(struct MainObj*);
#define CKX() (state_extra = so.ext.main_25.unk80 | (u32)so.ext.main_25.unk84 << 8 | (u32)so.ext.main_25.unk88 << 16 | (u32)so.state << 24)
#define CKP(step, sub, px, py) (CK(step, sub), so.ext.main_25.unk80 = 5, g_Player.x_pos.i.hi = 0x80 + (px), g_Player.y_pos.i.hi = 0x60 + (py))
#define CKT(step, sub, attr) (CK(step, sub), so.terrain_box = &state_hit_box, state_terrain(attr))
static void ck_update_hang(void)
{
    CK(6, 0), state_terrain(0), so.terrain_box = &state_hit_box, so.state = 1, so.ext.main_25.unk88 = 1, caterkiller_update(&so), CKX();
}
static void ck_update_despawn(void) { CK(0, 0), state_terrain(0), so.terrain_box = &state_hit_box, so.state = 2, so.active = 1, so.ext.main_25.unk88 = 1, caterkiller_update(&so), CKX(); }
static void ck_main_defeated(void) { CKT(3, 1, 0x38), so.state = 1, so.hp = 1, state_hit(&so, 0, 0, 1), cur_random = 1, func_80057308(&so), CKX(); }
static void ck_crawl_start_left(void) { CKP(2, 0, -0x40, 0), caterkiller_crawl_start(&so); }
static void ck_crawl_event2_far(void) { CKP(2, 1, 0, -0x40), so.animation_step.fields.event = 2, func_8005754C(&so), CKX(); }
static void ck_crawl_event1_timeout(void) { CKP(2, 1, 0, -0x40), so.ext.main_25.unk80 = 1, so.animation_step.fields.event = 1, func_8005754C(&so), CKX(); }
static void ck_crawl_wall_left(void) { CKP(2, 1, 0, -0x40), so.collision_flags = 2, func_8005754C(&so), CKX(); }
static void ck_crawl_wall_right(void) { CKP(2, 1, 0, -0x40), so.unk15 = PLAYER_FACING_RIGHT, so.collision_flags = 1, func_8005754C(&so), CKX(); }
static void ck_crawl_player_below(void) { CKP(2, 1, -0x10, 0x50), func_8005754C(&so), CKX(); }
static void ck_crawl_player_below_far(void) { CKP(2, 1, 0x40, 0x50), func_8005754C(&so), CKX(); }
static void ck_lunge_start_left(void) { CKP(3, 0, -0x40, 0), caterkiller_lunge_start(&so); }
static void ck_lunge_event2_away(void) { CKP(3, 1, 0, 0x40), so.animation_step.fields.event = 2, func_80057874(&so), CKX(); }
static void ck_lunge_event1_left_passed(void) { CKP(3, 1, 0x20, 0), so.animation_step.fields.event = 1, func_80057874(&so), CKX(); }
static void ck_lunge_left_ahead(void) { CKP(3, 1, -0x20, 0), func_80057874(&so), CKX(); }
static void ck_lunge_right_passed(void) { CKP(3, 1, -0x20, 0), so.unk15 = PLAYER_FACING_RIGHT, func_80057874(&so), CKX(); }
static void ck_lunge_right_ahead(void) { CKP(3, 1, 0x20, 0), so.unk15 = PLAYER_FACING_RIGHT, func_80057874(&so), CKX(); }
static void ck_lunge_player_above(void) { CKP(3, 1, 0, -0x40), func_80057874(&so), CKX(); }
static void ck_drop_landed(void) { CKT(4, 1, 0x38), caterkiller_fall_drop(&so), CKX(); }
static void ck_drop_air(void) { CKT(4, 1, 0), caterkiller_fall_drop(&so), CKX(); }
static void ck_rise_air(void) { CKT(5, 1, 0), caterkiller_climb_rise(&so), CKX(); }
static void ck_cling_lost(void) { CKT(5, 2, 0), caterkiller_climb_cling(&so), CKX(); }
static void (*const caterkiller_states_cases[])(void) = {
    ck_init_crawl,
    ck_init_drop,
    ck_init_hang,
    ck_init_other,
    ck_wait,
    ck_wait_drop,
    ck_fall,
    ck_fall_push,
    ck_fall_curl,
    ck_update_hang,
    ck_main_defeated,
    ck_crawl_start_left,
    ck_crawl_event2_far,
    ck_crawl_event1_timeout,
    ck_crawl_wall_left,
    ck_crawl_wall_right,
    ck_crawl_player_below,
    ck_crawl_player_below_far,
    ck_lunge_start_left,
    ck_lunge_event2_away,
    ck_lunge_event1_left_passed,
    ck_lunge_left_ahead,
    ck_lunge_right_passed,
    ck_lunge_right_ahead,
    ck_drop_landed,
    ck_drop_air,
    ck_rise_air,
    ck_cling_lost,
    ck_lunge_player_above,
    ck_update_despawn,
};
static const u32 caterkiller_states_expected[] = {
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0x30003u,
    0x40u,
    0u,
    0x1000004u,
    0u,
    0x800000u,
    0u,
    0u,
    0x420000u,
    4u,
    0x30003u,
    2u,
    0u,
    0x1000006u,
    0u,
    0x800000u,
    0u,
    0u,
    0x420000u,
    4u,
    0x30003u,
    2u,
    0u,
    0u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0x30000u,
    0u,
    0u,
    3u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    4u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    4u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    4u,
    0u,
    0x800000u,
    0u,
    0u,
    0x420000u,
    0u,
    0u,
    0u,
    0u,
    0x104u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    4u,
    0u,
    2u,
    0u,
    0x6u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1010000u,
    0x0u,
    0x1000004u,
    0x0u,
    0x7E0000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x80000003u,
    0x3u,
    0x2000200u,
    0x2100u,
    0x102u,
    0x0u,
    0x800000u,
    0xFFFF0000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x102u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x104u,
    0x0u,
    0x202u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0xFFFFF000u,
    0x0u,
    0x0u,
    0x80u,
    0x0u,
    0x202u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0xFFFFF000u,
    0x0u,
    0x0u,
    0x80u,
    0x0u,
    0x202u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0xFFFFF000u,
    0x4000u,
    0x0u,
    0x80u,
    0x0u,
    0x1000005u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x10504u,
    0x0u,
    0x102u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x4u,
    0x0u,
    0x103u,
    0x0u,
    0x800000u,
    0xFFFE0000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x40u,
    0x0u,
    0x203u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0xFFFFF000u,
    0x0u,
    0x0u,
    0x5u,
    0x0u,
    0x103u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x5u,
    0x0u,
    0x203u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0xFFFFF000u,
    0x4000u,
    0x0u,
    0x5u,
    0x0u,
    0x103u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x5u,
    0x0u,
    0x204u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x5u,
    0x0u,
    0x0u,
    0x0u,
    0x104u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x105u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x104u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x40u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
};

static u32 test_caterkiller_states(u32 row)
{
    return state_run(caterkiller_states_cases[row], row, &caterkiller_states_expected[row * 10]);
}

void func_80057308(struct MainObj* self);
static struct Unk_unk68 ck_top_box = { -2, -2, 4, 4 };
static const struct {
    u8 step, segment, far, hit;
    u32 expected[4];
} ck_main_cases[] = {
    { 6, 0, 0, 0, { 0x10010601u, 0xFFFB0000u, 0u, 0u } },
    { 1, 0, 1, 0, { 0x10010102u, 0u, 0x1809EBFFu, 0x1C0CE8FEu } },
    { 1, 1, 0, 0, { 0x10010101u, 0u, 0x100EF3F4u, 0x1413F0F0u } },
    { 1, 0, 0, 2, { 0x00010102u, 0u, 0x1809EBFFu, 0x1C0CE8FEu } },
};
static u32 ck_box(const struct Unk_unk68* box)
{
    const u8* bytes = (const u8*)box;
    return box == NULL ? 0 : bytes[0] | (u32)bytes[1] << 8 | (u32)bytes[2] << 16 | (u32)bytes[3] << 24;
}
static u32 ck_main(u32 row)
{
    u32 observed[4];
    state_reset(ck_main_cases[row].step, 0, 0);
    so.active = 0x41;
    so.id = 25;
    so.state = 1;
    so.hp = 0x10;
    so.collision_flags = 8;
    so.y_speed = ck_main_cases[row].step == 6 ? -0x60000 : 0;
    so.ext.main_25.saved_unk5 = 1;
    so.ext.main_25.unk84 = ck_main_cases[row].segment;
    so.x_pos.i.hi = ck_main_cases[row].far ? 0x400 : 0xA0;
    so.y_pos.i.hi = ck_main_cases[row].far ? 0x400 : 0x78;
    g_Player.x_pos.i.hi = so.x_pos.i.hi;
    if (ck_main_cases[row].hit) {
        state_hit(&so, 0, 0, 0x20);
        so.hp = 1;
        so.hurt_box = NULL;
        if (ck_main_cases[row].hit == 2) {
            ((struct MainObj*)&weapon_objects[0])->attack_box = &ck_top_box;
            weapon_objects[0].y_pos.i.hi -= 18;
        }
    }
    func_80057308(&so);
    observed[0] = (u8)so.state | (u32)(u8)so.unk5 << 8 | (u32)(u8)so.ext.main_25.saved_unk5 << 16 | (u32)(u8)so.hp << 24;
    observed[1] = so.y_speed;
    observed[2] = ck_box(so.attack_box);
    observed[3] = ck_box(so.hurt_box);
    if (row == 2)
        assert(so.on_screen == C_TEST_VISIBLE(so.unk16));
    return c_test_observe(0, row, observed, ck_main_cases[row].expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "caterkiller_states", 0, 0, COUNT(caterkiller_states_cases), test_caterkiller_states },
    { "caterkiller_end_boundaries", NULL, caterkiller_end_boundaries_cases_expected, COUNT(caterkiller_end_boundaries_cases_expected), caterkiller_end_boundaries_cases_row },
    { "caterkiller_events", NULL, caterkiller_events_cases_expected, COUNT(caterkiller_events_cases_expected), caterkiller_events_run },
    { "caterkiller_fall_animation", NULL, caterkiller_fall_animation_cases_expected, COUNT(caterkiller_fall_animation_cases_expected), fall_case },
    { "caterkiller_climb_cling", 0, 0, 1, test_caterkiller_climb_cling },
    { "caterkiller_climb_rise", 0, 0, 1, test_caterkiller_climb_rise },
    { "caterkiller_fall_drop", 0, 0, 1, test_caterkiller_fall_drop },
    { "func_80057874", 0, 0, 1, test_func_80057874 },
    { "main_step_boxes_hits_and_view", NULL, NULL, COUNT(ck_main_cases), ck_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(caterkiller_states_cases) + COUNT(caterkiller_end_boundaries_cases_expected) + COUNT(caterkiller_events_cases_expected) + COUNT(caterkiller_fall_animation_cases_expected) + 1 + 1 + 1 + 1 + COUNT(ck_main_cases);
