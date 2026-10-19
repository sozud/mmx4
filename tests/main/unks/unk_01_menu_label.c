#include "test_runtime.h"
#include "main/unks/unk_01_menu_label.h"

#undef main_bss_state

static const s16 positions[] = { 16, 17, 120 };
static const u8 restricted[] = { 0, 1, 1, 0 };
static u32 highlight(u32 row)
{
    struct UnkObj obj, expected;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    struct PlayerObj player_before = g_Player;
    u32 label = row % 4, y = row / 4 % 3, selected = row / 12 % 2, mode = row / 24 % 2, character = row / 48;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    main_bss_state.character_mode = mode;
    main_bss_state.transition.selection = selected ? label + 4 : 0;
    main_before = main_bss_state;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk7 = label + 4;
    obj.bg_offset = -1;
    obj.unk42 = 0x4567;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = positions[y] * 65536 + 0x5678;
    expected = obj;
    expected.on_screen = 1;
    if (y)
        expected.unk42 = selected ? 0x7803 : 0x7800;
    if (character && !mode && restricted[label])
        expected.unk42 = 0x7804;
    menu_label_highlight(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "selection_special_row_and_character_restrictions", NULL, NULL, 96, highlight },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 96;
