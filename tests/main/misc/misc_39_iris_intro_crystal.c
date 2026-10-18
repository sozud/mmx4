#include "test_runtime.h"
#include "main/55C4.h"
#include "main/misc/misc_39_iris_intro_crystal.h"
#include "main/mains/main_66_iris.h"
void iris_intro_crystal_charge(struct MiscObj*);
void iris_intro_crystal_rise(struct MiscObj*);
void iris_intro_crystal_start(struct MiscObj*);
extern union AnimationStep* iris_animations[37];
static struct MiscObj expected_pool[64];
static u32 full(u32 row)
{
    struct MainObj iris, expected_iris;
    struct MiscObj* obj = &misc_objects[0];
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 11;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_ZERO;
    g_Player.unk2 = CHARACTER_ZERO;
    player = g_Player;
    engine = engine_obj;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 1; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memset(&iris, 0, sizeof(iris));
    iris.active = 0x41;
    iris.id = 66;
    iris.state = 1;
    iris.unk5 = 2;
    iris.unk6 = 6;
    iris.unk7C = 40;
    iris.x_pos.i.hi = 2304;
    iris.y_pos.i.hi = 446;
    iris.animation_table = (const u8* const*)iris_animations;
    set_animation(&iris, 9);
    for (i = 0; i < 40; i++)
        iris_intro_toss_crystal(&iris);
    assert(iris.unk6 == 7 && obj->active == 0x41 && obj->id == 39 && obj->ext.misc_39.related == ANIMATED_OBJECT(&iris));
    iris_intro_crystal_start(obj);
    for (i = 0; i < 214; i++)
        iris_intro_crystal_rise(obj);
    assert(obj->unk5 == 2 && obj->y_pos.val == 308 * 65536);
    for (i = 0; i < 120; i++)
        iris_intro_crystal_charge(obj);
    assert(obj->unk5 == 3 && obj->unk17 == 12 && iris.unk17 == 33);
    for (i = 0; i < 28; i++)
        func_800CF950(obj);
    assert(obj->unk5 == 3 && obj->animation_step.packed == 0x40010001);
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    expected_pool[0].unk17 = 16;
    expected_pool[0].previous_animation_index = 255;
    expected_pool[0].animation_cursor = (u32*)iris_animations[16];
    expected_pool[0].animation_step.packed = 0x55010003;
    expected_pool[0].ext.misc_39.timer = 136;
    expected_pool[0].unk5 = 4;
    expected_iris = iris;
    expected_iris.unk17 = 36;
    expected_iris.previous_animation_index = 255;
    expected_iris.animation_cursor = (const u8*)iris_animations[36];
    expected_iris.animation_step.packed = 0x2E010003;
    expected_iris.unk6 = 8;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    func_800CF950(obj);
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&iris, &expected_iris, sizeof(iris));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && D_8013E198[2] == -1);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "actual_Iris_crystal_factory_214_rise_120_charge_29_transform_full_misc_pool", NULL, NULL, 1, full } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
