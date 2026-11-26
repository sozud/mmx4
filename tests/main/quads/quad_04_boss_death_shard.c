#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/quads/quad_04_boss_death_shard.h"

static struct QuadObj shard;
#define SHARD(st, dir, timer_, setup) (state_reset(0, 0, 0), memset(&shard, 0, sizeof(shard)), cur_random = 0x1234, shard.active = 1, shard.state = st, shard.unk2 = dir, shard.ext.quad_4.unk38 = dir, shard.ext.quad_4.unk39 = 1, shard.ext.quad_4.timer = timer_, setup, boss_death_shard_update(&shard), state_extra = shard.state | (u32)shard.ext.quad_4.timer << 8 | (u32)shard.ext.quad_4.unk39 << 16 | (u32)shard.active << 24, so.x_pos.val = shard.vertices[1].x.val, so.y_pos.val = shard.vertices[1].y.val, state_room.shot.x_vel.val = shard.vertices[2].x.val, state_room.shot.y_vel.val = shard.vertices[2].y.val)
static void shard_init(void)
{
    SHARD(0, 3, 0, 0);
}
static void shard_shape(void) { SHARD(1, 3, 0, 0); }
static void shard_shape_mirrored(void) { SHARD(1, 0x13, 0, 0); }
static void shard_flies(void) { SHARD(2, 3, 2, 0); }
static void shard_lands(void) { SHARD(2, 3, 0, 0); }
static void shard_despawn(void) { SHARD(3, 3, 0, 0); }
static void (*const shard_cases[])(void) = {
    shard_init,
    shard_shape,
    shard_shape_mirrored,
    shard_flies,
    shard_lands,
    shard_despawn,
};
static const u32 shard_expected[] = {
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x83010001u,
    0x0u,
    0x0u,
    0x0u,
    0x6B0000u,
    0x940000u,
    0x660000u,
    0x710000u,
    0x0u,
    0x50000u,
    0x1010102u,
    0x0u,
    0x0u,
    0x0u,
    0xFF950000u,
    0xFF6C0000u,
    0xFF9A0000u,
    0xFF8F0000u,
    0x0u,
    0x50000u,
    0x1010102u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1010102u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x101FF03u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
};
static u32 test_shard(u32 row)
{
    return object_run(shard_cases[row], row, &shard_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "boss_death_shard_states", 0, 0, COUNT(shard_cases), test_shard },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(shard_cases);
