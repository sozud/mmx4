#include "test_runtime.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/menu.h"
#include "support/platform_fixture.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#define TEST_OPTION_PALETTE(psx) ((psx) == 0x7803 ? SATURN_OPTION_SELECTED_PALETTE : (psx) == 0x7804 ? SATURN_OPTION_LOCKED_PALETTE \
        : (psx) == 0x7802 ? SATURN_OPTION_TITLE_PALETTE : (psx) == 0x7800 ? SATURN_OPTION_PALETTE : (psx))
#else
#define TEST_OPTION_PALETTE(psx) (psx)
#endif

struct func_800CDF4C_case {
    u32 timer, unk2, pressed, unk0, selection;
    u32 expected[2];
};
static const struct func_800CDF4C_case func_800CDF4C_cases[] = {
    { 255, 3, 0, 0, 255, { 3u, 0x7800u } },
    { 0, 0, 2048, 10, 0, { 0xFFFFFFFFu, 0u } },
    { 0, 0, 2048, 8, 0, { 0xFFFFFFFFu, 0u } },
    { 0, 0, 2048, 0, 0, { 0u, 0x7803u } },
    { 255, 0, 0, 0, 255, { 0u, 0x7800u } },
};
static u32 test_func_800CDF4C(u32 row)
{
    const struct func_800CDF4C_case* c = &func_800CDF4C_cases[row];
    u32 observed_values[2];
    u32 expected[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800F1D90.save, 0, sizeof(D_800F1D90.save));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.misc_31.timer = c->timer;
    obj.unk2 = c->unk2;
    TEST_PAD_PRESSED = c->pressed ? TEST_PAD_START : 0;
    game_info.unk0 = c->unk0;
    main_bss_state.transition.selection = c->selection;
    func_800CDF4C(&obj);
    observed_values[0] = (u32)obj.unk2;
    observed_values[1] = (u32)obj.unk42;
    expected[0] = c->expected[0];
    expected[1] = TEST_OPTION_PALETTE(c->expected[1]);
    return c_test_observe(0, row, observed_values, expected, 2);
}
#undef controller_input
#undef main_bss_state

#ifdef MMX4_SATURN
#include "saturn/menu.h"
#define TOGGLE_TEXTURE SATURN_OPTION_WINDOW_TEXTURE
#define TOGGLE_FRAMES(offset) ((u8*)SATURN_OPTION_WINDOW_FRAMES)
#define TOGGLE_VALUE saturn_sound_output
#define TOGGLE_FRAME(on) ((on) ? 0x57 : 0x56)
#else
#define TOGGLE_TEXTURE 0x1F00
#define TOGGLE_FRAMES(offset) (WINDOW_ARCHIVE_DATA + (offset))
#define TOGGLE_VALUE D_80171EA9
#define TOGGLE_FRAME(on) ((on) ? 0x56 : 0x57)
#endif
static const u8 labels[] = { 2, 3, 0x56, 0x57 };
static const s16 positions[] = { 16, 17, 120, 272 };
static u32 toggle_init(u32 row)
{
    struct MiscObj obj, expected;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 label = row % 4, y = row / 4 % 4, saved = row / 16 % 2, animation = row / 32, directory, offset = saved ? 0x80 : 0x40;
    u8 character;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
#ifndef MMX4_SATURN
    memcpy(&directory, WINDOW_ARCHIVE_DATA, 4);
    memcpy(WINDOW_ARCHIVE_DATA, &offset, 4);
#else
    (void)directory;
#endif
    character = D_800F1D90.save.character;
    D_800F1D90.save.character = saved ? 0xFF : 0;
    TOGGLE_VALUE = animation;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 31;
    obj.unk2 = labels[label];
    obj.on_screen = 7;
    obj.bg_offset = 2;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 0x12345678;
    obj.y_pos.val = positions[y] * 65536 + 0x5678;
    obj.animation_step.packed = C_TEST_STEP(0x12345678);
    obj.ext.misc_31.animation = 0x55;
    expected = obj;
    expected.unk40 = TOGGLE_TEXTURE;
    expected.bg_offset = -1;
    expected.unk3C = TOGGLE_FRAMES(offset);
    expected.unk15 = 0;
    expected.unk42 = TEST_OPTION_PALETTE(y == 0 ? 0x7802 : label == 1 && saved ? 0x7804
                                                                                : 0x7800);
    expected.x_pos.i.hi = 160;
    expected.unk16 = VISUAL_SATURN_LAYER(16);
    expected.on_screen = y != 3;
    if (label >= 2) {
        expected.state = 2;
        expected.ext.misc_31.animation = animation;
        expected.animation_step.fields.frame_index = TOGGLE_FRAME(animation);
    } else {
        expected.state = 1;
        expected.animation_step.fields.frame_index = labels[label];
    }
    func_800CDE44(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(D_800F1D90.save.character == (saved ? 0xFF : 0) && TOGGLE_VALUE == animation);
    D_800F1D90.save.character = character;
#ifndef MMX4_SATURN
    assert(*(u32*)WINDOW_ARCHIVE_DATA == offset);
    memcpy(WINDOW_ARCHIVE_DATA, &directory, 4);
#endif
    return 1;
}

static u32 header_row(u32 row)
{
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.y_pos.i.hi = 0x10;
    obj.unk2 = 3;
    obj.unk42 = 0x1234;
    func_800CDF4C(&obj);
    return obj.unk42 | (u32)(u8)obj.unk2 << 16;
}
static const u32 header_row_expected[] = { 0x31234u };
const struct CTestGroup c_test_groups[] = {
    { "func_800CDF4C", 0, 0, 5, test_func_800CDF4C },
    { "option_toggle_header_row", NULL, header_row_expected, 1, header_row },
    { "normal_restricted_and_toggle_labels_with_header_row", NULL, NULL, 64, toggle_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 5 + 1 + 64;
