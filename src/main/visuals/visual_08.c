// VisualObj, visual_object_update_funcs[8]
// 800B0890..800B1354
#include "common.h"

s8 ice_shard_offsets[4][2] = {
    { 0, -32 },
    { 32, 0 },
    { 0, 32 },
    { -32, 0 },
};

void ice_shard_update(struct VisualObj* arg0)
{
    ice_shard_state_funcs[arg0->state](arg0);
}

// ice_shard_init
INCLUDE_ASM("main/nonmatchings/visuals/visual_08", func_800B08CC);

// ice_shard_main
INCLUDE_ASM("main/nonmatchings/visuals/visual_08", func_800B0B48);

void ice_shard_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void ice_shard_idle(struct VisualObj* arg0)
{
}

// spawn_dust_puffs_at_object
INCLUDE_ASM("main/nonmatchings/visuals/visual_08", func_800B0CA0);

// spawn_dust_puffs_in_rect
INCLUDE_ASM("main/nonmatchings/visuals/visual_08", func_800B10E4);

void (*ice_shard_state_funcs[])(struct VisualObj*) = {
    func_800B08CC,
    func_800B0B48,
    ice_shard_despawn,
    ice_shard_idle,
};
