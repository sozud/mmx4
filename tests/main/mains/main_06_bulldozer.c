#include "test_runtime.h"
#include "main/mains/main_06_bulldozer.h"
extern struct Unk_unk68 bulldozer_hurt_boxes[2];
extern union AnimationStep* D_800FA4E8[];

static const u32 bulldozer_fall_0_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_bulldozer_fall_0(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    bulldozer_fall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, bulldozer_fall_0_expected, 7);
}

static const u32 bulldozer_fall_1_expected[] = { 4u, 0u, 0x640000u, 0x770000u, 0u, 0xBE00u, 0u, 0x4200u, 1u, 0x10002u };
static u32 test_bulldozer_fall_1(u32 row)
{
    u32 observed_values[10];
    struct MainObj obj;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 6;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 7864320;
    func_80046B80(&obj);
    obj.unk5 = 4;
    obj.unk6 = 0;
    obj.air_state = 1;
    obj.collision_flags = 0;
    obj.y_speed = 65536;
    obj.gravity = 16896;
    player_before = g_Player;
    bulldozer_fall(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    observed_values[4] = (u32)obj.x_speed;
    observed_values[5] = (u32)obj.y_speed;
    observed_values[6] = (u32)obj.x_accel;
    observed_values[7] = (u32)obj.gravity;
    observed_values[8] = (u32)obj.air_state;
    observed_values[9] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, bulldozer_fall_1_expected, 10);
}

static const u32 func_80046C8C_expected[] = { 2u, 2u, 1u, 0x7Eu, 0x40u, 0x8000u, 1u, 0u, 0x12u, 0xFFFFFFFFu, 1u, 2u, 0x640000u, 0x780000u, 0u, 0x770054u, 0xA30Du, 1u, 1u };
static u32 test_func_80046C8C(u32 row)
{
    u32 observed_values[19];
    struct MainObj obj;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct ItemObj items_before[32];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    engine_obj.stage = 1;
    cur_random = 0x1234;
    g_Player.spike_immune = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    obj.active = 0x41;
    obj.id = 6;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 7864320;
    func_80046B80(&obj);
    obj.unk6 = 1;
    obj.unk7C = 2;
    obj.collision_flags = 8;
    obj.ext.main_6.core_health = 0;
    assert(obj.unk15 == 0x40 && obj.ext.main_6.hitbox_toggle == 0);
    assert(obj.animation_table == (const u8* const*)D_800FA4E8);
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 1;
    weapon_objects[0].unk15 = 0x40;
    weapon_objects[0].unk50 = (const u8*)&bulldozer_hurt_boxes[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(items_before, item_objects, sizeof(items_before));
    func_80046C8C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk15;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.ext.main_6.armor_broken;
    observed_values[8] = (u32)obj.ext.main_6.armor_health;
    observed_values[9] = (u32)obj.ext.main_6.core_health;
    observed_values[10] = (u32)obj.ext.main_6.hitbox_toggle;
    observed_values[11] = (u32)obj.ext.main_6.saved_step;
    observed_values[12] = (u32)obj.x_pos.val;
    observed_values[13] = (u32)obj.y_pos.val;
    observed_values[14] = (u32)weapon_objects[0].unk98;
    observed_values[15] = (u32)weapon_objects[0].unk80.word;
    observed_values[16] = (u32)cur_random;
    observed_values[17] = (u32)(obj.hurt_box == (const void*)&bulldozer_hurt_boxes[1]);
    observed_values[18] = (u32)(obj.attack_box == (const void*)&bulldozer_hurt_boxes[1]);
    return c_test_observe(0, row, observed_values, func_80046C8C_expected, 19);
}

const struct CTestGroup c_test_groups[] = {
    { "bulldozer_fall_0", 0, 0, 1, test_bulldozer_fall_0 },
    { "bulldozer_fall_1", 0, 0, 1, test_bulldozer_fall_1 },
    { "func_80046C8C", 0, 0, 1, test_func_80046C8C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 1;
