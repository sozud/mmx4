#include "test_runtime.h"
void player_hurt_slide(struct PlayerObj*);

static const u32 player_hurt_slide_expected[] = { 0u, 0u };
static u32 test_player_hurt_slide(u32 row)
{
    u32 observed_values[2];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.capsule_state = -1;
    player_hurt_slide(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, player_hurt_slide_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "player_hurt_slide", 0, 0, 1, test_player_hurt_slide },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
