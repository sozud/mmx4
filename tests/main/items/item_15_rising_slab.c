#include "test_runtime.h"
#include "main/items/item_15_rising_slab.h"
#include "support/state_cases.h"
void rising_slab_rise(struct ItemObj*);

#define rs state_room.item
#define RS(t, setup) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), rs.active = 1, rs.id = 0xF, rs.state = 1, rs.x_pos.i.hi = 0x80, rs.y_pos.i.hi = 0x60, rs.unk7C.timer = t, g_Player.unk68 = NULL, setup, rising_slab_rise(&rs), state_extra = rs.unk7C.timer | (u32)rs.ext.packed << 8 | (u32)(u8)background_objects[0].unk36 << 16)
static void rs_shake(void) { RS(7, 0); }
static void rs_shake_panning(void) { RS(7, (background_objects[0].unk34 = 0x10, background_objects[0].unk3E.bytes[0] = 1)); }
static void rs_quiet_panning(void) { RS(7, (background_objects[0].unk34 = 0x10, background_objects[0].unk3E.bytes[0] = 2)); }
static void rs_climb_capped(void) { RS(0, (rs.y_vel.val = -0x18000, rs.unk2C = 0x100)); }
static void rs_gone(void) { RS(0, rs.y_pos.i.hi = -0x100); }

static void (*const rising_slab_states_cases[])(void) = {
    rs_shake,
    rs_shake_panning,
    rs_quiet_panning,
    rs_climb_capped,
    rs_gone,
};
static const u32 rising_slab_states_expected[] = {
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x80108u, 0x2100u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x80108u, 0x2100u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x108u, 0x2100u,
    0x1u, 0x1u, 0x800000u, 0x618000u, 0x0u, 0xFFFF0000u, 0x0u, 0x50000u, 0x1u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0xFF000000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1u, 0x0u,
};
static u32 test_rising_slab_states(u32 row)
{
    return object_run(rising_slab_states_cases[row], row, &rising_slab_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "rising_slab_states", 0, 0, COUNT(rising_slab_states_cases), test_rising_slab_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rising_slab_states_cases);
