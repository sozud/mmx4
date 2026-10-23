#include "test_runtime.h"
#include "main/mains/main_14_ice_bird.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/effects/effect_17_freeze_blast.h"
#include "main/1AC84.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u8 sound_entries[65 * 4];
static u32 bird_case(u32 mode)
{
    struct MainObj obj, expected;
    struct VisualObj pool[32];
    struct BackgroundObj backgrounds[3];
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u8 spawn = 0xFF;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(sound_entries, 0, sizeof(sound_entries));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[2] = sound_entries;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    if (mode == 1 || mode == 3)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.on_screen = 1;
    obj.unk5 = 2;
    obj.unk6 = 0;
    obj.unk7 = 7;
    obj.unk2 = 1;
    obj.unk15 = mode & 2 ? 0x40 : 0;
    obj.unk16 = 8;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.ext.main_14.unk80 = 9;
    obj.ext.main_14.unk84 = 8;
    obj.ext.main_14.visual_variant = 7;
    obj.ext.main_14.unk94 = mode == 5;
    obj.backref = &spawn;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    set_animation(&obj, 0);
    engine_obj.character_state.bytes[0] = 7;
    expected = obj;
    engine_before = engine_obj;
    memcpy(pool, visual_objects, sizeof(pool));
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    if (mode < 4) {
        expected.animation_step.fields.duration = 4;
        expected.ext.main_14.unk80 = 0x20;
        expected.ext.main_14.unk84 = 1;
        assert(ice_bird_fly_speeds[0] == -131072 && ice_bird_fly_speeds[1] == 131072);
        expected.x_speed = mode & 2 ? 131072 : -131072;
        expected.unk6 = 1;
        if (mode == 1 || mode == 3) {
            struct VisualObj* child = &pool[31];
            expected.ext.main_14.visual_variant = 3;
            child->unk50 = PLAYER_OBJECT(&obj);
            child->active = 0x41;
            child->unk2 = 3;
            child->id = 0xB;
            child->state = child->unk5 = child->unk6 = 0;
            child->unk38 = 0;
            child->unk3C = ANIMATED_OBJECT(&obj)->unk3C;
            child->animation_table = ANIMATED_OBJECT(&obj)->animation_table;
            child->unk40 = obj.unk40;
            child->unk42 = obj.unk42;
            child->unk16 = 4;
            child->x_pos = obj.x_pos;
            child->y_pos = obj.y_pos;
        }
        ice_bird_fly_in_start(&obj);
    } else {
        expected.ext.main_14.unk80 = expected.ext.main_14.unk84 = 0;
        engine_before.character_state.bytes[0] = 0;
        expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
        expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
        ice_bird_despawn(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(backgrounds) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(spawn == (mode == 5 ? 0x70 : 0xFF));
    for (i = 0; i < sizeof(sound_entries); i++)
        assert(sound_entries[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.unk6 | ((u32)(u8)visual_objects[31].active << 8) | ((u32)spawn << 16);
}
static const u32 ice_bird_flight_and_despawn_cases_expected[] = { 0xFF0101u, 0xFF4101u, 0xFF0101u, 0xFF4101u, 0xFF0100u, 0x700100u };

struct func_8004D6FC_1_case {
    u32 unk5, obj_main_14_unk84, obj_main_14_visual_variant, expected_main_14_unk84;
    u32 expected_main_14_visual_variant;
};
static const struct func_8004D6FC_1_case func_8004D6FC_1_cases[] = {
    { 3, 1, 2, 0, 3 },
    { 3, 1, 3, 30, 4 },
    { 3, 1, 4, 20, 5 },
    { 3, 1, 5, 50, 6 },
    { 3, 1, 6, 0, 7 },
    { 3, 1, 7, 0, 7 },
    { 3, 0, 2, 4294967295, 2 },
    { 2, 1, 2, 1, 2 },
    { 5, 1, 2, 1, 2 },
};
static u32 test_func_8004D6FC_1(u32 row)
{
    const struct func_8004D6FC_1_case* c = &func_8004D6FC_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = c->unk5;
    obj.ext.main_14.unk84 = c->obj_main_14_unk84;
    obj.ext.main_14.visual_variant = c->obj_main_14_visual_variant;
    expected = obj;
    expected.ext.main_14.unk84 = c->expected_main_14_unk84;
    expected.ext.main_14.visual_variant = c->expected_main_14_visual_variant;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004D6FC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct ice_bird_blast_release_case {
    u32 full;
};
static const struct ice_bird_blast_release_case ice_bird_blast_release_cases[] = {
    { 1 },
    { 0 },
};
static u32 test_ice_bird_blast_release(u32 row)
{
    const struct ice_bird_blast_release_case* c = &ice_bird_blast_release_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct EffectObj effects_expected[32];
    struct VisualObj visuals_before[32];
    u8 sound[264], sound_before[264];
    u8 full, pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.unk2 = 3;
    obj.ext.main_14.visual_variant = 0xFF;
    D_8013E198[2] = -1;
    memset(sound, 0, sizeof(sound));
    D_80141F50[2] = sound;
    memcpy(sound_before, sound, sizeof(sound_before));
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    full = c->full;
    if (!full) {
        memset(&effect_objects[31], 0, sizeof(effect_objects[31]));
    }
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    if (!full) {
        effects_expected[31].active = 1;
    }
    if (!full) {
        effects_expected[31].id = 0x11;
    }
    if (!full) {
        effects_expected[31].unk2 = obj.unk2;
    }
    if (!full) {
        effects_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        effects_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        effects_expected[31].ext.effect_17.source = ANIMATED_OBJECT(&obj);
    }
    expected = obj;
    expected.animation_step.fields.duration = 4;
    expected.unk6 = 3;
    player_expected = g_Player;
    engine_before = engine_obj;
    ice_bird_blast_release(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(effect_objects, effects_expected, sizeof(effects_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(sound, sound_before, sizeof(sound));
    assert(D_80141F50[2] == sound);
    assert(D_8013E198[2] == -1);
    return 1;
}

static const u32 ice_bird_face_player_expected[] = { 0x40u };
static u32 test_ice_bird_face_player(u32 row)
{
    u32 observed_values[1];
    struct AnimatedObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    ice_bird_face_player(&obj);
    observed_values[0] = (u32)obj.unk15;
    return c_test_observe(0, row, observed_values, ice_bird_face_player_expected, 1);
}

struct ice_bird_main_1_case {
    u32 saved_unk5, unk8C, obj_x_pos_hi, g_Player_x_pos_hi, unk5, state, on_screen, unk42, unk84, unk94;
};
static const struct ice_bird_main_1_case ice_bird_main_1_cases[] = {
    { 0, 0, 500, 100, 0, 2, 0, 37428, 1, 1 },
    { 5, 1, 500, 100, 5, 2, 0, 4660, 2, 0 },
    { 5, 0, -100, 100, 5, 2, 0, 4660, 2, 0 },
    { 0, 0, 100, 200, 0, 1, 1, 37428, 1, 0 },
};
static u32 test_ice_bird_main_1(u32 row)
{
    const struct ice_bird_main_1_case* c = &ice_bird_main_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    struct BackgroundObj background_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 14;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 14;
    obj.contact_damage = 3;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)ice_bird_animations;
    obj.hurt_box = &ice_bird_body_box;
    obj.attack_box = &ice_bird_body_box;
    obj.collision_data = D_80106974;
    obj.ext.main_14.unk84 = 2;
    set_animation(&obj, 0);
    obj.unk5 = 1;
    obj.ext.main_14.saved_unk5 = c->saved_unk5;
    obj.ext.main_14.unk8C = c->unk8C;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    obj.unk42 = 0x9234;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    g_Player.spike_immune = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    FILL_ACTIVE(weapon_objects, 16, 0);
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk5 = c->unk5;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.state = c->state;
    expected.on_screen = c->on_screen;
    expected.unk42 = c->unk42;
    expected.ext.main_14.unk84 = c->unk84;
    expected.ext.main_14.unk94 = c->unk94;
    player_expected = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    ice_bird_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    return 1;
}

void ice_bird_blast_start(struct MainObj* arg0);
void ice_bird_blast_wait(struct MainObj*);
void ice_bird_init(struct MainObj*);
extern u8 D_80110F7C[696], freeze_blast_tile_patches[4][6];
static struct MainObj expected_mains[48];
static struct VisualObj expected_visuals[32];
static struct EffectObj expected_effects[32];
static u32 expected_map[174], sound_entries_freeze_blast_enemy_capacity[65];
static u32 full(u32 row)
{
    struct MainObj* bird = &main_objects[0];
    struct EffectObj* obj = &effect_objects[0];
    struct PlayerObj player;
    struct EngineObj engine;
    struct BackgroundObj backgrounds[3];
    u8* map = (u8*)expected_map;
    u8* patch = freeze_blast_tile_patches[row];
    u32 i, column;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    engine = engine_obj;
    engine.unk10 = engine.unk11 = engine.unk12 = engine.unk13 = 0;
    engine.character_state.fields.active = 1;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 1; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    bird->id = 14;
    bird->unk2 = row;
    bird->x_pos.i.hi = row == 0 ? 3392 : row == 1 ? 4416
        : row == 2                                ? 5184
                                                  : 5952;
    bird->y_pos.i.hi = row == 0 ? 336 : row == 1 ? 347
        : row == 2                               ? 376
                                                 : 320;
    ice_bird_init(bird);
    bird->unk5 = 4;
    set_animation(bird, 2);
    ice_bird_blast_start(bird);
    for (i = 0; i < 12; i++)
        ice_bird_blast_wait(bird);
    assert(bird->unk6 == 2 && bird->ext.main_14.visual_variant == 255);
    D_8013E198[2] = -1;
    memset(sound_entries_freeze_blast_enemy_capacity, 0, sizeof(sound_entries_freeze_blast_enemy_capacity));
    D_80141F50[2] = (u8*)sound_entries_freeze_blast_enemy_capacity;
    ice_bird_blast_release(bird);
    assert(obj->active == 1 && obj->id == 17 && obj->unk2 == row && obj->ext.effect_17.source == ANIMATED_OBJECT(bird));
    memcpy(expected_mains, main_objects, sizeof(expected_mains));
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    expected_effects[0].state = 2;
    expected_effects[0].ext.effect_17.phase = 255;
    expected_effects[0].ext.effect_17.timer = 2;
    player = g_Player;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    for (i = 0; i < 3; i++)
        backgrounds[i].unk4C = 1;
    layout_width = 29;
    layout_height = 8;
    layout_size = 232;
    c_test_copy_words((u32*)D_80141BE8, (u32*)D_80110F7C, 174);
    c_test_copy_words(expected_map, (u32*)D_80110F7C, 174);
    for (i = 0; i < 2; i++) {
        column = patch[5] + i;
        map[column] = patch[0] + i;
        map[29 + column] = patch[1] + i;
        map[232 + column] = patch[2] ? patch[2] + i : 0;
        map[261 + column] = patch[3] + i;
        map[493 + column] = patch[4] + i;
    }
    need_palette_load = 32;
    cur_random = 0x1234;
    freeze_blast_update(obj);
    assert(obj->state == 1);
    for (i = 0; i < 60; i++)
        freeze_blast_update(obj);
    c_test_same_words(main_objects, expected_mains, sizeof(expected_mains));
    c_test_same_words(visual_objects, expected_visuals, sizeof(expected_visuals));
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(D_80141BE8, expected_map, sizeof(expected_map));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(cur_random == 0x1234 && need_palette_load == 33 && layout_width == 29 && layout_height == 8 && layout_size == 232 && g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0 && g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == -1);
    for (i = 0; i < COUNT(sound_entries_freeze_blast_enemy_capacity); i++)
        assert(sound_entries_freeze_blast_enemy_capacity[i] == 0);
    assert(D_80141F50[2] == (u8*)sound_entries_freeze_blast_enemy_capacity && D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ice_bird_flight_and_despawn", NULL, ice_bird_flight_and_despawn_cases_expected, COUNT(ice_bird_flight_and_despawn_cases_expected), bird_case },
    { "func_8004D6FC_1", 0, 0, 9, test_func_8004D6FC_1 },
    { "ice_bird_blast_release", 0, 0, 2, test_ice_bird_blast_release },
    { "ice_bird_face_player", 0, 0, 1, test_ice_bird_face_player },
    { "ice_bird_main_1", 0, 0, 4, test_ice_bird_main_1 },
    { "four_shipped_Ice_Birds_actual_freeze_factory_full_main_pool_original_stage_map", NULL, NULL, 4, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_bird_flight_and_despawn_cases_expected) + 9 + 2 + 1 + 4 + 4;
