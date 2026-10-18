#include "test_runtime.h"
#include "main/quads/quad_00_search_light.h"
#include "support/search_light_data.h"
#include "main/effects/effect_07_search_light_maker.h"

extern struct SearchLightIntensityLookup search_light_blend_modes;
extern struct SearchLightColorLookup search_light_colors;
extern s32 search_light_speeds[3];
extern void search_light_move(struct Unk22* arg0);

extern s32 search_light_accels[3];
extern struct SearchLightSpawner search_light_spawners[12];

static struct {
    u32 before;
    struct QuadObj value;
    u32 after;
} guarded;
#define obj guarded.value
static struct QuadObj expected, pool_before[32];
static struct SearchLightSpawner spawner, spawner_expected, spawners_before[12];
static struct PlayerObj player_before, entity_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static u16 expected_random;
static const s16 cameras[3][2] = { { 0, 0 }, { 1024, 512 }, { 32760, -32760 } };

static void prepare(u32 type, u32 layer, u32 seed)
{
    u32 i;
    c_test_zero_words((u32*)&guarded, sizeof(guarded) / 4);
    guarded.before = 0x12345678;
    guarded.after = 0x87654321;
    obj.active = 1;
    obj.unk2 = type;
    obj.bg_offset = layer;
    obj.x_pos.i.hi = (s16)(cameras[layer][0] + 160);
    obj.y_pos.i.hi = (s16)(cameras[layer][1] + 120);
    obj.x_pos.u.lo = 0xFEDC;
    obj.y_pos.u.lo = 0xBA98;
    obj.unk6 = 0x12;
    obj.unk7 = 0x34;
    obj.unk34 = 0x4567;
    obj.unk36 = 0x23;
    for (i = 0; i < 4; i++) {
        obj.vertices[i].x.i.hi = 0x123;
        obj.vertices[i].y.i.hi = -0x456;
        obj.vertices[i].x.u.lo = 0x1234 + i * 0x1111;
        obj.vertices[i].y.u.lo = 0x5678 + i * 0x1111;
    }
    obj.ext.search_light.velocity = 0x12345;
    obj.ext.search_light.acceleration = -0x234;
    obj.ext.search_light.vertical_velocity = -0x34567;
    obj.ext.search_light.vertical_acceleration = 0x456;
    obj.runtime.search_light.x_accumulator = -0x1234567;
    obj.runtime.search_light.y_accumulator = 0x2345678;
    obj.runtime.search_light.pause_timer = 7;
    obj.runtime.search_light.extent = 0x789;
    obj.runtime.search_light.base_speed = -0x23456;
    obj.link.direction = 1;
    spawner.active = 1;
    spawner.type = type;
    spawner.reserved = 0xA5;
    spawner.background_index = layer;
    spawner.x = obj.x_pos.i.hi;
    spawner.y = obj.y_pos.i.hi;
    obj.backref = &spawner;
    obj.unk5C = &g_Player;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.i.hi = cameras[i][0];
        background_objects[i].y_pos.i.hi = cameras[i][1];
        background_objects[i].x_pos.u.lo = 0x5678;
        background_objects[i].y_pos.u.lo = 0x1234;
    }
    cur_random = expected_random = random_cases[seed].before;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    expected = obj;
    spawner_expected = spawner;
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)pool_before, (const u32*)g_QuadObjects, sizeof(pool_before) / 4);
    c_test_copy_words((u32*)spawners_before, (const u32*)search_light_spawners, sizeof(spawners_before) / 4);
}

static void check_object(void)
{
    assert(guarded.before == 0x12345678 && guarded.after == 0x87654321);
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&spawner, &spawner_expected, sizeof(spawner_expected));
    assert(cur_random == expected_random);
}

static void check(void)
{
    u32 i, j;
    check_object();
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&g_Entity, &entity_before, sizeof(entity_before));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)g_QuadObjects, (const u32*)pool_before, sizeof(pool_before) / 4) == 0);
    c_test_same_words(search_light_spawners, spawners_before, sizeof(spawners_before));
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(need_palette_load == 0x20);
    for (i = 0; i < 6; i++) {
        assert(search_light_shapes[i].extent == shapes[i].extent);
        for (j = 0; j < 8; j++)
            assert(search_light_shapes[i].vertices[j] == shapes[i].vertices[j]);
    }
    for (i = 0; i < 3; i++) {
        assert(search_light_speeds[i] == speeds[i] && search_light_accels[i] == accels[i]);
        assert(search_light_colors.values[i] == colors[i] && search_light_blend_modes.values[i] == blends[i]);
    }
}

