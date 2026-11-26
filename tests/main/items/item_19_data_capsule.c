#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/items/item_19_data_capsule.h"
#include "main/195B4.h"
#include "main/mains/main_41_data_hopper.h"
#include "main/player_animations.h"
#include "main/player_common.h"
extern u8 data_capsule_box_0[4], data_capsule_box_1[4], data_capsule_box_2[4];

static s32 frames[128];
static u32 metadata[16];
static u32 capsule_case(u32 mode)
{
    struct ItemObj obj, expected, pool_expected[32];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    s32 frames_before[128];
    u32 metadata_before[16];
    u8 backref[4] = { 0x11, 0x22, 0x33, 0x44 };
    u32 i, free_count = mode < 4 ? 0 : (mode - 4) % 3;
    memset(&obj, 0, sizeof(obj));
    memset(item_objects, 0, sizeof(item_objects));
    for (i = 0; i < 32; i++) {
        item_objects[i].active = i < 32 - free_count ? 1 : 0;
        item_objects[i].id = 39;
        item_objects[i].unk2 = 9;
        item_objects[i].state = 40;
        item_objects[i].unk5 = 3;
        item_objects[i].unk6 = 4;
        item_objects[i].unk7 = 5;
        item_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        item_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    for (i = 0; i < 128; i++)
        frames[i] = 0x12340000 + i;
    for (i = 0; i < 16; i++)
        metadata[i] = 0x1000 + i * 0x400;
    frames[2] = 64;
    memcpy(frames_before, frames, sizeof(frames));
    memcpy(metadata_before, metadata, sizeof(metadata));
    test_stage_graphics(metadata);
    TEST_MENU_FRAMES = (u8*)frames;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    engine_obj.character_state.fields.active = 1;
    g_Player.bg_offset = 1;
    obj.active = 1;
    obj.id = 19;
    obj.unk2 = mode < 4 ? mode : mode < 7 ? 4
                                          : 5;
    obj.state = 0;
    obj.on_screen = 0;
    obj.unk5 = 9;
    obj.unk6 = 10;
    obj.unk7 = 11;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.unk18.val = 0x11223344;
    obj.unk1C.val = 0x55667788;
    obj.x_vel.val = -12345;
    obj.y_vel.val = 54321;
    obj.unk28 = 123;
    obj.unk2C = -456;
    obj.bg_offset = -1;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.unk40 = 0x3333;
    obj.unk42 = 0x5555;
    obj.unk75 = 9;
    obj.unk76 = 10;
    obj.unk67 = 11;
    obj.unk7C.timer16 = 123;
    ((u16*)&obj.unk7C)[1] = 456;
    obj.backref = mode >= 7 ? backref : NULL;
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_expected, item_objects, sizeof(pool_expected));
    if (mode < 4) {
        expected.active = 0x41;
        expected.state = 1;
        expected.on_screen = 1;
        expected.unk5 = expected.unk6 = 0;
        expected.unk7 = 1;
        expected.unk18 = obj.x_pos;
        expected.unk1C = obj.y_pos;
        expected.animation_table = (const u8* const*)data_hopper_animations;
        expected.sprite_frames = (const u8*)frames + 64;
        expected.unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x29));
        expected.unk42 = OBJECT_CLUT(0x7880);
        expected.unk16 = VISUAL_SATURN_LAYER(6);
        expected.unk54 = NULL;
        expected.unk50 = NULL;
        expected.unk68 = (struct Unk_unk68*)(mode == 0 ? data_capsule_box_0 : mode == 1 ? data_capsule_box_1
                                                                                        : data_capsule_box_2);
        expected.unk76 = -1;
        expected.unk75 = 1;
        expected.unk67 = 0;
        expected.x_vel.val = expected.y_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.unk7C.timer16 = 10;
        ((u16*)&expected.unk7C)[1] = 0;
        expected.animation_cursor = (const u8*)data_hopper_animations[mode + 15];
        expected.animation_step = data_hopper_animations[mode + 15][0];
        expected.unk17 = mode + 15;
        expected.previous_animation_index = 0xFF;
    } else {
        memset(&expected, 0, 8);
        for (i = 0; i < free_count; i++) {
            struct ItemObj* child = &pool_expected[32 - free_count + i];
            child->active = 1;
            child->id = 19;
            child->unk2 = i;
            child->x_pos.u.hi = 0x7B0;
            child->y_pos.u.hi = mode < 7 ? (i == 0 ? 0x22C : 0x3A0) : (i == 0 ? 0x458 : 0x5D8);
        }
    }
    assert(s_StageMainIds[6][1][2] == 0x29 && (u8)func_8002938C(0x29) == 2);
    func_800C4778(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(item_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    for (i = 0; i < 128; i++)
        assert(frames[i] == frames_before[i]);
    for (i = 0; i < 16; i++)
        assert(metadata[i] == metadata_before[i]);
    assert(backref[0] == (mode >= 7 ? 0x80 : 0x11) && backref[1] == 0x22 && backref[2] == 0x33 && backref[3] == 0x44);
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    i = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)obj.unk17 << 16) | ((u32)backref[0] << 24);
    return i;
}
static const u32 data_capsule_resources_child_pool_cases_expected[] = { 0x110F0141u, 0x11100141u, 0x11110141u, 0x11120141u, 0x11000000u, 0x11000000u, 0x11000000u, 0x80000000u, 0x80000000u, 0x80000000u };

