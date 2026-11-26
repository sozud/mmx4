#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/misc/misc_33_cyberspace_warp.h"
#include "main/195B4.h"
#include "weapon_resources.h"
extern union AnimationStep* cyberspace_warp_animations[];
static const s16 positions[6][2] = { { 0x778, 0x60 }, { 0x378, 0x360 }, { 0x878, 0x260 }, { 0x378, 0x360 }, { 0xC78, 0x560 }, { 0x378, 0x360 } };
static const u32 words[] = { C_TEST_STEP(0x00010003), C_TEST_STEP(0x00010003), C_TEST_STEP(0x2F000008), C_TEST_STEP(0x30000008), C_TEST_STEP(0x31000008) };
static const u16 cluts[] = { 0x788C, 0x78C4 };
static u32 metadata[12], archive[24];
static u32 initial_mode(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct MainBssState main_before = main_bss_state;
    u32 type = row % 5, checkpoint = row / 5 % 6, exit = row / 30, resource = exit ? 7 : 5, i;
    for (i = 0; i < 12; i++) {
        metadata[i] = (i + 1) * 128;
        archive[i] = 48 + i * 4;
        archive[12 + i] = 0x13570000u + i;
    }
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = metadata;
#ifdef MMX4_SATURN
    saturn_stage_graphics_offsets_pointer = metadata;
#endif
    engine_obj.stage = 6;
    engine_obj.substage = exit;
    engine_obj.checkpoint = checkpoint;
    engine_before = engine_obj;
    g_Player.x_pos.val = 160 * 65536 + 0xAAAA;
    g_Player.y_pos.val = 120 * 65536 + 0xBBBB;
    g_Player.bg_offset = 0;
    player_before = g_Player;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 33;
    obj.unk2 = type;
    obj.unk5 = 4;
    obj.unk6 = 3;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.misc_33.timer = 9;
    expected = obj;
    expected.state = 1;
    expected.unk5 = type >= 2;
    expected.unk6 = 0;
    expected.unk15 = 0;
    expected.unk16 = VISUAL_SATURN_LAYER(type == 0 ? 6 : type == 1 ? 17
                                                                   : 16);
    expected.animation_table = (u32**)cyberspace_warp_animations;
#ifdef MMX4_SATURN
    expected.unk40 = (u16)(((metadata[resource] & ~127u) + 0x25C24000u) >> 3);
    expected.unk42 = resource * 4 + 0x18;
#else
    expected.unk40 = resource + 1;
    expected.unk42 = cluts[exit];
#endif
    expected.unk3C = (u8*)archive + 48 + resource * 4;
    expected.x_pos.i.hi = exit ? 0xFF0 : positions[checkpoint][0] - (type < 2 ? 10 : 0);
    expected.y_pos.i.hi = exit ? 0x290 : positions[checkpoint][1] + (type < 2 ? 48 : 0);
    if (type < 2)
        expected.ext.misc_33.timer = 72;
    expected.unk17 = type;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (u32*)cyberspace_warp_animations[type];
    expected.animation_step.packed = words[type];
    assert(s_StageMainIds[6][exit][resource] == 0x9B && (u8)func_8002938C(0x9B) == resource && cyberspace_warp_animations[type][0].packed == words[type]);
    func_800CE388(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    for (i = 0; i < 12; i++)
        assert(metadata[i] == (i + 1) * 128 && archive[i] == 48 + i * 4 && archive[12 + i] == 0x13570000u + i);
    assert(D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    return 1;
}

#include "support/state_cases.h"
#define sm state_room.misc
static s8 cw_flag;
#define WARP(step, sub, setup) (state_reset(step, sub, 0), cw_flag = 1, sm.active = 1, sm.state = 1, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.misc_33.completion_flag = &cw_flag, sm.ext.misc_33.timer = 3, setup, cyberspace_warp_update(&sm), state_extra = sm.ext.misc_33.timer | (u32)(u8)sm.on_screen << 16)
static void cw_fading(void) { WARP(0, 0, 0); }
static void cw_faded(void) { WARP(0, 0, sm.ext.misc_33.timer = 1); }
static void cw_fade_away(void) { WARP(0, 0, sm.x_pos.i.hi = 0x1000); }
static void cw_blink_on(void) { WARP(1, 1, sm.on_screen = 0); }
static void cw_blink_off(void) { WARP(1, 1, sm.on_screen = 1); }
static void cw_blink_done(void) { WARP(1, 1, sm.ext.misc_33.timer = 0); }
static void cw_trial_done(void) { WARP(1, 1, cw_flag = 0); }

static void (*const cw_cases[])(void) = {
    cw_fading,
    cw_faded,
    cw_fade_away,
    cw_blink_on,
    cw_blink_off,
    cw_blink_done,
    cw_trial_done,
};
static const u32 cw_expected[] = {
    0x1u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10002u, 0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u,
    0x2u, 0x1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2u, 0u,
    0x10101u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10002u, 0u,
    0x10101u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2u, 0u,
    0x10101u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10002u, 0u,
};
static u32 test_cw(u32 row)
{
    return object_run(cw_cases[row], row, &cw_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "cyberspace_warp_steps", 0, 0, COUNT(cw_cases), test_cw },
    { "all_valid_warp_subtypes_checkpoints_and_exit_archive", NULL, NULL, 60, initial_mode },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 60 + COUNT(cw_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
