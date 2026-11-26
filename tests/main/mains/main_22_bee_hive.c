#include "test_runtime.h"
#include "main/mains/main_22_bee_hive.h"
#include "main/55C4.h"
#include "support/state_cases.h"
#include "main/195B4.h"
#include "weapon_resources.h"
void func_800559BC(struct MainObj*);

static const u32 inputs_0[2][2] = {
    { 1, 0 },
    { 0, 0 },
};
struct bee_hive_wait_watch_case {
    u32 expected[3];
};
static const struct bee_hive_wait_watch_case bee_hive_wait_watch_cases[] = {
    { { 0u, 0u, 0u } },
    { { 0x28u, 0u, 0u } },
};
static u32 test_bee_hive_wait_watch(u32 row)
{
    const struct bee_hive_wait_watch_case* c = &bee_hive_wait_watch_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_22.unk84 = inputs_0[row][0];
    obj.ext.main_22.unk8C = inputs_0[row][1];
    bee_hive_wait_watch(&obj);
    observed_values[0] = (u32)obj.ext.main_22.unk84;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static struct MainObj func_80055358_0_hive_pool_expected[48];
static const u32 func_80055358_expected[] = { 8u };
static u32 test_func_80055358(u32 row)
{
    u32 observed_values[1];
    struct EngineObj engine_expected;
    struct PlayerObj player_expected;
    struct MainObj* obj;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    obj = &main_objects[0];
    memset(obj, 0, sizeof(*obj));
    obj->active = 0x41;
    obj->id = 22;
    obj->x_pos.i.hi = 104;
    obj->y_pos.i.hi = 132;
    func_80055024(obj);
    main_objects[1] = *obj;
    main_objects[2] = *obj;
    main_objects[3] = *obj;
    main_objects[4] = *obj;
    main_objects[5] = *obj;
    main_objects[6] = *obj;
    main_objects[7] = *obj;
    main_objects[8] = *obj;
    main_objects[9] = *obj;
    main_objects[10] = *obj;
    main_objects[11] = *obj;
    main_objects[12] = *obj;
    main_objects[13] = *obj;
    main_objects[14] = *obj;
    main_objects[15] = *obj;
    main_objects[16] = *obj;
    main_objects[17] = *obj;
    main_objects[18] = *obj;
    main_objects[19] = *obj;
    main_objects[20] = *obj;
    main_objects[21] = *obj;
    main_objects[22] = *obj;
    main_objects[23] = *obj;
    main_objects[24] = *obj;
    main_objects[25] = *obj;
    main_objects[26] = *obj;
    main_objects[27] = *obj;
    main_objects[28] = *obj;
    main_objects[29] = *obj;
    main_objects[30] = *obj;
    main_objects[31] = *obj;
    main_objects[32] = *obj;
    main_objects[33] = *obj;
    main_objects[34] = *obj;
    main_objects[35] = *obj;
    main_objects[36] = *obj;
    main_objects[37] = *obj;
    main_objects[38] = *obj;
    main_objects[39] = *obj;
    main_objects[40] = *obj;
    main_objects[41] = *obj;
    main_objects[42] = *obj;
    main_objects[43] = *obj;
    main_objects[44] = *obj;
    main_objects[45] = *obj;
    main_objects[46] = *obj;
    main_objects[47] = *obj;
    bee_hive_open_start(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    memcpy(func_80055358_0_hive_pool_expected, main_objects, sizeof(main_objects));
    animate_object(ANIMATED_OBJECT(&func_80055358_0_hive_pool_expected[0]));
    func_80055358_0_hive_pool_expected[0].ext.main_22.unk84 = 8;
    engine_expected = engine_obj;
    player_expected = g_Player;
    func_80055358(obj);
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)func_80055358_0_hive_pool_expected, sizeof(main_objects) / 4) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&engine_expected, sizeof(engine_obj) / 4) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&player_expected, sizeof(g_Player) / 4) == 0);
    observed_values[0] = obj->ext.main_22.unk84;
    return c_test_observe(0, row, observed_values, func_80055358_expected, 1);
}