static struct MainObj mains_before[48];
static struct ItemObj items_expected[32];
static u32 archive[64], metadata_data_capsule_enemy_capacity[16];
static u32 full(u32 row)
{
    struct PlayerObj player;
    struct EngineObj engine;
    struct ItemObj* child = &item_objects[1];
    u32 i;
    (void)row;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    engine_obj.character_state.fields.active = 1;
    background_objects[0].x_pos.i.hi = 1808;
    background_objects[0].y_pos.i.hi = 436;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 1000;
    g_Player.y_pos.i.hi = 1000;
    g_Player.unk54 = &D_801194F0[0];
    g_Player.unk68 = &player_x_collision_bounds;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 16 ? 64 + i * 4 : 0x13570000 + i;
    for (i = 0; i < COUNT(metadata_data_capsule_enemy_capacity); i++)
        metadata_data_capsule_enemy_capacity[i] = (i + 1) * 128;
    TEST_MENU_FRAMES = (u8*)archive;
    test_stage_graphics(metadata_data_capsule_enemy_capacity);
    assert(func_8002938C(0x29) == 2);
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    item_objects[0].active = 1;
    item_objects[0].id = 19;
    item_objects[0].unk2 = 4;
    item_objects[0].x_pos.i.hi = 624;
    item_objects[0].y_pos.i.hi = 912;
    func_800C4778(&item_objects[0]);
    assert(child->active == 1 && child->id == 19 && child->unk2 == 0 && child->x_pos.i.hi == 1968 && child->y_pos.i.hi == 556);
    func_800C4778(child);
    assert(child->state == 1 && child->unk17 == 15 && child->unk7C.timer16 == 10);
    for (i = 0; i < 16; i++)
        func_800C49BC(child);
    assert(child->unk7C.timer16 == 0 && child->animation_step.packed == C_TEST_STEP(0x42000001) && child->on_screen == 1);
    memcpy(items_expected, item_objects, sizeof(items_expected));
    items_expected[1].unk7C.timer16 = 30;
    memcpy(mains_before, main_objects, sizeof(mains_before));
    player = g_Player;
    engine = engine_obj;
    cur_random = 0x1234;
    func_800C49BC(child);
    assert(c_test_word_difference((u32*)item_objects, (u32*)items_expected, sizeof(items_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)main_objects, (u32*)mains_before, sizeof(mains_before) / 4) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && TEST_MENU_FRAMES == (u8*)archive && D_801406A8 == metadata_data_capsule_enemy_capacity);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 16 ? 64 + i * 4 : 0x13570000 + i));
    for (i = 0; i < COUNT(metadata_data_capsule_enemy_capacity); i++)
        assert(metadata_data_capsule_enemy_capacity[i] == (i + 1) * 128);
    return 1;
}

