#include "test_runtime.h"
#include "main/quads/quad_11_title_quad.h"
#include "main/object_motion.h"
void title_quad_init(struct QuadObj* arg0);
extern s16 title_quad_morph_targets[6][2];
extern s16 title_quad_shapes[][8];
extern u16 title_quad_palette[30];

static u32 morph_case(u32 observation)
{
    struct QuadObj obj, before;
    u32 i, actual;
    s32 dx, dy;
    u8 angle;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 5;
    obj.unk2 = 0;
    obj.bg_offset = -1;
    obj.unk34 = 0x2468;
    obj.unk36 = 0x10;
    obj.ext.title_quad.unk38 = 3;
    obj.ext.title_quad.unk43 = 4;
    for (i = 0; i < 4; i++) {
        dx = (s32)(i + 2) * 65536 + 0x2468;
        dy = -(s32)(i + 3) * 65536 + 0x1234;
        obj.vertices[i].x.val = title_quad_morph_targets[i][0] * 65536 + dx;
        obj.vertices[i].y.val = title_quad_morph_targets[i][1] * 65536 + dy;
        angle = angle_from_delta(dx, dy);
        obj.ext.title_quad.unk3E[i] = i == 1 ? angle ^ 0x10 : angle;
        obj.ext.title_quad.unk3A[i] = i == 0 || i == 3;
    }
    before = obj;
    title_quad_morph(&obj);
    before.on_screen = obj.on_screen;
    before.unk34 = obj.unk34;
    before.ext.title_quad = obj.ext.title_quad;
    for (i = 0; i < 4; i++)
        before.vertices[i] = obj.vertices[i];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    if (observation < 8)
        return observation & 1 ? (u32)obj.vertices[observation / 2].y.val : (u32)obj.vertices[observation / 2].x.val;
    switch (observation) {
    case 8:
        actual = obj.ext.title_quad.unk38 | ((u32)obj.ext.title_quad.unk42 << 16) | ((u32)obj.ext.title_quad.unk43 << 24);
        break;
    case 9:
        actual = obj.unk34 | ((u32)obj.on_screen << 16);
        break;
    case 10:
        actual = obj.ext.title_quad.unk3E[0] | ((u32)obj.ext.title_quad.unk3E[1] << 8) | ((u32)obj.ext.title_quad.unk3E[2] << 16) | ((u32)obj.ext.title_quad.unk3E[3] << 24);
        break;
    default:
        actual = obj.ext.title_quad.unk3A[0] | ((u32)obj.ext.title_quad.unk3A[1] << 8) | ((u32)obj.ext.title_quad.unk3A[2] << 16) | ((u32)obj.ext.title_quad.unk3A[3] << 24);
        break;
    }
    return actual;
}
static const u32 title_morph_context_cases_expected[] = { 0x170000u, 0x480000u, 0xD80000u, 0x410000u, 0xDAC2F0u, 0x3FB6CDu, 0x170000u, 0x4A0000u, 0x6000002u, 0x1C210u, 0x14141414u, 0x1000101u };

