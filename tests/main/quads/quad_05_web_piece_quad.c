#include "test_runtime.h"
#include "main/quads/quad_05_web_piece_quad.h"

static u32 quad_case(u32 mode, u32 observation)
{
    struct QuadObj obj, before;
    struct BackgroundObj background_before[3];
    u32 i, index, scale;
    s32* frame;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0xC1;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.bg_offset = 0;
    obj.x_pos.i.hi = mode == 0 ? 2000 : 100;
    obj.y_pos.i.hi = mode == 0 ? 2000 : 100;
    obj.ext.quad_5.index = 7;
    obj.ext.quad_5.scale = mode == 0 ? 0x100 : 0x500;
    obj.ext.quad_5.update_timer = mode == 0 ? 0 : 2;
    before = obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    web_piece_quad_main(&obj);
    index = mode == 0 ? 7 : 0;
    scale = 0x100;
    frame = web_piece_quad_frame_table[index];
    before.ext.quad_5.index = index;
    before.ext.quad_5.scale = scale;
    before.ext.quad_5.update_timer = mode == 0 ? 1 : 0;
    before.ext.quad_5.data = frame;
    for (i = 0; i < 4; i++) {
        before.vertices[i].x.val = frame[i * 2] * scale;
        before.vertices[i].y.val = frame[i * 2 + 1] * scale;
    }
    before.on_screen = mode == 0 ? 0 : 1;
    if (mode == 0) {
        before.state = 2;
        before.unk5 = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    return observation == 0 ? (u8)obj.state | ((u32)(u8)obj.on_screen << 8) | ((u32)obj.ext.quad_5.index << 16) : (u32)obj.vertices[1].x.val;
}
#define CASE(m, n)                                                    \
    static u32 web_piece_quad_visibility_context_quad_##m##_##n(void) \
    {                                                                 \
        return quad_case(m, n);                                       \
    }
CASE(0, 0)
CASE(0, 1)
CASE(1, 0)
CASE(1, 1)
#define ENTRY(m, n) web_piece_quad_visibility_context_quad_##m##_##n,
static const CTestCase web_piece_quad_visibility_context_cases[]
    = { ENTRY(0, 0) ENTRY(0, 1) ENTRY(1, 0) ENTRY(1, 1) };
static const u32 web_piece_quad_visibility_context_cases_expected[] = { 0x70002u, 0x10000u, 0x101u, 0x80000u };
#undef CASE
#undef ENTRY

static const u32 inputs_0[2][15] = {
    { 32768, 0, 0, 0, 0, 0, 0, 0, 0, -1024, 0, -32768, 0, 23328, 32769 },
    { 53280, 0, 0, 0, 0, 57348, 6144, 0, 0, 8192, 0, -7168, 0, 25440, 1024 },
};
struct web_piece_quad_is_visible_case {
    u32 expected[1];
};
static const struct web_piece_quad_is_visible_case web_piece_quad_is_visible_cases[] = {
    { { 0u } },
    { { 0u } },
};
static u32 test_web_piece_quad_is_visible(u32 row)
{
    const struct web_piece_quad_is_visible_case* c = &web_piece_quad_is_visible_cases[row];
    u32 observed_values[1];
    struct QuadObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.x_pos.u.hi = inputs_0[row][0];
    background_objects[0].x_pos.u.hi = inputs_0[row][1];
    background_objects[1].x_pos.u.hi = inputs_0[row][2];
    background_objects[2].x_pos.u.hi = inputs_0[row][3];
    obj.bg_offset = inputs_0[row][4];
    obj.y_pos.u.hi = inputs_0[row][5];
    background_objects[0].y_pos.u.hi = inputs_0[row][6];
    background_objects[1].y_pos.u.hi = inputs_0[row][7];
    background_objects[2].y_pos.u.hi = inputs_0[row][8];
    obj.vertices[1].x.i.hi = inputs_0[row][9];
    obj.vertices[0].x.i.hi = inputs_0[row][10];
    obj.vertices[3].y.i.hi = inputs_0[row][11];
    obj.vertices[0].y.i.hi = inputs_0[row][12];
    obj.vertices[0].x.u.hi = inputs_0[row][13];
    obj.vertices[0].y.u.hi = inputs_0[row][14];
    return_value = web_piece_quad_is_visible(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 web_piece_quad_main_expected[] = { 1u, 0x100u, 0u, 1u, 0u, 0u };
static u32 test_web_piece_quad_main(u32 row)
{
    u32 observed_values[6];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.quad_5.update_timer = 2;
    obj.ext.quad_5.index = 0;
    obj.ext.quad_5.scale = 1232;
    web_piece_quad_main(&obj);
    observed_values[0] = (u32)obj.ext.quad_5.index;
    observed_values[1] = (u32)obj.ext.quad_5.scale;
    observed_values[2] = (u32)obj.ext.quad_5.update_timer;
    observed_values[3] = (u32)obj.on_screen;
    observed_values[4] = (u32)obj.state;
    observed_values[5] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, web_piece_quad_main_expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "web_piece_quad_visibility_context", web_piece_quad_visibility_context_cases, web_piece_quad_visibility_context_cases_expected, COUNT(web_piece_quad_visibility_context_cases), 0 },
    { "web_piece_quad_is_visible", 0, 0, 2, test_web_piece_quad_is_visible },
    { "web_piece_quad_main", 0, 0, 1, test_web_piece_quad_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_piece_quad_visibility_context_cases) + 2 + 1;
