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
    SPIKE_IMMUNE_SET(g_Player, 1);
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
#ifndef VERSION_DEMO
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
    expected[0].animation_step.packed = C_TEST_STEP(0x00010002);
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
#endif

#include "support/state_cases.h"
void func_80074438(struct MainObj*);
void func_800745E8(struct MainObj*);
void beam_drone_despawn(struct MainObj*);
void beam_drone_fire_end(struct MainObj*);
void beam_drone_leave_start(struct MainObj*);
void beam_drone_leave_move(struct MainObj*);
void beam_drone_spawn_beam(struct VisualObj*);
void beam_drone_spawn_charge(struct AnimatedObj*);
#define BM2(step, sub) (state_reset(step, sub, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), engine_obj.character_state.fields.active = 0, so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x100, g_Player.y_pos.i.hi = 0x80, SPIKE_IMMUNE_SET(g_Player, 1))
#define BM2X() (engine_obj.character_state.fields.active = 0, state_extra = so.state | so.ext.main_58.unk88 << 8 | (u32)so.ext.main_58.saved_unk5 << 16 | (u32)(u8)so.unk2 << 24)
#define BMINIT(kind, px, py) (BM2(0, 0), so.state = 0, so.unk2 = kind, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, func_80074438(&so), BM2X())
static void bm2_init_0_right(void)
{
    BMINIT(0, 0x100, 0x80);
}
static void bm2_init_0_left(void) { BMINIT(0, 0x40, 0x80); }
static void bm2_init_1_below(void) { BMINIT(1, 0x100, 0x80); }
static void bm2_init_2_left(void) { BMINIT(2, 0x40, 0x80); }
static void bm2_init_2_right(void) { BMINIT(2, 0x100, 0x80); }
#define BMMAIN(kind, setup) (BM2(1, 0), so.unk2 = kind, so.ext.main_58.saved_unk5 = 1, setup, func_800745E8(&so), BM2X())
static void bm2_main_1(void)
{
    BMMAIN(1, 0);
}
static void bm2_main_2_away(void) { BMMAIN(2, so.x_pos.i.hi = 0x400); }
static void bm2_main_firing_away(void) { BMMAIN(0, (so.unk5 = 4, so.unk6 = 3, so.unk7C = 5, so.x_pos.i.hi = 0x400)); }
static void bm2_main_defeat_0(void) { BMMAIN(0, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void bm2_main_defeat_1(void) { BMMAIN(1, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void bm2_main_pod_gone(void) { BMMAIN(1, engine_obj.character_state.fields.active = 1); }
static void bm2_main_left(void) { BMMAIN(1, (so.unk5 = 5, so.unk6 = 1, so.unk7C = 1)); }
static void bm2_despawn_placed(void) { BM2(0, 0), so.state = 2, beam_drone_despawn(&so), BM2X(); }
static void bm2_despawn_pod(void) { BM2(0, 0), so.state = 2, so.unk2 = 1, beam_drone_despawn(&so), BM2X(); }
static void bm2_fire_end_placed(void) { BM2(4, 3), so.unk7C = 1, beam_drone_fire_end(&so), BM2X(); }
#ifndef VERSION_DEMO
#define LEAVE(kind, x, y) (BM2(5, 0), so.unk2 = kind, so.x_pos.i.hi = x, so.y_pos.i.hi = y, beam_drone_leave_start(&so), BM2X())
static void bm2_leave_down(void)
{
    LEAVE(1, 0x80, 0x300);
}
static void bm2_leave_right(void) { LEAVE(2, 0x960, 0x60); }
static void bm2_leave_left(void) { LEAVE(2, 0x900, 0x60); }
static void bm2_leave_wait(void) { BM2(5, 1), so.unk7C = 3, beam_drone_leave_move(&so), BM2X(); }
#endif
static void bm2_beam_left(void)
{
    BM2(4, 1), beam_drone_spawn_beam(VISUAL_OBJECT(&so)), BM2X(), state_extra ^= shot_objects[0].unk16 << 4 | shot_objects[1].unk2 << 12;
}
static void bm2_beam_right(void) { BM2(4, 1), so.unk15 = PLAYER_FACING_RIGHT, beam_drone_spawn_beam(VISUAL_OBJECT(&so)), BM2X(), state_extra ^= shot_objects[0].unk16 << 4; }
static void bm2_charge(void) { BM2(4, 0), beam_drone_spawn_charge(ANIMATED_OBJECT(&so)), BM2X(), state_extra ^= visual_objects[0].id << 4; }
static void (*const bm2_cases[])(void) = {
    bm2_init_0_right,
    bm2_init_0_left,
    bm2_init_1_below,
    bm2_init_2_left,
    bm2_init_2_right,
    bm2_main_1,
    bm2_main_2_away,
    bm2_main_firing_away,
    bm2_main_defeat_0,
    bm2_main_defeat_1,
    bm2_main_pod_gone,
    bm2_main_left,
    bm2_despawn_placed,
    bm2_despawn_pod,
    bm2_fire_end_placed,
    bm2_beam_left,
    bm2_beam_right,
    bm2_charge,
#ifndef VERSION_DEMO
    bm2_leave_down,
    bm2_leave_right,
    bm2_leave_left,
    bm2_leave_wait,
#endif
};
static const u32 bm2_expected[] = {
    0x2u,
    0x280000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x50003u,
    0x1u,
    0x41000000u,
    0x2u,
    0x280000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50003u,
    0x1u,
    0x41000000u,
    0x2u,
    0x3C0000u,
    0x800000u,
    0x0u,
    0xFFFE8000u,
    0x0u,
    0x0u,
    0x50003u,
    0x1000001u,
    0x41000000u,
    0x2u,
    0x3C0000u,
    0x800000u,
    0xFFFEB000u,
    0x0u,
    0x0u,
    0x0u,
    0x50003u,
    0x2000001u,
    0x41000000u,
    0x2u,
    0x3C0000u,
    0x800000u,
    0x15000u,
    0x0u,
    0x0u,
    0x0u,
    0x50003u,
    0x2000001u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1010001u,
    0x41000000u,
    0x102u,
    0x0u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2020002u,
    0x41000000u,
    0x304u,
    0x4u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x40001u,
    0x41000000u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x10202u,
    0x41002100u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x1010202u,
    0x41002100u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1010202u,
    0x41002100u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x10200u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x200u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x200u,
    0x0u,
    0x2u,
    0x280000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x104u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1001u,
    0x41410000u,
    0x104u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x11u,
    0x41410000u,
    0x4u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x101u,
    0x41004100u,
#ifndef VERSION_DEMO
    0x105u,
    0x3Cu,
    0x800000u,
    0x0u,
    0x18000u,
    0x0u,
    0x0u,
    0x0u,
    0x1000001u,
    0x41000000u,
    0x105u,
    0x3Cu,
    0x9600000u,
    0x18000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2000001u,
    0x41000000u,
    0x105u,
    0x3Cu,
    0x9000000u,
    0xFFFE8000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2000001u,
    0x41000000u,
    0x105u,
    0x2u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
#endif
};
static u32 bm2_run(u32 row)
{
    return state_run(bm2_cases[row], row, &bm2_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "beam_drone_branch_steps", 0, 0, COUNT(bm2_cases), bm2_run },
    { "func_800745E8", 0, 0, 2, test_func_800745E8 },
#ifndef VERSION_DEMO
    { "supported_vertical_drone_263_own_attack_steps_upper_exit", NULL, NULL, 1, upper_exit },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bm2_cases) + 2
#ifndef VERSION_DEMO
    + 1
#endif
    ;
