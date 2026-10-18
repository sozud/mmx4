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
const struct CTestGroup c_test_groups[] = {
    { "moving_block_resource_facing", moving_block_resource_facing_cases, moving_block_resource_facing_cases_expected, COUNT(moving_block_resource_facing_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(moving_block_resource_facing_cases);
