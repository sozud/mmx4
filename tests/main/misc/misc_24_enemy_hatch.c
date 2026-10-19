#include "test_runtime.h"
#include "main/55C4.h"
void enemy_hatch_wait_start(struct MiscObj*);
void func_800CC114(struct MiscObj*);
extern union AnimationStep* enemy_hatch_animations[4];
static struct MiscObj expected_pool[64];
static u32 full(u32 row)
{
    struct MiscObj* obj = &misc_objects[0];
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    engine = engine_obj;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    obj->active = 0x41;
    obj->id = 24;
    obj->state = 1;
    obj->x_pos.i.hi = 984;
    obj->y_pos.i.hi = 936;
    obj->animation_table = (u32**)enemy_hatch_animations;
    enemy_hatch_wait_start(obj);
    for (i = 0; i < 43; i++)
        func_800CC114(obj);
    assert(obj->unk5 == 0 && obj->unk6 == 1 && obj->animation_cursor == (u32*)enemy_hatch_animations[0] + 14 && obj->animation_step.fields.duration == 1);
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    expected_pool[0].unk5 = 1;
    expected_pool[0].unk6 = 0;
    expected_pool[0].animation_cursor = (u32*)enemy_hatch_animations[0] + 15;
    expected_pool[0].animation_step.packed = 0x0C000003;
    cur_random = 0x1234;
    func_800CC114(obj);
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

void enemy_hatch_release_spawn(struct MiscObj*);
extern union AnimationStep* enemy_hatch_animations[4];
static struct MainObj pool_expected[48];
static u32 release(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 type = row % 2, full = row / 2 % 2, face = row / 4, i;
    engine_obj.stage = 6;
    engine_obj.substage = type ? 0 : 1;
    engine_before = engine_obj;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = i == 47 && !full ? 0 : 1;
    memcpy(pool_expected, main_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 24;
    obj.unk2 = type;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = (type ? 751 : 984) * 65536 + 0x1234;
    obj.y_pos.val = (type ? 608 : 936) * 65536 + 0x5678;
    obj.animation_table = (u32**)enemy_hatch_animations;
    set_animation(&obj, 0);
    expected = obj;
    expected.unk17 = 1;
    expected.animation_cursor = (u32*)enemy_hatch_animations[1];
    expected.animation_step.packed = 0x0D010002;
    D_8013E198[2] = -1;
    if (!full) {
        struct MainObj* m = &pool_expected[47];
        m->active = 0x41;
        m->id = type ? 3 : 48;
        m->unk2 = -128;
        m->unk15 = obj.unk15;
        m->x_pos = obj.x_pos;
        m->y_pos.val = obj.y_pos.val - (type ? 4 * 65536 : 0);
        expected.ext.misc_5.owner = &main_objects[47];
        expected.ext.misc_24.timer = 32;
        expected.unk6 = 1;
    }
    enemy_hatch_release_spawn(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(main_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "own_hatch_animation_tick_44_child_all_64_misc_slots_full", NULL, NULL, 1, full },
    { "both_shipped_Cyber_Peacock_hatches_full_48_main_slots_and_last_slot", NULL, NULL, 8, release },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 8;
