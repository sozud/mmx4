#include "test_runtime.h"
#include "main/mains/main_54_slash_beast.h"
#include "support/slash_beast_fixture.h"

void func_8006C378(struct MainObj*);
void func_8006CDD4(struct MainObj*);
void slash_beast_dash_turn(struct MainObj*);
#ifdef VERSION_DEMO
#define SLASH_BEAST_MORE 1
#else
#define SLASH_BEAST_MORE 4
#endif
static u32 test_slash_beast_more(u32 row)
{
#ifdef VERSION_DEMO
    row = 3;
#else
    u32 i;
#endif
    switch (row) {
#ifndef VERSION_DEMO
    case 0:
        BEAST(4, 1), so.animation_step.fields.event = 2;
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1, shot_objects[i].id = 0;
        func_8006C378(&so);
        assert(so.attack_box == (const u8*)D_80100230 && so.hurt_box == (const u8*)D_80100234);
        for (i = 0; i < COUNT(shot_objects); i++)
            assert(shot_objects[i].id == 0);
        memset(shot_objects, 0, sizeof(shot_objects));
        break;
    case 1:
        BEAST(4, 1), memset(shot_objects, 0, sizeof(shot_objects)), so.animation_step.fields.event = 3, so.ext.main_54.powered_up = 1;
        func_8006C378(&so);
        assert(so.attack_box == (const u8*)D_80100238 && so.hurt_box == (const u8*)&D_80100240);
        assert(shot_objects[0].active == 0x41 && shot_objects[0].id == 0x1F && shot_objects[0].unk2 == 1 && shot_objects[0].unk7C == (struct WeaponObj*)&so);
        memset(shot_objects, 0, sizeof(shot_objects));
        break;
    case 2:
        BEAST(5, 0), so.ext.main_54.was_hit = 1, so.unk7C = 5, so.x_pos.i.hi = 0x80, g_Player.x_pos.i.hi = 0x40;
        func_8006CDD4(&so);
        assert(so.unk5 == 2 && so.unk6 == 0 && so.unk7C == 5);
        break;
#endif
    default:
        BEAST(6, 2), so.x_speed = 0x30000, so.contact_damage = 3;
        slash_beast_dash_turn(&so);
        assert(so.unk6 == 2 && so.x_speed == 0x30000 && so.contact_damage == 3 && so.ext.main_54.claw_hitbox == 0);
        break;
    }
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "slash_beast_grab_trails", 0, 0, 72, test_slash_beast_grab_trails },
    { "slash_beast_afterimages", 0, 0, 21, test_slash_beast_afterimages },
    { "slash_beast_high_leap_landing", 0, 0, 12, test_slash_beast_high_leap_landing },
#ifndef MMX4_SATURN
    { "slash_beast_fill_health", 0, 0, 20, test_slash_beast_fill_health },
#endif
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
#ifndef MMX4_SATURN
    { "boss_music_selection", 0, 0, 36, test_boss_music_selection },
    { "slash_beast_intro_pose", 0, 0, COUNT(beast_poses), test_slash_beast_intro_pose },
#endif
    { "slash_beast_intro_landing", 0, 0, 45, test_slash_beast_intro_landing },
    { "slash_beast_intro_wait", 0, 0, 112, test_slash_beast_intro_wait },
    { "slash_beast_more", 0, 0, SLASH_BEAST_MORE, test_slash_beast_more },
};
const u32 c_test_group_count = COUNT(c_test_groups);
#ifndef MMX4_SATURN
#define PSX_MUSIC_AND_POSE_CASES (20 + 36 + COUNT(beast_poses))
#else
#define PSX_MUSIC_AND_POSE_CASES 0
#endif
const u32 c_test_count = 72 + 21 + 12 + 8 + 4 + 48 + 78 + 20 + 20 + 8 + 96 + COUNT(beast_decisions) * 4 + 60 + 36 + 8 + COUNT(beast_scenes) * 4 + COUNT(slash_beast_patterns_cases) + COUNT(slash_beast_states_cases) + 1 + COUNT(slash_beast_death_flash_cases) + 20 + 8 + 32 + 18 + 12 + PSX_MUSIC_AND_POSE_CASES + 45 + 112 + SLASH_BEAST_MORE;
