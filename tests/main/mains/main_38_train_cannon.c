#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_38_train_cannon.h"
#include "main/55C4.h"

static u32 signed_default(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.unk6 = 0x28;
    obj.ext.main_38.unk84 = 0xFFFFFFFFu;
    obj.unk7E = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_step.fields.duration = 2;
    before = obj;
    train_cannon_idle_pick(&obj);
    before.animation_step.fields.duration = 1;
    before.unk7E = 0;
    before.unk6 = 0;
    before.ext.main_38.unk84 = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = obj.ext.main_38.unk84 | ((u32)(u8)obj.unk5 << 16);
    return actual;
}
static const CTestCase train_cannon_signed_default_cases[] = { signed_default };
static const u32 train_cannon_signed_default_cases_expected[] = { 0x270000u };

struct train_cannon_fire_blast_1_case {
    u32 free_last;
    u32 expected[8];
};
static const struct train_cannon_fire_blast_1_case train_cannon_fire_blast_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x14u, 0u, 1u, 0x1234u, 0x40u, 0x56u, 0u } },
};
static u32 test_train_cannon_fire_blast_1(u32 row)
{
    const struct train_cannon_fire_blast_1_case* c = &train_cannon_fire_blast_1_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj, object_before;
    struct PlayerObj player_before;
    struct ShotObj expected[32];
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    obj.unk2 = 1;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        shot_objects[31].active = 0;
    }
    memcpy(expected, shot_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 20;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk7C = WEAPON_OBJECT(&obj);
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.unk3C;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = VISUAL_SATURN_LAYER(1);
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_fire_blast(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(shot_objects, expected, sizeof(shot_objects));
    observed_values[0] = (u32)shot_objects[31].active;
    observed_values[1] = (u32)shot_objects[31].id;
    observed_values[2] = (u32)shot_objects[31].unk2;
    observed_values[3] = TEST_PSX_LAYER(shot_objects[31].unk16);
    observed_values[4] = (u32)shot_objects[31].unk42;
    observed_values[5] = C_TEST_PSX_FACING(shot_objects[31].unk15);
    observed_values[6] = (u32)shot_objects[31].unk40;
    observed_values[7] = (u32)shot_objects[31].bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

struct train_cannon_fire_volley_1_case {
    u32 free_last;
    u32 expected[8];
};
static const struct train_cannon_fire_volley_1_case train_cannon_fire_volley_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x15u, 0u, 4u, 0x1234u, 0x40u, 0x56u, 0u } },
};
static u32 test_train_cannon_fire_volley_1(u32 row)
{
    const struct train_cannon_fire_volley_1_case* c = &train_cannon_fire_volley_1_cases[row];
    u32 observed_values[8];
    struct MainObj obj, object_before;
    struct PlayerObj player_before;
    struct ShotObj expected[32];
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    obj.unk2 = 0;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        shot_objects[31].active = 0;
    }
    memcpy(expected, shot_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 21;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk7C = WEAPON_OBJECT(&obj);
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = VISUAL_SATURN_LAYER(4);
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_fire_volley(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(shot_objects, expected, sizeof(shot_objects));
    observed_values[0] = (u32)shot_objects[31].active;
    observed_values[1] = (u32)shot_objects[31].id;
    observed_values[2] = (u32)shot_objects[31].unk2;
    observed_values[3] = TEST_PSX_LAYER(shot_objects[31].unk16);
    observed_values[4] = (u32)shot_objects[31].unk42;
    observed_values[5] = C_TEST_PSX_FACING(shot_objects[31].unk15);
    observed_values[6] = (u32)shot_objects[31].unk40;
    observed_values[7] = (u32)shot_objects[31].bg_offset;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

struct train_cannon_main_case {
    u32 g_Player_x_pos, obj_x_pos, unk5, saved_unk5;
    u32 expected[16];
};
static const struct train_cannon_main_case train_cannon_main_cases[] = {
    { 65536000, 13111860, 1, 0, { 1u, 0u, 1u, 0u, 1u, 1u, 7u, 3u, 0u, 0x1234u, 0x12u, 0xC81234u, 0x645678u, 0xC81234u, 0x645678u, 1u } },
    { 65536000, 52433460, 4, 2, { 1u, 4u, 1u, 4u, 1u, 0u, 6u, 3u, 0u, 0x1234u, 0x12u, 0x3201234u, 0x645678u, 0x3201234u, 0x645678u, 0xC010001u } },
    { 45879860, 52433460, 2, 4, { 1u, 2u, 1u, 2u, 1u, 0u, 7u, 2u, 0u, 0x1234u, 0x12u, 0x3201234u, 0x645678u, 0x3201234u, 0x645678u, 1u } },
};
static u32 test_train_cannon_main(u32 row)
{
    const struct train_cannon_main_case* c = &train_cannon_main_cases[row];
    u32 observed_values[16];
    struct MainObj obj;
    struct PlayerObj player_before, entity_before;
    struct EngineObj engine_before;
    struct BackgroundObj cameras_before[3];
    struct WeaponObj weapons_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    g_Entity.active = 0;
    qux_object.active = 0;
    g_Player.bg_offset = 0;
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.x_pos.val = c->g_Player_x_pos;
    g_Player.y_pos.val = 65536000;
    g_Player.unk68 = NULL;
    train_cannon_init(&obj);
    obj.x_pos.val = c->obj_x_pos;
    obj.unk5 = c->unk5;
    obj.unk6 = 1;
    obj.unk63 = 0;
    obj.invincibility_timer = 0;
    obj.ext.main_38.saved_unk5 = c->saved_unk5;
    obj.ext.main_38.unk88 = 1;
    obj.unk7C = 7;
    obj.unk7E = 3;
    if (obj.unk5 == 4) {
        set_animation(&obj, 2);
    }
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    FILL_ACTIVE(weapon_objects, 16, 0);
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    memcpy(cameras_before, background_objects, sizeof(cameras_before));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    train_cannon_main(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, cameras_before, sizeof(background_objects));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapon_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.ext.main_38.saved_unk5;
    observed_values[4] = (u32)obj.ext.main_38.unk88;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.unk7E;
    observed_values[8] = (u32)obj.invincibility_timer;
    observed_values[9] = (u32)obj.unk42;
    observed_values[10] = (u32)obj.hp;
    observed_values[11] = (u32)obj.x_pos.val;
    observed_values[12] = (u32)obj.y_pos.val;
    observed_values[13] = (u32)obj.unk18.val;
    observed_values[14] = (u32)obj.unk1C.val;
    observed_values[15] = C_TEST_STEP(obj.animation_step.packed);
    return c_test_observe(0, row, observed_values, c->expected, 16);
}

struct train_cannon_spawn_charge_glow_1_case {
    u32 free_last;
    u32 expected[6];
};
static const struct train_cannon_spawn_charge_glow_1_case train_cannon_spawn_charge_glow_1_cases[] = {
    { 0, { 1u, 0u, 0u, 0u, 0u, 0u } },
    { 1, { 0x41u, 0x10u, 4u, 0x1234u, 0x3201234u, 0x645678u } },
};
static u32 test_train_cannon_spawn_charge_glow_1(u32 row)
{
    const struct train_cannon_spawn_charge_glow_1_case* c = &train_cannon_spawn_charge_glow_1_cases[row];
    u32 observed_values[6];
    struct VisualObj obj, object_before, expected[32];
    struct PlayerObj player_before;
    u8 pools_full, free_last;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 38;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x56;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.animation_table = (const u8* const*)train_cannon_animations;
    obj.x_pos.val = 52433460;
    obj.y_pos.val = 6575736;
    pools_full = 1;
    free_last = c->free_last;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    if (free_last) {
        visual_objects[31].active = 0;
    }
    memcpy(expected, visual_objects, sizeof(expected));
    if (free_last) {
        expected[31].active = 0x41;
    }
    if (free_last) {
        expected[31].id = 0x10;
    }
    if (free_last) {
        expected[31].unk2 = 0;
    }
    if (free_last) {
        expected[31].unk50 = (struct PlayerObj*)&obj;
    }
    if (free_last) {
        expected[31].unk42 = obj.unk42;
    }
    if (free_last) {
        expected[31].animation_table = (const u8* const*)train_cannon_animations;
    }
    if (free_last) {
        expected[31].unk3C = (void*)obj.unk3C;
    }
    if (free_last) {
        expected[31].unk40 = obj.unk40;
    }
    if (free_last) {
        expected[31].bg_offset = obj.bg_offset;
    }
    if (free_last) {
        expected[31].unk16 = VISUAL_SATURN_LAYER(4);
    }
    if (free_last) {
        expected[31].unk15 = obj.unk15;
    }
    if (free_last) {
        expected[31].x_pos.val = obj.x_pos.val;
    }
    if (free_last) {
        expected[31].y_pos.val = obj.y_pos.val;
    }
    object_before = obj;
    player_before = g_Player;
    train_cannon_spawn_charge_glow(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &object_before, sizeof(obj));
    c_test_same_words(visual_objects, expected, sizeof(visual_objects));
    observed_values[0] = (u32)visual_objects[31].active;
    observed_values[1] = (u32)visual_objects[31].id;
    observed_values[2] = TEST_PSX_LAYER(visual_objects[31].unk16);
    observed_values[3] = (u32)visual_objects[31].unk42;
    observed_values[4] = (u32)visual_objects[31].x_pos.val;
    observed_values[5] = (u32)visual_objects[31].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

#include "support/state_cases.h"
#include "support/tile_writes.h"
void train_cannon_explode(struct MainObj*);
void train_cannon_despawn(struct MainObj*);
void train_cannon_charge_wait(struct MainObj*);
void train_cannon_blast_fire(struct MainObj*);
void train_cannon_blast_end(struct MainObj*);
void train_cannon_volley_fire(struct MainObj*);
void train_cannon_volley_end(struct MainObj*);
void train_cannon_recoil_end(struct MainObj*);
static u32 tc_layer(u8 layer) { return layer == VISUAL_SATURN_LAYER(6) ? 6 : layer == VISUAL_SATURN_LAYER(4) ? 4 : layer; }
#define TC(step, sub) (state_reset(step, sub, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), memset(&engine_obj, 0, sizeof(engine_obj)), state_terrain(0), g_Player.unk68 = NULL, so.active = 0x41, so.id = 0x26, so.state = 1, so.x_pos.i.hi = 0x174C, so.y_pos.i.hi = 0x152, background_objects[0].x_pos.i.hi = 0x1700, background_objects[0].y_pos.i.hi = 0x100, g_Player.x_pos.i.hi = 0x1700, tile_writes_begin())
#define TCX() (state_extra = so.ext.main_38.unk84 | so.ext.main_38.unk88 << 8 | (u32)so.ext.main_38.unk8C << 16 | (u32)shot_objects[1].active << 24 ^ tc_layer(shot_objects[0].unk16) << 4 ^ tc_layer(shot_objects[1].unk16) << 12, state_extra ^= tile_writes_end(), engine_obj.stage = 0)
static void tc_killed(u8 stage)
{
    TC(2, 1), engine_obj.stage = stage, so.hp = 1, state_hit(&so, 0, 0, 1);
    if (stage == 8)
        tile_writes_expect(0xB, 0x174C - 0x28, 0x152, 1);
    train_cannon_main(&so), TCX();
}
static void tc_killed_stage8(void) { tc_killed(8); }
static void tc_killed_stage7(void) { tc_killed(7); }
static void tc_off_screen_passed(void) { TC(2, 1), g_Player.x_pos.i.hi = 0x1800, background_objects[0].x_pos.i.hi = 0x1400, train_cannon_main(&so), TCX(); }
static void tc_explode_end(void) { TC(0, 0), so.state = 2, so.unk7C = 1, so.unk7E = 1, train_cannon_explode(&so), TCX(); }
static void tc_explode(void) { TC(0, 0), so.state = 2, so.unk7C = 2, so.unk7E = 2, train_cannon_explode(&so), TCX(); }
static void tc_despawn_broken(void) { TC(0, 0), so.state = 3, so.ext.main_38.unk8C = 1, train_cannon_despawn(&so), TCX(); }
static void tc_despawn(void) { TC(0, 0), so.state = 3, train_cannon_despawn(&so), TCX(); }
#define PICK(n) (TC(2, 1), so.unk7E = 1, so.ext.main_38.unk84 = n, train_cannon_idle_pick(&so), TCX())
static void tc_pick_charge(void) { PICK(0); }
static void tc_pick_volley(void) { PICK(1); }
static void tc_pick_volley_quick(void) { PICK(2); }
#define TIMER(step, sub, timer, run) (TC(step, sub), so.unk7C = timer, run(&so), TCX())
static void tc_charge_wait(void) { TIMER(3, 1, 2, train_cannon_charge_wait); }
static void tc_charge_done(void) { TIMER(3, 1, 1, train_cannon_charge_wait); }
static void tc_blast_fire_top(void) { TIMER(4, 0, 0, train_cannon_blast_fire); }
static void tc_blast_end(void) { TIMER(4, 1, 1, train_cannon_blast_end); }
static void tc_volley_wait(void) { TIMER(5, 1, 2, train_cannon_volley_fire); }
static void tc_volley_fire(void) { TIMER(5, 1, 1, train_cannon_volley_fire); }
static void tc_volley_end_wait(void) { TIMER(5, 2, 2, train_cannon_volley_end); }
static void tc_volley_end(void) { TIMER(5, 2, 1, train_cannon_volley_end); }
static void tc_recoil_wait(void) { TIMER(6, 1, 2, train_cannon_recoil_end); }
static void tc_recoil_end(void) { TIMER(6, 1, 1, train_cannon_recoil_end); }
static void (*const train_cannon_states_cases[])(void) = {
    tc_killed_stage8,
    tc_killed_stage7,
    tc_off_screen_passed,
    tc_explode_end,
    tc_explode,
    tc_despawn_broken,
    tc_despawn,
    tc_pick_charge,
    tc_pick_volley,
    tc_pick_volley_quick,
    tc_charge_wait,
    tc_charge_done,
    tc_blast_fire_top,
    tc_blast_end,
    tc_volley_wait,
    tc_volley_fire,
    tc_volley_end_wait,
    tc_volley_end,
    tc_recoil_wait,
    tc_recoil_end,
};
static const u32 train_cannon_states_expected[] = {
    0x102u, 0x50020u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x2D8FC6D3u, 0x41002100u,
    0x102u, 0x50020u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x10200u, 0x41002100u,
    0x102u, 0xFFFF0000u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x0u, 0x50000u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41002100u,
    0x0u, 0x10001u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x0u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10200u, 0x0u,
    0x0u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x200u, 0x0u,
    0x3u, 0x140000u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x41000000u,
    0x5u, 0x140000u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x2u, 0x41000000u,
    0x5u, 0xA0000u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x103u, 0x1u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x4u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x100u, 0x41000000u,
    0x104u, 0x6Eu, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x0u, 0x41002220u, 0x41410000u,
    0x2u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x105u, 0x1u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x205u, 0x14u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41006040u, 0x41410000u,
    0x205u, 0x1u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x6u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x106u, 0x1u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x2u, 0x0u, 0x174C0000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
};
static u32 test_train_cannon_states(u32 row)
{
    return state_run(train_cannon_states_cases[row], row, &train_cannon_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "train_cannon_signed_default", train_cannon_signed_default_cases, train_cannon_signed_default_cases_expected, COUNT(train_cannon_signed_default_cases), 0 },
    { "train_cannon_fire_blast_1", 0, 0, 2, test_train_cannon_fire_blast_1 },
    { "train_cannon_fire_volley_1", 0, 0, 2, test_train_cannon_fire_volley_1 },
    { "train_cannon_main", 0, 0, 3, test_train_cannon_main },
    { "train_cannon_spawn_charge_glow_1", 0, 0, 2, test_train_cannon_spawn_charge_glow_1 },
    { "train_cannon_states", 0, 0, COUNT(train_cannon_states_cases), test_train_cannon_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_cannon_signed_default_cases) + 2 + 2 + 3 + 2 + COUNT(train_cannon_states_cases);
