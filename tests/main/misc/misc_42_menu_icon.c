#include "test_runtime.h"
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
#define FRAME_CASE(name, mode)   \
    static u32 name(void)        \
    {                            \
        return frame_case(mode); \
    }
FRAME_CASE(FRAME_32, 0)
FRAME_CASE(FRAME_08, 1)
FRAME_CASE(FRAME_3E, 2)
FRAME_CASE(FRAME_3C, 3)
FRAME_CASE(FRAME_3A, 4)
FRAME_CASE(FRAME_DEFAULT_SELECTED, 5)
FRAME_CASE(FRAME_DEFAULT_UNSELECTED, 6)
static const CTestCase menu_icon_displayed_frame_cases[] = {
    FRAME_32,
    FRAME_08,
    FRAME_3E,
    FRAME_3C,
    FRAME_3A,
    FRAME_DEFAULT_SELECTED,
    FRAME_DEFAULT_UNSELECTED,
};
static const u32 menu_icon_displayed_frame_cases_expected[] = { 0x32013456u, 0x8013456u, 0x3E013456u, 0x3C013456u, 0x3A013456u, 0x12017803u, 0x12017800u };
#undef main_bss_state
#undef FRAME_CASE

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
#define LIFECYCLE_CASE(name, mode, observation)   \
    static u32 name(void)                         \
    {                                             \
        return lifecycle_case(mode, observation); \
    }
LIFECYCLE_CASE(MENU_ICON_ADVANCE_HEADER, 0, 0)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_STATE, 0, 1)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_ANIMATION, 0, 2)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_POSITION, 0, 3)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_POINTERS, 0, 4)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_PARAMETERS, 0, 5)
LIFECYCLE_CASE(MENU_ICON_ADVANCE_DETAIL, 0, 6)
LIFECYCLE_CASE(MENU_ICON_WRAP_HEADER, 1, 0)
LIFECYCLE_CASE(MENU_ICON_WRAP_STATE, 1, 1)
LIFECYCLE_CASE(MENU_ICON_WRAP_ANIMATION, 1, 2)
LIFECYCLE_CASE(MENU_ICON_WRAP_POSITION, 1, 3)
LIFECYCLE_CASE(MENU_ICON_WRAP_POINTERS, 1, 4)
LIFECYCLE_CASE(MENU_ICON_WRAP_PARAMETERS, 1, 5)
LIFECYCLE_CASE(MENU_ICON_WRAP_DETAIL, 1, 6)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_HEADER, 2, 0)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_STATE, 2, 1)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_ANIMATION, 2, 2)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_POSITION, 2, 3)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_POINTERS, 2, 4)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_PARAMETERS, 2, 5)
LIFECYCLE_CASE(MENU_ICON_EXPIRE_DETAIL, 2, 6)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_HEADER, 3, 0)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_STATE, 3, 1)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_ANIMATION, 3, 2)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_POSITION, 3, 3)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_POINTERS, 3, 4)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_PARAMETERS, 3, 5)
LIFECYCLE_CASE(MENU_ICON_INIT_DEFAULT_DETAIL, 3, 6)
static const CTestCase menu_icon_lifecycle_cases[] = {
    MENU_ICON_ADVANCE_HEADER,
    MENU_ICON_ADVANCE_STATE,
    MENU_ICON_ADVANCE_ANIMATION,
    MENU_ICON_ADVANCE_POSITION,
    MENU_ICON_ADVANCE_POINTERS,
    MENU_ICON_ADVANCE_PARAMETERS,
    MENU_ICON_ADVANCE_DETAIL,
    MENU_ICON_WRAP_HEADER,
    MENU_ICON_WRAP_STATE,
    MENU_ICON_WRAP_ANIMATION,
    MENU_ICON_WRAP_POSITION,
    MENU_ICON_WRAP_POINTERS,
    MENU_ICON_WRAP_PARAMETERS,
    MENU_ICON_WRAP_DETAIL,
    MENU_ICON_EXPIRE_HEADER,
    MENU_ICON_EXPIRE_STATE,
    MENU_ICON_EXPIRE_ANIMATION,
    MENU_ICON_EXPIRE_POSITION,
    MENU_ICON_EXPIRE_POINTERS,
    MENU_ICON_EXPIRE_PARAMETERS,
    MENU_ICON_EXPIRE_DETAIL,
    MENU_ICON_INIT_DEFAULT_HEADER,
    MENU_ICON_INIT_DEFAULT_STATE,
    MENU_ICON_INIT_DEFAULT_ANIMATION,
    MENU_ICON_INIT_DEFAULT_POSITION,
    MENU_ICON_INIT_DEFAULT_POINTERS,
    MENU_ICON_INIT_DEFAULT_PARAMETERS,
    MENU_ICON_INIT_DEFAULT_DETAIL,
};
static const u32 menu_icon_lifecycle_cases_expected[] = { 0x1042A41u, 0x4030201u, 0x3201000Du, 0xA80040u, 0xFFFF0001u, 0xBEE12468u, 0x3522ABu, 0x1042A41u, 0x4030201u, 0x3101000Fu, 0xA80040u, 0xFFFF0000u, 0xBEE12468u, 0x3522ABu, 0x0u, 0x0u, 0x0u, 0x440040u, 0xFFFFFFFFu, 0xBEE12468u, 0x13522ABu, 0x1042A01u, 0x4000201u, 0x3101000Fu, 0x440040u, 0x1800000u, 0xBEE11E00u, 0x0u };
#undef main_bss_state
#undef LIFECYCLE_CASE

