#include "test_runtime.h"
#include "main/misc/misc_32_option_sprite.h"
#include "main/misc/misc_31_option_toggle.h"
extern union AnimationStep option_toggle_anim_0[36];

static u32 option_case(u32 mode, u32 observation)
{
    struct MiscObj obj, before;
    struct ControllerInput input_before;
    struct MainBssState main_before;
    struct GameInfo game_before;
    u8 rows[8] = { 0xA5, 0xA5, 40, 0xA5, 80, 0xA5, 120, 0xA5 };
    u32 i, actual, cursor = ~0u;
    memset(&obj, 0, sizeof(obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&game_info, 0, sizeof(game_info));
    obj.active = 0x41;
    obj.id = 32;
    obj.state = 1;
    obj.unk2 = 0;
    obj.unk5 = 0x35;
    obj.unk6 = 0x27;
    obj.bg_offset = -1;
    obj.x_pos.val = 80 * 65536 + 0x1357;
    obj.y_pos.val = 40 * 65536 + 0x2468;
    obj.ext.misc_32.owner = (struct MainObj*)rows;
    obj.ext.misc_32.animation = 0;
    obj.ext.misc_32.timer = 0;
    obj.unk17 = 0;
    obj.previous_animation_index = 0xA5;
    obj.animation_table = option_toggle_animations;
    obj.animation_cursor = (u32*)option_toggle_anim_0;
    obj.animation_step.packed = *obj.animation_cursor;
    obj.animation_step.fields.duration = 1;
    controller_input.pressed = PADstart;
    game_info.unk0 = mode == 0 ? 10 : mode == 1 ? 8
                                                : 9;
    main_bss_state.transition.selection = 1;
    before = obj;
    input_before = controller_input;
    main_before = main_bss_state;
    game_before = game_info;
    func_800CE1D4(&obj);
    before.unk2 = obj.unk2;
    before.on_screen = obj.on_screen;
    before.y_pos = obj.y_pos;
    before.ext.misc_32.animation = obj.ext.misc_32.animation;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(controller_input) / 4; i++)
        assert(((u32*)&controller_input)[i] == ((u32*)&input_before)[i]);
    for (i = 0; i < sizeof(main_bss_state) / 4; i++)
        assert(((u32*)&main_bss_state)[i] == ((u32*)&main_before)[i]);
    for (i = 0; i < sizeof(game_info) / 4; i++)
        assert(((u32*)&game_info)[i] == ((u32*)&game_before)[i]);
    assert(obj.ext.misc_32.owner == (struct MainObj*)rows && rows[2] == 40 && rows[4] == 80 && rows[6] == 120);
    assert(obj.animation_table == option_toggle_animations);
    for (i = 0; i < COUNT(option_toggle_anim_0); i++)
        if (obj.animation_cursor == (u32*)option_toggle_anim_0 + i)
            cursor = i;
    assert(cursor != ~0u);
    switch (observation) {
    case 0:
        actual = (u8)obj.unk2 | ((u32)(u8)obj.ext.misc_32.animation << 8) | ((u32)obj.on_screen << 16);
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = cursor;
        break;
    }
    return actual;
}
static const u32 option_start_modes_cases_expected[] = { 0x100FFu, 0x282468u, 0x3201000Du, 0x1u, 0x100FFu, 0x282468u, 0x3201000Du, 0x1u, 0x10100u, 0x582468u, 0x3201000Du, 0x1u };
static u32 option_start_modes_cases_row(u32 row)
{
    return option_case(row / 4, row % 4);
}

static const struct {
    u16 pressed;
    s8 screen, initial_step;
    u8 timer, selection;
    s8 expected_step;
    u8 expected_selection;
    s16 expected_y;
} cursor_cases[] = {
    { 0, 9, 0, 0, 0, 0, 0, 40 },
    { 0, 9, 0, 0, 1, 0, 1, 88 },
    { PAD_SELECTION_ALT, 9, 0, 0, 1, -1, 0, 40 },
    { PADstart, 10, 0, 1, 1, 0, 1, 88 },
    { PAD_SELECTION_ALT, 8, 0, 1, 1, 0, 1, 88 },
    { 0, 9, -1, 0, 1, -1, 0, 40 },
    { 0, 9, -1, 1, 1, -1, 0, 40 },
    { PADstart, 9, 0, 0, 2, 0, 2, 128 },
};

static u32 test_option_cursor(u32 row)
{
    struct MiscObj obj;
    u8 positions[] = { 0, 0, 40, 0, 80, 0, 120, 0 };
    memset(&obj, 0, sizeof(obj));
    memset(&controller_input, 0, sizeof(controller_input));
    obj.active = 1;
    obj.unk2 = cursor_cases[row].initial_step;
    obj.bg_offset = -1;
    obj.x_pos.val = FIXED(80);
    obj.y_pos.val = FIXED(40);
    obj.ext.misc_32.owner = (struct MainObj*)positions;
    obj.ext.misc_32.timer = cursor_cases[row].timer;
    obj.animation_table = option_toggle_animations;
    obj.animation_cursor = (u32*)option_toggle_anim_0;
    obj.animation_step.fields.duration = 1;
    controller_input.pressed = cursor_cases[row].pressed;
    game_info.unk0 = cursor_cases[row].screen;
    main_bss_state.transition.selection = cursor_cases[row].selection;

    func_800CE1D4(&obj);

    assert(obj.unk2 == cursor_cases[row].expected_step);
    assert(obj.ext.misc_32.animation == cursor_cases[row].expected_selection);
    assert(obj.ext.misc_32.timer == cursor_cases[row].timer);
    assert(obj.ext.misc_32.owner == (struct MainObj*)positions);
    assert(obj.x_pos.val == FIXED(80));
    assert(obj.y_pos.val == FIXED(cursor_cases[row].expected_y));
    assert(controller_input.pressed == cursor_cases[row].pressed);
    return (u8)obj.unk2;
}

const struct CTestGroup c_test_groups[] = {
    { "option_start_modes", NULL, option_start_modes_cases_expected, COUNT(option_start_modes_cases_expected), option_start_modes_cases_row },
    { "option_cursor", 0, 0, COUNT(cursor_cases), test_option_cursor },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(option_start_modes_cases_expected) + COUNT(cursor_cases);
