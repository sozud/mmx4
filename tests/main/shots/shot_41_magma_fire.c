#include "test_runtime.h"
extern void* magma_dragoon_animations[38];
extern u8 magma_fire_wave_hit_box[4], magma_fire_pillar_hit_boxes[1][4];
extern u8 magma_fire_ember_hit_box[4], magma_fire_ember_terrain_box[4];
extern u8 magma_fire_burst_hit_box[4], magma_fire_burst_terrain_box[4];
extern s16 magma_fire_wave_offsets[8];

static s32 sprites[4] = { 8, 12, 0x11223344, 0x55667788 };
static u32 fire_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i, kind = mode < 2 ? 0 : mode < 6 ? 1
        : mode == 6                       ? 2
        : mode == 7                       ? 3
                                          : 4;
    u32 animation = kind == 0 ? 28 : kind == 1 ? 29
        : kind == 2                            ? 31
                                               : 27;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    owner.active = 0x41;
    owner.id = 65;
    owner.state = 1;
    owner.unk5 = 7;
    owner.unk40 = 0x2345;
    owner.unk42 = 0x8123;
    owner.bg_offset = -1;
    owner.unk15 = mode & 1 ? 0x40 : 0;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 100 * 65536 + 0x5678;
    owner.animation_table = (const u8* const*)magma_dragoon_animations;
    owner.sprite_frames = (const u8*)sprites;
    obj.active = 0x41;
    obj.id = 41;
    obj.state = 1;
    obj.unk2 = kind;
    obj.unk7 = mode == 2 ? 1 : mode == 3 ? 7
        : mode == 4                      ? 2
        : mode == 5                      ? 3
                                         : 0;
    obj.unk15 = 0x20;
    obj.unk16 = 3;
    obj.unk5C = 9;
    obj.unk60 = 11;
    obj.unk28 = 0x123456;
    obj.unk2C = 0x654321;
    obj.x_pos.val = 50 * 65536 + 0xABCD;
    obj.y_pos.val = 60 * 65536 + 0xFEDC;
    obj.x_vel.val = 123;
    obj.y_vel.val = 456;
    obj.timer = 17;
    obj.unk7C = &owner;
    expected = obj;
    owner_expected = owner;
    expected.unk40 = owner.unk40;
    expected.animation_table = (u32**)magma_dragoon_animations;
    expected.unk3C = (void*)sprites;
    expected.unk5C = 0;
    expected.unk16 = 1;
    expected.unk42 = 0x123;
    expected.bg_offset = -1;
    if (kind < 4) {
        expected.unk54 = NULL;
        expected.unk58.data = (u8*)(kind == 1 ? D_80105FF0 : D_801060F0);
        expected.unk60 = kind == 0 ? 9 : kind == 3 ? 6
                                                   : 4;
        expected.state = 2;
        expected.unk5 = kind + 2;
        expected.unk15 = kind == 1 ? 0 : owner.unk15;
        if (kind == 0) {
            expected.unk50.data = magma_fire_wave_hit_box;
            expected.unk68 = NULL;
            expected.x_pos.val = owner.x_pos.val + (owner.unk15 ? 24 * 65536 : -24 * 65536);
            expected.y_pos.val = owner.y_pos.val + 16 * 65536;
            expected.x_vel.val = owner.unk15 ? 6 * 65536 : -6 * 65536;
            expected.y_vel.val = 2 * 65536;
            expected.timer = 7;
        } else if (kind == 1) {
            expected.unk50.data = (u8*)magma_fire_pillar_hit_boxes;
            expected.unk68 = NULL;
            expected.x_pos.val = owner.x_pos.val + (owner.unk15 ? -16 * 65536 : 16 * 65536);
            expected.y_pos.val = owner.y_pos.val - 32 * 65536;
            expected.x_vel.val = magma_fire_wave_offsets[obj.unk7] * 4096;
            expected.y_vel.val = 5 * 65536;
        } else if (kind == 2) {
            expected.unk50.data = magma_fire_ember_hit_box;
            expected.unk68 = (struct Unk_unk68*)magma_fire_ember_terrain_box;
            expected.x_pos.val = owner.x_pos.val;
            expected.y_pos.val = owner.y_pos.val - 64 * 65536;
            expected.x_vel.val = owner.unk15 ? 4 * 65536 : -4 * 65536;
            expected.y_vel.val = 0x1C000;
            expected.unk28 = 0;
            expected.unk2C = 0x1300;
        } else {
            expected.unk50.data = magma_fire_burst_hit_box;
            expected.unk68 = (struct Unk_unk68*)magma_fire_burst_terrain_box;
            expected.timer = 3;
        }
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        ANIMATED_OBJECT(&expected)->animation_cursor = magma_dragoon_animations[animation];
        expected.animation_step.packed = *(u32*)magma_dragoon_animations[animation];
    }
    expected.on_screen = 1;
    func_800A56E4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    return (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_vel.i.hi << 16);
}
#define CASE(m)                                                \
    static u32 magma_fire_owner_animation_start_fire_##m(void) \
    {                                                          \
        return fire_case(m);                                   \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
#define ENTRY(m) magma_fire_owner_animation_start_fire_##m,
static const CTestCase magma_fire_owner_animation_start_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) };
static const u32 magma_fire_owner_animation_start_cases_expected[] = { 0xFFFA1C02u, 0x61C02u, 0x1D03u, 0x1D03u, 0xFFFF1D03u, 0xFFFF1D03u, 0xFFFC1F04u, 0x1B05u, 0x0u };
#undef CASE
#undef ENTRY

