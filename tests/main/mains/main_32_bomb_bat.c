#include "test_runtime.h"
void bomb_bat_drop_end(struct MainObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 drop_case(u32 wait)
{
    struct MainObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 32;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7C = 0x7777;
    obj.ext.main_32.unk80 = wait ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.animation_table = (const u8* const*)bomb_bat_animations;
    set_animation(&obj, 0);
    before = obj;
    bomb_bat_drop_end(&obj);
    before.ext.main_32.unk80--;
    if (wait)
        before.animation_step.fields.duration = 2;
    else {
        before.unk5 = 4;
        before.unk6 = 0;
        before.unk17 = 3;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)bomb_bat_animations[3];
        before.animation_step = *bomb_bat_animations[3];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.ext.main_32.unk80 << 16) | ((u32)obj.unk17 << 24);
}
#define CASE(m)                                           \
    static u32 bomb_bat_drop_animation_end_drop_##m(void) \
    {                                                     \
        return drop_case(m);                              \
    }
CASE(0)
CASE(1)
#define ENTRY(m) bomb_bat_drop_animation_end_drop_##m,
static const CTestCase bomb_bat_drop_animation_end_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 bomb_bat_drop_animation_end_cases_expected[] = { 0x3000004u, 0x10203u };
#undef CASE
#undef ENTRY

static const u32 bomb_bat_drop_bomb_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_bomb_bat_drop_bomb(u32 row)
{
    u32 observed_values[10];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    bomb_bat_drop_bomb(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    observed_values[8] = (u32)shot_objects[0].x_pos.val;
    observed_values[9] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, bomb_bat_drop_bomb_expected, 10);
}

static const u32 bomb_bat_drop_end_expected[] = { 0xFFFFFFFFu, 0u, 0u };
static u32 test_bomb_bat_drop_end(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    bomb_bat_drop_end(&obj);
    observed_values[0] = (u32)obj.ext.main_32.unk80;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, bomb_bat_drop_end_expected, 3);
}

static const u32 bomb_bat_main_0_expected[] = { 0u, 1u, 0x1606060u, 0u };
static u32 test_bomb_bat_main_0(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = 23093344;
    obj.y_pos.val = 0;
    obj.unk5 = 1;
    obj.ext.main_32.unk88 = 2;
    obj.state = 0;
    bomb_bat_main(&obj);
    observed_values[0] = (u32)obj.ext.main_32.saved_unk5;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk18.val;
    observed_values[3] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, bomb_bat_main_0_expected, 4);
}

struct bomb_bat_main_1_case {
    u32 saved_unk5, unk88, obj_hp, fatal, expected_hp;
    u32 expected[6];
};
static const struct bomb_bat_main_1_case bomb_bat_main_1_cases[] = {
    { 2, 0, 16, 0, 13, { 1u, 0xDu, 2u, 0x9234u, 0x630063u, 0x1234u } },
    { 4, 1, 3, 1, 0, { 2u, 0u, 4u, 0x9234u, 0x630063u, 0xA30Du } },
    { 2, 0, 3, 1, 0, { 2u, 0u, 2u, 0x9234u, 0x630063u, 0xA30Du } },
};
static u32 test_bomb_bat_main_1(u32 row)
{
    const struct bomb_bat_main_1_case* c = &bomb_bat_main_1_cases[row];
    u32 observed_values[6];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct WeaponObj weapons_expected[16];
    struct ShotObj shots_before[32];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct ItemObj items_before[32];
    u8 pools_full, fatal;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 32;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    D_8013E198[0] = -1;
    D_8013E198[1] = -1;
    D_8013E198[2] = -1;
    D_8013E198[3] = -1;
    D_8013E198[4] = -1;
    D_8013E198[5] = -1;
    g_Player.bg_offset = 0;
    g_Player.spike_immune = 1;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    cur_random = 0x1234;
    func_8005C860(&obj);
    obj.unk5 = 1;
    obj.ext.main_32.saved_unk5 = c->saved_unk5;
    obj.ext.main_32.unk88 = c->unk88;
    obj.hp = c->obj_hp;
    fatal = c->fatal;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
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
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 0;
    weapon_objects[0].unk50 = (const u8*)lemon_hit_box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    expected = obj;
    expected.unk5 = obj.ext.main_32.saved_unk5;
    expected.hp = c->expected_hp;
    expected.unk42 = 0x9234;
    expected.on_screen = 1;
    if (fatal) {
        expected.state = 2;
    }
    if (fatal) {
        expected.on_screen = 0;
    }
    player_before = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    weapons_expected[0].unk98 = 1;
    weapons_expected[0].unk80.word = 0x00630063;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(items_before, item_objects, sizeof(items_before));
    assert(((const u8*)D_80107274)[1] == 3);
    bomb_bat_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_before));
    c_test_same_words(item_objects, items_before, sizeof(items_before));
    assert(D_8013E198[0] == -1 && D_8013E198[1] == -1 && D_8013E198[2] == -1 && D_8013E198[3] == -1 && D_8013E198[4] == -1 && D_8013E198[5] == -1);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.hp;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)weapon_objects[0].unk80.word;
    observed_values[5] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

