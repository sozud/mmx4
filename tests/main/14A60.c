#include "test_runtime.h"
#include "main/14A60.h"
#include "main/1AC84.h"
#include "support/sprite_render_fixture.h"

static u32 subtract_all_channels(void)
{
    POLY_F4 primitive;
    struct DrawInfo draw;
    u32 actual;
    memset(&primitive, 0, sizeof(primitive));
    memset(&draw, 0, sizeof(draw));
    memset(&engine_obj, 0, sizeof(engine_obj));
    cur_draw_info = &draw;
    SP_AUX_CURSOR = &primitive;
    setaddr(&draw.ordering_table.unk3, 0x00543210);
    g_FilterAmountR = 1;
    g_FilterAmountG = 1 << 5;
    g_FilterAmountB = 1 << 10;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    func_80025588(-17, 319, -3, 239, 0);
    assert(primitive.x0 == -17 && primitive.x2 == -17);
    assert(primitive.x1 == 319 && primitive.x3 == 319);
    assert(primitive.y0 == -3 && primitive.y1 == -3);
    assert(primitive.y2 == 239 && primitive.y3 == 239);
    assert(getcode(&primitive) == 0x28 && getlen(&primitive) == 5);
    assert(getaddr(&primitive) == 0x00543210);
    assert(nextPrim(&draw.ordering_table.unk3) == &primitive);
    assert(SP_AUX_POLY_F4_CURSOR == &primitive + 1);
    actual = primitive.r0 | ((u32)primitive.g0 << 8) | ((u32)primitive.b0 << 16);
    return actual;
}

static const CTestCase hud_color_subtraction_cases[] = {
    subtract_all_channels,
};
static const u32 hud_color_subtraction_cases_expected[] = { 0x39CE00u };

static const u32 func_80025588_expected[] = { 0x42u, 0x28u, 0xD6u, 8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80025588(u32 row)
{
    u32 observed_values[12];
    POLY_F4 child_0;
    struct DrawInfo child_1;
    s16 arg0;
    s16 arg1;
    s16 arg2;
    s16 arg3;
    s32 arg4;
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_FilterAmountB, 0, sizeof(g_FilterAmountB));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&g_FilterAmountR, 0, sizeof(g_FilterAmountR));
    memset(&g_FilterModeB, 0, sizeof(g_FilterModeB));
    memset(&g_FilterModeG, 0, sizeof(g_FilterModeG));
    memset(&g_FilterModeR, 0, sizeof(g_FilterModeR));
    g_FilterAmountB = 65535;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    engine_obj.stage = 2;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    arg0 = 0;
    arg1 = 0;
    arg2 = 0;
    arg3 = 0;
    arg4 = 0;
    SP_AUX_CURSOR = &child_0;
    cur_draw_info = &child_1;
    func_80025588(arg0, arg1, arg2, arg3, arg4);
    observed_values[0] = (u32)child_0.b0;
    observed_values[1] = (u32)child_0.code;
    observed_values[2] = (u32)child_0.g0;
    observed_values[3] = (u32)child_0.r0;
    observed_values[4] = (u32)child_0.x0;
    observed_values[5] = (u32)child_0.x1;
    observed_values[6] = (u32)child_0.x2;
    observed_values[7] = (u32)child_0.x3;
    observed_values[8] = (u32)child_0.y0;
    observed_values[9] = (u32)child_0.y1;
    observed_values[10] = (u32)child_0.y2;
    observed_values[11] = (u32)child_0.y3;
    return c_test_observe(0, row, observed_values, func_80025588_expected, 12);
}

