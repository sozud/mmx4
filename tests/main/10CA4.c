#include "test_runtime.h"
#include "main/10CA4.h"
#include "support/test_pad.h"
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
    { TEST_PAD_UP, 0, 2, 0, 0 },
    { TEST_PAD_DOWN, 2, 0, 0, 0 },
    { TEST_PAD_CONFIRM, 0, 0, 1, 0 },
    { TEST_PAD_CONFIRM, 1, 1, 1, 0 },
    { TEST_PAD_CONFIRM, 2, 2, 1, 0 },
    { TEST_PAD_UP | TEST_PAD_CONFIRM, 0, 2, 1, 0 },
    { TEST_PAD_DOWN | TEST_PAD_CONFIRM, 2, 0, 1, 0 },
    { TEST_PAD_START, 0, 0, 0, 0 },
    { TEST_PAD_UP | TEST_PAD_DOWN, 0, 0, 0, 0 },
    { TEST_PAD_CONFIRM | TEST_PAD_DOWN, 1, 1, 0, 1 },
    { TEST_PAD_CONFIRM, 2, 2, 0, -1 },
};

static u32 test_game_over_navigation(u32 row)
{
    u32 variant = row / COUNT(game_over_navigation);
    u32 index = row % COUNT(game_over_navigation);
    struct EngineObj expected;
    s8 next_fade;
    u32 started;
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
    TEST_PAD_PRESSED = game_over_navigation[index].pressed;
    next_fade = game_over_navigation[index].advance && (variant || game_over_navigation[index].next_cursor != 2) ? -1 : game_over_navigation[index].active;
    if (variant)
        func_80020808(&engine_obj);
    else
        func_80020638(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(main_bss_state.transition.selection == game_over_navigation[index].next_cursor);
    started = next_fade == -1 && game_over_navigation[index].active == 0;
    assert(main_bss_state.transition.active == (started ? TEST_FADE_OUT_ACTIVE : next_fade));
    assert(main_bss_state.transition.fade_amount == (started ? TEST_FADE_OUT_AMOUNT(8, 3) : 3));
    assert(TEST_PAD_PRESSED == game_over_navigation[index].pressed);
    return 1;
}

#ifndef MMX4_SATURN
#include <psyz/spu.h>
#include "main/menu.h"
#include "main/55C4.h"
#include "main/objects.h"
static u32 test_continue_menu_open(u32 row)
{
    static const u32 expected[2] = { 0x00780105u, 0x01780101u };
    u32 seen;
    Psyz_SpuInit();
    reset_objects();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    D_800F1D90.save.character = 0;
    engine_obj.stage = row == 0 ? 0 : 3;
    engine_obj.cur_character = CHARACTER_ZERO;
    func_80020580(&engine_obj);
    seen = (u8)engine_obj.unk1 | (u32)(u8)main_bss_state.transition.active << 8 | (u32)(u16)engine_obj.unk4 << 16;
    seen |= (u32)D_800F1D90.save.character << 24;
    return c_test_observe(0, row, &seen, &expected[row], 1);
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "game_over_choices", 0, 0, 20, test_game_over_choices },
    { "game_over_navigation", 0, 0, 2 * COUNT(game_over_navigation), test_game_over_navigation },
#ifndef MMX4_SATURN
    { "continue_menu_open", 0, 0, 2, test_continue_menu_open },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 20 + 2 * COUNT(game_over_navigation)
#ifndef MMX4_SATURN
    + 2
#endif
    ;