static u32 title_case(u32 mode, u32 observation)
{
    struct QuadObj quad;
    s32 dx, dy;
    u32 i, value;
    u8 hit;

    memset(&quad, 0, sizeof(quad));
    quad.state = 6;
    quad.bg_offset = -1;
    quad.x_pos.i.hi = 30;
    quad.y_pos.i.hi = 50;
    quad.ext.title_quad.unk38 = mode == 2 ? 1 : 2;
    quad.ext.title_quad.unk42 = mode == 1 ? 1 : 0;
    for (i = 0; i < 4; i++) {
        dx = (3 + i) * 65536 + 0x2468;
        dy = -(s32)(2 + i) * 65536 + 0x1234;
        quad.vertices[i].x.val = title_quad_shapes[0][i * 2] * 65536 + dx;
        quad.vertices[i].y.val = title_quad_shapes[0][i * 2 + 1] * 65536 + dy;
        hit = angle_from_delta(dx, dy);
        quad.ext.title_quad.unk3E[i] = i == 0 || i == 3 ? hit ^ 0x10 : hit;
        quad.ext.title_quad.unk3A[i] = i == 1;
    }
    func_800D7468(&quad);
    assert(quad.bg_offset == -1 && quad.unk2 == 0);
    assert(quad.x_pos.i.hi == 30 && quad.y_pos.i.hi == 50);
    if (observation < 8) {
        i = observation / 2;
        return observation & 1 ? (u32)quad.vertices[i].y.val : (u32)quad.vertices[i].x.val;
    }
    if (observation == 8) {
        return quad.ext.title_quad.unk3E[0] | ((u32)quad.ext.title_quad.unk3E[1] << 8) | ((u32)quad.ext.title_quad.unk3E[2] << 16) | ((u32)quad.ext.title_quad.unk3E[3] << 24);
    }
    value = quad.ext.title_quad.unk38 | ((u32)(u8)quad.state << 16) | ((u32)quad.ext.title_quad.unk42 << 24) | ((u32)quad.on_screen << 25);
    for (i = 0; i < 4; i++)
        value |= (u32)quad.ext.title_quad.unk3A[i] << (26 + i);
    return value;
}

#define TITLE_OBSERVATION(mode, field)                          \
    static u32 title_quad_converge_title_##mode##_##field(void) \
    {                                                           \
        return title_case(mode, field);                         \
    }
#define TITLE_MODE(mode)       \
    TITLE_OBSERVATION(mode, 0) \
    TITLE_OBSERVATION(mode, 1) \
    TITLE_OBSERVATION(mode, 2) \
    TITLE_OBSERVATION(mode, 3) \
    TITLE_OBSERVATION(mode, 4) \
    TITLE_OBSERVATION(mode, 5) \
    TITLE_OBSERVATION(mode, 6) \
    TITLE_OBSERVATION(mode, 7) \
    TITLE_OBSERVATION(mode, 8) \
    TITLE_OBSERVATION(mode, 9)
TITLE_MODE(0)
TITLE_MODE(1)
TITLE_MODE(2)
#define TITLE_ENTRY(mode, field) title_quad_converge_title_##mode##_##field,
#define TITLE_ENTRIES(mode) \
    TITLE_ENTRY(mode, 0)    \
    TITLE_ENTRY(mode, 1)    \
    TITLE_ENTRY(mode, 2)    \
    TITLE_ENTRY(mode, 3)    \
    TITLE_ENTRY(mode, 4)    \
    TITLE_ENTRY(mode, 5)    \
    TITLE_ENTRY(mode, 6)    \
    TITLE_ENTRY(mode, 7)    \
    TITLE_ENTRY(mode, 8)    \
    TITLE_ENTRY(mode, 9)
static const CTestCase title_quad_converge_cases[]
    = { TITLE_ENTRIES(0) TITLE_ENTRIES(1) TITLE_ENTRIES(2) };
static const u32 title_quad_converge_cases_expected[] = { 0x0u, 0x0u, 0x13F0000u, 0x0u, 0x1419234u, 0x76091Au, 0x0u, 0x780000u, 0x13131212u, 0x2E060001u, 0x19234u, 0xFFFF091Au, 0x1411234u, 0xFFFE891Au, 0x1419234u, 0x76091Au, 0x31234u, 0x75891Au, 0x13131212u, 0x2060001u, 0x0u, 0x0u, 0x13F0000u, 0x0u, 0x13F0000u, 0x780000u, 0x0u, 0x780000u, 0x13131212u, 0x2F040000u };
#undef TITLE_OBSERVATION
#undef TITLE_MODE
#undef TITLE_ENTRY
#undef TITLE_ENTRIES

