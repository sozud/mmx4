#include "test_runtime.h"
#include "main/E47C.h"
#include "main/323C.h"
#include "main/1AC84.h"
#include "support/test_pad.h"
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
#ifdef VERSION_DEMO
    if (mode == 1)
        before.unk4 = 0x1E;
#endif
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
#ifdef VERSION_DEMO
static const u32 title_points_context_cases_expected[] = { 0xB50000u, 0x1B0000u, 0xE10000u, 0x1B0000u, 0xE70000u, 0x1B0000u, 0x10D0000u, 0x1B0000u, 0xBE0000u, 0x220000u, 0xD50000u, 0x210000u, 0xEA0000u, 0x1F0000u, 0x930000u, 0x6E0000u, 0xB80000u, 0x680000u, 0xBB0000u, 0x6E0000u, 0xCF0000u, 0x660000u, 0xE60000u, 0x640000u, 0xC30000u, 0x6E0000u, 0xF10000u, 0x6E0000u, 0xC60000u, 0x400000u, 0xD90000u, 0x2F0000u, 0xDE0000u, 0x450000u, 0xCB0000u, 0x560000u, 0x1010101u, 0x1010101u, 0x1010101u, 0x1010101u, 0x101u, 0x1F1F1Fu, 0x1D1F1F1Fu, 0x1E1E1D1Du, 0x1F1F1E1Eu, 0x1E1Fu, 0x800000u, 0x40u, 0xFF4F0000u, 0xFFE90000u, 0xFF250000u, 0xFFEB0000u, 0xFF210000u, 0xFFED0000u, 0xFEFD0000u, 0xFFEF0000u, 0xFF4E0000u, 0xFFEA0000u, 0xFF390000u, 0xFFED0000u, 0xFF260000u, 0xFFF10000u, 0xFF7F0000u, 0xFFA40000u, 0xFF5C0000u, 0xFFAC0000u, 0xFF5B0000u, 0xFFA80000u, 0xFF490000u, 0xFFB20000u, 0xFF340000u, 0xFFB60000u, 0xFF590000u, 0xFFAE0000u, 0xFF2D0000u, 0xFFB00000u, 0xFF5A0000u, 0xFFE00000u, 0xFF490000u, 0xFFF30000u, 0xFF460000u, 0xFFDF0000u, 0xFF5B0000u, 0xFFD00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1F1F1Fu, 0x1D1F1F1Fu, 0x1E1E1D1Du, 0x1F1F1E1Eu, 0x1E1Fu, 0x7EFFFEu, 0x40u };
#else
static const u32 title_points_context_cases_expected[] = { 0xA90000u, 0x1A0000u, 0xD40000u, 0x1A0000u, 0xDE0000u, 0x1A0000u, 0x1060000u, 0x1A0000u, 0xB00000u, 0x240000u, 0xC70000u, 0x210000u, 0xE50000u, 0x1F0000u, 0x800000u, 0x700000u, 0xA30000u, 0x6C0000u, 0xA90000u, 0x700000u, 0xC30000u, 0x690000u, 0xDB0000u, 0x690000u, 0xB60000u, 0x700000u, 0xE20000u, 0x700000u, 0xB80000u, 0x430000u, 0xCC0000u, 0x320000u, 0xD00000u, 0x430000u, 0xBE0000u, 0x510000u, 0x1010101u, 0x1010101u, 0x1010101u, 0x1010101u, 0x101u, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0Cu, 0x7F0000u, 0x0u, 0xAD0000u, 0x1E0000u, 0xDA0000u, 0x200000u, 0xE60000u, 0x220000u, 0x1100000u, 0x240000u, 0xBC0000u, 0x300000u, 0xD50000u, 0x2F0000u, 0xF50000u, 0x2F0000u, 0x920000u, 0x820000u, 0xB70000u, 0x800000u, 0xBF0000u, 0x860000u, 0xDB0000u, 0x810000u, 0xF50000u, 0x830000u, 0xD20000u, 0x8C0000u, 0x1000000u, 0x8E0000u, 0xD80000u, 0x630000u, 0xEE0000u, 0x540000u, 0xF40000u, 0x670000u, 0xE40000u, 0x770000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0C0C0Cu, 0xC0Cu, 0x7EFFFEu, 0x40u };
#endif
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
#ifdef MMX4_SATURN
    observed_values[0] = saturn_display_mode == 6;
