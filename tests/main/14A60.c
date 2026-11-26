#include "test_runtime.h"
#ifndef MMX4_SATURN
#include "main/14A60.h"
#include "main/1AC84.h"
#include "main/player_weapon.h"
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

#ifndef MMX4_SATURN
static const struct {
    u16 r, g, b;
    u8 stage, substage, color;
    u32 expected;
} filter_rows[] = {
    { 2, 2 << 5, 2 << 10, 2, 1, 0, 24 | 231 << 8 | 82 << 16 },
    { 0x1F, 0x1F << 5, 0x1F << 10, 0, 0, 0, 255 | 255 << 8 | 255 << 16 },
    { 1, 2 << 5, 1 << 10, 0, 0, 0, 8 | 214 << 8 | 66 << 16 },
    { 1, 1 << 5, 2 << 10, 0, 0, 0, 8 | 214 << 8 | 66 << 16 },
};
static u32 filter_add(u32 row)
{
    POLY_F4 primitive;
    struct DrawInfo draw;
    u32 actual;
    memset(&primitive, 0, sizeof(primitive));
    memset(&draw, 0, sizeof(draw));
    memset(&engine_obj, 0, sizeof(engine_obj));
    cur_draw_info = &draw;
    SP_AUX_CURSOR = &primitive;
    engine_obj.stage = filter_rows[row].stage;
    engine_obj.substage = filter_rows[row].substage;
    g_FilterAmountR = filter_rows[row].r;
    g_FilterAmountG = filter_rows[row].g;
    g_FilterAmountB = filter_rows[row].b;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 0;
    func_80025588(1, 2, 3, 4, filter_rows[row].color);
    assert(nextPrim(&draw.ordering_table.unk3) == &primitive);
    actual = primitive.r0 | ((u32)primitive.g0 << 8) | ((u32)primitive.b0 << 16);
    assert(actual == filter_rows[row].expected);
    return actual;
}

static u8 hud_archive[8 + 256 * 4 + 256 * 4];
static SPRT_16 hud_sprites[10];
static DR_TPAGE hud_modes[10];
static POLY_F4 hud_bars[6];
static void hud_archive_setup(void)
{
    u32 i;
    memset(hud_archive, 0, sizeof(hud_archive));
    *(s32*)(hud_archive + 4) = 8;
    for (i = 0; i < 256; i++) {
        u8* entry = hud_archive + 8 + i * 4;
        u8* piece = hud_archive + 8 + (256 + i) * 4;
        *(u16*)entry = 1;
        *(u16*)(entry + 2) = 256 + i;
        piece[2] = i;
    }
}
static const u32 hud_expected[4][9] = {
    { 2, 1, 0x00580064, 0x00380065, 0, 0, 0, 0, 0 },
    { 6, 2, 0x00580064, 0x00380065, 0x00160050, 0x00160058, 0x00140076, 0x0038006E, 0 },
    { 7, 3, 0x00580064, 0x00380065, 0x00160050, 0x00160058, 0x00140074, 0x0038006E, 0x0041017C },
    { 2, 1, 0x00580064, 0x00380065, 0, 0, 0, 0, 0 },
};
static u32 hud_status(u32 row)
{
    struct DrawInfo draw;
    u32 observed[9], i, n;
    s8 divisor;
    hud_archive_setup();
    memset(&draw, 0, sizeof(draw));
    memset(&engine_obj, 0, sizeof(engine_obj));
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
    cur_draw_info = &draw;
    TEST_SPRITE_FRAMES = hud_archive;
    SP_BG_PRIM_CURSOR = hud_sprites;
    SP_OT_CURSOR = hud_modes;
    SP_AUX_CURSOR = hud_bars;
    SP_SPRITE_COUNT = 0;
    engine_obj.unk1F = 1;
    engine_obj.player_lives = 2;
    engine_obj.max_hp = 0x20;
    g_Player.hp = ((struct MainObj*)&g_Player)->unk5D = 10;
    g_Player.shot_types[0] = 1;
    divisor = player_weapon_energy.hud.health_divisors[1];
    assert(divisor > 0 && divisor <= 40);
    if (row == 1 || row == 2) {
        g_Player.weapon = row == 1 ? 3 : 1;
        g_Player.weapon_energy[g_Player.weapon] = divisor * 3;
    }
    if (row == 2) {
        engine_obj.enable_boss = 1;
        engine_obj.boss_ptr = &main_objects[0];
        main_objects[0].hp = main_objects[0].unk5D = 20;
    }
    if (row == 3)
        g_Player.unk2 = 1;
    func_80024E70();
    n = (SPRT_16*)SP_BG_PRIM_CURSOR - hud_sprites;
    assert(n == (u32)SP_SPRITE_COUNT && (DR_TPAGE*)SP_OT_CURSOR == &hud_modes[n]);
    observed[0] = n;
    observed[1] = (POLY_F4*)SP_AUX_POLY_F4_CURSOR - hud_bars;
    for (i = 0; i < 7; i++)
        observed[2 + i] = i < n ? (u16)hud_sprites[i].x0 | (u32)(u16)hud_sprites[i].y0 << 16 : 0;
    return c_test_observe(2, row, observed, hud_expected[row], 9);
}