static u32 quad_case(u32 shape, u32 mode)
{
    static const s16 morph_xy[8] = { 23, 72, 216, 65, 216, 67, 23, 74 };
    static const s16 shape_xy[8] = { 80, 192, 319, 121, 319, 240, 80, 240 };
    static const u16 timers[6] = { 6, 2, 3, 3, 1, 6 };
    static const u8 colors[6] = { 0, 7, 12, 13, 9, 14 };
    static const s32 residual[6] = { 5 * 65536 + 0x2800, 0,
        4 * 65536 + 0x2000, 4 * 65536 + 0x2000, 0,
        5 * 65536 + 0x2800 };
    const s16* xy = shape ? shape_xy : morph_xy;
    struct QuadObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = shape ? 6 : 1;
    obj.unk2 = shape ? 1 : 0;
    obj.bg_offset = -1;
    obj.on_screen = 0x71;
    obj.unk34 = 0x1234;
    obj.ext.title_quad.unk38 = timers[mode];
    obj.ext.title_quad.unk43 = colors[mode];
    obj.ext.title_quad.unk42 = mode == 3;
    for (i = 0; i < 4; i++) {
        assert((shape ? title_quad_shapes[1][2 * i] : title_quad_morph_targets[i][0]) == xy[2 * i]);
        assert((shape ? title_quad_shapes[1][2 * i + 1] : title_quad_morph_targets[i][1]) == xy[2 * i + 1]);
        obj.vertices[i].x.val = xy[2 * i] * 65536 + 6 * 65536 + 0x3000;
        obj.vertices[i].y.val = xy[2 * i + 1] * 65536;
        obj.ext.title_quad.unk3E[i] = (mode == 1 || mode == 3 || (mode == 5 && i < 2)) ? 0 : 16;
        obj.ext.title_quad.unk3A[i] = mode == 2 && i < 3;
    }
    expected = obj;
    for (i = 0; i < 4; i++) {
        u32 snap = mode == 1 || (mode == 2 && i < 3) || (mode == 5 && i < 2);
        expected.vertices[i].x.val = xy[2 * i] * 65536 + (snap ? 0 : residual[mode]);
        expected.ext.title_quad.unk3A[i] = snap;
        expected.ext.title_quad.unk3E[i] = 16;
    }
    expected.on_screen = 1;
    expected.ext.title_quad.unk42 = 0;
    expected.ext.title_quad.unk38 = timers[mode] - 1;
    if (!shape && mode != 1 && mode != 4) {
        expected.unk34 = mode == 0 ? 0x94A5 : 0x7FFF;
        expected.ext.title_quad.unk43 = mode == 0 ? 2 : mode == 2 || mode == 3 ? 14
                                                                               : 15;
        assert(title_quad_palette[2] == 0x94A5 && title_quad_palette[14] == 0x7FFF);
    }
    if (mode == 4) {
        expected.state = shape ? 4 : 2;
        if (shape)
            expected.ext.title_quad.unk42 = 1;
        else {
            expected.unk2 = 4;
            expected.ext.title_quad.unk38 = 3;
        }
    }
    if (shape)
        func_800D7468(&obj);
    else
        title_quad_morph(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.unk34 | ((u32)obj.ext.title_quad.unk38 << 16) | ((u32)(u8)obj.state << 24);
}
static const u32 title_quad_real_targets_cases_expected[] = { 0x10594A5u, 0x1011234u, 0x1027FFFu, 0x1027FFFu, 0x2031234u, 0x1057FFFu, 0x6051234u, 0x6011234u, 0x6021234u, 0x6021234u, 0x4001234u, 0x6051234u };
static u32 title_quad_real_targets_cases_row(u32 row)
{
    return quad_case(row / 6, row % 6);
}

struct title_quad_split_case {
    u32 unkA, unk2, hi, y;
    u32 expected[5];
};
static const struct title_quad_split_case title_quad_split_cases[] = {
    { 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 1, 0, 0, 0, { 2u, 0u, 0u, 0xFFF80000u, 0xFFF80000u } },
    { 1, -1, -1, -983040, { 0u, 0x80000u, 0xFFF90000u, 0xFFFF0000u, 0u } },
};
static u32 test_title_quad_split(u32 row)
{
    const struct title_quad_split_case* c = &title_quad_split_cases[row];
    u32 observed_values[5];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&game_info, 0, sizeof(game_info));
    memset(&background_objects, 0, sizeof(background_objects));
    game_info.unkA = c->unkA;
    obj.unk2 = c->unk2;
    obj.vertices[2].y.i.hi = c->hi;
    obj.vertices[1].y.i.hi = 0;
    obj.vertices[0].y.val = 0;
    obj.vertices[1].y.val = c->y;
    title_quad_split(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.vertices[0].y.val;
    observed_values[2] = (u32)obj.vertices[1].y.val;
    observed_values[3] = (u32)obj.vertices[2].y.val;
    observed_values[4] = (u32)obj.vertices[3].y.val;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static struct QuadObj title_quad;
#define TQ(kind) (memset(&title_quad, 0, sizeof(title_quad)), title_quad.active = 1, title_quad.unk2 = kind, title_quad_init(&title_quad))
static void tq_init_0(void)
{
    TQ(0);
}
static void tq_init_3(void) { TQ(3); }
static void tq_init_5(void) { TQ(5); }

static u32 title_quad_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[6];
    run();
    seen[0] = (u8)title_quad.active | (u8)title_quad.state << 8 | (u8)title_quad.unk2 << 16 | (u32)(u8)title_quad.bg_offset << 24;
    seen[1] = (u16)title_quad.vertices[0].x.i.hi | (u32)(u16)title_quad.vertices[0].y.i.hi << 16;
    seen[2] = (u16)title_quad.vertices[1].x.i.hi | (u32)(u16)title_quad.vertices[1].y.i.hi << 16;
    seen[3] = (u16)title_quad.vertices[2].x.i.hi | (u32)(u16)title_quad.vertices[2].y.i.hi << 16;
    seen[4] = (u16)title_quad.vertices[3].x.i.hi | (u32)(u16)title_quad.vertices[3].y.i.hi << 16;
    seen[5] = title_quad.unk34 | (u32)title_quad.unk36 << 16 | (u32)(u8)title_quad.ext.unk_ext.unk38 << 24;
    return c_test_observe(0, row, seen, expected, 6);
}

static void (*const title_quad_init_states_cases[])(void) = {
    tq_init_0,
    tq_init_3,
    tq_init_5,
};
static const u32 title_quad_init_states_expected[] = { 0xFF000381u, 0u, 0x13Fu, 0x78013Fu, 0x780000u, 0x14108421u, 0xFF030381u, 0xBF0050u, 0x780000u, 0x790004u, 0xC00054u, 0x14108421u, 0xFF050381u, 0x780000u, 0x78014Au, 0xC00050u, 0xC00050u, 0x14108421u };

static u32 test_title_quad_init_states(u32 row)
{
    return title_quad_run(title_quad_init_states_cases[row], row, &title_quad_init_states_expected[row * 6]);
}

const struct CTestGroup c_test_groups[] = {
    { "title_quad_init_states", 0, 0, COUNT(title_quad_init_states_cases), test_title_quad_init_states },
    { "title_morph_context", NULL, title_morph_context_cases_expected, COUNT(title_morph_context_cases_expected), morph_case },
    { "title_quad_converge", title_quad_converge_cases, title_quad_converge_cases_expected, COUNT(title_quad_converge_cases), 0 },
    { "title_quad_real_targets", NULL, title_quad_real_targets_cases_expected, COUNT(title_quad_real_targets_cases_expected), title_quad_real_targets_cases_row },
    { "title_quad_split", 0, 0, 3, test_title_quad_split },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_quad_init_states_cases) + COUNT(title_morph_context_cases_expected) + COUNT(title_quad_converge_cases) + COUNT(title_quad_real_targets_cases_expected) + 3;
