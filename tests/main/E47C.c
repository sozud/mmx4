#include "test_runtime.h"
extern s16 D_800F224C[36];
extern union TitleScratch D_80169498;
void func_8001E954(struct GameInfo* self);

static u32 title_case(u32 mode, u32 observation)
{
    struct GameInfo game, before;
    union TitleScratch title_points_context_title_before;
    struct MiscObj pool_before[64];
    s16 targets_before[36];
    u32 i, j, actual = 0;
    memset(&game, 0, sizeof(game));
    memset(&D_80169498, 0, sizeof(D_80169498));
    memset(misc_objects, 0, sizeof(misc_objects));
    game.mode = 126;
    game.unk6 = mode == 1 ? 1 : -1;
    game.unk4 = 0x2468;
    D_80169498.title.settled = mode == 2 ? 1 : 0;
    for (i = 0; i < 18; i++) {
        D_80169498.title.coordinates[i * 2].val = (s32)D_800F224C[i * 2] * 65536 + (i + 2) * 65536;
        D_80169498.title.coordinates[i * 2 + 1].val = (s32)D_800F224C[i * 2 + 1] * 65536 + (i + 2) * 65536;
        D_80169498.title.unk90[i] = mode == 1 || i == 0;
        D_80169498.title.unkA2[i] = i == 1 ? 0x10 : 0;
    }
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x35;
        misc_objects[i].unk2 = 0x27;
    }
    D_80139690 = OBJECT_HEADER(&misc_objects[63]);
    before = game;
    title_points_context_title_before = D_80169498;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    memcpy(targets_before, D_800F224C, sizeof(targets_before));
    func_8001E130(&game);
    before.mode = game.mode;
    before.unk6 = game.unk6;
    title_points_context_title_before.title = D_80169498.title;
    for (i = 0; i < sizeof(game) / 4; i++)
        assert(((u32*)&game)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(D_80169498) / 4; i++)
        assert(((u32*)&D_80169498)[i] == ((u32*)&title_points_context_title_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < COUNT(targets_before); i++)
        assert(D_800F224C[i] == targets_before[i]);
    assert(D_80139690 == NULL || D_80139690 == OBJECT_HEADER(&misc_objects[63]));
    if (observation < 36)
        return D_80169498.title.coordinates[observation].val;
    if (observation < 46) {
        u32 group = (observation - 36) % 5, angles = observation >= 41;
        for (j = 0; j < 4 && group * 4 + j < 18; j++)
            actual |= (u32)(angles ? D_80169498.title.unkA2[group * 4 + j] : D_80169498.title.unk90[group * 4 + j]) << (j * 8);
    } else if (observation == 46)
        actual = (u16)game.unk6 | ((u32)(u8)game.mode << 16) | ((u32)D_80169498.title.settled << 24);
    else
        actual = D_80139690 == NULL ? 0 : 64;
    return actual;
}
#define TITLE_CASE(m, n)                                  \
    static u32 title_points_context_title_##m##_##n(void) \
    {                                                     \
        return title_case(m, n);                          \
    }