static struct MainObj func_800559BC_0_hive_pool_expected[48];
static const u32 func_800559BC_expected[] = { 0x1Eu };
static u32 test_func_800559BC(u32 row)
{
    u32 observed_values[1];
    struct EngineObj engine_expected;
    struct PlayerObj player_expected;
    struct MainObj* obj;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    obj = &main_objects[0];
    memset(obj, 0, sizeof(*obj));
    obj->active = 0x41;
    obj->id = 22;
    obj->x_pos.i.hi = 104;
    obj->y_pos.i.hi = 132;
    func_80055024(obj);
    main_objects[1] = *obj;
    main_objects[2] = *obj;
    main_objects[3] = *obj;
    main_objects[4] = *obj;
    main_objects[5] = *obj;
    main_objects[6] = *obj;
    main_objects[7] = *obj;
    main_objects[8] = *obj;
    main_objects[9] = *obj;
    main_objects[10] = *obj;
    main_objects[11] = *obj;
    main_objects[12] = *obj;
    main_objects[13] = *obj;
    main_objects[14] = *obj;
    main_objects[15] = *obj;
    main_objects[16] = *obj;
    main_objects[17] = *obj;
    main_objects[18] = *obj;
    main_objects[19] = *obj;
    main_objects[20] = *obj;
    main_objects[21] = *obj;
    main_objects[22] = *obj;
    main_objects[23] = *obj;
    main_objects[24] = *obj;
    main_objects[25] = *obj;
    main_objects[26] = *obj;
    main_objects[27] = *obj;
    main_objects[28] = *obj;
    main_objects[29] = *obj;
    main_objects[30] = *obj;
    main_objects[31] = *obj;
    main_objects[32] = *obj;
    main_objects[33] = *obj;
    main_objects[34] = *obj;
    main_objects[35] = *obj;
    main_objects[36] = *obj;
    main_objects[37] = *obj;
    main_objects[38] = *obj;
    main_objects[39] = *obj;
    main_objects[40] = *obj;
    main_objects[41] = *obj;
    main_objects[42] = *obj;
    main_objects[43] = *obj;
    main_objects[44] = *obj;
    main_objects[45] = *obj;
    main_objects[46] = *obj;
    main_objects[47] = *obj;
    bee_hive_wait_start(obj);
    bee_hive_wait_watch(obj);
    bee_hive_release_start(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    memcpy(func_800559BC_0_hive_pool_expected, main_objects, sizeof(main_objects));
    animate_object(ANIMATED_OBJECT(&func_800559BC_0_hive_pool_expected[0]));
    func_800559BC_0_hive_pool_expected[0].ext.main_22.unk84 = 30;
    func_800559BC_0_hive_pool_expected[0].unk6 = func_800559BC_0_hive_pool_expected[0].unk6 + 1;
    engine_expected = engine_obj;
    player_expected = g_Player;
    bee_hive_release_wait(obj);
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)func_800559BC_0_hive_pool_expected, sizeof(main_objects) / 4) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&engine_expected, sizeof(engine_obj) / 4) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&player_expected, sizeof(g_Player) / 4) == 0);
    observed_values[0] = obj->ext.main_22.unk84;
    return c_test_observe(0, row, observed_values, func_800559BC_expected, 1);
}

static void bh_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_22.saved_unk5 = 3;
    bee_hive_resume_step(&so);
}