#else
    observed_values[0] = (u32)background_objects[2].unk3;
#endif
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
#ifdef VERSION_DEMO
    extra = func_8001E850(pf_title_end) + 0x100;
#else
    extra = func_8001E850(pf_title_end, 0) + 0x100;
#endif
    actual = pf_finish(extra);
    return actual;
}
#ifndef VERSION_DEMO
static u32 pool_full_title_logo_skip(void)
{
    u32 extra, actual;
    pf_prepare();
    pf_snapshot();
    extra = func_8001E850(pf_title_skip, 0) + 0x200;
    actual = pf_finish(extra);
    return actual;
}
#endif
static const CTestCase pool_full_cases[] = {
    pool_full_title_logo_end,
#ifndef VERSION_DEMO
    pool_full_title_logo_skip,
#endif
};

static const u32 pool_full_cases_expected[] = {
    0x50100u,
#ifndef VERSION_DEMO
    0x50200u,
#endif
};
static const struct {
    u16 pressed;
    s8 active, selection, mono, next_selection, next_mono, next_mode, next_fade;
} option_inputs[] = {
    { 0, 0, 0, 0, 0, 0, 2, 0 },
    { TEST_PAD_START, 0, 0, 0, 2, 0, 3, -1 },
    { TEST_PAD_SELECTION_ALT, 0, 1, 1, 2, 1, 3, -1 },
    { TEST_PAD_CONFIRM, 0, 0, 0, 0, 0, 3, -1 },
    { TEST_PAD_CONFIRM, 0, 2, 1, 2, 1, 3, -1 },
    { TEST_PAD_CONFIRM, 0, 1, 0, 1, 1, 2, 0 },
    { TEST_PAD_CONFIRM, 0, 1, 1, 1, 0, 2, 0 },
    { TEST_PAD_LEFT, 0, 1, 0, 1, 1, 2, 0 },
    { TEST_PAD_RIGHT, 0, 1, 1, 1, 0, 2, 0 },
    { TEST_PAD_LEFT, 0, 0, 0, 0, 0, 2, 0 },
    { TEST_PAD_UP, 0, 0, 0, 2, 0, 2, 0 },
    { TEST_PAD_DOWN, 0, 2, 1, 0, 1, 2, 0 },
    { TEST_PAD_DOWN | TEST_PAD_RIGHT, 0, 0, 0, 1, 1, 2, 0 },
    { TEST_PAD_START | TEST_PAD_CONFIRM, 0, 1, 0, 2, 0, 3, -1 },
    { TEST_PAD_CONFIRM | TEST_PAD_DOWN, 0, 1, 1, 2, 1, 2, 0 },
    { TEST_PAD_START | TEST_PAD_UP, 1, 1, 0, 1, 0, 2, 1 },
    { TEST_PAD_CONFIRM, -1, 0, 1, 0, 1, 2, -1 },
};

static void check_fade(s8 active, s8 next_fade)
{
    u32 started = next_fade == -1 && active == 0;
    assert(main_bss_state.transition.active == (started ? TEST_FADE_OUT_ACTIVE : next_fade));
    assert(main_bss_state.transition.fade_amount == (started ? TEST_FADE_OUT_AMOUNT(8, 3) : 3));
}

#ifdef MMX4_SATURN
#define TEST_MONO saturn_sound_output
#define TEST_MONO_BIT 0x80
#else
#define TEST_MONO D_80171EA9
#define TEST_MONO_BIT 1
#endif

