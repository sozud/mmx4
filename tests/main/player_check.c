#include "test_runtime.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/player.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 player_check_wall_jump_expected[] = { 0u };
static u32 test_player_check_wall_jump(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.input_locked = -1;
    obj.pressed_input = 0;
    obj.wall_climbable = 0;
    return_value = player_check_wall_jump(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, player_check_wall_jump_expected, 1);
}

static const u32 player_is_pushing_wall_expected[] = { 0u };
static u32 test_player_is_pushing_wall(u32 row)
{
    u32 observed_values[1];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.input_locked = -1;
    observed_values[0] = (u32)player_is_pushing_wall(&obj);
    return c_test_observe(0, row, observed_values, player_is_pushing_wall_expected, 1);
}

#include "support/player_archive_context.h"
ARCHIVE_CAPSULE(CAPSULE_ANIM_5, 5)
ARCHIVE_CAPSULE(CAPSULE_ANIM_6, 6)
ARCHIVE_CAPSULE(CAPSULE_ANIM_C, 0xC)
ARCHIVE_CAPSULE(CAPSULE_NO_TURN, 0xA)
static const CTestCase player_check_capsule_archive_cases[]
    = {
          CAPSULE_ANIM_5,
          CAPSULE_ANIM_6,
          CAPSULE_ANIM_C,
          CAPSULE_NO_TURN,
          capsule_hurt_blocked,
      };

static const u32 player_check_capsule_archive_cases_expected[] = { 0x40001326u, 0x40001326u, 0x40001326u, 0x4000130Au, 0x101u };
const struct CTestGroup c_test_groups[] = {
    { "player_check_wall_jump", 0, 0, 1, test_player_check_wall_jump },
    { "player_is_pushing_wall", 0, 0, 1, test_player_is_pushing_wall },
    { "player_check_capsule_archive", player_check_capsule_archive_cases, player_check_capsule_archive_cases_expected, COUNT(player_check_capsule_archive_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + COUNT(player_check_capsule_archive_cases);
