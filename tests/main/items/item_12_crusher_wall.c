#include "test_runtime.h"
#include "main/items/item_12_crusher_wall.h"

static const u32 inputs_0[2][5] = {
    { 0, 0x41, 12, 1, 0x27 },
    { 8, 0x41, 12, 1, 0x27 },
};
struct crusher_wall_crush_case {
    u32 expected[1];
};
static const struct crusher_wall_crush_case crusher_wall_crush_cases[] = {
    { { 0x27u } },
    { { 0xFFFFFF80u } },
};
static u32 test_crusher_wall_crush(u32 row)
{
    const struct crusher_wall_crush_case* c = &crusher_wall_crush_cases[row];
    u32 observed_values[1];
    struct ItemObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.unk70 = inputs_0[row][0];
    obj.active = inputs_0[row][1];
    obj.id = inputs_0[row][2];
    obj.state = inputs_0[row][3];
    obj.x_pos.val = g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.hp = inputs_0[row][4];
    before = obj;
    player_before = g_Player;
    crusher_wall_crush(&obj);
    if (player_before.unk70 & 8) {
        player_before.hp = -0x80;
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)g_Player.hp;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 crusher_wall_player_near_expected[] = { 0u };
static u32 test_crusher_wall_player_near(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.x_pos.i.hi = 16430;
    return_value = crusher_wall_player_near(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, crusher_wall_player_near_expected, 1);
}

#include "support/state_cases.h"
void crusher_wall_update(struct ItemObj*);
void crusher_wall_rumble(struct ItemObj*);
#define cw state_room.item
#define CW(st, setup) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), cw.active = 1, cw.id = 0xC, cw.state = st, cw.x_pos.i.hi = 0x80, cw.y_pos.i.hi = 0x60, g_Player.unk68 = NULL, g_Player.unk70 = 0, g_Player.hp = 0x10, g_Player.x_pos.i.hi = 0x200, setup)
#define CWX() (state_extra = cw.unk7C.timer16 | (u32)(u8)g_Player.hp << 16 | (u32)(cw.ext.item_12.x_offset >> 8) << 24)
static void cw_update_on_screen(void)
{
    CW(2, 0), crusher_wall_update(&cw), CWX();
}
static void cw_update_away(void) { CW(2, cw.x_pos.i.hi = 0x1000), crusher_wall_update(&cw), CWX(); }
static void cw_rumble_smoke(void) { CW(1, (cw.unk7C.timer16 = 5, WEAPON_FRAME_COUNTER = 8, cw.ext.item_12.x_offset = 0x400)), crusher_wall_rumble(&cw), CWX(); }
static void cw_rumble_fast(void) { CW(1, (cw.unk2 = 1, cw.unk7C.timer16 = 5, WEAPON_FRAME_COUNTER = 9, cw.ext.item_12.x_offset = 0x400)), crusher_wall_rumble(&cw), CWX(); }
static void cw_rumble_end(void) { CW(1, (cw.unk7C.timer16 = 1, cw.unk5 = 2)), crusher_wall_rumble(&cw), CWX(); }
static void (*const crusher_wall_states_cases[])(void) = {
    cw_update_on_screen,
    cw_update_away,
    cw_rumble_smoke,
    cw_rumble_fast,
    cw_rumble_end,
};
static const u32 crusher_wall_states_expected[] = {
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x100000u,
    0x0u,
    0x3u,
    0x1u,
    0x10000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x100000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x5100004u,
    0x2100u,
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x6100004u,
    0x0u,
    0x202u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x100000u,
    0x0u,
};
static u32 test_crusher_wall_states(u32 row) { return object_run(crusher_wall_states_cases[row], row, &crusher_wall_states_expected[row * 10]); }
#undef cw
const struct CTestGroup c_test_groups[] = {
    { "crusher_wall_crush", 0, 0, 2, test_crusher_wall_crush },
    { "crusher_wall_player_near", 0, 0, 1, test_crusher_wall_player_near },
    { "crusher_wall_states", 0, 0, COUNT(crusher_wall_states_cases), test_crusher_wall_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + COUNT(crusher_wall_states_cases);
