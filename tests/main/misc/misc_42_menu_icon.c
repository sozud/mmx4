#include "test_runtime.h"
#include "main/misc/misc_42_menu_icon.h"
#include "main/misc/misc_31_option_toggle.h"
#include "support/state_cases.h"
extern union AnimationStep option_toggle_anim_0[36];

static u32 frame_case(u32 mode)
{
    static const u8 frames[] = { 0x32, 8, 0x3E, 0x3C, 0x3A, 0x12, 0x12 };
    struct MiscObj obj, before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 1;
    obj.bg_offset = -1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk42 = 0x3456;
    obj.animation_step.fields.frame_index = frames[mode];
    obj.previous_animation_index = mode < 5 ? 0 : 0x32;
    main_bss_state.transition.selection = 3;
    obj.ext.misc_42.unk56 = mode == 6 ? 9 : 3;
    before = obj;
    func_800D0118(&obj);
    before.on_screen = obj.on_screen;
    before.unk42 = obj.unk42;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(main_bss_state.transition.selection == 3);
    return obj.unk42 | ((u32)(u8)obj.on_screen << 16) | ((u32)obj.animation_step.fields.frame_index << 24);
}
static const u32 menu_icon_displayed_frame_cases_expected[] = { 0x32013456u, 0x8013456u, 0x3E013456u, 0x3C013456u, 0x3A013456u, 0x12017803u, 0x12017800u };

static u32 lifecycle_case(u32 mode, u32 observation)
{
    struct MiscObj obj, before;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    u32 i, actual, cursor_offset, archive_offset;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    obj.active = 0x41;
    obj.id = 0x2A;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.bg_offset = -1;
    obj.x_pos.i.hi = 0x40;
    obj.y_pos.i.hi = 0x44;
    obj.unk15 = 0xAB;
    obj.unk16 = 0x22;
    obj.unk17 = 0x35;
    obj.previous_animation_index = 0xA5;
    obj.unk40 = 0x2468;
    obj.unk42 = 0xBEE1;
    obj.ext.misc_42.unk55 = 4;
    obj.ext.misc_42.unk56 = 4;
    obj.ext.misc_42.unk57 = 1;
    obj.unk2 = 4;
    if (mode < 2) {
        obj.animation_table = option_toggle_animations;
        obj.animation_cursor = (u32*)option_toggle_anim_0 + (mode ? 35 : 0);
        obj.animation_step.packed = *obj.animation_cursor;
        obj.animation_step.fields.duration = 1;
    } else if (mode == 2) {
        obj.unk2 = 1;
        obj.ext.misc_42.unk55 = 3;
        obj.ext.misc_42.unk54 = 0;
        main_bss_state.transition.selection = 1;
    } else {
        obj.ext.misc_42.unk58 = 5;
        ((u32*)WINDOW_ARCHIVE_DATA)[2] = 0x180;
    }
    before = obj;
    engine_before = engine_obj;
    main_before = main_bss_state;
    if (mode == 3) {
        func_800CFEE0(&obj);
        before.active = obj.active;
        before.state = obj.state;
        before.unk6 = obj.unk6;
        before.bg_offset = obj.bg_offset;
        before.unk15 = obj.unk15;
        before.unk16 = obj.unk16;
        before.unk17 = obj.unk17;
        before.previous_animation_index = obj.previous_animation_index;
        before.unk40 = obj.unk40;
        before.unk3C = obj.unk3C;
        before.animation_table = obj.animation_table;
    } else {
        func_800D0118(&obj);
        if (mode == 2) {
            before.active = obj.active;
            before.id = obj.id;
            before.unk2 = obj.unk2;
            before.state = obj.state;
            before.unk5 = obj.unk5;
            before.unk6 = obj.unk6;
            before.unk7 = obj.unk7;
        }
        before.y_pos = obj.y_pos;
    }
    before.on_screen = obj.on_screen;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    before.ext.misc_42.unk57 = obj.ext.misc_42.unk57;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(main_bss_state) / 4; i++)
        assert(((u32*)&main_bss_state)[i] == ((u32*)&main_before)[i]);
    cursor_offset = obj.animation_cursor ? obj.animation_cursor - (u32*)option_toggle_anim_0 : 0xFFFF;
    archive_offset = obj.unk3C ? (u8*)obj.unk3C - WINDOW_ARCHIVE_DATA : 0xFFFF;
    switch (observation) {
    case 0:
        actual = ((u32*)&obj)[0];
        break;
    case 1:
        actual = ((u32*)&obj)[1];
        break;
    case 2:
        actual = obj.animation_step.packed;
        break;
    case 3:
        actual = (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
        break;
    case 4:
        actual = cursor_offset | (archive_offset << 16);
        break;
    case 5:
        actual = obj.unk40 | ((u32)obj.unk42 << 16);
        break;
    default:
        actual = obj.unk15 | ((u32)obj.unk16 << 8) | ((u32)obj.unk17 << 16) | ((u32)(u8)obj.ext.misc_42.unk57 << 24);
        break;
    }
    assert(obj.animation_table == (mode == 2 ? NULL : option_toggle_animations));
    return actual;
}
static const u32 menu_icon_lifecycle_cases_expected[] = { 0x1042A41u, 0x4030201u, 0x3201000Du, 0xA80040u, 0xFFFF0001u, 0xBEE12468u, 0x3522ABu, 0x1042A41u, 0x4030201u, 0x3101000Fu, 0xA80040u, 0xFFFF0000u, 0xBEE12468u, 0x3522ABu, 0x0u, 0x0u, 0x0u, 0x440040u, 0xFFFFFFFFu, 0xBEE12468u, 0x13522ABu, 0x1042A01u, 0x4000201u, 0x3101000Fu, 0x440040u, 0x1800000u, 0xBEE11E00u, 0x0u };
static u32 menu_icon_lifecycle_cases_row(u32 row)
{
    return lifecycle_case(row / 7, row % 7);
}