static void seed_sweep(u32 type, u32 layer, u32 seed)
{
    u32 i;
    prepare(type, layer, seed);
    obj.active = (s8)0x91;
    obj.state = 1;
    obj.on_screen = 1;
    obj.unk34 = colors[type / 2];
    obj.unk36 = blends[type / 2];
    for (i = 0; i < 4; i++) {
        obj.vertices[i].x.i.hi = shapes[type].vertices[i * 2];
        obj.vertices[i].y.i.hi = shapes[type].vertices[i * 2 + 1];
    }
    obj.runtime.search_light.pause_timer = 0;
    obj.runtime.search_light.extent = shapes[type].extent;
    obj.runtime.search_light.base_speed = speeds[type / 2];
    obj.ext.search_light.velocity = speeds[type / 2];
    obj.ext.search_light.acceleration = 0;
    expected = obj;
}

static void expect_integrate(void)
{
    expected.runtime.search_light.x_accumulator += expected.ext.search_light.velocity;
    expected.runtime.search_light.y_accumulator += expected.ext.search_light.vertical_velocity;
    expected.ext.search_light.velocity += expected.ext.search_light.acceleration;
    expected.ext.search_light.vertical_velocity += expected.ext.search_light.vertical_acceleration;
    expected.vertices[0].x.val += expected.ext.search_light.velocity;
    expected.vertices[1].x.val += expected.ext.search_light.velocity;
}

static void place_top(s32 post_x, s32 post_velocity, u32 type)
{
    obj.vertices[0].x.val = post_x - post_velocity;
    obj.vertices[1].x.val = obj.vertices[0].x.val + (shapes[type].vertices[2] - shapes[type].vertices[0]) * 65536;
    expected = obj;
}

static u32 test_init(u32 row)
{
    u32 type = row % 6, seed = (row / 6) % 8, layer = row / 48, i;
    prepare(type, layer, seed);
    expected.active = (s8)0x91;
    expected.state = 1;
    expected.unk34 = colors[type / 2];
    expected.unk36 = blends[type / 2];
    for (i = 0; i < 4; i++) {
        expected.vertices[i].x.i.hi = shapes[type].vertices[i * 2];
        expected.vertices[i].y.i.hi = shapes[type].vertices[i * 2 + 1];
    }
    expected.runtime.search_light.extent = shapes[type].extent;
    expected.runtime.search_light.x_accumulator = 0;
    expected.runtime.search_light.y_accumulator = 0;
    expected.ext.search_light.velocity = speeds[type / 2] + (seed % 4 == 0 ? 0x4000 : 0);
    expected.ext.search_light.acceleration = 0;
    expected.ext.search_light.vertical_velocity = 0;
    expected.ext.search_light.vertical_acceleration = 0;
    expected.runtime.search_light.pause_timer = 0;
    expected.runtime.search_light.base_speed = expected.ext.search_light.velocity;
    expected.link.direction = 0;
    expected_random = random_cases[seed].after;
    SearchLightUpdate(&obj);
    check();
    return 1;
}

struct Edge {
    s8 phase, direction, threshold_sign, next_phase, accel_sign, velocity_mode;
    s32 delta;
};
#define RIGHT(p, t, n, a, v)                                \
    { p, 0, t, p, 0, 0, -65536 }, { p, 0, t, p, 0, 0, -1 }, \
        { p, 0, t, n, a, v, 0 }, { p, 0, t, n, a, v, 1 },   \
        { p, 0, t, n, a, v, 65535 },                        \
    {                                                       \
        p, 0, t, n, a, v, 65536                             \
    }
#define LEFT(p, t, n, a, v)                                 \
    { p, 1, t, n, a, v, -65536 }, { p, 1, t, n, a, v, -1 }, \
        { p, 1, t, n, a, v, 0 }, { p, 1, t, n, a, v, 1 },   \
        { p, 1, t, n, a, v, 65535 },                        \
    {                                                       \
        p, 1, t, p, 0, 0, 65536                             \
    }
static const struct Edge edges[] = {
    RIGHT(0, 1, 1, -1, 0),
    LEFT(0, -1, 1, 1, 0),
    RIGHT(3, -1, 0, 0, 1),
    LEFT(3, 1, 0, 0, 1),
};
#undef RIGHT
#undef LEFT

