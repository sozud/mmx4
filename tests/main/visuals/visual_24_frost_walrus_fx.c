#include "test_runtime.h"
#include "main/visuals/visual_24_frost_walrus_fx.h"
#include "support/state_cases.h"
void frost_walrus_fx_blizzard(struct VisualObj*);
void frost_walrus_fx_breath_start(struct VisualObj*);

#define sv state_room.visual
#define FX(sub, setup) (state_reset(0, sub, 0), sv.active = 1, sv.state = 1, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, cur_random = 0x1234, setup, frost_walrus_fx_blizzard(&sv))
static void fwf_blizzard_left(void)
{
    FX(0, 0);
}
static void fwf_blizzard_right(void) { FX(0, sv.unk15 = PLAYER_FACING_RIGHT); }
static void fwf_blizzard_drift(void) { FX(1, (sv.x_vel.val = 0x10000, sv.animation_step.fields.relative_step = 1)); }
static void fwf_blizzard_end(void) { FX(1, sv.animation_step.fields.relative_step = 0); }
static void fwf_breath_left(void)
{
    state_reset(0, 0, 0);
    cur_random = 0x1234;
    frost_walrus_fx_breath_start(&sv);
}
static void fwf_breath_right(void)
{
    state_reset(0, 0, 0);
    cur_random = 0x1234;
    sv.unk15 = PLAYER_FACING_RIGHT;
    frost_walrus_fx_breath_start(&sv);
}

static struct MainObj fwf_source;
#define UPD(mode, sub, setup) (state_reset(mode, sub, 0), memset(&fwf_source, 0, sizeof(fwf_source)), fwf_source.x_pos.i.hi = 0x90, fwf_source.y_pos.i.hi = 0x70, fwf_source.unk42 = (s16)0x8123, fwf_source.unk15 = PLAYER_FACING_RIGHT, fwf_source.animation_table = state_table, sv.active = 1, sv.state = 1, sv.unk50 = (struct PlayerObj*)&fwf_source, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, sv.x_vel.val = 0x10000, g_Player.update_delay = 0, setup, frost_walrus_fx_update(&sv), state_extra = sv.unk17)
#define LIVE (sv.animation_step.fields.relative_step = 1)
static void fwf_init_breath(void)
{
    UPD(0, 0, (sv.state = 0, sv.unk2 = 0x13));
}
static void fwf_burst_down(void) { UPD(0, 0, 0); }
static void fwf_burst_up(void) { UPD(0, 0, sv.unk2 = 1); }
static void fwf_burst_right(void) { UPD(0, 0, sv.unk2 = 2); }
static void fwf_burst_left(void) { UPD(0, 0, sv.unk2 = 3); }
static void fwf_burst_other(void) { UPD(0, 0, sv.unk2 = 4); }
static void fwf_burst_move(void) { UPD(0, 1, LIVE); }
static void fwf_burst_end(void) { UPD(0, 1, 0); }
static void fwf_breath_move(void) { UPD(1, 1, LIVE); }
static void fwf_breath_end(void) { UPD(1, 1, 0); }
static void fwf_regrow(void) { UPD(2, 0, LIVE); }
static void fwf_regrow_end(void) { UPD(2, 0, 0); }
static void fwf_sparkle_follow(void) { UPD(4, 1, sv.unk2 = 1); }
static void fwf_sparkle_end(void) { UPD(4, 1, (sv.unk2 = 2, fwf_source.unk6 = 2)); }
static void fwf_stagger_follow(void) { UPD(5, 1, LIVE); }
static void fwf_stagger_end(void) { UPD(5, 1, 0); }
static void (*const frost_walrus_fx_states_cases[])(void) = {
    fwf_blizzard_left,
    fwf_blizzard_right,
    fwf_blizzard_drift,
    fwf_blizzard_end,
    fwf_breath_left,
    fwf_breath_right,
    fwf_init_breath,
    fwf_burst_down,
    fwf_burst_up,
    fwf_burst_right,
    fwf_burst_left,
    fwf_burst_move,
    fwf_burst_end,
    fwf_breath_move,
    fwf_breath_end,
    fwf_regrow,
    fwf_regrow_end,
    fwf_sparkle_follow,
    fwf_sparkle_end,
    fwf_stagger_follow,
    fwf_stagger_end,
    fwf_burst_other,
};
static const u32 frost_walrus_fx_states_expected[] = {
    0x10001u,
    1u,
    0x800000u,
    0x600000u,
    0xFFFC4000u,
    0x28000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    0x400001u,
    0x800000u,
    0x600000u,
    0x3C000u,
    0x28000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    1u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x10000u,
    0u,
    0u,
    0u,
    0xFFFC4000u,
    0xFFFD8000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10000u,
    0x400000u,
    0u,
    0u,
    0x3C000u,
    0xFFFD8000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x101u,
    0xFF000301u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50123u,
    0x1Du,
    0u,
    0x10001u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0x14000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    0x101u,
    0x800000u,
    0x600000u,
    0u,
    0xFFFEC000u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    0x201u,
    0x800000u,
    0x600000u,
    0x14000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    0x301u,
    0x800000u,
    0x600000u,
    0xFFFEC000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x10001u,
    0x1u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x10101u,
    0x1u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x48123u,
    0u,
    0u,
    0u,
    0u,
    0x800000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x48123u,
    0u,
    0u,
    0x10401u,
    0x101u,
    0x6A0000u,
    0x5A0000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0xBB0000u,
    0x660000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x10501u,
    0x400001u,
    0x900000u,
    0x700000u,
    0x10000u,
    0u,
    0u,
    0x48123u,
    0u,
    0u,
    0u,
    0x400000u,
    0x900000u,
    0x700000u,
    0x10000u,
    0u,
    0u,
    0x48123u,
    0u,
    0u,
    0x10001u,
    0x401u,
    0x800000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
};

static u32 test_frost_walrus_fx_states(u32 row)
{
    return object_run(frost_walrus_fx_states_cases[row], row, &frost_walrus_fx_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "frost_walrus_fx_states", 0, 0, COUNT(frost_walrus_fx_states_cases), test_frost_walrus_fx_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frost_walrus_fx_states_cases);