#define TITLE_MODE(m) TITLE_CASE(m, 0) TITLE_CASE(m, 1) TITLE_CASE(m, 2) TITLE_CASE(m, 3) TITLE_CASE(m, 4) TITLE_CASE(m, 5) TITLE_CASE(m, 6) TITLE_CASE(m, 7) TITLE_CASE(m, 8) TITLE_CASE(m, 9) TITLE_CASE(m, 10) TITLE_CASE(m, 11) TITLE_CASE(m, 12) TITLE_CASE(m, 13) TITLE_CASE(m, 14) TITLE_CASE(m, 15) TITLE_CASE(m, 16) TITLE_CASE(m, 17) TITLE_CASE(m, 18) TITLE_CASE(m, 19) TITLE_CASE(m, 20) TITLE_CASE(m, 21) TITLE_CASE(m, 22) TITLE_CASE(m, 23) TITLE_CASE(m, 24) TITLE_CASE(m, 25) TITLE_CASE(m, 26) TITLE_CASE(m, 27) TITLE_CASE(m, 28) TITLE_CASE(m, 29) TITLE_CASE(m, 30) TITLE_CASE(m, 31) TITLE_CASE(m, 32) TITLE_CASE(m, 33) TITLE_CASE(m, 34) TITLE_CASE(m, 35) TITLE_CASE(m, 36) TITLE_CASE(m, 37) TITLE_CASE(m, 38) TITLE_CASE(m, 39) TITLE_CASE(m, 40) TITLE_CASE(m, 41) TITLE_CASE(m, 42) TITLE_CASE(m, 43) TITLE_CASE(m, 44) TITLE_CASE(m, 45) TITLE_CASE(m, 46) TITLE_CASE(m, 47)
TITLE_MODE(1)
TITLE_MODE(2)
#define TITLE_ENTRY(m, n) title_points_context_title_##m##_##n,
#define TITLE_ENTRIES(m) TITLE_ENTRY(m, 0) TITLE_ENTRY(m, 1) TITLE_ENTRY(m, 2) TITLE_ENTRY(m, 3) TITLE_ENTRY(m, 4) TITLE_ENTRY(m, 5) TITLE_ENTRY(m, 6) TITLE_ENTRY(m, 7) TITLE_ENTRY(m, 8) TITLE_ENTRY(m, 9) TITLE_ENTRY(m, 10) TITLE_ENTRY(m, 11) TITLE_ENTRY(m, 12) TITLE_ENTRY(m, 13) TITLE_ENTRY(m, 14) TITLE_ENTRY(m, 15) TITLE_ENTRY(m, 16) TITLE_ENTRY(m, 17) TITLE_ENTRY(m, 18) TITLE_ENTRY(m, 19) TITLE_ENTRY(m, 20) TITLE_ENTRY(m, 21) TITLE_ENTRY(m, 22) TITLE_ENTRY(m, 23) TITLE_ENTRY(m, 24) TITLE_ENTRY(m, 25) TITLE_ENTRY(m, 26) TITLE_ENTRY(m, 27) TITLE_ENTRY(m, 28) TITLE_ENTRY(m, 29) TITLE_ENTRY(m, 30) TITLE_ENTRY(m, 31) TITLE_ENTRY(m, 32) TITLE_ENTRY(m, 33) TITLE_ENTRY(m, 34) TITLE_ENTRY(m, 35) TITLE_ENTRY(m, 36) TITLE_ENTRY(m, 37) TITLE_ENTRY(m, 38) TITLE_ENTRY(m, 39) TITLE_ENTRY(m, 40) TITLE_ENTRY(m, 41) TITLE_ENTRY(m, 42) TITLE_ENTRY(m, 43) TITLE_ENTRY(m, 44) TITLE_ENTRY(m, 45) TITLE_ENTRY(m, 46) TITLE_ENTRY(m, 47)
static const CTestCase title_points_context_cases[]
    = { TITLE_ENTRIES(1) TITLE_ENTRIES(2) };
static const u32 title_points_context_cases_expected[] = { 0xA90000u, 0x1A0000u, 0xD40000u, 0x1A0000u, 0xDE0000u, 0x1A0000u, 0x1060000u, 0x1A0000u, 0xB00000u, 0x240000u, 0xC70000u, 0x210000u, 0xE50000u, 0x1F0000u, 0x800000u, 0x700000u, 0xA30000u, 0x6C0000u, 0xA90000u, 0x700000u, 0xC30000u, 0x690000u, 0xDB0000u, 0x690000u, 0xB60000u, 0x700000u, 0xE20000u, 0x700000u, 0xB80000u, 0x430000u, 0xCC0000u, 0x320000u, 0xD00000u, 0x430000u, 0xBE0000u, 0x510000u, 0x1010101u, 0x1010101u, 0x1010101u, 0x1010101u, 0x101u, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0Cu, 0x7F0000u, 0x0u, 0xAD0000u, 0x1E0000u, 0xDA0000u, 0x200000u, 0xE60000u, 0x220000u, 0x1100000u, 0x240000u, 0xBC0000u, 0x300000u, 0xD50000u, 0x2F0000u, 0xF50000u, 0x2F0000u, 0x920000u, 0x820000u, 0xB70000u, 0x800000u, 0xBF0000u, 0x860000u, 0xDB0000u, 0x810000u, 0xF50000u, 0x830000u, 0xD20000u, 0x8C0000u, 0x1000000u, 0x8E0000u, 0xD80000u, 0x630000u, 0xEE0000u, 0x540000u, 0xF40000u, 0x670000u, 0xE40000u, 0x770000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0Cu, 0x7EFFFEu, 0x40u };
#undef TITLE_CASE
#undef TITLE_MODE
#undef TITLE_ENTRY
#undef TITLE_ENTRIES

#define TRANSITION_CASE(name, active_value) \
    static u32 name(void)                   \
    {                                       \
        struct GameInfo obj;                \
        u32 actual;                         \
        memset(&obj, 0, sizeof(obj));       \
        obj.mode = 16;                      \
        set_active(active_value);           \
        func_8001E954(&obj);                \
        actual = (u32)obj.mode;             \
        return actual;                      \
    }
