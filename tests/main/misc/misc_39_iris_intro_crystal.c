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
    assert(obj->unk5 == 3 && obj->animation_step.packed == C_TEST_STEP(0x40010001));
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    expected_pool[0].unk17 = 16;
    expected_pool[0].previous_animation_index = 255;
    expected_pool[0].animation_cursor = (u32*)iris_animations[16];
    expected_pool[0].animation_step.packed = C_TEST_STEP(0x55010003);
    expected_pool[0].ext.misc_39.timer = 136;
    expected_pool[0].unk5 = 4;
    expected_iris = iris;
    expected_iris.unk17 = 36;
    expected_iris.previous_animation_index = 255;
    expected_iris.animation_cursor = (const u8*)iris_animations[36];
    expected_iris.animation_step.packed = C_TEST_STEP(0x2E010003);
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
static u32 crystal_paths(u32 row);
const struct CTestGroup c_test_groups[] = {
    { "actual_Iris_crystal_factory_214_rise_120_charge_29_transform_full_misc_pool", NULL, NULL, 1, full },
    { "crystal_paths", 0, 0, 5, crystal_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 5;

void func_800CF950(struct MiscObj*);
void iris_intro_crystal_wait(struct MiscObj*);
void iris_intro_crystal_leave(struct MiscObj*);
static u32 crystal_paths(u32 row)
{
    static const u8 layers[] = { 0x21, 0, 0x21, 0, 0x20 };
    struct MiscObj obj;
    struct MainObj iris;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&iris, 0, sizeof(iris));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(D_8013E198, -1, sizeof(D_8013E198));
    obj.active = 0x41;
    obj.id = 39;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.animation_table = (u32**)iris_animations;
    set_animation(&obj, 0xF);
    obj.animation_step.fields.duration = 2;
    obj.ext.misc_39.related = &iris;
    iris.animation_table = (const u8* const*)iris_animations;
    if (row == 0) {
        obj.animation_step.fields.event = 1;
        func_800CF950(&obj);
        assert(obj.unk5 == 4 && obj.ext.misc_39.timer == 0x88 && obj.unk17 == 0x10);
        assert(iris.unk17 == 0x24 && iris.unk6 == 8);
        for (i = 0; i < 5; i++) {
            assert(misc_objects[i].active == 0x41 && misc_objects[i].id == 0x16 && misc_objects[i].unk2 == 8);
            assert(misc_objects[i].unk16 == layers[i] && misc_objects[i].unk17 == i + 0x12);
            assert(misc_objects[i].x_pos.i.hi == 101 && misc_objects[i].y_pos.i.hi == 164);
        }
        return 1;
    }
    obj.ext.misc_39.timer = row == 1 || row == 3 ? 1 : 5;
    if (row <= 2) {
        obj.unk5 = 4;
        iris_intro_crystal_wait(&obj);
        assert(obj.unk5 == (row == 1 ? 5 : 4) && obj.ext.misc_39.timer == (row == 1 ? 0x76 : 4));
        assert(obj.y_vel.val == (row == 1 ? -0x10000 : 0));
    } else {
        obj.unk5 = 5;
        obj.state = 0;
        obj.y_vel.val = -0x10000;
        iris_intro_crystal_leave(&obj);
        assert(obj.state == (row == 3) && obj.y_pos.i.hi == 101);
    }
    return 1;
}
