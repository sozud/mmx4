#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/layers/layer_07_space_port_parallax.h"

static struct LayerObj parallax;
#define PARALLAX(drift) (state_reset(0, 0, 0), memset(&parallax, 0, sizeof(parallax)), parallax.active = 1, parallax.state = 1, background_objects[0].x_pos.val = 0x1000000, background_objects[0].unk14.val = 0x1400000 - drift, background_objects[0].y_pos.val = 0x300000, background_objects[1].x_pos.val = 0x800000, space_port_parallax_update(&parallax), state_extra = background_objects[1].x_pos.val ^ background_objects[1].y_pos.val)
static void spp_scroll(void)
{
    PARALLAX(0);
}
static void spp_scroll_back(void) { PARALLAX(0x800000); }

static void (*const space_port_parallax_states_cases[])(void) = {
    spp_scroll,
    spp_scroll_back,
};
static const u32 space_port_parallax_states_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x900000u, 0u };

static u32 test_space_port_parallax_states(u32 row)
{
    return object_run(space_port_parallax_states_cases[row], row, &space_port_parallax_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "space_port_parallax_states", 0, 0, COUNT(space_port_parallax_states_cases), test_space_port_parallax_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(space_port_parallax_states_cases);
