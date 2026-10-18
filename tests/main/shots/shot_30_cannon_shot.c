#include "test_runtime.h"
#include "main/shots/shot_30_cannon_shot.h"

static const u32 cannon_shot_spawn_flash_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_cannon_shot_spawn_flash(u32 row)
{
    u32 observed_values[10];
    struct ShotObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    cannon_shot_spawn_flash(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, cannon_shot_spawn_flash_expected, 10);
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_shot_spawn_flash", 0, 0, 1, test_cannon_shot_spawn_flash },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
