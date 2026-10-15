#include "test_runtime.h"

struct menu_label_highlight_case {
    u32 unk7, character_mode, cur_character;
    u32 expected[1];
};
static const struct menu_label_highlight_case menu_label_highlight_cases[] = {
    { 0, 255, 0, { 0u } },
    { 7, 0, -1, { 0u } },
    { 6, 0, -1, { 0x7804u } },
    { 0, 0, -1, { 0u } },
};
static u32 test_menu_label_highlight(u32 row)
{
    const struct menu_label_highlight_case* c = &menu_label_highlight_cases[row];
    u32 observed_values[1];
    struct UnkObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.y_pos.i.hi = 16;
    obj.unk7 = c->unk7;
    main_bss_state.character_mode = c->character_mode;
    engine_obj.cur_character = c->cur_character;
    menu_label_highlight(&obj);
    observed_values[0] = (u32)obj.unk42;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "menu_label_highlight", 0, 0, 4, test_menu_label_highlight },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
