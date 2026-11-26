#include "test_runtime.h"
#include "main/mains/main_59_timed_explosion.h"

static const u32 timed_explosion_explode_expected[] = { 1u };
static u32 test_timed_explosion_explode(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.animation_step.fields.relative_step = -128;
    timed_explosion_explode(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, timed_explosion_explode_expected, 1);
}

#include "support/state_cases.h"
#include "support/sound_probe.h"
void timed_explosion_wait(struct MainObj*);
#define TE(st, setup) (state_reset(0, 0, 0), state_terrain(0), g_Player.unk68 = NULL, TEST_SPRITE_FRAMES = (u8*)state_sprite_frames, so.active = 0x41, so.state = st, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, sound_probe_begin_group(0), setup)
static void te_fuse(void) { TE(1, so.unk7C = 2), timed_explosion_wait(&so), state_extra = (u16)so.unk7C; }
static void te_blow_even(void) { TE(1, (so.unk7C = 1, cur_random = 0)), timed_explosion_wait(&so), SOUND_CHECK(sound_probe_id() == 1), so.unk42 = so.unk42 == OBJECT_CLUT(0x788F); }
static void te_blow_odd(void) { TE(1, (so.unk7C = 1, cur_random = 1)), timed_explosion_wait(&so), SOUND_CHECK(sound_probe_id() == 0), so.unk42 = so.unk42 == OBJECT_CLUT(0x788F); }
static void te_explode_on_screen(void) { TE(2, 0), timed_explosion_explode(&so); }
static void te_explode_off_screen(void) { TE(2, so.x_pos.i.hi = 0x300), timed_explosion_explode(&so); }
static void (*const timed_explosion_states_cases[])(void) = {
    te_fuse,
    te_blow_even,
    te_blow_odd,
    te_explode_on_screen,
    te_explode_off_screen,
};
static const u32 timed_explosion_states_expected[] = {
    0x0u, 0x1u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x41000000u,
    0x0u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x10002u, 0x2u, 0x0u, 0x41000000u,
    0x0u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x10002u, 0x2u, 0x0u, 0x41000000u,
    0x0u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x0u, 0x0u, 0x3000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
};
static u32 test_timed_explosion_states(u32 row)
{
    return state_run(timed_explosion_states_cases[row], row, &timed_explosion_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "timed_explosion_explode", 0, 0, 1, test_timed_explosion_explode },
    { "timed_explosion_states", 0, 0, COUNT(timed_explosion_states_cases), test_timed_explosion_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(timed_explosion_states_cases);
