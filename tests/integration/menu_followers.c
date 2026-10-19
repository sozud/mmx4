#include "test_runtime.h"
#include "main/misc/misc_50_cutscene_actor.h"
#include "main/unks/unk_01_menu_label.h"
#include "main/misc/misc_12_stage_icon.h"
static const s16 edges[9][2] = {
    { 160, 120 },
    { -33, 120 },
    { -32, 120 },
    { 351, 120 },
    { 352, 120 },
    { 160, -33 },
    { 160, -32 },
    { 160, 271 },
    { 160, 272 },
};
static const u8 visible[] = { 1, 0, 1, 1, 0, 0, 1, 1, 0 };
static const u8 owner_active[] = { 0, 1, 0x41 };
static u32 follower(u32 row)
{
    struct MiscObj obj, expected;
    struct MainObj owner, owner_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 2, edge = row / 2 % 9, status = row / 18 % 3, layer = row / 54;
    s32 camera_x = layer ? (s32)layer * 512 - 320 : 0, camera_y = layer ? (s32)layer * 256 - 240 : 0;
    if (layer) {
        background_objects[layer - 1].x_pos.val = camera_x * 65536;
        background_objects[layer - 1].y_pos.val = camera_y * 65536;
    }
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    engine_obj.unk2 = status + 6;
    engine_before = engine_obj;
    memset(&owner, 0, sizeof(owner));
    owner.active = owner_active[status];
    owner.id = 11;
    owner.state = 1;
    owner_before = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = kind ? 50 : 12;
    obj.state = kind ? 1 : 3;
    obj.unk2 = 2;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.on_screen = 7;
    obj.bg_offset = (s32)layer - 1;
    obj.ext.misc_24.main = &owner;
    obj.unk42 = 0x8123;
    obj.x_pos.val = (camera_x + edges[edge][0]) * 65536 + 0x1234;
    obj.y_pos.val = (camera_y + edges[edge][1]) * 65536 + 0x5678;
    expected = obj;
    if (!kind && status == 0)
        memset(&expected, 0, 8);
    else {
        expected.on_screen = visible[edge];
        if (kind && status == 1) {
            expected.state = 3;
            expected.unk42 = 0x7848;
        }
    }
    if (kind)
        cutscene_actor_update(&obj);
    else
        stage_icon_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
static const s16 label_y[] = { 15, 16, 17, 272 };
static u32 label_init(u32 row)
{
    struct UnkObj obj, expected;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    u32 saved_directory, offset = row & 4 ? 0x80 : 0x40;
    memcpy(&saved_directory, WINDOW_ARCHIVE_DATA, 4);
    memcpy(WINDOW_ARCHIVE_DATA, &offset, 4);
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 1;
    obj.unk2 = 0x5E + row % 8;
    obj.on_screen = 7;
    obj.bg_offset = 2;
    obj.unk15 = 0x40;
    obj.unk16 = 7;
    obj.x_pos.val = 0x12345678;
    obj.y_pos.val = label_y[row % 4] * 65536 + (row & 8 ? 0x5678 : 0);
    obj.animation_step.packed = 0x12345678;
    expected = obj;
    expected.unk40 = 0x1F00;
    expected.bg_offset = -1;
    expected.unk3C = WINDOW_ARCHIVE_DATA + offset;
    expected.unk15 = 0;
    expected.unk16 = 0;
    expected.x_pos.i.hi = 160;
    expected.unk42 = row % 4 == 1 ? 0x7802 : 0x7800;
    expected.animation_step.fields.frame_index = obj.unk2;
    expected.state = 1;
    expected.on_screen = row % 4 != 3;
    menu_label_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(*(u32*)WINDOW_ARCHIVE_DATA == offset);
    memcpy(WINDOW_ARCHIVE_DATA, &saved_directory, 4);
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "menu_owner_followers", NULL, NULL, 56, follower },
    { "menu_label_init", NULL, NULL, 16, label_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 56 + 16;
