#include "test_runtime.h"
#include "main/mains/main_64_cyber_peacock.h"
#include "main/effects/effect_26_boss_death_fx.h"
#include "main/1AC84.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/mains/main_61_split_mushroom.h"
void boss_death_fx_finish(struct EffectObj*);
void boss_death_fx_wait(struct EffectObj*);
void jet_stingray_death_finish(struct MainObj*);
void jet_stingray_death_start(struct MainObj*);
void split_mushroom_death_finish(struct MainObj*);
void split_mushroom_death_start(struct MainObj*);
extern void* jet_stingray_animations[45];
extern void* split_mushroom_animations[26];
extern void* cyber_peacock_animations[38];
extern u16 player_stage_12_entry_y[20];
static struct EffectObj effects_before[32];
static struct QuadObj quads_before[32];
static struct BackgroundObj backgrounds_before[3];
static u32 finish(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct EffectObj* explosion = &effect_objects[0];
    u32 i, checkpoint = row == 0 ? 5 : row == 1 ? 4
                                                : 3;
    engine_obj.stage = 12;
    engine_obj.substage = 0;
    engine_obj.checkpoint = checkpoint;
    engine_obj.enable_boss = 1;
    engine_obj.boss_ptr = &obj;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = row == 0 ? 2688 : row == 1 ? 1872
                                                     : 1152;
    g_Player.y_pos.i.hi = player_stage_12_entry_y[checkpoint];
    background_objects[0].x_pos.i.hi = row == 0 ? 2576 : row == 1 ? 1792
                                                                  : 1040;
    background_objects[0].y_pos.i.hi = 1536;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = row == 0 ? 56 : row == 1 ? 61
                                      : 64;
    obj.state = 2;
    obj.x_pos.i.hi = row == 0 ? 2693 : row == 1 ? 2032
                                                : 1296;
    obj.y_pos.i.hi = row == 0 ? 1716 : row == 1 ? 1664
                                                : 1656;
    obj.animation_table = (const u8* const*)(row == 0 ? jet_stingray_animations : row == 1 ? split_mushroom_animations
                                                                                           : cyber_peacock_animations);
    if (row == 0)
        jet_stingray_death_start(&obj);
    else if (row == 1)
        split_mushroom_death_start(&obj);
    else
        cyber_peacock_death_start(&obj);
    for (i = 0; i < 127; i++) {
        if (row == 0)
            jet_stingray_death_explode(&obj);
        else if (row == 1)
            split_mushroom_death_explode(&obj);
        else
            cyber_peacock_death_explode(&obj);
    }
    assert(obj.unk5 == 2 && explosion->active == 1 && explosion->id == 26);
    assert((row == 0 ? obj.ext.main_56.object.effect : row == 1 ? obj.ext.main_61.data.effect
                                                                : obj.ext.main_64.object)
        == explosion);
    explosion->state = 4;
    explosion->ext.effect_26.timer = 154;
    explosion->ext.effect_26.quad_timer = 4;
    g_FilterAmountR = 30;
    g_FilterAmountG = 0x3C0;
    g_FilterAmountB = 0x7800;
    D_8013E198[0] = -1;
    func_800BB750(explosion);
    assert(explosion->state == 5 && explosion->ext.effect_26.timer == 40 && explosion->unk7 == 1);
    for (i = 0; i < 41; i++)
        boss_death_fx_wait(explosion);
    assert(explosion->state == 6 && explosion->ext.effect_26.timer == 65535);
    for (i = 0; i < 151; i++)
        func_800BB888(explosion);
    assert(explosion->state == 7 && g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    boss_death_fx_finish(explosion);
    assert(explosion->active == 0);
    expected = obj;
    ((u32*)&expected)[0] = ((u32*)&expected)[1] = 0;
    expected.on_screen = 0;
    engine = engine_obj;
    engine.unkF = -128;
    engine.character_state.bytes[checkpoint + 6] = 1;
    engine.checkpoint += 9;
    if (row == 1) {
        for (i = 0; i < 6; i++)
            expected.ext.raw[i] = 0;
        engine.enable_boss = 0;
        engine.boss_ptr = NULL;
    }
    player = g_Player;
    memcpy(effects_before, effect_objects, sizeof(effects_before));
    memcpy(quads_before, g_QuadObjects, sizeof(quads_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    cur_random = 0x1234;
    if (row == 0)
        jet_stingray_death_finish(&obj);
    else if (row == 1)
        split_mushroom_death_finish(&obj);
    else
        cyber_peacock_death_finish(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    assert(c_test_word_difference((u32*)effect_objects, (u32*)effects_before, sizeof(effects_before) / 4) == 0);
    assert(c_test_word_difference((u32*)g_QuadObjects, (u32*)quads_before, sizeof(quads_before) / 4) == 0);
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == 0x1234);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "stage12_real_rematch_finished_explosion_return_checkpoints_Jet_Mushroom_Peacock", NULL, NULL, 3, finish } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