void func_80055164(struct MainObj*);
void func_80055358(struct MainObj*);
void bee_hive_open_end(struct MainObj*);
void bee_hive_release_pause(struct MainObj*);
void bee_hive_shake_end(struct MainObj*);
void bee_hive_explode_smoke(struct MainObj*);
static s32 bh_frames[64];
static u32 bh_meta[0x40];
#define BH(step, sub, setup) (state_reset(step, sub, 0), memset(main_objects, 0, sizeof(main_objects)), memset(weapon_objects, 0, sizeof(weapon_objects)), TEST_MENU_FRAMES = (u8*)bh_frames, D_801406A8 = bh_meta, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, setup)
#define BHX() (state_extra = so.ext.main_22.unk84 | (u32)so.ext.main_22.destroyed << 8 | (u32)so.ext.main_22.parts_mask << 16 | (u32)so.state << 28)
static void bh_main_hit_reaction(void) { BH(0, 0, so.unk63 = 1), func_80055164(&so), BHX(); }
static void bh_main_destroyed_away(void) { BH(6, 1, (so.ext.main_22.destroyed = 1, so.ext.main_22.unk84 = 5, so.x_pos.i.hi = 0x1000)), func_80055164(&so), BHX(); }
static void bh_main_away_parts_out(void) { BH(6, 1, (so.ext.main_22.destroyed = 1, so.ext.main_22.unk84 = 5, so.ext.main_22.parts_mask = 1, so.x_pos.i.hi = 0x1000)), func_80055164(&so), BHX(); }
static void bh_main_defeated(void) { BH(6, 1, (so.ext.main_22.unk84 = 5, so.hp = 1, state_hit(&so, 0, 0, 1), cur_random = 1)), func_80055164(&so), BHX(); }
static void bh_open_last_pair(void) { BH(2, 1, (so.ext.main_22.unk84 = 1, so.ext.main_22.unk90 = 8)), func_80055358(&so), BHX(), state_extra ^= so.ext.main_22.unk90 << 8 ^ main_objects[0].ext.main_5.part_index << 24; }
static void bh_open_end(void) { BH(2, 2, so.ext.main_22.unk84 = 1), bee_hive_open_end(&so), BHX(); }
static void bh_open_end_wait(void) { BH(2, 2, so.ext.main_22.unk84 = 2), bee_hive_open_end(&so), BHX(); }
static void bh_release_pause_end(void) { BH(4, 2, so.ext.main_22.unk84 = 1), bee_hive_release_pause(&so), BHX(); }
static void bh_release_pause(void) { BH(4, 2, so.ext.main_22.unk84 = 2), bee_hive_release_pause(&so), BHX(); }
static void bh_shake_end(void) { BH(5, 1, so.ext.main_22.unk84 = 1), bee_hive_shake_end(&so), BHX(); }
static void bh_shake_end_wait(void) { BH(5, 1, so.ext.main_22.unk84 = 2), bee_hive_shake_end(&so), BHX(); }
static void bh_smoke(void) { BH(6, 1, (so.ext.main_22.unk84 = 2, WEAPON_FRAME_COUNTER = 5)), bee_hive_explode_smoke(&so), BHX(); }
static void bh_smoke_end(void) { BH(6, 1, so.ext.main_22.unk84 = 1), bee_hive_explode_smoke(&so), BHX(); }
#define BH_RELEASE(mask) (BH(4, 0, so.ext.main_22.parts_mask = mask), func_800559BC(&so), BHX(), state_extra ^= (u32)(u16)main_objects[1].x_pos.i.hi << 4 ^ main_objects[1].ext.main_5.part_index)
static void bh_release_skip_odd(void) { BH_RELEASE(5); }
static void bh_release_skip_even(void) { BH_RELEASE(2); }static void (*const bee_hive_misc_cases[])(void) = {
    bh_resume,
    bh_main_hit_reaction,
    bh_main_destroyed_away,
    bh_main_away_parts_out,
    bh_main_defeated,
    bh_open_last_pair,
    bh_open_end,
    bh_open_end_wait,
    bh_release_pause_end,
    bh_release_pause,
    bh_shake_end,
    bh_shake_end_wait,
    bh_smoke,
    bh_smoke_end,
    bh_release_skip_odd,
    bh_release_skip_even,
};
static const u32 bee_hive_misc_expected[] = {
    3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x100u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x2700u, 0x10000000u, 0x0u,
    0x106u, 0x0u, 0x10000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x20000104u, 0x2100u,
    0x106u, 0x0u, 0x10000000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10010104u, 0x2100u,
    0x6u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x3u, 0x1u, 0x10000104u, 0x2100u,
    0x202u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x2u, 0x0u, 0x1B000A08u, 0x0u,
    0x3u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000000u, 0x0u,
    0x202u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000001u, 0x0u,
    0x5u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000000u, 0x0u,
    0x204u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000001u, 0x0u,
    0x3u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000000u, 0x0u,
    0x105u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000001u, 0x0u,
    0x106u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000001u, 0x0u,
    0x206u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10000000u, 0x0u,
    0x4u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x100F0803u, 0x0u,
    0x4u, 0x0u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10070802u, 0x0u,
};

static u32 test_bee_hive_misc(u32 row)
{
    return state_run(bee_hive_misc_cases[row], row, &bee_hive_misc_expected[row * 10]);
}