static void set_active(s8 active)
{
    main_bss_state.transition.active = active;
}
TRANSITION_CASE(finished, 0)
TRANSITION_CASE(waiting, 1)

static const CTestCase title_transition_cases[] = {
    finished,
    waiting,
};
static const u32 title_transition_cases_expected[] = { 0x11u, 0x10u };
#undef TRANSITION_CASE

static u32 normalize_return(struct QuadObj* value)
{
    u32 i;
    if (value == NULL)
        return 0;
    for (i = 0; i < 32; ++i)
        if (value == &g_QuadObjects[i])
            return i + 1;
    assert(0);
    return ~0u;
}
static const u32 func_8001DC7C_expected[] = { 0u, 1u, 0u, 0u };
static u32 test_func_8001DC7C(u32 row)
{
    u32 observed_values[4];
    u8 pool_0_full;
    struct QuadObj* return_value;
    u32 normalized_return;
    s8 arg0;
    s8 arg1;
    memset(&g_QuadObjects, 0, sizeof(g_QuadObjects));
    pool_0_full = 255;
    arg0 = 0;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            g_QuadObjects[slot].active = pool_0_full ? 1 : 0;
    }
    return_value = func_8001DC7C(arg0, arg1);
    normalized_return = normalize_return(return_value);
    observed_values[0] = (u32)normalized_return;
    observed_values[1] = (u32)g_QuadObjects[0].active;
    observed_values[2] = (u32)g_QuadObjects[0].id;
    observed_values[3] = (u32)g_QuadObjects[0].unk2;
    return c_test_observe(0, row, observed_values, func_8001DC7C_expected, 4);
}

static const u32 inputs_0[2][4] = {
    { 0, 0, 0, 0 },
    { 1, 255, 255, 0 },
};
struct func_8001E54C_case {
    u32 expected[10];
};
static const struct func_8001E54C_case func_8001E54C_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { { 1u, 1u, 0u, 0u, 1u, 0u, 0u, 1u, 0x258u, 0u } },
};
static u32 test_func_8001E54C(u32 row)
{
    const struct func_8001E54C_case* c = &func_8001E54C_cases[row];
    u32 observed_values[10];
    struct GameInfo obj;
    u8 pool_0_full;
    u8 pool_1_full;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    obj.unk4 = inputs_0[row][0];
    pool_0_full = inputs_0[row][1];
    pool_1_full = inputs_0[row][2];
    obj.mode = inputs_0[row][3];
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_1_full ? 1 : 0;
    }
    func_8001E54C(&obj);
    observed_values[0] = (u32)background_objects[2].unk3;
    observed_values[1] = (u32)effect_objects[0].active;
    observed_values[2] = (u32)effect_objects[0].id;
    observed_values[3] = (u32)effect_objects[0].unk2;
    observed_values[4] = (u32)misc_objects[0].active;
    observed_values[5] = (u32)misc_objects[0].id;
    observed_values[6] = (u32)misc_objects[0].unk2;
    observed_values[7] = (u32)obj.mode;
    observed_values[8] = (u32)obj.unk4;
    observed_values[9] = (u32)obj.unkD;
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

#include "support/pool_full.h"
static u32 pool_full_title_logo_end(void)
{
    u32 extra, actual;
    pf_prepare();
    pf_snapshot();
    extra = func_8001E850(pf_title_end, 0) + 0x100;
    actual = pf_finish(extra);
    return actual;
}
static u32 pool_full_title_logo_skip(void)
{
    u32 extra, actual;
    pf_prepare();
    pf_snapshot();
    extra = func_8001E850(pf_title_skip, 0) + 0x200;
    actual = pf_finish(extra);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_title_logo_end,
    pool_full_title_logo_skip,
};

static const u32 pool_full_cases_expected[] = { 0x50100u, 0x50200u };
const struct CTestGroup c_test_groups[] = {
    { "title_points_context", title_points_context_cases, title_points_context_cases_expected, COUNT(title_points_context_cases), 0 },
    { "title_transition", title_transition_cases, title_transition_cases_expected, COUNT(title_transition_cases), 0 },
    { "func_8001DC7C", 0, 0, 1, test_func_8001DC7C },
    { "func_8001E54C", 0, 0, 2, test_func_8001E54C },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(title_points_context_cases) + COUNT(title_transition_cases) + 1 + 2 + COUNT(pool_full_cases);
