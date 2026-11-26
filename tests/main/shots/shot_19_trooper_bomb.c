#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_19_trooper_bomb.h"

static u32 tbomb_frames[0x40], tbomb_pages[0x40];
#define TBOMB(st, timer, frame, setup) (SHOT_FLIGHT(st, 0, (memset(misc_objects, 0, sizeof(misc_objects)), memset(&engine_obj, 0, sizeof(engine_obj)), TEST_MENU_FRAMES = (u8*)tbomb_frames, D_801406A8 = tbomb_pages, sf.unk84.value = timer, WEAPON_FRAME_COUNTER = frame, setup)), trooper_bomb_update(&sf), state_extra = (u8)sf.unk84.value | (u32)shot_flight_owner.unk1C.bytes[0] << 8 | (u32)misc_objects[0].active << 16 | (u32)sf.on_screen << 24)
static void tbomb_init(void)
{
    TBOMB(0, 0, 0, state_terrain(0));
}
static void tbomb_lands(void) { TBOMB(1, 0, 0, sf.unk70 = 8); }
static void tbomb_falls(void) { TBOMB(1, 0, 0, 0); }
static void tbomb_burst_debris(void) { TBOMB(2, 0x40, 8, 0); }
static void tbomb_burst_smoke(void) { TBOMB(2, 0x30, 8, 0); }
static void tbomb_flags_owner(void) { TBOMB(2, 0x21, 3, 0); }
static void tbomb_burns_out(void) { TBOMB(2, 1, 3, 0); }
static void tbomb_despawn(void) { TBOMB(3, 0, 0, 0); }
static void (*const tbomb_cases[])(void) = {
    tbomb_init,
    tbomb_lands,
    tbomb_falls,
    tbomb_burst_debris,
    tbomb_burst_smoke,
    tbomb_flags_owner,
    tbomb_burns_out,
    tbomb_despawn,
};
static const u32 tbomb_expected[] = {
    0x1u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0xFFFE4000u,
    0x1F000u,
    0x200000u,
    0x50000u,
    0x1000000u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x40u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1000000u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x41003Fu,
    0x41002100u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2Fu,
    0x2100u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x120u,
    0x0u,
    0x3u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
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
static u32 test_tbomb(u32 row)
{
    return object_run(tbomb_cases[row], row, &tbomb_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "trooper_bomb_states", 0, 0, COUNT(tbomb_cases), test_tbomb },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tbomb_cases);
