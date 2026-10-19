#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player.h"
#include "main/objects.h"
#include "main/102FC.h"
#include "main/visuals/visual_03_small_effect.h"
void func_8001DF48(struct GameInfo* arg0);
void func_8001DF7C(struct GameInfo* arg0);
void weapon_overlay_update(struct VisualObj*);
void sigma_collapse_update(struct EffectObj*);
void func_800D9C84(struct LayerObj*);
void TitleUpdate(struct MiscObj*);
extern struct StageObjectRecord stage_object_records_8_0[];
static struct MainObj mains[48];
static struct VisualObj visuals[32];
static struct MiscObj misc[64];
static struct EffectObj effects[32];
static struct LayerObj layers[4];
static struct PlayerObj player, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj cameras[3];
static struct GameInfo info;
static struct ControllerInput input;
static struct ObjectHeader *title, *old_title;
static u32 metadata[8], frames[64], *old_metadata;
static u8 *old_frames, old_demo, dirty;
static u16 rng;
static void* current[7];
static u32 zero_difference(const u32* p, u32 count)
{
    u32 different = 0;
    while (count >= 8) {
        different |= p[0] | p[1] | p[2] | p[3] | p[4] | p[5] | p[6] | p[7];
        p += 8;
        count -= 8;
    }
    while (count--)
        different |= *p++;
    return different;
}
static void prepare(void)
{
    u32 i;
    old_metadata = D_801406A8;
    old_frames = TEST_TITLE_FRAMES;
    old_demo = D_80171EA8;
    old_title = D_80139690;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)layer_objects, sizeof(layer_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&game_info, sizeof(game_info) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    c_test_zero_words(frames, COUNT(frames));
    D_801406A8 = metadata;
    TEST_TITLE_FRAMES = (u8*)frames;
    D_80171EA8 = 0;
    D_80139690 = NULL;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
}
static void capture(void)
{
    c_test_copy_words((u32*)mains, (u32*)main_objects, sizeof(mains) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    c_test_copy_words((u32*)effects, (u32*)effect_objects, sizeof(effects) / 4);
    c_test_copy_words((u32*)layers, (u32*)layer_objects, sizeof(layers) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    info = game_info;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    title = D_80139690;
    current[0] = SP_CUR_MAIN_OBJ;
    current[1] = SP_CUR_WEAPON_OBJ;
    current[2] = SP_CUR_SHOT_OBJ;
    current[3] = SP_CUR_VISUAL_OBJ;
    current[4] = SP_CUR_EFFECT_OBJ;
    current[5] = SP_CUR_MISC_OBJ;
    current[6] = SP_CUR_LAYER_OBJ;
    rng = cur_random;
    dirty = need_palette_load;
}
static u32 check(void)
{
    u32 i;
    assert(c_test_word_difference((u32*)main_objects, (u32*)mains, sizeof(mains) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0 && c_test_word_difference((u32*)effect_objects, (u32*)effects, sizeof(effects) / 4) == 0 && c_test_word_difference((u32*)layer_objects, (u32*)layers, sizeof(layers) / 4) == 0);
    assert(zero_difference((u32*)weapon_objects, sizeof(weapon_objects) / 4) == 0 && zero_difference((u32*)shot_objects, sizeof(shot_objects) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)&game_info, (u32*)&info, sizeof(info) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(SP_CUR_MAIN_OBJ == current[0] && SP_CUR_WEAPON_OBJ == current[1] && SP_CUR_SHOT_OBJ == current[2] && SP_CUR_VISUAL_OBJ == current[3] && SP_CUR_EFFECT_OBJ == current[4] && SP_CUR_MISC_OBJ == current[5] && SP_CUR_LAYER_OBJ == current[6]);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && D_80139690 == title && D_80171EA8 == 0 && D_801406A8 == metadata && TEST_TITLE_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    assert(zero_difference(frames, COUNT(frames)) == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    D_801406A8 = old_metadata;
    TEST_TITLE_FRAMES = old_frames;
    D_80171EA8 = old_demo;
    D_80139690 = old_title;
    return 1;
}
static u32 overlay_missing_owner(u32 row)
{
    struct VisualObj* object;
    (void)row;
    prepare();
    object = spawn_explosion_at(0, 160, 120, 0);
    assert(object == &visual_objects[0]);
    ZeroObjectState(OBJECT_HEADER(object));
    object = find_free_visual_obj();
    assert(object == &visual_objects[0]);
    object->active = 0x21;
    object->id = 26;
    object->unk2 = 1;
    assert(object->unk50 == NULL);
    capture();
    c_test_zero_words((u32*)&visuals[0], 2);
    weapon_overlay_update(object);
    return check();
}
static u32 zero_final_npc(u32 row)
{
    (void)row;
    prepare();
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_obj.cur_character = CHARACTER_ZERO;
    g_Player.unk2 = CHARACTER_ZERO;
    capture();
    engine.unk1E = -2;
    misc[0].active = 0x41;
    misc[0].id = 52;
    misc[0].unk2 = 1;
    func_8001FDBC();
    return check();
}
static u32 collapse_full_misc(u32 row)
{
    struct EffectObj* object;
    u32 i;
    (void)row;
    prepare();
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    object = find_free_effect_obj();
    assert(object == &effect_objects[0]);
    object->active = 1;
    object->id = 43;
    sigma_collapse_update(object);
    sigma_collapse_update(object);
    assert(object->state == 1 && object->unk5 == 1 && object->ext.effect_9.transition_timer == 1 && object->ext.effect_9.direction == 2);
    capture();
    effects[0].ext.effect_9.transition_timer = 5;
    cameras[0].unk37 = 5;
    cameras[0].unk46 = 2;
    cameras[0].unk3E.bytes[1] = 2;
    cameras[0].unk3D = cameras[0].unk3B = 1;
    cameras[0].unk34 |= 1;
    sigma_collapse_update(object);
    return check();
}
static u32 train_full_main(u32 row)
{
    struct LayerObj* object;
    struct StageObjectRecord* record;
    u32 i, before[2];
    (void)row;
    prepare();
    engine_obj.stage = 8;
    background_objects[0].x_pos.i.hi = 6720;
    background_objects[0].y_pos.i.hi = 256;
    g_Player.x_pos.i.hi = 0x1B61;
    g_Player.y_pos.i.hi = 384;
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    record = &stage_object_records_8_0[22];
    assert(record->id == 3 && record->object_type == 7 && record->x == 6608 && record->y == 384);
    c_test_copy_words(before, (u32*)record, 2);
    ((u8*)before)[0] &= 0x70;
    object = find_free_layer_obj();
    assert(object == &layer_objects[0]);
    object->active = 1;
    object->id = record->id;
    object->unk2 = record->subtype;
    object->x_pos.i.hi = record->x;
    object->y_pos.i.hi = record->y;
    object->backref = record;
    capture();
    c_test_zero_words((u32*)&layers[0], 2);
    player.script_state = 1;
    player.script_action = 0x14;
    player.script_facing = 0;
    player.spike_immune = 1;
    engine.gameplay_locked = 1;
    func_800D9C84(object);
    assert(c_test_word_difference((u32*)record, before, 2) == 0);
    return check();
}
static u32 title_full_effects(u32 row)
{
    struct MiscObj* object;
    u32 i;
    (void)row;
    prepare();
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = 1;
    object = find_free_misc_obj();
    assert(object == &misc_objects[0]);
    object->active = 1;
    object->id = 19;
    TitleUpdate(object);
    assert(object->state == 1 && object->id == 19);
    D_80139690 = OBJECT_HEADER(object);
    game_info.mode = 5;
    func_8001DF48(&game_info);
    assert(game_info.mode == 6 && game_info.unk4 == 50);
    for (i = 0; i < 49; i++)
        func_8001DF7C(&game_info);
    assert(game_info.unk4 == 1 && game_info.mode == 6);
    capture();
    info.mode = 7;
    info.unk4 = 10;
    func_8001DF7C(&game_info);
    return check();
}
const struct CTestGroup c_test_groups[] = {
    { "nullable_overlay_constructor_reused_record", NULL, NULL, 1, overlay_missing_owner },
    { "Zero_final_stage_actual_NPC_birth", NULL, NULL, 1, zero_final_npc },
    { "supported_debris_constructor_full_misc", NULL, NULL, 1, collapse_full_misc },
    { "original_train_trigger_full_main", NULL, NULL, 1, train_full_main },
    { "title_transition_real_50tick_deadline_full_effects", NULL, NULL, 1, title_full_effects },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 1 + 1 + 1;