static u32 test_option_inputs(u32 row)
{
    struct GameInfo info, expected;
    struct ControllerInput input;
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    info.mode = 2;
    info.unk8 = 2;
    expected = info;
    expected.mode = option_inputs[row].next_mode;
    TEST_PAD_PRESSED = option_inputs[row].pressed;
    input = controller_input;
    main_bss_state.transition.active = option_inputs[row].active;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = option_inputs[row].selection;
    TEST_MONO = option_inputs[row].mono ? TEST_MONO_BIT : 0;
    func_8001EA90(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(&controller_input, &input, sizeof(input));
    assert(main_bss_state.transition.selection == option_inputs[row].next_selection);
    check_fade(option_inputs[row].active, option_inputs[row].next_fade);
    assert(TEST_MONO == (option_inputs[row].next_mono ? TEST_MONO_BIT : 0));
    return 1;
}

#ifdef MMX4_SATURN
#define SKIP_BACKGROUND_RESTORE(restores) \
    if (restores)                         \
        c_test_skip();
#else
#define SKIP_BACKGROUND_RESTORE(restores)
#endif

static u32 test_option_exit(u32 row)
{
    struct GameInfo info, expected;
    struct BackgroundObj backgrounds[3];
    u32 i;
    SKIP_BACKGROUND_RESTORE(row == 1 || row == 2);
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0x12, sizeof(background_objects));
    background_objects[2].x_pos.val = 0x12345678;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    expected = info;
    need_palette_load = 0x10;
    main_bss_state.transition.selection = row % 3;
    main_bss_state.transition.active = row >= 3 ? 1 : 0;
    if (row < 3) {
        expected.unk0 = row == 0 ? 0xA : 6;
        expected.mode = expected.unk2 = expected.unk3 = 0;
        if (row != 0) {
            backgrounds[2].x_pos.i.hi = 0;
            for (i = 0; i < 3; i++)
                backgrounds[i].unk4C = 1;
            backgrounds[1].unk3 = backgrounds[2].unk3 = 1;
        }
    }
    func_8001EBA0(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(need_palette_load == (row == 1 || row == 2 ? 0x11 : 0x10));
    assert(main_bss_state.transition.selection == row % 3);
    assert(main_bss_state.transition.active == (row >= 3 ? 1 : 0));
    return 1;
}

#ifndef VERSION_DEMO
static const struct {
    u16 pressed;
    s8 active, selection, next_selection, next_mode, next_fade;
} continue_inputs[] = {
    { 0, 0, 0, 0, 4, 0 },
    { TEST_PAD_CONFIRM, 0, 0, 0, 5, -1 },
    { TEST_PAD_CONFIRM, 0, 1, 1, 5, 0 },
    { TEST_PAD_CONFIRM, 0, 2, 2, 5, -1 },
    { TEST_PAD_SELECTION_ALT, 0, 0, 2, 5, -1 },
    { TEST_PAD_UP, 0, 0, 2, 4, 0 },
    { TEST_PAD_DOWN, 0, 2, 0, 4, 0 },
    { TEST_PAD_CONFIRM | TEST_PAD_SELECTION_ALT, 0, 1, 1, 5, 0 },
    { TEST_PAD_CONFIRM | TEST_PAD_DOWN, 0, 0, 0, 5, -1 },
    { TEST_PAD_CONFIRM, 1, 1, 1, 4, 1 },
    { TEST_PAD_SELECTION_ALT, -1, 0, 0, 4, -1 },
};

static u32 test_continue_inputs(u32 row)
{
    struct GameInfo info, expected;
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    info.mode = 4;
    info.unk8 = 2;
    expected = info;
    expected.mode = continue_inputs[row].next_mode;
    main_bss_state.transition.active = continue_inputs[row].active;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = continue_inputs[row].selection;
    TEST_PAD_PRESSED = continue_inputs[row].pressed;
    func_8001ED44(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    assert(main_bss_state.transition.selection == continue_inputs[row].next_selection);
    check_fade(continue_inputs[row].active, continue_inputs[row].next_fade);
    return 1;
}

static const struct {
    u16 pressed;
    s8 active, selection, next_selection, next_mode, next_fade;
} no_save_inputs[] = {
    { 0, 0, 0, 0, 6, 0 },
    { TEST_PAD_CONFIRM, 0, 0, 0, 7, 0 },
    { TEST_PAD_CONFIRM, 0, 1, 1, 7, -1 },
    { TEST_PAD_CONFIRM, 0, 2, 2, 7, -1 },
    { TEST_PAD_SELECTION_ALT, 0, 0, 2, 7, -1 },
    { TEST_PAD_DOWN, 0, 0, 0, 6, 0 },
    { TEST_PAD_CONFIRM | TEST_PAD_SELECTION_ALT, 0, 0, 0, 7, 0 },
    { TEST_PAD_CONFIRM, 1, 1, 1, 6, 1 },
    { TEST_PAD_SELECTION_ALT, -1, 0, 0, 6, -1 },
};

static u32 test_no_save_inputs(u32 row)
{
    struct GameInfo info, expected;
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    info.mode = 6;
    expected = info;
    expected.mode = no_save_inputs[row].next_mode;
    main_bss_state.transition.active = no_save_inputs[row].active;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = no_save_inputs[row].selection;
    TEST_PAD_PRESSED = no_save_inputs[row].pressed;
    func_8001EF48(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    assert(main_bss_state.transition.selection == no_save_inputs[row].next_selection);
    check_fade(no_save_inputs[row].active, no_save_inputs[row].next_fade);
    return 1;
}

static u32 test_title_return(u32 row)
{
    struct GameInfo info, expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds[3];
    u32 saved = row < 4;
    u32 selection = saved ? row % 2 + 1 : (row - 4) % 3;
    u32 busy = saved ? row >= 2 : row >= 7;
    u32 to_load = saved ? selection == 1 : selection == 0;
    u32 i;
    SKIP_BACKGROUND_RESTORE(!busy && !to_load);
    memset(&info, 0x25, sizeof(info));
    memset(&engine_obj, 0x26, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0x12, sizeof(background_objects));
    background_objects[2].x_pos.val = 0x12345678;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    expected = info;
    engine_expected = engine_obj;
    need_palette_load = 0x10;
    main_bss_state.transition.selection = selection;
    main_bss_state.transition.active = busy;
    if (!busy) {
        expected.unk0 = to_load ? 9 : 6;
        if (to_load) {
            engine_expected.unk1 = engine_expected.unk2 = engine_expected.unk3 = 0;
        } else {
            expected.mode = expected.unk2 = expected.unk3 = 0;
            backgrounds[2].x_pos.i.hi = 0;
            for (i = 0; i < 3; i++)
                backgrounds[i].unk4C = 1;
            backgrounds[1].unk3 = backgrounds[2].unk3 = 1;
        }
    }
    if (saved)
        func_8001EE08(&info);
    else
        func_8001EFF0(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(need_palette_load == (!busy && !to_load ? 0x11 : 0x10));
    assert(main_bss_state.transition.selection == selection);
    assert(main_bss_state.transition.active == busy);
    return 1;
}
#define SAVE_MENU_CASES (COUNT(no_save_inputs) + 10 + COUNT(continue_inputs))
#else
#define SAVE_MENU_CASES 0
#endif

static u16 title_palette[0x800];
static u8 title_map[3 * 256];
static u16 title_tiles[2][256];
static u32 title_attrs[2];
static u32 test_title_skip(u32 row)
{
    struct GameInfo info;
    u32 skip = row == 0;
#ifndef MMX4_SATURN
    static struct DrawInfo draw;
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
#endif
    memset(&engine_obj, 0, sizeof(engine_obj));
    TEST_PALETTE = (u8*)title_palette;
    SP_BG_TILEMAP = title_map;
    TEST_BG_TILE_PIXELS = (u8*)title_tiles;
    TEST_BG_TILE_ATTRS = (u8*)title_attrs;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&info, 0, sizeof(info));
    memset(background_objects, 0, sizeof(background_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    info.mode = 11;
    info.unk4 = 5;
    info.unkD = 1;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 3;
    D_8013E188[0] = D_8013E188[1] = D_8013E188[2] = D_8013E188[3] = 7;
    need_palette_load = 0x10;
#ifdef MMX4_SATURN
    saturn_title_skip = 0;
#endif
    TEST_PAD_PRESSED = skip ? TEST_PAD_START : 0;
    func_8001E708(&info);
    assert(info.mode == (skip ? 12 : 11) && info.unk4 == (skip ? 1 : 4));
    assert(g_FilterAmountR == (skip ? 0 : 3) && g_FilterAmountG == g_FilterAmountR && g_FilterAmountB == g_FilterAmountR);
    assert(D_8013E188[0] == (skip ? 0 : 7));
#ifndef MMX4_SATURN
    assert(need_palette_load == (skip ? 0x11 : 2));
    assert(D_8013E188[1] == D_8013E188[0] && D_8013E188[2] == D_8013E188[0] && D_8013E188[3] == D_8013E188[0]);
    assert(background_objects[0].unk3 == 0 && background_objects[1].unk3 == skip && background_objects[2].unk3 == 0);
#endif
    return info.mode;
}

#ifndef VERSION_DEMO
#ifdef MMX4_SATURN
#define TITLE_LETTERS 7
#else
#define TITLE_LETTERS 9
#endif
extern u16 D_800F21DC[];
void func_8001DE20(struct GameInfo*);
void func_8001DE54(struct GameInfo*);
void func_8001DF7C(struct GameInfo*);
void func_8001E000(struct GameInfo*);
void func_8001E3FC(struct GameInfo*);
void func_8001E458(struct GameInfo*);
void func_8001E4F0(struct GameInfo*);
void func_8001E638(struct GameInfo*);
void func_8001E6BC(struct GameInfo*);
static u16 intro_palette[0x200];
static u32 count_objects(const void* pool, u32 count, u32 stride, u8 id)
{
    u32 i, n = 0;
    for (i = 0; i < count; i++) {
        const struct ObjectHeader* object = (const struct ObjectHeader*)((const u8*)pool + i * stride);
        n += object->active != 0 && object->id == id;
    }
    return n;
}
static u32 intro_step(u32 row)
{
    static const struct {
        u8 step;
        s16 timer, glow;
        u8 active, fading;
    } rows[] = {
        { 0, 2, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 2, 1, 0, 0, 0 }, { 3, 3, 0, 0, 0 }, { 3, 0, 0, 1, 0 },
        { 3, 0, 0, 0, 0 }, { 4, 0, 0, 0, 0 }, { 5, 0, 0, 1, 0 }, { 5, 0, 0, 0, 0 }, { 6, 2, 3, 0, 0 },
        { 6, 1, 3, 0, 0 }, { 6, 1, 0xE, 0, 0 }, { 7, 2, 0, 0, 0 }, { 8, 1, 0, 0, 0 }, { 9, 2, 0, 0, 0 },
        { 9, 1, 0, 0, 0 }, { 10, 0, 0, 0, 1 }, { 10, 0, 0, 0, 0 },
    };
    static void (*const steps[])(struct GameInfo*) = {
        func_8001DE20, func_8001DE54, func_8001DF7C, func_8001E000, func_8001E130, func_8001E3FC, func_8001E458,
        func_8001E4F0, func_8001E54C, func_8001E638, func_8001E6BC,
    };
    static struct MiscObj marker;
    struct GameInfo info;
    u32 i;
    memset(&info, 0, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&D_80169498, 0, sizeof(D_80169498));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(intro_palette, 0, sizeof(intro_palette));
    memset(&marker, 0, sizeof(marker));
    TEST_PALETTE = (u8*)intro_palette;
    marker.active = rows[row].active;
    marker.state = 2;
    D_80139690 = OBJECT_HEADER(&marker);
    info.unk0 = 3;
    info.mode = 20;
    info.unk4 = rows[row].timer;
    info.unk6 = rows[row].step == 4 ? 1 : rows[row].glow;
    info.unkD = 1;
    main_bss_state.transition.active = rows[row].fading;
    D_80169498.title.settled = rows[row].step == 4;
    for (i = 0; i < 36; i++)
        D_80169498.title.coordinates[i].val = (s32)D_800F224C[i] * 65536;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    steps[rows[row].step](&info);
    switch (row) {
    case 1:
        assert(misc_objects[0].active == 1 && misc_objects[0].id == 0x1D && misc_objects[0].unk2 == 0x20);
        assert(D_80139690 == OBJECT_HEADER(&misc_objects[0]) && D_80169498.title.settled == 1);
        assert(background_objects[1].x_pos.i.hi == 0x400);
        break;
    case 2:
        assert(effect_objects[0].active == 1 && effect_objects[0].id == 2 && effect_objects[0].unk2 == 0xC);
        assert(D_80139690 == OBJECT_HEADER(&effect_objects[0]));
        break;
    case 5:
        assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0 && info.unk6 == 0x3C);
        assert(count_objects(g_QuadObjects, COUNT(g_QuadObjects), sizeof(g_QuadObjects[0]), 0xC) == TITLE_LETTERS);
        break;
    case 6:
        assert(count_objects(misc_objects, COUNT(misc_objects), sizeof(misc_objects[0]), 0x13) == 3);
        assert(misc_objects[3].id == 0x1D && misc_objects[3].unk2 == 0x21 && D_80139690 == OBJECT_HEADER(&misc_objects[3]));
        break;
    case 8:
        assert(intro_palette[0x306 / 2] == 0x8000 && info.unk6 == 0);
        break;
    case 10:
        assert(intro_palette[0x106 / 2] == D_800F21DC[3] && info.unk6 == 4);
        break;
    case 13:
        assert(effect_objects[0].id == 2 && effect_objects[0].unk2 == 0xD && info.unkD == 0);
        assert(count_objects(misc_objects, COUNT(misc_objects), sizeof(misc_objects[0]), 0x13) == 9);
        break;
    case 15:
        assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
        break;
    case 17:
        assert(info.unk0 == 4 && info.unkD == 1);
        break;
    }
    return (u8)info.mode | (u32)(u16)info.unk4 << 8;
}
static const u32 intro_steps_expected[] = {
    20 | 1 << 8, 21, 21 | 0xA << 8, 20 | 2 << 8, 20, 21, 21, 20, 21 | 0x10 << 8, 20 | 1 << 8,
    20 | 6 << 8, 21 | 1 << 8, 20 | 1 << 8, 21 | 0x258 << 8, 20 | 1 << 8, 21, 20, 0,
};
#ifdef MMX4_SATURN
#define INTRO_STEPS (COUNT(intro_steps_expected) - 1)
#else
#define INTRO_STEPS COUNT(intro_steps_expected)
#endif
#else
#define INTRO_STEPS 0
#endif

const struct CTestGroup c_test_groups[] = {
#ifndef VERSION_DEMO
    { "no_save_inputs", 0, 0, COUNT(no_save_inputs), test_no_save_inputs },
    { "title_return", 0, 0, 10, test_title_return },
#endif
    { "option_inputs", 0, 0, COUNT(option_inputs), test_option_inputs },
    { "option_exit", 0, 0, 6, test_option_exit },
#ifndef VERSION_DEMO
    { "continue_inputs", 0, 0, COUNT(continue_inputs), test_continue_inputs },
#endif
    { "title_points_context", title_points_context_cases, title_points_context_cases_expected, COUNT(title_points_context_cases), 0 },
    { "title_transition", title_transition_cases, title_transition_cases_expected, COUNT(title_transition_cases), 0 },
    { "func_8001DC7C", 0, 0, 1, test_func_8001DC7C },
    { "func_8001E54C", 0, 0, 2, test_func_8001E54C },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "title_skip", 0, 0, 2, test_title_skip },
#ifndef VERSION_DEMO
    { "title_intro_steps", NULL, intro_steps_expected, INTRO_STEPS, intro_step },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = SAVE_MENU_CASES + COUNT(option_inputs) + 6 + COUNT(title_points_context_cases) + COUNT(title_transition_cases) + 1 + 2 + COUNT(pool_full_cases) + 2 + INTRO_STEPS;
