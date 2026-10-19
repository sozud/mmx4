#include "test_runtime.h"
#include "main/mains/main_57_frost_walrus.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void frost_walrus_blizzard(struct MainObj* arg0);
void frost_walrus_death_finish(struct MainObj* arg0);
extern void* frost_walrus_animations[39];
extern u32* D_80137E08;
void frost_walrus_choose_script(struct MainObj*);
extern u8** frost_walrus_scripts[3];
extern u8 frost_walrus_script_weights[3][4];
extern u8* D_80141EE8[6];

static u32 guarded_tiles[0x802];
static u8 selected_tiles[0x800];

static u32 floor_case(s8 stage, s32 attribute, u8 empty)
{
    u32 i, count, actual;
    u16* list;

    TEST_BG_TILE_ATTRS = (u8*)&guarded_tiles[1];
    engine_obj.stage = stage;
    guarded_tiles[0] = 0xCAFE1234u;
    guarded_tiles[0x801] = 0x5678BEEFu;
    memset(selected_tiles, 0, sizeof(selected_tiles));
    for (i = 0; i < COUNT(selected_tiles); i++)
        guarded_tiles[i + 1] = 0xA1230000u | (i & 0xFF);
    list = stage == 0xC ? frost_walrus_floor_tiles_rush : frost_walrus_floor_tiles;
    if (empty)
        list[0] = 0;
    count = stage == 0xC ? COUNT(frost_walrus_floor_tiles_rush) : COUNT(frost_walrus_floor_tiles);
    for (i = 0; i < count && list[i] != 0; i++) {
        assert(list[i] < COUNT(selected_tiles));
        selected_tiles[list[i]] = 1;
    }
    assert(i < count);

    frost_walrus_set_floor_tiles(attribute);
    actual = guarded_tiles[list[0] + 1];
    if (empty)
        assert(actual == 0xA1230000u);
    else
        assert(actual == (stage == 0xC ? 0xA1230039u : 0xA1230038u));
    for (i = 0; i < COUNT(selected_tiles); i++) {
        if (selected_tiles[i])
            assert(guarded_tiles[i + 1] == (stage == 0xC ? 0xA1230039u : 0xA1230038u));
        else
            assert(guarded_tiles[i + 1] == (0xA1230000u | (i & 0xFF)));
    }
    assert(guarded_tiles[0] == 0xCAFE1234u);
    assert(guarded_tiles[0x801] == 0x5678BEEFu);
    assert(engine_obj.stage == stage);
    return actual;
}

static u32 normal_floor(void) { return floor_case(7, 0x38, 0); }
static u32 boss_rush_floor(void) { return floor_case(0xC, 0x39, 0); }
static u32 empty_floor(void) { return floor_case(7, 0x38, 1); }

static const CTestCase frost_floor_archive_cases[] = {
    normal_floor,
    boss_rush_floor,
    empty_floor,
};
static const u32 frost_floor_archive_cases_expected[] = { 0xA1230038u, 0xA1230039u, 0xA1230000u };