#undef main_bss_state
#undef memcard_menu

struct func_800D0118_case {
    u32 unk2, frame_index, unk56, selection, unk55, unk54, unk1;
    u32 expected[3];
};
static const struct func_800D0118_case func_800D0118_cases[] = {
    { 0, 60, 0, 0, 0, 0, 0, { 0u, 0u, 0u } },
    { 4, 0, 4, 255, 1, -17, 16, { 0xFFFFFFFFu, 0u, 0xB8u } },
    { 4, 0, -1, 255, 1, -17, 16, { 0xFFFFFFFFu, 0u, 0u } },
    { 4, 0, 2, 255, 1, -17, 16, { 0xFFFFFFFFu, 0u, 0u } },
    { 4, 0, 3, 255, 1, -17, 16, { 0xFFFFFFFFu, 0u, 0u } },
};
static u32 test_func_800D0118(u32 row)
{
    const struct func_800D0118_case* c = &func_800D0118_cases[row];
    u32 observed_values[3];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk2 = c->unk2;
    obj.animation_step.fields.frame_index = c->frame_index;
    obj.ext.misc_42.unk56 = c->unk56;
    main_bss_state.transition.selection = c->selection;
    obj.ext.misc_42.unk57 = 0;
    obj.ext.misc_42.unk55 = c->unk55;
    obj.ext.misc_42.unk54 = c->unk54;
    engine_obj.unk1 = c->unk1;
    func_800D0118(&obj);
    observed_values[0] = (u32)obj.ext.misc_42.unk57;
    observed_values[1] = (u32)obj.unk42;
    observed_values[2] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
#undef main_bss_state

#define sm state_room.misc
#define ICON(st, kind, layout, sel, body)                                                                        \
    do {                                                                                                         \
        u8 selection = main_bss_state.transition.selection;                                                      \
        u8 cards[2];                                                                                             \
        u8 e1 = engine_obj.unk1, e2 = engine_obj.unk2;                                                           \
        cards[0] = memcard_menu.card_status[0];                                                                  \
        cards[1] = memcard_menu.card_status[1];                                                                  \
        state_reset(0, 0, 0);                                                                                    \
        sm.active = 1;                                                                                           \
        sm.state = st;                                                                                           \
        sm.unk2 = kind;                                                                                          \
        sm.x_pos.i.hi = 0x40;                                                                                    \
        sm.y_pos.i.hi = 0x20;                                                                                    \
        sm.ext.misc_42.unk58 = layout;                                                                           \
        sm.ext.misc_42.unk56 = layout;                                                                           \
        main_bss_state.transition.selection = sel;                                                               \
        engine_obj.unk1 = engine_obj.unk2 = 1;                                                                   \
        memcard_menu.card_status[0] = 1;                                                                         \
        memcard_menu.card_status[1] = 0;                                                                         \
        body;                                                                                                    \
        menu_icon_update(&sm);                                                                                   \
        state_extra = main_bss_state.transition.selection | (u8)sm.ext.misc_42.unk57 << 8 | (u32)sm.unk16 << 16; \
        main_bss_state.transition.selection = selection;                                                         \
        memcard_menu.card_status[0] = cards[0];                                                                  \
        memcard_menu.card_status[1] = cards[1];                                                                  \
        engine_obj.unk1 = e1;                                                                                    \
        engine_obj.unk2 = e2;                                                                                    \
    } while (0)
static void mi_cursor_top(void)
{
    ICON(0, 0, 0, 0, sm.y_pos.i.hi = 0x10);
}
static void mi_cursor_chosen(void) { ICON(0, 0, 0, 0, ); }
static void mi_cursor_other(void) { ICON(0, 0, 1, 0, ); }
static void mi_arrow(void) { ICON(0, 1, 0, 0, ); }
static void mi_arrow_flip(void) { ICON(0, 2, 0, 0, ); }
static void mi_frame(void) { ICON(0, 3, 0, 0, ); }
static void mi_toggle_card(void) { ICON(0, 4, 0, 0, ); }
static void mi_toggle_both(void) { ICON(0, 4, 0, 0, memcard_menu.card_status[1] = 1); }
static void mi_toggle_options(void) { ICON(0, 4, 1, 0, ); }
static void mi_toggle_wide(void) { ICON(0, 4, 2, 0, ); }
static void mi_toggle_right(void) { ICON(0, 4, 4, 0, ); }
static void mi_toggle_other(void) { ICON(0, 4, 5, 0, ); }
static void mi_other(void) { ICON(0, 5, 0, 0, ); }
static void mi_blink(void) { ICON(1, 0, 0, 1, ); }
static void mi_blink_hold(void) { ICON(1, 0, 0, 1, sm.animation_step.fields.frame_index = 8); }
static void mi_move_two(void) { ICON(1, 4, 0, 1, sm.ext.misc_42.unk57 = 0); }
static void mi_move_three(void) { ICON(1, 4, 2, 2, sm.ext.misc_42.unk57 = 0); }
static void mi_move_three_mid(void) { ICON(1, 4, 2, 1, sm.ext.misc_42.unk57 = 0); }
static void mi_move_three_top(void) { ICON(1, 4, 2, 0, sm.ext.misc_42.unk57 = 1); }
static void mi_move_four(void) { ICON(1, 4, 3, 3, sm.ext.misc_42.unk57 = 0); }
static void mi_move_four_two(void) { ICON(1, 4, 3, 2, sm.ext.misc_42.unk57 = 0); }
static void mi_move_four_one(void) { ICON(1, 4, 3, 1, sm.ext.misc_42.unk57 = 0); }
static void mi_move_four_top(void) { ICON(1, 4, 3, 0, sm.ext.misc_42.unk57 = 1); }
static void mi_move_low(void) { ICON(1, 4, 4, 1, sm.ext.misc_42.unk57 = 0); }
static void mi_move_low_top(void) { ICON(1, 4, 4, 0, sm.ext.misc_42.unk57 = 1); }
static void mi_move_same(void) { ICON(1, 4, 0, 0, sm.ext.misc_42.unk57 = 0); }
static void mi_kill_engine1(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 1, sm.ext.misc_42.unk54 = 2)); }
static void mi_keep_engine1(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 1, sm.ext.misc_42.unk54 = 1)); }
static void mi_kill_engine2(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 2, sm.ext.misc_42.unk54 = 2)); }
static void mi_keep_engine2(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 2, sm.ext.misc_42.unk54 = 1)); }
static void mi_kill_selection(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 3, sm.ext.misc_42.unk54 = 2)); }
static void mi_keep_selection(void) { ICON(1, 1, 0, 0, (sm.ext.misc_42.unk55 = 3, sm.ext.misc_42.unk54 = 0)); }

