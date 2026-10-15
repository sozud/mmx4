#include "test_runtime.h"
extern void* light_capsule_animations[14];

static u32 light_case(u32 mode)
{
    struct MiscObj obj, expected;
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memcpy(background_before, background_objects, sizeof(background_before));
    obj.active = 0x41;
    obj.id = 51;
    obj.state = 1;
    obj.unk2 = 3;
    obj.unk5 = 3;
    obj.unk6 = mode;
    obj.bg_offset = -1;
    obj.unk16 = 7;
    obj.unk17 = 0;
    obj.previous_animation_index = 6;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)light_capsule_animations;
    obj.animation_cursor = light_capsule_animations[9];
    obj.animation_step = *(union AnimationStep*)obj.animation_cursor;
    expected = obj;
    expected.on_screen = 1;
    if (mode == 0) {
        expected.unk16 = 1;
        expected.unk17 = 9;
        expected.previous_animation_index = 0xFF;
        expected.unk6 = 1;
    } else {
        expected.animation_cursor++;
        expected.animation_step = *(union AnimationStep*)expected.animation_cursor;
    }
    capsule_part_light(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(((u32*)light_capsule_animations[9])[0] == 0x2C010001 && ((u32*)light_capsule_animations[9])[1] == 0x2D010001);
    return obj.animation_step.packed ^ ((u32)(u8)obj.unk16 << 8) ^ ((u32)(u8)obj.unk17 << 16);
}
#define CASE(m)                                              \
    static u32 capsule_light_animation_start_light_##m(void) \
    {                                                        \
        return light_case(m);                                \
    }
CASE(0)
CASE(1)
static const CTestCase capsule_light_animation_start_cases[] = { capsule_light_animation_start_light_0, capsule_light_animation_start_light_1 };
static const u32 capsule_light_animation_start_cases_expected[] = { 0x2C080101u, 0x2D010701u };
#undef CASE

static const u32 capsule_part_light_expected[] = { 0u, 0xFFFFFFFFu };
static u32 test_capsule_part_light(u32 row)
{
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk6 = -1;
    capsule_part_light(&obj);
    observed_values[0] = (u32)obj.unk16;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, capsule_part_light_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "capsule_light_animation_start", capsule_light_animation_start_cases, capsule_light_animation_start_cases_expected, COUNT(capsule_light_animation_start_cases), 0 },
    { "capsule_part_light", 0, 0, 1, test_capsule_part_light },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(capsule_light_animation_start_cases) + 1;