#include "support/state_cases.h"
#include "support/sound_probe.h"
#define dc state_room.item
static struct MainObj dc_owner;
static u32 dc_archive[16], dc_meta[64];
#define DC(sub, setup)                                                                                                                          \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 6, engine_obj.substage = 1,                           \
        g_Player.unk68 = NULL, memset(main_objects, 0, sizeof(main_objects)), TEST_MENU_FRAMES = (u8*)dc_archive, test_stage_graphics(dc_meta), \
        dc_archive[2] = 64, sound_probe_begin(), dc.active = 0x41, dc.id = 0x13, dc.unk2 = sub, dc.state = 1,                                   \
        dc.x_pos.i.hi = 0x7B0, dc.y_pos.i.hi = 0x80, setup, data_capsule_update(&dc), DCX())
#define DCX() (state_extra = (u16)dc.unk7C.timer16 | (u32)(u16)dc.unk7C.saved_pos.y << 16 ^ (main_objects[0].active | main_objects[0].id << 8 | (u32)(u16)main_objects[0].y_pos.i.hi << 16), engine_obj.stage = engine_obj.substage = 0)
static void dc_spawn_on_screen(void)
{
    DC(0, dc.on_screen = 1);
    SOUND_CHECK(sound_probe_id() == 0xEA);
}
static void dc_spawn_off_screen(void)
{
    DC(0, dc.on_screen = 0);
    SOUND_CHECK(sound_probe_id() == -1);
}
static void dc_wait_low(void) { DC(0, dc.y_pos.i.hi = 0x100); }
static void dc_switch_rearm(void) { DC(1, engine_obj.character_state.fields.active = 1); }
static void dc_open_done(void) { DC(1, dc.unk7C.saved_pos.y = 1); }
static void dc_open_done_big(void) { DC(2, dc.unk7C.saved_pos.y = 1); }
static void dc_opening(void) { DC(1, (dc.unk7C.saved_pos.y = 1, dc.animation_step.fields.relative_step = 1)); }
static void dc_attached(u8 step) { DC(-1, (dc_owner.unk5 = step, dc_owner.x_pos.val = 0x1000000, dc_owner.y_pos.val = 0x2000000, dc.ext.owner = &dc_owner)); }
static void dc_attached_follow(void) { dc_attached(5); }
static void dc_attached_end(void) { dc_attached(4); }
static void (*const data_capsule_steps_cases[])(void) = {
    dc_spawn_on_screen,
    dc_spawn_off_screen,
    dc_wait_low,
    dc_switch_rearm,
    dc_open_done,
    dc_open_done_big,
    dc_opening,
    dc_attached_follow,
    dc_attached_end,
};
static const u32 data_capsule_steps_expected[] = {
    0x1u,
    0xFF000041u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0xA8295Fu,
    0x0u,
    0x1u,
    0xFF000041u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0xA8295Fu,
    0x0u,
    0x1u,
    0x41u,
    0x7B00000u,
    0x1000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1000001u,
    0x141u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1Eu,
    0x0u,
    0x1u,
    0xFF000141u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0xFF000241u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x141u,
    0x7B00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10000u,
    0x0u,
    0x1u,
    0xFF41u,
    0x1000000u,
    0x2000000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1000000u,
    0x2000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_data_capsule_steps(u32 row)
{
    return object_run(data_capsule_steps_cases[row], row, &data_capsule_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "data_capsule_resources_child_pool", NULL, data_capsule_resources_child_pool_cases_expected, COUNT(data_capsule_resources_child_pool_cases_expected), capsule_case },
    { "stage6_real_capsule_factory_own_animation_clock_full_main_pool", NULL, NULL, 1, full },
    { "data_capsule_steps", 0, 0, COUNT(data_capsule_steps_cases), test_data_capsule_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(data_capsule_resources_child_pool_cases_expected) + 1 + COUNT(data_capsule_steps_cases);
