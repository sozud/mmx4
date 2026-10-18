#include "test_runtime.h"
#include "main/mains/main_54_slash_beast.h"
#include "support/slash_beast_fixture.h"

const struct CTestGroup c_test_groups[] = {
    { "slash_beast_grab_trails", 0, 0, 72, test_slash_beast_grab_trails },
    { "slash_beast_afterimages", 0, 0, 21, test_slash_beast_afterimages },
    { "slash_beast_high_leap_landing", 0, 0, 12, test_slash_beast_high_leap_landing },
    { "slash_beast_fill_health", 0, 0, 20, test_slash_beast_fill_health },
    { "slash_beast_intro_dialogue", 0, 0, 8, test_slash_beast_intro_dialogue },
    { "slash_beast_intro_leap", 0, 0, 4, test_slash_beast_intro_leap },
    { "slash_beast_stagger_start", 0, 0, 48, test_slash_beast_stagger_start },
    { "slash_beast_air_recovery", 0, 0, 78, test_slash_beast_air_recovery },
    { "slash_beast_dash_transitions", 0, 0, 20, test_slash_beast_dash_transitions },
    { "slash_beast_jump_edges", 0, 0, 20, test_slash_beast_jump_edges },
    { "slash_beast_crouch", 0, 0, 8, test_slash_beast_crouch },
    { "slash_beast_pick_patterns", 0, 0, 96, test_slash_beast_pick_patterns },
    { "slash_beast_decisions", 0, 0, COUNT(beast_decisions) * 4, test_slash_beast_decisions },
    { "slash_beast_crescent", 0, 0, 60, test_slash_beast_crescent },
    { "slash_beast_dash_run", 0, 0, 36, test_slash_beast_dash_run },
    { "slash_beast_tile_masks", 0, 0, 8, test_slash_beast_tile_masks },
    { "slash_beast_run", 0, 0, COUNT(beast_scenes) * 4, test_slash_beast_run },
    { "slash_beast_patterns", 0, 0, COUNT(slash_beast_patterns_cases), test_slash_beast_patterns },
    { "slash_beast_states", 0, 0, COUNT(slash_beast_states_cases), test_slash_beast_states },
    { "slash_beast_death_blink", 0, 0, 1, test_slash_beast_death_blink },
    { "slash_beast_death_flash", slash_beast_death_flash_cases, slash_beast_death_flash_cases_expected, COUNT(slash_beast_death_flash_cases), 0 },
    { "slash_beast_stance", 0, 0, 20, test_slash_beast_stance },
    { "slash_beast_init_full", 0, 0, 8, test_slash_beast_init_full },
    { "slash_beast_leap_launch", 0, 0, 32, test_slash_beast_leap_launch },
    { "slash_beast_death_full", 0, 0, 18, test_slash_beast_death_full },
    { "slash_beast_intro_crates", 0, 0, 12, test_slash_beast_intro_crates },
    { "boss_music_selection", 0, 0, 36, test_boss_music_selection },
    { "slash_beast_intro_pose", 0, 0, COUNT(beast_poses), test_slash_beast_intro_pose },
    { "slash_beast_intro_landing", 0, 0, 45, test_slash_beast_intro_landing },
    { "slash_beast_intro_wait", 0, 0, 112, test_slash_beast_intro_wait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 72 + 21 + 12 + 20 + 8 + 4 + 48 + 78 + 20 + 20 + 8 + 96 + COUNT(beast_decisions) * 4 + 60 + 36 + 8 + COUNT(beast_scenes) * 4 + COUNT(slash_beast_patterns_cases) + COUNT(slash_beast_states_cases) + 1 + COUNT(slash_beast_death_flash_cases) + 20 + 8 + 32 + 18 + 12 + 36 + COUNT(beast_poses) + 45 + 112;
