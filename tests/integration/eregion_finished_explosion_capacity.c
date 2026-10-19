#include "test_runtime.h"
#include "main/mains/main_08_eregion.h"
#include "main/effects/effect_26_boss_death_fx.h"
#include "main/1A5BC.h"
#include "main/55C4.h"
void boss_death_fx_finish(struct EffectObj*);
void boss_death_fx_wait(struct EffectObj*);
void eregion_death_start(struct MainObj*);
void eregion_death_wait_explosion(struct MainObj*);
extern union AnimationStep* D_800FAD68[];
static struct MiscObj expected_misc[64];
static struct EffectObj expected_effects[32];
static struct QuadObj expected_quads[32];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct EffectObj* explosion = &effect_objects[0];
    u32 i;
    (void)row;
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.x_pos.val = 4800 * 65536;
    g_Player.y_pos.val = 363 * 65536;
    background_objects[0].x_pos.val = 4576 * 65536;
    background_objects[0].y_pos.val = 243 * 65536;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    memcpy(expected_quads, g_QuadObjects, sizeof(expected_quads));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 2;
    obj.x_pos.i.hi = 4736;
    obj.y_pos.i.hi = 363;
    obj.animation_table = (const u8* const*)D_800FAD68;
    set_animation(&obj, 0);
    eregion_death_start(&obj);
    for (i = 0; i < 127; i++)
        eregion_death_blink(&obj);
    assert(obj.unk6 == 2 && obj.ext.main_9.effect == explosion && explosion->active == 1 && explosion->id == 26);
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
    player = g_Player;
    player.script_state = 1;
    player.script_action = 0x14;
    player.script_facing = 0x40;
    player.spike_immune = 1;
    engine = engine_obj;
    engine.gameplay_locked = 1;
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    cur_random = 0x1234;
    eregion_death_wait_explosion(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected_misc, sizeof(expected_misc) / 4) == 0);
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(g_QuadObjects, expected_quads, sizeof(expected_quads));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "Eregion_actual_death_factory_last_whiteout_wait_fade_finish_full_misc_pool", NULL, NULL, 1, full } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
