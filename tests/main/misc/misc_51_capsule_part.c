#include "test_runtime.h"
#include "main/misc/misc_51_capsule_part.h"
#include "weapon_resources.h"
extern void* light_capsule_animations[14];

static u32 light_case(u32 mode)
{
    struct MiscObj obj, expected;
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before = g_Player;
    u32 i, steps[2];
    memset(&obj, 0, sizeof(obj));
    memcpy(background_before, background_objects, sizeof(background_before));
    obj.active = 0x41;
    obj.id = 51;
    obj.state = 1;
    obj.unk2 = 3;
    obj.unk5 = 3;
    obj.unk6 = mode;
    obj.bg_offset = -1;
    obj.unk16 = VISUAL_SATURN_LAYER(7);
    obj.unk17 = 0;
    obj.previous_animation_index = 6;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)light_capsule_animations;
    obj.animation_cursor = light_capsule_animations[9];
    memcpy(&obj.animation_step, obj.animation_cursor, sizeof(obj.animation_step));
    expected = obj;
    expected.on_screen = 1;
    if (mode == 0) {
        expected.unk16 = VISUAL_SATURN_LAYER(1);
        expected.unk17 = 9;
        expected.previous_animation_index = 0xFF;
        expected.unk6 = 1;
    } else {
        expected.animation_cursor++;
        memcpy(&expected.animation_step, expected.animation_cursor, sizeof(expected.animation_step));
    }
    capsule_part_light(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    memcpy(steps, light_capsule_animations[9], sizeof(steps));
    assert(steps[0] == C_TEST_STEP(0x2C010001) && steps[1] == C_TEST_STEP(0x2D010001));
    return C_TEST_STEP(obj.animation_step.packed) ^ ((u32)(u8)obj.unk17 << 16);
}
static const u32 capsule_light_animation_start_cases_expected[] = { 0x2C080001u, 0x2D010001u };

#include "support/state_cases.h"
void capsule_part_main(struct MiscObj*);
#define sm state_room.misc
static struct MainObj capsule_source;
#define PART(type, sub, setup) (state_reset(type, sub, 0), memset(&capsule_source, 0, sizeof(capsule_source)), capsule_source.active = 0x41, sm.active = 1, sm.state = 1, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.misc_51.source = &capsule_source, setup, capsule_part_main(&sm), state_extra = sm.unk17 | (u32)sm.unk16 << 8 | (u32)sm.ext.misc_51.unk54 << 16)
static void cp_base_opened(void)
{
    PART(0, 1, 0);
}
static void cp_base_opening(void) { PART(0, 1, sm.animation_step.fields.relative_step = 1); }
static void cp_glass_start(void) { PART(1, 0, 0); }
static void cp_glass(void) { PART(1, 1, 0); }
static void cp_beam_start(void) { PART(2, 0, 0); }
static void cp_beam(void) { PART(2, 1, sm.ext.misc_51.unk54 = 3); }
static void cp_beam_end(void) { PART(2, 1, sm.ext.misc_51.unk54 = 1); }
static void cp_source_gone(void) { PART(1, 1, capsule_source.active = 0x21); }

static void (*const cp_cases[])(void) = {
    cp_base_opened,
    cp_base_opening,
    cp_glass_start,
    cp_glass,
    cp_beam_start,
    cp_beam,
    cp_beam_end,
    cp_source_gone,
};
static const u32 cp_expected[] = {
    0x20001u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x5u,
    0u,
    0x10001u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x10101u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    (u32)VISUAL_SATURN_LAYER(6) << 8 | 3,
    0u,
    0x10101u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x10201u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x780107u,
    0u,
    0x10201u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x20000u,
    0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
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
};
static u32 test_cp(u32 row)
{
    return object_run(cp_cases[row], row, &cp_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "capsule_part_steps", 0, 0, COUNT(cp_cases), test_cp },
    { "capsule_light_animation_start", NULL, capsule_light_animation_start_cases_expected, COUNT(capsule_light_animation_start_cases_expected), light_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(capsule_light_animation_start_cases_expected) + COUNT(cp_cases);
