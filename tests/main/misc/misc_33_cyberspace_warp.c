#include "test_runtime.h"
#include "main/misc/misc_33_cyberspace_warp.h"
#include "main/195B4.h"
extern union AnimationStep* cyberspace_warp_animations[];
static const s16 positions[6][2] = { { 0x778, 0x60 }, { 0x378, 0x360 }, { 0x878, 0x260 }, { 0x378, 0x360 }, { 0xC78, 0x560 }, { 0x378, 0x360 } };
static const u32 words[] = { 0x00010003, 0x00010003, 0x2F000008, 0x30000008, 0x31000008 };
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
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.misc_33.timer = 9;
    expected = obj;
    expected.state = 1;
    expected.unk5 = type >= 2;
    expected.unk6 = 0;
    expected.unk15 = 0;
    expected.unk16 = type == 0 ? 6 : type == 1 ? 17
                                               : 16;
    expected.animation_table = (u32**)cyberspace_warp_animations;
    expected.unk40 = resource + 1;
    expected.unk42 = cluts[exit];
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
const struct CTestGroup c_test_groups[] = { { "all_valid_warp_subtypes_checkpoints_and_exit_archive", NULL, NULL, 60, initial_mode } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 60;
