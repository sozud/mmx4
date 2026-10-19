#include "test_runtime.h"
#include "main/mains/main_58_beam_drone.h"
#include "main/195B4.h"
extern struct Unk_unk68 beam_drone_hit_box;
extern struct Unk_unk68 beam_drone_debris;

struct func_800745E8_case {
    u32 unk2;
    u32 expected[1];
};
static const struct func_800745E8_case func_800745E8_cases[] = {
    { -1, { 0xFF010201u } },
    { 3, { 0x3010201u } },
};
static u32 test_func_800745E8(u32 row)
{
    const struct func_800745E8_case* c = &func_800745E8_cases[row];
    u32 observed_values[1];
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before[3];
    struct WeaponObj weapons_before[16];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.id = 58;
    obj.unk2 = c->unk2;
    obj.x_pos.val = 6558260;
    obj.y_pos.val = 5251909;
    g_Player.spike_immune = 1;
    func_80074438(&obj);
    obj.unk5 = 1;
    obj.ext.main_58.saved_unk5 = 2;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    func_800745E8(&obj);
    before.unk5 = 2;
    before.on_screen = 1;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.on_screen << 16) | ((u32)(u8)obj.unk2 << 24);
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

void beam_drone_update(struct MainObj*);
void beam_drone_drop(struct MainObj*);
void beam_drone_charge(struct MainObj*);
void beam_drone_fire(struct MainObj*);
void beam_drone_leave(struct MainObj*);
extern void* beam_drone_animations[];
static struct MainObj expected[48];
static struct ShotObj shots[32];
static struct VisualObj visuals[32];
static struct StageObjectRecord records[2] = { { 0, 58, 1, 0, 160, 1000 }, { 0, 0, 0, 255, 0, 0 } };
static u32 upper_exit(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    u16 rng;
    u32 i, record_before[4];
    (void)row;
    c_test_copy_words(record_before, (u32*)records, COUNT(record_before));
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    c_test_copy_words((u32*)shots, (u32*)shot_objects, sizeof(shots) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    g_Player.bg_offset = 0;
    g_Player.y_pos.i.hi = 120;
    engine_obj.checkpoint = 0;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    func_800292D0(records);
    SP_CUR_MAIN_OBJ = &main_objects[0];
    beam_drone_update(&main_objects[0]);
    assert(main_objects[0].state == 1 && main_objects[0].unk5 == 2 && main_objects[0].unk6 == 0 && main_objects[0].y_speed == 98304);
    beam_drone_drop(&main_objects[0]);
    for (i = 0; i < 60; i++)
        beam_drone_drop(&main_objects[0]);
    assert(main_objects[0].unk5 == 3 && main_objects[0].unk6 == 0 && main_objects[0].y_pos.val == 910 * 65536);
    beam_drone_charge(&main_objects[0]);
    for (i = 0; i < 80; i++)
        beam_drone_charge(&main_objects[0]);
    assert(main_objects[0].unk5 == 4 && main_objects[0].unk6 == 0);
    beam_drone_fire(&main_objects[0]);
    for (i = 0; i < 120; i++)
        beam_drone_fire(&main_objects[0]);
    assert(main_objects[0].unk5 == 5 && main_objects[0].unk6 == 0 && main_objects[0].y_pos.val == 910 * 65536 && main_objects[0].y_speed == 0);
    c_test_copy_words((u32*)expected, (u32*)main_objects, sizeof(expected) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    expected[0].unk17 = 0;
    expected[0].previous_animation_index = 255;
    expected[0].animation_cursor = beam_drone_animations[0];
    expected[0].animation_step.packed = 0x00010002;
    expected[0].unk7C = 60;
    expected[0].y_speed = -98304;
    expected[0].unk6 = 1;
    beam_drone_leave(&main_objects[0]);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots, sizeof(shots) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && D_8013E198[2] == -1 && SP_CUR_MAIN_OBJ == &main_objects[0] && c_test_word_difference((u32*)records, record_before, COUNT(record_before)) == 0);
    SP_CUR_MAIN_OBJ = current;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "func_800745E8", 0, 0, 2, test_func_800745E8 },
    { "supported_vertical_drone_263_own_attack_steps_upper_exit", NULL, NULL, 1, upper_exit },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1;
