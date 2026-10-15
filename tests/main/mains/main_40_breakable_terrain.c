#include "test_runtime.h"
extern s8* D_800FEA24[7];
extern struct Unk_unk68 D_800FEAA0;
extern union AnimationStep* breakable_terrain_animations[6];

struct func_80061F2C_0_case {
    u32 unk80;
    u32 expected[15];
};
static const struct func_80061F2C_0_case func_80061F2C_0_cases[] = {
    { 0, { 0x41u, 1u, 0u, 0u, 0x1234u, 0u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 7, { 0x41u, 1u, 0u, 0u, 0x1234u, 0u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_80061F2C_0(u32 row)
{
    const struct func_80061F2C_0_case* c = &func_80061F2C_0_cases[row];
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&visual_objects, 1, sizeof(visual_objects));
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk42 = 0x1234;
    obj.ext.main_40.unk80 = c->unk80;
    g_Player.spike_immune = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    g_Player.unk68 = &D_800FEAA0;
    player_before = g_Player;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_80061F2C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.ext.main_40.timer;
    observed_values[9] = (u32)obj.ext.main_40.trigger_time;
    observed_values[10] = (u32)obj.unk63;
    observed_values[11] = (u32)obj.unk65;
    observed_values[12] = (u32)weapon_objects[0].unk98;
    observed_values[13] = (u32)weapon_objects[0].unk80.word;
    observed_values[14] = (u32)(obj.animation_table == (const u8* const*)breakable_terrain_animations);
    return c_test_observe(0, row, observed_values, c->expected, 15);
}
static const u32 func_80061F2C_1_expected[] = { 0x41u, 1u, 0u, 2u, 0x9234u, 1u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0x500064u, 1u };
static u32 test_func_80061F2C_1(u32 row)
{
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&visual_objects, 1, sizeof(visual_objects));
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk42 = 0x1234;
    obj.ext.main_40.unk80 = 1;
    g_Player.spike_immune = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    g_Player.unk68 = &D_800FEAA0;
    obj.unk2 = 0x10;
    obj.state = 0;
    func_80061DFC(&obj);
    assert(obj.hp == 3 && obj.state == 1);
    assert(obj.hurt_box == (const u8*)D_800FEA24[1]);
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 1;
    weapon_objects[0].unk50 = (const u8*)D_800FEA24[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    player_before = g_Player;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_80061F2C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.ext.main_40.timer;
    observed_values[9] = (u32)obj.ext.main_40.trigger_time;
    observed_values[10] = (u32)obj.unk63;
    observed_values[11] = (u32)obj.unk65;
    observed_values[12] = (u32)weapon_objects[0].unk98;
    observed_values[13] = (u32)weapon_objects[0].unk80.word;
    observed_values[14] = (u32)(obj.animation_table == (const u8* const*)breakable_terrain_animations);
    return c_test_observe(1, row, observed_values, func_80061F2C_1_expected, 15);
}
static u32 test_func_80061F2C(u32 index)
{
    if (index < 2)
        return test_func_80061F2C_0(index);
    index -= 2;
    return test_func_80061F2C_1(index);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80061F2C", 0, 0, 3, test_func_80061F2C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
