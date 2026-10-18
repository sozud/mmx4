#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_04_dragon_rubble.h"

static struct MainObj rubble_dragon;
static u32 rubble_pages[0x100];
static s32 rubble_frames[0x100];
#define sm state_room.misc
#define RUBBLE(st, kind) (state_reset(0, 0, 0), memset(&rubble_dragon, 0, sizeof(rubble_dragon)), rubble_dragon.x_pos.i.hi = 0x200, rubble_dragon.y_pos.i.hi = 0x180, D_801406A8 = rubble_pages, TEST_MENU_FRAMES = (u8*)rubble_frames, sm.ext.misc_4.owner = &rubble_dragon, sm.state = st, sm.unk2 = kind)
#define RUBBLE_SEEN() (sm.unk42 = 0, state_extra = (u16)rubble_dragon.unk7C | (u32)visual_objects[0].active << 16 | (u32)(u8)sm.unk16 << 24)
static void dr_burst_right(void)
{
    RUBBLE(4, 0);
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_burst_left(void)
{
    RUBBLE(4, 1);
    rubble_dragon.unk15 = 0x40;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_end(void)
{
    RUBBLE(5, 0);
    sm.active = 1;
    sm.unk5 = 0;
    dragon_rubble_update(&sm);
}
static void dr_fade_1(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 1;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_4(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 4;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_8(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 8;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_13(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 13;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_15(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 15;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_fade_quiet(void)
{
    RUBBLE(5, 0);
    sm.unk5 = 2;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_chunk_back(void)
{
    RUBBLE(2, 0);
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_chunk_front(void)
{
    RUBBLE(2, 1);
    rubble_dragon.unk15 = 0x40;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}
static void dr_chunk_full(void)
{
    RUBBLE(2, 0);
    sm.active = 1;
    rubble_dragon.unk7C = 0x15;
    dragon_rubble_update(&sm);
    RUBBLE_SEEN();
}

static void (*const dragon_rubble_states_cases[])(void) = {
    dr_burst_right,
    dr_burst_left,
    dr_fade_end,
    dr_fade_1,
    dr_fade_4,
    dr_fade_8,
    dr_fade_13,
    dr_fade_15,
    dr_fade_quiet,
    dr_chunk_back,
    dr_chunk_front,
    dr_chunk_full,
};
static const u32 dragon_rubble_states_expected[] = { 0x1005u, 0u, 0x6C00000u, 0x18D0000u, 0x60000u, 0u, 0u, 0x50000u, 0x210000u, 0x41002100u, 0x1005u, 0x100u, 0x8C00000u, 0x18D0000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0x210000u, 0x41002100u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x210000u, 0x2100u, 0x305u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x210000u, 0x2100u, 0x705u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x210000u, 0x2100u, 0xC05u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x210000u, 0x2100u, 0xE05u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x210000u, 0x2100u, 0x105u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 3u, 0u, 0x2300000u, 0x1240000u, 0u, 0u, 0u, 0x50000u, 0x6000001u, 0u, 3u, 0x100u, 0x1D00000u, 0x1240000u, 0u, 0u, 0u, 0x50000u, 0x1210001u, 0x41002100u, 0u, 0u, 0x2300000u, 0x1240000u, 0u, 0u, 0u, 0x50000u, 0x6000015u, 0u };

static u32 test_dragon_rubble_states(u32 row)
{
    return object_run(dragon_rubble_states_cases[row], row, &dragon_rubble_states_expected[row * 10]);
}

void dragon_rubble_init(struct MiscObj* arg0);
static u32 metadata[7], archive[16];
static struct MiscObj misc_before[64];
static struct VisualObj visuals_before[32];
static const u16 seeds[2] = { 0x1234, 0x1000 }, final_seeds[2] = { 0xA30D, 0x90C0 };
static u32 enter(u32 row)
{
    struct MiscObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_expected[3];
    u32 full = row % 2, frame = row / 2 % 2, seed = row / 4, i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    assert(func_8002938C(0x85) == 6);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128 + 0x5A;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 7 ? 32 + i * 4 : 0x13570000 + i;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    D_8013E198[5] = -1;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    owner.active = 0x41;
    owner.id = 0;
    owner.state = 1;
    owner.unk7C = full ? 21 : 20;
    owner_expected = owner;
    obj.active = 1;
    obj.id = 4;
    obj.unk2 = frame;
    obj.ext.misc_4.owner = &owner;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 0x12345;
    expected = obj;
    expected.animation_table = (u32**)dragon_rubble_animations;
    expected.unk42 = 0x78C0;
    expected.unk40 = 7;
    expected.unk3C = (u8*)archive + 56;
    expected.unk15 = seed ? 0 : 0x40;
    expected.unk16 = 7;
    expected.x_vel.val = 0;
    expected.animation_step.fields.frame_index = frame;
    expected.state = 1;
    backgrounds_expected[0].unk37 = 20;
    backgrounds_expected[0].unk46 = backgrounds_expected[0].unk3E.bytes[1] = 4;
    backgrounds_expected[0].unk3D = backgrounds_expected[0].unk3B = 2;
    backgrounds_expected[0].unk34 |= 1;
    if (full)
        memset(&expected, 0, 8);
    else {
        owner_expected.unk7C = 21;
        expected.on_screen = 1;
    }
    cur_random = seeds[seed];
    dragon_rubble_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    assert(cur_random == final_seeds[seed] && D_8013E198[5] == -1 && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128 + 0x5A);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 7 ? 32 + i * 4 : 0x13570000 + i));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "dragon_rubble_states", 0, 0, COUNT(dragon_rubble_states_cases), test_dragon_rubble_states },
    { "actual_sky_lagoon_resource_six_owner_count_twenty_twenty_one_full_effect_pools", NULL, NULL, 8, enter },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragon_rubble_states_cases) + 8;
