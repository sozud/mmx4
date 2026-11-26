#include "test_runtime.h"
#include "main/effects/effect_00_camera_trigger.h"
extern u16** camera_trigger_stage_scripts[26];

static struct EffectObj ct;
static u8 ct_marker;
static u32 trigger(u8 state, s16 player_x, s16 player_y, s16 x)
{
    memset(&ct, 0, sizeof(ct));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    background_objects[0].x_pos.i.hi = 0xE80;
    background_objects[0].y_pos.i.hi = 0x100;
    background_objects[0].unk2A = background_objects[0].unk28 = 0x55;
    ct_marker = 0xC5;
    ct.active = 1;
    ct.state = state;
    ct.backref = &ct_marker;
    ct.x_pos.i.hi = x;
    ct.y_pos.i.hi = 0x180;
    if (state != 0)
        ct.ext.unk_effect.unk18 = camera_trigger_stage_scripts[0][0];
    g_Player.x_pos.i.hi = player_x;
    g_Player.y_pos.i.hi = player_y;
    camera_trigger_update(&ct);
    assert(ct.ext.unk_effect.unk18 == (void*)camera_trigger_stage_scripts[0][0]);
    return background_objects[0].unk47 | (u32)(u8)background_objects[0].unk2A << 8 | (u32)(u8)background_objects[0].unk28 << 16 | (u32)ct.state << 24;
}
static u32 ct_start_inside(void)
{
    u32 seen = trigger(0, 0xEF0, 0x1C0, 0xEF8);
    assert(background_objects[0].unk2A == 0x100 && background_objects[0].unk28 == 0x100);
    return seen;
}
static u32 ct_right_of(void) { return trigger(1, 0xF00, 0x180, 0xEF8); }
static u32 ct_left_of(void) { return trigger(1, 0xEEF, 0x180, 0xEF8); }
static u32 ct_below(void) { return trigger(1, 0xEFF, 0x1C1, 0xEF8); }
static u32 ct_above(void) { return trigger(1, 0xEFF, 0xFF, 0xEF8); }
static u32 ct_far(void)
{
    u32 seen = trigger(1, 0xEF8, 0x180, 0x1400);
    assert(ct.active == 0);
    return seen | (u32)ct_marker << 24;
}
static const CTestCase camera_trigger_bounds_cases[] = {
    ct_start_inside,
    ct_right_of,
    ct_left_of,
    ct_below,
    ct_above,
    ct_far,
};
static const u32 camera_trigger_bounds_cases_expected[] = { 0x1000002u, 0x1555500u, 0x1555500u, 0x1555500u, 0x1555500u, 0x40555500u };

const struct CTestGroup c_test_groups[] = {
    { "camera_trigger_bounds", camera_trigger_bounds_cases, camera_trigger_bounds_cases_expected, COUNT(camera_trigger_bounds_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(camera_trigger_bounds_cases);