void robot_bee_update(struct MainObj*);
void bee_hive_update(struct MainObj*);
void bee_hive_open(struct MainObj*);
void bee_hive_despawn(struct MainObj*);
static struct MainObj expected[48];
static struct StageObjectRecord records[2] = { { 0, 22, 0, 0, 160, 120 }, { 0, 0, 0, 255, 0, 0 } };
static struct StageObjectRecord replacement[2] = { { 0, 5, 0, 0, 160, 120 }, { 0, 0, 0, 255, 0, 0 } };
static u32 metadata[12], frames[64];
static u8 commands[84];
static u32 owner_reuse(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    u8 *old_frames = TEST_MENU_FRAMES, *old_commands = D_80141F50[2];
    u32* old_metadata = D_801406A8;
    u32 i, record_before[8];
    u16 rng;
    (void)row;
    c_test_copy_words(record_before, (u32*)records, 4);
    c_test_copy_words(record_before + 4, (u32*)replacement, 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    g_Player.bg_offset = 0;
    g_Player.x_pos.i.hi = 200;
    g_Player.y_pos.i.hi = 120;
    engine_obj.stage = 1;
    engine_obj.substage = 1;
    engine_obj.checkpoint = 0;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = i < 12 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    D_80141F50[2] = commands;
    assert(func_8002938C(5) == 2);
    func_800292D0(records);
    SP_CUR_MAIN_OBJ = &main_objects[0];
    bee_hive_update(&main_objects[0]);
    bee_hive_open(&main_objects[0]);
    for (i = 0; i < 8; i++)
        bee_hive_open(&main_objects[0]);
    assert(main_objects[0].ext.main_22.parts_mask == 3 && main_objects[1].active == 0x41 && main_objects[1].id == 5 && main_objects[1].unk2 == 3 && main_objects[1].ext.main_5.owner == &main_objects[0]);
    SP_CUR_MAIN_OBJ = &main_objects[1];
    robot_bee_update(&main_objects[1]);
    background_objects[0].x_pos.i.hi = 1000;
    robot_bee_update(&main_objects[1]);
    assert(main_objects[1].state == 2);
    bee_hive_despawn(&main_objects[0]);
    assert(main_objects[0].active == 0);
    if (row) {
        func_800292D0(replacement);
        assert(main_objects[0].active == 1 && main_objects[0].id == 5);
    }
    c_test_copy_words((u32*)expected, (u32*)main_objects, sizeof(expected) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    c_test_zero_words((u32*)&expected[1], 2);
    robot_bee_update(&main_objects[1]);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && SP_CUR_MAIN_OBJ == &main_objects[1] && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)frames && D_80141F50[2] == commands);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 12 ? 64u : 0));
    for (i = 0; i < COUNT(commands); i++)
        assert(commands[i] == 0);
    assert(c_test_word_difference((u32*)records, record_before, 4) == 0 && c_test_word_difference((u32*)replacement, record_before + 4, 4) == 0);
    SP_CUR_MAIN_OBJ = current;
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    D_80141F50[2] = old_commands;
    return 1;
}

static const struct {
    s16 player_x;
    u32 expected[5];
} release_cases[] = {
    { 0x300, { 0x01C8010Au, 0x0230010Au, 0x1000003u, 0x1000103u, 0x10003u } },
    { 0x100, { 0x01D0010Au, 0x0238010Au, 0x1000003u, 0x1000103u, 0x10003u } },
};
static u32 release(u32 row)
{
    static struct MainObj hive;
    u8* old_frames = TEST_MENU_FRAMES;
    u32* old_metadata = D_801406A8;
    u32 observed[5], i;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)&hive, sizeof(hive) / 4);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = (i + 1) * 64;
    D_801406A8 = metadata;
#ifdef MMX4_SATURN
    saturn_stage_graphics_offsets_pointer = metadata;
#endif
    TEST_MENU_FRAMES = (u8*)frames;
    engine_obj.stage = 1;
    engine_obj.substage = 1;
    hive.active = 0x41;
    hive.id = 22;
    hive.x_pos.i.hi = 0x200;
    hive.y_pos.i.hi = 0x100;
    g_Player.x_pos.val = release_cases[row].player_x << 16;
    func_800559BC(&hive);
    for (i = 0; i < 2; i++) {
        struct MainObj* bee = &main_objects[i];
        assert(bee->active == 0x41 && bee->id == 5 && bee->unk2 == 3 && bee->on_screen == 0 && bee->state == 0);
        assert(bee->x_pos.i.hi == (i ? 0x210 : 0x1F0) && bee->y_pos.i.hi == 0x109 && bee->ext.main_5.owner == &hive);
        assert(bee->unk40 == (u16)OBJECT_STAGE_TEXTURE(func_8002938C(5)) && bee->unk42 == (u16)OBJECT_STAGE_CLUT(5));
        assert(bee->sprite_frames == (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(5)]);
        observed[i] = bee->ext.main_5.target_x | (u32)bee->ext.main_5.target_y << 16;
    }
    assert(main_objects[2].active == 0);
    observed[2] = main_objects[0].ext.main_5.part_index | (u32)main_objects[0].unk2 | (u32)hive.ext.main_22.unk8C << 24;
    observed[3] = main_objects[1].ext.main_5.part_index << 8 | (u32)main_objects[1].unk2 | (u32)hive.ext.main_22.unk8C << 24;
    observed[4] = hive.ext.main_22.parts_mask | (u32)(engine_obj.stage == 1) << 16;
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    return c_test_observe(0, row, observed, release_cases[row].expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "bee_hive_misc", 0, 0, COUNT(bee_hive_misc_cases), test_bee_hive_misc },
    { "bee_hive_wait_watch", 0, 0, 2, test_bee_hive_wait_watch },
    { "func_80055358", 0, 0, 1, test_func_80055358 },
    { "func_800559BC", 0, 0, 1, test_func_800559BC },
    { "actual_hive_birth_child_offscreen_owner_despawn_or_Bee_slot_reuse", NULL, NULL, 2, owner_reuse },
    { "release_first_two_parts_into_an_empty_pool", NULL, NULL, COUNT(release_cases), release },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bee_hive_misc_cases) + 2 + 1 + 1 + 2 + COUNT(release_cases);
