#include "test_runtime.h"
extern u16 ready_line_sweep_vertices[8];
extern s16 ready_line_shutter_close_vertices[10][4][2];
extern u16 ready_line_shutter_repeats;

static u32 sweep_case(u32 mode)
{
    static const s16 x[] = { 100, 0, 1, 2, 3, 1, 320, 1, -1, 319, 1, 1 };
    struct QuadObj obj, expected;
    struct EffectObj owner, owner_before;
    struct MiscObj pool[64];
    struct PlayerObj player_before = g_Player;
    u32 i, available = mode == 2 ? 1 : mode >= 3 && mode <= 7 ? 2
                                                              : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    owner.active = 1;
    owner.id = 27;
    owner.state = 1;
    owner.ext.unk_effect.unk14 = 11;
    owner.ext.unk_effect.unk15 = mode == 5;
    obj.active = -127;
    obj.id = 7;
    obj.state = 1;
    obj.unk5 = mode == 0 ? 0 : mode == 7 ? 2
        : mode == 10                     ? 3
                                         : 1;
    if (mode == 11)
        obj.unk5 = -1;
    obj.link.owner = &owner;
    obj.x_pos.val = x[mode] * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.ready_line.x_vel.val = 32 * 65536;
    obj.ext.ready_line.y_vel.val = -32768;
    obj.ext.ready_line.x_accel.val = 0x1000;
    obj.ext.ready_line.y_accel.val = 0x2000;
    for (i = 0; i < 4; i++) {
        obj.vertices[i].x.val = i * 65536 + 0xCAFE;
        obj.vertices[i].y.val = i * 65536 + 0xBEEF;
    }
    expected = obj;
    owner_before = owner;
    memcpy(pool, misc_objects, sizeof(pool));
    if (mode == 0) {
        static const u16 vertices[] = { 0, 0, 320, 0, 320, 4, 0, 4 };
        expected.unk5 = 1;
        expected.x_pos.i.hi = -320;
        expected.y_pos.i.hi = 112;
        for (i = 0; i < 4; i++) {
            assert(ready_line_sweep_vertices[i * 2] == vertices[i * 2] && ready_line_sweep_vertices[i * 2 + 1] == vertices[i * 2 + 1]);
            expected.vertices[i].x.i.hi = vertices[i * 2];
            expected.vertices[i].y.i.hi = vertices[i * 2 + 1];
        }
        expected.ext.ready_line.x_vel.val = 32 * 65536;
        expected.ext.ready_line.y_vel.val = 0;
        expected.ext.ready_line.x_accel.val = expected.ext.ready_line.y_accel.val = 0;
    }
    if (mode <= 5 || mode == 8 || mode == 9) {
        expected.x_pos.val += expected.ext.ready_line.x_vel.val;
        expected.y_pos.val += expected.ext.ready_line.y_vel.val;
        expected.ext.ready_line.x_vel.val += expected.ext.ready_line.x_accel.val;
        expected.ext.ready_line.y_vel.val += expected.ext.ready_line.y_accel.val;
        if (mode == 2 || mode == 3) {
            for (i = 0; i < available; i++) {
                pool[64 - available + i].active = 1;
                pool[64 - available + i].id = 0x12;
                pool[64 - available + i].unk2 = i;
                pool[64 - available + i].ext.ready_text.owner = &owner;
            }
        }
    } else if (mode == 6)
        expected.unk5 = 2;
    else if (mode == 7) {
        owner_before.ext.unk_effect.unk14 = 0;
        expected.state = 2;
        expected.unk5 = 0;
    }
    ready_line_sweep(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u16)obj.x_pos.i.hi << 8) | ((u32)(u8)owner.ext.unk_effect.unk14 << 24);
}
#define CASE(m)                                            \
    static u32 ready_line_sweep_pool_edges_sweep_##m(void) \
    {                                                      \
        return sweep_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
#define ENTRY(m) ready_line_sweep_pool_edges_sweep_##m,
static const CTestCase ready_line_sweep_pool_edges_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) };
static const u32 ready_line_sweep_pool_edges_cases_expected[] = { 0xBFEE001u, 0xB002001u, 0xB002101u, 0xB002201u, 0xB002301u, 0xB002101u, 0xB014002u, 0x100u, 0xB001F01u, 0xB015F01u, 0xB000103u, 0xB0001FFu };
#undef CASE
#undef ENTRY

