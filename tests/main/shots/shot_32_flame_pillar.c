#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_32_flame_pillar.h"

static u32 pillar_frames[0x40], pillar_pages[0x40];
#define PILLAR(st, kind, setup) (SHOT_FLIGHT(st, 0, (memset(&engine_obj, 0, sizeof(engine_obj)), TEST_MENU_FRAMES = (u8*)pillar_frames, D_801406A8 = pillar_pages, sf.unk2 = kind, sf.animation_step.fields.relative_step = 1, setup)), flame_pillar_update(&sf))
static void pillar_init_near(void)
{
    PILLAR(0, 0, 0);
}
static void pillar_init_far(void) { PILLAR(0, 1, 0); }
static void pillar_burns(void) { PILLAR(1, 0, 0); }
static void pillar_ends(void) { PILLAR(1, 0, sf.animation_step.fields.relative_step = -1); }
static void pillar_despawn(void) { PILLAR(2, 0, 0); }
static void (*const pillar_cases[])(void) = {
    pillar_init_near,
    pillar_init_far,
    pillar_burns,
    pillar_ends,
    pillar_despawn,
};
static const u32 pillar_expected[] = {
    0x1u,
    0xFF000001u,
    0xA00000u,
    0x780000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u | VISUAL_STAGE_PALETTE(14),
    0x0u,
    0x0u,
    0x1u,
    0xFF000101u,
    0xC00000u,
    0x780000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u | VISUAL_STAGE_PALETTE(14),
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
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
static u32 test_pillar(u32 row)
{
    return object_run(pillar_cases[row], row, &pillar_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "flame_pillar_states", 0, 0, COUNT(pillar_cases), test_pillar },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pillar_cases);