static u32 test_edges(u32 row)
{
    u32 type = row % 6, e = row, layer = (type + e) % 3;
    const struct Edge* edge = &edges[e];
    s32 sign = edge->direction ? -1 : 1;
    s32 post = (shapes[type].vertices[0] + edge->threshold_sign * ((s32)shapes[type].extent - 32)) * 65536 + edge->delta;
    seed_sweep(type, layer, e % 8);
    obj.unk5 = edge->phase;
    obj.link.direction = edge->direction;
    obj.runtime.search_light.base_speed = sign * speeds[type / 2];
    obj.ext.search_light.velocity = sign * (speeds[type / 2] - accels[type / 2]);
    obj.ext.search_light.acceleration = edge->phase == 3 ? sign * accels[type / 2] : 0;
    place_top(post, obj.ext.search_light.velocity + obj.ext.search_light.acceleration, type);
    expect_integrate();
    expected.unk5 = edge->next_phase;
    if (edge->phase == 0)
        expected.ext.search_light.acceleration = edge->accel_sign * accels[type / 2];
    else if (edge->velocity_mode) {
        expected.ext.search_light.velocity = expected.runtime.search_light.base_speed;
        expected.ext.search_light.acceleration = 0;
    }
    SearchLightUpdate(&obj);
    check();
    return 1;
}

struct Clamp {
    s32 integrated_speed, final_speed;
    u8 keep_acceleration;
};
static const struct Clamp clamps[2][3] = {
    { { 0x7FFF, 0x8000, 0 }, { 0x8000, 0x8000, 1 }, { 0x8001, 0x8001, 1 } },
    { { -0x8001, -0x8001, 1 }, { -0x8000, -0x8000, 1 }, { -0x7FFF, -0x8000, 0 } },
};
static const s32 deltas[6] = { -65536, -1, 0, 1, 65535, 65536 };
static const u8 endpoint_hit[2][6] = { { 0, 0, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 0 } };

static void expect_endpoint(u32 type, u32 direction, u32 seed)
{
    s32 end = shapes[type].vertices[0] + (direction ? -(s32)shapes[type].extent : (s32)shapes[type].extent);
    expected.unk5 = 2;
    expected.ext.search_light.velocity = 0;
    expected.ext.search_light.acceleration = 0;
    expected.vertices[0].x.val = end * 65536;
    expected.vertices[1].x.val = (end + shapes[type].vertices[2] - shapes[type].vertices[0]) * 65536;
    expected_random = random_cases[seed].after;
    expected.runtime.search_light.pause_timer = seed;
    expected.link.direction = direction ^ 1;
}

static u32 test_endpoints(u32 row)
{
    u32 pos = row % 6, direction = (row / 6) % 2, clamp = row / 12;
    u32 type = (pos + clamp) % 6, layer = 0, seed = (pos + type + clamp) % 8;
    const struct Clamp* c = &clamps[direction][clamp];
    s32 accel = (direction ? 1 : -1) * accels[type / 2];
    s32 end = shapes[type].vertices[0] + (direction ? -(s32)shapes[type].extent : (s32)shapes[type].extent);
    seed_sweep(type, layer, seed);
    obj.unk5 = 1;
    obj.link.direction = direction;
    obj.ext.search_light.acceleration = accel;
    obj.ext.search_light.velocity = c->integrated_speed - accel;
    place_top(end * 65536 + deltas[pos], c->integrated_speed, type);
    expect_integrate();
    expected.ext.search_light.velocity = c->final_speed;
    expected.ext.search_light.acceleration = c->keep_acceleration ? accel : 0;
    if (endpoint_hit[direction][pos])
        expect_endpoint(type, direction, seed);
    SearchLightUpdate(&obj);
    check();
    return 1;
}

static u32 test_reverse(u32 row)
{
    u32 type = row % 6, direction = (row / 6) % 2, layer = row / 12;
    s32 sign = direction ? -1 : 1;
    seed_sweep(type, layer, type % 8);
    obj.unk5 = 2;
    obj.link.direction = direction;
    obj.ext.search_light.velocity = 0;
    obj.ext.search_light.acceleration = 0;
    obj.runtime.search_light.base_speed = -sign * speeds[type / 2];
    expected = obj;
    expect_integrate();
    expected.unk5 = 3;
    expected.ext.search_light.acceleration = sign * accels[type / 2];
    expected.runtime.search_light.base_speed = sign * speeds[type / 2];
    SearchLightUpdate(&obj);
    check();
    return 1;
}

static u32 test_pause(u32 row)
{
    static const u16 timers[3] = { 1, 2, 7 };
    u32 type = row % 6, direction = (row / 6) % 2, phase = (row / 12) % 4;
    u32 timer = (row / 48) % 3, layer = row / 144;
    seed_sweep(type, layer, timer);
    obj.unk5 = phase;
    obj.link.direction = direction;
    obj.runtime.search_light.pause_timer = timers[timer];
    expected = obj;
    expected.runtime.search_light.pause_timer--;
    SearchLightUpdate(&obj);
    check();
    return 1;
}