static const u32 func_800A56E4_expected[] = { 0xFFFFFF80u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800A56E4(u32 row)
{
    u32 observed_values[16];
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    child_0.bg_offset = -128;
    obj.unk2 = -1;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800A56E4(&obj);
    observed_values[0] = (u32)obj.bg_offset;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.timer;
    observed_values[3] = (u32)obj.unk15;
    observed_values[4] = (u32)obj.unk16;
    observed_values[5] = (u32)obj.unk28;
    observed_values[6] = (u32)obj.unk2C;
    observed_values[7] = (u32)obj.unk40;
    observed_values[8] = (u32)obj.unk42;
    observed_values[9] = (u32)obj.unk5;
    observed_values[10] = (u32)obj.unk5C;
    observed_values[11] = (u32)obj.unk60;
    observed_values[12] = (u32)obj.x_pos.val;
    observed_values[13] = (u32)obj.x_vel.val;
    observed_values[14] = (u32)obj.y_pos.val;
    observed_values[15] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_800A56E4_expected, 16);
}

static const u32 inputs_0[2][4] = {
    { -1, 1, 0, 0 },
    { 0, 0, 0, 0 },
};
struct magma_fire_pillar_repeat_case {
    u32 expected[4];
};
static const struct magma_fire_pillar_repeat_case magma_fire_pillar_repeat_cases[] = {
    { { 0u, 0u, 0xFFFFFFFEu, 0u } },
    { { 0u, 0u, 0u, 0u } },
};
static u32 test_magma_fire_pillar_repeat(u32 row)
{
    const struct magma_fire_pillar_repeat_case* c = &magma_fire_pillar_repeat_cases[row];
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.relative_step = inputs_0[row][0];
    obj.unk8A = inputs_0[row][1];
    obj.unk6 = inputs_0[row][2];
    obj.state = inputs_0[row][3];
    magma_fire_pillar_repeat(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk8A;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/animation_endings.h"
ENDING_CASE(3)
ENDING_CASE(4)
ENDING_CASE(5)
ENDING_CASE(6)
static const CTestCase pillar_repeat_ending_cases[] = { ENDING_ENTRY(3) ENDING_ENTRY(4) ENDING_ENTRY(5) ENDING_ENTRY(6) };

static const u32 pillar_repeat_ending_cases_expected[] = { 0x20401u, 0x20401u, 0x201u, 0x10002u };
const struct CTestGroup c_test_groups[] = {
    { "magma_fire_owner_animation_start", magma_fire_owner_animation_start_cases, magma_fire_owner_animation_start_cases_expected, COUNT(magma_fire_owner_animation_start_cases), 0 },
    { "func_800A56E4", 0, 0, 1, test_func_800A56E4 },
    { "magma_fire_pillar_repeat", 0, 0, 2, test_magma_fire_pillar_repeat },
    { "pillar_repeat_ending", pillar_repeat_ending_cases, pillar_repeat_ending_cases_expected, COUNT(pillar_repeat_ending_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(magma_fire_owner_animation_start_cases) + 1 + 2 + COUNT(pillar_repeat_ending_cases);
