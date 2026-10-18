#include "test_runtime.h"
#include "main/items/item_19_data_capsule.h"
#include "main/195B4.h"
#include "main/mains/main_41_data_hopper.h"
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
    D_801406A8 = metadata;
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
    obj.unk16 = 3;
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
        expected.unk40 = 0x30;
        expected.unk42 = 0x7880;
        expected.unk16 = 6;
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)item_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < 128; i++)
        assert(frames[i] == frames_before[i]);
    for (i = 0; i < 16; i++)
        assert(metadata[i] == metadata_before[i]);
    assert(backref[0] == (mode >= 7 ? 0x80 : 0x11) && backref[1] == 0x22 && backref[2] == 0x33 && backref[3] == 0x44);
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    i = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)obj.unk17 << 16) | ((u32)backref[0] << 24);
    return i;
}
#define CASE(m)                  \
    static u32 capsule_##m(void) \
    {                            \
        return capsule_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
#define ENTRY(m) capsule_##m,
static const CTestCase data_capsule_resources_child_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) };
static const u32 data_capsule_resources_child_pool_cases_expected[] = { 0x110F0141u, 0x11100141u, 0x11110141u, 0x11120141u, 0x11000000u, 0x11000000u, 0x11000000u, 0x80000000u, 0x80000000u, 0x80000000u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "data_capsule_resources_child_pool", data_capsule_resources_child_pool_cases, data_capsule_resources_child_pool_cases_expected, COUNT(data_capsule_resources_child_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(data_capsule_resources_child_pool_cases);
