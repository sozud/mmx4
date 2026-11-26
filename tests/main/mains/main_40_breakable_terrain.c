#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_40_breakable_terrain.h"
#include "support/state_cases.h"
extern s8* D_800FEA24[7];
extern struct Unk_unk68 D_800FEAA0;
extern union AnimationStep* breakable_terrain_animations[6];

struct func_80061F2C_0_case {
    u32 unk80;
    u32 expected[15];
};
static const struct func_80061F2C_0_case func_80061F2C_0_cases[] = {
    { 0, { 0x41u, 1u, 0u, 0u, 0x1234u, 0u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 7, { 0x41u, 1u, 0u, 0u, 0x1234u, 0u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_80061F2C_0(u32 row)
{
    const struct func_80061F2C_0_case* c = &func_80061F2C_0_cases[row];
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&visual_objects, 1, sizeof(visual_objects));
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk42 = 0x1234;
    obj.ext.main_40.unk80 = c->unk80;
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    g_Player.unk68 = &D_800FEAA0;
    player_before = g_Player;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_80061F2C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.ext.main_40.timer;
    observed_values[9] = (u32)obj.ext.main_40.trigger_time;
    observed_values[10] = (u32)obj.unk63;
    observed_values[11] = (u32)obj.unk65;
    observed_values[12] = (u32)weapon_objects[0].unk98;
    observed_values[13] = TEST_LE_HALVES(&weapon_objects[0].unk80);
    observed_values[14] = (u32)(obj.animation_table == (const u8* const*)breakable_terrain_animations);
    return c_test_observe(0, row, observed_values, c->expected, 15);
}
static const u32 func_80061F2C_1_expected[] = { 0x41u, 1u, 0u, 2u, 0x9234u, 1u, 0x640000u, 0x500000u, 0u, 0u, 0u, 0u, 0u, 0x500064u, 1u };
static u32 test_func_80061F2C_1(u32 row)
{
    u32 observed_values[15];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct VisualObj visuals_before[32];
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&visual_objects, 1, sizeof(visual_objects));
    memset(&D_8013E198, -1, sizeof(D_8013E198));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk42 = 0x1234;
    obj.ext.main_40.unk80 = 1;
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    g_Player.unk68 = &D_800FEAA0;
    obj.unk2 = 0x10;
    obj.state = 0;
    func_80061DFC(&obj);
    assert(obj.hp == 3 && obj.state == 1);
    assert(obj.hurt_box == (const u8*)D_800FEA24[1]);
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 1;
    weapon_objects[0].unk50 = (const u8*)D_800FEA24[1];
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    player_before = g_Player;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_80061F2C(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.ext.main_40.timer;
    observed_values[9] = (u32)obj.ext.main_40.trigger_time;
    observed_values[10] = (u32)obj.unk63;
    observed_values[11] = (u32)obj.unk65;
    observed_values[12] = (u32)weapon_objects[0].unk98;
    observed_values[13] = TEST_LE_HALVES(&weapon_objects[0].unk80);
    observed_values[14] = (u32)(obj.animation_table == (const u8* const*)breakable_terrain_animations);
    return c_test_observe(1, row, observed_values, func_80061F2C_1_expected, 15);
}
static u32 test_func_80061F2C(u32 index)
{
    if (index < 2)
        return test_func_80061F2C_0(index);
    index -= 2;
    return test_func_80061F2C_1(index);
}

static u8 terrain_record;
#define BT(mode, setup) (state_reset(0, 0, 0), so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.ext.main_40.unk80 = mode, setup, func_80061F2C(&so), state_extra = so.ext.main_40.timer | so.ext.main_40.trigger_time << 16)
static void btr_drop(void)
{
    BT(2, so.y_pos.i.hi = 0x200);
}
static void btr_drop_wait(void) { BT(3, 0); }
static void btr_idle(void) { BT(0, 0); }
static void btr_away(void)
{
    terrain_record = 0;
    BT(0, (so.x_pos.i.hi = 0x1000, so.backref = (void*)&terrain_record));
    state_extra ^= terrain_record << 8;
    so.backref = NULL;
}

static void (*const breakable_terrain_main_cases[])(void) = {
    btr_drop,
    btr_drop_wait,
    btr_idle,
    btr_away,
};
static const u32 breakable_terrain_main_expected[] = { 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x80010u, 0u, 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_breakable_terrain_main(u32 row)
{
    return state_run(breakable_terrain_main_cases[row], row, &breakable_terrain_main_expected[row * 10]);
}

#include "support/tile_writes.h"
void breakable_terrain_crumble(struct MainObj*);
void breakable_terrain_remove(struct MainObj*);
static struct Unk_unk68 bt_player_box = { 0, -16, 8, 16 };
#define BT(sub, st) (state_reset(0, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), memset(&engine_obj, 0, sizeof(engine_obj)), state_terrain(0), g_Player.unk68 = NULL, so.active = 0x41, so.id = 0x28, so.unk2 = sub, so.state = st, so.ext.main_40.unk80 = sub >> 4, so.ext.main_40.unk81 = sub & 0xF, so.x_pos.i.hi = 0x1780, so.y_pos.i.hi = 0x520, background_objects[0].x_pos.i.hi = 0x1700, background_objects[0].y_pos.i.hi = 0x480, tile_writes_begin())
#define BTX() (state_extra = so.ext.main_40.timer | so.ext.main_40.trigger_time << 8 | (u32)so.ext.main_40.unk80 << 16 | (u32)(u8)so.hp << 24, state_extra ^= tile_writes_end(), engine_obj.stage = engine_obj.substage = 0, g_Player.unk68 = NULL)
static void bt_init_piece(void) { BT(0x20, 0), so.ext.main_40.unk80 = 0, func_80061DFC(&so), BTX(); }
static void bt_block_walked_into(void) { BT(0x10, 1), so.terrain_box = &D_800FEAA0, g_Player.unk68 = &bt_player_box, g_Player.x_pos.i.hi = 0x1770, g_Player.y_pos.i.hi = 0x520, func_80061F2C(&so), BTX(); }
#define CRUMBLE(sub, count, at, frame) (BT(sub, 2), engine_obj.stage = 3, engine_obj.substage = 1, so.ext.main_40.timer = count, so.ext.main_40.trigger_time = at, WEAPON_FRAME_COUNTER = frame)
static void bt_crumble_block_sparks(void) { CRUMBLE(0x10, 3, 0x2F, 0), breakable_terrain_crumble(&so), BTX(); }
static void bt_crumble_piece_stamp(void) { CRUMBLE(0x20, 9, 8, 0), tile_writes_expect(6, 0x1780 - 16, 0x520 - 32, 1), breakable_terrain_crumble(&so), BTX(); }
static void bt_crumble_piece(void) { CRUMBLE(0x20, 5, 8, 1), breakable_terrain_crumble(&so), BTX(); }
static void bt_crumble_end(void) { CRUMBLE(0x20, 1, 8, 1), breakable_terrain_crumble(&so), BTX(); }
static void bt_remove_piece(void) { CRUMBLE(0x20, 0, 8, 0), so.state = 3, tile_writes_expect(0xB, 0x1780 - 16, 0x520 - 32, 1), breakable_terrain_remove(&so), BTX(); }
static void bt_remove_block(void) { CRUMBLE(0x10, 0, 8, 0), so.state = 3, breakable_terrain_remove(&so), BTX(); }
static void (*const breakable_terrain_steps_cases[])(void) = {
    bt_init_piece,
    bt_block_walked_into,
    bt_crumble_block_sparks,
    bt_crumble_piece_stamp,
    bt_crumble_piece,
    bt_crumble_end,
    bt_remove_piece,
    bt_remove_block,
};
static const u32 breakable_terrain_steps_expected[] = {
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x20000u, 0x41000000u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x12F30u, 0x41000000u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x12F02u, 0x41002100u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0xE7F469C4u, 0x41000000u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x20804u, 0x41000000u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x20800u, 0x41000000u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x9BF30808u, 0x2100u,
    0x0u, 0x0u, 0x17800000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x10800u, 0x0u,
};
static u32 test_breakable_terrain_steps(u32 row)
{
    return state_run(breakable_terrain_steps_cases[row], row, &breakable_terrain_steps_expected[row * 10]);
}

static u32 main_paths(u32 row)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&visual_objects, 1, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = 1000;
    g_Player.unk68 = &D_800FEAA0;
    if (row == 0) {
        obj.bg_offset = -1;
        obj.x_pos.val = 6553600;
        obj.y_pos.val = 5242880;
        obj.ext.main_40.unk80 = 1;
        obj.unk2 = 0x10;
        obj.state = 0;
        func_80061DFC(&obj);
        obj.hp = 1;
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 1;
        weapon_objects[0].unk50 = (const u8*)D_800FEA24[1];
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        func_80061F2C(&obj);
        assert(obj.state == 2 && obj.hp == 0 && obj.on_screen == 0);
        assert(obj.ext.main_40.timer == 0x30 && obj.ext.main_40.trigger_time == 0x2F);
        return obj.state;
    }
    obj.bg_offset = 0;
    obj.x_pos.i.hi = 0x80;
    obj.y_pos.i.hi = 0x12F;
    obj.ext.main_40.unk80 = 3 + row;
    func_80061F2C(&obj);
    assert(obj.active == 0x41 && obj.state == 2);
    assert(obj.ext.main_40.timer == 0x10 && obj.ext.main_40.trigger_time == 8);
    return obj.ext.main_40.unk80;
}

const struct CTestGroup c_test_groups[] = {
    { "breakable_terrain_main", 0, 0, COUNT(breakable_terrain_main_cases), test_breakable_terrain_main },
    { "func_80061F2C", 0, 0, 3, test_func_80061F2C },
    { "main_paths", 0, 0, 4, main_paths },
    { "breakable_terrain_steps", 0, 0, COUNT(breakable_terrain_steps_cases), test_breakable_terrain_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(breakable_terrain_main_cases) + 3 + 4 + COUNT(breakable_terrain_steps_cases);
