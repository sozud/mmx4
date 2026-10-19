#include "test_runtime.h"
#include "main/game_info.h"
void character_select_state_5(struct EngineObj*);
static const s8 active_values[] = { 0, 1, -1 };
static const s16 timers[] = { 1, 2, 300 };
static u32 fade_wait(u32 row)
{
    struct GameInfo info, expected;
    struct MainBssState main_expected;
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    u32 phase = row % 3, active = row / 3 % 3, timer = row / 9;
    engine_obj.unk1 = 5;
    engine_obj.unk4 = timers[timer] - 1;
    engine_expected = engine_obj;
    memset(&info, 0x25, sizeof(info));
    info.mode = phase ? 2 : 1;
    info.unk4 = timers[timer];
    main_bss_state.transition.active = active_values[active];
    main_bss_state.transition.fade_amount = 3;
    main_expected = main_bss_state;
    expected = info;
    if (phase == 2) {
        if (timer == 0) {
            engine_expected.unk1++;
            if (active == 0) {
                main_expected.transition.active = -1;
                main_expected.transition.fade_amount = 8;
            }
        } else
            engine_expected.unk4--;
        character_select_state_5(&engine_obj);
    } else if (phase == 1) {
        expected.unk4--;
        if (timer == 0) {
            expected.mode++;
            if (active == 0) {
                main_expected.transition.active = -1;
                main_expected.transition.fade_amount = 8;
            }
        }
        func_8001D64C(&info);
    } else {
        if (active == 0) {
            expected.mode++;
            expected.unkD = 0;
        }
        func_8001D178(&info);
    }
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "game_fade_wait", NULL, NULL, 27, fade_wait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 27;