struct func_8005C860_case {
    u32 unk2;
    u32 expected[22];
};
static const struct func_8005C860_case func_8005C860_cases[] = {
    { 1, { 0x41u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 1u, 6u, 0u, 0u, 5u, 0u, 0u, 0u, 0u } },
    { -1, { 0x41u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 1u, 6u, 0u, 0u, 6u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_8005C860(u32 row)
{
    const struct func_8005C860_case* c = &func_8005C860_cases[row];
    u32 observed_values[22];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&bomb_bat_body_box, 0, sizeof(bomb_bat_body_box));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = c->unk2;
    func_8005C860(&obj);
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.air_state;
    observed_values[2] = (u32)obj.bg_offset;
    observed_values[3] = (u32)obj.contact_damage;
    observed_values[4] = (u32)obj.ext.main_32.saved_unk5;
    observed_values[5] = (u32)obj.ext.main_32.unk80;
    observed_values[6] = (u32)obj.ext.main_32.unk84;
    observed_values[7] = (u32)obj.ext.main_32.unk88;
    observed_values[8] = (u32)obj.ext.main_32.unk8C;
    observed_values[9] = (u32)obj.ext.main_32.unk90;
    observed_values[10] = (u32)obj.gravity;
    observed_values[11] = (u32)obj.hp;
    observed_values[12] = (u32)obj.invincibility_timer;
    observed_values[13] = (u32)obj.state;
    observed_values[14] = (u32)obj.unk16;
    observed_values[15] = (u32)obj.unk18.val;
    observed_values[16] = (u32)obj.unk1C.val;
    observed_values[17] = (u32)obj.unk5;
    observed_values[18] = (u32)obj.unk6;
    observed_values[19] = (u32)obj.x_accel;
    observed_values[20] = (u32)obj.x_speed;
    observed_values[21] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 22);
}

struct func_8005CF9C_case {
    u32 unk2, unk15, cur_random, x_speed, unk7C, unk6, random_after;
    u32 expected[7];
};
static const struct func_8005CF9C_case func_8005CF9C_cases[] = {
    { 2, 0, 1, -229119, 1, 1, 1, { 0xFFFC8101u, 0x18000u, 0xFFFFF000u, 1u, 1u, 0xE010005u, 1u } },
    { 2, 64, 2, 228862, 2, 1, 2, { 0x37DFEu, 0x18000u, 0xFFFFF000u, 1u, 2u, 0xE010005u, 2u } },
    { 3, 0, 4660, -256525, 7, 2, 59894, { 0xFFFC15F3u, 0x18000u, 0xFFFFF000u, 2u, 7u, 0xE010005u, 0xE9F6u } },
    { 3, 64, 119, 260220, 7, 2, 3465, { 0x3F87Cu, 0x18000u, 0xFFFFF000u, 2u, 7u, 0xE010005u, 0xD89u } },
};
static u32 test_func_8005CF9C(u32 row)
{
    const struct func_8005CF9C_case* c = &func_8005CF9C_cases[row];
    u32 observed_values[7];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u16 random_after;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 32;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    g_Player.bg_offset = 0;
    obj.unk2 = c->unk2;
    func_8005C860(&obj);
    obj.unk15 = c->unk15;
    obj.unk5 = 6;
    obj.unk6 = 0;
    obj.unk7C = 7;
    cur_random = c->cur_random;
    expected = obj;
    set_animation(&expected, 3);
    expected.x_speed = c->x_speed;
    expected.y_speed = 0x18000;
    expected.x_accel = -0x1000;
    expected.attack_box = &bomb_bat_body_box;
    expected.ext.main_32.unk88 = 1;
    expected.unk7C = c->unk7C;
    expected.unk6 = c->unk6;
    random_after = c->random_after;
    player_before = g_Player;
    engine_before = engine_obj;
    func_8005CF9C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == random_after);
    observed_values[0] = (u32)obj.x_speed;
    observed_values[1] = (u32)obj.y_speed;
    observed_values[2] = (u32)obj.x_accel;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.animation_step.packed;
    observed_values[6] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

const struct CTestGroup c_test_groups[] = {
    { "bomb_bat_drop_animation_end", bomb_bat_drop_animation_end_cases, bomb_bat_drop_animation_end_cases_expected, COUNT(bomb_bat_drop_animation_end_cases), 0 },
    { "bomb_bat_drop_bomb", 0, 0, 1, test_bomb_bat_drop_bomb },
    { "bomb_bat_drop_end", 0, 0, 1, test_bomb_bat_drop_end },
    { "bomb_bat_main_0", 0, 0, 1, test_bomb_bat_main_0 },
    { "bomb_bat_main_1", 0, 0, 3, test_bomb_bat_main_1 },
    { "func_8005C860", 0, 0, 2, test_func_8005C860 },
    { "func_8005CF9C", 0, 0, 4, test_func_8005CF9C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bomb_bat_drop_animation_end_cases) + 1 + 1 + 1 + 3 + 2 + 4;