static u32 shutter_case(u32 raw)
{
    struct QuadObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0xC1;
    obj.id = 7;
    obj.state = 1;
    obj.unk5 = raw == 1 ? 4 : 2;
    obj.unk7 = 0;
    obj.runtime.ready_line.interpolation_frames = 1;
    obj.runtime.ready_line.converging = 1;
    for (i = 0; i < 4; i++) {
        obj.vertices[i].x.val = ready_line_shutter_close_vertices[0][i][0] * 65536;
        obj.vertices[i].y.val = ready_line_shutter_close_vertices[0][i][1] * 65536;
    }
    before = obj;
    ready_line_shutter_repeats = raw == 2 ? 1 : 0;
    ready_line_shutter(&obj);
    if (raw != 1) {
        before.unk5 = 3;
        before.runtime.legacy.unk50 = 16;
        before.runtime.legacy.unk54 = before.runtime.legacy.unk55 = 1;
        for (i = 0; i < 4; i++) {
            before.runtime.ready_line.directions[i] = angle_from_delta(0, 0);
            before.runtime.ready_line.crossed[i] = 0;
        }
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(ready_line_shutter_repeats == 0);
    actual = (u8)obj.unk5 | ((u32)obj.runtime.ready_line.interpolation_frames << 16);
    return actual;
}
#define CASE(m)                                                  \
    static u32 ready_shutter_close_and_default_shutter_##m(void) \
    {                                                            \
        return shutter_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
static const CTestCase ready_shutter_close_and_default_cases[] = { ready_shutter_close_and_default_shutter_0, ready_shutter_close_and_default_shutter_1, ready_shutter_close_and_default_shutter_2 };
static const u32 ready_shutter_close_and_default_cases_expected[] = { 0x100003u, 0x10004u, 0x100003u };
#undef CASE

static u32 vertex_case(u32 mode, u32 observation)
{
    struct QuadObj quad;
    struct QuadVertex before[4];
    s16 target[2] = { 10, 20 };
    u32 index, i, value;
    s32 dx = -7 * 65536 + 0x1234, dy = 5 * 65536 + 0x2468;
    u8 angle = angle_from_delta(dx, dy);

    memset(&quad, 0, sizeof(quad));
    index = mode == 0 ? 0 : mode == 3 ? 1
                                      : 3;
    quad.state = 1;
    quad.x_pos.val = 30 * 65536 + 0x2468;
    quad.y_pos.val = 50 * 65536 + 0x1234;
    for (i = 0; i < 4; i++) {
        quad.vertices[i].x.val = 100 * 65536 + i;
        quad.vertices[i].y.val = 200 * 65536 + i;
        quad.runtime.ready_line.directions[i] = 0xAA;
        quad.runtime.ready_line.crossed[i] = 0x55;
    }
    quad.vertices[index].x.val = target[0] * 65536 + dx;
    quad.vertices[index].y.val = target[1] * 65536 + dy;
    memcpy(before, quad.vertices, sizeof(before));
    quad.runtime.ready_line.directions[index] = mode == 0 || mode == 2 ? angle ^ 0x10 : angle;
    quad.runtime.ready_line.crossed[index] = mode == 1;
    quad.runtime.ready_line.converging = mode == 2;
    quad.runtime.ready_line.interpolation_frames = 8;
    ready_line_converge_vertex(&quad, 0, index, target);

    assert(target[0] == 10 && target[1] == 20);
    assert(quad.state == 1 && quad.x_pos.i.hi == 30 && quad.y_pos.i.hi == 50);
    assert(quad.runtime.ready_line.interpolation_frames == 8);
    for (i = 0; i < 4; i++) {
        if (i != index) {
            assert(quad.vertices[i].x.val == before[i].x.val);
            assert(quad.vertices[i].y.val == before[i].y.val);
            assert(quad.runtime.ready_line.directions[i] == 0xAA);
            assert(quad.runtime.ready_line.crossed[i] == 0x55);
        }
    }
    if (observation == 0)
        return (u32)quad.vertices[index].x.val;
    if (observation == 1)
        return (u32)quad.vertices[index].y.val;
    if (observation == 2)
        return quad.x_pos.u.lo | ((u32)quad.y_pos.u.lo << 16);
    value = quad.runtime.ready_line.directions[index] | ((u32)quad.runtime.ready_line.crossed[index] << 8) | ((u32)quad.runtime.ready_line.converging << 16);
    return value;
}
#define OBSERVE(mode, field)                             \
    static u32 ready_vertex_ready_##mode##_##field(void) \
    {                                                    \
        return vertex_case(mode, field);                 \
    }
#define MODE(mode) OBSERVE(mode, 0) OBSERVE(mode, 1) OBSERVE(mode, 2) OBSERVE(mode, 3)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(mode, field) ready_vertex_ready_##mode##_##field,
#define ENTRIES(mode) ENTRY(mode, 0) ENTRY(mode, 1) ENTRY(mode, 2) ENTRY(mode, 3)
static const CTestCase ready_vertex_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 ready_vertex_cases_expected[] = { 0x31234u, 0x192468u, 0x0u, 0x103u, 0x31234u, 0x192468u, 0x0u, 0x103u, 0x3EFEDu, 0x187FDBu, 0x12342468u, 0x3u, 0x3EFEDu, 0x187FDBu, 0x12342468u, 0x3u };
#undef OBSERVE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 ready_line_shutter_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_ready_line_shutter(u32 row)
{
    u32 observed_values[21];
    struct QuadObj obj;
    struct EffectObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&ready_line_shutter_repeats, 0, sizeof(ready_line_shutter_repeats));
    obj.unk5 = -1;
    ready_line_shutter_repeats = 0;
    child_0_present = 0;
    obj.link.owner = child_0_present ? &child_0 : NULL;
    ready_line_shutter(&obj);
    observed_values[0] = (u32)child_0.ext.unk_effect.unk14;
    observed_values[1] = (u32)obj.runtime.legacy.unk4C;
    observed_values[2] = (u32)obj.runtime.legacy.unk4D;
    observed_values[3] = (u32)obj.runtime.legacy.unk4E;
    observed_values[4] = (u32)obj.runtime.legacy.unk4F;
    observed_values[5] = (u32)obj.runtime.legacy.unk50;
    observed_values[6] = (u32)obj.runtime.legacy.unk54;
    observed_values[7] = (u32)obj.runtime.legacy.unk55;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk5;
    observed_values[10] = (u32)obj.vertices[0].x.i.hi;
    observed_values[11] = (u32)obj.vertices[0].y.i.hi;
    observed_values[12] = (u32)obj.vertices[1].x.i.hi;
    observed_values[13] = (u32)obj.vertices[1].y.i.hi;
    observed_values[14] = (u32)obj.vertices[2].x.i.hi;
    observed_values[15] = (u32)obj.vertices[2].y.i.hi;
    observed_values[16] = (u32)obj.vertices[3].x.i.hi;
    observed_values[17] = (u32)obj.vertices[3].y.i.hi;
    observed_values[18] = (u32)obj.x_pos.i.hi;
    observed_values[19] = (u32)obj.y_pos.i.hi;
    observed_values[20] = (u32)ready_line_shutter_repeats;
    return c_test_observe(0, row, observed_values, ready_line_shutter_expected, 21);
}

const struct CTestGroup c_test_groups[] = {
    { "ready_line_sweep_pool_edges", ready_line_sweep_pool_edges_cases, ready_line_sweep_pool_edges_cases_expected, COUNT(ready_line_sweep_pool_edges_cases), 0 },
    { "ready_shutter_close_and_default", ready_shutter_close_and_default_cases, ready_shutter_close_and_default_cases_expected, COUNT(ready_shutter_close_and_default_cases), 0 },
    { "ready_vertex", ready_vertex_cases, ready_vertex_cases_expected, COUNT(ready_vertex_cases), 0 },
    { "ready_line_shutter", 0, 0, 1, test_ready_line_shutter },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ready_line_sweep_pool_edges_cases) + COUNT(ready_shutter_close_and_default_cases) + COUNT(ready_vertex_cases) + 1;
