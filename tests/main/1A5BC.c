#include "test_runtime.h"
#include "main/1A5BC.h"

extern u16 D_800EE430[16];
extern u8 D_800F4568[], D_800F457C[];

static const u16 default_bindings[16] = {
    0x2000, 0x8000, 0x1000, 0x4000, 0x80, 0x10, 2, 0x40,
    0x20, 8, 4, 0, 0, 0, 0, 0
};

static void controls_reset(void)
{
    memset(&game_info, 0, sizeof(game_info));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memcpy(D_800EE430, default_bindings, sizeof(default_bindings));
    D_8013B7D0 = 3;
}

static const struct {
    u16 pressed;
    u8 selection, character, both_characters;
    s8 transition;
    u8 expected_selection, exits;
} navigation[] = {
    { PADstart | PADLup, 2, 0, 0, 1, 2, 0 },
    { PADstart, 0, 0, 0, 0, 0, 1 },
    { PAD_CONFIRM, 7, 0, 0, 0, 7, 1 },
    { PADLup, 0, 0, 0, 0, 7, 0 },
    { PADLup, 1, 0, 0, 0, 0, 0 },
    { PADLup, 2, 1, 0, 0, 1, 0 },
    { PADLup, 7, 0, 0, 0, 6, 0 },
    { PADLup, 7, 1, 0, 0, 4, 0 },
    { PADLup, 7, 1, 1, 0, 6, 0 },
    { PADLdown, 7, 0, 0, 0, 0, 0 },
    { PADLdown, 4, 0, 0, 0, 5, 0 },
    { PADLdown, 4, 1, 0, 0, 7, 0 },
    { PADLdown, 4, 1, 1, 0, 5, 0 },
    { PADLdown, 1, 1, 0, 0, 2, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 7, 0, 0, 0, 7, 0 },
    { PADLup | PADLright, 2, 0, 0, 0, 1, 0 },
};

static u32 test_controls_navigation(u32 row)
{
    u32 i;
    controls_reset();
    controller_input.pressed = navigation[row].pressed;
    main_bss_state.transition.selection = navigation[row].selection;
    main_bss_state.transition.active = navigation[row].transition;
    main_bss_state.character_mode = navigation[row].both_characters;
    engine_obj.cur_character = navigation[row].character;

    func_8002A098(&game_info);

    assert(main_bss_state.transition.selection == navigation[row].expected_selection);
    assert(main_bss_state.transition.active == (navigation[row].exits ? -1 : navigation[row].transition));
    assert(D_8013B7D0 == 3 + navigation[row].exits);
    if (navigation[row].exits)
        assert(main_bss_state.transition.fade_amount == 8);
    for (i = 0; i < COUNT(default_bindings); i++)
        assert(D_800EE430[i] == default_bindings[i]);
    assert(controller_input.pressed == navigation[row].pressed);
    return main_bss_state.transition.selection;
}

static const struct {
    u16 button;
    s8 previous_action;
} rebindings[] = {
    { 0x80, 4 },
    { 0x10, 5 },
    { 0x40, 7 },
    { 0x20, 8 },
    { 4, 10 },
    { 1, -1 },
    { 8, 9 },
    { 2, 6 },
};

static u32 test_controls_rebinding(u32 row)
{
    u16 expected[16];
    u32 i;
    controls_reset();
    memcpy(expected, default_bindings, sizeof(expected));
    controller_input.pressed = rebindings[row].button;
    expected[4] = rebindings[row].button;
    if (rebindings[row].previous_action >= 0 && rebindings[row].previous_action != 4)
        expected[(u8)rebindings[row].previous_action] = 0x80;

    func_8002A098(&game_info);

    for (i = 0; i < COUNT(expected); i++)
        assert(D_800EE430[i] == expected[i]);
    assert(main_bss_state.transition.selection == 0);
    assert(main_bss_state.transition.active == 0);
    assert(D_8013B7D0 == 3);
    return D_800EE430[4];
}

static const struct {
    u8 both_characters, character, free_slots, expected_labels;
} label_cases[] = {
    { 0, 0, 0, 0 },
    { 0, 0, 1, 1 },
    { 0, 0, 2, 2 },
    { 0, 0, 4, 4 },
    { 0, 0, 20, 18 },
    { 0, 1, 20, 18 },
    { 1, 0, 20, 20 },
    { 1, 1, 0, 0 },
    { 1, 1, 4, 4 },
};

static u32 test_controls_labels(u32 row)
{
    struct UnkObj occupied;
    u32 i, created = 0, footers = 0;
    controls_reset();
    memset(unk_objects, 0, sizeof(unk_objects));
    memset(&occupied, 0, sizeof(occupied));
    occupied.active = 1;
    occupied.id = 0x25;
    occupied.unk2 = 0x33;
    for (i = 0; i < COUNT(unk_objects); i++)
        if (i >= label_cases[row].free_slots)
            unk_objects[i] = occupied;
    main_bss_state.character_mode = label_cases[row].both_characters;
    engine_obj.cur_character = label_cases[row].character;
    main_bss_state.transition.selection = 4;

    func_80029E1C(&game_info);

    for (i = 0; i < COUNT(unk_objects); i++) {
        if (i >= label_cases[row].free_slots) {
            c_test_same_words(&unk_objects[i], &occupied, sizeof(occupied));
        } else if (unk_objects[i].active) {
            assert(unk_objects[i].active == 1 && unk_objects[i].id == 0);
            created++;
            footers += unk_objects[i].unk2 == -2;
        }
    }
    assert(created == label_cases[row].expected_labels);
    assert(footers == (label_cases[row].free_slots == 20));
    if (created != 0) {
        assert(unk_objects[0].unk2 == 0x5E && unk_objects[0].y_pos.i.hi == 0x10);
        if (created > 1) {
            assert(unk_objects[1].unk2 == -1);
            assert(unk_objects[1].link.data == (label_cases[row].both_characters ? D_800F4568 : D_800F457C));
        }
    }
    assert(main_bss_state.transition.selection == 0);
    assert(main_bss_state.transition.active == 1);
    assert(main_bss_state.transition.fade_amount == 8);
    assert(D_8013B7D0 == 4);
    return created;
}

const struct CTestGroup c_test_groups[] = {
    { "controls_navigation", 0, 0, COUNT(navigation), test_controls_navigation },
    { "controls_rebinding", 0, 0, COUNT(rebindings), test_controls_rebinding },
    { "controls_labels", 0, 0, COUNT(label_cases), test_controls_labels },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(navigation) + COUNT(rebindings) + COUNT(label_cases);
