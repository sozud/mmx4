#include "test_runtime.h"
#include "main/misc/misc_31_option_toggle.h"
void func_8001C008(s32, s32);
void func_8001B388(struct EngineObj*);
void menu_icon_update(struct MiscObj*);
static struct MiscObj expected[64];
static struct EngineObj engine;
static struct MainBssState main_before;
static struct MemcardMenuState cards;
static struct PlayerObj player, entity;
static struct ControllerInput input;
static struct BackgroundObj backgrounds[3];
static u32 window_before[32], window_expected[32];
static u16 rng;
static void capture(void)
{
    expected[0] = misc_objects[0];
    engine = engine_obj;
    main_before = main_bss_state;
    cards = memcard_menu;
    player = g_Player;
    entity = g_Entity;
    input = controller_input;
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    rng = cur_random;
}
static void check(void)
{
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)&memcard_menu, (u32*)&cards, sizeof(cards) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0 && cur_random == rng);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(c_test_word_difference((u32*)WINDOW_ARCHIVE_DATA, window_expected, sizeof(window_expected) / 4) == 0);
}
static u32 cursor(u32 row)
{
    u32 i;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)&memcard_menu, sizeof(memcard_menu) / 4);
    controller_input.held = controller_input.previous = controller_input.pressed = 0;
    engine_obj.state = 1;
    engine_obj.unk1 = row ? 4 : 1;
    cur_random = 0x1234;
    c_test_copy_words(window_before, (u32*)WINDOW_ARCHIVE_DATA, COUNT(window_before));
    for (i = 0; i < COUNT(window_expected); i++)
        window_expected[i] = i < 4 ? 64 : 0;
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_expected, COUNT(window_expected));
    func_8001C008(row == 0 ? 2 : row == 1 ? 3
                                          : 0,
        row == 0 ? 0 : row == 1 ? 3
                                : 1);
    assert(misc_objects[0].active == 1 && misc_objects[0].id == 42 && misc_objects[0].unk2 == 4 && misc_objects[0].state == 0);
    if (row < 2) {
        capture();
        expected[0].on_screen = 1;
        expected[0].bg_offset = -1;
        expected[0].unk40 = 0x1E00;
        expected[0].unk3C = WINDOW_ARCHIVE_DATA + 64;
        expected[0].animation_table = (u32**)option_toggle_animations;
        expected[0].unk16 = 0;
        expected[0].unk17 = 0;
        expected[0].previous_animation_index = 0xFF;
        expected[0].animation_cursor = (u32*)option_toggle_animations[0];
        expected[0].animation_step.packed = 0x3101000F;
        expected[0].x_pos.i.hi = row ? 0x28 : 0x50;
        expected[0].y_pos.i.hi = 0x78;
        expected[0].state = 1;
        menu_icon_update(&misc_objects[0]);
        check();
    } else {
        menu_icon_update(&misc_objects[0]);
        assert(misc_objects[0].y_pos.i.hi == 0x78 && main_bss_state.transition.selection == 0);
        controller_input.held = controller_input.pressed = PADLup;
        func_8001B388(&engine_obj);
        assert(main_bss_state.transition.selection == 1);
        menu_icon_update(&misc_objects[0]);
        assert(misc_objects[0].y_pos.i.hi == 0x98);
        controller_input.held = controller_input.pressed = 0;
        controller_input.previous = PADLup;
        func_8001B388(&engine_obj);
        controller_input.held = controller_input.pressed = PADLup;
        controller_input.previous = 0;
        func_8001B388(&engine_obj);
        assert(main_bss_state.transition.selection == 0);
        capture();
        expected[0].unk18 = expected[0].x_pos;
        expected[0].unk1C = expected[0].y_pos;
        expected[0].y_pos.i.hi = 0x78;
        expected[0].ext.misc_42.unk57 = 0;
        expected[0].animation_step.fields.duration--;
        menu_icon_update(&misc_objects[0]);
        check();
    }
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_before, COUNT(window_before));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "original_menu_cursor_port_slots_and_real_confirmation_Up_toggle", NULL, NULL, 3, cursor } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