static u32 blizzard_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    struct ShotObj expected_shots[32];
    struct VisualObj expected_visuals[32];
    u32* command_before = D_80137E08;
    const union AnimationStep* steps = frost_walrus_animations[22];
    u32 i, frame = mode < 4 ? 5 : mode == 6 ? 4
                                            : 0;
    u32 visual_free = (mode < 4 && (mode & 1)) || mode >= 6;
    u32 shot_free = (mode < 4 && (mode & 2)) || mode >= 6;
    u32 actual;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0xA5, sizeof(shot_objects));
    memset(visual_objects, 0x5A, sizeof(visual_objects));
    for (i = 0; i < 32; i++)
        shot_objects[i].active = visual_objects[i].active = 1;
    if (shot_free)
        shot_objects[29].active = 0;
    if (visual_free)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 8;
    obj.unk6 = 3;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk7C = mode == 4 ? 1 : mode == 5 ? 2
                                          : 65;
    obj.unk7E = mode == 5 ? 1 : 7;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    obj.animation_cursor = (const u8*)&steps[frame];
    obj.animation_step = steps[frame];
    obj.unk17 = 22;
    obj.previous_animation_index = 9;
    if (mode < 4)
        obj.animation_step.fields.duration = 2;
    expected = obj;
    memcpy(expected_shots, shot_objects, sizeof(expected_shots));
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    if (--expected.animation_step.fields.duration == 0) {
        expected.animation_cursor = (const u8*)&steps[frame + 1];
        expected.animation_step = steps[frame + 1];
    }
    expected.unk7E = mode == 5 ? 24 : 6;
    expected.unk7C--;
    if (mode == 4) {
        expected.unk7C = 128;
        expected.unk6 = 4;
        expected.animation_cursor = (const u8*)&steps[0];
        expected.animation_step = steps[0];
        expected.previous_animation_index = 0xFF;
    }
    if ((mode < 4 || mode == 6) && visual_free) {
        expected_visuals[31].active = 0x41;
        expected_visuals[31].id = 0x18;
        expected_visuals[31].unk2 = 0x30;
        expected_visuals[31].unk15 = obj.unk15;
        expected_visuals[31].unk50 = &obj;
        expected_visuals[31].x_pos.i.hi = obj.x_pos.i.hi + (obj.unk15 ? 21 : -21);
        expected_visuals[31].y_pos.i.hi = obj.y_pos.i.hi;
    }
    if (expected.unk7C == 64 && shot_free) {
        expected_shots[29].unk50.data = NULL;
        expected_shots[29].unk54 = NULL;
        expected_shots[29].unk68 = NULL;
        expected_shots[29].unk98 = NULL;
        expected_shots[29].unk61 = expected_shots[29].unk64 = expected_shots[29].unk65 = 0;
        expected_shots[29].unk66 = expected_shots[29].unk72 = expected_shots[29].unk73 = 0;
        expected_shots[29].unk74 = expected_shots[29].unk76 = expected_shots[29].unk77 = 0;
        expected_shots[29].unk78 = expected_shots[29].unk62 = expected_shots[29].unk63 = 0;
        expected_shots[29].unk7A = expected_shots[29].unk75 = 0;
        expected_shots[29].active = 0x41;
        expected_shots[29].id = 0x23;
        expected_shots[29].unk2 = 0x20;
        expected_shots[29].unk7C = &obj;
        expected.ext.main_57.shot = &shot_objects[29];
    }
    frost_walrus_blizzard_blow(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(expected_shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)expected_shots)[i]);
    for (i = 0; i < sizeof(expected_visuals) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)expected_visuals)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(D_80137E08 == command_before);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(steps[0].packed == 0x14010002 && steps[4].packed == 0x1B010101 && steps[5].packed == 0x6B010201);
    actual = (u8)obj.unk6 | ((u32)(u16)obj.unk7C << 8) | ((u32)visual_objects[31].active << 24);
    return actual;
}
static const u32 walrus_blizzard_animation_pools_cases_expected[] = { 0x1004003u, 0x41004003u, 0x1004003u, 0x41004003u, 0x1008004u, 0x1000103u, 0x41004003u, 0x4003u };

static u32 charge_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32* command_before = D_80137E08;
    u32 i, broken = mode >= 2, animation = broken ? 23 : 1;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 0;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.ext.main_57.tusks_broken = broken;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 0);
    expected = obj;
    expected.y_speed = expected.x_accel = expected.gravity = 0;
    expected.unk6 = broken ? 3 : 1;
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)frost_walrus_animations[animation];
    expected.animation_step = *(union AnimationStep*)frost_walrus_animations[animation];
    if (broken) {
        expected.x_speed = mode & 1 ? 0x18000 : -0x18000;
        expected.hurt_box = (const u8*)&frost_walrus_charge_hurt_box;
        expected.attack_box = (const u8*)&frost_walrus_charge_attack_box;
    } else {
        expected.hurt_box = (const u8*)&frost_walrus_hurt_box;
        expected.attack_box = (const u8*)&frost_walrus_attack_box;
    }
    frost_walrus_charge_start(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(D_80137E08 == command_before);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u16)(obj.x_speed / 32768) << 16);
}
static const u32 walrus_charge_tusk_context_cases_expected[] = { 0x101u, 0x101u, 0xFFFD1703u, 0x31703u };

