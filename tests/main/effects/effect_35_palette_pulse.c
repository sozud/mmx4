#include "test_runtime.h"
#include "main/effects/effect_35_palette_pulse.h"
extern u16 palette_pulse_palette[16];
static struct MainObj expected_pool[48];
static u32 palette[385], expected_palette[385];
static u32 full(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    struct BackgroundObj background;
    u32 i;
    (void)row;
    engine_obj.stage = 5;
    engine_obj.substage = 0;
    engine = engine_obj;
    background_objects[0].x_pos.i.hi = 15696;
    background_objects[0].y_pos.i.hi = 0;
    background = background_objects[0];
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    memcpy(expected_pool, main_objects, sizeof(expected_pool));
    for (i = 0; i < COUNT(palette); i++)
        palette[i] = expected_palette[i] = 0xBEEFBEEF;
    for (i = 0; i < 16; i++)
        ((u16*)expected_palette)[752 + i] = palette_pulse_palette[i];
    TEST_PALETTE = (u8*)palette;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 35;
    obj.x_pos.i.hi = 15856;
    obj.y_pos.i.hi = 130;
    expected = obj;
    expected.state = 1;
    expected.ext.unk_effect.unk14 = 7;
    expected.ext.unk_effect.unk15 = 1;
    expected.ext.effect_4.unk16 = 35;
    cur_random = 0x1234;
    palette_pulse_update(&obj);
    assert(obj.state == 1 && obj.ext.unk_effect.unk14 == 1 && obj.ext.effect_4.unk16 == 32);
    c_test_same_words(palette, expected_palette, sizeof(palette));
    palette_pulse_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(main_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(palette, expected_palette, sizeof(palette));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&background_objects[0], &background, sizeof(background));
    assert(cur_random == 0x1234 && TEST_PALETTE == (u8*)palette);
    return 1;
}

extern u16 palette_pulse_palette[16];
static struct MainObj expected_pool_palette_pulse_scroll_cap[48];
static u32 palette_palette_pulse_scroll_cap[385], expected_palette_palette_pulse_scroll_cap[385];
static u32 full_palette_pulse_scroll_cap(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    struct BackgroundObj background;
    u32 i;
    (void)row;
    engine_obj.stage = 5;
    engine_obj.substage = 0;
    engine = engine_obj;
    background_objects[0].x_pos.i.hi = 15696;
    background_objects[0].y_pos.i.hi = 0;
    background = background_objects[0];
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    memcpy(expected_pool_palette_pulse_scroll_cap, main_objects, sizeof(expected_pool_palette_pulse_scroll_cap));
    for (i = 0; i < COUNT(palette_palette_pulse_scroll_cap); i++)
        palette_palette_pulse_scroll_cap[i] = expected_palette_palette_pulse_scroll_cap[i] = 0xBEEFBEEF;
    for (i = 0; i < 16; i++)
        ((u16*)expected_palette_palette_pulse_scroll_cap)[752 + i] = palette_pulse_palette[i];
    TEST_PALETTE = (u8*)palette_palette_pulse_scroll_cap;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 35;
    obj.x_pos.i.hi = 15856;
    obj.y_pos.i.hi = 130;
    expected = obj;
    expected.state = 1;
    expected.ext.unk_effect.unk14 = 7;
    expected.ext.unk_effect.unk15 = 0;
    expected.ext.effect_4.unk16 = 113;
    cur_random = 0x1234;
    palette_pulse_update(&obj);
    assert(obj.state == 1 && obj.ext.unk_effect.unk14 == 1 && obj.ext.effect_4.unk16 == 32);
    assert(c_test_word_difference(palette_palette_pulse_scroll_cap, expected_palette_palette_pulse_scroll_cap, COUNT(palette_palette_pulse_scroll_cap)) == 0);
    for (i = 0; i < 190; i++)
        palette_pulse_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected_pool_palette_pulse_scroll_cap, sizeof(expected_pool_palette_pulse_scroll_cap) / 4) == 0);
    assert(c_test_word_difference(palette_palette_pulse_scroll_cap, expected_palette_palette_pulse_scroll_cap, COUNT(palette_palette_pulse_scroll_cap)) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&background_objects[0], &background, sizeof(background));
    assert(cur_random == 0x1234 && TEST_PALETTE == (u8*)palette_palette_pulse_scroll_cap);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "shipped_Jet_Stingray_palette_pulse_first_five_rocks_full_main_pool", NULL, NULL, 1, full },
    { "own_palette_pulse_28_waves_scroll_32_to_113_then_cap_full_main_pool", NULL, NULL, 1, full_palette_pulse_scroll_cap },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1;
