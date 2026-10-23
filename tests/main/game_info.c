#include "test_runtime.h"
#include "main/game_info.h"
#include "main/objects.h"
#include "main/1AC84.h"

static const u32 func_8001D698_expected[] = { 0u, 0u, 0u, 0u, 0u, 1u };
static u32 test_func_8001D698(u32 row)
{
    u32 observed_values[6];
    struct GameInfo obj;
    memset(&obj, 0, sizeof(obj));
    obj.unkC = 3;
    func_8001D698(&obj);
    observed_values[0] = (u32)obj.mode;
    observed_values[1] = (u32)obj.unk0;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.unk3;
    observed_values[4] = (u32)obj.unkC;
    observed_values[5] = (u32)obj.unkD;
    return c_test_observe(0, row, observed_values, func_8001D698_expected, 6);
}

static const struct {
    u16 pressed;
    s8 active, cursor, next_cursor, next_mode, next_fade;
} game_over_inputs[] = {
    { 0, 0, 0, 0, 4, 0 },
    { PADLup, 0, 0, 2, 4, 0 },
    { PADLup, 0, 2, 1, 4, 0 },
    { PADLdown, 0, 2, 0, 4, 0 },
    { PADLdown, 0, 0, 1, 4, 0 },
    { PAD_CONFIRM, 0, 1, 1, 5, -1 },
    { PADstart, 0, 2, 2, 5, -1 },
    { PADLup | PAD_CONFIRM, 0, 0, 2, 5, -1 },
    { PADLup | PADLdown, 0, 0, 0, 4, 0 },
    { PADLdown | PADstart, 0, 1, 2, 5, -1 },
    { PADLup | PADLdown | PAD_CONFIRM, 1, 2, 2, 4, 1 },
    { PADstart, -1, 0, 0, 4, -1 },
};

