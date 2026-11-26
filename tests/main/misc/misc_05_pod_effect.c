#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_05_pod_effect.h"

static struct MainObj pod_owner;
#define pm state_room.misc
#define POD(st, kind, setup) (state_reset(0, 0, 0), memset(&pod_owner, 0, sizeof(pod_owner)), pod_owner.active = 1, pm.active = 1, pm.state = st, pm.unk2 = kind, pm.ext.misc_5.owner = &pod_owner, pm.ext.misc_5.animation = 3, pm.x_pos.i.hi = 0x80, pm.y_pos.i.hi = 0x60, pm.animation_step.fields.relative_step = 1, setup, pod_effect_update(&pm), state_extra = pm.unk17 | (u32)pm.on_screen << 8)
static void pod_launch_init(void)
{
    POD(0, 0, 0);
}
static void pod_rising(void) { POD(1, 0, pm.y_vel.val = -0x40000); }
static void pod_peak(void) { POD(1, 0, (pm.y_vel.val = 0x6000, pm.unk2C = 0x6000)); }
static void pod_owner_gone(void) { POD(1, 0, (pm.y_vel.val = -0x40000, *(s32*)& pod_owner = 0)); }
static void pod_launch_despawn(void) { POD(2, 0, 0); }
static void pod_init(void) { POD(3, 0, 0); }
static void pod_plays(void) { POD(4, 0, 0); }
static void pod_event(void) { POD(4, 0, pm.animation_step.fields.event = 1); }
static void pod_ends(void) { POD(4, 0, pm.animation_step.fields.relative_step = -1); }
static void pod_follows_grounded(void) { POD(4, 1, pod_owner.state = 1); }
static void pod_owner_airborne(void) { POD(4, 1, pod_owner.air_state = 1); }
static void pod_owner_moves_on(void) { POD(4, 1, pod_owner.state = 2); }
static void pod_despawn(void) { POD(5, 0, 0); }
static void (*const pod_cases[])(void) = {
    pod_launch_init,
    pod_rising,
    pod_peak,
    pod_owner_gone,
    pod_launch_despawn,
    pod_init,
    pod_plays,
    pod_event,
    pod_ends,
    pod_follows_grounded,
    pod_owner_airborne,
    pod_owner_moves_on,
    pod_despawn,
};
static const u32 pod_expected[] = {
    0x1u,
    0xFF000001u,
    0x800000u,
    0x57C000u,
    0x0u,
    0x84000u,
    0x600000u,
    0x50000u,
    0xFu,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x640000u,
    0x0u,
    0xFFFC0000u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x5FA000u,
    0x0u,
    0x0u,
    0x600000u,
    0x40000u,
    0x100u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x640000u,
    0x0u,
    0xFFFC0000u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x4u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x3u,
    0x0u,
    0x4u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x5u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x5u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x4u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x5u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x5u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_pod(u32 row)
{
    return object_run(pod_cases[row], row, &pod_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "pod_effect_states", 0, 0, COUNT(pod_cases), test_pod },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pod_cases);
