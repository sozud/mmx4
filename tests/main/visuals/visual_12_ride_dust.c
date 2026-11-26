#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_12_ride_dust.h"

static struct PlayerObj dust_armor;
#define rd state_room.visual
#define RDUST(st, setup) (state_reset(0, 0, 0), memset(&dust_armor, 0, sizeof(dust_armor)), dust_armor.state = 1, dust_armor.x_pos.i.hi = 0x90, dust_armor.y_pos.i.hi = 0x70, rd.active = 1, rd.state = st, rd.unk2 = 5, rd.unk50 = &dust_armor, rd.animation_step.fields.relative_step = 1, setup, ride_dust_update(&rd), state_extra = rd.unk17, rd.unk50 = NULL)
static void rdust_init(void)
{
    RDUST(0, 0);
}
static void rdust_follows(void) { RDUST(1, 0); }
static void rdust_ends(void) { RDUST(1, rd.animation_step.fields.relative_step = -1); }
static void rdust_armor_gone(void) { RDUST(1, dust_armor.state = 2); }
static void rdust_despawn(void) { RDUST(2, 0); }
static void (*const rdust_cases[])(void) = {
    rdust_init,
    rdust_follows,
    rdust_ends,
    rdust_armor_gone,
    rdust_despawn,
};
static const u32 rdust_expected[] = {
    0x1u,
    0xFF000501u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x16u,
    0x0u,
    0x1u,
    0x501u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x2u,
    0x501u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x2u,
    0x501u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_rdust(u32 row)
{
    return object_run(rdust_cases[row], row, &rdust_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_dust_states", 0, 0, COUNT(rdust_cases), test_rdust },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rdust_cases);