static const s16 distances[7] = { 193, 192, -192, -193, 193, 192, 0 };
static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    const union AnimationStep* walk = frost_walrus_animations[38];
    const union AnimationStep* roar = frost_walrus_animations[1];
    u32 i, actual, close = mode == 1 || mode == 2 || mode == 4 || mode == 6;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk6 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = mode == 4 ? 65536 : mode == 5 ? -65536
                                                : 0;
    obj.y_speed = 32768;
    obj.x_accel = 123;
    obj.gravity = 456;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    obj.animation_cursor = (const u8*)walk;
    obj.animation_step = walk[0];
    obj.unk17 = 38;
    obj.previous_animation_index = 9;
    g_Player.x_pos.i.hi = 100 + distances[mode];
    player_before = g_Player;
    expected = obj;
    expected.animation_step.fields.duration = 2;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    if (close) {
        expected.x_speed = 0;
        expected.unk6 = 8;
        expected.unk17 = 1;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)roar;
        expected.animation_step = roar[0];
    }
    frost_walrus_intro_approach(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(walk[0].packed == 0x3E010003 && roar[0].packed == 0x00010002);
    actual = (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
    return actual;
}
static const u32 walrus_intro_player_boundary_cases_expected[] = { 0x642607u, 0x640108u, 0x640108u, 0x642607u, 0x650108u, 0x632607u, 0x640108u };

static u32 script_case(u32 mode)
{
    struct MainObj obj, before;
    u8 weights_before[3][4], sentinel[] = { 0x27, 0x28, 0x29, 0xFF };
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.hp = 0;
    obj.ext.main_57.script = sentinel;
    memcpy(weights_before, frost_walrus_script_weights, sizeof(weights_before));
    if (mode == 1)
        memset(frost_walrus_script_weights[0], 0, 4);
    cur_random = 0;
    before = obj;
    frost_walrus_choose_script(&obj);
    if (mode == 0) {
        assert(obj.ext.main_57.script == frost_walrus_scripts[0][0]);
        before.ext.main_57.script = frost_walrus_scripts[0][0];
    } else
        assert(obj.ext.main_57.script == sentinel);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(cur_random == 0 && sentinel[0] == 0x27 && sentinel[1] == 0x28 && sentinel[2] == 0x29 && sentinel[3] == 0xFF);
    for (i = 0; i < 12; i++)
        assert(((u8*)frost_walrus_script_weights)[i] == (mode == 1 && i < 4 ? 0 : ((u8*)weights_before)[i]));
    result = mode == 0 ? *obj.ext.main_57.script : 0x100 | *obj.ext.main_57.script;
    return result;
}
static const u32 walrus_script_exhaustion_cases_expected[] = { 0x6u, 0x127u };

static const u32 frost_walrus_death_explode_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_frost_walrus_death_explode(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    obj.invincibility_timer = 31;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    frost_walrus_death_explode(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, frost_walrus_death_explode_expected, 9);
}

static const u32 frost_walrus_shards_count_expected[] = { 0u, 4u, 1u, 0u };
static u32 test_frost_walrus_shards_count(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.hp = 24;
    frost_walrus_shards_count(&obj);
    observed_values[0] = (u32)obj.ext.main_57.leap_grounded;
    observed_values[1] = (u32)obj.ext.main_57.shard_count;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, frost_walrus_shards_count_expected, 4);
}