struct func_800CFEE0_case {
    u32 unk2, card_status_1, card_status_0;
    u32 expected[13];
};
static const struct func_800CFEE0_case func_800CFEE0_cases[] = {
    { -1, 0, 0, { 0u, 1u, 0xFFFFFFFFu, 0u, 1u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 4, 255, 0, { 0u, 1u, 0xFFFFFFFFu, 0u, 1u, 1u, 0u, 0u, 0x1E00u, 0u, 0u, 0x50u, 0x78u } },
    { 4, 0, 255, { 1u, 1u, 0xFFFFFFFFu, 0u, 1u, 1u, 0u, 0u, 0x1E00u, 0u, 0u, 0x50u, 0x98u } },
};
static u32 test_func_800CFEE0(u32 row)
{
    const struct func_800CFEE0_case* c = &func_800CFEE0_cases[row];
    u32 observed_values[13];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    obj.unk2 = c->unk2;
    memcard_menu.card_status[1] = c->card_status_1;
    memcard_menu.card_status[0] = c->card_status_0;
    func_800CFEE0(&obj);
    observed_values[0] = (u32)main_bss_state.transition.selection;
    observed_values[1] = (u32)obj.active;
    observed_values[2] = (u32)obj.bg_offset;
    observed_values[3] = (u32)obj.ext.misc_42.unk57;
    observed_values[4] = (u32)obj.on_screen;
    observed_values[5] = (u32)obj.state;
    observed_values[6] = (u32)obj.unk15;
    observed_values[7] = (u32)obj.unk16;
    observed_values[8] = (u32)obj.unk40;
    observed_values[9] = (u32)obj.unk42;
    observed_values[10] = (u32)obj.unk6;
    observed_values[11] = (u32)obj.x_pos.i.hi;
    observed_values[12] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 13);
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

const struct CTestGroup c_test_groups[] = {
    { "menu_icon_displayed_frame", menu_icon_displayed_frame_cases, menu_icon_displayed_frame_cases_expected, COUNT(menu_icon_displayed_frame_cases), 0 },
    { "menu_icon_lifecycle", menu_icon_lifecycle_cases, menu_icon_lifecycle_cases_expected, COUNT(menu_icon_lifecycle_cases), 0 },
    { "func_800CFEE0", 0, 0, 3, test_func_800CFEE0 },
    { "func_800D0118", 0, 0, 5, test_func_800D0118 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(menu_icon_displayed_frame_cases) + COUNT(menu_icon_lifecycle_cases) + 3 + 5;
