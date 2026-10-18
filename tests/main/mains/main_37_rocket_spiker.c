#include "test_runtime.h"
#include "main/mains/main_37_rocket_spiker.h"
extern union AnimationStep* rocket_spiker_animations[28];
extern struct Unk_unk68 D_800FE4E4;

struct func_8005FE1C_case {
    u32 unk2, x_pos, y_pos;
    u32 expected[17];
};
static const struct func_8005FE1C_case func_8005FE1C_cases[] = {
    { -1, 6553600, 5242880, { 1u, 0u, 0u, 6u, 4u, 2u, 0u, 0x1234u, 0x640000u, 0x500000u, 0u, 0u, 0x7Cu, 0u, 0u, 0x100u, 0u } },
    { 4, 6553600, 5242880, { 1u, 0u, 0u, 6u, 4u, 2u, 0u, 0x1234u, 0x640000u, 0x500000u, 0u, 0u, 0x7Cu, 0u, 0u, 0x100u, 0u } },
    { 3, 395837440, 57606144, { 1u, 4u, 0u, 6u, 4u, 2u, 0x40u, 0x1236u, 0x17080000u, 0x3500000u, 0xFFFF0000u, 0u, 5u, 0x3301710u, 0x380u, 0x100u, 0x17010003u } },
    { 3, 395837440, 57671680, { 1u, 4u, 0u, 6u, 4u, 2u, 0x40u, 0x1236u, 0x17080000u, 0x3B00000u, 0xFFFF0000u, 0u, 3u, 0x3901710u, 0x40Bu, 0x100u, 0x17010003u } },
    { 3, 395837440, 63963136, { 1u, 4u, 0u, 6u, 4u, 2u, 0x40u, 0x1236u, 0x17080000u, 0x4100000u, 0xFFFF0000u, 0u, 1u, 0x3F01710u, 0x480u, 0x100u, 0x17010003u } },
    { 3, 395902976, 57606144, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x3500000u, 0x10000u, 0u, 4u, 0x33017E0u, 0x380u, 0x100u, 0x17010003u } },
    { 3, 395902976, 57671680, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x3B00000u, 0x10000u, 0u, 2u, 0x39017E0u, 0x40Bu, 0x100u, 0x17010003u } },
    { 3, 395902976, 63963136, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x4100000u, 0x10000u, 0u, 0u, 0x3F017E0u, 0x480u, 0x100u, 0x17010003u } },
};
static u32 test_func_8005FE1C(u32 row)
{
    const struct func_8005FE1C_case* c = &func_8005FE1C_cases[row];
    u32 observed_values[17];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 37;
    obj.unk2 = c->unk2;
    obj.x_pos.val = c->x_pos;
    obj.y_pos.val = c->y_pos;
    obj.unk42 = 0x1234;
    obj.ext.main_37.unk80.word = 0x7A7B7C7D;
    player_before = g_Player;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_8005FE1C(&obj);
    assert(obj.animation_table == (const u8* const*)rocket_spiker_animations);
    assert(obj.terrain_box == &D_800FE4E4);
    assert(obj.unk18.val == obj.x_pos.val && obj.unk1C.val == obj.y_pos.val);
    assert(obj.x_accel == 0 && obj.gravity == 0);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.contact_damage;
    observed_values[5] = (u32)obj.unk62;
    observed_values[6] = (u32)obj.unk15;
    observed_values[7] = (u32)obj.unk42;
    observed_values[8] = (u32)obj.x_pos.val;
    observed_values[9] = (u32)obj.y_pos.val;
    observed_values[10] = (u32)obj.x_speed;
    observed_values[11] = (u32)obj.y_speed;
    observed_values[12] = (u32)((u8*)&obj.ext.main_37)[1];
    observed_values[13] = (u32)obj.ext.main_37.unk84.val;
    observed_values[14] = (u32)obj.ext.main_37.unk88.val;
    observed_values[15] = (u32)obj.ext.main_37.unk8C.val;
    observed_values[16] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8005FE1C", 0, 0, 8, test_func_8005FE1C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 8;