static const u32 frost_walrus_shards_fire_expected[] = { 1u, 2u, 0x20u, 1u, 0u, 0u, 0u };
static u32 test_frost_walrus_shards_fire(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    FILL_ACTIVE(shot_objects, 32, 255 ? 1 : 0);
    frost_walrus_shards_fire(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.unk7E;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk7;
    return c_test_observe(0, row, observed_values, frost_walrus_shards_fire_expected, 7);
}

#include "support/pool_full.h"
static u32 pool_full_frost_walrus_start_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    frost_walrus_start_warning(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_regrow_start(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    frost_walrus_regrow_start(&pf_self);
    pf_expected.collision_data = (const u16*)D_801060F0;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_intro_burst(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 2;
    pf_event(1, 1);
    pf_snapshot();
    frost_walrus_intro_burst(&pf_self);
    pf_animated();
    pf_expected.unk7C = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_breath_blow(void)
{
    u32 actual;
    pf_prepare();
    pf_event(2, 1);
    pf_self.unk7C = 0x41;
    pf_snapshot();
    frost_walrus_breath_blow(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x40;
    pf_expected.unk7E = 4;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_frost_walrus_start_warning,
    pool_full_frost_walrus_regrow_start,
    pool_full_frost_walrus_intro_burst,
    pool_full_frost_walrus_breath_blow,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x10000u, 0x400000u };
static struct EngineObj walrus_engine;
static u32 walrus_pages[8];
#define FW(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.ext.main_57.effect = &effect_objects[0])
#define ENGINE(stage_id, body)                                                                                                                 \
    do {                                                                                                                                       \
        u32* pages = D_801406A8;                                                                                                               \
        u8* frames = TEST_MENU_FRAMES;                                                                                                         \
        walrus_engine = engine_obj;                                                                                                            \
        engine_obj.stage = stage_id;                                                                                                           \
        engine_obj.checkpoint = 1;                                                                                                             \
        D_801406A8 = walrus_pages;                                                                                                             \
        TEST_MENU_FRAMES = (u8*)walrus_pages;                                                                                                  \
        body;                                                                                                                                  \
        state_extra = engine_obj.unk25 | (engine_obj.boss_ptr == &so) << 8 | (u8)engine_obj.unkF << 16 | (u32)(u8)engine_obj.checkpoint << 24; \
        so.unk42 = 0;                                                                                                                          \
        engine_obj = walrus_engine;                                                                                                            \
        D_801406A8 = pages;                                                                                                                    \
        TEST_MENU_FRAMES = frames;                                                                                                             \
    } while (0)
static void fw_blizzard_start(void)
{
    FW(5, 0);
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_wait(void)
{
    FW(5, 1);
    so.unk7C = 2;
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_blow(void)
{
    FW(5, 1);
    so.unk7C = 1;
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_finish_wait(void)
{
    FW(5, 2);
    so.unk7C = 2;
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_finish(void)
{
    FW(5, 2);
    so.unk7C = 1;
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_end_wait(void)
{
    FW(5, 3);
    so.unk7C = 2;
    frost_walrus_blizzard(&so);
}
static void fw_blizzard_end(void)
{
    FW(5, 3);
    so.unk7C = 1;
    frost_walrus_blizzard(&so);
}
static void fw_start_wait(void)
{
    FW(0, 0);
    effect_objects[0].active = 1;
    func_800722A0(&so);
}
static void fw_start(void) { ENGINE(0, (FW(0, 0), func_800722A0(&so))); }
static void fw_start_rematch(void) { ENGINE(0xC, (FW(0, 0), func_800722A0(&so))); }
static void fw_death_flash(void)
{
    FW(3, 0);
    effect_objects[0].active = 1;
    so.unk7E = 0;
    frost_walrus_death_finish(&so);
}
static void fw_death_count(void)
{
    FW(3, 0);
    effect_objects[0].active = 1;
    so.unk7E = 3;
    frost_walrus_death_finish(&so);
}
static void fw_death_held(void)
{
    FW(3, 0);
    effect_objects[0].active = 1;
    effect_objects[0].unk7 = 1;
    frost_walrus_death_finish(&so);
}
static void fw_death_done(void) { ENGINE(0, (FW(3, 0), frost_walrus_death_finish(&so))); }
static void fw_death_done_rematch(void) { ENGINE(0xC, (FW(3, 0), frost_walrus_death_finish(&so))); }

static void (*const frost_walrus_states_cases[])(void) = {
    fw_blizzard_start,
    fw_blizzard_wait,
    fw_blizzard_blow,
    fw_blizzard_finish_wait,
    fw_blizzard_finish,
    fw_blizzard_end_wait,
    fw_blizzard_end,
    fw_start_wait,
    fw_start,
    fw_start_rematch,
    fw_death_flash,
    fw_death_count,
    fw_death_held,
    fw_death_done,
    fw_death_done_rematch,
};
static const u32 frost_walrus_states_expected[] = { 0x105u, 0x180100u, 0x800000u, 0u, 0u, 0u, 0x16u, 3u, 0u, 0u, 0x105u, 0xFFFF0001u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0xFFFF0080u, 0x800000u, 0u, 0u, 0u, 0x16u, 0u, 0u, 0u, 0x205u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x305u, 0x60u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x305u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0x26u, 3u, 0x1000101u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0x26u, 3u, 0x1000101u, 0u, 3u, 0x50000u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 1u, 3u, 0x20000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1100000u, 0u, 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0xA800000u, 0u };

static u32 test_frost_walrus_states(u32 row)
{
    return state_run(frost_walrus_states_cases[row], row, &frost_walrus_states_expected[row * 10]);
}

extern void* frost_walrus_animations[39];
extern struct Unk_unk68 frost_walrus_hurt_box, frost_walrus_attack_box, D_80107A78[];
static const struct {
    u8 weapon, damage, lethal, flag;
} hits[] = {
    { 255, 0, 0, 0 },
    { 0, 1, 0, 1 },
    { 4, 4, 0, 0 },
    { 13, 5, 0, 0 },
    { 35, 5, 0, 0 },
    { 37, 0, 0, 0 },
    { 0, 1, 1, 1 },
};
static const u8 flash_times[] = { 0, 1, 2, 64 };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 weapon_flash(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % COUNT(hits), phase = row / COUNT(hits), character = phase % 2, staggered = phase / 2 % 2;
    u32 flash = flash_times[phase / 4], facing = (hit + phase) % 2, i;
    s32 kind = flash || hits[hit].weapon == 37 ? -1 : 0;
    u32 weakness = character ? hits[hit].weapon == 35 : hits[hit].weapon == 4 || hits[hit].weapon == 13;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_expected = g_Player;
    if (hits[hit].weapon == 35)
        player_expected.update_delay_request = 1;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.on_screen = 7;
    obj.bg_offset = 0;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x9234;
    obj.hp = hits[hit].lethal ? 1 : 48;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = 0x1234;
    obj.unk1C.val = 0x5678;
    obj.hurt_box = &frost_walrus_hurt_box;
    obj.attack_box = &frost_walrus_attack_box;
    obj.collision_data = flash ? D_801060F0 : D_80107A78;
    obj.ext.main_57.flash_timer = flash;
    obj.ext.main_57.flashing = flash != 0;
    obj.ext.main_57.staggered = staggered;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 0);
    if (hits[hit].weapon != 255) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = hits[hit].weapon;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)&frost_walrus_hurt_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk5 = 3;
    expected.unk6 = 0;
    expected.unk42 = 0x1234;
    expected.on_screen = 1;
    if (hits[hit].weapon != 255) {
        ((s16*)&weapons_expected[0].unk80)[0] = facing ? 159 : 161;
        ((s16*)&weapons_expected[0].unk80)[1] = 136;
        weapons_expected[0].unk98 = flash && hits[hit].weapon == 0 ? -1 : flash ? 0
                                                                                : hits[hit].flag;
        expected.unk63 = kind;
        if (!kind) {
            expected.hp = hits[hit].lethal ? 0 : 48 - hits[hit].damage;
            expected.unk42 |= 0x8000;
        }
    }
    if (flash) {
        expected.ext.main_57.flash_timer--;
        if (!(flash & 1))
            expected.unk42 |= 0x8000;
        if (flash == 1) {
            expected.collision_data = D_80107A78;
            expected.ext.main_57.flashing = 0;
        }
    } else if (hits[hit].lethal) {
        expected.state = 2;
        expected.unk5 = 0;
        expected.unk42 &= 0x7FFF;
        player_expected.spike_immune = 1;
    } else if (hits[hit].weapon != 255) {
        if (!kind && weakness && !staggered) {
            expected.unk5 = 10;
            expected.on_screen = 7;
        } else if (!character || !kind) {
            expected.collision_data = D_801060F0;
            expected.ext.main_57.flash_timer = 64;
            expected.ext.main_57.flashing = 1;
        }
    }
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    func_80072418(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == 0x1234);
    return 1;
}

void frost_walrus_stagger_recover(struct MainObj*);
extern void* frost_walrus_animations[39];
extern u8 frost_walrus_script_recover_high[4], frost_walrus_script_recover_low[4];
static const s8 health[] = { 23, 24, 48 };
static u32 recover(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 hp = row % 3, wait = row / 3 % 2, face = row / 6;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 10;
    obj.unk6 = 3;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = 1 + wait;
    obj.hp = health[hp];
    obj.ext.main_57.flashing = 1;
    obj.ext.main_57.flash_timer = 12;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 21);
    assert(obj.animation_step.packed == 0x23010002);
    expected = obj;
    expected.unk7C--;
    if (wait)
        expected.animation_step.fields.duration--;
    else {
        expected.ext.main_57.script = hp ? frost_walrus_script_recover_high : frost_walrus_script_recover_low;
        expected.unk5 = 3;
        expected.unk6 = 0;
        expected.ext.main_57.flashing = 0;
        expected.ext.main_57.flash_timer = 1;
    }
    frost_walrus_stagger_recover(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

void frost_walrus_stagger_fall(struct MainObj*);
extern void* frost_walrus_animations[39];
static struct VisualObj visuals_expected[32];
static u32 land(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_expected[3];
    u32 broken = row % 2, available = row / 2 % 2, face = row / 4 % 2, grounded = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    if (available)
        visual_objects[31].active = 0;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 10;
    obj.unk6 = 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.air_state = 1;
    obj.collision_flags = grounded ? 8 : 0;
    obj.ext.main_57.tusks_broken = broken;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 18);
    assert(obj.animation_step.packed == 0x08000001);
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x18000;
    obj.y_speed = -0x8000;
    obj.x_accel = 0x1000;
    obj.gravity = 0x4200;
    expected = obj;
    expected.x_pos.val += 0x18000;
    expected.y_pos.val += 0x8000;
    expected.x_speed += face ? 0x1000 : -0x1000;
    expected.y_speed -= 0x4200;
    expected.air_state = -1;
    if (grounded) {
        expected.air_state = 0;
        expected.unk6++;
        expected.unk17 = 20;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)frost_walrus_animations[20];
        expected.animation_step.packed = 0x21010002;
        backgrounds_expected[0].unk37 = 16;
        backgrounds_expected[0].unk46 = backgrounds_expected[0].unk3E.bytes[1] = 3;
        backgrounds_expected[0].unk3D = backgrounds_expected[0].unk3B = 1;
        backgrounds_expected[0].unk34 = 1;
        if (!broken && available) {
            visuals_expected[31].active = 0x41;
            visuals_expected[31].id = 24;
            visuals_expected[31].unk2 = 0x50;
            visuals_expected[31].unk15 = obj.unk15;
            visuals_expected[31].unk50 = PLAYER_OBJECT(&obj);
            expected.ext.main_57.tusks_broken = 1;
        }
    }
    cur_random = 0x1234;
    frost_walrus_stagger_fall(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_expected, sizeof(visuals_expected) / 4) == 0 && cur_random == 0x1234);
    return 1;
}

extern void* frost_walrus_animations[39];
static struct VisualObj expected_pool[32];
static u32 stagger(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 available = row % 3 == 2 ? 4 : row % 3, side = row / 3 % 2, face = row / 6, i;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    g_Player.x_pos.i.hi = side ? 180 : 140;
    player_before = g_Player;
    D_8013E198[2] = -1;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(expected_pool, visual_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.hp = 32;
    obj.unk5 = 10;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    expected = obj;
    expected.ext.main_57.staggered = 1;
    expected.unk17 = 18;
    expected.previous_animation_index = 255;
    expected.animation_cursor = frost_walrus_animations[18];
    expected.animation_step.packed = 0x08000001;
    expected.x_speed = side ? -0x20000 : 0x20000;
    expected.y_speed = 0x38000;
    expected.gravity = 0x4200;
    expected.ext.main_57.flash_timer = 200;
    expected.air_state = 1;
    expected.ext.main_57.flashing = 1;
    expected.collision_data = D_801060F0;
    expected.unk6 = 1;
    for (i = 0; i < available; i++) {
        struct VisualObj* v = &expected_pool[32 - available + i];
        v->active = 0x41;
        v->id = 24;
        v->unk2 = i + 64;
        v->unk50 = PLAYER_OBJECT(&obj);
        v->unk15 = obj.unk15;
    }
    func_80073E80(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "frost_walrus_states", 0, 0, COUNT(frost_walrus_states_cases), test_frost_walrus_states },
    { "frost_floor_archive", frost_floor_archive_cases, frost_floor_archive_cases_expected, COUNT(frost_floor_archive_cases), 0 },
    { "walrus_blizzard_animation_pools", NULL, walrus_blizzard_animation_pools_cases_expected, COUNT(walrus_blizzard_animation_pools_cases_expected), blizzard_case },
    { "walrus_charge_tusk_context", NULL, walrus_charge_tusk_context_cases_expected, COUNT(walrus_charge_tusk_context_cases_expected), charge_case },
    { "walrus_intro_player_boundary", NULL, walrus_intro_player_boundary_cases_expected, COUNT(walrus_intro_player_boundary_cases_expected), intro_case },
    { "walrus_script_exhaustion", NULL, walrus_script_exhaustion_cases_expected, COUNT(walrus_script_exhaustion_cases_expected), script_case },
    { "frost_walrus_death_explode", 0, 0, 1, test_frost_walrus_death_explode },
    { "frost_walrus_shards_count", 0, 0, 1, test_frost_walrus_shards_count },
    { "frost_walrus_shards_fire", 0, 0, 1, test_frost_walrus_shards_fire },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "character_weakness_parry_flash_and_death", NULL, NULL, COUNT(hits) * 16, weapon_flash },
    { "health23_24_boundary_selects_actual_recovery_script", NULL, NULL, 12, recover },
    { "grounding_existing_tusks_and_exhausted_visual_pool", NULL, NULL, 16, land },
    { "Walrus_own_stagger_four_sweat_sprites_full_partial_slots", NULL, NULL, 12, stagger },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frost_walrus_states_cases) + COUNT(frost_floor_archive_cases) + COUNT(walrus_blizzard_animation_pools_cases_expected) + COUNT(walrus_charge_tusk_context_cases_expected) + COUNT(walrus_intro_player_boundary_cases_expected) + COUNT(walrus_script_exhaustion_cases_expected) + 1 + 1 + 1 + COUNT(pool_full_cases) + COUNT(hits) * 16 + 12 + 16 + 12;
