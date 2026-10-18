#include "test_runtime.h"
#include "main/quads/quad_01_stage_select_panel.h"
extern s16 stage_select_panel_shapes[8][8];
u8 func_800D41EC(s32*, s32*, s32, s32, s32, s32);
extern s32 D_800F459C[9], D_800F45C0[9];

static u32 panel_case(u32 mode)
{
    struct QuadObj obj, expected;
    struct MiscObj misc_expected[64];
    struct EffectObj effects_expected[32];
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    s16 shapes_before[8][8];
    u32 i, misc_free = mode >= 5 && mode <= 10 ? (mode - 5) / 2 : 2;
    u32 effect_free = mode >= 5 && mode <= 10 ? (mode - 5) % 2 : 1;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(shapes_before, stage_select_panel_shapes, sizeof(shapes_before));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - misc_free ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i >= 32 - effect_free ? 0 : 1;
        effect_objects[i].id = 39;
        effect_objects[i].state = 40;
        effect_objects[i].unk2 = 9;
        effect_objects[i].unk5 = 3;
        effect_objects[i].unk6 = 4;
        effect_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        effect_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 1;
    obj.id = 1;
    obj.state = 1;
    obj.unk2 = mode % 8;
    obj.unk5 = 7;
    obj.bg_offset = -1;
    obj.on_screen = 0;
    obj.x_pos.val = 0xABCD;
    obj.y_pos.val = 0xDCBA;
    obj.ext.quad_1.delay = mode == 0 ? 2 : 0;
    obj.ext.quad_1.steps = mode >= 5 && mode <= 10 ? 1 : 2;
    obj.ext.quad_1.unk42 = mode == 1 ? 1 : 0;
    for (i = 0; i < 4; i++) {
        s32 offset = mode == 11 && (i & 1) ? -20 * 65536 : 20 * 65536;
        obj.vertices[i].x.val = stage_select_panel_shapes[obj.unk2][i * 2] * 65536 + offset;
        obj.vertices[i].y.val = stage_select_panel_shapes[obj.unk2][i * 2 + 1] * 65536;
        obj.ext.quad_1.region[i] = mode == 2 ? 0 : offset < 0 ? 0
                                                              : 16;
        obj.ext.quad_1.settled[i] = mode == 3 || (mode == 11 && i == 1) ? 1 : 0;
    }
    expected = obj;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    expected.on_screen = 1;
    if (mode == 0)
        expected.ext.quad_1.delay--;
    else {
        for (i = 0; i < 4; i++) {
            if (mode == 2 || mode == 3 || (mode == 11 && i == 1)) {
                expected.x_pos.i.lo = 0;
                expected.y_pos.i.lo = 0;
                expected.ext.quad_1.settled[i] = 1;
            } else {
                s32 offset = mode == 11 && (i & 1) ? -20 * 65536 : 20 * 65536;
                expected.vertices[i].x.val -= offset / obj.ext.quad_1.steps;
                expected.ext.quad_1.settled[i] = 0;
                if (i == 3)
                    expected.ext.quad_1.unk42 = 0;
            }
            expected.ext.quad_1.region[i] = mode == 11 && (i & 1) ? 0 : 16;
        }
        expected.ext.quad_1.steps--;
        if (expected.ext.quad_1.steps == 0) {
            expected.state = 2;
            for (i = 0; i < 4; i++) {
                expected.vertices[i].x.i.hi = stage_select_panel_shapes[obj.unk2][i * 2];
                expected.vertices[i].y.i.hi = stage_select_panel_shapes[obj.unk2][i * 2 + 1];
            }
            for (i = 0; i < misc_free; i++) {
                misc_expected[64 - misc_free + i].active = 0x41;
                misc_expected[64 - misc_free + i].id = 0xC;
                misc_expected[64 - misc_free + i].unk2 = obj.unk2 | (i ? 0x80 : 0);
            }
            if (effect_free) {
                effects_expected[31].active = 1;
                effects_expected[31].id = 3;
                effects_expected[31].unk2 = 0;
            }
        }
    }
    func_800D43F4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(misc_expected) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_expected)[i]);
    for (i = 0; i < sizeof(effects_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)effects_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 64; i++)
        assert(((s16*)stage_select_panel_shapes)[i] == ((s16*)shapes_before)[i]);
    return obj.state | ((u32)obj.ext.quad_1.steps << 8) | ((u32)(u8)misc_objects[63].unk2 << 16) | ((u32)(u8)effect_objects[31].id << 24);
}
#define CASE(m)                                                \
    static u32 stage_panel_interpolation_pools_panel_##m(void) \
    {                                                          \
        return panel_case(m);                                  \
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
#define ENTRY(m) stage_panel_interpolation_pools_panel_##m,
static const CTestCase stage_panel_interpolation_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) };
static const u32 stage_panel_interpolation_pools_cases_expected[] = { 0x27090201u, 0x27090101u, 0x27090101u, 0x27090101u, 0x27090101u, 0x27090002u, 0x3090002u, 0x27070002u, 0x3000002u, 0x27810002u, 0x3820002u, 0x27090101u };
#undef CASE
#undef ENTRY