extern u8 D_800F2B5C[21][12];
static POLY_FT4 primitives_14A60[4], expected_primitives_14A60[4];
static DR_TPAGE modes_14A60[4], expected_modes_14A60[4];
static P_TAG heads_14A60[2][4][8], expected_heads_14A60[2][4][8];
static P_TAG* expected_tails_14A60[2][4][8];
static u32 quad_capacity(u32 row)
{
    struct QuadObj obj, before;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 2, semi = row / 2 % 2, world = row / 4 % 2, buffer = row / 8, b, g, p, i;
    POLY_F4* f;
    POLY_G4* c;
    memset(primitives_14A60, 0xA5, sizeof(primitives_14A60));
    memset(modes_14A60, 0x5A, sizeof(modes_14A60));
    memset(heads_14A60, 0x36, sizeof(heads_14A60));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = 7;
    background_objects[0].y_pos.i.hi = -9;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (b = 0; b < 2; b++)
        for (g = 0; g < 4; g++)
            for (p = 0; p < 8; p++)
                D_8013BC40[b][g][p] = &heads_14A60[b][g][p];
    memset(&obj, 0, sizeof(obj));
    obj.active = semi ? 0x11 : 1;
    obj.id = 4;
    obj.bg_offset = world ? 0 : -1;
    obj.unk34 = kind ? 0 : 0x2341;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    for (i = 0; i < 4; i++) {
        obj.vertices[i].x.i.hi = i % 2 ? 10 : -10;
        obj.vertices[i].y.i.hi = i / 2 ? 6 : -6;
    }
    before = obj;
    SP_PRIM_CURSOR = &primitives_14A60[1];
    SP_DRAW_MODE_CURSOR = &modes_14A60[1];
    SP_DRAW_BUFFER = buffer;
    SP_SPRITE_COUNT = 999;
    memcpy(expected_primitives_14A60, primitives_14A60, sizeof(primitives_14A60));
    memcpy(expected_modes_14A60, modes_14A60, sizeof(modes_14A60));
    memcpy(expected_heads_14A60, heads_14A60, sizeof(heads_14A60));
    memcpy(expected_tails_14A60, D_8013BC40, sizeof(expected_tails_14A60));
    f = (POLY_F4*)&expected_primitives_14A60[1];
    c = (POLY_G4*)&expected_primitives_14A60[1];
    if (kind) {
        setPolyG4(c);
        c->code = semi ? 0x3A : 0x38;
        c->r0 = D_800F2B5C[0][0];
        c->g0 = D_800F2B5C[0][1];
        c->b0 = D_800F2B5C[0][2];
        c->r1 = D_800F2B5C[0][3];
        c->g1 = D_800F2B5C[0][4];
        c->b1 = D_800F2B5C[0][5];
        c->r3 = D_800F2B5C[0][6];
        c->g3 = D_800F2B5C[0][7];
        c->b3 = D_800F2B5C[0][8];
        c->r2 = D_800F2B5C[0][9];
        c->g2 = D_800F2B5C[0][10];
        c->b2 = D_800F2B5C[0][11];
        c->x0 = 150 - world * 7;
        c->x1 = 170 - world * 7;
        c->x2 = 170 - world * 7;
        c->x3 = 150 - world * 7;
        c->y0 = c->y1 = 114 + world * 9;
        c->y2 = c->y3 = 126 + world * 9;
    } else {
        setPolyF4(f);
        f->code = semi ? 0x2A : 0x28;
        f->r0 = 8;
        f->g0 = 214;
        f->b0 = 66;
        f->x0 = 150 - world * 7;
        f->x1 = 170 - world * 7;
        f->x2 = 170 - world * 7;
        f->x3 = 150 - world * 7;
        f->y0 = f->y1 = 114 + world * 9;
        f->y2 = f->y3 = 126 + world * 9;
    }
    setlen(&expected_modes_14A60[1], 1);
    expected_modes_14A60[1].code[0] = 0xE1000000;
    setaddr(&expected_heads_14A60[buffer][0][0], &modes_14A60[1]);
    setaddr(&expected_modes_14A60[1], &primitives_14A60[1]);
    expected_tails_14A60[buffer][0][0] = (P_TAG*)&primitives_14A60[1];
    if (kind) {
        func_80024B9C(&obj);
        func_80024B9C(&obj);
    } else {
        func_80024920(&obj);
        func_80024920(&obj);
    }
    c_test_same_words(primitives_14A60, expected_primitives_14A60, sizeof(primitives_14A60));
    c_test_same_words(modes_14A60, expected_modes_14A60, sizeof(modes_14A60));
    c_test_same_words(heads_14A60, expected_heads_14A60, sizeof(heads_14A60));
    c_test_same_words(D_8013BC40, expected_tails_14A60, sizeof(expected_tails_14A60));
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(SP_SPRITE_COUNT == 1000 && SP_DRAW_BUFFER == buffer && SP_PRIM_CURSOR == &primitives_14A60[2] && SP_DRAW_MODE_CURSOR == &modes_14A60[2]);
    return 1;
}

#ifdef MMX4_PC
static u32 renderer_guard(u32 row)
{
    struct VisualObj local, local_before;
    memset(&local, 0, sizeof(local));
    render_setup(10, 0, &render_vectors[0], 0);
    if (row == 0)
        misc_objects[0].unk3C = NULL;
    else {
        local = visual_objects[0];
        local.unk3C = frames;
        object = &local;
    }
    local_before = local;
    render_snapshot();
    func_80024334(object);
    R_SAME(local, local_before);
    return render_check(0, 0);
}
static u32 readonly_renderer_guard(u32 row)
{
    static const struct VisualObj readonly = { .unk3C = frames };
    struct VisualObj before_readonly = readonly;
    render_setup(10, 0, &render_vectors[0], 0);
    object = (struct VisualObj*)&readonly;
    render_snapshot();
    func_80024334(object);
    R_SAME(readonly, before_readonly);
    return render_check(0, 0);
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "hud_color_subtraction", hud_color_subtraction_cases, hud_color_subtraction_cases_expected, COUNT(hud_color_subtraction_cases), 0 },
    { "func_80025588", 0, 0, 1, test_func_80025588 },
    { "flat_and_gouraud_last_primitive_then_capacity_guard", NULL, NULL, 16, quad_capacity },
    { "sprite_pool_commands", NULL, NULL, 24, render_pool_case },
    { "sprite_empty_and_capacity", NULL, NULL, 36, render_limit_case },
#ifdef MMX4_PC
    { "pc_rejects_missing_or_unregistered_frame", NULL, NULL, 2, renderer_guard },
    { "pc_rejects_readonly_unregistered_object", NULL, NULL, 1, readonly_renderer_guard },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hud_color_subtraction_cases) + 1 + 16 + 24 + 36
#ifdef MMX4_PC
    + 2
    + 1
#endif
    ;