static u32 test_visibility(u32 row)
{
    u32 type = row % 6, point = (row / 6) % 32, layer = row / 192;
    const struct Visibility* v = &visibility[type][point];
    seed_sweep(type, layer, point % 8);
    obj.x_pos.i.hi = (s16)(cameras[layer][0] + v->x);
    obj.y_pos.i.hi = (s16)(cameras[layer][1] + v->y);
    obj.runtime.search_light.pause_timer = 1;
    expected = obj;
    expected.runtime.search_light.pause_timer = 0;
    expected.on_screen = v->visible;
    expected.state = v->visible ? 1 : 2;
    assert(search_light_is_visible(&obj) == v->visible);
    SearchLightUpdate(&obj);
    check();
    return 1;
}

static u32 test_endpoint_lifecycle(u32 row)
{
    u32 type = row % 6, direction = (row / 6) % 2, seed = (row / 12) % 8, layer = row / 96, tick;
    s32 sign = direction ? -1 : 1;
    s32 end = shapes[type].vertices[0] + sign * shapes[type].extent;
    seed_sweep(type, layer, seed);
    obj.unk5 = 1;
    obj.link.direction = direction;
    obj.runtime.search_light.base_speed = sign * speeds[type / 2];
    obj.ext.search_light.acceleration = -sign * accels[type / 2];
    obj.ext.search_light.velocity = sign * 0x8001 - obj.ext.search_light.acceleration;
    place_top(end * 65536 + 0x4321, sign * 0x8001, type);
    expect_integrate();
    expect_endpoint(type, direction, seed);
    SearchLightUpdate(&obj);
    check_object();
    for (tick = 0; tick < seed; tick++) {
        expected.runtime.search_light.pause_timer--;
        SearchLightUpdate(&obj);
        check_object();
    }
    expect_integrate();
    expected.unk5 = 3;
    expected.ext.search_light.acceleration = -sign * accels[type / 2];
    expected.runtime.search_light.base_speed = -sign * speeds[type / 2];
    SearchLightUpdate(&obj);
    check_object();
    expect_integrate();
    SearchLightUpdate(&obj);
    check_object();
    obj.x_pos.i.hi = expected.x_pos.i.hi = 10000;
    obj.y_pos.i.hi = expected.y_pos.i.hi = 10000;
    obj.runtime.search_light.pause_timer = 1;
    expected.runtime.search_light.pause_timer = 0;
    expected.on_screen = 0;
    expected.state = 2;
    expected.unk5 = 0;
    SearchLightUpdate(&obj);
    check_object();
    expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
    expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    spawner_expected.active = 0;
    SearchLightUpdate(&obj);
    check();
    return 1;
}

static u32 test_motion_helper(u32 row)
{
    static const s32 vectors[6][4] = {
        { 0x28000, -0x2000, -0x34567, 0x456 },
        { -0x28000, 0x2000, 0x34567, -0x456 },
        { 0, 0x1000, 0, -0x400 },
        { 0, -0x1000, 0, 0x400 },
        { 0x8000, 0, -0x8000, 0 },
        { -0x8000, 0, 0x8000, 0 },
    };
    static const u8 steps[5] = { 1, 2, 3, 7, 16 };
    struct Unk22 value, want;
    u32 i, n = steps[row / 6], v = row % 6;
    memset(&value, 0xA5, sizeof(value));
    value.unk38 = vectors[v][0];
    value.unk3C = vectors[v][1];
    value.unk40 = vectors[v][2];
    value.unk44 = vectors[v][3];
    value.unk48 = -0x1234567;
    value.unk4C = 0x2345678;
    want = value;
    want.unk38 += n * value.unk3C;
    want.unk40 += n * value.unk44;
    want.unk48 += (s32)n * value.unk38 + (s32)(n * (n - 1) / 2) * value.unk3C;
    want.unk4C += (s32)n * value.unk40 + (s32)(n * (n - 1) / 2) * value.unk44;
    for (i = 0; i < n; i++)
        search_light_move(&value);
    c_test_same_words(&value, &want, sizeof(want));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "init", 0, 0, 12, test_init },
    { "coast_and_accelerate_edges", 0, 0, COUNT(edges), test_edges },
    { "brake_and_endpoint", 0, 0, 36, test_endpoints },
    { "reverse", 0, 0, 6, test_reverse },
    { "pause", 0, 0, 6, test_pause },
    { "visibility", 0, 0, 6, test_visibility },
    { "endpoint_lifecycle", 0, 0, 6, test_endpoint_lifecycle },
    { "motion_helper", 0, 0, 6, test_motion_helper },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12 + COUNT(edges) + 36 + 6 + 6 + 6 + 6 + 6;
