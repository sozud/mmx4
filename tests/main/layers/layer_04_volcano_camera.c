#include "test_runtime.h"
#include "main/layers/layer_04_volcano_camera.h"

static struct LayerObj vc;
static u32 volcano(u8 state, u8 section, u8 unk6, s16 player_x)
{
    memset(&vc, 0, sizeof(vc));
    memset(background_objects, 0, sizeof(background_objects));
    vc.active = 1;
    vc.id = 4;
    vc.state = state;
    vc.unk5 = section;
    vc.unk6 = unk6;
    vc.bg_offset = section;
    g_Player.x_pos.i.hi = player_x;
    volcano_camera_update(&vc);
    return vc.unk5 | (u32)vc.unk6 << 8 | (u32)(u8)vc.bg_offset << 16 | (u32)vc.state << 24;
}
static u32 vc_start(void)
{
    u32 seen = volcano(0, 0, 0, 0x8CF);
    assert(background_objects[0].unk2E == 0xA0 && background_objects[0].unk2C == 0x50);
    return seen;
}
static u32 vc_left_settled(void) { return volcano(1, 0, 1, 0x8CF); }
static u32 vc_right_enter(void) { return volcano(1, 0, 1, 0x8D0); }
static u32 vc_right_settled(void) { return volcano(1, 1, 1, 0x8D0); }
static const CTestCase volcano_camera_sections_cases[] = {
    vc_start,
    vc_left_settled,
    vc_right_enter,
    vc_right_settled,
};
static const u32 volcano_camera_sections_cases_expected[] = { 0x1000100u, 0x1000002u, 0x1010101u, 0x1010002u };

const struct CTestGroup c_test_groups[] = {
    { "volcano_camera_sections", volcano_camera_sections_cases, volcano_camera_sections_cases_expected, COUNT(volcano_camera_sections_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(volcano_camera_sections_cases);
