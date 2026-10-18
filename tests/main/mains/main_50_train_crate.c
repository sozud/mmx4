#include "test_runtime.h"
#include "main/mains/main_50_train_crate.h"
#include "main/195B4.h"
#include "main/collision_bounds.h"
extern u8 train_crate_hurt_box[4];

struct func_80069748_case {
    u32 substage, unk2, slot;
    u32 expected[12];
};
static const struct func_80069748_case func_80069748_cases[] = {
    { 0, 0x01, 5, { 9u, 0x788Cu, 1u, 0u, 3u, 1u, 1u, 6u, 0u, 0u, 0x640000u, 0x500000u } },
    { 0, 0x81, 5, { 9u, 0x788Cu, 1u, 8u, 3u, 1u, 1u, 6u, 0u, 1u, 0x640000u, 0x500000u } },
    { 1, 0x01, 7, { 0xDu, 0x78C4u, 1u, 0u, 3u, 1u, 1u, 6u, 0u, 0u, 0x640000u, 0x500000u } },
    { 1, 0x81, 7, { 0xDu, 0x78C4u, 1u, 8u, 3u, 1u, 1u, 6u, 0u, 1u, 0x640000u, 0x500000u } },
};
static u32 test_func_80069748(u32 row)
{
    const struct func_80069748_case* c = &func_80069748_cases[row];
    u32 observed_values[12];
    struct MainObj obj;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u32 frames[64], metadata[32], frames_before[64], metadata_before[32];
    u8 slot;
    memset(&obj, 0, sizeof(obj));
    memset(&frames, 0, sizeof(frames));
    memset(&metadata, 0, sizeof(metadata));
    frames[5] = 128;
    frames[7] = 160;
    metadata[5] = 0x480;
    metadata[7] = 0x680;
    engine_obj.stage = 8;
    engine_obj.substage = c->substage;
    obj.active = 0x41;
    obj.id = 50;
    obj.unk2 = c->unk2;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (void*)frames;
    slot = c->slot;
    assert(s_StageMainIds[8][engine_obj.substage][slot] == 0x28);
    assert((u8)func_8002938C(0x28) == slot);
    engine_before = engine_obj;
    player_before = g_Player;
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(metadata_before, metadata, sizeof(metadata_before));
    func_80069748(&obj);
    assert(obj.hurt_box == train_crate_hurt_box);
    assert(obj.animation_table == (const u8* const*)train_crate_animations);
    assert(obj.sprite_frames == (u8*)frames + frames[slot]);
    assert(obj.terrain_box == 0 && obj.attack_box == 0);
    assert(obj.unk18.val == obj.x_pos.val && obj.unk1C.val == obj.y_pos.val);
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(metadata, metadata_before, sizeof(metadata));
    observed_values[0] = (u32)obj.unk40;
    observed_values[1] = (u32)obj.unk42;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.ext.main_50.unk84;
    observed_values[4] = (u32)obj.hp;
    observed_values[5] = (u32)obj.state;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk16;
    observed_values[8] = (u32)obj.on_screen;
    observed_values[9] = (u32)(obj.collision_data == D_80108584);
    observed_values[10] = (u32)obj.x_pos.val;
    observed_values[11] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80069748", 0, 0, 4, test_func_80069748 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
