#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/quads/quad_14_colonel_beam.h"

struct colonel_beam_widen_case {
    u32 v_2_x_hi, v_3_x_hi;
    u32 expected[5];
};
static const struct colonel_beam_widen_case colonel_beam_widen_cases[] = {
    { 6, -62, { 0u, 3u, 0xFFFFFFFDu, 0u, 0xFFFFFFC8u } },
    { -2170, 32762, { 1u, 3u, 0xFFFFFFFDu, 0xFFFFF780u, 0xFFFF8000u } },
};
static u32 test_colonel_beam_widen(u32 row)
{
    const struct colonel_beam_widen_case* c = &colonel_beam_widen_cases[row];
    u32 observed_values[5];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.vertices[2].x.i.hi = c->v_2_x_hi;
    obj.vertices[3].x.i.hi = c->v_3_x_hi;
    colonel_beam_widen(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.vertices[0].x.i.hi;
    observed_values[2] = (u32)obj.vertices[1].x.i.hi;
    observed_values[3] = (u32)obj.vertices[2].x.i.hi;
    observed_values[4] = (u32)obj.vertices[3].x.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static struct QuadObj cb;
static struct ShotObj cb_shot;
static void cb_reset(u8 state, u8 step)
{
    memset(&cb, 0, sizeof(cb));
    memset(&cb_shot, 0, sizeof(cb_shot));
    memset(background_objects, 0, sizeof(background_objects));
    g_Player.x_pos.val = 0x100 * 65536 + 0x8000;
    g_Player.bg_offset = 0;
    cb_shot.x_pos.val = 0x180 * 65536;
    cb.state = state;
    cb.unk5 = step;
    cb.unk5C = (struct PlayerObj*)&cb_shot;
    background_objects[0].y_pos.i.hi = 0x40;
}
#define CB_SEEN() (cb.state | (u32)cb.unk5 << 8 | (u32)(u16)cb.vertices[0].x.i.hi << 16)
static u32 cb_place_player(void)
{
    cb_reset(0, 3);
    colonel_beam_update(&cb);
    assert(cb.vertices[1].x.val == cb.vertices[0].x.val + 0x20000 && cb.vertices[3].y.val == 0x10000 && cb.active == (s8)0x93);
    return CB_SEEN();
}
static u32 cb_place_shot(void)
{
    cb_reset(0, 3);
    cb.unk2 = 1;
    colonel_beam_update(&cb);
    return CB_SEEN();
}
static u32 cb_drop(u16 y)
{
    cb_reset(1, 0);
    cb.vertices[2].y.i.hi = cb.vertices[3].y.i.hi = y;
    colonel_beam_update(&cb);
    assert(cb.vertices[3].y.i.hi == (s16)(y + 0x10) && cb.on_screen == 1);
    return CB_SEEN() | (u32)(u8)cb.vertices[2].y.i.hi << 24;
}
static u32 cb_drop_bottom(void) { return cb_drop(0x40 + 0xC8 - 0x10); }
static u32 cb_drop_falling(void) { return cb_drop(0x40); }
static u32 cb_widen(s16 v2, s16 v3)
{
    cb_reset(1, 1);
    cb.vertices[2].x.i.hi = v2;
    cb.vertices[3].x.i.hi = v3;
    colonel_beam_update(&cb);
    return CB_SEEN() | (u32)(u8)(cb.vertices[3].x.i.hi - cb.vertices[2].x.i.hi) << 24;
}
static u32 cb_widen_full(void) { return cb_widen(0, 100); }
static u32 cb_widen_more(void) { return cb_widen(0, 10); }
static u32 cb_hold(u8 shot_step)
{
    cb_reset(1, 2);
    cb_shot.unk7 = shot_step;
    colonel_beam_update(&cb);
    return CB_SEEN();
}
static u32 cb_hold_end(void) { return cb_hold(8); }
static u32 cb_holding(void) { return cb_hold(7); }
static const CTestCase colonel_beam_paths_cases[] = {
    cb_place_player,
    cb_place_shot,
    cb_drop_bottom,
    cb_drop_falling,
    cb_widen_full,
    cb_widen_more,
    cb_hold_end,
    cb_holding,
};
static const u32 colonel_beam_paths_cases_expected[] = { 0x00FF0001u, 0x017F0001u, 0x08000101u, 0x50000001u, 0x70030201u, 0x16030101u, 0x00000202u, 0x00000201u };

const struct CTestGroup c_test_groups[] = {
    { "colonel_beam_widen", 0, 0, 2, test_colonel_beam_widen },
    { "colonel_beam_paths", colonel_beam_paths_cases, colonel_beam_paths_cases_expected, COUNT(colonel_beam_paths_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + COUNT(colonel_beam_paths_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
