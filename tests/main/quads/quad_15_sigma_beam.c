#include "test_runtime.h"
#include "main/quads/quad_15_sigma_beam.h"

struct sigma_beam_sweep_case {
    u32 unk3C, cur_character, pool_0_full;
    u32 expected[7];
};
static const struct sigma_beam_sweep_case sigma_beam_sweep_cases[] = {
    { 1, -1, 0, { 0x46u, 1u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 0, 255, { 0xFFFFu, 0u, 0xFFFFFFFAu, 0xFFFFFFFAu, 1u, 0u, 0u } },
};
static u32 test_sigma_beam_sweep(u32 row)
{
    const struct sigma_beam_sweep_case* c = &sigma_beam_sweep_cases[row];
    u32 observed_values[7];
    struct QuadObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&shot_objects, 0, sizeof(shot_objects));
    obj.ext.unk_ext4.unk3C = c->unk3C;
    engine_obj.cur_character = c->cur_character;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    sigma_beam_sweep(&obj);
    observed_values[0] = (u32)obj.ext.unk_ext4.unk3C;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.vertices[2].x.i.hi;
    observed_values[3] = (u32)obj.vertices[3].x.i.hi;
    observed_values[4] = (u32)shot_objects[0].active;
    observed_values[5] = (u32)shot_objects[0].id;
    observed_values[6] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "sigma_beam_sweep", 0, 0, 2, test_sigma_beam_sweep },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
