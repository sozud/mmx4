#include "test_runtime.h"
#include "main/misc/misc_15_vent.h"

#include "support/pool_full.h"
static u32 pool_full_vent_spawn_mixed_puffs_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_mixed_puffs(&pf_misc, 1);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_mixed_puffs_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_mixed_puffs(&pf_misc, 0);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_puffs_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_puffs(&pf_misc, 1);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_puffs_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_puffs(&pf_misc, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_vent_spawn_mixed_puffs_one,
    pool_full_vent_spawn_mixed_puffs_none,
    pool_full_vent_spawn_puffs_one,
    pool_full_vent_spawn_puffs_none,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u, 0x50000u };

extern union AnimationStep* vent_animations[2];
static u32 metadata[5], archive[12];
static const u32 words[3] = { 0x03000001, 0x05000001, 0x04000001 };
static u32 enter(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 2, progress = 4 + row / 2 % 4, resource = row / 8, frame = progress < 5 ? 0 : progress < 7 ? 1
                                                                                                                : 2,
        i;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (resource + i + 1) * 128 + 0x5A;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 5 ? 20 + i * 4 : 0x13570000 + i;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    engine_obj.unk5F = progress;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].y_pos.i.hi = 256;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 15;
    obj.unk2 = type;
    obj.unk15 = 0x40;
    obj.x_pos.val = 0x1234;
    obj.y_pos.val = 0x5678;
    expected = obj;
    expected.unk42 = 0x7881;
    expected.unk40 = resource + 5;
    expected.animation_table = (u32**)vent_animations;
    expected.unk3C = (u8*)archive + 36;
    expected.x_pos.val = 124 * 65536;
    expected.y_pos.val = 392 * 65536;
    expected.bg_offset = 0;
    expected.unk15 = 0;
    expected.unk16 = type ? 1 : 2;
    expected.state = expected.on_screen = 1;
    expected.unk17 = type;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)(vent_animations[type] + (type ? frame : 0));
    expected.animation_step.packed = type ? words[frame] : 0x00010006;
    func_800CA86C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (resource + i + 1) * 128 + 0x5A);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 5 ? 20 + i * 4 : 0x13570000 + i));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "both_real_vent_layers_progress_four_through_seven_backed_archive", NULL, NULL, 16, enter },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases) + 16;
