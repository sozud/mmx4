#include "test_runtime.h"
#include "main/layers/layer_01_jungle_parallax.h"

static struct LayerObj jp;
static u32 parallax(u8 state, u8 section, u8 unk6, s16 player_x, s16 player_y)
{
    memset(&jp, 0, sizeof(jp));
    memset(background_objects, 0, sizeof(background_objects));
    jp.active = 1;
    jp.id = 1;
    jp.state = state;
    jp.unk5 = section;
    jp.unk6 = unk6;
    jp.bg_offset = section;
    g_Player.x_pos.i.hi = player_x;
    g_Player.y_pos.i.hi = player_y;
    background_objects[0].x_pos.i.hi = 0x500;
    background_objects[0].y_pos.i.hi = 0x480;
    background_objects[1].unk40 = 0x100;
    background_objects[1].unk42 = 8;
    jungle_parallax_update(&jp);
    return jp.unk5 | (u32)jp.unk6 << 8 | (u32)(u8)jp.bg_offset << 16 | (u32)background_objects[1].unk4 << 24;
}
#define LAYER_POS() ((u16)background_objects[1].x_pos.i.hi | (u32)(u16)background_objects[1].y_pos.i.hi << 16)
static u32 jp_start(void)
{
    u32 seen = parallax(0, 0, 0, 0x100, 0x100);
    assert(jp.state == 1 && background_objects[1].unk40 == 0x28);
    return seen;
}
static u32 jp_upper_scroll(void)
{
    parallax(1, 0, 1, 0x100, 0x100);
    assert(jp.unk6 == 1 && background_objects[1].unk40 == 0x100);
    return LAYER_POS();
}
static u32 jp_lower_enter(void)
{
    u32 seen = parallax(1, 0, 1, 0x9FF, 0x201);
    assert(background_objects[1].unk40 == 0x200);
    return seen;
}
static u32 jp_lower_stay(void) { return parallax(1, 1, 1, 0x9FF, 0x201); }
static u32 jp_far_enter(void)
{
    u32 seen = parallax(1, 1, 1, 0xA00, 0x201);
    assert(background_objects[1].unk40 == 0xB60);
    return seen;
}
static u32 jp_far_scroll(void)
{
    parallax(1, 2, 1, 0xA00, 0x201);
    return LAYER_POS();
}
static const CTestCase jungle_parallax_sections_cases[] = {
    jp_start,
    jp_upper_scroll,
    jp_lower_enter,
    jp_lower_stay,
    jp_far_enter,
    jp_far_scroll,
};
static const u32 jungle_parallax_sections_cases_expected[] = { 0x5000100u, 0x4800880u, 0x2010101u, 0x10003u, 0x5020102u, 0x4A8FDB8u };

const struct CTestGroup c_test_groups[] = {
    { "jungle_parallax_sections", jungle_parallax_sections_cases, jungle_parallax_sections_cases_expected, COUNT(jungle_parallax_sections_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jungle_parallax_sections_cases);
