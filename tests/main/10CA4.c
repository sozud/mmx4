#include "test_runtime.h"
#include "main/10CA4.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

#undef controller_input

static u32 test_game_over_choices(u32 row)
{
    struct EngineObj expected;
    u32 retry_menu = row >= 12;
    u32 choice = retry_menu ? (row - 12) / 4 : row / 4;
    u32 extra_lives = row / 2 % 2;
    u32 fading = row % 2;
    memset(&engine_obj, 0x25, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 8;
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 3;
    engine_obj.unk3 = 4;
    engine_obj.checkpoint = 5;
    engine_obj.unk1E = 6;
    engine_obj.collected_upgrades = extra_lives ? 0x8000 : 0;
    D_80171EA8 = 0;
    main_bss_state.transition.active = fading;
    main_bss_state.transition.selection = choice;
    expected = engine_obj;
    if (!fading) {
        expected.state = choice == 0 ? 5 : choice == 1 ? 3
                                                       : 12;
        expected.unk1 = expected.unk2 = expected.unk3 = 0;
        if (choice != 2)
            expected.player_lives = extra_lives ? 4 : 2;
        if (choice == 0)
            expected.checkpoint = expected.unk1E = 0;
        if (choice == 2)
            expected.unk4 = 8;
    }
    if (retry_menu)
        func_8002088C(&engine_obj);
    else
        func_800206D0(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(main_bss_state.transition.active == fading);
    assert(main_bss_state.transition.selection == choice && D_80171EA8 == 0);
    return 1;
}

static const struct {
    u16 pressed;
    u8 cursor, next_cursor, advance;
    s8 active;
} game_over_navigation[] = {
    { 0, 0, 0, 0, 0 },
    { PADLup, 0, 2, 0, 0 },
    { PADLdown, 2, 0, 0, 0 },
    { PAD_CONFIRM, 0, 0, 1, 0 },
    { PAD_CONFIRM, 1, 1, 1, 0 },
    { PAD_CONFIRM, 2, 2, 1, 0 },
    { PADLup | PAD_CONFIRM, 0, 2, 1, 0 },
    { PADLdown | PAD_CONFIRM, 2, 0, 1, 0 },
    { PADstart, 0, 0, 0, 0 },
    { PADLup | PADLdown, 0, 0, 0, 0 },
    { PAD_CONFIRM | PADLdown, 1, 1, 0, 1 },
    { PAD_CONFIRM, 2, 2, 0, -1 },
};

static u32 test_game_over_navigation(u32 row)
{
    u32 variant = row / COUNT(game_over_navigation);
    u32 index = row % COUNT(game_over_navigation);
    struct EngineObj expected;
    s8 next_fade;
    memset(&engine_obj, 0x25, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    engine_obj.unk1 = 1;
    engine_obj.unk8 = 2;
    expected = engine_obj;
    expected.unk1 += game_over_navigation[index].advance;
    main_bss_state.transition.active = game_over_navigation[index].active;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = game_over_navigation[index].cursor;
    controller_input.pressed = game_over_navigation[index].pressed;
    next_fade = game_over_navigation[index].advance && (variant || game_over_navigation[index].next_cursor != 2) ? -1 : game_over_navigation[index].active;
    if (variant)
        func_80020808(&engine_obj);
    else
        func_80020638(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(main_bss_state.transition.selection == game_over_navigation[index].next_cursor);
    assert(main_bss_state.transition.active == next_fade);
    assert(main_bss_state.transition.fade_amount == (next_fade == -1 && game_over_navigation[index].active == 0 ? 8 : 3));
    assert(controller_input.pressed == game_over_navigation[index].pressed);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "game_over_choices", 0, 0, 20, test_game_over_choices },
    { "game_over_navigation", 0, 0, 2 * COUNT(game_over_navigation), test_game_over_navigation },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 20 + 2 * COUNT(game_over_navigation);
