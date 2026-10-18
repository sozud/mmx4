#include "test_runtime.h"
#include "main/shots/shot_16_linked_spark.h"
extern union AnimationStep* pod_spawner_animations[16];
extern u8* turret_laser_beam_boxes[12];

static u32 linked_spark_animation_spark_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 16;
    obj.unk2 = mode == 5 ? -1 : mode;
    obj.unk15 = 0x40;
    obj.unk84.value = 2;
    obj.animation_table = (u32**)pod_spawner_animations;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    before = obj;
    linked_spark_init(&obj);
    before.state = obj.state;
    before.on_screen = obj.on_screen;
    before.unk5C = obj.unk5C;
    before.unk60 = obj.unk60;
    before.unk84 = obj.unk84;
    before.unk15 = obj.unk15;
    before.unk16 = 6;
    before.unk50.data = NULL;
    before.unk54 = NULL;
    before.unk68 = NULL;
    before.unk17 = obj.unk17;
    before.previous_animation_index = 0xFF;
    before.animation_step = obj.animation_step;
    before.animation_cursor = (void*)pod_spawner_animations[obj.unk17];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    if (observation == 0)
        actual = (u8)obj.state | ((u32)obj.on_screen << 8) | ((u32)(u8)obj.unk5C << 16) | ((u32)(u8)obj.unk60 << 24);
    else if (observation == 1)
        actual = (u16)obj.unk84.value | ((u32)obj.unk15 << 16) | ((u32)obj.unk17 << 24);
    else
        actual = obj.animation_step.packed;
    return actual;
}
#define SPARK(m, n)                                         \
    static u32 linked_spark_animation_spark_##m##_##n(void) \
    {                                                       \
        return linked_spark_animation_spark_case(m, n);     \
    }
#define MODE(m) SPARK(m, 0) SPARK(m, 1) SPARK(m, 2)
MODE(0)
MODE(1)
MODE(4)
MODE(5)
#define ENTRY(m, n) linked_spark_animation_spark_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2)
static const CTestCase linked_spark_animation_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(4) ENTRIES(5) };
static const u32 linked_spark_animation_cases_expected[] = { 0x4010101u, 0x6000006u, 0x20010102u, 0x4010101u, 0x6400006u, 0x20010102u, 0x4010101u, 0x2400002u, 0x10003u, 0x4010101u, 0x2400002u, 0x10003u };
#undef SPARK
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 linked_spark_owner_guards_spark_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, expected_owner;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct RideArmorObj ride_before = qux_object;
    struct BackgroundObj backgrounds_before[3];
    u32 i, actual, animation = mode == 5 || mode == 9 ? 9 : mode == 6 || mode == 10 ? 12
                                                                                    : 6;
    u32 frame = mode < 8 || mode == 11 ? 5 : 0;
    const union AnimationStep* steps = pod_spawner_animations[animation];
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = mode == 0 ? 0 : 0x41;
    owner.id = mode == 1 ? 30 : 29;
    owner.state = mode == 2 ? 2 : 1;
    owner.unk2 = mode == 3 ? -1 : mode == 7 ? 127
                                            : 0;
    owner.unk5 = 6;
    owner.unk6 = 8;
    owner.x_pos.val = 50 * 65536 + 0xBEEF;
    owner.y_pos.val = 60 * 65536 + 0xCAFE;
    obj.active = 0x41;
    obj.id = 16;
    obj.state = 1;
    obj.unk5 = mode == 11 ? 1 : 0;
    obj.unk2 = mode == 5 ? 2 : mode == 6 ? 3
        : mode == 7                      ? 1
                                         : 0;
    obj.bg_offset = -1;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 77 * 65536 + 0x1234;
    obj.y_pos.val = 88 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)pod_spawner_animations;
    obj.animation_cursor = (const u8*)&steps[frame];
    obj.animation_step = steps[frame];
    obj.unk17 = animation;
    obj.previous_animation_index = 9;
    obj.unk7C = (struct WeaponObj*)&owner;
    obj.unk84.value = animation;
    g_Player.ride_state = 0;
    g_Player.invincibility_timer = 1;
    player_before = g_Player;
    expected = obj;
    expected_owner = owner;
    expected.x_pos = owner.x_pos;
    expected.y_pos = owner.y_pos;
    expected.on_screen = 1;
    if (mode < 8) {
        expected.unk5 = 1;
        expected.unk17 = animation + 1;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)pod_spawner_animations[animation + 1];
        expected.animation_step = *pod_spawner_animations[animation + 1];
        if (mode >= 4)
            expected_owner.unk5 = 4;
    } else if (mode != 11) {
        expected.unk50.data = turret_laser_beam_boxes[steps[0].fields.event - 1];
    }
    expected.animation_step.fields.duration--;
    func_8009C45C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&expected_owner)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(qux_object) / 4; i++)
        assert(((u32*)&qux_object)[i] == ((u32*)&ride_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(pod_spawner_animations[6][5].packed == 0x1B000402);
    assert(pod_spawner_animations[9][5].packed == 0x27000802);
    assert(pod_spawner_animations[12][5].packed == 0x35000C02);
    actual = (u8)obj.unk5 | ((u32)(u8)owner.unk5 << 8) | ((u32)obj.unk17 << 16);
    return actual;
}
static const u32 linked_spark_owner_guards_cases_expected[] = { 0x70601u, 0x70601u, 0x70601u, 0x70601u, 0x70401u, 0xA0401u, 0xD0401u, 0x70401u, 0x60600u, 0x90600u, 0xC0600u, 0x60601u };

static const u32 inputs_0[2][5] = {
    { 255, 1, 0, 0, 0 },
    { 255, 1, 29, -128, 0 },
};
struct linked_spark_despawn_case {
    u32 expected[2];
};
static const struct linked_spark_despawn_case linked_spark_despawn_cases[] = {
    { { 0u, 0u } },
    { { 0u, 0u } },
};
static u32 test_linked_spark_despawn(u32 row)
{
    const struct linked_spark_despawn_case* c = &linked_spark_despawn_cases[row];
    u32 observed_values[2];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = inputs_0[row][0];
    child_0.active = inputs_0[row][1];
    child_0.id = inputs_0[row][2];
    child_0.unk2 = inputs_0[row][3];
    child_0.unk80.bytes[1] = inputs_0[row][4];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    linked_spark_despawn(&obj);
    observed_values[0] = (u32)child_0.ext.weapon_29.unk90;
    observed_values[1] = (u32)child_0.unk80.bytes[1];
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "linked_spark_animation", linked_spark_animation_cases, linked_spark_animation_cases_expected, COUNT(linked_spark_animation_cases), 0 },
    { "linked_spark_owner_guards", NULL, linked_spark_owner_guards_cases_expected, COUNT(linked_spark_owner_guards_cases_expected), linked_spark_owner_guards_spark_case },
    { "linked_spark_despawn", 0, 0, 2, test_linked_spark_despawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(linked_spark_animation_cases) + COUNT(linked_spark_owner_guards_cases_expected) + 2;
