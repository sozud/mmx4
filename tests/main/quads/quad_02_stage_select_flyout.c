#include "test_runtime.h"
#include "main/quads/quad_02_stage_select_flyout.h"

struct stage_select_flyout_wait_case {
    u32 unk7;
    u32 expected[2];
};
static const struct stage_select_flyout_wait_case stage_select_flyout_wait_cases[] = {
    { 0, { 0u, 0u } },
    { -1, { 0u, 0xFFFFFFFEu } },
};
static u32 test_stage_select_flyout_wait(u32 row)
{
    const struct stage_select_flyout_wait_case* c = &stage_select_flyout_wait_cases[row];
    u32 observed_values[2];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7 = c->unk7;
    stage_select_flyout_wait(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

extern s16 stage_select_flyout_targets[8][2];
extern s32 stage_select_flyout_vertices[4][2];
static u32 flyout(u32 row)
{
    struct QuadObj obj, expected;
    struct EngineObj engine_before = engine_obj;
    struct GameInfo info_before = game_info;
    struct BackgroundObj backgrounds_before[3];
    u32 target = row % 8, side = row / 8 % 2, crossed = row / 16 % 2, scale = row / 32, i;
    s32 x = 40 + 80 * (target % 4), y = target < 4 ? 16 : 224, direction = side ? 16 : 0;
    memset(&obj, 0, sizeof(obj));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x81;
    obj.id = 2;
    obj.state = 1;
    obj.unk2 = target;
    obj.bg_offset = -1;
    obj.x_pos.val = (x + (side ? 1 : -1) * (crossed ? 1 : 64)) * 65536 + 0x1234;
    obj.y_pos.val = y * 65536;
    obj.ext.quad_2.vertices = &stage_select_flyout_vertices[0][0];
    obj.ext.quad_2.x_scale.value = 0x100 + 0x40 * scale;
    obj.ext.quad_2.y_scale.value = 0x100 + 0x40 * scale;
    obj.ext.quad_2.direction[0] = direction ^ (crossed ? 16 : 0);
    expected = obj;
    expected.x_pos.val += side ? -0x28000 : 0x28000;
    expected.ext.quad_2.direction[1] = direction;
    expected.ext.quad_2.x_scale.value += 12;
    expected.ext.quad_2.y_scale.value += 12;
    if (crossed) {
        expected.x_pos.i.hi = x;
        expected.y_pos.i.hi = y;
        expected.state = 2;
        expected.unk7 = 60;
    }
    for (i = 0; i < 4; i++) {
        expected.vertices[i].x.val = (i == 0 || i == 3 ? -3840 : 3840) * expected.ext.quad_2.x_scale.value;
        expected.vertices[i].y.val = (i < 2 ? -1792 : 1792) * expected.ext.quad_2.y_scale.value;
    }
    expected.on_screen = crossed || (side ? x + 64 < 335 : x - 64 > -16);
    assert(stage_select_flyout_targets[target][0] == x && stage_select_flyout_targets[target][1] == y);
    stage_select_flyout_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&game_info, &info_before, sizeof(game_info));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "stage_select_flyout_wait", 0, 0, 2, test_stage_select_flyout_wait },
    { "flyout_all_targets_cardinal_crossings_and_scales", NULL, NULL, 64, flyout },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 64;