static void (*const menu_icon_states_cases[])(void) = {
    mi_cursor_top,
    mi_cursor_chosen,
    mi_cursor_other,
    mi_arrow,
    mi_arrow_flip,
    mi_frame,
    mi_toggle_card,
    mi_toggle_both,
    mi_toggle_options,
    mi_toggle_wide,
    mi_toggle_right,
    mi_toggle_other,
    mi_other,
    mi_blink,
    mi_blink_hold,
    mi_move_two,
    mi_move_three,
    mi_move_three_mid,
    mi_move_three_top,
    mi_move_four,
    mi_move_four_two,
    mi_move_four_one,
    mi_move_four_top,
    mi_move_low,
    mi_move_low_top,
    mi_move_same,
    mi_kill_engine1,
    mi_keep_engine1,
    mi_kill_engine2,
    mi_keep_engine2,
    mi_kill_selection,
    mi_keep_selection,
};
static const u32 menu_icon_states_expected[] = { 1u, 1u, 0x400000u, 0x100000u, 0u, 0u, 0u, 0x57802u, 0x20000u, 0u, 1u, 1u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x57803u, 0x20000u, 0u, 1u, 1u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x57800u, 0x20000u, 0u, 1u, 0x101u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x57807u, 0x60000u, 0u, 1u, 0x400201u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0x301u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0x30000u, 0u, 1u, 0xFF000401u, 0x500000u, 0x980000u, 0u, 0u, 0u, 0xF0000u, 1u, 0u, 1u, 0xFF000401u, 0x500000u, 0x780000u, 0u, 0u, 0u, 0xF0000u, 0u, 0u, 1u, 0xFF000401u, 0x280000u, 0x780000u, 0u, 0u, 0u, 0xF0000u, 0u, 0u, 1u, 0xFF000401u, 0x880000u, 0xB80000u, 0u, 0u, 0u, 0xF0000u, 0u, 0u, 1u, 0xFF000401u, 0x980000u, 0x780000u, 0u, 0u, 0u, 0xF0000u, 0u, 0u, 1u, 0xFF000401u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0xF0000u, 0u, 0u, 1u, 0x501u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 1u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x57800u, 1u, 0u, 1u, 1u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 1u, 0x401u, 0x400000u, 0x980000u, 0u, 0u, 0u, 0x40000u, 0x101u, 0u, 1u, 0x401u, 0x400000u, 0xB80000u, 0u, 0u, 0u, 0x40000u, 0x202u, 0u, 1u, 0x401u, 0x400000u, 0x980000u, 0u, 0u, 0u, 0x40000u, 0x101u, 0u, 1u, 0x401u, 0x400000u, 0x780000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x401u, 0x400000u, 0xB80000u, 0u, 0u, 0u, 0x40000u, 0x303u, 0u, 1u, 0x401u, 0x400000u, 0x980000u, 0u, 0u, 0u, 0x40000u, 0x202u, 0u, 1u, 0x401u, 0x400000u, 0x880000u, 0u, 0u, 0u, 0x40000u, 0x101u, 0u, 1u, 0x401u, 0x400000u, 0x780000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x401u, 0x400000u, 0xB80000u, 0u, 0u, 0u, 0x40000u, 0x101u, 0u, 1u, 0x401u, 0x400000u, 0xA80000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x401u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0x101u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0x101u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0x101u, 0x400000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_menu_icon_states(u32 row)
{
    return object_run(menu_icon_states_cases[row], row, &menu_icon_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "menu_icon_states", 0, 0, COUNT(menu_icon_states_cases), test_menu_icon_states },
    { "menu_icon_displayed_frame", NULL, menu_icon_displayed_frame_cases_expected, COUNT(menu_icon_displayed_frame_cases_expected), frame_case },
    { "menu_icon_lifecycle", NULL, menu_icon_lifecycle_cases_expected, COUNT(menu_icon_lifecycle_cases_expected), menu_icon_lifecycle_cases_row },
    { "func_800D0118", 0, 0, 5, test_func_800D0118 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(menu_icon_states_cases) + COUNT(menu_icon_displayed_frame_cases_expected) + COUNT(menu_icon_lifecycle_cases_expected) + 5;