static u32 armor_archive[32];
static POLY_FT4 armor_prims[5];
static DR_TPAGE armor_modes[5];
static P_TAG armor_tail;
static void armor_setup(void)
{
    u32 part;
    memset(armor_archive, 0, sizeof(armor_archive));
    for (part = 0; part < 4; part++) {
        u16* header = (u16*)&armor_archive[16 + part * 2];
        u8* piece = (u8*)&armor_archive[17 + part * 2];
        armor_archive[5 + part] = (16 + part * 2) * 4;
        header[0] = 1;
        header[1] = 1;
        piece[2] = part * 4;
    }
    TEST_SPRITE_FRAMES = (u8*)armor_archive;
    memset(&armor_tail, 0, sizeof(armor_tail));
    D_8013BC40[0][0][0] = &armor_tail;
    SP_DRAW_BUFFER = 0;
    SP_PRIM_CURSOR = armor_prims;
    SP_DRAW_MODE_CURSOR = armor_modes;
}
static const u32 armor_expected[2][4] = {
    { 3, 0x784300AC, 0x784300A0, 0x784300A4 },
    { 1, 0x784400A8, 0, 0 },
};
static u32 armor_parts(u32 row)
{
    u32 observed[4], i, n;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    memset(background_objects, 0, sizeof(background_objects));
    armor_setup();
    g_Player.active = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 120;
    g_Player.armor_parts = row == 0 ? 0xB : 4;
    g_Player.arm_type = row == 0 ? 0 : 2;
    func_800257BC(&g_Player);
    n = (POLY_FT4*)SP_PRIM_CURSOR - armor_prims;
    assert((DR_TPAGE*)SP_DRAW_MODE_CURSOR == &armor_modes[n]);
    observed[0] = n;
    for (i = 0; i < 3; i++)
        observed[1 + i] = i < n ? (u16)armor_prims[i].x0 | (u32)armor_prims[i].clut << 16 : 0;
    return c_test_observe(3, row, observed, armor_expected[row], 4);
}

void init_objects(void);
void func_80025CDC(void);
static void clear_draw_pools(void)
{
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)baz_objects, sizeof(baz_objects) / 4);
    c_test_zero_words((u32*)foo_objects, sizeof(foo_objects) / 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)unk_objects, sizeof(unk_objects) / 4);
    c_test_zero_words((u32*)&qux_object, sizeof(qux_object) / 4);
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
}
static u32 pool_draw(u32 row)
{
    static const u8 kinds[] = { 0, 1, 3, 3, 5, 2, 5 }, slots[] = { 0, 0, 0, 2, 0, 0, 0 };
    void (*draw)(void) = row == 6 ? func_80025CDC : init_objects;
    struct DrawInfo info;
    void *prims, *modes;
    u32 extra = row == 0;
    memset(&info, 0, sizeof(info));
    memset(&engine_obj, 0, sizeof(engine_obj));
    cur_draw_info = &info;
    clear_draw_pools();
    render_setup(kinds[row], slots[row], &render_vectors[0], 0);
    if (row == 0) {
        armor_setup();
        g_Player.armor_parts = 2;
    }
    object->on_screen = 0;
    draw();
    prims = SP_PRIM_CURSOR;
    modes = SP_DRAW_MODE_CURSOR;
    assert(SP_SPRITE_COUNT == 0 && D_8013E1E8[buffer][group][priority] == NULL);
    object->on_screen = 1;
    draw();
    assert(SP_SPRITE_COUNT == 1);
    assert((POLY_FT4*)SP_PRIM_CURSOR == (POLY_FT4*)prims + 1 + extra);
    assert((DR_TPAGE*)SP_DRAW_MODE_CURSOR == (DR_TPAGE*)modes + 1 + extra);
    assert(D_8013E1E8[buffer][group][priority] == (P_TAG*)modes);
    if (row == 3) {
        g_Player.unk2 = 1;
        draw();
        assert(SP_SPRITE_COUNT == 0 && D_8013E1E8[buffer][group][priority] == NULL);
    }
    return 1;
}
#define PSX_HUD_CASES (COUNT(filter_rows) + 4 + 2 + 7)
#else
#define PSX_HUD_CASES 0
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
#ifndef MMX4_SATURN
    { "hud_color_filter_add", NULL, NULL, COUNT(filter_rows), filter_add },
    { "hud_status", NULL, NULL, 4, hud_status },
    { "armor_overlay_parts", NULL, NULL, 2, armor_parts },
    { "pool_draw_on_screen", NULL, NULL, 7, pool_draw },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hud_color_subtraction_cases) + 1 + 16 + 24 + 36
#ifdef MMX4_PC
    + 2
    + 1
#endif
    + PSX_HUD_CASES;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
