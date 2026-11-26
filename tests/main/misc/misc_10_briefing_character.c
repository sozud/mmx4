#include "test_runtime.h"
#include "support/platform_fixture.h"
extern u32* briefing_x_animations[];
extern u32* briefing_x_partner_animations[];
extern u32* briefing_zero_animations[];
extern u32* briefing_zero_partner_animations[];
void briefing_character_init(struct MiscObj* arg0);
static u32 metadata[4], archive[8];
static const u32 words[] = { C_TEST_STEP(0x00010003), C_TEST_STEP(0x00010003), C_TEST_STEP(0x01010003), C_TEST_STEP(0x00010021) };
static u32 enter(u32 row)
{
    struct MiscObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 character = row % 2, partner = row / 2 % 2, camera = row / 4, resource = partner ? 3 : 2, i;
    u32** table = partner ? (character ? briefing_zero_partner_animations : briefing_x_partner_animations) : (character ? briefing_zero_animations : briefing_x_animations);
    for (i = 0; i < 4; i++) {
        metadata[i] = (i + 1) * 128;
        archive[i] = 16 + i * 4;
        archive[i + 4] = 0x12340000 + i;
    }
    test_stage_graphics(metadata);
    TEST_MENU_FRAMES = (u8*)archive;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = camera * 160;
    background_objects[0].y_pos.i.hi = 320;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.unk2 = partner;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 0x1234;
    obj.y_pos.val = 0x5678;
    expected = obj;
    expected.unk42 = partner ? OBJECT_CLUT(0x7885) : OBJECT_CLUT(0x7883);
    expected.unk40 = OBJECT_STAGE_TEXTURE(resource);
    expected.unk3C = (u8*)archive + 16 + resource * 4;
    expected.animation_table = table;
    expected.x_pos.val = (partner ? 282 : 42) * 65536;
    expected.y_pos.val = (partner ? 432 : 416) * 65536;
    expected.bg_offset = 0;
    expected.unk15 = 0;
    expected.unk16 = VISUAL_SATURN_LAYER(3);
    expected.state = 1;
    expected.animation_cursor = table[0];
    expected.previous_animation_index = 255;
    expected.animation_step.packed = words[character * 2 + partner];
    expected.on_screen = partner ? camera < 2 : !camera;
    assert(table[0][0] == words[character * 2 + partner]);
    briefing_character_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 4; i++)
        assert(metadata[i] == (i + 1) * 128 && archive[i] == 16 + i * 4 && archive[i + 4] == 0x12340000 + i);
    assert(D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    return 1;
}

#include "main/misc/misc_10_briefing_character.h"
#include "support/state_cases.h"
#define sm state_room.misc
#define BRIEF(kind, flags) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.unk40 = flags, sm.active = 0x41, sm.state = 1, sm.unk2 = kind, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, MegamanInBriefingRoomUpdate(&sm), state_extra = sm.unk17)
static void bc_character(void)
{
    BRIEF(0, 0x27);
}
static void bc_character_pose(void) { BRIEF(0, 0x17); }
static void bc_partner(void) { BRIEF(1, 0x16); }
static void bc_partner_pose(void) { BRIEF(1, 0x26); }
static void (*const briefing_poses_cases[])(void) = {
    bc_character,
    bc_character_pose,
    bc_partner,
    bc_partner_pose,
};
static const u32 briefing_poses_expected[] = {
    0x1u,
    0x41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x1u,
    0xFF000041u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    7u,
    0u,
    0x1u,
    0x141u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x1u,
    0xFF000141u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    6u,
    0u,
};
static u32 test_briefing_poses(u32 row)
{
    return object_run(briefing_poses_cases[row], row, &briefing_poses_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "both_characters_partners_and_backed_resource_directory", NULL, NULL, 12, enter },
    { "briefing_poses", 0, 0, COUNT(briefing_poses_cases), test_briefing_poses },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12 + COUNT(briefing_poses_cases);
