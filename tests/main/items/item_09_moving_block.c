#include "test_runtime.h"
#include "main/items/item_09_moving_block.h"
#include "main/195B4.h"
extern u8 moving_block_terrain_box[4];

static s32 frames[128];
static u32 metadata[16];
static u32 block_case(u32 mode)
{
    struct ItemObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    for (i = 0; i < 128; i++)
        frames[i] = 0x12340000 + i;
    for (i = 0; i < 16; i++)
        metadata[i] = 0x1000 + i * 0x400;
    frames[8] = 64;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    obj.active = 1;
    obj.id = 9;
    obj.state = 0;
    obj.unk2 = 0;
    obj.unk5 = 9;
    obj.unk6 = 10;
    obj.unk7 = 11;
    obj.unk16 = 3;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = -12345;
    obj.y_vel.val = 54321;
    obj.unk28 = 123;
    obj.unk2C = -456;
    obj.unk5C = 9;
    obj.unk61 = 10;
    obj.unk75 = 11;
    obj.unk76 = 12;
    obj.animation_step.packed = 0x18010003;
    obj.unk54 = moving_block_terrain_box;
    g_Player.x_pos.val = (mode == 0 ? 99 : 100) * 65536 + 0x1234;
    g_Player.bg_offset = 1;
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    expected.active = 0x41;
    expected.state = 1;
    expected.bg_offset = 1;
    expected.unk40 = 0x60;
    expected.unk42 = 0x78C8;
    expected.unk16 = 6;
    expected.sprite_frames = (const u8*)frames + 64;
    expected.animation_step.fields.frame_index = 0;
    expected.unk5C = 0;
    expected.unk61 = 0;
    expected.unk54 = NULL;
    expected.unk68 = (struct Unk_unk68*)moving_block_terrain_box;
    expected.x_vel.val = mode == 0 ? -65536 : 65536;
    expected.y_vel.val = 0;
    expected.unk28 = 0;
    expected.unk2C = 0;
    expected.unk75 = 0;
    expected.unk76 = 0;
    expected.unk7C.timer16 = 100;
    ((u16*)&expected.unk7C)[1] = 200;
    assert(s_StageMainIds[7][1][8] == 0xA1 && (u8)func_8002938C(0xA1) == 8);
    assert(moving_block_motion[0].x_velocity == 65536 && moving_block_motion[0].y_velocity == 0);
    func_800C20F4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < 128; i++)
        assert(frames[i] == (i == 8 ? 64 : 0x12340000 + i));
    for (i = 0; i < 16; i++)
        assert(metadata[i] == 0x1000 + i * 0x400);
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    result = obj.x_vel.val;
    return result;
}
static u32 left(void)
{
    return block_case(0);
}
static u32 equal(void)
{
    return block_case(1);
}
static const CTestCase moving_block_resource_facing_cases[] = { left, equal };

static const u32 moving_block_resource_facing_cases_expected[] = { 0xFFFF0000u, 0x10000u };

extern u8 moving_block_terrain_box[4];
static const struct {
    s32 velocity;
    s16 destination;
    u8 reverse;
} motions[] = {
    { 0x18000, 103, 1 },
    { 0x18000, 104, 1 },
    { 0x18000, 105, 0 },
    { -0x18000, 135, 0 },
    { -0x18000, 136, 1 },
    { -0x18000, 137, 1 },
    { 0, 135, 0 },
    { 0, 136, 0 },
    { 0, 137, 0 },
};
static const s16 x_edges[] = { 160, -64, -65, 383, 384 };
static const u8 wait_values[] = { 0, 1, 10 };
static const u8 far_away[] = { 0, 0, 1, 0, 1 };
static u32 vertical_motion(u32 row)
{
    struct ItemObj obj, expected;
    struct PlayerObj player_before, entity_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    struct RideArmorObj qux_before;
    struct MovingBlockMotion saved = moving_block_motion[0], configured;
    struct Unk_unk68 player_box = { 0, 0, 8, 16 };
    u32 motion = row % 9, edge = row / 9 % 5, wait = row / 45 % 3, fraction = (motion + edge) % 2, layer = (motion + wait) % 4, i;
    s32 camera_x = layer ? (s32)layer * 512 - 320 : 0, camera_y = layer ? (s32)layer * 256 - 240 : 0;
    s32 destination = (camera_y + motions[motion].destination) * 65536 + (fraction ? 0xFFFF : 0);
    assert(saved.x_velocity == 65536 && saved.y_velocity == 0 && saved.range == 144 && saved.vertical == 0);
    configured = saved;
    configured.x_velocity = 0;
    configured.y_velocity = motions[motion].velocity;
    configured.range = 16;
    configured.vertical = 1;
    moving_block_motion[0] = configured;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&qux_object, 0, sizeof(qux_object));
    g_Player.active = 0x41;
    g_Player.unk68 = &player_box;
    g_Player.x_pos.val = (camera_x - 2000) * 65536;
    g_Player.y_pos.val = (camera_y - 2000) * 65536;
    player_before = g_Player;
    entity_before = g_Entity;
    qux_before = qux_object;
    for (i = 0; i < 3; i++) {
        memset(&background_objects[i], 0, sizeof(background_objects[i]));
        background_objects[i].x_pos.val = camera_x * 65536;
        background_objects[i].y_pos.val = camera_y * 65536;
        background_objects[i].unk24 = 0x1234 + i;
    }
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 9;
    obj.state = 1;
    obj.on_screen = 1;
    obj.bg_offset = (s32)layer - 1;
    obj.x_pos.val = (camera_x + x_edges[edge]) * 65536 + 0x1234;
    obj.y_pos.val = destination + (wait == 0 ? motions[motion].velocity : 0);
    obj.y_vel.val = motions[motion].velocity;
    obj.unk68 = (struct Unk_unk68*)moving_block_terrain_box;
    obj.unk7C.saved_pos.x = camera_x + 160;
    obj.unk7C.saved_pos.y = camera_y + 120;
    obj.ext.packed = 0x35254700u | wait_values[wait];
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.y_pos.val = destination;
    if (wait != 0)
        ((u8*)&expected.ext)[0]--;
    if (motions[motion].reverse) {
        expected.y_vel.val = -obj.y_vel.val;
        ((u8*)&expected.ext)[0] = 10;
    }
    if (far_away[edge])
        expected.state = 2;
    else
        expected.on_screen = edge == 0;
    moving_block_update(&obj);
    c_test_same_words(&moving_block_motion[0], &configured, sizeof(configured));
    moving_block_motion[0] = saved;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&qux_object, &qux_before, sizeof(qux_object));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(moving_block_terrain_box[0] == 0 && moving_block_terrain_box[1] == 0 && moving_block_terrain_box[2] == 24 && moving_block_terrain_box[3] == 16);
    assert(player_box.unk0 == 0 && player_box.unk1 == 0 && player_box.unk2 == 8 && player_box.unk3 == 16);
    c_test_same_words(&moving_block_motion[0], &saved, sizeof(saved));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "moving_block_resource_facing", moving_block_resource_facing_cases, moving_block_resource_facing_cases_expected, COUNT(moving_block_resource_facing_cases), 0 },
    { "defined_vertical_motion", NULL, NULL, 54, vertical_motion },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(moving_block_resource_facing_cases) + 54;