static const s8 dx[11] = { -8, 8, 8, -8, -8, 0, 8, 0, 0, -8, -8 };
static const s8 dy[11] = { -8, -8, 8, 8, 0, 8, 0, -8, 0, -8, 8 };
static const u8 angles[11] = { 28, 20, 12, 4, 0, 8, 16, 24, 16, 28, 4 };
static const s32 x_steps[11] = { 115852, -115853, -115853, 115852, 163840, 0, -163840, 0, -163840, -115853, 46340 };
static const s32 y_steps[11] = { 69511, 69511, -69512, -69512, 0, -98304, 0, 98304, 0, -69512, 46340 };
static const s32 x_table[9] = { 0, 0x31F1, 0x61F7, 0x8E39, 0xB505, 0xD4DB, 0xEC83, 0xFB14, 0x10000 };
static const s32 y_table[9] = { 0x10000, 0xFB14, 0xEC83, 0xD4DB, 0xB505, 0x8E39, 0x61F7, 0x31F1, 0 };
static u32 move_case(u32 mode, u32 observation)
{
    s32 position[4] = { 0x11223344, 100 * 65536 + 0x1234, 200 * 65536 + 0x5678, 0x55667788 };
    s32 initial_x = position[1], initial_y = mode == 10 ? position[1] : position[2];
    s32 target_x = initial_x - dx[mode] * 65536, target_y = initial_y - dy[mode] * 65536;
    s32* y = mode == 10 ? &position[1] : &position[2];
    struct PlayerObj player_before = g_Player;
    u32 i, result;
    u8 angle = func_800D41EC(&position[1], y, target_x, target_y,
        mode == 9 ? -40 : 40, mode == 9 ? -24 : 24);
    assert(angle == angles[mode]);
    assert(position[1] == initial_x + x_steps[mode] && *y == initial_y + y_steps[mode]);
    assert(position[0] == 0x11223344 && position[3] == 0x55667788);
    if (mode == 10)
        assert(position[2] == 200 * 65536 + 0x5678);
    for (i = 0; i < 9; i++) {
        assert(D_800F459C[i] == x_table[i]);
        assert(D_800F45C0[i] == y_table[i]);
    }
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    result = observation == 0 ? angle : observation == 1 ? position[1]
                                                         : *y;
    return result;
}
#define CASE(m, n)                                              \
    static u32 stage_select_move_quadrants_move_##m##_##n(void) \
    {                                                           \
        return move_case(m, n);                                 \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
MODE(7)
MODE(8)
MODE(9)
MODE(10)
#define ENTRY(m, n) stage_select_move_quadrants_move_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2)
static const CTestCase stage_select_move_quadrants_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) ENTRIES(8) ENTRIES(9) ENTRIES(10) };
static const u32 stage_select_move_quadrants_cases_expected[] = { 0x1Cu, 0x65D6C0u, 0xC965FFu, 0x14u, 0x624DA7u, 0xC965FFu, 0xCu, 0x624DA7u, 0xC746F0u, 0x4u, 0x65D6C0u, 0xC746F0u, 0x0u, 0x669234u, 0xC85678u, 0x8u, 0x641234u, 0xC6D678u, 0x10u, 0x619234u, 0xC85678u, 0x18u, 0x641234u, 0xC9D678u, 0x10u, 0x619234u, 0xC85678u, 0x1Cu, 0x624DA7u, 0xC746F0u, 0x4u, 0x64C738u, 0x64C738u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 quad_is_on_screen_expected[] = { 1u };
static u32 test_quad_is_on_screen(u32 row)
{
    u32 observed_values[1];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.bg_offset = -128;
    obj.vertices[0].y.i.hi = 240;
    obj.vertices[1].x.i.hi = 320;
    obj.vertices[1].y.i.hi = 0;
    obj.vertices[2].x.i.hi = 1024;
    obj.vertices[2].y.i.hi = 0;
    obj.vertices[3].x.i.hi = 0;
    obj.vertices[3].y.i.hi = 0;
    quad_is_on_screen(&obj);
    observed_values[0] = (u32)obj.on_screen;
    return c_test_observe(0, row, observed_values, quad_is_on_screen_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "stage_panel_interpolation_pools", stage_panel_interpolation_pools_cases, stage_panel_interpolation_pools_cases_expected, COUNT(stage_panel_interpolation_pools_cases), 0 },
    { "stage_select_move_quadrants", stage_select_move_quadrants_cases, stage_select_move_quadrants_cases_expected, COUNT(stage_select_move_quadrants_cases), 0 },
    { "quad_is_on_screen", 0, 0, 1, test_quad_is_on_screen },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_panel_interpolation_pools_cases) + COUNT(stage_select_move_quadrants_cases) + 1;
