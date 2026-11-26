#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/items/item_27_boss_teleporter.h"
#include "support/state_cases.h"
#include "main/195B4.h"
void boss_teleporter_close(struct ItemObj*);

static const u32 func_800C7970_expected[] = { 1u };
static u32 test_func_800C7970(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    struct PlayerObj argument_obj_1;
    struct Unk_unk68 child_0;
    struct Unk_unk68 child_1;
    s8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    obj.x_pos.u.hi = 55300;
    child_1.unk2 = 136;
    argument_obj_1.x_pos.u.hi = 32768;
    child_0.unk2 = 192;
    obj.y_pos.u.hi = 32704;
    child_1.unk1 = 64;
    argument_obj_1.y_pos.u.hi = 12160;
    child_0.unk1 = 127;
    argument_obj_1.unk68 = &child_0;
    obj.unk68 = &child_1;
    return_value = func_800C7970(&obj, &argument_obj_1);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_800C7970_expected, 1);
}

#include "support/pool_full.h"
static u32 pool_full_boss_teleporter_warp_start(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    boss_teleporter_warp_start(&pf_item);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_boss_teleporter_warp_start,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

#include "support/warp_spawns.h"
WARP_BOSS_CASE(boss_first_uncleared, 8, 0)
WARP_BOSS_CASE(boss_last_uncleared, 15, 0)
WARP_BOSS_CASE(boss_spawn, 0, 0)
WARP_BOSS_CASE(boss_full, 0, 1)
static const CTestCase bosses_cleared_warp_cases[] = { WARP_ENTRY(boss_first_uncleared) WARP_ENTRY(boss_last_uncleared) WARP_ENTRY(boss_spawn) WARP_ENTRY(boss_full) };

static const u32 bosses_cleared_warp_cases_expected[] = { 0x7u, 0x7u, 0x1410100u, 0x10100u };
#define si state_room.item
#define TELE(rel)                                          \
    do {                                                   \
        u8 slot = engine_obj.character_state.bytes[7];     \
        state_reset(0, 0, 0);                              \
        si.active = 1;                                     \
        si.state = 2;                                      \
        si.unk2 = 1;                                       \
        si.x_pos.i.hi = 0x80;                              \
        si.y_pos.i.hi = 0x60;                              \
        si.animation_step.fields.relative_step = rel;      \
        engine_obj.character_state.bytes[7] = 0;           \
        boss_teleporter_close(&si);                        \
        state_extra = engine_obj.character_state.bytes[7]; \
        engine_obj.character_state.bytes[7] = slot;        \
    } while (0)
static void bt_closing(void)
{
    TELE(1);
}
static void bt_closed(void) { TELE(0); }
extern u8 boss_teleporter_box[4];
void boss_teleporter_warp(struct ItemObj*);
void boss_teleporter_main(struct ItemObj*);
void boss_teleporter_wait_player(struct ItemObj*);
void boss_teleporter_wait_enter(struct ItemObj*);
void boss_teleporter_warp_charge(struct ItemObj*);
void boss_teleporter_warp_leave(struct ItemObj*);
void boss_teleporter_warp_finish(struct ItemObj*);
static struct Unk_unk68 tele_player_box = { 0, -16, 8, 16 };
static u32 tele_archive[8], tele_meta[64];
#define BT(step, setup)                                                                                                                       \
    (state_reset(step, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 12,                                              \
        memset(main_objects, 0, sizeof(main_objects)), memset(&g_Player, 0, sizeof(g_Player)), g_Player.active = 0x41,                        \
        g_Player.hp = 24, TEST_MENU_FRAMES = (u8*)tele_archive, D_801406A8 = tele_meta, tele_archive[2] = 32, si.active = 0x41, si.id = 0x1B, \
        si.state = 1, si.unk2 = 0x13, si.x_pos.i.hi = 0x80, si.y_pos.i.hi = 0x60,                                                             \
        si.unk68 = (struct Unk_unk68*)boss_teleporter_box, setup)
#define BTX() (state_extra = (u8)si.tail_ext.unk1.unk84.timer | (u32)(u8)g_Player.script_action << 8 | (u32)(u16)g_Player.y_pos.i.hi << 16 ^ (u32)(u8)engine_obj.checkpoint << 24 ^ misc_objects[0].unk2 << 4 ^ misc_objects[1].unk17, engine_obj.stage = 0)
static void bt_init_return(void)
{
    BT(0, si.state = 0), func_800C71C0(&si), si.unk42 = 0, si.unk40 = 0, BTX();
}
static void bt_main_on_screen(void) { BT(3, g_Player.script_state = 0), boss_teleporter_main(&si), BTX(); }
static void bt_main_off_screen(void) { BT(3, (g_Player.script_state = -1, si.x_pos.i.hi = 0x300)), boss_teleporter_main(&si), BTX(); }
static void bt_wait(s16 dx, u8 box, u8 full)
{
    u32 i;
    BT(0, (g_Player.x_pos.i.hi = 0x80 + dx, g_Player.y_pos.i.hi = 0x58, g_Player.unk68 = box ? &tele_player_box : NULL));
    for (i = 0; full && i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    boss_teleporter_wait_player(&si), BTX();
}
static void bt_wait_no_box(void) { bt_wait(0, 0, 0); }
static void bt_wait_left(void) { bt_wait(-0x10, 1, 0); }
static void bt_wait_right(void) { bt_wait(0x10, 1, 0); }
static void bt_wait_inside(void) { bt_wait(0, 1, 0); }
static void bt_wait_inside_full(void) { bt_wait(0, 1, 1); }
static void bt_enter_waiting(void) { BT(1, g_Player.script_state = 0), boss_teleporter_wait_enter(&si), BTX(); }
static void bt_enter_done(void) { BT(1, (g_Player.script_state = -1, background_objects[0].x_pos.i.hi = 0x40)), boss_teleporter_wait_enter(&si), state_extra ^= (u16)background_objects[0].unk26, BTX(); }
static void bt_warp_start(void) { BT(2, 0), boss_teleporter_warp(&si), BTX(); }
#define BT_TIMER(run) (BT(2, (si.tail_ext.unk1.unk84.timer = 2, misc_objects[1].animation_table = state_table, si.unk7C.object = (struct MainObj*)&misc_objects[1])), run(&si), assert(si.tail_ext.unk1.unk84.timer == 1), run(&si), BTX())
static void bt_warp_charge(void)
{
    BT_TIMER(boss_teleporter_warp_charge);
}
static void bt_warp_leave(void) { BT_TIMER(boss_teleporter_warp_leave); }
static void bt_warp_finish(void) { BT_TIMER(boss_teleporter_warp_finish); }

static void (*const boss_teleporter_states_cases[])(void) = {
    bt_closing,
    bt_closed,
    bt_init_return,
    bt_main_on_screen,
    bt_main_off_screen,
    bt_wait_no_box,
    bt_wait_left,
    bt_wait_right,
    bt_wait_inside,
    bt_wait_inside_full,
    bt_enter_waiting,
    bt_enter_done,
    bt_warp_start,
    bt_warp_charge,
    bt_warp_leave,
    bt_warp_finish,
};
static const u32 boss_teleporter_states_expected[] = {
    0x2u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x3u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2u,
    0x0u,
    0x401u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000u,
    0x0u,
    0x0u,
    0x301u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x4u,
    0x1341u,
    0x3000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x3000000u,
    0x0u,
    0x1u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x580000u,
    0x0u,
    0x1u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x580000u,
    0x0u,
    0x1u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x580000u,
    0x0u,
    0x101u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x481500u,
    0x41000000u,
    0x101u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x481400u,
    0x1000000u,
    0x101u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x201u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x10201u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x278u,
    0x41000000u,
    0x10201u,
    0xFF001341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x78u,
    0x0u,
    0x10201u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1628u,
    0x0u,
    0x301u,
    0x1341u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};

static u32 test_boss_teleporter_states(u32 row)
{
    return object_run(boss_teleporter_states_cases[row], row, &boss_teleporter_states_expected[row * 10]);
}

struct Item26AnimationStep;
extern struct Item26AnimationStep* boss_teleporter_animations[11];
static struct MiscObj expected_pool[64];
static u32 teleporter_init_case(u32 row, u32 status)
{
    static const s8 free_slots[4] = { -1, 0, 31, 63 };
    static const u8 animations[3] = { 1, 10, 6 };
    static const u32 first_words[3] = { C_TEST_STEP(0x00010004), C_TEST_STEP(0x4901002D), C_TEST_STEP(0x4E000008) };
    struct ItemObj obj, expected;
    struct EngineObj engine_before;
    u32 archive[40], metadata[8], i, layout = row / 3 % 4;
    u32 kind = row / 12 % 8, animation = status >= 3 ? 6 : animations[status];
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = 0x13570000 + i;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = 0x10000 + 0x800 * i;
    archive[2] = 64;
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = metadata;
    engine_obj.stage = 12;
    engine_obj.substage = 0;
    engine_obj.character_state.bytes[6 + kind] = status;
    obj.active = 1;
    obj.id = 27;
    obj.unk2 = kind;
    obj.unk5 = 9;
    obj.unk6 = 10;
    obj.unk67 = 11;
    obj.unk75 = 12;
    obj.unk16 = VISUAL_SATURN_LAYER(0x25);
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk7C.misc = &misc_objects[63];
    obj.unk42 = 0xFFFF;
    obj.animation_step.packed = C_TEST_STEP(0x12345678);
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 21;
        misc_objects[i].state = 2;
        misc_objects[i].x_pos.val = 0x34567812;
        misc_objects[i].y_pos.val = 0x56781234;
        misc_objects[i].unk7 = 0x25;
    }
    if (layout)
        misc_objects[free_slots[layout]].active = 0;
    c_test_copy_words((u32*)expected_pool, (u32*)misc_objects, sizeof(expected_pool) / 4);
    expected = obj;
    engine_before = engine_obj;
    expected.active = 0x41;
    expected.unk16 = VISUAL_SATURN_LAYER(6);
    expected.unk15 = 0;
#ifdef MMX4_SATURN
    expected.unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x88));
    expected.unk42 = OBJECT_STAGE_CLUT(0x88);
#else
    expected.unk40 = 0x220;
    expected.unk42 = 0x7880;
#endif
    expected.sprite_frames = (u8*)archive + 64;
    expected.animation_table = (const u8* const*)boss_teleporter_animations;
    expected.unk67 = expected.unk75 = 0;
    expected.unk68 = (struct Unk_unk68*)boss_teleporter_box;
    if (status < 3) {
        expected.animation_cursor = (const u8*)boss_teleporter_animations[animation];
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_step.packed = first_words[status];
        expected.state = status + 1;
        expected.unk5 = 0;
        assert(*(u32*)boss_teleporter_animations[animation] == expected.animation_step.packed);
    }
    expected.unk6 = 0;
    expected.unk2 = kind;
    if (status < 2 && layout) {
        struct MiscObj* child = &expected_pool[free_slots[layout]];
        child->active = 0x41;
        child->id = 0x33;
        child->unk2 = status ? 0x30 : 0;
        child->x_pos = obj.x_pos;
        child->y_pos = obj.y_pos;
        child->ext.misc_51.source = (struct MainObj*)&obj;
        expected.unk7C.misc = &misc_objects[free_slots[layout]];
    }
    assert(s_StageMainIds[12][0][2] == 0x88 && (u8)func_8002938C(0x88) == 2);
    func_800C71C0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(misc_objects, expected_pool, sizeof(misc_objects));
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i == 2 ? 64 : 0x13570000 + i));
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == 0x10000 + 0x800 * i);
    assert(boss_teleporter_box[0] == 0 && boss_teleporter_box[1] == 0 && boss_teleporter_box[2] == 32 && boss_teleporter_box[3] == 8);
    assert(TEST_MENU_FRAMES == (u8*)archive && D_801406A8 == metadata);
    return 1;
}
static u32 test_teleporter_init(u32 row) { return teleporter_init_case(row, row % 3); }
static u32 test_unknown_status(u32 row) { return teleporter_init_case(row / 2 * 12 + (row & 1) * 3, row & 1 ? 0xFF : 3); }

const struct CTestGroup c_test_groups[] = {
    { "boss_teleporter_states", 0, 0, COUNT(boss_teleporter_states_cases), test_boss_teleporter_states },
    { "func_800C7970", 0, 0, 1, test_func_800C7970 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "bosses_cleared_warp", bosses_cleared_warp_cases, bosses_cleared_warp_cases_expected, COUNT(bosses_cleared_warp_cases), 0 },
    { "teleporter_initial_status_and_pool", NULL, NULL, 96, test_teleporter_init },
    { "teleporter_unknown_status_fallback", NULL, NULL, 16, test_unknown_status },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_teleporter_states_cases) + 1 + COUNT(pool_full_cases) + COUNT(bosses_cleared_warp_cases) + 96 + 16;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
