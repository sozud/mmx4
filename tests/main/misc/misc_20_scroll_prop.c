#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_20_scroll_prop.h"

static struct LayerObj prop_owner;
static u32 prop_frames[4], prop_pages[4];
#define pr state_room.misc
#define PROP(st, speed, px, setup) (state_reset(0, 0, 0), memset(&prop_owner, 0, sizeof(prop_owner)), TEST_MENU_FRAMES = (u8*)prop_frames, D_801406A8 = prop_pages, prop_owner.unk18.val = speed, prop_owner.private_state.misc_20_active = 1, g_Player.x_pos.i.hi = px, pr.active = 1, pr.state = st, pr.x_pos.i.hi = 0x80, pr.y_pos.i.hi = 0x60, pr.ext.misc_20.owner = &prop_owner, setup, scroll_prop_update(&pr), state_extra = prop_owner.private_state.misc_20_active | (u32)pr.on_screen << 8)
static void prop_init(void) { PROP(0, 0, 0, 0); }
static void prop_drifts_in_range(void) { PROP(1, 0x8000, 0x1800, 0); }
static void prop_still_on_screen(void) { PROP(1, 0, 0x100, 0); }
static void prop_past_range_off_screen(void) { PROP(1, 0, 0x2000, pr.x_pos.i.hi = 0x200); }
static void prop_despawn(void) { PROP(2, 0, 0, 0); }
static void (*const prop_cases[])(void) = {
    prop_init,
    prop_drifts_in_range,
    prop_still_on_screen,
    prop_past_range_off_screen,
    prop_despawn,
};
static const u32 prop_expected[] = {
    0x1u, 0x1u, 0x1600000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u | OBJECT_CLUT(0x7987), 0x1u, 0x0u,
    0x1u, 0x1u, 0x7E8000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x101u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x101u, 0x0u,
    0x2u, 0x1u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_prop(u32 row)
{
    return object_run(prop_cases[row], row, &prop_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "scroll_prop_states", 0, 0, COUNT(prop_cases), test_prop },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(prop_cases);