static u32 test_game_over_inputs(u32 row)
{
    struct GameInfo info, expected;
    struct ControllerInput input;
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    info.mode = 4;
    info.unk2 = game_over_inputs[row].cursor;
    expected = info;
    expected.mode = game_over_inputs[row].next_mode;
    expected.unk2 = game_over_inputs[row].next_cursor;
    controller_input.pressed = game_over_inputs[row].pressed;
    input = controller_input;
    main_bss_state.transition.active = game_over_inputs[row].active;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = 2;
    func_8001D8DC(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(&controller_input, &input, sizeof(input));
    assert(main_bss_state.transition.active == game_over_inputs[row].next_fade);
    assert(main_bss_state.transition.fade_amount == (info.mode == 5 ? 8 : 3));
    assert(main_bss_state.transition.selection == 2);
    return 1;
}

static u32 test_game_over_route(u32 row)
{
    struct GameInfo info, expected;
    memset(&info, 0x25, sizeof(info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    info.unk2 = row % 2 + 1;
    expected = info;
    main_bss_state.transition.active = row >= 2 ? 1 : 0;
    if (row < 2) {
        expected.unk0 = row == 0 ? 7 : 8;
        expected.mode = expected.unk2 = expected.unk3 = 0;
    }
    func_8001D9D0(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    return 1;
}

static struct DrawInfo fade_drawing;
static u8 fade_tilemap[12];
static u16 fade_tile_pixels[256];

static u32 test_fade_route(u32 row)
{
    struct GameInfo info, expected;
    u32 scene = row % 4;
    s8 fade = row < 4 ? 0 : row < 8 ? 1
                                    : -1;
    if (fade != 0)
        reset_objects();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&fade_drawing, 0, sizeof(fade_drawing));
    memset(fade_tilemap, 0, sizeof(fade_tilemap));
    memset(fade_tile_pixels, 0, sizeof(fade_tile_pixels));
    memset(&info, 0x25, sizeof(info));
    SP_DRAW_BUFFER = 0;
    SP_BG_TILEMAP = fade_tilemap;
    TEST_BG_TILE_PIXELS = (u8*)fade_tile_pixels;
    layout_width = layout_height = 2;
    layout_size = 4;
    cur_draw_info = &fade_drawing;
    engine_obj.stage = 9;
    info.unkE = scene;
    expected = info;
    if (fade == 0)
        expected.unk0 = scene == 1 ? 6 : 1;
    main_bss_state.transition.active = fade;
    func_8001D6DC(&info);
    c_test_same_words(&info, &expected, sizeof(expected));
    assert(main_bss_state.transition.active == fade);
    assert(engine_obj.stage == 9);
    return 1;
}

#ifdef MMX4_PC
#include <psyz/spu.h>
#include <libspu.h>
#include <libsnd.h>
extern s32 D_80141BD4, D_80139564, D_80139530;
extern s16 D_8013955C;
static struct MiscObj expected_misc[64];
static struct DrawInfo draw;
static u8 map[3 * 40 * 34];
static u16 pixels[256], expected_tiles[3][32][32];
static const u8 game_over_parts[14] = { 0x12, 0x13, 0, 11, 12, 7, 17, 9, 2, 13, 14, 15, 16, 5 };
static const s8 active_values[] = { 0, 1, -1 };
#define POOLS(X)       \
    X(g_Player);       \
    X(g_Entity);       \
    X(foo_objects);    \
    X(baz_objects);    \
    X(weapon_objects); \
    X(main_objects);   \
    X(shot_objects);   \
    X(visual_objects); \
    X(effect_objects); \
    X(item_objects);   \
    X(unk_objects);    \
    X(layer_objects);  \
    X(g_QuadObjects);  \
    X(qux_object);     \
    X(bar_object);     \
    X(abc_object)
static void fill(void* data, u32 size, u32 word)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)data)[i] = word;
}
static void check_value(const void* data, u32 size, u32 word)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        assert(((const u32*)data)[i] == word);
}
#define PRIME(pool) fill(&(pool), sizeof(pool), prime)
#define CHECK(pool) check_value(&(pool), sizeof(pool), retained)
static u32 reset_lifecycle(u32 row)
{
    struct GameInfo info, info_expected;
    struct EngineObj engine_expected;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    SpuVoiceAttr voices;
    s32 key_before[24];
    u32 kind = row % 3, active = row / 3 % 3, xa = row / 9, reset = kind == 2 || active == 0;
    u32 prime = reset ? 0x25252525 : 0, retained = 0, i, j, k;
    s16 left, right;
    Psyz_SpuInit();
    POOLS(PRIME);
    PRIME(misc_objects);
    memset(expected_misc, 0, sizeof(expected_misc));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&draw, 0, sizeof(draw));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++)
        background_objects[i].unk4E = 31;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    memset(map, 0, sizeof(map));
    for (i = 0; i < 256; i++)
        pixels[i] = 0x2222;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++) {
                D_801441C8[i][j][k] = 0x3333;
                expected_tiles[i][j][k] = kind == 1 && active != 0 && (j == 16 && k <= 20 || k == 21 && j <= 16) ? 0x2222 : 0x3333;
            }
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    layout_width = 40;
    layout_size = 40 * 34;
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &draw;
    engine_obj.state = 1;
    engine_obj.unk1 = 4;
    engine_obj.stage = 5;
    engine_expected = engine_obj;
    memset(&info, 0x25, sizeof(info));
    info.unk0 = kind == 2 ? 6 : 2;
    info.mode = 3;
    info_expected = info;
    main_bss_state.transition.active = active_values[active];
    main_bss_state.transition.suspended = 1;
    main_bss_state.transition.fade_amount = 3;
    main_expected = main_bss_state;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 17;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 3;
    need_palette_load = 0x20;
    for (i = 0; i < 4; i++) {
        D_8013E188[i] = 7;
        D_80173C6C[i] = 18 + i;
    }
    memset(&voices, 0, sizeof(voices));
    voices.voice = 0xFFFFFF;
    voices.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    voices.volume.left = 1234;
    voices.volume.right = 2345;
    SpuSetVoiceAttr(&voices);
    for (i = 0; i < 24; i++)
        D_80139234[i] = 25;
    SpuSetKey(SPU_ON, 0xFFFFFF);
    for (i = 0; i < 24; i++) {
        key_before[i] = SpuGetKeyStatus(1u << i);
        assert(key_before[i] != SPU_OFF);
    }
    D_80141BD4 = xa ? 2 : 0;
    D_80139564 = 2;
    D_8013955C = 0;
    D_80139530 = 3;
    D_80139568 = 1;
    D_80173C84 = 1;
    if (kind == 0 && reset) {
        info_expected.unkD = 1;
        info_expected.mode = 0;
        info_expected.unk0++;
    }
    if (kind == 1 && reset) {
        info_expected.unkD = 1;
        info_expected.unk0 = 3;
        info_expected.mode = 0;
        main_expected.transition.suspended = 0;
        memset(&engine_expected, 0, sizeof(engine_expected));
    }
    if (kind != 2 && reset) {
        memset(backgrounds_expected, 0, sizeof(backgrounds_expected));
        for (i = 0; i < 3; i++)
            backgrounds_expected[i].unk2 = i;
    }
    if (kind == 2) {
        main_expected.transition.suspended = 0;
        if (active == 0) {
            main_expected.transition.active = 1;
            main_expected.transition.fade_amount = 8;
        }
        info_expected.mode++;
        for (i = 0; i < 14; i++) {
            expected_misc[i].active = 1;
            expected_misc[i].id = 19;
            expected_misc[i].unk2 = game_over_parts[i];
        }
    }
    if (kind == 0)
        func_8001D1A4(&info);
    else if (kind == 1)
        func_8001D514(&info);
    else
        func_8001D7D0(&info);
    POOLS(CHECK);
    c_test_same_words(misc_objects, expected_misc, sizeof(expected_misc));
    c_test_same_words(&info, &info_expected, sizeof(info));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(D_801441C8, expected_tiles, sizeof(expected_tiles));
    assert(g_FilterAmountR == (reset ? 0 : 17) && g_FilterAmountG == (reset ? 0 : 17) && g_FilterAmountB == (reset ? 0 : 17));
    assert(g_FilterModeR == (reset ? 0 : 3) && g_FilterModeG == (reset ? 0 : 3) && g_FilterModeB == (reset ? 0 : 3));
    assert(need_palette_load == (kind == 2 ? 0x21 : 0x20));
    for (i = 0; i < 4; i++) {
        assert(D_8013E188[i] == (reset ? 0 : 7));
        assert(D_80173C6C[i] == (reset && kind != 2 ? i + 3 : i + 18));
    }
    for (i = 0; i < 24; i++) {
        SpuGetVoiceVolume(i, &left, &right);
        assert(left == 1234 && right == 2345);
        assert(SpuGetKeyStatus(1u << i) == key_before[i]);
    }
    SsSeqCalledTbyT();
    for (i = 0; i < 24; i++) {
        SpuGetVoiceVolume(i, &left, &right);
        assert(left == (reset ? 0 : 1234) && right == (reset ? 0 : 2345));
        assert(D_80139234[i] == 25);
    }
    assert(Psyz_SpuRead(0x18C) == (reset ? 0xFFFF : 0));
    assert(Psyz_SpuRead(0x18E) == (reset ? 0xFF : 0));
    assert(D_80139564 == (reset && xa ? 0 : 2) && D_80139530 == (reset && xa ? 0 : 3));
    assert(D_80139568 == (reset && xa ? 0 : 1) && D_80173C84 == (reset && xa ? 0 : 1));
    for (i = 0; i < sizeof(map); i++)
        assert(map[i] == 0);
    for (i = 0; i < 256; i++)
        assert(pixels[i] == 0x2222);
    return 1;
}
#endif
#ifdef MMX4_PC
#else
#endif

const struct CTestGroup c_test_groups[] = {
    { "game_over_inputs", 0, 0, COUNT(game_over_inputs), test_game_over_inputs },
    { "game_over_route", 0, 0, 4, test_game_over_route },
    { "func_8001D698", 0, 0, 1, test_func_8001D698 },
    { "fade_route", 0, 0, 12, test_fade_route },
#ifdef MMX4_PC
    { "game_reset_lifecycle", NULL, NULL, 18, reset_lifecycle },
#else
    { "native_reset_budget", NULL, NULL, 0, NULL },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(game_over_inputs) + 4 + 1 + 12
#ifdef MMX4_PC
    + 18
#else
    + 0
#endif
    ;
