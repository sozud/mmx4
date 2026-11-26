#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_27_owner_aura.h"

static struct MainObj aura_owner;
#define am state_room.misc
#define AURA(st, owner_state, steady, timer) (state_reset(0, steady, timer), memset(&aura_owner, 0, sizeof(aura_owner)), aura_owner.state = owner_state, aura_owner.x_pos.i.hi = 0x90, aura_owner.y_pos.i.hi = 0x70, aura_owner.unk15 = PLAYER_FACING_RIGHT, aura_owner.unk42 = 0x1234, am.active = 1, am.state = st, am.on_screen = 1, am.ext.misc_5.owner = &aura_owner, owner_aura_update(&am), state_extra = am.on_screen)
static void aura_owner_hurt(void) { AURA(0, 2, 0, 0); }
static void aura_owner_5(void) { AURA(0, 5, 0, 0); }
static void aura_owner_8(void) { AURA(0, 8, 0, 0); }
static void aura_blink_on(void) { AURA(0, 1, 0, 1); }
static void aura_blink_off(void) { AURA(0, 1, 0, 0); }
static void aura_steady(void) { AURA(0, 1, 1, 0); }
static void aura_despawn(void) { AURA(1, 1, 0, 0); }
static void (*const aura_cases[])(void) = {
    aura_owner_hurt,
    aura_owner_5,
    aura_owner_8,
    aura_blink_on,
    aura_blink_off,
    aura_steady,
    aura_despawn,
};
static const u32 aura_expected[] = {
    0x1u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x1u, 0x0u,
    0x1u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x1u, 0x0u,
    0x1u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x1u, 0x0u,
    0x2000000u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x1u, 0x0u,
    0x1000000u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x0u, 0x0u,
    0x10000u, 0x400001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x41234u, 0x1u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_aura(u32 row)
{
    return object_run(aura_cases[row], row, &aura_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "owner_aura_states", 0, 0, COUNT(aura_cases), test_aura },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(aura_cases);
